#include "TimelineService.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QStringList>
#include <QUuid>
#include <QtMath>

namespace mxu::app {

namespace {
// Deterministic waveform bars for a clip (real PCM analysis is provided by
// MediaService when a concrete media source is attached).
QVariantList waveformFor(const QString& seed, qint64 durationMs)
{
    QVariantList bars;
    const int count = qBound(12, static_cast<int>(durationMs / 500), 96);
    quint32 hash = 2166136261;
    for (const QChar ch : seed)
        hash = (hash ^ static_cast<quint32>(ch.unicode())) * 16777619;
    for (int i = 0; i < count; ++i) {
        hash = hash * 1664525 + 1013904223;
        const double amplitude = 0.18 + 0.82 * qAbs(qSin((hash >> 8) / 8388607.0 * 3.14159));
        bars.append(amplitude);
    }
    return bars;
}
} // namespace

TimelineService::TimelineService(QObject* parent)
    : QObject(parent)
{
    m_timer.setInterval(100);
    connect(&m_timer, &QTimer::timeout, this, &TimelineService::tick);
    load();
    if (m_cues.isEmpty()) {
        addCue(QStringLiteral(u"Pre-roll"), QStringLiteral(u"slides"), 0, 5000);
        addCue(QStringLiteral(u"Welcome"), QStringLiteral(u"slides"), 6000, 4000);
        addCue(QStringLiteral(u"Amazing Grace"), QStringLiteral(u"slides"), 11000, 24000);
        addCue(QStringLiteral(u"Playlist"), QStringLiteral(u"audio"), 0, 60000);
    }
}

void TimelineService::load()
{
    m_cues = m_store.value(QStringLiteral(u"mxu/timelineCues")).toList();
}

void TimelineService::save()
{
    m_store.setValue(QStringLiteral(u"mxu/timelineCues"), m_cues);
    m_store.sync();
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
        { QStringLiteral(u"source"), QString() },
        { QStringLiteral(u"color"), lane == QStringLiteral(u"audio") ? QStringLiteral(u"#0a64c8")
                                   : (lane == QStringLiteral(u"media") ? QStringLiteral(u"#8a3fc8")
                                                                        : QStringLiteral(u"#1f8f3f")) },
        { QStringLiteral(u"locked"), false },
        { QStringLiteral(u"fadeInMs"), 0 },
        { QStringLiteral(u"fadeOutMs"), 0 },
        { QStringLiteral(u"volume"), 1.0 },
        { QStringLiteral(u"waveform"), waveformFor(name, durationMs) },
    });
    save();
    emit changed();
    return id;
}

bool TimelineService::moveCue(const QString& id, qint64 atMs)
{
    for (qsizetype i = 0; i < m_cues.size(); ++i) {
        QVariantMap cue = m_cues.at(i).toMap();
        if (cue.value(QStringLiteral(u"id")).toString() != id || cue.value(QStringLiteral(u"locked")).toBool())
            continue;
        cue.insert(QStringLiteral(u"at"), qMax<qint64>(0, atMs));
        m_cues[i] = cue;
        save();
        emit changed();
        return true;
    }
    return false;
}

bool TimelineService::resizeCue(const QString& id, qint64 durationMs)
{
    for (qsizetype i = 0; i < m_cues.size(); ++i) {
        QVariantMap cue = m_cues.at(i).toMap();
        if (cue.value(QStringLiteral(u"id")).toString() != id || cue.value(QStringLiteral(u"locked")).toBool())
            continue;
        cue.insert(QStringLiteral(u"duration"), qMax<qint64>(100, durationMs));
        cue.insert(QStringLiteral(u"waveform"), waveformFor(cue.value(QStringLiteral(u"name")).toString(), durationMs));
        m_cues[i] = cue;
        save();
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
        save();
        emit changed();
        return true;
    }
    return false;
}

bool TimelineService::setCueProp(const QString& id, const QString& key, const QVariant& value)
{
    static const QStringList editable{ QStringLiteral(u"name"), QStringLiteral(u"source"),
        QStringLiteral(u"color"), QStringLiteral(u"fadeInMs"), QStringLiteral(u"fadeOutMs"),
        QStringLiteral(u"volume"), QStringLiteral(u"tags"), QStringLiteral(u"waveform") };
    if (!editable.contains(key))
        return false;
    for (qsizetype i = 0; i < m_cues.size(); ++i) {
        QVariantMap cue = m_cues.at(i).toMap();
        if (cue.value(QStringLiteral(u"id")).toString() != id)
            continue;
        cue.insert(key, value);
        if (key == QStringLiteral(u"name"))
            cue.insert(QStringLiteral(u"waveform"), waveformFor(value.toString(),
                          cue.value(QStringLiteral(u"duration")).toLongLong()));
        m_cues[i] = cue;
        save();
        emit changed();
        return true;
    }
    return false;
}

bool TimelineService::toggleLock(const QString& id)
{
    for (qsizetype i = 0; i < m_cues.size(); ++i) {
        QVariantMap cue = m_cues.at(i).toMap();
        if (cue.value(QStringLiteral(u"id")).toString() != id)
            continue;
        cue.insert(QStringLiteral(u"locked"), !cue.value(QStringLiteral(u"locked")).toBool());
        m_cues[i] = cue;
        save();
        emit changed();
        return true;
    }
    return false;
}

bool TimelineService::duplicateCue(const QString& id)
{
    for (const QVariant& item : m_cues) {
        QVariantMap cue = item.toMap();
        if (cue.value(QStringLiteral(u"id")).toString() != id)
            continue;
        const qint64 at = cue.value(QStringLiteral(u"at")).toLongLong()
                          + cue.value(QStringLiteral(u"duration")).toLongLong();
        addCue(cue.value(QStringLiteral(u"name")).toString() + QStringLiteral(u" copy"),
               cue.value(QStringLiteral(u"lane")).toString(), at,
               cue.value(QStringLiteral(u"duration")).toLongLong());
        return true;
    }
    return false;
}

QString TimelineService::timecodeAt(qint64 ms) const
{
    const qint64 total = qMax<qint64>(0, ms / 1000);
    const int frames = static_cast<int>((ms % 1000) * 30 / 1000);
    return QStringLiteral(u"%1:%2:%3:%4")
        .arg(total / 3600, 2, 10, QChar(u'0'))
        .arg((total / 60) % 60, 2, 10, QChar(u'0'))
        .arg(total % 60, 2, 10, QChar(u'0'))
        .arg(frames, 2, 10, QChar(u'0'));
}

bool TimelineService::seekTimecode(const QString& timecode)
{
    const QStringList parts = timecode.split(QLatin1Char(':'));
    qint64 seconds = 0;
    if (parts.size() == 4) {
        seconds = parts.at(0).toLongLong() * 3600 + parts.at(1).toLongLong() * 60
                  + parts.at(2).toLongLong();
        seek(seconds * 1000 + parts.at(3).toLongLong() * 1000 / 30);
        return true;
    }
    if (parts.size() == 3) {
        seconds = parts.at(0).toLongLong() * 60 + parts.at(1).toLongLong();
        seek(seconds * 1000 + parts.at(2).toLongLong() * 1000 / 30);
        return true;
    }
    if (parts.size() == 2) {
        seek((parts.at(0).toLongLong() * 60 + parts.at(1).toLongLong()) * 1000);
        return true;
    }
    return false;
}

QString TimelineService::exportJson() const
{
    return QString::fromUtf8(QJsonDocument::fromVariant(m_cues).toJson(QJsonDocument::Indented));
}

bool TimelineService::importJson(const QString& json)
{
    const QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    if (!document.isArray())
        return false;
    m_cues = document.array().toVariantList();
    save();
    emit changed();
    return true;
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
