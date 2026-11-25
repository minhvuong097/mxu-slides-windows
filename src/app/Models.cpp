#include "Models.h"

namespace mxu::app {

// ---------------------------------------------------------------- Service
ServiceModel::ServiceModel(QObject* parent)
    : QObject(parent)
{
}

void ServiceModel::setDocument(core::Document* document)
{
    m_document = document;
    m_current = 0;
    emit dataChanged();
    emit currentChanged();
    emit metaChanged();
}

QVariantList ServiceModel::sections() const
{
    QVariantList result;
    if (!m_document)
        return result;

    for (qsizetype s = 0; s < m_document->sections.size(); ++s) {
        QVariantList children;
        for (qsizetype i = 0; i < m_document->items.size(); ++i) {
            const auto& item = m_document->items[i];
            if (item.section != s)
                continue;
            children.append(QVariantMap{
                { QStringLiteral(u"name"), item.name },
                { QStringLiteral(u"note"), item.note },
                { QStringLiteral(u"index"), static_cast<int>(i) },
                { QStringLiteral(u"selected"), static_cast<int>(i) == m_current },
            });
        }
        if (children.isEmpty())
            continue;
        result.append(QVariantMap{
            { QStringLiteral(u"name"), m_document->sections[s].name },
            { QStringLiteral(u"color"), m_document->sections[s].color },
            { QStringLiteral(u"items"), children },
        });
    }
    return result;
}

int ServiceModel::itemCount() const
{
    return m_document ? m_document->items.size() : 0;
}

QVariantMap ServiceModel::currentItem() const
{
    if (!m_document || m_current < 0 || m_current >= m_document->items.size())
        return {};
    const auto& item = m_document->items[m_current];
    return {
        { QStringLiteral(u"name"), item.name },
        { QStringLiteral(u"note"), item.note },
        { QStringLiteral(u"index"), m_current },
    };
}

QString ServiceModel::serviceName() const { return m_document ? m_document->name : QString(); }
QString ServiceModel::serviceDate() const { return m_document ? m_document->date : QString(); }
QString ServiceModel::serviceTime() const { return m_document ? m_document->serviceTime : QString(); }
int ServiceModel::serviceTimeBadge() const { return 2; }

void ServiceModel::selectItem(int index)
{
    if (!m_document || index < 0 || index >= m_document->items.size() || index == m_current)
        return;
    m_current = index;
    emit currentChanged();
    emit dataChanged();
}

void ServiceModel::nextItem()
{
    if (itemCount() > 0)
        selectItem((m_current + 1) % itemCount());
}

void ServiceModel::previousItem()
{
    if (itemCount() > 0)
        selectItem((m_current - 1 + itemCount()) % itemCount());
}

bool ServiceModel::addItem(const QString& name, int section)
{
    if (!m_document || name.trimmed().isEmpty() || section < 0 || section >= m_document->sections.size())
        return false;
    m_document->items.append({ name.trimmed(), section, {}, {} });
    emit dataChanged();
    return true;
}

bool ServiceModel::removeItem(int index)
{
    if (!m_document || index < 0 || index >= m_document->items.size())
        return false;
    m_document->items.removeAt(index);
    if (m_current >= itemCount())
        m_current = qMax(0, itemCount() - 1);
    emit dataChanged();
    emit currentChanged();
    return true;
}

// -------------------------------------------------------------------- Cue
CueModel::CueModel(QObject* parent)
    : QObject(parent)
{
}

void CueModel::setDocument(core::Document* document)
{
    m_document = document;
    m_cue = 0;
    m_slide = 0;
    emit dataChanged();
    emit currentChanged();
}

int CueModel::cueCount() const
{
    return m_document ? m_document->cues.size() : 0;
}

QVariantMap CueModel::cueToMap(const core::Cue& cue, int index) const
{
    QVariantList chips;
    for (const auto& chip : cue.chips)
        chips.append(QVariantMap{ { QStringLiteral(u"name"), chip.name },
                                  { QStringLiteral(u"color"), chip.color } });

    QVariantList slides;
    for (qsizetype i = 0; i < cue.slides.size(); ++i) {
        const auto& slide = cue.slides[i];
        slides.append(QVariantMap{
            { QStringLiteral(u"tag"), slide.tag },
            { QStringLiteral(u"tagColor"), slide.tagColor },
            { QStringLiteral(u"text"), slide.text },
            { QStringLiteral(u"index"), static_cast<int>(i) },
            { QStringLiteral(u"selected"), m_cue == index && static_cast<int>(i) == m_slide },
        });
    }

    QVariantList posters;
    for (const auto& poster : cue.posters)
        posters.append(QVariantMap{ { QStringLiteral(u"title"), poster.title },
                                    { QStringLiteral(u"caption"), poster.caption },
                                    { QStringLiteral(u"from"), poster.from },
                                    { QStringLiteral(u"to"), poster.to } });

    return {
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
        { QStringLiteral(u"index"), index },
        { QStringLiteral(u"selected"), index == m_cue },
    };
}

QVariantList CueModel::cues() const
{
    QVariantList result;
    if (!m_document)
        return result;
    for (qsizetype i = 0; i < m_document->cues.size(); ++i)
        result.append(cueToMap(m_document->cues[i], static_cast<int>(i)));
    return result;
}

QVariantMap CueModel::currentCue() const
{
    if (!m_document || m_cue < 0 || m_cue >= m_document->cues.size())
        return {};
    return cueToMap(m_document->cues[m_cue], m_cue);
}

QVariantMap CueModel::currentSlide() const
{
    const QVariantMap cue = currentCue();
    const QVariantList slides = cue.value(QStringLiteral(u"slides")).toList();
    if (m_slide < 0 || m_slide >= slides.size())
        return {};
    return slides.at(m_slide).toMap();
}

void CueModel::selectCue(int index)
{
    if (!m_document || index < 0 || index >= m_document->cues.size() || index == m_cue)
        return;
    m_cue = index;
    m_slide = 0;
    emit currentChanged();
    emit dataChanged();
}

void CueModel::selectSlide(int index)
{
    if (!m_document || m_cue < 0 || m_cue >= m_document->cues.size())
        return;
    const int count = m_document->cues[m_cue].slides.size();
    if (index < 0 || index >= count || index == m_slide)
        return;
    m_slide = index;
    emit currentChanged();
    emit dataChanged();
}

void CueModel::nextSlide()
{
    if (!m_document || m_cue < 0 || m_cue >= m_document->cues.size())
        return;
    const int count = m_document->cues[m_cue].slides.size();
    if (count > 0)
        selectSlide((m_slide + 1) % count);
}

void CueModel::previousSlide()
{
    if (!m_document || m_cue < 0 || m_cue >= m_document->cues.size())
        return;
    const int count = m_document->cues[m_cue].slides.size();
    if (count > 0)
        selectSlide((m_slide - 1 + count) % count);
}

// --------------------------------------------------------------- Library
LibraryModel::LibraryModel(QObject* parent)
    : QObject(parent)
{
}

void LibraryModel::setDocument(core::Document* document)
{
    m_document = document;
    m_selected = 1;
    emit dataChanged();
    emit selectedChanged();
}

QStringList LibraryModel::categories() const
{
    return { QStringLiteral(u"Slides"), QStringLiteral(u"Media"), QStringLiteral(u"Overlays"),
             QStringLiteral(u"Songs"), QStringLiteral(u"Backgrounds") };
}

QVariantList LibraryModel::folders() const
{
    return { QStringLiteral(u"Drive"), QStringLiteral(u"Bold Blocks"),
             QStringLiteral(u"Side Thirds"), QStringLiteral(u"Imported") };
}

bool LibraryModel::matches(const core::MediaItem& item) const
{
    if (!m_category.isEmpty() && item.category != m_category)
        return false;
    if (m_search.trimmed().isEmpty())
        return true;
    return item.name.contains(m_search.trimmed(), Qt::CaseInsensitive)
        || item.folder.contains(m_search.trimmed(), Qt::CaseInsensitive);
}

QVariantList LibraryModel::items() const
{
    QVariantList result;
    if (!m_document)
        return result;
    for (qsizetype i = 0; i < m_document->media.size(); ++i) {
        const auto& item = m_document->media[i];
        if (!matches(item))
            continue;
        result.append(QVariantMap{
            { QStringLiteral(u"name"), item.name },
            { QStringLiteral(u"folder"), item.folder },
            { QStringLiteral(u"type"), item.type },
            { QStringLiteral(u"size"), item.size },
            { QStringLiteral(u"fileSize"), item.fileSize },
            { QStringLiteral(u"from"), item.from },
            { QStringLiteral(u"to"), item.to },
            { QStringLiteral(u"index"), static_cast<int>(i) },
            { QStringLiteral(u"selected"), static_cast<int>(i) == m_selected },
        });
    }
    return result;
}

QVariantMap LibraryModel::selectedItem() const
{
    if (!m_document || m_selected < 0 || m_selected >= m_document->media.size())
        return {};
    const auto& item = m_document->media[m_selected];
    return {
        { QStringLiteral(u"name"), item.name },
        { QStringLiteral(u"type"), item.type },
        { QStringLiteral(u"size"), item.size },
        { QStringLiteral(u"fileSize"), item.fileSize },
        { QStringLiteral(u"from"), item.from },
        { QStringLiteral(u"to"), item.to },
    };
}

void LibraryModel::setCategory(const QString& value)
{
    if (m_category == value)
        return;
    m_category = value;
    emit categoryChanged();
    emit dataChanged();
}

void LibraryModel::setSearch(const QString& value)
{
    if (m_search == value)
        return;
    m_search = value;
    emit searchChanged();
    emit dataChanged();
}

void LibraryModel::selectItem(int index)
{
    if (!m_document || index < 0 || index >= m_document->media.size() || index == m_selected)
        return;
    m_selected = index;
    emit selectedChanged();
    emit dataChanged();
}

void LibraryModel::addToServiceFlow(int index)
{
    if (!m_document || index < 0 || index >= m_document->media.size())
        return;
    emit notification(QStringLiteral(u"Added %1 to Service Flow").arg(m_document->media[index].name));
}

void LibraryModel::setAsBackground(int index)
{
    if (!m_document || index < 0 || index >= m_document->media.size())
        return;
    emit notification(QStringLiteral(u"Background set to %1").arg(m_document->media[index].name));
}

} // namespace mxu::app
