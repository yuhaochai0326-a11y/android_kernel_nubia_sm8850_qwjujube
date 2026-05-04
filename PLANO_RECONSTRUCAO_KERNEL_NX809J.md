# Plano de Reconstrução do Kernel — RedMagic 11 Pro (NX809J)

**Documento Técnico v1.0**  
**Data:** 03 de Maio de 2026  
**Autor:** Adriano Jr.  
**Dispositivo:** Nubia RedMagic 11 Pro (NX809J) — Codinome: Aston / qwjujube  
**SoC:** Qualcomm Canoe (SM8850 / Snapdragon 8 Elite)  
**GPU:** Adreno 840 (Gen8-2-0)  
**Kernel:** Linux 6.12.23 (GKI — Generic Kernel Image)  
**Android:** 16 (RedMagicOS 11.x)  

---

## 1. Visão Geral

Este documento descreve o plano técnico completo para reconstruir o kernel do RedMagic 11 Pro (NX809J) a partir do código-fonte GPL liberado pela ZTE/Nubia. O objetivo é manter a **máxima originalidade** do código, sem utilizar arquivos de outros dispositivos.

### 1.1 Origem do Código-Fonte

O código foi obtido do release oficial GPL da ZTE para o modelo NX809J, contendo:

- Kernel Linux 6.12.23 (base GKI do Google)
- Drivers proprietários da Qualcomm (open-source)
- Device Trees específicos do dispositivo (ZTE Aston / qwjujube)
- Configurações de hardware (GPU, Display, Câmera, Áudio, etc.)

### 1.2 Tamanho Total do Projeto

| Componente | Tamanho |
|---|---|
| Kernel Platform (GKI) | 1.7 GB |
| Kernel Prebuilts | 1.9 GB |
| Vendor (Drivers + DeviceTrees) | 296 MB |
| External (iproute2, iptables) | 9.9 MB |
| **Total** | **~3.9 GB** |

---

## 2. Inventário Completo do Código-Fonte

### 2.1 Componentes Presentes (✅)

#### Kernel Base
| Arquivo/Pasta | Descrição | Status |
|---|---|---|
| `kernel_platform/common/` | Código-fonte completo do Linux 6.12.23 | ✅ Completo |
| `kernel_platform/common/arch/arm64/configs/gki_defconfig` | Configuração base GKI | ✅ Presente |
| `kernel_platform/common/Makefile` | Makefile principal (VERSION=6, PATCHLEVEL=12, SUBLEVEL=23) | ✅ Presente |

#### Drivers da Qualcomm (vendor/qcom/opensource/)
| Driver | Pasta | Descrição |
|---|---|---|
| GPU (Adreno 840) | `graphics-kernel/` | Driver KGSL completo com suporte Gen8 |
| Display | `display-drivers/` | Driver DRM/SDE + código exclusivo ZTE (`zte_disp/`) |
| Câmera (Spectra) | `camera-kernel/` | ISP, ICP, JPEG, Sensor |
| Áudio | `audio-kernel/` | ASoC + config de portas Canoe |
| Vídeo (Codec) | `video-driver/` | Encoder/Decoder de vídeo |
| Touch | `touch-drivers/` | Drivers de touchscreen (PT, Raydium) |
| Bluetooth | `bt-kernel/` | Driver BT kernel |
| Wi-Fi (WLAN) | `wlan/` | Driver WLAN completo |
| SecureMSM | `securemsm-kernel/` | Módulos de segurança (QSEECOM, SMCInvoke) |
| MM-Drivers | `mm-drivers/` | hw_fence, sync_fence, msm_ext_display |
| DataIPA | `dataipa/` | Internet Protocol Accelerator |

#### Device Trees
| DeviceTree | Pasta | Descrição |
|---|---|---|
| GPU Canoe | `graphics-devicetree/gpu/canoe-gpu.dtsi` | Configuração Adreno 840 (freq: 160MHz–1050MHz) |
| Display Canoe | `display-devicetree/` | Painel `dsi_bf375_rm692h5_6p8_magic_dsc_cmd` |
| Câmera qwjujube | `camera-devicetree/zte-canoe-camera-sensor-qwjujube.dtsi` | 4 sensores (Principal+OIS, Wide, Front, Tele) |
| ZTE Aston (NX809J) | `proprietary/zte-devicetree/qwjujube/` | Overlay do dispositivo + ventoinha (fan) |
| Áudio | `audio-devicetree/` | Configuração de áudio Canoe |
| Bluetooth | `bt-devicetree/` | WCN7750 BT overlay |
| Wi-Fi | `wlan/wlan-devicetree/` | WLAN overlay Canoe |

#### Código Exclusivo ZTE/Nubia
| Componente | Arquivo | Descrição |
|---|---|---|
| Display ZTE | `display-drivers/msm/zte_disp/` | Backlight, features, panel info, reg debug |
| Bazel target qwjujube | `display-drivers/targets/zteqwjujube.bzl` | Build target exclusivo do NX809J |
| Ventoinha (Fan) | `zte-devicetree/qwjujube/zte-qwjujube-overlay.dtsi` | Controle PWM da ventoinha interna |

### 2.2 Componentes Ausentes (❌)

| Componente | Impacto | Solução |
|---|---|---|
| `Kconfig.ext` preenchido | 🔴 Crítico — sem `CONFIG_ARCH_CANOE`, drivers não compilam | **CORRIGIDO** — definição adicionada manualmente |
| Kbuild GPU para Canoe | 🔴 Crítico — GPU não seria compilada | **CORRIGIDO** — entrada adicionada |
| `vendor/qcom/opensource/core-utils/` | 🟡 Médio — link simbólico quebrado | Ignorável para build manual |
| Kleaf/Bazel build system (`kernel_platform/build/`) | 🟡 Médio — sistema de build automatizado | Substituído por script manual |
| Toolchain AOSP Clang | 🟡 Médio — compilador | Download do repositório oficial Google |

---

## 3. Especificações de Hardware Identificadas no Código

### 3.1 GPU — Adreno 840

```
Modelo:        Adreno 840 (qcom,adreno-gpu-gen8-2-0)
Chip ID:       0x44050a00
UBWC Mode:     6
Freq. Máxima:  1050 MHz (Turbo L1)
Freq. Nominal: 902 MHz
Freq. Mínima:  160 MHz (Low SVS D3)
Níveis:        17 power levels
Memória DDR:   Até 5333 MHz (TURBO_L5)
```

**Tabela de Frequências (Power Levels):**

| Nível | Nome | Frequência | Barramento DDR |
|---|---|---|---|
| 0 | Turbo L1 | 1050 MHz | 5333 MHz |
| 1 | Nom L1 | 967 MHz | 3187 MHz |
| 2 | Nominal | 902 MHz | 3187 MHz |
| 3 | SVS L2 | 826 MHz | 3187 MHz |
| 4 | SVS L1 | 726 MHz | 2092 MHz |
| 5 | SVS L0 | 646 MHz | 2092 MHz |
| 6 | SVS | 578 MHz | 1555 MHz |
| 7 | Low SVS L2 | 539 MHz | 1555 MHz |
| 8 | Low SVS L1 | 500 MHz | 1555 MHz |
| 9 | Low SVS L0 | 461 MHz | 1555 MHz |
| 10 | Low SVS | 422 MHz | 1555 MHz |
| 11 | Low SVS D0 | 382 MHz | 1353 MHz |
| 12 | Low SVS D1 | 342 MHz | 1353 MHz |
| 13 | Low SVS D1_1 | 282 MHz | 1353 MHz |
| 14 | Low SVS D2 | 222 MHz | 1353 MHz |
| 15 | Low SVS D2_1 | 191 MHz | 1353 MHz |
| 16 | Low SVS D3 | 160 MHz | 547 MHz |

### 3.2 Display

```
Painel:     dsi_bf375_rm692h5_6p8_magic_dsc_cmd
Tamanho:    6.8 polegadas
Tipo:       DSI, DSC (Display Stream Compression), CMD mode
```

### 3.3 Câmeras (4 sensores)

| Sensor | Tipo | Interface | Recursos |
|---|---|---|---|
| cam-sensor0 | Traseira Principal | CSIPHY 2, CCI Master 1 | Flash LED, Atuador AF, OIS, EEPROM |
| cam-sensor1 | Frontal | CSIPHY 3, CCI Master 0 | EEPROM |
| cam-sensor2 | Traseira Wide | CSIPHY 1, CCI Master 0 | Flash LED, EEPROM |
| cam-sensor3 | Traseira Tele/Macro | CSIPHY 0, CCI Master 0 | — |

### 3.4 Sistema de Refrigeração (Ventoinha)

```
Driver:       soc,fan
Controle:     PWM (fan_pwm)
Velocidade:   fan_speed (configurável)
Modos:        16 modos por configuração (fan_modex_count)
Alimentação:  pmh0101_l8 (fan,avdd-supply)
```

---

## 4. Estratégia de Compilação

### 4.1 Abordagem: Módulos Externos (Out-of-Tree)

A compilação utiliza a abordagem de **módulos out-of-tree**, que é exatamente como a ZTE/Nubia compila na fábrica. Os drivers são compilados como módulos `.ko` separados, carregados pelo sistema durante o boot.

**Justificativa:**
- Preserva 100% da originalidade do código GKI
- Cada driver tem seu próprio `Kbuild` já preparado para isso
- `CONFIG_QCOM_KGSL = m` (módulo) já definido nos configs Canoe
- Facilita a substituição individual de módulos

### 4.2 Dependências do Sistema

```bash
sudo apt install -y build-essential bc bison flex libssl-dev \
    libelf-dev python3 python3-pip git curl wget \
    lz4 zstd device-tree-compiler cpio
```

### 4.3 Toolchain

```
Compilador:   AOSP Clang r522858
Origem:       https://android.googlesource.com/platform/prebuilts/clang/host/linux-x86
Branch:       android-16.0.0_r1
Arquitetura:  ARCH=arm64, LLVM=1, LLVM_IAS=1
```

### 4.4 Fluxo de Compilação

```
┌─────────────────────────────────────────┐
│         1. KERNEL BASE (GKI)            │
│  make gki_defconfig + CONFIG_ARCH_CANOE │
│  make Image                             │
│  Resultado: arch/arm64/boot/Image       │
└──────────────────┬──────────────────────┘
                   │
┌──────────────────▼──────────────────────┐
│       2. MÓDULOS VENDOR (out-of-tree)   │
│  GPU → msm_kgsl.ko                     │
│  Display → msm_drm.ko                  │
│  Câmera → camera.ko                    │
│  Áudio → audio.ko                      │
│  BT, WLAN, Touch, Video, etc.          │
└──────────────────┬──────────────────────┘
                   │
┌──────────────────▼──────────────────────┐
│         3. DEVICE TREES                 │
│  GPU → canoe-gpu.dtbo                  │
│  Display → canoe-sde.dtbo             │
│  ZTE → zte-qwjujube-overlay.dtbo      │
│  Câmera → zte-canoe-camera-*.dtbo     │
└──────────────────┬──────────────────────┘
                   │
┌──────────────────▼──────────────────────┐
│         4. EMPACOTAMENTO                │
│  Image + DTBs → boot.img               │
│  Módulos .ko → vendor_dlkm             │
└─────────────────────────────────────────┘
```

### 4.5 Comandos de Compilação

#### Kernel Base
```bash
cd kernel_platform/common
make O=out gki_defconfig
echo "CONFIG_ARCH_CANOE=y" >> out/.config
make O=out -j$(nproc) Image
```

#### Módulos (exemplo: GPU)
```bash
make -C kernel_platform/common O=out \
    M=../../vendor/qcom/opensource/graphics-kernel \
    CONFIG_ARCH_CANOE=y \
    modules
```

#### Script Automatizado
Um script `build_nx809j.sh` foi criado na raiz do projeto que automatiza todos os passos acima.

---

## 5. Correções Aplicadas ao Código

### 5.1 Kconfig.ext (CRÍTICO)

**Arquivo:** `kernel_platform/common/Kconfig.ext`  
**Problema:** Arquivo era um placeholder vazio, fazendo com que `CONFIG_ARCH_CANOE` não fosse reconhecido.

**Correção aplicada:**
```diff
 # SPDX-License-Identifier: GPL-2.0
-# This file is intentionally empty. It's used as a placeholder for when
-# KCONFIG_EXT_PREFIX isn't defined.
+# Platform extensions for Qualcomm Canoe (SM8850 / Snapdragon 8 Elite)
+
+config ARCH_CANOE
+	bool "Qualcomm Technologies, Inc. Canoe (SM8850)"
+	depends on ARCH_QCOM
+	help
+	  Support for the Qualcomm Canoe (SM8850) SoC platform.
+	  This is used by the RedMagic 11 Pro (NX809J) and related devices.
```

### 5.2 Kbuild GPU (CRÍTICO)

**Arquivo:** `vendor/qcom/opensource/graphics-kernel/Kbuild`  
**Problema:** Não havia entrada para `CONFIG_ARCH_CANOE`, impedindo a compilação do driver Adreno 840.

**Correção aplicada:**
```diff
 ifeq ($(CONFIG_ARCH_SM6150), y)
 	include $(KGSL_PATH)/config/gki_sm6150.conf
 	subdir-ccflags-y += $(LE_EXTRA_CFLAGS)
 endif
+ifeq ($(CONFIG_ARCH_CANOE), y)
+	include $(KGSL_PATH)/config/canoe_consolidate_gpuconf
+endif
```

---

## 6. Teste e Validação

### 6.1 Teste Seguro (Sem Gravar no Dispositivo)

```bash
# Carrega o kernel na RAM sem gravar na memória interna
fastboot boot new_boot.img
```

Se o dispositivo não iniciar, basta forçar o desligamento (Power + Volume) e religar — o kernel original permanece intacto.

### 6.2 Checklist de Validação

| Componente | Teste | Comando de Verificação |
|---|---|---|
| Boot | Dispositivo liga normalmente | Visual |
| Wi-Fi | Conecta a uma rede | `adb shell ip addr show wlan0` |
| Bluetooth | Detecta dispositivos | Configurações → Bluetooth |
| Câmera | Abre e tira foto | App de câmera |
| Som | Reproduz áudio | Tocar música |
| Touch | Responde ao toque | Uso normal |
| GPU | Jogo roda sem artefatos | Rodar um jogo 3D |
| Ventoinha | Liga em carga pesada | Benchmark |
| Display | Sem flickering ou artefatos | Visual |

### 6.3 Recuperação de Emergência (EDL 9008)

Em caso de brick total, o dispositivo pode ser recuperado via modo EDL (Emergency Download):
1. Desligar o dispositivo
2. Segurar combinação de botões para entrar em EDL
3. Conectar ao PC via USB
4. Usar QFIL ou ferramenta da ZTE para gravar firmware stock

**Firmwares de recuperação disponíveis em:** `yhcres.top` (pacotes de 10-15 GB)

---

## 7. Arquivos de Referência

### 7.1 Estrutura do Projeto

```
NX809J_Android16_kernel(6.12.23)/
├── build_nx809j.sh                    ← Script de build automatizado
├── kernel_platform/
│   └── common/                        ← Kernel Linux 6.12.23 (GKI)
│       ├── Kconfig.ext                ← CORRIGIDO (CONFIG_ARCH_CANOE)
│       ├── Makefile                   ← VERSION=6, PATCHLEVEL=12, SUBLEVEL=23
│       └── arch/arm64/configs/
│           └── gki_defconfig          ← Configuração base
├── vendor/
│   └── qcom/
│       ├── opensource/
│       │   ├── graphics-kernel/       ← GPU Adreno 840
│       │   │   ├── Kbuild             ← CORRIGIDO (suporte Canoe)
│       │   │   └── config/
│       │   │       └── canoe_*        ← Configs da GPU Canoe
│       │   ├── display-drivers/       ← Display + zte_disp/
│       │   ├── camera-kernel/         ← Câmera Spectra
│       │   ├── audio-kernel/          ← Áudio
│       │   ├── bt-kernel/             ← Bluetooth
│       │   ├── wlan/                  ← Wi-Fi
│       │   ├── video-driver/          ← Codec de Vídeo
│       │   ├── touch-drivers/         ← Touchscreen
│       │   ├── securemsm-kernel/      ← Segurança
│       │   ├── mm-drivers/            ← Multimídia
│       │   ├── dataipa/               ← Data IPA
│       │   ├── graphics-devicetree/   ← DT GPU
│       │   ├── display-devicetree/    ← DT Display
│       │   ├── camera-devicetree/     ← DT Câmera
│       │   └── audio-devicetree/      ← DT Áudio
│       └── proprietary/
│           └── zte-devicetree/        ← DT específico NX809J
│               └── qwjujube/          ← Overlay Aston (NX809J)
├── kernel/
│   ├── prebuilts/6.12/                ← Kernel precompilado de referência
│   └── configs/                       ← Configs padrão Android
└── external/
    ├── iproute2/                      ← Ferramentas de rede
    └── iptables/                      ← Firewall
```

---

## 8. Recursos Externos

| Recurso | URL | Descrição |
|---|---|---|
| SourceForge NX809J | `sourceforge.net/projects/redmagic-11-pro-nx809j/` | Kernels modificados, EDL tools |
| YHC Resources | `yhcres.top` | Firmwares stock, pacotes EDL 9008 |
| Telegram RedMagic | `t.me/nubiaredmagic` | Comunidade de desenvolvedores |
| XDA Forums | `xdaforums.com` | Discussões técnicas |
| AOSP Clang | `android.googlesource.com/platform/prebuilts/clang/host/linux-x86` | Toolchain oficial |

---

## 9. ANÁLISE FORENSE PROFUNDA (Revisão Crítica)

> **Esta seção foi adicionada após uma segunda varredura exaustiva do código-fonte, verificando cada driver, dependência cruzada, arquivo de configuração e link simbólico do projeto.**

### 9.1 🔴 PROBLEMA CRÍTICO: Driver WLAN Ausente

| Item | Detalhe |
|---|---|
| **Problema** | O driver Wi-Fi (`vendor/qcom/opensource/wlan/`) contém **0 arquivos .c** (código-fonte) |
| **O que tem** | Apenas 3.357 arquivos `.h` (headers) na pasta `fw-api/` |
| **O que falta** | O driver principal `qcacld-3.0` ou `qcacmn` (código compilável) |
| **Impacto** | 🔴 **FATAL** — Sem este driver, o Wi-Fi simplesmente NÃO funciona |
| **Solução** | Os módulos WLAN `.ko` devem vir pré-compilados do firmware stock (extrair do `vendor_dlkm`) |

**Contagem de arquivos .c por driver (auditoria completa):**

| Driver | Arquivos .c | Arquivos .h | Status |
|---|---|---|---|
| audio-kernel | 162 | 197 | ✅ Completo |
| camera-kernel | 208 | 384 | ✅ Completo |
| display-drivers | 197 | 231 | ✅ Completo |
| graphics-kernel (GPU) | 85 | 82 | ✅ Completo |
| video-driver | 68 | 72 | ✅ Completo |
| touch-drivers | 84 | 57 | ✅ Completo |
| dataipa | 78 | 91 | ✅ Completo |
| securemsm-kernel | 29 | 71 | ✅ Completo |
| mm-drivers | 20 | 22 | ✅ Completo |
| bt-kernel | 17 | 22 | ✅ Completo |
| **wlan** | **0** | **3.357** | **❌ SÓ HEADERS** |

---

### 9.2 🔴 PROBLEMA CRÍTICO: 8 Drivers de Hardware ZTE/Nubia Ausentes

O device tree do NX809J (`zte-qwjujube-overlay.dtsi`) referencia 10 drivers via `compatible`. Apenas 2 existem na árvore de código. Os outros 8 estão **completamente ausentes**:

| # | Driver | `compatible` | Existe no Código? | Função |
|---|---|---|---|---|
| 1 | GPIO Nubia | `nubia_hw_gpio_ctrl` | ❌ **NÃO** | Controle de GPIOs da Nubia (botões gaming) |
| 2 | Touch ZTE | `zte_tp` | ❌ **NÃO** | Touch panel proprietário da ZTE |
| 3 | Haptic Awinic | `awinic,haptic_hv` | ❌ **NÃO** | Motor de vibração/haptic feedback |
| 4 | Fingerprint Goodix | `goodix,fingerprint` | ❌ **NÃO** | Leitor de impressão digital |
| 5 | Ventoinha (Fan) | `soc,fan` | ❌ **NÃO** | Controle da ventoinha RedMagic |
| 6 | Smart PA Awinic | `awinic,aw882xx_smartpa` | ⚠️ **Parcial** (apenas headers em audio-kernel) | Alto-falante inteligente |
| 7 | Infravermelho ZTE | `zte,zte_ir` | ❌ **NÃO** | Emissor infravermelho |
| 8 | LED Awinic | `awinic,aw22xxx_led` | ❌ **NÃO** | LEDs RGB gaming |
| 9 | NFC ST | `st,st21nfc` | ✅ **SIM** (no kernel base) | Chip NFC |
| 10 | Touch Synaptics | `synaptics,tcm-spi` | ✅ **SIM** (em touch-drivers) | Touch alternativo |

**Impacto:** Esses drivers são proprietários da ZTE/Nubia e **não foram incluídos no release GPL**. Eles provavelmente são compilados separadamente e distribuídos como módulos `.ko` pré-compilados dentro da partição `vendor` do firmware stock.

**Solução:** Extrair os módulos `.ko` do firmware original (da partição `vendor_dlkm` ou `vendor`) e usar como estão. Não é possível recompilar esses drivers sem o código-fonte.

---

### 9.3 🟡 ALERTA: Conflito de Merge no Driver GPU

| Item | Detalhe |
|---|---|
| **Arquivo** | `vendor/qcom/opensource/graphics-kernel/adreno_gen8.c.conflicted` |
| **O que é** | Uma cópia do driver GPU Gen8 com marcadores de conflito de merge do Git |
| **Tamanho** | 112.225 bytes (vs. 112.097 bytes do arquivo principal `adreno_gen8.c`) |
| **Risco** | 🟡 Se alguém editou o `.c` principal manualmente para resolver o conflito, pode haver um bug introduzido |
| **Ação** | Comparar ambos os arquivos com `diff adreno_gen8.c adreno_gen8.c.conflicted` antes de compilar |

---

### 9.4 🟢 DESCOBERTA POSITIVA: Kernel GKI Pré-compilado Disponível

**Você não PRECISA compilar o kernel base do zero se não quiser modificá-lo.** A pasta `kernel/prebuilts/6.12/arm64/` contém:

| Arquivo | Tamanho | Descrição |
|---|---|---|
| `kernel-6.12` | 37 MB | Image GKI pré-compilada (raw) |
| `kernel-6.12-gz` | 15 MB | Image comprimida com gzip |
| `kernel-6.12-lz4` | 17 MB | Image comprimida com LZ4 |
| `kernel-6.12-allsyms` | 41 MB | Image com todos os símbolos (debug) |
| `System.map` | — | Mapa de símbolos |
| `abi_symbollist` | 465 KB | Lista de símbolos ABI (KMI) |
| 121 módulos `.ko` | Vários | Módulos base do kernel GKI |

**O que isso significa:**
- Se o seu objetivo é apenas modificar um driver (ex.: overclock da GPU), você pode usar a Image GKI pré-compilada e recompilar **APENAS** o módulo da GPU (`msm_kgsl.ko`).
- Isso é MUITO mais rápido e seguro do que compilar o kernel inteiro.

---

### 9.5 Identificação do Dispositivo (Board ID)

Extraído do device tree overlay oficial:

```
model     = "Qualcomm Technologies, Inc. Canoe MTP + ST54L + Kundu, zte board qwjujube"
qcom,msm-id  = <660 0x10000>, <660 0x20000>, <661 0x10000>, <661 0x20000>
qcom,board-id = <8 0>
```

| Campo | Valor | Significado |
|---|---|---|
| `msm-id 660` | SM8850 (Canoe) | Snapdragon 8 Elite |
| `msm-id 661` | Variante SM8850 | Possível SKU diferente (Pro+?) |
| `board-id 8` | MTP | Mobile Test Platform |
| `ST54L` | NFC Chip | STMicroelectronics ST54L |
| `Kundu` | Modem | Nome do modem Qualcomm |
| `qwjujube` | Board name | Codinome interno ZTE (NX809J) |

---

### 9.6 Resumo de Risco por Componente

| Componente | Risco na Compilação | Risco no Boot | Solução |
|---|---|---|---|
| Kernel GKI (Image) | 🟢 Baixo | 🟢 Baixo | Usar pré-compilado ou compilar do fonte |
| GPU (msm_kgsl.ko) | 🟢 Baixo | 🟡 Médio | Compilar do fonte (código completo) |
| Display (msm_drm.ko) | 🟢 Baixo | 🟡 Médio | Compilar do fonte (código completo) |
| Câmera | 🟢 Baixo | 🟢 Baixo | Compilar do fonte |
| Áudio | 🟡 Médio | 🟡 Médio | Compilar, mas aw882xx pode faltar |
| Wi-Fi (WLAN) | 🔴 **IMPOSSÍVEL** | 🔴 **SEM WI-FI** | Extrair .ko do firmware stock |
| Bluetooth | 🟢 Baixo | 🟢 Baixo | Compilar do fonte |
| Touch | 🟢 Baixo | 🟢 Baixo | Compilar do fonte |
| Ventoinha (Fan) | 🔴 **IMPOSSÍVEL** | 🟡 Sem ventoinha | Extrair .ko do firmware stock |
| Fingerprint | 🔴 **IMPOSSÍVEL** | 🟡 Sem biometria | Extrair .ko do firmware stock |
| Haptic (Vibração) | 🔴 **IMPOSSÍVEL** | 🟡 Sem vibração | Extrair .ko do firmware stock |
| LED Gaming | 🔴 **IMPOSSÍVEL** | 🟡 Sem LED RGB | Extrair .ko do firmware stock |
| Infravermelho | 🔴 **IMPOSSÍVEL** | 🟡 Sem IR | Extrair .ko do firmware stock |

---

### 9.7 Estratégia Revisada: Abordagem Híbrida

Com base nesta análise profunda, a estratégia de reconstrução deve ser **HÍBRIDA**:

1. **Kernel GKI**: Usar o pré-compilado (`kernel-6.12`) ou compilar do fonte se precisar de modificações no base
2. **Drivers com código-fonte completo**: Compilar out-of-tree (GPU, Display, Câmera, BT, Touch, Vídeo, DataIPA, SecureMSM, MM-Drivers)
3. **Drivers sem código-fonte**: Extrair os módulos `.ko` pré-compilados do firmware stock (WLAN, Fan, Fingerprint, Haptic, LED, IR, GPIO Nubia)
4. **Device Trees**: Compilar usando os `.dtsi` que existem (GPU, Display, Câmera, Áudio, ZTE overlay)
5. **Empacotamento**: Montar `boot.img` + `vendor_dlkm.img` combinando os módulos compilados e os extraídos

### 9.8 Procedimento para Extrair Módulos do Firmware Stock

```bash
# 1. Baixar o firmware stock do yhcres.top ou EDL package
# 2. Extrair a partição vendor_dlkm
simg2img vendor_dlkm.img vendor_dlkm_raw.img
mkdir vendor_dlkm_mount
mount -o ro vendor_dlkm_raw.img vendor_dlkm_mount/

# 3. Copiar os módulos .ko que precisamos
cp vendor_dlkm_mount/lib/modules/*/wlan*.ko    modules_stock/
cp vendor_dlkm_mount/lib/modules/*/goodix*.ko  modules_stock/
cp vendor_dlkm_mount/lib/modules/*/aw882xx*.ko modules_stock/
cp vendor_dlkm_mount/lib/modules/*/fan*.ko     modules_stock/
cp vendor_dlkm_mount/lib/modules/*/haptic*.ko  modules_stock/
cp vendor_dlkm_mount/lib/modules/*/zte_*.ko    modules_stock/

# 4. Desmontar
umount vendor_dlkm_mount
```

---

*Documento atualizado em 03/05/2026. Análise forense profunda concluída. Todos os dados técnicos foram extraídos diretamente dos arquivos de código-fonte do kernel.*

