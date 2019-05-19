// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Common hypervisor code
 *
 * Copyright (C) 2008, VMware, Inc.
 * Author : Alok N Kataria <akataria@vmware.com>
 */

#include <linux/init.h>
#include <linux/export.h>
#include <asm/processor.h>
#include <asm/hypervisor.h>

extern const struct hypervisor_x86 x86_hyper_vmware;
extern const struct hypervisor_x86 x86_hyper_ms_hyperv;
extern const struct hypervisor_x86 x86_hyper_xen_pv;
extern const struct hypervisor_x86 x86_hyper_xen_hvm;
extern const struct hypervisor_x86 x86_hyper_kvm;
extern const struct hypervisor_x86 x86_hyper_jailhouse;

static const __initconst struct hypervisor_x86 * const hypervisors[] =
{
#ifdef CONFIG_XEN_PV
	&x86_hyper_xen_pv,
#endif
#ifdef CONFIG_XEN_PVHVM
	&x86_hyper_xen_hvm,
#endif
	&x86_hyper_vmware,
	&x86_hyper_ms_hyperv,
#ifdef CONFIG_KVM_GUEST
	&x86_hyper_kvm,
#endif
#ifdef CONFIG_JAILHOUSE_GUEST
	&x86_hyper_jailhouse,
#endif
};

enum x86_hypervisor_type x86_hyper_type;
EXPORT_SYMBOL(x86_hyper_type);

static inline const struct hypervisor_x86 * __init
detect_hypervisor_vendor(void)
{
	const struct hypervisor_x86 *h = NULL, * const *p;
	uint32_t pri, max_pri = 0;

	for (p = hypervisors; p < hypervisors + ARRAY_SIZE(hypervisors); p++) {
		pri = (*p)->detect();
		if (pri > max_pri) {
			max_pri = pri;
			h = *p;
		}
	}

	if (h)
		pr_info("Hypervisor detected: %s\n", h->name);

	return h;
}

static void __init copy_array(const void *src, void *target, unsigned int size)
{
	unsigned int i, n = size / sizeof(void *);
	const void * const *from = (const void * const *)src;
	const void **to = (const void **)target;

	for (i = 0; i < n; i++)
		if (from[i])
			to[i] = from[i];
}

void __init init_hypervisor_platform(void)
{
	const struct hypervisor_x86 *h;

	h = detect_hypervisor_vendor();

	if (!h)
		return;

	copy_array(&h->init, &x86_init.hyper, sizeof(h->init));
	copy_array(&h->runtime, &x86_platform.hyper, sizeof(h->runtime));

	x86_hyper_type = h->type;
	x86_init.hyper.init_platform();
}
