#include "SlideActionRouter.h"
#include "AppController.h"

namespace mxu::app {

SlideActionRouter::SlideActionRouter(QObject* parent)
    : QObject(parent)
{
}

bool SlideActionRouter::execute(const QVariantMap& action)
{
    if (!m_controller)
        return false;
    const QString kind = action.value(QStringLiteral(u"kind")).toString();
    if (kind == QStringLiteral(u"clearLayer") || kind == QStringLiteral(u"clearAll")) {
        if (action.value(QStringLiteral(u"layer")).toString().isEmpty())
            QMetaObject::invokeMethod(m_controller->showState(), "clearAll", Qt::QueuedConnection);
        else
            QMetaObject::invokeMethod(m_controller->showState(), "clearLayer", Qt::QueuedConnection,
                                      Q_ARG(QString, action.value(QStringLiteral(u"layer")).toString()));
    } else if (kind == QStringLiteral(u"restore")) {
        QMetaObject::invokeMethod(m_controller->showState(), "restoreAll", Qt::QueuedConnection);
    } else if (kind == QStringLiteral(u"fireAlert")) {
        QMetaObject::invokeMethod(m_controller->alerts(), "fire", Qt::QueuedConnection,
                                  Q_ARG(QString, action.value(QStringLiteral(u"alertId")).toString()),
                                  Q_ARG(QString, QStringLiteral(u"both")),
                                  Q_ARG(QString, QStringLiteral(u"persist")));
    } else if (kind == QStringLiteral(u"dismissAlert")) {
        QMetaObject::invokeMethod(m_controller->alerts(), "dismiss", Qt::QueuedConnection);
    } else if (kind == QStringLiteral(u"timerStart")) {
        QMetaObject::invokeMethod(m_controller->timerBoard(), "start", Qt::QueuedConnection,
                                  Q_ARG(QString, action.value(QStringLiteral(u"timerId")).toString()));
    } else if (kind == QStringLiteral(u"timerPause")) {
        QMetaObject::invokeMethod(m_controller->timerBoard(), "pause", Qt::QueuedConnection,
                                  Q_ARG(QString, action.value(QStringLiteral(u"timerId")).toString()));
    } else if (kind == QStringLiteral(u"fireMedia")) {
        QMetaObject::invokeMethod(m_controller->mediaService(), "addToServiceFlow", Qt::QueuedConnection,
                                  Q_ARG(int, action.value(QStringLiteral(u"mediaId")).toInt()));
    } else if (kind == QStringLiteral(u"switchOutputPreset")) {
        QMetaObject::invokeMethod(m_controller->outputPresets(), "apply", Qt::QueuedConnection,
                                  Q_ARG(QString, action.value(QStringLiteral(u"presetId")).toString()));
    } else if (kind == QStringLiteral(u"advance")) {
        QMetaObject::invokeMethod(m_controller, "next", Qt::QueuedConnection);
    } else if (kind == QStringLiteral(u"combo")) {
        QMetaObject::invokeMethod(m_controller->automation(), "fire", Qt::QueuedConnection,
                                  Q_ARG(QString, action.value(QStringLiteral(u"comboId")).toString()));
    } else {
        emit notification(QStringLiteral(u"Unknown slide action: %1").arg(kind));
        return false;
    }
    emit notification(QStringLiteral(u"Slide action: %1").arg(kind));
    return true;
}

} // namespace mxu::app
