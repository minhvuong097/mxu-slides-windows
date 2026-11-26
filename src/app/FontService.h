#pragma once

#include <QObject>
#include <QStringList>

namespace mxu::app {

// Installed font inventory used by the editor's font picker.
class FontService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList families READ families CONSTANT)

public:
    explicit FontService(QObject* parent = nullptr);
    QStringList families() const { return m_families; }

private:
    QStringList m_families;
};

} // namespace mxu::app
