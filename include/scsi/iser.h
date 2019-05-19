/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2015 Mellanox Technologies. All rights reserved.
 */
#ifndef ISCSI_ISER_H
#define ISCSI_ISER_H

#define ISER_ZBVA_NOT_SUP		0x80
#define ISER_SEND_W_INV_NOT_SUP		0x40
#define ISERT_ZBVA_NOT_USED		0x80
#define ISERT_SEND_W_INV_NOT_USED	0x40

#define ISCSI_CTRL	0x10
#define ISER_HELLO	0x20
#define ISER_HELLORPLY	0x30

#define ISER_VER	0x10
#define ISER_WSV	0x08
#define ISER_RSV	0x04

/**
 * struct iser_cm_hdr - iSER CM header (from iSER Annex A12)
 *
 * @flags:        flags support (zbva, send_w_inv)
 * @rsvd:         reserved
 */
struct iser_cm_hdr {
	u8      flags;
	u8      rsvd[3];
} __packed;

/**
 * struct iser_ctrl - iSER header of iSCSI control PDU
 *
 * @flags:        opcode and read/write valid bits
 * @rsvd:         reserved
 * @write_stag:   write rkey
 * @write_va:     write virtual address
 * @reaf_stag:    read rkey
 * @read_va:      read virtual address
 */
struct iser_ctrl {
	u8      flags;
	u8      rsvd[3];
	__be32  write_stag;
	__be64  write_va;
	__be32  read_stag;
	__be64  read_va;
} __packed;

#endif /* ISCSI_ISER_H */
