/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Stub header for qtee_shmbridge — GKI 6.12 compatibility
 * The QTEE shared memory bridge is not available in the vanilla GKI kernel.
 * These stubs allow the display driver to compile without TrustZone support.
 */
#ifndef _LINUX_QTEE_SHMBRIDGE_H
#define _LINUX_QTEE_SHMBRIDGE_H

#include <linux/types.h>

struct qtee_shm {
	phys_addr_t paddr;
	void *vaddr;
	size_t size;
};

static inline bool qtee_shmbridge_is_enabled(void)
{
	return false;
}

static inline int qtee_shmbridge_allocate_shm(size_t size, struct qtee_shm *shm)
{
	return -EOPNOTSUPP;
}

static inline void qtee_shmbridge_free_shm(struct qtee_shm *shm)
{
}

#endif /* _LINUX_QTEE_SHMBRIDGE_H */
