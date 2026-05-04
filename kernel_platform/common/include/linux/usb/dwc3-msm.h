/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _DWC3_MSM_H
#define _DWC3_MSM_H

#include <linux/types.h>
#include <linux/device.h>

static inline int dwc3_msm_set_dp_mode(struct device *dev, bool connect, int lanes)
{
	return 0;
}

#endif /* _DWC3_MSM_H */
