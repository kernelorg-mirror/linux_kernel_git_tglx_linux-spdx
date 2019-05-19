/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * OpenRISC unwinder.h
 *
 * Architecture API for unwinding stacks.
 *
 * Copyright (C) 2017 Stafford Horne <shorne@gmail.com>
 */

#ifndef __ASM_OPENRISC_UNWINDER_H
#define __ASM_OPENRISC_UNWINDER_H

void unwind_stack(void *data, unsigned long *stack,
		  void (*trace)(void *data, unsigned long addr,
				int reliable));

#endif /* __ASM_OPENRISC_UNWINDER_H */
