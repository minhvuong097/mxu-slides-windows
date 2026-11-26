#pragma once

#include <QObject>
#include <QUdpSocket>
#include <QString>
#include <QTimer>
#include <QVariantList>

namespace mxu::app {

// Lightweight LAN peer discovery for follow/backup pairing. Broadcasts a
// JSON heartbeat on UDP 6983 and tracks peers seen in the last 15 seconds.
class DiscoveryService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running NOTIFY changed)
    Q_PROPERTY(QVariantList peers READ peers NOTIFY changed)
    Q_PROPERTY(QString deviceId READ deviceId CONSTANT)

public:
    explicit DiscoveryService(QObject* parent = nullptr);

    bool running() const { return m_running; }
    QVariantList peers() const;
    QString deviceId() const { return m_deviceId; }

public slots:
    void start();
    void stop();

signals:
    void changed();
    void peerFound(const QVariantMap& peer);

private slots:
    void announce();
    void readPending();

private:
    QUdpSocket m_socket;
    QTimer m_timer;
    QVariantList m_peers;
    QString m_deviceId;
    bool m_running = false;
};

} // namespace mxu::app
