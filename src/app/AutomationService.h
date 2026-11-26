#pragma once

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
    Q_PROPERTY(QVariantList triggers READ triggers NOTIFY changed)
    Q_PROPERTY(QVariantList schedules READ schedules NOTIFY changed)

public:
    explicit AutomationService(QObject* parent = nullptr);
    void attach(AppController* controller) { m_controller = controller; }

    QString timecode() const;
    QString timecodeSource() const;
    bool midiAvailable() const;
    QVariantList triggers() const;
    QVariantList schedules() const;

public slots:
    bool fire(const QString& action);
    bool addKeyTrigger(const QString& action, const QString& key);
    bool addMidiTrigger(const QString& action, int note);
    bool removeTrigger(const QString& id);
    bool addSchedule(const QString& name, const QString& time, const QString& action);
    bool removeSchedule(const QString& id);

signals:
    void changed();
    void notification(const QString& message);

private slots:
    void tick();

private:
    void load();
    void save();

    QSettings m_store;
    AppController* m_controller = nullptr;
    QVariantList m_triggers;
    QVariantList m_schedules;
    QTimer m_timer;
    int m_frames = 0;
};

} // namespace mxu::app
