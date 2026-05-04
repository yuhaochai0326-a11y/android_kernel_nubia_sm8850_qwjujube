/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _SOC_QCOM_MINIDUMP_H
#define _SOC_QCOM_MINIDUMP_H

#include <linux/types.h>

/* Stub for Qualcomm Minidump */

struct md_region {
	char name[16];
	u64 address;
	u64 size;
};

static inline int msm_minidump_add_region(const struct md_region *region)
{
	return 0;
}

static inline int msm_minidump_remove_region(const struct md_region *region)
{
	return 0;
}

#endif /* _SOC_QCOM_MINIDUMP_H */
