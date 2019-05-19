/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * arch/arm/mach-w90x900/include/mach/entry-macro.S
 *
 * Low-level IRQ helper macros for W90P910-based platforms
 */

#include <mach/hardware.h>
#include <mach/regs-irq.h>

	.macro  get_irqnr_preamble, base, tmp
	.endm

	.macro	get_irqnr_and_base, irqnr, irqstat, base, tmp

		mov	\base, #AIC_BA

		ldr	\irqnr, [\base, #AIC_IPER]
		ldr	\irqnr, [\base, #AIC_ISNR]
		cmp	\irqnr, #0

	.endm
