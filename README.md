# RedMagic 11 Pro (NX809J) Kernel Stabilization — Android 16 (GKI 6.12)

This repository contains the ongoing effort to stabilize the Linux 6.12 GKI kernel for the **Nubia RedMagic 11 Pro** (Snapdragon 8 Elite / SM8750).

## Project Status: 🟢 Display Driver Stable
We have successfully mapped the proprietary hardware blocks of the Snapdragon 8 Elite and stabilized the `msm_drm.ko` driver.

### Key Achievements:
- **Hardware Mapping**: Real physical addresses identified for TLMM (GPIO), SPMI (PMIC), and GPU (Adreno 840).
- **Display Fixes**: 
  - Bypassed TE (Tearing Effect) register restore crashes using real physical offsets.
  - Stabilized PMIC arbiter mapping for backlight control.
  - Implemented real SoC Identification (ID 660) and Silicon Revision (2.0) detection.
- **144Hz Support**: Extracted and verified panel timings for 60Hz, 90Hz, 120Hz, and 144Hz modes from live hardware.

## Hardware Reference (SM8750)
| Block | Address | Notes |
|-------|---------|-------|
| **MDSS (Display)** | `0x09800000` | Main Multimedia Subsystem |
| **TLMM (GPIO)** | `0x0F000000` | GPIO 86 (TE) / GPIO 98 (Reset) |
| **SPMI Arbiter**| `0x0C400000` | PMIC Control |
| **GPU Adreno** | `0x03D00000` | Adreno 840 Base |
| **GMU (GPU)** | `0x03D37000` | Graphics Management Unit |

## Repository Structure
- `vendor/qcom/opensource/display-drivers/`: Stabilized display driver source.
- `kernel_platform/common/include/`: Modified GKI headers with hardware stubs.
- `STABILIZATION_PATCHES.md`: Consolidated diffs for applying these changes to other trees.
- `AUDITORIA_FORENSE_DISPLAY.md`: Detailed forensic analysis of the stabilization process.

## How to Build (Display Module Only)
```bash
./scratch/build_display_only.sh
```

## Credits
- **Kernel Version**: 6.12 (GKI)
- **Target Platform**: Snapdragon 8 Elite (SM8750)
- **Device**: RedMagic 11 Pro (NX809J)
