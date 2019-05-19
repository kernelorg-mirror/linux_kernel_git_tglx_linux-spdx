/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2018 Mellanox Technologies. All rights reserved.
 */

#ifndef __MLX5_ACCEL_TLS_H__
#define __MLX5_ACCEL_TLS_H__

#include <linux/mlx5/driver.h>
#include <linux/tls.h>

#ifdef CONFIG_MLX5_ACCEL

enum {
	MLX5_ACCEL_TLS_TX = BIT(0),
	MLX5_ACCEL_TLS_RX = BIT(1),
	MLX5_ACCEL_TLS_V12 = BIT(2),
	MLX5_ACCEL_TLS_V13 = BIT(3),
	MLX5_ACCEL_TLS_LRO = BIT(4),
	MLX5_ACCEL_TLS_IPV6 = BIT(5),
	MLX5_ACCEL_TLS_AES_GCM128 = BIT(30),
	MLX5_ACCEL_TLS_AES_GCM256 = BIT(31),
};

struct mlx5_ifc_tls_flow_bits {
	u8         src_port[0x10];
	u8         dst_port[0x10];
	union mlx5_ifc_ipv6_layout_ipv4_layout_auto_bits src_ipv4_src_ipv6;
	union mlx5_ifc_ipv6_layout_ipv4_layout_auto_bits dst_ipv4_dst_ipv6;
	u8         ipv6[0x1];
	u8         direction_sx[0x1];
	u8         reserved_at_2[0x1e];
};

int mlx5_accel_tls_add_flow(struct mlx5_core_dev *mdev, void *flow,
			    struct tls_crypto_info *crypto_info,
			    u32 start_offload_tcp_sn, u32 *p_swid,
			    bool direction_sx);
void mlx5_accel_tls_del_flow(struct mlx5_core_dev *mdev, u32 swid,
			     bool direction_sx);
int mlx5_accel_tls_resync_rx(struct mlx5_core_dev *mdev, u32 handle, u32 seq,
			     u64 rcd_sn);
bool mlx5_accel_is_tls_device(struct mlx5_core_dev *mdev);
u32 mlx5_accel_tls_device_caps(struct mlx5_core_dev *mdev);
int mlx5_accel_tls_init(struct mlx5_core_dev *mdev);
void mlx5_accel_tls_cleanup(struct mlx5_core_dev *mdev);

#else

static inline int
mlx5_accel_tls_add_flow(struct mlx5_core_dev *mdev, void *flow,
			struct tls_crypto_info *crypto_info,
			u32 start_offload_tcp_sn, u32 *p_swid,
			bool direction_sx) { return -ENOTSUPP; }
static inline void mlx5_accel_tls_del_flow(struct mlx5_core_dev *mdev, u32 swid,
					   bool direction_sx) { }
static inline int mlx5_accel_tls_resync_rx(struct mlx5_core_dev *mdev, u32 handle,
					   u32 seq, u64 rcd_sn) { return 0; }
static inline bool mlx5_accel_is_tls_device(struct mlx5_core_dev *mdev) { return false; }
static inline u32 mlx5_accel_tls_device_caps(struct mlx5_core_dev *mdev) { return 0; }
static inline int mlx5_accel_tls_init(struct mlx5_core_dev *mdev) { return 0; }
static inline void mlx5_accel_tls_cleanup(struct mlx5_core_dev *mdev) { }

#endif

#endif	/* __MLX5_ACCEL_TLS_H__ */
