/*
 * Copyright (c) 1998-2009 Apple Inc. All rights reserved.
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

#ifndef _IOKIT_SCSI_CMDS_INQUIRY_H_
#define _IOKIT_SCSI_CMDS_INQUIRY_H_


//-----------------------------------------------------------------------------
//	Includes
//-----------------------------------------------------------------------------

#if KERNEL
#include <IOKit/IOTypes.h>
#else
#include <CoreFoundation/CoreFoundation.h>
#endif


/*! @header SCSI Inquiry Definitions
	@discussion
	This file contains all definitions for the data returned from
	the INQUIRY (0x12) command.
*/


/*!
 * @enum Payload sizes
 * @discussion
 * Definitions for sizes related to the INQUIRY data.
 * @constant kINQUIRY_StandardDataHeaderSize
 * INQUIRY data header size.
 * @constant kINQUIRY_MaximumDataSize
 * Maximum size for INQUIRY data.
*/
enum
{
	kINQUIRY_StandardDataHeaderSize			= 5,
	kINQUIRY_MaximumDataSize				= 255	
};


/*!
@enum INQUIRY field sizes
@discussion
Sizes for some of the inquiry data fields.
@constant kINQUIRY_VENDOR_IDENTIFICATION_Length
Size of VENDOR_IDENTIFICATION field.
@constant kINQUIRY_PRODUCT_IDENTIFICATION_Length
Size of PRODUCT_IDENTIFICATION field.
@constant kINQUIRY_PRODUCT_REVISION_LEVEL_Length
Size of PRODUCT_REVISION_LEVEL field.
*/
enum
{
	kINQUIRY_VENDOR_IDENTIFICATION_Length	= 8,
	kINQUIRY_PRODUCT_IDENTIFICATION_Length	= 16,
	kINQUIRY_PRODUCT_REVISION_LEVEL_Length	= 4
};


/*!
@struct SCSICmd_INQUIRY_StandardData
@discussion
This structure defines the format of the required standard data that is 
returned for the INQUIRY command.  This is the data that is required to
be returned from all devices.
*/
typedef struct SCSICmd_INQUIRY_StandardData
{
	UInt8		PERIPHERAL_DEVICE_TYPE;				// 7-5 = Qualifier. 4-0 = Device type.
	UInt8		RMB;								// 7 = removable
	UInt8		VERSION;							// 7/6 = ISO/IEC, 5-3 = ECMA, 2-0 = ANSI.
	UInt8		RESPONSE_DATA_FORMAT;				// 7 = AERC, 6 = Obsolete, 5 = NormACA, 4 = HiSup 3-0 = Response data format. (SPC-3 obsoletes AERC)
													// If ANSI Version = 0, this is ATAPI and bits 7-4 = ATAPI version.
	UInt8		ADDITIONAL_LENGTH;					// Number of additional bytes available in inquiry data
	UInt8		SCCSReserved;						// SCC-2 device flag and reserved fields (SPC-3 adds PROTECT 3PC TPGS, and ACC)
	UInt8		flags1;								// First byte of support flags (See SPC-3 section 6.4.2)
	UInt8		flags2;								// Second byte of support flags (Byte 7) (See SPC-3 section 6.4.2)
	char		VENDOR_IDENTIFICATION[kINQUIRY_VENDOR_IDENTIFICATION_Length];
	char		PRODUCT_IDENTIFICATION[kINQUIRY_PRODUCT_IDENTIFICATION_Length];
	char		PRODUCT_REVISION_LEVEL[kINQUIRY_PRODUCT_REVISION_LEVEL_Length];
} SCSICmd_INQUIRY_StandardData;
typedef SCSICmd_INQUIRY_StandardData * SCSICmd_INQUIRY_StandardDataPtr;


/*!
@struct SCSICmd_INQUIRY_StandardDataAll
@discussion
This structure defines the all of the fields that can be returned in
repsonse to the INQUIRy request for the standard data.  There is no
requirement as to how much of the additional data must be returned by a device.
*/
typedef struct SCSICmd_INQUIRY_StandardDataAll
{
	UInt8		PERIPHERAL_DEVICE_TYPE;				// 7-5 = Qualifier. 4-0 = Device type.
	UInt8		RMB;								// 7 = removable
	UInt8		VERSION;							// 7/6 = ISO/IEC, 5-3 = ECMA, 2-0 = ANSI.
	UInt8		RESPONSE_DATA_FORMAT;				// 7 = AERC, 6 = Obsolete, 5 = NormACA, 4 = HiSup 3-0 = Response data format.
													// If ANSI Version = 0, this is ATAPI and bits 7-4 = ATAPI version.
	UInt8		ADDITIONAL_LENGTH;					// Number of additional bytes available in inquiry data
	UInt8		SCCSReserved;						// SCC-2 device flag and reserved fields
	UInt8		flags1;								// First byte of support flags (Byte 6)
	UInt8		flags2;								// Second byte of support flags (Byte 7)
	char		VENDOR_IDENTIFICATION[kINQUIRY_VENDOR_IDENTIFICATION_Length];
	char		PRODUCT_IDENTIFICATION[kINQUIRY_PRODUCT_IDENTIFICATION_Length];
	char		PRODUCT_REVISION_LEVEL[kINQUIRY_PRODUCT_REVISION_LEVEL_Length];
	
	// Following is the optional data that may be returned by a device.
	UInt8		VendorSpecific1[20];
	UInt8		flags3;								// Third byte of support flags, mainly SPI-3 (Byte 56)
	UInt8		Reserved1;
	UInt16		VERSION_DESCRIPTOR[8];
	UInt8		Reserved2[22];
	UInt8		VendorSpecific2[160];
} SCSICmd_INQUIRY_StandardDataAll;


/*!
@enum Peripheral Qualifier
@discussion
Inquiry Peripheral Qualifier definitions
@constant kINQUIRY_PERIPHERAL_QUALIFIER_Connected
Peripheral Device is connected.
@constant kINQUIRY_PERIPHERAL_QUALIFIER_SupportedButNotConnected
Peripheral Device is supported, but not connected.
@constant kINQUIRY_PERIPHERAL_QUALIFIER_NotSupported
Peripheral Device is not supported.
@constant kINQUIRY_PERIPHERAL_QUALIFIER_Mask
Mask to use for PERIPHERAL_DEVICE_TYPE field.
*/
enum
{
	kINQUIRY_PERIPHERAL_QUALIFIER_Connected					= 0x00,
	kINQUIRY_PERIPHERAL_QUALIFIER_SupportedButNotConnected	= 0x20,
	kINQUIRY_PERIPHERAL_QUALIFIER_NotSupported				= 0x60,
	kINQUIRY_PERIPHERAL_QUALIFIER_Mask						= 0xE0
};


/*!
@enum Peripheral Device types
@discussion
Inquiry Peripheral Device type definitions
@constant kINQUIRY_PERIPHERAL_TYPE_DirectAccessSBCDevice
SBC Device.
@constant kINQUIRY_PERIPHERAL_TYPE_SequentialAccessSSCDevice
Sequential Access (Tape) SSC Device.
@constant kINQUIRY_PERIPHERAL_TYPE_PrinterSSCDevice
SSC Device.
@constant kINQUIRY_PERIPHERAL_TYPE_ProcessorSPCDevice
SPC Device.
@constant kINQUIRY_PERIPHERAL_TYPE_WriteOnceSBCDevice
SBC Device.
@constant kINQUIRY_PERIPHERAL_TYPE_CDROM_MMCDevice
MMC Device.
@constant kINQUIRY_PERIPHERAL_TYPE_ScannerSCSI2Device
SCSI2 Device.
@constant kINQUIRY_PERIPHERAL_TYPE_OpticalMemorySBCDevice
SBC Device.
@constant kINQUIRY_PERIPHERAL_TYPE_MediumChangerSMCDevice
SMC Device.
@constant kINQUIRY_PERIPHERAL_TYPE_CommunicationsSSCDevice
Comms SSC Device.
@constant kINQUIRY_PERIPHERAL_TYPE_StorageArrayControllerSCC2Device
SCC2 Device.
@constant kINQUIRY_PERIPHERAL_TYPE_EnclosureServicesSESDevice
SES Device.
@constant kINQUIRY_PERIPHERAL_TYPE_SimplifiedDirectAccessRBCDevice
RBC Device.
@constant kINQUIRY_PERIPHERAL_TYPE_OpticalCardReaderOCRWDevice
OCRW Device.
@constant kINQUIRY_PERIPHERAL_TYPE_ObjectBasedStorageDevice
OSD device.
@constant kINQUIRY_PERIPHERAL_TYPE_AutomationDriveInterface
Automation Drive Interface device.
@constant kINQUIRY_PERIPHERAL_TYPE_WellKnownLogicalUnit
Well known logical unit.
@constant kINQUIRY_PERIPHERAL_TYPE_UnknownOrNoDeviceType
Unknown or no device.
@constant kINQUIRY_PERIPHERAL_TYPE_Mask
Mask to use for PERIPHERAL_DEVICE_TYPE field.
*/
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
	kINQUIRY_PERIPHERAL_TYPE_ObjectBasedStorageDevice			= 0x11,
	kINQUIRY_PERIPHERAL_TYPE_AutomationDriveInterface			= 0x12,
	kINQUIRY_PERIPHERAL_TYPE_WellKnownLogicalUnit				= 0x1E,
	kINQUIRY_PERIPHERAL_TYPE_UnknownOrNoDeviceType				= 0x1F,
	
	
	kINQUIRY_PERIPHERAL_TYPE_Mask								= 0x1F
};


/*!
@enum Removable Bit field definitions
@discussion
Inquiry Removable Bit field definitions
@constant kINQUIRY_PERIPHERAL_RMB_MediumFixed
Medium type is fixed disk.
@constant kINQUIRY_PERIPHERAL_RMB_MediumRemovable
Medium type is removable disk.
@constant kINQUIRY_PERIPHERAL_RMB_BitMask
Mask to use for RMB field.
*/
enum
{
	kINQUIRY_PERIPHERAL_RMB_MediumFixed 						= 0x00,
	kINQUIRY_PERIPHERAL_RMB_MediumRemovable 					= 0x80,
	kINQUIRY_PERIPHERAL_RMB_BitMask 							= 0x80
};


/*!
@enum Version field definitions
@discussion
Definitions for bits/masks in the INQUIRY Version field.
@constant kINQUIRY_ISO_IEC_VERSION_Mask
Mask for valid bits for ISO/IEC Version.
@constant kINQUIRY_ECMA_VERSION_Mask
Mask for valid bits for ECMA Version.
@constant kINQUIRY_ANSI_VERSION_NoClaimedConformance
No ANSI conformance claimed by the device server.
@constant kINQUIRY_ANSI_VERSION_SCSI_1_Compliant
SCSI-1 conformance claimed by the device server.
@constant kINQUIRY_ANSI_VERSION_SCSI_2_Compliant
SCSI-2 conformance claimed by the device server.
@constant kINQUIRY_ANSI_VERSION_SCSI_SPC_Compliant
SPC conformance claimed by the device server.
@constant kINQUIRY_ANSI_VERSION_SCSI_SPC_2_Compliant
SPC-2 conformance claimed by the device server.
@constant kINQUIRY_ANSI_VERSION_SCSI_SPC_3_Compliant
SPC-3 conformance claimed by the device server.
@constant kINQUIRY_ANSI_VERSION_Mask
Mask for valid bits for ANSI Version.
*/
enum
{
	kINQUIRY_ISO_IEC_VERSION_Mask								= 0xC0,
	
	kINQUIRY_ECMA_VERSION_Mask									= 0x38,
	
	kINQUIRY_ANSI_VERSION_NoClaimedConformance					= 0x00,
	kINQUIRY_ANSI_VERSION_SCSI_1_Compliant						= 0x01,
	kINQUIRY_ANSI_VERSION_SCSI_2_Compliant						= 0x02,
	kINQUIRY_ANSI_VERSION_SCSI_SPC_Compliant					= 0x03,
	kINQUIRY_ANSI_VERSION_SCSI_SPC_2_Compliant					= 0x04,
	kINQUIRY_ANSI_VERSION_SCSI_SPC_3_Compliant					= 0x05,
	kINQUIRY_ANSI_VERSION_Mask									= 0x07
};


/*!
@enum Response Data Format field definitions
@discussion
Definitions for bits/masks in the INQUIRY RESPONSE_DATA_FORMAT field.
@constant kINQUIRY_Byte3_HISUP_Bit
HISUP bit definition.
@constant kINQUIRY_Byte3_NORMACA_Bit
NORMACA bit definition.
@constant kINQUIRY_Byte3_AERC_Bit
AERC bit definition.
@constant kINQUIRY_RESPONSE_DATA_FORMAT_Mask
Mask for valid bits for RESPONSE_DATA_FORMAT.
@constant kINQUIRY_Byte3_HISUP_Mask
Mask to use to test the HISUP bit.
@constant kINQUIRY_Byte3_NORMACA_Mask
Mask to use to test the NORMACA bit.
@constant kINQUIRY_Byte3_AERC_Mask
Mask to use to test the AERC bit.
*/
enum
{
	// Bit definitions
	// Bits 0-3: RESPONSE DATA FORMAT
	kINQUIRY_Byte3_HISUP_Bit				= 4,
	kINQUIRY_Byte3_NORMACA_Bit				= 5,
	// Bit 6 is Obsolete
	kINQUIRY_Byte3_AERC_Bit					= 7,
	
	// Masks
	kINQUIRY_RESPONSE_DATA_FORMAT_Mask		= 0x0F, // Bits 0-3
	kINQUIRY_Byte3_HISUP_Mask				= (1 << kINQUIRY_Byte3_HISUP_Bit),
	kINQUIRY_Byte3_NORMACA_Mask				= (1 << kINQUIRY_Byte3_NORMACA_Bit),
	// Bit 6 is Obsolete
	kINQUIRY_Byte3_AERC_Mask				= (1 << kINQUIRY_Byte3_AERC_Bit)
};


/*!
@enum SCCS field definitions
@discussion
Definitions for bits/masks in the INQUIRY SCCSReserved field.
@constant kINQUIRY_Byte5_SCCS_Bit
SCCS bit definition.
@constant kINQUIRY_Byte5_ACC_Bit
ACC bit definition.
@constant kINQUIRY_Byte5_3PC_Bit
3PC bit definition.
@constant kINQUIRY_Byte5_PROTECT_Bit
PROTECT bit definition.
@constant kINQUIRY_Byte5_SCCS_Mask
Mask to use to test the SCCS bit.
@constant kINQUIRY_Byte5_ACC_Mask
Mask to use to test the ACC bit.
@constant kINQUIRY_Byte5_TPGS_Mask
Mask to use for the TPGS bits.
@constant kINQUIRY_Byte5_3PC_Mask
Mask to use to test the 3PC bit.
@constant kINQUIRY_Byte5_PROTECT_Mask
Mask to use to test the PROTECT bit.
*/
enum
{
	// Bit definitions
	kINQUIRY_Byte5_SCCS_Bit					= 7,
	kINQUIRY_Byte5_ACC_Bit					= 6,
	// Bits 4-5: TPGS
	kINQUIRY_Byte5_3PC_Bit					= 3,
	// Bits 1-2: Reserved
	kINQUIRY_Byte5_PROTECT_Bit				= 0,
	
	// Masks
	kINQUIRY_Byte5_SCCS_Mask				= (1 << kINQUIRY_Byte5_SCCS_Bit),
	kINQUIRY_Byte5_ACC_Mask					= (1 << kINQUIRY_Byte5_ACC_Bit),
	kINQUIRY_Byte5_TPGS_Mask				= 0x18,
	kINQUIRY_Byte5_3PC_Mask					= (1 << kINQUIRY_Byte5_3PC_Bit),
	// Bits 1-2: Reserved
	kINQUIRY_Byte5_PROTECT_Mask				= (1 << kINQUIRY_Byte5_PROTECT_Bit)
};


/*!
@enum flags1 field definitions
@discussion
Definitions for bits/masks in the INQUIRY flags1 field.
@constant kINQUIRY_Byte6_ADDR16_Bit
ADDR16 bit definition.
@constant kINQUIRY_Byte6_MCHNGR_Bit
MCHNGR bit definition.
@constant kINQUIRY_Byte6_MULTIP_Bit
MULTIP bit definition.
@constant kINQUIRY_Byte6_VS_Bit
VS bit definition.
@constant kINQUIRY_Byte6_ENCSERV_Bit
ENCSERV bit definition.
@constant kINQUIRY_Byte6_BQUE_Bit
BQUE bit definition.
@constant kINQUIRY_Byte6_ADDR16_Mask
Mask to use to test the ADDR16 bit.
@constant kINQUIRY_Byte6_MCHNGR_Mask
Mask to use to test the MCHNGR bit.
@constant kINQUIRY_Byte6_MULTIP_Mask
Mask to use to test the MULTIP bit.
@constant kINQUIRY_Byte6_VS_Mask
Mask to use to test the VS bit.
@constant kINQUIRY_Byte6_ENCSERV_Mask
Mask to use to test the ENCSERV bit.
@constant kINQUIRY_Byte6_BQUE_Mask
Mask to use to test the BQUE bit.
*/
enum
{
	// Byte offset
	kINQUIRY_Byte6_Offset					= 6,
	
	// Bit definitions
	kINQUIRY_Byte6_ADDR16_Bit				= 0,	// SPI Specific
	// Bit 1 is Obsolete
	// Bit 2 is Obsolete
	kINQUIRY_Byte6_MCHNGR_Bit				= 3,
	kINQUIRY_Byte6_MULTIP_Bit				= 4,
	kINQUIRY_Byte6_VS_Bit					= 5,	
	kINQUIRY_Byte6_ENCSERV_Bit				= 6,	
	kINQUIRY_Byte6_BQUE_Bit					= 7,	

	// Masks
	kINQUIRY_Byte6_ADDR16_Mask				= (1 << kINQUIRY_Byte6_ADDR16_Bit),	// SPI Specific
	// Bit 1 is Obsolete
	// Bit 2 is Obsolete
	kINQUIRY_Byte6_MCHNGR_Mask				= (1 << kINQUIRY_Byte6_MCHNGR_Bit),
	kINQUIRY_Byte6_MULTIP_Mask				= (1 << kINQUIRY_Byte6_MULTIP_Bit),
	kINQUIRY_Byte6_VS_Mask					= (1 << kINQUIRY_Byte6_VS_Bit),
	kINQUIRY_Byte6_ENCSERV_Mask				= (1 << kINQUIRY_Byte6_ENCSERV_Bit),
	kINQUIRY_Byte6_BQUE_Mask				= (1 << kINQUIRY_Byte6_BQUE_Bit)
};


/*!
@enum flags2 field definitions
@discussion
Definitions for bits/masks in the INQUIRY flags2 field.
@constant kINQUIRY_Byte7_VS_Bit
VS bit definition.
@constant kINQUIRY_Byte7_CMDQUE_Bit
CMDQUE bit definition.
@constant kINQUIRY_Byte7_TRANDIS_Bit
TRANDIS bit definition.
@constant kINQUIRY_Byte7_LINKED_Bit
LINKED bit definition.
@constant kINQUIRY_Byte7_SYNC_Bit
SYNC bit definition.
@constant kINQUIRY_Byte7_WBUS16_Bit
WBUS16 bit definition.
@constant kINQUIRY_Byte7_RELADR_Bit
RELADR bit definition.
@constant kINQUIRY_Byte7_VS_Mask
Mask to use to test the VS bit.
@constant kINQUIRY_Byte7_CMDQUE_Mask
Mask to use to test the CMDQUE bit.
@constant kINQUIRY_Byte7_TRANDIS_Mask
Mask to use to test the TRANDIS bit.
@constant kINQUIRY_Byte7_LINKED_Mask
Mask to use to test the LINKED bit.
@constant kINQUIRY_Byte7_SYNC_Mask
Mask to use to test the SYNC bit.
@constant kINQUIRY_Byte7_WBUS16_Mask
Mask to use to test the WBUS16 bit.
@constant kINQUIRY_Byte7_RELADR_Mask
Mask to use to test the RELADR bit.
*/
enum
{
	// Byte offset
	kINQUIRY_Byte7_Offset					= 7,
	
	// Bit definitions
	kINQUIRY_Byte7_VS_Bit					= 0,
	kINQUIRY_Byte7_CMDQUE_Bit				= 1,
	kINQUIRY_Byte7_TRANDIS_Bit				= 2,	// SPI Specific
	kINQUIRY_Byte7_LINKED_Bit				= 3,
	kINQUIRY_Byte7_SYNC_Bit					= 4,	// SPI Specific
	kINQUIRY_Byte7_WBUS16_Bit				= 5,	// SPI Specific
	// Bit 6 is Obsolete
	kINQUIRY_Byte7_RELADR_Bit				= 7,
	
	// Masks
	kINQUIRY_Byte7_VS_Mask					= (1 << kINQUIRY_Byte7_VS_Bit),
	kINQUIRY_Byte7_CMDQUE_Mask				= (1 << kINQUIRY_Byte7_CMDQUE_Bit),
	kINQUIRY_Byte7_TRANDIS_Mask				= (1 << kINQUIRY_Byte7_TRANDIS_Bit),// SPI Specific
	kINQUIRY_Byte7_LINKED_Mask				= (1 << kINQUIRY_Byte7_LINKED_Bit),
	kINQUIRY_Byte7_SYNC_Mask				= (1 << kINQUIRY_Byte7_SYNC_Bit),	// SPI Specific
	kINQUIRY_Byte7_WBUS16_Mask				= (1 << kINQUIRY_Byte7_WBUS16_Bit),	// SPI Specific
	// Bit 6 is Obsolete
	kINQUIRY_Byte7_RELADR_Mask				= (1 << kINQUIRY_Byte7_RELADR_Bit)
};


/*!
@enum Byte 56 features field definitions
@discussion
Definitions for bits/masks in the INQUIRY Byte 56 field.
Inquiry Byte 56 features (for devices that report an ANSI VERSION of
kINQUIRY_ANSI_VERSION_SCSI_SPC_Compliant or later).
These are SPI-3 Specific.
@constant kINQUIRY_Byte56_IUS_Bit
IUS bit definition.
@constant kINQUIRY_Byte56_QAS_Bit
QAS bit definition.
@constant kINQUIRY_Byte56_IUS_Mask
Mask to use to test the IUS bit.
@constant kINQUIRY_Byte56_QAS_Mask
Mask to use to test the QAS bit.
@constant kINQUIRY_Byte56_CLOCKING_Mask
Mask to use to test CLOCKING bits.
@constant kINQUIRY_Byte56_CLOCKING_ONLY_ST
Single-transition clocking only.
@constant kINQUIRY_Byte56_CLOCKING_ONLY_DT
Double-transition clocking only.
@constant kINQUIRY_Byte56_CLOCKING_ST_AND_DT
Single-transition and double-transition clocking.
*/
enum
{
	// Byte offset
	kINQUIRY_Byte56_Offset					= 56,

	// Bit definitions
	kINQUIRY_Byte56_IUS_Bit					= 0,
	kINQUIRY_Byte56_QAS_Bit					= 1,
	// Bits 2 and 3 are the CLOCKING bits
	// All other bits are reserved
	
	kINQUIRY_Byte56_IUS_Mask				= (1 << kINQUIRY_Byte56_IUS_Bit),
	kINQUIRY_Byte56_QAS_Mask				= (1 << kINQUIRY_Byte56_QAS_Bit),
	kINQUIRY_Byte56_CLOCKING_Mask			= 0x0C,

	// Definitions for the CLOCKING bits
	kINQUIRY_Byte56_CLOCKING_ONLY_ST		= 0x00,
	kINQUIRY_Byte56_CLOCKING_ONLY_DT		= 0x04,
	// kINQUIRY_Byte56_CLOCKING_RESERVED	= 0x08,
	kINQUIRY_Byte56_CLOCKING_ST_AND_DT		= 0x0C
};


/*!
@define kINQUIRY_VERSION_DESCRIPTOR_MaxCount
Maximum number of INQUIRY version descriptors supported.
*/
#define	kINQUIRY_VERSION_DESCRIPTOR_MaxCount		8


/*!
@enum kINQUIRY_VERSION_DESCRIPTOR_SAT
SAT specification version descriptor.
*/
enum
{
	kINQUIRY_VERSION_DESCRIPTOR_SAT					= 0x1EA0
};


/*
IORegistry property names for information derived from the Inquiry data.
The Peripheral Device Type is the only property that the 
generic Logical Unit Drivers will use to match. These properties are
listed in order of matching priority. First is the Peripheral Device Type.
Second is the Vendor Identification. Third is the Product Identification.
Last is the Product Revision Level. To match a particular product, you would
specify the Peripheral Device Type, Vendor Identification, and Product
Identification. To restrict the match to a particular firmware revision, you
would add the Product Revision Level. To not match on a particular product,
but on a particular vendor's products, you would only include the 
Peripheral Device Type and the Vendor Identification.
*/

/*!
@define kIOPropertySCSIPeripheralDeviceType
SCSI Peripheral Device Type as reported in the INQUIRY data.
*/
#define kIOPropertySCSIPeripheralDeviceType			"Peripheral Device Type"

/*!
@define kIOPropertySCSIPeripheralDeviceTypeSize
Size of the kIOPropertySCSIPeripheralDeviceType key.
*/
#define kIOPropertySCSIPeripheralDeviceTypeSize		8

/* These properties are listed in order of matching priority */

/*!
@define kIOPropertySCSIVendorIdentification
Vendor ID as reported in the INQUIRY data. Additional space characters (0x20)
are truncated.
*/
#define kIOPropertySCSIVendorIdentification			"Vendor Identification"

/*!
@define kIOPropertySCSIProductIdentification
Product ID as reported in the INQUIRY data. Additional space characters (0x20)
are truncated.
*/
#define kIOPropertySCSIProductIdentification		"Product Identification"

/*!
@define kIOPropertySCSIProductRevisionLevel
Product Revision Level as reported in the INQUIRY data.
*/
#define kIOPropertySCSIProductRevisionLevel			"Product Revision Level"


/*!
@enum INQUIRY Page Codes
@discussion INQUIRY Page Codes to be used when EVPD is set in the
INQUIRY command.
@constant kINQUIRY_Page00_PageCode
Page Code 00h.
@constant kINQUIRY_Page80_PageCode
Page Code 80h.
@constant kINQUIRY_Page83_PageCode
Page Code 83h.
@constant kINQUIRY_Page89_PageCode
Page Code 89h.
*/
enum
{
	kINQUIRY_Page00_PageCode				= 0x00,
	kINQUIRY_Page80_PageCode				= 0x80,
	kINQUIRY_Page83_PageCode				= 0x83,
	kINQUIRY_Page89_PageCode				= 0x89
};	


/*!
@struct SCSICmd_INQUIRY_Page00_Header
@discussion INQUIRY Page 00h Header.
*/
typedef struct SCSICmd_INQUIRY_Page00_Header
{
	UInt8		PERIPHERAL_DEVICE_TYPE;				// 7-5 = Qualifier. 4-0 = Device type.
	UInt8		PAGE_CODE;							// Must be equal to 00h
	UInt8		RESERVED;							// reserved field
	UInt8		PAGE_LENGTH;						// n-3 bytes
} SCSICmd_INQUIRY_Page00_Header;


/*!
@struct SCSICmd_INQUIRY_Page80_Header
@discussion INQUIRY Page 80h Header.
*/
typedef struct SCSICmd_INQUIRY_Page80_Header
{
	UInt8		PERIPHERAL_DEVICE_TYPE;				// 7-5 = Qualifier. 4-0 = Device type.
	UInt8		PAGE_CODE;							// Must be equal to 80h
	UInt8		RESERVED;							// reserved field
	UInt8		PAGE_LENGTH;						// n-3 bytes
	UInt8		PRODUCT_SERIAL_NUMBER;				// 4-n
} SCSICmd_INQUIRY_Page80_Header;


/*!
@define kIOPropertySCSIINQUIRYUnitSerialNumber
Key that describes the INQUIRY Unit Serial Number in the IORegistry.
*/
#define kIOPropertySCSIINQUIRYUnitSerialNumber		"INQUIRY Unit Serial Number"


/*!
@struct SCSICmd_INQUIRY_Page83_Header
@discussion INQUIRY Page 83h Header.
*/
typedef struct SCSICmd_INQUIRY_Page83_Header
{
	UInt8		PERIPHERAL_DEVICE_TYPE;				// 7-5 = Qualifier. 4-0 = Device type.
	UInt8		PAGE_CODE;							// Must be equal to 83h
	UInt8		RESERVED;							// reserved field
	UInt8		PAGE_LENGTH;						// n-3 bytes
} SCSICmd_INQUIRY_Page83_Header;


/*!
@struct SCSICmd_INQUIRY_Page83_Header_SPC_16
@discussion INQUIRY Page 83h Header used with the 16 byte INQUIRY command.
*/
typedef struct SCSICmd_INQUIRY_Page83_Header_SPC_16
{
	UInt8		PERIPHERAL_DEVICE_TYPE;				// 7-5 = Qualifier. 4-0 = Device type.
	UInt8		PAGE_CODE;							// Must be equal to 83h
	UInt16		PAGE_LENGTH;						// n-3 bytes
} SCSICmd_INQUIRY_Page83_Header_SPC_16;


/*!
@struct SCSICmd_INQUIRY_Page83_Identification_Descriptor
@discussion INQUIRY Page 83h Identification Descriptor.
*/
typedef struct SCSICmd_INQUIRY_Page83_Identification_Descriptor
{
	UInt8		CODE_SET;							// 7-4 = Protocol Identifier. 3-0 = Code Set
	UInt8		IDENTIFIER_TYPE;					// 7 = PIV 5-4 = ASSOCIATION 3-0 = Identifier
	UInt8		RESERVED;							
	UInt8		IDENTIFIER_LENGTH;
	UInt8		IDENTIFIER;
} SCSICmd_INQUIRY_Page83_Identification_Descriptor;


/*!
@enum INQUIRY Page 83h Code Set
@discussion
Definitions for the Code Set field.
@constant kINQUIRY_Page83_CodeSetBinaryData
The identifier contains binary data.
@constant kINQUIRY_Page83_CodeSetASCIIData
The identifier contains ASCII data.
@constant kINQUIRY_Page83_CodeSetUTF8Data
The identifier contains UTF-8 data.
*/
enum
{
	kINQUIRY_Page83_CodeSetReserved			= 0x0,
	kINQUIRY_Page83_CodeSetBinaryData		= 0x1,
	kINQUIRY_Page83_CodeSetASCIIData		= 0x2,
	kINQUIRY_Page83_CodeSetUTF8Data			= 0x3,
	// 0x4 - 0xF reserved
	kINQUIRY_Page83_CodeSetMask				= 0xF
};	


/*!
@enum INQUIRY Page 83h Association
@discussion
Definitions for the Association field.
@constant kINQUIRY_Page83_AssociationLogicalUnit
Association of the identifier is with the logical unit.
@constant kINQUIRY_Page83_AssociationDevice
Association of the identifier is with the device (same as logical unit in SPC-2).
@constant kINQUIRY_Page83_AssociationTargetPort
Association of the identifier is with the target port.
@constant kINQUIRY_Page83_AssociationTargetDevice
Association of the identifier is with the target device (i.e. all ports).
@constant kINQUIRY_Page83_AssociationMask
Mask to use to determine association.
*/
enum
{	
	// SPC-3 - Association is changed to be specific to 
	// Logical Units
	kINQUIRY_Page83_AssociationLogicalUnit	= 0x00,
	
	// Backwards compatibility for SPC-2
	kINQUIRY_Page83_AssociationDevice 		= kINQUIRY_Page83_AssociationLogicalUnit,
	
	// Association is related to a Target Port
	kINQUIRY_Page83_AssociationTargetPort	= 0x10,
	
	// SPC-3 - Added as specific association to
	// a Target device.
	kINQUIRY_Page83_AssociationTargetDevice	= 0x20,
	
	kINQUIRY_Page83_AssociationMask			= 0x30
};	
		

/*!
@enum INQUIRY Page 83h Identifier Type
@discussion
Definitions for the Identifier Type field.
@constant kINQUIRY_Page83_IdentifierTypeUndefined
Undefined Identifier Type.
@constant kINQUIRY_Page83_IdentifierTypeVendorID
Vendor Specific Identifier Type.
@constant kINQUIRY_Page83_IdentifierTypeIEEE_EUI64
EUI-64 Identifier Type.
@constant kINQUIRY_Page83_IdentifierTypeNAAIdentifier
NAA Identifier Type.
@constant kINQUIRY_Page83_IdentifierTypeRelativePortIdentifier
Relative Target Port Identifier Type.
@constant kINQUIRY_Page83_IdentifierTypeTargetPortGroup
Target Port Group Identifier Type.
@constant kINQUIRY_Page83_IdentifierTypeLogicalUnitGroup
Logical Unit Group Identifier Type.
@constant kINQUIRY_Page83_IdentifierTypeMD5LogicalUnitIdentifier
MD5 Logical Unit Identifier Type.
@constant kINQUIRY_Page83_IdentifierTypeSCSINameString
SCSI Name String Identifier Type.
@constant kINQUIRY_Page83_IdentifierTypeMask
Mask to use to determine association.
@constant kINQUIRY_Page83_ProtocolIdentifierValidBit
PIV Bit definition.
@constant kINQUIRY_Page83_ProtocolIdentifierValidMask
Mask to use to determine if PIV is set.
*/
enum
{
	kINQUIRY_Page83_IdentifierTypeUndefined					= 0,
	kINQUIRY_Page83_IdentifierTypeVendorID					= 1,
	kINQUIRY_Page83_IdentifierTypeIEEE_EUI64				= 2,
	kINQUIRY_Page83_IdentifierTypeNAAIdentifier				= 3,
	kINQUIRY_Page83_IdentifierTypeRelativePortIdentifier	= 4,
	kINQUIRY_Page83_IdentifierTypeTargetPortGroup			= 5,
	kINQUIRY_Page83_IdentifierTypeLogicalUnitGroup			= 6,
	kINQUIRY_Page83_IdentifierTypeMD5LogicalUnitIdentifier  = 7,
	kINQUIRY_Page83_IdentifierTypeSCSINameString			= 8,
	// 0x9 - 0xF Reserved
	
	kINQUIRY_Page83_IdentifierTypeMask						= 0xF,
	
	kINQUIRY_Page83_ProtocolIdentifierValidBit				= 7,
	kINQUIRY_Page83_ProtocolIdentifierValidMask				= (1 << kINQUIRY_Page83_ProtocolIdentifierValidBit)
	
};	

// Backwards compatibility
#define kINQUIRY_Page83_IdentifierTypeFCNameIdentifier		kINQUIRY_Page83_IdentifierTypeNAAIdentifier


/*!
@enum Protocol Identifier values
@discussion
Definitions for the protocol identifier values.
@constant kSCSIProtocolIdentifier_FibreChannel
FibreChannel Protocol Identifier.
@constant kSCSIProtocolIdentifier_ParallelSCSI
Parallel SCSI Protocol Identifier.
@constant kSCSIProtocolIdentifier_SSA
SSA Protocol Identifier.
@constant kSCSIProtocolIdentifier_FireWire
FireWire (IEEE-1394) Protocol Identifier.
@constant kSCSIProtocolIdentifier_RDMA
RDMA Protocol Identifier.
@constant kSCSIProtocolIdentifier_iSCSI
iSCSI Protocol Identifier.
@constant kSCSIProtocolIdentifier_SAS
SAS Protocol Identifier.
@constant kSCSIProtocolIdentifier_ADT
ADT Protocol Identifier.
@constant kSCSIProtocolIdentifier_ATAPI
ATAPI Protocol Identifier.
@constant kSCSIProtocolIdentifier_None
No Protocol Identifier.
*/
enum
{
	kSCSIProtocolIdentifier_FibreChannel					= 0,
	kSCSIProtocolIdentifier_ParallelSCSI					= 1,
	kSCSIProtocolIdentifier_SSA								= 2,
	kSCSIProtocolIdentifier_FireWire						= 3,
	kSCSIProtocolIdentifier_RDMA							= 4,
	kSCSIProtocolIdentifier_iSCSI							= 5,
	kSCSIProtocolIdentifier_SAS								= 6,
	kSCSIProtocolIdentifier_ADT								= 7,
	kSCSIProtocolIdentifier_ATAPI							= 8,
	// 0x9-0xE Reserved
	kSCSIProtocolIdentifier_None							= 0xF
};


/*!
@define kIOPropertySCSIINQUIRYDeviceIdentification
Device Identification key.
*/
#define kIOPropertySCSIINQUIRYDeviceIdentification		"INQUIRY Device Identification"


/*!
@define kIOPropertySCSIINQUIRYDeviceIdCodeSet
Code Set type key.
*/
#define kIOPropertySCSIINQUIRYDeviceIdCodeSet			"Code Set"


/*!
@define kIOPropertySCSIINQUIRYDeviceIdType
Identifier Type key.
*/
#define kIOPropertySCSIINQUIRYDeviceIdType				"Identifier Type"


/*!
@define kIOPropertySCSIINQUIRYDeviceIdAssociation
Association key.
*/
#define kIOPropertySCSIINQUIRYDeviceIdAssociation		"Association"


/*!
@define kIOPropertySCSIINQUIRYDeviceIdentifier
Identifier key (data or string).
*/
#define kIOPropertySCSIINQUIRYDeviceIdentifier			"Identifier"
		

/*!
@struct SCSICmd_INQUIRY_Page89_Data
@discussion INQUIRY Page 89h data as defined in the SAT 1.0
specification. This section contians all structures and
definitions used by the INQUIRY command in response to a request
for page 89h - ATA information VPD Page.
*/
typedef struct SCSICmd_INQUIRY_Page89_Data
{
	UInt8		PERIPHERAL_DEVICE_TYPE;				// 7-5 = Qualifier. 4-0 = Device type.
	UInt8		PAGE_CODE;							// Must be equal to 89h
	UInt16		PAGE_LENGTH;						// Must be equal to 238h
	UInt32		Reserved;
	UInt8		SAT_VENDOR_IDENTIFICATION[kINQUIRY_VENDOR_IDENTIFICATION_Length];
	UInt8		SAT_PRODUCT_IDENTIFICATION[kINQUIRY_PRODUCT_IDENTIFICATION_Length];
	UInt8		SAT_PRODUCT_REVISION_LEVEL[kINQUIRY_PRODUCT_REVISION_LEVEL_Length];
	UInt8		ATA_DEVICE_SIGNATURE[20];
	UInt8		COMMAND_CODE;
	UInt8		Reserved2[3];
	UInt8		IDENTIFY_DATA[512];
} SCSICmd_INQUIRY_Page89_Data;


/*!
@define kIOPropertySATVendorIdentification
Vendor Identification of the SATL.
*/
#define kIOPropertySATVendorIdentification			"SAT Vendor Identification"


/*!
@define kIOPropertySATProductIdentification
Product Identification of the SATL.
*/
#define kIOPropertySATProductIdentification			"SAT Product Identification"


/*!
@define kIOPropertySATProductRevisonLevel
Product Revision Level of the SATL.
*/
#define kIOPropertySATProductRevisonLevel			"SAT Product Revision Level"


#endif	/* _IOKIT_SCSI_CMDS_INQUIRY_H_ */
