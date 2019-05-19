// SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB
/*
 * Copyright (c) 2017 Mellanox Technologies. All rights reserved.
 */

#include <linux/ethtool.h>
#include <net/sock.h>

#include "en.h"
#include "accel/ipsec.h"
#include "fpga/sdk.h"
#include "en_accel/ipsec.h"

static const struct counter_desc mlx5e_ipsec_hw_stats_desc[] = {
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_stats, ipsec_dec_in_packets) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_stats, ipsec_dec_out_packets) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_stats, ipsec_dec_bypass_packets) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_stats, ipsec_enc_in_packets) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_stats, ipsec_enc_out_packets) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_stats, ipsec_enc_bypass_packets) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_stats, ipsec_dec_drop_packets) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_stats, ipsec_dec_auth_fail_packets) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_stats, ipsec_enc_drop_packets) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_stats, ipsec_add_sa_success) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_stats, ipsec_add_sa_fail) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_stats, ipsec_del_sa_success) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_stats, ipsec_del_sa_fail) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_stats, ipsec_cmd_drop) },
};

static const struct counter_desc mlx5e_ipsec_sw_stats_desc[] = {
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_sw_stats, ipsec_rx_drop_sp_alloc) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_sw_stats, ipsec_rx_drop_sadb_miss) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_sw_stats, ipsec_rx_drop_syndrome) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_sw_stats, ipsec_tx_drop_bundle) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_sw_stats, ipsec_tx_drop_no_state) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_sw_stats, ipsec_tx_drop_not_ip) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_sw_stats, ipsec_tx_drop_trailer) },
	{ MLX5E_DECLARE_STAT(struct mlx5e_ipsec_sw_stats, ipsec_tx_drop_metadata) },
};

#define MLX5E_READ_CTR_ATOMIC64(ptr, dsc, i) \
	atomic64_read((atomic64_t *)((char *)(ptr) + (dsc)[i].offset))

#define NUM_IPSEC_HW_COUNTERS ARRAY_SIZE(mlx5e_ipsec_hw_stats_desc)
#define NUM_IPSEC_SW_COUNTERS ARRAY_SIZE(mlx5e_ipsec_sw_stats_desc)

#define NUM_IPSEC_COUNTERS (NUM_IPSEC_HW_COUNTERS + NUM_IPSEC_SW_COUNTERS)

int mlx5e_ipsec_get_count(struct mlx5e_priv *priv)
{
	if (!priv->ipsec)
		return 0;

	return NUM_IPSEC_COUNTERS;
}

int mlx5e_ipsec_get_strings(struct mlx5e_priv *priv, uint8_t *data)
{
	unsigned int i, idx = 0;

	if (!priv->ipsec)
		return 0;

	for (i = 0; i < NUM_IPSEC_HW_COUNTERS; i++)
		strcpy(data + (idx++) * ETH_GSTRING_LEN,
		       mlx5e_ipsec_hw_stats_desc[i].format);

	for (i = 0; i < NUM_IPSEC_SW_COUNTERS; i++)
		strcpy(data + (idx++) * ETH_GSTRING_LEN,
		       mlx5e_ipsec_sw_stats_desc[i].format);

	return NUM_IPSEC_COUNTERS;
}

void mlx5e_ipsec_update_stats(struct mlx5e_priv *priv)
{
	int ret;

	if (!priv->ipsec)
		return;

	ret = mlx5_accel_ipsec_counters_read(priv->mdev, (u64 *)&priv->ipsec->stats,
					     NUM_IPSEC_HW_COUNTERS);
	if (ret)
		memset(&priv->ipsec->stats, 0, sizeof(priv->ipsec->stats));
}

int mlx5e_ipsec_get_stats(struct mlx5e_priv *priv, u64 *data)
{
	int i, idx = 0;

	if (!priv->ipsec)
		return 0;

	for (i = 0; i < NUM_IPSEC_HW_COUNTERS; i++)
		data[idx++] = MLX5E_READ_CTR64_CPU(&priv->ipsec->stats,
						   mlx5e_ipsec_hw_stats_desc, i);

	for (i = 0; i < NUM_IPSEC_SW_COUNTERS; i++)
		data[idx++] = MLX5E_READ_CTR_ATOMIC64(&priv->ipsec->sw_stats,
						      mlx5e_ipsec_sw_stats_desc, i);

	return NUM_IPSEC_COUNTERS;
}
