#pragma once

#include <QObject>
#include <QVariantList>

namespace mxu::app {

// Tracks imported media with file hashes and transcode status, equivalent to
// the macOS ImportLedger document kind.
class ImportLedgerService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList entries READ entries NOTIFY changed)

public:
    explicit ImportLedgerService(QObject* parent = nullptr);

    QVariantList entries() const { return m_entries; }

public slots:
    QString record(const QString& path);
    bool mark(const QString& id, const QString& status);
    bool remove(const QString& id);
    void clear();

signals:
    void changed();
    void notification(const QString& message);

private:
    QVariantList m_entries;
};

} // namespace mxu::app
