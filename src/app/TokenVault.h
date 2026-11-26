#pragma once

#include <QObject>
#include <QSettings>
#include <QString>

namespace mxu::app {

// Windows DPAPI-backed token vault with a QSettings fallback on other hosts.
class TokenVault : public QObject
{
    Q_OBJECT

public:
    explicit TokenVault(QObject* parent = nullptr);

    Q_INVOKABLE QString load(const QString& key);
    Q_INVOKABLE bool save(const QString& key, const QString& value);
    Q_INVOKABLE bool available() const;

private:
    QSettings m_store;
};

} // namespace mxu::app
