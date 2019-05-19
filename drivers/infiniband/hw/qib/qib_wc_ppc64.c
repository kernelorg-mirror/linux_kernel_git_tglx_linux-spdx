// SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB
/*
 * Copyright (c) 2006, 2007, 2008 QLogic Corporation. All rights reserved.
 */

/*
 * This file is conditionally built on PowerPC only.  Otherwise weak symbol
 * versions of the functions exported from here are used.
 */

#include "qib.h"

/**
 * qib_enable_wc - enable write combining for MMIO writes to the device
 * @dd: qlogic_ib device
 *
 * Nothing to do on PowerPC, so just return without error.
 */
int qib_enable_wc(struct qib_devdata *dd)
{
	return 0;
}

/**
 * qib_unordered_wc - indicate whether write combining is unordered
 *
 * Because our performance depends on our ability to do write
 * combining mmio writes in the most efficient way, we need to
 * know if we are on a processor that may reorder stores when
 * write combining.
 */
int qib_unordered_wc(void)
{
	return 1;
}
