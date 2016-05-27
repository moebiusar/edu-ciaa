/*
 * @brief LPCUSB library's configurations
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */
 
/** @defgroup USB_Config USB Configuration
 * @ingroup LPCUSBlib
* @{
*/

#ifndef LPCUSBLIB_CONFIG_H_
#define LPCUSBLIB_CONFIG_H_

/** Define NXPUSBLIB_DEBUG to allow the library prints out diagnostic messages */
//#define NXPUSBLIB_DEBUG

/** Available configuration number in a device */
#define FIXED_NUM_CONFIGURATIONS		1

/** Control endpoint max packet size */
#define FIXED_CONTROL_ENDPOINT_SIZE		64

//#define __TEST__			/* Test development */

/** Size of share memory that a device uses to store data transfer to/ receive from host
 *  or a host uses to store data transfer to/ receive from device.
 */
#define USBRAM_BUFFER_SIZE  (4*1024)

/** This option effects only on high speed parts that need to test full speed activities */
#define USB_FORCED_FULLSPEED		0

/** Define USE_USB_ROM_STACK = 1 to use MCU's internal ROM stack, 0 if otherwise */
#define USE_USB_ROM_STACK			0

/* Defines agregados para compilar la librería */
#define USB_CAN_BE_DEVICE

#define __LPC43XX__
#define __GNUC__ 4

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif
/* Fin de los defines */

#endif /* NXPUSBLIB_CONFIG_H_ */

/**
* @}
*/
