#include "ScenePaintedItem.h"
#include "core/SceneRasterizer.h"

#include <QPainter>

namespace mxu::ui {

ScenePaintedItem::ScenePaintedItem(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
    setAntialiasing(true);
    setRenderTarget(QQuickPaintedItem::Image);
}

void ScenePaintedItem::paint(QPainter* painter)
{
    const QSize size(qMax(1, static_cast<int>(width())), qMax(1, static_cast<int>(height())));
    const core::RenderScene current = core::SceneBuilder::sceneFromQml(m_layers);
    core::SceneRasterizer rasterizer;

    QImage image;
    if (m_previous.isEmpty() || m_progress >= 1.0 || m_kind == QStringLiteral(u"cut")) {
        image = rasterizer.render(current, size);
    } else {
        const core::RenderScene previous = core::SceneBuilder::sceneFromQml(m_previous);
        image = rasterizer.renderBlended(previous, current, size, m_progress, m_kind);
    }
    painter->drawImage(0, 0, image);
    emit rendered();
}

void ScenePaintedItem::setLayers(const QVariantList& value)
{
    if (m_layers == value)
        return;
    m_previous = m_layers;
    m_layers = value;
    update();
    emit layersChanged();
}

void ScenePaintedItem::setPreviousLayers(const QVariantList& value)
{
    if (m_previous == value)
        return;
    m_previous = value;
    update();
    emit layersChanged();
}

void ScenePaintedItem::setTransitionProgress(qreal value)
{
    value = qBound(0.0, value, 1.0);
    if (qFuzzyCompare(m_progress, value))
        return;
    m_progress = value;
    update();
    emit transitionChanged();
}

void ScenePaintedItem::setTransitionKind(const QString& value)
{
    if (m_kind == value)
        return;
    m_kind = value;
    update();
    emit transitionChanged();
}

void ScenePaintedItem::setBackground(const QColor& value)
{
    if (m_background == value)
        return;
    m_background = value;
    update();
    emit layersChanged();
}

} // namespace mxu::ui
