// SPDX-License-Identifier: GPL-2.0-or-later
/*
 *
 * BRIEF MODULE DESCRIPTION
 *      Board specific pci fixups for the Toshiba rbtx4927
 *
 * Copyright 2001 MontaVista Software Inc.
 * Author: MontaVista Software, Inc.
 *              ppopov@mvista.com or source@mvista.com
 *
 * Copyright (C) 2000-2001 Toshiba Corporation
 *
 * Copyright (C) 2004 MontaVista Software Inc.
 * Author: Manish Lachwani (mlachwani@mvista.com)
 */
#include <linux/types.h>
#include <asm/txx9/pci.h>
#include <asm/txx9/rbtx4927.h>

int rbtx4927_pci_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	unsigned char irq = pin;

	/* IRQ rotation */
	irq--;			/* 0-3 */
	if (slot == TX4927_PCIC_IDSEL_AD_TO_SLOT(23)) {
		/* PCI CardSlot (IDSEL=A23) */
		/* PCIA => PCIA */
		irq = (irq + 0 + slot) % 4;
	} else {
		/* PCI Backplane */
		if (txx9_pci_option & TXX9_PCI_OPT_PICMG)
			irq = (irq + 33 - slot) % 4;
		else
			irq = (irq + 3 + slot) % 4;
	}
	irq++;	/* 1-4 */

	switch (irq) {
	case 1:
		irq = RBTX4927_IRQ_IOC_PCIA;
		break;
	case 2:
		irq = RBTX4927_IRQ_IOC_PCIB;
		break;
	case 3:
		irq = RBTX4927_IRQ_IOC_PCIC;
		break;
	case 4:
		irq = RBTX4927_IRQ_IOC_PCID;
		break;
	}
	return irq;
}
