/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _ALTMODE_GLINK_H
#define _ALTMODE_GLINK_H

#include <linux/types.h>

struct altmode_client;

static inline struct altmode_client *altmode_client_register(struct device *dev,
		void *cb, void *priv)
{
	return NULL;
}

static inline void altmode_client_unregister(struct altmode_client *amclient)
{
}

#endif /* _ALTMODE_GLINK_H */
