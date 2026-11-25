#include <QGuiApplication>
#include <QtTest>
#include <QTemporaryDir>

#include "core/Document.h"
#include "app/AppController.h"

using namespace mxu;

class MxuDocumentTest : public QObject
{
    Q_OBJECT

private slots:
    void demoMatchesServiceFlow();
    void jsonRoundTrip();
    void controllerNavigation();
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

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);
    MxuDocumentTest test;
    return QTest::qExec(&test, argc, argv);
}

#include "tst_document.moc"
