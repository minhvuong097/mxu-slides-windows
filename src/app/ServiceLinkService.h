#pragma once

#include <QObject>
#include <QSettings>
#include <QVariantList>

namespace mxu::app {

// Follow/backup pairing rules between stations (macOS ServiceLinkRule).
class ServiceLinkService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList rules READ rules NOTIFY changed)

public:
    explicit ServiceLinkService(QObject* parent = nullptr);

    QVariantList rules() const { return m_rules; }

public slots:
    QString add(const QString& peerId, const QString& mode);
    bool remove(const QString& id);
    bool toggle(const QString& id);

signals:
    void changed();
    void notification(const QString& message);

private:
    void persist();

    QSettings m_store;
    QVariantList m_rules;
};

} // namespace mxu::app
