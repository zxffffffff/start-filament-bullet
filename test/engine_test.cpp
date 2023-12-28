#include "gtest/gtest.h"
#include "engine_c.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1500 && _MSC_VER < 1900)
/* msvc兼容utf-8: https://support.microsoft.com/en-us/kb/980263 */
#if (_MSC_VER >= 1700)
#pragma execution_character_set("utf-8")
#endif
#pragma warning(disable : 4566)
#endif

TEST(Engine, success)
{
    void *engine = agift_Engine_new("macOS", "OpenGL");
    ASSERT_STREQ(agift_Engine_getLastError(), "");
    ASSERT_STREQ(agift_Engine_getName(engine), "EngineFilamentBullet");

    agift_Engine_delete(engine);
    ASSERT_STREQ(agift_Engine_getLastError(), "");
}

TEST(Engine, unknownPlatform)
{
    void *engine = agift_Engine_new("88888", "OpenGL");
    ASSERT_STRNE(agift_Engine_getLastError(), "");
    ASSERT_STREQ(agift_Engine_getName(engine), "EngineCore");

    agift_Engine_delete(engine);
    ASSERT_STREQ(agift_Engine_getLastError(), "");
}

TEST(Engine, unknownBackend)
{
    void *engine = agift_Engine_new("macOS", "88888");
    ASSERT_STRNE(agift_Engine_getLastError(), "");
    ASSERT_STREQ(agift_Engine_getName(engine), "EngineCore");

    agift_Engine_delete(engine);
    ASSERT_STREQ(agift_Engine_getLastError(), "");
}
