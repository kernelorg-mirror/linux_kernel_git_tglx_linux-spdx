// SPDX-License-Identifier: GPL-2.0-only
/*
   BlueZ - Bluetooth protocol stack for Linux
   Copyright (C) 2000-2001 Qualcomm Incorporated

   Written 2000,2001 by Maxim Krasnyansky <maxk@qualcomm.com>

*/

/* Bluetooth kernel library. */

#define pr_fmt(fmt) "Bluetooth: " fmt

#include <linux/export.h>

#include <net/bluetooth/bluetooth.h>

void baswap(bdaddr_t *dst, const bdaddr_t *src)
{
	const unsigned char *s = (const unsigned char *)src;
	unsigned char *d = (unsigned char *)dst;
	unsigned int i;

	for (i = 0; i < 6; i++)
		d[i] = s[5 - i];
}
EXPORT_SYMBOL(baswap);

/* Bluetooth error codes to Unix errno mapping */
int bt_to_errno(__u16 code)
{
	switch (code) {
	case 0:
		return 0;

	case 0x01:
		return EBADRQC;

	case 0x02:
		return ENOTCONN;

	case 0x03:
		return EIO;

	case 0x04:
	case 0x3c:
		return EHOSTDOWN;

	case 0x05:
		return EACCES;

	case 0x06:
		return EBADE;

	case 0x07:
		return ENOMEM;

	case 0x08:
		return ETIMEDOUT;

	case 0x09:
		return EMLINK;

	case 0x0a:
		return EMLINK;

	case 0x0b:
		return EALREADY;

	case 0x0c:
		return EBUSY;

	case 0x0d:
	case 0x0e:
	case 0x0f:
		return ECONNREFUSED;

	case 0x10:
		return ETIMEDOUT;

	case 0x11:
	case 0x27:
	case 0x29:
	case 0x20:
		return EOPNOTSUPP;

	case 0x12:
		return EINVAL;

	case 0x13:
	case 0x14:
	case 0x15:
		return ECONNRESET;

	case 0x16:
		return ECONNABORTED;

	case 0x17:
		return ELOOP;

	case 0x18:
		return EACCES;

	case 0x1a:
		return EPROTONOSUPPORT;

	case 0x1b:
		return ECONNREFUSED;

	case 0x19:
	case 0x1e:
	case 0x23:
	case 0x24:
	case 0x25:
		return EPROTO;

	default:
		return ENOSYS;
	}
}
EXPORT_SYMBOL(bt_to_errno);

void bt_info(const char *format, ...)
{
	struct va_format vaf;
	va_list args;

	va_start(args, format);

	vaf.fmt = format;
	vaf.va = &args;

	pr_info("%pV", &vaf);

	va_end(args);
}
EXPORT_SYMBOL(bt_info);

void bt_warn(const char *format, ...)
{
	struct va_format vaf;
	va_list args;

	va_start(args, format);

	vaf.fmt = format;
	vaf.va = &args;

	pr_warn("%pV", &vaf);

	va_end(args);
}
EXPORT_SYMBOL(bt_warn);

void bt_err(const char *format, ...)
{
	struct va_format vaf;
	va_list args;

	va_start(args, format);

	vaf.fmt = format;
	vaf.va = &args;

	pr_err("%pV", &vaf);

	va_end(args);
}
EXPORT_SYMBOL(bt_err);

void bt_err_ratelimited(const char *format, ...)
{
	struct va_format vaf;
	va_list args;

	va_start(args, format);

	vaf.fmt = format;
	vaf.va = &args;

	pr_err_ratelimited("%pV", &vaf);

	va_end(args);
}
EXPORT_SYMBOL(bt_err_ratelimited);
