#pragma once

#include <QObject>
#include <QVector>
#include <atomic>
#include <cstddef>
#include <optional>

namespace mxu::audio {

enum class FadeCurve { Linear, EqualPower, SCurve };

// Lock-free single-producer/single-consumer ring buffer for float samples.
template <typename T>
class RingBuffer
{
public:
    explicit RingBuffer(std::size_t capacity)
        : m_data(capacity), m_read(0), m_write(0)
    {
    }

    std::size_t capacity() const { return m_data.size(); }

    bool push(const T& value)
    {
        const std::size_t write = m_write.load(std::memory_order_relaxed);
        const std::size_t next = (write + 1) % m_data.size();
        if (next == m_read.load(std::memory_order_acquire))
            return false;
        m_data[write] = value;
        m_write.store(next, std::memory_order_release);
        return true;
    }

    bool pop(T& value)
    {
        const std::size_t read = m_read.load(std::memory_order_relaxed);
        if (read == m_write.load(std::memory_order_acquire))
            return false;
        value = m_data[read];
        m_read.store((read + 1) % m_data.size(), std::memory_order_release);
        return true;
    }

    std::size_t available() const
    {
        const std::size_t write = m_write.load(std::memory_order_acquire);
        const std::size_t read = m_read.load(std::memory_order_acquire);
        return write >= read ? write - read : m_data.size() - read + write;
    }

private:
    QVector<T> m_data;
    std::atomic<std::size_t> m_read;
    std::atomic<std::size_t> m_write;
};

// Fade gain evaluation, sample accurate.
class FadeCurveEvaluator
{
public:
    static double gain(FadeCurve curve, double progress)
    {
        progress = progress < 0 ? 0 : (progress > 1 ? 1 : progress);
        switch (curve) {
        case FadeCurve::EqualPower:
            return 0.5 * (1.0 + qCos(3.141592653589793 * progress));
        case FadeCurve::SCurve:
            return progress * progress * (3.0 - 2.0 * progress);
        case FadeCurve::Linear:
        default:
            return 1.0 - progress;
        }
    }
};

// RMS/peak meter with attack/release ballistics.
class AudioMeter
{
public:
    void feed(double sample, double attack = 0.6, double release = 0.12)
    {
        const double magnitude = qAbs(sample);
        m_peak = magnitude > m_peak ? magnitude * attack + m_peak * (1.0 - attack)
                                    : magnitude * release + m_peak * (1.0 - release);
        m_sum += sample * sample;
        ++m_count;
    }

    double peak() const { return m_peak; }
    double rms() const { return m_count ? qSqrt(m_sum / m_count) : 0.0; }
    void reset() { m_peak = 0.0; m_sum = 0.0; m_count = 0; }

private:
    double m_peak = 0.0;
    double m_sum = 0.0;
    std::size_t m_count = 0;
};

struct DeckState
{
    QString id;
    double gain = 1.0;
    bool playing = false;
    bool muted = false;
    bool solo = false;
    quint64 positionFrames = 0;
};

// Mixer with mute/solo routing and equal-power crossfade between two decks.
class DspMixer
{
public:
    void setChannels(const QVector<DeckState>& channels) { m_channels = channels; }
    QVector<DeckState> channels() const { return m_channels; }

    double gainFor(int index, double crossfade = 0.0) const;
    double mixSample(const QVector<double>& samples, double crossfade = 0.0) const;
    void advanceFrames(quint64 frames);

private:
    QVector<DeckState> m_channels;
};

// Sample-accurate clock for scheduled starts, based on an external frame time.
class AudioClock
{
public:
    void setSampleRate(int rate) { m_rate = rate > 0 ? rate : 48000; }
    int sampleRate() const { return m_rate; }
    quint64 framesForMs(qint64 ms) const { return static_cast<quint64>(ms) * m_rate / 1000; }
    qint64 msForFrames(quint64 frames) const { return static_cast<qint64>(frames) * 1000 / m_rate; }

private:
    int m_rate = 48000;
};

} // namespace mxu::audio
