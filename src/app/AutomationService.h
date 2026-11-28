#pragma once

#include "TimecodeService.h"
#include "WindowsMidiInput.h"

#include <QObject>
#include <QSettings>
#include <QString>
#include <QTimer>
#include <QVariantList>
#include <QVariantMap>

namespace mxu::app {

class AppController;

// Keyboard/MIDI triggers, a simple scheduler and timecode display — the
// Windows counterparts of the macOS KeyInController, MIDIInController,
// SchedulerController and TimecodeFollower.
class AutomationService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString timecode READ timecode NOTIFY changed)
    Q_PROPERTY(QString timecodeSource READ timecodeSource NOTIFY changed)
    Q_PROPERTY(bool midiAvailable READ midiAvailable CONSTANT)
    Q_PROPERTY(QObject* midiInput READ midiInput CONSTANT)
    Q_PROPERTY(QObject* timecodeDecoder READ timecodeDecoder CONSTANT)
    Q_PROPERTY(QVariantList triggers READ triggers NOTIFY changed)
    Q_PROPERTY(QVariantList schedules READ schedules NOTIFY changed)
    Q_PROPERTY(QVariantList history READ history NOTIFY changed)
    Q_PROPERTY(int midiChannel READ midiChannel WRITE setMidiChannel NOTIFY changed)

public:
    explicit AutomationService(QObject* parent = nullptr);
    void attach(AppController* controller) { m_controller = controller; }

    QString timecode() const;
    QString timecodeSource() const;
    bool midiAvailable() const;
    QObject* midiInput() { return &m_midi; }
    QObject* timecodeDecoder() { return &m_timecode; }
    QVariantList triggers() const;
    QVariantList schedules() const;
    QVariantList history() const;
    int midiChannel() const { return m_midiChannel; }
    void setMidiChannel(int channel);
    Q_INVOKABLE QString midiNoteName(int note) const;

public slots:
    bool fire(const QString& action);
    bool addKeyTrigger(const QString& action, const QString& key);
    bool addMidiTrigger(const QString& action, int note);
    bool configureMidiTrigger(const QString& id, int channel, bool velocityAsIndex);
    bool removeTrigger(const QString& id);
    bool addSchedule(const QString& name, const QString& time, const QString& action);
    bool removeSchedule(const QString& id);
    bool setScheduleEnabled(const QString& id, bool enabled);
    bool resetSchedule(const QString& id);
    bool fireSchedule(const QString& id);
    bool clearHistory();

signals:
    void changed();
    void notification(const QString& message);

private slots:
    void tick();

private:
    void load();
    void save();

    QSettings m_store;
    WindowsMidiInput m_midi;
    TimecodeService m_timecode;
    AppController* m_controller = nullptr;
    QVariantList m_triggers;
    QVariantList m_schedules;
    QVariantList m_history;
    int m_midiChannel = -1;
    QTimer m_timer;
    int m_frames = 0;
};

} // namespace mxu::app
