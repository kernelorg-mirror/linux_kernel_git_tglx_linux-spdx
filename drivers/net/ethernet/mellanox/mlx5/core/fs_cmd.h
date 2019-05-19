/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2015, Mellanox Technologies. All rights reserved.
 */

#ifndef _MLX5_FS_CMD_
#define _MLX5_FS_CMD_

#include "fs_core.h"

struct mlx5_flow_cmds {
	int (*create_flow_table)(struct mlx5_flow_root_namespace *ns,
				 struct mlx5_flow_table *ft,
				 unsigned int log_size,
				 struct mlx5_flow_table *next_ft);
	int (*destroy_flow_table)(struct mlx5_flow_root_namespace *ns,
				  struct mlx5_flow_table *ft);

	int (*modify_flow_table)(struct mlx5_flow_root_namespace *ns,
				 struct mlx5_flow_table *ft,
				 struct mlx5_flow_table *next_ft);

	int (*create_flow_group)(struct mlx5_flow_root_namespace *ns,
				 struct mlx5_flow_table *ft,
				 u32 *in,
				 struct mlx5_flow_group *fg);

	int (*destroy_flow_group)(struct mlx5_flow_root_namespace *ns,
				  struct mlx5_flow_table *ft,
				  struct mlx5_flow_group *fg);

	int (*create_fte)(struct mlx5_flow_root_namespace *ns,
			  struct mlx5_flow_table *ft,
			  struct mlx5_flow_group *fg,
			  struct fs_fte *fte);

	int (*update_fte)(struct mlx5_flow_root_namespace *ns,
			  struct mlx5_flow_table *ft,
			  struct mlx5_flow_group *fg,
			  int modify_mask,
			  struct fs_fte *fte);

	int (*delete_fte)(struct mlx5_flow_root_namespace *ns,
			  struct mlx5_flow_table *ft,
			  struct fs_fte *fte);

	int (*update_root_ft)(struct mlx5_flow_root_namespace *ns,
			      struct mlx5_flow_table *ft,
			      u32 underlay_qpn,
			      bool disconnect);
};

int mlx5_cmd_fc_alloc(struct mlx5_core_dev *dev, u32 *id);
int mlx5_cmd_fc_free(struct mlx5_core_dev *dev, u32 id);
int mlx5_cmd_fc_query(struct mlx5_core_dev *dev, u32 id,
		      u64 *packets, u64 *bytes);

struct mlx5_cmd_fc_bulk;

struct mlx5_cmd_fc_bulk *
mlx5_cmd_fc_bulk_alloc(struct mlx5_core_dev *dev, u32 id, int num);
void mlx5_cmd_fc_bulk_free(struct mlx5_cmd_fc_bulk *b);
int
mlx5_cmd_fc_bulk_query(struct mlx5_core_dev *dev, struct mlx5_cmd_fc_bulk *b);
void mlx5_cmd_fc_bulk_get(struct mlx5_core_dev *dev,
			  struct mlx5_cmd_fc_bulk *b, u32 id,
			  u64 *packets, u64 *bytes);

const struct mlx5_flow_cmds *mlx5_fs_cmd_get_default(enum fs_flow_table_type type);

#endif
