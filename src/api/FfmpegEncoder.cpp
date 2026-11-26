#include "FfmpegEncoder.h"

#ifdef MXU_HAS_FFMPEG
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}
#endif

namespace mxu::api {

namespace {
#ifdef MXU_HAS_FFMPEG
struct FfmpegContext
{
    AVFormatContext* format = nullptr;
    AVCodecContext* codec = nullptr;
    AVStream* stream = nullptr;
    AVFrame* frame = nullptr;
    SwsContext* sws = nullptr;
    int width = 1920;
    int height = 1080;
    int fps = 30;
    qint64 pts = 0;
};
#endif
}

FfmpegEncoder::FfmpegEncoder(QObject* parent)
    : QObject(parent)
{
}

FfmpegEncoder::~FfmpegEncoder()
{
    stop();
}

bool FfmpegEncoder::available() const
{
#ifdef MXU_HAS_FFMPEG
    return true;
#else
    return false;
#endif
}

bool FfmpegEncoder::start(const QString& url, int width, int height, int fps)
{
#ifdef MXU_HAS_FFMPEG
    if (m_active || url.isEmpty())
        return false;
    auto* context = new FfmpegContext();
    context->width = width;
    context->height = height;
    context->fps = fps;

    const QByteArray target = url.toUtf8();
    if (avformat_alloc_output_context2(&context->format, nullptr, nullptr,
                                       target.constData()) < 0 || !context->format) {
        emit errorOccurred(QStringLiteral(u"Cannot allocate output context"));
        delete context;
        return false;
    }
    const AVCodec* codec = avcodec_find_encoder(AV_CODEC_ID_H264);
    if (!codec) {
        emit errorOccurred(QStringLiteral(u"H.264 encoder not available"));
        avformat_free_context(context->format);
        delete context;
        return false;
    }
    context->stream = avformat_new_stream(context->format, nullptr);
    context->codec = avcodec_alloc_context3(codec);
    context->codec->width = width;
    context->codec->height = height;
    context->codec->time_base = AVRational{ 1, fps };
    context->codec->framerate = AVRational{ fps, 1 };
    context->codec->pix_fmt = AV_PIX_FMT_YUV420P;
    context->codec->bit_rate = 6000000;
    if (context->format->oformat->flags & AVFMT_GLOBALHEADER)
        context->codec->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
    if (avcodec_open2(context->codec, codec, nullptr) < 0) {
        emit errorOccurred(QStringLiteral(u"Cannot open encoder"));
        avcodec_free_context(&context->codec);
        avformat_free_context(context->format);
        delete context;
        return false;
    }
    avcodec_parameters_from_context(context->stream->codecpar, context->codec);
    if (!(context->format->oformat->flags & AVFMT_NOFILE)
        && avio_open(&context->format->pb, target.constData(), AVIO_FLAG_WRITE) < 0) {
        emit errorOccurred(QStringLiteral(u"Cannot open output URL"));
        avcodec_free_context(&context->codec);
        avformat_free_context(context->format);
        delete context;
        return false;
    }
    if (avformat_write_header(context->format, nullptr) < 0) {
        emit errorOccurred(QStringLiteral(u"Cannot write header"));
        avio_closep(&context->format->pb);
        avcodec_free_context(&context->codec);
        avformat_free_context(context->format);
        delete context;
        return false;
    }
    context->frame = av_frame_alloc();
    context->frame->format = AV_PIX_FMT_YUV420P;
    context->frame->width = width;
    context->frame->height = height;
    av_frame_get_buffer(context->frame, 32);
    context->sws = sws_getContext(width, height, AV_PIX_FMT_BGRA, width, height,
                                  AV_PIX_FMT_YUV420P, SWS_BILINEAR, nullptr, nullptr, nullptr);
    m_context = context;
    m_active = true;
    m_status = url;
    emit changed();
    return true;
#else
    Q_UNUSED(url) Q_UNUSED(width) Q_UNUSED(height) Q_UNUSED(fps)
    emit errorOccurred(QStringLiteral(u"Build with MXU_ENABLE_FFMPEG"));
    return false;
#endif
}

void FfmpegEncoder::stop()
{
#ifdef MXU_HAS_FFMPEG
    if (!m_context)
        return;
    auto* context = static_cast<FfmpegContext*>(m_context);
    AVPacket* packet = av_packet_alloc();
    avcodec_send_frame(context->codec, nullptr);
    while (avcodec_receive_packet(context->codec, packet) == 0) {
        av_packet_rescale_ts(packet, context->codec->time_base, context->stream->time_base);
        av_interleaved_write_frame(context->format, packet);
        av_packet_unref(packet);
    }
    av_packet_free(&packet);
    av_write_trailer(context->format);
    sws_freeContext(context->sws);
    av_frame_free(&context->frame);
    if (!(context->format->oformat->flags & AVFMT_NOFILE))
        avio_closep(&context->format->pb);
    avcodec_free_context(&context->codec);
    avformat_free_context(context->format);
    delete context;
    m_context = nullptr;
#endif
    if (m_active) {
        m_active = false;
        m_status = QStringLiteral(u"Idle");
        emit changed();
    }
}

bool FfmpegEncoder::sendFrame(const QImage& input)
{
#ifdef MXU_HAS_FFMPEG
    if (!m_context || input.isNull())
        return false;
    auto* context = static_cast<FfmpegContext*>(m_context);
    const QImage frame = input.convertToFormat(QImage::Format_ARGB32);
    const uint8_t* src[4] = { reinterpret_cast<const uint8_t*>(frame.constBits()), nullptr, nullptr, nullptr };
    int srcStride[4] = { frame.bytesPerLine(), 0, 0, 0 };
    sws_scale(context->sws, src, srcStride, 0, frame.height(),
              context->frame->data, context->frame->linesize);
    context->frame->pts = context->pts++;
    if (avcodec_send_frame(context->codec, context->frame) < 0)
        return false;
    AVPacket* packet = av_packet_alloc();
    bool ok = true;
    while (avcodec_receive_packet(context->codec, packet) == 0) {
        av_packet_rescale_ts(packet, context->codec->time_base, context->stream->time_base);
        if (av_interleaved_write_frame(context->format, packet) < 0)
            ok = false;
        av_packet_unref(packet);
    }
    av_packet_free(&packet);
    return ok;
#else
    Q_UNUSED(input)
    return false;
#endif
}

} // namespace mxu::api
