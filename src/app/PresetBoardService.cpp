#include "PresetBoardService.h"

#include <QUuid>

namespace mxu::app {

PresetBoardService::PresetBoardService(const QString& board, QObject* parent)
    : QObject(parent)
    , m_board(board)
{
    m_presets = m_store.value(QStringLiteral(u"mxu/presets/") + board).toList();
    if (m_presets.isEmpty()) {
        const QStringList names = board == QStringLiteral(u"alerts")
                                      ? QStringList{ QStringLiteral(u"Wrap up"),
                                                     QStringLiteral(u"Stand by"),
                                                     QStringLiteral(u"Offering") }
                                      : QStringList{ QStringLiteral(u"Fade in"),
                                                     QStringLiteral(u"Dissolve") };
        for (const QString& name : names) {
            m_presets.append(QVariantMap{
                { QStringLiteral(u"id"), QUuid::createUuid().toString(QUuid::WithoutBraces) },
                { QStringLiteral(u"name"), name },
                { QStringLiteral(u"value"), name },
            });
        }
        m_store.setValue(QStringLiteral(u"mxu/presets/") + board, m_presets);
        m_store.sync();
    }
}

QString PresetBoardService::add(const QString& name, const QString& value)
{
    if (name.trimmed().isEmpty())
        return {};
    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    m_presets.append(QVariantMap{ { QStringLiteral(u"id"), id },
                                  { QStringLiteral(u"name"), name.trimmed() },
                                  { QStringLiteral(u"value"), value.isEmpty() ? name.trimmed() : value } });
    m_store.setValue(QStringLiteral(u"mxu/presets/") + m_board, m_presets);
    m_store.sync();
    emit changed();
    return id;
}

bool PresetBoardService::remove(const QString& id)
{
    for (qsizetype i = 0; i < m_presets.size(); ++i) {
        if (m_presets.at(i).toMap().value(QStringLiteral(u"id")).toString() != id)
            continue;
        m_presets.removeAt(i);
        m_store.setValue(QStringLiteral(u"mxu/presets/") + m_board, m_presets);
        m_store.sync();
        emit changed();
        return true;
    }
    return false;
}

QVariant PresetBoardService::preset(const QString& id) const
{
    for (const QVariant& entry : m_presets) {
        if (entry.toMap().value(QStringLiteral(u"id")).toString() == id)
            return entry;
    }
    return {};
}

} // namespace mxu::app
