/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2018 Mellanox Technologies. All rights reserved.
 */

#ifndef __MLX5_FPGA_TLS_H__
#define __MLX5_FPGA_TLS_H__

#include <linux/mlx5/driver.h>

#include <net/tls.h>
#include "fpga/core.h"

struct mlx5_fpga_tls {
	struct list_head pending_cmds;
	spinlock_t pending_cmds_lock; /* Protects pending_cmds */
	u32 caps;
	struct mlx5_fpga_conn *conn;

	struct idr tx_idr;
	struct idr rx_idr;
	spinlock_t tx_idr_spinlock; /* protects the IDR */
	spinlock_t rx_idr_spinlock; /* protects the IDR */
};

int mlx5_fpga_tls_add_flow(struct mlx5_core_dev *mdev, void *flow,
			   struct tls_crypto_info *crypto_info,
			   u32 start_offload_tcp_sn, u32 *p_swid,
			   bool direction_sx);

void mlx5_fpga_tls_del_flow(struct mlx5_core_dev *mdev, u32 swid,
			    gfp_t flags, bool direction_sx);

bool mlx5_fpga_is_tls_device(struct mlx5_core_dev *mdev);
int mlx5_fpga_tls_init(struct mlx5_core_dev *mdev);
void mlx5_fpga_tls_cleanup(struct mlx5_core_dev *mdev);

static inline u32 mlx5_fpga_tls_device_caps(struct mlx5_core_dev *mdev)
{
	return mdev->fpga->tls->caps;
}

int mlx5_fpga_tls_resync_rx(struct mlx5_core_dev *mdev, u32 handle, u32 seq,
			    u64 rcd_sn);

#endif /* __MLX5_FPGA_TLS_H__ */
