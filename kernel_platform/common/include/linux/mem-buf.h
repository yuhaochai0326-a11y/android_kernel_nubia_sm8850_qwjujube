/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2020-2021, The Linux Foundation. All rights reserved.
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 *
 * Simplified header for out-of-tree module compilation.
 * Only includes the APIs used by the graphics-kernel (kgsl) driver.
 */
#ifndef _LINUX_MEM_BUF_H
#define _LINUX_MEM_BUF_H

#include <linux/types.h>
#include <linux/dma-buf.h>

struct mem_buf_vmperm;

/* Returns true if the local VM has exclusive access and is the owner */
bool mem_buf_dma_buf_exclusive_owner(struct dma_buf *dmabuf);

/*
 * Returns a copy of the Virtual Machine vmids & permissions of the dmabuf.
 * The caller must kfree() when finished.
 */
int mem_buf_dma_buf_copy_vmperm(struct dma_buf *dmabuf, int **vmids, int **perms,
		int *nr_acl_entries);

#endif /* _LINUX_MEM_BUF_H */
