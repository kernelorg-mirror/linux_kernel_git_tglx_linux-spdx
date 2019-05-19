/* SPDX-License-Identifier: GPL-2.0-only */
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2017 Cavium, Inc.
 *
 * This file may also be available under a different license from Cavium.
 * Contact Cavium, Inc. for more information
 **********************************************************************/

/*! \file octeon_vf_main.h
 *  \brief Host Driver: This file defines vf_rep related macros and structures
 */
#ifndef __LIO_VF_REP_H__
#define __LIO_VF_REP_H__
#define LIO_VF_REP_REQ_TMO_MS 5000
#define LIO_VF_REP_STATS_POLL_TIME_MS 200

struct lio_vf_rep_desc {
	struct net_device *parent_ndev;
	struct net_device *ndev;
	struct octeon_device *oct;
	struct lio_vf_rep_stats stats;
	struct cavium_wk stats_wk;
	atomic_t ifstate;
	int ifidx;
};

struct lio_vf_rep_sc_ctx {
	struct completion complete;
};

int lio_vf_rep_create(struct octeon_device *oct);
void lio_vf_rep_destroy(struct octeon_device *oct);
int lio_vf_rep_modinit(void);
void lio_vf_rep_modexit(void);
#endif
