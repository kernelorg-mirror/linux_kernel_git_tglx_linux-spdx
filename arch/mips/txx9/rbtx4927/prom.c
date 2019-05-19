// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * rbtx4927 specific prom routines
 *
 * Author: MontaVista Software, Inc.
 *	   source@mvista.com
 *
 * Copyright 2001-2002 MontaVista Software Inc.
 *
 * Copyright (C) 2004 MontaVista Software Inc.
 * Author: Manish Lachwani, mlachwani@mvista.com
 */
#include <linux/init.h>
#include <asm/bootinfo.h>
#include <asm/txx9/generic.h>
#include <asm/txx9/rbtx4927.h>

void __init rbtx4927_prom_init(void)
{
	add_memory_region(0, tx4927_get_mem_size(), BOOT_MEM_RAM);
	txx9_sio_putchar_init(TX4927_SIO_REG(0) & 0xfffffffffULL);
}
