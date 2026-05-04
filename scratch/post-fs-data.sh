#!/system/bin/sh
MODDIR=${0%/*}
mount --bind $MODDIR/system/vendor/lib/modules/msm_drm.ko /vendor/lib/modules/msm_drm.ko
mount --bind $MODDIR/system/vendor/lib/modules/msm_kgsl.ko /vendor/lib/modules/msm_kgsl.ko
