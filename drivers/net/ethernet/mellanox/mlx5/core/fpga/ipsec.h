/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2017 Mellanox Technologies. All rights reserved.
 */

#ifndef __MLX5_FPGA_IPSEC_H__
#define __MLX5_FPGA_IPSEC_H__

#include "accel/ipsec.h"
#include "fs_cmd.h"

#ifdef CONFIG_MLX5_FPGA

u32 mlx5_fpga_ipsec_device_caps(struct mlx5_core_dev *mdev);
unsigned int mlx5_fpga_ipsec_counters_count(struct mlx5_core_dev *mdev);
int mlx5_fpga_ipsec_counters_read(struct mlx5_core_dev *mdev, u64 *counters,
				  unsigned int counters_count);

void *mlx5_fpga_ipsec_create_sa_ctx(struct mlx5_core_dev *mdev,
				    struct mlx5_accel_esp_xfrm *accel_xfrm,
				    const __be32 saddr[4],
				    const __be32 daddr[4],
				    const __be32 spi, bool is_ipv6);
void mlx5_fpga_ipsec_delete_sa_ctx(void *context);

int mlx5_fpga_ipsec_init(struct mlx5_core_dev *mdev);
void mlx5_fpga_ipsec_cleanup(struct mlx5_core_dev *mdev);
void mlx5_fpga_ipsec_build_fs_cmds(void);

struct mlx5_accel_esp_xfrm *
mlx5_fpga_esp_create_xfrm(struct mlx5_core_dev *mdev,
			  const struct mlx5_accel_esp_xfrm_attrs *attrs,
			  u32 flags);
void mlx5_fpga_esp_destroy_xfrm(struct mlx5_accel_esp_xfrm *xfrm);
int mlx5_fpga_esp_modify_xfrm(struct mlx5_accel_esp_xfrm *xfrm,
			      const struct mlx5_accel_esp_xfrm_attrs *attrs);

const struct mlx5_flow_cmds *
mlx5_fs_cmd_get_default_ipsec_fpga_cmds(enum fs_flow_table_type type);

#else

static inline u32 mlx5_fpga_ipsec_device_caps(struct mlx5_core_dev *mdev)
{
	return 0;
}

static inline unsigned int
mlx5_fpga_ipsec_counters_count(struct mlx5_core_dev *mdev)
{
	return 0;
}

static inline int mlx5_fpga_ipsec_counters_read(struct mlx5_core_dev *mdev,
						u64 *counters)
{
	return 0;
}

static inline void *
mlx5_fpga_ipsec_create_sa_ctx(struct mlx5_core_dev *mdev,
			      struct mlx5_accel_esp_xfrm *accel_xfrm,
			      const __be32 saddr[4],
			      const __be32 daddr[4],
			      const __be32 spi, bool is_ipv6)
{
	return NULL;
}

static inline void mlx5_fpga_ipsec_delete_sa_ctx(void *context)
{
}

static inline int mlx5_fpga_ipsec_init(struct mlx5_core_dev *mdev)
{
	return 0;
}

static inline void mlx5_fpga_ipsec_cleanup(struct mlx5_core_dev *mdev)
{
}

static inline void mlx5_fpga_ipsec_build_fs_cmds(void)
{
}

static inline struct mlx5_accel_esp_xfrm *
mlx5_fpga_esp_create_xfrm(struct mlx5_core_dev *mdev,
			  const struct mlx5_accel_esp_xfrm_attrs *attrs,
			  u32 flags)
{
	return ERR_PTR(-EOPNOTSUPP);
}

static inline void mlx5_fpga_esp_destroy_xfrm(struct mlx5_accel_esp_xfrm *xfrm)
{
}

static inline int
mlx5_fpga_esp_modify_xfrm(struct mlx5_accel_esp_xfrm *xfrm,
			  const struct mlx5_accel_esp_xfrm_attrs *attrs)
{
	return -EOPNOTSUPP;
}

static inline const struct mlx5_flow_cmds *
mlx5_fs_cmd_get_default_ipsec_fpga_cmds(enum fs_flow_table_type type)
{
	return mlx5_fs_cmd_get_default(type);
}

#endif /* CONFIG_MLX5_FPGA */

#endif	/* __MLX5_FPGA_SADB_H__ */
