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

double SceneTransitionEngine::outgoingOpacity() const
{
    if (m_kind == model::TransitionKind::Cut)
        return m_progress < 1.0 ? 0.0 : 1.0;
    return 1.0 - m_progress;
}

double SceneTransitionEngine::incomingOpacity() const
{
    if (m_kind == model::TransitionKind::Cut)
        return m_progress >= 1.0 ? 1.0 : 0.0;
    return m_progress;
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
        return 1.0 - qAbs(0.5 - m_progress) * 2.0;
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
