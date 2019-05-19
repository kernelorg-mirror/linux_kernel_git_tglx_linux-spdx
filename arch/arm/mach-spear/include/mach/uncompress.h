/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * arch/arm/plat-spear/include/plat/uncompress.h
 *
 * Serial port stubs for kernel decompress status messages
 *
 * Copyright (C) 2009 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 */

#include <linux/io.h>
#include <linux/amba/serial.h>
#include <mach/spear.h>

#ifndef __PLAT_UNCOMPRESS_H
#define __PLAT_UNCOMPRESS_H
/*
 * This does not append a newline
 */
static inline void putc(int c)
{
	void __iomem *base = (void __iomem *)SPEAR_DBG_UART_BASE;

	while (readl_relaxed(base + UART01x_FR) & UART01x_FR_TXFF)
		barrier();

	writel_relaxed(c, base + UART01x_DR);
}

static inline void flush(void)
{
}

/*
 * nothing to do
 */
#define arch_decomp_setup()

#endif /* __PLAT_UNCOMPRESS_H */
