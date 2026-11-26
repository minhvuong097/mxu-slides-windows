#pragma once

#include <QObject>
#include <QString>
#include <QVariantList>

namespace mxu::app {

// Minimal PPTX text importer: expands the archive with the OS unzip helper
// and extracts <a:t> runs from ppt/slides/slideN.xml.
class PptxImporter : public QObject
{
    Q_OBJECT

public:
    explicit PptxImporter(QObject* parent = nullptr);

    Q_INVOKABLE QVariantList import(const QString& path);
    Q_INVOKABLE QString lastError() const { return m_error; }

private:
    bool expand(const QString& archive, const QString& target);
    QString m_error;
};

} // namespace mxu::app
