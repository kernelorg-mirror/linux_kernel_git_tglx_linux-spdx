/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2004 Topspin Corporation.  All rights reserved.
 * Copyright (c) 2005 Sun Microsystems, Inc. All rights reserved.
 */

#if !defined(IB_FMR_POOL_H)
#define IB_FMR_POOL_H

#include <rdma/ib_verbs.h>

struct ib_fmr_pool;

/**
 * struct ib_fmr_pool_param - Parameters for creating FMR pool
 * @max_pages_per_fmr:Maximum number of pages per map request.
 * @page_shift: Log2 of sizeof "pages" mapped by this fmr
 * @access:Access flags for FMRs in pool.
 * @pool_size:Number of FMRs to allocate for pool.
 * @dirty_watermark:Flush is triggered when @dirty_watermark dirty
 *     FMRs are present.
 * @flush_function:Callback called when unmapped FMRs are flushed and
 *     more FMRs are possibly available for mapping
 * @flush_arg:Context passed to user's flush function.
 * @cache:If set, FMRs may be reused after unmapping for identical map
 *     requests.
 */
struct ib_fmr_pool_param {
	int                     max_pages_per_fmr;
	int                     page_shift;
	enum ib_access_flags    access;
	int                     pool_size;
	int                     dirty_watermark;
	void                  (*flush_function)(struct ib_fmr_pool *pool,
						void               *arg);
	void                   *flush_arg;
	unsigned                cache:1;
};

struct ib_pool_fmr {
	struct ib_fmr      *fmr;
	struct ib_fmr_pool *pool;
	struct list_head    list;
	struct hlist_node   cache_node;
	int                 ref_count;
	int                 remap_count;
	u64                 io_virtual_address;
	int                 page_list_len;
	u64                 page_list[0];
};

struct ib_fmr_pool *ib_create_fmr_pool(struct ib_pd             *pd,
				       struct ib_fmr_pool_param *params);

void ib_destroy_fmr_pool(struct ib_fmr_pool *pool);

int ib_flush_fmr_pool(struct ib_fmr_pool *pool);

struct ib_pool_fmr *ib_fmr_pool_map_phys(struct ib_fmr_pool *pool_handle,
					 u64                *page_list,
					 int                 list_len,
					 u64                 io_virtual_address);

void ib_fmr_pool_unmap(struct ib_pool_fmr *fmr);

#endif /* IB_FMR_POOL_H */
