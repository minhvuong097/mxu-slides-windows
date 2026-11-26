#include "PptxImporter.h"

#include <QDir>
#include <QFile>
#include <QProcess>
#include <QTemporaryDir>
#include <QXmlStreamReader>
#include <QCollator>
#include <QGuiApplication>
#include <algorithm>

namespace mxu::app {

PptxImporter::PptxImporter(QObject* parent)
    : QObject(parent)
{
}

bool PptxImporter::expand(const QString& archive, const QString& target)
{
#ifdef Q_OS_WIN
    const QString program = QStringLiteral(u"powershell");
    const QStringList args = { QStringLiteral(u"-NoProfile"), QStringLiteral(u"-Command"),
                               QStringLiteral(u"Expand-Archive -LiteralPath '%1' -DestinationPath '%2' -Force")
                                   .arg(archive, target) };
#else
    const QString program = QStringLiteral(u"unzip");
    const QStringList args = { QStringLiteral(u"-q"), archive, QStringLiteral(u"-d"), target };
#endif
    QProcess process;
    process.start(program, args);
    if (!process.waitForStarted(3000)) {
        m_error = QStringLiteral(u"Cannot start archive extractor: ") + program;
        return false;
    }
    if (!process.waitForFinished(10000)) {
        m_error = QStringLiteral(u"Archive extraction timed out");
        return false;
    }
    if (process.exitCode() != 0) {
        m_error = QString::fromLocal8Bit(process.readAllStandardError());
        return false;
    }
    return true;
}

QVariantList PptxImporter::import(const QString& path)
{
    m_error.clear();
    QVariantList result;
    QTemporaryDir dir;
    if (!dir.isValid() || !expand(path, dir.path()))
        return result;

    const QDir slides(dir.path() + QStringLiteral(u"/ppt/slides"));
    QStringList files = slides.entryList({ QStringLiteral(u"slide*.xml") }, QDir::Files);
    QCollator collator;
    collator.setNumericMode(true);
    std::sort(files.begin(), files.end(), [&collator](const QString& a, const QString& b) {
        return collator.compare(a, b) < 0;
    });

    for (const QString& file : files) {
        QFile xml(slides.filePath(file));
        if (!xml.open(QIODevice::ReadOnly))
            continue;
        QXmlStreamReader reader(&xml);
        QStringList runs;
        while (!reader.atEnd()) {
            reader.readNext();
            if (reader.isStartElement() && reader.name() == QStringLiteral(u"t"))
                runs.append(reader.readElementText());
        }
        if (!runs.isEmpty())
            result.append(QVariantMap{
                { QStringLiteral(u"name"), file },
                { QStringLiteral(u"text"), runs.join(QLatin1Char('\n')) },
            });
    }
    if (result.isEmpty())
        m_error = QStringLiteral(u"No slide text found in PPTX");
    return result;
}

} // namespace mxu::app
