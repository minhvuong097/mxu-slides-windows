#include "AutomergeCompat.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QSet>

namespace mxu::core {

namespace {

QJsonObject makeField(const QString& device, qint64 counter, const QJsonValue& value)
{
    QJsonArray values;
    values.append(QJsonObject{
        { QStringLiteral(u"device"), device },
        { QStringLiteral(u"counter"), counter },
        { QStringLiteral(u"value"), value },
    });
    QJsonObject vector;
    vector.insert(device, counter);
    return QJsonObject{
        { QStringLiteral(u"values"), values },
        { QStringLiteral(u"vector"), vector },
    };
}

QJsonObject mergeVector(const QJsonObject& a, const QJsonObject& b)
{
    QJsonObject result = a;
    for (auto it = b.constBegin(); it != b.constEnd(); ++it)
        result.insert(it.key(), qMax(it.value().toDouble(), a.value(it.key()).toDouble()));
    return result;
}

// 1 = a dominates, -1 = b dominates, 0 = concurrent or equal.
int compareVectors(const QJsonObject& a, const QJsonObject& b)
{
    bool aGreater = false;
    bool bGreater = false;
    QSet<QString> keys;
    for (auto it = a.constBegin(); it != a.constEnd(); ++it) keys.insert(it.key());
    for (auto it = b.constBegin(); it != b.constEnd(); ++it) keys.insert(it.key());
    for (const QString& key : keys) {
        const double av = a.value(key).toDouble();
        const double bv = b.value(key).toDouble();
        if (av > bv) aGreater = true;
        if (bv > av) bGreater = true;
    }
    if (aGreater && !bGreater) return 1;
    if (bGreater && !aGreater) return -1;
    return 0;
}

QJsonValue primaryValue(const QJsonArray& values)
{
    QJsonObject winner;
    qint64 bestCounter = -1;
    for (const QJsonValue& entry : values) {
        const QJsonObject map = entry.toObject();
        const qint64 counter = static_cast<qint64>(map.value(QStringLiteral(u"counter")).toDouble());
        const QString device = map.value(QStringLiteral(u"device")).toString();
        if (counter > bestCounter || (counter == bestCounter && device > winner.value(QStringLiteral(u"device")).toString())) {
            winner = map;
            bestCounter = counter;
        }
    }
    return winner.value(QStringLiteral(u"value"));
}

QJsonArray mergedValues(const QJsonArray& a, const QJsonArray& b)
{
    QJsonArray result = a;
    QSet<QByteArray> signatures;
    for (const QJsonValue& entry : result)
        signatures.insert(QJsonDocument(entry.toObject()).toJson(QJsonDocument::Compact));
    for (const QJsonValue& entry : b) {
        const QByteArray signature = QJsonDocument(entry.toObject()).toJson(QJsonDocument::Compact);
        if (signatures.contains(signature))
            continue;
        signatures.insert(signature);
        result.append(entry);
    }
    return result;
}

} // namespace

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
    const QString device = m_ledger.deviceId();
    const QJsonObject field = m_fields.value(key).toObject();
    const qint64 counter = static_cast<qint64>(field.value(QStringLiteral(u"vector")).toObject()
                                               .value(device).toDouble()) + 1;
    m_fields.insert(key, makeField(device, counter, QJsonValue::fromVariant(value)));
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
    QVariantMap result = m_state.toVariantMap();
    for (auto it = m_fields.constBegin(); it != m_fields.constEnd(); ++it) {
        const QJsonArray values = it.value().toObject().value(QStringLiteral(u"values")).toArray();
        if (values.size() > 1)
            result.insert(it.key() + QStringLiteral(u"#conflicts"), values.size() - 1);
    }
    return result;
}

QVariantList AutomergeCompat::conflicts(const QString& key) const
{
    QVariantList result;
    const QJsonArray values = m_fields.value(key).toObject().value(QStringLiteral(u"values")).toArray();
    for (const QJsonValue& entry : values)
        result.append(entry.toObject().toVariantMap());
    return result;
}

QByteArray AutomergeCompat::exportChanges() const
{
    QJsonObject envelope;
    envelope.insert(QStringLiteral(u"format"), QStringLiteral(u"mxu-crdt-v2"));
    envelope.insert(QStringLiteral(u"schemaVersion"), 161);
    envelope.insert(QStringLiteral(u"device"), m_ledger.deviceId());
    envelope.insert(QStringLiteral(u"clock"), static_cast<qint64>(m_ledger.clock()));
    envelope.insert(QStringLiteral(u"fields"), m_fields);
    envelope.insert(QStringLiteral(u"state"), m_state);

    QJsonArray peers;
    for (const QString& peer : m_peers)
        peers.append(peer);
    envelope.insert(QStringLiteral(u"peers"), peers);
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
    const QString format = remote.value(QStringLiteral(u"format")).toString();
    int applied = 0;

    if (format == QStringLiteral(u"mxu-crdt-v2")) {
        const QJsonObject remoteFields = remote.value(QStringLiteral(u"fields")).toObject();
        for (auto it = remoteFields.constBegin(); it != remoteFields.constEnd(); ++it) {
            const QJsonObject remoteField = it.value().toObject();
            const QJsonObject localField = m_fields.value(it.key()).toObject();
            const QJsonObject remoteVector = remoteField.value(QStringLiteral(u"vector")).toObject();
            const QJsonObject localVector = localField.value(QStringLiteral(u"vector")).toObject();
            const int order = compareVectors(localVector, remoteVector);
            QJsonObject merged;
            if (order < 0 || localVector.isEmpty()) {
                merged = remoteField;
            } else if (order > 0) {
                merged = localField;
            } else {
                const QJsonArray values = mergedValues(
                    localField.value(QStringLiteral(u"values")).toArray(),
                    remoteField.value(QStringLiteral(u"values")).toArray());
                merged = QJsonObject{
                    { QStringLiteral(u"values"), values },
                    { QStringLiteral(u"vector"), mergeVector(localVector, remoteVector) },
                };
            }
            m_fields.insert(it.key(), merged);
            m_state.insert(it.key(), primaryValue(merged.value(QStringLiteral(u"values")).toArray()));
            ++applied;
        }
    } else if (format == QStringLiteral(u"mxu-lww-v1")) {
        // Legacy wire format: replay operations, then keep unknown state values.
        applied = m_ledger.merge(QString::fromUtf8(
            QJsonDocument(remote.value(QStringLiteral(u"ops")).toArray()).toJson(QJsonDocument::Compact)));
        const QJsonObject state = remote.value(QStringLiteral(u"state")).toObject();
        for (auto it = state.constBegin(); it != state.constEnd(); ++it) {
            if (!m_state.contains(it.key())) {
                m_state.insert(it.key(), it.value());
                m_fields.insert(it.key(), makeField(
                    remote.value(QStringLiteral(u"device")).toString(), 1, it.value()));
            }
        }
    } else {
        return 0;
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
