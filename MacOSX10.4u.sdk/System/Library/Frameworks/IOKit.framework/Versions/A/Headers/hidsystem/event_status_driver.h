/*
 * Copyright (c) 1998-2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/******************************************************************************
	event_status_driver.h
	API for the events status driver.
	This file contains public API.
	mpaque 11Oct91
	
	Copyright 1991 NeXT Computer, Inc.
	
	Modified:
	
******************************************************************************/

#ifndef _DRIVERS_EVENT_STATUS_DRIVER_
#define _DRIVERS_EVENT_STATUS_DRIVER_

__BEGIN_DECLS

#include <mach/port.h>
#include <IOKit/hidsystem/IOLLEvent.h>
#include <IOKit/hidsystem/IOHIDTypes.h>
#include <AvailabilityMacros.h> 

/*
 * Event System Handle:
 *
 * Information used by the system between calls to NXOpenEventSystem and
 * NXCloseEventSystem.  The application should not
 * access any of the elements of this structure.
 */
typedef mach_port_t NXEventHandle;

/* Open and Close */
NXEventHandle NXOpenEventStatus(void);
void NXCloseEventStatus(NXEventHandle handle);

/* Status */
extern NXEventSystemInfoType NXEventSystemInfo(NXEventHandle handle,
				char *flavor,
				int *evs_info,
				unsigned int *evs_info_cnt);
/* Keyboard */
extern void NXSetKeyRepeatInterval(NXEventHandle handle, double seconds);
extern double NXKeyRepeatInterval(NXEventHandle handle);
extern void NXSetKeyRepeatThreshold(NXEventHandle handle, double threshold);
extern double NXKeyRepeatThreshold(NXEventHandle handle);
extern void NXResetKeyboard(NXEventHandle handle);

/* Mouse */
extern void NXSetClickTime(NXEventHandle handle, double seconds);
extern double NXClickTime(NXEventHandle handle);
extern void NXSetClickSpace(NXEventHandle handle, _NXSize_ *area);
extern void NXGetClickSpace(NXEventHandle handle, _NXSize_ *area);
extern void NXResetMouse(NXEventHandle handle);

/* DEPRECATED API */

/* NXIdleTime has been deprecated as this API does not take into account
   events posted through the CG API set.  Instead, we strongly encourage 
   developers to make use of the CGSSecondsSinceLastInputEvent API. */
extern double NXIdleTime(NXEventHandle handle)
AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/* These methods are NOT supported.   */
extern NXKeyMapping *NXSetKeyMapping(NXEventHandle h, NXKeyMapping *keymap)
AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

extern int NXKeyMappingLength(NXEventHandle handle)
AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

extern NXKeyMapping *NXGetKeyMapping(NXEventHandle h, NXKeyMapping *keymap)
AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/* These methods are NOT supported and will return NULL values.   */
extern void NXSetMouseScaling(NXEventHandle handle, NXMouseScaling *scaling)
AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

extern void NXGetMouseScaling(NXEventHandle handle, NXMouseScaling *scaling)
AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

extern void NXSetAutoDimThreshold(NXEventHandle handle, double seconds)
AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

extern double NXAutoDimThreshold(NXEventHandle handle)
AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

extern double NXAutoDimTime(NXEventHandle handle)
AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

extern void NXSetAutoDimState(NXEventHandle handle, boolean_t dimmed)
AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

extern boolean_t NXAutoDimState(NXEventHandle handle)
AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

extern void NXSetAutoDimBrightness(NXEventHandle handle, double level)
AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

extern double NXAutoDimBrightness(NXEventHandle handle)
AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

extern void NXSetScreenBrightness(NXEventHandle handle, double level)
AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

extern double NXScreenBrightness(NXEventHandle handle)
AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/* END DEPRECATED API */

__END_DECLS

#endif /*_DRIVERS_EVENT_STATUS_DRIVER_ */

