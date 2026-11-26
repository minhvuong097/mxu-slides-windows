#include "NotesService.h"

#include <QJsonArray>
#include <QJsonValue>
#include <QUuid>

namespace mxu::app {

NotesService::NotesService(QObject* parent)
    : QObject(parent)
{
}

void NotesService::setDocument(core::Document* document)
{
    m_document = document;
    m_blocks.clear();
    if (m_document) {
        const QJsonArray stored = m_document->notes.value(QStringLiteral(u"blocks")).toArray();
        for (const QJsonValue& value : stored)
            m_blocks.append(value.toVariant().toMap());
    }
    emit changed();
}

QVariantList NotesService::blocks() const { return m_blocks; }

QString NotesService::text() const
{
    QStringList lines;
    for (const QVariant& block : m_blocks)
        lines.append(block.toMap().value(QStringLiteral(u"text")).toString());
    return lines.join(QLatin1Char('\n'));
}

void NotesService::commit()
{
    if (!m_document)
        return;
    QJsonArray array;
    for (const QVariant& block : m_blocks)
        array.append(QJsonValue::fromVariant(block));
    QJsonObject notes = m_document->notes;
    notes.insert(QStringLiteral(u"blocks"), array);
    m_document->notes = notes;
    emit changed();
}

QString NotesService::addBlock(const QString& text)
{
    if (text.trimmed().isEmpty())
        return {};
    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    m_blocks.append(QVariantMap{
        { QStringLiteral(u"id"), id },
        { QStringLiteral(u"type"), QStringLiteral(u"paragraph") },
        { QStringLiteral(u"text"), text.trimmed() },
        { QStringLiteral(u"slideRef"), QString() },
    });
    commit();
    return id;
}

bool NotesService::updateBlock(const QString& id, const QString& text)
{
    for (qsizetype i = 0; i < m_blocks.size(); ++i) {
        QVariantMap block = m_blocks.at(i).toMap();
        if (block.value(QStringLiteral(u"id")).toString() != id)
            continue;
        block.insert(QStringLiteral(u"text"), text);
        m_blocks[i] = block;
        commit();
        return true;
    }
    return false;
}

bool NotesService::removeBlock(const QString& id)
{
    for (qsizetype i = 0; i < m_blocks.size(); ++i) {
        if (m_blocks.at(i).toMap().value(QStringLiteral(u"id")).toString() != id)
            continue;
        m_blocks.removeAt(i);
        commit();
        return true;
    }
    return false;
}

bool NotesService::linkSlide(const QString& id, const QString& slideId)
{
    for (qsizetype i = 0; i < m_blocks.size(); ++i) {
        QVariantMap block = m_blocks.at(i).toMap();
        if (block.value(QStringLiteral(u"id")).toString() != id)
            continue;
        block.insert(QStringLiteral(u"slideRef"), slideId);
        m_blocks[i] = block;
        commit();
        return true;
    }
    return false;
}

} // namespace mxu::app
