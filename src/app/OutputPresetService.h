#pragma once

#include <QObject>
#include <QSettings>
#include <QString>
#include <QVariantList>
#include <QVariantMap>

namespace mxu::app {

class OutputManager;

// Persisted per-show output presets: screen assignments + station flags,
// equivalent to the macOS OutputPresetsController.
class OutputPresetService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList presets READ presets NOTIFY changed)
    Q_PROPERTY(QString activeName READ activeName NOTIFY changed)

public:
    explicit OutputPresetService(QObject* parent = nullptr);
    void attach(OutputManager* outputs) { m_outputs = outputs; }

    QVariantList presets() const;
    QString activeName() const { return m_active; }

public slots:
    QString save(const QString& name, bool confidence, bool alwaysOnTop);
    bool apply(const QString& id);
    bool remove(const QString& id);

signals:
    void changed();
    void notification(const QString& message);

private:
    void load();
    void persist();

    QSettings m_store;
    QVariantList m_presets;
    OutputManager* m_outputs = nullptr;
    QString m_active;
};

} // namespace mxu::app
