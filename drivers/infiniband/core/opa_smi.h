/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2014 Intel Corporation.  All rights reserved.
 */

#ifndef __OPA_SMI_H_
#define __OPA_SMI_H_

#include <rdma/ib_smi.h>
#include <rdma/opa_smi.h>

#include "smi.h"

enum smi_action opa_smi_handle_dr_smp_recv(struct opa_smp *smp, bool is_switch,
				       int port_num, int phys_port_cnt);
int opa_smi_get_fwd_port(struct opa_smp *smp);
extern enum smi_forward_action opa_smi_check_forward_dr_smp(struct opa_smp *smp);
extern enum smi_action opa_smi_handle_dr_smp_send(struct opa_smp *smp,
					      bool is_switch, int port_num);

/*
 * Return IB_SMI_HANDLE if the SMP should be handled by the local SMA/SM
 * via process_mad
 */
static inline enum smi_action opa_smi_check_local_smp(struct opa_smp *smp,
						      struct ib_device *device)
{
	/* C14-9:3 -- We're at the end of the DR segment of path */
	/* C14-9:4 -- Hop Pointer = Hop Count + 1 -> give to SMA/SM */
	return (device->ops.process_mad &&
		!opa_get_smp_direction(smp) &&
		(smp->hop_ptr == smp->hop_cnt + 1)) ?
		IB_SMI_HANDLE : IB_SMI_DISCARD;
}

/*
 * Return IB_SMI_HANDLE if the SMP should be handled by the local SMA/SM
 * via process_mad
 */
static inline enum smi_action opa_smi_check_local_returning_smp(struct opa_smp *smp,
								struct ib_device *device)
{
	/* C14-13:3 -- We're at the end of the DR segment of path */
	/* C14-13:4 -- Hop Pointer == 0 -> give to SM */
	return (device->ops.process_mad &&
		opa_get_smp_direction(smp) &&
		!smp->hop_ptr) ? IB_SMI_HANDLE : IB_SMI_DISCARD;
}

#endif	/* __OPA_SMI_H_ */
