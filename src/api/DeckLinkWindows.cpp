#include "DeckLinkWindows.h"

#ifdef Q_OS_WIN
#define INITGUID
#include <windows.h>
#include <objbase.h>
#include "DeckLinkAPI.h"
#pragma comment(lib, "ole32.lib")
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
#ifdef Q_OS_WIN
    return true;
#else
    return false;
#endif
}

void DeckLinkWindows::refresh()
{
    m_devices.clear();
#ifdef Q_OS_WIN
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    IDeckLinkIterator* iterator = nullptr;
    if (CoCreateInstance(CLSID_DeckLinkIterator, nullptr, CLSCTX_ALL,
                         IID_IDeckLinkIterator, reinterpret_cast<void**>(&iterator)) != S_OK)
        return;
    IDeckLink* device = nullptr;
    int index = 0;
    while (iterator->Next(&device) == S_OK) {
        IDeckLinkDisplayMode* mode = nullptr;
        QString name = QStringLiteral(u"DeckLink %1").arg(index + 1);
        if (device->GetDisplayName(&mode) == S_OK && mode) {
            // GetDisplayName returns a string via IDeckLinkString in newer SDKs;
            // fall back to index-based naming for compatibility.
            mode->Release();
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
#ifdef Q_OS_WIN
    if (m_active)
        return true;
    IDeckLinkIterator* iterator = nullptr;
    if (CoCreateInstance(CLSID_DeckLinkIterator, nullptr, CLSCTX_ALL,
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
        emit errorOccurred(QStringLiteral(u"Cannot enable DeckLink video output"));
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
    emit errorOccurred(QStringLiteral(u"DeckLink is available on Windows only"));
    return false;
#endif
}

void DeckLinkWindows::stop()
{
#ifdef Q_OS_WIN
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
#ifdef Q_OS_WIN
    if (!m_output || input.isNull())
        return false;
    const QImage frame = input.convertToFormat(QImage::Format_ARGB32);
    auto* output = static_cast<IDeckLinkOutput*>(m_output);
    IDeckLinkMutableVideoFrame* videoFrame = nullptr;
    if (output->CreateVideoFrame(frame.width(), frame.height(), frame.bytesPerLine(),
                                 bmdFormat8BitBGRA, bmdFrameFlagDefault, &videoFrame) != S_OK)
        return false;
    void* bytes = nullptr;
    if (videoFrame->GetBytes(&bytes) == S_OK)
        memcpy(bytes, frame.constBits(), static_cast<size_t>(frame.sizeInBytes()));
    const auto result = output->ScheduleVideoFrame(videoFrame, 0, 0, 90000);
    videoFrame->Release();
    return result == S_OK;
#else
    Q_UNUSED(input)
    return false;
#endif
}

} // namespace mxu::api
