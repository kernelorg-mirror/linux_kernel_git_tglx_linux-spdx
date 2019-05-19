/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2018 Mellanox Technologies. All rights reserved.
 */

#ifndef __MLX5E_EN_ACCEL_H__
#define __MLX5E_EN_ACCEL_H__

#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include "en_accel/ipsec_rxtx.h"
#include "en_accel/tls_rxtx.h"
#include "en.h"

#if IS_ENABLED(CONFIG_GENEVE)
static inline bool mlx5_geneve_tx_allowed(struct mlx5_core_dev *mdev)
{
	return mlx5_tx_swp_supported(mdev);
}

static inline void
mlx5e_tx_tunnel_accel(struct sk_buff *skb, struct mlx5_wqe_eth_seg *eseg)
{
	struct mlx5e_swp_spec swp_spec = {};
	unsigned int offset = 0;
	__be16 l3_proto;
	u8 l4_proto;

	l3_proto = vlan_get_protocol(skb);
	switch (l3_proto) {
	case htons(ETH_P_IP):
		l4_proto = ip_hdr(skb)->protocol;
		break;
	case htons(ETH_P_IPV6):
		l4_proto = ipv6_find_hdr(skb, &offset, -1, NULL, NULL);
		break;
	default:
		return;
	}

	if (l4_proto != IPPROTO_UDP ||
	    udp_hdr(skb)->dest != cpu_to_be16(GENEVE_UDP_PORT))
		return;
	swp_spec.l3_proto = l3_proto;
	swp_spec.l4_proto = l4_proto;
	swp_spec.is_tun = true;
	if (inner_ip_hdr(skb)->version == 6) {
		swp_spec.tun_l3_proto = htons(ETH_P_IPV6);
		swp_spec.tun_l4_proto = inner_ipv6_hdr(skb)->nexthdr;
	} else {
		swp_spec.tun_l3_proto = htons(ETH_P_IP);
		swp_spec.tun_l4_proto = inner_ip_hdr(skb)->protocol;
	}

	mlx5e_set_eseg_swp(skb, eseg, &swp_spec);
}

#else
static inline bool mlx5_geneve_tx_allowed(struct mlx5_core_dev *mdev)
{
	return false;
}

#endif /* CONFIG_GENEVE */

static inline void
mlx5e_udp_gso_handle_tx_skb(struct sk_buff *skb)
{
	int payload_len = skb_shinfo(skb)->gso_size + sizeof(struct udphdr);

	udp_hdr(skb)->len = htons(payload_len);
}

static inline struct sk_buff *
mlx5e_accel_handle_tx(struct sk_buff *skb,
		      struct mlx5e_txqsq *sq,
		      struct net_device *dev,
		      struct mlx5e_tx_wqe **wqe,
		      u16 *pi)
{
#ifdef CONFIG_MLX5_EN_TLS
	if (test_bit(MLX5E_SQ_STATE_TLS, &sq->state)) {
		skb = mlx5e_tls_handle_tx_skb(dev, sq, skb, wqe, pi);
		if (unlikely(!skb))
			return NULL;
	}
#endif

#ifdef CONFIG_MLX5_EN_IPSEC
	if (test_bit(MLX5E_SQ_STATE_IPSEC, &sq->state)) {
		skb = mlx5e_ipsec_handle_tx_skb(dev, *wqe, skb);
		if (unlikely(!skb))
			return NULL;
	}
#endif

	if (skb_is_gso(skb) && skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4)
		mlx5e_udp_gso_handle_tx_skb(skb);

	return skb;
}

#endif /* __MLX5E_EN_ACCEL_H__ */
