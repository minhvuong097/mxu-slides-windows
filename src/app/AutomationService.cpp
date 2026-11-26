#include "AutomationService.h"
#include "AppController.h"

#include <QDateTime>
#include <QUuid>

namespace mxu::app {

AutomationService::AutomationService(QObject* parent)
    : QObject(parent)
{
    load();
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
    return false;
}

QVariantList AutomationService::triggers() const { return m_triggers; }
QVariantList AutomationService::schedules() const { return m_schedules; }

void AutomationService::load()
{
    m_triggers = m_store.value(QStringLiteral(u"mxu/triggers")).toList();
    m_schedules = m_store.value(QStringLiteral(u"mxu/schedules")).toList();
}

void AutomationService::save()
{
    m_store.setValue(QStringLiteral(u"mxu/triggers"), m_triggers);
    m_store.setValue(QStringLiteral(u"mxu/schedules"), m_schedules);
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

void AutomationService::tick()
{
    ++m_frames;
    emit changed();

    const QString now = QTime::currentTime().toString(QStringLiteral(u"hh:mm"));
    for (qsizetype i = 0; i < m_schedules.size(); ++i) {
        QVariantMap schedule = m_schedules.at(i).toMap();
        if (schedule.value(QStringLiteral(u"fired")).toBool()
            || schedule.value(QStringLiteral(u"time")).toString() != now)
            continue;
        schedule.insert(QStringLiteral(u"fired"), true);
        m_schedules[i] = schedule;
        fire(schedule.value(QStringLiteral(u"action")).toString());
        save();
        emit changed();
    }
}

} // namespace mxu::app
