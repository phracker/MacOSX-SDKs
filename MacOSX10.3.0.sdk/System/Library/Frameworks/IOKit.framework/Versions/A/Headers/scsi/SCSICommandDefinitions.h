/*
 * Copyright (c) 2001 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _IOKIT_SCSI_COMMAND_DEFINITIONS_H_
#define _IOKIT_SCSI_COMMAND_DEFINITIONS_H_


#if KERNEL
#include <IOKit/IOTypes.h>
#else
#include <CoreFoundation/CoreFoundation.h>
#endif


#pragma mark About this file
/* This file contains all the definitions for types and constants that are
 * used by the command set classes for building CDBs.  The field type
 * definitions are used for the parameters passed to a method that builds and
 * sends any SCSI defined command to clearly identify the type of value
 * expected for a parameter.
 * The command methods will then use the appropriate mask to verify that the
 * value passed into a parameter is of the specified type.
 * Currently only types and masks are defined for 4 bytes and smaller fields.
 * If a command is defined that uses a larger field, these should be expanded
 * to include those sizes.
 */ 

#pragma mark Field Type Definitions
/* These are the type definitions used for the parameters of methods that
 * build and send Command Descriptor Blocks.
 */
// 1 Byte or smaller fields.
typedef UInt8	SCSICmdField1Bit;
typedef UInt8	SCSICmdField2Bit;
typedef UInt8	SCSICmdField3Bit;
typedef UInt8	SCSICmdField4Bit;
typedef UInt8	SCSICmdField5Bit;
typedef UInt8	SCSICmdField6Bit;
typedef UInt8	SCSICmdField7Bit;
typedef UInt8	SCSICmdField1Byte;

// 2 Bytes or smaller fields.
typedef UInt16	SCSICmdField9Bit;
typedef UInt16	SCSICmdField10Bit;
typedef UInt16	SCSICmdField11Bit;
typedef UInt16	SCSICmdField12Bit;
typedef UInt16	SCSICmdField13Bit;
typedef UInt16	SCSICmdField14Bit;
typedef UInt16	SCSICmdField15Bit;
typedef UInt16	SCSICmdField2Byte;

// 3 Bytes or smaller fields.
typedef UInt32	SCSICmdField17Bit;
typedef UInt32	SCSICmdField18Bit;
typedef UInt32	SCSICmdField19Bit;
typedef UInt32	SCSICmdField20Bit;
typedef UInt32	SCSICmdField21Bit;
typedef UInt32	SCSICmdField22Bit;
typedef UInt32	SCSICmdField23Bit;
typedef UInt32	SCSICmdField3Byte;

// 4 Bytes or smaller fields.
typedef UInt32	SCSICmdField25Bit;
typedef UInt32	SCSICmdField26Bit;
typedef UInt32	SCSICmdField27Bit;
typedef UInt32	SCSICmdField28Bit;
typedef UInt32	SCSICmdField29Bit;
typedef UInt32	SCSICmdField30Bit;
typedef UInt32	SCSICmdField31Bit;
typedef UInt32	SCSICmdField4Byte;

#pragma mark Field Mask Definitions
// These are masks that are used to verify that the values passed into the
// parameters for the fields are not larger than the field size.
// 1 Byte or smaller fields.
enum
{
	kSCSICmdFieldMask1Bit 	= 0x01,
	kSCSICmdFieldMask2Bit 	= 0x03,
	kSCSICmdFieldMask3Bit 	= 0x07,
	kSCSICmdFieldMask4Bit 	= 0x0F,
	kSCSICmdFieldMask5Bit 	= 0x1F,
	kSCSICmdFieldMask6Bit 	= 0x3F,
	kSCSICmdFieldMask7Bit 	= 0x7F,
	kSCSICmdFieldMask1Byte 	= 0xFF
};

// 2 Byte or smaller fields.
enum
{
	kSCSICmdFieldMask9Bit 	= 0x01FF,
	kSCSICmdFieldMask10Bit 	= 0x03FF,
	kSCSICmdFieldMask11Bit 	= 0x07FF,
	kSCSICmdFieldMask12Bit 	= 0x0FFF,
	kSCSICmdFieldMask13Bit 	= 0x1FFF,
	kSCSICmdFieldMask14Bit 	= 0x3FFF,
	kSCSICmdFieldMask15Bit 	= 0x7FFF,
	kSCSICmdFieldMask2Byte 	= 0xFFFF
};

// 3 Byte or smaller fields.
enum
{
	kSCSICmdFieldMask17Bit 	= 0x01FFFF,
	kSCSICmdFieldMask18Bit 	= 0x03FFFF,
	kSCSICmdFieldMask19Bit 	= 0x07FFFF,
	kSCSICmdFieldMask20Bit 	= 0x0FFFFF,
	kSCSICmdFieldMask21Bit 	= 0x1FFFFF,
	kSCSICmdFieldMask22Bit 	= 0x3FFFFF,
	kSCSICmdFieldMask23Bit 	= 0x7FFFFF,
	kSCSICmdFieldMask3Byte 	= 0xFFFFFF
};

// 4 Byte or smaller fields.
enum
{
	kSCSICmdFieldMask25Bit 	= 0x01FFFFFF,
	kSCSICmdFieldMask26Bit 	= 0x03FFFFFF,
	kSCSICmdFieldMask27Bit 	= 0x07FFFFFF,
	kSCSICmdFieldMask28Bit 	= 0x0FFFFFFF,
	kSCSICmdFieldMask29Bit 	= 0x1FFFFFFF,
	kSCSICmdFieldMask30Bit 	= 0x3FFFFFFF,
	kSCSICmdFieldMask31Bit 	= 0x7FFFFFFF,
	kSCSICmdFieldMask4Byte 	= 0xFFFFFFFF
};

#endif	/* _IOKIT_SCSI_COMMAND_DEFINITIONS_H_ */