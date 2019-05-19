// SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB
/*
 * Copyright (c) 2009 QLogic Corporation. All rights reserved.
 */

#include "qib.h"

/**
 * qib_pio_copy - copy data to MMIO space, in multiples of 32-bits
 * @to: destination, in MMIO space (must be 64-bit aligned)
 * @from: source (must be 64-bit aligned)
 * @count: number of 32-bit quantities to copy
 *
 * Copy data from kernel space to MMIO space, in multiples of 32 bits at a
 * time.  Order of access is not guaranteed, nor is a memory barrier
 * performed afterwards.
 */
void qib_pio_copy(void __iomem *to, const void *from, size_t count)
{
#ifdef CONFIG_64BIT
	u64 __iomem *dst = to;
	const u64 *src = from;
	const u64 *end = src + (count >> 1);

	while (src < end)
		__raw_writeq(*src++, dst++);
	if (count & 1)
		__raw_writel(*(const u32 *)src, dst);
#else
	u32 __iomem *dst = to;
	const u32 *src = from;
	const u32 *end = src + count;

	while (src < end)
		__raw_writel(*src++, dst++);
#endif
}
