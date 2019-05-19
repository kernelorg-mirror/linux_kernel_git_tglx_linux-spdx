/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2018, Mellanox Technologies. All rights reserved.
 */

#ifndef __MLX5E_EN_PORT_H
#define __MLX5E_EN_PORT_H

#include <linux/mlx5/driver.h>
#include "en.h"

struct mlx5e_port_eth_proto {
	u32 cap;
	u32 admin;
	u32 oper;
};

int mlx5_port_query_eth_proto(struct mlx5_core_dev *dev, u8 port, bool ext,
			      struct mlx5e_port_eth_proto *eproto);
void mlx5_port_query_eth_autoneg(struct mlx5_core_dev *dev, u8 *an_status,
				 u8 *an_disable_cap, u8 *an_disable_admin);
int mlx5_port_set_eth_ptys(struct mlx5_core_dev *dev, bool an_disable,
			   u32 proto_admin, bool ext);
u32 mlx5e_port_ptys2speed(struct mlx5_core_dev *mdev, u32 eth_proto_oper);
int mlx5e_port_linkspeed(struct mlx5_core_dev *mdev, u32 *speed);
int mlx5e_port_max_linkspeed(struct mlx5_core_dev *mdev, u32 *speed);
u32 mlx5e_port_speed2linkmodes(struct mlx5_core_dev *mdev, u32 speed);

int mlx5e_port_query_pbmc(struct mlx5_core_dev *mdev, void *out);
int mlx5e_port_set_pbmc(struct mlx5_core_dev *mdev, void *in);
int mlx5e_port_query_priority2buffer(struct mlx5_core_dev *mdev, u8 *buffer);
int mlx5e_port_set_priority2buffer(struct mlx5_core_dev *mdev, u8 *buffer);

int mlx5e_get_fec_caps(struct mlx5_core_dev *dev, u8 *fec_caps);
int mlx5e_get_fec_mode(struct mlx5_core_dev *dev, u32 *fec_mode_active,
		       u8 *fec_configured_mode);
int mlx5e_set_fec_mode(struct mlx5_core_dev *dev, u8 fec_policy);

enum {
	MLX5E_FEC_NOFEC,
	MLX5E_FEC_FIRECODE,
	MLX5E_FEC_RS_528_514,
};

#endif
