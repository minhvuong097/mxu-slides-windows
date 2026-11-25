#include "Document.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>

namespace mxu::core {

namespace {
QJsonArray sectionsToJson(const QVector<ServiceSection>& sections)
{
    QJsonArray result;
    for (const auto& s : sections)
        result.append(QJsonObject{ { QStringLiteral(u"name"), s.name },
                                   { QStringLiteral(u"color"), s.color } });
    return result;
}

QJsonArray itemsToJson(const QVector<ServiceItem>& items)
{
    QJsonArray result;
    for (const auto& i : items)
        result.append(QJsonObject{ { QStringLiteral(u"name"), i.name },
                                   { QStringLiteral(u"section"), i.section },
                                   { QStringLiteral(u"note"), i.note },
                                   { QStringLiteral(u"showId"), i.showId } });
    return result;
}

QJsonArray cuesToJson(const QVector<Cue>& cues)
{
    QJsonArray result;
    for (const auto& cue : cues) {
        QJsonArray chips;
        for (const auto& c : cue.chips)
            chips.append(QJsonObject{ { QStringLiteral(u"name"), c.name },
                                      { QStringLiteral(u"color"), c.color } });
        QJsonArray slides;
        for (const auto& s : cue.slides)
            slides.append(QJsonObject{ { QStringLiteral(u"tag"), s.tag },
                                       { QStringLiteral(u"tagColor"), s.tagColor },
                                       { QStringLiteral(u"text"), s.text } });
        QJsonArray posters;
        for (const auto& p : cue.posters)
            posters.append(QJsonObject{ { QStringLiteral(u"title"), p.title },
                                        { QStringLiteral(u"caption"), p.caption },
                                        { QStringLiteral(u"from"), p.from },
                                        { QStringLiteral(u"to"), p.to } });
        result.append(QJsonObject{
            { QStringLiteral(u"title"), cue.title },
            { QStringLiteral(u"section"), cue.section },
            { QStringLiteral(u"sectionColor"), cue.sectionColor },
            { QStringLiteral(u"meta"), cue.meta },
            { QStringLiteral(u"key"), cue.key },
            { QStringLiteral(u"slideLabel"), cue.slideLabel },
            { QStringLiteral(u"description"), cue.description },
            { QStringLiteral(u"notes"), cue.notes },
            { QStringLiteral(u"notesHighlighted"), cue.notesHighlighted },
            { QStringLiteral(u"pictureShow"), cue.pictureShow },
            { QStringLiteral(u"chips"), chips },
            { QStringLiteral(u"slides"), slides },
            { QStringLiteral(u"posters"), posters },
        });
    }
    return result;
}

QJsonArray mediaToJson(const QVector<MediaItem>& media)
{
    QJsonArray result;
    for (const auto& m : media)
        result.append(QJsonObject{ { QStringLiteral(u"name"), m.name },
                                   { QStringLiteral(u"category"), m.category },
                                   { QStringLiteral(u"folder"), m.folder },
                                   { QStringLiteral(u"type"), m.type },
                                   { QStringLiteral(u"size"), m.size },
                                   { QStringLiteral(u"fileSize"), m.fileSize },
                                   { QStringLiteral(u"from"), m.from },
                                   { QStringLiteral(u"to"), m.to } });
    return result;
}

QVector<ServiceSection> sectionsFromJson(const QJsonArray& array)
{
    QVector<ServiceSection> result;
    for (const QJsonValue& value : array) {
        const QJsonObject o = value.toObject();
        result.append({ o.value(QStringLiteral(u"name")).toString(),
                        o.value(QStringLiteral(u"color")).toString() });
    }
    return result;
}

QVector<ServiceItem> itemsFromJson(const QJsonArray& array)
{
    QVector<ServiceItem> result;
    for (const QJsonValue& value : array) {
        const QJsonObject o = value.toObject();
        result.append({ o.value(QStringLiteral(u"name")).toString(),
                        o.value(QStringLiteral(u"section")).toInt(),
                        o.value(QStringLiteral(u"note")).toString(),
                        o.value(QStringLiteral(u"showId")).toString() });
    }
    return result;
}

QVector<Cue> cuesFromJson(const QJsonArray& array)
{
    QVector<Cue> result;
    for (const QJsonValue& value : array) {
        const QJsonObject o = value.toObject();
        Cue cue;
        cue.title = o.value(QStringLiteral(u"title")).toString();
        cue.section = o.value(QStringLiteral(u"section")).toString();
        cue.sectionColor = o.value(QStringLiteral(u"sectionColor")).toString();
        cue.meta = o.value(QStringLiteral(u"meta")).toString();
        cue.key = o.value(QStringLiteral(u"key")).toString();
        cue.slideLabel = o.value(QStringLiteral(u"slideLabel")).toString();
        cue.description = o.value(QStringLiteral(u"description")).toString();
        cue.notes = o.value(QStringLiteral(u"notes")).toString();
        cue.notesHighlighted = o.value(QStringLiteral(u"notesHighlighted")).toBool();
        cue.pictureShow = o.value(QStringLiteral(u"pictureShow")).toBool();
        for (const QJsonValue& c : o.value(QStringLiteral(u"chips")).toArray()) {
            const QJsonObject co = c.toObject();
            cue.chips.append({ co.value(QStringLiteral(u"name")).toString(),
                               co.value(QStringLiteral(u"color")).toString() });
        }
        for (const QJsonValue& s : o.value(QStringLiteral(u"slides")).toArray()) {
            const QJsonObject so = s.toObject();
            cue.slides.append({ so.value(QStringLiteral(u"tag")).toString(),
                                so.value(QStringLiteral(u"tagColor")).toString(),
                                so.value(QStringLiteral(u"text")).toString() });
        }
        for (const QJsonValue& p : o.value(QStringLiteral(u"posters")).toArray()) {
            const QJsonObject po = p.toObject();
            cue.posters.append({ po.value(QStringLiteral(u"title")).toString(),
                                 po.value(QStringLiteral(u"caption")).toString(),
                                 po.value(QStringLiteral(u"from")).toString(),
                                 po.value(QStringLiteral(u"to")).toString() });
        }
        result.append(cue);
    }
    return result;
}

QVector<MediaItem> mediaFromJson(const QJsonArray& array)
{
    QVector<MediaItem> result;
    for (const QJsonValue& value : array) {
        const QJsonObject o = value.toObject();
        result.append({ o.value(QStringLiteral(u"name")).toString(),
                        o.value(QStringLiteral(u"category")).toString(),
                        o.value(QStringLiteral(u"folder")).toString(),
                        o.value(QStringLiteral(u"type")).toString(),
                        o.value(QStringLiteral(u"size")).toString(),
                        o.value(QStringLiteral(u"fileSize")).toString(),
                        o.value(QStringLiteral(u"from")).toString(),
                        o.value(QStringLiteral(u"to")).toString() });
    }
    return result;
}

Cue preRollCue()
{
    Cue cue;
    cue.title = QStringLiteral(u"Pre-roll");
    cue.section = QStringLiteral(u"PRE-SERVICE");
    cue.sectionColor = QStringLiteral(u"#ffd60a");
    cue.meta = QStringLiteral(u"Slide Show: 5s · Loop");
    cue.slideLabel = QStringLiteral(u"Slide 1 of 12");
    cue.description = QStringLiteral(u"- Countdown running, automated in presentation software.\n- Playlist running during pre-service.");
    cue.notes = QStringLiteral(u"Countdown and playlist run automatically before the service.");
    cue.notesHighlighted = true;
    cue.pictureShow = true;
    cue.posters = {
        { QStringLiteral(u"VOLUNTEER\nNIGHT"), QStringLiteral(u"10 volunteer-night.jpg"), QStringLiteral(u"#6a2cf0"), QStringLiteral(u"#0a0a2a") },
        { QStringLiteral(u"PRAYER\nNIGHT"), QStringLiteral(u"11 Prayer Night Oct 1"), QStringLiteral(u"#2a2a2e"), QStringLiteral(u"#0b0b0c") },
        { QStringLiteral(u"FAMILY\nFUN NIGHT"), QStringLiteral(u"12 Family Fun Night"), QStringLiteral(u"#ff375f"), QStringLiteral(u"#a81a8f") },
    };
    return cue;
}

Cue worshipCue()
{
    Cue cue;
    cue.title = QStringLiteral(u"Amazing Grace");
    cue.section = QStringLiteral(u"WORSHIP SET");
    cue.sectionColor = QStringLiteral(u"#30d158");
    cue.meta = QStringLiteral(u"Full");
    cue.key = QStringLiteral(u"Key: G");
    cue.slideLabel = QStringLiteral(u"24 slides");
    cue.notes = QStringLiteral(u"Lead in after the welcome. Watch the congregation on the last chorus.");
    cue.chips = {
        { QStringLiteral(u"Intro"), QStringLiteral(u"#b8960b") },
        { QStringLiteral(u"Verse 1"), QStringLiteral(u"#0a64c8") },
        { QStringLiteral(u"Verse 2"), QStringLiteral(u"#0a64c8") },
        { QStringLiteral(u"Chorus"), QStringLiteral(u"#c8203f") },
        { QStringLiteral(u"Vamp"), QStringLiteral(u"#1f8f3f") },
        { QStringLiteral(u"Verse 3"), QStringLiteral(u"#0a64c8") },
        { QStringLiteral(u"Bridge"), QStringLiteral(u"#8a3fc8") },
        { QStringLiteral(u"Chorus"), QStringLiteral(u"#c8203f") },
        { QStringLiteral(u"Tag"), QStringLiteral(u"#d9472b") },
        { QStringLiteral(u"Outro"), QStringLiteral(u"#8c7a1c") },
        { QStringLiteral(u"Ending"), QStringLiteral(u"#a8861a") },
    };
    cue.slides = {
        { QStringLiteral(u"Intro"), QStringLiteral(u"#b8960b"), {} },
        { QStringLiteral(u"Verse 1"), QStringLiteral(u"#0a64c8"), QStringLiteral(u"AMAZING GRACE, HOW SWEET THE SOUND\nTHAT SAVED A WRETCH LIKE ME") },
        { QStringLiteral(u"Verse 1"), QStringLiteral(u"#0a64c8"), QStringLiteral(u"I ONCE WAS LOST, BUT NOW AM FOUND\nWAS BLIND, BUT NOW I SEE") },
        { QStringLiteral(u"Verse 2"), QStringLiteral(u"#0a64c8"), QStringLiteral(u"TWAS GRACE THAT TAUGHT MY HEART TO FEAR\nAND GRACE MY FEARS RELIEVED") },
        { QStringLiteral(u"Chorus"), QStringLiteral(u"#c8203f"), QStringLiteral(u"MY CHAINS ARE GONE, I'VE BEEN SET FREE") },
        { QStringLiteral(u"Chorus"), QStringLiteral(u"#c8203f"), QStringLiteral(u"MY GOD, MY SAVIOR HAS RANSOMED ME") },
        { QStringLiteral(u"Verse 3"), QStringLiteral(u"#0a64c8"), QStringLiteral(u"THE LORD HAS PROMISED GOOD TO ME\nHIS WORD MY HOPE SECURES") },
        { QStringLiteral(u"Verse 3"), QStringLiteral(u"#0a64c8"), QStringLiteral(u"HE WILL MY SHIELD AND PORTION BE") },
        { QStringLiteral(u"Bridge"), QStringLiteral(u"#8a3fc8"), QStringLiteral(u"WHEN WE'VE BEEN THERE TEN THOUSAND YEARS") },
    };
    return cue;
}

Cue lyricCue(const QString& title, const QString& section, const QString& note,
             const QString& key, const QStringList& lines)
{
    Cue cue;
    cue.title = title;
    cue.section = section;
    cue.sectionColor = QStringLiteral(u"#30d158");
    cue.meta = note;
    cue.key = key;
    cue.slideLabel = QStringLiteral(u"%1 slides").arg(lines.size());
    cue.notes = QStringLiteral(u"Prepared for the service flow.");
    for (qsizetype i = 0; i < lines.size(); ++i)
        cue.slides.append({ QStringLiteral(u"Verse %1").arg(i + 1), QStringLiteral(u"#0a64c8"), lines[i] });
    return cue;
}

} // namespace

Document::Document()
{
    settings = QJsonObject{
        { QStringLiteral(u"mainOutput"), QStringLiteral(u"Display 2 (1920 × 1080)") },
        { QStringLiteral(u"stageDisplay"), QStringLiteral(u"Display 3") },
        { QStringLiteral(u"confidenceMonitor"), true },
        { QStringLiteral(u"alwaysOnTop"), true },
        { QStringLiteral(u"ndiOutput"), true },
        { QStringLiteral(u"decklinkOutput"), false },
        { QStringLiteral(u"keyOutput"), false },
        { QStringLiteral(u"gpuAcceleration"), true },
        { QStringLiteral(u"frameRate"), QStringLiteral(u"60 fps") },
        { QStringLiteral(u"showChords"), true },
        { QStringLiteral(u"showClock"), true },
        { QStringLiteral(u"showSectionTimer"), true },
    };
}

Document Document::demo()
{
    Document doc;
    doc.sections = {
        { QStringLiteral(u"PRE-SERVICE"), QStringLiteral(u"#ffd60a") },
        { QStringLiteral(u"WORSHIP SET"), QStringLiteral(u"#30d158") },
        { QStringLiteral(u"WELCOME + TRANSITION"), QStringLiteral(u"#30d158") },
        { QStringLiteral(u"MESSAGE"), QStringLiteral(u"#30d158") },
        { QStringLiteral(u"CLOSING CALL TO ACTION"), QStringLiteral(u"#bf5af2") },
        { QStringLiteral(u"POST-SERVICE"), QStringLiteral(u"#ff375f") },
    };
    doc.items = {
        { QStringLiteral(u"Pre-roll"), 0, {}, {} },
        { QStringLiteral(u"Amazing Grace"), 1, QStringLiteral(u"Full"), {} },
        { QStringLiteral(u"How Great Thou Art"), 1, QStringLiteral(u"Full"), {} },
        { QStringLiteral(u"Great Is Thy Faithfulness"), 1, QStringLiteral(u"Full"), {} },
        { QStringLiteral(u"Announcements"), 2, {}, {} },
        { QStringLiteral(u"Social Break"), 2, {}, {} },
        { QStringLiteral(u"Sermon"), 3, {}, {} },
        { QStringLiteral(u"Be Thou My Vision"), 4, {}, {} },
        { QStringLiteral(u"Holy, Holy, Holy"), 4, {}, {} },
        { QStringLiteral(u"Give Us 5"), 4, {}, {} },
        { QStringLiteral(u"Post Service"), 5, {}, {} },
    };
    doc.cues = {
        preRollCue(),
        worshipCue(),
        lyricCue(QStringLiteral(u"How Great Thou Art"), QStringLiteral(u"WORSHIP SET"),
                 QStringLiteral(u"Full"), QStringLiteral(u"Key: C"), {
                     QStringLiteral(u"O LORD MY GOD, WHEN I IN AWESOME WONDER"),
                     QStringLiteral(u"THEN MY SAVIOR'S LOVE I SEE"),
                     QStringLiteral(u"HOW GREAT THOU ART"),
                 }),
        lyricCue(QStringLiteral(u"Sermon"), QStringLiteral(u"MESSAGE"),
                 QStringLiteral(u"Message"), {}, {
                     QStringLiteral(u"WELCOME TO THE WORD"),
                     QStringLiteral(u"JOHN 3:16"),
                 }),
    };
    doc.media = {
        { QStringLiteral(u"Welcome loop"), QStringLiteral(u"Media"), QStringLiteral(u"Drive"), QStringLiteral(u"Video"), QStringLiteral(u"1920 x 1080"), QStringLiteral(u"18.2 MB"), QStringLiteral(u"#3b2d8f"), QStringLiteral(u"#111111") },
        { QStringLiteral(u"Prayer night"), QStringLiteral(u"Media"), QStringLiteral(u"Drive"), QStringLiteral(u"Image"), QStringLiteral(u"1920 x 1080"), QStringLiteral(u"2.4 MB"), QStringLiteral(u"#8f2d4a"), QStringLiteral(u"#111111") },
        { QStringLiteral(u"Kids night"), QStringLiteral(u"Media"), QStringLiteral(u"Drive"), QStringLiteral(u"Image"), QStringLiteral(u"1920 x 1080"), QStringLiteral(u"3.1 MB"), QStringLiteral(u"#1f6f5f"), QStringLiteral(u"#111111") },
        { QStringLiteral(u"Offering"), QStringLiteral(u"Media"), QStringLiteral(u"Bold Blocks"), QStringLiteral(u"Image"), QStringLiteral(u"1920 x 1080"), QStringLiteral(u"1.8 MB"), QStringLiteral(u"#8a5a14"), QStringLiteral(u"#111111") },
        { QStringLiteral(u"Easter"), QStringLiteral(u"Media"), QStringLiteral(u"Bold Blocks"), QStringLiteral(u"Video"), QStringLiteral(u"3840 x 2160"), QStringLiteral(u"42.6 MB"), QStringLiteral(u"#2d5a8f"), QStringLiteral(u"#111111") },
        { QStringLiteral(u"Sermon title"), QStringLiteral(u"Media"), QStringLiteral(u"Side Thirds"), QStringLiteral(u"Image"), QStringLiteral(u"1920 x 1080"), QStringLiteral(u"2.0 MB"), QStringLiteral(u"#5a2d8f"), QStringLiteral(u"#111111") },
        { QStringLiteral(u"Countdown"), QStringLiteral(u"Media"), QStringLiteral(u"Side Thirds"), QStringLiteral(u"Video"), QStringLiteral(u"1920 x 1080"), QStringLiteral(u"9.7 MB"), QStringLiteral(u"#2d8f4a"), QStringLiteral(u"#111111") },
        { QStringLiteral(u"Thank you"), QStringLiteral(u"Media"), QStringLiteral(u"Imported"), QStringLiteral(u"Image"), QStringLiteral(u"1920 x 1080"), QStringLiteral(u"1.2 MB"), QStringLiteral(u"#8f6f2d"), QStringLiteral(u"#111111") },
        { QStringLiteral(u"Call to Action"), QStringLiteral(u"Overlays"), QStringLiteral(u"Side Thirds"), QStringLiteral(u"Overlay"), QStringLiteral(u"1920 x 1080"), {}, QStringLiteral(u"#ffd60a"), QStringLiteral(u"#2a2a2e") },
        { QStringLiteral(u"Point (Side Third)"), QStringLiteral(u"Overlays"), QStringLiteral(u"Side Thirds"), QStringLiteral(u"Overlay"), QStringLiteral(u"1920 x 1080"), {}, QStringLiteral(u"#0a84ff"), QStringLiteral(u"#2a2a2e") },
        { QStringLiteral(u"Verse + Reference"), QStringLiteral(u"Overlays"), QStringLiteral(u"Side Thirds"), QStringLiteral(u"Overlay"), QStringLiteral(u"1920 x 1080"), {}, QStringLiteral(u"#bf5af2"), QStringLiteral(u"#2a2a2e") },
    };
    return doc;
}

Document Document::fromJson(const QByteArray& json, QString* error)
{
    QJsonParseError parseError;
    const QJsonDocument parsed = QJsonDocument::fromJson(json, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        if (error) *error = parseError.errorString();
        return demo();
    }
    const QJsonObject root = parsed.object();
    Document doc;
    doc.schemaVersion = root.value(QStringLiteral(u"schemaVersion")).toInt(161);
    doc.name = root.value(QStringLiteral(u"name")).toString(doc.name);
    doc.date = root.value(QStringLiteral(u"date")).toString(doc.date);
    doc.serviceTime = root.value(QStringLiteral(u"serviceTime")).toString(doc.serviceTime);
    doc.sections = sectionsFromJson(root.value(QStringLiteral(u"sections")).toArray());
    doc.items = itemsFromJson(root.value(QStringLiteral(u"items")).toArray());
    doc.cues = cuesFromJson(root.value(QStringLiteral(u"cues")).toArray());
    doc.media = mediaFromJson(root.value(QStringLiteral(u"media")).toArray());
    const QJsonObject settings = root.value(QStringLiteral(u"settings")).toObject();
    for (auto it = settings.constBegin(); it != settings.constEnd(); ++it)
        doc.settings.insert(it.key(), QJsonValue::fromVariant(it.value().toVariant()));
    if (doc.cues.isEmpty())
        return demo();
    return doc;
}

QByteArray Document::toJson() const
{
    QJsonObject root;
    root.insert(QStringLiteral(u"schemaVersion"), schemaVersion);
    root.insert(QStringLiteral(u"name"), name);
    root.insert(QStringLiteral(u"date"), date);
    root.insert(QStringLiteral(u"serviceTime"), serviceTime);
    root.insert(QStringLiteral(u"sections"), sectionsToJson(sections));
    root.insert(QStringLiteral(u"items"), itemsToJson(items));
    root.insert(QStringLiteral(u"cues"), cuesToJson(cues));
    root.insert(QStringLiteral(u"media"), mediaToJson(media));
    root.insert(QStringLiteral(u"settings"), QJsonObject::fromVariantMap(settings.toVariantMap()));
    return QJsonDocument(root).toJson(QJsonDocument::Indented);
}

bool Document::load(const QString& path, QString* error)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        if (error) *error = file.errorString();
        return false;
    }
    *this = fromJson(file.readAll(), error);
    return true;
}

bool Document::save(const QString& path, QString* error) const
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        if (error) *error = file.errorString();
        return false;
    }
    file.write(toJson());
    return true;
}

} // namespace mxu::core
