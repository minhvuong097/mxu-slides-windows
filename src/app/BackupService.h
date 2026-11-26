#pragma once

#include "core/Document.h"
#include "core/ShowDocument.h"

#include <QObject>
#include <QString>
#include <QVariantList>

namespace mxu::app {

// Local snapshot backups, equivalent to the macOS BackupManager.
class BackupService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList backups READ backups NOTIFY changed)

public:
    explicit BackupService(QObject* parent = nullptr);

    QVariantList backups() const;

private:
    static QString directory();
    static QVariantList backupsFromDisk();

public slots:
    QString createBackup(const core::Document& document, const QString& label);
    bool restore(const QString& id, core::Document* target);
    bool remove(const QString& id);
    void refresh();

signals:
    void changed();
    void notification(const QString& message);

private:
    QVariantList m_backups;
};

} // namespace mxu::app
