/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * This file is part of the Chelsio T4 Ethernet driver for Linux.
 *
 * Copyright (c) 2003-2016 Chelsio Communications, Inc. All rights reserved.
 */

#ifndef __CXGB4_FILTER_H
#define __CXGB4_FILTER_H

#include "t4_msg.h"

#define WORD_MASK	0xffffffff

void filter_rpl(struct adapter *adap, const struct cpl_set_tcb_rpl *rpl);
void hash_filter_rpl(struct adapter *adap, const struct cpl_act_open_rpl *rpl);
void hash_del_filter_rpl(struct adapter *adap,
			 const struct cpl_abort_rpl_rss *rpl);
void clear_filter(struct adapter *adap, struct filter_entry *f);

int set_filter_wr(struct adapter *adapter, int fidx);
int delete_filter(struct adapter *adapter, unsigned int fidx);

int writable_filter(struct filter_entry *f);
void clear_all_filters(struct adapter *adapter);
int init_hash_filter(struct adapter *adap);
bool is_filter_exact_match(struct adapter *adap,
			   struct ch_filter_specification *fs);
#endif /* __CXGB4_FILTER_H */
