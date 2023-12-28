#!/bin/bash
set -e

root_path=$(dirname $(readlink -f "$0"))
cd ${root_path}

# vcpkg (vcpkg.json)
vcpkg_path=${root_path}/vcpkg
vcpkg_exe=${vcpkg_path}/vcpkg
echo vcpkg_path: ${vcpkg_path}
echo vcpkg_exe: ${vcpkg_exe}
if [ ! -x ${vcpkg_exe} ]; then
  vcpkg_sh=${vcpkg_path}/bootstrap-vcpkg.sh
  echo vcpkg_sh: ${vcpkg_sh}
  xcode-select --install
  sh ${vcpkg_sh}
fi

# third_party/filament
cd third_party/filament
echo ./build.sh -p desktop,ios -i -l -s debug release
./build.sh -p desktop,ios -i -l -s debug release

# cmake (Debug/Release)
cd ${root_path}

function cmake_build {
  config=$1
  install_path=install/${config}

  cmake -B build -S . -DCMAKE_INSTALL_PREFIX=${install_path}
  cmake --build build --target install --config ${config}
}
cmake_build Debug
cmake_build Release
