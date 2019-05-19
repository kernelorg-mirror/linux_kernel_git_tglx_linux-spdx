// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * The setup file for USB related hardware on PMC-Sierra MSP processors.
 *
 * Copyright 2006 PMC-Sierra, Inc.
 */
#if defined(CONFIG_USB_EHCI_HCD) || defined(CONFIG_USB_GADGET)

#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/platform_device.h>

#include <asm/mipsregs.h>

#include <msp_regs.h>
#include <msp_int.h>
#include <msp_prom.h>
#include <msp_usb.h>


#if defined(CONFIG_USB_EHCI_HCD)
static struct resource msp_usbhost0_resources[] = {
	[0] = { /* EHCI-HS operational and capabilities registers */
		.start	= MSP_USB0_HS_START,
		.end	= MSP_USB0_HS_END,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= MSP_INT_USB,
		.end	= MSP_INT_USB,
		.flags	= IORESOURCE_IRQ,
	},
	[2] = { /* MSBus-to-AMBA bridge register space */
		.start	= MSP_USB0_MAB_START,
		.end	= MSP_USB0_MAB_END,
		.flags	= IORESOURCE_MEM,
	},
	[3] = { /* Identification and general hardware parameters */
		.start	= MSP_USB0_ID_START,
		.end	= MSP_USB0_ID_END,
		.flags	= IORESOURCE_MEM,
	},
};

static u64 msp_usbhost0_dma_mask = 0xffffffffUL;

static struct mspusb_device msp_usbhost0_device = {
	.dev	= {
		.name	= "pmcmsp-ehci",
		.id	= 0,
		.dev	= {
			.dma_mask = &msp_usbhost0_dma_mask,
			.coherent_dma_mask = 0xffffffffUL,
		},
		.num_resources	= ARRAY_SIZE(msp_usbhost0_resources),
		.resource	= msp_usbhost0_resources,
	},
};
#endif /* CONFIG_USB_EHCI_HCD */

#if defined(CONFIG_USB_GADGET)
static struct resource msp_usbdev0_resources[] = {
	[0] = { /* EHCI-HS operational and capabilities registers */
		.start	= MSP_USB0_HS_START,
		.end	= MSP_USB0_HS_END,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= MSP_INT_USB,
		.end	= MSP_INT_USB,
		.flags	= IORESOURCE_IRQ,
	},
	[2] = { /* MSBus-to-AMBA bridge register space */
		.start	= MSP_USB0_MAB_START,
		.end	= MSP_USB0_MAB_END,
		.flags	= IORESOURCE_MEM,
	},
	[3] = { /* Identification and general hardware parameters */
		.start	= MSP_USB0_ID_START,
		.end	= MSP_USB0_ID_END,
		.flags	= IORESOURCE_MEM,
	},
};

static u64 msp_usbdev_dma_mask = 0xffffffffUL;

/* This may need to be converted to a mspusb_device, too. */
static struct mspusb_device msp_usbdev0_device = {
	.dev	= {
		.name	= "msp71xx_udc",
		.id	= 0,
		.dev	= {
			.dma_mask = &msp_usbdev_dma_mask,
			.coherent_dma_mask = 0xffffffffUL,
		},
		.num_resources	= ARRAY_SIZE(msp_usbdev0_resources),
		.resource	= msp_usbdev0_resources,
	},
};
#endif /* CONFIG_USB_GADGET */

static int __init msp_usb_setup(void)
{
	char		*strp;
	char		envstr[32];
	struct platform_device *msp_devs[NUM_USB_DEVS];
	unsigned int val;

	/* construct environment name usbmode */
	/* set usbmode <host/device> as pmon environment var */
	/*
	 * Could this perhaps be integrated into the "features" env var?
	 * Use the features key "U", and follow with "H" for host-mode,
	 * "D" for device-mode.	 If it works for Ethernet, why not USB...
	 *  -- hammtrev, 2007/03/22
	 */
	snprintf(&envstr[0], sizeof(envstr), "usbmode");

	/* set default host mode */
	val = 1;

	/* get environment string */
	strp = prom_getenv(&envstr[0]);
	if (strp) {
		/* compare string */
		if (!strcmp(strp, "device"))
			val = 0;
	}

	if (val) {
#if defined(CONFIG_USB_EHCI_HCD)
		msp_devs[0] = &msp_usbhost0_device.dev;
		ppfinit("platform add USB HOST done %s.\n", msp_devs[0]->name);
#else
		ppfinit("%s: echi_hcd not supported\n", __FILE__);
#endif	/* CONFIG_USB_EHCI_HCD */
	} else {
#if defined(CONFIG_USB_GADGET)
		/* get device mode structure */
		msp_devs[0] = &msp_usbdev0_device.dev;
		ppfinit("platform add USB DEVICE done %s.\n"
					, msp_devs[0]->name);
#else
		ppfinit("%s: usb_gadget not supported\n", __FILE__);
#endif	/* CONFIG_USB_GADGET */
	}
	/* add device */
	platform_add_devices(msp_devs, ARRAY_SIZE(msp_devs));

	return 0;
}

subsys_initcall(msp_usb_setup);
#endif /* CONFIG_USB_EHCI_HCD || CONFIG_USB_GADGET */
