#include "ThemeService.h"

#include <QUuid>

namespace mxu::app {

namespace {
QVariantMap palette(const QString& bg, const QString& card, const QString& accent,
                    const QString& text, const QString& dim, const QString& green,
                    const QString& pink, const QString& yellow)
{
    return QVariantMap{
        { QStringLiteral(u"bg"), bg },
        { QStringLiteral(u"card"), card },
        { QStringLiteral(u"accent"), accent },
        { QStringLiteral(u"text"), text },
        { QStringLiteral(u"dim"), dim },
        { QStringLiteral(u"green"), green },
        { QStringLiteral(u"pink"), pink },
        { QStringLiteral(u"yellow"), yellow },
    };
}
} // namespace

ThemeService::ThemeService(QObject* parent)
    : QObject(parent)
{
    load();
    if (m_themes.isEmpty()) {
        m_themes = QVariantList{
            QVariantMap{
                { QStringLiteral(u"id"), QStringLiteral(u"midnight") },
                { QStringLiteral(u"name"), QStringLiteral(u"Midnight") },
                { QStringLiteral(u"colors"), palette(QStringLiteral(u"#1c1c1e"), QStringLiteral(u"#232326"),
                    QStringLiteral(u"#0a84ff"), QStringLiteral(u"#f5f5f7"), QStringLiteral(u"#98989d"),
                    QStringLiteral(u"#30d158"), QStringLiteral(u"#ff453a"), QStringLiteral(u"#ffd60a")) },
            },
            QVariantMap{
                { QStringLiteral(u"id"), QStringLiteral(u"contrast") },
                { QStringLiteral(u"name"), QStringLiteral(u"High contrast") },
                { QStringLiteral(u"colors"), palette(QStringLiteral(u"#000000"), QStringLiteral(u"#1a1a1a"),
                    QStringLiteral(u"#ffff00"), QStringLiteral(u"#ffffff"), QStringLiteral(u"#cccccc"),
                    QStringLiteral(u"#00ff66"), QStringLiteral(u"#ff3366"), QStringLiteral(u"#ffff00")) },
            },
            QVariantMap{
                { QStringLiteral(u"id"), QStringLiteral(u"warm") },
                { QStringLiteral(u"name"), QStringLiteral(u"Warm") },
                { QStringLiteral(u"colors"), palette(QStringLiteral(u"#24201d"), QStringLiteral(u"#302a25"),
                    QStringLiteral(u"#ff9f0a"), QStringLiteral(u"#fff3e6"), QStringLiteral(u"#c7b6a5"),
                    QStringLiteral(u"#7ad17a"), QStringLiteral(u"#ff6b6b"), QStringLiteral(u"#ffd60a")) },
            },
            QVariantMap{
                { QStringLiteral(u"id"), QStringLiteral(u"cool") },
                { QStringLiteral(u"name"), QStringLiteral(u"Cool") },
                { QStringLiteral(u"colors"), palette(QStringLiteral(u"#161c24"), QStringLiteral(u"#1e2833"),
                    QStringLiteral(u"#64d2ff"), QStringLiteral(u"#e6f2ff"), QStringLiteral(u"#9fb3c8"),
                    QStringLiteral(u"#40c8a0"), QStringLiteral(u"#ff6b9d"), QStringLiteral(u"#ffe066")) },
            },
        };
        m_currentId = QStringLiteral(u"midnight");
        save();
    }
}

void ThemeService::load()
{
    m_themes = m_store.value(QStringLiteral(u"mxu/themes")).toList();
    m_currentId = m_store.value(QStringLiteral(u"mxu/themeCurrent")).toString();
}

void ThemeService::save()
{
    m_store.setValue(QStringLiteral(u"mxu/themes"), m_themes);
    m_store.setValue(QStringLiteral(u"mxu/themeCurrent"), m_currentId);
    m_store.sync();
}

QVariantMap ThemeService::current() const
{
    for (const QVariant& entry : m_themes) {
        const QVariantMap theme = entry.toMap();
        if (theme.value(QStringLiteral(u"id")).toString() == m_currentId)
            return theme.value(QStringLiteral(u"colors")).toMap();
    }
    return m_themes.isEmpty() ? QVariantMap() : m_themes.first().toMap().value(QStringLiteral(u"colors")).toMap();
}

QString ThemeService::color(const QString& key) const
{
    const QVariantMap colors = current();
    if (colors.contains(key))
        return colors.value(key).toString();
    if (key == QStringLiteral(u"accent")) return QStringLiteral(u"#0a84ff");
    if (key == QStringLiteral(u"bg")) return QStringLiteral(u"#1c1c1e");
    if (key == QStringLiteral(u"card")) return QStringLiteral(u"#232326");
    if (key == QStringLiteral(u"green")) return QStringLiteral(u"#30d158");
    if (key == QStringLiteral(u"pink")) return QStringLiteral(u"#ff453a");
    if (key == QStringLiteral(u"yellow")) return QStringLiteral(u"#ffd60a");
    return QStringLiteral(u"#f5f5f7");
}

void ThemeService::setColor(const QString& key, const QString& value)
{
    if (key.isEmpty() || value.isEmpty())
        return;
    for (qsizetype i = 0; i < m_themes.size(); ++i) {
        QVariantMap theme = m_themes.at(i).toMap();
        if (theme.value(QStringLiteral(u"id")).toString() != m_currentId)
            continue;
        QVariantMap colors = theme.value(QStringLiteral(u"colors")).toMap();
        colors.insert(key, value);
        theme.insert(QStringLiteral(u"colors"), colors);
        m_themes[i] = theme;
        save();
        emit changed();
        return;
    }
}

QString ThemeService::addTheme(const QString& name, const QVariantMap& colors)
{
    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    QVariantMap theme{
        { QStringLiteral(u"id"), id },
        { QStringLiteral(u"name"), name.isEmpty() ? QStringLiteral(u"Custom") : name },
        { QStringLiteral(u"colors"), colors.isEmpty() ? current() : colors },
    };
    m_themes.append(theme);
    m_currentId = id;
    save();
    emit changed();
    return id;
}

bool ThemeService::apply(const QString& id)
{
    for (const QVariant& entry : m_themes) {
        if (entry.toMap().value(QStringLiteral(u"id")).toString() != id)
            continue;
        m_currentId = id;
        save();
        emit changed();
        return true;
    }
    return false;
}

bool ThemeService::remove(const QString& id)
{
    if (m_themes.size() <= 1)
        return false;
    for (qsizetype i = 0; i < m_themes.size(); ++i) {
        if (m_themes.at(i).toMap().value(QStringLiteral(u"id")).toString() != id)
            continue;
        m_themes.removeAt(i);
        if (m_currentId == id)
            m_currentId = m_themes.first().toMap().value(QStringLiteral(u"id")).toString();
        save();
        emit changed();
        return true;
    }
    return false;
}

} // namespace mxu::app
