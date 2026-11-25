#pragma once

#include "Models.h"
#include "api/LocalApiServer.h"
#include "core/Document.h"

#include <QObject>
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
    void togglePresenting();
    void toggleStageOutput();
    bool saveDocument(const QString& path = {});
    bool openDocument(const QString& path);

signals:
    void screenChanged();
    void tick();
    void timersChanged();
    void stageChanged();
    void previewChanged();
    void apiChanged();
    void documentChanged();
    void outputChanged();
    void notification(const QString& message);

private slots:
    void onTick();
    void refreshPreview();

private:
    void loadSettings();
    void persistSettings();
    static QString duration(int seconds);

    core::Document m_document;
    ServiceModel m_service;
    CueModel m_cues;
    LibraryModel m_library;
    api::LocalApiServer m_api;
    QSettings m_store;
    QTimer m_clock;

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
};

} // namespace mxu::app
