/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _MSM_GPIO_H
#define _MSM_GPIO_H

#include <linux/types.h>
#include <linux/ioport.h>

static inline int msm_gpio_get_pin_address(unsigned int gpio, struct resource *res)
{
	return -ENODEV;
}

#endif /* _MSM_GPIO_H */
