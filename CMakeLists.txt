message("[engine] -------- start")
cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

if(WIN32)
    # Windows 可选编译配置集（vcpkg built-in/community triplets）
    set(VCPKG_TARGET_TRIPLET x64-windows-static)
    
    # 源码使用 utf-8 编码格式编译
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
elseif(APPLE)
    # 编译动态库需要设置-fPIC
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

    # 需要 macOS 10.15 支持 C++17 filesystem
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15")
else()
    # 编译动态库需要设置-fPIC
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -pthread")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -pthread")

    # 静态链接 C++ 依赖库，不要使用 -static 静态链接 glibc
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()

# 使用 vcpkg 工具链，需要在 project 之前设置
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
message(STATUS "[engine] CMAKE_TOOLCHAIN_FILE : ${CMAKE_TOOLCHAIN_FILE}")

project("engine")

message(STATUS "[engine] CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message(STATUS "[engine] CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "[engine] CMAKE_CURRENT_SOURCE_DIR : ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "[engine] PROJECT_SOURCE_DIR : ${PROJECT_SOURCE_DIR}")

# src
include_directories(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(src)

# test
include_directories(${PROJECT_SOURCE_DIR}/test)
add_subdirectory(test)

message("[engine] -------- done")