/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * This file is part of the Chelsio T4/T5/T6 Ethernet driver for Linux.
 *
 * Copyright (c) 2017 Chelsio Communications, Inc. All rights reserved.
 */

#ifndef __CXGB4_SMT_H
#define __CXGB4_SMT_H

#include <linux/spinlock.h>
#include <linux/if_ether.h>
#include <linux/atomic.h>

struct adapter;
struct cpl_smt_write_rpl;

/* SMT related handling. Heavily adapted based on l2t ops in l2t.h/l2t.c
 */
enum {
	SMT_STATE_SWITCHING,
	SMT_STATE_UNUSED,
	SMT_STATE_ERROR
};

enum {
	SMT_SIZE = 256
};

struct smt_entry {
	u16 state;
	u16 idx;
	u16 pfvf;
	u8 src_mac[ETH_ALEN];
	atomic_t refcnt;
	spinlock_t lock;	/* protect smt entry add,removal */
};

struct smt_data {
	unsigned int smt_size;
	rwlock_t lock;
	struct smt_entry smtab[0];
};

struct smt_data *t4_init_smt(void);
struct smt_entry *cxgb4_smt_alloc_switching(struct net_device *dev, u8 *smac);
void cxgb4_smt_release(struct smt_entry *e);
void do_smt_write_rpl(struct adapter *p, const struct cpl_smt_write_rpl *rpl);
#endif /* __CXGB4_SMT_H */
