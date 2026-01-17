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
 * adb_bus.h - Architecture-indpendent ADB bus defintions.
 *
 * HISTORY
 * 12-Sep-91    Doug Mitchell at NeXT
 *      Created. 
 */
 
#ifndef	_ARCHITECTURE_ADB_BUS_
#define _ARCHITECTURE_ADB_BUS_

typedef unsigned char adbHandlerId;
typedef unsigned char adbAddress;

#define ADB_ADDRESS_NONE	((adbAddress)-1)
#define ADB_HANDLER_ID_NONE	((adbHandlerId)0)


/*
 * ADB Command byte fields.
 */
#define AC_ADDRESS_MASK		0xf0
#define AC_ADDRESS_SHIFT	4
#define AC_COMMAND_MASK		0x0c
#define AC_REGISTER_MASK	0x03

#define AC_ADDRESS(commandByte)		\
	((commandByte & AC_ADDRESS_MASK) >> AC_ADDRESS_SHIFT)
#define AC_REGISTER(commandByte)	\
	(commandByte & AC_REGISTER_MASK)
#define AC_COMMAND(commandByte)		\
	(commandByte & AC_COMMAND_MASK)

/*
 * Command values.
 */
#define ADB_CMD_TALK		0x0c
#define ADB_CMD_LISTEN		0x08
#define ADB_CMD_FLUSH		0x01
#define ADB_CMD_SENDRESET	0x00

/*
 * Macros to build the known ADB commands.
 */
#define TALK_REGISTER(reg, deviceAddress) 				\
	(ADB_CMD_TALK | (deviceAddress << AC_ADDRESS_SHIFT) | 		\
		(unsigned char)(reg))

#define LISTEN_REGISTER(reg, deviceAddress) 				\
	(ADB_CMD_LISTEN | (deviceAddress << AC_ADDRESS_SHIFT) | 	\
		(unsigned char)(reg))

#define ADB_FLUSH(deviceAddress)					\
	(ADB_CMD_FLUSH | (deviceAddress << AC_ADDRESS_SHIFT))

#define ADB_SEND_RESET	ADB_CMD_SENDRESET


/*
 * Standard device register (register 0 thru 2).
 */
#define ADB_REGISTER_SIZE	8	
typedef struct {
	unsigned char byte[ADB_REGISTER_SIZE];
} adbRegisterStandard;

/*
 * Two ways of looking at Register 3.
 */
typedef struct {

	unsigned reserved0:1,			// bit 15, always 0
		 exceptionalEvent:1,		// bit 14
		 serviceRequestEnable:1,	// bit 13
		 reserved1:1,			// bit 12, always 0
		 deviceAddress:4,		// bits 11..8
		 handlerId:8;			// bits 7..0
		 
	/* 
	 * Pad out to remainder of standard register size.
	 */
	unsigned char reserved2[ADB_REGISTER_SIZE-2];
	
} adbRegister3bits;

typedef struct {
	unsigned short data;
	unsigned char reserved[ADB_REGISTER_SIZE-2];
} adbRegister3short;

typedef union {
	adbRegister3bits	bits;
	adbRegister3short	sh;
} adbRegister3;

/*
 * Bit fields for adbRegister3.sh.
 */
#define AR3_RESERVED0			0x8000
#define AR3_EXCEPTIONAL_EVENT		0x4000
#define AR3_SERVICE_REQUEST_ENABLE	0x2000
#define AR3_RESERVED1			0x1000
#define AR3_DEVICE_ADDRESS_MASK		0x0f00		
#define AR3_HANDLER_ID_MASK		0x00ff

/*
 * Common device register.
 */
typedef union {
	adbRegisterStandard	stand;
	adbRegister3		reg3;
} adbRegister;

/*
 * Reserved Handler IDs.
 */
#define HANDLER_ID_SELF_TEST		0xff
#define HANDLER_ID_UPDATE_ALWAYS	0xff	// listen only - update address
						//    and enable bits
#define HANDLER_ID_SELF_TEST_FAIL	0xff	// talk only - self test failed
#define HANDLER_ID_UPDATE_NO_COLLISION	0xfe	// update address only if no 
						//    collision detected
#define HANDLER_ID_UPDATE_IF_ACTIVATOR	0xfd	// update address only if 
						//    activator depressed

/*
 * Maximum number of ADB devices on the bus.
 */	
#define NUM_ADB_ADDRESSES		16
#define MIN_BUS_DEVICE_ADDRESS		1
#define MAX_BUS_DEVICE_ADDRESS		15

/*
 * 'soft address' range.
 */
#define ADB_SOFT_ADDRESS_START		8
#define ADB_SOFT_ADDRESS_END		(NUM_ADB_ADDRESSES - 1)

#endif	/* _ARCHITECTURE_ADB_BUS_ */
