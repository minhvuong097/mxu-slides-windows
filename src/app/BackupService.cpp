#include "BackupService.h"

#include <QDir>
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QUuid>
#include <QStandardPaths>

namespace mxu::app {

BackupService::BackupService(QObject* parent)
    : QObject(parent)
{
    refresh();
}

QVariantList BackupService::backups() const { return m_backups; }

QString BackupService::directory()
{
    const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
                        + QStringLiteral(u"/backups");
    QDir().mkpath(dir);
    return dir;
}

QVariantList BackupService::backupsFromDisk()
{
    QVariantList result;
    const QDir dir(directory());
    const QStringList files = dir.entryList({ QStringLiteral(u"*.json") }, QDir::Files, QDir::Time);
    for (const QString& file : files) {
        const QFileInfo info(dir.filePath(file));
        result.append(QVariantMap{
            { QStringLiteral(u"id"), info.completeBaseName() },
            { QStringLiteral(u"path"), info.filePath() },
            { QStringLiteral(u"created"), info.fileTime(QFileDevice::FileModificationTime).toString(Qt::ISODate) },
            { QStringLiteral(u"size"), info.size() },
        });
    }
    return result;
}

void BackupService::refresh()
{
    m_backups = backupsFromDisk();
    emit changed();
}

QString BackupService::createBackup(const core::Document& document, const QString& label)
{
    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    const QString path = directory() + QStringLiteral(u"/") + id + QStringLiteral(u".json");
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return {};
    QJsonObject root = QJsonDocument::fromJson(document.toJson()).object();
    root.insert(QStringLiteral(u"backupLabel"), label.isEmpty() ? QDateTime::currentDateTime().toString() : label);
    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    refresh();
    emit notification(QStringLiteral(u"Backup created"));
    return id;
}

bool BackupService::restore(const QString& id, core::Document* target)
{
    if (!target)
        return false;
    const QString path = directory() + QStringLiteral(u"/") + id + QStringLiteral(u".json");
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    *target = core::Document::fromJson(file.readAll());
    emit notification(QStringLiteral(u"Backup restored"));
    return true;
}

bool BackupService::remove(const QString& id)
{
    if (QFile::remove(directory() + QStringLiteral(u"/") + id + QStringLiteral(u".json"))) {
        refresh();
        return true;
    }
    return false;
}

} // namespace mxu::app
