#pragma once

#include <QJsonArray>
#include <QObject>
#include <QString>
#include <QVariantMap>

namespace mxu::core {

// Minimal LWW-style operation log with a Lamport clock. Exchanges JSON with
// peers so cross-platform sync can be layered on later (Automerge on macOS).
class SyncLedger : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint64 clock READ clock NOTIFY changed)
    Q_PROPERTY(int operationCount READ operationCount NOTIFY changed)
    Q_PROPERTY(QString deviceId READ deviceId CONSTANT)

public:
    explicit SyncLedger(QObject* parent = nullptr);

    quint64 clock() const { return m_clock; }
    int operationCount() const { return m_operations.size(); }
    QString deviceId() const { return m_deviceId; }

    Q_INVOKABLE QVariantMap append(const QString& entityId, const QString& field, const QVariant& value);
    Q_INVOKABLE int merge(const QString& json);
    Q_INVOKABLE QByteArray exportJson() const;

signals:
    void changed();
    void operationApplied(const QVariantMap& operation);

private:
    QJsonArray m_operations;
    quint64 m_clock = 0;
    QString m_deviceId;
};

} // namespace mxu::core
