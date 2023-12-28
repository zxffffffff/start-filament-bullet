project(engine-core)
message("[${PROJECT_NAME}] -------- start")

message(STATUS "[${PROJECT_NAME}] PROJECT_SOURCE_DIR : ${PROJECT_SOURCE_DIR}")

# 引入 fmt
find_package(fmt CONFIG REQUIRED)

# 引入 bullet3
find_package(Bullet CONFIG REQUIRED)
message(STATUS "[${PROJECT_NAME}] BULLET_INCLUDE_DIRS : ${BULLET_INCLUDE_DIRS}")
message(STATUS "[${PROJECT_NAME}] BULLET_LIBRARIES : ${BULLET_LIBRARIES}")

# 引入 filament
set(FILAMENT_OUT "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/filament/out")
set(FILAMENT_LIBRARIES "filament;backend;bluegl;bluevk;filabridge;filaflat;utils;geometry;smol-v;ibl;vkshaders")
if(WIN32)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(FILAMENT_INCLUDE_BIN "${FILAMENT_OUT}/debug/filament/bin")
        set(FILAMENT_INCLUDE_DIRS "${FILAMENT_OUT}/debug/filament/include")
        set(FILAMENT_LIBRARY_DIRS "${FILAMENT_OUT}/debug/filament/lib/x86_64")
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        set(FILAMENT_INCLUDE_BIN "${FILAMENT_OUT}/release/filament/bin")
        set(FILAMENT_INCLUDE_DIRS "${FILAMENT_OUT}/release/filament/include")
        set(FILAMENT_LIBRARY_DIRS "${FILAMENT_OUT}/release/filament/lib/x86_64")
    endif()
elseif(APPLE)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(FILAMENT_INCLUDE_BIN "${FILAMENT_OUT}/debug/filament/bin")
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        set(FILAMENT_INCLUDE_BIN "${FILAMENT_OUT}/release/filament/bin")
    endif()
    if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            set(FILAMENT_INCLUDE_DIRS "${FILAMENT_OUT}/debug/filament/include")
            set(FILAMENT_LIBRARY_DIRS "${FILAMENT_OUT}/debug/filament/lib/arm64")
        elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
            set(FILAMENT_INCLUDE_DIRS "${FILAMENT_OUT}/release/filament/include")
            set(FILAMENT_LIBRARY_DIRS "${FILAMENT_OUT}/release/filament/lib/arm64")
        endif()
    elseif(CMAKE_SYSTEM_NAME STREQUAL "iOS")
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            set(FILAMENT_INCLUDE_DIRS "${FILAMENT_OUT}/ios-debug/filament/include")
            set(FILAMENT_LIBRARY_DIRS "${FILAMENT_OUT}/ios-debug/filament/lib/arm64")
        elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
            set(FILAMENT_INCLUDE_DIRS "${FILAMENT_OUT}/ios-release/filament/include")
            set(FILAMENT_LIBRARY_DIRS "${FILAMENT_OUT}/ios-release/filament/lib/arm64")
        endif()
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Android")
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            set(FILAMENT_INCLUDE_DIRS "${FILAMENT_OUT}/android-debug/filament/include")
            set(FILAMENT_LIBRARY_DIRS "${FILAMENT_OUT}/android-debug/filament/lib/arm64")
        elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
            set(FILAMENT_INCLUDE_DIRS "${FILAMENT_OUT}/android-release/filament/include")
            set(FILAMENT_LIBRARY_DIRS "${FILAMENT_OUT}/android-release/filament/lib/arm64")
        endif()
    endif()
endif()
message(STATUS "[${PROJECT_NAME}] FILAMENT_INCLUDE_DIRS : ${FILAMENT_INCLUDE_DIRS}")
message(STATUS "[${PROJECT_NAME}] FILAMENT_LIBRARY_DIRS : ${FILAMENT_LIBRARY_DIRS}")
message(STATUS "[${PROJECT_NAME}] FILAMENT_LIBRARIES : ${FILAMENT_LIBRARIES}")

# Public 头文件
file(GLOB_RECURSE include_headers
    engine_c.h
    engine_core.h
    engine_filament_bullet.h
)

add_library(${PROJECT_NAME} STATIC
    ${include_headers}
    engine_c.cpp
    engine_core.cpp
    engine_filament_bullet.cpp
)

target_link_directories(${PROJECT_NAME}
    PUBLIC ${FILAMENT_LIBRARY_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC fmt::fmt-header-only
    PUBLIC ${BULLET_LIBRARIES}
    PUBLIC ${FILAMENT_LIBRARIES}
)

if (APPLE)
target_link_libraries(${PROJECT_NAME}
    PUBLIC "-framework Cocoa"
    PUBLIC "-framework Metal"
    PUBLIC "-framework CoreVideo"
)
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
    PRIVATE ${FILAMENT_INCLUDE_DIRS}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    PUBLIC_HEADER "${include_headers}"
)

install(TARGETS ${PROJECT_NAME}
    PUBLIC_HEADER DESTINATION include
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib
)

message("[${PROJECT_NAME}] -------- done")