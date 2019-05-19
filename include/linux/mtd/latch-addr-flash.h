/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Interface for NOR flash driver whose high address lines are latched
 *
 * Copyright © 2008 MontaVista Software, Inc. <source@mvista.com>
 */
#ifndef __LATCH_ADDR_FLASH__
#define __LATCH_ADDR_FLASH__

struct map_info;
struct mtd_partition;

struct latch_addr_flash_data {
	unsigned int		width;
	unsigned int		size;

	int			(*init)(void *data, int cs);
	void			(*done)(void *data);
	void			(*set_window)(unsigned long offset, void *data);
	void			*data;

	unsigned int		nr_parts;
	struct mtd_partition	*parts;
};

#endif
