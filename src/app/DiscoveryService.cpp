#include "DiscoveryService.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include <QUuid>
#include <QHostAddress>

namespace mxu::app {

DiscoveryService::DiscoveryService(QObject* parent)
    : QObject(parent)
    , m_deviceId(QUuid::createUuid().toString(QUuid::WithoutBraces))
{
    m_timer.setInterval(3000);
    connect(&m_timer, &QTimer::timeout, this, &DiscoveryService::announce);
    connect(&m_socket, &QUdpSocket::readyRead, this, &DiscoveryService::readPending);
}

QVariantList DiscoveryService::peers() const
{
    const qint64 now = QDateTime::currentMSecsSinceEpoch();
    QVariantList fresh;
    for (const QVariant& peer : m_peers) {
        if (now - peer.toMap().value(QStringLiteral(u"seen")).toLongLong() < 15000)
            fresh.append(peer);
    }
    return fresh;
}

void DiscoveryService::start()
{
    if (m_running)
        return;
    if (!m_socket.bind(QHostAddress::AnyIPv4, 6983, QUdpSocket::ShareAddress)) {
        m_socket.bind(QHostAddress::AnyIPv4, 6984, QUdpSocket::ShareAddress);
    }
    m_running = true;
    m_timer.start();
    announce();
    emit changed();
}

void DiscoveryService::stop()
{
    if (!m_running)
        return;
    m_timer.stop();
    m_socket.close();
    m_running = false;
    emit changed();
}

void DiscoveryService::announce()
{
    const QByteArray datagram = QJsonDocument::fromVariant(QVariantMap{
        { QStringLiteral(u"type"), QStringLiteral(u"mxu-slides") },
        { QStringLiteral(u"id"), m_deviceId },
        { QStringLiteral(u"name"), QStringLiteral(u"MxU Slides (Windows)") },
        { QStringLiteral(u"seen"), QDateTime::currentMSecsSinceEpoch() },
    }).toJson(QJsonDocument::Compact);
    m_socket.writeDatagram(datagram, QHostAddress::Broadcast, 6983);
}

void DiscoveryService::readPending()
{
    while (m_socket.hasPendingDatagrams()) {
        QByteArray data;
        data.resize(static_cast<qsizetype>(m_socket.pendingDatagramSize()));
        m_socket.readDatagram(data.data(), data.size());
        const QJsonObject object = QJsonDocument::fromJson(data).object();
        if (object.value(QStringLiteral(u"type")).toString() != QStringLiteral(u"mxu-slides"))
            continue;
        const QString id = object.value(QStringLiteral(u"id")).toString();
        if (id == m_deviceId)
            continue;
        QVariantMap peer = object.toVariantMap();
        peer.insert(QStringLiteral(u"seen"), QDateTime::currentMSecsSinceEpoch());
        bool replaced = false;
        for (qsizetype i = 0; i < m_peers.size(); ++i) {
            if (m_peers.at(i).toMap().value(QStringLiteral(u"id")).toString() != id)
                continue;
            m_peers[i] = peer;
            replaced = true;
            break;
        }
        if (!replaced) {
            m_peers.append(peer);
            emit peerFound(peer);
        }
        emit changed();
    }
}

} // namespace mxu::app
