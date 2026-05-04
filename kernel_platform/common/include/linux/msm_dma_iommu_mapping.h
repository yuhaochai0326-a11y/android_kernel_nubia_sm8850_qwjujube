/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Stub header for msm_dma_iommu_mapping — GKI 6.12 compatibility
 * MSM-specific DMA IOMMU mapping helpers not available in vanilla GKI.
 */
#ifndef _LINUX_MSM_DMA_IOMMU_MAPPING_H
#define _LINUX_MSM_DMA_IOMMU_MAPPING_H

#include <linux/device.h>

struct dma_buf;

static inline void msm_dma_unmap_all_for_dev(struct device *dev)
{
	/* No-op in GKI — IOMMU mappings are managed by the standard kernel */
}

static inline int msm_dma_map_sg_attrs(struct device *dev,
	struct scatterlist *sg, int nents, enum dma_data_direction dir,
	struct dma_buf *dma_buf, unsigned long attrs)
{
	return dma_map_sg_attrs(dev, sg, nents, dir, attrs);
}

static inline void msm_dma_unmap_sg_attrs(struct device *dev,
	struct scatterlist *sg, int nents, enum dma_data_direction dir,
	struct dma_buf *dma_buf, unsigned long attrs)
{
	dma_unmap_sg_attrs(dev, sg, nents, dir, attrs);
}

#endif /* _LINUX_MSM_DMA_IOMMU_MAPPING_H */
