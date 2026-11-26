#include "WavRecorder.h"

#include <QFile>
#include <QDataStream>

namespace mxu::audio {

WavRecorder::WavRecorder(QObject* parent)
    : QObject(parent)
{
}

WavRecorder::~WavRecorder()
{
    finish();
}

bool WavRecorder::start(const QString& path, int sampleRate, int channels, int bits)
{
    if (path.isEmpty() || sampleRate <= 0 || channels <= 0 || (bits != 16 && bits != 24 && bits != 32))
        return false;
    finish();
    m_path = path;
    m_rate = sampleRate;
    m_channels = channels;
    m_bits = bits;
    m_frames = 0;
    m_data.clear();
    m_recording = true;
    emit changed();
    return true;
}

void WavRecorder::write(const QVector<float>& samples)
{
    if (!m_recording)
        return;
    for (float sample : samples) {
        const double clamped = qBound(-1.0, static_cast<double>(sample), 1.0);
        if (m_bits == 16) {
            const qint16 value = static_cast<qint16>(clamped * 32767.0);
            m_data.append(reinterpret_cast<const char*>(&value), sizeof(value));
        } else if (m_bits == 24) {
            const qint32 value = static_cast<qint32>(clamped * 8388607.0);
            const char bytes[3] = {
                static_cast<char>(value & 0xFF),
                static_cast<char>((value >> 8) & 0xFF),
                static_cast<char>((value >> 16) & 0xFF),
            };
            m_data.append(bytes, 3);
        } else {
            const float value = static_cast<float>(clamped);
            m_data.append(reinterpret_cast<const char*>(&value), sizeof(value));
        }
    }
    m_frames += static_cast<quint64>(samples.size()) / m_channels;
    emit changed();
}

void WavRecorder::writeHeader()
{
    if (m_path.isEmpty())
        return;
    QFile file(m_path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        emit errorOccurred(file.errorString());
        return;
    }
    const int blockAlign = m_channels * (m_bits / 8);
    const quint32 byteRate = static_cast<quint32>(m_rate) * blockAlign;
    const quint32 dataSize = static_cast<quint32>(m_data.size());
    QDataStream out(&file);
    out.setByteOrder(QDataStream::LittleEndian);
    out.writeRawData("RIFF", 4);
    out << quint32(36 + dataSize);
    out.writeRawData("WAVE", 4);
    out.writeRawData("fmt ", 4);
    out << quint32(16);
    out << quint16(1);
    out << quint16(m_channels);
    out << quint32(m_rate);
    out << byteRate;
    out << quint16(blockAlign);
    out << quint16(m_bits);
    out.writeRawData("data", 4);
    out << dataSize;
    out.writeRawData(m_data.constData(), static_cast<qint64>(m_data.size()));
    file.close();
}

void WavRecorder::finish()
{
    if (!m_recording)
        return;
    m_recording = false;
    writeHeader();
    m_data.clear();
    emit changed();
}

} // namespace mxu::audio
