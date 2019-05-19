/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Xilinx pci external definitions
 *
 * Copyright 2009 Roderick Colenbrander
 * Copyright 2009 Secret Lab Technologies Ltd.
 */

#ifndef INCLUDE_XILINX_PCI
#define INCLUDE_XILINX_PCI

#ifdef CONFIG_XILINX_PCI
extern void __init xilinx_pci_init(void);
#else
static inline void __init xilinx_pci_init(void) { return; }
#endif

#endif /* INCLUDE_XILINX_PCI */
