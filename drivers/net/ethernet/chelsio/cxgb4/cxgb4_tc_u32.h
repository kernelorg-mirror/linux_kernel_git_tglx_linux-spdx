/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * This file is part of the Chelsio T4 Ethernet driver for Linux.
 *
 * Copyright (c) 2016 Chelsio Communications, Inc. All rights reserved.
 */

#ifndef __CXGB4_TC_U32_H
#define __CXGB4_TC_U32_H

#include <net/pkt_cls.h>

static inline bool can_tc_u32_offload(struct net_device *dev)
{
	struct adapter *adap = netdev2adap(dev);

	return (dev->features & NETIF_F_HW_TC) && adap->tc_u32 ? true : false;
}

int cxgb4_config_knode(struct net_device *dev, struct tc_cls_u32_offload *cls);
int cxgb4_delete_knode(struct net_device *dev, struct tc_cls_u32_offload *cls);

void cxgb4_cleanup_tc_u32(struct adapter *adapter);
struct cxgb4_tc_u32_table *cxgb4_init_tc_u32(struct adapter *adap);
#endif /* __CXGB4_TC_U32_H */
