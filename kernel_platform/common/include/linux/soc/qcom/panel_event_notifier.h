/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _PANEL_EVENT_NOTIFIER_H
#define _PANEL_EVENT_NOTIFIER_H

#include <linux/types.h>
#include <linux/notifier.h>

enum {
	DRM_PANEL_EVENT_BLANK,
	DRM_PANEL_EVENT_UNBLANK,
	DRM_PANEL_EVENT_BLANK_LP,
	DRM_PANEL_EVENT_FPS_CHANGE,
};

enum panel_event_notifier_tag {
	PANEL_EVENT_NOTIFICATION_PRIMARY,
	PANEL_EVENT_NOTIFICATION_SECONDARY,
};

struct panel_event_notification_data {
	u32 old_fps;
	u32 new_fps;
	bool early_trigger;
	void *client_data;
};

struct panel_event_notification {
	u32 notif_type;
	void *panel;
	struct panel_event_notification_data notif_data;
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

static inline void panel_event_notification_trigger(enum panel_event_notifier_tag tag,
		struct panel_event_notification *notif)
{
}

#endif /* _PANEL_EVENT_NOTIFIER_H */
