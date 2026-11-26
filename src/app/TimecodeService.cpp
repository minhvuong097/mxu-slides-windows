#include "TimecodeService.h"

namespace mxu::app {

TimecodeService::TimecodeService(QObject* parent)
    : QObject(parent)
{
    updateText();
}

void TimecodeService::setFramesPerSecond(double value)
{
    if (qFuzzyCompare(m_fps, value))
        return;
    m_fps = value <= 0 ? 30.0 : value;
    updateText();
    emit changed();
}

QString TimecodeService::timecode() const
{
    return QStringLiteral(u"%1%2:%3%4:%5%6:%7%8")
        .arg(m_digits[4]).arg(m_digits[5]).arg(m_digits[6]).arg(m_digits[7])
        .arg(m_digits[0]).arg(m_digits[1]).arg(m_digits[2]).arg(m_digits[3]);
}

void TimecodeService::quarterFrame(int value)
{
    const int nibble = value & 0x0F;
    const int kind = (value >> 4) & 0x07;
    switch (kind) {
    case 0: m_digits[0] = nibble; break;
    case 1: m_digits[1] = nibble; break;
    case 2: m_digits[2] = nibble; break;
    case 3: m_digits[3] = nibble; break;
    case 4: m_digits[4] = nibble; break;
    case 5: m_digits[5] = nibble; break;
    case 6: m_digits[6] = nibble; break;
    case 7: m_digits[7] = nibble; break;
    }
    ++m_index;
    if (m_index >= 8) {
        m_index = 0;
        m_locked = true;
        updateText();
        emit fullFrame(timecode());
    }
    emit changed();
}

void TimecodeService::setManual(const QString& text)
{
    const QStringList parts = text.split(QLatin1Char(':'));
    if (parts.size() != 4)
        return;
    const int targets[4][2] = { { 4, 5 }, { 6, 7 }, { 0, 1 }, { 2, 3 } };
    for (int i = 0; i < 4; ++i) {
        const QString part = parts.at(i);
        if (part.size() < 2)
            return;
        m_digits[targets[i][0]] = part.at(0).digitValue();
        m_digits[targets[i][1]] = part.at(1).digitValue();
    }
    m_locked = true;
    updateText();
    emit changed();
}

void TimecodeService::reset()
{
    for (int i = 0; i < 8; ++i)
        m_digits[i] = 0;
    m_index = 0;
    m_locked = false;
    updateText();
    emit changed();
}

void TimecodeService::updateText()
{
    emit changed();
}

} // namespace mxu::app
