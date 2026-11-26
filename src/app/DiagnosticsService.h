#pragma once

#include <QObject>
#include <QElapsedTimer>
#include <QString>
#include <QVariantList>

namespace mxu::app {

// Lightweight runtime diagnostics: ring-buffer of events, counters and a
// JSON report, analogous to the macOS DiagnosticsStore breadcrumbs.
class DiagnosticsService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList events READ events NOTIFY changed)
    Q_PROPERTY(int tickCount READ tickCount NOTIFY changed)
    Q_PROPERTY(int errorCount READ errorCount NOTIFY changed)
    Q_PROPERTY(QString uptime READ uptime NOTIFY changed)

public:
    explicit DiagnosticsService(QObject* parent = nullptr);

    QVariantList events() const;
    int tickCount() const { return m_ticks; }
    int errorCount() const { return m_errors; }
    QString uptime() const;

public slots:
    void log(const QString& message, bool isError = false);
    void tick();
    QString reportJson() const;

signals:
    void changed();

private:
    QVariantList m_events;
    QElapsedTimer m_started;
    int m_ticks = 0;
    int m_errors = 0;
};

} // namespace mxu::app
