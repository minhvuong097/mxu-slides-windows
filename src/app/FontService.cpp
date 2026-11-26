#include "FontService.h"

#include <QFontDatabase>

namespace mxu::app {

FontService::FontService(QObject* parent)
    : QObject(parent)
    , m_families(QFontDatabase::families())
{
}

} // namespace mxu::app
