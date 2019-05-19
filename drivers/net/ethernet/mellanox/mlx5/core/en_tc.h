/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2016, Mellanox Technologies. All rights reserved.
 */

#ifndef __MLX5_EN_TC_H__
#define __MLX5_EN_TC_H__

#include <net/pkt_cls.h>

#define MLX5E_TC_FLOW_ID_MASK 0x0000ffff

#ifdef CONFIG_MLX5_ESWITCH

enum {
	MLX5E_TC_INGRESS = BIT(0),
	MLX5E_TC_EGRESS  = BIT(1),
	MLX5E_TC_NIC_OFFLOAD = BIT(2),
	MLX5E_TC_ESW_OFFLOAD = BIT(3),
	MLX5E_TC_LAST_EXPORTED_BIT = 3,
};

int mlx5e_tc_nic_init(struct mlx5e_priv *priv);
void mlx5e_tc_nic_cleanup(struct mlx5e_priv *priv);

int mlx5e_tc_esw_init(struct rhashtable *tc_ht);
void mlx5e_tc_esw_cleanup(struct rhashtable *tc_ht);

int mlx5e_configure_flower(struct net_device *dev, struct mlx5e_priv *priv,
			   struct tc_cls_flower_offload *f, int flags);
int mlx5e_delete_flower(struct net_device *dev, struct mlx5e_priv *priv,
			struct tc_cls_flower_offload *f, int flags);

int mlx5e_stats_flower(struct net_device *dev, struct mlx5e_priv *priv,
		       struct tc_cls_flower_offload *f, int flags);

struct mlx5e_encap_entry;
void mlx5e_tc_encap_flows_add(struct mlx5e_priv *priv,
			      struct mlx5e_encap_entry *e);
void mlx5e_tc_encap_flows_del(struct mlx5e_priv *priv,
			      struct mlx5e_encap_entry *e);

struct mlx5e_neigh_hash_entry;
void mlx5e_tc_update_neigh_used_value(struct mlx5e_neigh_hash_entry *nhe);

int mlx5e_tc_num_filters(struct mlx5e_priv *priv, int flags);

void mlx5e_tc_reoffload_flows_work(struct work_struct *work);

#else /* CONFIG_MLX5_ESWITCH */
static inline int  mlx5e_tc_nic_init(struct mlx5e_priv *priv) { return 0; }
static inline void mlx5e_tc_nic_cleanup(struct mlx5e_priv *priv) {}
static inline int  mlx5e_tc_num_filters(struct mlx5e_priv *priv, int flags) { return 0; }
#endif

#endif /* __MLX5_EN_TC_H__ */
