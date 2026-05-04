#include <linux/types.h>

/* ZTE GPU Stubs to satisfy GKI link requirements */

/* Function Pointers used by kgsl.c */
void (*kgsl_pwrctrl_set_max_level_fp)(u32 level) = NULL;
void (*kgsl_pwrctrl_set_min_level_fp)(u32 level) = NULL;
u32 (*kgsl_pwrctrl_get_max_level_fp)(void) = NULL;
u32 (*kgsl_pwrctrl_get_min_level_fp)(void) = NULL;
int (*kgsl_pwrctrl_get_loading_fp)(void) = NULL;
int (*kgsl_gpu_num_freqs_fp)(void) = NULL;

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
int mem_buf_fd_to_vmid(int a) { return -1; }
void *mem_buf_dev = NULL;

/* SCM stubs */
int qcom_scm_set_remote_state(u32 state, u32 id) { return -1; }
int qcom_scm_pas_shutdown(u32 peripheral) { return -1; }

/* IOMMU / PageTable stubs */
void *qcom_io_pgtable_alloc_init(void *a, void *b, void *c) { return NULL; }
void qcom_io_pgtable_alloc_exit(void *a) { }
void qcom_io_pgtable_arm_64_lpae_s1_init_fns(void *a) { }
void qcom_arm_lpae_do_selftests(void) { }
