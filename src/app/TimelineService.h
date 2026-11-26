#pragma once

#include <QObject>
#include <QTimer>
#include <QVariantList>
#include <QVariantMap>

namespace mxu::app {

// Cue timeline with a playhead, lanes and movable blocks — a compact version
// of the macOS PresentationTimelineController/TimelineEngine.
class TimelineService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList cues READ cues NOTIFY changed)
    Q_PROPERTY(QVariantList lanes READ lanes CONSTANT)
    Q_PROPERTY(qint64 playhead READ playhead NOTIFY changed)
    Q_PROPERTY(bool playing READ playing NOTIFY changed)
    Q_PROPERTY(qint64 duration READ duration NOTIFY changed)

public:
    explicit TimelineService(QObject* parent = nullptr);

    QVariantList cues() const;
    QVariantList lanes() const;
    qint64 playhead() const { return m_playhead; }
    bool playing() const { return m_playing; }
    qint64 duration() const;

public slots:
    QString addCue(const QString& name, const QString& lane, qint64 atMs, qint64 durationMs);
    bool moveCue(const QString& id, qint64 atMs);
    bool resizeCue(const QString& id, qint64 durationMs);
    bool removeCue(const QString& id);
    void play();
    void pause();
    void stop();
    void seek(qint64 ms);

signals:
    void changed();
    void cueReached(const QVariantMap& cue);

private slots:
    void tick();

private:
    QVariantList m_cues;
    QTimer m_timer;
    qint64 m_playhead = 0;
    bool m_playing = false;
};

} // namespace mxu::app
