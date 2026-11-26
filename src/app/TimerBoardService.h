#pragma once

#include <QObject>
#include <QTimer>
#include <QVariantList>
#include <QVariantMap>

namespace mxu::app {

// Multiple service timers with countdown/count-up/count-down-to-time modes,
// warning thresholds and per-timer state — the macOS TimerBoard module.
class TimerBoardService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList timers READ timers NOTIFY changed)
    Q_PROPERTY(int runningCount READ runningCount NOTIFY changed)

public:
    explicit TimerBoardService(QObject* parent = nullptr);

    QVariantList timers() const;
    int runningCount() const { return m_running; }

public slots:
    QString add(const QString& name, qint64 seconds, int warnSeconds,
                const QString& mode = QStringLiteral(u"countdown"));
    bool start(const QString& id);
    bool pause(const QString& id);
    bool reset(const QString& id);
    bool remove(const QString& id);
    void stopAll();

signals:
    void changed();
    void warning(const QString& name);
    void expired(const QString& name);
    void notification(const QString& message);

private slots:
    void tick();

private:
    QVariantList m_timers;
    QTimer m_clock;
    int m_running = 0;
};

} // namespace mxu::app
