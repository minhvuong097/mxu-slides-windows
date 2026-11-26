#pragma once

#include <QObject>
#include <QString>
#include <QVariantList>

namespace mxu::app {

// Windows MIDI input via WinMM (midiInOpen/midiInStart). Compiles to a no-op
// stub on non-Windows hosts; on Windows it reports real devices and notes.
class WindowsMidiInput : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool available READ available CONSTANT)
    Q_PROPERTY(QVariantList devices READ devices NOTIFY changed)
    Q_PROPERTY(bool connected READ connected NOTIFY changed)
    Q_PROPERTY(int lastNote READ lastNote NOTIFY noteReceived)

public:
    explicit WindowsMidiInput(QObject* parent = nullptr);
    ~WindowsMidiInput() override;

    bool available() const;
    QVariantList devices() const;
    bool connected() const { return m_connected; }
    int lastNote() const { return m_lastNote; }

public slots:
    bool connectDevice(int index);
    void disconnectDevice();
    void refresh();
    Q_INVOKABLE void onNote(int note, bool on);

signals:
    void changed();
    void noteReceived(int note, bool on);
    void notification(const QString& message);

private:
    QVariantList m_devices;
    bool m_connected = false;
    int m_lastNote = -1;
    void* m_handle = nullptr;
};

} // namespace mxu::app
