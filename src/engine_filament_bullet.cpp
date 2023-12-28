#include "engine_filament_bullet.h"
#include <fmt/core.h>
#include <map>

#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filament/View.h>
#include <filament/Viewport.h>
#include <filament/Scene.h>
#include <filament/Engine.h>
#include <filament/Camera.h>
#include <filament/Skybox.h>
#include <filament/VertexBuffer.h>
#include <filament/IndexBuffer.h>
#include <filament/Material.h>
#include <filament/RenderableManager.h>
#include <utils/EntityManager.h>

using namespace filament;
using utils::Entity;
using utils::EntityManager;

#include <bullet/btBulletDynamicsCommon.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1500 && _MSC_VER < 1900)
/* msvc兼容utf-8: https://support.microsoft.com/en-us/kb/980263 */
#if (_MSC_VER >= 1700)
#pragma execution_character_set("utf-8")
#endif
#pragma warning(disable : 4566)
#endif

namespace agift
{
    class EngineFilamentBulletPriv
    {
    public:
        Engine *engine = nullptr;
        Renderer *renderer = nullptr;

        View *view = nullptr;
        Scene *scene = nullptr;
        Camera *camera = nullptr;
        Skybox *skybox = nullptr;

        std::map<void *, SwapChain *> native_views;
    };

    EngineFilamentBullet::EngineFilamentBullet(const std::string &platform, const std::string &backend)
        : EngineCore(platform, backend), priv(std::make_unique<EngineFilamentBulletPriv>())
    {
    }

    EngineFilamentBullet::~EngineFilamentBullet()
    {
    }

    void EngineFilamentBullet::init()
    {
        assert(!priv->engine);

        Engine::Backend config_backend = Engine::Backend::DEFAULT;
        if (getBackend() == "Metal")
            config_backend = Engine::Backend::METAL;
        else if (getBackend() == "Vulkan")
            config_backend = Engine::Backend::VULKAN;
        else if (getBackend() == "OpenGL")
            config_backend = Engine::Backend::OPENGL;

        priv->engine = Engine::create(config_backend);

        priv->renderer = priv->engine->createRenderer();
    }

    void EngineFilamentBullet::cleanup()
    {
        assert(priv->engine);
        cleanupScene();

        priv->engine->destroy(priv->renderer);
        priv->renderer = nullptr;

        priv->engine->destroy(priv->engine);
        priv->engine = nullptr;
    }

    void EngineFilamentBullet::setScene(std::string scene)
    {
        assert(priv->engine);
        cleanupScene();

        priv->view = priv->engine->createView();
        priv->view->setPostProcessingEnabled(false);

        priv->scene = priv->engine->createScene();
        priv->view->setScene(priv->scene);

        priv->skybox = Skybox::Builder().color({0.1, 0.125, 0.25, 1.0}).build(*priv->engine);
        priv->scene->setSkybox(priv->skybox);

        Entity cameraEntity = EntityManager::get().create();
        priv->camera = priv->engine->createCamera(cameraEntity);
        priv->view->setCamera(priv->camera);
    }

    void EngineFilamentBullet::cleanupScene()
    {
        assert(priv->engine);

        if (priv->camera)
        {
            Entity cameraEntity = priv->camera->getEntity();
            priv->engine->destroyCameraComponent(cameraEntity);
            EntityManager::get().destroy(cameraEntity);
            priv->camera = nullptr;
        }

        if (priv->skybox)
        {
            priv->engine->destroy(priv->skybox);
            priv->skybox = nullptr;
        }

        if (priv->scene)
        {
            priv->engine->destroy(priv->scene);
            priv->scene = nullptr;
        }

        if (priv->view)
        {
            priv->engine->destroy(priv->view);
            priv->view = nullptr;
        }

        while (priv->native_views.size() > 0)
        {
            removeNativeView(priv->native_views.begin()->first);
        }
    }

    void EngineFilamentBullet::addNativeView(void *native_view)
    {
        assert(priv->engine);

        if (priv->native_views.contains(native_view))
            return;
        priv->native_views[native_view] = priv->engine->createSwapChain(native_view);
    }

    void EngineFilamentBullet::removeNativeView(void *native_view)
    {
        assert(priv->engine);

        auto ite = priv->native_views.find(native_view);
        if (ite == priv->native_views.end())
            return;
        priv->engine->destroy(ite->second);
        priv->native_views.erase(ite);
    }

    bool EngineFilamentBullet::checkNativeView(void *native_view)
    {
        assert(priv->engine);

        return priv->native_views.contains(native_view);
    }

    void EngineFilamentBullet::resize(int width, int height)
    {
        assert(priv->engine);

        if (priv->view)
        {
            priv->view->setViewport(Viewport(0, 0, width, height));
        }
    }

    void EngineFilamentBullet::render()
    {
        assert(priv->engine);

        for (auto &[native_view, swapChain] : priv->native_views)
        {
            if (priv->renderer->beginFrame(swapChain))
            {
                priv->renderer->render(priv->view);
                priv->renderer->endFrame();
            }
        }
    }
}
