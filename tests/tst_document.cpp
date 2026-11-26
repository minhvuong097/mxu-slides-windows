#include <QGuiApplication>
#include <QtTest>
#include <QTemporaryDir>

#include "core/Document.h"
#include "core/ShowDocument.h"
#include "core/SceneModel.h"
#include "core/SearchIndex.h"
#include "core/SyncLedger.h"
#include "app/AppController.h"
#include "app/AudioService.h"
#include "app/AutomationService.h"
#include "app/NotesService.h"
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

    const QByteArray openapi = request("GET /openapi.json HTTP/1.1\r\nHost: localhost\r\n\r\n");
    QVERIFY(openapi.contains("/v1/advance"));
    QVERIFY(openapi.contains("/v1/search"));

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

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);
    MxuDocumentTest test;
    return QTest::qExec(&test, argc, argv);
}

#include "tst_document.moc"
