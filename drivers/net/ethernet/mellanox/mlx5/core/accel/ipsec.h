/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2017 Mellanox Technologies. All rights reserved.
 */

#ifndef __MLX5_ACCEL_IPSEC_H__
#define __MLX5_ACCEL_IPSEC_H__

#include <linux/mlx5/driver.h>
#include <linux/mlx5/accel.h>

#ifdef CONFIG_MLX5_ACCEL

#define MLX5_IPSEC_DEV(mdev) (mlx5_accel_ipsec_device_caps(mdev) & \
			      MLX5_ACCEL_IPSEC_CAP_DEVICE)

unsigned int mlx5_accel_ipsec_counters_count(struct mlx5_core_dev *mdev);
int mlx5_accel_ipsec_counters_read(struct mlx5_core_dev *mdev, u64 *counters,
				   unsigned int count);

void *mlx5_accel_esp_create_hw_context(struct mlx5_core_dev *mdev,
				       struct mlx5_accel_esp_xfrm *xfrm,
				       const __be32 saddr[4],
				       const __be32 daddr[4],
				       const __be32 spi, bool is_ipv6);
void mlx5_accel_esp_free_hw_context(void *context);

int mlx5_accel_ipsec_init(struct mlx5_core_dev *mdev);
void mlx5_accel_ipsec_cleanup(struct mlx5_core_dev *mdev);

#else

#define MLX5_IPSEC_DEV(mdev) false

static inline void *
mlx5_accel_esp_create_hw_context(struct mlx5_core_dev *mdev,
				 struct mlx5_accel_esp_xfrm *xfrm,
				 const __be32 saddr[4],
				 const __be32 daddr[4],
				 const __be32 spi, bool is_ipv6)
{
	return NULL;
}

static inline void mlx5_accel_esp_free_hw_context(void *context)
{
}

static inline int mlx5_accel_ipsec_init(struct mlx5_core_dev *mdev)
{
	return 0;
}

static inline void mlx5_accel_ipsec_cleanup(struct mlx5_core_dev *mdev)
{
}

#endif

#endif	/* __MLX5_ACCEL_IPSEC_H__ */
