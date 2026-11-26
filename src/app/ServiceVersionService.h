#pragma once

#include <QObject>
#include <QVariantList>
#include <QVariantMap>

namespace mxu::app {

// Per-station overlays on a service plan (added items + changes), matching
// the macOS ServiceVersion model.
class ServiceVersionService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList versions READ versions NOTIFY changed)
    Q_PROPERTY(QString activeStation READ activeStation NOTIFY changed)

public:
    explicit ServiceVersionService(QObject* parent = nullptr);

    QVariantList versions() const;
    QString activeStation() const { return m_active; }

public slots:
    QString add(const QString& station, const QVariantList& changes);
    bool activate(const QString& id);
    bool remove(const QString& id);

signals:
    void changed();
    void notification(const QString& message);

private:
    QVariantList m_versions;
    QString m_active;
};

} // namespace mxu::app
