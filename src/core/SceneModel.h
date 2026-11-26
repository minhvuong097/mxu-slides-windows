#pragma once

#include "generated/Models.h"
#include "ShowDocument.h"

#include <QColor>
#include <QElapsedTimer>
#include <QObject>
#include <QString>
#include <QVariantList>
#include <QVariantList>
#include <QVariantMap>
#include <QVector>

namespace mxu::core {

enum class LayerKind
{
    Slide,
    ForegroundVideo,
    Overlay,
    Alert,
    LiveInput,
};

QString layerKindName(LayerKind kind);
QString transitionName(model::TransitionKind kind);
model::TransitionKind transitionFromName(const QString& name);

// A single renderable item inside a layer. Geometry is in the 1920x1080
// coordinate system, matching the macOS RenderItem.
struct RenderItem
{
    QString id;
    QString text;
    QString chord;
    QString kind = QStringLiteral(u"text");
    QString shapeKind;
    QString pathData;
    QString fillColor;
    QString strokeColor;
    double strokeWidth = 0;
    QString blendMode = QStringLiteral(u"normal");
    QVariantList styleRuns;
    QString renderedHtml;
    double x = 0;
    double y = 0;
    double width = 0;
    double height = 0;
    double fontSize = 22;
    QString colorHex = QStringLiteral(u"#FFFFFF");
    double opacity = 1.0;
    int z = 0;
};

struct RenderLayer
{
    LayerKind kind = LayerKind::Slide;
    int z = 0;
    double opacity = 1.0;
    bool visible = true;
    QVector<RenderItem> items;
};

struct RenderScene
{
    QVector<RenderLayer> layers;
    QString backgroundHex = QStringLiteral(u"#0b0b0c");
    QString slideName;
    QString scaleMode = QStringLiteral(u"fit");
    QString maskMode = QStringLiteral(u"out");
    QString maskShape = QStringLiteral(u"rectangle");
};

// Builds a render scene from the current slide and stage options.
class SceneBuilder
{
public:
    RenderScene build(const ShowDocument& show, bool showChords, bool showClock,
                      const QString& clockText, const QString& scaleMode = QStringLiteral(u"fit"),
                      const QString& maskMode = QStringLiteral(u"out"),
                      const QString& maskShape = QStringLiteral(u"rectangle")) const;

    static QVariantList sceneToQml(const RenderScene& scene);
    static RenderScene sceneFromQml(const QVariantList& layers);
};

// Qt-side counterpart of the macOS SceneTransitionEngine.
class SceneTransitionEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString kind READ kind NOTIFY changed)
    Q_PROPERTY(QString easing READ easing WRITE setEasing NOTIFY changed)
    Q_PROPERTY(double progress READ progress NOTIFY changed)
    Q_PROPERTY(double outgoingOpacity READ outgoingOpacity NOTIFY changed)
    Q_PROPERTY(double incomingOpacity READ incomingOpacity NOTIFY changed)
    Q_PROPERTY(QColor curtainColor READ curtainColor NOTIFY changed)
    Q_PROPERTY(double curtainOpacity READ curtainOpacity NOTIFY changed)
    Q_PROPERTY(bool running READ running NOTIFY changed)

public:
    explicit SceneTransitionEngine(QObject* parent = nullptr);

    QString kind() const { return transitionName(m_kind); }
    QString easing() const { return m_easing; }
    void setEasing(const QString& value);
    double progress() const { return m_progress; }
    double outgoingOpacity() const;
    double incomingOpacity() const;
    QColor curtainColor() const;
    double curtainOpacity() const;
    bool running() const { return m_running; }

    Q_INVOKABLE void start(const QString& kind, double durationSeconds);
    Q_INVOKABLE void finish();

signals:
    void changed();
    void finished();

private slots:
    void tick();

    double eased() const;

private:
    model::TransitionKind m_kind = model::TransitionKind::Cut;
    double m_duration = 0.0;
    double m_progress = 1.0;
    QString m_easing = QStringLiteral(u"inOut");
    bool m_running = false;
    QElapsedTimer m_clock;
};

// Live show state: which slide is on air, what was cleared, active overlays.
class ShowState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString liveSlideId READ liveSlideId NOTIFY changed)
    Q_PROPERTY(QString lastSlideId READ lastSlideId NOTIFY changed)
    Q_PROPERTY(QStringList clearedLayers READ clearedLayers NOTIFY changed)
    Q_PROPERTY(QString stageMessage READ stageMessage WRITE setStageMessage NOTIFY changed)

public:
    explicit ShowState(QObject* parent = nullptr);

    QString liveSlideId() const { return m_live; }
    QString lastSlideId() const { return m_last; }
    QStringList clearedLayers() const { return m_cleared; }
    QString stageMessage() const { return m_stageMessage; }

    Q_INVOKABLE void present(const QString& slideId);
    Q_INVOKABLE void clearLayer(const QString& kind);
    Q_INVOKABLE void clearAll();
    Q_INVOKABLE void restoreAll();
    Q_INVOKABLE bool isCleared(const QString& kind) const;

    void setStageMessage(const QString& message);

signals:
    void changed();
    void cleared();
    void restored();

private:
    QString m_live;
    QString m_last;
    QStringList m_cleared;
    QString m_stageMessage;
};

} // namespace mxu::core
