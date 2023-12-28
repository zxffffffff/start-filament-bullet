#include "engine_c.h"
#include "engine_core.h"
#include "engine_filament_bullet.h"
#include <iostream>
#include <cstring>
#include <set>

#if defined(_MSC_VER) && (_MSC_VER >= 1500 && _MSC_VER < 1900)
/* msvc兼容utf-8: https://support.microsoft.com/en-us/kb/980263 */
#if (_MSC_VER >= 1700)
#pragma execution_character_set("utf-8")
#endif
#pragma warning(disable : 4566)
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    static std::string last_error;
    static const std::set<const std::string> supported_platforms = {"Windows", "macOS", "iOS", "Android", "Web"};
    static const std::set<const std::string> supported_backends = {"Metal", "Vulkan", "OpenGL"};
    static const std::set<const std::string> supported_scenes = {"Test"};

    const char *agift_Engine_getLastError()
    {
        return last_error.c_str();
    }

    void *agift_Engine_new(const char *_platform, const char *_backend)
    {
        last_error.clear();
        std::string platform(_platform);
        std::string backend(_backend);

        agift::EngineCore *engine = 0;
        if (!supported_platforms.contains(platform))
        {
            engine = new agift::EngineCore();
            last_error = "Unknown platform: " + platform;
        }
        else if (!supported_backends.contains(backend))
        {
            engine = new agift::EngineCore();
            last_error = "Unknown backend: " + backend;
        }
        else
        {
            engine = new agift::EngineFilamentBullet(platform, backend);
        }
        engine->init();
        return engine;
    }

    void agift_Engine_delete(void *_engine)
    {
        last_error.clear();
        agift::EngineCore *engine = (agift::EngineCore *)_engine;
        if (!engine)
        {
            last_error = "Invalid engine pointer";
            return;
        }
        engine->cleanup();
        delete engine;
    }

    const char *agift_Engine_getName(void *_engine)
    {
        last_error.clear();
        agift::EngineCore *engine = (agift::EngineCore *)_engine;
        if (!engine)
        {
            last_error = "Invalid engine pointer";
            return "";
        }

        static std::string buf;
        buf = engine->getName();
        return buf.c_str();
    }

    void agift_Engine_setScene(void *_engine, const char *_scene)
    {
        last_error.clear();
        std::string scene(_scene);
        agift::EngineCore *engine = (agift::EngineCore *)_engine;
        if (!engine)
        {
            last_error = "Invalid engine pointer";
            return;
        }
        if (!supported_scenes.contains(scene))
        {
            last_error = "Unknown scene: " + scene;
            return;
        }

        engine->setScene(scene);
    }

    void agift_Engine_cleanupScene(void *_engine)
    {
       last_error.clear();
        agift::EngineCore *engine = (agift::EngineCore *)_engine;
        if (!engine)
        {
            last_error = "Invalid engine pointer";
            return;
        }

        engine->cleanupScene();
    }

    void agift_Engine_addView(void *_engine, void *native_view)
    {
        last_error.clear();
        agift::EngineCore *engine = (agift::EngineCore *)_engine;
        if (!engine)
        {
            last_error = "Invalid engine pointer";
            return;
        }

        engine->addNativeView(native_view);
    }

    void agift_Engine_removeView(void *_engine, void *native_view)
    {
        last_error.clear();
        agift::EngineCore *engine = (agift::EngineCore *)_engine;
        if (!engine)
        {
            last_error = "Invalid engine pointer";
            return;
        }

        engine->removeNativeView(native_view);
    }

    void agift_Engine_resize(void *_engine, int width, int height)
    {
        last_error.clear();
        agift::EngineCore *engine = (agift::EngineCore *)_engine;
        if (!engine)
        {
            last_error = "Invalid engine pointer";
            return;
        }

        engine->resize(width, height);
    }

    void agift_Engine_render(void *_engine)
    {
        last_error.clear();
        agift::EngineCore *engine = (agift::EngineCore *)_engine;
        if (!engine)
        {
            last_error = "Invalid engine pointer";
            return;
        }

        engine->render();
    }

#ifdef __cplusplus
}
#endif
