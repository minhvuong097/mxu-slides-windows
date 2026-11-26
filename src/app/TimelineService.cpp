#include "TimelineService.h"

#include <QJsonDocument>
#include <QUuid>

namespace mxu::app {

TimelineService::TimelineService(QObject* parent)
    : QObject(parent)
{
    m_timer.setInterval(100);
    connect(&m_timer, &QTimer::timeout, this, &TimelineService::tick);

    addCue(QStringLiteral(u"Pre-roll"), QStringLiteral(u"slides"), 0, 5000);
    addCue(QStringLiteral(u"Welcome"), QStringLiteral(u"slides"), 6000, 4000);
    addCue(QStringLiteral(u"Amazing Grace"), QStringLiteral(u"slides"), 11000, 24000);
    addCue(QStringLiteral(u"Playlist"), QStringLiteral(u"audio"), 0, 60000);
}

QVariantList TimelineService::cues() const { return m_cues; }

QVariantList TimelineService::lanes() const
{
    return {
        QVariantMap{ { QStringLiteral(u"id"), QStringLiteral(u"slides") },
                     { QStringLiteral(u"name"), QStringLiteral(u"Slides") } },
        QVariantMap{ { QStringLiteral(u"id"), QStringLiteral(u"audio") },
                     { QStringLiteral(u"name"), QStringLiteral(u"Audio") } },
        QVariantMap{ { QStringLiteral(u"id"), QStringLiteral(u"media") },
                     { QStringLiteral(u"name"), QStringLiteral(u"Media") } },
    };
}

qint64 TimelineService::duration() const
{
    qint64 result = 60000;
    for (const QVariant& cue : m_cues) {
        const QVariantMap map = cue.toMap();
        result = qMax(result, map.value(QStringLiteral(u"at")).toLongLong()
                              + map.value(QStringLiteral(u"duration")).toLongLong());
    }
    return result;
}

QString TimelineService::addCue(const QString& name, const QString& lane, qint64 atMs, qint64 durationMs)
{
    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    m_cues.append(QVariantMap{
        { QStringLiteral(u"id"), id },
        { QStringLiteral(u"name"), name },
        { QStringLiteral(u"lane"), lane },
        { QStringLiteral(u"at"), atMs },
        { QStringLiteral(u"duration"), durationMs },
    });
    emit changed();
    return id;
}

bool TimelineService::moveCue(const QString& id, qint64 atMs)
{
    for (qsizetype i = 0; i < m_cues.size(); ++i) {
        QVariantMap cue = m_cues.at(i).toMap();
        if (cue.value(QStringLiteral(u"id")).toString() != id)
            continue;
        cue.insert(QStringLiteral(u"at"), qMax<qint64>(0, atMs));
        m_cues[i] = cue;
        emit changed();
        return true;
    }
    return false;
}

bool TimelineService::resizeCue(const QString& id, qint64 durationMs)
{
    for (qsizetype i = 0; i < m_cues.size(); ++i) {
        QVariantMap cue = m_cues.at(i).toMap();
        if (cue.value(QStringLiteral(u"id")).toString() != id)
            continue;
        cue.insert(QStringLiteral(u"duration"), qMax<qint64>(100, durationMs));
        m_cues[i] = cue;
        emit changed();
        return true;
    }
    return false;
}

bool TimelineService::removeCue(const QString& id)
{
    for (qsizetype i = 0; i < m_cues.size(); ++i) {
        if (m_cues.at(i).toMap().value(QStringLiteral(u"id")).toString() != id)
            continue;
        m_cues.removeAt(i);
        emit changed();
        return true;
    }
    return false;
}

void TimelineService::play() { m_playing = true; m_timer.start(); emit changed(); }
void TimelineService::pause() { m_playing = false; m_timer.stop(); emit changed(); }
void TimelineService::stop() { pause(); m_playhead = 0; emit changed(); }
void TimelineService::seek(qint64 ms) { m_playhead = qBound<qint64>(0, ms, duration()); emit changed(); }

void TimelineService::tick()
{
    const qint64 previous = m_playhead;
    m_playhead = qMin(duration(), m_playhead + 100);
    if (m_playhead >= duration())
        pause();
    for (const QVariant& cue : m_cues) {
        const QVariantMap map = cue.toMap();
        const qint64 at = map.value(QStringLiteral(u"at")).toLongLong();
        if (previous < at && m_playhead >= at)
            emit cueReached(map);
    }
    emit changed();
}

} // namespace mxu::app
