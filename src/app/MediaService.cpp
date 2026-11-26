#include "MediaService.h"
#include "ImportLedgerService.h"

#include <QDir>
#include <QFileInfo>
#include <QImage>
#include <QImageReader>
#include <QMediaPlayer>
#include <QTimer>
#include <QVideoSink>
#include <QEventLoop>
#include <QPainter>
#include <QStandardPaths>
#include <QUrl>
#include <QUuid>

namespace mxu::app {

MediaService::MediaService(QObject* parent)
    : QObject(parent)
{
}

QString MediaService::backgroundUrl() const
{
    const QString path = m_paths.value(m_background);
    return path.isEmpty() ? QString() : QUrl::fromLocalFile(path).toString();
}

QVariantList MediaService::items() const
{
    return m_items;
}

void MediaService::setDocument(core::Document* document)
{
    m_document = document;
    refresh();
}

QString MediaService::thumbnailFor(const QString& id, const QString& path, bool isVideo)
{
    const QString dirPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
                            + QStringLiteral(u"/thumbs");
    QDir().mkpath(dirPath);
    const QString target = dirPath + QStringLiteral(u"/") + id + QStringLiteral(u".png");

    if (isVideo && grabVideoFrame(path, target)) {
        m_status = QStringLiteral(u"Video frame captured");
        return QUrl::fromLocalFile(target).toString();
    }

    if (!isVideo) {
        QImageReader reader(path);
        reader.setScaledSize(QSize(320, 180));
        const QImage image = reader.read();
        if (!image.isNull() && image.save(target)) {
            m_status = QStringLiteral(u"Thumbnail generated");
            return QUrl::fromLocalFile(target).toString();
        }
    }

    QImage image(320, 180, QImage::Format_ARGB32);
    image.fill(QColor(QStringLiteral(u"#1b1b20")));
    QPainter painter(&image);
    const QColor from(QStringLiteral(u"#3b2d8f"));
    const QColor to(QStringLiteral(u"#0b0b0c"));
    for (int x = 0; x < image.width(); ++x) {
        const qreal t = static_cast<qreal>(x) / image.width();
        painter.fillRect(x, 0, 1, image.height(),
                         QColor::fromRgb(qRound(from.red() + (to.red() - from.red()) * t),
                                         qRound(from.green() + (to.green() - from.green()) * t),
                                         qRound(from.blue() + (to.blue() - from.blue()) * t)));
    }
    painter.setPen(Qt::white);
    painter.setFont(QFont(QStringLiteral(u"Segoe UI"), 16, QFont::Bold));
    painter.drawText(image.rect(), Qt::AlignCenter, isVideo ? QStringLiteral(u"VIDEO") : QString());
    painter.end();
    image.save(target);
    m_status = isVideo ? QStringLiteral(u"Video placeholder — frame grab pending")
                       : QStringLiteral(u"Thumbnail unavailable");
    return QUrl::fromLocalFile(target).toString();
}


bool MediaService::grabVideoFrame(const QString& path, const QString& target)
{
    QMediaPlayer player;
    QVideoSink sink;
    player.setVideoSink(&sink);
    QEventLoop loop;
    QTimer timeout;
    timeout.setSingleShot(true);
    timeout.setInterval(3000);
    QImage frame;
    QObject::connect(&sink, &QVideoSink::videoFrameChanged, &loop, [&](const QVideoFrame& videoFrame) {
        if (!videoFrame.isValid())
            return;
        frame = videoFrame.toImage();
        loop.quit();
    });
    QObject::connect(&timeout, &QTimer::timeout, &loop, [&loop]() { loop.quit(); });
    player.setSource(QUrl::fromLocalFile(path));
    timeout.start();
    player.play();
    loop.exec();
    player.stop();
    if (frame.isNull())
        return false;
    return frame.scaled(320, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation).save(target);
}

QString MediaService::importFile(const QString& path)
{
    if (!m_document || path.isEmpty())
        return {};
    const QFileInfo info(path);
    if (!info.exists())
        return {};
    const QString suffix = info.suffix().toLower();
    const bool isVideo = suffix == QStringLiteral(u"mp4") || suffix == QStringLiteral(u"mov")
                         || suffix == QStringLiteral(u"mkv") || suffix == QStringLiteral(u"webm");
    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    const QString thumb = thumbnailFor(id, path, isVideo);
    m_thumbnails.insert(id, thumb);
    m_paths.insert(id, path);

    core::MediaItem item;
    item.name = info.completeBaseName();
    item.category = QStringLiteral(u"Media");
    item.folder = QStringLiteral(u"Imported");
    item.type = isVideo ? QStringLiteral(u"Video") : QStringLiteral(u"Image");
    item.fileSize = QStringLiteral(u"%1 MB").arg(info.size() / (1024 * 1024), 1, 'f', 1);
    item.from = isVideo ? QStringLiteral(u"#2d5a8f") : QStringLiteral(u"#8f2d4a");
    item.to = QStringLiteral(u"#111111");
    m_document->media.append(item);

    if (m_ledger)
        m_ledger->record(path);
    m_status = QStringLiteral(u"Imported %1").arg(item.name);
    emit statusChanged();
    emit notification(m_status);
    refresh();
    return id;
}

int MediaService::importFolder(const QString& path)
{
    int count = 0;
    const QDir dir(path);
    const QStringList files = dir.entryList({ QStringLiteral(u"*.png"), QStringLiteral(u"*.jpg"),
                                              QStringLiteral(u"*.jpeg"), QStringLiteral(u"*.mp4"),
                                              QStringLiteral(u"*.mov") }, QDir::Files);
    for (const QString& file : files) {
        if (!importFile(dir.filePath(file)).isEmpty())
            ++count;
    }
    return count;
}

bool MediaService::setBackground(const QString& id)
{
    if (!m_document || id.isEmpty())
        return false;
    for (qsizetype i = 0; i < m_document->media.size(); ++i) {
        if (m_document->media[i].name != id && QString::number(i) != id)
            continue;
        m_background = QString::number(i);
        emit changed();
        emit notification(QStringLiteral(u"Background set to %1").arg(id));
        return true;
    }
    return false;
}

bool MediaService::addToServiceFlow(const QString& id)
{
    if (!m_document || id.isEmpty())
        return false;
    m_document->items.append({ id, 0, {}, {} });
    refresh();
    emit mediaAddedToFlow(id);
    emit notification(QStringLiteral(u"Added %1 to Service Flow").arg(id));
    return true;
}

bool MediaService::removeMedia(int index)
{
    if (!m_document || index < 0 || index >= m_document->media.size())
        return false;
    const QString name = m_document->media[index].name;
    m_document->media.removeAt(index);
    m_thumbnails.remove(QString::number(index));
    m_paths.remove(QString::number(index));
    refresh();
    emit notification(QStringLiteral(u"Removed %1").arg(name));
    return true;
}

void MediaService::refresh()
{
    m_items.clear();
    if (!m_document)
        return;
    for (qsizetype i = 0; i < m_document->media.size(); ++i) {
        const auto& item = m_document->media[i];
        m_items.append(QVariantMap{
            { QStringLiteral(u"id"), QString::number(i) },
            { QStringLiteral(u"thumbnail"), m_thumbnails.value(QString::number(i)) },
            { QStringLiteral(u"name"), item.name },
            { QStringLiteral(u"category"), item.category },
            { QStringLiteral(u"folder"), item.folder },
            { QStringLiteral(u"type"), item.type },
            { QStringLiteral(u"size"), item.size },
            { QStringLiteral(u"fileSize"), item.fileSize },
            { QStringLiteral(u"from"), item.from },
            { QStringLiteral(u"to"), item.to },
            { QStringLiteral(u"index"), static_cast<int>(i) },
        });
    }
    emit changed();
}

} // namespace mxu::app
