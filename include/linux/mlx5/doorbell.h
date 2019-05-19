/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2013-2015, Mellanox Technologies. All rights reserved.
 */

#ifndef MLX5_DOORBELL_H
#define MLX5_DOORBELL_H

#define MLX5_BF_OFFSET	      0x800
#define MLX5_CQ_DOORBELL      0x20

/* Assume that we can just write a 64-bit doorbell atomically.  s390
 * actually doesn't have writeq() but S/390 systems don't even have
 * PCI so we won't worry about it.
 *
 * Note that the write is not atomic on 32-bit systems! In contrast to 64-bit
 * ones, it requires proper locking. mlx5_write64 doesn't do any locking, so use
 * it at your own discretion, protected by some kind of lock on 32 bits.
 *
 * TODO: use write{q,l}_relaxed()
 */

static inline void mlx5_write64(__be32 val[2], void __iomem *dest)
{
#if BITS_PER_LONG == 64
	__raw_writeq(*(u64 *)val, dest);
#else
	__raw_writel((__force u32) val[0], dest);
	__raw_writel((__force u32) val[1], dest + 4);
#endif
}

#endif /* MLX5_DOORBELL_H */
