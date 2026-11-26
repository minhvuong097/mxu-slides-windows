#pragma once

#include "AlertsService.h"
#include "AudioDeviceService.h"
#include "AutomationService.h"
#include "ConfidenceLayoutService.h"
#include "DiagnosticsService.h"
#include "DocumentRegistry.h"
#include "DiscoveryService.h"
#include "FontService.h"
#include "ArrangementService.h"
#include "AudioService.h"
#include "BackupService.h"
#include "TimelineService.h"
#include "ServiceVersionService.h"
#include "SlideActionRouter.h"
#include "TimerBoardService.h"
#include "MediaService.h"
#include "Models.h"
#include "NotesService.h"
#include "OutputManager.h"
#include "OutputPresetService.h"
#include "PlaylistService.h"
#include "PptxImporter.h"
#include "api/LocalApiServer.h"
#include "api/OutputBackends.h"
#include "api/StreamingService.h"
#include "core/Document.h"
#include "core/SearchIndex.h"
#include "core/SceneModel.h"
#include "core/SyncLedger.h"
#include "core/ShowDocument.h"

#include <QObject>
#include <QtGui/QPainter>
#include <QSettings>
#include <QString>
#include <QTimer>
#include <QVariantList>
#include <QVariantMap>

namespace mxu::app {

// Central shell state for the five macOS-style screens. Owns the document,
// the three QML models, timers, station settings and the Local API.
class AppController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString screen READ screen WRITE setScreen NOTIFY screenChanged)
    Q_PROPERTY(QString accent READ accent CONSTANT)
    Q_PROPERTY(QObject* serviceModel READ serviceModel CONSTANT)
    Q_PROPERTY(QObject* cueModel READ cueModel CONSTANT)
    Q_PROPERTY(QObject* libraryModel READ libraryModel CONSTANT)

    Q_PROPERTY(QString serviceClock READ serviceClock NOTIFY tick)
    Q_PROPERTY(QString previewClock READ previewClock NOTIFY tick)
    Q_PROPERTY(QString serviceTimerText READ serviceTimerText NOTIFY timersChanged)
    Q_PROPERTY(QString serviceTimerDelta READ serviceTimerDelta NOTIFY timersChanged)
    Q_PROPERTY(QString timerState READ timerState NOTIFY timersChanged)
    Q_PROPERTY(QString advanceHeld READ advanceHeld NOTIFY tick)
    Q_PROPERTY(QVariantList timerRows READ timerRows NOTIFY timersChanged)
    Q_PROPERTY(QString currentServiceItem READ currentServiceItem NOTIFY previewChanged)
    Q_PROPERTY(QString nextServiceItem READ nextServiceItem NOTIFY previewChanged)
    Q_PROPERTY(bool timerRunning READ timerRunning NOTIFY timersChanged)

    Q_PROPERTY(QString stageLayout READ stageLayout WRITE setStageLayout NOTIFY stageChanged)
    Q_PROPERTY(QString stageMessage READ stageMessage NOTIFY stageChanged)
    Q_PROPERTY(bool chordsVisible READ chordsVisible NOTIFY stageChanged)
    Q_PROPERTY(bool clockVisible READ clockVisible NOTIFY stageChanged)
    Q_PROPERTY(bool sectionTimerVisible READ sectionTimerVisible NOTIFY stageChanged)
    Q_PROPERTY(int lyricsFontSize READ lyricsFontSize WRITE setLyricsFontSize NOTIFY stageChanged)
    Q_PROPERTY(QString connectedScreens READ connectedScreens NOTIFY stageChanged)

    Q_PROPERTY(QString currentSlideText READ currentSlideText NOTIFY previewChanged)
    Q_PROPERTY(QString currentChord READ currentChord NOTIFY previewChanged)
    Q_PROPERTY(QString nextSlideText READ nextSlideText NOTIFY previewChanged)
    Q_PROPERTY(QString nextChord READ nextChord NOTIFY previewChanged)

    Q_PROPERTY(bool localApiEnabled READ localApiEnabled WRITE setLocalApiEnabled NOTIFY apiChanged)
    Q_PROPERTY(QString localApiToken READ localApiToken NOTIFY apiChanged)
    Q_PROPERTY(QString documentPath READ documentPath NOTIFY documentChanged)

    Q_PROPERTY(bool presenting READ presenting WRITE setPresenting NOTIFY outputChanged)
    Q_PROPERTY(bool stageOutputVisible READ stageOutputVisible WRITE setStageOutputVisible NOTIFY outputChanged)
    Q_PROPERTY(bool outputCleared READ outputCleared WRITE setOutputCleared NOTIFY outputChanged)
    Q_PROPERTY(bool confidenceVisible READ confidenceVisible WRITE setConfidenceVisible NOTIFY outputChanged)
    Q_PROPERTY(bool autoAdvance READ autoAdvance WRITE setAutoAdvance NOTIFY timerChanged)
    Q_PROPERTY(int autoAdvanceSeconds READ autoAdvanceSeconds WRITE setAutoAdvanceSeconds NOTIFY timerChanged)

    Q_PROPERTY(QVariantList slides READ slides NOTIFY editorChanged)
    Q_PROPERTY(QVariantList slideObjects READ slideObjects NOTIFY editorChanged)
    Q_PROPERTY(QVariantMap selectedObject READ selectedObject NOTIFY editorChanged)
    Q_PROPERTY(int selectedSlideIndex READ selectedSlideIndex NOTIFY editorChanged)
    Q_PROPERTY(bool canUndo READ canUndo NOTIFY editorChanged)
    Q_PROPERTY(bool canRedo READ canRedo NOTIFY editorChanged)

    Q_PROPERTY(QVariantList renderLayers READ renderLayers NOTIFY sceneChanged)
    Q_PROPERTY(QString currentSlideName READ currentSlideName NOTIFY sceneChanged)
    Q_PROPERTY(QObject* transition READ transition CONSTANT)
    Q_PROPERTY(QObject* showState READ showState CONSTANT)
    Q_PROPERTY(QObject* mediaService READ mediaService CONSTANT)
    Q_PROPERTY(QObject* audioService READ audioService CONSTANT)
    Q_PROPERTY(QObject* outputs READ outputs CONSTANT)
    Q_PROPERTY(QObject* outputPresets READ outputPresets CONSTANT)
    Q_PROPERTY(QObject* playlist READ playlist CONSTANT)
    Q_PROPERTY(QObject* arrangements READ arrangements CONSTANT)
    Q_PROPERTY(QObject* backupService READ backupService CONSTANT)
    Q_PROPERTY(QObject* fontService READ fontService CONSTANT)
    Q_PROPERTY(QObject* discovery READ discovery CONSTANT)
    Q_PROPERTY(QObject* timerBoard READ timerBoard CONSTANT)
    Q_PROPERTY(QObject* slideActions READ slideActions CONSTANT)
    Q_PROPERTY(QObject* confidenceLayout READ confidenceLayout CONSTANT)
    Q_PROPERTY(QObject* serviceVersions READ serviceVersions CONSTANT)
    Q_PROPERTY(QObject* documents READ documents CONSTANT)
    Q_PROPERTY(QObject* audioDevices READ audioDevices CONSTANT)
    Q_PROPERTY(QVariantList currentSlideActions READ currentSlideActions NOTIFY editorChanged)
    Q_PROPERTY(QString outputScaleMode READ outputScaleMode WRITE setOutputScaleMode NOTIFY settingsChanged)
    Q_PROPERTY(QString outputMaskMode READ outputMaskMode WRITE setOutputMaskMode NOTIFY settingsChanged)
    Q_PROPERTY(QString outputMaskShape READ outputMaskShape WRITE setOutputMaskShape NOTIFY settingsChanged)
    Q_PROPERTY(QObject* ndiSender READ ndiSender CONSTANT)
    Q_PROPERTY(QObject* deckLinkOutput READ deckLinkOutput CONSTANT)
    Q_PROPERTY(QObject* streaming READ streaming CONSTANT)
    Q_PROPERTY(QObject* automation READ automation CONSTANT)
    Q_PROPERTY(QObject* alerts READ alerts CONSTANT)
    Q_PROPERTY(QObject* timeline READ timeline CONSTANT)
    Q_PROPERTY(QObject* notes READ notes CONSTANT)
    Q_PROPERTY(QObject* searchIndex READ searchIndex CONSTANT)
    Q_PROPERTY(QObject* syncLedger READ syncLedger CONSTANT)
    Q_PROPERTY(QObject* diagnostics READ diagnostics CONSTANT)
    Q_PROPERTY(QVariantList audioChannels READ audioChannels NOTIFY audioChanged)
    Q_PROPERTY(QString transitionKind READ transitionKind WRITE setTransitionKind NOTIFY sceneChanged)
    Q_PROPERTY(double transitionDuration READ transitionDuration WRITE setTransitionDuration NOTIFY sceneChanged)

public:
    explicit AppController(QObject* parent = nullptr);
    ~AppController() override;

    QString screen() const { return m_screen; }
    QString accent() const { return QStringLiteral(u"#0a84ff"); }
    QObject* serviceModel() { return &m_service; }
    QObject* cueModel() { return &m_cues; }
    QObject* libraryModel() { return &m_library; }

    QString serviceClock() const;
    QString previewClock() const;
    QString serviceTimerText() const;
    QString serviceTimerDelta() const;
    QString timerState() const;
    QString advanceHeld() const;
    QVariantList timerRows() const;
    QString currentServiceItem() const;
    QString nextServiceItem() const;
    bool timerRunning() const { return m_timerRunning; }

    QString stageLayout() const { return m_stageLayout; }
    QString stageMessage() const { return m_stageMessage; }
    bool chordsVisible() const;
    bool clockVisible() const;
    bool sectionTimerVisible() const;
    int lyricsFontSize() const { return m_lyricsFontSize; }
    QString connectedScreens() const;

    QString currentSlideText() const;
    QString currentChord() const;
    QString nextSlideText() const;
    QString nextChord() const;

    bool localApiEnabled() const;
    QString localApiToken() const;
    QString documentPath() const { return m_documentPath; }

    bool presenting() const { return m_presenting; }
    bool stageOutputVisible() const { return m_stageOutputVisible; }
    bool outputCleared() const { return m_outputCleared; }
    bool confidenceVisible() const { return m_confidenceVisible; }
    bool autoAdvance() const { return m_autoAdvance; }
    int autoAdvanceSeconds() const { return m_autoAdvanceSeconds; }
    void setAutoAdvance(bool value);
    void setAutoAdvanceSeconds(int value);

    QVariantList slides() const;
    QVariantList slideObjects() const;
    QVariantMap selectedObject() const;
    int selectedSlideIndex() const;
    bool canUndo() const;
    bool canRedo() const;

    QVariantList renderLayers() const;
    QString currentSlideName() const;
    QObject* transition() { return &m_transition; }
    QObject* showState() { return &m_showState; }
    QObject* mediaService() { return &m_media; }
    QObject* audioService() { return &m_audio; }
    QVariantList audioChannels() const;
    QObject* outputs() { return &m_outputs; }
    QObject* outputPresets() { return &m_outputPresets; }
    QObject* playlist() { return &m_playlist; }
    QObject* arrangements() { return &m_arrangements; }
    QObject* backupService() { return &m_backups; }
    QObject* fontService() { return &m_fonts; }
    QObject* discovery() { return &m_discovery; }
    QObject* timerBoard() { return &m_timerBoard; }
    QObject* slideActions() { return &m_actionRouter; }
    QObject* confidenceLayout() { return &m_confidenceLayout; }
    QObject* serviceVersions() { return &m_serviceVersions; }
    QObject* documents() { return &m_documents; }
    QObject* audioDevices() { return &m_audioDevices; }
    QVariantList currentSlideActions() const;
    QString outputScaleMode() const;
    QString outputMaskMode() const;
    QString outputMaskShape() const;
    void setOutputScaleMode(const QString& value);
    void setOutputMaskMode(const QString& value);
    void setOutputMaskShape(const QString& value);
    Q_INVOKABLE QString addSlideAction(const QString& kind, const QString& target);
    Q_INVOKABLE bool fireSlideAction(const QString& id);
    QObject* ndiSender() { return &m_ndi; }
    QObject* deckLinkOutput() { return &m_decklink; }
    QObject* streaming() { return &m_streaming; }
    QObject* automation() { return &m_automation; }
    QObject* alerts() { return &m_alerts; }
    QObject* timeline() { return &m_timeline; }
    QObject* notes() { return &m_notes; }
    QObject* searchIndex() { return &m_search; }
    QObject* syncLedger() { return &m_sync; }
    QObject* diagnostics() { return &m_diagnostics; }
    Q_INVOKABLE QVariantList search(const QString& query) const;
    Q_INVOKABLE bool addServiceItem(const QString& name, int section);
    Q_INVOKABLE bool openSearchResult(const QString& kind, const QString& ref);
    Q_INVOKABLE bool moveServiceItem(int from, int to);
    Q_INVOKABLE bool moveSlide(int from, int to);
    Q_INVOKABLE bool exportSlideImage(const QString& path);
    QString transitionKind() const;
    double transitionDuration() const { return m_transitionDuration; }
    void setTransitionKind(const QString& value);
    void setTransitionDuration(double value);

    Q_INVOKABLE QVariant setting(const QString& key) const;
    Q_INVOKABLE void setSetting(const QString& key, const QVariant& value);

public slots:
    void setScreen(const QString& value);
    void toggleSidebar();
    void goToCue(int index);
    void next();
    void previous();
    void toggleClear();
    void toggleRecording();
    void toggleTimer();
    void resetTimer();
    void setStageLayout(const QString& value);
    void setLyricsFontSize(int value);
    void sendStageMessage(const QString& message);
    void toggleStageFlag(const QString& flag);
    void undo();
    void redo();
    void identifyDisplays();
    void setLocalApiEnabled(bool value);
    void regenerateLocalApiToken();
    void setPresenting(bool value);
    void setStageOutputVisible(bool value);
    void setOutputCleared(bool value);
    void setConfidenceVisible(bool value);
    void toggleConfidence();
    void togglePresenting();
    void toggleStageOutput();
    void selectSlide(int index);
    void selectObject(const QString& id);
    void updateObject(const QVariantMap& patch);
    void addTextObject();
    void playTransition();
    int importLyrics(const QString& text);
    bool importProPresenter(const QString& path);
    bool importPptx(const QString& path);
    bool saveDocument(const QString& path = {});
    bool openDocument(const QString& path);

signals:
    void screenChanged();
    void tick();
    void timersChanged();
    void timerChanged();
    void stageChanged();
    void previewChanged();
    void apiChanged();
    void documentChanged();
    void outputChanged();
    void editorChanged();
    void sceneChanged();
    void settingsChanged();
    void audioChanged();
    void notification(const QString& message);

private slots:
    void onTick();
    void refreshPreview();

private:
    void loadSettings();
    void persistSettings();
    void scheduleAutoAdvance();
    static QPainter::CompositionMode itemBlendMode(const QString& mode);
    static QString duration(int seconds);

    core::Document m_document;
    core::ShowDocument m_show;
    core::SceneBuilder m_sceneBuilder;
    core::SceneTransitionEngine m_transition;
    core::ShowState m_showState;
    MediaService m_media;
    AudioService m_audio;
    OutputManager m_outputs;
    OutputPresetService m_outputPresets;
    PlaylistService m_playlist;
    ArrangementService m_arrangements;
    BackupService m_backups;
    PptxImporter m_pptx;
    DiscoveryService m_discovery;
    TimerBoardService m_timerBoard;
    SlideActionRouter m_actionRouter;
    ConfidenceLayoutService m_confidenceLayout;
    ServiceVersionService m_serviceVersions;
    DocumentRegistry m_documents;
    AudioDeviceService m_audioDevices;
    FontService m_fonts;
    api::NdiSender m_ndi;
    api::DeckLinkOutput m_decklink;
    api::StreamingService m_streaming;
    AlertsService m_alerts;
    TimelineService m_timeline;
    AutomationService m_automation;
    NotesService m_notes;
    DiagnosticsService m_diagnostics;
    core::SearchIndex m_search;
    core::SyncLedger m_sync;
    QString m_transitionKind = QStringLiteral(u"dissolve");
    double m_transitionDuration = 0.6;
    ServiceModel m_service;
    CueModel m_cues;
    LibraryModel m_library;
    api::LocalApiServer m_api;
    QSettings m_store;
    QTimer m_clock;
    QTimer m_autoAdvanceTimer;

    QString m_screen = QStringLiteral(u"present");
    QString m_documentPath;
    int m_seconds = 155;
    int m_held = 4;
    bool m_timerRunning = false;
    QString m_stageLayout = QStringLiteral(u"Lyrics + Next");
    QString m_stageMessage = QStringLiteral(u"Please wrap up the song in 1 minute");
    int m_lyricsFontSize = 30;
    bool m_presenting = false;
    bool m_stageOutputVisible = false;
    bool m_outputCleared = false;
    bool m_confidenceVisible = false;
    bool m_autoAdvance = false;
    int m_autoAdvanceSeconds = 5;
};

} // namespace mxu::app
