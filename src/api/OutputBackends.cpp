#include "OutputBackends.h"

namespace mxu::api {

NdiSender::NdiSender(QObject* parent)
    : QObject(parent)
{
}

bool NdiSender::available() const
{
#ifdef MXU_HAS_NDI_SDK
    return true;
#else
    return false;
#endif
}

bool NdiSender::start(const QString& name)
{
    Q_UNUSED(name)
    if (!available())
        return false;
    m_active = true;
    emit changed();
    return true;
}

void NdiSender::stop()
{
    if (!m_active)
        return;
    m_active = false;
    emit changed();
}

DeckLinkOutput::DeckLinkOutput(QObject* parent)
    : QObject(parent)
{
}

bool DeckLinkOutput::available() const
{
#ifdef MXU_HAS_DECKLINK_SDK
    return true;
#else
    return false;
#endif
}

bool DeckLinkOutput::start(int deviceIndex)
{
    Q_UNUSED(deviceIndex)
    if (!available())
        return false;
    m_active = true;
    emit changed();
    return true;
}

void DeckLinkOutput::stop()
{
    if (!m_active)
        return;
    m_active = false;
    emit changed();
}

} // namespace mxu::api
