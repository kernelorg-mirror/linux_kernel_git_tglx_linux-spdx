/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * arch/arm/mach-omap1/board-h2.h
 *
 * Hardware definitions for TI OMAP1610 H2 board.
 *
 * Cleanup for Linux-2.6 by Dirk Behme <dirk.behme@de.bosch.com>
 */

#ifndef __ASM_ARCH_OMAP_H2_H
#define __ASM_ARCH_OMAP_H2_H

#define H2_TPS_GPIO_BASE		(OMAP_MAX_GPIO_LINES + 16 /* MPUIO */)
#	define H2_TPS_GPIO_MMC_PWR_EN	(H2_TPS_GPIO_BASE + 3)

extern void h2_mmc_init(void);

#endif /*  __ASM_ARCH_OMAP_H2_H */

