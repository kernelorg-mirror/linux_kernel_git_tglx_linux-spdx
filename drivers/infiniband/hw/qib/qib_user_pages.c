// SPDX-License-Identifier: GPL-2.0-only or Linux-OpenIB
/*
 * Copyright (c) 2006, 2007, 2008, 2009 QLogic Corporation. All rights reserved.
 * Copyright (c) 2003, 2004, 2005, 2006 PathScale, Inc. All rights reserved.
 */

#include <linux/mm.h>
#include <linux/sched/signal.h>
#include <linux/device.h>

#include "qib.h"

static void __qib_release_user_pages(struct page **p, size_t num_pages,
				     int dirty)
{
	size_t i;

	for (i = 0; i < num_pages; i++) {
		if (dirty)
			set_page_dirty_lock(p[i]);
		put_page(p[i]);
	}
}

/**
 * qib_map_page - a safety wrapper around pci_map_page()
 *
 * A dma_addr of all 0's is interpreted by the chip as "disabled".
 * Unfortunately, it can also be a valid dma_addr returned on some
 * architectures.
 *
 * The powerpc iommu assigns dma_addrs in ascending order, so we don't
 * have to bother with retries or mapping a dummy page to insure we
 * don't just get the same mapping again.
 *
 * I'm sure we won't be so lucky with other iommu's, so FIXME.
 */
int qib_map_page(struct pci_dev *hwdev, struct page *page, dma_addr_t *daddr)
{
	dma_addr_t phys;

	phys = pci_map_page(hwdev, page, 0, PAGE_SIZE, PCI_DMA_FROMDEVICE);
	if (pci_dma_mapping_error(hwdev, phys))
		return -ENOMEM;

	if (!phys) {
		pci_unmap_page(hwdev, phys, PAGE_SIZE, PCI_DMA_FROMDEVICE);
		phys = pci_map_page(hwdev, page, 0, PAGE_SIZE,
				    PCI_DMA_FROMDEVICE);
		if (pci_dma_mapping_error(hwdev, phys))
			return -ENOMEM;
		/*
		 * FIXME: If we get 0 again, we should keep this page,
		 * map another, then free the 0 page.
		 */
	}
	*daddr = phys;
	return 0;
}

/**
 * qib_get_user_pages - lock user pages into memory
 * @start_page: the start page
 * @num_pages: the number of pages
 * @p: the output page structures
 *
 * This function takes a given start page (page aligned user virtual
 * address) and pins it and the following specified number of pages.  For
 * now, num_pages is always 1, but that will probably change at some point
 * (because caller is doing expected sends on a single virtually contiguous
 * buffer, so we can do all pages at once).
 */
int qib_get_user_pages(unsigned long start_page, size_t num_pages,
		       struct page **p)
{
	unsigned long locked, lock_limit;
	size_t got;
	int ret;

	lock_limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;
	locked = atomic64_add_return(num_pages, &current->mm->pinned_vm);

	if (locked > lock_limit && !capable(CAP_IPC_LOCK)) {
		ret = -ENOMEM;
		goto bail;
	}

	down_read(&current->mm->mmap_sem);
	for (got = 0; got < num_pages; got += ret) {
		ret = get_user_pages(start_page + got * PAGE_SIZE,
				     num_pages - got,
				     FOLL_LONGTERM | FOLL_WRITE | FOLL_FORCE,
				     p + got, NULL);
		if (ret < 0) {
			up_read(&current->mm->mmap_sem);
			goto bail_release;
		}
	}
	up_read(&current->mm->mmap_sem);

	return 0;
bail_release:
	__qib_release_user_pages(p, got, 0);
bail:
	atomic64_sub(num_pages, &current->mm->pinned_vm);
	return ret;
}

void qib_release_user_pages(struct page **p, size_t num_pages)
{
	__qib_release_user_pages(p, num_pages, 1);

	/* during close after signal, mm can be NULL */
	if (current->mm)
		atomic64_sub(num_pages, &current->mm->pinned_vm);
}
