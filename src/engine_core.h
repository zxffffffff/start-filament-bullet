#pragma once
#include <string>
#include <cassert>

#if defined(_MSC_VER) && (_MSC_VER >= 1500 && _MSC_VER < 1900)
/* msvc兼容utf-8: https://support.microsoft.com/en-us/kb/980263 */
#if (_MSC_VER >= 1700)
#pragma execution_character_set("utf-8")
#endif
#pragma warning(disable : 4566)
#endif

namespace agift
{
    class EngineCore
    {
    protected:
        const std::string platform;
        const std::string backend;

    public:
        EngineCore(std::string platform = "", std::string backend = "");
        virtual ~EngineCore();

        const std::string &getPlatform() const { return platform; }
        const std::string &getBackend() const { return backend; }

        virtual std::string getName() const { return "EngineCore"; }

        virtual void init() {}
        virtual void cleanup() {}

        virtual void setScene(std::string scene) { assert(false); }
        virtual void cleanupScene() { assert(false); }

        virtual void addNativeView(void *native_view) { assert(false); }
        virtual void removeNativeView(void *native_view) { assert(false); }
        virtual bool checkNativeView(void *native_view) { return false; }

        virtual void resize(int width, int height) { assert(false); }
        virtual void render() { assert(false); }
    };
}
