#pragma once

#include "Document.h"
#include "generated/Models.h"

#include <QJsonObject>
#include <QString>
#include <QVariantList>
#include <QVariantMap>
#include <QVector>

namespace mxu::core {

// Editing session around a Document. Every mutation snapshots the document
// as JSON so undo/redo works across slides, objects and properties.
class ShowDocument
{
public:
    static constexpr int kMaxHistory = 100;

    void setDocument(Document document);
    Document& document() { return m_document; }
    const Document& document() const { return m_document; }

    bool canUndo() const { return !m_undo.isEmpty(); }
    bool canRedo() const { return !m_redo.isEmpty(); }
    void undo();
    void redo();

    QString addSlide(const QString& name, const QString& text);
    bool removeSlide(const QString& id);
    bool duplicateSlide(const QString& id);
    bool moveSlide(const QString& id, int delta);

    QString addTextObject(const QString& slideId, const QString& text,
                          double x, double y, double width, double height);
    bool updateObject(const QString& slideId, const QString& objectId,
                      const QVariantMap& patch);
    bool removeObject(const QString& slideId, const QString& objectId);

    void selectSlide(const QString& id) { m_selectedSlide = id; }
    void selectObject(const QString& id) { m_selectedObject = id; }
    QString selectedSlide() const { return m_selectedSlide; }
    QString selectedObject() const { return m_selectedObject; }

    QVariantList slidesForQml() const;
    QVariantList objectsForQml(const QString& slideId) const;
    QVariantMap objectForQml(const QString& objectId) const;

private:
    void pushUndo();
    model::Slide* findSlide(const QString& id);
    const model::Slide* findSlide(const QString& id) const;
    model::SlideObject* findObject(const QString& slideId, const QString& objectId);

    Document m_document;
    QVector<QJsonObject> m_undo;
    QVector<QJsonObject> m_redo;
    QString m_selectedSlide;
    QString m_selectedObject;
};

} // namespace mxu::core
