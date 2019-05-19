/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * This file is part of the Chelsio T4/T5/T6 Ethernet driver for Linux.
 *
 * Copyright (c) 2017 Chelsio Communications, Inc. All rights reserved.
 */

#ifndef __T4_TCB_H
#define __T4_TCB_H

#define TCB_SMAC_SEL_W		0
#define TCB_SMAC_SEL_S		24
#define TCB_SMAC_SEL_M		0xffULL
#define TCB_SMAC_SEL_V(x)	((x) << TCB_SMAC_SEL_S)

#define TCB_T_FLAGS_W		1
#define TCB_T_FLAGS_S		0
#define TCB_T_FLAGS_M		0xffffffffffffffffULL
#define TCB_T_FLAGS_V(x)	((__u64)(x) << TCB_T_FLAGS_S)

#define TCB_RQ_START_W		30
#define TCB_RQ_START_S		0
#define TCB_RQ_START_M		0x3ffffffULL
#define TCB_RQ_START_V(x)	((x) << TCB_RQ_START_S)

#define TF_CCTRL_ECE_S		60
#define TF_CCTRL_CWR_S		61
#define TF_CCTRL_RFR_S		62

#define TCB_RSS_INFO_W		3
#define TCB_RSS_INFO_S		0
#define TCB_RSS_INFO_M		0x3ffULL
#define TCB_RSS_INFO_V(x)	((x) << TCB_RSS_INFO_S)

#define TCB_TIMESTAMP_W		5
#define TCB_TIMESTAMP_S		0
#define TCB_TIMESTAMP_M		0xffffffffULL
#define TCB_TIMESTAMP_V(x)	((x) << TCB_TIMESTAMP_S)

#define TCB_RTT_TS_RECENT_AGE_W		6
#define TCB_RTT_TS_RECENT_AGE_S		0
#define TCB_RTT_TS_RECENT_AGE_M		0xffffffffULL
#define TCB_RTT_TS_RECENT_AGE_V(x)	((x) << TCB_RTT_TS_RECENT_AGE_S)

#define TCB_SND_UNA_RAW_W	10
#define TCB_RX_FRAG2_PTR_RAW_W	27
#define TCB_RX_FRAG3_LEN_RAW_W	29
#define TCB_RX_FRAG3_START_IDX_OFFSET_RAW_W	30
#define TCB_PDU_HDR_LEN_W	31

#define TF_RX_PDU_OUT_S		49
#define TF_RX_PDU_OUT_V(x)	((__u64)(x) << TF_RX_PDU_OUT_S)

#endif /* __T4_TCB_H */
