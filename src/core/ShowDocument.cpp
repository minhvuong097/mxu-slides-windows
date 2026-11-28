#include "ShowDocument.h"

#include <QJsonDocument>
#include <QUuid>
#include <QJsonObject>
#include <QDateTime>

namespace mxu::core {

static QVariantList animationStepsForQml(const std::optional<QVector<model::AnimationStep>>& steps);

namespace {
QString makeId()
{
    return QUuid::createUuid().toString(QUuid::WithoutBraces);
}

QJsonObject snapshot(const Document& document)
{
    return QJsonDocument::fromJson(document.toJson()).object();
}
} // namespace

void ShowDocument::setDocument(Document document)
{
    m_document = std::move(document);
    m_undo.clear();
    m_redo.clear();
    m_selectedSlide.clear();
    m_selectedObject.clear();
    if (!m_document.slides.isEmpty())
        m_selectedSlide = m_document.slides.first().id;
}

void ShowDocument::pushUndo()
{
    m_undo.append(snapshot(m_document));
    if (m_undo.size() > kMaxHistory)
        m_undo.removeFirst();
    m_redo.clear();
}

void ShowDocument::undo()
{
    if (m_undo.isEmpty())
        return;
    m_redo.append(snapshot(m_document));
    const QJsonObject previous = m_undo.takeLast();
    m_document = Document::fromJson(QJsonDocument(previous).toJson());
}

void ShowDocument::redo()
{
    if (m_redo.isEmpty())
        return;
    m_undo.append(snapshot(m_document));
    const QJsonObject next = m_redo.takeLast();
    m_document = Document::fromJson(QJsonDocument(next).toJson());
}

model::Slide* ShowDocument::findSlide(const QString& id)
{
    for (auto& slide : m_document.slides) {
        if (slide.id == id)
            return &slide;
    }
    return nullptr;
}

const model::Slide* ShowDocument::findSlide(const QString& id) const
{
    for (const auto& slide : m_document.slides) {
        if (slide.id == id)
            return &slide;
    }
    return nullptr;
}

model::SlideObject* ShowDocument::findObject(const QString& slideId, const QString& objectId)
{
    model::Slide* slide = findSlide(slideId);
    if (!slide)
        return nullptr;
    for (auto& object : slide->objects) {
        if (object.id == objectId)
            return &object;
    }
    return nullptr;
}

QString ShowDocument::addSlide(const QString& name, const QString& text)
{
    pushUndo();
    model::Slide slide;
    slide.id = makeId();
    slide.name = name.isEmpty() ? QStringLiteral(u"Untitled") : name;
    model::SlideObject object;
    object.id = makeId();
    object.objectKind = model::SlideObjectKind::Text;
    object.name = QStringLiteral(u"Lyrics");
    object.text = text;
    object.x = 70.0;
    object.y = 130.0;
    object.width = 500.0;
    object.height = 100.0;
    object.textStyle = model::TextStyle{};
    object.textStyle->fontName = QStringLiteral(u"Segoe UI");
    object.textStyle->fontSize = 22.0;
    object.textStyle->colorHex = QStringLiteral(u"#FFFFFF");
    object.textStyle->horizontalAlignment = model::TextHorizontalAlignment::Center;
    slide.objects.append(object);

    m_document.slides.append(slide);
    m_selectedSlide = slide.id;
    m_selectedObject = object.id;
    return slide.id;
}

bool ShowDocument::removeSlide(const QString& id)
{
    for (qsizetype i = 0; i < m_document.slides.size(); ++i) {
        if (m_document.slides[i].id != id)
            continue;
        pushUndo();
        m_document.slides.removeAt(i);
        if (m_selectedSlide == id)
            m_selectedSlide = m_document.slides.isEmpty() ? QString()
                                                          : m_document.slides.first().id;
        return true;
    }
    return false;
}

bool ShowDocument::duplicateSlide(const QString& id)
{
    const model::Slide* source = findSlide(id);
    if (!source)
        return false;
    pushUndo();
    model::Slide copy = *source;
    copy.id = makeId();
    copy.name = source->name + QStringLiteral(u" copy");
    for (auto& object : copy.objects)
        object.id = makeId();
    m_document.slides.append(copy);
    m_selectedSlide = copy.id;
    return true;
}

bool ShowDocument::moveSlide(const QString& id, int delta)
{
    for (qsizetype i = 0; i < m_document.slides.size(); ++i) {
        if (m_document.slides[i].id != id)
            continue;
        const qsizetype target = i + delta;
        if (target < 0 || target >= m_document.slides.size())
            return false;
        pushUndo();
        m_document.slides.move(i, target);
        return true;
    }
    return false;
}

QString ShowDocument::addTextObject(const QString& slideId, const QString& text,
                                    double x, double y, double width, double height)
{
    model::Slide* slide = findSlide(slideId);
    if (!slide)
        return {};
    pushUndo();
    model::SlideObject object;
    object.id = makeId();
    object.objectKind = model::SlideObjectKind::Text;
    object.name = QStringLiteral(u"Text");
    object.text = text;
    object.x = x;
    object.y = y;
    object.width = width;
    object.height = height;
    object.textStyle = model::TextStyle{};
    object.textStyle->fontName = QStringLiteral(u"Segoe UI");
    object.textStyle->fontSize = 22.0;
    object.textStyle->colorHex = QStringLiteral(u"#FFFFFF");
    object.textStyle->horizontalAlignment = model::TextHorizontalAlignment::Center;
    slide->objects.append(object);
    m_selectedObject = object.id;
    return object.id;
}

bool ShowDocument::updateObject(const QString& slideId, const QString& objectId,
                                const QVariantMap& patch)
{
    model::SlideObject* object = findObject(slideId, objectId);
    if (!object)
        return false;
    pushUndo();

    auto number = [&patch](const QString& key, double& target) {
        if (patch.contains(key))
            target = patch.value(key).toDouble();
    };
    number(QStringLiteral(u"x"), *object->x);
    number(QStringLiteral(u"y"), *object->y);
    number(QStringLiteral(u"width"), *object->width);
    number(QStringLiteral(u"height"), *object->height);
    if (patch.contains(QStringLiteral(u"text")))
        object->text = patch.value(QStringLiteral(u"text")).toString();

    if (!object->textStyle)
        object->textStyle = model::TextStyle{};
    if (patch.contains(QStringLiteral(u"fontSize")))
        object->textStyle->fontSize = patch.value(QStringLiteral(u"fontSize")).toDouble();
    if (patch.contains(QStringLiteral(u"colorHex")))
        object->textStyle->colorHex = patch.value(QStringLiteral(u"colorHex")).toString();
    if (patch.contains(QStringLiteral(u"fontName")))
        object->textStyle->fontName = patch.value(QStringLiteral(u"fontName")).toString();
    if (patch.contains(QStringLiteral(u"styleRun"))) {
        const QVariantMap runMap = patch.value(QStringLiteral(u"styleRun")).toMap();
        model::TextStyleRun run;
        run.line = runMap.value(QStringLiteral(u"line")).toInt();
        run.column = runMap.value(QStringLiteral(u"column")).toInt();
        run.length = runMap.value(QStringLiteral(u"length")).toInt();
        if (runMap.contains(QStringLiteral(u"colorHex")))
            run.colorHex = runMap.value(QStringLiteral(u"colorHex")).toString();
        if (runMap.contains(QStringLiteral(u"underline")))
            run.underline = runMap.value(QStringLiteral(u"underline")).toBool();
        if (runMap.contains(QStringLiteral(u"fontSize")))
            run.fontSize = runMap.value(QStringLiteral(u"fontSize")).toDouble();
        if (!object->styleRuns)
            object->styleRuns = QVector<model::TextStyleRun>();
        object->styleRuns->append(run);
    }

    if (patch.contains(QStringLiteral(u"animationSeconds"))) {
        model::AnimationStep step;
        step.id = makeId();
        step.kind = model::AnimationKind::In;
        step.animation = model::StepAnimation::Fade;
        step.trigger = model::AnimationTrigger::OnClick;
        step.durationSeconds = patch.value(QStringLiteral(u"animationSeconds")).toDouble();
        object->animationSteps = QVector<model::AnimationStep>{ step };
    }

    // Deep object editing (Mac SlideObjectInspector parity).
    auto optionalNumber = [&patch](const QString& key, std::optional<double>& target) {
        if (patch.contains(key))
            target = patch.value(key).toDouble();
    };
    auto optionalString = [&patch](const QString& key, std::optional<QString>& target) {
        if (patch.contains(key))
            target = patch.value(key).toString();
    };
    auto optionalBool = [&patch](const QString& key, std::optional<bool>& target) {
        if (patch.contains(key))
            target = patch.value(key).toBool();
    };
    optionalNumber(QStringLiteral(u"rotationDegrees"), object->rotationDegrees);
    optionalNumber(QStringLiteral(u"opacity"), object->opacity);
    optionalNumber(QStringLiteral(u"cornerRadius"), object->cornerRadius);
    optionalNumber(QStringLiteral(u"tilt"), object->tilt);
    optionalNumber(QStringLiteral(u"swing"), object->swing);
    optionalBool(QStringLiteral(u"hidden"), object->hidden);
    optionalBool(QStringLiteral(u"flipHorizontal"), object->flipHorizontal);
    optionalBool(QStringLiteral(u"flipVertical"), object->flipVertical);
    optionalString(QStringLiteral(u"groupId"), object->groupId);
    optionalString(QStringLiteral(u"mediaId"), object->mediaId);
    if (patch.contains(QStringLiteral(u"blendMode")))
        object->blendMode = model::BlendModeFromString(patch.value(QStringLiteral(u"blendMode")).toString());
    if (patch.contains(QStringLiteral(u"shapeKind")))
        object->shapeKind = model::ShapeKindFromString(patch.value(QStringLiteral(u"shapeKind")).toString());

    if (patch.contains(QStringLiteral(u"fillColor"))) {
        const QString color = patch.value(QStringLiteral(u"fillColor")).toString();
        if (!object->fill)
            object->fill = model::ObjectFill{ model::FillKind::Solid, color };
        else
            object->fill->colorHex = color;
    }
    if (patch.contains(QStringLiteral(u"strokeColor")) || patch.contains(QStringLiteral(u"strokeWidth"))) {
        const QString color = patch.contains(QStringLiteral(u"strokeColor"))
                              ? patch.value(QStringLiteral(u"strokeColor")).toString()
                              : (object->stroke ? object->stroke->colorHex : QStringLiteral(u"#FFFFFF"));
        const double width = patch.contains(QStringLiteral(u"strokeWidth"))
                             ? patch.value(QStringLiteral(u"strokeWidth")).toDouble()
                             : (object->stroke ? object->stroke->width : 0.0);
        object->stroke = model::ObjectStroke{ color, width };
    }
    if (patch.contains(QStringLiteral(u"shadowColor")) || patch.contains(QStringLiteral(u"shadowBlur"))
        || patch.contains(QStringLiteral(u"shadowOffsetX")) || patch.contains(QStringLiteral(u"shadowOffsetY"))) {
        model::ObjectShadow shadow = object->shadow.value_or(model::ObjectShadow{});
        if (patch.contains(QStringLiteral(u"shadowColor")))
            shadow.colorHex = patch.value(QStringLiteral(u"shadowColor")).toString();
        if (patch.contains(QStringLiteral(u"shadowBlur")))
            shadow.blurRadius = patch.value(QStringLiteral(u"shadowBlur")).toDouble();
        if (patch.contains(QStringLiteral(u"shadowOffsetX")))
            shadow.offsetX = patch.value(QStringLiteral(u"shadowOffsetX")).toDouble();
        if (patch.contains(QStringLiteral(u"shadowOffsetY")))
            shadow.offsetY = patch.value(QStringLiteral(u"shadowOffsetY")).toDouble();
        object->shadow = shadow;
    }

    // Multiple animation steps with explicit kind / effect / trigger.
    if (patch.contains(QStringLiteral(u"animationSteps"))) {
        QVector<model::AnimationStep> steps;
        for (const QVariant& value : patch.value(QStringLiteral(u"animationSteps")).toList()) {
            const QVariantMap map = value.toMap();
            model::AnimationStep step;
            step.id = map.value(QStringLiteral(u"id")).toString().isEmpty()
                      ? makeId() : map.value(QStringLiteral(u"id")).toString();
            step.kind = model::AnimationKindFromString(map.value(QStringLiteral(u"kind")).toString());
            step.animation = model::StepAnimationFromString(map.value(QStringLiteral(u"animation")).toString());
            step.trigger = model::AnimationTriggerFromString(map.value(QStringLiteral(u"trigger")).toString());
            step.durationSeconds = map.value(QStringLiteral(u"durationSeconds")).toDouble();
            if (map.contains(QStringLiteral(u"delaySeconds")))
                step.delaySeconds = map.value(QStringLiteral(u"delaySeconds")).toDouble();
            steps.append(step);
        }
        object->animationSteps = steps;
    }
    return true;
}

bool ShowDocument::removeObject(const QString& slideId, const QString& objectId)
{
    model::Slide* slide = findSlide(slideId);
    if (!slide)
        return false;
    for (qsizetype i = 0; i < slide->objects.size(); ++i) {
        if (slide->objects[i].id != objectId)
            continue;
        pushUndo();
        slide->objects.removeAt(i);
        if (m_selectedObject == objectId)
            m_selectedObject.clear();
        return true;
    }
    return false;
}

QString ShowDocument::addAction(const QString& slideId, const QVariantMap& action)
{
    model::Slide* slide = findSlide(slideId);
    if (!slide)
        return {};
    pushUndo();
    model::SlideAction value = model::SlideActionFromJson(QJsonObject::fromVariantMap(action));
    if (value.id.isEmpty())
        value.id = makeId();
    if (!slide->actions)
        slide->actions = QVector<model::SlideAction>();
    slide->actions->append(value);
    return value.id;
}

QVariantList ShowDocument::actionsForQml(const QString& slideId) const
{
    QVariantList result;
    const model::Slide* slide = findSlide(slideId);
    if (!slide || !slide->actions)
        return result;
    for (const auto& action : *slide->actions)
        result.append(model::toJson(action).toVariantMap());
    return result;
}

bool ShowDocument::removeAction(const QString& slideId, const QString& actionId)
{
    model::Slide* slide = findSlide(slideId);
    if (!slide || !slide->actions)
        return false;
    for (qsizetype i = 0; i < slide->actions->size(); ++i) {
        if (slide->actions->at(i).id != actionId)
            continue;
        pushUndo();
        slide->actions->removeAt(i);
        return true;
    }
    return false;
}

QString ShowDocument::saveVersion(const QString& slideId, const QString& reason)
{
    model::Slide* slide = findSlide(slideId);
    if (!slide)
        return {};
    pushUndo();
    model::SlideVersion version;
    version.at = QDateTime::currentDateTimeUtc().toString(Qt::ISODate);
    version.reason = reason.isEmpty() ? QStringLiteral(u"Manual") : reason;
    version.slide = std::make_shared<model::Slide>(*slide);
    if (!slide->history)
        slide->history = QVector<model::SlideVersion>();
    slide->history->append(version);
    return version.at;
}

QVariantList ShowDocument::versionsForQml(const QString& slideId) const
{
    QVariantList result;
    const model::Slide* slide = findSlide(slideId);
    if (!slide || !slide->history)
        return result;
    for (const auto& version : *slide->history) {
        result.append(QVariantMap{
            { QStringLiteral(u"id"), version.at },
            { QStringLiteral(u"at"), version.at },
            { QStringLiteral(u"reason"), version.reason },
        });
    }
    return result;
}

bool ShowDocument::restoreVersion(const QString& slideId, const QString& versionId)
{
    model::Slide* slide = findSlide(slideId);
    if (!slide || !slide->history)
        return false;
    for (const auto& version : *slide->history) {
        if (version.at != versionId || !version.slide)
            continue;
        pushUndo();
        const QString id = slide->id;
        *slide = *version.slide;
        slide->id = id;
        return true;
    }
    return false;
}

QVariantList ShowDocument::slidesForQml() const
{
    QVariantList result;
    for (const auto& slide : m_document.slides) {
        QString text;
        if (!slide.objects.isEmpty())
            text = slide.objects.first().text;
        result.append(QVariantMap{
            { QStringLiteral(u"id"), slide.id },
            { QStringLiteral(u"name"), slide.name },
            { QStringLiteral(u"text"), text },
            { QStringLiteral(u"objectCount"), slide.objects.size() },
        });
    }
    return result;
}

QVariantList ShowDocument::objectsForQml(const QString& slideId) const
{
    QVariantList result;
    const model::Slide* slide = findSlide(slideId);
    if (!slide)
        return result;
    for (const auto& object : slide->objects) {
        result.append(QVariantMap{
            { QStringLiteral(u"id"), object.id },
            { QStringLiteral(u"text"), object.text },
            { QStringLiteral(u"x"), object.x.value_or(0) },
            { QStringLiteral(u"y"), object.y.value_or(0) },
            { QStringLiteral(u"width"), object.width.value_or(0) },
            { QStringLiteral(u"height"), object.height.value_or(0) },
            { QStringLiteral(u"fontSize"), object.textStyle ? object.textStyle->fontSize.value_or(22) : 22 },
            { QStringLiteral(u"colorHex"), object.textStyle && object.textStyle->colorHex
                                               ? *object.textStyle->colorHex : QStringLiteral(u"#FFFFFF") },
            { QStringLiteral(u"fontName"), object.textStyle && object.textStyle->fontName
                                               ? *object.textStyle->fontName : QStringLiteral(u"Segoe UI") },
            { QStringLiteral(u"selected"), object.id == m_selectedObject },
            { QStringLiteral(u"name"), object.name },
            { QStringLiteral(u"animationSteps"), animationStepsForQml(object.animationSteps) },
        });
    }
    return result;
}

static QVariantList styleRunsForQml(const std::optional<QVector<model::TextStyleRun>>& runs)
{
    QVariantList result;
    if (!runs)
        return result;
    for (const auto& run : *runs) {
        result.append(QVariantMap{
            { QStringLiteral(u"line"), run.line },
            { QStringLiteral(u"column"), run.column },
            { QStringLiteral(u"length"), run.length },
            { QStringLiteral(u"colorHex"), run.colorHex.value_or(QString()) },
            { QStringLiteral(u"fontSize"), run.fontSize.value_or(0.0) },
        });
    }
    return result;
}

static QVariantList animationStepsForQml(const std::optional<QVector<model::AnimationStep>>& steps)
{
    QVariantList result;
    if (!steps)
        return result;
    for (const auto& step : *steps) {
        result.append(QVariantMap{
            { QStringLiteral(u"id"), step.id },
            { QStringLiteral(u"kind"), model::toString(step.kind) },
            { QStringLiteral(u"animation"), model::toString(step.animation) },
            { QStringLiteral(u"trigger"), model::toString(step.trigger) },
            { QStringLiteral(u"durationSeconds"), step.durationSeconds },
            { QStringLiteral(u"delaySeconds"), step.delaySeconds.value_or(0.0) },
        });
    }
    return result;
}

QVariantMap ShowDocument::objectForQml(const QString& objectId) const
{
    for (const auto& slide : m_document.slides) {
        for (const auto& object : slide.objects) {
            if (object.id != objectId)
                continue;
            return QVariantMap{
                { QStringLiteral(u"id"), object.id },
                { QStringLiteral(u"objectKind"), model::toString(object.objectKind) },
                { QStringLiteral(u"name"), object.name },
                { QStringLiteral(u"text"), object.text },
                { QStringLiteral(u"x"), object.x.value_or(0) },
                { QStringLiteral(u"y"), object.y.value_or(0) },
                { QStringLiteral(u"width"), object.width.value_or(0) },
                { QStringLiteral(u"height"), object.height.value_or(0) },
                { QStringLiteral(u"rotationDegrees"), object.rotationDegrees.value_or(0) },
                { QStringLiteral(u"hidden"), object.hidden.value_or(false) },
                { QStringLiteral(u"opacity"), object.opacity.value_or(1.0) },
                { QStringLiteral(u"blendMode"), model::toString(object.blendMode.value_or(model::BlendMode::Normal)) },
                { QStringLiteral(u"groupId"), object.groupId.value_or(QString()) },
                { QStringLiteral(u"shapeKind"), object.shapeKind ? model::toString(*object.shapeKind) : QString() },
                { QStringLiteral(u"cornerRadius"), object.cornerRadius.value_or(0) },
                { QStringLiteral(u"fillColor"), object.fill && object.fill->colorHex
                                                    ? *object.fill->colorHex : QString() },
                { QStringLiteral(u"strokeColor"), object.stroke ? object.stroke->colorHex : QString() },
                { QStringLiteral(u"strokeWidth"), object.stroke ? object.stroke->width : 0.0 },
                { QStringLiteral(u"shadowColor"), object.shadow ? object.shadow->colorHex : QString() },
                { QStringLiteral(u"shadowBlur"), object.shadow ? object.shadow->blurRadius : 0.0 },
                { QStringLiteral(u"mediaId"), object.mediaId.value_or(QString()) },
                { QStringLiteral(u"fontSize"), object.textStyle ? object.textStyle->fontSize.value_or(22) : 22 },
                { QStringLiteral(u"colorHex"), object.textStyle && object.textStyle->colorHex
                                                   ? *object.textStyle->colorHex : QStringLiteral(u"#FFFFFF") },
                { QStringLiteral(u"fontName"), object.textStyle && object.textStyle->fontName
                                                   ? *object.textStyle->fontName : QStringLiteral(u"Segoe UI") },
                { QStringLiteral(u"styleRuns"), styleRunsForQml(object.styleRuns) },
                { QStringLiteral(u"animationSteps"), animationStepsForQml(object.animationSteps) },
            };
        }
    }
    return {};
}

} // namespace mxu::core
