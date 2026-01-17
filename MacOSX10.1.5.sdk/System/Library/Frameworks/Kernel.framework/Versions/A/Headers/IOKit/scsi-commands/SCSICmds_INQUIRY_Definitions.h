/*
 * Copyright (c) 1998-2001 Apple Computer, Inc. All rights reserved.
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

#ifndef _IOKIT_SCSI_CMDS_INQUIRY_H_
#define _IOKIT_SCSI_CMDS_INQUIRY_H_

// This file contains all the definitions for the data returned from
// the INQUIRY (0x12) command.

//
// Sizes for some of the inquiry data fields
//
enum
{
	kINQUIRY_VENDOR_IDENTIFICATION_Length	= 8,
	kINQUIRY_PRODUCT_IDENTIFICATION_Length	= 16,
	kINQUIRY_PRODUCT_REVISION_LEVEL_Length	= 4
};

struct SCSICmd_INQUIRY_StandardData
{
	UInt8		PERIPHERAL_DEVICE_TYPE;				// 7-5 = Qualifier. 4-0 = Device type.
	UInt8		RMB;								// 7 = removable
	UInt8		VERSION;							// 7/6 = ISO/IEC, 5-3 = ECMA, 2-0 = ANSI.
	UInt8		RESPONSE_DATA_FORMAT;				// 7 = AERC, 6 = Obsolete, 5 = NormACA, 4 = HiSup 3-0 = Response data format.
													// If ANSI Version = 0, this is ATAPI and bits 7-4 = ATAPI version.
	UInt8		ADDITIONAL_LENGTH;					// Number of additional bytes available in inquiry data
	UInt8		SCCSReserved;						// SCC-2 device flag and reserved fields
	UInt8		flags1;								// First byte of support flags
	UInt8		flags2;								// Second byte of support flags
	char		VENDOR_IDENTIFICATION[kINQUIRY_VENDOR_IDENTIFICATION_Length];
	char		PRODUCT_INDENTIFICATION[kINQUIRY_PRODUCT_IDENTIFICATION_Length];
	char		PRODUCT_REVISION_LEVEL[kINQUIRY_PRODUCT_REVISION_LEVEL_Length];
};
typedef struct SCSICmd_INQUIRY_StandardData SCSICmd_INQUIRY_StandardData;
typedef SCSICmd_INQUIRY_StandardData* SCSICmd_INQUIRY_StandardDataPtr;


// Inquiry Peripheral Qualifier
enum
{
	kINQUIRY_PERIPHERAL_QUALIFIER_Connected					= 0x00,
	kINQUIRY_PERIPHERAL_QUALIFIER_SupportedButNotConnected	= 0x20,
	kINQUIRY_PERIPHERAL_QUALIFIER_NotSupported				= 0x60,
	kINQUIRY_PERIPHERAL_QUALIFIER_Mask						= 0xE0
};

// Inquiry Peripheral Device types
enum
{
	kINQUIRY_PERIPHERAL_TYPE_DirectAccessSBCDevice				= 0x00,
	kINQUIRY_PERIPHERAL_TYPE_SequentialAccessSSCDevice			= 0x01,
	kINQUIRY_PERIPHERAL_TYPE_PrinterSSCDevice					= 0x02,
	kINQUIRY_PERIPHERAL_TYPE_ProcessorSPCDevice					= 0x03,
	kINQUIRY_PERIPHERAL_TYPE_WriteOnceSBCDevice					= 0x04,
	kINQUIRY_PERIPHERAL_TYPE_CDROM_MMCDevice					= 0x05,
	kINQUIRY_PERIPHERAL_TYPE_ScannerSCSI2Device					= 0x06,
	kINQUIRY_PERIPHERAL_TYPE_OpticalMemorySBCDevice				= 0x07,
	kINQUIRY_PERIPHERAL_TYPE_MediumChangerSMCDevice				= 0x08,
	kINQUIRY_PERIPHERAL_TYPE_CommunicationsSSCDevice			= 0x09,
	/* 0x0A - 0x0B ASC IT8 Graphic Arts Prepress Devices */
	kINQUIRY_PERIPHERAL_TYPE_StorageArrayControllerSCC2Device	= 0x0C,
	kINQUIRY_PERIPHERAL_TYPE_EnclosureServicesSESDevice			= 0x0D,
	kINQUIRY_PERIPHERAL_TYPE_SimplifiedDirectAccessRBCDevice	= 0x0E,
	kINQUIRY_PERIPHERAL_TYPE_OpticalCardReaderOCRWDevice		= 0x0F,
	/* 0x10 - 0x1E Reserved Device Types */
	kINQUIRY_PERIPHERAL_TYPE_UnknownOrNoDeviceType				= 0x1F,
	
	kINQUIRY_PERIPHERAL_TYPE_Mask								= 0x1F
};

// Inquiry Removable Bit field definitions
enum
{
	kINQUIRY_PERIPHERAL_RMB_MediumFixed 						= 0x00,
	kINQUIRY_PERIPHERAL_RMB_MediumRemovable 					= 0x80,
	kINQUIRY_PERIPHERAL_RMB_BitMask 							= 0x80
};

// Inquiry ISO/IEC Version field definitions
enum
{
	kINQUIRY_ISO_IEC_VERSION_Mask								= 0xC0
};

// Inquiry ECMA Version field definitions
enum
{
	kINQUIRY_ECMA_VERSION_Mask									= 0x38
};

// Inquiry ANSI Version field definitions
enum
{
	kINQUIRY_ANSI_VERSION_NoClaimedConformance					= 0x00,
	kINQUIRY_ANSI_VERSION_SCSI_1_Compliant						= 0x01,
	kINQUIRY_ANSI_VERSION_SCSI_2_Compliant						= 0x02,
	kINQUIRY_ANSI_VERSION_SCSI_SPC_Compliant					= 0x03,
	kINQUIRY_ANSI_VERSION_SCSI_SPC_2_Compliant					= 0x04,
	kINQUIRY_ANSI_VERSION_Mask									= 0x07
};

// IORegistry property names for information derived from the Inquiry data.
// The Peripheral Device Type is the only property that the 
// generic Logical Unit Drivers will use to match.
#define kIOPropertySCSIPeripheralDeviceType		"Peripheral Device Type"

// These properties are listed in order of matching priority.
#define kIOPropertySCSIVendorIdentification		"Vendor Identification"
#define kIOPropertySCSIProductIdentification	"Product Identification"
#define kIOPropertySCSIProductRevisionLevel		"Product Revision Level"

#endif	/* _IOKIT_SCSI_CMDS_INQUIRY_H_ */
