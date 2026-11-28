#pragma once

#include <QObject>
#include <QString>
#include <QVariantList>

namespace mxu::app {

// Decodes a local media file with Qt's audio backend and produces real RMS
// waveform peaks (Windows counterpart of the Mac MediaEngine waveform pass).
class WaveformService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList peaks READ peaks NOTIFY changed)
    Q_PROPERTY(qint64 durationMs READ durationMs NOTIFY changed)
    Q_PROPERTY(QString status READ status NOTIFY changed)

public:
    explicit WaveformService(QObject* parent = nullptr);

    QVariantList peaks() const { return m_peaks; }
    qint64 durationMs() const { return m_durationMs; }
    QString status() const { return m_status; }

public slots:
    bool decode(const QString& path);

signals:
    void changed();

private:
    QVariantList m_peaks;
    qint64 m_durationMs = 0;
    QString m_status = QStringLiteral(u"Ready");
};

} // namespace mxu::app
