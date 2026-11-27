#include "app/AppController.h"
#include "ui/ScenePaintedItem.h"

#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QCommandLineParser>
#include <QQuickStyle>

int main(int argc, char* argv[])
{
    // Custom-styled controls (ComboBox/TextField backgrounds) need a style that
    // supports customization; the native Windows styles do not.
    QQuickStyle::setStyle(QStringLiteral(u"Basic"));

    QGuiApplication app(argc, argv);
    qmlRegisterType<mxu::ui::ScenePaintedItem>("Mxu.Scene", 1, 0, "SceneSurface");
    app.setApplicationName(QStringLiteral(u"MxU Slides"));
    app.setApplicationDisplayName(QStringLiteral(u"ProSlides"));
    app.setOrganizationName(QStringLiteral(u"MxU"));
    app.setOrganizationDomain(QStringLiteral(u"mxu.app"));
    app.setApplicationVersion(QStringLiteral(u"0.1.0"));
    QGuiApplication::setWindowIcon(QIcon(QStringLiteral(u":/resources/icons/appicon.ico")));

    QCommandLineParser parser;
    parser.setApplicationDescription(QStringLiteral(u"ProSlides for Windows"));
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
