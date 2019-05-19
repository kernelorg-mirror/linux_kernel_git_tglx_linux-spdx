/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2013, Cisco Systems, Inc. All rights reserved.
 */
#ifndef USNIC_DEBUGFS_H_
#define USNIC_DEBUGFS_H_

#include "usnic_ib_qp_grp.h"

void usnic_debugfs_init(void);

void usnic_debugfs_exit(void);
void usnic_debugfs_flow_add(struct usnic_ib_qp_grp_flow *qp_flow);
void usnic_debugfs_flow_remove(struct usnic_ib_qp_grp_flow *qp_flow);

#endif /*!USNIC_DEBUGFS_H_ */
