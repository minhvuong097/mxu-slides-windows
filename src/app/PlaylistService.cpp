#include "PlaylistService.h"

#include <QUuid>
#include <QRandomGenerator>

namespace mxu::app {

PlaylistService::PlaylistService(QObject* parent)
    : QObject(parent)
{
}

QVariantList PlaylistService::entries() const { return m_entries; }

void PlaylistService::setPlayMode(const QString& value)
{
    if (m_playMode == value)
        return;
    m_playMode = value;
    emit changed();
}

void PlaylistService::setCrossfade(double value)
{
    value = qBound(0.0, value, 10.0);
    if (qFuzzyCompare(m_crossfade, value))
        return;
    m_crossfade = value;
    emit changed();
}

QString PlaylistService::add(const QString& name, const QString& path)
{
    if (name.trimmed().isEmpty())
        return {};
    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    m_entries.append(QVariantMap{
        { QStringLiteral(u"id"), id },
        { QStringLiteral(u"name"), name.trimmed() },
        { QStringLiteral(u"path"), path },
    });
    if (m_current < 0)
        m_current = 0;
    emit changed();
    return id;
}

bool PlaylistService::remove(const QString& id)
{
    for (qsizetype i = 0; i < m_entries.size(); ++i) {
        if (m_entries.at(i).toMap().value(QStringLiteral(u"id")).toString() != id)
            continue;
        m_entries.removeAt(i);
        if (m_current >= m_entries.size())
            m_current = m_entries.isEmpty() ? -1 : 0;
        emit changed();
        return true;
    }
    return false;
}

QString PlaylistService::next()
{
    if (m_entries.isEmpty())
        return {};
    if (m_playMode == QStringLiteral(u"shuffle"))
        m_current = (m_current + 1 + (QRandomGenerator::global()->bounded(qMax(1, m_entries.size() - 1)))) % m_entries.size();
    else if (m_current + 1 >= m_entries.size())
        m_current = m_playMode == QStringLiteral(u"loopPlaylist") ? 0 : m_entries.size() - 1;
    else
        ++m_current;
    const QVariantMap entry = m_entries.at(m_current).toMap();
    emit changed();
    emit entryStarted(entry);
    return entry.value(QStringLiteral(u"id")).toString();
}

void PlaylistService::reset()
{
    m_current = m_entries.isEmpty() ? -1 : 0;
    emit changed();
}

} // namespace mxu::app
