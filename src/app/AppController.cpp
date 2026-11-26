#include "AppController.h"
#include "core/SceneRasterizer.h"

#include <QGuiApplication>
#include <QImage>
#include <QPainter>
#include <QPainterPath>
#include <QTextDocument>
#include <QScreen>
#include <QTime>
#include <QStandardPaths>
#include <QJsonValue>
#include <QUuid>

namespace mxu::app {

namespace {
QString clockText()
{
    return QTime::currentTime().toString(QStringLiteral(u"h:mm AP"));
}

void seedSlides(core::ShowDocument& show, const core::Document& document)
{
    core::Document seeded = document;
    for (const auto& cue : document.cues) {
        mxu::model::Slide slide;
        slide.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
        slide.name = cue.title;
        for (const auto& line : cue.slides) {
            mxu::model::SlideObject object;
            object.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
            object.objectKind = mxu::model::SlideObjectKind::Text;
            object.name = line.tag;
            object.text = line.text.isEmpty() ? cue.title : line.text;
            object.x = 70.0;
            object.y = 130.0;
            object.width = 500.0;
            object.height = 100.0;
            object.textStyle = mxu::model::TextStyle{};
            object.textStyle->fontName = QStringLiteral(u"Segoe UI");
            object.textStyle->fontSize = 22.0;
            object.textStyle->colorHex = QStringLiteral(u"#FFFFFF");
            slide.objects.append(object);
        }
        seeded.slides.append(slide);
    }
    show.setDocument(seeded);
}
}

AppController::AppController(QObject* parent)
    : QObject(parent)
{
    m_document = core::Document::demo();
    seedSlides(m_show, m_document);
    m_service.setDocument(&m_document);
    m_cues.setDocument(&m_document);
    m_library.setDocument(&m_document);
    m_media.setDocument(&m_document);
    m_media.setLedger(&m_importLedger);
    m_notes.setDocument(&m_document);
    m_arrangements.setDocument(&m_document);
    connect(&m_arrangements, &ArrangementService::slideRequested, this, &AppController::selectSlide);
    connect(&m_arrangements, &ArrangementService::notification, this, &AppController::notification);
    connect(&m_backups, &BackupService::notification, this, &AppController::notification);
    m_actionRouter.attach(this);
    connect(&m_actionRouter, &SlideActionRouter::notification, this, &AppController::notification);
    connect(&m_serviceVersions, &ServiceVersionService::notification, this, &AppController::notification);
    connect(&m_documents, &DocumentRegistry::notification, this, &AppController::notification);
    connect(&m_serviceLinks, &ServiceLinkService::notification, this, &AppController::notification);
    connect(&m_importLedger, &ImportLedgerService::notification, this, &AppController::notification);
    connect(&m_timerBoard, &TimerBoardService::warning, this, [this](const QString& name) {
        emit notification(QStringLiteral(u"Warning: %1").arg(name));
    });
    connect(&m_timerBoard, &TimerBoardService::expired, this, [this](const QString& name) {
        emit notification(QStringLiteral(u"Timer expired: %1").arg(name));
    });
    connect(&m_discovery, &DiscoveryService::peerFound, this, [this](const QVariantMap& peer) {
        emit notification(QStringLiteral(u"Peer: %1").arg(peer.value(QStringLiteral(u"name")).toString()));
    });
    m_search.rebuild(m_document, m_show);
    connect(&m_media, &MediaService::notification, this, &AppController::notification);
    connect(&m_audio, &AudioService::notification, this, &AppController::notification);
    connect(&m_audio, &AudioService::changed, this, &AppController::audioChanged);
    connect(&m_outputs, &OutputManager::notification, this, &AppController::notification);
    m_outputPresets.attach(&m_outputs);
    connect(&m_outputPresets, &OutputPresetService::notification, this, &AppController::notification);
    m_automation.attach(this);
    connect(&m_automation, &AutomationService::notification, this, &AppController::notification);
    connect(&m_alerts, &AlertsService::notification, this, &AppController::notification);
    connect(this, &AppController::notification, &m_diagnostics, [this](const QString& message) { m_diagnostics.log(message); });

    loadSettings();

    m_api.attach(this);
    connect(&m_api, &api::LocalApiServer::stateChanged, this, &AppController::apiChanged);
    connect(&m_api, &api::LocalApiServer::tokenChanged, this, &AppController::apiChanged);
    connect(&m_api, &api::LocalApiServer::errorOccurred, this, &AppController::notification);

    connect(&m_service, &ServiceModel::currentChanged, this, &AppController::refreshPreview);
    connect(&m_cues, &CueModel::currentChanged, this, &AppController::refreshPreview);
    connect(&m_library, &LibraryModel::notification, this, &AppController::notification);

    connect(&m_transition, &core::SceneTransitionEngine::changed, this, &AppController::sceneChanged);
    connect(&m_showState, &core::ShowState::changed, this, &AppController::sceneChanged);
    if (!m_show.document().slides.isEmpty())
        m_showState.present(m_show.document().slides.first().id);

    m_autoAdvanceTimer.setSingleShot(true);
    connect(&m_autoAdvanceTimer, &QTimer::timeout, this, [this]() {
        if (m_autoAdvance) {
            next();
            scheduleAutoAdvance();
        }
    });

    m_clock.setInterval(1000);
    connect(&m_clock, &QTimer::timeout, this, &AppController::onTick);
    m_clock.start();
}

AppController::~AppController()
{
    m_api.stop();
}

QString AppController::duration(int seconds)
{
    seconds = qMax(0, seconds);
    return QStringLiteral(u"%1:%2").arg(seconds / 60).arg(seconds % 60, 2, 10, QChar(u'0'));
}

void AppController::loadSettings()
{
    const QStringList defaults = m_document.settings.keys();
    for (const QString& key : defaults)
        m_document.settings.insert(key, QJsonValue::fromVariant(m_store.value(
        QStringLiteral(u"mxu/") + key, m_document.settings.value(key))));
    m_stageLayout = m_store.value(QStringLiteral(u"mxu/stageLayout"), m_stageLayout).toString();
    m_lyricsFontSize = m_store.value(QStringLiteral(u"mxu/lyricsFontSize"), m_lyricsFontSize).toInt();
    m_autoAdvance = m_store.value(QStringLiteral(u"mxu/autoAdvance"), false).toBool();
    m_autoAdvanceSeconds = m_store.value(QStringLiteral(u"mxu/autoAdvanceSeconds"), 5).toInt();
}

void AppController::persistSettings()
{
    const QStringList keys = m_document.settings.keys();
    for (const QString& key : keys)
        m_store.setValue(QStringLiteral(u"mxu/") + key, m_document.settings.value(key));
    m_store.setValue(QStringLiteral(u"mxu/stageLayout"), m_stageLayout);
    m_store.setValue(QStringLiteral(u"mxu/lyricsFontSize"), m_lyricsFontSize);
    m_store.sync();
}

QString AppController::serviceClock() const { return clockText(); }
QString AppController::previewClock() const { return clockText(); }
QString AppController::serviceTimerText() const { return duration(m_seconds); }
QString AppController::serviceTimerDelta() const
{
    return m_timerRunning ? QStringLiteral(u"+0:00") : QStringLiteral(u"+7:24");
}
QString AppController::timerState() const
{
    return m_timerRunning ? QStringLiteral(u"Running preview") : QStringLiteral(u"Not started");
}
QString AppController::advanceHeld() const { return duration(m_held); }

QVariantList AppController::timerRows() const
{
    return {
        QVariantMap{ { QStringLiteral(u"label"), QStringLiteral(u"Section") },
                     { QStringLiteral(u"delta"), QStringLiteral(u"+7:24") },
                     { QStringLiteral(u"value"), serviceTimerText() } },
        QVariantMap{ { QStringLiteral(u"label"), QStringLiteral(u"Service") },
                     { QStringLiteral(u"delta"), QStringLiteral(u"+1:03:53") },
                     { QStringLiteral(u"value"), QStringLiteral(u"23:20") } },
        QVariantMap{ { QStringLiteral(u"label"), QStringLiteral(u"Pre-Service") },
                     { QStringLiteral(u"delta"), QStringLiteral(u"+0:00") },
                     { QStringLiteral(u"value"), QStringLiteral(u"0:00") } },
        QVariantMap{ { QStringLiteral(u"label"), QStringLiteral(u"Next · Amazing Grace") },
                     { QStringLiteral(u"delta"), QString() },
                     { QStringLiteral(u"value"), QStringLiteral(u"4:42") } },
        QVariantMap{ { QStringLiteral(u"label"), QStringLiteral(u"Next service · Retreat") },
                     { QStringLiteral(u"delta"), QString() },
                     { QStringLiteral(u"value"), QStringLiteral(u"44:38:06") } },
    };
}

bool AppController::chordsVisible() const { return setting(QStringLiteral(u"showChords")).toBool(); }
bool AppController::clockVisible() const { return setting(QStringLiteral(u"showClock")).toBool(); }
bool AppController::sectionTimerVisible() const { return setting(QStringLiteral(u"showSectionTimer")).toBool(); }

QString AppController::connectedScreens() const
{
    return QStringLiteral(u"%1 screens connected")
        .arg(qMax(1, QGuiApplication::screens().size()));
}

QString AppController::currentSlideText() const
{
    const QString text = m_cues.currentSlide().value(QStringLiteral(u"text")).toString();
    if (!text.isEmpty())
        return text.split(QLatin1Char('\n')).first();
    return QStringLiteral(u"Amazing grace, how sweet");
}

QString AppController::currentChord() const
{
    static const QStringList chords = { QStringLiteral(u"G"), QStringLiteral(u"D"),
                                        QStringLiteral(u"Em"), QStringLiteral(u"C") };
    return chords.at(qAbs(m_cues.currentSlideIndex()) % chords.size());
}

QString AppController::nextSlideText() const
{
    const QVariantList slides = m_cues.currentCue().value(QStringLiteral(u"slides")).toList();
    const int next = m_cues.currentSlideIndex() + 1;
    if (next >= 0 && next < slides.size()) {
        const QString text = slides.at(next).toMap().value(QStringLiteral(u"text")).toString();
        if (!text.isEmpty())
            return text.split(QLatin1Char('\n')).first();
    }
    return QStringLiteral(u"That saved a wretch like me");
}

QString AppController::nextChord() const
{
    static const QStringList chords = { QStringLiteral(u"D"), QStringLiteral(u"C"),
                                        QStringLiteral(u"G"), QStringLiteral(u"Em") };
    return chords.at(qAbs(m_cues.currentSlideIndex() + 1) % chords.size());
}

bool AppController::localApiEnabled() const { return m_api.running(); }
QString AppController::localApiToken() const { return m_api.token(); }

QVariant AppController::setting(const QString& key) const
{
    return m_document.settings.value(key);
}

void AppController::setSetting(const QString& key, const QVariant& value)
{
    if (!m_document.settings.contains(key) || m_document.settings.value(key) == value)
        return;
    m_document.settings.insert(key, QJsonValue::fromVariant(value));
    persistSettings();
    emit stageChanged();
}

void AppController::setScreen(const QString& value)
{
    if (m_screen == value)
        return;
    m_screen = value;
    emit screenChanged();
}

void AppController::toggleSidebar()
{
    emit notification(QStringLiteral(u"Sidebar toggled"));
}

void AppController::goToCue(int index)
{
    m_cues.selectCue(index);
    m_service.selectItem(index);
}

void AppController::next()
{
    m_cues.nextSlide();
    m_service.nextItem();
    playTransition();
    const QVariantList list = slides();
    const QString id = list.isEmpty() ? QString() : list.at(selectedSlideIndex()).toMap()
                                            .value(QStringLiteral(u"id")).toString();
    if (!id.isEmpty())
        m_showState.present(id);
    m_api.broadcastState();
}

void AppController::previous()
{
    m_cues.previousSlide();
    m_service.previousItem();
    playTransition();
    m_api.broadcastState();
}

void AppController::toggleClear()
{
    setOutputCleared(!m_outputCleared);
    if (m_outputCleared)
        m_showState.clearAll();
    else
        m_showState.restoreAll();
    emit notification(m_outputCleared ? QStringLiteral(u"Output cleared")
                                      : QStringLiteral(u"Output restored"));
}

void AppController::toggleRecording()
{
    emit notification(QStringLiteral(u"Recording toggled"));
}

void AppController::toggleTimer()
{
    m_timerRunning = !m_timerRunning;
    emit timersChanged();
    emit notification(m_timerRunning ? QStringLiteral(u"Service preview running")
                                     : QStringLiteral(u"Service preview paused"));
}

void AppController::resetTimer()
{
    m_timerRunning = false;
    m_seconds = 155;
    m_held = 4;
    emit timersChanged();
}

void AppController::setStageLayout(const QString& value)
{
    if (m_stageLayout == value)
        return;
    m_stageLayout = value;
    persistSettings();
    emit stageChanged();
}

void AppController::setLyricsFontSize(int value)
{
    value = qBound(14, value, 72);
    if (m_lyricsFontSize == value)
        return;
    m_lyricsFontSize = value;
    persistSettings();
    emit stageChanged();
}

void AppController::sendStageMessage(const QString& message)
{
    if (message.trimmed().isEmpty())
        return;
    m_stageMessage = message.trimmed();
    m_showState.setStageMessage(m_stageMessage);
    emit stageChanged();
    emit notification(QStringLiteral(u"Message sent to stage"));
}

void AppController::toggleStageFlag(const QString& flag)
{
    if (!m_document.settings.contains(flag))
        return;
    setSetting(flag, !m_document.settings.value(flag).toBool());
}

void AppController::setPresenting(bool value)
{
    if (m_presenting == value)
        return;
    m_presenting = value;
    emit outputChanged();
    emit notification(m_presenting ? QStringLiteral(u"Presentation output started")
                                   : QStringLiteral(u"Presentation output stopped"));
    m_api.broadcastState();
}

void AppController::setStageOutputVisible(bool value)
{
    if (m_stageOutputVisible == value)
        return;
    m_stageOutputVisible = value;
    emit outputChanged();
    emit notification(m_stageOutputVisible ? QStringLiteral(u"Stage display opened")
                                           : QStringLiteral(u"Stage display closed"));
}

void AppController::setOutputCleared(bool value)
{
    if (m_outputCleared == value)
        return;
    m_outputCleared = value;
    emit outputChanged();
    m_api.broadcastState();
}

void AppController::setAutoAdvance(bool value)
{
    if (m_autoAdvance == value)
        return;
    m_autoAdvance = value;
    m_store.setValue(QStringLiteral(u"mxu/autoAdvance"), value);
    if (value)
        scheduleAutoAdvance();
    else
        m_autoAdvanceTimer.stop();
    emit timerChanged();
    emit notification(value ? QStringLiteral(u"Auto-advance on") : QStringLiteral(u"Auto-advance off"));
}

void AppController::setAutoAdvanceSeconds(int value)
{
    value = qBound(1, value, 120);
    if (m_autoAdvanceSeconds == value)
        return;
    m_autoAdvanceSeconds = value;
    m_store.setValue(QStringLiteral(u"mxu/autoAdvanceSeconds"), value);
    if (m_autoAdvance)
        scheduleAutoAdvance();
    emit timerChanged();
}

void AppController::scheduleAutoAdvance()
{
    if (!m_autoAdvance)
        return;
    m_autoAdvanceTimer.start(m_autoAdvanceSeconds * 1000);
}

void AppController::setConfidenceVisible(bool value)
{
    if (m_confidenceVisible == value)
        return;
    m_confidenceVisible = value;
    emit outputChanged();
    emit notification(m_confidenceVisible ? QStringLiteral(u"Confidence monitor opened")
                                          : QStringLiteral(u"Confidence monitor closed"));
}

void AppController::toggleConfidence()
{
    setConfidenceVisible(!m_confidenceVisible);
}

void AppController::togglePresenting()
{
    setPresenting(!m_presenting);
}

void AppController::toggleStageOutput()
{
    setStageOutputVisible(!m_stageOutputVisible);
}

QVariantList AppController::slides() const
{
    return m_show.slidesForQml();
}

QVariantList AppController::slideObjects() const
{
    return m_show.objectsForQml(m_show.selectedSlide());
}

QVariantMap AppController::selectedObject() const
{
    return m_show.objectForQml(m_show.selectedObject());
}

int AppController::selectedSlideIndex() const
{
    const QVariantList list = slides();
    const QString id = m_show.selectedSlide();
    for (qsizetype i = 0; i < list.size(); ++i) {
        if (list.at(i).toMap().value(QStringLiteral(u"id")).toString() == id)
            return static_cast<int>(i);
    }
    return 0;
}

bool AppController::canUndo() const { return m_show.canUndo(); }
bool AppController::canRedo() const { return m_show.canRedo(); }

void AppController::selectSlide(int index)
{
    const QVariantList list = slides();
    if (index < 0 || index >= list.size())
        return;
    const QString id = list.at(index).toMap().value(QStringLiteral(u"id")).toString();
    m_show.selectSlide(id);
    m_showState.present(id);
    playTransition();
    m_search.rebuild(m_document, m_show);
    emit editorChanged();
    emit sceneChanged();
}

void AppController::selectObject(const QString& id)
{
    m_show.selectObject(id);
    emit editorChanged();
}

void AppController::updateObject(const QVariantMap& patch)
{
    if (!m_show.updateObject(m_show.selectedSlide(), m_show.selectedObject(), patch))
        return;
    emit editorChanged();
}

void AppController::addTextObject()
{
    const QString id = m_show.addTextObject(m_show.selectedSlide(),
                                            QStringLiteral(u"New text"), 70, 300, 500, 80);
    if (!id.isEmpty())
        emit editorChanged();
}

int AppController::importLyrics(const QString& text)
{
    const QStringList lines = text.split(QLatin1Char('\n'));
    int count = 0;
    QString buffer;
    for (const QString& line : lines) {
        const QString trimmed = line.trimmed();
        if (trimmed.isEmpty()) {
            if (!buffer.isEmpty()) {
                m_show.addSlide(QStringLiteral(u"Imported"), buffer);
                ++count;
                buffer.clear();
            }
            continue;
        }
        if (!buffer.isEmpty())
            buffer += QLatin1Char('\n');
        buffer += trimmed;
    }
    if (!buffer.isEmpty()) {
        m_show.addSlide(QStringLiteral(u"Imported"), buffer);
        ++count;
    }
    if (count > 0) {
        emit editorChanged();
        emit sceneChanged();
        emit notification(QStringLiteral(u"Imported %1 slides").arg(count));
    }
    return count;
}

bool AppController::importProPresenter(const QString& path)
{
    Q_UNUSED(path)
    emit notification(QStringLiteral(u"ProPresenter import requires the generated protobuf types"));
    return false;
}

bool AppController::importPptx(const QString& path)
{
    const QVariantList slides = m_pptx.import(path);
    if (slides.isEmpty()) {
        emit notification(m_pptx.lastError().isEmpty() ? QStringLiteral(u"PPTX import failed")
                                                       : m_pptx.lastError());
        return false;
    }
    for (const QVariant& slide : slides) {
        const QVariantMap map = slide.toMap();
        m_show.addSlide(map.value(QStringLiteral(u"name")).toString(),
                        map.value(QStringLiteral(u"text")).toString());
    }
    m_search.rebuild(m_document, m_show);
    emit editorChanged();
    emit sceneChanged();
    emit notification(QStringLiteral(u"Imported %1 PPTX slides").arg(slides.size()));
    return true;
}

bool AppController::moveServiceItem(int from, int to)
{
    if (!m_service.moveItem(from, to))
        return false;
    m_showState.present(QStringLiteral(u""));
    emit notification(QStringLiteral(u"Service item moved"));
    return true;
}

bool AppController::moveSlide(int from, int to)
{
    const QVariantList list = slides();
    if (from < 0 || to < 0 || from >= list.size() || to >= list.size() || from == to)
        return false;
    if (!m_show.moveSlide(list.at(from).toMap().value(QStringLiteral(u"id")).toString(), to - from))
        return false;
    m_search.rebuild(m_document, m_show);
    emit editorChanged();
    emit sceneChanged();
    return true;
}

QPainter::CompositionMode AppController::itemBlendMode(const QString& mode)
{
    if (mode == QStringLiteral(u"multiply"))
        return QPainter::CompositionMode_Multiply;
    if (mode == QStringLiteral(u"screen"))
        return QPainter::CompositionMode_Screen;
    if (mode == QStringLiteral(u"add"))
        return QPainter::CompositionMode_Plus;
    return QPainter::CompositionMode_SourceOver;
}

bool AppController::exportSlideImage(const QString& path)
{
    if (path.isEmpty())
        return false;
    const core::RenderScene scene = m_sceneBuilder.build(m_show, chordsVisible(), clockVisible(),
                                                          serviceClock(), outputScaleMode(),
                                                          outputMaskMode(), outputMaskShape());
    core::SceneRasterizer rasterizer;
    const QImage image = rasterizer.render(scene, QSize(1920, 1080));
    if (!image.save(path))
        return false;
    emit notification(QStringLiteral(u"Exported %1").arg(path));
    return true;
}

bool AppController::openSearchResult(const QString& kind, const QString& ref)
{
    if (kind == QStringLiteral(u"cue")) {
        const QVariantList cues = m_cues.property("cues").toList();
        for (qsizetype i = 0; i < cues.size(); ++i) {
            if (cues.at(i).toMap().value(QStringLiteral(u"title")).toString() != ref)
                continue;
            QMetaObject::invokeMethod(&m_cues, "selectCue", Q_ARG(int, static_cast<int>(i)));
            setScreen(QStringLiteral(u"present"));
            return true;
        }
    } else if (kind == QStringLiteral(u"slide")) {
        const QVariantList list = slides();
        for (qsizetype i = 0; i < list.size(); ++i) {
            if (list.at(i).toMap().value(QStringLiteral(u"name")).toString() != ref)
                continue;
            selectSlide(static_cast<int>(i));
            setScreen(QStringLiteral(u"edit"));
            return true;
        }
    } else if (kind == QStringLiteral(u"media")) {
        setScreen(QStringLiteral(u"library"));
        return true;
    } else if (kind == QStringLiteral(u"note")) {
        setScreen(QStringLiteral(u"edit"));
        return true;
    }
    return false;
}

void AppController::undo()
{
    if (!m_show.canUndo())
        return;
    m_show.undo();
    emit editorChanged();
    emit notification(QStringLiteral(u"Undo"));
}

void AppController::redo()
{
    if (!m_show.canRedo())
        return;
    m_show.redo();
    emit editorChanged();
    emit notification(QStringLiteral(u"Redo"));
}

void AppController::identifyDisplays()
{
    m_outputs.identify();
}

void AppController::setLocalApiEnabled(bool value)
{
    if (value == m_api.running())
        return;
    if (value) {
        if (!m_api.start())
            return;
        emit notification(QStringLiteral(u"Local API listening on %1").arg(m_api.address()));
    } else {
        m_api.stop();
        emit notification(QStringLiteral(u"Local API stopped"));
    }
    emit apiChanged();
}

void AppController::regenerateLocalApiToken()
{
    m_api.regenerateToken();
    emit apiChanged();
    emit notification(QStringLiteral(u"Local API token regenerated"));
}

bool AppController::saveDocument(const QString& path)
{
    const QString target = path.isEmpty() ? m_documentPath : path;
    if (target.isEmpty())
        return false;
    QString error;
    if (!m_show.document().save(target, &error)) {
        emit notification(error);
        return false;
    }
    m_documentPath = target;
    emit documentChanged();
    emit notification(QStringLiteral(u"Saved %1").arg(target));
    m_backups.createBackup(m_document, QStringLiteral(u"Auto"));
    return true;
}

bool AppController::openDocument(const QString& path)
{
    QString error;
    core::Document loaded;
    if (!loaded.load(path, &error)) {
        emit notification(error);
        return false;
    }
    m_document = loaded;
    seedSlides(m_show, m_document);
    m_service.setDocument(&m_document);
    m_cues.setDocument(&m_document);
    m_library.setDocument(&m_document);
    m_media.setDocument(&m_document);
    m_notes.setDocument(&m_document);
    m_arrangements.setDocument(&m_document);
    m_search.rebuild(m_document, m_show);
    loadSettings();
    m_documentPath = path;
    emit documentChanged();
    emit editorChanged();
    return true;
}

QString AppController::currentServiceItem() const
{
    const QVariantMap item = m_service.currentItem();
    return item.value(QStringLiteral(u"name")).toString();
}

QString AppController::nextServiceItem() const
{
    const int count = m_service.itemCount();
    const int index = m_service.currentItemIndex() + 1;
    if (count <= 0 || index >= count)
        return QString();
    const QVariantList sections = m_service.property("sections").toList();
    for (const QVariant& section : sections) {
        const QVariantList items = section.toMap().value(QStringLiteral(u"items")).toList();
        for (const QVariant& entry : items) {
            if (entry.toMap().value(QStringLiteral(u"index")).toInt() == index)
                return entry.toMap().value(QStringLiteral(u"name")).toString();
        }
    }
    return QString();
}

QString AppController::outputScaleMode() const { return setting(QStringLiteral(u"outputScaleMode")).toString(); }
QString AppController::outputMaskMode() const { return setting(QStringLiteral(u"outputMaskMode")).toString(); }
QString AppController::outputMaskShape() const { return setting(QStringLiteral(u"outputMaskShape")).toString(); }
void AppController::setOutputScaleMode(const QString& value) { setSetting(QStringLiteral(u"outputScaleMode"), value); }
void AppController::setOutputMaskMode(const QString& value) { setSetting(QStringLiteral(u"outputMaskMode"), value); }
void AppController::setOutputMaskShape(const QString& value) { setSetting(QStringLiteral(u"outputMaskShape"), value); }

QVariantList AppController::slideVersions() const
{
    return m_show.versionsForQml(m_show.selectedSlide());
}

void AppController::saveSlideVersion(const QString& reason)
{
    if (!m_show.saveVersion(m_show.selectedSlide(), reason).isEmpty()) {
        emit editorChanged();
        emit notification(QStringLiteral(u"Slide version saved"));
    }
}

bool AppController::restoreSlideVersion(const QString& id)
{
    if (!m_show.restoreVersion(m_show.selectedSlide(), id))
        return false;
    emit editorChanged();
    emit sceneChanged();
    emit notification(QStringLiteral(u"Slide version restored"));
    return true;
}

QVariantList AppController::currentSlideActions() const
{
    return m_show.actionsForQml(m_show.selectedSlide());
}

QString AppController::addSlideAction(const QString& kind, const QString& target)
{
    QVariantMap action{
        { QStringLiteral(u"kind"), kind },
        { QStringLiteral(u"layer"), target },
    };
    if (kind == QStringLiteral(u"fireAlert"))
        action.insert(QStringLiteral(u"alertId"), target);
    if (kind.startsWith(QStringLiteral(u"timer")))
        action.insert(QStringLiteral(u"timerId"), target);
    const QString id = m_show.addAction(m_show.selectedSlide(), action);
    if (!id.isEmpty())
        emit editorChanged();
    return id;
}

bool AppController::fireSlideAction(const QString& id)
{
    for (const QVariant& action : currentSlideActions()) {
        const QVariantMap map = action.toMap();
        if (map.value(QStringLiteral(u"id")).toString() != id)
            continue;
        return m_actionRouter.execute(map);
    }
    return false;
}

QVariantList AppController::audioChannels() const
{
    return m_audio.channels();
}

QVariantList AppController::renderLayers() const
{
    const core::RenderScene scene = m_sceneBuilder.build(
        m_show, chordsVisible(), clockVisible(), serviceClock());
    return core::SceneBuilder::sceneToQml(scene);
}

QString AppController::currentSlideName() const
{
    const core::RenderScene scene = m_sceneBuilder.build(m_show, true, true, serviceClock(),
                                                          outputScaleMode(), outputMaskMode(), outputMaskShape());
    return scene.slideName;
}

QString AppController::transitionKind() const
{
    return m_transitionKind;
}

void AppController::setTransitionKind(const QString& value)
{
    if (m_transitionKind == value)
        return;
    m_transitionKind = value;
    emit sceneChanged();
}

void AppController::setTransitionDuration(double value)
{
    value = qBound(0.05, value, 5.0);
    if (qFuzzyCompare(m_transitionDuration, value))
        return;
    m_transitionDuration = value;
    emit sceneChanged();
}

void AppController::playTransition()
{
    m_transition.start(m_transitionKind, m_transitionDuration);
}

void AppController::refreshPreview()
{
    scheduleAutoAdvance();
    emit previewChanged();
    emit sceneChanged();
    m_api.broadcastState();
}

QVariantList AppController::search(const QString& query) const
{
    return m_search.search(query);
}

bool AppController::addServiceItem(const QString& name, int section)
{
    if (!m_service.addItem(name, section))
        return false;
    m_search.rebuild(m_document, m_show);
    emit notification(QStringLiteral(u"Added service item: %1").arg(name));
    return true;
}

void AppController::onTick()
{
    m_diagnostics.tick();
    emit tick();
    if (!m_timerRunning)
        return;
    if (m_seconds > 0)
        --m_seconds;
    ++m_held;
    emit timersChanged();
}

} // namespace mxu::app
