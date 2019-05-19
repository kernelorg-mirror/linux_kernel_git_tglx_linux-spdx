/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2004 Mellanox Technologies Ltd.  All rights reserved.
 * Copyright (c) 2004 Infinicon Corporation.  All rights reserved.
 * Copyright (c) 2004 Intel Corporation.  All rights reserved.
 * Copyright (c) 2004 Topspin Corporation.  All rights reserved.
 * Copyright (c) 2004-2007 Voltaire Corporation.  All rights reserved.
 */

#ifndef __SMI_H_
#define __SMI_H_

#include <rdma/ib_smi.h>

enum smi_action {
	IB_SMI_DISCARD,
	IB_SMI_HANDLE
};

enum smi_forward_action {
	IB_SMI_LOCAL,	/* SMP should be completed up the stack */
	IB_SMI_SEND,	/* received DR SMP should be forwarded to the send queue */
	IB_SMI_FORWARD	/* SMP should be forwarded (for switches only) */
};

enum smi_action smi_handle_dr_smp_recv(struct ib_smp *smp, bool is_switch,
				       int port_num, int phys_port_cnt);
int smi_get_fwd_port(struct ib_smp *smp);
extern enum smi_forward_action smi_check_forward_dr_smp(struct ib_smp *smp);
extern enum smi_action smi_handle_dr_smp_send(struct ib_smp *smp,
					      bool is_switch, int port_num);

/*
 * Return IB_SMI_HANDLE if the SMP should be handled by the local SMA/SM
 * via process_mad
 */
static inline enum smi_action smi_check_local_smp(struct ib_smp *smp,
						  struct ib_device *device)
{
	/* C14-9:3 -- We're at the end of the DR segment of path */
	/* C14-9:4 -- Hop Pointer = Hop Count + 1 -> give to SMA/SM */
	return ((device->ops.process_mad &&
		!ib_get_smp_direction(smp) &&
		(smp->hop_ptr == smp->hop_cnt + 1)) ?
		IB_SMI_HANDLE : IB_SMI_DISCARD);
}

/*
 * Return IB_SMI_HANDLE if the SMP should be handled by the local SMA/SM
 * via process_mad
 */
static inline enum smi_action smi_check_local_returning_smp(struct ib_smp *smp,
						   struct ib_device *device)
{
	/* C14-13:3 -- We're at the end of the DR segment of path */
	/* C14-13:4 -- Hop Pointer == 0 -> give to SM */
	return ((device->ops.process_mad &&
		ib_get_smp_direction(smp) &&
		!smp->hop_ptr) ? IB_SMI_HANDLE : IB_SMI_DISCARD);
}

#endif	/* __SMI_H_ */
