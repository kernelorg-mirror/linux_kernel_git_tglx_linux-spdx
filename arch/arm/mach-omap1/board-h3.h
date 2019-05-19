/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * arch/arm/mach-omap1/board-h3.h
 *
 * Copyright (C) 2001 RidgeRun, Inc.
 * Copyright (C) 2004 Texas Instruments, Inc.
 */
#ifndef __ASM_ARCH_OMAP_H3_H
#define __ASM_ARCH_OMAP_H3_H

#define H3_TPS_GPIO_BASE		(OMAP_MAX_GPIO_LINES + 16 /* MPUIO */)
#	define H3_TPS_GPIO_MMC_PWR_EN	(H3_TPS_GPIO_BASE + 4)

extern void h3_mmc_init(void);

#endif /*  __ASM_ARCH_OMAP_H3_H */
