/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _WCD939X_I2C_H
#define _WCD939X_I2C_H

#include <linux/types.h>

enum wcd_usbss_cable_status {
	WCD_USBSS_CABLE_DISCONNECT,
	WCD_USBSS_CABLE_CONNECT,
};

enum wcd_usbss_cable_types {
	WCD_USBSS_DP_AUX_CC1,
	WCD_USBSS_DP_AUX_CC2,
};

static inline int wcd_usbss_switch_update(enum wcd_usbss_cable_types event,
		enum wcd_usbss_cable_status status)
{
	return 0;
}

static inline int wcd_usbss_reg_notifier(struct notifier_block *nb)
{
	return 0;
}

static inline int wcd_usbss_unreg_notifier(struct notifier_block *nb)
{
	return 0;
}

#endif /* _WCD939X_I2C_H */
