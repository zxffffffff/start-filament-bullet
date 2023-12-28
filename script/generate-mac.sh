#!/bin/bash
set -e

root_path=$(dirname $(readlink -f "$0"))/..
cd ${root_path}

HOST_TOOLS_PATH=${root_path}/third_party/filament/out/release/filament/bin
matc_path=`find ${HOST_TOOLS_PATH} -name matc -type f | head -n 1`
resgen_path=`find ${HOST_TOOLS_PATH} -name resgen -type f | head -n 1`

if [[ ! -e "${matc_path}" ]]; then
  echo "No matc binary could be found in ${HOST_TOOLS_PATH}."
  echo "Ensure Filament has been built/installed before building this app."
  exit 1
fi

# Build materials
materials=("bakedColor")
filamats=()
for material in "${materials[@]}"
do
  material_path=${root_path}/generated/material
  mkdir -p ${material_path}
  mat_path="${root_path}/materials/${material}.mat"
  filamat_path="${material_path}/${material}.filamat"
  filamats+=(${filamat_path})

  "${matc_path}" \
    -p all \
    --api all \
    -f header \
    -o ${filamat_path} \
    ${mat_path}
done

# Build resources
res_path=${root_path}/generated/resources
mkdir -p ${res_path}

"${resgen_path}" \
  -x "${res_path}" \
  ${filamats}
