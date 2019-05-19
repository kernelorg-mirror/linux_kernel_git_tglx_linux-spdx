// SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB
/*
 * Copyright (c) 2018 Mellanox Technologies. All rights reserved.
 */

#include <linux/ethtool.h>
#include <net/sock.h>

#include "en.h"
#include "accel/tls.h"
#include "fpga/sdk.h"
#include "en_accel/tls.h"

static const struct counter_desc mlx5e_tls_sw_stats_desc[] = {
	{ MLX5E_DECLARE_STAT(struct mlx5e_tls_sw_stats, tx_tls_drop_metadata) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_tls_sw_stats, tx_tls_drop_resync_alloc) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_tls_sw_stats, tx_tls_drop_no_sync_data) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_tls_sw_stats, tx_tls_drop_bypass_required) },
};

#define MLX5E_READ_CTR_ATOMIC64(ptr, dsc, i) \
	atomic64_read((atomic64_t *)((char *)(ptr) + (dsc)[i].offset))

#define NUM_TLS_SW_COUNTERS ARRAY_SIZE(mlx5e_tls_sw_stats_desc)

int mlx5e_tls_get_count(struct mlx5e_priv *priv)
{
	if (!priv->tls)
		return 0;

	return NUM_TLS_SW_COUNTERS;
}

int mlx5e_tls_get_strings(struct mlx5e_priv *priv, uint8_t *data)
{
	unsigned int i, idx = 0;

	if (!priv->tls)
		return 0;

	for (i = 0; i < NUM_TLS_SW_COUNTERS; i++)
		strcpy(data + (idx++) * ETH_GSTRING_LEN,
		       mlx5e_tls_sw_stats_desc[i].format);

	return NUM_TLS_SW_COUNTERS;
}

int mlx5e_tls_get_stats(struct mlx5e_priv *priv, u64 *data)
{
	int i, idx = 0;

	if (!priv->tls)
		return 0;

	for (i = 0; i < NUM_TLS_SW_COUNTERS; i++)
		data[idx++] =
		    MLX5E_READ_CTR_ATOMIC64(&priv->tls->sw_stats,
					    mlx5e_tls_sw_stats_desc, i);

	return NUM_TLS_SW_COUNTERS;
}
