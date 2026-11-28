#include "LocalApiServer.h"
#include "app/AppController.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonDocument>
#include <QUrlQuery>
#include <QUuid>
#include <QDateTime>

namespace mxu::api {

LocalApiServer::LocalApiServer(QObject* parent)
    : QObject(parent)
    , m_events(QStringLiteral(u"MxU Slides Local API"), QWebSocketServer::NonSecureMode)
{
    m_lanEnabled = m_store.value(QStringLiteral(u"mxu/api/lanEnabled"), false).toBool();
    loadTokens();
    connect(&m_http, &QTcpServer::newConnection, this, &LocalApiServer::onNewConnection);
    connect(&m_events, &QWebSocketServer::newConnection, this, &LocalApiServer::onNewWebSocket);
}

LocalApiServer::~LocalApiServer()
{
    stop();
}

QString LocalApiServer::address() const
{
    if (!m_running)
        return QString();
    return QStringLiteral(u"http://%1:%2")
        .arg(m_lanEnabled ? QStringLiteral(u"0.0.0.0") : QStringLiteral(u"127.0.0.1"))
        .arg(m_port);
}

void LocalApiServer::setLanEnabled(bool value)
{
    if (m_lanEnabled == value)
        return;
    const bool wasRunning = m_running;
    if (wasRunning)
        stop();
    m_lanEnabled = value;
    m_store.setValue(QStringLiteral(u"mxu/api/lanEnabled"), value);
    m_store.sync();
    if (wasRunning)
        start();
    emit stateChanged();
}

QString LocalApiServer::addToken(const QString& scope)
{
    QString internal = scope.trimmed().toLower();
    if (internal == QStringLiteral(u"watch")) internal = QStringLiteral(u"status");
    else if (internal == QStringLiteral(u"operate")) internal = QStringLiteral(u"control");
    else if (internal == QStringLiteral(u"manage")) internal = QStringLiteral(u"admin");
    if (internal != QStringLiteral(u"status") && internal != QStringLiteral(u"control")
        && internal != QStringLiteral(u"admin"))
        return QString();
    const QString value = QUuid::createUuid().toString(QUuid::WithoutBraces);
    m_tokens.append({ value, { internal } });
    saveTokens();
    emit tokenChanged();
    return value;
}

bool LocalApiServer::removeToken(const QString& value)
{
    if (m_tokens.size() <= 1)
        return false;
    for (qsizetype i = 0; i < m_tokens.size(); ++i) {
        if (m_tokens.at(i).value != value)
            continue;
        m_tokens.removeAt(i);
        if (m_token == value)
            m_token = m_tokens.first().value;
        saveTokens();
        emit tokenChanged();
        return true;
    }
    return false;
}

void LocalApiServer::setPort(quint16 value)
{
    if (m_port == value)
        return;
    const bool wasRunning = m_running;
    if (wasRunning)
        stop();
    m_port = value;
    if (wasRunning)
        start();
    emit stateChanged();
}

void LocalApiServer::loadTokens()
{
    const QByteArray vaultData = m_vault.load(QStringLiteral(u"api-tokens")).toUtf8();
    const QVariantList stored = vaultData.isEmpty()
                                    ? m_store.value(QStringLiteral(u"mxu/api/tokens")).toList()
                                    : QJsonDocument::fromJson(vaultData).toVariant().toList();
    for (const QVariant& entry : stored) {
        const QVariantMap map = entry.toMap();
        const QString value = map.value(QStringLiteral(u"value")).toString();
        if (!value.isEmpty())
            m_tokens.append({ value, map.value(QStringLiteral(u"scopes")).toStringList() });
    }
    if (m_tokens.isEmpty()) {
        m_tokens.append({ QUuid::createUuid().toString(QUuid::WithoutBraces),
                          { QStringLiteral(u"admin") } });
        saveTokens();
    }
    m_token = m_tokens.first().value;
    emit tokenChanged();
}

void LocalApiServer::saveTokens()
{
    QVariantList stored;
    for (const Token& token : m_tokens)
        stored.append(QVariantMap{ { QStringLiteral(u"value"), token.value },
                                   { QStringLiteral(u"scopes"), token.scopes } });
    m_vault.save(QStringLiteral(u"api-tokens"), QJsonDocument::fromVariant(stored).toJson(QJsonDocument::Compact));
    m_store.setValue(QStringLiteral(u"mxu/api/tokens"), stored);
    m_store.sync();
}

bool LocalApiServer::start()
{
    if (m_running)
        return true;
    if (!m_http.listen(m_lanEnabled ? QHostAddress::Any : QHostAddress::LocalHost, m_port)) {
        emit errorOccurred(m_http.errorString());
        return false;
    }
    if (!m_events.listen(m_lanEnabled ? QHostAddress::Any : QHostAddress::LocalHost, m_port + 1)) {
        const QString error = m_events.errorString();
        m_http.close();
        emit errorOccurred(error);
        return false;
    }
    m_running = true;
    emit stateChanged();
    return true;
}

void LocalApiServer::stop()
{
    if (!m_running)
        return;
    for (QTcpSocket* socket : m_sockets)
        socket->disconnectFromHost();
    for (QWebSocket* client : m_clients)
        client->close();
    m_http.close();
    m_events.close();
    m_running = false;
    emit stateChanged();
}

void LocalApiServer::regenerateToken()
{
    if (m_tokens.isEmpty())
        return;
    m_tokens[0].value = QUuid::createUuid().toString(QUuid::WithoutBraces);
    m_token = m_tokens[0].value;
    saveTokens();
    emit tokenChanged();
}

QVariantList LocalApiServer::tokens() const
{
    QVariantList result;
    for (const Token& token : m_tokens)
        result.append(QVariantMap{ { QStringLiteral(u"value"), token.value },
                                   { QStringLiteral(u"scopes"), token.scopes } });
    return result;
}

void LocalApiServer::onNewConnection()
{
    while (m_http.hasPendingConnections()) {
        QTcpSocket* socket = m_http.nextPendingConnection();
        m_sockets.insert(socket);
        connect(socket, &QTcpSocket::readyRead, this, &LocalApiServer::onReadyRead);
        connect(socket, &QTcpSocket::disconnected, this, &LocalApiServer::onDisconnected);
    }
}

void LocalApiServer::onDisconnected()
{
    auto* socket = qobject_cast<QTcpSocket*>(sender());
    if (socket) {
        m_sockets.remove(socket);
        socket->deleteLater();
    }
}

void LocalApiServer::onReadyRead()
{
    auto* socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket)
        return;
    const QByteArray data = socket->readAll();
    const int end = data.indexOf("\r\n\r\n");
    if (end < 0)
        return;
    const QList<QByteArray> lines = data.left(end).split('\n');
    if (lines.isEmpty())
        return;
    const QList<QByteArray> request = lines.first().trimmed().split(' ');
    if (request.size() < 2)
        return;
    const QString method = QString::fromLatin1(request.at(0));
    const QString path = QString::fromLatin1(request.at(1));
    QString auth;
    int contentLength = 0;
    for (qsizetype i = 1; i < lines.size(); ++i) {
        const QByteArray line = lines.at(i).trimmed();
        const int colon = line.indexOf(':');
        if (colon < 0)
            continue;
        const QString key = QString::fromLatin1(line.left(colon)).trimmed();
        if (key.compare(QStringLiteral(u"Authorization"), Qt::CaseInsensitive) == 0)
            auth = QString::fromLatin1(line.mid(colon + 1)).trimmed();
        else if (key.compare(QStringLiteral(u"Content-Length"), Qt::CaseInsensitive) == 0)
            contentLength = QString::fromLatin1(line.mid(colon + 1)).trimmed().toInt();
    }
    const QByteArray requestBody = contentLength > 0 ? data.mid(end + 4, contentLength) : QByteArray();

    const QByteArray json = dispatch(method, path, auth, requestBody);
    QByteArray reply = "HTTP/1.1 200 OK\r\n"
                       "Content-Type: application/json; charset=utf-8\r\n"
                       "Access-Control-Allow-Origin: *\r\n"
                       "Connection: close\r\n"
                       "Content-Length: " + QByteArray::number(json.size()) + "\r\n\r\n";
    reply += json;
    socket->write(reply);
    socket->flush();
    socket->disconnectFromHost();
}

bool LocalApiServer::authorized(const QString& header, const QUrl& url,
                                const QString& scope) const
{
    QString value = header;
    if (value.startsWith(QStringLiteral(u"Bearer "), Qt::CaseInsensitive))
        value = value.mid(7).trimmed();
    if (value.isEmpty())
        value = QUrlQuery(url).queryItemValue(QStringLiteral(u"token"));
    for (const Token& token : m_tokens) {
        if (token.value == value)
            return token.scopes.contains(QStringLiteral(u"admin")) || token.scopes.contains(scope);
    }
    return false;
}

QVariantMap LocalApiServer::statusDocument() const
{
    QVariantMap live;
    if (m_controller) {
        live.insert(QStringLiteral(u"screen"), m_controller->screen());
        live.insert(QStringLiteral(u"cue"), m_controller->cueModel()->property("currentCueIndex"));
        live.insert(QStringLiteral(u"slide"), m_controller->cueModel()->property("currentSlideIndex"));
        live.insert(QStringLiteral(u"text"), m_controller->property("currentSlideText"));
        live.insert(QStringLiteral(u"timer"), m_controller->property("serviceTimerText"));
    }
    QVariantMap result;
    result.insert(QStringLiteral(u"ok"), true);
    result.insert(QStringLiteral(u"app"), QStringLiteral(u"MxU Slides for Windows"));
    result.insert(QStringLiteral(u"version"), QStringLiteral(u"0.1.0"));
    result.insert(QStringLiteral(u"timestamp"), QDateTime::currentDateTimeUtc().toString(Qt::ISODate));
    result.insert(QStringLiteral(u"live"), live);
    return result;
}

QByteArray LocalApiServer::dispatch(const QString& method, const QString& path,
                                    const QString& auth, const QByteArray& body) const
{
    const QJsonObject payload = QJsonDocument::fromJson(body).object();
    const QUrl url(path);
    const QString route = url.path();
    QVariantMap response;

    if (route == QStringLiteral(u"/v1/ping")) {
        response.insert(QStringLiteral(u"ok"), true);
        response.insert(QStringLiteral(u"service"), QStringLiteral(u"MxU Slides Local API"));
    } else if (route == QStringLiteral(u"/openapi.json")) {
        response.insert(QStringLiteral(u"openapi"), QStringLiteral(u"3.0.3"));
        response.insert(QStringLiteral(u"info"), QVariantMap{
            { QStringLiteral(u"title"), QStringLiteral(u"MxU Slides Local API") },
            { QStringLiteral(u"version"), QStringLiteral(u"0.1.0") } });
        response.insert(QStringLiteral(u"servers"), QVariantList{
            QVariantMap{ { QStringLiteral(u"url"), address() } } });
        QVariantMap paths;
        auto addRoute = [&paths](const QString& route, const QString& method,
                                 const QString& summary, const QString& scope) {
            QVariantMap operation{
                { QStringLiteral(u"summary"), summary },
                { QStringLiteral(u"x-scope"), scope },
            };
            QVariantMap entry = paths.value(route).toMap();
            entry.insert(method, operation);
            paths.insert(route, entry);
        };
        addRoute(QStringLiteral(u"/v1/ping"), QStringLiteral(u"get"), QStringLiteral(u"Health check"), QString());
        addRoute(QStringLiteral(u"/v1/status"), QStringLiteral(u"get"), QStringLiteral(u"Live show state"), QStringLiteral(u"status"));
        addRoute(QStringLiteral(u"/v1/slides"), QStringLiteral(u"get"), QStringLiteral(u"List slides"), QStringLiteral(u"status"));
        addRoute(QStringLiteral(u"/v1/advance"), QStringLiteral(u"post"), QStringLiteral(u"Next slide"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/clear"), QStringLiteral(u"post"), QStringLiteral(u"Toggle clear"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/goToSlide"), QStringLiteral(u"post"), QStringLiteral(u"Go to slide index"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/timers"), QStringLiteral(u"get"), QStringLiteral(u"Service timers"), QStringLiteral(u"status"));
        addRoute(QStringLiteral(u"/v1/present"), QStringLiteral(u"post"), QStringLiteral(u"Start presentation"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/stop"), QStringLiteral(u"post"), QStringLiteral(u"Stop presentation"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/clearLayer"), QStringLiteral(u"post"), QStringLiteral(u"Clear a layer"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/stream"), QStringLiteral(u"post"), QStringLiteral(u"Start stream"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/stream"), QStringLiteral(u"delete"), QStringLiteral(u"Stop stream"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/record"), QStringLiteral(u"post"), QStringLiteral(u"Start recorder"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/record"), QStringLiteral(u"delete"), QStringLiteral(u"Stop recorder"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/search"), QStringLiteral(u"get"), QStringLiteral(u"Full-text search"), QStringLiteral(u"status"));
        addRoute(QStringLiteral(u"/v1/sync"), QStringLiteral(u"post"), QStringLiteral(u"Merge sync operations"), QStringLiteral(u"admin"));
        addRoute(QStringLiteral(u"/v1/diagnostics"), QStringLiteral(u"get"), QStringLiteral(u"Diagnostics report"), QStringLiteral(u"admin"));
        addRoute(QStringLiteral(u"/v1/tokens"), QStringLiteral(u"get"), QStringLiteral(u"List tokens"), QStringLiteral(u"admin"));
        addRoute(QStringLiteral(u"/v1/alert"), QStringLiteral(u"post"), QStringLiteral(u"Fire alert"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/dismissAlert"), QStringLiteral(u"post"), QStringLiteral(u"Dismiss alert"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/fire"), QStringLiteral(u"post"), QStringLiteral(u"Fire trigger action"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/notes"), QStringLiteral(u"get"), QStringLiteral(u"List sermon notes"), QStringLiteral(u"status"));
        addRoute(QStringLiteral(u"/v1/next"), QStringLiteral(u"post"), QStringLiteral(u"Next slide alias"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/previous"), QStringLiteral(u"post"), QStringLiteral(u"Previous slide alias"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/clearAll"), QStringLiteral(u"post"), QStringLiteral(u"Clear all layers"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/restore"), QStringLiteral(u"post"), QStringLiteral(u"Restore layers"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/timers/start"), QStringLiteral(u"post"), QStringLiteral(u"Toggle timer"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/playlist/next"), QStringLiteral(u"post"), QStringLiteral(u"Next playlist track"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/presets"), QStringLiteral(u"get"), QStringLiteral(u"List output presets"), QStringLiteral(u"status"));
        addRoute(QStringLiteral(u"/v1/discovery"), QStringLiteral(u"get"), QStringLiteral(u"Discovered peers"), QStringLiteral(u"status"));
        addRoute(QStringLiteral(u"/v1/audio"), QStringLiteral(u"get"), QStringLiteral(u"Audio channels"), QStringLiteral(u"status"));
        addRoute(QStringLiteral(u"/v1/overlays"), QStringLiteral(u"get"), QStringLiteral(u"Active alerts"), QStringLiteral(u"status"));
        addRoute(QStringLiteral(u"/v1/status/live"), QStringLiteral(u"get"), QStringLiteral(u"Live state only"), QStringLiteral(u"status"));
        addRoute(QStringLiteral(u"/v1/slides/current"), QStringLiteral(u"get"), QStringLiteral(u"Current slide"), QStringLiteral(u"status"));
        addRoute(QStringLiteral(u"/v1/slides/next"), QStringLiteral(u"get"), QStringLiteral(u"Next slide"), QStringLiteral(u"status"));
        addRoute(QStringLiteral(u"/v1/notes/blocks"), QStringLiteral(u"get"), QStringLiteral(u"Sermon notes"), QStringLiteral(u"status"));
        addRoute(QStringLiteral(u"/v1/timers/reset"), QStringLiteral(u"post"), QStringLiteral(u"Reset timers"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/audio/play"), QStringLiteral(u"post"), QStringLiteral(u"Play audio"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/audio/stop"), QStringLiteral(u"post"), QStringLiteral(u"Stop audio"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/recording/start"), QStringLiteral(u"post"), QStringLiteral(u"Start recording"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/recording/stop"), QStringLiteral(u"post"), QStringLiteral(u"Stop recording"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/notes/add"), QStringLiteral(u"post"), QStringLiteral(u"Add note"), QStringLiteral(u"control"));
        addRoute(QStringLiteral(u"/v1/documents"), QStringLiteral(u"get"), QStringLiteral(u"Document registry"), QStringLiteral(u"status"));
        addRoute(QStringLiteral(u"/v1/links"), QStringLiteral(u"get"), QStringLiteral(u"Follow links"), QStringLiteral(u"status"));
        addRoute(QStringLiteral(u"/v1/slides/history"), QStringLiteral(u"get"), QStringLiteral(u"Slide versions"), QStringLiteral(u"status"));
        addRoute(QStringLiteral(u"/v1/service/versions"), QStringLiteral(u"get"), QStringLiteral(u"Service station versions"), QStringLiteral(u"status"));
        addRoute(QStringLiteral(u"/v1/backup/create"), QStringLiteral(u"post"), QStringLiteral(u"Create backup"), QStringLiteral(u"control"));
        response.insert(QStringLiteral(u"paths"), paths);
    } else if (route == QStringLiteral(u"/v1/status") && method == QStringLiteral(u"GET")) {
        if (!authorized(auth, url, QStringLiteral(u"status")))
            response.insert(QStringLiteral(u"error"), QStringLiteral(u"Unauthorized"));
        else
            return QJsonDocument::fromVariant(statusDocument()).toJson(QJsonDocument::Compact);
    } else if (route == QStringLiteral(u"/v1/slides") && method == QStringLiteral(u"GET")) {
        if (!authorized(auth, url, QStringLiteral(u"status"))) {
            response.insert(QStringLiteral(u"error"), QStringLiteral(u"Unauthorized"));
        } else {
            QVariantList slides;
            const QVariantList cues = m_controller ? m_controller->cueModel()->property("cues").toList()
                                                   : QVariantList();
            for (const QVariant& cue : cues) {
                const QVariantMap cueMap = cue.toMap();
                for (const QVariant& slide : cueMap.value(QStringLiteral(u"slides")).toList()) {
                    const QVariantMap slideMap = slide.toMap();
                    slides.append(QVariantMap{
                        { QStringLiteral(u"cue"), cueMap.value(QStringLiteral(u"title")) },
                        { QStringLiteral(u"tag"), slideMap.value(QStringLiteral(u"tag")) },
                        { QStringLiteral(u"text"), slideMap.value(QStringLiteral(u"text")) } });
                }
            }
            response.insert(QStringLiteral(u"slides"), slides);
        }
    } else if ((route == QStringLiteral(u"/v1/advance") || route == QStringLiteral(u"/v1/clear"))
               && method == QStringLiteral(u"POST")) {
        if (!authorized(auth, url, QStringLiteral(u"control"))) {
            response.insert(QStringLiteral(u"error"), QStringLiteral(u"Control scope required"));
        } else if (m_controller) {
            QMetaObject::invokeMethod(m_controller,
                                      route == QStringLiteral(u"/v1/advance") ? "next" : "toggleClear",
                                      Qt::QueuedConnection);
            response.insert(QStringLiteral(u"ok"), true);
        }
    } else if (route == QStringLiteral(u"/v1/alert") && method == QStringLiteral(u"POST")) {
        if (!authorized(auth, url, QStringLiteral(u"control"))) {
            response.insert(QStringLiteral(u"error"), QStringLiteral(u"Control scope required"));
        } else if (m_controller) {
            bool applied = false;
            QMetaObject::invokeMethod(m_controller->alerts(), "fire",
                                      Q_RETURN_ARG(bool, applied),
                                      Q_ARG(QString, payload.value(QStringLiteral(u"text")).toString()),
                                      Q_ARG(QString, payload.value(QStringLiteral(u"target")).toString()),
                                      Q_ARG(QString, payload.value(QStringLiteral(u"behavior")).toString()));
            response.insert(QStringLiteral(u"ok"), applied);
        }
    } else if (route == QStringLiteral(u"/v1/dismissAlert") && method == QStringLiteral(u"POST")) {
        if (!authorized(auth, url, QStringLiteral(u"control"))) {
            response.insert(QStringLiteral(u"error"), QStringLiteral(u"Control scope required"));
        } else if (m_controller) {
            QMetaObject::invokeMethod(m_controller->alerts(), "dismiss");
            response.insert(QStringLiteral(u"ok"), true);
        }
    } else if (route == QStringLiteral(u"/v1/fire") && method == QStringLiteral(u"POST")) {
        if (!authorized(auth, url, QStringLiteral(u"control"))) {
            response.insert(QStringLiteral(u"error"), QStringLiteral(u"Control scope required"));
        } else if (m_controller) {
            bool applied = false;
            QMetaObject::invokeMethod(m_controller->automation(), "fire",
                                      Q_RETURN_ARG(bool, applied),
                                      Q_ARG(QString, payload.value(QStringLiteral(u"action")).toString()));
            response.insert(QStringLiteral(u"ok"), applied);
        }
    } else if (route == QStringLiteral(u"/v1/notes") && method == QStringLiteral(u"GET")) {
        if (!authorized(auth, url, QStringLiteral(u"status"))) {
            response.insert(QStringLiteral(u"error"), QStringLiteral(u"Unauthorized"));
        } else if (m_controller) {
            response.insert(QStringLiteral(u"blocks"), m_controller->notes()->property("blocks"));
        }
    } else if (route == QStringLiteral(u"/v1/goToSlide") && method == QStringLiteral(u"POST")) {
        if (!authorized(auth, url, QStringLiteral(u"control"))) {
            response.insert(QStringLiteral(u"error"), QStringLiteral(u"Control scope required"));
        } else if (m_controller) {
            QMetaObject::invokeMethod(m_controller, "selectSlide", Qt::QueuedConnection,
                                      Q_ARG(int, payload.value(QStringLiteral(u"index")).toInt()));
            response.insert(QStringLiteral(u"ok"), true);
        }
    } else if (route == QStringLiteral(u"/v1/timers") && method == QStringLiteral(u"GET")) {
        if (!authorized(auth, url, QStringLiteral(u"status"))) {
            response.insert(QStringLiteral(u"error"), QStringLiteral(u"Unauthorized"));
        } else if (m_controller) {
            response.insert(QStringLiteral(u"timer"), m_controller->property("serviceTimerText"));
            response.insert(QStringLiteral(u"running"), m_controller->property("timerRunning"));
            response.insert(QStringLiteral(u"rows"), m_controller->property("timerRows"));
        }
    } else if ((route == QStringLiteral(u"/v1/present") || route == QStringLiteral(u"/v1/stop"))
               && method == QStringLiteral(u"POST")) {
        if (!authorized(auth, url, QStringLiteral(u"control"))) {
            response.insert(QStringLiteral(u"error"), QStringLiteral(u"Control scope required"));
        } else if (m_controller) {
            QMetaObject::invokeMethod(m_controller,
                                      route == QStringLiteral(u"/v1/present") ? "setPresenting" : "setPresenting",
                                      Qt::QueuedConnection,
                                      Q_ARG(bool, route == QStringLiteral(u"/v1/present")));
            response.insert(QStringLiteral(u"ok"), true);
        }
    } else if (route == QStringLiteral(u"/v1/clearLayer") && method == QStringLiteral(u"POST")) {
        if (!authorized(auth, url, QStringLiteral(u"control"))) {
            response.insert(QStringLiteral(u"error"), QStringLiteral(u"Control scope required"));
        } else if (m_controller) {
            QMetaObject::invokeMethod(m_controller->showState(), "clearLayer", Qt::QueuedConnection,
                                      Q_ARG(QString, payload.value(QStringLiteral(u"kind")).toString()));
            response.insert(QStringLiteral(u"ok"), true);
        }
    } else if ((route == QStringLiteral(u"/v1/stream") || route == QStringLiteral(u"/v1/record"))
               && method == QStringLiteral(u"POST")) {
        if (!authorized(auth, url, QStringLiteral(u"control"))) {
            response.insert(QStringLiteral(u"error"), QStringLiteral(u"Control scope required"));
        } else if (m_controller) {
            QObject* backend = m_controller->streaming();
            const bool result =
                QMetaObject::invokeMethod(backend,
                                          route == QStringLiteral(u"/v1/stream") ? "start" : "startRecording",
                                          Q_ARG(QString, payload.value(QStringLiteral(u"url")).toString()));
            response.insert(QStringLiteral(u"ok"), result);
        }
    } else if ((route == QStringLiteral(u"/v1/stream") || route == QStringLiteral(u"/v1/record"))
               && method == QStringLiteral(u"DELETE")) {
        if (!authorized(auth, url, QStringLiteral(u"control"))) {
            response.insert(QStringLiteral(u"error"), QStringLiteral(u"Control scope required"));
        } else if (m_controller) {
            QMetaObject::invokeMethod(m_controller->streaming(),
                                      route == QStringLiteral(u"/v1/stream") ? "stop" : "stopRecording");
            response.insert(QStringLiteral(u"ok"), true);
        }
    } else if (route == QStringLiteral(u"/v1/search") && method == QStringLiteral(u"GET")) {
        if (!authorized(auth, url, QStringLiteral(u"status"))) {
            response.insert(QStringLiteral(u"error"), QStringLiteral(u"Unauthorized"));
        } else if (m_controller) {
            response.insert(QStringLiteral(u"results"),
                            m_controller->search(QUrlQuery(url).queryItemValue(QStringLiteral(u"q"))));
        }
    } else if (route == QStringLiteral(u"/v1/diagnostics") && method == QStringLiteral(u"GET")) {
        if (!authorized(auth, url, QStringLiteral(u"admin"))) {
            response.insert(QStringLiteral(u"error"), QStringLiteral(u"Admin scope required"));
        } else if (m_controller) {
            response.insert(QStringLiteral(u"report"),
                            m_controller->diagnostics()->property("reportJson").toString());
        }
    } else if (route == QStringLiteral(u"/v1/sync") && method == QStringLiteral(u"POST")) {
        if (!authorized(auth, url, QStringLiteral(u"admin"))) {
            response.insert(QStringLiteral(u"error"), QStringLiteral(u"Admin scope required"));
        } else if (m_controller) {
            int applied = 0;
            QMetaObject::invokeMethod(m_controller->syncLedger(), "merge",
                                      Q_RETURN_ARG(int, applied),
                                      Q_ARG(QString, QString::fromUtf8(body)));
            response.insert(QStringLiteral(u"ok"), true);
            response.insert(QStringLiteral(u"applied"), applied);
        }
    } else if (route == QStringLiteral(u"/v1/tokens") && method == QStringLiteral(u"GET")) {
        if (!authorized(auth, url, QStringLiteral(u"admin"))) {
            response.insert(QStringLiteral(u"error"), QStringLiteral(u"Admin scope required"));
        } else {
            response.insert(QStringLiteral(u"tokens"), tokens());
        }
    } else if (method == QStringLiteral(u"POST") && (
                   route == QStringLiteral(u"/v1/next") || route == QStringLiteral(u"/v1/previous")
                   || route == QStringLiteral(u"/v1/clearAll") || route == QStringLiteral(u"/v1/restore")
                   || route == QStringLiteral(u"/v1/timers/start") || route == QStringLiteral(u"/v1/playlist/next"))) {
        if (!authorized(auth, url, QStringLiteral(u"control"))) {
            response.insert(QStringLiteral(u"error"), QStringLiteral(u"Control scope required"));
        } else if (m_controller) {
            QByteArray action;
            if (route == QStringLiteral(u"/v1/next")) action = "next";
            else if (route == QStringLiteral(u"/v1/previous")) action = "previous";
            else if (route == QStringLiteral(u"/v1/playlist/next")) action = "playlistNext";
            else if (route == QStringLiteral(u"/v1/timers/start")) action = "toggleTimer";
            else if (route == QStringLiteral(u"/v1/clearAll")) action = "clearAllLayers";
            else action = "restoreLayers";
            if (action == "playlistNext")
                QMetaObject::invokeMethod(m_controller->playlist(), "next", Qt::QueuedConnection);
            else if (action == "clearAllLayers")
                QMetaObject::invokeMethod(m_controller->showState(), "clearAll", Qt::QueuedConnection);
            else if (action == "restoreLayers")
                QMetaObject::invokeMethod(m_controller->showState(), "restoreAll", Qt::QueuedConnection);
            else
                QMetaObject::invokeMethod(m_controller, action.constData(), Qt::QueuedConnection);
            response.insert(QStringLiteral(u"ok"), true);
        }
    } else if (method == QStringLiteral(u"GET") && (
                   route == QStringLiteral(u"/v1/status/live") || route == QStringLiteral(u"/v1/slides/current")
                   || route == QStringLiteral(u"/v1/slides/next") || route == QStringLiteral(u"/v1/notes/blocks"))) {
        if (!authorized(auth, url, QStringLiteral(u"status"))) {
            response.insert(QStringLiteral(u"error"), QStringLiteral(u"Unauthorized"));
        } else if (m_controller) {
            if (route == QStringLiteral(u"/v1/status/live"))
                response.insert(QStringLiteral(u"live"), statusDocument().value(QStringLiteral(u"live")));
            else if (route == QStringLiteral(u"/v1/slides/current"))
                response.insert(QStringLiteral(u"slide"), m_controller->property("currentSlideText"));
            else if (route == QStringLiteral(u"/v1/slides/next"))
                response.insert(QStringLiteral(u"slide"), m_controller->property("nextSlideText"));
            else if (route == QStringLiteral(u"/v1/service/versions"))
                response.insert(QStringLiteral(u"versions"), m_controller->serviceVersions()->property("versions"));
            else if (route == QStringLiteral(u"/v1/documents"))
                response.insert(QStringLiteral(u"documents"), m_controller->documents()->property("documents"));
            else if (route == QStringLiteral(u"/v1/links"))
                response.insert(QStringLiteral(u"links"), m_controller->serviceLinks()->property("rules"));
            else if (route == QStringLiteral(u"/v1/slides/history"))
                response.insert(QStringLiteral(u"versions"), m_controller->property("slideVersions"));
            else
                response.insert(QStringLiteral(u"blocks"), m_controller->notes()->property("blocks"));
        }
    } else if (method == QStringLiteral(u"POST") && (
                   route == QStringLiteral(u"/v1/timers/reset") || route == QStringLiteral(u"/v1/audio/play")
                   || route == QStringLiteral(u"/v1/audio/stop") || route == QStringLiteral(u"/v1/recording/start")
                   || route == QStringLiteral(u"/v1/recording/stop") || route == QStringLiteral(u"/v1/notes/add")
                   || route == QStringLiteral(u"/v1/backup/create"))) {
        if (!authorized(auth, url, QStringLiteral(u"control"))) {
            response.insert(QStringLiteral(u"error"), QStringLiteral(u"Control scope required"));
        } else if (m_controller) {
            QObject* target = nullptr;
            QByteArray action;
            if (route == QStringLiteral(u"/v1/timers/reset")) { target = m_controller->timerBoard(); action = "reset"; }
            else if (route == QStringLiteral(u"/v1/audio/play")) { target = m_controller->audioService(); action = "playAll"; }
            else if (route == QStringLiteral(u"/v1/audio/stop")) { target = m_controller->audioService(); action = "stopAll"; }
            else if (route == QStringLiteral(u"/v1/recording/start")) { target = m_controller->streaming(); action = "startRecording"; }
            else if (route == QStringLiteral(u"/v1/recording/stop")) { target = m_controller->streaming(); action = "stopRecording"; }
            else if (route == QStringLiteral(u"/v1/notes/add")) { target = m_controller->notes(); action = "addBlock"; }
            else { target = m_controller->backupService(); action = "createBackup"; }
            const QString text = payload.value(QStringLiteral(u"text")).toString();
            bool ok = false;
            if (action == "addBlock" || action == "createBackup" || action == "startRecording")
                ok = QMetaObject::invokeMethod(target, action.constData(), Qt::QueuedConnection,
                                               Q_ARG(QString, text.isEmpty() ? QStringLiteral(u"API") : text));
            else
                ok = QMetaObject::invokeMethod(target, action.constData(), Qt::QueuedConnection);
            response.insert(QStringLiteral(u"ok"), ok);
        }
    } else if (method == QStringLiteral(u"GET") && (
                   route == QStringLiteral(u"/v1/presets") || route == QStringLiteral(u"/v1/discovery")
                   || route == QStringLiteral(u"/v1/audio") || route == QStringLiteral(u"/v1/overlays"))) {
        if (!authorized(auth, url, QStringLiteral(u"status"))) {
            response.insert(QStringLiteral(u"error"), QStringLiteral(u"Unauthorized"));
        } else if (m_controller) {
            if (route == QStringLiteral(u"/v1/presets"))
                response.insert(QStringLiteral(u"presets"), m_controller->outputPresets()->property("presets"));
            else if (route == QStringLiteral(u"/v1/discovery"))
                response.insert(QStringLiteral(u"peers"), m_controller->discovery()->property("peers"));
            else if (route == QStringLiteral(u"/v1/audio"))
                response.insert(QStringLiteral(u"channels"), m_controller->property("audioChannels"));
            else
                response.insert(QStringLiteral(u"alerts"), m_controller->alerts()->property("active"));
        }
    } else {
        response.insert(QStringLiteral(u"error"), QStringLiteral(u"Unknown route"));
    }
    return QJsonDocument::fromVariant(response).toJson(QJsonDocument::Compact);
}

void LocalApiServer::onNewWebSocket()
{
    while (m_events.hasPendingConnections()) {
        QWebSocket* socket = m_events.nextPendingConnection();
        m_clients.insert(socket);
        connect(socket, &QWebSocket::disconnected, this, &LocalApiServer::onWebSocketDisconnected);
        socket->sendTextMessage(QJsonDocument::fromVariant(QVariantMap{
            { QStringLiteral(u"type"), QStringLiteral(u"hello") },
            { QStringLiteral(u"version"), QStringLiteral(u"0.1.0") } }).toJson(QJsonDocument::Compact));
    }
}

void LocalApiServer::onWebSocketDisconnected()
{
    auto* socket = qobject_cast<QWebSocket*>(sender());
    if (socket) {
        m_clients.remove(socket);
        socket->deleteLater();
    }
}

void LocalApiServer::broadcastState()
{
    if (m_clients.isEmpty())
        return;
    const QByteArray message = QJsonDocument::fromVariant(QVariantMap{
        { QStringLiteral(u"type"), QStringLiteral(u"state") },
        { QStringLiteral(u"state"), statusDocument() } }).toJson(QJsonDocument::Compact);
    for (QWebSocket* client : m_clients)
        client->sendTextMessage(message);
}

} // namespace mxu::api
