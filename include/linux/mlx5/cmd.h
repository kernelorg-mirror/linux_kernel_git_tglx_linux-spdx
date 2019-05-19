/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2013-2015, Mellanox Technologies. All rights reserved.
 */

#ifndef MLX5_CMD_H
#define MLX5_CMD_H

#include <linux/types.h>

struct manage_pages_layout {
	u64	ptr;
	u32	reserved;
	u16	num_entries;
	u16	func_id;
};


struct mlx5_cmd_alloc_uar_imm_out {
	u32	rsvd[3];
	u32	uarn;
};

#endif /* MLX5_CMD_H */
