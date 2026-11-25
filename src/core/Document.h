#pragma once

#include <QJsonObject>
#include <QString>
#include <QVector>

namespace mxu::core {

// Domain values mirroring the macOS MxU Slides document schema
// (packages/schema/documents.json, schemaVersion 161). The Windows port uses
// a compact JSON projection of the same concepts: service run-of-show, cues,
// slides, media and station settings.
struct ServiceSection
{
    QString name;
    QString color;
};

struct ServiceItem
{
    QString name;
    int section = 0;
    QString note;
    QString showId;
};

struct Chip
{
    QString name;
    QString color;
};

struct Slide
{
    QString tag;
    QString tagColor;
    QString text;
};

struct Poster
{
    QString title;
    QString caption;
    QString from;
    QString to;
};

struct Cue
{
    QString title;
    QString section;
    QString sectionColor;
    QString meta;
    QString key;
    QString slideLabel;
    QString description;
    QString notes;
    bool notesHighlighted = false;
    bool pictureShow = false;
    QVector<Chip> chips;
    QVector<Slide> slides;
    QVector<Poster> posters;
};

struct MediaItem
{
    QString name;
    QString category;
    QString folder;
    QString type;
    QString size;
    QString fileSize;
    QString from;
    QString to;
};

class Document
{
public:
    Document();

    static Document demo();
    static Document fromJson(const QByteArray& json, QString* error = nullptr);
    QByteArray toJson() const;

    bool load(const QString& path, QString* error = nullptr);
    bool save(const QString& path, QString* error = nullptr) const;

    QVector<ServiceSection> sections;
    QVector<ServiceItem> items;
    QVector<Cue> cues;
    QVector<MediaItem> media;
    QJsonObject settings;
    int schemaVersion = 161;
    QString name = QStringLiteral(u"Renew Worship");
    QString date = QStringLiteral(u"Nov 29, 2026");
    QString serviceTime = QStringLiteral(u"9:00 AM");
};

} // namespace mxu::core
