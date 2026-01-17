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

#ifndef _IOKIT_IOAUDIOTYPES_H
#define _IOKIT_IOAUDIOTYPES_H

#include <libkern/OSTypes.h>
#include <mach/message.h>
#include <device/device_types.h>
/*!
 * @enum IOAudioEngineMemory
 * @abstract Used to identify the type of memory requested by a client process to be mapped into its process space
 * @discussion This is the parameter to the type field of IOMapMemory when called on an IOAudioEngine.  This is
 *  only intended for use by the Audio Device API library.
 * @constant kSampleBuffer This requests the IOAudioEngine's sample buffer
 * @constant kStatus This requests the IOAudioEngine's status buffer.  It's type is IOAudioEngineStatus.
 * @constant kMixBuffer This requests the IOAudioEngine's mix buffer
*/
typedef enum _IOAudioEngineMemory {
    kStatusBuffer 	= 0,
    kSampleBuffer	= 1,
    kMixBuffer		= 2
} IOAudioEngineMemory;

/*!
 * @enum IOAudioEngineCalls
 * @abstract The set of constants passed to IOAudioEngineUserClient::getExternalMethodForIndex() when making calls
 *  from the IOAudioFamily user client code.
 */
typedef enum _IOAudioEngineCalls {
    kIOAudioEngineCallRegisterClientBuffer		= 0,
    kIOAudioEngineCallUnregisterClientBuffer	= 1,
    kIOAudioEngineCallGetConnectionID			= 2,
    kIOAudioEngineCallStart						= 3,
    kIOAudioEngineCallStop						= 4
} IOAudioEngineCalls;

/*! @defined kIOAudioEngineNumCalls The number of elements in the IOAudioEngineCalls enum. */
#define kIOAudioEngineNumCalls		5

typedef enum _IOAudioEngineTraps {
    kIOAudioEngineTrapPerformClientIO = 0
} IOAudioEngineTraps;

typedef enum _IOAudioEngineNotifications {
    kIOAudioEngineAllNotifications 					= 0,
    kIOAudioEngineStreamFormatChangeNotification	= 1,
    kIOAudioEngineChangeNotification 				= 2,
    kIOAudioEngineStartedNotification 				= 3,
    kIOAudioEngineStoppedNotification 				= 4,
    kIOAudioEnginePausedNotification				= 5,
    kIOAudioEngineResumedNotification				= 6
} IOAudioEngineNotifications;

/*!
 * @enum IOAudioEngineState
 * @abstract Represents the state of an IOAudioEngine
 * @constant kIOAudioEngineRunning The IOAudioEngine is currently running - it is transferring data to or 
 *           from the device.
 * @constant kIOAudioEngineStopped The IOAudioEngine is currently stopped - no activity is occurring.
 */

typedef enum _IOAudioEngineState {
    kIOAudioEngineStopped	= 0,
    kIOAudioEngineRunning	= 1,
    kIOAudioEnginePaused	= 2,
    kIOAudioEngineResumed	= 3
} IOAudioEngineState;


/*!
 * @typedef IOAudioEngineStatus
 * @abstract Shared-memory structure giving audio engine status
 * @discussion
 * @field fVersion Indicates version of this structure
 * @field fCurrentLoopCount Number of times around the ring buffer since the audio engine started
 * @field fLastLoopTime Timestamp of the last time the ring buffer wrapped
 * @field fEraseHeadSampleFrame Location of the erase head in sample frames - erased up to but not
 *        including the given sample frame
 */

typedef struct _IOAudioEngineStatus {
    UInt32					fVersion;
    volatile UInt32			fCurrentLoopCount;
    volatile AbsoluteTime	fLastLoopTime;
    volatile UInt32			fEraseHeadSampleFrame;
} IOAudioEngineStatus;

#define kIOAudioEngineCurrentStatusStructVersion		2

typedef struct _IOAudioStreamFormat {
    UInt32	fNumChannels;
    UInt32	fSampleFormat;
    UInt32	fNumericRepresentation;
    UInt8	fBitDepth;
    UInt8	fBitWidth;
    UInt8	fAlignment;
    UInt8	fByteOrder;
    UInt8	fIsMixable;
    UInt32	fDriverTag;
} IOAudioStreamFormat;

/*!
* @enum IOAudioStreamDirection
 * @abstract Represents the direction of an IOAudioStream
 * @constant kAudioOutput Output buffer
 * @constant kAudioInput Input buffer
 */

typedef enum _IOAudioStreamDirection {
    kIOAudioStreamDirectionOutput	= 0,
    kIOAudioStreamDirectionInput	= 1
} IOAudioStreamDirection;


/*!
 * @defined kIOAudioEngineDefaultMixBufferSampleSize
 */

#define kIOAudioEngineDefaultMixBufferSampleSize		sizeof(float)

/* The following are for use only by the IOKit.framework audio family code */

/*!
 * @enum IOAudioControlCalls
 * @abstract The set of constants passed to IOAudioControlUserClient::getExternalMethodForIndex() when making calls
 *  from the IOAudioFamily user client code.
 * @constant kIOAudioControlCallSetValue Used to set the value of an IOAudioControl.
 * @constant kIOAudioControlCallGetValue Used to get the value of an IOAudioControl.
 */
typedef enum _IOAudioControlCalls {
    kIOAudioControlCallSetValue = 0,
    kIOAudioControlCallGetValue = 1
} IOAudioControlCalls;

/*! @defined kIOAudioControlNumCalls The number of elements in the IOAudioControlCalls enum. */
#define kIOAudioControlNumCalls 	2

/*!
 * @enum IOAudioControlNotifications
 * @abstract The set of constants passed in the type field of IOAudioControlUserClient::registerNotificaitonPort().
 * @constant kIOAudioControlValueChangeNotification Used to request value change notifications.
 */
typedef enum _IOAudioControlNotifications {
    kIOAudioControlValueChangeNotification = 0
} IOAudioControlNotifications;

/*!
 * @struct IOAudioNotificationMessage
 * @abstract Used in the mach message for IOAudio notifications.
 * @field messageHeader Standard mach message header
 * @field ref The param passed to registerNotificationPort() in refCon.
 */
typedef struct _IOAudioNotificationMessage {
    mach_msg_header_t	messageHeader;
    UInt32		type;
    UInt32		ref;
    void *		sender;
} IOAudioNotificationMessage;

typedef struct _IOAudioSampleRate {
    UInt32	whole;
    UInt32	fraction;
} IOAudioSampleRate;


enum {
    kIOAudioPortTypeOutput		= 'outp',
    kIOAudioPortTypeInput		= 'inpt',
    kIOAudioPortTypeMixer		= 'mixr',
    kIOAudioPortTypePassThru	= 'pass',
    kIOAudioPortTypeProcessing	= 'proc'
};

enum {
    kIOAudioOutputPortSubTypeInternalSpeaker	= 'ispk',
    kIOAudioOutputPortSubTypeExternalSpeaker	= 'espk',
    kIOAudioOutputPortSubTypeHeadphones			= 'hdpn',
    kIOAudioOutputPortSubTypeLine				= 'line',
    kIOAudioOutputPortSubTypeSPDIF				= 'spdf',
    
    kIOAudioInputPortSubTypeInternalMicrophone	= 'imic',
    kIOAudioInputPortSubTypeExternalMicrophone	= 'emic',
    kIOAudioInputPortSubTypeCD					= 'cd  ',
    kIOAudioInputPortSubTypeLine				= 'line',
    kIOAudioInputPortSubTypeSPDIF				= 'spdf'
};

enum {
    kIOAudioControlTypeLevel			= 'levl',
    kIOAudioControlTypeToggle			= 'togl',
    kIOAudioControlTypeSelector			= 'slct'
};

enum {
    kIOAudioLevelControlSubTypeVolume			= 'vlme',

    kIOAudioToggleControlSubTypeMute			= 'mute',

    kIOAudioSelectorControlSubTypeOutput		= 'outp',
    kIOAudioSelectorControlSubTypeInput			= 'inpt',
    kIOAudioSelectorControlSubTypeClockSource	= 'clck'
};

enum {
    kIOAudioControlUsageOutput				= 'outp',
    kIOAudioControlUsageInput				= 'inpt',
    kIOAudioControlUsagePassThru			= 'pass',
    kIOAudioControlUsageCoreAudioProperty	= 'prop'
};

enum {
    kIOAudioControlChannelNumberInactive		= -1,
    kIOAudioControlChannelIDAll					= 0,
    kIOAudioControlChannelIDDefaultLeft			= 1,
    kIOAudioControlChannelIDDefaultRight		= 2,
    kIOAudioControlChannelIDDefaultCenter		= 3,
    kIOAudioControlChannelIDDefaultLeftRear		= 4,
    kIOAudioControlChannelIDDefaultRightRear	= 5,
    kIOAudioControlChannelIDDefaultSub			= 6
};

enum {
    kIOAudioSelectorControlSelectionValueNone				= 'none',
    
    // Output-specific selection IDs 
    kIOAudioSelectorControlSelectionValueInternalSpeaker	= 'ispk',
    kIOAudioSelectorControlSelectionValueExternalSpeaker	= 'espk',
    kIOAudioSelectorControlSelectionValueHeadphones			= 'hdpn',
    
    // Input-specific selection IDs
    kIOAudioSelectorControlSelectionValueInternalMicrophone	= 'imic',
    kIOAudioSelectorControlSelectionValueExternalMicrophone	= 'emic',
    kIOAudioSelectorControlSelectionValueCD					= 'cd  ',
    
    // Common selection IDs
    kIOAudioSelectorControlSelectionValueLine				= 'line',
    kIOAudioSelectorControlSelectionValueSPDIF				= 'spdf'
};

enum {
    kIOAudioStreamSampleFormatLinearPCM		= 'lpcm'
};

enum {
    kIOAudioStreamNumericRepresentationSignedInt	= 'sint',
    kIOAudioStreamNumericRepresentationUnsignedInt	= 'uint'
// Need float format(s) here
};

enum {
    kIOAudioStreamAlignmentLowByte		= 0,
    kIOAudioStreamAlignmentHighByte		= 1
};

enum {
    kIOAudioStreamByteOrderBigEndian		= 0,
    kIOAudioStreamByteOrderLittleEndian		= 1
};

enum {
    kIOAudioLevelControlNegativeInfinity	= 0xffffffff
};

#endif /* _IOKIT_IOAUDIOTYPES_H */
