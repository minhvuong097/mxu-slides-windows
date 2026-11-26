#include "DiagnosticsService.h"

#include <QDateTime>
#include <QJsonDocument>

namespace mxu::app {

DiagnosticsService::DiagnosticsService(QObject* parent)
    : QObject(parent)
{
    m_started.start();
}

QVariantList DiagnosticsService::events() const { return m_events; }

QString DiagnosticsService::uptime() const
{
    const qint64 seconds = m_started.elapsed() / 1000;
    return QStringLiteral(u"%1:%2:%3")
        .arg(seconds / 3600, 2, 10, QChar(u'0'))
        .arg((seconds / 60) % 60, 2, 10, QChar(u'0'))
        .arg(seconds % 60, 2, 10, QChar(u'0'));
}

void DiagnosticsService::log(const QString& message, bool isError)
{
    if (isError)
        ++m_errors;
    m_events.prepend(QVariantMap{
        { QStringLiteral(u"at"), QDateTime::currentDateTimeUtc().toString(Qt::ISODate) },
        { QStringLiteral(u"message"), message },
        { QStringLiteral(u"error"), isError },
    });
    while (m_events.size() > 200)
        m_events.removeLast();
    emit changed();
}

void DiagnosticsService::tick()
{
    ++m_ticks;
    if (m_ticks % 30 == 0)
        emit changed();
}

QString DiagnosticsService::reportJson() const
{
    return QString::fromUtf8(QJsonDocument::fromVariant(QVariantMap{
        { QStringLiteral(u"uptime"), uptime() },
        { QStringLiteral(u"ticks"), m_ticks },
        { QStringLiteral(u"errors"), m_errors },
        { QStringLiteral(u"events"), m_events },
    }).toJson(QJsonDocument::Compact));
}

} // namespace mxu::app
