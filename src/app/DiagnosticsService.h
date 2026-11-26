#pragma once

#include <QObject>
#include <QElapsedTimer>
#include <QTimer>
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
    Q_PROPERTY(double fps READ fps NOTIFY changed)
    Q_PROPERTY(int hitchCount READ hitchCount NOTIFY changed)
    Q_PROPERTY(double maxFrameMs READ maxFrameMs NOTIFY changed)

public:
    explicit DiagnosticsService(QObject* parent = nullptr);

    QVariantList events() const;
    int tickCount() const { return m_ticks; }
    int errorCount() const { return m_errors; }
    QString uptime() const;
    double fps() const { return m_fps; }
    int hitchCount() const { return m_hitches; }
    double maxFrameMs() const { return m_maxFrameMs; }

public slots:
    void frameTick();
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
    QTimer m_frameTimer;
    qint64 m_lastFrame = 0;
    double m_fps = 60.0;
    double m_maxFrameMs = 0.0;
    int m_hitches = 0;
    int m_frames = 0;
};

} // namespace mxu::app
