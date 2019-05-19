/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
*
* smapi.h -- declarations for SMAPI interface routines
*
* Written By: Mike Sullivan IBM Corporation
*
* Copyright (C) 1999 IBM Corporation
*
* 10/23/2000 - Alpha Release
*	First release to the public
*/

#ifndef _LINUX_SMAPI_H
#define _LINUX_SMAPI_H

typedef struct {
	int bDSPPresent;
	int bDSPEnabled;
	int bModemEnabled;
	int bMIDIEnabled;
	int bSblstEnabled;
	unsigned short usDspIRQ;
	unsigned short usDspDMA;
	unsigned short usDspBaseIO;
	unsigned short usUartIRQ;
	unsigned short usUartBaseIO;
	unsigned short usMidiIRQ;
	unsigned short usMidiBaseIO;
	unsigned short usSndblstIRQ;
	unsigned short usSndblstDMA;
	unsigned short usSndblstBaseIO;
} SMAPI_DSP_SETTINGS;

int smapi_init(void);
int smapi_query_DSP_cfg(SMAPI_DSP_SETTINGS * pSettings);
int smapi_set_DSP_cfg(void);
int smapi_set_DSP_power_state(bool bOn);


#endif
