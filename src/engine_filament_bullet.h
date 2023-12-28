#pragma once
#include "engine_core.h"
#include <memory>

#if defined(_MSC_VER) && (_MSC_VER >= 1500 && _MSC_VER < 1900)
/* msvc兼容utf-8: https://support.microsoft.com/en-us/kb/980263 */
#if (_MSC_VER >= 1700)
#pragma execution_character_set("utf-8")
#endif
#pragma warning(disable : 4566)
#endif

namespace agift
{
    class EngineFilamentBullet : public EngineCore
    {
    private:
        std::unique_ptr<class EngineFilamentBulletPriv> priv;

    public:
        EngineFilamentBullet(const std::string &platform, const std::string &backend);
        virtual ~EngineFilamentBullet();

        virtual std::string getName() const override { return "EngineFilamentBullet"; }

        virtual void init() override;
        virtual void cleanup() override;

        virtual void setScene(std::string scene) override;
        virtual void cleanupScene() override;

        virtual void addNativeView(void *native_view) override;
        virtual void removeNativeView(void *native_view) override;
        virtual bool checkNativeView(void *native_view) override;

        virtual void resize(int width, int height) override;
        virtual void render() override;
    };
}
