# start-filament-bullet
一个 C++ filament bullet 脚手架，TODO

## submodules
- git submodule add -f https://github.com/microsoft/vcpkg.git vcpkg
- git submodule add -b release https://github.com/google/filament.git third_party/filament

## third_party

### filament

仓库：https://github.com/google/filament.git

构建文档：https://github.com/google/filament/blob/main/BUILDING.md

依赖：
- CMake 3.19+
- clang 14.0+
- ninja 1.10+

Android 依赖：
- Android Studio Flamingo
- Android NDK 25.1 or higher
- Java 17

WebGL 依赖：
- EMSDK

macOS 和 Linux 使用简化编译脚本 (封装执行 cmake)：
```bash
cd third_party/filament

# 查看帮助
./build.sh -h

# macOS + iOS
# -i 安装到 out
# -l 同时编译 arm64/x86_64
# -s 支持 iOS 模拟器
./build.sh -p desktop,ios -i -l -s debug release

# Android
./build.sh -p android -i release

# WebGL
export EMSDK=<your chosen home for the emscripten SDK>
./build.sh -p webgl release

# 清理 out
./build.sh -c
```

Windows 需要手动执行 cmake 命令编译：
```bash
cd third_party/filament

mkdir -p out/cmake-debug
cd out/cmake-debug

cmake -DIMPORT_EXECUTABLES_DIR=out -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="../debug/filament" ../..
cmake --build . --target install --config Debug
```

## bullet3

仓库：https://github.com/bulletphysics/bullet3.git

支持 vcpkg (已添加)：
```bash
vcpkg search bullet3

# bullet3  3.25#1  Bullet Physics is a professional collision detection, rigid body, and soft...
```
