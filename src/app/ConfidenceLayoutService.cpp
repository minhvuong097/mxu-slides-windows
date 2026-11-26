#include "ConfidenceLayoutService.h"

#include <QUuid>

namespace mxu::app {

ConfidenceLayoutService::ConfidenceLayoutService(QObject* parent)
    : QObject(parent)
{
    load();
    if (m_nodes.isEmpty())
        reset();
}

QVariantList ConfidenceLayoutService::nodes() const { return m_nodes; }

QStringList ConfidenceLayoutService::sourceKinds() const
{
    return { QStringLiteral(u"currentSlide"), QStringLiteral(u"nextSlide"), QStringLiteral(u"clock"),
             QStringLiteral(u"timer"), QStringLiteral(u"stageMessage"), QStringLiteral(u"media") };
}

void ConfidenceLayoutService::setStructure(const QString& value)
{
    if (m_structure == value)
        return;
    m_structure = value;
    save();
    emit changed();
}

void ConfidenceLayoutService::load()
{
    m_nodes = m_store.value(QStringLiteral(u"mxu/confidence/nodes")).toList();
    m_structure = m_store.value(QStringLiteral(u"mxu/confidence/structure"),
                                QStringLiteral(u"Tall Stack")).toString();
}

void ConfidenceLayoutService::save()
{
    m_store.setValue(QStringLiteral(u"mxu/confidence/nodes"), m_nodes);
    m_store.setValue(QStringLiteral(u"mxu/confidence/structure"), m_structure);
    m_store.sync();
}

void ConfidenceLayoutService::reset()
{
    m_nodes.clear();
    m_nodes.append(QVariantMap{ { QStringLiteral(u"id"), QUuid::createUuid().toString(QUuid::WithoutBraces) },
                                { QStringLiteral(u"source"), QStringLiteral(u"clock") },
                                { QStringLiteral(u"title"), QStringLiteral(u"Clock") } });
    m_nodes.append(QVariantMap{ { QStringLiteral(u"id"), QUuid::createUuid().toString(QUuid::WithoutBraces) },
                                { QStringLiteral(u"source"), QStringLiteral(u"currentSlide") },
                                { QStringLiteral(u"title"), QStringLiteral(u"Current Slide") } });
    m_nodes.append(QVariantMap{ { QStringLiteral(u"id"), QUuid::createUuid().toString(QUuid::WithoutBraces) },
                                { QStringLiteral(u"source"), QStringLiteral(u"nextSlide") },
                                { QStringLiteral(u"title"), QStringLiteral(u"Next Slide") } });
    save();
    emit changed();
}

QString ConfidenceLayoutService::add(const QString& source, const QString& title)
{
    if (!sourceKinds().contains(source))
        return {};
    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    m_nodes.append(QVariantMap{ { QStringLiteral(u"id"), id },
                                { QStringLiteral(u"source"), source },
                                { QStringLiteral(u"title"), title.isEmpty() ? source : title } });
    save();
    emit changed();
    return id;
}

bool ConfidenceLayoutService::remove(const QString& id)
{
    for (qsizetype i = 0; i < m_nodes.size(); ++i) {
        if (m_nodes.at(i).toMap().value(QStringLiteral(u"id")).toString() != id)
            continue;
        m_nodes.removeAt(i);
        save();
        emit changed();
        return true;
    }
    return false;
}

bool ConfidenceLayoutService::move(const QString& id, int delta)
{
    for (qsizetype i = 0; i < m_nodes.size(); ++i) {
        if (m_nodes.at(i).toMap().value(QStringLiteral(u"id")).toString() != id)
            continue;
        const qsizetype target = i + delta;
        if (target < 0 || target >= m_nodes.size())
            return false;
        m_nodes.move(i, target);
        save();
        emit changed();
        return true;
    }
    return false;
}

} // namespace mxu::app
