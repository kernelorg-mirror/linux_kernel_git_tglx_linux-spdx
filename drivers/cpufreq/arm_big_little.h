/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * ARM big.LITTLE platform's CPUFreq header file
 *
 * Copyright (C) 2013 ARM Ltd.
 * Sudeep KarkadaNagesha <sudeep.karkadanagesha@arm.com>
 *
 * Copyright (C) 2013 Linaro.
 * Viresh Kumar <viresh.kumar@linaro.org>
 */
#ifndef CPUFREQ_ARM_BIG_LITTLE_H
#define CPUFREQ_ARM_BIG_LITTLE_H

#include <linux/cpufreq.h>
#include <linux/device.h>
#include <linux/types.h>

struct cpufreq_arm_bL_ops {
	char name[CPUFREQ_NAME_LEN];

	/*
	 * This must set opp table for cpu_dev in a similar way as done by
	 * dev_pm_opp_of_add_table().
	 */
	int (*init_opp_table)(const struct cpumask *cpumask);

	/* Optional */
	int (*get_transition_latency)(struct device *cpu_dev);
	void (*free_opp_table)(const struct cpumask *cpumask);
};

int bL_cpufreq_register(const struct cpufreq_arm_bL_ops *ops);
void bL_cpufreq_unregister(const struct cpufreq_arm_bL_ops *ops);

#endif /* CPUFREQ_ARM_BIG_LITTLE_H */
