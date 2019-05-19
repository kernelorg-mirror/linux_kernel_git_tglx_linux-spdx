/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2007 Cisco Systems, Inc.  All rights reserved.
 */

#ifndef MLX4_SRQ_H
#define MLX4_SRQ_H

struct mlx4_wqe_srq_next_seg {
	u16			reserved1;
	__be16			next_wqe_index;
	u32			reserved2[3];
};

struct mlx4_srq *mlx4_srq_lookup(struct mlx4_dev *dev, u32 srqn);

#endif /* MLX4_SRQ_H */
