#pragma once

#include <QObject>
#include <QSettings>
#include <QVariantList>
#include <QVariantMap>

namespace mxu::app {

// Tracks imported media with file hashes and transcode status, equivalent to
// the macOS ImportLedger document kind.
class ImportLedgerService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList entries READ entries NOTIFY changed)
    Q_PROPERTY(QVariantMap counts READ counts NOTIFY changed)

public:
    explicit ImportLedgerService(QObject* parent = nullptr);

    QVariantList entries() const { return m_entries; }
    QVariantMap counts() const;

public slots:
    QString record(const QString& path);
    bool mark(const QString& id, const QString& status);
    bool remove(const QString& id);
    bool verify(const QString& id);
    bool retry(const QString& id);
    void clear();

private:
    void load();
    void save();

    QSettings m_store;

signals:
    void changed();
    void notification(const QString& message);

private:
    QVariantList m_entries;
};

} // namespace mxu::app
