/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _LINUX_IPC_LOGGING_H
#define _LINUX_IPC_LOGGING_H

#include <linux/types.h>

/* Stub for IPC logging */

static inline void *ipc_log_context_create(int pages, const char *name, uint16_t sub)
{
	return NULL;
}

static inline void ipc_log_context_destroy(void *ctxt)
{
}

#define ipc_log_string(ctxt, fmt, ...) do { (void)(ctxt); } while (0)

#endif /* _LINUX_IPC_LOGGING_H */
