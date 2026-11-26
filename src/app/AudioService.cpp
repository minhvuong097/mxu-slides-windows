#include "AudioService.h"

#include <QFileInfo>
#include <QPointer>
#include <QUrl>
#include <QUuid>

namespace mxu::app {

AudioService::AudioService(QObject* parent)
    : QObject(parent)
{
}

AudioService::~AudioService()
{
    for (auto& channel : m_channels) {
        delete channel.player;
        delete channel.output;
    }
}

AudioService::Channel* AudioService::find(const QString& id)
{
    for (auto& channel : m_channels) {
        if (channel.id == id)
            return &channel;
    }
    return nullptr;
}

void AudioService::applyRouting()
{
    bool anySolo = false;
    for (const auto& channel : m_channels)
        anySolo = anySolo || channel.solo;
    for (auto& channel : m_channels) {
        if (!channel.output)
            continue;
        const bool audible = !channel.muted && (!anySolo || channel.solo);
        channel.output->setVolume(audible ? channel.volume : 0.0);
    }
}

QVariantList AudioService::channels() const
{
    QVariantList result;
    bool anyPlaying = false;
    for (const auto& channel : m_channels) {
        const bool playing = channel.player && channel.player->playbackState() == QMediaPlayer::PlayingState;
        anyPlaying = anyPlaying || playing;
        result.append(QVariantMap{
            { QStringLiteral(u"id"), channel.id },
            { QStringLiteral(u"name"), channel.name },
            { QStringLiteral(u"muted"), channel.muted },
            { QStringLiteral(u"solo"), channel.solo },
            { QStringLiteral(u"volume"), channel.volume },
            { QStringLiteral(u"playing"), playing },
        });
    }
    return result;
}

bool AudioService::playing() const
{
    for (const auto& channel : m_channels) {
        if (channel.player && channel.player->playbackState() == QMediaPlayer::PlayingState)
            return true;
    }
    return false;
}

QString AudioService::addChannel(const QString& name, const QString& path)
{
    if (path.isEmpty())
        return {};
    const QFileInfo info(path);
    Channel channel;
    channel.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    channel.name = name.isEmpty() ? info.completeBaseName() : name;
    channel.path = path;
    channel.output = new QAudioOutput(this);
    channel.player = new QMediaPlayer(this);
    channel.player->setAudioOutput(channel.output);
    channel.player->setSource(QUrl::fromLocalFile(path));
    m_channels.append(channel);
    applyRouting();
    emit changed();
    emit notification(QStringLiteral(u"Audio added: %1").arg(channel.name));
    return channel.id;
}

bool AudioService::removeChannel(const QString& id)
{
    for (qsizetype i = 0; i < m_channels.size(); ++i) {
        if (m_channels[i].id != id)
            continue;
        delete m_channels[i].player;
        delete m_channels[i].output;
        m_channels.removeAt(i);
        emit changed();
        return true;
    }
    return false;
}

bool AudioService::play(const QString& id)
{
    Channel* channel = find(id);
    if (!channel || !channel->player)
        return false;
    channel->player->play();
    emit changed();
    return true;
}

bool AudioService::stop(const QString& id)
{
    Channel* channel = find(id);
    if (!channel || !channel->player)
        return false;
    channel->player->stop();
    emit changed();
    return true;
}

void AudioService::playAll()
{
    for (auto& channel : m_channels) {
        if (channel.player)
            channel.player->play();
    }
    emit changed();
}

void AudioService::stopAll()
{
    for (auto& channel : m_channels) {
        if (channel.player)
            channel.player->stop();
    }
    emit changed();
}

bool AudioService::setVolume(const QString& id, double volume)
{
    Channel* channel = find(id);
    if (!channel)
        return false;
    channel->volume = qBound(0.0, volume, 1.0);
    applyRouting();
    emit changed();
    return true;
}

bool AudioService::toggleMute(const QString& id)
{
    Channel* channel = find(id);
    if (!channel)
        return false;
    channel->muted = !channel->muted;
    applyRouting();
    emit changed();
    return true;
}

bool AudioService::crossfade(const QString& fromId, const QString& toId, double seconds)
{
    Channel* from = find(fromId);
    Channel* to = find(toId);
    if (!from || !to || !from->output || !to->output)
        return false;
    if (to->player)
        to->player->play();

    const int duration = qBound(50, static_cast<int>(seconds * 1000), 10000);
    auto* fadeOut = new QPropertyAnimation(from->output, "volume", this);
    fadeOut->setDuration(duration);
    fadeOut->setStartValue(from->volume);
    fadeOut->setEndValue(0.0);
    auto* fadeIn = new QPropertyAnimation(to->output, "volume", this);
    fadeIn->setDuration(duration);
    fadeIn->setStartValue(0.0);
    fadeIn->setEndValue(to->volume);
    fadeOut->start(QAbstractAnimation::DeleteWhenStopped);
    fadeIn->start(QAbstractAnimation::DeleteWhenStopped);
    QObject::connect(fadeOut, &QPropertyAnimation::finished, this, [this, fromId]() {
        stop(fromId);
    });
    emit notification(QStringLiteral(u"Crossfade %1 → %2").arg(from->name, to->name));
    return true;
}

bool AudioService::toggleSolo(const QString& id)
{
    Channel* channel = find(id);
    if (!channel)
        return false;
    channel->solo = !channel->solo;
    applyRouting();
    emit changed();
    return true;
}

} // namespace mxu::app
