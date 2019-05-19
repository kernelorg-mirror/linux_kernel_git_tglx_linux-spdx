/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2015, Marvell International Ltd.
 */

#ifndef _NFCMRVL_PTF_H_
#define _NFCMRVL_PTF_H_

struct nfcmrvl_platform_data {
	/*
	 * Generic
	 */

	/* GPIO that is wired to RESET_N signal */
	int reset_n_io;
	/* Tell if transport is muxed in HCI one */
	unsigned int hci_muxed;

	/*
	 * UART specific
	 */

	/* Tell if UART needs flow control at init */
	unsigned int flow_control;
	/* Tell if firmware supports break control for power management */
	unsigned int break_control;


	/*
	 * I2C specific
	 */

	unsigned int irq;
	unsigned int irq_polarity;
};

#endif /* _NFCMRVL_PTF_H_ */
