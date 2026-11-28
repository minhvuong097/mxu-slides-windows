#pragma once

#include <QObject>
#include <QSettings>
#include <QString>
#include <QVariantList>
#include <QVariantMap>

namespace mxu::app {

// Editable theme presets (Mac ThemeExplorerView / ThemeDesigns): persisted
// color tokens that QML reads through Mxu.themeService.color().
class ThemeService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList themes READ themes NOTIFY changed)
    Q_PROPERTY(QVariantMap current READ current NOTIFY changed)
    Q_PROPERTY(QString currentId READ currentId NOTIFY changed)

public:
    explicit ThemeService(QObject* parent = nullptr);

    QVariantList themes() const { return m_themes; }
    QVariantMap current() const;
    QString currentId() const { return m_currentId; }

    Q_INVOKABLE QString color(const QString& key) const;
    Q_INVOKABLE void setColor(const QString& key, const QString& value);

public slots:
    QString addTheme(const QString& name, const QVariantMap& colors);
    bool apply(const QString& id);
    bool remove(const QString& id);

signals:
    void changed();

private:
    void load();
    void save();

    QSettings m_store;
    QVariantList m_themes;
    QString m_currentId;
};

} // namespace mxu::app
