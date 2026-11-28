#include "AutomationService.h"
#include "AppController.h"

#include <QDateTime>
#include <QUuid>

namespace mxu::app {

namespace {
void recordHistory(QVariantList& history, const QString& name, const QString& action, const QString& source)
{
    history.prepend(QVariantMap{
        { QStringLiteral(u"at"), QTime::currentTime().toString(QStringLiteral(u"hh:mm:ss")) },
        { QStringLiteral(u"name"), name },
        { QStringLiteral(u"action"), action },
        { QStringLiteral(u"source"), source },
    });
    while (history.size() > 200)
        history.removeLast();
}
} // namespace

AutomationService::AutomationService(QObject* parent)
    : QObject(parent)
{
    load();
    connect(&m_midi, &WindowsMidiInput::quarterFrame, &m_timecode, &TimecodeService::quarterFrame);
    connect(&m_midi, &WindowsMidiInput::noteReceived, this, [this](int note, bool on) {
        if (!on)
            return;
        for (const QVariant& trigger : m_triggers) {
            const QVariantMap map = trigger.toMap();
            if (map.value(QStringLiteral(u"kind")).toString() == QStringLiteral(u"midi")
                && map.value(QStringLiteral(u"value")).toInt() == note)
                fire(map.value(QStringLiteral(u"action")).toString());
        }
    });
    m_timer.setInterval(100);
    connect(&m_timer, &QTimer::timeout, this, &AutomationService::tick);
    m_timer.start();
}

QString AutomationService::timecode() const
{
    const QTime now = QTime::currentTime();
    const int frames = m_frames % 30;
    return QStringLiteral(u"%1:%2:%3:%4")
        .arg(now.hour(), 2, 10, QChar(u'0'))
        .arg(now.minute(), 2, 10, QChar(u'0'))
        .arg(now.second(), 2, 10, QChar(u'0'))
        .arg(frames, 2, 10, QChar(u'0'));
}

QString AutomationService::timecodeSource() const
{
    return QStringLiteral(u"System clock (no MTC/LTC input)");
}

bool AutomationService::midiAvailable() const
{
    return m_midi.available();
}

QVariantList AutomationService::triggers() const { return m_triggers; }
QVariantList AutomationService::schedules() const { return m_schedules; }
QVariantList AutomationService::history() const { return m_history; }

void AutomationService::load()
{
    m_triggers = m_store.value(QStringLiteral(u"mxu/triggers")).toList();
    m_schedules = m_store.value(QStringLiteral(u"mxu/schedules")).toList();
    m_history = m_store.value(QStringLiteral(u"mxu/scheduleHistory")).toList();
    m_midiChannel = m_store.value(QStringLiteral(u"mxu/midiChannel"), -1).toInt();
}

void AutomationService::save()
{
    m_store.setValue(QStringLiteral(u"mxu/triggers"), m_triggers);
    m_store.setValue(QStringLiteral(u"mxu/schedules"), m_schedules);
    m_store.setValue(QStringLiteral(u"mxu/scheduleHistory"), m_history);
    m_store.setValue(QStringLiteral(u"mxu/midiChannel"), m_midiChannel);
    m_store.sync();
}

bool AutomationService::fire(const QString& action)
{
    if (!m_controller)
        return false;
    if (action == QStringLiteral(u"next")) QMetaObject::invokeMethod(m_controller, "next", Qt::QueuedConnection);
    else if (action == QStringLiteral(u"previous")) QMetaObject::invokeMethod(m_controller, "previous", Qt::QueuedConnection);
    else if (action == QStringLiteral(u"clear")) QMetaObject::invokeMethod(m_controller, "toggleClear", Qt::QueuedConnection);
    else if (action == QStringLiteral(u"present")) QMetaObject::invokeMethod(m_controller, "setPresenting", Qt::QueuedConnection, Q_ARG(bool, true));
    else if (action == QStringLiteral(u"stop")) QMetaObject::invokeMethod(m_controller, "setPresenting", Qt::QueuedConnection, Q_ARG(bool, false));
    else if (action == QStringLiteral(u"stage")) QMetaObject::invokeMethod(m_controller, "toggleStageOutput", Qt::QueuedConnection);
    else return false;
    emit notification(QStringLiteral(u"Trigger: %1").arg(action));
    return true;
}

bool AutomationService::addKeyTrigger(const QString& action, const QString& key)
{
    if (action.isEmpty() || key.isEmpty())
        return false;
    m_triggers.append(QVariantMap{
        { QStringLiteral(u"id"), QUuid::createUuid().toString(QUuid::WithoutBraces) },
        { QStringLiteral(u"kind"), QStringLiteral(u"key") },
        { QStringLiteral(u"action"), action },
        { QStringLiteral(u"value"), key },
    });
    save();
    emit changed();
    return true;
}

bool AutomationService::addMidiTrigger(const QString& action, int note)
{
    if (action.isEmpty() || note < 0 || note > 127)
        return false;
    m_triggers.append(QVariantMap{
        { QStringLiteral(u"id"), QUuid::createUuid().toString(QUuid::WithoutBraces) },
        { QStringLiteral(u"kind"), QStringLiteral(u"midi") },
        { QStringLiteral(u"action"), action },
        { QStringLiteral(u"value"), note },
        { QStringLiteral(u"noteName"), midiNoteName(note) },
        { QStringLiteral(u"channel"), -1 },
        { QStringLiteral(u"velocityAsIndex"), false },
    });
    save();
    emit changed();
    return true;
}

bool AutomationService::removeTrigger(const QString& id)
{
    for (qsizetype i = 0; i < m_triggers.size(); ++i) {
        if (m_triggers.at(i).toMap().value(QStringLiteral(u"id")).toString() != id)
            continue;
        m_triggers.removeAt(i);
        save();
        emit changed();
        return true;
    }
    return false;
}

bool AutomationService::addSchedule(const QString& name, const QString& time, const QString& action)
{
    if (name.isEmpty() || !QTime::fromString(time, QStringLiteral(u"hh:mm")).isValid())
        return false;
    m_schedules.append(QVariantMap{
        { QStringLiteral(u"id"), QUuid::createUuid().toString(QUuid::WithoutBraces) },
        { QStringLiteral(u"name"), name },
        { QStringLiteral(u"time"), time },
        { QStringLiteral(u"action"), action },
        { QStringLiteral(u"fired"), false },
        { QStringLiteral(u"enabled"), true },
    });
    save();
    emit changed();
    return true;
}

bool AutomationService::removeSchedule(const QString& id)
{
    for (qsizetype i = 0; i < m_schedules.size(); ++i) {
        if (m_schedules.at(i).toMap().value(QStringLiteral(u"id")).toString() != id)
            continue;
        m_schedules.removeAt(i);
        save();
        emit changed();
        return true;
    }
    return false;
}

void AutomationService::setMidiChannel(int channel)
{
    m_midiChannel = channel < 1 ? -1 : qMin(channel, 16);
    save();
    emit changed();
}

QString AutomationService::midiNoteName(int note) const
{
    static const char* names[] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
    if (note < 0 || note > 127)
        return QStringLiteral(u"—");
    return QStringLiteral(u"%1%2").arg(QLatin1String(names[note % 12])).arg(note / 12 - 1);
}

bool AutomationService::configureMidiTrigger(const QString& id, int channel, bool velocityAsIndex)
{
    for (qsizetype i = 0; i < m_triggers.size(); ++i) {
        QVariantMap trigger = m_triggers.at(i).toMap();
        if (trigger.value(QStringLiteral(u"id")).toString() != id
            || trigger.value(QStringLiteral(u"kind")).toString() != QStringLiteral(u"midi"))
            continue;
        trigger.insert(QStringLiteral(u"channel"), channel);
        trigger.insert(QStringLiteral(u"velocityAsIndex"), velocityAsIndex);
        m_triggers[i] = trigger;
        save();
        emit changed();
        return true;
    }
    return false;
}

bool AutomationService::setScheduleEnabled(const QString& id, bool enabled)
{
    for (qsizetype i = 0; i < m_schedules.size(); ++i) {
        QVariantMap schedule = m_schedules.at(i).toMap();
        if (schedule.value(QStringLiteral(u"id")).toString() != id)
            continue;
        schedule.insert(QStringLiteral(u"enabled"), enabled);
        m_schedules[i] = schedule;
        save();
        emit changed();
        return true;
    }
    return false;
}

bool AutomationService::resetSchedule(const QString& id)
{
    for (qsizetype i = 0; i < m_schedules.size(); ++i) {
        QVariantMap schedule = m_schedules.at(i).toMap();
        if (schedule.value(QStringLiteral(u"id")).toString() != id)
            continue;
        schedule.insert(QStringLiteral(u"fired"), false);
        m_schedules[i] = schedule;
        save();
        emit changed();
        return true;
    }
    return false;
}

bool AutomationService::fireSchedule(const QString& id)
{
    for (qsizetype i = 0; i < m_schedules.size(); ++i) {
        QVariantMap schedule = m_schedules.at(i).toMap();
        if (schedule.value(QStringLiteral(u"id")).toString() != id)
            continue;
        const QString action = schedule.value(QStringLiteral(u"action")).toString();
        fire(action);
        recordHistory(m_history, schedule.value(QStringLiteral(u"name")).toString(), action,
                      QStringLiteral(u"manual"));
        schedule.insert(QStringLiteral(u"fired"), true);
        m_schedules[i] = schedule;
        save();
        emit changed();
        return true;
    }
    return false;
}

bool AutomationService::clearHistory()
{
    m_history.clear();
    save();
    emit changed();
    return true;
}

void AutomationService::tick()
{
    ++m_frames;
    emit changed();

    const QString now = QTime::currentTime().toString(QStringLiteral(u"hh:mm"));
    for (qsizetype i = 0; i < m_schedules.size(); ++i) {
        QVariantMap schedule = m_schedules.at(i).toMap();
        if (schedule.value(QStringLiteral(u"fired")).toBool()
            || !schedule.value(QStringLiteral(u"enabled"), true).toBool()
            || schedule.value(QStringLiteral(u"time")).toString() != now)
            continue;
        schedule.insert(QStringLiteral(u"fired"), true);
        m_schedules[i] = schedule;
        const QString action = schedule.value(QStringLiteral(u"action")).toString();
        fire(action);
        recordHistory(m_history, schedule.value(QStringLiteral(u"name")).toString(), action,
                      QStringLiteral(u"scheduled"));
        save();
        emit changed();
    }
}

} // namespace mxu::app
