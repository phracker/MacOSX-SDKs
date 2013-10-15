/*
 * Copyright (c) 2009 Apple Inc. All rights reserved.
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
/*
	File:		DVFamily.h

	Copyright:	© 2001 by Apple Computer, Inc., all rights reserved.

*/
//
//	DVFamily.h
//

#ifndef __DVFAMILY__
#define __DVFAMILY__

#include <IOKit/avc/IOFireWireAVCConsts.h>
#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////
//
// constants
//
///////////////////////////////////////////////////////////////////////

enum 
{
	kInvalidDVDeviceID		= 0,
	kEveryDVDeviceID		= 0xFFFFFFFF,
	kInvalidDVConnectionID		= 0,
        kInvalidDVDeviceRefNum		= 0,
	kEveryDVDeviceRefNum		= 0xFFFFFFFF
};

enum
{
	kDVDisconnectedErr			= -14101,
	kDVBadIDErr				= -14102,
	kUnknownStandardErr			= -14103,
	kAlreadyEnabledErr			= -14104,
	kNotEnabledErr				= -14105,
	kDVDeviceBusyErr			= -14106,
        kDVNoNotificationsErr			= -14107
};

enum
{
	kUnknownStandard	= 0,
	kNTSCStandard		= 1,
	kPALStandard 		= 2
};

// DV events
enum
{
	kInvalidDVDeviceEvent		= 0,
	
	kDVDeviceAdded				= 1 << 0,
	kDVDeviceRemoved			= 1 << 1,
	KDVDeviceInfoChanged		= 1 << 2,
	
	kDVIsochReadEnabled			= 1 << 3,
	kDVIsochReadComplete		= 1 << 4,
	kDVIsochReadDisabled	 	= 1 << 5,

	kDVIsochWriteEnabled		= 1 << 6,
	kDVIsochWriteComplete		= 1 << 7,
	kDVIsochWriteDisabled		= 1 << 8,

	kDVAVCEnabled				= 1 << 9,
	kDVAVCDisabled				= 1 << 10,
	kDVAVCTransactionComplete	= 1 << 11,

	// Tempory new event for input. Goes away DVFamily is dead.
	kDVInputEvent = 1 << 12,

	kDVEveryEvent				= 0x00001fff
};

enum
{
	kDVGlobalEventConnectionID	= 0xffffffff,
	kEventSpecificDataSize		= 16
};

///////////////////////////////////////////////////////////////////////
//
// types
//
///////////////////////////////////////////////////////////////////////

// holds our device identification...
typedef UInt32 DVDeviceID;			

// holds our device connection identification...
typedef UInt32 DVDeviceRefNum;

typedef UInt32 DVClientID;

// AVC
enum {
    kAVCSupportInquiryCommand       	= 0x02,
    kAVCReportInquiryCommand        	= 0x03,

    // Opcodes and parameters
    kAVCWindOpcode                          = 0xc4,
    kAVCWindHighSpeedRewind                 = 0x45,
    kAVCWindStop                            = 0x60,
    kAVCWindRewind                          = 0x65,
    kAVCWindFastForward                     = 0x75,

    kAVCPlayOpcode                          = 0xc3,
    kAVCPlayNextFrame                       = 0x30,
    kAVCPlaySlowest                         = 0x31,
    kAVCPlaySlow6                           = 0x32, 
    kAVCPlaySlow5                           = 0x33,
    kAVCPlaySlow4                           = 0x34,
    kAVCPlaySlow3                           = 0x35,
    kAVCPlaySlow2                           = 0x36,
    kAVCPlaySlow1                           = 0x37,
    kAVCPlay1x                              = 0x38,
    kAVCPlayFast1                           = 0x39, 
    kAVCPlayFast2                           = 0x3a,
    kAVCPlayFast3                           = 0x3b,
    kAVCPlayFast4                           = 0x3c,
    kAVCPlayFast5                           = 0x3d,
    kAVCPlayFast6                           = 0x3e,
    kAVCPlayFastest                         = 0x3f,
    kAVCPlayPreviousFrame                   = 0x40,
    kAVCPlayRevSlowest                      = 0x41,
    kAVCPlayRevSlow6                        = 0x42,
    kAVCPlayRevSlow5                        = 0x43,
    kAVCPlayRevSlow4                        = 0x44,
    kAVCPlayRevSlow3                        = 0x45,
    kAVCPlayRevSlow2                        = 0x46,
    kAVCPlayRevSlow1                        = 0x47,
    kAVCPlayRev1x                           = 0x48,
    kAVCPlayRevFast1                        = 0x49,
    kAVCPlayRevFast2                        = 0x4a,
    kAVCPlayRevFast3                        = 0x4b,
    kAVCPlayRevFast4                        = 0x4c,
    kAVCPlayRevFast5                        = 0x4d,
    kAVCPlayRevFast6                        = 0x4e,
    kAVCPlayRevFastest                      = 0x4f,
    kAVCPlayForward                         = 0x75,
    kAVCPlayForwardPause                    = 0x7d,
    kAVCPlayReverse                         = 0x65,
    kAVCPlayReversePause                    = 0x6d,

    kAVCMediumOpcode                        = 0xc1,
    kAVCMediumEject                         = 0x60,
    kAVCMediumTrayOpen                      = 0x31,
    kAVCMediumTrayClose                     = 0x32,

    kAVCRecordOpcode                        = 0xc2,
    kAVCRecVideoInsert                      = 0x31,
    kAVCRecAudioInsert                      = 0x32,
    kAVCRecAVInsert                         = 0x33,
    kAVCRecSubcodeInsert                    = 0x34,
    kAVCRecord                              = 0x75,
    kAVCRecPause                            = 0x7d,
    kAVCRecVideoInsertPause                 = 0x41,
    kAVCRecAudioInsertPause                 = 0x42,
    kAVCRecAVInsertPause                    = 0x43,
    kAVCRecSubcodeInsertPause               = 0x44,

    kAVCRecSpeedOpcode                      = 0xdb,
    kAVCRecSpeedLowSpeed                    = 0x00,
    kAVCRecSpeed32                          = 0x20, 
    kAVCRecSpeedStandard                    = 0x6f,
    kAVCRecSpeedHighSpeed                   = 0xfe,
    kAVCRecSpeedDummyOperand                = 0x7f,

    kAVCEditPresetOpcode                    = 0x45,
    kAVCEditPreRollAndStandby               = 0x00,
    kAVCEditVideoInsert                     = 0x21,
    kAVCEditAudioInsert                     = 0x22,
    kAVCEditAVInsert                        = 0x23,
    kAVCEditSubcodeInsert                   = 0x24,
    kAVCEditSyncRecord                      = 0x25,
    kAVCEditSyncPlay                        = 0x35,
    kAVCEditOtherMode                       = 0x60,
    kAVCEditInPoint                         = 0x00,
    kAVCEditOutPoint                        = 0x01,
    kAVCEditPreRollTime                     = 0x02,
    kAVCEditDummyOperand                    = 0xff,

    kAVCPositionDummyOperand                = 0xff,

    kAVCPositionTimeCodeOpcode              = 0x51,
    kAVCPositionValueInquiry                = 0x71,

    kAVCMechaModeInquiryOpcode              = 0xd0,
    kAVCMechaModeDummyOperand               = 0x7f

};

typedef struct AVCCTSFrameStruct {
        UInt8           cmdType_respCode;     // cmd type/resp onse code
        UInt8           headerAddress;
        UInt8           opcode;
        UInt8           operand[5];
} AVCCTSFrameStruct, *AVCCTSFrameStructPtr;

// for sending AVC commands
typedef struct AVCTransactionParamsStruct {
	Ptr						commandBufferPtr;
	UInt32					commandLength;
	Ptr						responseBufferPtr;
	UInt32					responseBufferSize;
	void *		responseHandler;	// Obsolete
} AVCTransactionParams, *AVCTransactionParamsPtr;

///////////////////////////////////////////////////////////////////////
//
// DV Event Notification
//

typedef struct OpaqueRef	*DVNotificationID;

typedef struct DVEventHeaderStruct {
	DVDeviceID			deviceID;			// who it's from
	DVNotificationID	notifID;
	UInt32				theEvent;			// what the event was
} DVEventHeader, *DVEventHeaderPtr;

typedef struct DVEventRecordStruct {		// generalized form
	DVEventHeader		eventHeader;
	UInt8				eventData[kEventSpecificDataSize];
} DVEventRecord, *DVEventRecordPtr;

typedef struct DVConnectionEventStruct {
	DVEventHeader		eventHeader;
} DVConnectionEvent, *DVConnectionEventPtr;

typedef struct DVIsochCompleteEventStruct {
	DVEventHeader		eventHeader;
	Ptr					pFrameBuffer;
	unsigned long		bufferSize;
	UInt32				fwCycleTime;
} DVIsochCompleteEvent, *DVIsochCompleteEventPtr;

typedef struct DVAVTransactionCompleteEventStruct {
	DVEventHeader			eventHeader;
	Ptr						commandBufferPtr;
	UInt32					commandLength;
	Ptr						responseBufferPtr;
	UInt32					responseBufferSize;
} DVAVCTransactionCompleteEvent, *DVAVCTransactionCompleteEventPtr;

// DV notification proc
typedef OSStatus (*DVNotifyProc)(DVEventRecordPtr event, void *userData );
								
///////////////////////////////////////////////////////////////////////
//
// external prototypes
//
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//
// general device management
//
UInt32 DVCountDevices( void );
OSErr DVGetIndDevice( DVDeviceID * pDVDevice, UInt32 index );

OSErr DVSetDeviceName( DVDeviceID deviceID, char * str );
OSErr DVGetDeviceName( DVDeviceID deviceID, char * str );

OSErr DVOpenDriver( DVDeviceID deviceID, DVDeviceRefNum *pRefNum );
OSErr DVCloseDriver( DVDeviceRefNum refNum );

//OSErr DVGetDeviceInfo( DVDeviceID deviceID, DVDeviceInfoPtr pInfo );
//OSErr DVGetDeviceClock( DVDeviceID deviceID, Component *clock );

///////////////////////////////////////////////////////////////////////
//
// DV event notification
//
// kEveryDVDeviceRefNum can be used as a wild card refNum, for notifications about all
// devices - especially handy when there aren't any yet!
//
OSErr DVNewNotification( DVDeviceRefNum refNum, DVNotifyProc notifyProc,
						void *userData, DVNotificationID *pNotifyID );
	
OSErr DVNotifyMeWhen( DVDeviceRefNum refNum, DVNotificationID notifyID, UInt32 events);
OSErr DVCancelNotification( DVDeviceRefNum refNum, DVNotificationID notifyID );
OSErr DVDisposeNotification( DVDeviceRefNum refNum, DVNotificationID notifyID );

///////////////////////////////////////////////////////////////////////
//
// DV Isoch Read
//
OSErr DVEnableRead( DVDeviceRefNum refNum );
OSErr DVDisableRead( DVDeviceRefNum refNum );
OSErr DVReadFrame( DVDeviceRefNum refNum, Ptr *ppReadBuffer, UInt32 * pSize );
OSErr DVReleaseFrame( DVDeviceRefNum refNum, Ptr pReadBuffer );

///////////////////////////////////////////////////////////////////////
//
// DV Isoch Write
//
OSErr DVEnableWrite( DVDeviceRefNum refNum );
OSErr DVDisableWrite( DVDeviceRefNum refNum );
OSErr DVGetEmptyFrame( DVDeviceRefNum refNum, Ptr *ppEmptyFrameBuffer, UInt32 * pSize );
OSErr DVWriteFrame( DVDeviceRefNum refNum, Ptr pWriteBuffer );
OSErr DVSetWriteSignalMode( DVDeviceRefNum refNum, UInt8 mode);

///////////////////////////////////////////////////////////////////////
//
// AVC transactions
//
OSErr DVDoAVCTransaction( DVDeviceRefNum refNum, AVCTransactionParamsPtr pParams );

OSErr DVIsEnabled( DVDeviceRefNum refNum, Boolean *isEnabled);
OSErr DVGetDeviceStandard( DVDeviceRefNum refNum, UInt32 * pStandard );




#ifdef __cplusplus
}
#endif

#endif __DVFAMILY__


