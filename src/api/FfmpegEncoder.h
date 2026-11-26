#pragma once

#include <QImage>
#include <QObject>
#include <QString>

namespace mxu::api {

// H.264 encoder + muxer (file/RTMP/HLS via FFmpeg URL). Compiles as a stub
// unless MXU_ENABLE_FFMPEG is set and FFmpeg is found by CMake.
class FfmpegEncoder : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool available READ available CONSTANT)
    Q_PROPERTY(bool active READ active NOTIFY changed)
    Q_PROPERTY(QString status READ status NOTIFY changed)

public:
    explicit FfmpegEncoder(QObject* parent = nullptr);
    ~FfmpegEncoder() override;

    bool available() const;
    bool active() const { return m_active; }
    QString status() const { return m_status; }

public slots:
    bool start(const QString& url, int width = 1920, int height = 1080, int fps = 30);
    void stop();
    bool sendFrame(const QImage& frame);

signals:
    void changed();
    void errorOccurred(const QString& message);

private:
    bool m_active = false;
    QString m_status = QStringLiteral(u"Idle");
    void* m_context = nullptr;
};

} // namespace mxu::api
