#pragma once

#include <QObject>
#include <QVector>
#include <functional>

namespace mxu::audio {

// Event-driven WASAPI render engine with a low-latency callback. On Windows
// it uses IAudioClient/IAudioRenderClient in shared mode with a event handle;
// other hosts get an inert stub so the project still builds cross-platform.
class WasapiRenderEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool available READ available CONSTANT)
    Q_PROPERTY(bool active READ active NOTIFY changed)
    Q_PROPERTY(int sampleRate READ sampleRate NOTIFY changed)
    Q_PROPERTY(int bufferFrames READ bufferFrames NOTIFY changed)
    Q_PROPERTY(double cpuLoad READ cpuLoad NOTIFY changed)

public:
    using FrameCallback = std::function<QVector<float>(int frames)>;

    explicit WasapiRenderEngine(QObject* parent = nullptr);
    ~WasapiRenderEngine() override;

    bool available() const;
    bool active() const { return m_active; }
    int sampleRate() const { return m_sampleRate; }
    int bufferFrames() const { return m_bufferFrames; }
    double cpuLoad() const { return m_cpuLoad; }

    void setFrameCallback(FrameCallback callback) { m_callback = std::move(callback); }
    Q_INVOKABLE QVector<float> renderFrames(int frames);

public slots:
    bool start();
    void stop();

signals:
    void changed();
    void errorOccurred(const QString& message);

private:
    void* m_context = nullptr;
    FrameCallback m_callback;
    bool m_active = false;
    int m_sampleRate = 48000;
    int m_bufferFrames = 480;
    double m_cpuLoad = 0.0;
};

} // namespace mxu::audio
