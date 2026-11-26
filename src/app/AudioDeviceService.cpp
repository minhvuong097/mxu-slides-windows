#include "AudioDeviceService.h"

#include <QMediaDevices>
#include <QAudioDevice>

namespace mxu::app {

AudioDeviceService::AudioDeviceService(QObject* parent)
    : QObject(parent)
{
    refresh();
}

void AudioDeviceService::refresh()
{
    m_inputs.clear();
    m_outputs.clear();
    const auto inputs = QMediaDevices::audioInputs();
    for (qsizetype i = 0; i < inputs.size(); ++i) {
        m_inputs.append(QVariantMap{
            { QStringLiteral(u"index"), static_cast<int>(i) },
            { QStringLiteral(u"name"), inputs.at(i).description() },
            { QStringLiteral(u"id"), inputs.at(i).id() },
        });
    }
    const auto outputs = QMediaDevices::audioOutputs();
    for (qsizetype i = 0; i < outputs.size(); ++i) {
        m_outputs.append(QVariantMap{
            { QStringLiteral(u"index"), static_cast<int>(i) },
            { QStringLiteral(u"name"), outputs.at(i).description() },
            { QStringLiteral(u"id"), outputs.at(i).id() },
        });
    }
    emit changed();
}

} // namespace mxu::app
