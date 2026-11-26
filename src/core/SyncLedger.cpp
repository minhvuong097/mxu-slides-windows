#include "SyncLedger.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QUuid>

namespace mxu::core {

SyncLedger::SyncLedger(QObject* parent)
    : QObject(parent)
    , m_deviceId(QUuid::createUuid().toString(QUuid::WithoutBraces))
{
}

QVariantMap SyncLedger::append(const QString& entityId, const QString& field, const QVariant& value)
{
    ++m_clock;
    QVariantMap operation{
        { QStringLiteral(u"counter"), static_cast<qulonglong>(m_clock) },
        { QStringLiteral(u"device"), m_deviceId },
        { QStringLiteral(u"entity"), entityId },
        { QStringLiteral(u"field"), field },
        { QStringLiteral(u"value"), value },
    };
    m_operations.append(QJsonValue::fromVariant(operation));
    emit changed();
    emit operationApplied(operation);
    return operation;
}

int SyncLedger::merge(const QString& json)
{
    QJsonParseError error;
    const QJsonDocument document = QJsonDocument::fromJson(json.toUtf8(), &error);
    if (error.error != QJsonParseError::NoError || !document.isArray())
        return 0;

    int applied = 0;
    for (const QJsonValue& value : document.array()) {
        const QJsonObject operation = value.toObject();
        const quint64 counter = static_cast<quint64>(operation.value(QStringLiteral(u"counter")).toDouble());
        if (counter <= m_clock)
            continue;
        m_operations.append(operation);
        m_clock = counter;
        ++applied;
        emit operationApplied(operation.toVariantMap());
    }
    if (applied > 0)
        emit changed();
    return applied;
}

QByteArray SyncLedger::exportJson() const
{
    return QJsonDocument(m_operations).toJson(QJsonDocument::Compact);
}

} // namespace mxu::core
