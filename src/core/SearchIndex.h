#pragma once

#include "Document.h"
#include "ShowDocument.h"

#include <QObject>
#include <QSqlDatabase>
#include <QString>
#include <QVariantList>

namespace mxu::core {

// SQLite FTS5 index over slides, notes and media, equivalent to the macOS
// LibraryIndex. Falls back to a linear scan when FTS5 is unavailable.
class SearchIndex : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int indexedCount READ indexedCount NOTIFY changed)
    Q_PROPERTY(QString backend READ backend CONSTANT)

public:
    explicit SearchIndex(QObject* parent = nullptr);
    ~SearchIndex() override;

    int indexedCount() const { return m_count; }
    QString backend() const { return m_backend; }

    void rebuild(const Document& document, const ShowDocument& show);
    Q_INVOKABLE QVariantList search(const QString& query) const;

signals:
    void changed();

private:
    QSqlDatabase m_database;
    QString m_backend;
    QVariantList m_rows;
    int m_count = 0;
    QString m_connection;
};

} // namespace mxu::core
