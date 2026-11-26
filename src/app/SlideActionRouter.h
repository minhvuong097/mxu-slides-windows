#pragma once

#include <QObject>
#include <QVariantList>
#include <QVariantMap>

namespace mxu::app {

class AppController;

// Executes SlideAction values attached to a slide (clearLayer, fireAlert,
// timerStart, fireMedia, switchOutputPreset, ...).
class SlideActionRouter : public QObject
{
    Q_OBJECT

public:
    explicit SlideActionRouter(QObject* parent = nullptr);
    void attach(AppController* controller) { m_controller = controller; }

    Q_INVOKABLE bool execute(const QVariantMap& action);

signals:
    void notification(const QString& message);

private:
    AppController* m_controller = nullptr;
};

} // namespace mxu::app
