#!/bin/bash
ROOT_DIR="$(pwd)"
KERNEL_DIR="${ROOT_DIR}/kernel_platform/common"
DISPLAY_DIR="${ROOT_DIR}/vendor/qcom/opensource/display-drivers"
CLANG_PATH="${HOME}/toolchains/linux-x86/clang-r547379/bin"
export PATH="${CLANG_PATH}:${PATH}"
export ARCH=arm64
export LLVM=1
export LLVM_IAS=1

echo "Building Display Module..."
make -C "${KERNEL_DIR}" O=out \
    M="${DISPLAY_DIR}" \
    DISPLAY_ROOT="${DISPLAY_DIR}" \
    CONFIG_ARCH_CANOE=y \
    CONFIG_DISPLAY_BUILD=m \
    CONFIG_DRM_MSM=y \
    CONFIG_DRM_ZTE_DISP=y \
    modules -j$(nproc)
