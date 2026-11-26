#include "SceneModel.h"

#include <QTimer>

namespace mxu::core {

QString layerKindName(LayerKind kind)
{
    switch (kind) {
    case LayerKind::Slide: return QStringLiteral(u"slide");
    case LayerKind::ForegroundVideo: return QStringLiteral(u"foregroundVideos");
    case LayerKind::Overlay: return QStringLiteral(u"overlays");
    case LayerKind::Alert: return QStringLiteral(u"alerts");
    case LayerKind::LiveInput: return QStringLiteral(u"liveInputs");
    }
    return {};
}

QString transitionName(model::TransitionKind kind)
{
    switch (kind) {
    case model::TransitionKind::Cut: return QStringLiteral(u"cut");
    case model::TransitionKind::Dissolve: return QStringLiteral(u"dissolve");
    case model::TransitionKind::FadeBlack: return QStringLiteral(u"fadeBlack");
    case model::TransitionKind::FadeWhite: return QStringLiteral(u"fadeWhite");
    case model::TransitionKind::FadeColor: return QStringLiteral(u"fadeColor");
    case model::TransitionKind::BlurDissolve: return QStringLiteral(u"blurDissolve");
    case model::TransitionKind::FilmBurn: return QStringLiteral(u"filmBurn");
    }
    return QStringLiteral(u"cut");
}

model::TransitionKind transitionFromName(const QString& name)
{
    if (name == QStringLiteral(u"dissolve")) return model::TransitionKind::Dissolve;
    if (name == QStringLiteral(u"fadeBlack")) return model::TransitionKind::FadeBlack;
    if (name == QStringLiteral(u"fadeWhite")) return model::TransitionKind::FadeWhite;
    if (name == QStringLiteral(u"fadeColor")) return model::TransitionKind::FadeColor;
    if (name == QStringLiteral(u"blurDissolve")) return model::TransitionKind::BlurDissolve;
    if (name == QStringLiteral(u"filmBurn")) return model::TransitionKind::FilmBurn;
    return model::TransitionKind::Cut;
}

RenderScene SceneBuilder::build(const ShowDocument& show, bool showChords,
                                bool showClock, const QString& clockText,
                                const QString& scaleMode, const QString& maskMode,
                                const QString& maskShape) const
{
    Q_UNUSED(showClock)
    Q_UNUSED(clockText)
    auto escapeHtml = [](const QString& text) {
        return text.toHtmlEscaped();
    };

    RenderScene scene;
    scene.scaleMode = scaleMode;
    scene.maskMode = maskMode;
    scene.maskShape = maskShape;
    const QString slideId = show.selectedSlide().isEmpty()
                                ? (show.document().slides.isEmpty() ? QString()
                                                                    : show.document().slides.first().id)
                                : show.selectedSlide();
    const model::Slide* slide = nullptr;
    for (const auto& candidate : show.document().slides) {
        if (candidate.id == slideId) {
            slide = &candidate;
            break;
        }
    }

    RenderLayer layer;
    layer.kind = LayerKind::Slide;
    layer.z = 0;
    if (slide) {
        scene.slideName = slide->name;
        int index = 0;
        for (const auto& object : slide->objects) {
            if (object.hidden.value_or(false))
                continue;
            RenderItem item;
            item.id = object.id;
            item.text = object.text;
            item.kind = object.objectKind == model::SlideObjectKind::Shape
                            ? QStringLiteral(u"shape") : QStringLiteral(u"text");
            if (object.shapeKind)
                item.shapeKind = model::toString(*object.shapeKind);
            if (object.pathData)
                item.pathData = *object.pathData;
            if (object.blendMode)
                item.blendMode = model::toString(*object.blendMode);
            if (object.fill && object.fill->fillKind == model::FillKind::Solid && object.fill->colorHex)
                item.fillColor = *object.fill->colorHex;
            if (object.stroke) {
                item.strokeColor = object.stroke->colorHex;
                item.strokeWidth = object.stroke->width;
            }
            item.x = object.x.value_or(70);
            item.y = object.y.value_or(130);
            item.width = object.width.value_or(500);
            item.height = object.height.value_or(100);
            item.colorHex = object.textStyle && object.textStyle->colorHex
                                ? *object.textStyle->colorHex : QStringLiteral(u"#FFFFFF");
            item.fontSize = object.textStyle && object.textStyle->fontSize
                                ? *object.textStyle->fontSize : 22.0;
            item.opacity = object.opacity.value_or(1.0);

            if (object.styleRuns) {
                for (const auto& run : *object.styleRuns) {
                    item.styleRuns.append(QVariantMap{
                        { QStringLiteral(u"line"), run.line },
                        { QStringLiteral(u"column"), run.column },
                        { QStringLiteral(u"length"), run.length },
                        { QStringLiteral(u"fontSize"), run.fontSize.value_or(item.fontSize) },
                        { QStringLiteral(u"color"), run.colorHex.value_or(item.colorHex) },
                    });
                }
            }

            const QStringList lines = item.text.split(QLatin1Char('\n'));
            QStringList htmlLines;
            for (qsizetype lineIndex = 0; lineIndex < lines.size(); ++lineIndex) {
                QString line = escapeHtml(lines.at(lineIndex));
                for (const QVariant& runValue : item.styleRuns) {
                    const QVariantMap run = runValue.toMap();
                    if (run.value(QStringLiteral(u"line")).toInt() != lineIndex)
                        continue;
                    const int start = qBound(0, run.value(QStringLiteral(u"column")).toInt(), line.size());
                    const int length = qBound(0, run.value(QStringLiteral(u"length")).toInt(), line.size() - start);
                    const QString color = run.value(QStringLiteral(u"color")).toString();
                    if (length <= 0 || color.isEmpty())
                        continue;
                    const QString segment = line.mid(start, length);
                    line.replace(start, length,
                                 QStringLiteral(u"<span style='color:%1'>%2</span>").arg(color, segment));
                }
                htmlLines.append(line);
            }
            item.renderedHtml = htmlLines.join(QStringLiteral(u"<br>"));
            item.z = index++;
            if (showChords && object.chords) {
                for (const auto& chord : *object.chords)
                    item.chord = chord.symbol;
            }
            layer.items.append(item);
        }
    }
    scene.layers.append(layer);
    return scene;
}

QVariantList SceneBuilder::sceneToQml(const RenderScene& scene)
{
    QVariantList layers;
    for (const auto& layer : scene.layers) {
        QVariantList items;
        for (const auto& item : layer.items) {
            items.append(QVariantMap{
                { QStringLiteral(u"id"), item.id },
                { QStringLiteral(u"text"), item.text },
                { QStringLiteral(u"kind"), item.kind },
                { QStringLiteral(u"shapeKind"), item.shapeKind },
                { QStringLiteral(u"pathData"), item.pathData },
                { QStringLiteral(u"fillColor"), item.fillColor },
                { QStringLiteral(u"strokeColor"), item.strokeColor },
                { QStringLiteral(u"strokeWidth"), item.strokeWidth },
                { QStringLiteral(u"blendMode"), item.blendMode },
                { QStringLiteral(u"styleRuns"), item.styleRuns },
                { QStringLiteral(u"richText"), item.renderedHtml },
                { QStringLiteral(u"chord"), item.chord },
                { QStringLiteral(u"x"), item.x },
                { QStringLiteral(u"y"), item.y },
                { QStringLiteral(u"width"), item.width },
                { QStringLiteral(u"height"), item.height },
                { QStringLiteral(u"fontSize"), item.fontSize },
                { QStringLiteral(u"colorHex"), item.colorHex },
                { QStringLiteral(u"opacity"), item.opacity },
                { QStringLiteral(u"z"), item.z },
            });
        }
        layers.append(QVariantMap{
            { QStringLiteral(u"scaleMode"), scene.scaleMode },
            { QStringLiteral(u"maskMode"), scene.maskMode },
            { QStringLiteral(u"maskShape"), scene.maskShape },
            { QStringLiteral(u"kind"), layerKindName(layer.kind) },
            { QStringLiteral(u"z"), layer.z },
            { QStringLiteral(u"opacity"), layer.opacity },
            { QStringLiteral(u"visible"), layer.visible },
            { QStringLiteral(u"items"), items },
        });
    }
    return layers;
}

RenderScene SceneBuilder::sceneFromQml(const QVariantList& layers)
{
    RenderScene scene;
    for (const QVariant& layerValue : layers) {
        const QVariantMap layerMap = layerValue.toMap();
        RenderLayer layer;
        layer.z = layerMap.value(QStringLiteral(u"z")).toInt();
        layer.opacity = layerMap.value(QStringLiteral(u"opacity")).toDouble();
        layer.visible = layerMap.value(QStringLiteral(u"visible")).toBool();
        const QString kind = layerMap.value(QStringLiteral(u"kind")).toString();
        if (kind == QStringLiteral(u"foregroundVideos")) layer.kind = LayerKind::ForegroundVideo;
        else if (kind == QStringLiteral(u"overlays")) layer.kind = LayerKind::Overlay;
        else if (kind == QStringLiteral(u"alerts")) layer.kind = LayerKind::Alert;
        else if (kind == QStringLiteral(u"liveInputs")) layer.kind = LayerKind::LiveInput;
        else layer.kind = LayerKind::Slide;
        if (layerMap.contains(QStringLiteral(u"scaleMode")))
            scene.scaleMode = layerMap.value(QStringLiteral(u"scaleMode")).toString();
        if (layerMap.contains(QStringLiteral(u"maskMode")))
            scene.maskMode = layerMap.value(QStringLiteral(u"maskMode")).toString();
        if (layerMap.contains(QStringLiteral(u"maskShape")))
            scene.maskShape = layerMap.value(QStringLiteral(u"maskShape")).toString();

        for (const QVariant& itemValue : layerMap.value(QStringLiteral(u"items")).toList()) {
            const QVariantMap itemMap = itemValue.toMap();
            RenderItem item;
            item.id = itemMap.value(QStringLiteral(u"id")).toString();
            item.text = itemMap.value(QStringLiteral(u"text")).toString();
            item.chord = itemMap.value(QStringLiteral(u"chord")).toString();
            item.kind = itemMap.value(QStringLiteral(u"kind")).toString();
            item.shapeKind = itemMap.value(QStringLiteral(u"shapeKind")).toString();
            item.pathData = itemMap.value(QStringLiteral(u"pathData")).toString();
            item.fillColor = itemMap.value(QStringLiteral(u"fillColor")).toString();
            item.strokeColor = itemMap.value(QStringLiteral(u"strokeColor")).toString();
            item.strokeWidth = itemMap.value(QStringLiteral(u"strokeWidth")).toDouble();
            item.blendMode = itemMap.value(QStringLiteral(u"blendMode")).toString();
            item.renderedHtml = itemMap.value(QStringLiteral(u"richText")).toString();
            item.x = itemMap.value(QStringLiteral(u"x")).toDouble();
            item.y = itemMap.value(QStringLiteral(u"y")).toDouble();
            item.width = itemMap.value(QStringLiteral(u"width")).toDouble();
            item.height = itemMap.value(QStringLiteral(u"height")).toDouble();
            item.fontSize = itemMap.value(QStringLiteral(u"fontSize")).toDouble();
            item.colorHex = itemMap.value(QStringLiteral(u"colorHex")).toString();
            item.opacity = itemMap.value(QStringLiteral(u"opacity")).toDouble();
            item.z = itemMap.value(QStringLiteral(u"z")).toInt();
            layer.items.append(item);
        }
        scene.layers.append(layer);
    }
    return scene;
}

// ------------------------------------------------------------- Transitions
SceneTransitionEngine::SceneTransitionEngine(QObject* parent)
    : QObject(parent)
{
    // QTimer drives the transition without a render-thread dependency.
    auto* timer = new QTimer(this);
    timer->setInterval(16);
    connect(timer, &QTimer::timeout, this, &SceneTransitionEngine::tick);
    timer->start();
}

void SceneTransitionEngine::setEasing(const QString& value)
{
    if (m_easing == value)
        return;
    m_easing = value;
    emit changed();
}

double SceneTransitionEngine::eased() const
{
    const double t = m_progress;
    if (m_easing == QStringLiteral(u"in"))
        return t * t;
    if (m_easing == QStringLiteral(u"out"))
        return 1.0 - (1.0 - t) * (1.0 - t);
    if (m_easing == QStringLiteral(u"inOut"))
        return t < 0.5 ? 2 * t * t : 1.0 - qPow(-2 * t + 2, 2) / 2.0;
    return t;
}

double SceneTransitionEngine::outgoingOpacity() const
{
    if (m_kind == model::TransitionKind::Cut)
        return m_progress < 1.0 ? 0.0 : 1.0;
    return 1.0 - eased();
}

double SceneTransitionEngine::incomingOpacity() const
{
    if (m_kind == model::TransitionKind::Cut)
        return m_progress >= 1.0 ? 1.0 : 0.0;
    return eased();
}

QColor SceneTransitionEngine::curtainColor() const
{
    switch (m_kind) {
    case model::TransitionKind::FadeWhite: return QColor(Qt::white);
    case model::TransitionKind::FadeColor: return QColor(QStringLiteral(u"#0a84ff"));
    case model::TransitionKind::FilmBurn: return QColor(QStringLiteral(u"#ff8c1a"));
    default: return QColor(Qt::black);
    }
}

double SceneTransitionEngine::curtainOpacity() const
{
    if (!m_running)
        return 0.0;
    switch (m_kind) {
    case model::TransitionKind::FadeBlack:
    case model::TransitionKind::FadeWhite:
    case model::TransitionKind::FadeColor:
    case model::TransitionKind::FilmBurn:
        return 1.0 - qAbs(0.5 - eased()) * 2.0;
    default:
        return 0.0;
    }
}

void SceneTransitionEngine::start(const QString& kind, double durationSeconds)
{
    m_kind = transitionFromName(kind);
    m_duration = qMax(0.05, durationSeconds);
    m_progress = 0.0;
    m_running = true;
    m_clock.restart();
    emit changed();
}

void SceneTransitionEngine::finish()
{
    if (!m_running)
        return;
    m_progress = 1.0;
    m_running = false;
    emit changed();
    emit finished();
}

void SceneTransitionEngine::tick()
{
    if (!m_running)
        return;
    m_progress = qMin(1.0, m_clock.elapsed() / 1000.0 / m_duration);
    if (m_progress >= 1.0) {
        m_running = false;
        emit finished();
    }
    emit changed();
}

// ---------------------------------------------------------------- ShowState
ShowState::ShowState(QObject* parent)
    : QObject(parent)
{
}

void ShowState::present(const QString& slideId)
{
    if (m_live == slideId)
        return;
    m_last = m_live;
    m_live = slideId;
    m_cleared.clear();
    emit changed();
}

void ShowState::clearLayer(const QString& kind)
{
    if (!m_cleared.contains(kind))
        m_cleared.append(kind);
    emit changed();
    emit cleared();
}

void ShowState::clearAll()
{
    m_cleared = { layerKindName(LayerKind::Slide), layerKindName(LayerKind::Overlay),
                  layerKindName(LayerKind::Alert), layerKindName(LayerKind::ForegroundVideo) };
    emit changed();
    emit cleared();
}

void ShowState::restoreAll()
{
    m_cleared.clear();
    emit changed();
    emit restored();
}

bool ShowState::isCleared(const QString& kind) const
{
    return m_cleared.contains(kind);
}

void ShowState::setStageMessage(const QString& message)
{
    if (m_stageMessage == message)
        return;
    m_stageMessage = message;
    emit changed();
}

} // namespace mxu::core
