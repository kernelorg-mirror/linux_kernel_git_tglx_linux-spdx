/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * This file is part of the Chelsio T4 Ethernet driver for Linux.
 *
 * Copyright (c) 2003-2014 Chelsio Communications, Inc. All rights reserved.
 */

#ifndef __CXGB4_DEBUGFS_H
#define __CXGB4_DEBUGFS_H

#include <linux/export.h>

struct t4_debugfs_entry {
	const char *name;
	const struct file_operations *ops;
	umode_t mode;
	unsigned char data;
};

struct seq_tab {
	int (*show)(struct seq_file *seq, void *v, int idx);
	unsigned int rows;        /* # of entries */
	unsigned char width;      /* size in bytes of each entry */
	unsigned char skip_first; /* whether the first line is a header */
	char data[0];             /* the table data */
};

static inline unsigned int hex2val(char c)
{
	return isdigit(c) ? c - '0' : tolower(c) - 'a' + 10;
}

struct seq_tab *seq_open_tab(struct file *f, unsigned int rows,
			     unsigned int width, unsigned int have_header,
			     int (*show)(struct seq_file *seq, void *v, int i));

int t4_setup_debugfs(struct adapter *adap);
void add_debugfs_files(struct adapter *adap,
		       struct t4_debugfs_entry *files,
		       unsigned int nfiles);
int mem_open(struct inode *inode, struct file *file);

#endif
