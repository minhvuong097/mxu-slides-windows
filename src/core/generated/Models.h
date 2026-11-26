// Generated from schema/documents.json — do not edit by hand.
// Regenerate: python3 scripts/generate_models.py
#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QVector>

#include <memory>
#include <optional>
#include <type_traits>

namespace mxu::model {

// Forward declarations (record dependency graph is acyclic).
struct MediaSourceRect;
struct GradientStop;
struct ObjectFill;
struct ObjectStroke;
struct ObjectShadow;
struct LineStyleOverride;
struct TextLineFill;
struct ChordPlacement;
struct TextStyle;
struct VisibilityCondition;
struct TextStyleRun;
struct KeepFromSlideOptions;
struct BlockScroll;
struct AnimationRange;
struct VideoPush;
struct AnimationStep;
struct AnimationPreset;
struct AnimationPresetBoard;
struct SlideObject;
struct CueMedia;
struct Slide;
struct AutoAdvance;
struct PresentationSection;
struct CCLIInfo;
struct Arrangement;
struct PresentationOrigin;
struct TimelineCue;
struct ClipFade;
struct PresentationTimeline;
struct SongMap;
struct AudioSection;
struct SongMapBlock;
struct Presentation;
struct MediaItem;
struct VideoMark;
struct AudioItem;
struct PlaylistEntry;
struct Playlist;
struct ServiceItem;
struct SongTransition;
struct ServiceLinkRule;
struct ServiceLinkRules;
struct MxUPlanTime;
struct MxUPlanItemNote;
struct MxUPlanTimeOrder;
struct ServiceVersionStation;
struct ServiceItemChange;
struct ServiceVersion;
struct Service;
struct Overlay;
struct OutputAssignment;
struct OutputPreset;
struct MIDIDevice;
struct AlertPreset;
struct Theme;
struct StreamPresetDestination;
struct StreamDestination;
struct StreamRecordPreset;
struct SlideAction;
struct ActionCombo;
struct ScheduleCondition;
struct ScheduleTrigger;
struct ScheduleFolder;
struct SchedulerBoard;
struct ControlFolder;
struct ControlBoard;
struct GroupDefinition;
struct GroupPalette;
struct ImportLedgerEntry;
struct ImportLedger;
struct Transition;
struct EffectPreset;
struct EffectPresetBoard;
struct Effect;
struct TextLink;
struct MultiViewNode;
struct MultiViewTree;
struct ConfidenceLayout;
struct NoteRun;
struct NoteListItem;
struct NoteSlideRef;
struct NoteBlock;
struct NoteBody;
struct OverrideDesign;
struct SlideAnchor;
struct NoteMadeBox;
struct NoteMadeSlide;
struct NoteMadePassage;
struct NotePendingUpdate;
struct SlideVersion;
struct NoteDocument;
struct NoteSkippedUpdate;
struct NoteMediaImport;
struct StationSettings;
struct SlideBuildingSettings;
struct FontFile;
struct WorkspaceSettings;
struct TrackChannel;
struct TrackChannelList;
struct TrackSetStem;
struct TrackSet;
struct LayerPlacement;
struct CustomLayer;

enum class SlideObjectKind { Text, Media, Shape, LiveInput };
QString toString(SlideObjectKind value);
SlideObjectKind SlideObjectKindFromString(const QString& text);

enum class BlendMode { Normal, Multiply, Screen, Add };
QString toString(BlendMode value);
BlendMode BlendModeFromString(const QString& text);

enum class FillKind { None, Solid, LinearGradient, Media };
QString toString(FillKind value);
FillKind FillKindFromString(const QString& text);

enum class ShapeKind { Rectangle, RoundedRectangle, Ellipse, Path };
QString toString(ShapeKind value);
ShapeKind ShapeKindFromString(const QString& text);

enum class ShapeTextPlacement { Inside, EdgeOutside, EdgeInside };
QString toString(ShapeTextPlacement value);
ShapeTextPlacement ShapeTextPlacementFromString(const QString& text);

enum class TickerDirection { RightToLeft, LeftToRight };
QString toString(TickerDirection value);
TickerDirection TickerDirectionFromString(const QString& text);

enum class TextPathSide { Outside, Inside };
QString toString(TextPathSide value);
TextPathSide TextPathSideFromString(const QString& text);

enum class MediaScaleMode { Fill, Fit, Stretch, ScaleAndBlur };
QString toString(MediaScaleMode value);
MediaScaleMode MediaScaleModeFromString(const QString& text);

enum class TextHorizontalAlignment { Left, Center, Right };
QString toString(TextHorizontalAlignment value);
TextHorizontalAlignment TextHorizontalAlignmentFromString(const QString& text);

enum class TextVerticalAlignment { Top, Middle, Bottom };
QString toString(TextVerticalAlignment value);
TextVerticalAlignment TextVerticalAlignmentFromString(const QString& text);

enum class TextTransform { None, Uppercase };
QString toString(TextTransform value);
TextTransform TextTransformFromString(const QString& text);

enum class StrokeDashKind { Solid, Dashed, Dotted };
QString toString(StrokeDashKind value);
StrokeDashKind StrokeDashKindFromString(const QString& text);

enum class TextLineFillWidthMode { FullWidth, LineWidth, MaxLineWidth };
QString toString(TextLineFillWidthMode value);
TextLineFillWidthMode TextLineFillWidthModeFromString(const QString& text);

enum class ChordNotation { Chords, Numbers, Numerals, DoReMi };
QString toString(ChordNotation value);
ChordNotation ChordNotationFromString(const QString& text);

enum class VisibilityMatch { All, Any, None };
QString toString(VisibilityMatch value);
VisibilityMatch VisibilityMatchFromString(const QString& text);

enum class VisibilityConditionKind { Timer, VideoCountdown, AudioPlayback, LiveInput, Capture, ObjectText };
QString toString(VisibilityConditionKind value);
VisibilityConditionKind VisibilityConditionKindFromString(const QString& text);

enum class VisibilityConditionState { HasTimeRemaining, HasExpired, IsRunning, IsNotRunning, IsActive, IsInactive, IsConnected, IsDisconnected, HasText, HasNoText };
QString toString(VisibilityConditionState value);
VisibilityConditionState VisibilityConditionStateFromString(const QString& text);

enum class AnimationKind { In, Out, Emphasis, Morph };
QString toString(AnimationKind value);
AnimationKind AnimationKindFromString(const QString& text);

enum class AnimationTrigger { OnClick, WithPrevious, AfterPrevious, OnDismiss };
QString toString(AnimationTrigger value);
AnimationTrigger AnimationTriggerFromString(const QString& text);

enum class StepAnimation { Fade, Move, Scale, Wipe, Blur, Burn, Glitch, Draw, Type, Pulse, Color };
QString toString(StepAnimation value);
StepAnimation StepAnimationFromString(const QString& text);

enum class BlockScrollAxis { Up, Down, Left, Right };
QString toString(BlockScrollAxis value);
BlockScrollAxis BlockScrollAxisFromString(const QString& text);

enum class AnimationRamp { None, In, Out, Both };
QString toString(AnimationRamp value);
AnimationRamp AnimationRampFromString(const QString& text);

enum class AnimationEdge { Left, Right, Top, Bottom };
QString toString(AnimationEdge value);
AnimationEdge AnimationEdgeFromString(const QString& text);

enum class VideoPushAlignment { Center, Left, Right, Top, Bottom };
QString toString(VideoPushAlignment value);
VideoPushAlignment VideoPushAlignmentFromString(const QString& text);

enum class VideoPushMode { Fill, Fit, BlurBackground };
QString toString(VideoPushMode value);
VideoPushMode VideoPushModeFromString(const QString& text);

enum class KeystoneMode { Perspective, Stretch };
QString toString(KeystoneMode value);
KeystoneMode KeystoneModeFromString(const QString& text);

enum class TiltPivot { Top, Center, Bottom };
QString toString(TiltPivot value);
TiltPivot TiltPivotFromString(const QString& text);

enum class CueMediaLayer { LoopingVideos, StillGraphics, Videos };
QString toString(CueMediaLayer value);
CueMediaLayer CueMediaLayerFromString(const QString& text);

enum class CueMediaMode { SlideOnly, UntilReplaced };
QString toString(CueMediaMode value);
CueMediaMode CueMediaModeFromString(const QString& text);

enum class MediaEndFade { Black, Clear };
QString toString(MediaEndFade value);
MediaEndFade MediaEndFadeFromString(const QString& text);

enum class PresentationOriginSource { MadeHere, ProPresenter, PlanningCenterChart, PlanningCenterLyrics, SongSelect, LyricsFile, ChartFile, PastedLyrics, SlidesFile, Duplicate };
QString toString(PresentationOriginSource value);
PresentationOriginSource PresentationOriginSourceFromString(const QString& text);

enum class PresentationKind { Song, Deck };
QString toString(PresentationKind value);
PresentationKind PresentationKindFromString(const QString& text);

enum class MediaKind { Image, Video };
QString toString(MediaKind value);
MediaKind MediaKindFromString(const QString& text);

enum class MediaClassification { Foreground, Background };
QString toString(MediaClassification value);
MediaClassification MediaClassificationFromString(const QString& text);

enum class MediaFileStatus { Ready, NeedsTranscode, Transcoding, TranscodeFailed };
QString toString(MediaFileStatus value);
MediaFileStatus MediaFileStatusFromString(const QString& text);

enum class PlaylistRefKind { Media, Audio };
QString toString(PlaylistRefKind value);
PlaylistRefKind PlaylistRefKindFromString(const QString& text);

enum class PlaybackMode { PlayAll, LoopPlaylist, LoopSingle };
QString toString(PlaybackMode value);
PlaybackMode PlaybackModeFromString(const QString& text);

enum class PlaylistKind { Media, Audio };
QString toString(PlaylistKind value);
PlaylistKind PlaylistKindFromString(const QString& text);

enum class ServiceItemKind { Presentation, Media, Audio, Playlist, Header, Info };
QString toString(ServiceItemKind value);
ServiceItemKind ServiceItemKindFromString(const QString& text);

enum class OutputTargetKind { Display, PlaceholderScreen };
QString toString(OutputTargetKind value);
OutputTargetKind OutputTargetKindFromString(const QString& text);

enum class MIDIDeviceItemDirection { Input, Output, Both };
QString toString(MIDIDeviceItemDirection value);
MIDIDeviceItemDirection MIDIDeviceItemDirectionFromString(const QString& text);

enum class AlertBehavior { Persist, Flash };
QString toString(AlertBehavior value);
AlertBehavior AlertBehaviorFromString(const QString& text);

enum class AlertTarget { Confidence, Audience, Both };
QString toString(AlertTarget value);
AlertTarget AlertTargetFromString(const QString& text);

enum class StreamTransport { Rtmp, Rtmps, Srt, Hls };
QString toString(StreamTransport value);
StreamTransport StreamTransportFromString(const QString& text);

enum class StreamVideoCodec { H264, Hevc };
QString toString(StreamVideoCodec value);
StreamVideoCodec StreamVideoCodecFromString(const QString& text);

enum class StreamPresetKind { Stream, RecordOnly };
QString toString(StreamPresetKind value);
StreamPresetKind StreamPresetKindFromString(const QString& text);

enum class StreamSourceKind { Screen, MediaItem, LatestRecording };
QString toString(StreamSourceKind value);
StreamSourceKind StreamSourceKindFromString(const QString& text);

enum class CaptureSourceKind { Camera, Ndi, Decklink };
QString toString(CaptureSourceKind value);
CaptureSourceKind CaptureSourceKindFromString(const QString& text);

enum class SlideActionKind { ClearLayer, ClearAll, ClearAudio, ClearSignage, SwitchOutputPreset, FireMedia, FireAlert, DismissAlert, TimerStart, TimerPause, TimerReset, TimerConfigure, MidiOut, FireCombo, CaptureStart, CaptureStop, FirePresentation, SetConfidenceLayout, FireOverlay, DismissOverlay, FireLiveInput, SetSignage, SetScreenSource, EnableAudioInput, DisableAudioInput, FireAudio, FireAudioPlaylist };
QString toString(SlideActionKind value);
SlideActionKind SlideActionKindFromString(const QString& text);

enum class MIDIMessageKind { NoteOn, ControlChange };
QString toString(MIDIMessageKind value);
MIDIMessageKind MIDIMessageKindFromString(const QString& text);

enum class TimerMode { Countdown, CountdownToTime, CountUp };
QString toString(TimerMode value);
TimerMode TimerModeFromString(const QString& text);

enum class ScheduleConditionKind { Weekly, OneTime, TimerReaches };
QString toString(ScheduleConditionKind value);
ScheduleConditionKind ScheduleConditionKindFromString(const QString& text);

enum class ScheduleConditionLogic { Any, All };
QString toString(ScheduleConditionLogic value);
ScheduleConditionLogic ScheduleConditionLogicFromString(const QString& text);

enum class TransitionKind { Cut, Dissolve, FadeBlack, FadeWhite, FadeColor, BlurDissolve, FilmBurn };
QString toString(TransitionKind value);
TransitionKind TransitionKindFromString(const QString& text);

enum class MaskMode { In, Out };
QString toString(MaskMode value);
MaskMode MaskModeFromString(const QString& text);

enum class EffectKind { Blur, ColorAdjust, HueRotate, Invert, Posterize, Pixelate, Vignette, Warp, Echo, Scatter, StainedGlass, Grain, GhostTrails };
QString toString(EffectKind value);
EffectKind EffectKindFromString(const QString& text);

enum class TextSourceKind { CurrentSlide, NextSlide, LastSlide, Clock, Timer, VideoCountdown, SlidePosition, CurrentServiceItem, NextServiceItem, StageMessage, CurrentGroup, CurrentPresentation, NextServiceTitle, Timecode, VideoMarkName };
QString toString(TextSourceKind value);
TextSourceKind TextSourceKindFromString(const QString& text);

enum class TimerTextFormat { Digits, Abbreviated, Words };
QString toString(TimerTextFormat value);
TimerTextFormat TimerTextFormatFromString(const QString& text);

enum class VideoCountdownTarget { End, NextMark, NamedMark };
QString toString(VideoCountdownTarget value);
VideoCountdownTarget VideoCountdownTargetFromString(const QString& text);

enum class MultiViewSplitAxis { Columns, Rows };
QString toString(MultiViewSplitAxis value);
MultiViewSplitAxis MultiViewSplitAxisFromString(const QString& text);

enum class MultiViewSourceKind { Empty, Screen, LiveInput, Media, Clock, Timer, VideoCountdown, Text };
QString toString(MultiViewSourceKind value);
MultiViewSourceKind MultiViewSourceKindFromString(const QString& text);

enum class NoteBlockType { Heading, Paragraph, List, TaskList, Quote, Code, Rule, Image, Attachment, SlideRef, Unknown };
QString toString(NoteBlockType value);
NoteBlockType NoteBlockTypeFromString(const QString& text);

template <typename T>
QJsonArray encodeList(const QVector<T>& values)
{
    QJsonArray array;
    for (const auto& value : values)
        array.append(QJsonValue::fromVariant(QVariant::fromValue(value)));
    return array;
}

template <typename T, typename Encode>
QJsonArray encodeList(const QVector<T>& values, Encode encode)
{
    QJsonArray array;
    for (const auto& value : values)
        array.append(encode(value));
    return array;
}

template <typename T>
QVector<T> decodeList(const QJsonValue& value)
{
    QVector<T> result;
    for (const QJsonValue& item : value.toArray()) {
        if constexpr (std::is_same_v<T, QString>) result.append(item.toString());
        else if constexpr (std::is_same_v<T, int>) result.append(item.toInt());
        else if constexpr (std::is_same_v<T, double>) result.append(item.toDouble());
        else if constexpr (std::is_same_v<T, bool>) result.append(item.toBool());
    }
    return result;
}

template <typename T, typename Decode>
QVector<T> decodeList(const QJsonValue& value, Decode decode)
{
    QVector<T> result;
    for (const QJsonValue& item : value.toArray())
        result.append(decode(item.toObject()));
    return result;
}

struct MediaSourceRect
{
    double x;
    double y;
    double width;
    double height;
};
QJsonObject toJson(const MediaSourceRect& value);
MediaSourceRect MediaSourceRectFromJson(const QJsonObject& object);

struct GradientStop
{
    QString colorHex;
    double position;
};
QJsonObject toJson(const GradientStop& value);
GradientStop GradientStopFromJson(const QJsonObject& object);

struct ObjectFill
{
    FillKind fillKind;
    std::optional<QString> colorHex;
    std::optional<double> gradientAngleDegrees;
    std::optional<QVector<GradientStop>> gradientStops;
    std::optional<QString> mediaId;
    std::optional<MediaScaleMode> mediaScaleMode;
    std::optional<MediaSourceRect> mediaSourceRect;
    std::optional<bool> loops;
    std::optional<CaptureSourceKind> captureSourceKind;
    std::optional<QString> captureSourceId;
    std::optional<QString> screenSourceId;
    std::optional<QString> liveInputId;
};
QJsonObject toJson(const ObjectFill& value);
ObjectFill ObjectFillFromJson(const QJsonObject& object);

struct ObjectStroke
{
    QString colorHex;
    double width;
    std::optional<StrokeDashKind> dashKind;
};
QJsonObject toJson(const ObjectStroke& value);
ObjectStroke ObjectStrokeFromJson(const QJsonObject& object);

struct ObjectShadow
{
    QString colorHex;
    double blurRadius;
    double offsetX;
    double offsetY;
};
QJsonObject toJson(const ObjectShadow& value);
ObjectShadow ObjectShadowFromJson(const QJsonObject& object);

struct LineStyleOverride
{
    int lineIndex;
    std::optional<QString> fontName;
    std::optional<double> fontSize;
    std::optional<QString> colorHex;
    std::optional<double> tracking;
    std::optional<double> firstLineIndent;
    std::optional<double> leftIndent;
    std::optional<double> rightIndent;
};
QJsonObject toJson(const LineStyleOverride& value);
LineStyleOverride LineStyleOverrideFromJson(const QJsonObject& object);

struct TextLineFill
{
    ObjectFill fill;
    std::optional<TextLineFillWidthMode> widthMode;
    std::optional<double> verticalPadding;
    std::optional<double> horizontalPadding;
    std::optional<double> verticalOffset;
    std::optional<double> horizontalOffset;
    std::optional<double> cornerRadius;
};
QJsonObject toJson(const TextLineFill& value);
TextLineFill TextLineFillFromJson(const QJsonObject& object);

struct ChordPlacement
{
    int line;
    int column;
    QString symbol;
};
QJsonObject toJson(const ChordPlacement& value);
ChordPlacement ChordPlacementFromJson(const QJsonObject& object);

struct BlockScroll
{
    std::optional<BlockScrollAxis> axis;
    double speed;
    std::optional<int> passes;
    std::optional<AnimationRamp> ramp;
    std::optional<bool> restAtEnd;
    std::optional<double> fadeTowardTop;
};
QJsonObject toJson(const BlockScroll& value);
BlockScroll BlockScrollFromJson(const QJsonObject& object);

struct TextStyle
{
    std::optional<QString> fontName;
    std::optional<double> fontSize;
    std::optional<QString> colorHex;
    std::optional<ObjectFill> fill;
    std::optional<double> tracking;
    std::optional<double> lineHeightMultiple;
    std::optional<TextHorizontalAlignment> horizontalAlignment;
    std::optional<TextVerticalAlignment> verticalAlignment;
    std::optional<TextTransform> textTransform;
    std::optional<bool> tabularFigures;
    std::optional<bool> autoShrink;
    std::optional<double> minFontSize;
    std::optional<bool> keepLinesWhole;
    std::optional<bool> pageOnClick;
    std::optional<bool> balancedWrap;
    std::optional<ObjectStroke> outline;
    std::optional<ObjectShadow> shadow;
    std::optional<QVector<LineStyleOverride>> lineStyles;
    std::optional<TextLineFill> lineFill;
    std::optional<QString> pathData;
    std::optional<double> tickerSpeed;
    std::optional<TickerDirection> tickerDirection;
    std::optional<TextPathSide> pathSide;
    std::optional<double> pathOffset;
    std::optional<int> tickerRepeat;
    std::optional<AnimationRamp> tickerRamp;
    std::optional<BlockScroll> scroll;
    std::optional<bool> tickerStream;
    std::optional<double> tickerGap;
    std::optional<QString> tickerSeparator;
    std::optional<double> wordSpacing;
    std::optional<double> insetTop;
    std::optional<double> insetLeft;
    std::optional<double> insetBottom;
    std::optional<double> insetRight;
    std::optional<double> firstLineIndent;
    std::optional<double> leftIndent;
    std::optional<double> rightIndent;
    std::optional<double> paragraphSpacing;
    std::optional<bool> showChords;
    std::optional<ChordNotation> chordNotation;
    std::optional<QString> chordColorHex;
    std::optional<bool> underline;
    std::optional<bool> strikethrough;
};
QJsonObject toJson(const TextStyle& value);
TextStyle TextStyleFromJson(const QJsonObject& object);

struct VisibilityCondition
{
    VisibilityConditionKind conditionKind;
    VisibilityConditionState state;
    std::optional<QString> timerId;
    std::optional<QString> objectId;
    std::optional<QString> liveInputId;
};
QJsonObject toJson(const VisibilityCondition& value);
VisibilityCondition VisibilityConditionFromJson(const QJsonObject& object);

struct TextStyleRun
{
    int line;
    int column;
    int length;
    std::optional<bool> underline;
    std::optional<bool> strikethrough;
    std::optional<QString> fontName;
    std::optional<double> fontSize;
    std::optional<QString> colorHex;
    std::optional<QString> highlightColorHex;
    std::optional<double> tracking;
    std::optional<TextTransform> textTransform;
};
QJsonObject toJson(const TextStyleRun& value);
TextStyleRun TextStyleRunFromJson(const QJsonObject& object);

struct KeepFromSlideOptions
{
    std::optional<bool> bold;
    std::optional<bool> italic;
    std::optional<bool> underline;
    std::optional<bool> strikethrough;
    std::optional<bool> sizeEmphasis;
    std::optional<bool> wordLetterSpacing;
    std::optional<bool> highlight;
    std::optional<bool> textColor;
};
QJsonObject toJson(const KeepFromSlideOptions& value);
KeepFromSlideOptions KeepFromSlideOptionsFromJson(const QJsonObject& object);

struct AnimationRange
{
    int line;
    int column;
    int length;
};
QJsonObject toJson(const AnimationRange& value);
AnimationRange AnimationRangeFromJson(const QJsonObject& object);

struct VideoPush
{
    std::optional<VideoPushAlignment> alignment;
    std::optional<VideoPushMode> mode;
    std::optional<double> zoom;
    std::optional<double> margin;
    std::optional<bool> backdrop;
    std::optional<double> blurRadius;
};
QJsonObject toJson(const VideoPush& value);
VideoPush VideoPushFromJson(const QJsonObject& object);

struct Effect
{
    EffectKind effectKind;
    std::optional<bool> enabled;
    std::optional<double> opacity;
    std::optional<double> radius;
    std::optional<double> amount;
    std::optional<double> scale;
    std::optional<double> speed;
    std::optional<double> fade;
    std::optional<double> smooth;
    std::optional<double> brightness;
    std::optional<double> contrast;
    std::optional<double> saturation;
    std::optional<double> hue;
};
QJsonObject toJson(const Effect& value);
Effect EffectFromJson(const QJsonObject& object);

struct TextLink
{
    TextSourceKind source;
    std::optional<QString> timerId;
    std::optional<QString> clockFormat;
    std::optional<bool> usesWarningColor;
    std::optional<int> maxLines;
    std::optional<bool> includeSteps;
    std::optional<bool> includeBuilds;
    std::optional<QString> sourceObjectName;
    std::optional<bool> showsVideoName;
    std::optional<QString> videoLayer;
    std::optional<TimerTextFormat> timerFormat;
    std::optional<QString> timerPattern;
    std::optional<VideoCountdownTarget> videoTarget;
    std::optional<QString> videoMarkName;
    std::optional<bool> countsUp;
};
QJsonObject toJson(const TextLink& value);
TextLink TextLinkFromJson(const QJsonObject& object);

struct SlideObject
{
    QString id;
    SlideObjectKind objectKind;
    QString name;
    QString text;
    std::optional<double> x;
    std::optional<double> y;
    std::optional<double> width;
    std::optional<double> height;
    std::optional<double> rotationDegrees;
    std::optional<bool> hidden;
    std::optional<VisibilityMatch> visibilityMatch;
    std::optional<QVector<VisibilityCondition>> visibilityConditions;
    std::optional<bool> flipHorizontal;
    std::optional<bool> flipVertical;
    std::optional<double> opacity;
    std::optional<BlendMode> blendMode;
    std::optional<QString> groupId;
    std::optional<QString> maskObjectId;
    std::optional<MaskMode> maskMode;
    std::optional<QVector<Effect>> effects;
    std::optional<bool> effectsApplyBelow;
    std::optional<TextLink> textLink;
    std::optional<TextStyle> textStyle;
    std::optional<QVector<ChordPlacement>> chords;
    std::optional<QVector<TextStyleRun>> styleRuns;
    std::optional<ShapeKind> shapeKind;
    std::optional<double> cornerRadius;
    std::optional<QString> pathData;
    std::optional<ShapeTextPlacement> shapeTextPlacement;
    std::optional<double> shapeTextCornerRadius;
    std::optional<ObjectFill> fill;
    std::optional<ObjectStroke> stroke;
    std::optional<ObjectShadow> shadow;
    std::optional<QString> mediaId;
    std::optional<MediaScaleMode> mediaScaleMode;
    std::optional<MediaSourceRect> mediaSourceRect;
    std::optional<bool> loops;
    std::optional<CaptureSourceKind> captureSourceKind;
    std::optional<QString> captureSourceId;
    std::optional<QString> screenSourceId;
    std::optional<QString> liveInputId;
    std::optional<KeepFromSlideOptions> keepFromSlide;
    std::optional<QVector<AnimationStep>> animationSteps;
    std::optional<QVector<AnimationStep>> builds;
    std::optional<double> tilt;
    std::optional<double> swing;
    std::optional<TiltPivot> tiltPivot;
    std::optional<double> keystoneTop;
    std::optional<double> keystoneBottom;
    std::optional<double> skewX;
    std::optional<double> skewY;
    std::optional<KeystoneMode> keystoneMode;
    std::optional<bool> photoSpot;
};
QJsonObject toJson(const SlideObject& value);
SlideObject SlideObjectFromJson(const QJsonObject& object);

struct AnimationStep
{
    QString id;
    AnimationKind kind;
    StepAnimation animation;
    AnimationTrigger trigger;
    std::optional<double> delaySeconds;
    double durationSeconds;
    std::optional<AnimationRamp> ramp;
    std::optional<bool> withFade;
    std::optional<QVector<AnimationRange>> ranges;
    std::optional<AnimationEdge> edge;
    std::optional<double> offsetX;
    std::optional<double> offsetY;
    std::optional<double> fromScale;
    std::optional<double> amount;
    std::optional<double> softEdge;
    std::optional<bool> cursor;
    std::optional<QString> colorHex;
    std::optional<bool> placeholderUnderline;
    std::optional<double> drawStart;
    std::optional<bool> reverse;
    std::optional<std::shared_ptr<SlideObject>> toObject;
    std::optional<VideoPush> videoPush;
    std::optional<std::shared_ptr<SlideObject>> fromObject;
};
QJsonObject toJson(const AnimationStep& value);
AnimationStep AnimationStepFromJson(const QJsonObject& object);

struct AnimationPreset
{
    QString id;
    QString name;
    QVector<AnimationStep> steps;
    std::optional<double> staggerSeconds;
    std::optional<BlockScroll> scroll;
    std::optional<double> tilt;
};
QJsonObject toJson(const AnimationPreset& value);
AnimationPreset AnimationPresetFromJson(const QJsonObject& object);

struct AnimationPresetBoard
{
    QString id;
    QVector<AnimationPreset> presets;
    std::optional<AnimationStep> defaultIn;
    std::optional<AnimationStep> defaultOut;
};
QJsonObject toJson(const AnimationPresetBoard& value);
AnimationPresetBoard AnimationPresetBoardFromJson(const QJsonObject& object);

struct CueMedia
{
    QString mediaId;
    std::optional<CueMediaMode> mode;
    std::optional<CueMediaLayer> layer;
    std::optional<bool> loops;
    std::optional<MediaClassification> classification;
    std::optional<MediaScaleMode> scaleMode;
    std::optional<MediaEndFade> endFade;
    std::optional<QString> layerId;
};
QJsonObject toJson(const CueMedia& value);
CueMedia CueMediaFromJson(const QJsonObject& object);

struct AutoAdvance
{
    double delaySeconds;
    std::optional<bool> loopToStart;
    std::optional<bool> afterPlayback;
};
QJsonObject toJson(const AutoAdvance& value);
AutoAdvance AutoAdvanceFromJson(const QJsonObject& object);

struct OverrideDesign
{
    QString themeId;
    QString themeSlideName;
};
QJsonObject toJson(const OverrideDesign& value);
OverrideDesign OverrideDesignFromJson(const QJsonObject& object);

struct SlideAction
{
    QString id;
    SlideActionKind kind;
    std::optional<QString> layer;
    std::optional<QString> presetId;
    std::optional<QString> mediaId;
    std::optional<QString> alertId;
    std::optional<QString> timerId;
    std::optional<TimerMode> timerMode;
    std::optional<double> timerDurationSeconds;
    std::optional<int> timerHour;
    std::optional<int> timerMinute;
    std::optional<QString> comboId;
    std::optional<MIDIMessageKind> midiKind;
    std::optional<int> midiChannel;
    std::optional<int> midiNumber;
    std::optional<int> midiValue;
    std::optional<QString> midiDeviceId;
    std::optional<QString> capturePresetId;
    std::optional<QString> capturePrivacy;
    std::optional<QString> presentationId;
    std::optional<int> slideIndex;
    std::optional<QString> confidenceLayoutId;
    std::optional<QString> confidenceScreenId;
    std::optional<QString> overlayId;
    std::optional<CaptureSourceKind> inputSourceKind;
    std::optional<QString> inputSourceId;
    std::optional<QString> liveInputId;
    std::optional<QString> audioInputId;
    std::optional<QString> playlistId;
    std::optional<QString> audioItemId;
    std::optional<QString> audioEntryId;
    std::optional<bool> audioRepeat;
    std::optional<double> delaySeconds;
};
QJsonObject toJson(const SlideAction& value);
SlideAction SlideActionFromJson(const QJsonObject& object);

struct SlideVersion
{
    QString at;
    QString reason;
    std::shared_ptr<Slide> slide;
};
QJsonObject toJson(const SlideVersion& value);
SlideVersion SlideVersionFromJson(const QJsonObject& object);

struct Transition
{
    TransitionKind transitionKind;
    std::optional<double> durationSeconds;
    std::optional<QString> colorHex;
};
QJsonObject toJson(const Transition& value);
Transition TransitionFromJson(const QJsonObject& object);

struct Slide
{
    QString id;
    QString name;
    QVector<SlideObject> objects;
    std::optional<CueMedia> background;
    std::optional<ObjectFill> backgroundFill;
    std::optional<QString> sectionId;
    std::optional<QString> folder;
    std::optional<QString> themeSlideName;
    std::optional<QString> themeId;
    std::optional<bool> unthemed;
    std::optional<QVector<OverrideDesign>> overrideDesigns;
    std::optional<QVector<SlideAction>> actions;
    std::optional<QString> notes;
    std::optional<AutoAdvance> autoAdvance;
    std::optional<Transition> transition;
    std::optional<QVector<QString>> animationOrder;
    std::optional<QVector<QString>> buildOrder;
    std::optional<bool> keepWords;
    std::optional<QVector<SlideVersion>> history;
};
QJsonObject toJson(const Slide& value);
Slide SlideFromJson(const QJsonObject& object);

struct PresentationSection
{
    QString id;
    QString name;
    std::optional<CueMedia> background;
    std::optional<QString> colorHex;
};
QJsonObject toJson(const PresentationSection& value);
PresentationSection PresentationSectionFromJson(const QJsonObject& object);

struct CCLIInfo
{
    std::optional<int> songNumber;
    std::optional<QString> songTitle;
    std::optional<QString> author;
    std::optional<QString> publisher;
    std::optional<int> copyrightYear;
    std::optional<QString> copyright;
};
QJsonObject toJson(const CCLIInfo& value);
CCLIInfo CCLIInfoFromJson(const QJsonObject& object);

struct Arrangement
{
    QString id;
    QString name;
    QVector<QString> sectionIds;
};
QJsonObject toJson(const Arrangement& value);
Arrangement ArrangementFromJson(const QJsonObject& object);

struct PresentationOrigin
{
    PresentationOriginSource source;
    std::optional<QString> detail;
    std::optional<QString> createdAt;
};
QJsonObject toJson(const PresentationOrigin& value);
PresentationOrigin PresentationOriginFromJson(const QJsonObject& object);

struct ClipFade
{
    double seconds;
    std::optional<QString> shape;
    std::optional<double> midpoint;
    std::optional<QString> placement;
};
QJsonObject toJson(const ClipFade& value);
ClipFade ClipFadeFromJson(const QJsonObject& object);

struct TimelineCue
{
    QString id;
    QString lane;
    double at;
    std::optional<double> duration;
    std::optional<QString> sectionId;
    std::optional<int> sectionOccurrence;
    std::optional<QString> slideId;
    std::optional<QString> mediaId;
    std::optional<QString> overlayId;
    std::optional<QString> alertId;
    std::optional<QString> liveInputId;
    std::optional<QVector<SlideAction>> actions;
    std::optional<double> inPoint;
    std::optional<ClipFade> fadeIn;
    std::optional<ClipFade> fadeOut;
    std::optional<bool> edgeFades;
};
QJsonObject toJson(const TimelineCue& value);
TimelineCue TimelineCueFromJson(const QJsonObject& object);

struct SongMapBlock
{
    std::optional<QString> sectionId;
    int occurrence;
    double start;
    double length;
    QVector<QString> audioSectionIds;
};
QJsonObject toJson(const SongMapBlock& value);
SongMapBlock SongMapBlockFromJson(const QJsonObject& object);

struct PresentationTimeline
{
    QString id;
    std::optional<QString> arrangementId;
    bool timecodeEnabled;
    int timecodeStart;
    std::optional<double> length;
    QVector<TimelineCue> cues;
    std::optional<QVector<SongMapBlock>> mapLayout;
};
QJsonObject toJson(const PresentationTimeline& value);
PresentationTimeline PresentationTimelineFromJson(const QJsonObject& object);

struct AudioSection
{
    QString id;
    QString name;
    double start;
    std::optional<QString> sectionId;
};
QJsonObject toJson(const AudioSection& value);
AudioSection AudioSectionFromJson(const QJsonObject& object);

struct SongMap
{
    QVector<TimelineCue> recording;
    QVector<AudioSection> sections;
    std::optional<QString> source;
};
QJsonObject toJson(const SongMap& value);
SongMap SongMapFromJson(const QJsonObject& object);

struct Presentation
{
    QString id;
    QString name;
    PresentationKind presentationKind;
    QString themeId;
    std::optional<QString> folder;
    std::optional<QString> folderId;
    QVector<Slide> slides;
    std::optional<int> canvasWidth;
    std::optional<int> canvasHeight;
    std::optional<CueMedia> background;
    std::optional<ObjectFill> backgroundFill;
    std::optional<QVector<PresentationSection>> sections;
    std::optional<QVector<Arrangement>> arrangements;
    std::optional<QString> defaultArrangementId;
    std::optional<QString> reflowSource;
    std::optional<CCLIInfo> ccli;
    std::optional<QString> chordProSource;
    std::optional<QString> musicKey;
    std::optional<AutoAdvance> autoAdvance;
    std::optional<Transition> transition;
    std::optional<QString> displayKey;
    std::optional<PresentationOrigin> origin;
    std::optional<QVector<PresentationTimeline>> timelines;
    std::optional<SongMap> songMap;
};
QJsonObject toJson(const Presentation& value);
Presentation PresentationFromJson(const QJsonObject& object);

struct VideoMark
{
    QString id;
    QString name;
    double at;
    QVector<SlideAction> actions;
    std::optional<QString> colorHex;
};
QJsonObject toJson(const VideoMark& value);
VideoMark VideoMarkFromJson(const QJsonObject& object);

struct MediaItem
{
    QString id;
    QString name;
    MediaKind mediaKind;
    MediaClassification classification;
    QString fileHash;
    QString fileName;
    MediaFileStatus fileStatus;
    QString statusDetail;
    QVector<QString> tags;
    bool favorite;
    QVector<QString> collections;
    bool loops;
    std::optional<double> inPoint;
    std::optional<double> outPoint;
    std::optional<double> playRate;
    std::optional<QVector<Effect>> effects;
    std::optional<Transition> transition;
    std::optional<double> durationSeconds;
    std::optional<int> pixelWidth;
    std::optional<int> pixelHeight;
    std::optional<QString> folder;
    std::optional<QString> folderId;
    std::optional<double> recordedAt;
    std::optional<double> importedAt;
    std::optional<QString> recordedByPresetId;
    std::optional<QVector<SlideAction>> actions;
    std::optional<AutoAdvance> autoAdvance;
    std::optional<QVector<VideoMark>> marks;
};
QJsonObject toJson(const MediaItem& value);
MediaItem MediaItemFromJson(const QJsonObject& object);

struct AudioItem
{
    QString id;
    QString name;
    QString fileHash;
    QString fileName;
    QVector<QString> tags;
    bool favorite;
    std::optional<double> inPoint;
    std::optional<double> outPoint;
    std::optional<double> durationSeconds;
    std::optional<QString> folder;
    std::optional<QString> folderId;
};
QJsonObject toJson(const AudioItem& value);
AudioItem AudioItemFromJson(const QJsonObject& object);

struct PlaylistEntry
{
    QString id;
    PlaylistRefKind refKind;
    QString refId;
};
QJsonObject toJson(const PlaylistEntry& value);
PlaylistEntry PlaylistEntryFromJson(const QJsonObject& object);

struct Playlist
{
    QString id;
    QString name;
    std::optional<PlaylistKind> playlistKind;
    QVector<PlaylistEntry> entries;
    PlaybackMode playbackMode;
    std::optional<bool> shuffle;
    std::optional<double> crossfadeSeconds;
};
QJsonObject toJson(const Playlist& value);
Playlist PlaylistFromJson(const QJsonObject& object);

struct MxUPlanItemNote
{
    std::optional<QString> label;
    QString text;
    std::optional<QString> kind;
    std::optional<QVector<QString>> positions;
};
QJsonObject toJson(const MxUPlanItemNote& value);
MxUPlanItemNote MxUPlanItemNoteFromJson(const QJsonObject& object);

struct SongTransition
{
    QString kind;
    std::optional<double> seconds;
};
QJsonObject toJson(const SongTransition& value);
SongTransition SongTransitionFromJson(const QJsonObject& object);

struct ServiceItem
{
    QString id;
    ServiceItemKind itemKind;
    QString name;
    QString refId;
    std::optional<QString> arrangementId;
    std::optional<QString> colorHex;
    std::optional<QString> outputPresetId;
    std::optional<QString> mxuItemHexId;
    std::optional<int> duration;
    std::optional<QString> mxuKind;
    std::optional<QVector<QString>> excludedTimeHexIds;
    std::optional<bool> hiddenInPresenter;
    std::optional<QString> mxuSongTitle;
    std::optional<int> mxuCcliNumber;
    std::optional<QString> mxuArrangementName;
    std::optional<QString> mxuSongAuthor;
    std::optional<QString> mxuMultiTracksUrl;
    std::optional<QVector<MxUPlanItemNote>> mxuNotes;
    std::optional<QString> mxuMessageNotesDocumentHexId;
    std::optional<QString> mxuMessageNotesSubmittedAt;
    std::optional<QString> mxuMessageNotesOnReady;
    std::optional<QString> mxuMessageNotesDeckDocId;
    std::optional<QString> mxuPcoItemId;
    std::optional<QString> mxuPcoSongId;
    std::optional<QString> mxuPcoArrangementId;
    std::optional<QString> mxuPcoKeyId;
    std::optional<QString> mxuSongKey;
    std::optional<QString> mxuDescription;
    std::optional<QString> mxuServicePosition;
    std::optional<double> mxuBpm;
    std::optional<QString> mxuTimeSignature;
    std::optional<QString> mxuSongKeyApplied;
    std::optional<SongTransition> transition;
};
QJsonObject toJson(const ServiceItem& value);
ServiceItem ServiceItemFromJson(const QJsonObject& object);

struct ServiceLinkRule
{
    QString id;
    QString normalizedName;
    std::optional<QString> serviceTypeName;
    ServiceItemKind itemKind;
    QString refId;
};
QJsonObject toJson(const ServiceLinkRule& value);
ServiceLinkRule ServiceLinkRuleFromJson(const QJsonObject& object);

struct ServiceLinkRules
{
    QString id;
    QVector<ServiceLinkRule> rules;
};
QJsonObject toJson(const ServiceLinkRules& value);
ServiceLinkRules ServiceLinkRulesFromJson(const QJsonObject& object);

struct MxUPlanTime
{
    QString hexId;
    QString name;
    std::optional<QString> startsAt;
    std::optional<bool> isRehearsal;
};
QJsonObject toJson(const MxUPlanTime& value);
MxUPlanTime MxUPlanTimeFromJson(const QJsonObject& object);

struct MxUPlanTimeOrder
{
    QString timeHexId;
    QVector<QString> itemHexIds;
};
QJsonObject toJson(const MxUPlanTimeOrder& value);
MxUPlanTimeOrder MxUPlanTimeOrderFromJson(const QJsonObject& object);

struct ServiceVersionStation
{
    QString id;
    QString name;
};
QJsonObject toJson(const ServiceVersionStation& value);
ServiceVersionStation ServiceVersionStationFromJson(const QJsonObject& object);

struct ServiceItemChange
{
    QString itemId;
    std::optional<QString> after;
    std::optional<bool> hidden;
    std::optional<ServiceItemKind> itemKind;
    std::optional<QString> refId;
    std::optional<QString> name;
    std::optional<QString> arrangementId;
    std::optional<QString> outputPresetId;
};
QJsonObject toJson(const ServiceItemChange& value);
ServiceItemChange ServiceItemChangeFromJson(const QJsonObject& object);

struct ServiceVersion
{
    QString id;
    QString name;
    std::optional<QVector<ServiceVersionStation>> stations;
    std::optional<QVector<ServiceItem>> added;
    std::optional<QVector<ServiceItemChange>> changes;
};
QJsonObject toJson(const ServiceVersion& value);
ServiceVersion ServiceVersionFromJson(const QJsonObject& object);

struct Service
{
    QString id;
    QString name;
    QString serviceDate;
    QVector<ServiceItem> items;
    std::optional<QString> origin;
    std::optional<QString> mxuPlanHexId;
    std::optional<QString> mxuServiceTypeName;
    std::optional<QString> mxuPlanVersion;
    std::optional<QVector<MxUPlanTime>> mxuPlanTimes;
    std::optional<QVector<MxUPlanTimeOrder>> mxuTimeOrders;
    std::optional<QVector<QString>> mxuSyncedOrder;
    std::optional<QString> mxuDerivedName;
    std::optional<bool> mxuSyncPaused;
    std::optional<QVector<ServiceVersion>> versions;
    std::optional<bool> timecodeByOrder;
};
QJsonObject toJson(const Service& value);
Service ServiceFromJson(const QJsonObject& object);

struct Overlay
{
    QString id;
    QString name;
    QVector<SlideObject> objects;
    std::optional<QString> folder;
    std::optional<QString> folderId;
    std::optional<QString> layer;
    std::optional<QVector<QString>> animationOrder;
    std::optional<QVector<QString>> buildOrder;
};
QJsonObject toJson(const Overlay& value);
Overlay OverlayFromJson(const QJsonObject& object);

struct OutputAssignment
{
    OutputTargetKind targetKind;
    QString targetId;
    QVector<QString> enabledLayers;
    std::optional<QString> slideThemeId;
    std::optional<QString> slideThemeFolder;
    std::optional<QString> slideThemeSlideId;
    std::optional<QVector<QString>> maskIds;
};
QJsonObject toJson(const OutputAssignment& value);
OutputAssignment OutputAssignmentFromJson(const QJsonObject& object);

struct CustomLayer
{
    QString id;
    QString name;
    std::optional<QString> above;
};
QJsonObject toJson(const CustomLayer& value);
CustomLayer CustomLayerFromJson(const QJsonObject& object);

struct LayerPlacement
{
    QString layerId;
    double x;
    double y;
    double width;
    double height;
    std::optional<MediaScaleMode> scale;
};
QJsonObject toJson(const LayerPlacement& value);
LayerPlacement LayerPlacementFromJson(const QJsonObject& object);

struct OutputPreset
{
    QString id;
    QString name;
    QVector<OutputAssignment> assignments;
    std::optional<QVector<LayerPlacement>> placements;
    std::optional<QVector<CustomLayer>> layers;
};
QJsonObject toJson(const OutputPreset& value);
OutputPreset OutputPresetFromJson(const QJsonObject& object);

struct MIDIDevice
{
    QString id;
    QString name;
    std::optional<MIDIDeviceItemDirection> direction;
    std::optional<int> channel;
    std::optional<bool> enabled;
    std::optional<QVector<QString>> sourceNames;
    std::optional<QVector<QString>> destinationNames;
    std::optional<bool> autoReconnect;
};
QJsonObject toJson(const MIDIDevice& value);
MIDIDevice MIDIDeviceFromJson(const QJsonObject& object);

struct AlertPreset
{
    QString id;
    QString name;
    QString message;
    AlertBehavior behavior;
    std::optional<AlertTarget> target;
    std::optional<QString> themeId;
    std::optional<QString> layer;
};
QJsonObject toJson(const AlertPreset& value);
AlertPreset AlertPresetFromJson(const QJsonObject& object);

struct Theme
{
    QString id;
    QString name;
    QString fontFamily;
    double fontSize;
    QString textColorHex;
    QString backgroundColorHex;
    std::optional<QVector<Slide>> slides;
};
QJsonObject toJson(const Theme& value);
Theme ThemeFromJson(const QJsonObject& object);

struct StreamPresetDestination
{
    QString id;
    QString name;
    StreamTransport transport;
    QString url;
    std::optional<QString> streamKey;
    std::optional<QString> linkedPlatform;
    std::optional<QString> linkedTargetId;
    std::optional<StreamVideoCodec> videoCodec;
    std::optional<int> maxHeight;
    std::optional<bool> hdr;
    std::optional<QString> privacy;
    std::optional<QString> canvasScreenId;
    std::optional<int> width;
    std::optional<int> height;
    std::optional<int> frameRate;
};
QJsonObject toJson(const StreamPresetDestination& value);
StreamPresetDestination StreamPresetDestinationFromJson(const QJsonObject& object);

struct StreamDestination
{
    QString id;
    QString name;
    StreamTransport transport;
    QString url;
    std::optional<QString> streamKey;
    std::optional<QString> linkedPlatform;
    std::optional<QString> linkedTargetId;
    std::optional<QString> linkedTargetName;
    std::optional<StreamVideoCodec> videoCodec;
    std::optional<int> maxHeight;
    std::optional<bool> hdr;
    std::optional<QString> defaultPrivacy;
    std::optional<QString> canvasScreenId;
    std::optional<int> width;
    std::optional<int> height;
    std::optional<int> frameRate;
};
QJsonObject toJson(const StreamDestination& value);
StreamDestination StreamDestinationFromJson(const QJsonObject& object);

struct StreamRecordPreset
{
    QString id;
    QString name;
    QVector<StreamPresetDestination> destinations;
    std::optional<QVector<QString>> destinationIds;
    std::optional<StreamPresetKind> presetKind;
    std::optional<int> width;
    std::optional<int> height;
    std::optional<int> frameRate;
    std::optional<int> videoBitrateKbps;
    std::optional<bool> adaptBitrate;
    std::optional<int> minBitrateKbps;
    std::optional<QString> canvasScreenId;
    std::optional<bool> recordWhileStreaming;
    std::optional<QString> recordCodec;
    std::optional<QString> title;
    std::optional<QString> streamDescription;
    std::optional<QString> recordFolder;
    std::optional<QString> audioInputUid;
    std::optional<bool> audioIncludesProgram;
    std::optional<QString> audioInputId;
    std::optional<QString> audioMixId;
    std::optional<int> audioDelayMs;
    std::optional<StreamSourceKind> sourceKind;
    std::optional<QString> sourceMediaId;
    std::optional<QString> sourceFolder;
    std::optional<int> sourceMaxAgeHours;
    std::optional<QString> recordLibraryFolder;
    std::optional<QString> recordExportFolder;
};
QJsonObject toJson(const StreamRecordPreset& value);
StreamRecordPreset StreamRecordPresetFromJson(const QJsonObject& object);

struct ActionCombo
{
    QString id;
    QString name;
    QVector<SlideAction> actions;
    std::optional<QString> colorHex;
    std::optional<QString> iconName;
    std::optional<bool> runOnStartup;
};
QJsonObject toJson(const ActionCombo& value);
ActionCombo ActionComboFromJson(const QJsonObject& object);

struct ScheduleCondition
{
    QString id;
    ScheduleConditionKind kind;
    std::optional<QVector<int>> days;
    std::optional<QString> timeOfDay;
    std::optional<QString> date;
    std::optional<QString> timerId;
    std::optional<double> timerSeconds;
    std::optional<QVector<QString>> excludedDates;
};
QJsonObject toJson(const ScheduleCondition& value);
ScheduleCondition ScheduleConditionFromJson(const QJsonObject& object);

struct ScheduleTrigger
{
    QString id;
    QString name;
    QVector<ScheduleCondition> conditions;
    QVector<SlideAction> actions;
    std::optional<ScheduleConditionLogic> conditionLogic;
    std::optional<bool> enabled;
    std::optional<QString> notes;
    std::optional<bool> archived;
    std::optional<QString> disabledUntil;
    std::optional<QString> enabledUntil;
};
QJsonObject toJson(const ScheduleTrigger& value);
ScheduleTrigger ScheduleTriggerFromJson(const QJsonObject& object);

struct ScheduleFolder
{
    QString id;
    QString name;
    std::optional<bool> enabled;
    std::optional<bool> collapsed;
    QVector<QString> triggerIds;
};
QJsonObject toJson(const ScheduleFolder& value);
ScheduleFolder ScheduleFolderFromJson(const QJsonObject& object);

struct SchedulerBoard
{
    QString id;
    QVector<QString> nodes;
    QVector<ScheduleFolder> folders;
};
QJsonObject toJson(const SchedulerBoard& value);
SchedulerBoard SchedulerBoardFromJson(const QJsonObject& object);

struct ControlFolder
{
    QString id;
    QString name;
    std::optional<bool> collapsed;
    QVector<QString> itemIds;
};
QJsonObject toJson(const ControlFolder& value);
ControlFolder ControlFolderFromJson(const QJsonObject& object);

struct ControlBoard
{
    QString id;
    QVector<QString> nodes;
    QVector<ControlFolder> folders;
};
QJsonObject toJson(const ControlBoard& value);
ControlBoard ControlBoardFromJson(const QJsonObject& object);

struct GroupDefinition
{
    QString id;
    QString name;
    QString colorHex;
    std::optional<QString> hotKey;
};
QJsonObject toJson(const GroupDefinition& value);
GroupDefinition GroupDefinitionFromJson(const QJsonObject& object);

struct GroupPalette
{
    QString id;
    QVector<GroupDefinition> groups;
};
QJsonObject toJson(const GroupPalette& value);
GroupPalette GroupPaletteFromJson(const QJsonObject& object);

struct ImportLedgerEntry
{
    QString docId;
    QString hash;
};
QJsonObject toJson(const ImportLedgerEntry& value);
ImportLedgerEntry ImportLedgerEntryFromJson(const QJsonObject& object);

struct ImportLedger
{
    QString id;
    QVector<ImportLedgerEntry> entries;
};
QJsonObject toJson(const ImportLedger& value);
ImportLedger ImportLedgerFromJson(const QJsonObject& object);

struct EffectPreset
{
    QString id;
    QString name;
    QVector<Effect> effects;
};
QJsonObject toJson(const EffectPreset& value);
EffectPreset EffectPresetFromJson(const QJsonObject& object);

struct EffectPresetBoard
{
    QString id;
    QVector<EffectPreset> presets;
};
QJsonObject toJson(const EffectPresetBoard& value);
EffectPresetBoard EffectPresetBoardFromJson(const QJsonObject& object);

struct MultiViewNode
{
    QString id;
    std::optional<MultiViewSplitAxis> axis;
    std::optional<QVector<QString>> children;
    std::optional<QVector<double>> fractions;
    std::optional<MultiViewSourceKind> sourceKind;
    std::optional<QString> screenSourceId;
    std::optional<QString> screenSourceName;
    std::optional<QString> liveInputId;
    std::optional<QString> mediaId;
    std::optional<QString> timerId;
    std::optional<QString> text;
    std::optional<QString> label;
    std::optional<MediaScaleMode> scaleMode;
    std::optional<bool> matchSourceShape;
};
QJsonObject toJson(const MultiViewNode& value);
MultiViewNode MultiViewNodeFromJson(const QJsonObject& object);

struct MultiViewTree
{
    QString rootId;
    QVector<MultiViewNode> nodes;
};
QJsonObject toJson(const MultiViewTree& value);
MultiViewTree MultiViewTreeFromJson(const QJsonObject& object);

struct ConfidenceLayout
{
    QString id;
    QString name;
    QVector<SlideObject> objects;
    std::optional<QString> folder;
    std::optional<QString> folderId;
    std::optional<int> canvasWidth;
    std::optional<int> canvasHeight;
    std::optional<QVector<QString>> animationOrder;
    std::optional<QVector<QString>> buildOrder;
    std::optional<MultiViewTree> multiView;
};
QJsonObject toJson(const ConfidenceLayout& value);
ConfidenceLayout ConfidenceLayoutFromJson(const QJsonObject& object);

struct NoteRun
{
    QString text;
    std::optional<bool> bold;
    std::optional<bool> italic;
    std::optional<bool> underline;
    std::optional<bool> strike;
    std::optional<bool> code;
    std::optional<QString> highlight;
    std::optional<QString> color;
    std::optional<QString> size;
    std::optional<QString> href;
    std::optional<QString> slideGroup;
    std::optional<QString> slideType;
    std::optional<QString> slideId;
    std::optional<QString> slideState;
    std::optional<QString> commentId;
};
QJsonObject toJson(const NoteRun& value);
NoteRun NoteRunFromJson(const QJsonObject& object);

struct NoteSlideRef
{
    std::optional<QString> presentationId;
    std::optional<QString> slideId;
    std::optional<int> slideIndex;
    std::optional<QString> ppIntegrationHexId;
    std::optional<QString> ppPresentationUuid;
    std::optional<QString> ppPlaylistUuid;
    std::optional<int> ppItemIndex;
    std::optional<int> ppSlideIndex;
    std::optional<QString> presentationName;
    std::optional<QString> slideText;
    std::optional<QString> slideLabel;
    std::optional<QString> slideLabelColor;
    std::optional<QString> slideNotes;
    std::optional<QString> thumbnailUrl;
    std::optional<bool> showThumbnail;
    std::optional<bool> showText;
    std::optional<bool> showNotes;
    std::optional<bool> showLabels;
    std::optional<bool> showName;
    std::optional<bool> showNumber;
    std::optional<int> width;
    std::optional<bool> placedByHand;
};
QJsonObject toJson(const NoteSlideRef& value);
NoteSlideRef NoteSlideRefFromJson(const QJsonObject& object);

struct NoteBlock
{
    NoteBlockType type;
    std::optional<int> level;
    std::optional<QVector<NoteRun>> runs;
    std::optional<bool> ordered;
    std::optional<QVector<NoteListItem>> items;
    std::optional<QVector<NoteBlock>> blocks;
    std::optional<QString> language;
    std::optional<QString> text;
    std::optional<QString> url;
    std::optional<int> width;
    std::optional<QString> alt;
    std::optional<QString> attachmentKind;
    std::optional<QString> hexId;
    std::optional<QString> filename;
    std::optional<NoteSlideRef> slide;
    std::optional<QString> slideGroup;
    std::optional<QString> slideType;
    std::optional<QString> slideId;
    std::optional<QString> slideState;
};
QJsonObject toJson(const NoteBlock& value);
NoteBlock NoteBlockFromJson(const QJsonObject& object);

struct NoteListItem
{
    QVector<NoteRun> runs;
    std::optional<bool> checked;
    std::optional<QVector<NoteBlock>> blocks;
};
QJsonObject toJson(const NoteListItem& value);
NoteListItem NoteListItemFromJson(const QJsonObject& object);

struct NoteBody
{
    QVector<NoteBlock> blocks;
    QString plainText;
};
QJsonObject toJson(const NoteBody& value);
NoteBody NoteBodyFromJson(const QJsonObject& object);

struct SlideAnchor
{
    QString presentationId;
    QString slideId;
    int slideIndex;
    int blockIndex;
    std::optional<int> offset;
};
QJsonObject toJson(const SlideAnchor& value);
SlideAnchor SlideAnchorFromJson(const QJsonObject& object);

struct NoteMadeBox
{
    QString name;
    QString text;
};
QJsonObject toJson(const NoteMadeBox& value);
NoteMadeBox NoteMadeBoxFromJson(const QJsonObject& object);

struct NoteMadeSlide
{
    QString slideId;
    QVector<NoteMadeBox> boxes;
};
QJsonObject toJson(const NoteMadeSlide& value);
NoteMadeSlide NoteMadeSlideFromJson(const QJsonObject& object);

struct NoteMadePassage
{
    QString groupId;
    QString text;
    std::optional<QString> kind;
    std::optional<QString> themeSlideName;
    std::optional<QString> themeId;
    QVector<NoteMadeSlide> slides;
};
QJsonObject toJson(const NoteMadePassage& value);
NoteMadePassage NoteMadePassageFromJson(const QJsonObject& object);

struct NotePendingUpdate
{
    QString id;
    QString kind;
    QString groupId;
    std::optional<QString> slideId;
    std::optional<QString> afterSlideId;
    std::optional<QVector<NoteMadeBox>> before;
    std::optional<QVector<NoteMadeBox>> after;
    std::optional<Slide> proposed;
};
QJsonObject toJson(const NotePendingUpdate& value);
NotePendingUpdate NotePendingUpdateFromJson(const QJsonObject& object);

struct NoteMediaImport
{
    QString key;
    QString mediaId;
};
QJsonObject toJson(const NoteMediaImport& value);
NoteMediaImport NoteMediaImportFromJson(const QJsonObject& object);

struct NoteSkippedUpdate
{
    QString id;
    QString text;
};
QJsonObject toJson(const NoteSkippedUpdate& value);
NoteSkippedUpdate NoteSkippedUpdateFromJson(const QJsonObject& object);

struct NoteDocument
{
    QString id;
    QString name;
    std::optional<QString> folder;
    QString origin;
    std::optional<QString> mxuDocumentHexId;
    std::optional<QString> mxuVersion;
    std::optional<QString> mxuUpdatedAt;
    std::optional<QString> mxuIconEmoji;
    std::optional<NoteBody> body;
    std::optional<QVector<SlideAnchor>> anchors;
    std::optional<bool> removedFromMxU;
    std::optional<QString> presentationId;
    std::optional<QString> slidesMadeFromSubmittedAt;
    std::optional<QVector<NoteMadePassage>> madePassages;
    std::optional<bool> markedByStructure;
    std::optional<QVector<NotePendingUpdate>> pendingUpdates;
    std::optional<QVector<NoteMediaImport>> mediaImports;
    std::optional<QString> buildMode;
    std::optional<QVector<NoteSkippedUpdate>> skippedUpdates;
};
QJsonObject toJson(const NoteDocument& value);
NoteDocument NoteDocumentFromJson(const QJsonObject& object);

struct StationSettings
{
    QString id;
    std::optional<int> localOnlyThresholdBytes;
};
QJsonObject toJson(const StationSettings& value);
StationSettings StationSettingsFromJson(const QJsonObject& object);

struct SlideBuildingSettings
{
    QString id;
    std::optional<QString> designMap;
    std::optional<QString> messageNotesThemeId;
    std::optional<QString> lyricsImportThemeId;
    std::optional<QString> lyricsImportDesign;
};
QJsonObject toJson(const SlideBuildingSettings& value);
SlideBuildingSettings SlideBuildingSettingsFromJson(const QJsonObject& object);

struct FontFile
{
    QString id;
    QString family;
    QVector<QString> faces;
    QString ext;
    std::optional<int> byteSize;
};
QJsonObject toJson(const FontFile& value);
FontFile FontFileFromJson(const QJsonObject& object);

struct WorkspaceSettings
{
    QString id;
    std::optional<QString> screens;
    std::optional<QString> timers;
    std::optional<QString> transitions;
    std::optional<QString> controlMappings;
    std::optional<QString> audio;
    std::optional<QString> confidence;
    std::optional<QString> inputs;
    std::optional<QString> behavior;
};
QJsonObject toJson(const WorkspaceSettings& value);
WorkspaceSettings WorkspaceSettingsFromJson(const QJsonObject& object);

struct TrackChannel
{
    QString id;
    QString name;
    std::optional<QString> role;
    std::optional<QString> colorHex;
    std::optional<QVector<QString>> matchNames;
    std::optional<bool> mono;
};
QJsonObject toJson(const TrackChannel& value);
TrackChannel TrackChannelFromJson(const QJsonObject& object);

struct TrackChannelList
{
    QString id;
    QVector<TrackChannel> channels;
};
QJsonObject toJson(const TrackChannelList& value);
TrackChannelList TrackChannelListFromJson(const QJsonObject& object);

struct TrackSetStem
{
    QString audioId;
    QString name;
    std::optional<QString> channelId;
};
QJsonObject toJson(const TrackSetStem& value);
TrackSetStem TrackSetStemFromJson(const QJsonObject& object);

struct TrackSet
{
    QString id;
    QString name;
    QVector<TrackSetStem> stems;
    std::optional<QString> key;
    std::optional<double> tempo;
    std::optional<QString> source;
};
QJsonObject toJson(const TrackSet& value);
TrackSet TrackSetFromJson(const QJsonObject& object);

static constexpr int schemaVersion = 161;

} // namespace mxu::model

// Forward declarations (record dependency graph is acyclic).
struct MediaSourceRect;
struct GradientStop;
struct ObjectFill;
struct ObjectStroke;
struct ObjectShadow;
struct LineStyleOverride;
struct TextLineFill;
struct ChordPlacement;
struct TextStyle;
struct VisibilityCondition;
struct TextStyleRun;
struct KeepFromSlideOptions;
struct BlockScroll;
struct AnimationRange;
struct VideoPush;
struct AnimationStep;
struct AnimationPreset;
struct AnimationPresetBoard;
struct SlideObject;
struct CueMedia;
struct Slide;
struct AutoAdvance;
struct PresentationSection;
struct CCLIInfo;
struct Arrangement;
struct PresentationOrigin;
struct TimelineCue;
struct ClipFade;
struct PresentationTimeline;
struct SongMap;
struct AudioSection;
struct SongMapBlock;
struct Presentation;
struct MediaItem;
struct VideoMark;
struct AudioItem;
struct PlaylistEntry;
struct Playlist;
struct ServiceItem;
struct SongTransition;
struct ServiceLinkRule;
struct ServiceLinkRules;
struct MxUPlanTime;
struct MxUPlanItemNote;
struct MxUPlanTimeOrder;
struct ServiceVersionStation;
struct ServiceItemChange;
struct ServiceVersion;
struct Service;
struct Overlay;
struct OutputAssignment;
struct OutputPreset;
struct MIDIDevice;
struct AlertPreset;
struct Theme;
struct StreamPresetDestination;
struct StreamDestination;
struct StreamRecordPreset;
struct SlideAction;
struct ActionCombo;
struct ScheduleCondition;
struct ScheduleTrigger;
struct ScheduleFolder;
struct SchedulerBoard;
struct ControlFolder;
struct ControlBoard;
struct GroupDefinition;
struct GroupPalette;
struct ImportLedgerEntry;
struct ImportLedger;
struct Transition;
struct EffectPreset;
struct EffectPresetBoard;
struct Effect;
struct TextLink;
struct MultiViewNode;
struct MultiViewTree;
struct ConfidenceLayout;
struct NoteRun;
struct NoteListItem;
struct NoteSlideRef;
struct NoteBlock;
struct NoteBody;
struct OverrideDesign;
struct SlideAnchor;
struct NoteMadeBox;
struct NoteMadeSlide;
struct NoteMadePassage;
struct NotePendingUpdate;
struct SlideVersion;
struct NoteDocument;
struct NoteSkippedUpdate;
struct NoteMediaImport;
struct StationSettings;
struct SlideBuildingSettings;
struct FontFile;
struct WorkspaceSettings;
struct TrackChannel;
struct TrackChannelList;
struct TrackSetStem;
struct TrackSet;
struct LayerPlacement;
struct CustomLayer;
