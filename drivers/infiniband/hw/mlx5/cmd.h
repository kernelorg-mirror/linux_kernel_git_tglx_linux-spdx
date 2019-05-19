/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2017, Mellanox Technologies. All rights reserved.
 */

#ifndef MLX5_IB_CMD_H
#define MLX5_IB_CMD_H

#include "mlx5_ib.h"
#include <linux/kernel.h>
#include <linux/mlx5/driver.h>

int mlx5_cmd_dump_fill_mkey(struct mlx5_core_dev *dev, u32 *mkey);
int mlx5_cmd_null_mkey(struct mlx5_core_dev *dev, u32 *null_mkey);
int mlx5_cmd_query_cong_params(struct mlx5_core_dev *dev, int cong_point,
			       void *out, int out_size);
int mlx5_cmd_query_ext_ppcnt_counters(struct mlx5_core_dev *dev, void *out);
int mlx5_cmd_modify_cong_params(struct mlx5_core_dev *mdev,
				void *in, int in_size);
int mlx5_cmd_alloc_memic(struct mlx5_dm *dm, phys_addr_t *addr,
			 u64 length, u32 alignment);
int mlx5_cmd_dealloc_memic(struct mlx5_dm *dm, phys_addr_t addr, u64 length);
void mlx5_cmd_dealloc_pd(struct mlx5_core_dev *dev, u32 pdn, u16 uid);
void mlx5_cmd_destroy_tir(struct mlx5_core_dev *dev, u32 tirn, u16 uid);
void mlx5_cmd_destroy_tis(struct mlx5_core_dev *dev, u32 tisn, u16 uid);
void mlx5_cmd_destroy_rqt(struct mlx5_core_dev *dev, u32 rqtn, u16 uid);
int mlx5_cmd_alloc_transport_domain(struct mlx5_core_dev *dev, u32 *tdn,
				    u16 uid);
void mlx5_cmd_dealloc_transport_domain(struct mlx5_core_dev *dev, u32 tdn,
				       u16 uid);
int mlx5_cmd_attach_mcg(struct mlx5_core_dev *dev, union ib_gid *mgid,
			u32 qpn, u16 uid);
int mlx5_cmd_detach_mcg(struct mlx5_core_dev *dev, union ib_gid *mgid,
			u32 qpn, u16 uid);
int mlx5_cmd_xrcd_alloc(struct mlx5_core_dev *dev, u32 *xrcdn, u16 uid);
int mlx5_cmd_xrcd_dealloc(struct mlx5_core_dev *dev, u32 xrcdn, u16 uid);
int mlx5_cmd_alloc_q_counter(struct mlx5_core_dev *dev, u16 *counter_id,
			     u16 uid);
int mlx5_cmd_mad_ifc(struct mlx5_core_dev *dev, const void *inb, void *outb,
		     u16 opmod, u8 port);
int mlx5_cmd_alloc_sw_icm(struct mlx5_dm *dm, int type, u64 length,
			  u16 uid, phys_addr_t *addr, u32 *obj_id);
int mlx5_cmd_dealloc_sw_icm(struct mlx5_dm *dm, int type, u64 length,
			    u16 uid, phys_addr_t addr, u32 obj_id);
#endif /* MLX5_IB_CMD_H */
