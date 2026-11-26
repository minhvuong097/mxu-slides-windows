#pragma once

#include "core/Document.h"

#include <QObject>
#include <QString>
#include <QVariantList>

namespace mxu::app {

// Song arrangements: named subsets of a song's slides ("Full", "Chorus only").
class ArrangementService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList arrangements READ arrangements NOTIFY changed)
    Q_PROPERTY(QString active READ active NOTIFY changed)

public:
    explicit ArrangementService(QObject* parent = nullptr);
    void setDocument(core::Document* document);

    QVariantList arrangements() const;
    QString active() const { return m_active; }

public slots:
    QString save(const QString& name, const QVariantList& slideIndexes);
    bool apply(const QString& id);
    bool remove(const QString& id);

signals:
    void changed();
    void slideRequested(int index);
    void notification(const QString& message);

private:
    void refresh();
    void commit();

    core::Document* m_document = nullptr;
    QVariantList m_arrangements;
    QString m_active;
};

} // namespace mxu::app
