/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _SPMI_PMIC_ARB_H
#define _SPMI_PMIC_ARB_H

#include <linux/types.h>
#include <linux/device.h>

static inline int spmi_pmic_arb_map_address(struct device *dev, u32 sid,
		struct resource *res)
{
	if (!res)
		return -EINVAL;

	/* SM8750 SPMI Arbiter Base: 0x0c400000 */
	res->start = 0x0c400000 + sid;
	res->end = res->start + 0x1000 - 1; /* Dummy size */
	res->flags = IORESOURCE_MEM;
	return 0;
}

#endif /* _SPMI_PMIC_ARB_H */
