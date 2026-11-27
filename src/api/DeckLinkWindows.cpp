#include "DeckLinkWindows.h"

#include <QSize>
#include <cstring>

// The native path needs the *Windows* Blackmagic DeckLink SDK headers (COM/MIDL
// generated, CLSID_CDeckLinkIterator, BSTR strings). The headers under
// vendor/decklink are the macOS flavour (CoreFoundation) and cannot be used
// here, so the real backend is opt-in: configure with -DMXU_ENABLE_DECKLINK=ON
// and -DDECKLINK_SDK_INCLUDE_DIR=<Windows SDK>/Win/include.
#if defined(Q_OS_WIN) && defined(MXU_HAS_DECKLINK_SDK)
#define MXU_DECKLINK_NATIVE 1
#define INITGUID
#include <windows.h>
#include <objbase.h>
#include <comdef.h>
#include "DeckLinkAPI.h"
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "uuid.lib")
#endif

namespace mxu::api {

DeckLinkWindows::DeckLinkWindows(QObject* parent)
    : QObject(parent)
{
    refresh();
}

DeckLinkWindows::~DeckLinkWindows()
{
    stop();
}

bool DeckLinkWindows::available() const
{
#ifdef MXU_DECKLINK_NATIVE
    return true;
#else
    return false;
#endif
}

void DeckLinkWindows::refresh()
{
    m_devices.clear();
#ifdef MXU_DECKLINK_NATIVE
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    IDeckLinkIterator* iterator = nullptr;
    if (CoCreateInstance(CLSID_CDeckLinkIterator, nullptr, CLSCTX_ALL,
                         IID_IDeckLinkIterator, reinterpret_cast<void**>(&iterator)) != S_OK) {
        emit changed();
        return;
    }
    IDeckLink* device = nullptr;
    int index = 0;
    while (iterator->Next(&device) == S_OK) {
        QString name = QStringLiteral(u"DeckLink %1").arg(index + 1);
        BSTR displayName = nullptr;
        if (device->GetDisplayName(&displayName) == S_OK && displayName) {
            name = QString::fromWCharArray(displayName);
            SysFreeString(displayName);
        }
        m_devices.append(QVariantMap{
            { QStringLiteral(u"index"), index },
            { QStringLiteral(u"name"), name },
        });
        device->Release();
        ++index;
        if (index >= 8)
            break;
    }
    iterator->Release();
#else
    m_devices.append(QVariantMap{ { QStringLiteral(u"index"), 0 },
                                  { QStringLiteral(u"name"), QStringLiteral(u"DeckLink unavailable") } });
#endif
    emit changed();
}

bool DeckLinkWindows::start(int index)
{
#ifdef MXU_DECKLINK_NATIVE
    if (m_active)
        return true;
    IDeckLinkIterator* iterator = nullptr;
    if (CoCreateInstance(CLSID_CDeckLinkIterator, nullptr, CLSCTX_ALL,
                         IID_IDeckLinkIterator, reinterpret_cast<void**>(&iterator)) != S_OK)
        return false;
    IDeckLink* device = nullptr;
    for (int i = 0; i <= index; ++i) {
        if (device) { device->Release(); device = nullptr; }
        if (iterator->Next(&device) != S_OK)
            break;
    }
    iterator->Release();
    if (!device)
        return false;

    IDeckLinkOutput* output = nullptr;
    if (device->QueryInterface(IID_IDeckLinkOutput, reinterpret_cast<void**>(&output)) != S_OK) {
        device->Release();
        emit errorOccurred(QStringLiteral(u"DeckLink output interface unavailable"));
        return false;
    }
    if (output->EnableVideoOutput(bmdModeHD1080p2997, bmdVideoOutputFlagDefault) != S_OK) {
        output->Release();
        device->Release();
        emit errorOccurred(QStringLiteral(u"Cannot enable DeckLink video output (1080p29.97)"));
        return false;
    }
    m_output = output;
    m_frame = nullptr;
    m_active = true;
    device->Release();
    emit changed();
    return true;
#else
    Q_UNUSED(index)
    emit errorOccurred(QStringLiteral(u"DeckLink support is not built in (enable MXU_ENABLE_DECKLINK with the Windows SDK)"));
    return false;
#endif
}

void DeckLinkWindows::stop()
{
#ifdef MXU_DECKLINK_NATIVE
    if (!m_output)
        return;
    auto* output = static_cast<IDeckLinkOutput*>(m_output);
    if (m_frame)
        static_cast<IDeckLinkMutableVideoFrame*>(m_frame)->Release();
    output->DisableVideoOutput();
    output->Release();
    m_output = nullptr;
    m_frame = nullptr;
#endif
    if (m_active) {
        m_active = false;
        emit changed();
    }
}

bool DeckLinkWindows::sendFrame(const QImage& input)
{
#ifdef MXU_DECKLINK_NATIVE
    if (!m_output || input.isNull())
        return false;
    // Output mode is fixed at 1080p29.97 (see start()), so always send 1920x1080.
    const QImage frame = input.size() == QSize(1920, 1080)
        ? input.convertToFormat(QImage::Format_ARGB32)
        : input.scaled(1920, 1080, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
              .convertToFormat(QImage::Format_ARGB32);
    auto* output = static_cast<IDeckLinkOutput*>(m_output);
    IDeckLinkMutableVideoFrame* videoFrame = nullptr;
    if (output->CreateVideoFrame(frame.width(), frame.height(), frame.bytesPerLine(),
                                 bmdFormat8BitBGRA, bmdFrameFlagDefault, &videoFrame) != S_OK)
        return false;
    void* bytes = nullptr;
    if (videoFrame->GetBytes(&bytes) == S_OK && bytes)
        memcpy(bytes, frame.constBits(), static_cast<size_t>(frame.sizeInBytes()));
    const HRESULT result = output->DisplayVideoFrameSync(videoFrame);
    videoFrame->Release();
    return result == S_OK;
#else
    Q_UNUSED(input)
    return false;
#endif
}

} // namespace mxu::api
