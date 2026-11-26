#pragma once

#include <QObject>
#include <QString>

namespace mxu::api {

// RTMP/HLS/SRT + recorder surface. The actual encoders require FFmpeg/Media
// Foundation; when unavailable the service reports the reason instead of
// silently pretending to stream. Build with MXU_ENABLE_FFMPEG to wire them.
class StreamingService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool available READ available CONSTANT)
    Q_PROPERTY(bool streaming READ streaming NOTIFY changed)
    Q_PROPERTY(bool recording READ recording NOTIFY changed)
    Q_PROPERTY(QString status READ status NOTIFY changed)

public:
    explicit StreamingService(QObject* parent = nullptr);

    bool available() const;
    bool streaming() const { return m_streaming; }
    bool recording() const { return m_recording; }
    QString status() const { return m_status; }

public slots:
    bool start(const QString& url, const QString& transport = QStringLiteral(u"rtmp"));
    void stop();
    bool startRecording(const QString& path);
    void stopRecording();

signals:
    void changed();
    void notification(const QString& message);

private:
    bool m_streaming = false;
    bool m_recording = false;
    QString m_status = QStringLiteral(u"Idle");
};

} // namespace mxu::api
