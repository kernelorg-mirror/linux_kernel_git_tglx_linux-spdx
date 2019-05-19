/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 *  Definitions for the PROM
 *
 *  Copyright 2002 Ryan Holm <ryan.holmQVist@idt.com>
 *  Copyright 2008 Florian Fainelli <florian@openwrt.org>
 */

#define PROM_ENTRY(x)		(0xbfc00000 + ((x) * 8))

#define SR_NMI			0x00180000
#define SERIAL_SPEED_ENTRY	0x00000001

#define FREQ_TAG		"HZ="
#define KMAC_TAG		"kmac="
#define MEM_TAG			"mem="
#define BOARD_TAG		"board="

#define BOARD_RB532		"500"
#define BOARD_RB532A		"500r5"
