/* SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB */
/*
 * Copyright (c) 2017, Mellanox Technologies, Ltd.  All rights reserved.
 */

#ifndef __LIB_CLOCK_H__
#define __LIB_CLOCK_H__

#if IS_ENABLED(CONFIG_PTP_1588_CLOCK)
void mlx5_init_clock(struct mlx5_core_dev *mdev);
void mlx5_cleanup_clock(struct mlx5_core_dev *mdev);

static inline int mlx5_clock_get_ptp_index(struct mlx5_core_dev *mdev)
{
	return mdev->clock.ptp ? ptp_clock_index(mdev->clock.ptp) : -1;
}

static inline ktime_t mlx5_timecounter_cyc2time(struct mlx5_clock *clock,
						u64 timestamp)
{
	unsigned int seq;
	u64 nsec;

	do {
		seq = read_seqbegin(&clock->lock);
		nsec = timecounter_cyc2time(&clock->tc, timestamp);
	} while (read_seqretry(&clock->lock, seq));

	return ns_to_ktime(nsec);
}

#else
static inline void mlx5_init_clock(struct mlx5_core_dev *mdev) {}
static inline void mlx5_cleanup_clock(struct mlx5_core_dev *mdev) {}
static inline int mlx5_clock_get_ptp_index(struct mlx5_core_dev *mdev)
{
	return -1;
}

static inline ktime_t mlx5_timecounter_cyc2time(struct mlx5_clock *clock,
						u64 timestamp)
{
	return 0;
}
#endif

#endif
