#include <QGuiApplication>
#include <QtTest>
#include <QTemporaryDir>

#include "core/Document.h"
#include "core/ShowDocument.h"
#include "core/SceneModel.h"
#include "core/SearchIndex.h"
#include "core/SceneRasterizer.h"
#include "core/AutomergeCompat.h"
#include "audio/WavRecorder.h"
#include "core/SyncLedger.h"
#include "app/AppController.h"
#include "app/AudioService.h"
#include "app/BackupService.h"
#include "app/ConfidenceLayoutService.h"
#include "app/DocumentRegistry.h"
#include "app/ServiceLinkService.h"
#include "app/GroupPaletteService.h"
#include "app/ImportLedgerService.h"
#include "app/PresetBoardService.h"
#include "app/TimecodeService.h"
#include "app/ServiceVersionService.h"
#include "app/DiscoveryService.h"
#include "app/PptxImporter.h"
#include "app/FontService.h"
#include "app/AlertsService.h"
#include "audio/DspEngine.h"
#include "app/AutomationService.h"
#include "app/NotesService.h"
#include "app/TimelineService.h"
#include "app/TimerBoardService.h"
#include "app/MediaService.h"
#include "api/LocalApiServer.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QEventLoop>
#include <QTimer>

using namespace mxu;

class MxuDocumentTest : public QObject
{
    Q_OBJECT

private slots:
    void demoMatchesServiceFlow();
    void jsonRoundTrip();
    void controllerNavigation();
    void slideObjectUndoRedo();
    void sceneAndTransitions();
    void mediaAndAudio();
    void localApiRoutes();
    void automationNotesAndImports();
    void searchSyncDiagnostics();
    void timelineBasic();
    void searchNavigation();
    void slideExport();
    void backupsAndFonts();
    void pptxAndDiscovery();
    void timerBoard();
    void slideActions();
    void confidenceLayout();
    void serviceVersions();
    void documentRegistry();
    void serviceLinks();
    void ledgerAndGroups();
    void presetBoards();
    void slideHistory();
    void midiTimecode();
    void sceneRasterizer();
    void qmlSceneRoundTrip();
    void audioDsp();
    void automergeAndWav();
};

void MxuDocumentTest::demoMatchesServiceFlow()
{
    const core::Document doc = core::Document::demo();
    QCOMPARE(doc.items.size(), 11);
    QCOMPARE(doc.sections.size(), 6);
    QCOMPARE(doc.cues.size(), 4);
    QCOMPARE(doc.cues[0].title, QStringLiteral(u"Pre-roll"));
    QCOMPARE(doc.cues[1].slides.size(), 9);
    QCOMPARE(doc.media.size(), 11);
    QCOMPARE(doc.schemaVersion, 161);
}

void MxuDocumentTest::jsonRoundTrip()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString path = dir.path() + QStringLiteral(u"/service.mxuslides");
    core::Document saved = core::Document::demo();
    QVERIFY(saved.save(path));

    core::Document loaded;
    QVERIFY(loaded.load(path));
    QCOMPARE(loaded.items.size(), saved.items.size());
    QCOMPARE(loaded.cues[1].slides[1].text, saved.cues[1].slides[1].text);
    QCOMPARE(loaded.settings.value(QStringLiteral(u"frameRate")).toString(),
             QStringLiteral(u"60 fps"));
}

void MxuDocumentTest::controllerNavigation()
{
    app::AppController controller;
    QCOMPARE(controller.serviceModel()->property("itemCount").toInt(), 11);
    QCOMPARE(controller.screen(), QStringLiteral(u"present"));

    QMetaObject::invokeMethod(controller.cueModel(), "selectCue", Q_ARG(int, 1));
    controller.next();
    QCOMPARE(controller.cueModel()->property("currentSlideIndex").toInt(), 1);
    controller.previous();
    QCOMPARE(controller.cueModel()->property("currentSlideIndex").toInt(), 0);

    controller.setScreen(QStringLiteral(u"settings"));
    QCOMPARE(controller.screen(), QStringLiteral(u"settings"));
    controller.setSetting(QStringLiteral(u"ndiOutput"), true);
    QVERIFY(controller.setting(QStringLiteral(u"ndiOutput")).toBool());
    controller.setSetting(QStringLiteral(u"ndiOutput"), false);
    QVERIFY(!controller.setting(QStringLiteral(u"ndiOutput")).toBool());
    QCOMPARE(controller.serviceTimerText(), QStringLiteral(u"2:35"));
    controller.setAutoAdvance(true);
    QVERIFY(controller.autoAdvance());
    controller.setAutoAdvanceSeconds(3);
    QCOMPARE(controller.autoAdvanceSeconds(), 3);
    controller.setAutoAdvance(false);
}

void MxuDocumentTest::slideObjectUndoRedo()
{
    core::ShowDocument show;
    show.setDocument(core::Document::demo());
    QCOMPARE(show.slidesForQml().size(), 0);

    const QString slideId = show.addSlide(QStringLiteral(u"Test"), QStringLiteral(u"Hello"));
    QCOMPARE(show.slidesForQml().size(), 1);
    QVERIFY(show.canUndo());
    QVERIFY(!show.canRedo());

    const QString objectId = show.addTextObject(slideId, QStringLiteral(u"Lyric"), 10, 20, 300, 80);
    QCOMPARE(show.objectsForQml(slideId).size(), 2);

    QVERIFY(show.updateObject(slideId, objectId,
                              { { QStringLiteral(u"x"), 123.0 },
                                { QStringLiteral(u"fontSize"), 30.0 },
                                { QStringLiteral(u"colorHex"), QStringLiteral(u"#ff0000") } }));
    const QVariantMap object = show.objectForQml(objectId);
    QCOMPARE(object.value(QStringLiteral(u"x")).toDouble(), 123.0);
    QCOMPARE(object.value(QStringLiteral(u"fontSize")).toDouble(), 30.0);

    show.undo();
    QCOMPARE(show.objectForQml(objectId).value(QStringLiteral(u"x")).toDouble(), 10.0);
    QVERIFY(show.canRedo());
    show.redo();
    QCOMPARE(show.objectForQml(objectId).value(QStringLiteral(u"x")).toDouble(), 123.0);

    QVERIFY(show.removeObject(slideId, objectId));
    QCOMPARE(show.objectsForQml(slideId).size(), 1);
    QVERIFY(show.duplicateSlide(slideId));
    QCOMPARE(show.slidesForQml().size(), 2);
}

void MxuDocumentTest::sceneAndTransitions()
{
    core::ShowDocument show;
    show.setDocument(core::Document::demo());
    const QString id = show.addSlide(QStringLiteral(u"Scene"), QStringLiteral(u"Amazing grace"));
    show.selectSlide(id);

    core::SceneBuilder builder;
    const core::RenderScene scene = builder.build(show, true, true, QStringLiteral(u"9:12 AM"));
    QCOMPARE(scene.layers.size(), 1);
    QCOMPARE(scene.layers.first().items.size(), 1);
    QCOMPARE(core::SceneBuilder::sceneToQml(scene).size(), 1);

    core::SceneTransitionEngine transition;
    transition.start(QStringLiteral(u"fadeBlack"), 0.2);
    QVERIFY(transition.running());
    QCOMPARE(transition.kind(), QStringLiteral(u"fadeBlack"));
    QVERIFY(transition.curtainOpacity() >= 0.0);
    transition.finish();
    QVERIFY(!transition.running());
    QCOMPARE(transition.incomingOpacity(), 1.0);

    core::ShowState state;
    state.present(id);
    QCOMPARE(state.liveSlideId(), id);
    state.clearAll();
    QVERIFY(state.isCleared(QStringLiteral(u"slide")));
    state.restoreAll();
    QVERIFY(!state.isCleared(QStringLiteral(u"slide")));
}

void MxuDocumentTest::mediaAndAudio()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString imagePath = dir.path() + QStringLiteral(u"/sample.png");
    QImage(320, 180, QImage::Format_ARGB32).save(imagePath);

    core::Document doc = core::Document::demo();
    app::MediaService media;
    media.setDocument(&doc);
    const int before = doc.media.size();
    const QString id = media.importFile(imagePath);
    QVERIFY(!id.isEmpty());
    QCOMPARE(doc.media.size(), before + 1);
    QCOMPARE(media.items().size(), before + 1);

    app::AudioService audio;
    const QString channel = audio.addChannel(QStringLiteral(u"Prayer"), imagePath);
    QVERIFY(!channel.isEmpty());
    QCOMPARE(audio.channels().size(), 1);
    QVERIFY(audio.toggleMute(channel));
    QVERIFY(audio.setVolume(channel, 0.5));
    const QString second = audio.addChannel(QStringLiteral(u"Second"), imagePath);
    QVERIFY(audio.crossfade(channel, second, 0.1));
    QVERIFY(audio.stop(channel));
    audio.stopAll();
}

void MxuDocumentTest::localApiRoutes()
{
    app::AppController controller;
    api::LocalApiServer server;
    server.attach(&controller);
    server.setPort(6982);
    QVERIFY(server.start());

    auto request = [](const QByteArray& data) {
        QTcpSocket socket;
        socket.connectToHost(QHostAddress::LocalHost, 6982);
        if (!socket.waitForConnected(2000))
            return QByteArray();
        socket.write(data);
        socket.waitForBytesWritten(1000);
        QEventLoop loop;
        QTimer timeout;
        timeout.setSingleShot(true);
        timeout.setInterval(800);
        QObject::connect(&socket, &QIODevice::readyRead, &loop, [&loop]() { loop.quit(); });
        QObject::connect(&timeout, &QTimer::timeout, &loop, [&loop]() { loop.quit(); });
        timeout.start();
        loop.exec();
        return socket.readAll();
    };

    const QByteArray ping = request("GET /v1/ping HTTP/1.1\r\nHost: localhost\r\n\r\n");
    QVERIFY(ping.contains("\"ok\":true"));

    const QByteArray noAuth = request("GET /v1/status HTTP/1.1\r\nHost: localhost\r\n\r\n");
    QVERIFY(noAuth.contains("Unauthorized"));

    const QByteArray auth = "Authorization: Bearer " + server.token().toUtf8() + "\r\n";
    const QByteArray status = request(QByteArray("GET /v1/status HTTP/1.1\r\nHost: localhost\r\n")
                                      + auth + "\r\n");
    QVERIFY(status.contains("\"ok\":true"));
    QVERIFY(status.contains("MxU Slides for Windows"));

    const QByteArray body = "{\"index\":1}";
    const QByteArray goTo = request(QByteArray("POST /v1/goToSlide HTTP/1.1\r\nHost: localhost\r\n")
                                    + auth + "Content-Type: application/json\r\nContent-Length: "
                                    + QByteArray::number(body.size()) + "\r\n\r\n" + body);
    QVERIFY(goTo.contains("\"ok\":true"));

    const QByteArray fireBody = "{\"action\":\"next\"}";
    const QByteArray fire = request(QByteArray("POST /v1/fire HTTP/1.1\r\nHost: localhost\r\n")
                                    + auth + "Content-Length: "
                                    + QByteArray::number(fireBody.size()) + "\r\n\r\n" + fireBody);
    QVERIFY(fire.contains("\"ok\":true"));

    const QByteArray alertBody = "{\"text\":\"Test alert\"}";
    const QByteArray alert = request(QByteArray("POST /v1/alert HTTP/1.1\r\nHost: localhost\r\n")
                                     + auth + "Content-Length: "
                                     + QByteArray::number(alertBody.size()) + "\r\n\r\n" + alertBody);
    QVERIFY(alert.contains("\"ok\":true"));

    const QByteArray openapi = request("GET /openapi.json HTTP/1.1\r\nHost: localhost\r\n\r\n");
    QVERIFY(openapi.contains("/v1/advance"));
    QVERIFY(openapi.contains("/v1/search"));
    QVERIFY(openapi.contains("/v1/alert"));

    server.stop();
    QVERIFY(!server.running());
}

void MxuDocumentTest::automationNotesAndImports()
{
    app::AppController controller;
    QVERIFY(controller.importLyrics(QStringLiteral(u"Line one\nLine two\n\nLine three")) >= 2);

    app::AutomationService automation;
    automation.attach(&controller);
    QVERIFY(automation.addKeyTrigger(QStringLiteral(u"next"), QStringLiteral(u"F5")));
    QVERIFY(automation.triggers().size() >= 1);
    QVERIFY(automation.triggers().at(0).toMap().value(QStringLiteral(u"action")).toString()
                == QStringLiteral(u"next"));
    QVERIFY(automation.fire(QStringLiteral(u"next")));
    QVERIFY(automation.addSchedule(QStringLiteral(u"Service"), QStringLiteral(u"09:00"),
                                   QStringLiteral(u"present")));
    QVERIFY(automation.schedules().size() >= 1);
    QVERIFY(!automation.timecode().isEmpty());
    QVERIFY(!automation.midiAvailable());

    app::NotesService notes;
    core::Document doc = core::Document::demo();
    notes.setDocument(&doc);
    const QString id = notes.addBlock(QStringLiteral(u"Prayer before sermon"));
    QVERIFY(notes.blocks().size() >= 1);
    QVERIFY(notes.updateBlock(id, QStringLiteral(u"Prayer after sermon")));
    QVERIFY(notes.text().contains(QStringLiteral(u"after sermon")));
    QVERIFY(doc.notes.contains(QStringLiteral(u"blocks")));

    app::AlertsService alerts;
    QVERIFY(alerts.fire(QStringLiteral(u"Wrap up"), QStringLiteral(u"both")));
    QVERIFY(alerts.visible());
    alerts.dismiss();
    QVERIFY(!alerts.visible());
}

void MxuDocumentTest::searchSyncDiagnostics()
{
    core::Document document = core::Document::demo();
    core::ShowDocument show;
    show.setDocument(document);
    const QString id = show.addSlide(QStringLiteral(u"Search"), QStringLiteral(u"amazing grace lyric"));

    core::SearchIndex index;
    index.rebuild(document, show);
    QVERIFY(index.indexedCount() > 0);
    QVERIFY(!index.search(QStringLiteral(u"amazing")).isEmpty());
    QVERIFY(index.search(QStringLiteral(u"zzzznotfound")).isEmpty());

    core::SyncLedger ledger;
    const QVariantMap op = ledger.append(id, QStringLiteral(u"text"), QStringLiteral(u"changed"));
    QCOMPARE(ledger.clock(), 1);
    QCOMPARE(ledger.operationCount(), 1);
    core::SyncLedger peer;
    QCOMPARE(peer.merge(QString::fromUtf8(ledger.exportJson())), 1);
    QCOMPARE(peer.clock(), 1);

    app::DiagnosticsService diagnostics;
    diagnostics.log(QStringLiteral(u"test event"));
    diagnostics.tick();
    QCOMPARE(diagnostics.errorCount(), 0);
    QVERIFY(diagnostics.reportJson().contains(QStringLiteral(u"test event")));
    Q_UNUSED(op)
}

void MxuDocumentTest::timelineBasic()
{
    app::TimelineService timeline;
    QVERIFY(timeline.cues().size() >= 4);
    QCOMPARE(timeline.lanes().size(), 3);
    const QString id = timeline.cues().first().toMap().value(QStringLiteral(u"id")).toString();
    QVERIFY(timeline.moveCue(id, 1234));
    QVERIFY(timeline.resizeCue(id, 2500));
    timeline.seek(1000);
    QCOMPARE(timeline.playhead(), 1000);
    timeline.play();
    QVERIFY(timeline.playing());
    timeline.pause();
    QVERIFY(!timeline.playing());
    QVERIFY(timeline.removeCue(id));
}

void MxuDocumentTest::searchNavigation()
{
    app::AppController controller;
    QVERIFY(controller.openSearchResult(QStringLiteral(u"cue"), QStringLiteral(u"Pre-roll")));
    QCOMPARE(controller.screen(), QStringLiteral(u"present"));
    QVERIFY(controller.openSearchResult(QStringLiteral(u"media"), QStringLiteral(u"Prayer night")));
    QCOMPARE(controller.screen(), QStringLiteral(u"library"));
    QVERIFY(!controller.openSearchResult(QStringLiteral(u"cue"), QStringLiteral(u"missing")));
}

void MxuDocumentTest::slideExport()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    app::AppController controller;
    const QString path = dir.path() + QStringLiteral(u"/slide.png");
    QVERIFY(controller.exportSlideImage(path));
    QVERIFY(QFile::exists(path));
    QVERIFY(QImage(path).size() == QSize(1920, 1080));
}

void MxuDocumentTest::backupsAndFonts()
{
    app::BackupService backups;
    core::Document document = core::Document::demo();
    const QString id = backups.createBackup(document, QStringLiteral(u"Test"));
    QVERIFY(!id.isEmpty());
    QVERIFY(!backups.backups().isEmpty());
    core::Document restored;
    QVERIFY(backups.restore(id, &restored));
    QCOMPARE(restored.items.size(), document.items.size());
    QVERIFY(backups.remove(id));

    app::FontService fonts;
    QVERIFY(!fonts.families().isEmpty());
}

void MxuDocumentTest::pptxAndDiscovery()
{
    app::DiscoveryService discovery;
    discovery.start();
    QVERIFY(discovery.running());
    QVERIFY(!discovery.deviceId().isEmpty());
    discovery.stop();
    QVERIFY(!discovery.running());

    app::PptxImporter importer;
    const QVariantList slides = importer.import(QStringLiteral(u"/does/not/exist.pptx"));
    QVERIFY(slides.isEmpty());
    QVERIFY(!importer.lastError().isEmpty());
}

void MxuDocumentTest::timerBoard()
{
    app::TimerBoardService board;
    QVERIFY(board.timers().size() >= 1);
    const QString id = board.add(QStringLiteral(u"Sermon"), 60, 10, QStringLiteral(u"countUp"));
    QVERIFY(!id.isEmpty());
    QVERIFY(board.start(id));
    QVERIFY(board.runningCount() >= 1);
    QVERIFY(board.pause(id));
    QVERIFY(board.runningCount() == 0);
    QVERIFY(board.reset(id));
    QVERIFY(board.remove(id));
}

void MxuDocumentTest::slideActions()
{
    app::AppController controller;
    const QString id = controller.addSlideAction(QStringLiteral(u"advance"), QString());
    QVERIFY(!id.isEmpty());
    QVERIFY(controller.currentSlideActions().size() >= 1);
    QVERIFY(controller.fireSlideAction(id));
}

void MxuDocumentTest::confidenceLayout()
{
    app::ConfidenceLayoutService layout;
    QVERIFY(layout.nodes().size() >= 3);
    const QString id = layout.add(QStringLiteral(u"stageMessage"), QStringLiteral(u"Message"));
    QVERIFY(!id.isEmpty());
    QVERIFY(layout.move(id, -1));
    QVERIFY(layout.remove(id));
    layout.setStructure(QStringLiteral(u"Grid"));
    QCOMPARE(layout.structure(), QStringLiteral(u"Grid"));
}

void MxuDocumentTest::serviceVersions()
{
    app::ServiceVersionService versions;
    const QString id = versions.add(QStringLiteral(u"Stage"), QVariantList{ QStringLiteral(u"item-1") });
    QVERIFY(!id.isEmpty());
    QCOMPARE(versions.versions().size(), 1);
    QVERIFY(versions.activate(id));
    QCOMPARE(versions.activeStation(), QStringLiteral(u"Stage"));
    QVERIFY(versions.remove(id));
}

void MxuDocumentTest::documentRegistry()
{
    app::DocumentRegistry registry;
    QCOMPARE(registry.kinds().size(), 29);
    QCOMPARE(registry.directoryFor(QStringLiteral(u"presentation")), QStringLiteral(u"presentations"));
    const QString id = registry.create(QStringLiteral(u"presentation"), QStringLiteral(u"Song"));
    QVERIFY(!id.isEmpty());
    QCOMPARE(registry.inKind(QStringLiteral(u"presentation")).size(), 1);
    QVERIFY(registry.remove(id));
}

void MxuDocumentTest::serviceLinks()
{
    app::ServiceLinkService links;
    const QString id = links.add(QStringLiteral(u"station-2"), QStringLiteral(u"follow"));
    QVERIFY(!id.isEmpty());
    QVERIFY(links.toggle(id));
    QVERIFY(links.remove(id));
}

void MxuDocumentTest::ledgerAndGroups()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString file = dir.path() + QStringLiteral(u"/sample.bin");
    QFile out(file);
    QVERIFY(out.open(QIODevice::WriteOnly));
    out.write("sample");
    out.close();

    app::ImportLedgerService ledger;
    const QString id = ledger.record(file);
    QVERIFY(!id.isEmpty());
    QCOMPARE(ledger.record(file), id);
    QVERIFY(ledger.mark(id, QStringLiteral(u"needsTranscode")));
    QVERIFY(ledger.remove(id));

    app::GroupPaletteService groups;
    QVERIFY(groups.groups().size() >= 5);
    const QString gid = groups.add(QStringLiteral(u"Tag"), QStringLiteral(u"#d9472b"));
    QVERIFY(groups.rename(gid, QStringLiteral(u"Tag 2")));
    QVERIFY(groups.remove(gid));
}

void MxuDocumentTest::presetBoards()
{
    app::PresetBoardService board(QStringLiteral(u"effects"));
    QVERIFY(board.presets().size() >= 1);
    const QString id = board.add(QStringLiteral(u"Blur"), QStringLiteral(u"blur"));
    QVERIFY(!id.isEmpty());
    QVERIFY(!board.preset(id).isNull());
    QVERIFY(board.remove(id));
}

void MxuDocumentTest::slideHistory()
{
    app::AppController controller;
    controller.saveSlideVersion(QStringLiteral(u"Before edit"));
    const QVariantList versions = controller.property("slideVersions").toList();
    QVERIFY(versions.size() >= 1);
    QVERIFY(controller.restoreSlideVersion(versions.first().toMap()
                                           .value(QStringLiteral(u"id")).toString()));
}

void MxuDocumentTest::midiTimecode()
{
    app::TimecodeService timecode;
    timecode.setFramesPerSecond(30);
    for (int i = 0; i < 8; ++i)
        timecode.quarterFrame(i);
    QVERIFY(timecode.locked());
    QVERIFY(!timecode.timecode().isEmpty());
    timecode.setManual(QStringLiteral(u"01:02:03:15"));
    QVERIFY(timecode.timecode().contains(QStringLiteral(u"01:02:03")));
    timecode.reset();
    QVERIFY(!timecode.locked());
}

void MxuDocumentTest::sceneRasterizer()
{
    core::ShowDocument show;
    show.setDocument(core::Document::demo());
    show.addSlide(QStringLiteral(u"Raster"), QStringLiteral(u"Hello world"));
    const core::SceneBuilder builder;
    const core::RenderScene scene = builder.build(show, true, true, QStringLiteral(u"9:00 AM"));
    core::SceneRasterizer rasterizer;
    const QImage image = rasterizer.render(scene, QSize(320, 180));
    QVERIFY(!image.isNull());
    QCOMPARE(image.size(), QSize(320, 180));
}

void MxuDocumentTest::qmlSceneRoundTrip()
{
    core::ShowDocument show;
    show.setDocument(core::Document::demo());
    show.addSlide(QStringLiteral(u"Blend"), QStringLiteral(u"Blend me"));
    const core::SceneBuilder builder;
    const core::RenderScene scene = builder.build(show, true, true, QStringLiteral(u"9:00 AM"));
    const QVariantList qml = core::SceneBuilder::sceneToQml(scene);
    const core::RenderScene rebuilt = core::SceneBuilder::sceneFromQml(qml);
    QCOMPARE(rebuilt.layers.size(), 1);
    QCOMPARE(rebuilt.layers.first().items.size(), 1);

    core::SceneRasterizer rasterizer;
    const QImage blended = rasterizer.renderBlended(scene, rebuilt, QSize(160, 90), 0.5,
                                                    QStringLiteral(u"dissolve"));
    QVERIFY(!blended.isNull());
    QCOMPARE(blended.size(), QSize(160, 90));
}

void MxuDocumentTest::audioDsp()
{
    audio::RingBuffer<double> ring(8);
    for (int i = 0; i < 7; ++i)
        QVERIFY(ring.push(i * 0.1));
    QVERIFY(!ring.push(9.0));
    double value = 0.0;
    QVERIFY(ring.pop(value));
    QCOMPARE(ring.available(), 6u);

    QVERIFY(audio::FadeCurveEvaluator::gain(audio::FadeCurve::Linear, 0.0) > 0.9);
    QVERIFY(audio::FadeCurveEvaluator::gain(audio::FadeCurve::EqualPower, 1.0) < 0.01);

    audio::AudioMeter meter;
    for (int i = 0; i < 100; ++i)
        meter.feed(0.5);
    QVERIFY(meter.peak() > 0.0);
    QVERIFY(meter.rms() > 0.0);

    audio::DspMixer mixer;
    QVector<audio::DeckState> decks(2);
    decks[0].playing = true;
    decks[0].gain = 1.0;
    decks[1].playing = true;
    decks[1].gain = 1.0;
    mixer.setChannels(decks);
    QVERIFY(mixer.gainFor(0, 0.0) > 0.9);
    QVERIFY(mixer.gainFor(1, 0.0) < 0.01);
    mixer.advanceFrames(48000);
    QCOMPARE(decks[0].positionFrames, 0u);

    audio::AudioClock clock;
    clock.setSampleRate(48000);
    QCOMPARE(clock.framesForMs(1000), 48000u);
}

void MxuDocumentTest::automergeAndWav()
{
    core::AutomergeCompat local;
    local.setLocalValue(QStringLiteral(u"title"), QStringLiteral(u"Sunday"));
    const QByteArray envelope = local.exportChanges();
    QVERIFY(!envelope.isEmpty());
    core::AutomergeCompat remote;
    QVERIFY(remote.importChanges(envelope) >= 0);
    QCOMPARE(remote.localValue(QStringLiteral(u"title")).toString(), QStringLiteral(u"Sunday"));

    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString path = dir.path() + QStringLiteral(u"/audio.wav");
    audio::WavRecorder recorder;
    QVERIFY(recorder.start(path, 48000, 2, 16));
    recorder.write(QVector<float>{ 0.0f, 0.25f, -0.25f, 0.5f });
    QVERIFY(recorder.frames() >= 2);
    recorder.finish();
    QVERIFY(QFile::exists(path));
    QFile file(path);
    QVERIFY(file.open(QIODevice::ReadOnly));
    QCOMPARE(file.read(4), QByteArray("RIFF"));
}

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);
    MxuDocumentTest test;
    return QTest::qExec(&test, argc, argv);
}

#include "tst_document.moc"
