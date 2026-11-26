#include <QGuiApplication>
#include <QtTest>
#include <QTemporaryDir>

#include "core/Document.h"
#include "core/ShowDocument.h"
#include "core/SceneModel.h"
#include "app/AppController.h"

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

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);
    MxuDocumentTest test;
    return QTest::qExec(&test, argc, argv);
}

#include "tst_document.moc"
