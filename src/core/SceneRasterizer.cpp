#include "SceneRasterizer.h"

#include <QFont>
#include <QPainterPath>
#include <QTextDocument>

namespace mxu::core {

SceneRasterizer::SceneRasterizer(QObject* parent)
    : QObject(parent)
{
}

QPainter::CompositionMode SceneRasterizer::compositionMode(const QString& mode)
{
    if (mode == QStringLiteral(u"multiply"))
        return QPainter::CompositionMode_Multiply;
    if (mode == QStringLiteral(u"screen"))
        return QPainter::CompositionMode_Screen;
    if (mode == QStringLiteral(u"add"))
        return QPainter::CompositionMode_Plus;
    return QPainter::CompositionMode_SourceOver;
}

void SceneRasterizer::drawChord(QPainter& painter, const RenderItem& item, const QRect& bounds) const
{
    if (item.chord.isEmpty())
        return;
    QFont font(QStringLiteral(u"Segoe UI"));
    font.setPixelSize(qMax(12, static_cast<int>(item.fontSize * 0.7)));
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(QColor(QStringLiteral(u"#ffd60a")));
    painter.drawText(QRect(bounds.x(), bounds.y() - font.pixelSize(), bounds.width(), font.pixelSize()),
                     Qt::AlignLeft, item.chord);
}

void SceneRasterizer::drawItem(QPainter& painter, const RenderItem& item, const QRect& bounds) const
{
    painter.setOpacity(item.opacity);
    painter.setCompositionMode(compositionMode(item.blendMode));

    if (item.kind == QStringLiteral(u"shape")) {
        QPen pen(QColor(item.strokeColor));
        pen.setWidthF(item.strokeWidth);
        painter.setPen(pen);
        painter.setBrush(QColor(item.fillColor));
        QPainterPath path;
        if (item.shapeKind == QStringLiteral(u"ellipse") || item.pathData.startsWith(QStringLiteral(u"M ")))
            path.addEllipse(QRectF(bounds));
        else
            path.addRect(QRectF(bounds));
        painter.drawPath(path);
        return;
    }

    const QColor color(item.colorHex);
    if (!item.renderedHtml.isEmpty()) {
        QTextDocument document;
        document.setHtml(QStringLiteral(u"<div style='color:%1;'>%2</div>")
                             .arg(item.colorHex, item.renderedHtml));
        document.setTextWidth(bounds.width());
        painter.save();
        painter.translate(bounds.x(), bounds.y() + (bounds.height() - document.size().height()) / 2);
        document.drawContents(&painter);
        painter.restore();
    } else {
        QFont font(QStringLiteral(u"Segoe UI"));
        font.setPixelSize(static_cast<int>(item.fontSize));
        font.setBold(true);
        painter.setFont(font);
        painter.setPen(color);
        painter.drawText(bounds, Qt::AlignCenter | Qt::TextWordWrap, item.text);
    }
    drawChord(painter, item, bounds);
}

void SceneRasterizer::applyMask(QImage& image, const QString& mode, const QString& shape) const
{
    if (mode != QStringLiteral(u"out") && mode != QStringLiteral(u"in"))
        return;
    const QRect region(static_cast<int>(image.width() * 0.08), static_cast<int>(image.height() * 0.08),
                       static_cast<int>(image.width() * 0.84), static_cast<int>(image.height() * 0.84));
    QPainterPath path;
    if (shape == QStringLiteral(u"ellipse"))
        path.addEllipse(QRectF(region));
    else
        path.addRect(region);

    QPainter painter(&image);
    painter.setPen(Qt::NoPen);
    if (mode == QStringLiteral(u"out")) {
        QPainterPath outside;
        outside.addRect(image.rect());
        painter.setBrush(QColor(Qt::black));
        painter.drawPath(outside.subtracted(path));
    } else {
        const QRect inner = region.adjusted(6, 6, -6, -6);
        QPainterPath fill;
        if (shape == QStringLiteral(u"ellipse"))
            fill.addEllipse(QRectF(inner));
        else
            fill.addRect(inner);
        painter.setBrush(QColor(Qt::white));
        painter.drawPath(fill.subtracted(path));
    }
    painter.end();
}

QImage SceneRasterizer::render(const RenderScene& scene, const QSize& size) const
{
    QImage image(size, QImage::Format_ARGB32);
    image.fill(QColor(scene.backgroundHex));
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);
    for (const auto& layer : scene.layers) {
        if (!layer.visible)
            continue;
        painter.setOpacity(layer.opacity);
        for (const auto& item : layer.items) {
            const QRect bounds(static_cast<int>(item.x), static_cast<int>(item.y),
                               static_cast<int>(item.width), static_cast<int>(item.height));
            drawItem(painter, item, bounds);
        }
    }
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.setOpacity(1.0);
    painter.end();
    applyMask(image, scene.maskMode, scene.maskShape);
    return image;
}

QImage SceneRasterizer::renderBlended(const RenderScene& previous, const RenderScene& current,
                                      const QSize& size, double progress, const QString& kind) const
{
    const QImage outgoing = render(previous, size);
    QImage result = outgoing.copy();
    if (kind == QStringLiteral(u"cut")) {
        if (progress >= 0.5)
            return render(current, size);
        return result;
    }
    const QImage incoming = render(current, size);
    QPainter painter(&result);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setOpacity(qBound(0.0, progress, 1.0));
    painter.drawImage(0, 0, incoming);
    painter.end();
    if (kind == QStringLiteral(u"fadeBlack") || kind == QStringLiteral(u"fadeWhite")
        || kind == QStringLiteral(u"fadeColor") || kind == QStringLiteral(u"filmBurn")) {
        QPainter curtain(&result);
        const QColor color = kind == QStringLiteral(u"fadeWhite") ? QColor(Qt::white)
                             : kind == QStringLiteral(u"fadeColor") ? QColor(QStringLiteral(u"#0a84ff"))
                             : kind == QStringLiteral(u"filmBurn") ? QColor(QStringLiteral(u"#ff8c1a"))
                             : QColor(Qt::black);
        curtain.fillRect(result.rect(), QColor(color.red(), color.green(), color.blue(),
                                               qRound(255 * (1.0 - qAbs(0.5 - progress) * 2.0))));
        curtain.end();
    }
    return result;
}

} // namespace mxu::core
