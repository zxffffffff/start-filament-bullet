#ifndef ENGINE_C_H
#define ENGINE_C_H

#ifdef __cplusplus
extern "C"
{
#endif

    const char *agift_Engine_getLastError();

    /* [1] 初始化 engine
     * @param platform "Windows", "macOS", "iOS", "Android", "Web"
     * @param backend  "Metal", “Vulkan”， “OpenGL”
     */
    void *agift_Engine_new(const char *platform, const char *backend);
    void agift_Engine_delete(void *engine);

    const char *agift_Engine_getName(void *engine);

    /* [2] 选择场景 scene
     * @param scene "Test"
     */
    void agift_Engine_setScene(void *engine, const char *scene);
    void agift_Engine_cleanupScene(void *engine);

    /* [3] 初始化 window
     * @param native_view 窗口句柄、CAEAGLLayer
     */
    void agift_Engine_addView(void *engine, void *native_view);
    void agift_Engine_removeView(void *engine, void *native_view);

    /* [4] 启动循环 loop
     */
    void agift_Engine_resize(void *engine, int width, int height);
    void agift_Engine_render(void *engine);

#ifdef __cplusplus
}
#endif

#endif // ENGINE_C_H