# SM8750 (Snapdragon 8 Elite) Hardware Reference

For developers contributing to the RedMagic 11 Pro (NX809J) kernel effort, use the following verified hardware mapping:

### GPU & Graphics (Adreno 840)
- **GPU Base**: `0x03D00000`
- **GMU Base**: `0x03D37000`
- **GPU SMMU**: `0x03DA0000`
- **Available Frequencies**: 160MHz to 1200MHz (18 levels).
  *   *Max*: 1.2 GHz
  *   *Min*: 160 MHz

### RedMagic 11 Pro Hardware Pins
- **TE (Tearing Effect)**: GPIO 86
- **Reset**: GPIO 98
- **Fingerprint (Goodix)**: SPI/QUP linked to MDSS Panel.
  - LCD State Notifier: Required for FOD (Fingerprint on Display).

### DSI Timings (Verified)
| Mode | Framerate | H-Active | V-Active |
|------|-----------|----------|----------|
| 0    | 60 Hz     | 1216     | 2688     |
| 1    | 90 Hz     | 1216     | 2688     |
| 2    | 120 Hz    | 1216     | 2688     |
| 3    | 144 Hz    | 1216     | 2688     |

*Extracted from live hardware via ADB root forensics.*
