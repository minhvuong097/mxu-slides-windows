#include "app/AppController.h"
#include "ui/ScenePaintedItem.h"

#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QCommandLineParser>

int main(int argc, char* argv[])
{
    qmlRegisterType<mxu::ui::ScenePaintedItem>("Mxu.Scene", 1, 0, "SceneSurface");

    QGuiApplication app(argc, argv);
    app.setApplicationName(QStringLiteral(u"MxU Slides"));
    app.setApplicationDisplayName(QStringLiteral(u"MxU Slides"));
    app.setOrganizationName(QStringLiteral(u"MxU"));
    app.setOrganizationDomain(QStringLiteral(u"mxu.app"));
    app.setApplicationVersion(QStringLiteral(u"0.1.0"));
    QGuiApplication::setWindowIcon(QIcon(QStringLiteral(u":/resources/icons/appicon.ico")));

    QCommandLineParser parser;
    parser.setApplicationDescription(QStringLiteral(u"MxU Slides for Windows"));
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument(QStringLiteral(u"document"),
                                 QStringLiteral(u"Optional .mxuslides document"),
                                 QStringLiteral(u"[document]"));
    parser.process(app);

    mxu::app::AppController controller;

    QQmlApplicationEngine engine;
    engine.addImportPath(QStringLiteral(u"qrc:/qml"));
    engine.rootContext()->setContextProperty(QStringLiteral(u"Mxu"), &controller);
    engine.rootContext()->setContextProperty(QStringLiteral(u"AppVersion"),
                                             QStringLiteral(u"0.1.0"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
    engine.load(QUrl(QStringLiteral(u"qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    const auto args = parser.positionalArguments();
    if (!args.isEmpty())
        controller.openDocument(args.first());

    return app.exec();
}
