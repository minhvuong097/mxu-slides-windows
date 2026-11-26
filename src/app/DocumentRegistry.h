#pragma once

#include <QObject>
#include <QSettings>
#include <QString>
#include <QVariantList>
#include <QVariantMap>

namespace mxu::app {

// Registry of the 29 document kinds from the macOS DocumentEntity, with
// per-kind storage directories and lightweight metadata records.
class DocumentRegistry : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList kinds READ kinds CONSTANT)
    Q_PROPERTY(QVariantList documents READ documents NOTIFY changed)

public:
    explicit DocumentRegistry(QObject* parent = nullptr);

    QVariantList kinds() const;
    QVariantList documents() const;
    Q_INVOKABLE QString directoryFor(const QString& kind) const;

public slots:
    QString create(const QString& kind, const QString& name);
    bool remove(const QString& id);
    QVariantList inKind(const QString& kind) const;

signals:
    void changed();
    void notification(const QString& message);

private:
    void persist();

    QSettings m_store;
    QVariantList m_documents;
};

} // namespace mxu::app
