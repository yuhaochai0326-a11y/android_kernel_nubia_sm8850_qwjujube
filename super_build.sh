#!/bin/bash
# super_build.sh - Compile the official ZTE kernel tree (in-tree)
set -e

cd "$(dirname "$(readlink -f "$0")")"

# Tools paths (can be overridden via environment variables)
CLANG_DIR="${CLANG_DIR:-$(pwd)/clang-r547379}"
PREBUILTS_DIR="${PREBUILTS_DIR:-/home/adrianojr59/Downloads/KernelNX809J/infinity_build/prebuilts/kernel-build-tools/linux-x86/bin}"

if [ ! -d "$CLANG_DIR" ]; then
    echo "❌ Error: Clang compiler not found at $CLANG_DIR"
    echo "Please download the Android Clang compiler (revision r547379) and extract it to the root of this repository,"
    echo "or set the CLANG_DIR environment variable to its location (e.g. export CLANG_DIR=/path/to/clang)."
    exit 1
fi

if [ -d "$PREBUILTS_DIR" ]; then
    export PATH="$CLANG_DIR/bin:$PREBUILTS_DIR:$PATH"
else
    export PATH="$CLANG_DIR/bin:$PATH"
fi

# Architecture config
export ARCH=arm64
export SUBARCH=arm64
export CROSS_COMPILE=aarch64-linux-gnu-
export CROSS_COMPILE_ARM32=arm-linux-gnueabi-
export CLANG_TRIPLE=aarch64-linux-gnu-
export CC=clang

# Rust toolchain detection (required for CONFIG_RUST=y in defconfig)
# The nx809j_defconfig was generated with Rust 1.82.0 (CONFIG_RUSTC_VERSION=108200).
# Without Rust, olddefconfig disables RUST in cascade, altering struct layouts that
# stock .ko modules (qti_battery_charger, etc.) depend on → kernel crash.
if command -v rustc &>/dev/null; then
    export RUSTC="$(command -v rustc)"
    # rust-src component: needed for kernel Rust compilation
    RUST_SYSROOT="$(rustc --print sysroot 2>/dev/null)"
    if [ -d "$RUST_SYSROOT/lib/rustlib/src/rust/library" ]; then
        export RUST_LIB_SRC="$RUST_SYSROOT/lib/rustlib/src/rust/library"
    fi
    echo "🦀 Rust detected: $(rustc --version)"
else
    echo "⚠️  WARNING: rustc not found. Building without Rust support."
    echo "   This will differ from the defconfig and may cause stock .ko modules to crash."
fi

# BINDGEN detection (required for Rust kernel bindings)
if command -v bindgen &>/dev/null; then
    export BINDGEN="$(command -v bindgen)"
    echo "🔗 bindgen detected: $(bindgen --version 2>/dev/null | head -1)"
fi

# ZTE/Vendor variables
export ZTE_BOARD_NAME=qwjujube

# Kernel Source Path
KERNEL_DIR="$(pwd)/kernel_platform/common"

echo "🚀 Starting Unified Build for RedMagic 11 Pro (NX809J)"
echo "🔧 Using Clang: $CLANG_DIR"

# 1. Defconfig (Base configuration)
echo "[1/4] Applying factory kernel config..."
make -C $KERNEL_DIR LLVM=1 LLVM_IAS=1 nx809j_factory_defconfig

# Process config overrides
echo "[2/4] Enabling Droidspaces container support..."
"$KERNEL_DIR"/scripts/config --file "$KERNEL_DIR/.config" --enable CONFIG_USER_NS
"$KERNEL_DIR"/scripts/config --file "$KERNEL_DIR/.config" --enable CONFIG_PID_NS
"$KERNEL_DIR"/scripts/config --file "$KERNEL_DIR/.config" --enable CONFIG_IPC_NS
"$KERNEL_DIR"/scripts/config --file "$KERNEL_DIR/.config" --enable CONFIG_DEVTMPFS
"$KERNEL_DIR"/scripts/config --file "$KERNEL_DIR/.config" --enable CONFIG_DEVTMPFS_MOUNT
"$KERNEL_DIR"/scripts/config --file "$KERNEL_DIR/.config" --enable CONFIG_CGROUP_DEVICE
"$KERNEL_DIR"/scripts/config --file "$KERNEL_DIR/.config" --enable CONFIG_CGROUP_PIDS

# Disable MODULE_SIG_PROTECT (requires abi_symbollist.raw which we don't have)
"$KERNEL_DIR"/scripts/config --file "$KERNEL_DIR/.config" --disable CONFIG_MODULE_SIG_PROTECT 2>/dev/null || true
echo "[3/4] Resolving config dependencies..."
make -C $KERNEL_DIR LLVM=1 LLVM_IAS=1 olddefconfig

if [ ! -f "$KERNEL_DIR/.config" ]; then
    echo "❌ Error: failed to generate .config"
    exit 1
fi

# Apply KABI patch for Droidspaces compatibility
echo "📦 Applying Droidspaces KABI patch..."
if [ -f patches/Kernel_6.12.patch ]; then
    cd "$KERNEL_DIR" && patch -p1 -t < ../../patches/Kernel_6.12.patch && cd ../..
    echo "✅ KABI patch applied"
else
    echo "⚠️  KABI patch not found, skipping"
fi

# Create dummy abi_symbollist.raw (GKI modpost requirement, we use factory vendor modules)
touch "$KERNEL_DIR"/abi_symbollist.raw

# 2. Build kernel Image
echo "[4/4] Compiling Kernel Image..."
make -C $KERNEL_DIR -j$(nproc) LLVM=1 LLVM_IAS=1 KBUILD_MODPOST_WARN=1 Image

echo "✅ Compilation finished!"
echo "📦 Kernel Image built at: $KERNEL_DIR/arch/arm64/boot/Image"
