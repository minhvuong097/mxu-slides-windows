#pragma once

#include <QObject>
#include <QVariantList>
#include <QVariantMap>

namespace mxu::app {

// Audio/media playlist with shuffle, repeat and crossfade, equivalent to the
// macOS PlaylistQueue. Entries reference local media paths.
class PlaylistService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList entries READ entries NOTIFY changed)
    Q_PROPERTY(int currentIndex READ currentIndex NOTIFY changed)
    Q_PROPERTY(QString playMode READ playMode WRITE setPlayMode NOTIFY changed)
    Q_PROPERTY(double crossfade READ crossfade WRITE setCrossfade NOTIFY changed)

public:
    explicit PlaylistService(QObject* parent = nullptr);

    QVariantList entries() const;
    int currentIndex() const { return m_current; }
    QString playMode() const { return m_playMode; }
    double crossfade() const { return m_crossfade; }
    void setPlayMode(const QString& value);
    void setCrossfade(double value);

public slots:
    QString add(const QString& name, const QString& path);
    bool remove(const QString& id);
    QString next();
    void reset();

signals:
    void changed();
    void entryStarted(const QVariantMap& entry);

private:
    QVariantList m_entries;
    int m_current = -1;
    QString m_playMode = QStringLiteral(u"playAll");
    double m_crossfade = 2.0;
};

} // namespace mxu::app
