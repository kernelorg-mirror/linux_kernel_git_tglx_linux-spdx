/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
#ifndef _QIB_DEBUGFS_H
#define _QIB_DEBUGFS_H

#ifdef CONFIG_DEBUG_FS
/*
 * Copyright (c) 2013 Intel Corporation.  All rights reserved.
 */

struct qib_ibdev;
void qib_dbg_ibdev_init(struct qib_ibdev *ibd);
void qib_dbg_ibdev_exit(struct qib_ibdev *ibd);
void qib_dbg_init(void);
void qib_dbg_exit(void);

#endif

#endif                          /* _QIB_DEBUGFS_H */
