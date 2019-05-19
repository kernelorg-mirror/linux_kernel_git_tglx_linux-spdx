/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * This file is part of the Chelsio T4 Ethernet driver for Linux.
 *
 * Copyright (c) 2016 Chelsio Communications, Inc. All rights reserved.
 */

#ifndef __CXGB4_SCHED_H
#define __CXGB4_SCHED_H

#include <linux/spinlock.h>
#include <linux/atomic.h>

#define SCHED_CLS_NONE 0xff

#define FW_SCHED_CLS_NONE 0xffffffff

/* Max rate that can be set to a scheduling class is 100 Gbps */
#define SCHED_MAX_RATE_KBPS 100000000U

enum {
	SCHED_STATE_ACTIVE,
	SCHED_STATE_UNUSED,
};

enum sched_fw_ops {
	SCHED_FW_OP_ADD,
};

enum sched_bind_type {
	SCHED_QUEUE,
};

struct sched_queue_entry {
	struct list_head list;
	unsigned int cntxt_id;
	struct ch_sched_queue param;
};

struct sched_class {
	u8 state;
	u8 idx;
	struct ch_sched_params info;
	struct list_head queue_list;
	atomic_t refcnt;
};

struct sched_table {      /* per port scheduling table */
	u8 sched_size;
	struct sched_class tab[0];
};

static inline bool can_sched(struct net_device *dev)
{
	struct port_info *pi = netdev2pinfo(dev);

	return !pi->sched_tbl ? false : true;
}

static inline bool valid_class_id(struct net_device *dev, u8 class_id)
{
	struct port_info *pi = netdev2pinfo(dev);

	if ((class_id > pi->sched_tbl->sched_size - 1) &&
	    (class_id != SCHED_CLS_NONE))
		return false;

	return true;
}

int cxgb4_sched_class_bind(struct net_device *dev, void *arg,
			   enum sched_bind_type type);
int cxgb4_sched_class_unbind(struct net_device *dev, void *arg,
			     enum sched_bind_type type);

struct sched_class *cxgb4_sched_class_alloc(struct net_device *dev,
					    struct ch_sched_params *p);

struct sched_table *t4_init_sched(unsigned int size);
void t4_cleanup_sched(struct adapter *adap);
#endif  /* __CXGB4_SCHED_H */
