#include "NdiDynamicSender.h"

#include <QDir>
#include <QStandardPaths>

namespace mxu::api {

namespace {
struct SendCreate
{
    const char* name;
    const char* groups;
    bool clockVideo;
    bool clockAudio;
};

struct VideoFrameV2
{
    int xres;
    int yres;
    int fourCC;
    unsigned char* data;
    int lineStride;
    double frameRateN;
    double frameRateD;
    int pictureAspectRatio;
    int frameFormatType;
    long long timecode;
    const char* metadata;
    long long timestamp;
};
}

NdiDynamicSender::NdiDynamicSender(QObject* parent)
    : QObject(parent)
{
    resolve();
}

NdiDynamicSender::~NdiDynamicSender()
{
    stop();
}

QString NdiDynamicSender::libraryPath() const
{
#ifdef Q_OS_WIN
    const QStringList candidates = {
        QStringLiteral(u"Processing.NDI.Lib.x64.dll"),
        QStringLiteral(u"C:/Program Files/NDI/NDI 5 SDK/Lib/x64/Processing.NDI.Lib.x64.dll"),
    };
#else
    const QStringList candidates = {
        QStringLiteral(u"libndi.so.5"),
        QStringLiteral(u"libndi.so"),
    };
#endif
    for (const QString& candidate : candidates) {
        QLibrary probe(candidate);
        if (probe.load())
            return candidate;
    }
    return {};
}

bool NdiDynamicSender::resolve()
{
    if (m_resolved)
        return true;
    const QString path = libraryPath();
    if (path.isEmpty())
        return false;
    m_library.setFileName(path);
    if (!m_library.load())
        return false;
    m_create = m_library.resolve("NDIlib_send_create");
    m_destroy = m_library.resolve("NDIlib_send_destroy");
    m_sendVideo = m_library.resolve("NDIlib_send_send_video_v2");
    m_resolved = m_create && m_destroy && m_sendVideo;
    if (!m_resolved)
        emit errorOccurred(QStringLiteral(u"NDI runtime missing required symbols"));
    return m_resolved;
}

bool NdiDynamicSender::available() const
{
    return const_cast<NdiDynamicSender*>(this)->resolve();
}

bool NdiDynamicSender::start(const QString& name)
{
    if (!resolve() || m_active)
        return false;
    using CreateFn = void* (*)(const SendCreate*);
    auto create = reinterpret_cast<CreateFn>(m_create);
    const QByteArray bytes = name.toUtf8();
    SendCreate config{ bytes.constData(), nullptr, true, false };
    m_instance = create(&config);
    if (!m_instance) {
        emit errorOccurred(QStringLiteral(u"NDIlib_send_create failed"));
        return false;
    }
    m_active = true;
    emit changed();
    return true;
}

void NdiDynamicSender::stop()
{
    if (!m_instance || !m_destroy)
        return;
    using DestroyFn = void (*)(void*);
    reinterpret_cast<DestroyFn>(m_destroy)(m_instance);
    m_instance = nullptr;
    m_active = false;
    emit changed();
}

bool NdiDynamicSender::sendFrame(const QImage& input)
{
    if (!m_active || !m_sendVideo || input.isNull())
        return false;
    const QImage frame = input.convertToFormat(QImage::Format_ARGB32);
    QByteArray bytes(reinterpret_cast<const char*>(frame.constBits()),
                     static_cast<qsizetype>(frame.sizeInBytes()));
    VideoFrameV2 video{
        frame.width(), frame.height(), 0,
        reinterpret_cast<unsigned char*>(bytes.data()),
        static_cast<int>(frame.bytesPerLine()),
        30.0, 1.0, 0, 0, 0, nullptr, 0,
    };
    using SendFn = void (*)(void*, const VideoFrameV2*);
    reinterpret_cast<SendFn>(m_sendVideo)(m_instance, &video);
    return true;
}

} // namespace mxu::api
