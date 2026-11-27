#include "app/AppController.h"
#include "ui/ScenePaintedItem.h"

#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QCommandLineParser>
#include <QQuickStyle>
#include <QQuickWindow>
#include <QCommandLineOption>
#include <QDir>
#include <QEventLoop>
#include <QImage>
#include <QSettings>
#include <QTimer>

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
    const QCommandLineOption screenshotsOption(
        QStringLiteral(u"screenshots"),
        QStringLiteral(u"Render the five screens (present, edit, stage, settings, library) "
                       u"to PNG files in <dir> and exit."),
        QStringLiteral(u"dir"));
    parser.addOption(screenshotsOption);
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

    // -- Output window state persistence ---------------------------------
    // The audience / stage / confidence output windows remember their geometry
    // and maximized flag in QSettings so the operator's window layout survives
    // an app restart. The --screenshots path runs against a throw-away window
    // rect, so persistence wiring is only installed for real launches.
    if (parser.value(screenshotsOption).isEmpty()) {
        QSettings outputWindowStore;
        const auto saveOutputWindowState = [&outputWindowStore](QQuickWindow* w) {
            QVariantMap state;
            state[QStringLiteral(u"x")] = w->x();
            state[QStringLiteral(u"y")] = w->y();
            state[QStringLiteral(u"width")] = w->width();
            state[QStringLiteral(u"height")] = w->height();
            state[QStringLiteral(u"maximized")] = w->windowState() == Qt::WindowMaximized;
            outputWindowStore.setValue(QStringLiteral(u"mxu/windows/") + w->objectName(), state);
        };
        const auto restoreOutputWindowState = [&outputWindowStore](QQuickWindow* w,
                                                                    const QString& key) {
            const QVariantMap state = outputWindowStore.value(key).toMap();
            if (state.isEmpty())
                return;
            const int x = state.value(QStringLiteral(u"x")).toInt();
            const int y = state.value(QStringLiteral(u"y")).toInt();
            const int width = state.value(QStringLiteral(u"width")).toInt();
            const int height = state.value(QStringLiteral(u"height")).toInt();
            if (width > 0 && height > 0)
                w->setGeometry(x, y, width, height);
            if (state.value(QStringLiteral(u"maximized")).toBool())
                w->showMaximized();
        };
        const auto wireOutputWindow = [&saveOutputWindowState, &restoreOutputWindowState](QQuickWindow* w,
                                                                                            const QString& key) {
            QObject::connect(w, &QWindow::visibleChanged, w, [&restoreOutputWindowState, w, key](bool visible) {
                if (visible)
                    restoreOutputWindowState(w, key);
            });
            QObject::connect(w, &QWindow::widthChanged, w, [&saveOutputWindowState, w](int) { saveOutputWindowState(w); });
            QObject::connect(w, &QWindow::heightChanged, w, [&saveOutputWindowState, w](int) { saveOutputWindowState(w); });
            QObject::connect(w, &QWindow::xChanged, w, [&saveOutputWindowState, w](int) { saveOutputWindowState(w); });
            QObject::connect(w, &QWindow::yChanged, w, [&saveOutputWindowState, w](int) { saveOutputWindowState(w); });
            QObject::connect(w, &QWindow::windowStateChanged, w, [&saveOutputWindowState, w](Qt::WindowState) {
                saveOutputWindowState(w);
            });
        };

        const auto* shellWindow = qobject_cast<QQuickWindow*>(engine.rootObjects().first());
        const auto outputWindows = shellWindow ? shellWindow->findChildren<QQuickWindow*>() : QList<QQuickWindow*>();
        for (QQuickWindow* w : outputWindows) {
            const QString name = w->objectName();
            if (name == QStringLiteral(u"presentationOutput")) {
                wireOutputWindow(w, QStringLiteral(u"mxu/windows/presentation"));
            } else if (name == QStringLiteral(u"stageOutput")) {
                wireOutputWindow(w, QStringLiteral(u"mxu/windows/stage"));
            } else if (name == QStringLiteral(u"confidenceMonitor")) {
                wireOutputWindow(w, QStringLiteral(u"mxu/windows/confidence"));
            }
        }
    }

    // `--screenshots <dir>`: render every screen to a PNG so the UI can be
    // compared with the Claude mockup without driving the window by hand.
    const QString shotDir = parser.value(screenshotsOption);
    if (!shotDir.isEmpty()) {
        QDir().mkpath(shotDir);
        auto* window = qobject_cast<QQuickWindow*>(engine.rootObjects().first());
        if (!window)
            return -2;
        window->resize(1280, 840);
        const auto wait = [](int ms) {
            QEventLoop loop;
            QTimer::singleShot(ms, &loop, &QEventLoop::quit);
            loop.exec();
        };
        const QStringList screens{QStringLiteral(u"present"), QStringLiteral(u"edit"),
                                  QStringLiteral(u"stage"), QStringLiteral(u"settings"),
                                  QStringLiteral(u"library")};
        wait(1200);
        int index = 1;
        for (const QString& name : screens) {
            controller.setScreen(name);
            wait(700);
            const QImage image = window->grabWindow();
            const QString file = QDir(shotDir).filePath(
                QStringLiteral("%1-%2.png").arg(index, 2, 10, QLatin1Char('0')).arg(name));
            if (image.isNull() || !image.save(file))
                return -3;
            ++index;
        }
        return 0;
    }

    return app.exec();
}
