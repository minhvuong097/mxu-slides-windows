#pragma once

#include <QPropertyAnimation>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QObject>
#include <QVector>

namespace mxu::app {

// Program audio + simple mixer with mute/solo/volume, built on Qt Multimedia
// (WASAPI on Windows). Mirrors the Mac app's AudioController/AudioMixer basics.
class AudioService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList channels READ channels NOTIFY changed)
    Q_PROPERTY(bool playing READ playing NOTIFY changed)

public:
    explicit AudioService(QObject* parent = nullptr);
    ~AudioService() override;

    QVariantList channels() const;
    bool playing() const;

public slots:
    QString addChannel(const QString& name, const QString& path);
    bool removeChannel(const QString& id);
    bool play(const QString& id);
    bool stop(const QString& id);
    void stopAll();
    bool setVolume(const QString& id, double volume);
    bool toggleMute(const QString& id);
    bool toggleSolo(const QString& id);
    bool crossfade(const QString& fromId, const QString& toId, double seconds);

signals:
    void changed();
    void notification(const QString& message);

private:
    struct Channel
    {
        QString id;
        QString name;
        QString path;
        QMediaPlayer* player = nullptr;
        QAudioOutput* output = nullptr;
        bool muted = false;
        bool solo = false;
        double volume = 1.0;
    };

    Channel* find(const QString& id);
    void applyRouting();

    QVector<Channel> m_channels;
};

} // namespace mxu::app
