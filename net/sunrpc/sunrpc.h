/* SPDX-License-Identifier: GPL-2.0-only */
/******************************************************************************

(c) 2008 NetApp.  All Rights Reserved.


******************************************************************************/

/*
 * Functions and macros used internally by RPC
 */

#ifndef _NET_SUNRPC_SUNRPC_H
#define _NET_SUNRPC_SUNRPC_H

#include <linux/net.h>

/*
 * Header for dynamically allocated rpc buffers.
 */
struct rpc_buffer {
	size_t	len;
	char	data[];
};

static inline int sock_is_loopback(struct sock *sk)
{
	struct dst_entry *dst;
	int loopback = 0;
	rcu_read_lock();
	dst = rcu_dereference(sk->sk_dst_cache);
	if (dst && dst->dev &&
	    (dst->dev->features & NETIF_F_LOOPBACK))
		loopback = 1;
	rcu_read_unlock();
	return loopback;
}

int svc_send_common(struct socket *sock, struct xdr_buf *xdr,
		    struct page *headpage, unsigned long headoffset,
		    struct page *tailpage, unsigned long tailoffset);

int rpc_clients_notifier_register(void);
void rpc_clients_notifier_unregister(void);
#endif /* _NET_SUNRPC_SUNRPC_H */
