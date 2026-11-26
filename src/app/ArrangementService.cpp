#include "ArrangementService.h"

#include <QJsonArray>
#include <QJsonValue>
#include <QUuid>

namespace mxu::app {

ArrangementService::ArrangementService(QObject* parent)
    : QObject(parent)
{
}

void ArrangementService::setDocument(core::Document* document)
{
    m_document = document;
    refresh();
}

QVariantList ArrangementService::arrangements() const { return m_arrangements; }

void ArrangementService::refresh()
{
    m_arrangements.clear();
    if (!m_document)
        return;
    const QJsonArray stored = m_document->arrangements.value(QStringLiteral(u"items")).toArray();
    for (const QJsonValue& value : stored)
        m_arrangements.append(value.toVariant().toMap());
    emit changed();
}

void ArrangementService::commit()
{
    if (!m_document)
        return;
    QJsonArray array;
    for (const QVariant& item : m_arrangements)
        array.append(QJsonValue::fromVariant(item));
    QJsonObject obj = m_document->arrangements;
    obj.insert(QStringLiteral(u"items"), array);
    m_document->arrangements = obj;
    emit changed();
}

QString ArrangementService::save(const QString& name, const QVariantList& slideIndexes)
{
    if (name.trimmed().isEmpty())
        return {};
    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    m_arrangements.append(QVariantMap{
        { QStringLiteral(u"id"), id },
        { QStringLiteral(u"name"), name.trimmed() },
        { QStringLiteral(u"slides"), slideIndexes },
    });
    m_active = name.trimmed();
    commit();
    emit notification(QStringLiteral(u"Arrangement saved: %1").arg(m_active));
    return id;
}

bool ArrangementService::apply(const QString& id)
{
    for (const QVariant& entry : m_arrangements) {
        const QVariantMap arrangement = entry.toMap();
        if (arrangement.value(QStringLiteral(u"id")).toString() != id)
            continue;
        m_active = arrangement.value(QStringLiteral(u"name")).toString();
        const QVariantList slides = arrangement.value(QStringLiteral(u"slides")).toList();
        if (!slides.isEmpty())
            emit slideRequested(slides.first().toInt());
        emit changed();
        emit notification(QStringLiteral(u"Arrangement: %1").arg(m_active));
        return true;
    }
    return false;
}

bool ArrangementService::remove(const QString& id)
{
    for (qsizetype i = 0; i < m_arrangements.size(); ++i) {
        if (m_arrangements.at(i).toMap().value(QStringLiteral(u"id")).toString() != id)
            continue;
        m_arrangements.removeAt(i);
        commit();
        return true;
    }
    return false;
}

} // namespace mxu::app
