/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * USB related definitions
 *
 * Copyright (C) 2009 MontaVista Software, Inc. <source@mvista.com>
 */

#ifndef __ASM_ARCH_USB_H
#define __ASM_ARCH_USB_H

/* Passed as the platform data to the OHCI driver */
struct	da8xx_ohci_root_hub {
	/* Time from power on to power good (in 2 ms units) */
	u8	potpgt;
};

void davinci_setup_usb(unsigned mA, unsigned potpgt_ms);

#endif	/* ifndef __ASM_ARCH_USB_H */
