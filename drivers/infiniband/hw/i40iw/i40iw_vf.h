/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*******************************************************************************
*
* Copyright (c) 2015-2016 Intel Corporation.  All rights reserved.
*
*******************************************************************************/

#ifndef I40IW_VF_H
#define I40IW_VF_H

struct i40iw_sc_cqp;

struct i40iw_manage_vf_pble_info {
	u32 sd_index;
	u16 first_pd_index;
	u16 pd_entry_cnt;
	u8 inv_pd_ent;
	u64 pd_pl_pba;
};

struct i40iw_vf_cqp_ops {
	enum i40iw_status_code (*manage_vf_pble_bp)(struct i40iw_sc_cqp *,
						    struct i40iw_manage_vf_pble_info *,
						    u64,
						    bool);
};

enum i40iw_status_code i40iw_manage_vf_pble_bp(struct i40iw_sc_cqp *cqp,
					       struct i40iw_manage_vf_pble_info *info,
					       u64 scratch,
					       bool post_sq);

extern const struct i40iw_vf_cqp_ops iw_vf_cqp_ops;

#endif
