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

/*
 * Copyright (c) 2000-2001 Apple Computer, Inc.  All rights reserved.
 *
 * HISTORY
 *
 *		09/28/2000	CJS		Started IOATABlockStorageDevice
 *							(ported IOATAHDDrive)
 *
 */


/*
 * Important word offsets in device identify data as
 * defined in ATA-5 standard
 */
	
enum
{
	kATAIdentifyConfiguration				= 0,
	kATAIdentifyLogicalCylinderCount 		= 1,
	kATAIdentifyLogicalHeadCount			= 3,
	kATAIdentifySectorsPerTrack				= 6,
	kATAIdentifySerialNumber				= 10,
	kATAIdentifyFirmwareRevision			= 23,
	kATAIdentifyModelNumber					= 27,
	kATAIdentifyMultipleSectorCount			= 47,
	kATAIdentifyDriveCapabilities			= 49,
	kATAIdentifyDriveCapabilitiesExtended	= 50,
	kATAIdentifyPIOTiming					= 51,
	kATAIdentifyExtendedInfoSupport			= 53,
	kATAIdentifyCurrentCylinders			= 54,
	kATAIdentifyCurrentHeads				= 55,
	kATAIdentifyCurrentSectors				= 56,
	kATAIdentifyCurrentCapacity				= 57,
	kATAIdentifyCurrentMultipleSectors		= 59,
	kATAIdentifyLBACapacity					= 60,
	kATAIdentifySingleWordDMA				= 62,
	kATAIdentifyMultiWordDMA				= 63,
	kATAIdentifyAdvancedPIOModes			= 64,
	kATAIdentifyMinMultiWordDMATime			= 65,
	kATAIdentifyRecommendedMultiWordDMATime	= 66,
	kATAIdentifyMinPIOTime					= 67,
	kATAIdentifyMinPIOTimeWithIORDY			= 68,
	kATAIdentifyQueueDepth					= 75,
	kATAIdentifyMajorVersion				= 80,
	kATAIdentifyMinorVersion				= 81,
	kATAIdentifyCommandSetSupported			= 82,
	kATAIdentifyCommandSetSupported2		= 83,
	kATAIdentifyCommandExtension1			= 84,
	kATAIdentifyCommandExtension2			= 85,
	kATAIdentifyCommandsEnabled				= 86,
	kATAIdentifyCommandsDefault				= 87,
	kATAIdentifyUltraDMASupported			= 88
};
	

/* 
 * Important bits in device identify data
 * as defined in ATA-5 standard
 */
 
enum
{
	// Configuration field (word 0)
	kFixedDeviceBit			= 6,							// Fixed disk indicator bit
	kRemoveableMediaBit		= 7,							// Removable media indicator bit
	kNonMagneticDriveBit	= 15,							// Non-magnetic drive indicator bit
	
	kFixedDeviceMask		= (1 << kFixedDeviceBit),		// Mask for fixed disk indicator
	kRemoveableMediaMask	= (1 << kRemoveableMediaBit),	// Mask for removable media indicator
	kNonMagneticDriveMask	= (1 << kNonMagneticDriveBit),	// Mask for non-magnetic drive indicator

	// Capabilities field (word 49)
	kDMABit					= 8,							// DMA supported bit
	kLBABit					= 9,							// LBA supported bit
	kIORDYDisableBit		= 10,							// IORDY can be disabled bit
	kIORDYBit				= 11,							// IORDY supported bit
	kStandbyTimerBit		= 13,							// Standby timer supported bit

	kDMASupportedMask		= (1 << kDMABit),				// Mask for DMA supported
	kLBASupportedMask		= (1 << kLBABit),				// Mask for LBA supported
	kDMADisableMask			= (1 << kIORDYDisableBit),		// Mask for DMA supported
	kIORDYSupportedMask		= (1 << kIORDYBit),				// Mask for IORDY supported
	kStandbySupportedMask	= (1 << kStandbyTimerBit),		// Mask for Standby Timer supported

	// Extensions field (word 53)
	kCurFieldsValidBit		= 0,							// Bit to show words 54-58 are valid
	kExtFieldsValidBit		= 1,							// Bit to show words 64-70 are valid
	kCurFieldsValidMask		= (1 << kCurFieldsValidBit),	// Mask for current fields valid
	kExtFieldsValidMask		= (1 << kExtFieldsValidBit),	// Extension word valid

	// Advanced PIO Transfer Modes field (word 64)
	kMode3Bit				= 0,							// Bit to indicate mode 3 is supported
	kMode3Mask				= (1 << kMode3Bit)				// Mask for mode 3 support
};


/* String size constants */
enum
{
	kSizeOfATAModelString 		= 40,
	kSizeOfATARevisionString	= 8
};

/* ATA Command timeout constants ( in milliseconds ) */
enum
{
	kATATimeout10Seconds	= 10000,
	kATATimeout30Seconds	= 30000,
	kATATimeout45Seconds	= 45000,
	kATATimeout1Minute		= 60000,
	kATADefaultTimeout		= kATATimeout30Seconds
};


/* Retry constants */
enum
{
	kATAZeroRetries		= 0,
	kATADefaultRetries	= 4
};

/* max number of blocks supported in ATA transaction */
enum
{
	kIOATAMaxBlocksPerXfer	= 256
};

/* Power Management time constants (in seconds) */
enum
{
	kSecondsInAMinute	= 60,
	k5Minutes			= 5 * kSecondsInAMinute
};

/* Bits for features published in Word 82 of device identify data */
enum
{
	kATASupportsPowerManagementBit  		= 3,
	kATASupportsWriteCacheBit				= 5
};

/* Masks for features published in Word 82 of device identify data */
enum
{
	kATASupportsPowerManagementMask 		= (1 << kATASupportsPowerManagementBit),
	kATASupportsWriteCacheMask				= (1 << kATASupportsWriteCacheBit)
};

/* Bits for features published in Word 83 of device identify data */
enum
{
	kATASupportsCompactFlashBit				= 2,
	kATASupportsAdvancedPowerManagementBit 	= 3,
	
	kATASupports48BitAddressingBit			= 10,
	
	kATASupportsFlushCacheBit				= 12,
	kATASupportsFlushCacheExtendedBit		= 13,
	
};

/* Masks for features published in Word 83 of device identify data */
enum
{
	kATASupportsCompactFlashMask			= (1 << kATASupportsCompactFlashBit),
	kATASupportsAdvancedPowerManagementMask = (1 << kATASupportsAdvancedPowerManagementBit),
	
	kATASupports48BitAddressingMask			= (1 << kATASupports48BitAddressingBit),
	
	kATASupportsFlushCacheMask				= (1 << kATASupportsFlushCacheBit),
	kATASupportsFlushCacheExtendedMask		= (1 << kATASupportsFlushCacheExtendedBit),
	
	// Mask to ensure data is valid
	kATADataIsValidMask						= 0xC000
};

/* ATA supported features */
enum
{
	kIOATAFeaturePowerManagement			= 0x01,
	kIOATAFeatureWriteCache					= 0x02,
	kIOATAFeatureAdvancedPowerManagement 	= 0x04,
	kIOATAFeatureCompactFlash				= 0x08,
	kIOATAFeature48BitLBA					= 0x10
};

/* ATA Advanced Power Management settings (valid settings range from 1-254),
the settings below are the more common settings */
enum
{
	kIOATAMaxPerformance					= 0xFE,
	kIOATADefaultPerformance			 	= 0x80,
	kIOATAMaxPowerSavings					= 0x01
};

/* ATA power states, from lowest to highest power usage */
typedef UInt32 IOATAPowerState;
enum
{
	kIOATAPowerStateSystemSleep	= 0,
	kIOATAPowerStateSleep 		= 1,
	kIOATAPowerStateStandby		= 2,
	kIOATAPowerStateIdle		= 3,
	kIOATAPowerStateActive		= 4,
	kIOATAPowerStates			= 5
};

/* ATA Transfer Mode bit masks */
enum
{
	kATAEnableUltraDMAModeMask 		= 0x40,
	kATAEnableMultiWordDMAModeMask	= 0x20,
	kATAEnablePIOModeMask			= 0x08,
};