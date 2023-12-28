@echo off
setlocal EnableDelayedExpansion

set root_path=%~dp0
cd %root_path%

:: vcpkg (vcpkg.json)
set vcpkg_path=%root_path%vcpkg
set vcpkg_exe=%vcpkg_path%\vcpkg.exe
echo vcpkg_path: %vcpkg_path%
echo vcpkg_exe: %vcpkg_exe%
if not exist %vcpkg_exe% (
  set vcpkg_bat=%vcpkg_path%\bootstrap-vcpkg.bat
  echo vcpkg_bat: !vcpkg_bat!
  call !vcpkg_bat!
)

:: third_party\filament
mkdir -p %root_path%\third_party\filament\out\cmake-debug
cd %root_path%\third_party\filament\out\cmake-debug
cmake -DIMPORT_EXECUTABLES_DIR=out -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="../debug/filament" ../..
cmake --build . --target install --config Debug
IF %ERRORLEVEL% NEQ 0 (
    echo "cmake error"
    exit /b %ERRORLEVEL%
)

mkdir -p %root_path%\third_party\filament\out\cmake-release
cd %root_path%\third_party\filament\out\cmake-release
cmake -DIMPORT_EXECUTABLES_DIR=out -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="../release/filament" ../..
cmake --build . --target install --config Release
IF %ERRORLEVEL% NEQ 0 (
    echo "cmake error"
    exit /b %ERRORLEVEL%
)

:: cmake (Debug/Release)
cd %root_path%

cmake -B build -S . -DCMAKE_INSTALL_PREFIX=install\Debug
cmake --build build --target install --config Debug
IF %ERRORLEVEL% NEQ 0 (
    echo "cmake error"
    exit /b %ERRORLEVEL%
)

cmake -B build -S . -DCMAKE_INSTALL_PREFIX=install\Release
cmake --build build --target install --config Release
IF %ERRORLEVEL% NEQ 0 (
    echo "cmake error"
    exit /b %ERRORLEVEL%
)
