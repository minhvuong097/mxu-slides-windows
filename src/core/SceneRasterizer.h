#pragma once

#include "SceneModel.h"

#include <QImage>
#include <QtGui/QPainter>
#include <QObject>
#include <QRect>

namespace mxu::core {

// QPainter-based scene rasterizer used for PNG export and thumbnails. Keeps
// geometry, style runs, chords, blend modes and masks in one place instead of
// duplicating draw logic in the controller.
class SceneRasterizer : public QObject
{
    Q_OBJECT

public:
    explicit SceneRasterizer(QObject* parent = nullptr);

    Q_INVOKABLE QImage render(const RenderScene& scene, const QSize& size) const;

private:
    void drawItem(QPainter& painter, const RenderItem& item, const QRect& bounds) const;
    void drawChord(QPainter& painter, const RenderItem& item, const QRect& bounds) const;
    void applyMask(QImage& image, const QString& mode, const QString& shape) const;
    static QPainter::CompositionMode compositionMode(const QString& mode);
};

} // namespace mxu::core
