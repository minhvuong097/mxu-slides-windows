#include "DspEngine.h"

#include <QtMath>

namespace mxu::audio {

double DspMixer::gainFor(int index, double crossfade) const
{
    if (index < 0 || index >= m_channels.size())
        return 0.0;
    bool anySolo = false;
    for (const auto& channel : m_channels)
        anySolo = anySolo || channel.solo;
    const auto& channel = m_channels.at(index);
    if (!channel.playing || channel.muted || (anySolo && !channel.solo))
        return 0.0;

    double gain = channel.gain;
    if (m_channels.size() >= 2) {
        if (index == 0)
            gain *= FadeCurveEvaluator::gain(FadeCurve::EqualPower, crossfade);
        else if (index == 1)
            gain *= 1.0 - FadeCurveEvaluator::gain(FadeCurve::EqualPower, crossfade);
    }
    return gain;
}

double DspMixer::mixSample(const QVector<double>& samples, double crossfade) const
{
    double result = 0.0;
    for (qsizetype i = 0; i < m_channels.size() && i < samples.size(); ++i)
        result += samples.at(i) * gainFor(static_cast<int>(i), crossfade);
    return result;
}

void DspMixer::advanceFrames(quint64 frames)
{
    for (auto& channel : m_channels) {
        if (channel.playing)
            channel.positionFrames += frames;
    }
}

} // namespace mxu::audio
