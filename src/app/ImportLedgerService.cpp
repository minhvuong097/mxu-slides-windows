#include "ImportLedgerService.h"

#include <QCryptographicHash>
#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QUuid>

namespace mxu::app {

ImportLedgerService::ImportLedgerService(QObject* parent)
    : QObject(parent)
{
}

QString ImportLedgerService::record(const QString& path)
{
    if (path.isEmpty())
        return {};
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return {};
    QCryptographicHash hash(QCryptographicHash::Sha256);
    if (!hash.addData(&file))
        return {};
    const QString digest = QString::fromLatin1(hash.result().toHex());
    for (const QVariant& entry : m_entries) {
        if (entry.toMap().value(QStringLiteral(u"hash")).toString() == digest)
            return entry.toMap().value(QStringLiteral(u"id")).toString();
    }
    const QFileInfo info(path);
    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    m_entries.append(QVariantMap{
        { QStringLiteral(u"id"), id },
        { QStringLiteral(u"path"), path },
        { QStringLiteral(u"name"), info.fileName() },
        { QStringLiteral(u"hash"), digest },
        { QStringLiteral(u"size"), info.size() },
        { QStringLiteral(u"status"), QStringLiteral(u"ready") },
        { QStringLiteral(u"imported"), QDateTime::currentDateTimeUtc().toString(Qt::ISODate) },
    });
    emit changed();
    emit notification(QStringLiteral(u"Imported %1").arg(info.fileName()));
    return id;
}

bool ImportLedgerService::mark(const QString& id, const QString& status)
{
    for (qsizetype i = 0; i < m_entries.size(); ++i) {
        QVariantMap entry = m_entries.at(i).toMap();
        if (entry.value(QStringLiteral(u"id")).toString() != id)
            continue;
        entry.insert(QStringLiteral(u"status"), status);
        m_entries[i] = entry;
        emit changed();
        return true;
    }
    return false;
}

bool ImportLedgerService::remove(const QString& id)
{
    for (qsizetype i = 0; i < m_entries.size(); ++i) {
        if (m_entries.at(i).toMap().value(QStringLiteral(u"id")).toString() != id)
            continue;
        m_entries.removeAt(i);
        emit changed();
        return true;
    }
    return false;
}

void ImportLedgerService::clear()
{
    m_entries.clear();
    emit changed();
}

} // namespace mxu::app
