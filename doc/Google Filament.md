# Google Filament

<img src="https://google.github.io/filament/images/filament_logo.png" width="200">

# 一、简介

开源：Apache-2.0 license

仓库：https://github.com/google/filament

文档：https://google.github.io/filament/

## 1、Authors 作者

Romain Guy (罗曼·盖伊), @romainguy

Mathias Agopian (马蒂亚斯·阿戈皮安), @darthmoosious

## 2、Overview 概述

Filament is a real-time physically based rendering (PBR) engine for Android, iOS, Linux, macOS, Windows, and WebGL. It is designed to be as small as possible and as efficient as possible on Android.
> Filament 是一个基于物理的实时渲染 (PBR) 引擎，适用于 Android、iOS、Linux、macOS、Windows 和 WebGL。它被设计为在 Android 上尽可能小、尽可能高效。

Filament is a real-time physically-based renderer written in C++. It is mobile-first, but also multi-platform.
> Filament 是一个用 C++ 编写的基于物理的实时渲染器。它是移动优先的，也是多平台的。

We are very conscientious about keeping Filament small, fast to load, and focused on rendering. For example, Filament does not compile materials at run time. Instead, we provide a command line tool ([matc](https://github.com/google/filament/tree/master/tools/matc)) that does this offline.
> 我们非常认真地保持 Filament 的体积小、加载速度快，并专注于渲染。例如，Filament 不会在运行时编译材料。相反，我们提供了一个命令行工具（[matc](https://github.com/google/filament/tree/master/tools/matc)）来离线执行此操作。

Filament offers a customizable material system that you can use to create both simple and complex materials.
> Filament 提供了可定制的材料系统，您可以使用它来创建简单和复杂的材料。

## 3、Features 特征

### APIs 接口

- **Native C++** API for **Android, iOS, Linux, macOS and Windows**
- Java/JNI API for Android
- **JavaScript** API

```cpp
// 创建一个 Engine 、一个 Renderer 和一个 SwapChain 。 
// SwapChain 是从本机窗口指针创建的（例如 macOS 上的 NSView 或 Windows 上的 HWND ）：
Engine* engine = Engine::create();
SwapChain* swapChain = engine->createSwapChain(nativeWindow);
Renderer* renderer = engine->createRenderer();

// 创建一个 View 、一个 Scene 和一个 Camera
Camera* camera = engine->createCamera(EntityManager::get().create());
View* view = engine->createView();
Scene* scene = engine->createScene();

view->setCamera(camera);
view->setScene(scene);

// 场景中添加对象
Entity renderable = EntityManager::get().create();
scene->addEntity(renderable);

// beginFrame() returns false if we need to skip a frame
if (renderer->beginFrame(swapChain)) {
    // for each View
    renderer->render(view);
    renderer->endFrame();
}
```

### Backends 后端

- OpenGL 4.1+ for Linux, macOS and Windows
- OpenGL ES 3.0+ for Android and iOS
- **Metal** for **macOS and iOS**
- **Vulkan 1.0** for **Android, Linux, macOS, and Windows**
- **WebGL 2.0** for all platforms

## 4、Principles 原则

### Real-time mobile performance 实时移动性能

Our primary goal is to design and implement a rendering system able to perform efficiently on mobile platforms. The primary target will be OpenGL ES 3.x class GPUs.
> 我们的主要目标是设计和实现一个能够在移动平台上高效执行的渲染系统。主要目标是 OpenGL ES 3.x 级 GPU。

### Quality  质量

Our rendering system will emphasize overall picture quality. We will however accept quality compromises to support low and medium performance GPUs.
> 我们的渲染系统将强调整体图像质量。不过，我们会接受质量妥协以支持中低性能 GPU。

### Ease of use 使用方便

Artists need to be able to iterate often and quickly on their assets and our rendering system must allow them to do so intuitively. We must therefore provide parameters that are easy to understand (for instance, no specular power).
> 艺术家需要能够经常、快速地迭代他们的资产，我们的渲染系统必须允许他们直观地做到这一点。因此，我们必须提供易于理解的参数（例如，无镜面反射强度）。

We also understand that not all developers have the luxury to work with artists. The physically based approach of our system will allow developers to craft visually plausible materials without the need to understand the theory behind our implementation.
> 我们也明白，并非所有开发商都有机会与艺术家合作。我们系统的基于物理的方法将允许开发人员制作视觉上合理的材料，而无需了解我们实现背后的理论。

For both artists and developers, our system will rely on as few parameters as possible to reduce trial and error and allow users to quickly master the material model.
> 对于艺术家和开发人员来说，我们的系统将依赖尽可能少的参数来减少试错，让用户快速掌握材质模型。

In addition, any combination of parameter values should lead to physically plausible results. Physically implausible materials must be hard to create.
> 此外，参数值的任何组合都应该产生物理上合理的结果。物理上难以置信的材料一定很难创造。

### Familiarity 熟悉度

Our system should use physical units everywhere possible: distances in meters or centimeters, color temperatures in Kelvin, light units in lumens or candelas, etc.
> 我们的系统应尽可能使用物理单位：以米或厘米为单位的距离、以开尔文为单位的色温、以流明或坎德拉为单位的光单位等。

### Flexibility 灵活性

A physically based approach must not preclude non-realistic rendering. User interfaces for instance will need unlit materials.
> 基于物理的方法不得排除非真实渲染。例如，用户界面将需要不发光的材料。

### Deployment size 部署规模

While not directly related to the content of this document, it bears emphasizing our desire to keep the rendering library as small as possible so any application can bundle it without increasing the binary to undesirable sizes.
> 虽然与本文档的内容没有直接关系，但值得强调的是，我们希望使渲染库尽可能小，以便任何应用程序都可以将其捆绑在一起，而无需将二进制文件增加到不理想的大小。

## 5、Material 材质

A material defines the visual appearance of a surface. To completely describe and render a surface, a material provides the following information:
> 材质定义了表面的视觉外观。为了完整地描述和渲染表面，材质提供以下信息：

- Material model  材料模型
- Set of use-controllable named parameters 使用可控的命名参数集
- Raster state 光栅状态 (blending mode, backface culling, etc. 混合模式、背面剔除等)
- Vertex shader code  顶点着色器代码
- Fragment shader code 片段着色器代码
