#pragma once

#include <QObject>
#include <QSettings>
#include <QString>
#include <QVariantList>
#include <QVariantMap>

namespace mxu::app {

// Display topology and per-role output assignment, equivalent to the macOS
// OutputManager/ScreenMap. Uses QScreen on Windows (DXGI behind Qt).
class OutputManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList screens READ screens CONSTANT)
    Q_PROPERTY(QVariantMap assignments READ assignments NOTIFY changed)
    Q_PROPERTY(bool confidenceMonitor READ confidenceMonitor WRITE setConfidenceMonitor NOTIFY changed)
    Q_PROPERTY(bool alwaysOnTop READ alwaysOnTop WRITE setAlwaysOnTop NOTIFY changed)

public:
    explicit OutputManager(QObject* parent = nullptr);

    QVariantList screens() const;
    QVariantMap assignments() const;
    QString assignment(const QString& role) const;
    bool confidenceMonitor() const;
    bool alwaysOnTop() const;

    void setConfidenceMonitor(bool value);
    void setAlwaysOnTop(bool value);

public slots:
    bool assign(const QString& role, int screenIndex);
    void cycleScreen(const QString& role);
    void identify();

signals:
    void changed();
    void notification(const QString& message);

private:
    void load();
    void save();

    QSettings m_store;
    QVariantMap m_assignments;
    bool m_confidenceMonitor = true;
    bool m_alwaysOnTop = true;
};

} // namespace mxu::app
