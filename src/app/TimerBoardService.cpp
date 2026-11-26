#include "TimerBoardService.h"

#include <QDateTime>
#include <QUuid>

namespace mxu::app {

TimerBoardService::TimerBoardService(QObject* parent)
    : QObject(parent)
{
    add(QStringLiteral(u"Pre-Service Preroll"), 155, 30);
    m_clock.setInterval(1000);
    connect(&m_clock, &QTimer::timeout, this, &TimerBoardService::tick);
    m_clock.start();
}

QVariantList TimerBoardService::timers() const { return m_timers; }

QString TimerBoardService::add(const QString& name, qint64 seconds, int warnSeconds, const QString& mode)
{
    if (name.trimmed().isEmpty())
        return {};
    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    m_timers.append(QVariantMap{
        { QStringLiteral(u"id"), id },
        { QStringLiteral(u"name"), name.trimmed() },
        { QStringLiteral(u"total"), seconds },
        { QStringLiteral(u"remaining"), seconds },
        { QStringLiteral(u"warn"), warnSeconds },
        { QStringLiteral(u"mode"), mode },
        { QStringLiteral(u"running"), false },
        { QStringLiteral(u"warned"), false },
    });
    emit changed();
    return id;
}

bool TimerBoardService::start(const QString& id)
{
    for (qsizetype i = 0; i < m_timers.size(); ++i) {
        QVariantMap timer = m_timers.at(i).toMap();
        if (timer.value(QStringLiteral(u"id")).toString() != id)
            continue;
        if (timer.value(QStringLiteral(u"mode")).toString() == QStringLiteral(u"countdownToTime")) {
            const QTime target = QTime::fromString(timer.value(QStringLiteral(u"name")).toString(),
                                                   QStringLiteral(u"hh:mm"));
            if (target.isValid())
                timer.insert(QStringLiteral(u"remaining"),
                             QTime::currentTime().secsTo(target));
        }
        timer.insert(QStringLiteral(u"running"), true);
        m_timers[i] = timer;
        emit changed();
        return true;
    }
    return false;
}

bool TimerBoardService::pause(const QString& id)
{
    for (qsizetype i = 0; i < m_timers.size(); ++i) {
        QVariantMap timer = m_timers.at(i).toMap();
        if (timer.value(QStringLiteral(u"id")).toString() != id)
            continue;
        timer.insert(QStringLiteral(u"running"), false);
        m_timers[i] = timer;
        emit changed();
        return true;
    }
    return false;
}

bool TimerBoardService::reset(const QString& id)
{
    for (qsizetype i = 0; i < m_timers.size(); ++i) {
        QVariantMap timer = m_timers.at(i).toMap();
        if (timer.value(QStringLiteral(u"id")).toString() != id)
            continue;
        timer.insert(QStringLiteral(u"remaining"), timer.value(QStringLiteral(u"total")).toLongLong());
        timer.insert(QStringLiteral(u"running"), false);
        timer.insert(QStringLiteral(u"warned"), false);
        m_timers[i] = timer;
        emit changed();
        return true;
    }
    return false;
}

bool TimerBoardService::remove(const QString& id)
{
    for (qsizetype i = 0; i < m_timers.size(); ++i) {
        if (m_timers.at(i).toMap().value(QStringLiteral(u"id")).toString() != id)
            continue;
        m_timers.removeAt(i);
        emit changed();
        return true;
    }
    return false;
}

void TimerBoardService::stopAll()
{
    for (qsizetype i = 0; i < m_timers.size(); ++i) {
        QVariantMap timer = m_timers.at(i).toMap();
        timer.insert(QStringLiteral(u"running"), false);
        m_timers[i] = timer;
    }
    emit changed();
}

void TimerBoardService::tick()
{
    int running = 0;
    bool anyChanged = false;
    for (qsizetype i = 0; i < m_timers.size(); ++i) {
        QVariantMap timer = m_timers.at(i).toMap();
        if (!timer.value(QStringLiteral(u"running")).toBool())
            continue;
        ++running;
        const QString mode = timer.value(QStringLiteral(u"mode")).toString();
        qint64 remaining = timer.value(QStringLiteral(u"remaining")).toLongLong();
        if (mode == QStringLiteral(u"countUp"))
            remaining += 1;
        else
            remaining -= 1;
        timer.insert(QStringLiteral(u"remaining"), qMax<qint64>(0, remaining));
        if (remaining <= timer.value(QStringLiteral(u"warn")).toInt()
            && !timer.value(QStringLiteral(u"warned")).toBool() && mode != QStringLiteral(u"countUp")) {
            timer.insert(QStringLiteral(u"warned"), true);
            emit warning(timer.value(QStringLiteral(u"name")).toString());
        }
        if (remaining <= 0 && mode != QStringLiteral(u"countUp")) {
            timer.insert(QStringLiteral(u"running"), false);
            emit expired(timer.value(QStringLiteral(u"name")).toString());
        }
        m_timers[i] = timer;
        anyChanged = true;
    }
    m_running = running;
    if (anyChanged)
        emit changed();
}

} // namespace mxu::app
