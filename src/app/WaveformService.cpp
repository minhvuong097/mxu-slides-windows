#include "WaveformService.h"

#include <QAudioBuffer>
#include <QAudioDecoder>
#include <QAudioFormat>
#include <QEventLoop>
#include <QFileInfo>
#include <QUrl>

namespace mxu::app {

WaveformService::WaveformService(QObject* parent)
    : QObject(parent)
{
}

bool WaveformService::decode(const QString& path)
{
    const QFileInfo info(path);
    if (!info.exists()) {
        m_status = QStringLiteral(u"File not found");
        emit changed();
        return false;
    }

    QAudioDecoder decoder;
    decoder.setSource(QUrl::fromLocalFile(path));
    QEventLoop loop;
    bool failed = false;
    QObject::connect(&decoder, QOverload<QAudioDecoder::Error>::of(&QAudioDecoder::error), &loop, [&](QAudioDecoder::Error) {
        failed = true;
        loop.quit();
    });
    QObject::connect(&decoder, &QAudioDecoder::finished, &loop, &QEventLoop::quit);
    decoder.start();
    loop.exec();
    if (failed) {
        m_status = decoder.errorString().isEmpty() ? QStringLiteral(u"Decode failed") : decoder.errorString();
        emit changed();
        return false;
    }

    QList<QAudioBuffer> buffers;
    while (true) {
        const QAudioBuffer buffer = decoder.read();
        if (!buffer.isValid())
            break;
        buffers.append(buffer);
    }
    if (buffers.isEmpty()) {
        m_status = QStringLiteral(u"No audio stream");
        emit changed();
        return false;
    }

    qint64 frames = 0;
    for (const QAudioBuffer& buffer : buffers)
        frames += buffer.frameCount();
    if (frames <= 0) {
        m_status = QStringLiteral(u"Empty audio stream");
        emit changed();
        return false;
    }

    const int buckets = qBound(16, static_cast<int>(frames / 2000), 128);
    QVector<double> sums(buckets, 0.0);
    QVector<int> counts(buckets, 0);

    qint64 globalFrame = 0;
    for (const QAudioBuffer& buffer : buffers) {
        const QAudioFormat format = buffer.format();
        const int channels = qMax(1, format.channelCount());
        if (format.sampleFormat() == QAudioFormat::Int16) {
            const qint16* data = buffer.constData<qint16>();
            for (qint64 frame = 0; frame < buffer.frameCount(); ++frame) {
                double sample = 0;
                for (int channel = 0; channel < channels; ++channel)
                    sample += qAbs(static_cast<double>(data[frame * channels + channel])) / 32768.0;
                const int bucket = qMin(buckets - 1, static_cast<int>((globalFrame + frame) * buckets / qMax<qint64>(1, frames)));
                sums[bucket] += sample / channels;
                counts[bucket] += 1;
            }
        } else if (format.sampleFormat() == QAudioFormat::Float) {
            const float* data = buffer.constData<float>();
            for (qint64 frame = 0; frame < buffer.frameCount(); ++frame) {
                double sample = 0;
                for (int channel = 0; channel < channels; ++channel)
                    sample += qAbs(static_cast<double>(data[frame * channels + channel]));
                const int bucket = qMin(buckets - 1, static_cast<int>((globalFrame + frame) * buckets / qMax<qint64>(1, frames)));
                sums[bucket] += sample / channels;
                counts[bucket] += 1;
            }
        } else {
            m_status = QStringLiteral(u"Unsupported sample format");
            emit changed();
            return false;
        }
        globalFrame += buffer.frameCount();
    }

    m_peaks.clear();
    for (int i = 0; i < buckets; ++i) {
        const double rms = counts[i] > 0 ? sums[i] / counts[i] : 0.0;
        m_peaks.append(qBound(0.05, rms * 3.0, 1.0));
    }
    const qint64 decoderDuration = decoder.duration();
    m_durationMs = decoderDuration > 0
                   ? decoderDuration
                   : static_cast<qint64>(frames * 1000 / qMax(1, buffers.first().format().sampleRate()));
    m_status = QStringLiteral(u"Decoded %1 peaks").arg(buckets);
    emit changed();
    return true;
}

} // namespace mxu::app
