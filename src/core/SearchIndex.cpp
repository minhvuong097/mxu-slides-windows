#include "SearchIndex.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QUuid>

namespace mxu::core {

SearchIndex::SearchIndex(QObject* parent)
    : QObject(parent)
{
    m_connection = QUuid::createUuid().toString(QUuid::WithoutBraces);
    m_database = QSqlDatabase::addDatabase(QStringLiteral(u"QSQLITE"), m_connection);
    m_database.setDatabaseName(QStringLiteral(u":memory:"));
    if (m_database.open()) {
        QSqlQuery query(m_database);
        if (query.exec(QStringLiteral(u"CREATE VIRTUAL TABLE search USING fts5(kind, ref, text)")))
            m_backend = QStringLiteral(u"SQLite FTS5");
        else
            m_backend = QStringLiteral(u"linear fallback");
    } else {
        m_backend = QStringLiteral(u"linear fallback");
    }
}

SearchIndex::~SearchIndex()
{
    const QString name = m_connection;
    m_database.close();
    QSqlDatabase::removeDatabase(name);
}

void SearchIndex::rebuild(const Document& document, const ShowDocument& show)
{
    m_rows.clear();
    auto add = [this](const QString& kind, const QString& ref, const QString& text) {
        if (text.trimmed().isEmpty())
            return;
        m_rows.append(QVariantMap{
            { QStringLiteral(u"kind"), kind },
            { QStringLiteral(u"ref"), ref },
            { QStringLiteral(u"text"), text },
        });
    };

    for (const auto& slide : show.document().slides) {
        QString text;
        for (const auto& object : slide.objects)
            text += object.text + QLatin1Char('\n');
        add(QStringLiteral(u"slide"), slide.name, text.trimmed());
    }
    for (const auto& cue : document.cues) {
        for (const auto& slide : cue.slides)
            add(QStringLiteral(u"cue"), cue.title, slide.text);
    }
    for (qsizetype i = 0; i < document.media.size(); ++i)
        add(QStringLiteral(u"media"), document.media[i].name, document.media[i].folder);

    const QJsonArray notes = document.notes.value(QStringLiteral(u"blocks")).toArray();
    for (const QJsonValue& value : notes)
        add(QStringLiteral(u"note"), QStringLiteral(u"Notes"),
            value.toObject().value(QStringLiteral(u"text")).toString());

    if (m_backend == QStringLiteral(u"SQLite FTS5")) {
        QSqlQuery clear(m_database);
        clear.exec(QStringLiteral(u"DELETE FROM search"));
        QSqlQuery insert(m_database);
        insert.prepare(QStringLiteral(u"INSERT INTO search(kind,ref,text) VALUES(?,?,?)"));
        for (const QVariant& row : m_rows) {
            const QVariantMap map = row.toMap();
            insert.addBindValue(map.value(QStringLiteral(u"kind")).toString());
            insert.addBindValue(map.value(QStringLiteral(u"ref")).toString());
            insert.addBindValue(map.value(QStringLiteral(u"text")).toString());
            insert.exec();
        }
    }
    m_count = m_rows.size();
    emit changed();
}

QVariantList SearchIndex::search(const QString& query) const
{
    if (query.trimmed().isEmpty())
        return {};
    QVariantList result;
    if (m_backend == QStringLiteral(u"SQLite FTS5")) {
        QSqlQuery sql(m_database);
        sql.prepare(QStringLiteral(u"SELECT kind,ref,text FROM search WHERE search MATCH ? LIMIT 40"));
        sql.addBindValue(query.trimmed());
        if (sql.exec()) {
            while (sql.next()) {
                result.append(QVariantMap{
                    { QStringLiteral(u"kind"), sql.value(0).toString() },
                    { QStringLiteral(u"ref"), sql.value(1).toString() },
                    { QStringLiteral(u"text"), sql.value(2).toString() },
                });
            }
            return result;
        }
    }
    for (const QVariant& row : m_rows) {
        const QVariantMap map = row.toMap();
        if (map.value(QStringLiteral(u"text")).toString().contains(query.trimmed(), Qt::CaseInsensitive)
            || map.value(QStringLiteral(u"ref")).toString().contains(query.trimmed(), Qt::CaseInsensitive))
            result.append(map);
    }
    return result;
}

} // namespace mxu::core
