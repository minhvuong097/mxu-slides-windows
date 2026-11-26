#include "TokenVault.h"

#ifdef Q_OS_WIN
#include <windows.h>
#include <wincrypt.h>
#pragma comment(lib, "advapi32.lib")
#endif

namespace mxu::app {

TokenVault::TokenVault(QObject* parent)
    : QObject(parent)
{
}

bool TokenVault::available() const
{
#ifdef Q_OS_WIN
    return true;
#else
    return false;
#endif
}

QString TokenVault::load(const QString& key)
{
    const QByteArray stored = m_store.value(QStringLiteral(u"mxu/vault/") + key).toByteArray();
    if (stored.isEmpty())
        return {};
#ifdef Q_OS_WIN
    DATA_BLOB input;
    input.cbData = static_cast<DWORD>(stored.size());
    input.pbData = reinterpret_cast<BYTE*>(const_cast<char*>(stored.constData()));
    DATA_BLOB output{};
    if (CryptUnprotectData(&input, nullptr, nullptr, nullptr, nullptr, 0, &output)) {
        const QString value = QString::fromUtf8(reinterpret_cast<const char*>(output.pbData),
                                                static_cast<qsizetype>(output.cbData));
        LocalFree(output.pbData);
        return value;
    }
#endif
    return QString::fromUtf8(stored);
}

bool TokenVault::save(const QString& key, const QString& value)
{
    if (value.isEmpty())
        return false;
    QByteArray data = value.toUtf8();
#ifdef Q_OS_WIN
    DATA_BLOB input;
    input.cbData = static_cast<DWORD>(data.size());
    input.pbData = reinterpret_cast<BYTE*>(data.data());
    DATA_BLOB output{};
    if (!CryptProtectData(&input, nullptr, nullptr, nullptr, nullptr, 0, &output))
        return false;
    data = QByteArray(reinterpret_cast<const char*>(output.pbData),
                      static_cast<qsizetype>(output.cbData));
    LocalFree(output.pbData);
#endif
    m_store.setValue(QStringLiteral(u"mxu/vault/") + key, data);
    m_store.sync();
    return true;
}

} // namespace mxu::app
