/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * "Portions Copyright (c) 1999 Apple Computer, Inc.  All Rights
 * Reserved.  This file contains Original Code and/or Modifications of
 * Original Code as defined in and that are subject to the Apple Public
 * Source License Version 1.0 (the 'License').  You may not use this file
 * except in compliance with the License.  Please obtain a copy of the
 * License at http://www.apple.com/publicsource and read it before using
 * this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License."
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/* 	Copyright (c) 1991 NeXT Computer, Inc.  All rights reserved. 
 *
 * arch_types.h - Common machine-description data types.
 *
 * HISTORY
 * 10-Sep-91    Doug Mitchell at NeXT
 *      Created. 
 */

#ifndef	_ARCHITECTURE_ARCH_TYPES_H_
#define _ARCHITECTURE_ARCH_TYPES_H_

/*
 * DMA channel status values.
 */
typedef unsigned char	IOChannelStatus;
typedef unsigned char	IOUserStatus;

/*
 * Two ways of looking at deviceType.
 */
typedef unsigned int	IODeviceType;
typedef unsigned short	IODeviceIndex;
typedef unsigned short 	IODeviceRevision;

typedef struct {
	IODeviceIndex 		deviceIndex;
	IODeviceRevision 	deviceRevision;
} IODeviceTypeIr;

typedef union {
	IODeviceType 		deviceType;
	IODeviceTypeIr 		deviceTypeIr;
} IODeviceTypeUn;


/*
 * Two ways of looking at slot ID.
 */
typedef	unsigned int	IOSlotId;
typedef struct {		
	unsigned short		valid:1,	// 15 
				console:1,	// 14 - should be 0 (?)
				bootDev:1,	// 13 - should be 0 (?)
				rsvd:3,		// 12..10 - must be 0
				blockId:3,	// 9..7
				prodId:7;	// 6..0
} IOSlotIdMfg;

typedef union {
	IOSlotId		slotId;		// all 32 bits
	struct {
		IOSlotIdMfg	mfgId;		// 31..16
		unsigned short 	boardId;	// 15..0
	} slotIdStr;
} IOSlotIdUn;

#endif	/* _ARCHITECTURE_ARCH_TYPES_H_ */
