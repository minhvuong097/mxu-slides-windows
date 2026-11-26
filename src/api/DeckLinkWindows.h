#pragma once

#include <QImage>
#include <QObject>
#include <QVariantList>
#include <QString>
#include <QVector>

namespace mxu::api {

// Blackmagic DeckLink output using the vendored cross-platform SDK headers.
// Real implementation is compiled only on Windows; other hosts get a stub.
class DeckLinkWindows : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool available READ available CONSTANT)
    Q_PROPERTY(bool active READ active NOTIFY changed)
    Q_PROPERTY(QVariantList devices READ devices NOTIFY changed)

public:
    explicit DeckLinkWindows(QObject* parent = nullptr);
    ~DeckLinkWindows() override;

    bool available() const;
    bool active() const { return m_active; }
    QVariantList devices() const { return m_devices; }

public slots:
    void refresh();
    bool start(int index = 0);
    void stop();
    bool sendFrame(const QImage& frame);

signals:
    void changed();
    void errorOccurred(const QString& message);

private:
    QVariantList m_devices;
    bool m_active = false;
    void* m_output = nullptr;
    void* m_frame = nullptr;
};

} // namespace mxu::api
