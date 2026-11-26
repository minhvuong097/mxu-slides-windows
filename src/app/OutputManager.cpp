#include "OutputManager.h"

#include <QGuiApplication>
#include <QScreen>

namespace mxu::app {

OutputManager::OutputManager(QObject* parent)
    : QObject(parent)
{
    load();
}

QVariantList OutputManager::screens() const
{
    QVariantList result;
    const auto list = QGuiApplication::screens();
    for (qsizetype i = 0; i < list.size(); ++i) {
        const QSize size = list.at(i)->geometry().size();
        result.append(QVariantMap{
            { QStringLiteral(u"index"), static_cast<int>(i) },
            { QStringLiteral(u"name"), QStringLiteral(u"Display %1").arg(i + 1) },
            { QStringLiteral(u"geometry"), QStringLiteral(u"%1 × %2").arg(size.width()).arg(size.height()) },
        });
    }
    return result;
}

QVariantMap OutputManager::assignments() const
{
    return m_assignments;
}

QString OutputManager::assignment(const QString& role) const
{
    return m_assignments.value(role).toString();
}

bool OutputManager::confidenceMonitor() const { return m_confidenceMonitor; }
bool OutputManager::alwaysOnTop() const { return m_alwaysOnTop; }

void OutputManager::setConfidenceMonitor(bool value)
{
    if (m_confidenceMonitor == value)
        return;
    m_confidenceMonitor = value;
    save();
    emit changed();
}

void OutputManager::setAlwaysOnTop(bool value)
{
    if (m_alwaysOnTop == value)
        return;
    m_alwaysOnTop = value;
    save();
    emit changed();
}

void OutputManager::load()
{
    m_assignments = m_store.value(QStringLiteral(u"mxu/outputs/assignments")).toMap();
    if (!m_assignments.contains(QStringLiteral(u"main")))
        m_assignments.insert(QStringLiteral(u"main"), QStringLiteral(u"Display 2 (1920 × 1080)"));
    if (!m_assignments.contains(QStringLiteral(u"stage")))
        m_assignments.insert(QStringLiteral(u"stage"), QStringLiteral(u"Display 3"));
    m_confidenceMonitor = m_store.value(QStringLiteral(u"mxu/outputs/confidence"), true).toBool();
    m_alwaysOnTop = m_store.value(QStringLiteral(u"mxu/outputs/alwaysOnTop"), true).toBool();
}

void OutputManager::save()
{
    m_store.setValue(QStringLiteral(u"mxu/outputs/assignments"), m_assignments);
    m_store.setValue(QStringLiteral(u"mxu/outputs/confidence"), m_confidenceMonitor);
    m_store.setValue(QStringLiteral(u"mxu/outputs/alwaysOnTop"), m_alwaysOnTop);
    m_store.sync();
}

bool OutputManager::assign(const QString& role, int screenIndex)
{
    const QVariantList list = screens();
    if (screenIndex < 0 || screenIndex >= list.size())
        return false;
    const QVariantMap screen = list.at(screenIndex).toMap();
    m_assignments.insert(role, QStringLiteral(u"%1 (%2)")
                                   .arg(screen.value(QStringLiteral(u"name")).toString(),
                                        screen.value(QStringLiteral(u"geometry")).toString()));
    save();
    emit changed();
    emit notification(QStringLiteral(u"%1 → %2").arg(role, assignment(role)));
    return true;
}

int OutputManager::screenIndexFor(const QString& role) const
{
    const QString current = assignment(role);
    const QVariantList list = screens();
    for (int i = 0; i < list.size(); ++i) {
        const QString name = QStringLiteral(u"Display %1").arg(i + 1);
        if (current.contains(name))
            return i;
    }
    const int fallback = role == QStringLiteral(u"main") ? 1
                         : role == QStringLiteral(u"stage") ? 2 : 0;
    return fallback < list.size() ? fallback : 0;
}

void OutputManager::cycleScreen(const QString& role)
{
    const int count = screens().size();
    if (count == 0)
        return;
    const QString current = assignment(role);
    int index = 0;
    for (int i = 0; i < count; ++i) {
        if (current.contains(QStringLiteral(u"Display %1").arg(i + 1)))
            index = (i + 1) % count;
    }
    assign(role, index);
}

void OutputManager::identify()
{
    QStringList labels;
    for (const QVariant& entry : screens()) {
        const QVariantMap screen = entry.toMap();
        labels.append(QStringLiteral(u"%1 (%2)")
                          .arg(screen.value(QStringLiteral(u"name")).toString(),
                               screen.value(QStringLiteral(u"geometry")).toString()));
    }
    emit notification(labels.join(QStringLiteral(u", ")));
}

} // namespace mxu::app
