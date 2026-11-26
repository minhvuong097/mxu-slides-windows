#pragma once

#include "app/TokenVault.h"

#include <QObject>
#include <QSet>
#include <QSettings>
#include <QString>
#include <QVariantList>
#include <QTcpServer>
#include <QWebSocket>
#include <QWebSocketServer>

class QTcpSocket;

namespace mxu::app { class AppController; }

namespace mxu::api {

// REST + WebSocket control surface compatible with the macOS Local API:
// GET /v1/ping, /v1/status, /v1/slides, /openapi.json;
// POST /v1/advance, /v1/clear; WS /v1/ws on port 6981.
class LocalApiServer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running NOTIFY stateChanged)
    Q_PROPERTY(quint16 port READ port WRITE setPort NOTIFY stateChanged)
    Q_PROPERTY(QString token READ token NOTIFY tokenChanged)
    Q_PROPERTY(QString address READ address NOTIFY stateChanged)

public:
    explicit LocalApiServer(QObject* parent = nullptr);
    ~LocalApiServer() override;

    bool running() const { return m_running; }
    quint16 port() const { return m_port; }
    QString token() const { return m_token; }
    QString address() const;
    void setPort(quint16 value);
    void attach(mxu::app::AppController* controller) { m_controller = controller; }

    bool start();
    void stop();
    void regenerateToken();
    QVariantList tokens() const;

    void broadcastState();

signals:
    void stateChanged();
    void tokenChanged();
    void errorOccurred(const QString& message);

private slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();
    void onNewWebSocket();
    void onWebSocketDisconnected();

private:
    struct Token { QString value; QStringList scopes; };

    void loadTokens();
    void saveTokens();
    bool authorized(const QString& header, const QUrl& url, const QString& scope) const;
    QByteArray dispatch(const QString& method, const QString& path, const QString& auth,
                        const QByteArray& body) const;
    QVariantMap statusDocument() const;

    QTcpServer m_http;
    QWebSocketServer m_events;
    QSet<QTcpSocket*> m_sockets;
    QSet<QWebSocket*> m_clients;
    QSettings m_store;
    app::TokenVault m_vault;
    QVector<Token> m_tokens;
    QString m_token;
    quint16 m_port = 6980;
    bool m_running = false;
    mxu::app::AppController* m_controller = nullptr;
};

} // namespace mxu::api
