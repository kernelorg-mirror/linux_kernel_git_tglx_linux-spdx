// SPDX-License-Identifier: GPL-2.0-or-later
/*
 *  Copyright (C) 2004 Florian Schirmer <jolt@tuxbox.org>
 */

#include "bcm47xx_private.h"

#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <asm/setup.h>
#include <asm/irq_cpu.h>
#include <bcm47xx.h>

asmlinkage void plat_irq_dispatch(void)
{
	u32 cause;

	cause = read_c0_cause() & read_c0_status() & CAUSEF_IP;

	clear_c0_status(cause);

	if (cause & CAUSEF_IP7)
		do_IRQ(7);
	if (cause & CAUSEF_IP2)
		do_IRQ(2);
	if (cause & CAUSEF_IP3)
		do_IRQ(3);
	if (cause & CAUSEF_IP4)
		do_IRQ(4);
	if (cause & CAUSEF_IP5)
		do_IRQ(5);
	if (cause & CAUSEF_IP6)
		do_IRQ(6);
}

#define DEFINE_HWx_IRQDISPATCH(x)					\
	static void bcm47xx_hw ## x ## _irqdispatch(void)		\
	{								\
		do_IRQ(x);						\
	}
DEFINE_HWx_IRQDISPATCH(2)
DEFINE_HWx_IRQDISPATCH(3)
DEFINE_HWx_IRQDISPATCH(4)
DEFINE_HWx_IRQDISPATCH(5)
DEFINE_HWx_IRQDISPATCH(6)
DEFINE_HWx_IRQDISPATCH(7)

void __init arch_init_irq(void)
{
	/*
	 * This is the first arch callback after mm_init (we can use kmalloc),
	 * so let's finish bus initialization now.
	 */
	bcm47xx_bus_setup();

#ifdef CONFIG_BCM47XX_BCMA
	if (bcm47xx_bus_type == BCM47XX_BUS_TYPE_BCMA) {
		bcma_write32(bcm47xx_bus.bcma.bus.drv_mips.core,
			     BCMA_MIPS_MIPS74K_INTMASK(5), 1 << 31);
		/*
		 * the kernel reads the timer irq from some register and thinks
		 * it's #5, but we offset it by 2 and route to #7
		 */
		cp0_compare_irq = 7;
	}
#endif
	mips_cpu_irq_init();

	if (cpu_has_vint) {
		pr_info("Setting up vectored interrupts\n");
		set_vi_handler(2, bcm47xx_hw2_irqdispatch);
		set_vi_handler(3, bcm47xx_hw3_irqdispatch);
		set_vi_handler(4, bcm47xx_hw4_irqdispatch);
		set_vi_handler(5, bcm47xx_hw5_irqdispatch);
		set_vi_handler(6, bcm47xx_hw6_irqdispatch);
		set_vi_handler(7, bcm47xx_hw7_irqdispatch);
	}
}
