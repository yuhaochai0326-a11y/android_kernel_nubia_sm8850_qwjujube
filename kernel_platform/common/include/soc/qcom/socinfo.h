/* SPDX-License-Identifier: GPL-2.0 */

#ifndef __QCOM_SOCINFO_H__
#define __QCOM_SOCINFO_H__

#include <linux/types.h>

/*
 * SMEM item id, used to acquire handles to respective
 * SMEM region.
 */
#define SMEM_HW_SW_BUILD_ID		137

#define SMEM_SOCINFO_BUILD_ID_LENGTH	32
#define SMEM_SOCINFO_CHIP_ID_LENGTH	32

/*
 * SoC version type with major number in the upper 16 bits and minor
 * number in the lower 16 bits.
 */
#define SOCINFO_MAJOR(ver) (((ver) >> 16) & 0xffff)
#define SOCINFO_MINOR(ver) ((ver) & 0xffff)
#define SOCINFO_VERSION(maj, min)  ((((maj) & 0xffff) << 16)|((min) & 0xffff))

/* Socinfo SMEM item structure */
struct socinfo {
	__le32 fmt;
	__le32 id;
	__le32 ver;
	char build_id[SMEM_SOCINFO_BUILD_ID_LENGTH];
	/* Version 2 */
	__le32 raw_id;
	__le32 raw_ver;
	/* Version 3 */
	__le32 hw_plat;
	/* Version 4 */
	__le32 plat_ver;
	/* Version 5 */
	__le32 accessory_chip;
	/* Version 6 */
	__le32 hw_plat_subtype;
	/* Version 7 */
	__le32 pmic_model;
	__le32 pmic_die_rev;
	/* Version 8 */
	__le32 pmic_model_1;
	__le32 pmic_die_rev_1;
	__le32 pmic_model_2;
	__le32 pmic_die_rev_2;
	/* Version 9 */
	__le32 foundry_id;
	/* Version 10 */
	__le32 serial_num;
	/* Version 11 */
	__le32 num_pmics;
	__le32 pmic_array_offset;
	/* Version 12 */
	__le32 chip_family;
	__le32 raw_device_family;
	__le32 raw_device_num;
	/* Version 13 */
	__le32 nproduct_id;
	char chip_id[SMEM_SOCINFO_CHIP_ID_LENGTH];
	/* Version 14 */
	__le32 num_clusters;
	__le32 ncluster_array_offset;
	__le32 num_subset_parts;
	__le32 nsubset_parts_array_offset;
	/* Version 15 */
	__le32 nmodem_supported;
	/* Version 16 */
	__le32  feature_code;
	__le32  pcode;
	__le32  npartnamemap_offset;
	__le32  nnum_partname_mapping;
	/* Version 17 */
	__le32 oem_variant;
	/* Version 18 */
	__le32 num_kvps;
	__le32 kvps_offset;
	/* Version 19 */
	__le32 num_func_clusters;
	__le32 boot_cluster;
	__le32 boot_core;
	/* Version 20 */
	__le32 raw_package_type;
	/* Version 21, 22, 23 */
	__le32 reserve1[4];
};

/* Internal feature codes */
enum qcom_socinfo_feature_code {
	/* External feature codes */
	SOCINFO_FC_UNKNOWN = 0x0,
	SOCINFO_FC_AA,
	SOCINFO_FC_AB,
	SOCINFO_FC_AC,
	SOCINFO_FC_AD,
	SOCINFO_FC_AE,
	SOCINFO_FC_AF,
	SOCINFO_FC_AG,
	SOCINFO_FC_AH,
};

/* Internal feature codes */
/* Valid values: 0 <= n <= 0xf */
#define SOCINFO_FC_Yn(n)		(0xf1 + (n))
#define SOCINFO_FC_INT_MAX		SOCINFO_FC_Yn(0xf)

/* Product codes */
#define SOCINFO_PC_UNKNOWN		0
#define SOCINFO_PCn(n)			((n) + 1)
#define SOCINFO_PC_RESERVE		(BIT(31) - 1)

#define SOCINFO_PCODE_UNKNOWN   SOCINFO_PC_UNKNOWN

/* Part identifiers */
#define SOCINFO_PART_GPU        1

/* Feature codes */
#define SOCINFO_FC_W0           0x2
#define SOCINFO_FC_Y0           0x3
#define SOCINFO_FC_INT_RESERVE  0x4
#define SOCINFO_FC_SUBPART_RESERVE 0x5

static inline int socinfo_get_feature_code(void)
{
	return SOCINFO_FC_UNKNOWN;
}

static inline int socinfo_get_pcode(void)
{
	return SOCINFO_PCODE_UNKNOWN;
}

static inline u32 socinfo_get_partinfo_chip_id(u32 part)
{
	return 0;
}

static inline const char *socinfo_get_partinfo_part_name(u32 part)
{
	return NULL;
}

static inline u32 socinfo_get_partinfo_vulkan_id(u32 part)
{
	return 0;
}

enum socinfo_part {
	PART_DISPLAY = 1,
};

static inline u32 socinfo_get_id(void)
{
	return 660; /* SM8750 (Canoe) */
}

static inline u32 socinfo_get_version(void)
{
	return SOCINFO_VERSION(2, 0); /* V2 Silicon */
}

static inline bool socinfo_get_part_info(enum socinfo_part part)
{
	if (part == PART_DISPLAY)
		return true;
	return false;
}

static inline u32 socinfo_get_part_count(enum socinfo_part part)
{
	if (part == PART_DISPLAY)
		return 1;
	return 0;
}

static inline int socinfo_get_subpart_info(enum socinfo_part part,
		void *info, u32 count)
{
	return -ENODEV;
}

#endif
