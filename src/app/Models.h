#pragma once

#include "core/Document.h"

#include <QObject>
#include <QVariantList>
#include <QVariantMap>

namespace mxu::app {

// QML-facing projection of the service run-of-show.
class ServiceModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList sections READ sections NOTIFY dataChanged)
    Q_PROPERTY(int itemCount READ itemCount NOTIFY dataChanged)
    Q_PROPERTY(int currentItemIndex READ currentItemIndex NOTIFY currentChanged)
    Q_PROPERTY(QVariantMap currentItem READ currentItem NOTIFY currentChanged)
    Q_PROPERTY(QString serviceName READ serviceName NOTIFY metaChanged)
    Q_PROPERTY(QString serviceDate READ serviceDate NOTIFY metaChanged)
    Q_PROPERTY(QString serviceTime READ serviceTime NOTIFY metaChanged)
    Q_PROPERTY(int serviceTimeBadge READ serviceTimeBadge NOTIFY metaChanged)

public:
    explicit ServiceModel(QObject* parent = nullptr);
    void setDocument(core::Document* document);

    QVariantList sections() const;
    int itemCount() const;
    int currentItemIndex() const { return m_current; }
    QVariantMap currentItem() const;
    QString serviceName() const;
    QString serviceDate() const;
    QString serviceTime() const;
    int serviceTimeBadge() const;

public slots:
    void selectItem(int index);
    void nextItem();
    void previousItem();
    bool addItem(const QString& name, int section);
    bool removeItem(int index);

signals:
    void dataChanged();
    void currentChanged();
    void metaChanged();

private:
    core::Document* m_document = nullptr;
    int m_current = 0;
};

// QML-facing cue cards, grouping lyric slides and picture shows.
class CueModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList cues READ cues NOTIFY dataChanged)
    Q_PROPERTY(int cueCount READ cueCount NOTIFY dataChanged)
    Q_PROPERTY(int currentCueIndex READ currentCueIndex NOTIFY currentChanged)
    Q_PROPERTY(int currentSlideIndex READ currentSlideIndex NOTIFY currentChanged)
    Q_PROPERTY(QVariantMap currentCue READ currentCue NOTIFY currentChanged)
    Q_PROPERTY(QVariantMap currentSlide READ currentSlide NOTIFY currentChanged)

public:
    explicit CueModel(QObject* parent = nullptr);
    void setDocument(core::Document* document);

    QVariantList cues() const;
    int cueCount() const;
    int currentCueIndex() const { return m_cue; }
    int currentSlideIndex() const { return m_slide; }
    QVariantMap currentCue() const;
    QVariantMap currentSlide() const;

public slots:
    void selectCue(int index);
    void selectSlide(int index);
    void nextSlide();
    void previousSlide();

signals:
    void dataChanged();
    void currentChanged();

private:
    QVariantMap cueToMap(const core::Cue& cue, int index) const;
    core::Document* m_document = nullptr;
    int m_cue = 0;
    int m_slide = 0;
};

// QML-facing media library with category and text filtering.
class LibraryModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList items READ items NOTIFY dataChanged)
    Q_PROPERTY(QVariantList folders READ folders CONSTANT)
    Q_PROPERTY(QStringList categories READ categories CONSTANT)
    Q_PROPERTY(QString category READ category WRITE setCategory NOTIFY categoryChanged)
    Q_PROPERTY(QString search READ search WRITE setSearch NOTIFY searchChanged)
    Q_PROPERTY(int selectedIndex READ selectedIndex NOTIFY selectedChanged)
    Q_PROPERTY(QVariantMap selectedItem READ selectedItem NOTIFY selectedChanged)

public:
    explicit LibraryModel(QObject* parent = nullptr);
    void setDocument(core::Document* document);

    QVariantList items() const;
    QVariantList folders() const;
    QStringList categories() const;
    QString category() const { return m_category; }
    QString search() const { return m_search; }
    int selectedIndex() const { return m_selected; }
    QVariantMap selectedItem() const;

    void setCategory(const QString& value);
    void setSearch(const QString& value);

public slots:
    void selectItem(int index);
    void addToServiceFlow(int index);
    void setAsBackground(int index);

signals:
    void dataChanged();
    void categoryChanged();
    void searchChanged();
    void selectedChanged();
    void notification(const QString& message);

private:
    bool matches(const core::MediaItem& item) const;
    core::Document* m_document = nullptr;
    QString m_category = QStringLiteral(u"Media");
    QString m_search;
    int m_selected = 1;
};

} // namespace mxu::app
