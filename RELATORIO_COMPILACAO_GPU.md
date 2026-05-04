# Relatório Técnico: Compilação do Driver GPU SM8750 (GKI 6.12)

Este documento registra as fontes, dependências e modificações realizadas para portar o driver `msm_kgsl` para o Android 16 (Kernel 6.12).

## 1. Repositórios de Origem e Referência

### **A. Fonte de Compatibilidade 6.12 (CodeLinaro)**
Este repositório foi a base para as correções de API exigidas pelo Kernel 6.12 Linux.
*   **Link**: [https://git.codelinaro.org/clo/la/kernel/qcom.git](https://git.codelinaro.org/clo/la/kernel/qcom.git)
*   **Branch**: `qclinux.6.12.y`
*   **Commit de Referência**: `da010be9139468ef277deecbb94834e4e6c3c2b0`
*   **Uso**: Extração dos arquivos de compatibilidade IOMMU e Memory Buffer (`mem-buf_6.12.c`).

### **B. Driver GPU Adreno 840 (Base)**
Repositório contendo a implementação específica do KGSL para o hardware Snapdragon 8 Elite.
*   **Link**: [https://github.com/cmfnels/android_vendor_qcom_opensource_graphics-kernel.git](https://github.com/cmfnels/android_vendor_qcom_opensource_graphics-kernel.git)
*   **Uso**: Base de código do driver que foi integrada ao diretório `vendor/qcom/opensource/graphics-kernel`.

### **C. Referência de Headers (Kernel Nubia NX809J)**
Kernel original do dispositivo usado para resolver dependências de cabeçalhos proprietários.
*   **Link**: [https://github.com/cmfnels/android_kernel_nubia_sm8750.git](https://github.com/cmfnels/android_kernel_nubia_sm8750.git)
*   **Uso**: Extração do header `msm_performance.h` e outros arquivos `soc/qcom`.

### **D. Repositório de Linhagem (MSM Mainline)**
Usado para verificar commits de segurança e integração do Android 16.
*   **Link**: [https://git.codelinaro.org/clo/la/kernel/msm.git](https://git.codelinaro.org/clo/la/kernel/msm.git)

---

## 2. Componentes Extraídos e Portados

Para que o driver compilasse no ambiente GKI, os seguintes arquivos foram integrados manualmente ao diretório `graphics-kernel/compat/`:

1.  **`qcom-iommu-util.c`**: Refatorado para suportar a nova estrutura `iommu_get_resv_regions`.
2.  **`mem-buf_6.12.c`**: Versão atualizada do gerenciador de buffers compatível com as APIs de `class_create` do Kernel 6.12.
3.  **Headers de IOMMU** (Extraídos para `include/linux/`):
    *   `dma-mapping-fast.h`
    *   `io-pgtable-fast.h`
    *   `iommu-v8.h`

---

## 3. Modificações Técnicas Principais

### **IOMMU (Kernel 6.12 API)**
*   **Mudança**: O Kernel 6.12 removeu o campo `iommu_ops` de dentro da `struct bus_type`.
*   **Solução**: O driver foi alterado para usar a função exportada `iommu_get_resv_regions(dev, list)`, garantindo compatibilidade com o GKI.

### **Unificação de Inicialização**
*   **Mudança**: Removidos os macros `module_init` e `arch_initcall` dos arquivos auxiliares.
*   **Solução**: A inicialização do IOMMU e do Mem-Buf agora é chamada manualmente dentro da função `kgsl_3d_init`.

### **Resolução de Section Mismatches**
*   **Mudança**: Erros de linkagem ocorriam ao tentar chamar funções de limpeza (`exit`) a partir de caminhos de erro na inicialização.
*   **Solução**: Removidos os atributos `__exit` das funções de limpeza manuais, permitindo sua chamada segura durante o boot.

---

## 4. O que ainda falta (Pendências)

Para que você tenha o driver rodando no aparelho, restam apenas dois passos:

1.  **Geração do Module.symvers**: Necessário realizar um build completo do kernel (`kernel_platform/common`) para gerar este arquivo de símbolos.
2.  **Linkagem Final**: Com o `Module.symvers` em mãos, o comando `make modules` completará o MODPOST.

---

## 5. Estratégia de Integração (Abordagem Híbrida)

Como a ZTE não forneceu o código-fonte de alguns componentes críticos, é **obrigatório** utilizar uma abordagem híbrida, extraindo os binários originais de um **backup (dump) do aparelho**:
*   **WLAN (Wi-Fi)**: Extrair `qca_cld3_wlan.ko`.
*   **Fan (Ventoinha)**: Extrair `zte_fan.ko` (essencial para o RedMagic).

---

## 6. Guia de Implementação (Passo-a-Passo para Reprodução)

### **Passo 0: Preparação de Arquivos**
Extraia os seguintes arquivos do repositório CodeLinaro (`qclinux.6.12.y`):
1.  Copie `qcom-iommu-util.c` e `mem-buf_6.12.c` para `compat/`.
2.  Copie `dma-mapping-fast.h`, `io-pgtable-fast.h` e `iommu-v8.h` para `kernel_platform/common/include/linux/`.
3.  Copie `msm_performance.h` (do Nubia) para `include/soc/qcom/`.

### **Passo 1: Correção de Macros GKI**
**Arquivo:** `kernel_platform/common/include/linux/android_vendor.h`
```c
#include <linux/android_kabi.h>
#define ANDROID_BACKPORT_RESERVED ANDROID_BACKPORT_RESERVE
```

### **Passo 2: Adaptação IOMMU**
**Arquivo:** `compat/qcom-iommu-util.c`
```c
struct iommu_ops *ops = (struct iommu_ops *)iommu_get_resv_regions(dev, list);
```

### **Passo 3: Configuração Kbuild**
**Arquivo:** `Kbuild`
```makefile
msm_kgsl-y += compat/mem-buf_6.12.o
```

### **Passo 4: Hooks de Inicialização**
**Arquivo:** `adreno.c`
```c
// Declarar externs e chamar manualmente em kgsl_3d_init()
qcom_iommu_util_init();
mem_buf_init();
```

### **Passo 5: Stubs de SCM**
**Arquivos:** `adreno_sysfs.c` e `governor_msm_adreno_tz.c`
```c
static inline int qcom_scm_kgsl_dcvs_tuning(...) { return -EOPNOTSUPP; }
```

### **Passo 6: APIs Kernel 6.12**
**Arquivo:** `compat/mem-buf_6.12.c`
1.  Atualizar `class_create` para 1 argumento.
2.  Atualizar `platform_driver.remove` para retornar `void`.

---

## 7. Comando de Compilação
```bash
export PATH="/home/adrianojr59/toolchains/linux-x86/clang-r547379/bin:${PATH}"
cd kernel_platform/common
make ARCH=arm64 LLVM=1 LLVM_IAS=1 O=out \
    M="../../vendor/qcom/opensource/graphics-kernel" \
    CONFIG_ARCH_CANOE=y \
    KGSL_PATH="../../vendor/qcom/opensource/graphics-kernel" \
    KBUILD_MODPOST_WARN=1 \
    modules
```

---

---
---

# Technical Report: SM8750 GPU Driver Compilation (GKI 6.12)

This document records the sources, dependencies, and modifications performed to port the `msm_kgsl` driver to Android 16 (Kernel 6.12).

## 1. Source and Reference Repositories

### **A. 6.12 Compatibility Source (CodeLinaro)**
This repository was the base for API fixes required by the Linux 6.12 Kernel.
*   **Link**: [https://git.codelinaro.org/clo/la/kernel/qcom.git](https://git.codelinaro.org/clo/la/kernel/qcom.git)
*   **Branch**: `qclinux.6.12.y`
*   **Reference Commit**: `da010be9139468ef277deecbb94834e4e6c3c2b0`
*   **Usage**: Extraction of IOMMU and Memory Buffer (`mem-buf_6.12.c`) compatibility files.

### **B. Adreno 840 GPU Driver (Base)**
Repository containing the specific KGSL implementation for Snapdragon 8 Elite hardware.
*   **Link**: [https://github.com/cmfnels/android_vendor_qcom_opensource_graphics-kernel.git](https://github.com/cmfnels/android_vendor_qcom_opensource_graphics-kernel.git)
*   **Usage**: Driver codebase integrated into the `vendor/qcom/opensource/graphics-kernel` directory.

### **C. Header Reference (Nubia NX809J Kernel)**
Original device kernel used to resolve proprietary header dependencies.
*   **Link**: [https://github.com/cmfnels/android_kernel_nubia_sm8750.git](https://github.com/cmfnels/android_kernel_nubia_sm8750.git)
*   **Usage**: Extraction of the `msm_performance.h` header and other `soc/qcom` files.

### **D. Lineage Repository (MSM Mainline)**
Used to verify security commits and Android 16 integration.
*   **Link**: [https://git.codelinaro.org/clo/la/kernel/msm.git](https://git.codelinaro.org/clo/la/kernel/msm.git)

---

## 2. Extracted and Ported Components

To enable driver compilation in the GKI environment, the following files were manually integrated into the `graphics-kernel/compat/` directory:

1.  **`qcom-iommu-util.c`**: Refactored to support the new `iommu_get_resv_regions` structure.
2.  **`mem-buf_6.12.c`**: Updated version of the buffer manager compatible with Kernel 6.12 `class_create` APIs.
3.  **IOMMU Headers** (Extracted to `include/linux/`):
    *   `dma-mapping-fast.h`
    *   `io-pgtable-fast.h`
    *   `iommu-v8.h`

---

## 3. Main Technical Modifications

### **IOMMU (Kernel 6.12 API)**
*   **Change**: Kernel 6.12 removed the `iommu_ops` field from `struct bus_type`.
*   **Solution**: The driver was modified to use the exported `iommu_get_resv_regions(dev, list)` function, ensuring GKI compatibility.

### **Initialization Unification**
*   **Change**: Removed `module_init` and `arch_initcall` macros from auxiliary files.
*   **Solution**: IOMMU and Mem-Buf initialization are now called manually within the `kgsl_3d_init` function.

### **Section Mismatch Resolution**
*   **Change**: Linking errors occurred when attempting to call cleanup functions (`exit`) from error paths in initialization.
*   **Solution**: Removed `__exit` attributes from manual cleanup functions, allowing safe calls during boot.

---

## 4. Pending Tasks

Two steps remain for the driver to run on the device:

1.  **Module.symvers Generation**: A full kernel build (`kernel_platform/common`) is required to generate this symbol file.
2.  **Final Linking**: With `Module.symvers` available, the `make modules` command will complete the MODPOST.

---

## 5. Integration Strategy (Hybrid Approach)

Since ZTE did not provide source code for some critical components, a hybrid approach is **mandatory**, extracting original binaries from a **device backup (dump)**:
*   **WLAN (Wi-Fi)**: Extract `qca_cld3_wlan.ko`.
*   **Fan**: Extract `zte_fan.ko` (essential for RedMagic).

---

## 6. Implementation Guide (Step-by-Step for Reproduction)

### **Step 0: File Preparation**
Extract the following files from the CodeLinaro repository (`qclinux.6.12.y`):
1.  Copy `qcom-iommu-util.c` and `mem-buf_6.12.c` to `compat/`.
2.  Copy `dma-mapping-fast.h`, `io-pgtable-fast.h`, and `iommu-v8.h` to `kernel_platform/common/include/linux/`.
3.  Copy `msm_performance.h` (from Nubia) to `include/soc/qcom/`.

### **Step 1: GKI Macro Fix**
**File:** `kernel_platform/common/include/linux/android_vendor.h`
```c
#include <linux/android_kabi.h>
#define ANDROID_BACKPORT_RESERVED ANDROID_BACKPORT_RESERVE
```

### **Step 2: IOMMU Adaptation**
**File:** `compat/qcom-iommu-util.c`
```c
struct iommu_ops *ops = (struct iommu_ops *)iommu_get_resv_regions(dev, list);
```

### **Step 3: Kbuild Configuration**
**File:** `Kbuild`
```makefile
msm_kgsl-y += compat/mem-buf_6.12.o
```

### **Step 4: Initialization Hooks**
**File:** `adreno.c`
```c
// Declare externs and call manually in kgsl_3d_init()
qcom_iommu_util_init();
mem_buf_init();
```

### **Step 5: SCM Stubs**
**Files:** `adreno_sysfs.c` and `governor_msm_adreno_tz.c`
```c
static inline int qcom_scm_kgsl_dcvs_tuning(...) { return -EOPNOTSUPP; }
```

### **Step 6: Kernel 6.12 APIs**
**File:** `compat/mem-buf_6.12.c`
1.  Update `class_create` to 1 argument.
2.  Update `platform_driver.remove` to return `void`.

---

## 7. Compilation Command
```bash
export PATH="/home/adrianojr59/toolchains/linux-x86/clang-r547379/bin:${PATH}"
cd kernel_platform/common
make ARCH=arm64 LLVM=1 LLVM_IAS=1 O=out \
    M="../../vendor/qcom/opensource/graphics-kernel" \
    CONFIG_ARCH_CANOE=y \
    KGSL_PATH="../../vendor/qcom/opensource/graphics-kernel" \
    KBUILD_MODPOST_WARN=1 \
    modules
```

---
*Consolidated report by Antigravity AI on 05/03/2026.*
