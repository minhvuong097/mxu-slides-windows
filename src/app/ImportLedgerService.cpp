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
    load();
}

void ImportLedgerService::load()
{
    m_entries = m_store.value(QStringLiteral(u"mxu/importLedger")).toList();
}

void ImportLedgerService::save()
{
    m_store.setValue(QStringLiteral(u"mxu/importLedger"), m_entries);
    m_store.sync();
}

QVariantMap ImportLedgerService::counts() const
{
    QVariantMap result{
        { QStringLiteral(u"total"), m_entries.size() },
        { QStringLiteral(u"ready"), 0 },
        { QStringLiteral(u"pending"), 0 },
        { QStringLiteral(u"failed"), 0 },
        { QStringLiteral(u"missing"), 0 },
    };
    for (const QVariant& entry : m_entries) {
        const QString status = entry.toMap().value(QStringLiteral(u"status")).toString();
        if (result.contains(status))
            result[status] = result.value(status).toInt() + 1;
    }
    return result;
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
    save();
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
        save();
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
        save();
        emit changed();
        return true;
    }
    return false;
}

bool ImportLedgerService::verify(const QString& id)
{
    for (qsizetype i = 0; i < m_entries.size(); ++i) {
        QVariantMap entry = m_entries.at(i).toMap();
        if (entry.value(QStringLiteral(u"id")).toString() != id)
            continue;
        const QString path = entry.value(QStringLiteral(u"path")).toString();
        if (!QFileInfo::exists(path)) {
            entry.insert(QStringLiteral(u"status"), QStringLiteral(u"missing"));
        } else {
            QFile file(path);
            QCryptographicHash hash(QCryptographicHash::Sha256);
            if (file.open(QIODevice::ReadOnly) && hash.addData(&file)) {
                const QString digest = QString::fromLatin1(hash.result().toHex());
                entry.insert(QStringLiteral(u"status"),
                             digest == entry.value(QStringLiteral(u"hash")).toString()
                             ? QStringLiteral(u"ready") : QStringLiteral(u"changed"));
            } else {
                entry.insert(QStringLiteral(u"status"), QStringLiteral(u"failed"));
            }
        }
        m_entries[i] = entry;
        save();
        emit changed();
        return true;
    }
    return false;
}

bool ImportLedgerService::retry(const QString& id)
{
    if (!mark(id, QStringLiteral(u"pending")))
        return false;
    const bool verified = verify(id);
    emit notification(verified ? QStringLiteral(u"Import rechecked") : QStringLiteral(u"Retry failed"));
    return verified;
}

void ImportLedgerService::clear()
{
    m_entries.clear();
    save();
    emit changed();
}

} // namespace mxu::app
