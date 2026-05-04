/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _MSM_EXT_DISPLAY_H
#define _MSM_EXT_DISPLAY_H

#include <linux/types.h>
#include <linux/platform_device.h>

enum msm_ext_disp_type {
	EXT_DISPLAY_TYPE_HDMI,
	EXT_DISPLAY_TYPE_DP,
	EXT_DISPLAY_TYPE_MAX,
};

enum msm_ext_disp_cable_state {
	EXT_DISPLAY_CABLE_DISCONNECT,
	EXT_DISPLAY_CABLE_CONNECT,
	EXT_DISPLAY_CABLE_STATE_MAX,
};

struct msm_ext_disp_audio_setup_params {
	u32 sample_rate_hz;
	u32 num_of_channels;
	u32 bit_width;
};

struct msm_ext_disp_audio_edid_blk {
	u8 *audio_data_blk;
	u32 audio_data_blk_size;
	u8 *spk_alloc_data_blk;
	u32 spk_alloc_data_blk_size;
};

struct msm_ext_disp_codec_data {
	enum msm_ext_disp_type type;
	u32 ctrl_id;
	u32 stream_id;
};

struct msm_ext_disp_audio_codec_ops {
	int (*audio_info_setup)(struct platform_device *pdev,
			struct msm_ext_disp_audio_setup_params *params);
	int (*get_audio_edid_blk)(struct platform_device *pdev,
			struct msm_ext_disp_audio_edid_blk *blk);
	int (*cable_status)(struct platform_device *pdev, u32 vote);
	int (*get_intf_id)(struct platform_device *pdev);
	void (*teardown_done)(struct platform_device *pdev);
	int (*acknowledge)(struct platform_device *pdev, u32 ack);
	int (*ready)(struct platform_device *pdev);
};

struct msm_ext_disp_intf_ops {
	int (*audio_config)(struct platform_device *pdev,
			struct msm_ext_disp_codec_data *codec, u32 state);
	int (*audio_notify)(struct platform_device *pdev,
			struct msm_ext_disp_codec_data *codec, u32 state);
};

struct msm_ext_disp_init_data {
	struct msm_ext_disp_codec_data codec;
	struct platform_device *pdev;
	void *intf_data;
	struct msm_ext_disp_audio_codec_ops codec_ops;
	struct msm_ext_disp_intf_ops intf_ops;
};

struct msm_ext_disp_data {
	void *intf_data;
};

static inline int msm_ext_disp_register_intf(struct platform_device *pdev,
		struct msm_ext_disp_init_data *init_data)
{
	return 0;
}

static inline int msm_ext_disp_deregister_intf(struct platform_device *pdev,
		struct msm_ext_disp_init_data *init_data)
{
	return 0;
}

#define AUDIO_ACK_SET_ENABLE BIT(0)
#define AUDIO_ACK_ENABLE     BIT(1)
#define AUDIO_ACK_CONNECT    BIT(2)

#endif /* _MSM_EXT_DISPLAY_H */
