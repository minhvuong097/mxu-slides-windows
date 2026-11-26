#pragma once

#include <QObject>
#include <QVariantList>

namespace mxu::app {

// Named, colour-coded groups for slides and service items (GroupPalette).
class GroupPaletteService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList groups READ groups NOTIFY changed)

public:
    explicit GroupPaletteService(QObject* parent = nullptr);

    QVariantList groups() const { return m_groups; }

public slots:
    QString add(const QString& name, const QString& color);
    bool remove(const QString& id);
    bool rename(const QString& id, const QString& name);

signals:
    void changed();

private:
    QVariantList m_groups;
};

} // namespace mxu::app
