#pragma once

#include "core/Document.h"

#include <QHash>
#include <QObject>
#include <QVideoFrame>
#include <QVideoSink>
#include <QString>
#include <QVariantList>

namespace mxu::app {

// Imports media files into the document, generates thumbnails and exposes
// the result to the Library screen. Video thumbnails fall back to a painted
// placeholder until an FFmpeg frame grabber is wired in.
class MediaService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList items READ items NOTIFY changed)
    Q_PROPERTY(QString status READ status NOTIFY changed)
    Q_PROPERTY(QString backgroundUrl READ backgroundUrl NOTIFY changed)

public:
    explicit MediaService(QObject* parent = nullptr);
    void setDocument(core::Document* document);

    QVariantList items() const;
    QString status() const { return m_status; }
    QString backgroundUrl() const;

public slots:
    QString importFile(const QString& path);
    int importFolder(const QString& path);
    bool setBackground(const QString& id);
    bool addToServiceFlow(const QString& id);
    bool removeMedia(int index);

signals:
    void changed();
    void statusChanged();
    void notification(const QString& message);
    void mediaAddedToFlow(const QString& name);

private:
    QString thumbnailFor(const QString& id, const QString& path, bool isVideo);
    bool grabVideoFrame(const QString& path, const QString& target);
    void refresh();

    core::Document* m_document = nullptr;
    QVariantList m_items;
    QHash<QString, QString> m_thumbnails;
    QHash<QString, QString> m_paths;
    QString m_background;
    QString m_status = QStringLiteral(u"Ready");
};

} // namespace mxu::app
