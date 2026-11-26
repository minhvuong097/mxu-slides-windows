#include "DocumentRegistry.h"

#include <QUuid>

namespace mxu::app {

DocumentRegistry::DocumentRegistry(QObject* parent)
    : QObject(parent)
{
    m_documents = m_store.value(QStringLiteral(u"mxu/documents")).toList();
}

QVariantList DocumentRegistry::kinds() const
{
    const QList<std::pair<QString, QString>> values = {
        { QStringLiteral(u"presentation"), QStringLiteral(u"presentations") },
        { QStringLiteral(u"service"), QStringLiteral(u"services") },
        { QStringLiteral(u"theme"), QStringLiteral(u"themes") },
        { QStringLiteral(u"media"), QStringLiteral(u"media") },
        { QStringLiteral(u"audio"), QStringLiteral(u"audio") },
        { QStringLiteral(u"playlist"), QStringLiteral(u"playlists") },
        { QStringLiteral(u"overlay"), QStringLiteral(u"overlays") },
        { QStringLiteral(u"outputPreset"), QStringLiteral(u"output-presets") },
        { QStringLiteral(u"alertPreset"), QStringLiteral(u"alert-presets") },
        { QStringLiteral(u"streamRecordPreset"), QStringLiteral(u"stream-presets") },
        { QStringLiteral(u"streamDestination"), QStringLiteral(u"stream-destinations") },
        { QStringLiteral(u"actionCombo"), QStringLiteral(u"action-combos") },
        { QStringLiteral(u"scheduleTrigger"), QStringLiteral(u"schedule-triggers") },
        { QStringLiteral(u"schedulerBoard"), QStringLiteral(u"scheduler") },
        { QStringLiteral(u"controlBoard"), QStringLiteral(u"control-boards") },
        { QStringLiteral(u"confidenceLayout"), QStringLiteral(u"confidence-layouts") },
        { QStringLiteral(u"groupPalette"), QStringLiteral(u"groups") },
        { QStringLiteral(u"effectPresetBoard"), QStringLiteral(u"effect-presets") },
        { QStringLiteral(u"animationPresetBoard"), QStringLiteral(u"animation-presets") },
        { QStringLiteral(u"midiDevice"), QStringLiteral(u"midi-devices") },
        { QStringLiteral(u"importLedger"), QStringLiteral(u"import-ledger") },
        { QStringLiteral(u"serviceLinkRules"), QStringLiteral(u"service-link-rules") },
        { QStringLiteral(u"note"), QStringLiteral(u"notes") },
        { QStringLiteral(u"stationSettings"), QStringLiteral(u"station-settings") },
        { QStringLiteral(u"slideBuildingSettings"), QStringLiteral(u"slide-building-settings") },
        { QStringLiteral(u"font"), QStringLiteral(u"font-files") },
        { QStringLiteral(u"workspaceSettings"), QStringLiteral(u"workspace-settings") },
        { QStringLiteral(u"trackChannelList"), QStringLiteral(u"track-channels") },
        { QStringLiteral(u"trackSet"), QStringLiteral(u"track-sets") },
    };
    QVariantList result;
    for (const auto& kind : values)
        result.append(QVariantMap{ { QStringLiteral(u"name"), kind.first },
                                   { QStringLiteral(u"directory"), kind.second } });
    return result;
}

QString DocumentRegistry::directoryFor(const QString& kind) const
{
    for (const QVariant& entry : kinds()) {
        const QVariantMap map = entry.toMap();
        if (map.value(QStringLiteral(u"name")).toString() == kind)
            return map.value(QStringLiteral(u"directory")).toString();
    }
    return {};
}

QVariantList DocumentRegistry::documents() const { return m_documents; }

QVariantList DocumentRegistry::inKind(const QString& kind) const
{
    QVariantList result;
    for (const QVariant& doc : m_documents) {
        if (doc.toMap().value(QStringLiteral(u"kind")).toString() == kind)
            result.append(doc);
    }
    return result;
}

void DocumentRegistry::persist()
{
    m_store.setValue(QStringLiteral(u"mxu/documents"), m_documents);
    m_store.sync();
}

QString DocumentRegistry::create(const QString& kind, const QString& name)
{
    if (directoryFor(kind).isEmpty() || name.trimmed().isEmpty())
        return {};
    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    m_documents.append(QVariantMap{
        { QStringLiteral(u"id"), id },
        { QStringLiteral(u"kind"), kind },
        { QStringLiteral(u"name"), name.trimmed() },
        { QStringLiteral(u"directory"), directoryFor(kind) },
    });
    persist();
    emit changed();
    emit notification(QStringLiteral(u"Created %1: %2").arg(kind, name));
    return id;
}

bool DocumentRegistry::remove(const QString& id)
{
    for (qsizetype i = 0; i < m_documents.size(); ++i) {
        if (m_documents.at(i).toMap().value(QStringLiteral(u"id")).toString() != id)
            continue;
        m_documents.removeAt(i);
        persist();
        emit changed();
        return true;
    }
    return false;
}

} // namespace mxu::app
