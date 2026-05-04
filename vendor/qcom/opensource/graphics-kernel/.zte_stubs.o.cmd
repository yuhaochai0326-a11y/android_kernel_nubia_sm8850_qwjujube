savedcmd_/home/adrianojr59/Downloads/NX809JAndroid16/vendor/qcom/opensource/graphics-kernel/zte_stubs.o := clang -Wp,-MMD,/home/adrianojr59/Downloads/NX809JAndroid16/vendor/qcom/opensource/graphics-kernel/.zte_stubs.o.d -nostdinc -I../arch/arm64/include -I./arch/arm64/include/generated -I../include -I./include -I../arch/arm64/include/uapi -I./arch/arm64/include/generated/uapi -I../include/uapi -I./include/generated/uapi -include ../include/linux/compiler-version.h -include ../include/linux/kconfig.h -include ../include/linux/compiler_types.h -D__KERNEL__ --target=aarch64-linux-gnu -fintegrated-as -Werror=unknown-warning-option -Werror=ignored-optimization-argument -Werror=option-ignored -Werror=unused-command-line-argument -mlittle-endian -DKASAN_SHADOW_SCALE_SHIFT= -fmacro-prefix-map=../= -Werror -std=gnu11 -fshort-wchar -funsigned-char -fno-common -fno-PIE -fno-strict-aliasing -mgeneral-regs-only -DCONFIG_CC_HAS_K_CONSTRAINT=1 -Wno-psabi -fasynchronous-unwind-tables -mbranch-protection=pac-ret -Wa,-march=armv8.5-a -DARM64_ASM_ARCH='"armv8.5-a"' -ffixed-x18 -DKASAN_SHADOW_SCALE_SHIFT= -fno-delete-null-pointer-checks -O2 -fstack-protector-strong -fno-omit-frame-pointer -fno-optimize-sibling-calls -ftrivial-auto-var-init=zero -fno-stack-clash-protection -fsanitize=kcfi -falign-functions=4 -fstrict-flex-arrays=3 -fno-strict-overflow -fno-stack-check -Wall -Wundef -Werror=implicit-function-declaration -Werror=implicit-int -Werror=return-type -Werror=strict-prototypes -Wno-format-security -Wno-trigraphs -Wno-frame-address -Wno-address-of-packed-member -Wframe-larger-than=2048 -Wno-gnu -Wno-format-overflow-non-kprintf -Wno-format-truncation-non-kprintf -Wvla -Wno-pointer-sign -Wcast-function-type -Wimplicit-fallthrough -Werror=date-time -Werror=incompatible-pointer-types -Wenum-conversion -Wextra -Wunused -Wno-unused-but-set-variable -Wno-unused-const-variable -Wno-format-overflow -Wno-override-init -Wno-pointer-to-enum-cast -Wno-tautological-constant-out-of-range-compare -Wno-unaligned-access -Wno-enum-compare-conditional -Wno-missing-field-initializers -Wno-type-limits -Wno-shift-negative-value -Wno-enum-enum-conversion -Wno-sign-compare -Wno-unused-parameter -g -gdwarf-5 -gz=zstd -mstack-protector-guard=sysreg -mstack-protector-guard-reg=sp_el0 -mstack-protector-guard-offset=1616 -I/home/adrianojr59/Downloads/NX809JAndroid16/vendor/qcom/opensource/graphics-kernel/include -DCONFIG_QCOM_KGSL_USE_SHMEM=1 -DCONFIG_QCOM_ADRENO_DEFAULT_GOVERNOR="msm-adreno-tz" -DCONFIG_QCOM_KGSL_PROCESS_RECLAIM=1 -DCONFIG_QCOM_KGSL_CONTEXT_DEBUG=1 -DCONFIG_QCOM_KGSL_IOCOHERENCY_DEFAULT=1 -DCONFIG_QCOM_KGSL_RT_MUTEX=1 -DCONFIG_QCOM_KGSL_SORT_POOL=1 -DCONFIG_QCOM_KGSL_IDLE_TIMEOUT=80 -I/home/adrianojr59/Downloads/NX809JAndroid16/vendor/qcom/opensource/graphics-kernel -I/home/adrianojr59/Downloads/NX809JAndroid16/vendor/qcom/opensource/graphics-kernel/include/linux -I../drivers/devfreq -I/home/adrianojr59/Downloads/NX809JAndroid16/vendor/qcom/opensource/graphics-kernel/compat -I/home/adrianojr59/Downloads/NX809JAndroid16/vendor/qcom/opensource/mm-drivers/hw_fence/include  -fsanitize=array-bounds -fsanitize=local-bounds -fsanitize-trap=undefined    -fdebug-info-for-profiling -mllvm -enable-fs-discriminator=true -mllvm -improved-fs-discriminator=true  -DMODULE  -DKBUILD_BASENAME='"zte_stubs"' -DKBUILD_MODNAME='"msm_kgsl"' -D__KBUILD_MODNAME=kmod_msm_kgsl -c -o /home/adrianojr59/Downloads/NX809JAndroid16/vendor/qcom/opensource/graphics-kernel/zte_stubs.o /home/adrianojr59/Downloads/NX809JAndroid16/vendor/qcom/opensource/graphics-kernel/zte_stubs.c  

source_/home/adrianojr59/Downloads/NX809JAndroid16/vendor/qcom/opensource/graphics-kernel/zte_stubs.o := /home/adrianojr59/Downloads/NX809JAndroid16/vendor/qcom/opensource/graphics-kernel/zte_stubs.c

deps_/home/adrianojr59/Downloads/NX809JAndroid16/vendor/qcom/opensource/graphics-kernel/zte_stubs.o := \
  ../include/linux/compiler-version.h \
    $(wildcard include/config/CC_VERSION_TEXT) \
  ../include/linux/kconfig.h \
    $(wildcard include/config/CPU_BIG_ENDIAN) \
    $(wildcard include/config/BOOGER) \
    $(wildcard include/config/FOO) \
  ../include/linux/compiler_types.h \
    $(wildcard include/config/DEBUG_INFO_BTF) \
    $(wildcard include/config/PAHOLE_HAS_BTF_TAG) \
    $(wildcard include/config/FUNCTION_ALIGNMENT) \
    $(wildcard include/config/CC_HAS_SANE_FUNCTION_ALIGNMENT) \
    $(wildcard include/config/X86_64) \
    $(wildcard include/config/ARM64) \
    $(wildcard include/config/LD_DEAD_CODE_DATA_ELIMINATION) \
    $(wildcard include/config/LTO_CLANG) \
    $(wildcard include/config/HAVE_ARCH_COMPILER_H) \
    $(wildcard include/config/CC_HAS_COUNTED_BY) \
    $(wildcard include/config/UBSAN_SIGNED_WRAP) \
    $(wildcard include/config/CC_HAS_ASM_INLINE) \
  ../include/linux/compiler_attributes.h \
  ../include/linux/compiler-clang.h \
    $(wildcard include/config/ARCH_USE_BUILTIN_BSWAP) \
  ../arch/arm64/include/asm/compiler.h \
    $(wildcard include/config/ARM64_PTR_AUTH_KERNEL) \
    $(wildcard include/config/ARM64_PTR_AUTH) \
    $(wildcard include/config/BUILTIN_RETURN_ADDRESS_STRIPS_PAC) \
  ../include/linux/types.h \
    $(wildcard include/config/HAVE_UID16) \
    $(wildcard include/config/UID16) \
    $(wildcard include/config/ARCH_DMA_ADDR_T_64BIT) \
    $(wildcard include/config/PHYS_ADDR_T_64BIT) \
    $(wildcard include/config/64BIT) \
    $(wildcard include/config/ARCH_32BIT_USTAT_F_TINODE) \
  ../include/uapi/linux/types.h \
  arch/arm64/include/generated/uapi/asm/types.h \
  ../include/uapi/asm-generic/types.h \
  ../include/asm-generic/int-ll64.h \
  ../include/uapi/asm-generic/int-ll64.h \
  ../arch/arm64/include/uapi/asm/bitsperlong.h \
  ../include/asm-generic/bitsperlong.h \
  ../include/uapi/asm-generic/bitsperlong.h \
  ../include/uapi/linux/posix_types.h \
  ../include/linux/stddef.h \
  ../include/uapi/linux/stddef.h \
  ../arch/arm64/include/uapi/asm/posix_types.h \
  ../include/uapi/asm-generic/posix_types.h \

/home/adrianojr59/Downloads/NX809JAndroid16/vendor/qcom/opensource/graphics-kernel/zte_stubs.o: $(deps_/home/adrianojr59/Downloads/NX809JAndroid16/vendor/qcom/opensource/graphics-kernel/zte_stubs.o)

$(deps_/home/adrianojr59/Downloads/NX809JAndroid16/vendor/qcom/opensource/graphics-kernel/zte_stubs.o):
