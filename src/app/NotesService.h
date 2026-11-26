#pragma once

#include "core/Document.h"

#include <QObject>
#include <QString>
#include <QVariantList>

namespace mxu::app {

// Sermon notes backed by the generated NoteDocument schema. Blocks are kept
// as JSON so the document format stays compatible with the macOS app.
class NotesService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList blocks READ blocks NOTIFY changed)
    Q_PROPERTY(QString text READ text NOTIFY changed)

public:
    explicit NotesService(QObject* parent = nullptr);
    void setDocument(core::Document* document);

    QVariantList blocks() const;
    QString text() const;

public slots:
    QString addBlock(const QString& text);
    bool updateBlock(const QString& id, const QString& text);
    bool removeBlock(const QString& id);
    bool linkSlide(const QString& id, const QString& slideId);

signals:
    void changed();

private:
    void commit();

    core::Document* m_document = nullptr;
    QVariantList m_blocks;
};

} // namespace mxu::app
