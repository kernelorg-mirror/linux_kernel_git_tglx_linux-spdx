/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2016, Mellanox Technologies, Ltd.  All rights reserved.
 */
#ifndef __MLX5_VXLAN_H__
#define __MLX5_VXLAN_H__

#include <linux/mlx5/driver.h>

struct mlx5_vxlan;
struct mlx5_vxlan_port;

static inline bool mlx5_vxlan_allowed(struct mlx5_vxlan *vxlan)
{
	/* not allowed reason is encoded in vxlan pointer as error,
	 * on mlx5_vxlan_create
	 */
	return !IS_ERR_OR_NULL(vxlan);
}

#if IS_ENABLED(CONFIG_VXLAN)
struct mlx5_vxlan *mlx5_vxlan_create(struct mlx5_core_dev *mdev);
void mlx5_vxlan_destroy(struct mlx5_vxlan *vxlan);
int mlx5_vxlan_add_port(struct mlx5_vxlan *vxlan, u16 port);
int mlx5_vxlan_del_port(struct mlx5_vxlan *vxlan, u16 port);
struct mlx5_vxlan_port *mlx5_vxlan_lookup_port(struct mlx5_vxlan *vxlan, u16 port);
#else
static inline struct mlx5_vxlan*
mlx5_vxlan_create(struct mlx5_core_dev *mdev) { return ERR_PTR(-EOPNOTSUPP); }
static inline void mlx5_vxlan_destroy(struct mlx5_vxlan *vxlan) { return; }
static inline int mlx5_vxlan_add_port(struct mlx5_vxlan *vxlan, u16 port) { return -EOPNOTSUPP; }
static inline int mlx5_vxlan_del_port(struct mlx5_vxlan *vxlan, u16 port) { return -EOPNOTSUPP; }
static inline struct mx5_vxlan_port*
mlx5_vxlan_lookup_port(struct mlx5_vxlan *vxlan, u16 port) { return NULL; }
#endif

#endif /* __MLX5_VXLAN_H__ */
