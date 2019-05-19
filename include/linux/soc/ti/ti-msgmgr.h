/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Texas Instruments' Message Manager
 *
 * Copyright (C) 2015-2016 Texas Instruments Incorporated - http://www.ti.com/
 *	Nishanth Menon
 */

#ifndef TI_MSGMGR_H
#define TI_MSGMGR_H

/**
 * struct ti_msgmgr_message - Message Manager structure
 * @len: Length of data in the Buffer
 * @buf: Buffer pointer
 *
 * This is the structure for data used in mbox_send_message
 * the length of data buffer used depends on the SoC integration
 * parameters - each message may be 64, 128 bytes long depending
 * on SoC. Client is supposed to be aware of this.
 */
struct ti_msgmgr_message {
	size_t len;
	u8 *buf;
};

#endif /* TI_MSGMGR_H */
