/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Sun Microsystems, Inc. All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
 */

#ifndef MLX4_DOORBELL_H
#define MLX4_DOORBELL_H

#include <linux/types.h>
#include <linux/io.h>

#define MLX4_SEND_DOORBELL    0x14
#define MLX4_CQ_DOORBELL      0x20

#if BITS_PER_LONG == 64
/*
 * Assume that we can just write a 64-bit doorbell atomically.  s390
 * actually doesn't have writeq() but S/390 systems don't even have
 * PCI so we won't worry about it.
 */

#define MLX4_DECLARE_DOORBELL_LOCK(name)
#define MLX4_INIT_DOORBELL_LOCK(ptr)    do { } while (0)
#define MLX4_GET_DOORBELL_LOCK(ptr)      (NULL)

static inline void mlx4_write64(__be32 val[2], void __iomem *dest,
				spinlock_t *doorbell_lock)
{
	__raw_writeq(*(u64 *) val, dest);
}

#else

/*
 * Just fall back to a spinlock to protect the doorbell if
 * BITS_PER_LONG is 32 -- there's no portable way to do atomic 64-bit
 * MMIO writes.
 */

#define MLX4_DECLARE_DOORBELL_LOCK(name) spinlock_t name;
#define MLX4_INIT_DOORBELL_LOCK(ptr)     spin_lock_init(ptr)
#define MLX4_GET_DOORBELL_LOCK(ptr)      (ptr)

static inline void mlx4_write64(__be32 val[2], void __iomem *dest,
				spinlock_t *doorbell_lock)
{
	unsigned long flags;

	spin_lock_irqsave(doorbell_lock, flags);
	__raw_writel((__force u32) val[0], dest);
	__raw_writel((__force u32) val[1], dest + 4);
	spin_unlock_irqrestore(doorbell_lock, flags);
}

#endif

#endif /* MLX4_DOORBELL_H */
