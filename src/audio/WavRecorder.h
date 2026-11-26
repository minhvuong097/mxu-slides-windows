#pragma once

#include <QObject>
#include <QString>
#include <QVector>
#include <QByteArray>

namespace mxu::audio {

// Minimal PCM WAV writer fed by the DSP mixer / WASAPI callback. Provides
// local recording without FFmpeg or Media Foundation dependencies.
class WavRecorder : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool recording READ recording NOTIFY changed)
    Q_PROPERTY(QString path READ path NOTIFY changed)
    Q_PROPERTY(quint64 frames READ frames NOTIFY changed)

public:
    explicit WavRecorder(QObject* parent = nullptr);
    ~WavRecorder() override;

    bool recording() const { return m_recording; }
    QString path() const { return m_path; }
    quint64 frames() const { return m_frames; }

public slots:
    bool start(const QString& path, int sampleRate = 48000, int channels = 2, int bits = 16);
    void write(const QVector<float>& samples);
    void finish();

signals:
    void changed();
    void errorOccurred(const QString& message);

private:
    void writeHeader();

    QString m_path;
    bool m_recording = false;
    int m_rate = 48000;
    int m_channels = 2;
    int m_bits = 16;
    quint64 m_frames = 0;
    QByteArray m_data;
};

} // namespace mxu::audio
