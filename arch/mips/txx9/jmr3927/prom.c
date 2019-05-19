// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * BRIEF MODULE DESCRIPTION
 *    PROM library initialisation code, assuming a version of
 *    pmon is the boot code.
 *
 * Copyright 2001 MontaVista Software Inc.
 * Author: MontaVista Software, Inc.
 *              ahennessy@mvista.com
 *
 * Based on arch/mips/au1000/common/prom.c
 *
 * This file was derived from Carsten Langgaard's
 * arch/mips/mips-boards/xx files.
 *
 * Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 1999,2000 MIPS Technologies, Inc.  All rights reserved.
 */
#include <linux/init.h>
#include <linux/kernel.h>
#include <asm/bootinfo.h>
#include <asm/txx9/generic.h>
#include <asm/txx9/jmr3927.h>

void __init jmr3927_prom_init(void)
{
	/* CCFG */
	if ((tx3927_ccfgptr->ccfg & TX3927_CCFG_TLBOFF) == 0)
		pr_err("TX3927 TLB off\n");

	add_memory_region(0, JMR3927_SDRAM_SIZE, BOOT_MEM_RAM);
	txx9_sio_putchar_init(TX3927_SIO_REG(1));
}
