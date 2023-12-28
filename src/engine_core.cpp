#include "engine_core.h"
#include <fmt/core.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1500 && _MSC_VER < 1900)
/* msvc兼容utf-8: https://support.microsoft.com/en-us/kb/980263 */
#if (_MSC_VER >= 1700)
#pragma execution_character_set("utf-8")
#endif
#pragma warning(disable : 4566)
#endif

namespace agift
{
    EngineCore::EngineCore(std::string platform, std::string backend)
        : platform(platform), backend(backend)
    {
        fmt::print("{} {} {} {}\n", getName(), getPlatform(), getBackend(), size_t(this));
    }

    EngineCore::~EngineCore()
    {
        fmt::print("{} {} {} {}\n", getName(), getPlatform(), getBackend(), size_t(this));
    }
}
