/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _PANEL_EVENT_NOTIFIER_H
#define _PANEL_EVENT_NOTIFIER_H

#include <linux/types.h>

struct panel_event_notification_data {
	u32 old_fps;
	u32 new_fps;
	void *client_data;
};

struct panel_event_notifier {
	struct notifier_block nb;
};

static inline void *panel_event_notifier_register(const char *name,
		struct notifier_block *nb)
{
	return NULL;
}

static inline void panel_event_notifier_unregister(void *handle,
		struct notifier_block *nb)
{
}

#endif /* _PANEL_EVENT_NOTIFIER_H */
