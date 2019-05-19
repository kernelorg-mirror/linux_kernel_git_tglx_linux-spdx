/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Marvell Wireless LAN device driver: 802.11n Aggregation
 *
 * Copyright (C) 2011-2014, Marvell International Ltd.
 */

#ifndef _MWIFIEX_11N_AGGR_H_
#define _MWIFIEX_11N_AGGR_H_

#define PKT_TYPE_AMSDU	0xE6
#define MIN_NUM_AMSDU 2

int mwifiex_11n_deaggregate_pkt(struct mwifiex_private *priv,
				struct sk_buff *skb);
int mwifiex_11n_aggregate_pkt(struct mwifiex_private *priv,
			      struct mwifiex_ra_list_tbl *ptr,
			      int ptr_index, unsigned long flags)
			      __releases(&priv->wmm.ra_list_spinlock);

#endif /* !_MWIFIEX_11N_AGGR_H_ */
