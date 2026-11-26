#pragma once

#include <QObject>
#include <QVariantList>

namespace mxu::app {

// Audio input/output inventory via Qt Multimedia (WASAPI on Windows).
class AudioDeviceService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList inputs READ inputs NOTIFY changed)
    Q_PROPERTY(QVariantList outputs READ outputs NOTIFY changed)

public:
    explicit AudioDeviceService(QObject* parent = nullptr);

    QVariantList inputs() const { return m_inputs; }
    QVariantList outputs() const { return m_outputs; }

public slots:
    void refresh();

signals:
    void changed();

private:
    QVariantList m_inputs;
    QVariantList m_outputs;
};

} // namespace mxu::app
