/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _QCOM_PINCTRL_H
#define _QCOM_PINCTRL_H

#include <linux/types.h>
#include <linux/ioport.h>

static inline bool msm_gpio_get_pin_address(unsigned int gpio, struct resource *res)
{
	if (!res)
		return false;

	/* SM8750 TLMM Base: 0x0f000000. Each GPIO has 0x1000 bytes space. */
	res->start = 0x0f000000 + (0x1000 * gpio);
	res->end = res->start + 0x1000 - 1;
	res->flags = IORESOURCE_MEM;
	return true;
}

#endif /* _QCOM_PINCTRL_H */
