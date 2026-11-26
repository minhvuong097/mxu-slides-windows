#pragma once

#include "core/SceneModel.h"

#include <QQuickPaintedItem>
#include <QVariantList>

namespace mxu::ui {

// QML-visible render surface. Paints a RenderScene through SceneRasterizer and
// cross-fades to the previous scene during transitions — the Windows
// counterpart of the macOS MetalSceneView/Compositor.
class ScenePaintedItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QVariantList layers READ layers WRITE setLayers NOTIFY layersChanged)
    Q_PROPERTY(QVariantList previousLayers READ previousLayers WRITE setPreviousLayers NOTIFY layersChanged)
    Q_PROPERTY(qreal transitionProgress READ transitionProgress WRITE setTransitionProgress NOTIFY transitionChanged)
    Q_PROPERTY(QString transitionKind READ transitionKind WRITE setTransitionKind NOTIFY transitionChanged)
    Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY layersChanged)

public:
    explicit ScenePaintedItem(QQuickItem* parent = nullptr);

    void paint(QPainter* painter) override;

    QVariantList layers() const { return m_layers; }
    QVariantList previousLayers() const { return m_previous; }
    qreal transitionProgress() const { return m_progress; }
    QString transitionKind() const { return m_kind; }
    QColor background() const { return m_background; }

    void setLayers(const QVariantList& value);
    void setPreviousLayers(const QVariantList& value);
    void setTransitionProgress(qreal value);
    void setTransitionKind(const QString& value);
    void setBackground(const QColor& value);

signals:
    void layersChanged();
    void transitionChanged();
    void rendered();

private:
    QVariantList m_layers;
    QVariantList m_previous;
    qreal m_progress = 1.0;
    QString m_kind = QStringLiteral(u"dissolve");
    QColor m_background = QColor(QStringLiteral(u"#0b0b0c"));
};

} // namespace mxu::ui
