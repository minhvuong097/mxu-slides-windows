#pragma once

#include <QObject>
#include <QSettings>
#include <QString>
#include <QVariantList>
#include <QVariantMap>

namespace mxu::app {

// Layout tree for the confidence monitor: ordered nodes of sources
// (current slide, next slide, clock, timer, stage message, media).
class ConfidenceLayoutService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList nodes READ nodes NOTIFY changed)
    Q_PROPERTY(QString structure READ structure WRITE setStructure NOTIFY changed)
    Q_PROPERTY(QStringList sourceKinds READ sourceKinds CONSTANT)

public:
    explicit ConfidenceLayoutService(QObject* parent = nullptr);

    QVariantList nodes() const;
    QString structure() const { return m_structure; }
    QStringList sourceKinds() const;
    void setStructure(const QString& value);

public slots:
    QString add(const QString& source, const QString& title);
    bool remove(const QString& id);
    bool move(const QString& id, int delta);
    void reset();

signals:
    void changed();
    void notification(const QString& message);

private:
    void load();
    void save();

    QSettings m_store;
    QVariantList m_nodes;
    QString m_structure = QStringLiteral(u"Tall Stack");
};

} // namespace mxu::app
