#include <linux/types.h>
#include <linux/device.h>

/* ZTE Display Stubs to satisfy GKI link requirements */

/* Mem-buf stubs */
int mem_buf_dma_buf_copy_vmperm(void *a, void *b, void *c, int d) { return -1; }
int mem_buf_dma_buf_exclusive_owner(void *a, void *b) { return -1; }
void *to_mem_buf_vmperm(void *a) { return NULL; }
int mem_buf_dma_buf_get_memparcel_hdl(void *a, u32 *b) { return -1; }
int mem_buf_dma_buf_allow_share(void *a, u32 b, u32 c) { return -1; }
int mem_buf_lend(u32 a, void *b, u32 c, void *d, u32 e) { return -1; }
int mem_buf_share(u32 a, void *b, u32 c, void *d, u32 e) { return -1; }
int mem_buf_unmap_vmperm(void *a, void *b, void *c, int d) { return -1; }
int mem_buf_reclaim(u32 a, void *b, u32 c, void *d) { return -1; }

/* IOMMU stubs */
int qcom_iommu_sid_switch(struct device *a, u32 b) { return -1; }
int qcom_iommu_enable_s1_translation(struct device *a) { return -1; }

/* HFI stubs */
void hfi_core_deallocate_shared_mem(void *a) { }
int hfi_core_allocate_shared_mem(void *a, u32 b, u32 c, void **d, u32 *e) { return -1; }
int hfi_core_cmds_tx_buf_send(void *a, void *b, u32 c) { return -1; }
void *hfi_core_cmds_tx_buf_get(void *a, u32 b, u32 c) { return NULL; }
void hfi_core_release_tx_buffer(void *a, void *b) { }
void *hfi_core_cmds_rx_buf_get(void *a, u32 b, u32 c) { return NULL; }
void hfi_core_release_rx_buffer(void *a, void *b) { }
int hfi_core_open_session(void *a, void *b) { return -1; }

/* Clock stubs */
int qcom_clk_set_flags(void *a, unsigned long b) { return -1; }
