# SPDX-License-Identifier: GPL-2.0-only
#/*******************************************************************
# * This file is part of the Emulex Linux Device Driver for         *
# * Fibre Channel Host Bus Adapters.                                *
# * Copyright (C) 2017-2018 Broadcom. All Rights Reserved. The term *
# * “Broadcom” refers to Broadcom Inc. and/or its subsidiaries.     *
# * Copyright (C) 2004-2012 Emulex.  All rights reserved.           *
# * EMULEX and SLI are trademarks of Emulex.                        *
# * www.broadcom.com                                                *
# *                                                                 *
# *******************************************************************/
######################################################################

ccflags-$(GCOV) := -fprofile-arcs -ftest-coverage
ccflags-$(GCOV) += -O0

ifdef WARNINGS_BECOME_ERRORS
ccflags-y += -Werror
endif

obj-$(CONFIG_SCSI_LPFC) := lpfc.o

lpfc-objs := lpfc_mem.o lpfc_sli.o lpfc_ct.o lpfc_els.o \
	lpfc_hbadisc.o	lpfc_init.o lpfc_mbox.o lpfc_nportdisc.o   \
	lpfc_scsi.o lpfc_attr.o lpfc_vport.o lpfc_debugfs.o lpfc_bsg.o \
	lpfc_nvme.o lpfc_nvmet.o
