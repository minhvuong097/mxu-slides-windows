// Generated from schema/documents.json — do not edit by hand.
#include "Models.h"

#include <QJsonArray>
#include <QJsonValue>

#include <type_traits>

namespace mxu::model {

QString toString(SlideObjectKind value)
{
    switch (value) {
    case SlideObjectKind::Text: return QStringLiteral(u"text");
    case SlideObjectKind::Media: return QStringLiteral(u"media");
    case SlideObjectKind::Shape: return QStringLiteral(u"shape");
    case SlideObjectKind::LiveInput: return QStringLiteral(u"liveInput");
    }
    return {};
}

SlideObjectKind SlideObjectKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"text")) return SlideObjectKind::Text;
    if (text == QStringLiteral(u"media")) return SlideObjectKind::Media;
    if (text == QStringLiteral(u"shape")) return SlideObjectKind::Shape;
    if (text == QStringLiteral(u"liveInput")) return SlideObjectKind::LiveInput;
    return SlideObjectKind::Text;
}

QString toString(BlendMode value)
{
    switch (value) {
    case BlendMode::Normal: return QStringLiteral(u"normal");
    case BlendMode::Multiply: return QStringLiteral(u"multiply");
    case BlendMode::Screen: return QStringLiteral(u"screen");
    case BlendMode::Add: return QStringLiteral(u"add");
    }
    return {};
}

BlendMode BlendModeFromString(const QString& text)
{
    if (text == QStringLiteral(u"normal")) return BlendMode::Normal;
    if (text == QStringLiteral(u"multiply")) return BlendMode::Multiply;
    if (text == QStringLiteral(u"screen")) return BlendMode::Screen;
    if (text == QStringLiteral(u"add")) return BlendMode::Add;
    return BlendMode::Normal;
}

QString toString(FillKind value)
{
    switch (value) {
    case FillKind::None: return QStringLiteral(u"none");
    case FillKind::Solid: return QStringLiteral(u"solid");
    case FillKind::LinearGradient: return QStringLiteral(u"linearGradient");
    case FillKind::Media: return QStringLiteral(u"media");
    }
    return {};
}

FillKind FillKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"none")) return FillKind::None;
    if (text == QStringLiteral(u"solid")) return FillKind::Solid;
    if (text == QStringLiteral(u"linearGradient")) return FillKind::LinearGradient;
    if (text == QStringLiteral(u"media")) return FillKind::Media;
    return FillKind::None;
}

QString toString(ShapeKind value)
{
    switch (value) {
    case ShapeKind::Rectangle: return QStringLiteral(u"rectangle");
    case ShapeKind::RoundedRectangle: return QStringLiteral(u"roundedRectangle");
    case ShapeKind::Ellipse: return QStringLiteral(u"ellipse");
    case ShapeKind::Path: return QStringLiteral(u"path");
    }
    return {};
}

ShapeKind ShapeKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"rectangle")) return ShapeKind::Rectangle;
    if (text == QStringLiteral(u"roundedRectangle")) return ShapeKind::RoundedRectangle;
    if (text == QStringLiteral(u"ellipse")) return ShapeKind::Ellipse;
    if (text == QStringLiteral(u"path")) return ShapeKind::Path;
    return ShapeKind::Rectangle;
}

QString toString(ShapeTextPlacement value)
{
    switch (value) {
    case ShapeTextPlacement::Inside: return QStringLiteral(u"inside");
    case ShapeTextPlacement::EdgeOutside: return QStringLiteral(u"edgeOutside");
    case ShapeTextPlacement::EdgeInside: return QStringLiteral(u"edgeInside");
    }
    return {};
}

ShapeTextPlacement ShapeTextPlacementFromString(const QString& text)
{
    if (text == QStringLiteral(u"inside")) return ShapeTextPlacement::Inside;
    if (text == QStringLiteral(u"edgeOutside")) return ShapeTextPlacement::EdgeOutside;
    if (text == QStringLiteral(u"edgeInside")) return ShapeTextPlacement::EdgeInside;
    return ShapeTextPlacement::Inside;
}

QString toString(TickerDirection value)
{
    switch (value) {
    case TickerDirection::RightToLeft: return QStringLiteral(u"rightToLeft");
    case TickerDirection::LeftToRight: return QStringLiteral(u"leftToRight");
    }
    return {};
}

TickerDirection TickerDirectionFromString(const QString& text)
{
    if (text == QStringLiteral(u"rightToLeft")) return TickerDirection::RightToLeft;
    if (text == QStringLiteral(u"leftToRight")) return TickerDirection::LeftToRight;
    return TickerDirection::RightToLeft;
}

QString toString(TextPathSide value)
{
    switch (value) {
    case TextPathSide::Outside: return QStringLiteral(u"outside");
    case TextPathSide::Inside: return QStringLiteral(u"inside");
    }
    return {};
}

TextPathSide TextPathSideFromString(const QString& text)
{
    if (text == QStringLiteral(u"outside")) return TextPathSide::Outside;
    if (text == QStringLiteral(u"inside")) return TextPathSide::Inside;
    return TextPathSide::Outside;
}

QString toString(MediaScaleMode value)
{
    switch (value) {
    case MediaScaleMode::Fill: return QStringLiteral(u"fill");
    case MediaScaleMode::Fit: return QStringLiteral(u"fit");
    case MediaScaleMode::Stretch: return QStringLiteral(u"stretch");
    case MediaScaleMode::ScaleAndBlur: return QStringLiteral(u"scaleAndBlur");
    }
    return {};
}

MediaScaleMode MediaScaleModeFromString(const QString& text)
{
    if (text == QStringLiteral(u"fill")) return MediaScaleMode::Fill;
    if (text == QStringLiteral(u"fit")) return MediaScaleMode::Fit;
    if (text == QStringLiteral(u"stretch")) return MediaScaleMode::Stretch;
    if (text == QStringLiteral(u"scaleAndBlur")) return MediaScaleMode::ScaleAndBlur;
    return MediaScaleMode::Fill;
}

QString toString(TextHorizontalAlignment value)
{
    switch (value) {
    case TextHorizontalAlignment::Left: return QStringLiteral(u"left");
    case TextHorizontalAlignment::Center: return QStringLiteral(u"center");
    case TextHorizontalAlignment::Right: return QStringLiteral(u"right");
    }
    return {};
}

TextHorizontalAlignment TextHorizontalAlignmentFromString(const QString& text)
{
    if (text == QStringLiteral(u"left")) return TextHorizontalAlignment::Left;
    if (text == QStringLiteral(u"center")) return TextHorizontalAlignment::Center;
    if (text == QStringLiteral(u"right")) return TextHorizontalAlignment::Right;
    return TextHorizontalAlignment::Left;
}

QString toString(TextVerticalAlignment value)
{
    switch (value) {
    case TextVerticalAlignment::Top: return QStringLiteral(u"top");
    case TextVerticalAlignment::Middle: return QStringLiteral(u"middle");
    case TextVerticalAlignment::Bottom: return QStringLiteral(u"bottom");
    }
    return {};
}

TextVerticalAlignment TextVerticalAlignmentFromString(const QString& text)
{
    if (text == QStringLiteral(u"top")) return TextVerticalAlignment::Top;
    if (text == QStringLiteral(u"middle")) return TextVerticalAlignment::Middle;
    if (text == QStringLiteral(u"bottom")) return TextVerticalAlignment::Bottom;
    return TextVerticalAlignment::Top;
}

QString toString(TextTransform value)
{
    switch (value) {
    case TextTransform::None: return QStringLiteral(u"none");
    case TextTransform::Uppercase: return QStringLiteral(u"uppercase");
    }
    return {};
}

TextTransform TextTransformFromString(const QString& text)
{
    if (text == QStringLiteral(u"none")) return TextTransform::None;
    if (text == QStringLiteral(u"uppercase")) return TextTransform::Uppercase;
    return TextTransform::None;
}

QString toString(StrokeDashKind value)
{
    switch (value) {
    case StrokeDashKind::Solid: return QStringLiteral(u"solid");
    case StrokeDashKind::Dashed: return QStringLiteral(u"dashed");
    case StrokeDashKind::Dotted: return QStringLiteral(u"dotted");
    }
    return {};
}

StrokeDashKind StrokeDashKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"solid")) return StrokeDashKind::Solid;
    if (text == QStringLiteral(u"dashed")) return StrokeDashKind::Dashed;
    if (text == QStringLiteral(u"dotted")) return StrokeDashKind::Dotted;
    return StrokeDashKind::Solid;
}

QString toString(TextLineFillWidthMode value)
{
    switch (value) {
    case TextLineFillWidthMode::FullWidth: return QStringLiteral(u"fullWidth");
    case TextLineFillWidthMode::LineWidth: return QStringLiteral(u"lineWidth");
    case TextLineFillWidthMode::MaxLineWidth: return QStringLiteral(u"maxLineWidth");
    }
    return {};
}

TextLineFillWidthMode TextLineFillWidthModeFromString(const QString& text)
{
    if (text == QStringLiteral(u"fullWidth")) return TextLineFillWidthMode::FullWidth;
    if (text == QStringLiteral(u"lineWidth")) return TextLineFillWidthMode::LineWidth;
    if (text == QStringLiteral(u"maxLineWidth")) return TextLineFillWidthMode::MaxLineWidth;
    return TextLineFillWidthMode::FullWidth;
}

QString toString(ChordNotation value)
{
    switch (value) {
    case ChordNotation::Chords: return QStringLiteral(u"chords");
    case ChordNotation::Numbers: return QStringLiteral(u"numbers");
    case ChordNotation::Numerals: return QStringLiteral(u"numerals");
    case ChordNotation::DoReMi: return QStringLiteral(u"doReMi");
    }
    return {};
}

ChordNotation ChordNotationFromString(const QString& text)
{
    if (text == QStringLiteral(u"chords")) return ChordNotation::Chords;
    if (text == QStringLiteral(u"numbers")) return ChordNotation::Numbers;
    if (text == QStringLiteral(u"numerals")) return ChordNotation::Numerals;
    if (text == QStringLiteral(u"doReMi")) return ChordNotation::DoReMi;
    return ChordNotation::Chords;
}

QString toString(VisibilityMatch value)
{
    switch (value) {
    case VisibilityMatch::All: return QStringLiteral(u"all");
    case VisibilityMatch::Any: return QStringLiteral(u"any");
    case VisibilityMatch::None: return QStringLiteral(u"none");
    }
    return {};
}

VisibilityMatch VisibilityMatchFromString(const QString& text)
{
    if (text == QStringLiteral(u"all")) return VisibilityMatch::All;
    if (text == QStringLiteral(u"any")) return VisibilityMatch::Any;
    if (text == QStringLiteral(u"none")) return VisibilityMatch::None;
    return VisibilityMatch::All;
}

QString toString(VisibilityConditionKind value)
{
    switch (value) {
    case VisibilityConditionKind::Timer: return QStringLiteral(u"timer");
    case VisibilityConditionKind::VideoCountdown: return QStringLiteral(u"videoCountdown");
    case VisibilityConditionKind::AudioPlayback: return QStringLiteral(u"audioPlayback");
    case VisibilityConditionKind::LiveInput: return QStringLiteral(u"liveInput");
    case VisibilityConditionKind::Capture: return QStringLiteral(u"capture");
    case VisibilityConditionKind::ObjectText: return QStringLiteral(u"objectText");
    }
    return {};
}

VisibilityConditionKind VisibilityConditionKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"timer")) return VisibilityConditionKind::Timer;
    if (text == QStringLiteral(u"videoCountdown")) return VisibilityConditionKind::VideoCountdown;
    if (text == QStringLiteral(u"audioPlayback")) return VisibilityConditionKind::AudioPlayback;
    if (text == QStringLiteral(u"liveInput")) return VisibilityConditionKind::LiveInput;
    if (text == QStringLiteral(u"capture")) return VisibilityConditionKind::Capture;
    if (text == QStringLiteral(u"objectText")) return VisibilityConditionKind::ObjectText;
    return VisibilityConditionKind::Timer;
}

QString toString(VisibilityConditionState value)
{
    switch (value) {
    case VisibilityConditionState::HasTimeRemaining: return QStringLiteral(u"hasTimeRemaining");
    case VisibilityConditionState::HasExpired: return QStringLiteral(u"hasExpired");
    case VisibilityConditionState::IsRunning: return QStringLiteral(u"isRunning");
    case VisibilityConditionState::IsNotRunning: return QStringLiteral(u"isNotRunning");
    case VisibilityConditionState::IsActive: return QStringLiteral(u"isActive");
    case VisibilityConditionState::IsInactive: return QStringLiteral(u"isInactive");
    case VisibilityConditionState::IsConnected: return QStringLiteral(u"isConnected");
    case VisibilityConditionState::IsDisconnected: return QStringLiteral(u"isDisconnected");
    case VisibilityConditionState::HasText: return QStringLiteral(u"hasText");
    case VisibilityConditionState::HasNoText: return QStringLiteral(u"hasNoText");
    }
    return {};
}

VisibilityConditionState VisibilityConditionStateFromString(const QString& text)
{
    if (text == QStringLiteral(u"hasTimeRemaining")) return VisibilityConditionState::HasTimeRemaining;
    if (text == QStringLiteral(u"hasExpired")) return VisibilityConditionState::HasExpired;
    if (text == QStringLiteral(u"isRunning")) return VisibilityConditionState::IsRunning;
    if (text == QStringLiteral(u"isNotRunning")) return VisibilityConditionState::IsNotRunning;
    if (text == QStringLiteral(u"isActive")) return VisibilityConditionState::IsActive;
    if (text == QStringLiteral(u"isInactive")) return VisibilityConditionState::IsInactive;
    if (text == QStringLiteral(u"isConnected")) return VisibilityConditionState::IsConnected;
    if (text == QStringLiteral(u"isDisconnected")) return VisibilityConditionState::IsDisconnected;
    if (text == QStringLiteral(u"hasText")) return VisibilityConditionState::HasText;
    if (text == QStringLiteral(u"hasNoText")) return VisibilityConditionState::HasNoText;
    return VisibilityConditionState::HasTimeRemaining;
}

QString toString(AnimationKind value)
{
    switch (value) {
    case AnimationKind::In: return QStringLiteral(u"in");
    case AnimationKind::Out: return QStringLiteral(u"out");
    case AnimationKind::Emphasis: return QStringLiteral(u"emphasis");
    case AnimationKind::Morph: return QStringLiteral(u"morph");
    }
    return {};
}

AnimationKind AnimationKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"in")) return AnimationKind::In;
    if (text == QStringLiteral(u"out")) return AnimationKind::Out;
    if (text == QStringLiteral(u"emphasis")) return AnimationKind::Emphasis;
    if (text == QStringLiteral(u"morph")) return AnimationKind::Morph;
    return AnimationKind::In;
}

QString toString(AnimationTrigger value)
{
    switch (value) {
    case AnimationTrigger::OnClick: return QStringLiteral(u"onClick");
    case AnimationTrigger::WithPrevious: return QStringLiteral(u"withPrevious");
    case AnimationTrigger::AfterPrevious: return QStringLiteral(u"afterPrevious");
    case AnimationTrigger::OnDismiss: return QStringLiteral(u"onDismiss");
    }
    return {};
}

AnimationTrigger AnimationTriggerFromString(const QString& text)
{
    if (text == QStringLiteral(u"onClick")) return AnimationTrigger::OnClick;
    if (text == QStringLiteral(u"withPrevious")) return AnimationTrigger::WithPrevious;
    if (text == QStringLiteral(u"afterPrevious")) return AnimationTrigger::AfterPrevious;
    if (text == QStringLiteral(u"onDismiss")) return AnimationTrigger::OnDismiss;
    return AnimationTrigger::OnClick;
}

QString toString(StepAnimation value)
{
    switch (value) {
    case StepAnimation::Fade: return QStringLiteral(u"fade");
    case StepAnimation::Move: return QStringLiteral(u"move");
    case StepAnimation::Scale: return QStringLiteral(u"scale");
    case StepAnimation::Wipe: return QStringLiteral(u"wipe");
    case StepAnimation::Blur: return QStringLiteral(u"blur");
    case StepAnimation::Burn: return QStringLiteral(u"burn");
    case StepAnimation::Glitch: return QStringLiteral(u"glitch");
    case StepAnimation::Draw: return QStringLiteral(u"draw");
    case StepAnimation::Type: return QStringLiteral(u"type");
    case StepAnimation::Pulse: return QStringLiteral(u"pulse");
    case StepAnimation::Color: return QStringLiteral(u"color");
    }
    return {};
}

StepAnimation StepAnimationFromString(const QString& text)
{
    if (text == QStringLiteral(u"fade")) return StepAnimation::Fade;
    if (text == QStringLiteral(u"move")) return StepAnimation::Move;
    if (text == QStringLiteral(u"scale")) return StepAnimation::Scale;
    if (text == QStringLiteral(u"wipe")) return StepAnimation::Wipe;
    if (text == QStringLiteral(u"blur")) return StepAnimation::Blur;
    if (text == QStringLiteral(u"burn")) return StepAnimation::Burn;
    if (text == QStringLiteral(u"glitch")) return StepAnimation::Glitch;
    if (text == QStringLiteral(u"draw")) return StepAnimation::Draw;
    if (text == QStringLiteral(u"type")) return StepAnimation::Type;
    if (text == QStringLiteral(u"pulse")) return StepAnimation::Pulse;
    if (text == QStringLiteral(u"color")) return StepAnimation::Color;
    return StepAnimation::Fade;
}

QString toString(BlockScrollAxis value)
{
    switch (value) {
    case BlockScrollAxis::Up: return QStringLiteral(u"up");
    case BlockScrollAxis::Down: return QStringLiteral(u"down");
    case BlockScrollAxis::Left: return QStringLiteral(u"left");
    case BlockScrollAxis::Right: return QStringLiteral(u"right");
    }
    return {};
}

BlockScrollAxis BlockScrollAxisFromString(const QString& text)
{
    if (text == QStringLiteral(u"up")) return BlockScrollAxis::Up;
    if (text == QStringLiteral(u"down")) return BlockScrollAxis::Down;
    if (text == QStringLiteral(u"left")) return BlockScrollAxis::Left;
    if (text == QStringLiteral(u"right")) return BlockScrollAxis::Right;
    return BlockScrollAxis::Up;
}

QString toString(AnimationRamp value)
{
    switch (value) {
    case AnimationRamp::None: return QStringLiteral(u"none");
    case AnimationRamp::In: return QStringLiteral(u"in");
    case AnimationRamp::Out: return QStringLiteral(u"out");
    case AnimationRamp::Both: return QStringLiteral(u"both");
    }
    return {};
}

AnimationRamp AnimationRampFromString(const QString& text)
{
    if (text == QStringLiteral(u"none")) return AnimationRamp::None;
    if (text == QStringLiteral(u"in")) return AnimationRamp::In;
    if (text == QStringLiteral(u"out")) return AnimationRamp::Out;
    if (text == QStringLiteral(u"both")) return AnimationRamp::Both;
    return AnimationRamp::None;
}

QString toString(AnimationEdge value)
{
    switch (value) {
    case AnimationEdge::Left: return QStringLiteral(u"left");
    case AnimationEdge::Right: return QStringLiteral(u"right");
    case AnimationEdge::Top: return QStringLiteral(u"top");
    case AnimationEdge::Bottom: return QStringLiteral(u"bottom");
    }
    return {};
}

AnimationEdge AnimationEdgeFromString(const QString& text)
{
    if (text == QStringLiteral(u"left")) return AnimationEdge::Left;
    if (text == QStringLiteral(u"right")) return AnimationEdge::Right;
    if (text == QStringLiteral(u"top")) return AnimationEdge::Top;
    if (text == QStringLiteral(u"bottom")) return AnimationEdge::Bottom;
    return AnimationEdge::Left;
}

QString toString(VideoPushAlignment value)
{
    switch (value) {
    case VideoPushAlignment::Center: return QStringLiteral(u"center");
    case VideoPushAlignment::Left: return QStringLiteral(u"left");
    case VideoPushAlignment::Right: return QStringLiteral(u"right");
    case VideoPushAlignment::Top: return QStringLiteral(u"top");
    case VideoPushAlignment::Bottom: return QStringLiteral(u"bottom");
    }
    return {};
}

VideoPushAlignment VideoPushAlignmentFromString(const QString& text)
{
    if (text == QStringLiteral(u"center")) return VideoPushAlignment::Center;
    if (text == QStringLiteral(u"left")) return VideoPushAlignment::Left;
    if (text == QStringLiteral(u"right")) return VideoPushAlignment::Right;
    if (text == QStringLiteral(u"top")) return VideoPushAlignment::Top;
    if (text == QStringLiteral(u"bottom")) return VideoPushAlignment::Bottom;
    return VideoPushAlignment::Center;
}

QString toString(VideoPushMode value)
{
    switch (value) {
    case VideoPushMode::Fill: return QStringLiteral(u"fill");
    case VideoPushMode::Fit: return QStringLiteral(u"fit");
    case VideoPushMode::BlurBackground: return QStringLiteral(u"blurBackground");
    }
    return {};
}

VideoPushMode VideoPushModeFromString(const QString& text)
{
    if (text == QStringLiteral(u"fill")) return VideoPushMode::Fill;
    if (text == QStringLiteral(u"fit")) return VideoPushMode::Fit;
    if (text == QStringLiteral(u"blurBackground")) return VideoPushMode::BlurBackground;
    return VideoPushMode::Fill;
}

QString toString(KeystoneMode value)
{
    switch (value) {
    case KeystoneMode::Perspective: return QStringLiteral(u"perspective");
    case KeystoneMode::Stretch: return QStringLiteral(u"stretch");
    }
    return {};
}

KeystoneMode KeystoneModeFromString(const QString& text)
{
    if (text == QStringLiteral(u"perspective")) return KeystoneMode::Perspective;
    if (text == QStringLiteral(u"stretch")) return KeystoneMode::Stretch;
    return KeystoneMode::Perspective;
}

QString toString(TiltPivot value)
{
    switch (value) {
    case TiltPivot::Top: return QStringLiteral(u"top");
    case TiltPivot::Center: return QStringLiteral(u"center");
    case TiltPivot::Bottom: return QStringLiteral(u"bottom");
    }
    return {};
}

TiltPivot TiltPivotFromString(const QString& text)
{
    if (text == QStringLiteral(u"top")) return TiltPivot::Top;
    if (text == QStringLiteral(u"center")) return TiltPivot::Center;
    if (text == QStringLiteral(u"bottom")) return TiltPivot::Bottom;
    return TiltPivot::Top;
}

QString toString(CueMediaLayer value)
{
    switch (value) {
    case CueMediaLayer::LoopingVideos: return QStringLiteral(u"loopingVideos");
    case CueMediaLayer::StillGraphics: return QStringLiteral(u"stillGraphics");
    case CueMediaLayer::Videos: return QStringLiteral(u"videos");
    }
    return {};
}

CueMediaLayer CueMediaLayerFromString(const QString& text)
{
    if (text == QStringLiteral(u"loopingVideos")) return CueMediaLayer::LoopingVideos;
    if (text == QStringLiteral(u"stillGraphics")) return CueMediaLayer::StillGraphics;
    if (text == QStringLiteral(u"videos")) return CueMediaLayer::Videos;
    return CueMediaLayer::LoopingVideos;
}

QString toString(CueMediaMode value)
{
    switch (value) {
    case CueMediaMode::SlideOnly: return QStringLiteral(u"slideOnly");
    case CueMediaMode::UntilReplaced: return QStringLiteral(u"untilReplaced");
    }
    return {};
}

CueMediaMode CueMediaModeFromString(const QString& text)
{
    if (text == QStringLiteral(u"slideOnly")) return CueMediaMode::SlideOnly;
    if (text == QStringLiteral(u"untilReplaced")) return CueMediaMode::UntilReplaced;
    return CueMediaMode::SlideOnly;
}

QString toString(MediaEndFade value)
{
    switch (value) {
    case MediaEndFade::Black: return QStringLiteral(u"black");
    case MediaEndFade::Clear: return QStringLiteral(u"clear");
    }
    return {};
}

MediaEndFade MediaEndFadeFromString(const QString& text)
{
    if (text == QStringLiteral(u"black")) return MediaEndFade::Black;
    if (text == QStringLiteral(u"clear")) return MediaEndFade::Clear;
    return MediaEndFade::Black;
}

QString toString(PresentationOriginSource value)
{
    switch (value) {
    case PresentationOriginSource::MadeHere: return QStringLiteral(u"madeHere");
    case PresentationOriginSource::ProPresenter: return QStringLiteral(u"proPresenter");
    case PresentationOriginSource::PlanningCenterChart: return QStringLiteral(u"planningCenterChart");
    case PresentationOriginSource::PlanningCenterLyrics: return QStringLiteral(u"planningCenterLyrics");
    case PresentationOriginSource::SongSelect: return QStringLiteral(u"songSelect");
    case PresentationOriginSource::LyricsFile: return QStringLiteral(u"lyricsFile");
    case PresentationOriginSource::ChartFile: return QStringLiteral(u"chartFile");
    case PresentationOriginSource::PastedLyrics: return QStringLiteral(u"pastedLyrics");
    case PresentationOriginSource::SlidesFile: return QStringLiteral(u"slidesFile");
    case PresentationOriginSource::Duplicate: return QStringLiteral(u"duplicate");
    }
    return {};
}

PresentationOriginSource PresentationOriginSourceFromString(const QString& text)
{
    if (text == QStringLiteral(u"madeHere")) return PresentationOriginSource::MadeHere;
    if (text == QStringLiteral(u"proPresenter")) return PresentationOriginSource::ProPresenter;
    if (text == QStringLiteral(u"planningCenterChart")) return PresentationOriginSource::PlanningCenterChart;
    if (text == QStringLiteral(u"planningCenterLyrics")) return PresentationOriginSource::PlanningCenterLyrics;
    if (text == QStringLiteral(u"songSelect")) return PresentationOriginSource::SongSelect;
    if (text == QStringLiteral(u"lyricsFile")) return PresentationOriginSource::LyricsFile;
    if (text == QStringLiteral(u"chartFile")) return PresentationOriginSource::ChartFile;
    if (text == QStringLiteral(u"pastedLyrics")) return PresentationOriginSource::PastedLyrics;
    if (text == QStringLiteral(u"slidesFile")) return PresentationOriginSource::SlidesFile;
    if (text == QStringLiteral(u"duplicate")) return PresentationOriginSource::Duplicate;
    return PresentationOriginSource::MadeHere;
}

QString toString(PresentationKind value)
{
    switch (value) {
    case PresentationKind::Song: return QStringLiteral(u"song");
    case PresentationKind::Deck: return QStringLiteral(u"deck");
    }
    return {};
}

PresentationKind PresentationKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"song")) return PresentationKind::Song;
    if (text == QStringLiteral(u"deck")) return PresentationKind::Deck;
    return PresentationKind::Song;
}

QString toString(MediaKind value)
{
    switch (value) {
    case MediaKind::Image: return QStringLiteral(u"image");
    case MediaKind::Video: return QStringLiteral(u"video");
    }
    return {};
}

MediaKind MediaKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"image")) return MediaKind::Image;
    if (text == QStringLiteral(u"video")) return MediaKind::Video;
    return MediaKind::Image;
}

QString toString(MediaClassification value)
{
    switch (value) {
    case MediaClassification::Foreground: return QStringLiteral(u"foreground");
    case MediaClassification::Background: return QStringLiteral(u"background");
    }
    return {};
}

MediaClassification MediaClassificationFromString(const QString& text)
{
    if (text == QStringLiteral(u"foreground")) return MediaClassification::Foreground;
    if (text == QStringLiteral(u"background")) return MediaClassification::Background;
    return MediaClassification::Foreground;
}

QString toString(MediaFileStatus value)
{
    switch (value) {
    case MediaFileStatus::Ready: return QStringLiteral(u"ready");
    case MediaFileStatus::NeedsTranscode: return QStringLiteral(u"needsTranscode");
    case MediaFileStatus::Transcoding: return QStringLiteral(u"transcoding");
    case MediaFileStatus::TranscodeFailed: return QStringLiteral(u"transcodeFailed");
    }
    return {};
}

MediaFileStatus MediaFileStatusFromString(const QString& text)
{
    if (text == QStringLiteral(u"ready")) return MediaFileStatus::Ready;
    if (text == QStringLiteral(u"needsTranscode")) return MediaFileStatus::NeedsTranscode;
    if (text == QStringLiteral(u"transcoding")) return MediaFileStatus::Transcoding;
    if (text == QStringLiteral(u"transcodeFailed")) return MediaFileStatus::TranscodeFailed;
    return MediaFileStatus::Ready;
}

QString toString(PlaylistRefKind value)
{
    switch (value) {
    case PlaylistRefKind::Media: return QStringLiteral(u"media");
    case PlaylistRefKind::Audio: return QStringLiteral(u"audio");
    }
    return {};
}

PlaylistRefKind PlaylistRefKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"media")) return PlaylistRefKind::Media;
    if (text == QStringLiteral(u"audio")) return PlaylistRefKind::Audio;
    return PlaylistRefKind::Media;
}

QString toString(PlaybackMode value)
{
    switch (value) {
    case PlaybackMode::PlayAll: return QStringLiteral(u"playAll");
    case PlaybackMode::LoopPlaylist: return QStringLiteral(u"loopPlaylist");
    case PlaybackMode::LoopSingle: return QStringLiteral(u"loopSingle");
    }
    return {};
}

PlaybackMode PlaybackModeFromString(const QString& text)
{
    if (text == QStringLiteral(u"playAll")) return PlaybackMode::PlayAll;
    if (text == QStringLiteral(u"loopPlaylist")) return PlaybackMode::LoopPlaylist;
    if (text == QStringLiteral(u"loopSingle")) return PlaybackMode::LoopSingle;
    if (text == QStringLiteral(u"shuffle")) return PlaybackMode::PlayAll;
    return PlaybackMode::PlayAll;
}

QString toString(PlaylistKind value)
{
    switch (value) {
    case PlaylistKind::Media: return QStringLiteral(u"media");
    case PlaylistKind::Audio: return QStringLiteral(u"audio");
    }
    return {};
}

PlaylistKind PlaylistKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"media")) return PlaylistKind::Media;
    if (text == QStringLiteral(u"audio")) return PlaylistKind::Audio;
    return PlaylistKind::Media;
}

QString toString(ServiceItemKind value)
{
    switch (value) {
    case ServiceItemKind::Presentation: return QStringLiteral(u"presentation");
    case ServiceItemKind::Media: return QStringLiteral(u"media");
    case ServiceItemKind::Audio: return QStringLiteral(u"audio");
    case ServiceItemKind::Playlist: return QStringLiteral(u"playlist");
    case ServiceItemKind::Header: return QStringLiteral(u"header");
    case ServiceItemKind::Info: return QStringLiteral(u"info");
    }
    return {};
}

ServiceItemKind ServiceItemKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"presentation")) return ServiceItemKind::Presentation;
    if (text == QStringLiteral(u"media")) return ServiceItemKind::Media;
    if (text == QStringLiteral(u"audio")) return ServiceItemKind::Audio;
    if (text == QStringLiteral(u"playlist")) return ServiceItemKind::Playlist;
    if (text == QStringLiteral(u"header")) return ServiceItemKind::Header;
    if (text == QStringLiteral(u"info")) return ServiceItemKind::Info;
    return ServiceItemKind::Presentation;
}

QString toString(OutputTargetKind value)
{
    switch (value) {
    case OutputTargetKind::Display: return QStringLiteral(u"display");
    case OutputTargetKind::PlaceholderScreen: return QStringLiteral(u"placeholderScreen");
    }
    return {};
}

OutputTargetKind OutputTargetKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"display")) return OutputTargetKind::Display;
    if (text == QStringLiteral(u"placeholderScreen")) return OutputTargetKind::PlaceholderScreen;
    if (text == QStringLiteral(u"virtualScreen")) return OutputTargetKind::PlaceholderScreen;
    return OutputTargetKind::Display;
}

QString toString(MIDIDeviceItemDirection value)
{
    switch (value) {
    case MIDIDeviceItemDirection::Input: return QStringLiteral(u"input");
    case MIDIDeviceItemDirection::Output: return QStringLiteral(u"output");
    case MIDIDeviceItemDirection::Both: return QStringLiteral(u"both");
    }
    return {};
}

MIDIDeviceItemDirection MIDIDeviceItemDirectionFromString(const QString& text)
{
    if (text == QStringLiteral(u"input")) return MIDIDeviceItemDirection::Input;
    if (text == QStringLiteral(u"output")) return MIDIDeviceItemDirection::Output;
    if (text == QStringLiteral(u"both")) return MIDIDeviceItemDirection::Both;
    return MIDIDeviceItemDirection::Input;
}

QString toString(AlertBehavior value)
{
    switch (value) {
    case AlertBehavior::Persist: return QStringLiteral(u"persist");
    case AlertBehavior::Flash: return QStringLiteral(u"flash");
    }
    return {};
}

AlertBehavior AlertBehaviorFromString(const QString& text)
{
    if (text == QStringLiteral(u"persist")) return AlertBehavior::Persist;
    if (text == QStringLiteral(u"flash")) return AlertBehavior::Flash;
    return AlertBehavior::Persist;
}

QString toString(AlertTarget value)
{
    switch (value) {
    case AlertTarget::Confidence: return QStringLiteral(u"confidence");
    case AlertTarget::Audience: return QStringLiteral(u"audience");
    case AlertTarget::Both: return QStringLiteral(u"both");
    }
    return {};
}

AlertTarget AlertTargetFromString(const QString& text)
{
    if (text == QStringLiteral(u"confidence")) return AlertTarget::Confidence;
    if (text == QStringLiteral(u"audience")) return AlertTarget::Audience;
    if (text == QStringLiteral(u"both")) return AlertTarget::Both;
    return AlertTarget::Confidence;
}

QString toString(StreamTransport value)
{
    switch (value) {
    case StreamTransport::Rtmp: return QStringLiteral(u"rtmp");
    case StreamTransport::Rtmps: return QStringLiteral(u"rtmps");
    case StreamTransport::Srt: return QStringLiteral(u"srt");
    case StreamTransport::Hls: return QStringLiteral(u"hls");
    }
    return {};
}

StreamTransport StreamTransportFromString(const QString& text)
{
    if (text == QStringLiteral(u"rtmp")) return StreamTransport::Rtmp;
    if (text == QStringLiteral(u"rtmps")) return StreamTransport::Rtmps;
    if (text == QStringLiteral(u"srt")) return StreamTransport::Srt;
    if (text == QStringLiteral(u"hls")) return StreamTransport::Hls;
    return StreamTransport::Rtmp;
}

QString toString(StreamVideoCodec value)
{
    switch (value) {
    case StreamVideoCodec::H264: return QStringLiteral(u"h264");
    case StreamVideoCodec::Hevc: return QStringLiteral(u"hevc");
    }
    return {};
}

StreamVideoCodec StreamVideoCodecFromString(const QString& text)
{
    if (text == QStringLiteral(u"h264")) return StreamVideoCodec::H264;
    if (text == QStringLiteral(u"hevc")) return StreamVideoCodec::Hevc;
    return StreamVideoCodec::H264;
}

QString toString(StreamPresetKind value)
{
    switch (value) {
    case StreamPresetKind::Stream: return QStringLiteral(u"stream");
    case StreamPresetKind::RecordOnly: return QStringLiteral(u"recordOnly");
    }
    return {};
}

StreamPresetKind StreamPresetKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"stream")) return StreamPresetKind::Stream;
    if (text == QStringLiteral(u"recordOnly")) return StreamPresetKind::RecordOnly;
    return StreamPresetKind::Stream;
}

QString toString(StreamSourceKind value)
{
    switch (value) {
    case StreamSourceKind::Screen: return QStringLiteral(u"screen");
    case StreamSourceKind::MediaItem: return QStringLiteral(u"mediaItem");
    case StreamSourceKind::LatestRecording: return QStringLiteral(u"latestRecording");
    }
    return {};
}

StreamSourceKind StreamSourceKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"screen")) return StreamSourceKind::Screen;
    if (text == QStringLiteral(u"mediaItem")) return StreamSourceKind::MediaItem;
    if (text == QStringLiteral(u"latestRecording")) return StreamSourceKind::LatestRecording;
    return StreamSourceKind::Screen;
}

QString toString(CaptureSourceKind value)
{
    switch (value) {
    case CaptureSourceKind::Camera: return QStringLiteral(u"camera");
    case CaptureSourceKind::Ndi: return QStringLiteral(u"ndi");
    case CaptureSourceKind::Decklink: return QStringLiteral(u"decklink");
    }
    return {};
}

CaptureSourceKind CaptureSourceKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"camera")) return CaptureSourceKind::Camera;
    if (text == QStringLiteral(u"ndi")) return CaptureSourceKind::Ndi;
    if (text == QStringLiteral(u"decklink")) return CaptureSourceKind::Decklink;
    return CaptureSourceKind::Camera;
}

QString toString(SlideActionKind value)
{
    switch (value) {
    case SlideActionKind::ClearLayer: return QStringLiteral(u"clearLayer");
    case SlideActionKind::ClearAll: return QStringLiteral(u"clearAll");
    case SlideActionKind::ClearAudio: return QStringLiteral(u"clearAudio");
    case SlideActionKind::ClearSignage: return QStringLiteral(u"clearSignage");
    case SlideActionKind::SwitchOutputPreset: return QStringLiteral(u"switchOutputPreset");
    case SlideActionKind::FireMedia: return QStringLiteral(u"fireMedia");
    case SlideActionKind::FireAlert: return QStringLiteral(u"fireAlert");
    case SlideActionKind::DismissAlert: return QStringLiteral(u"dismissAlert");
    case SlideActionKind::TimerStart: return QStringLiteral(u"timerStart");
    case SlideActionKind::TimerPause: return QStringLiteral(u"timerPause");
    case SlideActionKind::TimerReset: return QStringLiteral(u"timerReset");
    case SlideActionKind::TimerConfigure: return QStringLiteral(u"timerConfigure");
    case SlideActionKind::MidiOut: return QStringLiteral(u"midiOut");
    case SlideActionKind::FireCombo: return QStringLiteral(u"fireCombo");
    case SlideActionKind::CaptureStart: return QStringLiteral(u"captureStart");
    case SlideActionKind::CaptureStop: return QStringLiteral(u"captureStop");
    case SlideActionKind::FirePresentation: return QStringLiteral(u"firePresentation");
    case SlideActionKind::SetConfidenceLayout: return QStringLiteral(u"setConfidenceLayout");
    case SlideActionKind::FireOverlay: return QStringLiteral(u"fireOverlay");
    case SlideActionKind::DismissOverlay: return QStringLiteral(u"dismissOverlay");
    case SlideActionKind::FireLiveInput: return QStringLiteral(u"fireLiveInput");
    case SlideActionKind::SetSignage: return QStringLiteral(u"setSignage");
    case SlideActionKind::SetScreenSource: return QStringLiteral(u"setScreenSource");
    case SlideActionKind::EnableAudioInput: return QStringLiteral(u"enableAudioInput");
    case SlideActionKind::DisableAudioInput: return QStringLiteral(u"disableAudioInput");
    case SlideActionKind::FireAudio: return QStringLiteral(u"fireAudio");
    case SlideActionKind::FireAudioPlaylist: return QStringLiteral(u"fireAudioPlaylist");
    }
    return {};
}

SlideActionKind SlideActionKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"clearLayer")) return SlideActionKind::ClearLayer;
    if (text == QStringLiteral(u"clearAll")) return SlideActionKind::ClearAll;
    if (text == QStringLiteral(u"clearAudio")) return SlideActionKind::ClearAudio;
    if (text == QStringLiteral(u"clearSignage")) return SlideActionKind::ClearSignage;
    if (text == QStringLiteral(u"switchOutputPreset")) return SlideActionKind::SwitchOutputPreset;
    if (text == QStringLiteral(u"fireMedia")) return SlideActionKind::FireMedia;
    if (text == QStringLiteral(u"fireAlert")) return SlideActionKind::FireAlert;
    if (text == QStringLiteral(u"dismissAlert")) return SlideActionKind::DismissAlert;
    if (text == QStringLiteral(u"timerStart")) return SlideActionKind::TimerStart;
    if (text == QStringLiteral(u"timerPause")) return SlideActionKind::TimerPause;
    if (text == QStringLiteral(u"timerReset")) return SlideActionKind::TimerReset;
    if (text == QStringLiteral(u"timerConfigure")) return SlideActionKind::TimerConfigure;
    if (text == QStringLiteral(u"midiOut")) return SlideActionKind::MidiOut;
    if (text == QStringLiteral(u"fireCombo")) return SlideActionKind::FireCombo;
    if (text == QStringLiteral(u"captureStart")) return SlideActionKind::CaptureStart;
    if (text == QStringLiteral(u"captureStop")) return SlideActionKind::CaptureStop;
    if (text == QStringLiteral(u"firePresentation")) return SlideActionKind::FirePresentation;
    if (text == QStringLiteral(u"setConfidenceLayout")) return SlideActionKind::SetConfidenceLayout;
    if (text == QStringLiteral(u"fireOverlay")) return SlideActionKind::FireOverlay;
    if (text == QStringLiteral(u"dismissOverlay")) return SlideActionKind::DismissOverlay;
    if (text == QStringLiteral(u"fireLiveInput")) return SlideActionKind::FireLiveInput;
    if (text == QStringLiteral(u"setSignage")) return SlideActionKind::SetSignage;
    if (text == QStringLiteral(u"setScreenSource")) return SlideActionKind::SetScreenSource;
    if (text == QStringLiteral(u"enableAudioInput")) return SlideActionKind::EnableAudioInput;
    if (text == QStringLiteral(u"disableAudioInput")) return SlideActionKind::DisableAudioInput;
    if (text == QStringLiteral(u"fireAudio")) return SlideActionKind::FireAudio;
    if (text == QStringLiteral(u"fireAudioPlaylist")) return SlideActionKind::FireAudioPlaylist;
    return SlideActionKind::ClearLayer;
}

QString toString(MIDIMessageKind value)
{
    switch (value) {
    case MIDIMessageKind::NoteOn: return QStringLiteral(u"noteOn");
    case MIDIMessageKind::ControlChange: return QStringLiteral(u"controlChange");
    }
    return {};
}

MIDIMessageKind MIDIMessageKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"noteOn")) return MIDIMessageKind::NoteOn;
    if (text == QStringLiteral(u"controlChange")) return MIDIMessageKind::ControlChange;
    return MIDIMessageKind::NoteOn;
}

QString toString(TimerMode value)
{
    switch (value) {
    case TimerMode::Countdown: return QStringLiteral(u"countdown");
    case TimerMode::CountdownToTime: return QStringLiteral(u"countdownToTime");
    case TimerMode::CountUp: return QStringLiteral(u"countUp");
    }
    return {};
}

TimerMode TimerModeFromString(const QString& text)
{
    if (text == QStringLiteral(u"countdown")) return TimerMode::Countdown;
    if (text == QStringLiteral(u"countdownToTime")) return TimerMode::CountdownToTime;
    if (text == QStringLiteral(u"countUp")) return TimerMode::CountUp;
    return TimerMode::Countdown;
}

QString toString(ScheduleConditionKind value)
{
    switch (value) {
    case ScheduleConditionKind::Weekly: return QStringLiteral(u"weekly");
    case ScheduleConditionKind::OneTime: return QStringLiteral(u"oneTime");
    case ScheduleConditionKind::TimerReaches: return QStringLiteral(u"timerReaches");
    }
    return {};
}

ScheduleConditionKind ScheduleConditionKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"weekly")) return ScheduleConditionKind::Weekly;
    if (text == QStringLiteral(u"oneTime")) return ScheduleConditionKind::OneTime;
    if (text == QStringLiteral(u"timerReaches")) return ScheduleConditionKind::TimerReaches;
    return ScheduleConditionKind::Weekly;
}

QString toString(ScheduleConditionLogic value)
{
    switch (value) {
    case ScheduleConditionLogic::Any: return QStringLiteral(u"any");
    case ScheduleConditionLogic::All: return QStringLiteral(u"all");
    }
    return {};
}

ScheduleConditionLogic ScheduleConditionLogicFromString(const QString& text)
{
    if (text == QStringLiteral(u"any")) return ScheduleConditionLogic::Any;
    if (text == QStringLiteral(u"all")) return ScheduleConditionLogic::All;
    return ScheduleConditionLogic::Any;
}

QString toString(TransitionKind value)
{
    switch (value) {
    case TransitionKind::Cut: return QStringLiteral(u"cut");
    case TransitionKind::Dissolve: return QStringLiteral(u"dissolve");
    case TransitionKind::FadeBlack: return QStringLiteral(u"fadeBlack");
    case TransitionKind::FadeWhite: return QStringLiteral(u"fadeWhite");
    case TransitionKind::FadeColor: return QStringLiteral(u"fadeColor");
    case TransitionKind::BlurDissolve: return QStringLiteral(u"blurDissolve");
    case TransitionKind::FilmBurn: return QStringLiteral(u"filmBurn");
    }
    return {};
}

TransitionKind TransitionKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"cut")) return TransitionKind::Cut;
    if (text == QStringLiteral(u"dissolve")) return TransitionKind::Dissolve;
    if (text == QStringLiteral(u"fadeBlack")) return TransitionKind::FadeBlack;
    if (text == QStringLiteral(u"fadeWhite")) return TransitionKind::FadeWhite;
    if (text == QStringLiteral(u"fadeColor")) return TransitionKind::FadeColor;
    if (text == QStringLiteral(u"blurDissolve")) return TransitionKind::BlurDissolve;
    if (text == QStringLiteral(u"filmBurn")) return TransitionKind::FilmBurn;
    return TransitionKind::Cut;
}

QString toString(MaskMode value)
{
    switch (value) {
    case MaskMode::In: return QStringLiteral(u"in");
    case MaskMode::Out: return QStringLiteral(u"out");
    }
    return {};
}

MaskMode MaskModeFromString(const QString& text)
{
    if (text == QStringLiteral(u"in")) return MaskMode::In;
    if (text == QStringLiteral(u"out")) return MaskMode::Out;
    return MaskMode::In;
}

QString toString(EffectKind value)
{
    switch (value) {
    case EffectKind::Blur: return QStringLiteral(u"blur");
    case EffectKind::ColorAdjust: return QStringLiteral(u"colorAdjust");
    case EffectKind::HueRotate: return QStringLiteral(u"hueRotate");
    case EffectKind::Invert: return QStringLiteral(u"invert");
    case EffectKind::Posterize: return QStringLiteral(u"posterize");
    case EffectKind::Pixelate: return QStringLiteral(u"pixelate");
    case EffectKind::Vignette: return QStringLiteral(u"vignette");
    case EffectKind::Warp: return QStringLiteral(u"warp");
    case EffectKind::Echo: return QStringLiteral(u"echo");
    case EffectKind::Scatter: return QStringLiteral(u"scatter");
    case EffectKind::StainedGlass: return QStringLiteral(u"stainedGlass");
    case EffectKind::Grain: return QStringLiteral(u"grain");
    case EffectKind::GhostTrails: return QStringLiteral(u"ghostTrails");
    }
    return {};
}

EffectKind EffectKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"blur")) return EffectKind::Blur;
    if (text == QStringLiteral(u"colorAdjust")) return EffectKind::ColorAdjust;
    if (text == QStringLiteral(u"hueRotate")) return EffectKind::HueRotate;
    if (text == QStringLiteral(u"invert")) return EffectKind::Invert;
    if (text == QStringLiteral(u"posterize")) return EffectKind::Posterize;
    if (text == QStringLiteral(u"pixelate")) return EffectKind::Pixelate;
    if (text == QStringLiteral(u"vignette")) return EffectKind::Vignette;
    if (text == QStringLiteral(u"warp")) return EffectKind::Warp;
    if (text == QStringLiteral(u"echo")) return EffectKind::Echo;
    if (text == QStringLiteral(u"scatter")) return EffectKind::Scatter;
    if (text == QStringLiteral(u"stainedGlass")) return EffectKind::StainedGlass;
    if (text == QStringLiteral(u"grain")) return EffectKind::Grain;
    if (text == QStringLiteral(u"ghostTrails")) return EffectKind::GhostTrails;
    return EffectKind::Blur;
}

QString toString(TextSourceKind value)
{
    switch (value) {
    case TextSourceKind::CurrentSlide: return QStringLiteral(u"currentSlide");
    case TextSourceKind::NextSlide: return QStringLiteral(u"nextSlide");
    case TextSourceKind::LastSlide: return QStringLiteral(u"lastSlide");
    case TextSourceKind::Clock: return QStringLiteral(u"clock");
    case TextSourceKind::Timer: return QStringLiteral(u"timer");
    case TextSourceKind::VideoCountdown: return QStringLiteral(u"videoCountdown");
    case TextSourceKind::SlidePosition: return QStringLiteral(u"slidePosition");
    case TextSourceKind::CurrentServiceItem: return QStringLiteral(u"currentServiceItem");
    case TextSourceKind::NextServiceItem: return QStringLiteral(u"nextServiceItem");
    case TextSourceKind::StageMessage: return QStringLiteral(u"stageMessage");
    case TextSourceKind::CurrentGroup: return QStringLiteral(u"currentGroup");
    case TextSourceKind::CurrentPresentation: return QStringLiteral(u"currentPresentation");
    case TextSourceKind::NextServiceTitle: return QStringLiteral(u"nextServiceTitle");
    case TextSourceKind::Timecode: return QStringLiteral(u"timecode");
    case TextSourceKind::VideoMarkName: return QStringLiteral(u"videoMarkName");
    }
    return {};
}

TextSourceKind TextSourceKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"currentSlide")) return TextSourceKind::CurrentSlide;
    if (text == QStringLiteral(u"nextSlide")) return TextSourceKind::NextSlide;
    if (text == QStringLiteral(u"lastSlide")) return TextSourceKind::LastSlide;
    if (text == QStringLiteral(u"clock")) return TextSourceKind::Clock;
    if (text == QStringLiteral(u"timer")) return TextSourceKind::Timer;
    if (text == QStringLiteral(u"videoCountdown")) return TextSourceKind::VideoCountdown;
    if (text == QStringLiteral(u"slidePosition")) return TextSourceKind::SlidePosition;
    if (text == QStringLiteral(u"currentServiceItem")) return TextSourceKind::CurrentServiceItem;
    if (text == QStringLiteral(u"nextServiceItem")) return TextSourceKind::NextServiceItem;
    if (text == QStringLiteral(u"stageMessage")) return TextSourceKind::StageMessage;
    if (text == QStringLiteral(u"currentGroup")) return TextSourceKind::CurrentGroup;
    if (text == QStringLiteral(u"currentPresentation")) return TextSourceKind::CurrentPresentation;
    if (text == QStringLiteral(u"nextServiceTitle")) return TextSourceKind::NextServiceTitle;
    if (text == QStringLiteral(u"timecode")) return TextSourceKind::Timecode;
    if (text == QStringLiteral(u"videoMarkName")) return TextSourceKind::VideoMarkName;
    return TextSourceKind::CurrentSlide;
}

QString toString(TimerTextFormat value)
{
    switch (value) {
    case TimerTextFormat::Digits: return QStringLiteral(u"digits");
    case TimerTextFormat::Abbreviated: return QStringLiteral(u"abbreviated");
    case TimerTextFormat::Words: return QStringLiteral(u"words");
    }
    return {};
}

TimerTextFormat TimerTextFormatFromString(const QString& text)
{
    if (text == QStringLiteral(u"digits")) return TimerTextFormat::Digits;
    if (text == QStringLiteral(u"abbreviated")) return TimerTextFormat::Abbreviated;
    if (text == QStringLiteral(u"words")) return TimerTextFormat::Words;
    return TimerTextFormat::Digits;
}

QString toString(VideoCountdownTarget value)
{
    switch (value) {
    case VideoCountdownTarget::End: return QStringLiteral(u"end");
    case VideoCountdownTarget::NextMark: return QStringLiteral(u"nextMark");
    case VideoCountdownTarget::NamedMark: return QStringLiteral(u"namedMark");
    }
    return {};
}

VideoCountdownTarget VideoCountdownTargetFromString(const QString& text)
{
    if (text == QStringLiteral(u"end")) return VideoCountdownTarget::End;
    if (text == QStringLiteral(u"nextMark")) return VideoCountdownTarget::NextMark;
    if (text == QStringLiteral(u"namedMark")) return VideoCountdownTarget::NamedMark;
    return VideoCountdownTarget::End;
}

QString toString(MultiViewSplitAxis value)
{
    switch (value) {
    case MultiViewSplitAxis::Columns: return QStringLiteral(u"columns");
    case MultiViewSplitAxis::Rows: return QStringLiteral(u"rows");
    }
    return {};
}

MultiViewSplitAxis MultiViewSplitAxisFromString(const QString& text)
{
    if (text == QStringLiteral(u"columns")) return MultiViewSplitAxis::Columns;
    if (text == QStringLiteral(u"rows")) return MultiViewSplitAxis::Rows;
    return MultiViewSplitAxis::Columns;
}

QString toString(MultiViewSourceKind value)
{
    switch (value) {
    case MultiViewSourceKind::Empty: return QStringLiteral(u"empty");
    case MultiViewSourceKind::Screen: return QStringLiteral(u"screen");
    case MultiViewSourceKind::LiveInput: return QStringLiteral(u"liveInput");
    case MultiViewSourceKind::Media: return QStringLiteral(u"media");
    case MultiViewSourceKind::Clock: return QStringLiteral(u"clock");
    case MultiViewSourceKind::Timer: return QStringLiteral(u"timer");
    case MultiViewSourceKind::VideoCountdown: return QStringLiteral(u"videoCountdown");
    case MultiViewSourceKind::Text: return QStringLiteral(u"text");
    }
    return {};
}

MultiViewSourceKind MultiViewSourceKindFromString(const QString& text)
{
    if (text == QStringLiteral(u"empty")) return MultiViewSourceKind::Empty;
    if (text == QStringLiteral(u"screen")) return MultiViewSourceKind::Screen;
    if (text == QStringLiteral(u"liveInput")) return MultiViewSourceKind::LiveInput;
    if (text == QStringLiteral(u"media")) return MultiViewSourceKind::Media;
    if (text == QStringLiteral(u"clock")) return MultiViewSourceKind::Clock;
    if (text == QStringLiteral(u"timer")) return MultiViewSourceKind::Timer;
    if (text == QStringLiteral(u"videoCountdown")) return MultiViewSourceKind::VideoCountdown;
    if (text == QStringLiteral(u"text")) return MultiViewSourceKind::Text;
    return MultiViewSourceKind::Empty;
}

QString toString(NoteBlockType value)
{
    switch (value) {
    case NoteBlockType::Heading: return QStringLiteral(u"heading");
    case NoteBlockType::Paragraph: return QStringLiteral(u"paragraph");
    case NoteBlockType::List: return QStringLiteral(u"list");
    case NoteBlockType::TaskList: return QStringLiteral(u"taskList");
    case NoteBlockType::Quote: return QStringLiteral(u"quote");
    case NoteBlockType::Code: return QStringLiteral(u"code");
    case NoteBlockType::Rule: return QStringLiteral(u"rule");
    case NoteBlockType::Image: return QStringLiteral(u"image");
    case NoteBlockType::Attachment: return QStringLiteral(u"attachment");
    case NoteBlockType::SlideRef: return QStringLiteral(u"slideRef");
    case NoteBlockType::Unknown: return QStringLiteral(u"unknown");
    }
    return {};
}

NoteBlockType NoteBlockTypeFromString(const QString& text)
{
    if (text == QStringLiteral(u"heading")) return NoteBlockType::Heading;
    if (text == QStringLiteral(u"paragraph")) return NoteBlockType::Paragraph;
    if (text == QStringLiteral(u"list")) return NoteBlockType::List;
    if (text == QStringLiteral(u"taskList")) return NoteBlockType::TaskList;
    if (text == QStringLiteral(u"quote")) return NoteBlockType::Quote;
    if (text == QStringLiteral(u"code")) return NoteBlockType::Code;
    if (text == QStringLiteral(u"rule")) return NoteBlockType::Rule;
    if (text == QStringLiteral(u"image")) return NoteBlockType::Image;
    if (text == QStringLiteral(u"attachment")) return NoteBlockType::Attachment;
    if (text == QStringLiteral(u"slideRef")) return NoteBlockType::SlideRef;
    if (text == QStringLiteral(u"unknown")) return NoteBlockType::Unknown;
    return NoteBlockType::Heading;
}

QJsonObject toJson(const MediaSourceRect& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"x"), value.x);
    object.insert(QStringLiteral(u"y"), value.y);
    object.insert(QStringLiteral(u"width"), value.width);
    object.insert(QStringLiteral(u"height"), value.height);
    return object;
}

MediaSourceRect MediaSourceRectFromJson(const QJsonObject& object)
{
    MediaSourceRect value;
    value.x = object.value(QStringLiteral(u"x")).toDouble();
    value.y = object.value(QStringLiteral(u"y")).toDouble();
    value.width = object.value(QStringLiteral(u"width")).toDouble();
    value.height = object.value(QStringLiteral(u"height")).toDouble();
    return value;
}

QJsonObject toJson(const GradientStop& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"colorHex"), value.colorHex);
    object.insert(QStringLiteral(u"position"), value.position);
    return object;
}

GradientStop GradientStopFromJson(const QJsonObject& object)
{
    GradientStop value;
    value.colorHex = object.value(QStringLiteral(u"colorHex")).toString();
    value.position = object.value(QStringLiteral(u"position")).toDouble();
    return value;
}

QJsonObject toJson(const ObjectFill& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"fillKind"), toString(value.fillKind));
    if (value.colorHex)
        object.insert(QStringLiteral(u"colorHex"), *value.colorHex);
    if (value.gradientAngleDegrees)
        object.insert(QStringLiteral(u"gradientAngleDegrees"), *value.gradientAngleDegrees);
    if (value.gradientStops)
        object.insert(QStringLiteral(u"gradientStops"), encodeList(*value.gradientStops, [](const GradientStop& item) { return toJson(item); }));
    if (value.mediaId)
        object.insert(QStringLiteral(u"mediaId"), *value.mediaId);
    if (value.mediaScaleMode)
        object.insert(QStringLiteral(u"mediaScaleMode"), toString(*value.mediaScaleMode));
    if (value.mediaSourceRect)
        object.insert(QStringLiteral(u"mediaSourceRect"), toJson(*value.mediaSourceRect));
    if (value.loops)
        object.insert(QStringLiteral(u"loops"), *value.loops);
    if (value.captureSourceKind)
        object.insert(QStringLiteral(u"captureSourceKind"), toString(*value.captureSourceKind));
    if (value.captureSourceId)
        object.insert(QStringLiteral(u"captureSourceId"), *value.captureSourceId);
    if (value.screenSourceId)
        object.insert(QStringLiteral(u"screenSourceId"), *value.screenSourceId);
    if (value.liveInputId)
        object.insert(QStringLiteral(u"liveInputId"), *value.liveInputId);
    return object;
}

ObjectFill ObjectFillFromJson(const QJsonObject& object)
{
    ObjectFill value;
    value.fillKind = FillKindFromString(object.value(QStringLiteral(u"fillKind")).toString());
    if (object.contains(QStringLiteral(u"colorHex")))
        value.colorHex = object.value(QStringLiteral(u"colorHex")).toString();
    if (object.contains(QStringLiteral(u"gradientAngleDegrees")))
        value.gradientAngleDegrees = object.value(QStringLiteral(u"gradientAngleDegrees")).toDouble();
    if (object.contains(QStringLiteral(u"gradientStops")))
        value.gradientStops = decodeList<GradientStop>(object.value(QStringLiteral(u"gradientStops")), GradientStopFromJson);
    if (object.contains(QStringLiteral(u"mediaId")))
        value.mediaId = object.value(QStringLiteral(u"mediaId")).toString();
    if (object.contains(QStringLiteral(u"mediaScaleMode")))
        value.mediaScaleMode = MediaScaleModeFromString(object.value(QStringLiteral(u"mediaScaleMode")).toString());
    if (object.contains(QStringLiteral(u"mediaSourceRect")))
        value.mediaSourceRect = MediaSourceRectFromJson(object.value(QStringLiteral(u"mediaSourceRect")).toObject());
    if (object.contains(QStringLiteral(u"loops")))
        value.loops = object.value(QStringLiteral(u"loops")).toBool();
    if (object.contains(QStringLiteral(u"captureSourceKind")))
        value.captureSourceKind = CaptureSourceKindFromString(object.value(QStringLiteral(u"captureSourceKind")).toString());
    if (object.contains(QStringLiteral(u"captureSourceId")))
        value.captureSourceId = object.value(QStringLiteral(u"captureSourceId")).toString();
    if (object.contains(QStringLiteral(u"screenSourceId")))
        value.screenSourceId = object.value(QStringLiteral(u"screenSourceId")).toString();
    if (object.contains(QStringLiteral(u"liveInputId")))
        value.liveInputId = object.value(QStringLiteral(u"liveInputId")).toString();
    return value;
}

QJsonObject toJson(const ObjectStroke& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"colorHex"), value.colorHex);
    object.insert(QStringLiteral(u"width"), value.width);
    if (value.dashKind)
        object.insert(QStringLiteral(u"dashKind"), toString(*value.dashKind));
    return object;
}

ObjectStroke ObjectStrokeFromJson(const QJsonObject& object)
{
    ObjectStroke value;
    value.colorHex = object.value(QStringLiteral(u"colorHex")).toString();
    value.width = object.value(QStringLiteral(u"width")).toDouble();
    if (object.contains(QStringLiteral(u"dashKind")))
        value.dashKind = StrokeDashKindFromString(object.value(QStringLiteral(u"dashKind")).toString());
    return value;
}

QJsonObject toJson(const ObjectShadow& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"colorHex"), value.colorHex);
    object.insert(QStringLiteral(u"blurRadius"), value.blurRadius);
    object.insert(QStringLiteral(u"offsetX"), value.offsetX);
    object.insert(QStringLiteral(u"offsetY"), value.offsetY);
    return object;
}

ObjectShadow ObjectShadowFromJson(const QJsonObject& object)
{
    ObjectShadow value;
    value.colorHex = object.value(QStringLiteral(u"colorHex")).toString();
    value.blurRadius = object.value(QStringLiteral(u"blurRadius")).toDouble();
    value.offsetX = object.value(QStringLiteral(u"offsetX")).toDouble();
    value.offsetY = object.value(QStringLiteral(u"offsetY")).toDouble();
    return value;
}

QJsonObject toJson(const LineStyleOverride& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"lineIndex"), value.lineIndex);
    if (value.fontName)
        object.insert(QStringLiteral(u"fontName"), *value.fontName);
    if (value.fontSize)
        object.insert(QStringLiteral(u"fontSize"), *value.fontSize);
    if (value.colorHex)
        object.insert(QStringLiteral(u"colorHex"), *value.colorHex);
    if (value.tracking)
        object.insert(QStringLiteral(u"tracking"), *value.tracking);
    if (value.firstLineIndent)
        object.insert(QStringLiteral(u"firstLineIndent"), *value.firstLineIndent);
    if (value.leftIndent)
        object.insert(QStringLiteral(u"leftIndent"), *value.leftIndent);
    if (value.rightIndent)
        object.insert(QStringLiteral(u"rightIndent"), *value.rightIndent);
    return object;
}

LineStyleOverride LineStyleOverrideFromJson(const QJsonObject& object)
{
    LineStyleOverride value;
    value.lineIndex = object.value(QStringLiteral(u"lineIndex")).toInt();
    if (object.contains(QStringLiteral(u"fontName")))
        value.fontName = object.value(QStringLiteral(u"fontName")).toString();
    if (object.contains(QStringLiteral(u"fontSize")))
        value.fontSize = object.value(QStringLiteral(u"fontSize")).toDouble();
    if (object.contains(QStringLiteral(u"colorHex")))
        value.colorHex = object.value(QStringLiteral(u"colorHex")).toString();
    if (object.contains(QStringLiteral(u"tracking")))
        value.tracking = object.value(QStringLiteral(u"tracking")).toDouble();
    if (object.contains(QStringLiteral(u"firstLineIndent")))
        value.firstLineIndent = object.value(QStringLiteral(u"firstLineIndent")).toDouble();
    if (object.contains(QStringLiteral(u"leftIndent")))
        value.leftIndent = object.value(QStringLiteral(u"leftIndent")).toDouble();
    if (object.contains(QStringLiteral(u"rightIndent")))
        value.rightIndent = object.value(QStringLiteral(u"rightIndent")).toDouble();
    return value;
}

QJsonObject toJson(const TextLineFill& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"fill"), toJson(value.fill));
    if (value.widthMode)
        object.insert(QStringLiteral(u"widthMode"), toString(*value.widthMode));
    if (value.verticalPadding)
        object.insert(QStringLiteral(u"verticalPadding"), *value.verticalPadding);
    if (value.horizontalPadding)
        object.insert(QStringLiteral(u"horizontalPadding"), *value.horizontalPadding);
    if (value.verticalOffset)
        object.insert(QStringLiteral(u"verticalOffset"), *value.verticalOffset);
    if (value.horizontalOffset)
        object.insert(QStringLiteral(u"horizontalOffset"), *value.horizontalOffset);
    if (value.cornerRadius)
        object.insert(QStringLiteral(u"cornerRadius"), *value.cornerRadius);
    return object;
}

TextLineFill TextLineFillFromJson(const QJsonObject& object)
{
    TextLineFill value;
    value.fill = ObjectFillFromJson(object.value(QStringLiteral(u"fill")).toObject());
    if (object.contains(QStringLiteral(u"widthMode")))
        value.widthMode = TextLineFillWidthModeFromString(object.value(QStringLiteral(u"widthMode")).toString());
    if (object.contains(QStringLiteral(u"verticalPadding")))
        value.verticalPadding = object.value(QStringLiteral(u"verticalPadding")).toDouble();
    if (object.contains(QStringLiteral(u"horizontalPadding")))
        value.horizontalPadding = object.value(QStringLiteral(u"horizontalPadding")).toDouble();
    if (object.contains(QStringLiteral(u"verticalOffset")))
        value.verticalOffset = object.value(QStringLiteral(u"verticalOffset")).toDouble();
    if (object.contains(QStringLiteral(u"horizontalOffset")))
        value.horizontalOffset = object.value(QStringLiteral(u"horizontalOffset")).toDouble();
    if (object.contains(QStringLiteral(u"cornerRadius")))
        value.cornerRadius = object.value(QStringLiteral(u"cornerRadius")).toDouble();
    return value;
}

QJsonObject toJson(const ChordPlacement& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"line"), value.line);
    object.insert(QStringLiteral(u"column"), value.column);
    object.insert(QStringLiteral(u"symbol"), value.symbol);
    return object;
}

ChordPlacement ChordPlacementFromJson(const QJsonObject& object)
{
    ChordPlacement value;
    value.line = object.value(QStringLiteral(u"line")).toInt();
    value.column = object.value(QStringLiteral(u"column")).toInt();
    value.symbol = object.value(QStringLiteral(u"symbol")).toString();
    return value;
}

QJsonObject toJson(const BlockScroll& value)
{
    QJsonObject object;
    if (value.axis)
        object.insert(QStringLiteral(u"axis"), toString(*value.axis));
    object.insert(QStringLiteral(u"speed"), value.speed);
    if (value.passes)
        object.insert(QStringLiteral(u"passes"), *value.passes);
    if (value.ramp)
        object.insert(QStringLiteral(u"ramp"), toString(*value.ramp));
    if (value.restAtEnd)
        object.insert(QStringLiteral(u"restAtEnd"), *value.restAtEnd);
    if (value.fadeTowardTop)
        object.insert(QStringLiteral(u"fadeTowardTop"), *value.fadeTowardTop);
    return object;
}

BlockScroll BlockScrollFromJson(const QJsonObject& object)
{
    BlockScroll value;
    if (object.contains(QStringLiteral(u"axis")))
        value.axis = BlockScrollAxisFromString(object.value(QStringLiteral(u"axis")).toString());
    value.speed = object.value(QStringLiteral(u"speed")).toDouble();
    if (object.contains(QStringLiteral(u"passes")))
        value.passes = object.value(QStringLiteral(u"passes")).toInt();
    if (object.contains(QStringLiteral(u"ramp")))
        value.ramp = AnimationRampFromString(object.value(QStringLiteral(u"ramp")).toString());
    if (object.contains(QStringLiteral(u"restAtEnd")))
        value.restAtEnd = object.value(QStringLiteral(u"restAtEnd")).toBool();
    if (object.contains(QStringLiteral(u"fadeTowardTop")))
        value.fadeTowardTop = object.value(QStringLiteral(u"fadeTowardTop")).toDouble();
    return value;
}

QJsonObject toJson(const TextStyle& value)
{
    QJsonObject object;
    if (value.fontName)
        object.insert(QStringLiteral(u"fontName"), *value.fontName);
    if (value.fontSize)
        object.insert(QStringLiteral(u"fontSize"), *value.fontSize);
    if (value.colorHex)
        object.insert(QStringLiteral(u"colorHex"), *value.colorHex);
    if (value.fill)
        object.insert(QStringLiteral(u"fill"), toJson(*value.fill));
    if (value.tracking)
        object.insert(QStringLiteral(u"tracking"), *value.tracking);
    if (value.lineHeightMultiple)
        object.insert(QStringLiteral(u"lineHeightMultiple"), *value.lineHeightMultiple);
    if (value.horizontalAlignment)
        object.insert(QStringLiteral(u"horizontalAlignment"), toString(*value.horizontalAlignment));
    if (value.verticalAlignment)
        object.insert(QStringLiteral(u"verticalAlignment"), toString(*value.verticalAlignment));
    if (value.textTransform)
        object.insert(QStringLiteral(u"textTransform"), toString(*value.textTransform));
    if (value.tabularFigures)
        object.insert(QStringLiteral(u"tabularFigures"), *value.tabularFigures);
    if (value.autoShrink)
        object.insert(QStringLiteral(u"autoShrink"), *value.autoShrink);
    if (value.minFontSize)
        object.insert(QStringLiteral(u"minFontSize"), *value.minFontSize);
    if (value.keepLinesWhole)
        object.insert(QStringLiteral(u"keepLinesWhole"), *value.keepLinesWhole);
    if (value.pageOnClick)
        object.insert(QStringLiteral(u"pageOnClick"), *value.pageOnClick);
    if (value.balancedWrap)
        object.insert(QStringLiteral(u"balancedWrap"), *value.balancedWrap);
    if (value.outline)
        object.insert(QStringLiteral(u"outline"), toJson(*value.outline));
    if (value.shadow)
        object.insert(QStringLiteral(u"shadow"), toJson(*value.shadow));
    if (value.lineStyles)
        object.insert(QStringLiteral(u"lineStyles"), encodeList(*value.lineStyles, [](const LineStyleOverride& item) { return toJson(item); }));
    if (value.lineFill)
        object.insert(QStringLiteral(u"lineFill"), toJson(*value.lineFill));
    if (value.pathData)
        object.insert(QStringLiteral(u"pathData"), *value.pathData);
    if (value.tickerSpeed)
        object.insert(QStringLiteral(u"tickerSpeed"), *value.tickerSpeed);
    if (value.tickerDirection)
        object.insert(QStringLiteral(u"tickerDirection"), toString(*value.tickerDirection));
    if (value.pathSide)
        object.insert(QStringLiteral(u"pathSide"), toString(*value.pathSide));
    if (value.pathOffset)
        object.insert(QStringLiteral(u"pathOffset"), *value.pathOffset);
    if (value.tickerRepeat)
        object.insert(QStringLiteral(u"tickerRepeat"), *value.tickerRepeat);
    if (value.tickerRamp)
        object.insert(QStringLiteral(u"tickerRamp"), toString(*value.tickerRamp));
    if (value.scroll)
        object.insert(QStringLiteral(u"scroll"), toJson(*value.scroll));
    if (value.tickerStream)
        object.insert(QStringLiteral(u"tickerStream"), *value.tickerStream);
    if (value.tickerGap)
        object.insert(QStringLiteral(u"tickerGap"), *value.tickerGap);
    if (value.tickerSeparator)
        object.insert(QStringLiteral(u"tickerSeparator"), *value.tickerSeparator);
    if (value.wordSpacing)
        object.insert(QStringLiteral(u"wordSpacing"), *value.wordSpacing);
    if (value.insetTop)
        object.insert(QStringLiteral(u"insetTop"), *value.insetTop);
    if (value.insetLeft)
        object.insert(QStringLiteral(u"insetLeft"), *value.insetLeft);
    if (value.insetBottom)
        object.insert(QStringLiteral(u"insetBottom"), *value.insetBottom);
    if (value.insetRight)
        object.insert(QStringLiteral(u"insetRight"), *value.insetRight);
    if (value.firstLineIndent)
        object.insert(QStringLiteral(u"firstLineIndent"), *value.firstLineIndent);
    if (value.leftIndent)
        object.insert(QStringLiteral(u"leftIndent"), *value.leftIndent);
    if (value.rightIndent)
        object.insert(QStringLiteral(u"rightIndent"), *value.rightIndent);
    if (value.paragraphSpacing)
        object.insert(QStringLiteral(u"paragraphSpacing"), *value.paragraphSpacing);
    if (value.showChords)
        object.insert(QStringLiteral(u"showChords"), *value.showChords);
    if (value.chordNotation)
        object.insert(QStringLiteral(u"chordNotation"), toString(*value.chordNotation));
    if (value.chordColorHex)
        object.insert(QStringLiteral(u"chordColorHex"), *value.chordColorHex);
    if (value.underline)
        object.insert(QStringLiteral(u"underline"), *value.underline);
    if (value.strikethrough)
        object.insert(QStringLiteral(u"strikethrough"), *value.strikethrough);
    return object;
}

TextStyle TextStyleFromJson(const QJsonObject& object)
{
    TextStyle value;
    if (object.contains(QStringLiteral(u"fontName")))
        value.fontName = object.value(QStringLiteral(u"fontName")).toString();
    if (object.contains(QStringLiteral(u"fontSize")))
        value.fontSize = object.value(QStringLiteral(u"fontSize")).toDouble();
    if (object.contains(QStringLiteral(u"colorHex")))
        value.colorHex = object.value(QStringLiteral(u"colorHex")).toString();
    if (object.contains(QStringLiteral(u"fill")))
        value.fill = ObjectFillFromJson(object.value(QStringLiteral(u"fill")).toObject());
    if (object.contains(QStringLiteral(u"tracking")))
        value.tracking = object.value(QStringLiteral(u"tracking")).toDouble();
    if (object.contains(QStringLiteral(u"lineHeightMultiple")))
        value.lineHeightMultiple = object.value(QStringLiteral(u"lineHeightMultiple")).toDouble();
    if (object.contains(QStringLiteral(u"horizontalAlignment")))
        value.horizontalAlignment = TextHorizontalAlignmentFromString(object.value(QStringLiteral(u"horizontalAlignment")).toString());
    if (object.contains(QStringLiteral(u"verticalAlignment")))
        value.verticalAlignment = TextVerticalAlignmentFromString(object.value(QStringLiteral(u"verticalAlignment")).toString());
    if (object.contains(QStringLiteral(u"textTransform")))
        value.textTransform = TextTransformFromString(object.value(QStringLiteral(u"textTransform")).toString());
    if (object.contains(QStringLiteral(u"tabularFigures")))
        value.tabularFigures = object.value(QStringLiteral(u"tabularFigures")).toBool();
    if (object.contains(QStringLiteral(u"autoShrink")))
        value.autoShrink = object.value(QStringLiteral(u"autoShrink")).toBool();
    if (object.contains(QStringLiteral(u"minFontSize")))
        value.minFontSize = object.value(QStringLiteral(u"minFontSize")).toDouble();
    if (object.contains(QStringLiteral(u"keepLinesWhole")))
        value.keepLinesWhole = object.value(QStringLiteral(u"keepLinesWhole")).toBool();
    if (object.contains(QStringLiteral(u"pageOnClick")))
        value.pageOnClick = object.value(QStringLiteral(u"pageOnClick")).toBool();
    if (object.contains(QStringLiteral(u"balancedWrap")))
        value.balancedWrap = object.value(QStringLiteral(u"balancedWrap")).toBool();
    if (object.contains(QStringLiteral(u"outline")))
        value.outline = ObjectStrokeFromJson(object.value(QStringLiteral(u"outline")).toObject());
    if (object.contains(QStringLiteral(u"shadow")))
        value.shadow = ObjectShadowFromJson(object.value(QStringLiteral(u"shadow")).toObject());
    if (object.contains(QStringLiteral(u"lineStyles")))
        value.lineStyles = decodeList<LineStyleOverride>(object.value(QStringLiteral(u"lineStyles")), LineStyleOverrideFromJson);
    if (object.contains(QStringLiteral(u"lineFill")))
        value.lineFill = TextLineFillFromJson(object.value(QStringLiteral(u"lineFill")).toObject());
    if (object.contains(QStringLiteral(u"pathData")))
        value.pathData = object.value(QStringLiteral(u"pathData")).toString();
    if (object.contains(QStringLiteral(u"tickerSpeed")))
        value.tickerSpeed = object.value(QStringLiteral(u"tickerSpeed")).toDouble();
    if (object.contains(QStringLiteral(u"tickerDirection")))
        value.tickerDirection = TickerDirectionFromString(object.value(QStringLiteral(u"tickerDirection")).toString());
    if (object.contains(QStringLiteral(u"pathSide")))
        value.pathSide = TextPathSideFromString(object.value(QStringLiteral(u"pathSide")).toString());
    if (object.contains(QStringLiteral(u"pathOffset")))
        value.pathOffset = object.value(QStringLiteral(u"pathOffset")).toDouble();
    if (object.contains(QStringLiteral(u"tickerRepeat")))
        value.tickerRepeat = object.value(QStringLiteral(u"tickerRepeat")).toInt();
    if (object.contains(QStringLiteral(u"tickerRamp")))
        value.tickerRamp = AnimationRampFromString(object.value(QStringLiteral(u"tickerRamp")).toString());
    if (object.contains(QStringLiteral(u"scroll")))
        value.scroll = BlockScrollFromJson(object.value(QStringLiteral(u"scroll")).toObject());
    if (object.contains(QStringLiteral(u"tickerStream")))
        value.tickerStream = object.value(QStringLiteral(u"tickerStream")).toBool();
    if (object.contains(QStringLiteral(u"tickerGap")))
        value.tickerGap = object.value(QStringLiteral(u"tickerGap")).toDouble();
    if (object.contains(QStringLiteral(u"tickerSeparator")))
        value.tickerSeparator = object.value(QStringLiteral(u"tickerSeparator")).toString();
    if (object.contains(QStringLiteral(u"wordSpacing")))
        value.wordSpacing = object.value(QStringLiteral(u"wordSpacing")).toDouble();
    if (object.contains(QStringLiteral(u"insetTop")))
        value.insetTop = object.value(QStringLiteral(u"insetTop")).toDouble();
    if (object.contains(QStringLiteral(u"insetLeft")))
        value.insetLeft = object.value(QStringLiteral(u"insetLeft")).toDouble();
    if (object.contains(QStringLiteral(u"insetBottom")))
        value.insetBottom = object.value(QStringLiteral(u"insetBottom")).toDouble();
    if (object.contains(QStringLiteral(u"insetRight")))
        value.insetRight = object.value(QStringLiteral(u"insetRight")).toDouble();
    if (object.contains(QStringLiteral(u"firstLineIndent")))
        value.firstLineIndent = object.value(QStringLiteral(u"firstLineIndent")).toDouble();
    if (object.contains(QStringLiteral(u"leftIndent")))
        value.leftIndent = object.value(QStringLiteral(u"leftIndent")).toDouble();
    if (object.contains(QStringLiteral(u"rightIndent")))
        value.rightIndent = object.value(QStringLiteral(u"rightIndent")).toDouble();
    if (object.contains(QStringLiteral(u"paragraphSpacing")))
        value.paragraphSpacing = object.value(QStringLiteral(u"paragraphSpacing")).toDouble();
    if (object.contains(QStringLiteral(u"showChords")))
        value.showChords = object.value(QStringLiteral(u"showChords")).toBool();
    if (object.contains(QStringLiteral(u"chordNotation")))
        value.chordNotation = ChordNotationFromString(object.value(QStringLiteral(u"chordNotation")).toString());
    if (object.contains(QStringLiteral(u"chordColorHex")))
        value.chordColorHex = object.value(QStringLiteral(u"chordColorHex")).toString();
    if (object.contains(QStringLiteral(u"underline")))
        value.underline = object.value(QStringLiteral(u"underline")).toBool();
    if (object.contains(QStringLiteral(u"strikethrough")))
        value.strikethrough = object.value(QStringLiteral(u"strikethrough")).toBool();
    return value;
}

QJsonObject toJson(const VisibilityCondition& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"conditionKind"), toString(value.conditionKind));
    object.insert(QStringLiteral(u"state"), toString(value.state));
    if (value.timerId)
        object.insert(QStringLiteral(u"timerId"), *value.timerId);
    if (value.objectId)
        object.insert(QStringLiteral(u"objectId"), *value.objectId);
    if (value.liveInputId)
        object.insert(QStringLiteral(u"liveInputId"), *value.liveInputId);
    return object;
}

VisibilityCondition VisibilityConditionFromJson(const QJsonObject& object)
{
    VisibilityCondition value;
    value.conditionKind = VisibilityConditionKindFromString(object.value(QStringLiteral(u"conditionKind")).toString());
    value.state = VisibilityConditionStateFromString(object.value(QStringLiteral(u"state")).toString());
    if (object.contains(QStringLiteral(u"timerId")))
        value.timerId = object.value(QStringLiteral(u"timerId")).toString();
    if (object.contains(QStringLiteral(u"objectId")))
        value.objectId = object.value(QStringLiteral(u"objectId")).toString();
    if (object.contains(QStringLiteral(u"liveInputId")))
        value.liveInputId = object.value(QStringLiteral(u"liveInputId")).toString();
    return value;
}

QJsonObject toJson(const TextStyleRun& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"line"), value.line);
    object.insert(QStringLiteral(u"column"), value.column);
    object.insert(QStringLiteral(u"length"), value.length);
    if (value.underline)
        object.insert(QStringLiteral(u"underline"), *value.underline);
    if (value.strikethrough)
        object.insert(QStringLiteral(u"strikethrough"), *value.strikethrough);
    if (value.fontName)
        object.insert(QStringLiteral(u"fontName"), *value.fontName);
    if (value.fontSize)
        object.insert(QStringLiteral(u"fontSize"), *value.fontSize);
    if (value.colorHex)
        object.insert(QStringLiteral(u"colorHex"), *value.colorHex);
    if (value.highlightColorHex)
        object.insert(QStringLiteral(u"highlightColorHex"), *value.highlightColorHex);
    if (value.tracking)
        object.insert(QStringLiteral(u"tracking"), *value.tracking);
    if (value.textTransform)
        object.insert(QStringLiteral(u"textTransform"), toString(*value.textTransform));
    return object;
}

TextStyleRun TextStyleRunFromJson(const QJsonObject& object)
{
    TextStyleRun value;
    value.line = object.value(QStringLiteral(u"line")).toInt();
    value.column = object.value(QStringLiteral(u"column")).toInt();
    value.length = object.value(QStringLiteral(u"length")).toInt();
    if (object.contains(QStringLiteral(u"underline")))
        value.underline = object.value(QStringLiteral(u"underline")).toBool();
    if (object.contains(QStringLiteral(u"strikethrough")))
        value.strikethrough = object.value(QStringLiteral(u"strikethrough")).toBool();
    if (object.contains(QStringLiteral(u"fontName")))
        value.fontName = object.value(QStringLiteral(u"fontName")).toString();
    if (object.contains(QStringLiteral(u"fontSize")))
        value.fontSize = object.value(QStringLiteral(u"fontSize")).toDouble();
    if (object.contains(QStringLiteral(u"colorHex")))
        value.colorHex = object.value(QStringLiteral(u"colorHex")).toString();
    if (object.contains(QStringLiteral(u"highlightColorHex")))
        value.highlightColorHex = object.value(QStringLiteral(u"highlightColorHex")).toString();
    if (object.contains(QStringLiteral(u"tracking")))
        value.tracking = object.value(QStringLiteral(u"tracking")).toDouble();
    if (object.contains(QStringLiteral(u"textTransform")))
        value.textTransform = TextTransformFromString(object.value(QStringLiteral(u"textTransform")).toString());
    return value;
}

QJsonObject toJson(const KeepFromSlideOptions& value)
{
    QJsonObject object;
    if (value.bold)
        object.insert(QStringLiteral(u"bold"), *value.bold);
    if (value.italic)
        object.insert(QStringLiteral(u"italic"), *value.italic);
    if (value.underline)
        object.insert(QStringLiteral(u"underline"), *value.underline);
    if (value.strikethrough)
        object.insert(QStringLiteral(u"strikethrough"), *value.strikethrough);
    if (value.sizeEmphasis)
        object.insert(QStringLiteral(u"sizeEmphasis"), *value.sizeEmphasis);
    if (value.wordLetterSpacing)
        object.insert(QStringLiteral(u"wordLetterSpacing"), *value.wordLetterSpacing);
    if (value.highlight)
        object.insert(QStringLiteral(u"highlight"), *value.highlight);
    if (value.textColor)
        object.insert(QStringLiteral(u"textColor"), *value.textColor);
    return object;
}

KeepFromSlideOptions KeepFromSlideOptionsFromJson(const QJsonObject& object)
{
    KeepFromSlideOptions value;
    if (object.contains(QStringLiteral(u"bold")))
        value.bold = object.value(QStringLiteral(u"bold")).toBool();
    if (object.contains(QStringLiteral(u"italic")))
        value.italic = object.value(QStringLiteral(u"italic")).toBool();
    if (object.contains(QStringLiteral(u"underline")))
        value.underline = object.value(QStringLiteral(u"underline")).toBool();
    if (object.contains(QStringLiteral(u"strikethrough")))
        value.strikethrough = object.value(QStringLiteral(u"strikethrough")).toBool();
    if (object.contains(QStringLiteral(u"sizeEmphasis")))
        value.sizeEmphasis = object.value(QStringLiteral(u"sizeEmphasis")).toBool();
    if (object.contains(QStringLiteral(u"wordLetterSpacing")))
        value.wordLetterSpacing = object.value(QStringLiteral(u"wordLetterSpacing")).toBool();
    if (object.contains(QStringLiteral(u"highlight")))
        value.highlight = object.value(QStringLiteral(u"highlight")).toBool();
    if (object.contains(QStringLiteral(u"textColor")))
        value.textColor = object.value(QStringLiteral(u"textColor")).toBool();
    return value;
}

QJsonObject toJson(const AnimationRange& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"line"), value.line);
    object.insert(QStringLiteral(u"column"), value.column);
    object.insert(QStringLiteral(u"length"), value.length);
    return object;
}

AnimationRange AnimationRangeFromJson(const QJsonObject& object)
{
    AnimationRange value;
    value.line = object.value(QStringLiteral(u"line")).toInt();
    value.column = object.value(QStringLiteral(u"column")).toInt();
    value.length = object.value(QStringLiteral(u"length")).toInt();
    return value;
}

QJsonObject toJson(const VideoPush& value)
{
    QJsonObject object;
    if (value.alignment)
        object.insert(QStringLiteral(u"alignment"), toString(*value.alignment));
    if (value.mode)
        object.insert(QStringLiteral(u"mode"), toString(*value.mode));
    if (value.zoom)
        object.insert(QStringLiteral(u"zoom"), *value.zoom);
    if (value.margin)
        object.insert(QStringLiteral(u"margin"), *value.margin);
    if (value.backdrop)
        object.insert(QStringLiteral(u"backdrop"), *value.backdrop);
    if (value.blurRadius)
        object.insert(QStringLiteral(u"blurRadius"), *value.blurRadius);
    return object;
}

VideoPush VideoPushFromJson(const QJsonObject& object)
{
    VideoPush value;
    if (object.contains(QStringLiteral(u"alignment")))
        value.alignment = VideoPushAlignmentFromString(object.value(QStringLiteral(u"alignment")).toString());
    if (object.contains(QStringLiteral(u"mode")))
        value.mode = VideoPushModeFromString(object.value(QStringLiteral(u"mode")).toString());
    if (object.contains(QStringLiteral(u"zoom")))
        value.zoom = object.value(QStringLiteral(u"zoom")).toDouble();
    if (object.contains(QStringLiteral(u"margin")))
        value.margin = object.value(QStringLiteral(u"margin")).toDouble();
    if (object.contains(QStringLiteral(u"backdrop")))
        value.backdrop = object.value(QStringLiteral(u"backdrop")).toBool();
    if (object.contains(QStringLiteral(u"blurRadius")))
        value.blurRadius = object.value(QStringLiteral(u"blurRadius")).toDouble();
    return value;
}

QJsonObject toJson(const Effect& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"effectKind"), toString(value.effectKind));
    if (value.enabled)
        object.insert(QStringLiteral(u"enabled"), *value.enabled);
    if (value.opacity)
        object.insert(QStringLiteral(u"opacity"), *value.opacity);
    if (value.radius)
        object.insert(QStringLiteral(u"radius"), *value.radius);
    if (value.amount)
        object.insert(QStringLiteral(u"amount"), *value.amount);
    if (value.scale)
        object.insert(QStringLiteral(u"scale"), *value.scale);
    if (value.speed)
        object.insert(QStringLiteral(u"speed"), *value.speed);
    if (value.fade)
        object.insert(QStringLiteral(u"fade"), *value.fade);
    if (value.smooth)
        object.insert(QStringLiteral(u"smooth"), *value.smooth);
    if (value.brightness)
        object.insert(QStringLiteral(u"brightness"), *value.brightness);
    if (value.contrast)
        object.insert(QStringLiteral(u"contrast"), *value.contrast);
    if (value.saturation)
        object.insert(QStringLiteral(u"saturation"), *value.saturation);
    if (value.hue)
        object.insert(QStringLiteral(u"hue"), *value.hue);
    return object;
}

Effect EffectFromJson(const QJsonObject& object)
{
    Effect value;
    value.effectKind = EffectKindFromString(object.value(QStringLiteral(u"effectKind")).toString());
    if (object.contains(QStringLiteral(u"enabled")))
        value.enabled = object.value(QStringLiteral(u"enabled")).toBool();
    if (object.contains(QStringLiteral(u"opacity")))
        value.opacity = object.value(QStringLiteral(u"opacity")).toDouble();
    if (object.contains(QStringLiteral(u"radius")))
        value.radius = object.value(QStringLiteral(u"radius")).toDouble();
    if (object.contains(QStringLiteral(u"amount")))
        value.amount = object.value(QStringLiteral(u"amount")).toDouble();
    if (object.contains(QStringLiteral(u"scale")))
        value.scale = object.value(QStringLiteral(u"scale")).toDouble();
    if (object.contains(QStringLiteral(u"speed")))
        value.speed = object.value(QStringLiteral(u"speed")).toDouble();
    if (object.contains(QStringLiteral(u"fade")))
        value.fade = object.value(QStringLiteral(u"fade")).toDouble();
    if (object.contains(QStringLiteral(u"smooth")))
        value.smooth = object.value(QStringLiteral(u"smooth")).toDouble();
    if (object.contains(QStringLiteral(u"brightness")))
        value.brightness = object.value(QStringLiteral(u"brightness")).toDouble();
    if (object.contains(QStringLiteral(u"contrast")))
        value.contrast = object.value(QStringLiteral(u"contrast")).toDouble();
    if (object.contains(QStringLiteral(u"saturation")))
        value.saturation = object.value(QStringLiteral(u"saturation")).toDouble();
    if (object.contains(QStringLiteral(u"hue")))
        value.hue = object.value(QStringLiteral(u"hue")).toDouble();
    return value;
}

QJsonObject toJson(const TextLink& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"source"), toString(value.source));
    if (value.timerId)
        object.insert(QStringLiteral(u"timerId"), *value.timerId);
    if (value.clockFormat)
        object.insert(QStringLiteral(u"clockFormat"), *value.clockFormat);
    if (value.usesWarningColor)
        object.insert(QStringLiteral(u"usesWarningColor"), *value.usesWarningColor);
    if (value.maxLines)
        object.insert(QStringLiteral(u"maxLines"), *value.maxLines);
    if (value.includeSteps)
        object.insert(QStringLiteral(u"includeSteps"), *value.includeSteps);
    if (value.includeBuilds)
        object.insert(QStringLiteral(u"includeBuilds"), *value.includeBuilds);
    if (value.sourceObjectName)
        object.insert(QStringLiteral(u"sourceObjectName"), *value.sourceObjectName);
    if (value.showsVideoName)
        object.insert(QStringLiteral(u"showsVideoName"), *value.showsVideoName);
    if (value.videoLayer)
        object.insert(QStringLiteral(u"videoLayer"), *value.videoLayer);
    if (value.timerFormat)
        object.insert(QStringLiteral(u"timerFormat"), toString(*value.timerFormat));
    if (value.timerPattern)
        object.insert(QStringLiteral(u"timerPattern"), *value.timerPattern);
    if (value.videoTarget)
        object.insert(QStringLiteral(u"videoTarget"), toString(*value.videoTarget));
    if (value.videoMarkName)
        object.insert(QStringLiteral(u"videoMarkName"), *value.videoMarkName);
    if (value.countsUp)
        object.insert(QStringLiteral(u"countsUp"), *value.countsUp);
    return object;
}

TextLink TextLinkFromJson(const QJsonObject& object)
{
    TextLink value;
    value.source = TextSourceKindFromString(object.value(QStringLiteral(u"source")).toString());
    if (object.contains(QStringLiteral(u"timerId")))
        value.timerId = object.value(QStringLiteral(u"timerId")).toString();
    if (object.contains(QStringLiteral(u"clockFormat")))
        value.clockFormat = object.value(QStringLiteral(u"clockFormat")).toString();
    if (object.contains(QStringLiteral(u"usesWarningColor")))
        value.usesWarningColor = object.value(QStringLiteral(u"usesWarningColor")).toBool();
    if (object.contains(QStringLiteral(u"maxLines")))
        value.maxLines = object.value(QStringLiteral(u"maxLines")).toInt();
    if (object.contains(QStringLiteral(u"includeSteps")))
        value.includeSteps = object.value(QStringLiteral(u"includeSteps")).toBool();
    if (object.contains(QStringLiteral(u"includeBuilds")))
        value.includeBuilds = object.value(QStringLiteral(u"includeBuilds")).toBool();
    if (object.contains(QStringLiteral(u"sourceObjectName")))
        value.sourceObjectName = object.value(QStringLiteral(u"sourceObjectName")).toString();
    if (object.contains(QStringLiteral(u"showsVideoName")))
        value.showsVideoName = object.value(QStringLiteral(u"showsVideoName")).toBool();
    if (object.contains(QStringLiteral(u"videoLayer")))
        value.videoLayer = object.value(QStringLiteral(u"videoLayer")).toString();
    if (object.contains(QStringLiteral(u"timerFormat")))
        value.timerFormat = TimerTextFormatFromString(object.value(QStringLiteral(u"timerFormat")).toString());
    if (object.contains(QStringLiteral(u"timerPattern")))
        value.timerPattern = object.value(QStringLiteral(u"timerPattern")).toString();
    if (object.contains(QStringLiteral(u"videoTarget")))
        value.videoTarget = VideoCountdownTargetFromString(object.value(QStringLiteral(u"videoTarget")).toString());
    if (object.contains(QStringLiteral(u"videoMarkName")))
        value.videoMarkName = object.value(QStringLiteral(u"videoMarkName")).toString();
    if (object.contains(QStringLiteral(u"countsUp")))
        value.countsUp = object.value(QStringLiteral(u"countsUp")).toBool();
    return value;
}

QJsonObject toJson(const SlideObject& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"objectKind"), toString(value.objectKind));
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"text"), value.text);
    if (value.x)
        object.insert(QStringLiteral(u"x"), *value.x);
    if (value.y)
        object.insert(QStringLiteral(u"y"), *value.y);
    if (value.width)
        object.insert(QStringLiteral(u"width"), *value.width);
    if (value.height)
        object.insert(QStringLiteral(u"height"), *value.height);
    if (value.rotationDegrees)
        object.insert(QStringLiteral(u"rotationDegrees"), *value.rotationDegrees);
    if (value.hidden)
        object.insert(QStringLiteral(u"hidden"), *value.hidden);
    if (value.visibilityMatch)
        object.insert(QStringLiteral(u"visibilityMatch"), toString(*value.visibilityMatch));
    if (value.visibilityConditions)
        object.insert(QStringLiteral(u"visibilityConditions"), encodeList(*value.visibilityConditions, [](const VisibilityCondition& item) { return toJson(item); }));
    if (value.flipHorizontal)
        object.insert(QStringLiteral(u"flipHorizontal"), *value.flipHorizontal);
    if (value.flipVertical)
        object.insert(QStringLiteral(u"flipVertical"), *value.flipVertical);
    if (value.opacity)
        object.insert(QStringLiteral(u"opacity"), *value.opacity);
    if (value.blendMode)
        object.insert(QStringLiteral(u"blendMode"), toString(*value.blendMode));
    if (value.groupId)
        object.insert(QStringLiteral(u"groupId"), *value.groupId);
    if (value.maskObjectId)
        object.insert(QStringLiteral(u"maskObjectId"), *value.maskObjectId);
    if (value.maskMode)
        object.insert(QStringLiteral(u"maskMode"), toString(*value.maskMode));
    if (value.effects)
        object.insert(QStringLiteral(u"effects"), encodeList(*value.effects, [](const Effect& item) { return toJson(item); }));
    if (value.effectsApplyBelow)
        object.insert(QStringLiteral(u"effectsApplyBelow"), *value.effectsApplyBelow);
    if (value.textLink)
        object.insert(QStringLiteral(u"textLink"), toJson(*value.textLink));
    if (value.textStyle)
        object.insert(QStringLiteral(u"textStyle"), toJson(*value.textStyle));
    if (value.chords)
        object.insert(QStringLiteral(u"chords"), encodeList(*value.chords, [](const ChordPlacement& item) { return toJson(item); }));
    if (value.styleRuns)
        object.insert(QStringLiteral(u"styleRuns"), encodeList(*value.styleRuns, [](const TextStyleRun& item) { return toJson(item); }));
    if (value.shapeKind)
        object.insert(QStringLiteral(u"shapeKind"), toString(*value.shapeKind));
    if (value.cornerRadius)
        object.insert(QStringLiteral(u"cornerRadius"), *value.cornerRadius);
    if (value.pathData)
        object.insert(QStringLiteral(u"pathData"), *value.pathData);
    if (value.shapeTextPlacement)
        object.insert(QStringLiteral(u"shapeTextPlacement"), toString(*value.shapeTextPlacement));
    if (value.shapeTextCornerRadius)
        object.insert(QStringLiteral(u"shapeTextCornerRadius"), *value.shapeTextCornerRadius);
    if (value.fill)
        object.insert(QStringLiteral(u"fill"), toJson(*value.fill));
    if (value.stroke)
        object.insert(QStringLiteral(u"stroke"), toJson(*value.stroke));
    if (value.shadow)
        object.insert(QStringLiteral(u"shadow"), toJson(*value.shadow));
    if (value.mediaId)
        object.insert(QStringLiteral(u"mediaId"), *value.mediaId);
    if (value.mediaScaleMode)
        object.insert(QStringLiteral(u"mediaScaleMode"), toString(*value.mediaScaleMode));
    if (value.mediaSourceRect)
        object.insert(QStringLiteral(u"mediaSourceRect"), toJson(*value.mediaSourceRect));
    if (value.loops)
        object.insert(QStringLiteral(u"loops"), *value.loops);
    if (value.captureSourceKind)
        object.insert(QStringLiteral(u"captureSourceKind"), toString(*value.captureSourceKind));
    if (value.captureSourceId)
        object.insert(QStringLiteral(u"captureSourceId"), *value.captureSourceId);
    if (value.screenSourceId)
        object.insert(QStringLiteral(u"screenSourceId"), *value.screenSourceId);
    if (value.liveInputId)
        object.insert(QStringLiteral(u"liveInputId"), *value.liveInputId);
    if (value.keepFromSlide)
        object.insert(QStringLiteral(u"keepFromSlide"), toJson(*value.keepFromSlide));
    if (value.animationSteps)
        object.insert(QStringLiteral(u"animationSteps"), encodeList(*value.animationSteps, [](const AnimationStep& item) { return toJson(item); }));
    if (value.builds)
        object.insert(QStringLiteral(u"builds"), encodeList(*value.builds, [](const AnimationStep& item) { return toJson(item); }));
    if (value.tilt)
        object.insert(QStringLiteral(u"tilt"), *value.tilt);
    if (value.swing)
        object.insert(QStringLiteral(u"swing"), *value.swing);
    if (value.tiltPivot)
        object.insert(QStringLiteral(u"tiltPivot"), toString(*value.tiltPivot));
    if (value.keystoneTop)
        object.insert(QStringLiteral(u"keystoneTop"), *value.keystoneTop);
    if (value.keystoneBottom)
        object.insert(QStringLiteral(u"keystoneBottom"), *value.keystoneBottom);
    if (value.skewX)
        object.insert(QStringLiteral(u"skewX"), *value.skewX);
    if (value.skewY)
        object.insert(QStringLiteral(u"skewY"), *value.skewY);
    if (value.keystoneMode)
        object.insert(QStringLiteral(u"keystoneMode"), toString(*value.keystoneMode));
    if (value.photoSpot)
        object.insert(QStringLiteral(u"photoSpot"), *value.photoSpot);
    return object;
}

SlideObject SlideObjectFromJson(const QJsonObject& object)
{
    SlideObject value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.objectKind = SlideObjectKindFromString(object.value(QStringLiteral(u"objectKind")).toString());
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.text = object.value(QStringLiteral(u"text")).toString();
    if (object.contains(QStringLiteral(u"x")))
        value.x = object.value(QStringLiteral(u"x")).toDouble();
    if (object.contains(QStringLiteral(u"y")))
        value.y = object.value(QStringLiteral(u"y")).toDouble();
    if (object.contains(QStringLiteral(u"width")))
        value.width = object.value(QStringLiteral(u"width")).toDouble();
    if (object.contains(QStringLiteral(u"height")))
        value.height = object.value(QStringLiteral(u"height")).toDouble();
    if (object.contains(QStringLiteral(u"rotationDegrees")))
        value.rotationDegrees = object.value(QStringLiteral(u"rotationDegrees")).toDouble();
    if (object.contains(QStringLiteral(u"hidden")))
        value.hidden = object.value(QStringLiteral(u"hidden")).toBool();
    if (object.contains(QStringLiteral(u"visibilityMatch")))
        value.visibilityMatch = VisibilityMatchFromString(object.value(QStringLiteral(u"visibilityMatch")).toString());
    if (object.contains(QStringLiteral(u"visibilityConditions")))
        value.visibilityConditions = decodeList<VisibilityCondition>(object.value(QStringLiteral(u"visibilityConditions")), VisibilityConditionFromJson);
    if (object.contains(QStringLiteral(u"flipHorizontal")))
        value.flipHorizontal = object.value(QStringLiteral(u"flipHorizontal")).toBool();
    if (object.contains(QStringLiteral(u"flipVertical")))
        value.flipVertical = object.value(QStringLiteral(u"flipVertical")).toBool();
    if (object.contains(QStringLiteral(u"opacity")))
        value.opacity = object.value(QStringLiteral(u"opacity")).toDouble();
    if (object.contains(QStringLiteral(u"blendMode")))
        value.blendMode = BlendModeFromString(object.value(QStringLiteral(u"blendMode")).toString());
    if (object.contains(QStringLiteral(u"groupId")))
        value.groupId = object.value(QStringLiteral(u"groupId")).toString();
    if (object.contains(QStringLiteral(u"maskObjectId")))
        value.maskObjectId = object.value(QStringLiteral(u"maskObjectId")).toString();
    if (object.contains(QStringLiteral(u"maskMode")))
        value.maskMode = MaskModeFromString(object.value(QStringLiteral(u"maskMode")).toString());
    if (object.contains(QStringLiteral(u"effects")))
        value.effects = decodeList<Effect>(object.value(QStringLiteral(u"effects")), EffectFromJson);
    if (object.contains(QStringLiteral(u"effectsApplyBelow")))
        value.effectsApplyBelow = object.value(QStringLiteral(u"effectsApplyBelow")).toBool();
    if (object.contains(QStringLiteral(u"textLink")))
        value.textLink = TextLinkFromJson(object.value(QStringLiteral(u"textLink")).toObject());
    if (object.contains(QStringLiteral(u"textStyle")))
        value.textStyle = TextStyleFromJson(object.value(QStringLiteral(u"textStyle")).toObject());
    if (object.contains(QStringLiteral(u"chords")))
        value.chords = decodeList<ChordPlacement>(object.value(QStringLiteral(u"chords")), ChordPlacementFromJson);
    if (object.contains(QStringLiteral(u"styleRuns")))
        value.styleRuns = decodeList<TextStyleRun>(object.value(QStringLiteral(u"styleRuns")), TextStyleRunFromJson);
    if (object.contains(QStringLiteral(u"shapeKind")))
        value.shapeKind = ShapeKindFromString(object.value(QStringLiteral(u"shapeKind")).toString());
    if (object.contains(QStringLiteral(u"cornerRadius")))
        value.cornerRadius = object.value(QStringLiteral(u"cornerRadius")).toDouble();
    if (object.contains(QStringLiteral(u"pathData")))
        value.pathData = object.value(QStringLiteral(u"pathData")).toString();
    if (object.contains(QStringLiteral(u"shapeTextPlacement")))
        value.shapeTextPlacement = ShapeTextPlacementFromString(object.value(QStringLiteral(u"shapeTextPlacement")).toString());
    if (object.contains(QStringLiteral(u"shapeTextCornerRadius")))
        value.shapeTextCornerRadius = object.value(QStringLiteral(u"shapeTextCornerRadius")).toDouble();
    if (object.contains(QStringLiteral(u"fill")))
        value.fill = ObjectFillFromJson(object.value(QStringLiteral(u"fill")).toObject());
    if (object.contains(QStringLiteral(u"stroke")))
        value.stroke = ObjectStrokeFromJson(object.value(QStringLiteral(u"stroke")).toObject());
    if (object.contains(QStringLiteral(u"shadow")))
        value.shadow = ObjectShadowFromJson(object.value(QStringLiteral(u"shadow")).toObject());
    if (object.contains(QStringLiteral(u"mediaId")))
        value.mediaId = object.value(QStringLiteral(u"mediaId")).toString();
    if (object.contains(QStringLiteral(u"mediaScaleMode")))
        value.mediaScaleMode = MediaScaleModeFromString(object.value(QStringLiteral(u"mediaScaleMode")).toString());
    if (object.contains(QStringLiteral(u"mediaSourceRect")))
        value.mediaSourceRect = MediaSourceRectFromJson(object.value(QStringLiteral(u"mediaSourceRect")).toObject());
    if (object.contains(QStringLiteral(u"loops")))
        value.loops = object.value(QStringLiteral(u"loops")).toBool();
    if (object.contains(QStringLiteral(u"captureSourceKind")))
        value.captureSourceKind = CaptureSourceKindFromString(object.value(QStringLiteral(u"captureSourceKind")).toString());
    if (object.contains(QStringLiteral(u"captureSourceId")))
        value.captureSourceId = object.value(QStringLiteral(u"captureSourceId")).toString();
    if (object.contains(QStringLiteral(u"screenSourceId")))
        value.screenSourceId = object.value(QStringLiteral(u"screenSourceId")).toString();
    if (object.contains(QStringLiteral(u"liveInputId")))
        value.liveInputId = object.value(QStringLiteral(u"liveInputId")).toString();
    if (object.contains(QStringLiteral(u"keepFromSlide")))
        value.keepFromSlide = KeepFromSlideOptionsFromJson(object.value(QStringLiteral(u"keepFromSlide")).toObject());
    if (object.contains(QStringLiteral(u"animationSteps")))
        value.animationSteps = decodeList<AnimationStep>(object.value(QStringLiteral(u"animationSteps")), AnimationStepFromJson);
    if (object.contains(QStringLiteral(u"builds")))
        value.builds = decodeList<AnimationStep>(object.value(QStringLiteral(u"builds")), AnimationStepFromJson);
    if (object.contains(QStringLiteral(u"tilt")))
        value.tilt = object.value(QStringLiteral(u"tilt")).toDouble();
    if (object.contains(QStringLiteral(u"swing")))
        value.swing = object.value(QStringLiteral(u"swing")).toDouble();
    if (object.contains(QStringLiteral(u"tiltPivot")))
        value.tiltPivot = TiltPivotFromString(object.value(QStringLiteral(u"tiltPivot")).toString());
    if (object.contains(QStringLiteral(u"keystoneTop")))
        value.keystoneTop = object.value(QStringLiteral(u"keystoneTop")).toDouble();
    if (object.contains(QStringLiteral(u"keystoneBottom")))
        value.keystoneBottom = object.value(QStringLiteral(u"keystoneBottom")).toDouble();
    if (object.contains(QStringLiteral(u"skewX")))
        value.skewX = object.value(QStringLiteral(u"skewX")).toDouble();
    if (object.contains(QStringLiteral(u"skewY")))
        value.skewY = object.value(QStringLiteral(u"skewY")).toDouble();
    if (object.contains(QStringLiteral(u"keystoneMode")))
        value.keystoneMode = KeystoneModeFromString(object.value(QStringLiteral(u"keystoneMode")).toString());
    if (object.contains(QStringLiteral(u"photoSpot")))
        value.photoSpot = object.value(QStringLiteral(u"photoSpot")).toBool();
    return value;
}

QJsonObject toJson(const AnimationStep& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"kind"), toString(value.kind));
    object.insert(QStringLiteral(u"animation"), toString(value.animation));
    object.insert(QStringLiteral(u"trigger"), toString(value.trigger));
    if (value.delaySeconds)
        object.insert(QStringLiteral(u"delaySeconds"), *value.delaySeconds);
    object.insert(QStringLiteral(u"durationSeconds"), value.durationSeconds);
    if (value.ramp)
        object.insert(QStringLiteral(u"ramp"), toString(*value.ramp));
    if (value.withFade)
        object.insert(QStringLiteral(u"withFade"), *value.withFade);
    if (value.ranges)
        object.insert(QStringLiteral(u"ranges"), encodeList(*value.ranges, [](const AnimationRange& item) { return toJson(item); }));
    if (value.edge)
        object.insert(QStringLiteral(u"edge"), toString(*value.edge));
    if (value.offsetX)
        object.insert(QStringLiteral(u"offsetX"), *value.offsetX);
    if (value.offsetY)
        object.insert(QStringLiteral(u"offsetY"), *value.offsetY);
    if (value.fromScale)
        object.insert(QStringLiteral(u"fromScale"), *value.fromScale);
    if (value.amount)
        object.insert(QStringLiteral(u"amount"), *value.amount);
    if (value.softEdge)
        object.insert(QStringLiteral(u"softEdge"), *value.softEdge);
    if (value.cursor)
        object.insert(QStringLiteral(u"cursor"), *value.cursor);
    if (value.colorHex)
        object.insert(QStringLiteral(u"colorHex"), *value.colorHex);
    if (value.placeholderUnderline)
        object.insert(QStringLiteral(u"placeholderUnderline"), *value.placeholderUnderline);
    if (value.drawStart)
        object.insert(QStringLiteral(u"drawStart"), *value.drawStart);
    if (value.reverse)
        object.insert(QStringLiteral(u"reverse"), *value.reverse);
    if (value.toObject)
        object.insert(QStringLiteral(u"toObject"), toJson(**value.toObject));
    if (value.videoPush)
        object.insert(QStringLiteral(u"videoPush"), toJson(*value.videoPush));
    if (value.fromObject)
        object.insert(QStringLiteral(u"fromObject"), toJson(**value.fromObject));
    return object;
}

AnimationStep AnimationStepFromJson(const QJsonObject& object)
{
    AnimationStep value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.kind = AnimationKindFromString(object.value(QStringLiteral(u"kind")).toString());
    value.animation = StepAnimationFromString(object.value(QStringLiteral(u"animation")).toString());
    value.trigger = AnimationTriggerFromString(object.value(QStringLiteral(u"trigger")).toString());
    if (object.contains(QStringLiteral(u"delaySeconds")))
        value.delaySeconds = object.value(QStringLiteral(u"delaySeconds")).toDouble();
    value.durationSeconds = object.value(QStringLiteral(u"durationSeconds")).toDouble();
    if (object.contains(QStringLiteral(u"ramp")))
        value.ramp = AnimationRampFromString(object.value(QStringLiteral(u"ramp")).toString());
    if (object.contains(QStringLiteral(u"withFade")))
        value.withFade = object.value(QStringLiteral(u"withFade")).toBool();
    if (object.contains(QStringLiteral(u"ranges")))
        value.ranges = decodeList<AnimationRange>(object.value(QStringLiteral(u"ranges")), AnimationRangeFromJson);
    if (object.contains(QStringLiteral(u"edge")))
        value.edge = AnimationEdgeFromString(object.value(QStringLiteral(u"edge")).toString());
    if (object.contains(QStringLiteral(u"offsetX")))
        value.offsetX = object.value(QStringLiteral(u"offsetX")).toDouble();
    if (object.contains(QStringLiteral(u"offsetY")))
        value.offsetY = object.value(QStringLiteral(u"offsetY")).toDouble();
    if (object.contains(QStringLiteral(u"fromScale")))
        value.fromScale = object.value(QStringLiteral(u"fromScale")).toDouble();
    if (object.contains(QStringLiteral(u"amount")))
        value.amount = object.value(QStringLiteral(u"amount")).toDouble();
    if (object.contains(QStringLiteral(u"softEdge")))
        value.softEdge = object.value(QStringLiteral(u"softEdge")).toDouble();
    if (object.contains(QStringLiteral(u"cursor")))
        value.cursor = object.value(QStringLiteral(u"cursor")).toBool();
    if (object.contains(QStringLiteral(u"colorHex")))
        value.colorHex = object.value(QStringLiteral(u"colorHex")).toString();
    if (object.contains(QStringLiteral(u"placeholderUnderline")))
        value.placeholderUnderline = object.value(QStringLiteral(u"placeholderUnderline")).toBool();
    if (object.contains(QStringLiteral(u"drawStart")))
        value.drawStart = object.value(QStringLiteral(u"drawStart")).toDouble();
    if (object.contains(QStringLiteral(u"reverse")))
        value.reverse = object.value(QStringLiteral(u"reverse")).toBool();
    if (object.contains(QStringLiteral(u"toObject")))
        value.toObject = std::make_shared<SlideObject>(SlideObjectFromJson(object.value(QStringLiteral(u"toObject")).toObject()));
    if (object.contains(QStringLiteral(u"videoPush")))
        value.videoPush = VideoPushFromJson(object.value(QStringLiteral(u"videoPush")).toObject());
    if (object.contains(QStringLiteral(u"fromObject")))
        value.fromObject = std::make_shared<SlideObject>(SlideObjectFromJson(object.value(QStringLiteral(u"fromObject")).toObject()));
    return value;
}

QJsonObject toJson(const AnimationPreset& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"steps"), encodeList(value.steps, [](const AnimationStep& item) { return toJson(item); }));
    if (value.staggerSeconds)
        object.insert(QStringLiteral(u"staggerSeconds"), *value.staggerSeconds);
    if (value.scroll)
        object.insert(QStringLiteral(u"scroll"), toJson(*value.scroll));
    if (value.tilt)
        object.insert(QStringLiteral(u"tilt"), *value.tilt);
    return object;
}

AnimationPreset AnimationPresetFromJson(const QJsonObject& object)
{
    AnimationPreset value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.steps = decodeList<AnimationStep>(object.value(QStringLiteral(u"steps")), AnimationStepFromJson);
    if (object.contains(QStringLiteral(u"staggerSeconds")))
        value.staggerSeconds = object.value(QStringLiteral(u"staggerSeconds")).toDouble();
    if (object.contains(QStringLiteral(u"scroll")))
        value.scroll = BlockScrollFromJson(object.value(QStringLiteral(u"scroll")).toObject());
    if (object.contains(QStringLiteral(u"tilt")))
        value.tilt = object.value(QStringLiteral(u"tilt")).toDouble();
    return value;
}

QJsonObject toJson(const AnimationPresetBoard& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"presets"), encodeList(value.presets, [](const AnimationPreset& item) { return toJson(item); }));
    if (value.defaultIn)
        object.insert(QStringLiteral(u"defaultIn"), toJson(*value.defaultIn));
    if (value.defaultOut)
        object.insert(QStringLiteral(u"defaultOut"), toJson(*value.defaultOut));
    return object;
}

AnimationPresetBoard AnimationPresetBoardFromJson(const QJsonObject& object)
{
    AnimationPresetBoard value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.presets = decodeList<AnimationPreset>(object.value(QStringLiteral(u"presets")), AnimationPresetFromJson);
    if (object.contains(QStringLiteral(u"defaultIn")))
        value.defaultIn = AnimationStepFromJson(object.value(QStringLiteral(u"defaultIn")).toObject());
    if (object.contains(QStringLiteral(u"defaultOut")))
        value.defaultOut = AnimationStepFromJson(object.value(QStringLiteral(u"defaultOut")).toObject());
    return value;
}

QJsonObject toJson(const CueMedia& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"mediaId"), value.mediaId);
    if (value.mode)
        object.insert(QStringLiteral(u"mode"), toString(*value.mode));
    if (value.layer)
        object.insert(QStringLiteral(u"layer"), toString(*value.layer));
    if (value.loops)
        object.insert(QStringLiteral(u"loops"), *value.loops);
    if (value.classification)
        object.insert(QStringLiteral(u"classification"), toString(*value.classification));
    if (value.scaleMode)
        object.insert(QStringLiteral(u"scaleMode"), toString(*value.scaleMode));
    if (value.endFade)
        object.insert(QStringLiteral(u"endFade"), toString(*value.endFade));
    if (value.layerId)
        object.insert(QStringLiteral(u"layerId"), *value.layerId);
    return object;
}

CueMedia CueMediaFromJson(const QJsonObject& object)
{
    CueMedia value;
    value.mediaId = object.value(QStringLiteral(u"mediaId")).toString();
    if (object.contains(QStringLiteral(u"mode")))
        value.mode = CueMediaModeFromString(object.value(QStringLiteral(u"mode")).toString());
    if (object.contains(QStringLiteral(u"layer")))
        value.layer = CueMediaLayerFromString(object.value(QStringLiteral(u"layer")).toString());
    if (object.contains(QStringLiteral(u"loops")))
        value.loops = object.value(QStringLiteral(u"loops")).toBool();
    if (object.contains(QStringLiteral(u"classification")))
        value.classification = MediaClassificationFromString(object.value(QStringLiteral(u"classification")).toString());
    if (object.contains(QStringLiteral(u"scaleMode")))
        value.scaleMode = MediaScaleModeFromString(object.value(QStringLiteral(u"scaleMode")).toString());
    if (object.contains(QStringLiteral(u"endFade")))
        value.endFade = MediaEndFadeFromString(object.value(QStringLiteral(u"endFade")).toString());
    if (object.contains(QStringLiteral(u"layerId")))
        value.layerId = object.value(QStringLiteral(u"layerId")).toString();
    return value;
}

QJsonObject toJson(const AutoAdvance& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"delaySeconds"), value.delaySeconds);
    if (value.loopToStart)
        object.insert(QStringLiteral(u"loopToStart"), *value.loopToStart);
    if (value.afterPlayback)
        object.insert(QStringLiteral(u"afterPlayback"), *value.afterPlayback);
    return object;
}

AutoAdvance AutoAdvanceFromJson(const QJsonObject& object)
{
    AutoAdvance value;
    value.delaySeconds = object.value(QStringLiteral(u"delaySeconds")).toDouble();
    if (object.contains(QStringLiteral(u"loopToStart")))
        value.loopToStart = object.value(QStringLiteral(u"loopToStart")).toBool();
    if (object.contains(QStringLiteral(u"afterPlayback")))
        value.afterPlayback = object.value(QStringLiteral(u"afterPlayback")).toBool();
    return value;
}

QJsonObject toJson(const OverrideDesign& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"themeId"), value.themeId);
    object.insert(QStringLiteral(u"themeSlideName"), value.themeSlideName);
    return object;
}

OverrideDesign OverrideDesignFromJson(const QJsonObject& object)
{
    OverrideDesign value;
    value.themeId = object.value(QStringLiteral(u"themeId")).toString();
    value.themeSlideName = object.value(QStringLiteral(u"themeSlideName")).toString();
    return value;
}

QJsonObject toJson(const SlideAction& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"kind"), toString(value.kind));
    if (value.layer)
        object.insert(QStringLiteral(u"layer"), *value.layer);
    if (value.presetId)
        object.insert(QStringLiteral(u"presetId"), *value.presetId);
    if (value.mediaId)
        object.insert(QStringLiteral(u"mediaId"), *value.mediaId);
    if (value.alertId)
        object.insert(QStringLiteral(u"alertId"), *value.alertId);
    if (value.timerId)
        object.insert(QStringLiteral(u"timerId"), *value.timerId);
    if (value.timerMode)
        object.insert(QStringLiteral(u"timerMode"), toString(*value.timerMode));
    if (value.timerDurationSeconds)
        object.insert(QStringLiteral(u"timerDurationSeconds"), *value.timerDurationSeconds);
    if (value.timerHour)
        object.insert(QStringLiteral(u"timerHour"), *value.timerHour);
    if (value.timerMinute)
        object.insert(QStringLiteral(u"timerMinute"), *value.timerMinute);
    if (value.comboId)
        object.insert(QStringLiteral(u"comboId"), *value.comboId);
    if (value.midiKind)
        object.insert(QStringLiteral(u"midiKind"), toString(*value.midiKind));
    if (value.midiChannel)
        object.insert(QStringLiteral(u"midiChannel"), *value.midiChannel);
    if (value.midiNumber)
        object.insert(QStringLiteral(u"midiNumber"), *value.midiNumber);
    if (value.midiValue)
        object.insert(QStringLiteral(u"midiValue"), *value.midiValue);
    if (value.midiDeviceId)
        object.insert(QStringLiteral(u"midiDeviceId"), *value.midiDeviceId);
    if (value.capturePresetId)
        object.insert(QStringLiteral(u"capturePresetId"), *value.capturePresetId);
    if (value.capturePrivacy)
        object.insert(QStringLiteral(u"capturePrivacy"), *value.capturePrivacy);
    if (value.presentationId)
        object.insert(QStringLiteral(u"presentationId"), *value.presentationId);
    if (value.slideIndex)
        object.insert(QStringLiteral(u"slideIndex"), *value.slideIndex);
    if (value.confidenceLayoutId)
        object.insert(QStringLiteral(u"confidenceLayoutId"), *value.confidenceLayoutId);
    if (value.confidenceScreenId)
        object.insert(QStringLiteral(u"confidenceScreenId"), *value.confidenceScreenId);
    if (value.overlayId)
        object.insert(QStringLiteral(u"overlayId"), *value.overlayId);
    if (value.inputSourceKind)
        object.insert(QStringLiteral(u"inputSourceKind"), toString(*value.inputSourceKind));
    if (value.inputSourceId)
        object.insert(QStringLiteral(u"inputSourceId"), *value.inputSourceId);
    if (value.liveInputId)
        object.insert(QStringLiteral(u"liveInputId"), *value.liveInputId);
    if (value.audioInputId)
        object.insert(QStringLiteral(u"audioInputId"), *value.audioInputId);
    if (value.playlistId)
        object.insert(QStringLiteral(u"playlistId"), *value.playlistId);
    if (value.audioItemId)
        object.insert(QStringLiteral(u"audioItemId"), *value.audioItemId);
    if (value.audioEntryId)
        object.insert(QStringLiteral(u"audioEntryId"), *value.audioEntryId);
    if (value.audioRepeat)
        object.insert(QStringLiteral(u"audioRepeat"), *value.audioRepeat);
    if (value.delaySeconds)
        object.insert(QStringLiteral(u"delaySeconds"), *value.delaySeconds);
    return object;
}

SlideAction SlideActionFromJson(const QJsonObject& object)
{
    SlideAction value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.kind = SlideActionKindFromString(object.value(QStringLiteral(u"kind")).toString());
    if (object.contains(QStringLiteral(u"layer")))
        value.layer = object.value(QStringLiteral(u"layer")).toString();
    if (object.contains(QStringLiteral(u"presetId")))
        value.presetId = object.value(QStringLiteral(u"presetId")).toString();
    if (object.contains(QStringLiteral(u"mediaId")))
        value.mediaId = object.value(QStringLiteral(u"mediaId")).toString();
    if (object.contains(QStringLiteral(u"alertId")))
        value.alertId = object.value(QStringLiteral(u"alertId")).toString();
    if (object.contains(QStringLiteral(u"timerId")))
        value.timerId = object.value(QStringLiteral(u"timerId")).toString();
    if (object.contains(QStringLiteral(u"timerMode")))
        value.timerMode = TimerModeFromString(object.value(QStringLiteral(u"timerMode")).toString());
    if (object.contains(QStringLiteral(u"timerDurationSeconds")))
        value.timerDurationSeconds = object.value(QStringLiteral(u"timerDurationSeconds")).toDouble();
    if (object.contains(QStringLiteral(u"timerHour")))
        value.timerHour = object.value(QStringLiteral(u"timerHour")).toInt();
    if (object.contains(QStringLiteral(u"timerMinute")))
        value.timerMinute = object.value(QStringLiteral(u"timerMinute")).toInt();
    if (object.contains(QStringLiteral(u"comboId")))
        value.comboId = object.value(QStringLiteral(u"comboId")).toString();
    if (object.contains(QStringLiteral(u"midiKind")))
        value.midiKind = MIDIMessageKindFromString(object.value(QStringLiteral(u"midiKind")).toString());
    if (object.contains(QStringLiteral(u"midiChannel")))
        value.midiChannel = object.value(QStringLiteral(u"midiChannel")).toInt();
    if (object.contains(QStringLiteral(u"midiNumber")))
        value.midiNumber = object.value(QStringLiteral(u"midiNumber")).toInt();
    if (object.contains(QStringLiteral(u"midiValue")))
        value.midiValue = object.value(QStringLiteral(u"midiValue")).toInt();
    if (object.contains(QStringLiteral(u"midiDeviceId")))
        value.midiDeviceId = object.value(QStringLiteral(u"midiDeviceId")).toString();
    if (object.contains(QStringLiteral(u"capturePresetId")))
        value.capturePresetId = object.value(QStringLiteral(u"capturePresetId")).toString();
    if (object.contains(QStringLiteral(u"capturePrivacy")))
        value.capturePrivacy = object.value(QStringLiteral(u"capturePrivacy")).toString();
    if (object.contains(QStringLiteral(u"presentationId")))
        value.presentationId = object.value(QStringLiteral(u"presentationId")).toString();
    if (object.contains(QStringLiteral(u"slideIndex")))
        value.slideIndex = object.value(QStringLiteral(u"slideIndex")).toInt();
    if (object.contains(QStringLiteral(u"confidenceLayoutId")))
        value.confidenceLayoutId = object.value(QStringLiteral(u"confidenceLayoutId")).toString();
    if (object.contains(QStringLiteral(u"confidenceScreenId")))
        value.confidenceScreenId = object.value(QStringLiteral(u"confidenceScreenId")).toString();
    if (object.contains(QStringLiteral(u"overlayId")))
        value.overlayId = object.value(QStringLiteral(u"overlayId")).toString();
    if (object.contains(QStringLiteral(u"inputSourceKind")))
        value.inputSourceKind = CaptureSourceKindFromString(object.value(QStringLiteral(u"inputSourceKind")).toString());
    if (object.contains(QStringLiteral(u"inputSourceId")))
        value.inputSourceId = object.value(QStringLiteral(u"inputSourceId")).toString();
    if (object.contains(QStringLiteral(u"liveInputId")))
        value.liveInputId = object.value(QStringLiteral(u"liveInputId")).toString();
    if (object.contains(QStringLiteral(u"audioInputId")))
        value.audioInputId = object.value(QStringLiteral(u"audioInputId")).toString();
    if (object.contains(QStringLiteral(u"playlistId")))
        value.playlistId = object.value(QStringLiteral(u"playlistId")).toString();
    if (object.contains(QStringLiteral(u"audioItemId")))
        value.audioItemId = object.value(QStringLiteral(u"audioItemId")).toString();
    if (object.contains(QStringLiteral(u"audioEntryId")))
        value.audioEntryId = object.value(QStringLiteral(u"audioEntryId")).toString();
    if (object.contains(QStringLiteral(u"audioRepeat")))
        value.audioRepeat = object.value(QStringLiteral(u"audioRepeat")).toBool();
    if (object.contains(QStringLiteral(u"delaySeconds")))
        value.delaySeconds = object.value(QStringLiteral(u"delaySeconds")).toDouble();
    return value;
}

QJsonObject toJson(const SlideVersion& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"at"), value.at);
    object.insert(QStringLiteral(u"reason"), value.reason);
    object.insert(QStringLiteral(u"slide"), toJson(*value.slide));
    return object;
}

SlideVersion SlideVersionFromJson(const QJsonObject& object)
{
    SlideVersion value;
    value.at = object.value(QStringLiteral(u"at")).toString();
    value.reason = object.value(QStringLiteral(u"reason")).toString();
    value.slide = std::make_shared<Slide>(SlideFromJson(object.value(QStringLiteral(u"slide")).toObject()));
    return value;
}

QJsonObject toJson(const Transition& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"transitionKind"), toString(value.transitionKind));
    if (value.durationSeconds)
        object.insert(QStringLiteral(u"durationSeconds"), *value.durationSeconds);
    if (value.colorHex)
        object.insert(QStringLiteral(u"colorHex"), *value.colorHex);
    return object;
}

Transition TransitionFromJson(const QJsonObject& object)
{
    Transition value;
    value.transitionKind = TransitionKindFromString(object.value(QStringLiteral(u"transitionKind")).toString());
    if (object.contains(QStringLiteral(u"durationSeconds")))
        value.durationSeconds = object.value(QStringLiteral(u"durationSeconds")).toDouble();
    if (object.contains(QStringLiteral(u"colorHex")))
        value.colorHex = object.value(QStringLiteral(u"colorHex")).toString();
    return value;
}

QJsonObject toJson(const Slide& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"objects"), encodeList(value.objects, [](const SlideObject& item) { return toJson(item); }));
    if (value.background)
        object.insert(QStringLiteral(u"background"), toJson(*value.background));
    if (value.backgroundFill)
        object.insert(QStringLiteral(u"backgroundFill"), toJson(*value.backgroundFill));
    if (value.sectionId)
        object.insert(QStringLiteral(u"sectionId"), *value.sectionId);
    if (value.folder)
        object.insert(QStringLiteral(u"folder"), *value.folder);
    if (value.themeSlideName)
        object.insert(QStringLiteral(u"themeSlideName"), *value.themeSlideName);
    if (value.themeId)
        object.insert(QStringLiteral(u"themeId"), *value.themeId);
    if (value.unthemed)
        object.insert(QStringLiteral(u"unthemed"), *value.unthemed);
    if (value.overrideDesigns)
        object.insert(QStringLiteral(u"overrideDesigns"), encodeList(*value.overrideDesigns, [](const OverrideDesign& item) { return toJson(item); }));
    if (value.actions)
        object.insert(QStringLiteral(u"actions"), encodeList(*value.actions, [](const SlideAction& item) { return toJson(item); }));
    if (value.notes)
        object.insert(QStringLiteral(u"notes"), *value.notes);
    if (value.autoAdvance)
        object.insert(QStringLiteral(u"autoAdvance"), toJson(*value.autoAdvance));
    if (value.transition)
        object.insert(QStringLiteral(u"transition"), toJson(*value.transition));
    if (value.animationOrder)
        object.insert(QStringLiteral(u"animationOrder"), encodeList(*value.animationOrder));
    if (value.buildOrder)
        object.insert(QStringLiteral(u"buildOrder"), encodeList(*value.buildOrder));
    if (value.keepWords)
        object.insert(QStringLiteral(u"keepWords"), *value.keepWords);
    if (value.history)
        object.insert(QStringLiteral(u"history"), encodeList(*value.history, [](const SlideVersion& item) { return toJson(item); }));
    return object;
}

Slide SlideFromJson(const QJsonObject& object)
{
    Slide value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.objects = decodeList<SlideObject>(object.value(QStringLiteral(u"objects")), SlideObjectFromJson);
    if (object.contains(QStringLiteral(u"background")))
        value.background = CueMediaFromJson(object.value(QStringLiteral(u"background")).toObject());
    if (object.contains(QStringLiteral(u"backgroundFill")))
        value.backgroundFill = ObjectFillFromJson(object.value(QStringLiteral(u"backgroundFill")).toObject());
    if (object.contains(QStringLiteral(u"sectionId")))
        value.sectionId = object.value(QStringLiteral(u"sectionId")).toString();
    if (object.contains(QStringLiteral(u"folder")))
        value.folder = object.value(QStringLiteral(u"folder")).toString();
    if (object.contains(QStringLiteral(u"themeSlideName")))
        value.themeSlideName = object.value(QStringLiteral(u"themeSlideName")).toString();
    if (object.contains(QStringLiteral(u"themeId")))
        value.themeId = object.value(QStringLiteral(u"themeId")).toString();
    if (object.contains(QStringLiteral(u"unthemed")))
        value.unthemed = object.value(QStringLiteral(u"unthemed")).toBool();
    if (object.contains(QStringLiteral(u"overrideDesigns")))
        value.overrideDesigns = decodeList<OverrideDesign>(object.value(QStringLiteral(u"overrideDesigns")), OverrideDesignFromJson);
    if (object.contains(QStringLiteral(u"actions")))
        value.actions = decodeList<SlideAction>(object.value(QStringLiteral(u"actions")), SlideActionFromJson);
    if (object.contains(QStringLiteral(u"notes")))
        value.notes = object.value(QStringLiteral(u"notes")).toString();
    if (object.contains(QStringLiteral(u"autoAdvance")))
        value.autoAdvance = AutoAdvanceFromJson(object.value(QStringLiteral(u"autoAdvance")).toObject());
    if (object.contains(QStringLiteral(u"transition")))
        value.transition = TransitionFromJson(object.value(QStringLiteral(u"transition")).toObject());
    if (object.contains(QStringLiteral(u"animationOrder")))
        value.animationOrder = decodeList<QString>(object.value(QStringLiteral(u"animationOrder")));
    if (object.contains(QStringLiteral(u"buildOrder")))
        value.buildOrder = decodeList<QString>(object.value(QStringLiteral(u"buildOrder")));
    if (object.contains(QStringLiteral(u"keepWords")))
        value.keepWords = object.value(QStringLiteral(u"keepWords")).toBool();
    if (object.contains(QStringLiteral(u"history")))
        value.history = decodeList<SlideVersion>(object.value(QStringLiteral(u"history")), SlideVersionFromJson);
    return value;
}

QJsonObject toJson(const PresentationSection& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    if (value.background)
        object.insert(QStringLiteral(u"background"), toJson(*value.background));
    if (value.colorHex)
        object.insert(QStringLiteral(u"colorHex"), *value.colorHex);
    return object;
}

PresentationSection PresentationSectionFromJson(const QJsonObject& object)
{
    PresentationSection value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    if (object.contains(QStringLiteral(u"background")))
        value.background = CueMediaFromJson(object.value(QStringLiteral(u"background")).toObject());
    if (object.contains(QStringLiteral(u"colorHex")))
        value.colorHex = object.value(QStringLiteral(u"colorHex")).toString();
    return value;
}

QJsonObject toJson(const CCLIInfo& value)
{
    QJsonObject object;
    if (value.songNumber)
        object.insert(QStringLiteral(u"songNumber"), *value.songNumber);
    if (value.songTitle)
        object.insert(QStringLiteral(u"songTitle"), *value.songTitle);
    if (value.author)
        object.insert(QStringLiteral(u"author"), *value.author);
    if (value.publisher)
        object.insert(QStringLiteral(u"publisher"), *value.publisher);
    if (value.copyrightYear)
        object.insert(QStringLiteral(u"copyrightYear"), *value.copyrightYear);
    if (value.copyright)
        object.insert(QStringLiteral(u"copyright"), *value.copyright);
    return object;
}

CCLIInfo CCLIInfoFromJson(const QJsonObject& object)
{
    CCLIInfo value;
    if (object.contains(QStringLiteral(u"songNumber")))
        value.songNumber = object.value(QStringLiteral(u"songNumber")).toInt();
    if (object.contains(QStringLiteral(u"songTitle")))
        value.songTitle = object.value(QStringLiteral(u"songTitle")).toString();
    if (object.contains(QStringLiteral(u"author")))
        value.author = object.value(QStringLiteral(u"author")).toString();
    if (object.contains(QStringLiteral(u"publisher")))
        value.publisher = object.value(QStringLiteral(u"publisher")).toString();
    if (object.contains(QStringLiteral(u"copyrightYear")))
        value.copyrightYear = object.value(QStringLiteral(u"copyrightYear")).toInt();
    if (object.contains(QStringLiteral(u"copyright")))
        value.copyright = object.value(QStringLiteral(u"copyright")).toString();
    return value;
}

QJsonObject toJson(const Arrangement& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"sectionIds"), encodeList(value.sectionIds));
    return object;
}

Arrangement ArrangementFromJson(const QJsonObject& object)
{
    Arrangement value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.sectionIds = decodeList<QString>(object.value(QStringLiteral(u"sectionIds")));
    return value;
}

QJsonObject toJson(const PresentationOrigin& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"source"), toString(value.source));
    if (value.detail)
        object.insert(QStringLiteral(u"detail"), *value.detail);
    if (value.createdAt)
        object.insert(QStringLiteral(u"createdAt"), *value.createdAt);
    return object;
}

PresentationOrigin PresentationOriginFromJson(const QJsonObject& object)
{
    PresentationOrigin value;
    value.source = PresentationOriginSourceFromString(object.value(QStringLiteral(u"source")).toString());
    if (object.contains(QStringLiteral(u"detail")))
        value.detail = object.value(QStringLiteral(u"detail")).toString();
    if (object.contains(QStringLiteral(u"createdAt")))
        value.createdAt = object.value(QStringLiteral(u"createdAt")).toString();
    return value;
}

QJsonObject toJson(const ClipFade& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"seconds"), value.seconds);
    if (value.shape)
        object.insert(QStringLiteral(u"shape"), *value.shape);
    if (value.midpoint)
        object.insert(QStringLiteral(u"midpoint"), *value.midpoint);
    if (value.placement)
        object.insert(QStringLiteral(u"placement"), *value.placement);
    return object;
}

ClipFade ClipFadeFromJson(const QJsonObject& object)
{
    ClipFade value;
    value.seconds = object.value(QStringLiteral(u"seconds")).toDouble();
    if (object.contains(QStringLiteral(u"shape")))
        value.shape = object.value(QStringLiteral(u"shape")).toString();
    if (object.contains(QStringLiteral(u"midpoint")))
        value.midpoint = object.value(QStringLiteral(u"midpoint")).toDouble();
    if (object.contains(QStringLiteral(u"placement")))
        value.placement = object.value(QStringLiteral(u"placement")).toString();
    return value;
}

QJsonObject toJson(const TimelineCue& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"lane"), value.lane);
    object.insert(QStringLiteral(u"at"), value.at);
    if (value.duration)
        object.insert(QStringLiteral(u"duration"), *value.duration);
    if (value.sectionId)
        object.insert(QStringLiteral(u"sectionId"), *value.sectionId);
    if (value.sectionOccurrence)
        object.insert(QStringLiteral(u"sectionOccurrence"), *value.sectionOccurrence);
    if (value.slideId)
        object.insert(QStringLiteral(u"slideId"), *value.slideId);
    if (value.mediaId)
        object.insert(QStringLiteral(u"mediaId"), *value.mediaId);
    if (value.overlayId)
        object.insert(QStringLiteral(u"overlayId"), *value.overlayId);
    if (value.alertId)
        object.insert(QStringLiteral(u"alertId"), *value.alertId);
    if (value.liveInputId)
        object.insert(QStringLiteral(u"liveInputId"), *value.liveInputId);
    if (value.actions)
        object.insert(QStringLiteral(u"actions"), encodeList(*value.actions, [](const SlideAction& item) { return toJson(item); }));
    if (value.inPoint)
        object.insert(QStringLiteral(u"inPoint"), *value.inPoint);
    if (value.fadeIn)
        object.insert(QStringLiteral(u"fadeIn"), toJson(*value.fadeIn));
    if (value.fadeOut)
        object.insert(QStringLiteral(u"fadeOut"), toJson(*value.fadeOut));
    if (value.edgeFades)
        object.insert(QStringLiteral(u"edgeFades"), *value.edgeFades);
    return object;
}

TimelineCue TimelineCueFromJson(const QJsonObject& object)
{
    TimelineCue value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.lane = object.value(QStringLiteral(u"lane")).toString();
    value.at = object.value(QStringLiteral(u"at")).toDouble();
    if (object.contains(QStringLiteral(u"duration")))
        value.duration = object.value(QStringLiteral(u"duration")).toDouble();
    if (object.contains(QStringLiteral(u"sectionId")))
        value.sectionId = object.value(QStringLiteral(u"sectionId")).toString();
    if (object.contains(QStringLiteral(u"sectionOccurrence")))
        value.sectionOccurrence = object.value(QStringLiteral(u"sectionOccurrence")).toInt();
    if (object.contains(QStringLiteral(u"slideId")))
        value.slideId = object.value(QStringLiteral(u"slideId")).toString();
    if (object.contains(QStringLiteral(u"mediaId")))
        value.mediaId = object.value(QStringLiteral(u"mediaId")).toString();
    if (object.contains(QStringLiteral(u"overlayId")))
        value.overlayId = object.value(QStringLiteral(u"overlayId")).toString();
    if (object.contains(QStringLiteral(u"alertId")))
        value.alertId = object.value(QStringLiteral(u"alertId")).toString();
    if (object.contains(QStringLiteral(u"liveInputId")))
        value.liveInputId = object.value(QStringLiteral(u"liveInputId")).toString();
    if (object.contains(QStringLiteral(u"actions")))
        value.actions = decodeList<SlideAction>(object.value(QStringLiteral(u"actions")), SlideActionFromJson);
    if (object.contains(QStringLiteral(u"inPoint")))
        value.inPoint = object.value(QStringLiteral(u"inPoint")).toDouble();
    if (object.contains(QStringLiteral(u"fadeIn")))
        value.fadeIn = ClipFadeFromJson(object.value(QStringLiteral(u"fadeIn")).toObject());
    if (object.contains(QStringLiteral(u"fadeOut")))
        value.fadeOut = ClipFadeFromJson(object.value(QStringLiteral(u"fadeOut")).toObject());
    if (object.contains(QStringLiteral(u"edgeFades")))
        value.edgeFades = object.value(QStringLiteral(u"edgeFades")).toBool();
    return value;
}

QJsonObject toJson(const SongMapBlock& value)
{
    QJsonObject object;
    if (value.sectionId)
        object.insert(QStringLiteral(u"sectionId"), *value.sectionId);
    object.insert(QStringLiteral(u"occurrence"), value.occurrence);
    object.insert(QStringLiteral(u"start"), value.start);
    object.insert(QStringLiteral(u"length"), value.length);
    object.insert(QStringLiteral(u"audioSectionIds"), encodeList(value.audioSectionIds));
    return object;
}

SongMapBlock SongMapBlockFromJson(const QJsonObject& object)
{
    SongMapBlock value;
    if (object.contains(QStringLiteral(u"sectionId")))
        value.sectionId = object.value(QStringLiteral(u"sectionId")).toString();
    value.occurrence = object.value(QStringLiteral(u"occurrence")).toInt();
    value.start = object.value(QStringLiteral(u"start")).toDouble();
    value.length = object.value(QStringLiteral(u"length")).toDouble();
    value.audioSectionIds = decodeList<QString>(object.value(QStringLiteral(u"audioSectionIds")));
    return value;
}

QJsonObject toJson(const PresentationTimeline& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    if (value.arrangementId)
        object.insert(QStringLiteral(u"arrangementId"), *value.arrangementId);
    object.insert(QStringLiteral(u"timecodeEnabled"), value.timecodeEnabled);
    object.insert(QStringLiteral(u"timecodeStart"), value.timecodeStart);
    if (value.length)
        object.insert(QStringLiteral(u"length"), *value.length);
    object.insert(QStringLiteral(u"cues"), encodeList(value.cues, [](const TimelineCue& item) { return toJson(item); }));
    if (value.mapLayout)
        object.insert(QStringLiteral(u"mapLayout"), encodeList(*value.mapLayout, [](const SongMapBlock& item) { return toJson(item); }));
    return object;
}

PresentationTimeline PresentationTimelineFromJson(const QJsonObject& object)
{
    PresentationTimeline value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    if (object.contains(QStringLiteral(u"arrangementId")))
        value.arrangementId = object.value(QStringLiteral(u"arrangementId")).toString();
    value.timecodeEnabled = object.value(QStringLiteral(u"timecodeEnabled")).toBool();
    value.timecodeStart = object.value(QStringLiteral(u"timecodeStart")).toInt();
    if (object.contains(QStringLiteral(u"length")))
        value.length = object.value(QStringLiteral(u"length")).toDouble();
    value.cues = decodeList<TimelineCue>(object.value(QStringLiteral(u"cues")), TimelineCueFromJson);
    if (object.contains(QStringLiteral(u"mapLayout")))
        value.mapLayout = decodeList<SongMapBlock>(object.value(QStringLiteral(u"mapLayout")), SongMapBlockFromJson);
    return value;
}

QJsonObject toJson(const AudioSection& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"start"), value.start);
    if (value.sectionId)
        object.insert(QStringLiteral(u"sectionId"), *value.sectionId);
    return object;
}

AudioSection AudioSectionFromJson(const QJsonObject& object)
{
    AudioSection value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.start = object.value(QStringLiteral(u"start")).toDouble();
    if (object.contains(QStringLiteral(u"sectionId")))
        value.sectionId = object.value(QStringLiteral(u"sectionId")).toString();
    return value;
}

QJsonObject toJson(const SongMap& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"recording"), encodeList(value.recording, [](const TimelineCue& item) { return toJson(item); }));
    object.insert(QStringLiteral(u"sections"), encodeList(value.sections, [](const AudioSection& item) { return toJson(item); }));
    if (value.source)
        object.insert(QStringLiteral(u"source"), *value.source);
    return object;
}

SongMap SongMapFromJson(const QJsonObject& object)
{
    SongMap value;
    value.recording = decodeList<TimelineCue>(object.value(QStringLiteral(u"recording")), TimelineCueFromJson);
    value.sections = decodeList<AudioSection>(object.value(QStringLiteral(u"sections")), AudioSectionFromJson);
    if (object.contains(QStringLiteral(u"source")))
        value.source = object.value(QStringLiteral(u"source")).toString();
    return value;
}

QJsonObject toJson(const Presentation& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"presentationKind"), toString(value.presentationKind));
    object.insert(QStringLiteral(u"themeId"), value.themeId);
    if (value.folder)
        object.insert(QStringLiteral(u"folder"), *value.folder);
    if (value.folderId)
        object.insert(QStringLiteral(u"folderId"), *value.folderId);
    object.insert(QStringLiteral(u"slides"), encodeList(value.slides, [](const Slide& item) { return toJson(item); }));
    if (value.canvasWidth)
        object.insert(QStringLiteral(u"canvasWidth"), *value.canvasWidth);
    if (value.canvasHeight)
        object.insert(QStringLiteral(u"canvasHeight"), *value.canvasHeight);
    if (value.background)
        object.insert(QStringLiteral(u"background"), toJson(*value.background));
    if (value.backgroundFill)
        object.insert(QStringLiteral(u"backgroundFill"), toJson(*value.backgroundFill));
    if (value.sections)
        object.insert(QStringLiteral(u"sections"), encodeList(*value.sections, [](const PresentationSection& item) { return toJson(item); }));
    if (value.arrangements)
        object.insert(QStringLiteral(u"arrangements"), encodeList(*value.arrangements, [](const Arrangement& item) { return toJson(item); }));
    if (value.defaultArrangementId)
        object.insert(QStringLiteral(u"defaultArrangementId"), *value.defaultArrangementId);
    if (value.reflowSource)
        object.insert(QStringLiteral(u"reflowSource"), *value.reflowSource);
    if (value.ccli)
        object.insert(QStringLiteral(u"ccli"), toJson(*value.ccli));
    if (value.chordProSource)
        object.insert(QStringLiteral(u"chordProSource"), *value.chordProSource);
    if (value.musicKey)
        object.insert(QStringLiteral(u"musicKey"), *value.musicKey);
    if (value.autoAdvance)
        object.insert(QStringLiteral(u"autoAdvance"), toJson(*value.autoAdvance));
    if (value.transition)
        object.insert(QStringLiteral(u"transition"), toJson(*value.transition));
    if (value.displayKey)
        object.insert(QStringLiteral(u"displayKey"), *value.displayKey);
    if (value.origin)
        object.insert(QStringLiteral(u"origin"), toJson(*value.origin));
    if (value.timelines)
        object.insert(QStringLiteral(u"timelines"), encodeList(*value.timelines, [](const PresentationTimeline& item) { return toJson(item); }));
    if (value.songMap)
        object.insert(QStringLiteral(u"songMap"), toJson(*value.songMap));
    return object;
}

Presentation PresentationFromJson(const QJsonObject& object)
{
    Presentation value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.presentationKind = PresentationKindFromString(object.value(QStringLiteral(u"presentationKind")).toString());
    value.themeId = object.value(QStringLiteral(u"themeId")).toString();
    if (object.contains(QStringLiteral(u"folder")))
        value.folder = object.value(QStringLiteral(u"folder")).toString();
    if (object.contains(QStringLiteral(u"folderId")))
        value.folderId = object.value(QStringLiteral(u"folderId")).toString();
    value.slides = decodeList<Slide>(object.value(QStringLiteral(u"slides")), SlideFromJson);
    if (object.contains(QStringLiteral(u"canvasWidth")))
        value.canvasWidth = object.value(QStringLiteral(u"canvasWidth")).toInt();
    if (object.contains(QStringLiteral(u"canvasHeight")))
        value.canvasHeight = object.value(QStringLiteral(u"canvasHeight")).toInt();
    if (object.contains(QStringLiteral(u"background")))
        value.background = CueMediaFromJson(object.value(QStringLiteral(u"background")).toObject());
    if (object.contains(QStringLiteral(u"backgroundFill")))
        value.backgroundFill = ObjectFillFromJson(object.value(QStringLiteral(u"backgroundFill")).toObject());
    if (object.contains(QStringLiteral(u"sections")))
        value.sections = decodeList<PresentationSection>(object.value(QStringLiteral(u"sections")), PresentationSectionFromJson);
    if (object.contains(QStringLiteral(u"arrangements")))
        value.arrangements = decodeList<Arrangement>(object.value(QStringLiteral(u"arrangements")), ArrangementFromJson);
    if (object.contains(QStringLiteral(u"defaultArrangementId")))
        value.defaultArrangementId = object.value(QStringLiteral(u"defaultArrangementId")).toString();
    if (object.contains(QStringLiteral(u"reflowSource")))
        value.reflowSource = object.value(QStringLiteral(u"reflowSource")).toString();
    if (object.contains(QStringLiteral(u"ccli")))
        value.ccli = CCLIInfoFromJson(object.value(QStringLiteral(u"ccli")).toObject());
    if (object.contains(QStringLiteral(u"chordProSource")))
        value.chordProSource = object.value(QStringLiteral(u"chordProSource")).toString();
    if (object.contains(QStringLiteral(u"musicKey")))
        value.musicKey = object.value(QStringLiteral(u"musicKey")).toString();
    if (object.contains(QStringLiteral(u"autoAdvance")))
        value.autoAdvance = AutoAdvanceFromJson(object.value(QStringLiteral(u"autoAdvance")).toObject());
    if (object.contains(QStringLiteral(u"transition")))
        value.transition = TransitionFromJson(object.value(QStringLiteral(u"transition")).toObject());
    if (object.contains(QStringLiteral(u"displayKey")))
        value.displayKey = object.value(QStringLiteral(u"displayKey")).toString();
    if (object.contains(QStringLiteral(u"origin")))
        value.origin = PresentationOriginFromJson(object.value(QStringLiteral(u"origin")).toObject());
    if (object.contains(QStringLiteral(u"timelines")))
        value.timelines = decodeList<PresentationTimeline>(object.value(QStringLiteral(u"timelines")), PresentationTimelineFromJson);
    if (object.contains(QStringLiteral(u"songMap")))
        value.songMap = SongMapFromJson(object.value(QStringLiteral(u"songMap")).toObject());
    return value;
}

QJsonObject toJson(const VideoMark& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"at"), value.at);
    object.insert(QStringLiteral(u"actions"), encodeList(value.actions, [](const SlideAction& item) { return toJson(item); }));
    if (value.colorHex)
        object.insert(QStringLiteral(u"colorHex"), *value.colorHex);
    return object;
}

VideoMark VideoMarkFromJson(const QJsonObject& object)
{
    VideoMark value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.at = object.value(QStringLiteral(u"at")).toDouble();
    value.actions = decodeList<SlideAction>(object.value(QStringLiteral(u"actions")), SlideActionFromJson);
    if (object.contains(QStringLiteral(u"colorHex")))
        value.colorHex = object.value(QStringLiteral(u"colorHex")).toString();
    return value;
}

QJsonObject toJson(const MediaItem& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"mediaKind"), toString(value.mediaKind));
    object.insert(QStringLiteral(u"classification"), toString(value.classification));
    object.insert(QStringLiteral(u"fileHash"), value.fileHash);
    object.insert(QStringLiteral(u"fileName"), value.fileName);
    object.insert(QStringLiteral(u"fileStatus"), toString(value.fileStatus));
    object.insert(QStringLiteral(u"statusDetail"), value.statusDetail);
    object.insert(QStringLiteral(u"tags"), encodeList(value.tags));
    object.insert(QStringLiteral(u"favorite"), value.favorite);
    object.insert(QStringLiteral(u"collections"), encodeList(value.collections));
    object.insert(QStringLiteral(u"loops"), value.loops);
    if (value.inPoint)
        object.insert(QStringLiteral(u"inPoint"), *value.inPoint);
    if (value.outPoint)
        object.insert(QStringLiteral(u"outPoint"), *value.outPoint);
    if (value.playRate)
        object.insert(QStringLiteral(u"playRate"), *value.playRate);
    if (value.effects)
        object.insert(QStringLiteral(u"effects"), encodeList(*value.effects, [](const Effect& item) { return toJson(item); }));
    if (value.transition)
        object.insert(QStringLiteral(u"transition"), toJson(*value.transition));
    if (value.durationSeconds)
        object.insert(QStringLiteral(u"durationSeconds"), *value.durationSeconds);
    if (value.pixelWidth)
        object.insert(QStringLiteral(u"pixelWidth"), *value.pixelWidth);
    if (value.pixelHeight)
        object.insert(QStringLiteral(u"pixelHeight"), *value.pixelHeight);
    if (value.folder)
        object.insert(QStringLiteral(u"folder"), *value.folder);
    if (value.folderId)
        object.insert(QStringLiteral(u"folderId"), *value.folderId);
    if (value.recordedAt)
        object.insert(QStringLiteral(u"recordedAt"), *value.recordedAt);
    if (value.importedAt)
        object.insert(QStringLiteral(u"importedAt"), *value.importedAt);
    if (value.recordedByPresetId)
        object.insert(QStringLiteral(u"recordedByPresetId"), *value.recordedByPresetId);
    if (value.actions)
        object.insert(QStringLiteral(u"actions"), encodeList(*value.actions, [](const SlideAction& item) { return toJson(item); }));
    if (value.autoAdvance)
        object.insert(QStringLiteral(u"autoAdvance"), toJson(*value.autoAdvance));
    if (value.marks)
        object.insert(QStringLiteral(u"marks"), encodeList(*value.marks, [](const VideoMark& item) { return toJson(item); }));
    return object;
}

MediaItem MediaItemFromJson(const QJsonObject& object)
{
    MediaItem value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.mediaKind = MediaKindFromString(object.value(QStringLiteral(u"mediaKind")).toString());
    value.classification = MediaClassificationFromString(object.value(QStringLiteral(u"classification")).toString());
    value.fileHash = object.value(QStringLiteral(u"fileHash")).toString();
    value.fileName = object.value(QStringLiteral(u"fileName")).toString();
    value.fileStatus = MediaFileStatusFromString(object.value(QStringLiteral(u"fileStatus")).toString());
    value.statusDetail = object.value(QStringLiteral(u"statusDetail")).toString();
    value.tags = decodeList<QString>(object.value(QStringLiteral(u"tags")));
    value.favorite = object.value(QStringLiteral(u"favorite")).toBool();
    value.collections = decodeList<QString>(object.value(QStringLiteral(u"collections")));
    value.loops = object.value(QStringLiteral(u"loops")).toBool();
    if (object.contains(QStringLiteral(u"inPoint")))
        value.inPoint = object.value(QStringLiteral(u"inPoint")).toDouble();
    if (object.contains(QStringLiteral(u"outPoint")))
        value.outPoint = object.value(QStringLiteral(u"outPoint")).toDouble();
    if (object.contains(QStringLiteral(u"playRate")))
        value.playRate = object.value(QStringLiteral(u"playRate")).toDouble();
    if (object.contains(QStringLiteral(u"effects")))
        value.effects = decodeList<Effect>(object.value(QStringLiteral(u"effects")), EffectFromJson);
    if (object.contains(QStringLiteral(u"transition")))
        value.transition = TransitionFromJson(object.value(QStringLiteral(u"transition")).toObject());
    if (object.contains(QStringLiteral(u"durationSeconds")))
        value.durationSeconds = object.value(QStringLiteral(u"durationSeconds")).toDouble();
    if (object.contains(QStringLiteral(u"pixelWidth")))
        value.pixelWidth = object.value(QStringLiteral(u"pixelWidth")).toInt();
    if (object.contains(QStringLiteral(u"pixelHeight")))
        value.pixelHeight = object.value(QStringLiteral(u"pixelHeight")).toInt();
    if (object.contains(QStringLiteral(u"folder")))
        value.folder = object.value(QStringLiteral(u"folder")).toString();
    if (object.contains(QStringLiteral(u"folderId")))
        value.folderId = object.value(QStringLiteral(u"folderId")).toString();
    if (object.contains(QStringLiteral(u"recordedAt")))
        value.recordedAt = object.value(QStringLiteral(u"recordedAt")).toDouble();
    if (object.contains(QStringLiteral(u"importedAt")))
        value.importedAt = object.value(QStringLiteral(u"importedAt")).toDouble();
    if (object.contains(QStringLiteral(u"recordedByPresetId")))
        value.recordedByPresetId = object.value(QStringLiteral(u"recordedByPresetId")).toString();
    if (object.contains(QStringLiteral(u"actions")))
        value.actions = decodeList<SlideAction>(object.value(QStringLiteral(u"actions")), SlideActionFromJson);
    if (object.contains(QStringLiteral(u"autoAdvance")))
        value.autoAdvance = AutoAdvanceFromJson(object.value(QStringLiteral(u"autoAdvance")).toObject());
    if (object.contains(QStringLiteral(u"marks")))
        value.marks = decodeList<VideoMark>(object.value(QStringLiteral(u"marks")), VideoMarkFromJson);
    return value;
}

QJsonObject toJson(const AudioItem& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"fileHash"), value.fileHash);
    object.insert(QStringLiteral(u"fileName"), value.fileName);
    object.insert(QStringLiteral(u"tags"), encodeList(value.tags));
    object.insert(QStringLiteral(u"favorite"), value.favorite);
    if (value.inPoint)
        object.insert(QStringLiteral(u"inPoint"), *value.inPoint);
    if (value.outPoint)
        object.insert(QStringLiteral(u"outPoint"), *value.outPoint);
    if (value.durationSeconds)
        object.insert(QStringLiteral(u"durationSeconds"), *value.durationSeconds);
    if (value.folder)
        object.insert(QStringLiteral(u"folder"), *value.folder);
    if (value.folderId)
        object.insert(QStringLiteral(u"folderId"), *value.folderId);
    return object;
}

AudioItem AudioItemFromJson(const QJsonObject& object)
{
    AudioItem value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.fileHash = object.value(QStringLiteral(u"fileHash")).toString();
    value.fileName = object.value(QStringLiteral(u"fileName")).toString();
    value.tags = decodeList<QString>(object.value(QStringLiteral(u"tags")));
    value.favorite = object.value(QStringLiteral(u"favorite")).toBool();
    if (object.contains(QStringLiteral(u"inPoint")))
        value.inPoint = object.value(QStringLiteral(u"inPoint")).toDouble();
    if (object.contains(QStringLiteral(u"outPoint")))
        value.outPoint = object.value(QStringLiteral(u"outPoint")).toDouble();
    if (object.contains(QStringLiteral(u"durationSeconds")))
        value.durationSeconds = object.value(QStringLiteral(u"durationSeconds")).toDouble();
    if (object.contains(QStringLiteral(u"folder")))
        value.folder = object.value(QStringLiteral(u"folder")).toString();
    if (object.contains(QStringLiteral(u"folderId")))
        value.folderId = object.value(QStringLiteral(u"folderId")).toString();
    return value;
}

QJsonObject toJson(const PlaylistEntry& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"refKind"), toString(value.refKind));
    object.insert(QStringLiteral(u"refId"), value.refId);
    return object;
}

PlaylistEntry PlaylistEntryFromJson(const QJsonObject& object)
{
    PlaylistEntry value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.refKind = PlaylistRefKindFromString(object.value(QStringLiteral(u"refKind")).toString());
    value.refId = object.value(QStringLiteral(u"refId")).toString();
    return value;
}

QJsonObject toJson(const Playlist& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    if (value.playlistKind)
        object.insert(QStringLiteral(u"playlistKind"), toString(*value.playlistKind));
    object.insert(QStringLiteral(u"entries"), encodeList(value.entries, [](const PlaylistEntry& item) { return toJson(item); }));
    object.insert(QStringLiteral(u"playbackMode"), toString(value.playbackMode));
    if (value.shuffle)
        object.insert(QStringLiteral(u"shuffle"), *value.shuffle);
    if (value.crossfadeSeconds)
        object.insert(QStringLiteral(u"crossfadeSeconds"), *value.crossfadeSeconds);
    return object;
}

Playlist PlaylistFromJson(const QJsonObject& object)
{
    Playlist value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    if (object.contains(QStringLiteral(u"playlistKind")))
        value.playlistKind = PlaylistKindFromString(object.value(QStringLiteral(u"playlistKind")).toString());
    value.entries = decodeList<PlaylistEntry>(object.value(QStringLiteral(u"entries")), PlaylistEntryFromJson);
    value.playbackMode = PlaybackModeFromString(object.value(QStringLiteral(u"playbackMode")).toString());
    if (object.contains(QStringLiteral(u"shuffle")))
        value.shuffle = object.value(QStringLiteral(u"shuffle")).toBool();
    if (object.contains(QStringLiteral(u"crossfadeSeconds")))
        value.crossfadeSeconds = object.value(QStringLiteral(u"crossfadeSeconds")).toDouble();
    return value;
}

QJsonObject toJson(const MxUPlanItemNote& value)
{
    QJsonObject object;
    if (value.label)
        object.insert(QStringLiteral(u"label"), *value.label);
    object.insert(QStringLiteral(u"text"), value.text);
    if (value.kind)
        object.insert(QStringLiteral(u"kind"), *value.kind);
    if (value.positions)
        object.insert(QStringLiteral(u"positions"), encodeList(*value.positions));
    return object;
}

MxUPlanItemNote MxUPlanItemNoteFromJson(const QJsonObject& object)
{
    MxUPlanItemNote value;
    if (object.contains(QStringLiteral(u"label")))
        value.label = object.value(QStringLiteral(u"label")).toString();
    value.text = object.value(QStringLiteral(u"text")).toString();
    if (object.contains(QStringLiteral(u"kind")))
        value.kind = object.value(QStringLiteral(u"kind")).toString();
    if (object.contains(QStringLiteral(u"positions")))
        value.positions = decodeList<QString>(object.value(QStringLiteral(u"positions")));
    return value;
}

QJsonObject toJson(const SongTransition& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"kind"), value.kind);
    if (value.seconds)
        object.insert(QStringLiteral(u"seconds"), *value.seconds);
    return object;
}

SongTransition SongTransitionFromJson(const QJsonObject& object)
{
    SongTransition value;
    value.kind = object.value(QStringLiteral(u"kind")).toString();
    if (object.contains(QStringLiteral(u"seconds")))
        value.seconds = object.value(QStringLiteral(u"seconds")).toDouble();
    return value;
}

QJsonObject toJson(const ServiceItem& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"itemKind"), toString(value.itemKind));
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"refId"), value.refId);
    if (value.arrangementId)
        object.insert(QStringLiteral(u"arrangementId"), *value.arrangementId);
    if (value.colorHex)
        object.insert(QStringLiteral(u"colorHex"), *value.colorHex);
    if (value.outputPresetId)
        object.insert(QStringLiteral(u"outputPresetId"), *value.outputPresetId);
    if (value.mxuItemHexId)
        object.insert(QStringLiteral(u"mxuItemHexId"), *value.mxuItemHexId);
    if (value.duration)
        object.insert(QStringLiteral(u"duration"), *value.duration);
    if (value.mxuKind)
        object.insert(QStringLiteral(u"mxuKind"), *value.mxuKind);
    if (value.excludedTimeHexIds)
        object.insert(QStringLiteral(u"excludedTimeHexIds"), encodeList(*value.excludedTimeHexIds));
    if (value.hiddenInPresenter)
        object.insert(QStringLiteral(u"hiddenInPresenter"), *value.hiddenInPresenter);
    if (value.mxuSongTitle)
        object.insert(QStringLiteral(u"mxuSongTitle"), *value.mxuSongTitle);
    if (value.mxuCcliNumber)
        object.insert(QStringLiteral(u"mxuCcliNumber"), *value.mxuCcliNumber);
    if (value.mxuArrangementName)
        object.insert(QStringLiteral(u"mxuArrangementName"), *value.mxuArrangementName);
    if (value.mxuSongAuthor)
        object.insert(QStringLiteral(u"mxuSongAuthor"), *value.mxuSongAuthor);
    if (value.mxuMultiTracksUrl)
        object.insert(QStringLiteral(u"mxuMultiTracksUrl"), *value.mxuMultiTracksUrl);
    if (value.mxuNotes)
        object.insert(QStringLiteral(u"mxuNotes"), encodeList(*value.mxuNotes, [](const MxUPlanItemNote& item) { return toJson(item); }));
    if (value.mxuMessageNotesDocumentHexId)
        object.insert(QStringLiteral(u"mxuMessageNotesDocumentHexId"), *value.mxuMessageNotesDocumentHexId);
    if (value.mxuMessageNotesSubmittedAt)
        object.insert(QStringLiteral(u"mxuMessageNotesSubmittedAt"), *value.mxuMessageNotesSubmittedAt);
    if (value.mxuMessageNotesOnReady)
        object.insert(QStringLiteral(u"mxuMessageNotesOnReady"), *value.mxuMessageNotesOnReady);
    if (value.mxuMessageNotesDeckDocId)
        object.insert(QStringLiteral(u"mxuMessageNotesDeckDocId"), *value.mxuMessageNotesDeckDocId);
    if (value.mxuPcoItemId)
        object.insert(QStringLiteral(u"mxuPcoItemId"), *value.mxuPcoItemId);
    if (value.mxuPcoSongId)
        object.insert(QStringLiteral(u"mxuPcoSongId"), *value.mxuPcoSongId);
    if (value.mxuPcoArrangementId)
        object.insert(QStringLiteral(u"mxuPcoArrangementId"), *value.mxuPcoArrangementId);
    if (value.mxuPcoKeyId)
        object.insert(QStringLiteral(u"mxuPcoKeyId"), *value.mxuPcoKeyId);
    if (value.mxuSongKey)
        object.insert(QStringLiteral(u"mxuSongKey"), *value.mxuSongKey);
    if (value.mxuDescription)
        object.insert(QStringLiteral(u"mxuDescription"), *value.mxuDescription);
    if (value.mxuServicePosition)
        object.insert(QStringLiteral(u"mxuServicePosition"), *value.mxuServicePosition);
    if (value.mxuBpm)
        object.insert(QStringLiteral(u"mxuBpm"), *value.mxuBpm);
    if (value.mxuTimeSignature)
        object.insert(QStringLiteral(u"mxuTimeSignature"), *value.mxuTimeSignature);
    if (value.mxuSongKeyApplied)
        object.insert(QStringLiteral(u"mxuSongKeyApplied"), *value.mxuSongKeyApplied);
    if (value.transition)
        object.insert(QStringLiteral(u"transition"), toJson(*value.transition));
    return object;
}

ServiceItem ServiceItemFromJson(const QJsonObject& object)
{
    ServiceItem value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.itemKind = ServiceItemKindFromString(object.value(QStringLiteral(u"itemKind")).toString());
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.refId = object.value(QStringLiteral(u"refId")).toString();
    if (object.contains(QStringLiteral(u"arrangementId")))
        value.arrangementId = object.value(QStringLiteral(u"arrangementId")).toString();
    if (object.contains(QStringLiteral(u"colorHex")))
        value.colorHex = object.value(QStringLiteral(u"colorHex")).toString();
    if (object.contains(QStringLiteral(u"outputPresetId")))
        value.outputPresetId = object.value(QStringLiteral(u"outputPresetId")).toString();
    if (object.contains(QStringLiteral(u"mxuItemHexId")))
        value.mxuItemHexId = object.value(QStringLiteral(u"mxuItemHexId")).toString();
    if (object.contains(QStringLiteral(u"duration")))
        value.duration = object.value(QStringLiteral(u"duration")).toInt();
    if (object.contains(QStringLiteral(u"mxuKind")))
        value.mxuKind = object.value(QStringLiteral(u"mxuKind")).toString();
    if (object.contains(QStringLiteral(u"excludedTimeHexIds")))
        value.excludedTimeHexIds = decodeList<QString>(object.value(QStringLiteral(u"excludedTimeHexIds")));
    if (object.contains(QStringLiteral(u"hiddenInPresenter")))
        value.hiddenInPresenter = object.value(QStringLiteral(u"hiddenInPresenter")).toBool();
    if (object.contains(QStringLiteral(u"mxuSongTitle")))
        value.mxuSongTitle = object.value(QStringLiteral(u"mxuSongTitle")).toString();
    if (object.contains(QStringLiteral(u"mxuCcliNumber")))
        value.mxuCcliNumber = object.value(QStringLiteral(u"mxuCcliNumber")).toInt();
    if (object.contains(QStringLiteral(u"mxuArrangementName")))
        value.mxuArrangementName = object.value(QStringLiteral(u"mxuArrangementName")).toString();
    if (object.contains(QStringLiteral(u"mxuSongAuthor")))
        value.mxuSongAuthor = object.value(QStringLiteral(u"mxuSongAuthor")).toString();
    if (object.contains(QStringLiteral(u"mxuMultiTracksUrl")))
        value.mxuMultiTracksUrl = object.value(QStringLiteral(u"mxuMultiTracksUrl")).toString();
    if (object.contains(QStringLiteral(u"mxuNotes")))
        value.mxuNotes = decodeList<MxUPlanItemNote>(object.value(QStringLiteral(u"mxuNotes")), MxUPlanItemNoteFromJson);
    if (object.contains(QStringLiteral(u"mxuMessageNotesDocumentHexId")))
        value.mxuMessageNotesDocumentHexId = object.value(QStringLiteral(u"mxuMessageNotesDocumentHexId")).toString();
    if (object.contains(QStringLiteral(u"mxuMessageNotesSubmittedAt")))
        value.mxuMessageNotesSubmittedAt = object.value(QStringLiteral(u"mxuMessageNotesSubmittedAt")).toString();
    if (object.contains(QStringLiteral(u"mxuMessageNotesOnReady")))
        value.mxuMessageNotesOnReady = object.value(QStringLiteral(u"mxuMessageNotesOnReady")).toString();
    if (object.contains(QStringLiteral(u"mxuMessageNotesDeckDocId")))
        value.mxuMessageNotesDeckDocId = object.value(QStringLiteral(u"mxuMessageNotesDeckDocId")).toString();
    if (object.contains(QStringLiteral(u"mxuPcoItemId")))
        value.mxuPcoItemId = object.value(QStringLiteral(u"mxuPcoItemId")).toString();
    if (object.contains(QStringLiteral(u"mxuPcoSongId")))
        value.mxuPcoSongId = object.value(QStringLiteral(u"mxuPcoSongId")).toString();
    if (object.contains(QStringLiteral(u"mxuPcoArrangementId")))
        value.mxuPcoArrangementId = object.value(QStringLiteral(u"mxuPcoArrangementId")).toString();
    if (object.contains(QStringLiteral(u"mxuPcoKeyId")))
        value.mxuPcoKeyId = object.value(QStringLiteral(u"mxuPcoKeyId")).toString();
    if (object.contains(QStringLiteral(u"mxuSongKey")))
        value.mxuSongKey = object.value(QStringLiteral(u"mxuSongKey")).toString();
    if (object.contains(QStringLiteral(u"mxuDescription")))
        value.mxuDescription = object.value(QStringLiteral(u"mxuDescription")).toString();
    if (object.contains(QStringLiteral(u"mxuServicePosition")))
        value.mxuServicePosition = object.value(QStringLiteral(u"mxuServicePosition")).toString();
    if (object.contains(QStringLiteral(u"mxuBpm")))
        value.mxuBpm = object.value(QStringLiteral(u"mxuBpm")).toDouble();
    if (object.contains(QStringLiteral(u"mxuTimeSignature")))
        value.mxuTimeSignature = object.value(QStringLiteral(u"mxuTimeSignature")).toString();
    if (object.contains(QStringLiteral(u"mxuSongKeyApplied")))
        value.mxuSongKeyApplied = object.value(QStringLiteral(u"mxuSongKeyApplied")).toString();
    if (object.contains(QStringLiteral(u"transition")))
        value.transition = SongTransitionFromJson(object.value(QStringLiteral(u"transition")).toObject());
    return value;
}

QJsonObject toJson(const ServiceLinkRule& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"normalizedName"), value.normalizedName);
    if (value.serviceTypeName)
        object.insert(QStringLiteral(u"serviceTypeName"), *value.serviceTypeName);
    object.insert(QStringLiteral(u"itemKind"), toString(value.itemKind));
    object.insert(QStringLiteral(u"refId"), value.refId);
    return object;
}

ServiceLinkRule ServiceLinkRuleFromJson(const QJsonObject& object)
{
    ServiceLinkRule value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.normalizedName = object.value(QStringLiteral(u"normalizedName")).toString();
    if (object.contains(QStringLiteral(u"serviceTypeName")))
        value.serviceTypeName = object.value(QStringLiteral(u"serviceTypeName")).toString();
    value.itemKind = ServiceItemKindFromString(object.value(QStringLiteral(u"itemKind")).toString());
    value.refId = object.value(QStringLiteral(u"refId")).toString();
    return value;
}

QJsonObject toJson(const ServiceLinkRules& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"rules"), encodeList(value.rules, [](const ServiceLinkRule& item) { return toJson(item); }));
    return object;
}

ServiceLinkRules ServiceLinkRulesFromJson(const QJsonObject& object)
{
    ServiceLinkRules value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.rules = decodeList<ServiceLinkRule>(object.value(QStringLiteral(u"rules")), ServiceLinkRuleFromJson);
    return value;
}

QJsonObject toJson(const MxUPlanTime& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"hexId"), value.hexId);
    object.insert(QStringLiteral(u"name"), value.name);
    if (value.startsAt)
        object.insert(QStringLiteral(u"startsAt"), *value.startsAt);
    if (value.isRehearsal)
        object.insert(QStringLiteral(u"isRehearsal"), *value.isRehearsal);
    return object;
}

MxUPlanTime MxUPlanTimeFromJson(const QJsonObject& object)
{
    MxUPlanTime value;
    value.hexId = object.value(QStringLiteral(u"hexId")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    if (object.contains(QStringLiteral(u"startsAt")))
        value.startsAt = object.value(QStringLiteral(u"startsAt")).toString();
    if (object.contains(QStringLiteral(u"isRehearsal")))
        value.isRehearsal = object.value(QStringLiteral(u"isRehearsal")).toBool();
    return value;
}

QJsonObject toJson(const MxUPlanTimeOrder& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"timeHexId"), value.timeHexId);
    object.insert(QStringLiteral(u"itemHexIds"), encodeList(value.itemHexIds));
    return object;
}

MxUPlanTimeOrder MxUPlanTimeOrderFromJson(const QJsonObject& object)
{
    MxUPlanTimeOrder value;
    value.timeHexId = object.value(QStringLiteral(u"timeHexId")).toString();
    value.itemHexIds = decodeList<QString>(object.value(QStringLiteral(u"itemHexIds")));
    return value;
}

QJsonObject toJson(const ServiceVersionStation& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    return object;
}

ServiceVersionStation ServiceVersionStationFromJson(const QJsonObject& object)
{
    ServiceVersionStation value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    return value;
}

QJsonObject toJson(const ServiceItemChange& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"itemId"), value.itemId);
    if (value.after)
        object.insert(QStringLiteral(u"after"), *value.after);
    if (value.hidden)
        object.insert(QStringLiteral(u"hidden"), *value.hidden);
    if (value.itemKind)
        object.insert(QStringLiteral(u"itemKind"), toString(*value.itemKind));
    if (value.refId)
        object.insert(QStringLiteral(u"refId"), *value.refId);
    if (value.name)
        object.insert(QStringLiteral(u"name"), *value.name);
    if (value.arrangementId)
        object.insert(QStringLiteral(u"arrangementId"), *value.arrangementId);
    if (value.outputPresetId)
        object.insert(QStringLiteral(u"outputPresetId"), *value.outputPresetId);
    return object;
}

ServiceItemChange ServiceItemChangeFromJson(const QJsonObject& object)
{
    ServiceItemChange value;
    value.itemId = object.value(QStringLiteral(u"itemId")).toString();
    if (object.contains(QStringLiteral(u"after")))
        value.after = object.value(QStringLiteral(u"after")).toString();
    if (object.contains(QStringLiteral(u"hidden")))
        value.hidden = object.value(QStringLiteral(u"hidden")).toBool();
    if (object.contains(QStringLiteral(u"itemKind")))
        value.itemKind = ServiceItemKindFromString(object.value(QStringLiteral(u"itemKind")).toString());
    if (object.contains(QStringLiteral(u"refId")))
        value.refId = object.value(QStringLiteral(u"refId")).toString();
    if (object.contains(QStringLiteral(u"name")))
        value.name = object.value(QStringLiteral(u"name")).toString();
    if (object.contains(QStringLiteral(u"arrangementId")))
        value.arrangementId = object.value(QStringLiteral(u"arrangementId")).toString();
    if (object.contains(QStringLiteral(u"outputPresetId")))
        value.outputPresetId = object.value(QStringLiteral(u"outputPresetId")).toString();
    return value;
}

QJsonObject toJson(const ServiceVersion& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    if (value.stations)
        object.insert(QStringLiteral(u"stations"), encodeList(*value.stations, [](const ServiceVersionStation& item) { return toJson(item); }));
    if (value.added)
        object.insert(QStringLiteral(u"added"), encodeList(*value.added, [](const ServiceItem& item) { return toJson(item); }));
    if (value.changes)
        object.insert(QStringLiteral(u"changes"), encodeList(*value.changes, [](const ServiceItemChange& item) { return toJson(item); }));
    return object;
}

ServiceVersion ServiceVersionFromJson(const QJsonObject& object)
{
    ServiceVersion value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    if (object.contains(QStringLiteral(u"stations")))
        value.stations = decodeList<ServiceVersionStation>(object.value(QStringLiteral(u"stations")), ServiceVersionStationFromJson);
    if (object.contains(QStringLiteral(u"added")))
        value.added = decodeList<ServiceItem>(object.value(QStringLiteral(u"added")), ServiceItemFromJson);
    if (object.contains(QStringLiteral(u"changes")))
        value.changes = decodeList<ServiceItemChange>(object.value(QStringLiteral(u"changes")), ServiceItemChangeFromJson);
    return value;
}

QJsonObject toJson(const Service& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"serviceDate"), value.serviceDate);
    object.insert(QStringLiteral(u"items"), encodeList(value.items, [](const ServiceItem& item) { return toJson(item); }));
    if (value.origin)
        object.insert(QStringLiteral(u"origin"), *value.origin);
    if (value.mxuPlanHexId)
        object.insert(QStringLiteral(u"mxuPlanHexId"), *value.mxuPlanHexId);
    if (value.mxuServiceTypeName)
        object.insert(QStringLiteral(u"mxuServiceTypeName"), *value.mxuServiceTypeName);
    if (value.mxuPlanVersion)
        object.insert(QStringLiteral(u"mxuPlanVersion"), *value.mxuPlanVersion);
    if (value.mxuPlanTimes)
        object.insert(QStringLiteral(u"mxuPlanTimes"), encodeList(*value.mxuPlanTimes, [](const MxUPlanTime& item) { return toJson(item); }));
    if (value.mxuTimeOrders)
        object.insert(QStringLiteral(u"mxuTimeOrders"), encodeList(*value.mxuTimeOrders, [](const MxUPlanTimeOrder& item) { return toJson(item); }));
    if (value.mxuSyncedOrder)
        object.insert(QStringLiteral(u"mxuSyncedOrder"), encodeList(*value.mxuSyncedOrder));
    if (value.mxuDerivedName)
        object.insert(QStringLiteral(u"mxuDerivedName"), *value.mxuDerivedName);
    if (value.mxuSyncPaused)
        object.insert(QStringLiteral(u"mxuSyncPaused"), *value.mxuSyncPaused);
    if (value.versions)
        object.insert(QStringLiteral(u"versions"), encodeList(*value.versions, [](const ServiceVersion& item) { return toJson(item); }));
    if (value.timecodeByOrder)
        object.insert(QStringLiteral(u"timecodeByOrder"), *value.timecodeByOrder);
    return object;
}

Service ServiceFromJson(const QJsonObject& object)
{
    Service value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.serviceDate = object.value(QStringLiteral(u"serviceDate")).toString();
    value.items = decodeList<ServiceItem>(object.value(QStringLiteral(u"items")), ServiceItemFromJson);
    if (object.contains(QStringLiteral(u"origin")))
        value.origin = object.value(QStringLiteral(u"origin")).toString();
    if (object.contains(QStringLiteral(u"mxuPlanHexId")))
        value.mxuPlanHexId = object.value(QStringLiteral(u"mxuPlanHexId")).toString();
    if (object.contains(QStringLiteral(u"mxuServiceTypeName")))
        value.mxuServiceTypeName = object.value(QStringLiteral(u"mxuServiceTypeName")).toString();
    if (object.contains(QStringLiteral(u"mxuPlanVersion")))
        value.mxuPlanVersion = object.value(QStringLiteral(u"mxuPlanVersion")).toString();
    if (object.contains(QStringLiteral(u"mxuPlanTimes")))
        value.mxuPlanTimes = decodeList<MxUPlanTime>(object.value(QStringLiteral(u"mxuPlanTimes")), MxUPlanTimeFromJson);
    if (object.contains(QStringLiteral(u"mxuTimeOrders")))
        value.mxuTimeOrders = decodeList<MxUPlanTimeOrder>(object.value(QStringLiteral(u"mxuTimeOrders")), MxUPlanTimeOrderFromJson);
    if (object.contains(QStringLiteral(u"mxuSyncedOrder")))
        value.mxuSyncedOrder = decodeList<QString>(object.value(QStringLiteral(u"mxuSyncedOrder")));
    if (object.contains(QStringLiteral(u"mxuDerivedName")))
        value.mxuDerivedName = object.value(QStringLiteral(u"mxuDerivedName")).toString();
    if (object.contains(QStringLiteral(u"mxuSyncPaused")))
        value.mxuSyncPaused = object.value(QStringLiteral(u"mxuSyncPaused")).toBool();
    if (object.contains(QStringLiteral(u"versions")))
        value.versions = decodeList<ServiceVersion>(object.value(QStringLiteral(u"versions")), ServiceVersionFromJson);
    if (object.contains(QStringLiteral(u"timecodeByOrder")))
        value.timecodeByOrder = object.value(QStringLiteral(u"timecodeByOrder")).toBool();
    return value;
}

QJsonObject toJson(const Overlay& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"objects"), encodeList(value.objects, [](const SlideObject& item) { return toJson(item); }));
    if (value.folder)
        object.insert(QStringLiteral(u"folder"), *value.folder);
    if (value.folderId)
        object.insert(QStringLiteral(u"folderId"), *value.folderId);
    if (value.layer)
        object.insert(QStringLiteral(u"layer"), *value.layer);
    if (value.animationOrder)
        object.insert(QStringLiteral(u"animationOrder"), encodeList(*value.animationOrder));
    if (value.buildOrder)
        object.insert(QStringLiteral(u"buildOrder"), encodeList(*value.buildOrder));
    return object;
}

Overlay OverlayFromJson(const QJsonObject& object)
{
    Overlay value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.objects = decodeList<SlideObject>(object.value(QStringLiteral(u"objects")), SlideObjectFromJson);
    if (object.contains(QStringLiteral(u"folder")))
        value.folder = object.value(QStringLiteral(u"folder")).toString();
    if (object.contains(QStringLiteral(u"folderId")))
        value.folderId = object.value(QStringLiteral(u"folderId")).toString();
    if (object.contains(QStringLiteral(u"layer")))
        value.layer = object.value(QStringLiteral(u"layer")).toString();
    if (object.contains(QStringLiteral(u"animationOrder")))
        value.animationOrder = decodeList<QString>(object.value(QStringLiteral(u"animationOrder")));
    if (object.contains(QStringLiteral(u"buildOrder")))
        value.buildOrder = decodeList<QString>(object.value(QStringLiteral(u"buildOrder")));
    return value;
}

QJsonObject toJson(const OutputAssignment& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"targetKind"), toString(value.targetKind));
    object.insert(QStringLiteral(u"targetId"), value.targetId);
    object.insert(QStringLiteral(u"enabledLayers"), encodeList(value.enabledLayers));
    if (value.slideThemeId)
        object.insert(QStringLiteral(u"slideThemeId"), *value.slideThemeId);
    if (value.slideThemeFolder)
        object.insert(QStringLiteral(u"slideThemeFolder"), *value.slideThemeFolder);
    if (value.slideThemeSlideId)
        object.insert(QStringLiteral(u"slideThemeSlideId"), *value.slideThemeSlideId);
    if (value.maskIds)
        object.insert(QStringLiteral(u"maskIds"), encodeList(*value.maskIds));
    return object;
}

OutputAssignment OutputAssignmentFromJson(const QJsonObject& object)
{
    OutputAssignment value;
    value.targetKind = OutputTargetKindFromString(object.value(QStringLiteral(u"targetKind")).toString());
    value.targetId = object.value(QStringLiteral(u"targetId")).toString();
    value.enabledLayers = decodeList<QString>(object.value(QStringLiteral(u"enabledLayers")));
    if (object.contains(QStringLiteral(u"slideThemeId")))
        value.slideThemeId = object.value(QStringLiteral(u"slideThemeId")).toString();
    if (object.contains(QStringLiteral(u"slideThemeFolder")))
        value.slideThemeFolder = object.value(QStringLiteral(u"slideThemeFolder")).toString();
    if (object.contains(QStringLiteral(u"slideThemeSlideId")))
        value.slideThemeSlideId = object.value(QStringLiteral(u"slideThemeSlideId")).toString();
    if (object.contains(QStringLiteral(u"maskIds")))
        value.maskIds = decodeList<QString>(object.value(QStringLiteral(u"maskIds")));
    return value;
}

QJsonObject toJson(const CustomLayer& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    if (value.above)
        object.insert(QStringLiteral(u"above"), *value.above);
    return object;
}

CustomLayer CustomLayerFromJson(const QJsonObject& object)
{
    CustomLayer value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    if (object.contains(QStringLiteral(u"above")))
        value.above = object.value(QStringLiteral(u"above")).toString();
    return value;
}

QJsonObject toJson(const LayerPlacement& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"layerId"), value.layerId);
    object.insert(QStringLiteral(u"x"), value.x);
    object.insert(QStringLiteral(u"y"), value.y);
    object.insert(QStringLiteral(u"width"), value.width);
    object.insert(QStringLiteral(u"height"), value.height);
    if (value.scale)
        object.insert(QStringLiteral(u"scale"), toString(*value.scale));
    return object;
}

LayerPlacement LayerPlacementFromJson(const QJsonObject& object)
{
    LayerPlacement value;
    value.layerId = object.value(QStringLiteral(u"layerId")).toString();
    value.x = object.value(QStringLiteral(u"x")).toDouble();
    value.y = object.value(QStringLiteral(u"y")).toDouble();
    value.width = object.value(QStringLiteral(u"width")).toDouble();
    value.height = object.value(QStringLiteral(u"height")).toDouble();
    if (object.contains(QStringLiteral(u"scale")))
        value.scale = MediaScaleModeFromString(object.value(QStringLiteral(u"scale")).toString());
    return value;
}

QJsonObject toJson(const OutputPreset& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"assignments"), encodeList(value.assignments, [](const OutputAssignment& item) { return toJson(item); }));
    if (value.placements)
        object.insert(QStringLiteral(u"placements"), encodeList(*value.placements, [](const LayerPlacement& item) { return toJson(item); }));
    if (value.layers)
        object.insert(QStringLiteral(u"layers"), encodeList(*value.layers, [](const CustomLayer& item) { return toJson(item); }));
    return object;
}

OutputPreset OutputPresetFromJson(const QJsonObject& object)
{
    OutputPreset value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.assignments = decodeList<OutputAssignment>(object.value(QStringLiteral(u"assignments")), OutputAssignmentFromJson);
    if (object.contains(QStringLiteral(u"placements")))
        value.placements = decodeList<LayerPlacement>(object.value(QStringLiteral(u"placements")), LayerPlacementFromJson);
    if (object.contains(QStringLiteral(u"layers")))
        value.layers = decodeList<CustomLayer>(object.value(QStringLiteral(u"layers")), CustomLayerFromJson);
    return value;
}

QJsonObject toJson(const MIDIDevice& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    if (value.direction)
        object.insert(QStringLiteral(u"direction"), toString(*value.direction));
    if (value.channel)
        object.insert(QStringLiteral(u"channel"), *value.channel);
    if (value.enabled)
        object.insert(QStringLiteral(u"enabled"), *value.enabled);
    if (value.sourceNames)
        object.insert(QStringLiteral(u"sourceNames"), encodeList(*value.sourceNames));
    if (value.destinationNames)
        object.insert(QStringLiteral(u"destinationNames"), encodeList(*value.destinationNames));
    if (value.autoReconnect)
        object.insert(QStringLiteral(u"autoReconnect"), *value.autoReconnect);
    return object;
}

MIDIDevice MIDIDeviceFromJson(const QJsonObject& object)
{
    MIDIDevice value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    if (object.contains(QStringLiteral(u"direction")))
        value.direction = MIDIDeviceItemDirectionFromString(object.value(QStringLiteral(u"direction")).toString());
    if (object.contains(QStringLiteral(u"channel")))
        value.channel = object.value(QStringLiteral(u"channel")).toInt();
    if (object.contains(QStringLiteral(u"enabled")))
        value.enabled = object.value(QStringLiteral(u"enabled")).toBool();
    if (object.contains(QStringLiteral(u"sourceNames")))
        value.sourceNames = decodeList<QString>(object.value(QStringLiteral(u"sourceNames")));
    if (object.contains(QStringLiteral(u"destinationNames")))
        value.destinationNames = decodeList<QString>(object.value(QStringLiteral(u"destinationNames")));
    if (object.contains(QStringLiteral(u"autoReconnect")))
        value.autoReconnect = object.value(QStringLiteral(u"autoReconnect")).toBool();
    return value;
}

QJsonObject toJson(const AlertPreset& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"message"), value.message);
    object.insert(QStringLiteral(u"behavior"), toString(value.behavior));
    if (value.target)
        object.insert(QStringLiteral(u"target"), toString(*value.target));
    if (value.themeId)
        object.insert(QStringLiteral(u"themeId"), *value.themeId);
    if (value.layer)
        object.insert(QStringLiteral(u"layer"), *value.layer);
    return object;
}

AlertPreset AlertPresetFromJson(const QJsonObject& object)
{
    AlertPreset value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.message = object.value(QStringLiteral(u"message")).toString();
    value.behavior = AlertBehaviorFromString(object.value(QStringLiteral(u"behavior")).toString());
    if (object.contains(QStringLiteral(u"target")))
        value.target = AlertTargetFromString(object.value(QStringLiteral(u"target")).toString());
    if (object.contains(QStringLiteral(u"themeId")))
        value.themeId = object.value(QStringLiteral(u"themeId")).toString();
    if (object.contains(QStringLiteral(u"layer")))
        value.layer = object.value(QStringLiteral(u"layer")).toString();
    return value;
}

QJsonObject toJson(const Theme& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"fontFamily"), value.fontFamily);
    object.insert(QStringLiteral(u"fontSize"), value.fontSize);
    object.insert(QStringLiteral(u"textColorHex"), value.textColorHex);
    object.insert(QStringLiteral(u"backgroundColorHex"), value.backgroundColorHex);
    if (value.slides)
        object.insert(QStringLiteral(u"slides"), encodeList(*value.slides, [](const Slide& item) { return toJson(item); }));
    return object;
}

Theme ThemeFromJson(const QJsonObject& object)
{
    Theme value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.fontFamily = object.value(QStringLiteral(u"fontFamily")).toString();
    value.fontSize = object.value(QStringLiteral(u"fontSize")).toDouble();
    value.textColorHex = object.value(QStringLiteral(u"textColorHex")).toString();
    value.backgroundColorHex = object.value(QStringLiteral(u"backgroundColorHex")).toString();
    if (object.contains(QStringLiteral(u"slides")))
        value.slides = decodeList<Slide>(object.value(QStringLiteral(u"slides")), SlideFromJson);
    return value;
}

QJsonObject toJson(const StreamPresetDestination& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"transport"), toString(value.transport));
    object.insert(QStringLiteral(u"url"), value.url);
    if (value.streamKey)
        object.insert(QStringLiteral(u"streamKey"), *value.streamKey);
    if (value.linkedPlatform)
        object.insert(QStringLiteral(u"linkedPlatform"), *value.linkedPlatform);
    if (value.linkedTargetId)
        object.insert(QStringLiteral(u"linkedTargetId"), *value.linkedTargetId);
    if (value.videoCodec)
        object.insert(QStringLiteral(u"videoCodec"), toString(*value.videoCodec));
    if (value.maxHeight)
        object.insert(QStringLiteral(u"maxHeight"), *value.maxHeight);
    if (value.hdr)
        object.insert(QStringLiteral(u"hdr"), *value.hdr);
    if (value.privacy)
        object.insert(QStringLiteral(u"privacy"), *value.privacy);
    if (value.canvasScreenId)
        object.insert(QStringLiteral(u"canvasScreenId"), *value.canvasScreenId);
    if (value.width)
        object.insert(QStringLiteral(u"width"), *value.width);
    if (value.height)
        object.insert(QStringLiteral(u"height"), *value.height);
    if (value.frameRate)
        object.insert(QStringLiteral(u"frameRate"), *value.frameRate);
    return object;
}

StreamPresetDestination StreamPresetDestinationFromJson(const QJsonObject& object)
{
    StreamPresetDestination value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.transport = StreamTransportFromString(object.value(QStringLiteral(u"transport")).toString());
    value.url = object.value(QStringLiteral(u"url")).toString();
    if (object.contains(QStringLiteral(u"streamKey")))
        value.streamKey = object.value(QStringLiteral(u"streamKey")).toString();
    if (object.contains(QStringLiteral(u"linkedPlatform")))
        value.linkedPlatform = object.value(QStringLiteral(u"linkedPlatform")).toString();
    if (object.contains(QStringLiteral(u"linkedTargetId")))
        value.linkedTargetId = object.value(QStringLiteral(u"linkedTargetId")).toString();
    if (object.contains(QStringLiteral(u"videoCodec")))
        value.videoCodec = StreamVideoCodecFromString(object.value(QStringLiteral(u"videoCodec")).toString());
    if (object.contains(QStringLiteral(u"maxHeight")))
        value.maxHeight = object.value(QStringLiteral(u"maxHeight")).toInt();
    if (object.contains(QStringLiteral(u"hdr")))
        value.hdr = object.value(QStringLiteral(u"hdr")).toBool();
    if (object.contains(QStringLiteral(u"privacy")))
        value.privacy = object.value(QStringLiteral(u"privacy")).toString();
    if (object.contains(QStringLiteral(u"canvasScreenId")))
        value.canvasScreenId = object.value(QStringLiteral(u"canvasScreenId")).toString();
    if (object.contains(QStringLiteral(u"width")))
        value.width = object.value(QStringLiteral(u"width")).toInt();
    if (object.contains(QStringLiteral(u"height")))
        value.height = object.value(QStringLiteral(u"height")).toInt();
    if (object.contains(QStringLiteral(u"frameRate")))
        value.frameRate = object.value(QStringLiteral(u"frameRate")).toInt();
    return value;
}

QJsonObject toJson(const StreamDestination& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"transport"), toString(value.transport));
    object.insert(QStringLiteral(u"url"), value.url);
    if (value.streamKey)
        object.insert(QStringLiteral(u"streamKey"), *value.streamKey);
    if (value.linkedPlatform)
        object.insert(QStringLiteral(u"linkedPlatform"), *value.linkedPlatform);
    if (value.linkedTargetId)
        object.insert(QStringLiteral(u"linkedTargetId"), *value.linkedTargetId);
    if (value.linkedTargetName)
        object.insert(QStringLiteral(u"linkedTargetName"), *value.linkedTargetName);
    if (value.videoCodec)
        object.insert(QStringLiteral(u"videoCodec"), toString(*value.videoCodec));
    if (value.maxHeight)
        object.insert(QStringLiteral(u"maxHeight"), *value.maxHeight);
    if (value.hdr)
        object.insert(QStringLiteral(u"hdr"), *value.hdr);
    if (value.defaultPrivacy)
        object.insert(QStringLiteral(u"defaultPrivacy"), *value.defaultPrivacy);
    if (value.canvasScreenId)
        object.insert(QStringLiteral(u"canvasScreenId"), *value.canvasScreenId);
    if (value.width)
        object.insert(QStringLiteral(u"width"), *value.width);
    if (value.height)
        object.insert(QStringLiteral(u"height"), *value.height);
    if (value.frameRate)
        object.insert(QStringLiteral(u"frameRate"), *value.frameRate);
    return object;
}

StreamDestination StreamDestinationFromJson(const QJsonObject& object)
{
    StreamDestination value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.transport = StreamTransportFromString(object.value(QStringLiteral(u"transport")).toString());
    value.url = object.value(QStringLiteral(u"url")).toString();
    if (object.contains(QStringLiteral(u"streamKey")))
        value.streamKey = object.value(QStringLiteral(u"streamKey")).toString();
    if (object.contains(QStringLiteral(u"linkedPlatform")))
        value.linkedPlatform = object.value(QStringLiteral(u"linkedPlatform")).toString();
    if (object.contains(QStringLiteral(u"linkedTargetId")))
        value.linkedTargetId = object.value(QStringLiteral(u"linkedTargetId")).toString();
    if (object.contains(QStringLiteral(u"linkedTargetName")))
        value.linkedTargetName = object.value(QStringLiteral(u"linkedTargetName")).toString();
    if (object.contains(QStringLiteral(u"videoCodec")))
        value.videoCodec = StreamVideoCodecFromString(object.value(QStringLiteral(u"videoCodec")).toString());
    if (object.contains(QStringLiteral(u"maxHeight")))
        value.maxHeight = object.value(QStringLiteral(u"maxHeight")).toInt();
    if (object.contains(QStringLiteral(u"hdr")))
        value.hdr = object.value(QStringLiteral(u"hdr")).toBool();
    if (object.contains(QStringLiteral(u"defaultPrivacy")))
        value.defaultPrivacy = object.value(QStringLiteral(u"defaultPrivacy")).toString();
    if (object.contains(QStringLiteral(u"canvasScreenId")))
        value.canvasScreenId = object.value(QStringLiteral(u"canvasScreenId")).toString();
    if (object.contains(QStringLiteral(u"width")))
        value.width = object.value(QStringLiteral(u"width")).toInt();
    if (object.contains(QStringLiteral(u"height")))
        value.height = object.value(QStringLiteral(u"height")).toInt();
    if (object.contains(QStringLiteral(u"frameRate")))
        value.frameRate = object.value(QStringLiteral(u"frameRate")).toInt();
    return value;
}

QJsonObject toJson(const StreamRecordPreset& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"destinations"), encodeList(value.destinations, [](const StreamPresetDestination& item) { return toJson(item); }));
    if (value.destinationIds)
        object.insert(QStringLiteral(u"destinationIds"), encodeList(*value.destinationIds));
    if (value.presetKind)
        object.insert(QStringLiteral(u"presetKind"), toString(*value.presetKind));
    if (value.width)
        object.insert(QStringLiteral(u"width"), *value.width);
    if (value.height)
        object.insert(QStringLiteral(u"height"), *value.height);
    if (value.frameRate)
        object.insert(QStringLiteral(u"frameRate"), *value.frameRate);
    if (value.videoBitrateKbps)
        object.insert(QStringLiteral(u"videoBitrateKbps"), *value.videoBitrateKbps);
    if (value.adaptBitrate)
        object.insert(QStringLiteral(u"adaptBitrate"), *value.adaptBitrate);
    if (value.minBitrateKbps)
        object.insert(QStringLiteral(u"minBitrateKbps"), *value.minBitrateKbps);
    if (value.canvasScreenId)
        object.insert(QStringLiteral(u"canvasScreenId"), *value.canvasScreenId);
    if (value.recordWhileStreaming)
        object.insert(QStringLiteral(u"recordWhileStreaming"), *value.recordWhileStreaming);
    if (value.recordCodec)
        object.insert(QStringLiteral(u"recordCodec"), *value.recordCodec);
    if (value.title)
        object.insert(QStringLiteral(u"title"), *value.title);
    if (value.streamDescription)
        object.insert(QStringLiteral(u"streamDescription"), *value.streamDescription);
    if (value.recordFolder)
        object.insert(QStringLiteral(u"recordFolder"), *value.recordFolder);
    if (value.audioInputUid)
        object.insert(QStringLiteral(u"audioInputUid"), *value.audioInputUid);
    if (value.audioIncludesProgram)
        object.insert(QStringLiteral(u"audioIncludesProgram"), *value.audioIncludesProgram);
    if (value.audioInputId)
        object.insert(QStringLiteral(u"audioInputId"), *value.audioInputId);
    if (value.audioMixId)
        object.insert(QStringLiteral(u"audioMixId"), *value.audioMixId);
    if (value.audioDelayMs)
        object.insert(QStringLiteral(u"audioDelayMs"), *value.audioDelayMs);
    if (value.sourceKind)
        object.insert(QStringLiteral(u"sourceKind"), toString(*value.sourceKind));
    if (value.sourceMediaId)
        object.insert(QStringLiteral(u"sourceMediaId"), *value.sourceMediaId);
    if (value.sourceFolder)
        object.insert(QStringLiteral(u"sourceFolder"), *value.sourceFolder);
    if (value.sourceMaxAgeHours)
        object.insert(QStringLiteral(u"sourceMaxAgeHours"), *value.sourceMaxAgeHours);
    if (value.recordLibraryFolder)
        object.insert(QStringLiteral(u"recordLibraryFolder"), *value.recordLibraryFolder);
    if (value.recordExportFolder)
        object.insert(QStringLiteral(u"recordExportFolder"), *value.recordExportFolder);
    return object;
}

StreamRecordPreset StreamRecordPresetFromJson(const QJsonObject& object)
{
    StreamRecordPreset value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.destinations = decodeList<StreamPresetDestination>(object.value(QStringLiteral(u"destinations")), StreamPresetDestinationFromJson);
    if (object.contains(QStringLiteral(u"destinationIds")))
        value.destinationIds = decodeList<QString>(object.value(QStringLiteral(u"destinationIds")));
    if (object.contains(QStringLiteral(u"presetKind")))
        value.presetKind = StreamPresetKindFromString(object.value(QStringLiteral(u"presetKind")).toString());
    if (object.contains(QStringLiteral(u"width")))
        value.width = object.value(QStringLiteral(u"width")).toInt();
    if (object.contains(QStringLiteral(u"height")))
        value.height = object.value(QStringLiteral(u"height")).toInt();
    if (object.contains(QStringLiteral(u"frameRate")))
        value.frameRate = object.value(QStringLiteral(u"frameRate")).toInt();
    if (object.contains(QStringLiteral(u"videoBitrateKbps")))
        value.videoBitrateKbps = object.value(QStringLiteral(u"videoBitrateKbps")).toInt();
    if (object.contains(QStringLiteral(u"adaptBitrate")))
        value.adaptBitrate = object.value(QStringLiteral(u"adaptBitrate")).toBool();
    if (object.contains(QStringLiteral(u"minBitrateKbps")))
        value.minBitrateKbps = object.value(QStringLiteral(u"minBitrateKbps")).toInt();
    if (object.contains(QStringLiteral(u"canvasScreenId")))
        value.canvasScreenId = object.value(QStringLiteral(u"canvasScreenId")).toString();
    if (object.contains(QStringLiteral(u"recordWhileStreaming")))
        value.recordWhileStreaming = object.value(QStringLiteral(u"recordWhileStreaming")).toBool();
    if (object.contains(QStringLiteral(u"recordCodec")))
        value.recordCodec = object.value(QStringLiteral(u"recordCodec")).toString();
    if (object.contains(QStringLiteral(u"title")))
        value.title = object.value(QStringLiteral(u"title")).toString();
    if (object.contains(QStringLiteral(u"streamDescription")))
        value.streamDescription = object.value(QStringLiteral(u"streamDescription")).toString();
    if (object.contains(QStringLiteral(u"recordFolder")))
        value.recordFolder = object.value(QStringLiteral(u"recordFolder")).toString();
    if (object.contains(QStringLiteral(u"audioInputUid")))
        value.audioInputUid = object.value(QStringLiteral(u"audioInputUid")).toString();
    if (object.contains(QStringLiteral(u"audioIncludesProgram")))
        value.audioIncludesProgram = object.value(QStringLiteral(u"audioIncludesProgram")).toBool();
    if (object.contains(QStringLiteral(u"audioInputId")))
        value.audioInputId = object.value(QStringLiteral(u"audioInputId")).toString();
    if (object.contains(QStringLiteral(u"audioMixId")))
        value.audioMixId = object.value(QStringLiteral(u"audioMixId")).toString();
    if (object.contains(QStringLiteral(u"audioDelayMs")))
        value.audioDelayMs = object.value(QStringLiteral(u"audioDelayMs")).toInt();
    if (object.contains(QStringLiteral(u"sourceKind")))
        value.sourceKind = StreamSourceKindFromString(object.value(QStringLiteral(u"sourceKind")).toString());
    if (object.contains(QStringLiteral(u"sourceMediaId")))
        value.sourceMediaId = object.value(QStringLiteral(u"sourceMediaId")).toString();
    if (object.contains(QStringLiteral(u"sourceFolder")))
        value.sourceFolder = object.value(QStringLiteral(u"sourceFolder")).toString();
    if (object.contains(QStringLiteral(u"sourceMaxAgeHours")))
        value.sourceMaxAgeHours = object.value(QStringLiteral(u"sourceMaxAgeHours")).toInt();
    if (object.contains(QStringLiteral(u"recordLibraryFolder")))
        value.recordLibraryFolder = object.value(QStringLiteral(u"recordLibraryFolder")).toString();
    if (object.contains(QStringLiteral(u"recordExportFolder")))
        value.recordExportFolder = object.value(QStringLiteral(u"recordExportFolder")).toString();
    return value;
}

QJsonObject toJson(const ActionCombo& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"actions"), encodeList(value.actions, [](const SlideAction& item) { return toJson(item); }));
    if (value.colorHex)
        object.insert(QStringLiteral(u"colorHex"), *value.colorHex);
    if (value.iconName)
        object.insert(QStringLiteral(u"iconName"), *value.iconName);
    if (value.runOnStartup)
        object.insert(QStringLiteral(u"runOnStartup"), *value.runOnStartup);
    return object;
}

ActionCombo ActionComboFromJson(const QJsonObject& object)
{
    ActionCombo value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.actions = decodeList<SlideAction>(object.value(QStringLiteral(u"actions")), SlideActionFromJson);
    if (object.contains(QStringLiteral(u"colorHex")))
        value.colorHex = object.value(QStringLiteral(u"colorHex")).toString();
    if (object.contains(QStringLiteral(u"iconName")))
        value.iconName = object.value(QStringLiteral(u"iconName")).toString();
    if (object.contains(QStringLiteral(u"runOnStartup")))
        value.runOnStartup = object.value(QStringLiteral(u"runOnStartup")).toBool();
    return value;
}

QJsonObject toJson(const ScheduleCondition& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"kind"), toString(value.kind));
    if (value.days)
        object.insert(QStringLiteral(u"days"), encodeList(*value.days));
    if (value.timeOfDay)
        object.insert(QStringLiteral(u"timeOfDay"), *value.timeOfDay);
    if (value.date)
        object.insert(QStringLiteral(u"date"), *value.date);
    if (value.timerId)
        object.insert(QStringLiteral(u"timerId"), *value.timerId);
    if (value.timerSeconds)
        object.insert(QStringLiteral(u"timerSeconds"), *value.timerSeconds);
    if (value.excludedDates)
        object.insert(QStringLiteral(u"excludedDates"), encodeList(*value.excludedDates));
    return object;
}

ScheduleCondition ScheduleConditionFromJson(const QJsonObject& object)
{
    ScheduleCondition value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.kind = ScheduleConditionKindFromString(object.value(QStringLiteral(u"kind")).toString());
    if (object.contains(QStringLiteral(u"days")))
        value.days = decodeList<int>(object.value(QStringLiteral(u"days")));
    if (object.contains(QStringLiteral(u"timeOfDay")))
        value.timeOfDay = object.value(QStringLiteral(u"timeOfDay")).toString();
    if (object.contains(QStringLiteral(u"date")))
        value.date = object.value(QStringLiteral(u"date")).toString();
    if (object.contains(QStringLiteral(u"timerId")))
        value.timerId = object.value(QStringLiteral(u"timerId")).toString();
    if (object.contains(QStringLiteral(u"timerSeconds")))
        value.timerSeconds = object.value(QStringLiteral(u"timerSeconds")).toDouble();
    if (object.contains(QStringLiteral(u"excludedDates")))
        value.excludedDates = decodeList<QString>(object.value(QStringLiteral(u"excludedDates")));
    return value;
}

QJsonObject toJson(const ScheduleTrigger& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"conditions"), encodeList(value.conditions, [](const ScheduleCondition& item) { return toJson(item); }));
    object.insert(QStringLiteral(u"actions"), encodeList(value.actions, [](const SlideAction& item) { return toJson(item); }));
    if (value.conditionLogic)
        object.insert(QStringLiteral(u"conditionLogic"), toString(*value.conditionLogic));
    if (value.enabled)
        object.insert(QStringLiteral(u"enabled"), *value.enabled);
    if (value.notes)
        object.insert(QStringLiteral(u"notes"), *value.notes);
    if (value.archived)
        object.insert(QStringLiteral(u"archived"), *value.archived);
    if (value.disabledUntil)
        object.insert(QStringLiteral(u"disabledUntil"), *value.disabledUntil);
    if (value.enabledUntil)
        object.insert(QStringLiteral(u"enabledUntil"), *value.enabledUntil);
    return object;
}

ScheduleTrigger ScheduleTriggerFromJson(const QJsonObject& object)
{
    ScheduleTrigger value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.conditions = decodeList<ScheduleCondition>(object.value(QStringLiteral(u"conditions")), ScheduleConditionFromJson);
    value.actions = decodeList<SlideAction>(object.value(QStringLiteral(u"actions")), SlideActionFromJson);
    if (object.contains(QStringLiteral(u"conditionLogic")))
        value.conditionLogic = ScheduleConditionLogicFromString(object.value(QStringLiteral(u"conditionLogic")).toString());
    if (object.contains(QStringLiteral(u"enabled")))
        value.enabled = object.value(QStringLiteral(u"enabled")).toBool();
    if (object.contains(QStringLiteral(u"notes")))
        value.notes = object.value(QStringLiteral(u"notes")).toString();
    if (object.contains(QStringLiteral(u"archived")))
        value.archived = object.value(QStringLiteral(u"archived")).toBool();
    if (object.contains(QStringLiteral(u"disabledUntil")))
        value.disabledUntil = object.value(QStringLiteral(u"disabledUntil")).toString();
    if (object.contains(QStringLiteral(u"enabledUntil")))
        value.enabledUntil = object.value(QStringLiteral(u"enabledUntil")).toString();
    return value;
}

QJsonObject toJson(const ScheduleFolder& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    if (value.enabled)
        object.insert(QStringLiteral(u"enabled"), *value.enabled);
    if (value.collapsed)
        object.insert(QStringLiteral(u"collapsed"), *value.collapsed);
    object.insert(QStringLiteral(u"triggerIds"), encodeList(value.triggerIds));
    return object;
}

ScheduleFolder ScheduleFolderFromJson(const QJsonObject& object)
{
    ScheduleFolder value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    if (object.contains(QStringLiteral(u"enabled")))
        value.enabled = object.value(QStringLiteral(u"enabled")).toBool();
    if (object.contains(QStringLiteral(u"collapsed")))
        value.collapsed = object.value(QStringLiteral(u"collapsed")).toBool();
    value.triggerIds = decodeList<QString>(object.value(QStringLiteral(u"triggerIds")));
    return value;
}

QJsonObject toJson(const SchedulerBoard& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"nodes"), encodeList(value.nodes));
    object.insert(QStringLiteral(u"folders"), encodeList(value.folders, [](const ScheduleFolder& item) { return toJson(item); }));
    return object;
}

SchedulerBoard SchedulerBoardFromJson(const QJsonObject& object)
{
    SchedulerBoard value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.nodes = decodeList<QString>(object.value(QStringLiteral(u"nodes")));
    value.folders = decodeList<ScheduleFolder>(object.value(QStringLiteral(u"folders")), ScheduleFolderFromJson);
    return value;
}

QJsonObject toJson(const ControlFolder& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    if (value.collapsed)
        object.insert(QStringLiteral(u"collapsed"), *value.collapsed);
    object.insert(QStringLiteral(u"itemIds"), encodeList(value.itemIds));
    return object;
}

ControlFolder ControlFolderFromJson(const QJsonObject& object)
{
    ControlFolder value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    if (object.contains(QStringLiteral(u"collapsed")))
        value.collapsed = object.value(QStringLiteral(u"collapsed")).toBool();
    value.itemIds = decodeList<QString>(object.value(QStringLiteral(u"itemIds")));
    return value;
}

QJsonObject toJson(const ControlBoard& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"nodes"), encodeList(value.nodes));
    object.insert(QStringLiteral(u"folders"), encodeList(value.folders, [](const ControlFolder& item) { return toJson(item); }));
    return object;
}

ControlBoard ControlBoardFromJson(const QJsonObject& object)
{
    ControlBoard value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.nodes = decodeList<QString>(object.value(QStringLiteral(u"nodes")));
    value.folders = decodeList<ControlFolder>(object.value(QStringLiteral(u"folders")), ControlFolderFromJson);
    return value;
}

QJsonObject toJson(const GroupDefinition& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"colorHex"), value.colorHex);
    if (value.hotKey)
        object.insert(QStringLiteral(u"hotKey"), *value.hotKey);
    return object;
}

GroupDefinition GroupDefinitionFromJson(const QJsonObject& object)
{
    GroupDefinition value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.colorHex = object.value(QStringLiteral(u"colorHex")).toString();
    if (object.contains(QStringLiteral(u"hotKey")))
        value.hotKey = object.value(QStringLiteral(u"hotKey")).toString();
    return value;
}

QJsonObject toJson(const GroupPalette& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"groups"), encodeList(value.groups, [](const GroupDefinition& item) { return toJson(item); }));
    return object;
}

GroupPalette GroupPaletteFromJson(const QJsonObject& object)
{
    GroupPalette value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.groups = decodeList<GroupDefinition>(object.value(QStringLiteral(u"groups")), GroupDefinitionFromJson);
    return value;
}

QJsonObject toJson(const ImportLedgerEntry& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"docId"), value.docId);
    object.insert(QStringLiteral(u"hash"), value.hash);
    return object;
}

ImportLedgerEntry ImportLedgerEntryFromJson(const QJsonObject& object)
{
    ImportLedgerEntry value;
    value.docId = object.value(QStringLiteral(u"docId")).toString();
    value.hash = object.value(QStringLiteral(u"hash")).toString();
    return value;
}

QJsonObject toJson(const ImportLedger& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"entries"), encodeList(value.entries, [](const ImportLedgerEntry& item) { return toJson(item); }));
    return object;
}

ImportLedger ImportLedgerFromJson(const QJsonObject& object)
{
    ImportLedger value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.entries = decodeList<ImportLedgerEntry>(object.value(QStringLiteral(u"entries")), ImportLedgerEntryFromJson);
    return value;
}

QJsonObject toJson(const EffectPreset& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"effects"), encodeList(value.effects, [](const Effect& item) { return toJson(item); }));
    return object;
}

EffectPreset EffectPresetFromJson(const QJsonObject& object)
{
    EffectPreset value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.effects = decodeList<Effect>(object.value(QStringLiteral(u"effects")), EffectFromJson);
    return value;
}

QJsonObject toJson(const EffectPresetBoard& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"presets"), encodeList(value.presets, [](const EffectPreset& item) { return toJson(item); }));
    return object;
}

EffectPresetBoard EffectPresetBoardFromJson(const QJsonObject& object)
{
    EffectPresetBoard value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.presets = decodeList<EffectPreset>(object.value(QStringLiteral(u"presets")), EffectPresetFromJson);
    return value;
}

QJsonObject toJson(const MultiViewNode& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    if (value.axis)
        object.insert(QStringLiteral(u"axis"), toString(*value.axis));
    if (value.children)
        object.insert(QStringLiteral(u"children"), encodeList(*value.children));
    if (value.fractions)
        object.insert(QStringLiteral(u"fractions"), encodeList(*value.fractions));
    if (value.sourceKind)
        object.insert(QStringLiteral(u"sourceKind"), toString(*value.sourceKind));
    if (value.screenSourceId)
        object.insert(QStringLiteral(u"screenSourceId"), *value.screenSourceId);
    if (value.screenSourceName)
        object.insert(QStringLiteral(u"screenSourceName"), *value.screenSourceName);
    if (value.liveInputId)
        object.insert(QStringLiteral(u"liveInputId"), *value.liveInputId);
    if (value.mediaId)
        object.insert(QStringLiteral(u"mediaId"), *value.mediaId);
    if (value.timerId)
        object.insert(QStringLiteral(u"timerId"), *value.timerId);
    if (value.text)
        object.insert(QStringLiteral(u"text"), *value.text);
    if (value.label)
        object.insert(QStringLiteral(u"label"), *value.label);
    if (value.scaleMode)
        object.insert(QStringLiteral(u"scaleMode"), toString(*value.scaleMode));
    if (value.matchSourceShape)
        object.insert(QStringLiteral(u"matchSourceShape"), *value.matchSourceShape);
    return object;
}

MultiViewNode MultiViewNodeFromJson(const QJsonObject& object)
{
    MultiViewNode value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    if (object.contains(QStringLiteral(u"axis")))
        value.axis = MultiViewSplitAxisFromString(object.value(QStringLiteral(u"axis")).toString());
    if (object.contains(QStringLiteral(u"children")))
        value.children = decodeList<QString>(object.value(QStringLiteral(u"children")));
    if (object.contains(QStringLiteral(u"fractions")))
        value.fractions = decodeList<double>(object.value(QStringLiteral(u"fractions")));
    if (object.contains(QStringLiteral(u"sourceKind")))
        value.sourceKind = MultiViewSourceKindFromString(object.value(QStringLiteral(u"sourceKind")).toString());
    if (object.contains(QStringLiteral(u"screenSourceId")))
        value.screenSourceId = object.value(QStringLiteral(u"screenSourceId")).toString();
    if (object.contains(QStringLiteral(u"screenSourceName")))
        value.screenSourceName = object.value(QStringLiteral(u"screenSourceName")).toString();
    if (object.contains(QStringLiteral(u"liveInputId")))
        value.liveInputId = object.value(QStringLiteral(u"liveInputId")).toString();
    if (object.contains(QStringLiteral(u"mediaId")))
        value.mediaId = object.value(QStringLiteral(u"mediaId")).toString();
    if (object.contains(QStringLiteral(u"timerId")))
        value.timerId = object.value(QStringLiteral(u"timerId")).toString();
    if (object.contains(QStringLiteral(u"text")))
        value.text = object.value(QStringLiteral(u"text")).toString();
    if (object.contains(QStringLiteral(u"label")))
        value.label = object.value(QStringLiteral(u"label")).toString();
    if (object.contains(QStringLiteral(u"scaleMode")))
        value.scaleMode = MediaScaleModeFromString(object.value(QStringLiteral(u"scaleMode")).toString());
    if (object.contains(QStringLiteral(u"matchSourceShape")))
        value.matchSourceShape = object.value(QStringLiteral(u"matchSourceShape")).toBool();
    return value;
}

QJsonObject toJson(const MultiViewTree& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"rootId"), value.rootId);
    object.insert(QStringLiteral(u"nodes"), encodeList(value.nodes, [](const MultiViewNode& item) { return toJson(item); }));
    return object;
}

MultiViewTree MultiViewTreeFromJson(const QJsonObject& object)
{
    MultiViewTree value;
    value.rootId = object.value(QStringLiteral(u"rootId")).toString();
    value.nodes = decodeList<MultiViewNode>(object.value(QStringLiteral(u"nodes")), MultiViewNodeFromJson);
    return value;
}

QJsonObject toJson(const ConfidenceLayout& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"objects"), encodeList(value.objects, [](const SlideObject& item) { return toJson(item); }));
    if (value.folder)
        object.insert(QStringLiteral(u"folder"), *value.folder);
    if (value.folderId)
        object.insert(QStringLiteral(u"folderId"), *value.folderId);
    if (value.canvasWidth)
        object.insert(QStringLiteral(u"canvasWidth"), *value.canvasWidth);
    if (value.canvasHeight)
        object.insert(QStringLiteral(u"canvasHeight"), *value.canvasHeight);
    if (value.animationOrder)
        object.insert(QStringLiteral(u"animationOrder"), encodeList(*value.animationOrder));
    if (value.buildOrder)
        object.insert(QStringLiteral(u"buildOrder"), encodeList(*value.buildOrder));
    if (value.multiView)
        object.insert(QStringLiteral(u"multiView"), toJson(*value.multiView));
    return object;
}

ConfidenceLayout ConfidenceLayoutFromJson(const QJsonObject& object)
{
    ConfidenceLayout value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.objects = decodeList<SlideObject>(object.value(QStringLiteral(u"objects")), SlideObjectFromJson);
    if (object.contains(QStringLiteral(u"folder")))
        value.folder = object.value(QStringLiteral(u"folder")).toString();
    if (object.contains(QStringLiteral(u"folderId")))
        value.folderId = object.value(QStringLiteral(u"folderId")).toString();
    if (object.contains(QStringLiteral(u"canvasWidth")))
        value.canvasWidth = object.value(QStringLiteral(u"canvasWidth")).toInt();
    if (object.contains(QStringLiteral(u"canvasHeight")))
        value.canvasHeight = object.value(QStringLiteral(u"canvasHeight")).toInt();
    if (object.contains(QStringLiteral(u"animationOrder")))
        value.animationOrder = decodeList<QString>(object.value(QStringLiteral(u"animationOrder")));
    if (object.contains(QStringLiteral(u"buildOrder")))
        value.buildOrder = decodeList<QString>(object.value(QStringLiteral(u"buildOrder")));
    if (object.contains(QStringLiteral(u"multiView")))
        value.multiView = MultiViewTreeFromJson(object.value(QStringLiteral(u"multiView")).toObject());
    return value;
}

QJsonObject toJson(const NoteRun& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"text"), value.text);
    if (value.bold)
        object.insert(QStringLiteral(u"bold"), *value.bold);
    if (value.italic)
        object.insert(QStringLiteral(u"italic"), *value.italic);
    if (value.underline)
        object.insert(QStringLiteral(u"underline"), *value.underline);
    if (value.strike)
        object.insert(QStringLiteral(u"strike"), *value.strike);
    if (value.code)
        object.insert(QStringLiteral(u"code"), *value.code);
    if (value.highlight)
        object.insert(QStringLiteral(u"highlight"), *value.highlight);
    if (value.color)
        object.insert(QStringLiteral(u"color"), *value.color);
    if (value.size)
        object.insert(QStringLiteral(u"size"), *value.size);
    if (value.href)
        object.insert(QStringLiteral(u"href"), *value.href);
    if (value.slideGroup)
        object.insert(QStringLiteral(u"slideGroup"), *value.slideGroup);
    if (value.slideType)
        object.insert(QStringLiteral(u"slideType"), *value.slideType);
    if (value.slideId)
        object.insert(QStringLiteral(u"slideId"), *value.slideId);
    if (value.slideState)
        object.insert(QStringLiteral(u"slideState"), *value.slideState);
    if (value.commentId)
        object.insert(QStringLiteral(u"commentId"), *value.commentId);
    return object;
}

NoteRun NoteRunFromJson(const QJsonObject& object)
{
    NoteRun value;
    value.text = object.value(QStringLiteral(u"text")).toString();
    if (object.contains(QStringLiteral(u"bold")))
        value.bold = object.value(QStringLiteral(u"bold")).toBool();
    if (object.contains(QStringLiteral(u"italic")))
        value.italic = object.value(QStringLiteral(u"italic")).toBool();
    if (object.contains(QStringLiteral(u"underline")))
        value.underline = object.value(QStringLiteral(u"underline")).toBool();
    if (object.contains(QStringLiteral(u"strike")))
        value.strike = object.value(QStringLiteral(u"strike")).toBool();
    if (object.contains(QStringLiteral(u"code")))
        value.code = object.value(QStringLiteral(u"code")).toBool();
    if (object.contains(QStringLiteral(u"highlight")))
        value.highlight = object.value(QStringLiteral(u"highlight")).toString();
    if (object.contains(QStringLiteral(u"color")))
        value.color = object.value(QStringLiteral(u"color")).toString();
    if (object.contains(QStringLiteral(u"size")))
        value.size = object.value(QStringLiteral(u"size")).toString();
    if (object.contains(QStringLiteral(u"href")))
        value.href = object.value(QStringLiteral(u"href")).toString();
    if (object.contains(QStringLiteral(u"slideGroup")))
        value.slideGroup = object.value(QStringLiteral(u"slideGroup")).toString();
    if (object.contains(QStringLiteral(u"slideType")))
        value.slideType = object.value(QStringLiteral(u"slideType")).toString();
    if (object.contains(QStringLiteral(u"slideId")))
        value.slideId = object.value(QStringLiteral(u"slideId")).toString();
    if (object.contains(QStringLiteral(u"slideState")))
        value.slideState = object.value(QStringLiteral(u"slideState")).toString();
    if (object.contains(QStringLiteral(u"commentId")))
        value.commentId = object.value(QStringLiteral(u"commentId")).toString();
    return value;
}

QJsonObject toJson(const NoteSlideRef& value)
{
    QJsonObject object;
    if (value.presentationId)
        object.insert(QStringLiteral(u"presentationId"), *value.presentationId);
    if (value.slideId)
        object.insert(QStringLiteral(u"slideId"), *value.slideId);
    if (value.slideIndex)
        object.insert(QStringLiteral(u"slideIndex"), *value.slideIndex);
    if (value.ppIntegrationHexId)
        object.insert(QStringLiteral(u"ppIntegrationHexId"), *value.ppIntegrationHexId);
    if (value.ppPresentationUuid)
        object.insert(QStringLiteral(u"ppPresentationUuid"), *value.ppPresentationUuid);
    if (value.ppPlaylistUuid)
        object.insert(QStringLiteral(u"ppPlaylistUuid"), *value.ppPlaylistUuid);
    if (value.ppItemIndex)
        object.insert(QStringLiteral(u"ppItemIndex"), *value.ppItemIndex);
    if (value.ppSlideIndex)
        object.insert(QStringLiteral(u"ppSlideIndex"), *value.ppSlideIndex);
    if (value.presentationName)
        object.insert(QStringLiteral(u"presentationName"), *value.presentationName);
    if (value.slideText)
        object.insert(QStringLiteral(u"slideText"), *value.slideText);
    if (value.slideLabel)
        object.insert(QStringLiteral(u"slideLabel"), *value.slideLabel);
    if (value.slideLabelColor)
        object.insert(QStringLiteral(u"slideLabelColor"), *value.slideLabelColor);
    if (value.slideNotes)
        object.insert(QStringLiteral(u"slideNotes"), *value.slideNotes);
    if (value.thumbnailUrl)
        object.insert(QStringLiteral(u"thumbnailUrl"), *value.thumbnailUrl);
    if (value.showThumbnail)
        object.insert(QStringLiteral(u"showThumbnail"), *value.showThumbnail);
    if (value.showText)
        object.insert(QStringLiteral(u"showText"), *value.showText);
    if (value.showNotes)
        object.insert(QStringLiteral(u"showNotes"), *value.showNotes);
    if (value.showLabels)
        object.insert(QStringLiteral(u"showLabels"), *value.showLabels);
    if (value.showName)
        object.insert(QStringLiteral(u"showName"), *value.showName);
    if (value.showNumber)
        object.insert(QStringLiteral(u"showNumber"), *value.showNumber);
    if (value.width)
        object.insert(QStringLiteral(u"width"), *value.width);
    if (value.placedByHand)
        object.insert(QStringLiteral(u"placedByHand"), *value.placedByHand);
    return object;
}

NoteSlideRef NoteSlideRefFromJson(const QJsonObject& object)
{
    NoteSlideRef value;
    if (object.contains(QStringLiteral(u"presentationId")))
        value.presentationId = object.value(QStringLiteral(u"presentationId")).toString();
    if (object.contains(QStringLiteral(u"slideId")))
        value.slideId = object.value(QStringLiteral(u"slideId")).toString();
    if (object.contains(QStringLiteral(u"slideIndex")))
        value.slideIndex = object.value(QStringLiteral(u"slideIndex")).toInt();
    if (object.contains(QStringLiteral(u"ppIntegrationHexId")))
        value.ppIntegrationHexId = object.value(QStringLiteral(u"ppIntegrationHexId")).toString();
    if (object.contains(QStringLiteral(u"ppPresentationUuid")))
        value.ppPresentationUuid = object.value(QStringLiteral(u"ppPresentationUuid")).toString();
    if (object.contains(QStringLiteral(u"ppPlaylistUuid")))
        value.ppPlaylistUuid = object.value(QStringLiteral(u"ppPlaylistUuid")).toString();
    if (object.contains(QStringLiteral(u"ppItemIndex")))
        value.ppItemIndex = object.value(QStringLiteral(u"ppItemIndex")).toInt();
    if (object.contains(QStringLiteral(u"ppSlideIndex")))
        value.ppSlideIndex = object.value(QStringLiteral(u"ppSlideIndex")).toInt();
    if (object.contains(QStringLiteral(u"presentationName")))
        value.presentationName = object.value(QStringLiteral(u"presentationName")).toString();
    if (object.contains(QStringLiteral(u"slideText")))
        value.slideText = object.value(QStringLiteral(u"slideText")).toString();
    if (object.contains(QStringLiteral(u"slideLabel")))
        value.slideLabel = object.value(QStringLiteral(u"slideLabel")).toString();
    if (object.contains(QStringLiteral(u"slideLabelColor")))
        value.slideLabelColor = object.value(QStringLiteral(u"slideLabelColor")).toString();
    if (object.contains(QStringLiteral(u"slideNotes")))
        value.slideNotes = object.value(QStringLiteral(u"slideNotes")).toString();
    if (object.contains(QStringLiteral(u"thumbnailUrl")))
        value.thumbnailUrl = object.value(QStringLiteral(u"thumbnailUrl")).toString();
    if (object.contains(QStringLiteral(u"showThumbnail")))
        value.showThumbnail = object.value(QStringLiteral(u"showThumbnail")).toBool();
    if (object.contains(QStringLiteral(u"showText")))
        value.showText = object.value(QStringLiteral(u"showText")).toBool();
    if (object.contains(QStringLiteral(u"showNotes")))
        value.showNotes = object.value(QStringLiteral(u"showNotes")).toBool();
    if (object.contains(QStringLiteral(u"showLabels")))
        value.showLabels = object.value(QStringLiteral(u"showLabels")).toBool();
    if (object.contains(QStringLiteral(u"showName")))
        value.showName = object.value(QStringLiteral(u"showName")).toBool();
    if (object.contains(QStringLiteral(u"showNumber")))
        value.showNumber = object.value(QStringLiteral(u"showNumber")).toBool();
    if (object.contains(QStringLiteral(u"width")))
        value.width = object.value(QStringLiteral(u"width")).toInt();
    if (object.contains(QStringLiteral(u"placedByHand")))
        value.placedByHand = object.value(QStringLiteral(u"placedByHand")).toBool();
    return value;
}

QJsonObject toJson(const NoteBlock& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"type"), toString(value.type));
    if (value.level)
        object.insert(QStringLiteral(u"level"), *value.level);
    if (value.runs)
        object.insert(QStringLiteral(u"runs"), encodeList(*value.runs, [](const NoteRun& item) { return toJson(item); }));
    if (value.ordered)
        object.insert(QStringLiteral(u"ordered"), *value.ordered);
    if (value.items)
        object.insert(QStringLiteral(u"items"), encodeList(*value.items, [](const NoteListItem& item) { return toJson(item); }));
    if (value.blocks)
        object.insert(QStringLiteral(u"blocks"), encodeList(*value.blocks, [](const NoteBlock& item) { return toJson(item); }));
    if (value.language)
        object.insert(QStringLiteral(u"language"), *value.language);
    if (value.text)
        object.insert(QStringLiteral(u"text"), *value.text);
    if (value.url)
        object.insert(QStringLiteral(u"url"), *value.url);
    if (value.width)
        object.insert(QStringLiteral(u"width"), *value.width);
    if (value.alt)
        object.insert(QStringLiteral(u"alt"), *value.alt);
    if (value.attachmentKind)
        object.insert(QStringLiteral(u"attachmentKind"), *value.attachmentKind);
    if (value.hexId)
        object.insert(QStringLiteral(u"hexId"), *value.hexId);
    if (value.filename)
        object.insert(QStringLiteral(u"filename"), *value.filename);
    if (value.slide)
        object.insert(QStringLiteral(u"slide"), toJson(*value.slide));
    if (value.slideGroup)
        object.insert(QStringLiteral(u"slideGroup"), *value.slideGroup);
    if (value.slideType)
        object.insert(QStringLiteral(u"slideType"), *value.slideType);
    if (value.slideId)
        object.insert(QStringLiteral(u"slideId"), *value.slideId);
    if (value.slideState)
        object.insert(QStringLiteral(u"slideState"), *value.slideState);
    return object;
}

NoteBlock NoteBlockFromJson(const QJsonObject& object)
{
    NoteBlock value;
    value.type = NoteBlockTypeFromString(object.value(QStringLiteral(u"type")).toString());
    if (object.contains(QStringLiteral(u"level")))
        value.level = object.value(QStringLiteral(u"level")).toInt();
    if (object.contains(QStringLiteral(u"runs")))
        value.runs = decodeList<NoteRun>(object.value(QStringLiteral(u"runs")), NoteRunFromJson);
    if (object.contains(QStringLiteral(u"ordered")))
        value.ordered = object.value(QStringLiteral(u"ordered")).toBool();
    if (object.contains(QStringLiteral(u"items")))
        value.items = decodeList<NoteListItem>(object.value(QStringLiteral(u"items")), NoteListItemFromJson);
    if (object.contains(QStringLiteral(u"blocks")))
        value.blocks = decodeList<NoteBlock>(object.value(QStringLiteral(u"blocks")), NoteBlockFromJson);
    if (object.contains(QStringLiteral(u"language")))
        value.language = object.value(QStringLiteral(u"language")).toString();
    if (object.contains(QStringLiteral(u"text")))
        value.text = object.value(QStringLiteral(u"text")).toString();
    if (object.contains(QStringLiteral(u"url")))
        value.url = object.value(QStringLiteral(u"url")).toString();
    if (object.contains(QStringLiteral(u"width")))
        value.width = object.value(QStringLiteral(u"width")).toInt();
    if (object.contains(QStringLiteral(u"alt")))
        value.alt = object.value(QStringLiteral(u"alt")).toString();
    if (object.contains(QStringLiteral(u"attachmentKind")))
        value.attachmentKind = object.value(QStringLiteral(u"attachmentKind")).toString();
    if (object.contains(QStringLiteral(u"hexId")))
        value.hexId = object.value(QStringLiteral(u"hexId")).toString();
    if (object.contains(QStringLiteral(u"filename")))
        value.filename = object.value(QStringLiteral(u"filename")).toString();
    if (object.contains(QStringLiteral(u"slide")))
        value.slide = NoteSlideRefFromJson(object.value(QStringLiteral(u"slide")).toObject());
    if (object.contains(QStringLiteral(u"slideGroup")))
        value.slideGroup = object.value(QStringLiteral(u"slideGroup")).toString();
    if (object.contains(QStringLiteral(u"slideType")))
        value.slideType = object.value(QStringLiteral(u"slideType")).toString();
    if (object.contains(QStringLiteral(u"slideId")))
        value.slideId = object.value(QStringLiteral(u"slideId")).toString();
    if (object.contains(QStringLiteral(u"slideState")))
        value.slideState = object.value(QStringLiteral(u"slideState")).toString();
    return value;
}

QJsonObject toJson(const NoteListItem& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"runs"), encodeList(value.runs, [](const NoteRun& item) { return toJson(item); }));
    if (value.checked)
        object.insert(QStringLiteral(u"checked"), *value.checked);
    if (value.blocks)
        object.insert(QStringLiteral(u"blocks"), encodeList(*value.blocks, [](const NoteBlock& item) { return toJson(item); }));
    return object;
}

NoteListItem NoteListItemFromJson(const QJsonObject& object)
{
    NoteListItem value;
    value.runs = decodeList<NoteRun>(object.value(QStringLiteral(u"runs")), NoteRunFromJson);
    if (object.contains(QStringLiteral(u"checked")))
        value.checked = object.value(QStringLiteral(u"checked")).toBool();
    if (object.contains(QStringLiteral(u"blocks")))
        value.blocks = decodeList<NoteBlock>(object.value(QStringLiteral(u"blocks")), NoteBlockFromJson);
    return value;
}

QJsonObject toJson(const NoteBody& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"blocks"), encodeList(value.blocks, [](const NoteBlock& item) { return toJson(item); }));
    object.insert(QStringLiteral(u"plainText"), value.plainText);
    return object;
}

NoteBody NoteBodyFromJson(const QJsonObject& object)
{
    NoteBody value;
    value.blocks = decodeList<NoteBlock>(object.value(QStringLiteral(u"blocks")), NoteBlockFromJson);
    value.plainText = object.value(QStringLiteral(u"plainText")).toString();
    return value;
}

QJsonObject toJson(const SlideAnchor& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"presentationId"), value.presentationId);
    object.insert(QStringLiteral(u"slideId"), value.slideId);
    object.insert(QStringLiteral(u"slideIndex"), value.slideIndex);
    object.insert(QStringLiteral(u"blockIndex"), value.blockIndex);
    if (value.offset)
        object.insert(QStringLiteral(u"offset"), *value.offset);
    return object;
}

SlideAnchor SlideAnchorFromJson(const QJsonObject& object)
{
    SlideAnchor value;
    value.presentationId = object.value(QStringLiteral(u"presentationId")).toString();
    value.slideId = object.value(QStringLiteral(u"slideId")).toString();
    value.slideIndex = object.value(QStringLiteral(u"slideIndex")).toInt();
    value.blockIndex = object.value(QStringLiteral(u"blockIndex")).toInt();
    if (object.contains(QStringLiteral(u"offset")))
        value.offset = object.value(QStringLiteral(u"offset")).toInt();
    return value;
}

QJsonObject toJson(const NoteMadeBox& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"text"), value.text);
    return object;
}

NoteMadeBox NoteMadeBoxFromJson(const QJsonObject& object)
{
    NoteMadeBox value;
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.text = object.value(QStringLiteral(u"text")).toString();
    return value;
}

QJsonObject toJson(const NoteMadeSlide& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"slideId"), value.slideId);
    object.insert(QStringLiteral(u"boxes"), encodeList(value.boxes, [](const NoteMadeBox& item) { return toJson(item); }));
    return object;
}

NoteMadeSlide NoteMadeSlideFromJson(const QJsonObject& object)
{
    NoteMadeSlide value;
    value.slideId = object.value(QStringLiteral(u"slideId")).toString();
    value.boxes = decodeList<NoteMadeBox>(object.value(QStringLiteral(u"boxes")), NoteMadeBoxFromJson);
    return value;
}

QJsonObject toJson(const NoteMadePassage& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"groupId"), value.groupId);
    object.insert(QStringLiteral(u"text"), value.text);
    if (value.kind)
        object.insert(QStringLiteral(u"kind"), *value.kind);
    if (value.themeSlideName)
        object.insert(QStringLiteral(u"themeSlideName"), *value.themeSlideName);
    if (value.themeId)
        object.insert(QStringLiteral(u"themeId"), *value.themeId);
    object.insert(QStringLiteral(u"slides"), encodeList(value.slides, [](const NoteMadeSlide& item) { return toJson(item); }));
    return object;
}

NoteMadePassage NoteMadePassageFromJson(const QJsonObject& object)
{
    NoteMadePassage value;
    value.groupId = object.value(QStringLiteral(u"groupId")).toString();
    value.text = object.value(QStringLiteral(u"text")).toString();
    if (object.contains(QStringLiteral(u"kind")))
        value.kind = object.value(QStringLiteral(u"kind")).toString();
    if (object.contains(QStringLiteral(u"themeSlideName")))
        value.themeSlideName = object.value(QStringLiteral(u"themeSlideName")).toString();
    if (object.contains(QStringLiteral(u"themeId")))
        value.themeId = object.value(QStringLiteral(u"themeId")).toString();
    value.slides = decodeList<NoteMadeSlide>(object.value(QStringLiteral(u"slides")), NoteMadeSlideFromJson);
    return value;
}

QJsonObject toJson(const NotePendingUpdate& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"kind"), value.kind);
    object.insert(QStringLiteral(u"groupId"), value.groupId);
    if (value.slideId)
        object.insert(QStringLiteral(u"slideId"), *value.slideId);
    if (value.afterSlideId)
        object.insert(QStringLiteral(u"afterSlideId"), *value.afterSlideId);
    if (value.before)
        object.insert(QStringLiteral(u"before"), encodeList(*value.before, [](const NoteMadeBox& item) { return toJson(item); }));
    if (value.after)
        object.insert(QStringLiteral(u"after"), encodeList(*value.after, [](const NoteMadeBox& item) { return toJson(item); }));
    if (value.proposed)
        object.insert(QStringLiteral(u"proposed"), toJson(*value.proposed));
    return object;
}

NotePendingUpdate NotePendingUpdateFromJson(const QJsonObject& object)
{
    NotePendingUpdate value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.kind = object.value(QStringLiteral(u"kind")).toString();
    value.groupId = object.value(QStringLiteral(u"groupId")).toString();
    if (object.contains(QStringLiteral(u"slideId")))
        value.slideId = object.value(QStringLiteral(u"slideId")).toString();
    if (object.contains(QStringLiteral(u"afterSlideId")))
        value.afterSlideId = object.value(QStringLiteral(u"afterSlideId")).toString();
    if (object.contains(QStringLiteral(u"before")))
        value.before = decodeList<NoteMadeBox>(object.value(QStringLiteral(u"before")), NoteMadeBoxFromJson);
    if (object.contains(QStringLiteral(u"after")))
        value.after = decodeList<NoteMadeBox>(object.value(QStringLiteral(u"after")), NoteMadeBoxFromJson);
    if (object.contains(QStringLiteral(u"proposed")))
        value.proposed = SlideFromJson(object.value(QStringLiteral(u"proposed")).toObject());
    return value;
}

QJsonObject toJson(const NoteMediaImport& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"key"), value.key);
    object.insert(QStringLiteral(u"mediaId"), value.mediaId);
    return object;
}

NoteMediaImport NoteMediaImportFromJson(const QJsonObject& object)
{
    NoteMediaImport value;
    value.key = object.value(QStringLiteral(u"key")).toString();
    value.mediaId = object.value(QStringLiteral(u"mediaId")).toString();
    return value;
}

QJsonObject toJson(const NoteSkippedUpdate& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"text"), value.text);
    return object;
}

NoteSkippedUpdate NoteSkippedUpdateFromJson(const QJsonObject& object)
{
    NoteSkippedUpdate value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.text = object.value(QStringLiteral(u"text")).toString();
    return value;
}

QJsonObject toJson(const NoteDocument& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    if (value.folder)
        object.insert(QStringLiteral(u"folder"), *value.folder);
    object.insert(QStringLiteral(u"origin"), value.origin);
    if (value.mxuDocumentHexId)
        object.insert(QStringLiteral(u"mxuDocumentHexId"), *value.mxuDocumentHexId);
    if (value.mxuVersion)
        object.insert(QStringLiteral(u"mxuVersion"), *value.mxuVersion);
    if (value.mxuUpdatedAt)
        object.insert(QStringLiteral(u"mxuUpdatedAt"), *value.mxuUpdatedAt);
    if (value.mxuIconEmoji)
        object.insert(QStringLiteral(u"mxuIconEmoji"), *value.mxuIconEmoji);
    if (value.body)
        object.insert(QStringLiteral(u"body"), toJson(*value.body));
    if (value.anchors)
        object.insert(QStringLiteral(u"anchors"), encodeList(*value.anchors, [](const SlideAnchor& item) { return toJson(item); }));
    if (value.removedFromMxU)
        object.insert(QStringLiteral(u"removedFromMxU"), *value.removedFromMxU);
    if (value.presentationId)
        object.insert(QStringLiteral(u"presentationId"), *value.presentationId);
    if (value.slidesMadeFromSubmittedAt)
        object.insert(QStringLiteral(u"slidesMadeFromSubmittedAt"), *value.slidesMadeFromSubmittedAt);
    if (value.madePassages)
        object.insert(QStringLiteral(u"madePassages"), encodeList(*value.madePassages, [](const NoteMadePassage& item) { return toJson(item); }));
    if (value.markedByStructure)
        object.insert(QStringLiteral(u"markedByStructure"), *value.markedByStructure);
    if (value.pendingUpdates)
        object.insert(QStringLiteral(u"pendingUpdates"), encodeList(*value.pendingUpdates, [](const NotePendingUpdate& item) { return toJson(item); }));
    if (value.mediaImports)
        object.insert(QStringLiteral(u"mediaImports"), encodeList(*value.mediaImports, [](const NoteMediaImport& item) { return toJson(item); }));
    if (value.buildMode)
        object.insert(QStringLiteral(u"buildMode"), *value.buildMode);
    if (value.skippedUpdates)
        object.insert(QStringLiteral(u"skippedUpdates"), encodeList(*value.skippedUpdates, [](const NoteSkippedUpdate& item) { return toJson(item); }));
    return object;
}

NoteDocument NoteDocumentFromJson(const QJsonObject& object)
{
    NoteDocument value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    if (object.contains(QStringLiteral(u"folder")))
        value.folder = object.value(QStringLiteral(u"folder")).toString();
    value.origin = object.value(QStringLiteral(u"origin")).toString();
    if (object.contains(QStringLiteral(u"mxuDocumentHexId")))
        value.mxuDocumentHexId = object.value(QStringLiteral(u"mxuDocumentHexId")).toString();
    if (object.contains(QStringLiteral(u"mxuVersion")))
        value.mxuVersion = object.value(QStringLiteral(u"mxuVersion")).toString();
    if (object.contains(QStringLiteral(u"mxuUpdatedAt")))
        value.mxuUpdatedAt = object.value(QStringLiteral(u"mxuUpdatedAt")).toString();
    if (object.contains(QStringLiteral(u"mxuIconEmoji")))
        value.mxuIconEmoji = object.value(QStringLiteral(u"mxuIconEmoji")).toString();
    if (object.contains(QStringLiteral(u"body")))
        value.body = NoteBodyFromJson(object.value(QStringLiteral(u"body")).toObject());
    if (object.contains(QStringLiteral(u"anchors")))
        value.anchors = decodeList<SlideAnchor>(object.value(QStringLiteral(u"anchors")), SlideAnchorFromJson);
    if (object.contains(QStringLiteral(u"removedFromMxU")))
        value.removedFromMxU = object.value(QStringLiteral(u"removedFromMxU")).toBool();
    if (object.contains(QStringLiteral(u"presentationId")))
        value.presentationId = object.value(QStringLiteral(u"presentationId")).toString();
    if (object.contains(QStringLiteral(u"slidesMadeFromSubmittedAt")))
        value.slidesMadeFromSubmittedAt = object.value(QStringLiteral(u"slidesMadeFromSubmittedAt")).toString();
    if (object.contains(QStringLiteral(u"madePassages")))
        value.madePassages = decodeList<NoteMadePassage>(object.value(QStringLiteral(u"madePassages")), NoteMadePassageFromJson);
    if (object.contains(QStringLiteral(u"markedByStructure")))
        value.markedByStructure = object.value(QStringLiteral(u"markedByStructure")).toBool();
    if (object.contains(QStringLiteral(u"pendingUpdates")))
        value.pendingUpdates = decodeList<NotePendingUpdate>(object.value(QStringLiteral(u"pendingUpdates")), NotePendingUpdateFromJson);
    if (object.contains(QStringLiteral(u"mediaImports")))
        value.mediaImports = decodeList<NoteMediaImport>(object.value(QStringLiteral(u"mediaImports")), NoteMediaImportFromJson);
    if (object.contains(QStringLiteral(u"buildMode")))
        value.buildMode = object.value(QStringLiteral(u"buildMode")).toString();
    if (object.contains(QStringLiteral(u"skippedUpdates")))
        value.skippedUpdates = decodeList<NoteSkippedUpdate>(object.value(QStringLiteral(u"skippedUpdates")), NoteSkippedUpdateFromJson);
    return value;
}

QJsonObject toJson(const StationSettings& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    if (value.localOnlyThresholdBytes)
        object.insert(QStringLiteral(u"localOnlyThresholdBytes"), *value.localOnlyThresholdBytes);
    return object;
}

StationSettings StationSettingsFromJson(const QJsonObject& object)
{
    StationSettings value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    if (object.contains(QStringLiteral(u"localOnlyThresholdBytes")))
        value.localOnlyThresholdBytes = object.value(QStringLiteral(u"localOnlyThresholdBytes")).toInt();
    return value;
}

QJsonObject toJson(const SlideBuildingSettings& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    if (value.designMap)
        object.insert(QStringLiteral(u"designMap"), *value.designMap);
    if (value.messageNotesThemeId)
        object.insert(QStringLiteral(u"messageNotesThemeId"), *value.messageNotesThemeId);
    if (value.lyricsImportThemeId)
        object.insert(QStringLiteral(u"lyricsImportThemeId"), *value.lyricsImportThemeId);
    if (value.lyricsImportDesign)
        object.insert(QStringLiteral(u"lyricsImportDesign"), *value.lyricsImportDesign);
    return object;
}

SlideBuildingSettings SlideBuildingSettingsFromJson(const QJsonObject& object)
{
    SlideBuildingSettings value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    if (object.contains(QStringLiteral(u"designMap")))
        value.designMap = object.value(QStringLiteral(u"designMap")).toString();
    if (object.contains(QStringLiteral(u"messageNotesThemeId")))
        value.messageNotesThemeId = object.value(QStringLiteral(u"messageNotesThemeId")).toString();
    if (object.contains(QStringLiteral(u"lyricsImportThemeId")))
        value.lyricsImportThemeId = object.value(QStringLiteral(u"lyricsImportThemeId")).toString();
    if (object.contains(QStringLiteral(u"lyricsImportDesign")))
        value.lyricsImportDesign = object.value(QStringLiteral(u"lyricsImportDesign")).toString();
    return value;
}

QJsonObject toJson(const FontFile& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"family"), value.family);
    object.insert(QStringLiteral(u"faces"), encodeList(value.faces));
    object.insert(QStringLiteral(u"ext"), value.ext);
    if (value.byteSize)
        object.insert(QStringLiteral(u"byteSize"), *value.byteSize);
    return object;
}

FontFile FontFileFromJson(const QJsonObject& object)
{
    FontFile value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.family = object.value(QStringLiteral(u"family")).toString();
    value.faces = decodeList<QString>(object.value(QStringLiteral(u"faces")));
    value.ext = object.value(QStringLiteral(u"ext")).toString();
    if (object.contains(QStringLiteral(u"byteSize")))
        value.byteSize = object.value(QStringLiteral(u"byteSize")).toInt();
    return value;
}

QJsonObject toJson(const WorkspaceSettings& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    if (value.screens)
        object.insert(QStringLiteral(u"screens"), *value.screens);
    if (value.timers)
        object.insert(QStringLiteral(u"timers"), *value.timers);
    if (value.transitions)
        object.insert(QStringLiteral(u"transitions"), *value.transitions);
    if (value.controlMappings)
        object.insert(QStringLiteral(u"controlMappings"), *value.controlMappings);
    if (value.audio)
        object.insert(QStringLiteral(u"audio"), *value.audio);
    if (value.confidence)
        object.insert(QStringLiteral(u"confidence"), *value.confidence);
    if (value.inputs)
        object.insert(QStringLiteral(u"inputs"), *value.inputs);
    if (value.behavior)
        object.insert(QStringLiteral(u"behavior"), *value.behavior);
    return object;
}

WorkspaceSettings WorkspaceSettingsFromJson(const QJsonObject& object)
{
    WorkspaceSettings value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    if (object.contains(QStringLiteral(u"screens")))
        value.screens = object.value(QStringLiteral(u"screens")).toString();
    if (object.contains(QStringLiteral(u"timers")))
        value.timers = object.value(QStringLiteral(u"timers")).toString();
    if (object.contains(QStringLiteral(u"transitions")))
        value.transitions = object.value(QStringLiteral(u"transitions")).toString();
    if (object.contains(QStringLiteral(u"controlMappings")))
        value.controlMappings = object.value(QStringLiteral(u"controlMappings")).toString();
    if (object.contains(QStringLiteral(u"audio")))
        value.audio = object.value(QStringLiteral(u"audio")).toString();
    if (object.contains(QStringLiteral(u"confidence")))
        value.confidence = object.value(QStringLiteral(u"confidence")).toString();
    if (object.contains(QStringLiteral(u"inputs")))
        value.inputs = object.value(QStringLiteral(u"inputs")).toString();
    if (object.contains(QStringLiteral(u"behavior")))
        value.behavior = object.value(QStringLiteral(u"behavior")).toString();
    return value;
}

QJsonObject toJson(const TrackChannel& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    if (value.role)
        object.insert(QStringLiteral(u"role"), *value.role);
    if (value.colorHex)
        object.insert(QStringLiteral(u"colorHex"), *value.colorHex);
    if (value.matchNames)
        object.insert(QStringLiteral(u"matchNames"), encodeList(*value.matchNames));
    if (value.mono)
        object.insert(QStringLiteral(u"mono"), *value.mono);
    return object;
}

TrackChannel TrackChannelFromJson(const QJsonObject& object)
{
    TrackChannel value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    if (object.contains(QStringLiteral(u"role")))
        value.role = object.value(QStringLiteral(u"role")).toString();
    if (object.contains(QStringLiteral(u"colorHex")))
        value.colorHex = object.value(QStringLiteral(u"colorHex")).toString();
    if (object.contains(QStringLiteral(u"matchNames")))
        value.matchNames = decodeList<QString>(object.value(QStringLiteral(u"matchNames")));
    if (object.contains(QStringLiteral(u"mono")))
        value.mono = object.value(QStringLiteral(u"mono")).toBool();
    return value;
}

QJsonObject toJson(const TrackChannelList& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"channels"), encodeList(value.channels, [](const TrackChannel& item) { return toJson(item); }));
    return object;
}

TrackChannelList TrackChannelListFromJson(const QJsonObject& object)
{
    TrackChannelList value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.channels = decodeList<TrackChannel>(object.value(QStringLiteral(u"channels")), TrackChannelFromJson);
    return value;
}

QJsonObject toJson(const TrackSetStem& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"audioId"), value.audioId);
    object.insert(QStringLiteral(u"name"), value.name);
    if (value.channelId)
        object.insert(QStringLiteral(u"channelId"), *value.channelId);
    return object;
}

TrackSetStem TrackSetStemFromJson(const QJsonObject& object)
{
    TrackSetStem value;
    value.audioId = object.value(QStringLiteral(u"audioId")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    if (object.contains(QStringLiteral(u"channelId")))
        value.channelId = object.value(QStringLiteral(u"channelId")).toString();
    return value;
}

QJsonObject toJson(const TrackSet& value)
{
    QJsonObject object;
    object.insert(QStringLiteral(u"id"), value.id);
    object.insert(QStringLiteral(u"name"), value.name);
    object.insert(QStringLiteral(u"stems"), encodeList(value.stems, [](const TrackSetStem& item) { return toJson(item); }));
    if (value.key)
        object.insert(QStringLiteral(u"key"), *value.key);
    if (value.tempo)
        object.insert(QStringLiteral(u"tempo"), *value.tempo);
    if (value.source)
        object.insert(QStringLiteral(u"source"), *value.source);
    return object;
}

TrackSet TrackSetFromJson(const QJsonObject& object)
{
    TrackSet value;
    value.id = object.value(QStringLiteral(u"id")).toString();
    value.name = object.value(QStringLiteral(u"name")).toString();
    value.stems = decodeList<TrackSetStem>(object.value(QStringLiteral(u"stems")), TrackSetStemFromJson);
    if (object.contains(QStringLiteral(u"key")))
        value.key = object.value(QStringLiteral(u"key")).toString();
    if (object.contains(QStringLiteral(u"tempo")))
        value.tempo = object.value(QStringLiteral(u"tempo")).toDouble();
    if (object.contains(QStringLiteral(u"source")))
        value.source = object.value(QStringLiteral(u"source")).toString();
    return value;
}

} // namespace mxu::model
