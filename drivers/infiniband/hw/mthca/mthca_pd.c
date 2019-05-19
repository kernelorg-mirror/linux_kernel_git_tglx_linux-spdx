// SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Cisco Systems.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
 */

#include <linux/errno.h>

#include "mthca_dev.h"

int mthca_pd_alloc(struct mthca_dev *dev, int privileged, struct mthca_pd *pd)
{
	int err = 0;

	pd->privileged = privileged;

	atomic_set(&pd->sqp_count, 0);
	pd->pd_num = mthca_alloc(&dev->pd_table.alloc);
	if (pd->pd_num == -1)
		return -ENOMEM;

	if (privileged) {
		err = mthca_mr_alloc_notrans(dev, pd->pd_num,
					     MTHCA_MPT_FLAG_LOCAL_READ |
					     MTHCA_MPT_FLAG_LOCAL_WRITE,
					     &pd->ntmr);
		if (err)
			mthca_free(&dev->pd_table.alloc, pd->pd_num);
	}

	return err;
}

void mthca_pd_free(struct mthca_dev *dev, struct mthca_pd *pd)
{
	if (pd->privileged)
		mthca_free_mr(dev, &pd->ntmr);
	mthca_free(&dev->pd_table.alloc, pd->pd_num);
}

int mthca_init_pd_table(struct mthca_dev *dev)
{
	return mthca_alloc_init(&dev->pd_table.alloc,
				dev->limits.num_pds,
				(1 << 24) - 1,
				dev->limits.reserved_pds);
}

void mthca_cleanup_pd_table(struct mthca_dev *dev)
{
	/* XXX check if any PDs are still allocated? */
	mthca_alloc_cleanup(&dev->pd_table.alloc);
}
