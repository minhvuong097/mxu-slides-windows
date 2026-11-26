#include "GroupPaletteService.h"

#include <QUuid>

namespace mxu::app {

GroupPaletteService::GroupPaletteService(QObject* parent)
    : QObject(parent)
{
    const QStringList names = { QStringLiteral(u"Intro"), QStringLiteral(u"Verse"),
                                QStringLiteral(u"Chorus"), QStringLiteral(u"Bridge"),
                                QStringLiteral(u"Outro") };
    const QStringList colors = { QStringLiteral(u"#b8960b"), QStringLiteral(u"#0a64c8"),
                                 QStringLiteral(u"#c8203f"), QStringLiteral(u"#8a3fc8"),
                                 QStringLiteral(u"#8c7a1c") };
    for (qsizetype i = 0; i < names.size(); ++i) {
        m_groups.append(QVariantMap{ { QStringLiteral(u"id"), QUuid::createUuid().toString(QUuid::WithoutBraces) },
                                     { QStringLiteral(u"name"), names.at(i) },
                                     { QStringLiteral(u"color"), colors.at(i) } });
    }
}

QString GroupPaletteService::add(const QString& name, const QString& color)
{
    if (name.trimmed().isEmpty())
        return {};
    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    m_groups.append(QVariantMap{ { QStringLiteral(u"id"), id },
                                 { QStringLiteral(u"name"), name.trimmed() },
                                 { QStringLiteral(u"color"), color.isEmpty() ? QStringLiteral(u"#0a84ff") : color } });
    emit changed();
    return id;
}

bool GroupPaletteService::remove(const QString& id)
{
    for (qsizetype i = 0; i < m_groups.size(); ++i) {
        if (m_groups.at(i).toMap().value(QStringLiteral(u"id")).toString() != id)
            continue;
        m_groups.removeAt(i);
        emit changed();
        return true;
    }
    return false;
}

bool GroupPaletteService::rename(const QString& id, const QString& name)
{
    for (qsizetype i = 0; i < m_groups.size(); ++i) {
        QVariantMap group = m_groups.at(i).toMap();
        if (group.value(QStringLiteral(u"id")).toString() != id || name.trimmed().isEmpty())
            continue;
        group.insert(QStringLiteral(u"name"), name.trimmed());
        m_groups[i] = group;
        emit changed();
        return true;
    }
    return false;
}

} // namespace mxu::app
