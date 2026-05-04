/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _SYNX_API_H
#define _SYNX_API_H

#include <linux/types.h>

enum synx_client_id {
	SYNX_CLIENT_ID_DISPLAY = 0,
	SYNX_CLIENT_ID_MAX,
};

#define SYNX_HW_FENCE_FLAG_ENABLED_BIT 1

struct synx_initialization_params {
	enum synx_client_id id;
	u32 reserved;
};

struct synx_create_params {
	u32 *h_synx;
	u32 reserved;
};

struct synx_import_params {
	union {
		struct {
			u32 *new_h_synx;
		} indv;
	};
};

struct synx_hw_fence_hfi_queue_header {
	u32 reserved[16];
};

struct synx_hw_fence_hfi_queue_table_header {
	u32 reserved[16];
};

struct synx_session {
	void *client;
};

struct synx_queue_desc {
	u64 vaddr;
	u64 paddr;
	u32 size;
};

static inline void *synx_initialize(struct synx_initialization_params *params)
{
	return NULL;
}

static inline int synx_uninitialize(void *handle)
{
	return 0;
}

static inline int synx_create(void *handle, struct synx_create_params *params)
{
	return -EOPNOTSUPP;
}

static inline int synx_import(void *handle, struct synx_import_params *params)
{
	return -EOPNOTSUPP;
}

#endif /* _SYNX_API_H */
