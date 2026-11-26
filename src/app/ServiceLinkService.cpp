#include "ServiceLinkService.h"

#include <QUuid>

namespace mxu::app {

ServiceLinkService::ServiceLinkService(QObject* parent)
    : QObject(parent)
{
    m_rules = m_store.value(QStringLiteral(u"mxu/serviceLinks")).toList();
}

void ServiceLinkService::persist()
{
    m_store.setValue(QStringLiteral(u"mxu/serviceLinks"), m_rules);
    m_store.sync();
}

QString ServiceLinkService::add(const QString& peerId, const QString& mode)
{
    if (peerId.trimmed().isEmpty())
        return {};
    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    m_rules.append(QVariantMap{
        { QStringLiteral(u"id"), id },
        { QStringLiteral(u"peer"), peerId.trimmed() },
        { QStringLiteral(u"mode"), mode.isEmpty() ? QStringLiteral(u"follow") : mode },
        { QStringLiteral(u"enabled"), true },
    });
    persist();
    emit changed();
    emit notification(QStringLiteral(u"Link added: %1").arg(peerId));
    return id;
}

bool ServiceLinkService::remove(const QString& id)
{
    for (qsizetype i = 0; i < m_rules.size(); ++i) {
        if (m_rules.at(i).toMap().value(QStringLiteral(u"id")).toString() != id)
            continue;
        m_rules.removeAt(i);
        persist();
        emit changed();
        return true;
    }
    return false;
}

bool ServiceLinkService::toggle(const QString& id)
{
    for (qsizetype i = 0; i < m_rules.size(); ++i) {
        QVariantMap rule = m_rules.at(i).toMap();
        if (rule.value(QStringLiteral(u"id")).toString() != id)
            continue;
        rule.insert(QStringLiteral(u"enabled"), !rule.value(QStringLiteral(u"enabled")).toBool());
        m_rules[i] = rule;
        persist();
        emit changed();
        return true;
    }
    return false;
}

} // namespace mxu::app
