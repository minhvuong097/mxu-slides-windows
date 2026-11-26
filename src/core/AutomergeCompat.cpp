#include "AutomergeCompat.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>

namespace mxu::core {

AutomergeCompat::AutomergeCompat(QObject* parent)
    : QObject(parent)
{
}

void AutomergeCompat::addPeer(const QString& id)
{
    if (id.isEmpty() || m_peers.contains(id))
        return;
    m_peers.append(id);
    emit changed();
}

void AutomergeCompat::clearPeers()
{
    m_peers.clear();
    emit changed();
}

void AutomergeCompat::setLocalValue(const QString& key, const QVariant& value)
{
    if (key.isEmpty())
        return;
    m_state.insert(key, QJsonValue::fromVariant(value));
    m_ledger.append(QStringLiteral(u"document"), key, value);
    ++m_applied;
    emit changed();
    emit stateMerged(documentState());
}

QVariant AutomergeCompat::localValue(const QString& key) const
{
    return m_state.value(key).toVariant();
}

QVariantMap AutomergeCompat::documentState() const
{
    return m_state.toVariantMap();
}

QByteArray AutomergeCompat::exportChanges() const
{
    QJsonObject envelope;
    envelope.insert(QStringLiteral(u"format"), QStringLiteral(u"mxu-lww-v1"));
    envelope.insert(QStringLiteral(u"schemaVersion"), 161);
    envelope.insert(QStringLiteral(u"device"), m_ledger.deviceId());
    envelope.insert(QStringLiteral(u"clock"), static_cast<qint64>(m_ledger.clock()));

    QJsonArray peers;
    for (const QString& peer : m_peers)
        peers.append(peer);
    envelope.insert(QStringLiteral(u"peers"), peers);
    envelope.insert(QStringLiteral(u"state"), m_state);
    envelope.insert(QStringLiteral(u"ops"), QJsonDocument::fromJson(m_ledger.exportJson()).array());
    return QJsonDocument(envelope).toJson(QJsonDocument::Compact);
}

int AutomergeCompat::importChanges(const QByteArray& envelope)
{
    QJsonParseError error;
    const QJsonDocument document = QJsonDocument::fromJson(envelope, &error);
    if (error.error != QJsonParseError::NoError || !document.isObject())
        return 0;
    const QJsonObject remote = document.object();
    if (remote.value(QStringLiteral(u"format")).toString() != QStringLiteral(u"mxu-lww-v1"))
        return 0;

    int applied = m_ledger.merge(QString::fromUtf8(
        QJsonDocument(remote.value(QStringLiteral(u"ops")).toArray()).toJson(QJsonDocument::Compact)));
    const QJsonObject state = remote.value(QStringLiteral(u"state")).toObject();
    for (auto it = state.constBegin(); it != state.constEnd(); ++it) {
        if (!m_state.contains(it.key()))
            m_state.insert(it.key(), it.value());
    }
    const QJsonArray peers = remote.value(QStringLiteral(u"peers")).toArray();
    for (const QJsonValue& peer : peers) {
        const QString id = peer.toString();
        if (!id.isEmpty() && !m_peers.contains(id))
            m_peers.append(id);
    }
    m_applied += applied;
    emit changed();
    emit stateMerged(documentState());
    return applied;
}

} // namespace mxu::core
