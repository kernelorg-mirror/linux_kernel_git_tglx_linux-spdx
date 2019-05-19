/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2011 Texas Instruments Incorporated
 * Author: Mark Salter <msalter@redhat.com>
 */

#ifndef __ASM_C6X_SYSCALLS_H
#define __ASM_C6X_SYSCALLS_H

#include <linux/compiler.h>
#include <linux/linkage.h>
#include <linux/types.h>

/* The array of function pointers for syscalls. */
extern void *sys_call_table[];

/* The following are trampolines in entry.S to handle 64-bit arguments */
extern long sys_pread_c6x(unsigned int fd, char __user *buf,
			  size_t count, off_t pos_low, off_t pos_high);
extern long sys_pwrite_c6x(unsigned int fd, const char __user *buf,
			   size_t count, off_t pos_low, off_t pos_high);
extern long sys_truncate64_c6x(const char __user *path,
			       off_t length_low, off_t length_high);
extern long sys_ftruncate64_c6x(unsigned int fd,
			       off_t length_low, off_t length_high);
extern long sys_fadvise64_c6x(int fd, u32 offset_lo, u32 offset_hi,
			      u32 len, int advice);
extern long sys_fadvise64_64_c6x(int fd, u32 offset_lo, u32 offset_hi,
				u32 len_lo, u32 len_hi, int advice);
extern long sys_fallocate_c6x(int fd, int mode,
			      u32 offset_lo, u32 offset_hi,
			      u32 len_lo, u32 len_hi);
extern int sys_cache_sync(unsigned long s, unsigned long e);

#include <asm-generic/syscalls.h>

#endif /* __ASM_C6X_SYSCALLS_H */
