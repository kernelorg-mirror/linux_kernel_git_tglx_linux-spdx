// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright 2000, 2007-2008 MontaVista Software Inc.
 * Author: MontaVista Software, Inc. <source@mvista.com
 *
 * Updates to 2.6, Pete Popov, Embedded Alley Solutions, Inc.
 */

#include <linux/init.h>
#include <linux/ioport.h>

#include <asm/dma-coherence.h>
#include <asm/mipsregs.h>

#include <au1000.h>

extern void __init board_setup(void);
extern void __init alchemy_set_lpj(void);

void __init plat_mem_setup(void)
{
	alchemy_set_lpj();

	if (au1xxx_cpu_needs_config_od())
		/* Various early Au1xx0 errata corrected by this */
		set_c0_config(1 << 19); /* Set Config[OD] */
	else
		/* Clear to obtain best system bus performance */
		clear_c0_config(1 << 19); /* Clear Config[OD] */

	hw_coherentio = 0;
	coherentio = IO_COHERENCE_ENABLED;
	switch (alchemy_get_cputype()) {
	case ALCHEMY_CPU_AU1000:
	case ALCHEMY_CPU_AU1500:
	case ALCHEMY_CPU_AU1100:
		coherentio = IO_COHERENCE_DISABLED;
		break;
	case ALCHEMY_CPU_AU1200:
		/* Au1200 AB USB does not support coherent memory */
		if (0 == (read_c0_prid() & PRID_REV_MASK))
			coherentio = IO_COHERENCE_DISABLED;
		break;
	}

	board_setup();	/* board specific setup */

	/* IO/MEM resources. */
	set_io_port_base(0);
	ioport_resource.start = IOPORT_RESOURCE_START;
	ioport_resource.end = IOPORT_RESOURCE_END;
	iomem_resource.start = IOMEM_RESOURCE_START;
	iomem_resource.end = IOMEM_RESOURCE_END;
}

#if defined(CONFIG_PHYS_ADDR_T_64BIT) && defined(CONFIG_PCI)
/* This routine should be valid for all Au1x based boards */
phys_addr_t __fixup_bigphys_addr(phys_addr_t phys_addr, phys_addr_t size)
{
	unsigned long start = ALCHEMY_PCI_MEMWIN_START;
	unsigned long end = ALCHEMY_PCI_MEMWIN_END;

	/* Don't fixup 36-bit addresses */
	if ((phys_addr >> 32) != 0)
		return phys_addr;

	/* Check for PCI memory window */
	if (phys_addr >= start && (phys_addr + size - 1) <= end)
		return (phys_addr_t)(AU1500_PCI_MEM_PHYS_ADDR + phys_addr);

	/* default nop */
	return phys_addr;
}
EXPORT_SYMBOL(__fixup_bigphys_addr);
#endif
