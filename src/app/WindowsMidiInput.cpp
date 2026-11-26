#include "WindowsMidiInput.h"

#ifdef Q_OS_WIN
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#endif

namespace mxu::app {

namespace {
#ifdef Q_OS_WIN
void CALLBACK midiCallback(HMIDIIN, UINT message, DWORD_PTR instance, DWORD_PTR param1, DWORD_PTR)
{
    auto* self = reinterpret_cast<WindowsMidiInput*>(instance);
    if (!self)
        return;
    if (message == MIM_DATA) {
        const int status = static_cast<int>(param1 & 0xFF);
        const int note = static_cast<int>((param1 >> 8) & 0x7F);
        const int velocity = static_cast<int>((param1 >> 16) & 0x7F);
        if ((status & 0xF0) == 0x90 || (status & 0xF0) == 0x80)
            QMetaObject::invokeMethod(self, "onNote", Qt::QueuedConnection,
                                      Q_ARG(int, note), Q_ARG(bool, (status & 0xF0) == 0x90 && velocity > 0));
    }
}
#endif
}

WindowsMidiInput::WindowsMidiInput(QObject* parent)
    : QObject(parent)
{
    refresh();
}

WindowsMidiInput::~WindowsMidiInput()
{
    disconnectDevice();
}

bool WindowsMidiInput::available() const
{
#ifdef Q_OS_WIN
    return true;
#else
    return false;
#endif
}

QVariantList WindowsMidiInput::devices() const { return m_devices; }

void WindowsMidiInput::onNote(int note, bool on)
{
    m_lastNote = note;
    emit noteReceived(note, on);
    emit changed();
}

void WindowsMidiInput::refresh()
{
    m_devices.clear();
#ifdef Q_OS_WIN
    const UINT count = midiInGetNumDevs();
    for (UINT i = 0; i < count; ++i) {
        MIDIINCAPS caps;
        if (midiInGetDevCaps(i, &caps, sizeof(caps)) != MMSYSERR_NOERROR)
            continue;
        m_devices.append(QVariantMap{
            { QStringLiteral(u"index"), static_cast<int>(i) },
            { QStringLiteral(u"name"), QString::fromWCharArray(caps.szPname) },
        });
    }
#else
    m_devices.append(QVariantMap{
        { QStringLiteral(u"index"), 0 },
        { QStringLiteral(u"name"), QStringLiteral(u"MIDI unavailable on this host") },
    });
#endif
    emit changed();
}

bool WindowsMidiInput::connectDevice(int index)
{
#ifdef Q_OS_WIN
    if (m_connected || index < 0 || index >= static_cast<int>(midiInGetNumDevs()))
        return false;
    HMIDIIN handle = nullptr;
    const MMRESULT result = midiInOpen(&handle, index,
                                       reinterpret_cast<DWORD_PTR>(&midiCallback),
                                       reinterpret_cast<DWORD_PTR>(this),
                                       CALLBACK_FUNCTION);
    if (result != MMSYSERR_NOERROR)
        return false;
    m_handle = handle;
    midiInStart(handle);
    m_connected = true;
    emit changed();
    emit notification(QStringLiteral(u"MIDI device %1 connected").arg(index));
    return true;
#else
    Q_UNUSED(index)
    return false;
#endif
}

void WindowsMidiInput::disconnectDevice()
{
#ifdef Q_OS_WIN
    if (!m_connected || !m_handle)
        return;
    auto* handle = static_cast<HMIDIIN>(m_handle);
    midiInStop(handle);
    midiInClose(handle);
    m_handle = nullptr;
    m_connected = false;
    emit changed();
#endif
}

} // namespace mxu::app
