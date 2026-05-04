/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _HDCP_QSEECOM_H
#define _HDCP_QSEECOM_H

#include <linux/types.h>

/* Stub for HDCP QSEECOM */

enum hdcp2_app_cmd {
	HDCP2_CMD_START,
	HDCP2_CMD_STOP,
	HDCP2_CMD_PROCESS_MSG,
	HDCP2_CMD_TIMEOUT,
};

static inline int hdcp2_app_comm(void *ctx, uint32_t cmd, void *msg, uint32_t msg_len)
{
	return -EOPNOTSUPP;
}

#endif /* _HDCP_QSEECOM_H */
