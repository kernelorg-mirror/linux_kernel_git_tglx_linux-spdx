/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2018 Mellanox Technologies. All rights reserved.
 */

#ifndef __MLX5E_TLS_RXTX_H__
#define __MLX5E_TLS_RXTX_H__

#ifdef CONFIG_MLX5_EN_TLS

#include <linux/skbuff.h>
#include "en.h"

struct sk_buff *mlx5e_tls_handle_tx_skb(struct net_device *netdev,
					struct mlx5e_txqsq *sq,
					struct sk_buff *skb,
					struct mlx5e_tx_wqe **wqe,
					u16 *pi);

void mlx5e_tls_handle_rx_skb(struct net_device *netdev, struct sk_buff *skb,
			     u32 *cqe_bcnt);

#endif /* CONFIG_MLX5_EN_TLS */

#endif /* __MLX5E_TLS_RXTX_H__ */
