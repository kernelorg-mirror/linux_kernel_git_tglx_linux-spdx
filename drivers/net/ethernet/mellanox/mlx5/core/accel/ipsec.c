// SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB
/*
 * Copyright (c) 2017 Mellanox Technologies. All rights reserved.
 */

#include <linux/mlx5/device.h>

#include "accel/ipsec.h"
#include "mlx5_core.h"
#include "fpga/ipsec.h"

u32 mlx5_accel_ipsec_device_caps(struct mlx5_core_dev *mdev)
{
	return mlx5_fpga_ipsec_device_caps(mdev);
}
EXPORT_SYMBOL_GPL(mlx5_accel_ipsec_device_caps);

unsigned int mlx5_accel_ipsec_counters_count(struct mlx5_core_dev *mdev)
{
	return mlx5_fpga_ipsec_counters_count(mdev);
}

int mlx5_accel_ipsec_counters_read(struct mlx5_core_dev *mdev, u64 *counters,
				   unsigned int count)
{
	return mlx5_fpga_ipsec_counters_read(mdev, counters, count);
}

void *mlx5_accel_esp_create_hw_context(struct mlx5_core_dev *mdev,
				       struct mlx5_accel_esp_xfrm *xfrm,
				       const __be32 saddr[4],
				       const __be32 daddr[4],
				       const __be32 spi, bool is_ipv6)
{
	return mlx5_fpga_ipsec_create_sa_ctx(mdev, xfrm, saddr, daddr,
					     spi, is_ipv6);
}

void mlx5_accel_esp_free_hw_context(void *context)
{
	mlx5_fpga_ipsec_delete_sa_ctx(context);
}

int mlx5_accel_ipsec_init(struct mlx5_core_dev *mdev)
{
	return mlx5_fpga_ipsec_init(mdev);
}

void mlx5_accel_ipsec_cleanup(struct mlx5_core_dev *mdev)
{
	mlx5_fpga_ipsec_cleanup(mdev);
}

struct mlx5_accel_esp_xfrm *
mlx5_accel_esp_create_xfrm(struct mlx5_core_dev *mdev,
			   const struct mlx5_accel_esp_xfrm_attrs *attrs,
			   u32 flags)
{
	struct mlx5_accel_esp_xfrm *xfrm;

	xfrm = mlx5_fpga_esp_create_xfrm(mdev, attrs, flags);
	if (IS_ERR(xfrm))
		return xfrm;

	xfrm->mdev = mdev;
	return xfrm;
}
EXPORT_SYMBOL_GPL(mlx5_accel_esp_create_xfrm);

void mlx5_accel_esp_destroy_xfrm(struct mlx5_accel_esp_xfrm *xfrm)
{
	mlx5_fpga_esp_destroy_xfrm(xfrm);
}
EXPORT_SYMBOL_GPL(mlx5_accel_esp_destroy_xfrm);

int mlx5_accel_esp_modify_xfrm(struct mlx5_accel_esp_xfrm *xfrm,
			       const struct mlx5_accel_esp_xfrm_attrs *attrs)
{
	return mlx5_fpga_esp_modify_xfrm(xfrm, attrs);
}
EXPORT_SYMBOL_GPL(mlx5_accel_esp_modify_xfrm);
