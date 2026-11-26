#pragma once

#include <QObject>
#include <QString>

namespace mxu::app {

// MTC quarter-frame + LTC-style timecode decoder. Takes 4-bit nibbles from
// MIDI quarter-frame messages and produces hh:mm:ss:ff output.
class TimecodeService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString timecode READ timecode NOTIFY changed)
    Q_PROPERTY(bool locked READ locked NOTIFY changed)
    Q_PROPERTY(double framesPerSecond READ framesPerSecond WRITE setFramesPerSecond NOTIFY changed)

public:
    explicit TimecodeService(QObject* parent = nullptr);

    QString timecode() const;
    bool locked() const { return m_locked; }
    double framesPerSecond() const { return m_fps; }
    void setFramesPerSecond(double value);

public slots:
    void quarterFrame(int value);
    void setManual(const QString& timecode);
    void reset();

signals:
    void changed();
    void fullFrame(const QString& timecode);

private:
    void updateText();

    int m_digits[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int m_index = 0;
    int m_frame = 0;
    bool m_locked = false;
    double m_fps = 30.0;
};

} // namespace mxu::app
