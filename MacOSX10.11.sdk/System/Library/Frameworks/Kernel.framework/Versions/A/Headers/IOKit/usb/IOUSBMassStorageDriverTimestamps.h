/*
 * Copyright (c) 2015 Apple Inc. All rights reserved.
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

#ifndef __IOKIT_IO_IOUSBMASSTORAGEDRIVER_TIMESTAMPS__
#define __IOKIT_IO_IOUSBMASSTORAGEDRIVER_TIMESTAMPS__

#include <stdint.h>

#include <sys/kdebug.h>
#if KERNEL
#include <IOKit/IOTimeStamp.h>
#endif

#include <IOKit/scsi/IOSCSIArchitectureModelFamilyTimestamps.h>

#ifndef kSAMClassUMD
#define kSAMClassUMD 44
#endif

extern u_int32_t                    gIOUSBMassStorageDriverDebugFlags;

#ifdef __cplusplus
extern "C" {
#endif
    
#if KERNEL

//--------------------------------------------------------------------------------------------------
//  RecordUSBTimeStamp                                                                      [STATIC]
//--------------------------------------------------------------------------------------------------

static inline void
RecordUMDTimeStamp ( unsigned int   code,
                     unsigned int   a,
                     unsigned int   b,
                     unsigned int   c,
                     unsigned int   d     )
{
    
    if ( gIOUSBMassStorageDriverDebugFlags != 0 )
    {
        IOTimeStampConstant ( code, a, b, c, d );
    }
    
}

#endif


/* The trace codes consist of the following:
 *
 * ----------------------------------------------------------------------
 *|              |               |              |               |Func   |
 *| Class (8)    | SubClass (8)  | SAM Class(6) |  Code (8)     |Qual(2)|
 * ----------------------------------------------------------------------
 *
 * DBG_IOKIT(05h)  DBG_IOSAM(27h)
 *
 * See <sys/kdebug.h> and IOTimeStamp.h for more details.
 *
 */


// USB Mass Storage Driver Tracepoints  0x0527B000 - 0x0527B3FF
enum
{
    
    // Generic UMC Tracepoints
    kIOUSBMassStorageInterfaceNubProbe              		= 0x00,
    kIOUSBMassStorageInterfaceNubStart              		= 0x01,
    kIOUSBMassStorageInterfaceNubStop               		= 0x02,
    kIOUSBMassStorageDriverNubProbe                         = 0x03,
    kIOUSBMassStorageDriverNubStart                         = 0x04,
    kIOUSBMassStorageDriverNubStop                          = 0x05,
    kIOUSBMassStorageDriverStart                            = 0x06,
    kIOUSBMassStorageDriverStop                             = 0x07,
    kSubclassUse                                   		 	= 0x08,
    kCDBLog1                                       		 	= 0x09,
    kCDBLog2                                       		 	= 0x0A,
    kCompleteCommand                                        = 0x0B,
    kCompleteCommandGated                                   = 0x0C,
    
    // CBI & UFI Tracepoints
    
    // UAS Tracepoints
    
    // Bulk-Only Tracepoints           
    kBOTUSBCompletion                                       = 0x040
    
};

// SubclassCodes
enum
{
    
    kSubclassCode_AppleUSBODD                      		 	= 0x00,
    kSubclassCode_AppleUSBCardReaderUMC             		= 0x01
    
};

// SubclassCodes for AppleUSBODD
enum
{
    
    kAppleUSBODD_probe                              		= 0x00,
    kAppleUSBODD_start                              		= 0x01,
    kAppleUSBODD_requestedExtraPower                		= 0x02,
    kAppleUSBODD_isMacModelSupported                		= 0x03,
    kAppleUSBODD_FindACPIPlatformDevice             		= 0x04,
    kAppleUSBODD_CheckForACPIFlags                  		= 0x05
    
};

// SubclassCodes for AppleUSBCardReaderUMC
enum
{
    
    kAppleUSBCardReaderUMC_start                    		= 0x00,
    kAppleUSBCardReaderUMC_stop                     		= 0x01,
    kAppleUSBCardReaderUMC_stop_2							= 0x02,
    kAppleUSBCardReaderUMC_HandlePowerChange        		= 0x03,
    kAppleUSBCardReaderUMC_message                  		= 0x04,
    kAppleUSBCardReaderUMC_setProperty              		= 0x05,
    kAppleUSBCardReaderUMC_gpioMediaDetectFired     		= 0x06,
    kAppleUSBCardReaderUMC_gpioMediaDetectEnable    		= 0x07,
    kAppleUSBCardReaderUMC_controllerReset          		= 0x08,
    kAppleUSBCardReaderUMC_powerControl           		  	= 0x09,
    kAppleUSBCardReaderUMC_waitForReconnect       		  	= 0x0A,
    kAppleUSBCardReaderUMC_systemWillShutdown     		  	= 0x0B,
    kAppleUSBCardReaderUMC_generalPurpose         		 	= 0x0C,
    kAppleUSBCardReaderInterfaceNub_setPowerState   		= 0x0D,
    kAppleUSBCardReaderDriverNub_setPowerState      		= 0x0E,
    kAppleUSBCardReaderDriverNub_powerStateDidChangeTo      = 0x0F
    
};

// Tracepoint macros.
#define UMD_TRACE( code )           ( ( ( DBG_IOKIT & 0xFF ) << 24 ) | ( ( DBG_IOSAM & 0xFF ) << 16 ) | ( ( kSAMClassUMD & 0x3F ) << 10 ) | ( ( code & 0xFF ) << 2 ) )
#define USBODD_TRACE( code )        ( ( ( kSubclassCode_AppleUSBODD & 0xFF ) << 24 ) | ( code & 0xFFFFFF ) )
#define USBCARDREADER_TRACE( code ) ( ( ( kSubclassCode_AppleUSBCardReaderUMC & 0xFF ) << 24 ) | ( code & 0xFFFFFF ) )
    
#ifdef __cplusplus
}
#endif


#endif  /* __IOKIT_IO_IOUSBMASSTORAGEDRIVER_TIMESTAMPS__ */
