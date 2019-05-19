/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Allwinner SoCs SRAM Controller Driver
 *
 * Copyright (C) 2015 Maxime Ripard
 *
 * Author: Maxime Ripard <maxime.ripard@free-electrons.com>
 */

#ifndef _SUNXI_SRAM_H_
#define _SUNXI_SRAM_H_

int sunxi_sram_claim(struct device *dev);
int sunxi_sram_release(struct device *dev);

#endif /* _SUNXI_SRAM_H_ */
