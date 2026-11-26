#include "OutputPresetService.h"
#include "OutputManager.h"

#include <QUuid>

namespace mxu::app {

OutputPresetService::OutputPresetService(QObject* parent)
    : QObject(parent)
{
    load();
}

QVariantList OutputPresetService::presets() const { return m_presets; }

void OutputPresetService::load()
{
    m_presets = m_store.value(QStringLiteral(u"mxu/outputPresets")).toList();
    if (m_presets.isEmpty()) {
        m_presets.append(QVariantMap{
            { QStringLiteral(u"id"), QStringLiteral(u"default") },
            { QStringLiteral(u"name"), QStringLiteral(u"Default — All") },
            { QStringLiteral(u"main"), QStringLiteral(u"Display 2 (1920 × 1080)") },
            { QStringLiteral(u"stage"), QStringLiteral(u"Display 3") },
            { QStringLiteral(u"confidence"), true },
            { QStringLiteral(u"alwaysOnTop"), true },
        });
        persist();
    }
    m_active = m_store.value(QStringLiteral(u"mxu/outputPresetActive"),
                             QStringLiteral(u"Default — All")).toString();
}

void OutputPresetService::persist()
{
    m_store.setValue(QStringLiteral(u"mxu/outputPresets"), m_presets);
    m_store.setValue(QStringLiteral(u"mxu/outputPresetActive"), m_active);
    m_store.sync();
}

QString OutputPresetService::save(const QString& name, bool confidence, bool alwaysOnTop)
{
    if (name.trimmed().isEmpty() || !m_outputs)
        return {};
    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    m_presets.append(QVariantMap{
        { QStringLiteral(u"id"), id },
        { QStringLiteral(u"name"), name.trimmed() },
        { QStringLiteral(u"main"), m_outputs->assignment(QStringLiteral(u"main")) },
        { QStringLiteral(u"stage"), m_outputs->assignment(QStringLiteral(u"stage")) },
        { QStringLiteral(u"confidence"), confidence },
        { QStringLiteral(u"alwaysOnTop"), alwaysOnTop },
    });
    m_active = name.trimmed();
    persist();
    emit changed();
    emit notification(QStringLiteral(u"Output preset saved: %1").arg(m_active));
    return id;
}

bool OutputPresetService::apply(const QString& id)
{
    if (!m_outputs)
        return false;
    for (const QVariant& entry : m_presets) {
        const QVariantMap preset = entry.toMap();
        if (preset.value(QStringLiteral(u"id")).toString() != id)
            continue;
        m_outputs->assign(QStringLiteral(u"main"),
                          preset.value(QStringLiteral(u"main")).toString().contains(QStringLiteral(u"Display 2")) ? 1 : 0);
        m_outputs->assign(QStringLiteral(u"stage"),
                          preset.value(QStringLiteral(u"stage")).toString().contains(QStringLiteral(u"Display 3")) ? 2 : 0);
        m_outputs->setConfidenceMonitor(preset.value(QStringLiteral(u"confidence")).toBool());
        m_outputs->setAlwaysOnTop(preset.value(QStringLiteral(u"alwaysOnTop")).toBool());
        m_active = preset.value(QStringLiteral(u"name")).toString();
        persist();
        emit changed();
        emit notification(QStringLiteral(u"Preset applied: %1").arg(m_active));
        return true;
    }
    return false;
}

bool OutputPresetService::remove(const QString& id)
{
    for (qsizetype i = 0; i < m_presets.size(); ++i) {
        if (m_presets.at(i).toMap().value(QStringLiteral(u"id")).toString() != id)
            continue;
        m_presets.removeAt(i);
        persist();
        emit changed();
        return true;
    }
    return false;
}

} // namespace mxu::app
