#pragma once

#include "SyncLedger.h"

#include <QByteArray>
#include <QJsonObject>
#include <QObject>
#include <QVector>
#include <QString>
#include <QVariantMap>

namespace mxu::core {

// Wire-format adapter that maps the local LWW operation log onto an
// Automerge-style change envelope. It is intentionally self-contained so a
// real automerge-cpp backend can replace the transport without changing callers.
class AutomergeCompat : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int peers READ peersCount NOTIFY changed)
    Q_PROPERTY(int appliedChanges READ appliedChanges NOTIFY changed)

public:
    explicit AutomergeCompat(QObject* parent = nullptr);

    int peersCount() const { return m_peers.size(); }
    int appliedChanges() const { return m_applied; }

    Q_INVOKABLE QByteArray exportChanges() const;
    Q_INVOKABLE int importChanges(const QByteArray& envelope);
    Q_INVOKABLE QVariantMap documentState() const;
    Q_INVOKABLE void setLocalValue(const QString& key, const QVariant& value);
    Q_INVOKABLE QVariant localValue(const QString& key) const;

public slots:
    void addPeer(const QString& id);
    void clearPeers();

signals:
    void changed();
    void stateMerged(const QVariantMap& state);

private:
    QJsonObject m_state;
    QVector<QString> m_peers;
    SyncLedger m_ledger;
    int m_applied = 0;
};

} // namespace mxu::core
