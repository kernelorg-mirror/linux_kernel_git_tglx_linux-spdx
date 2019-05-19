/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2017 Mellanox Technologies. All rights reserved.
 */

#ifndef __MLX5E_IPSEC_H__
#define __MLX5E_IPSEC_H__

#ifdef CONFIG_MLX5_EN_IPSEC

#include <linux/mlx5/device.h>
#include <net/xfrm.h>
#include <linux/idr.h>

#include "accel/ipsec.h"

#define MLX5E_IPSEC_SADB_RX_BITS 10
#define MLX5E_IPSEC_ESN_SCOPE_MID 0x80000000L

struct mlx5e_priv;

struct mlx5e_ipsec_sw_stats {
	atomic64_t ipsec_rx_drop_sp_alloc;
	atomic64_t ipsec_rx_drop_sadb_miss;
	atomic64_t ipsec_rx_drop_syndrome;
	atomic64_t ipsec_tx_drop_bundle;
	atomic64_t ipsec_tx_drop_no_state;
	atomic64_t ipsec_tx_drop_not_ip;
	atomic64_t ipsec_tx_drop_trailer;
	atomic64_t ipsec_tx_drop_metadata;
};

struct mlx5e_ipsec_stats {
	u64 ipsec_dec_in_packets;
	u64 ipsec_dec_out_packets;
	u64 ipsec_dec_bypass_packets;
	u64 ipsec_enc_in_packets;
	u64 ipsec_enc_out_packets;
	u64 ipsec_enc_bypass_packets;
	u64 ipsec_dec_drop_packets;
	u64 ipsec_dec_auth_fail_packets;
	u64 ipsec_enc_drop_packets;
	u64 ipsec_add_sa_success;
	u64 ipsec_add_sa_fail;
	u64 ipsec_del_sa_success;
	u64 ipsec_del_sa_fail;
	u64 ipsec_cmd_drop;
};

struct mlx5e_ipsec {
	struct mlx5e_priv *en_priv;
	DECLARE_HASHTABLE(sadb_rx, MLX5E_IPSEC_SADB_RX_BITS);
	bool no_trailer;
	spinlock_t sadb_rx_lock; /* Protects sadb_rx and halloc */
	struct ida halloc;
	struct mlx5e_ipsec_sw_stats sw_stats;
	struct mlx5e_ipsec_stats stats;
	struct workqueue_struct *wq;
};

struct mlx5e_ipsec_esn_state {
	u32 esn;
	u8 trigger: 1;
	u8 overlap: 1;
};

struct mlx5e_ipsec_sa_entry {
	struct hlist_node hlist; /* Item in SADB_RX hashtable */
	struct mlx5e_ipsec_esn_state esn_state;
	unsigned int handle; /* Handle in SADB_RX */
	struct xfrm_state *x;
	struct mlx5e_ipsec *ipsec;
	struct mlx5_accel_esp_xfrm *xfrm;
	void *hw_context;
	void (*set_iv_op)(struct sk_buff *skb, struct xfrm_state *x,
			  struct xfrm_offload *xo);
};

void mlx5e_ipsec_build_inverse_table(void);
int mlx5e_ipsec_init(struct mlx5e_priv *priv);
void mlx5e_ipsec_cleanup(struct mlx5e_priv *priv);
void mlx5e_ipsec_build_netdev(struct mlx5e_priv *priv);

int mlx5e_ipsec_get_count(struct mlx5e_priv *priv);
int mlx5e_ipsec_get_strings(struct mlx5e_priv *priv, uint8_t *data);
void mlx5e_ipsec_update_stats(struct mlx5e_priv *priv);
int mlx5e_ipsec_get_stats(struct mlx5e_priv *priv, u64 *data);

struct xfrm_state *mlx5e_ipsec_sadb_rx_lookup(struct mlx5e_ipsec *dev,
					      unsigned int handle);

#else

static inline void mlx5e_ipsec_build_inverse_table(void)
{
}

static inline int mlx5e_ipsec_init(struct mlx5e_priv *priv)
{
	return 0;
}

static inline void mlx5e_ipsec_cleanup(struct mlx5e_priv *priv)
{
}

static inline void mlx5e_ipsec_build_netdev(struct mlx5e_priv *priv)
{
}

static inline int mlx5e_ipsec_get_count(struct mlx5e_priv *priv)
{
	return 0;
}

static inline int mlx5e_ipsec_get_strings(struct mlx5e_priv *priv,
					  uint8_t *data)
{
	return 0;
}

static inline void mlx5e_ipsec_update_stats(struct mlx5e_priv *priv)
{
}

static inline int mlx5e_ipsec_get_stats(struct mlx5e_priv *priv, u64 *data)
{
	return 0;
}

#endif

#endif	/* __MLX5E_IPSEC_H__ */
