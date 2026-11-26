#pragma once

#include <QObject>
#include <QString>

namespace mxu::api {

// Thin backend stubs. The Windows SDKs are optional at build time; when the
// SDK macros are absent these classes report unavailable and no-op. Replace
// the bodies with NDIlib_send_create / IDeckLinkOutput when the SDK is present.
class NdiSender : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool available READ available CONSTANT)
    Q_PROPERTY(bool active READ active NOTIFY changed)

public:
    explicit NdiSender(QObject* parent = nullptr);
    bool available() const;
    bool active() const { return m_active; }

public slots:
    bool start(const QString& name);
    void stop();

signals:
    void changed();

private:
    bool m_active = false;
};

class DeckLinkOutput : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool available READ available CONSTANT)
    Q_PROPERTY(bool active READ active NOTIFY changed)

public:
    explicit DeckLinkOutput(QObject* parent = nullptr);
    bool available() const;
    bool active() const { return m_active; }

public slots:
    bool start(int deviceIndex);
    void stop();

signals:
    void changed();

private:
    bool m_active = false;
};

} // namespace mxu::api
