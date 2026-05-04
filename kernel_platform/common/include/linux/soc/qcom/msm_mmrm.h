/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _MSM_MMRM_H
#define _MSM_MMRM_H

#include <linux/types.h>

enum mmrm_client_type {
	MMRM_CLIENT_TYPE_DISPLAY,
	MMRM_CLIENT_CLOCK,
};

enum mmrm_client_domain {
	MMRM_CLIENT_DOMAIN_VIDEO,
	MMRM_CLIENT_DOMAIN_DISPLAY,
};

enum mmrm_client_priority {
	MMRM_CLIENT_PRIOR_LOW,
	MMRM_CLIENT_PRIOR_HIGH,
};

enum mmrm_cb_type {
	MMRM_CLIENT_RESOURCE_VALUE_CHANGE,
};

struct mmrm_client_notifier_data {
	enum mmrm_cb_type cb_type;
	union {
		struct {
			u64 new_val;
		} val_chng;
	} cb_data;
	void *pvt_data;
};

struct mmrm_client_desc {
	enum mmrm_client_type client_type;
	struct {
		struct {
			enum mmrm_client_domain client_domain;
			u32 client_id;
			char name[64];
			void *clk;
		} desc;
	} client_info;
	enum mmrm_client_priority priority;
	void *pvt_data;
	int (*notifier_callback_fn)(struct mmrm_client_notifier_data *data);
};

struct mmrm_client_data {
	u32 num_hw_blocks;
	u32 flags;
	u32 value;
};

struct mmrm_client;

static inline struct mmrm_client *mmrm_client_register(struct mmrm_client_desc *desc)
{
	return (struct mmrm_client *)1; // dummy handle
}

static inline int mmrm_client_deregister(struct mmrm_client *client)
{
	return 0;
}

static inline int mmrm_client_set_value(struct mmrm_client *client,
		struct mmrm_client_data *data, u64 rate)
{
	return 0;
}

static inline bool mmrm_client_check_scaling_supported(enum mmrm_client_type type,
	enum mmrm_client_domain domain)
{
	return false;
}

#define MMRM_CLIENT_DATA_FLAG_RESERVE_ONLY BIT(0)

#endif /* _MSM_MMRM_H */
