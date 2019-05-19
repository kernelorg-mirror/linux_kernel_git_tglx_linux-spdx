/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 *  linux/drivers/scsi/esas2r/esas2r_log.h
 *      For use with ATTO ExpressSAS R6xx SAS/SATA RAID controllers
 *
 *  Copyright (c) 2001-2013 ATTO Technology, Inc.
 *  (mailto:linuxdrivers@attotech.com)
 */

#ifndef __esas2r_log_h__
#define __esas2r_log_h__

struct device;

enum {
	ESAS2R_LOG_NONE = 0,    /* no events logged */
	ESAS2R_LOG_CRIT = 1,    /* critical events  */
	ESAS2R_LOG_WARN = 2,    /* warning events   */
	ESAS2R_LOG_INFO = 3,    /* info events      */
	ESAS2R_LOG_DEBG = 4,    /* debugging events */
	ESAS2R_LOG_TRCE = 5,    /* tracing events   */

#ifdef ESAS2R_TRACE
	ESAS2R_LOG_DFLT = ESAS2R_LOG_TRCE
#else
	ESAS2R_LOG_DFLT = ESAS2R_LOG_WARN
#endif
};

__printf(2, 3) int esas2r_log(const long level, const char *format, ...);
__printf(3, 4) int esas2r_log_dev(const long level,
		   const struct device *dev,
		   const char *format,
		   ...);
int esas2r_log_hexdump(const long level,
		       const void *buf,
		       size_t len);

/*
 * the following macros are provided specifically for debugging and tracing
 * messages.  esas2r_debug() is provided for generic non-hardware layer
 * debugging and tracing events.  esas2r_hdebug is provided specifically for
 * hardware layer debugging and tracing events.
 */

#ifdef ESAS2R_DEBUG
#define esas2r_debug(f, args ...) esas2r_log(ESAS2R_LOG_DEBG, f, ## args)
#define esas2r_hdebug(f, args ...) esas2r_log(ESAS2R_LOG_DEBG, f, ## args)
#else
#define esas2r_debug(f, args ...)
#define esas2r_hdebug(f, args ...)
#endif  /* ESAS2R_DEBUG */

/*
 * the following macros are provided in order to trace the driver and catch
 * some more serious bugs.  be warned, enabling these macros may *severely*
 * impact performance.
 */

#ifdef ESAS2R_TRACE
#define esas2r_bugon() \
	do { \
		esas2r_log(ESAS2R_LOG_TRCE, "esas2r_bugon() called in %s:%d" \
			   " - dumping stack and stopping kernel", __func__, \
			   __LINE__); \
		dump_stack(); \
		BUG(); \
	} while (0)

#define esas2r_trace_enter() esas2r_log(ESAS2R_LOG_TRCE, "entered %s (%s:%d)", \
					__func__, __FILE__, __LINE__)
#define esas2r_trace_exit() esas2r_log(ESAS2R_LOG_TRCE, "exited %s (%s:%d)", \
				       __func__, __FILE__, __LINE__)
#define esas2r_trace(f, args ...) esas2r_log(ESAS2R_LOG_TRCE, "(%s:%s:%d): " \
					     f, __func__, __FILE__, __LINE__, \
					     ## args)
#else
#define esas2r_bugon()
#define esas2r_trace_enter()
#define esas2r_trace_exit()
#define esas2r_trace(f, args ...)
#endif  /* ESAS2R_TRACE */

#endif  /* __esas2r_log_h__ */
