#pragma once

#include <QImage>
#include <QLibrary>
#include <QObject>
#include <QString>

namespace mxu::api {

// Runtime-loaded NDI sender. Resolves the official NDIlib C API at runtime so
// the project builds without the SDK; install the NDI runtime to enable it.
class NdiDynamicSender : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool available READ available NOTIFY changed)
    Q_PROPERTY(bool active READ active NOTIFY changed)
    Q_PROPERTY(QString libraryPath READ libraryPath CONSTANT)

public:
    explicit NdiDynamicSender(QObject* parent = nullptr);
    ~NdiDynamicSender() override;

    bool available() const;
    bool active() const { return m_active; }
    QString libraryPath() const;

public slots:
    bool start(const QString& name);
    void stop();
    bool sendFrame(const QImage& frame);

signals:
    void changed();
    void errorOccurred(const QString& message);

private:
    bool resolve();
    void* m_instance = nullptr;
    QLibrary m_library;
    QFunctionPointer m_create = nullptr;
    QFunctionPointer m_destroy = nullptr;
    QFunctionPointer m_sendVideo = nullptr;
    bool m_resolved = false;
    bool m_active = false;
};

} // namespace mxu::api
