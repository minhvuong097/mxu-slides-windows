#include "ServiceVersionService.h"

#include <QUuid>

namespace mxu::app {

ServiceVersionService::ServiceVersionService(QObject* parent)
    : QObject(parent)
{
}

QVariantList ServiceVersionService::versions() const { return m_versions; }

QString ServiceVersionService::add(const QString& station, const QVariantList& changes)
{
    if (station.trimmed().isEmpty())
        return {};
    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    m_versions.append(QVariantMap{
        { QStringLiteral(u"id"), id },
        { QStringLiteral(u"station"), station.trimmed() },
        { QStringLiteral(u"changes"), changes },
        { QStringLiteral(u"added"), QVariantList() },
    });
    emit changed();
    emit notification(QStringLiteral(u"Service version: %1").arg(station));
    return id;
}

bool ServiceVersionService::activate(const QString& id)
{
    for (const QVariant& entry : m_versions) {
        const QVariantMap version = entry.toMap();
        if (version.value(QStringLiteral(u"id")).toString() != id)
            continue;
        m_active = version.value(QStringLiteral(u"station")).toString();
        emit changed();
        emit notification(QStringLiteral(u"Station: %1").arg(m_active));
        return true;
    }
    return false;
}

bool ServiceVersionService::remove(const QString& id)
{
    for (qsizetype i = 0; i < m_versions.size(); ++i) {
        if (m_versions.at(i).toMap().value(QStringLiteral(u"id")).toString() != id)
            continue;
        m_versions.removeAt(i);
        emit changed();
        return true;
    }
    return false;
}

} // namespace mxu::app
