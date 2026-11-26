#include "StreamingService.h"

namespace mxu::api {

StreamingService::StreamingService(QObject* parent)
    : QObject(parent)
{
}

bool StreamingService::available() const
{
#ifdef MXU_HAS_FFMPEG
    return true;
#else
    return false;
#endif
}

bool StreamingService::start(const QString& url, const QString& transport)
{
    if (!available() || url.isEmpty()) {
        m_status = QStringLiteral(u"Streaming backend unavailable (build with MXU_ENABLE_FFMPEG)");
        emit changed();
        emit notification(m_status);
        return false;
    }
    m_streaming = true;
    m_status = QStringLiteral(u"%1 → %2").arg(transport, url);
    emit changed();
    return true;
}

void StreamingService::stop()
{
    if (!m_streaming)
        return;
    m_streaming = false;
    m_status = QStringLiteral(u"Idle");
    emit changed();
}

bool StreamingService::startRecording(const QString& path)
{
    if (!available() || path.isEmpty()) {
        m_status = QStringLiteral(u"Recorder unavailable (build with MXU_ENABLE_FFMPEG)");
        emit changed();
        emit notification(m_status);
        return false;
    }
    m_recording = true;
    m_status = QStringLiteral(u"Recording to %1").arg(path);
    emit changed();
    return true;
}

void StreamingService::stopRecording()
{
    if (!m_recording)
        return;
    m_recording = false;
    m_status = QStringLiteral(u"Idle");
    emit changed();
}

} // namespace mxu::api
