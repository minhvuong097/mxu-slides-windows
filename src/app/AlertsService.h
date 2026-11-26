#pragma once

#include <QObject>
#include <QString>
#include <QVariantMap>

namespace mxu::app {

// Alerts/lower-thirds surfaced in presentation, stage and confidence outputs.
class AlertsService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap active READ active NOTIFY changed)
    Q_PROPERTY(bool visible READ visible NOTIFY changed)

public:
    explicit AlertsService(QObject* parent = nullptr);

    QVariantMap active() const { return m_active; }
    bool visible() const { return m_visible; }

public slots:
    bool fire(const QString& text, const QString& target = QStringLiteral(u"both"),
              const QString& behavior = QStringLiteral(u"persist"));
    void dismiss();

signals:
    void changed();
    void notification(const QString& message);

private:
    QVariantMap m_active;
    bool m_visible = false;
};

} // namespace mxu::app
