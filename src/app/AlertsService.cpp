#include "AlertsService.h"

#include <QDateTime>

namespace mxu::app {

AlertsService::AlertsService(QObject* parent)
    : QObject(parent)
{
}

bool AlertsService::fire(const QString& text, const QString& target, const QString& behavior)
{
    if (text.trimmed().isEmpty())
        return false;
    m_active = QVariantMap{
        { QStringLiteral(u"id"), QDateTime::currentMSecsSinceEpoch() },
        { QStringLiteral(u"text"), text.trimmed() },
        { QStringLiteral(u"target"), target },
        { QStringLiteral(u"behavior"), behavior },
    };
    m_visible = true;
    emit changed();
    emit notification(QStringLiteral(u"Alert: %1").arg(text.trimmed()));
    return true;
}

void AlertsService::dismiss()
{
    if (!m_visible)
        return;
    m_visible = false;
    m_active.clear();
    emit changed();
}

} // namespace mxu::app
