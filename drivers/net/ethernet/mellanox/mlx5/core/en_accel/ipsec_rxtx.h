/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2017 Mellanox Technologies. All rights reserved.
 */

#ifndef __MLX5E_IPSEC_RXTX_H__
#define __MLX5E_IPSEC_RXTX_H__

#ifdef CONFIG_MLX5_EN_IPSEC

#include <linux/skbuff.h>
#include <net/xfrm.h>
#include "en.h"

struct sk_buff *mlx5e_ipsec_handle_rx_skb(struct net_device *netdev,
					  struct sk_buff *skb, u32 *cqe_bcnt);
void mlx5e_ipsec_handle_rx_cqe(struct mlx5e_rq *rq, struct mlx5_cqe64 *cqe);

void mlx5e_ipsec_inverse_table_init(void);
bool mlx5e_ipsec_feature_check(struct sk_buff *skb, struct net_device *netdev,
			       netdev_features_t features);
void mlx5e_ipsec_set_iv_esn(struct sk_buff *skb, struct xfrm_state *x,
			    struct xfrm_offload *xo);
void mlx5e_ipsec_set_iv(struct sk_buff *skb, struct xfrm_state *x,
			struct xfrm_offload *xo);
struct sk_buff *mlx5e_ipsec_handle_tx_skb(struct net_device *netdev,
					  struct mlx5e_tx_wqe *wqe,
					  struct sk_buff *skb);

#endif /* CONFIG_MLX5_EN_IPSEC */

#endif /* __MLX5E_IPSEC_RXTX_H__ */
