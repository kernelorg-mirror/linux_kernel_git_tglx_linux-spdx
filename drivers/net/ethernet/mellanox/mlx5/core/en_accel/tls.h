/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2018 Mellanox Technologies. All rights reserved.
 */
#ifndef __MLX5E_TLS_H__
#define __MLX5E_TLS_H__

#ifdef CONFIG_MLX5_EN_TLS

#include <net/tls.h>
#include "en.h"

struct mlx5e_tls_sw_stats {
	atomic64_t tx_tls_drop_metadata;
	atomic64_t tx_tls_drop_resync_alloc;
	atomic64_t tx_tls_drop_no_sync_data;
	atomic64_t tx_tls_drop_bypass_required;
	atomic64_t rx_tls_drop_resync_request;
	atomic64_t rx_tls_resync_request;
	atomic64_t rx_tls_resync_reply;
	atomic64_t rx_tls_auth_fail;
};

struct mlx5e_tls {
	struct mlx5e_tls_sw_stats sw_stats;
};

struct mlx5e_tls_offload_context_tx {
	struct tls_offload_context_tx base;
	u32 expected_seq;
	__be32 swid;
};

static inline struct mlx5e_tls_offload_context_tx *
mlx5e_get_tls_tx_context(struct tls_context *tls_ctx)
{
	BUILD_BUG_ON(sizeof(struct mlx5e_tls_offload_context_tx) >
		     TLS_OFFLOAD_CONTEXT_SIZE_TX);
	return container_of(tls_offload_ctx_tx(tls_ctx),
			    struct mlx5e_tls_offload_context_tx,
			    base);
}

struct mlx5e_tls_offload_context_rx {
	struct tls_offload_context_rx base;
	__be32 handle;
};

static inline struct mlx5e_tls_offload_context_rx *
mlx5e_get_tls_rx_context(struct tls_context *tls_ctx)
{
	BUILD_BUG_ON(sizeof(struct mlx5e_tls_offload_context_rx) >
		     TLS_OFFLOAD_CONTEXT_SIZE_RX);
	return container_of(tls_offload_ctx_rx(tls_ctx),
			    struct mlx5e_tls_offload_context_rx,
			    base);
}

void mlx5e_tls_build_netdev(struct mlx5e_priv *priv);
int mlx5e_tls_init(struct mlx5e_priv *priv);
void mlx5e_tls_cleanup(struct mlx5e_priv *priv);

int mlx5e_tls_get_count(struct mlx5e_priv *priv);
int mlx5e_tls_get_strings(struct mlx5e_priv *priv, uint8_t *data);
int mlx5e_tls_get_stats(struct mlx5e_priv *priv, u64 *data);

#else

static inline void mlx5e_tls_build_netdev(struct mlx5e_priv *priv) { }
static inline int mlx5e_tls_init(struct mlx5e_priv *priv) { return 0; }
static inline void mlx5e_tls_cleanup(struct mlx5e_priv *priv) { }
static inline int mlx5e_tls_get_count(struct mlx5e_priv *priv) { return 0; }
static inline int mlx5e_tls_get_strings(struct mlx5e_priv *priv, uint8_t *data) { return 0; }
static inline int mlx5e_tls_get_stats(struct mlx5e_priv *priv, u64 *data) { return 0; }

#endif

#endif /* __MLX5E_TLS_H__ */
