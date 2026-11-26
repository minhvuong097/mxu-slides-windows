#pragma once

#include <QObject>
#include <QSettings>
#include <QString>
#include <QVariantList>

namespace mxu::app {

// Generic preset boards for alerts, effects and animations (macOS
// AlertPresetBoard / EffectPresetBoard / AnimationPresetBoard).
class PresetBoardService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString board READ board CONSTANT)
    Q_PROPERTY(QVariantList presets READ presets NOTIFY changed)

public:
    explicit PresetBoardService(const QString& board, QObject* parent = nullptr);

    QString board() const { return m_board; }
    QVariantList presets() const { return m_presets; }

public slots:
    QString add(const QString& name, const QString& value);
    bool remove(const QString& id);
    QVariant preset(const QString& id) const;

signals:
    void changed();

private:
    QString m_board;
    QSettings m_store;
    QVariantList m_presets;
};

} // namespace mxu::app
