/*
     File:       CoreAudio/AudioHardwarePlugIn.h

     Contains:   API for the CFPlugIn that implements an audio driver for the HAL
                 from user space.

     Version:    Technology: Mac OS X
                 Release:    Mac OS X

     Copyright:  (c) 1985-2003 by Apple Computer, Inc., all rights reserved.

     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:

                     http://developer.apple.com/bugreporter/

*/
#if !defined(__AudioHardwarePlugIn_h__)
#define __AudioHardwarePlugIn_h__

//=============================================================================
//	Includes
//=============================================================================

#include <AvailabilityMacros.h>
#include <CoreAudio/AudioHardware.h>
#include <CoreFoundation/CFPlugIn.h>
#if COREFOUNDATION_CFPLUGINCOM_SEPARATE
	#include <CoreFoundation/CFPlugInCOM.h>
#endif
#include <CoreFoundation/CFRunLoop.h>

#if PRAGMA_ENUM_ALWAYSINT
	#pragma enumsalwaysint off
#endif

#if defined(__cplusplus)
extern "C"
{
#endif

//=============================================================================
//	Types
//=============================================================================

typedef struct AudioHardwarePlugInInterface	AudioHardwarePlugInInterface;
typedef AudioHardwarePlugInInterface**		AudioHardwarePlugInRef;

//=============================================================================
//	Constants
//=============================================================================

#define kAudioHardwarePlugInTypeID \
	CFUUIDGetConstantUUIDWithBytes(NULL, 0xF8, 0xBB, 0x1C, 0x28, 0xBA, 0xE8, 0x11, 0xD6, 0x9C, 0x31, 0x00, 0x03, 0x93, 0x15, 0xCD, 0x46)
/* F8BB1C28-BAE8-11D6-9C31-00039315CD46 */

#define kAudioHardwarePlugInInterfaceID \
	CFUUIDGetConstantUUIDWithBytes(NULL, 0xFA, 0xFC, 0xAF, 0xC3, 0xBA, 0xE8, 0x11, 0xD6, 0xB4, 0xA8, 0x00, 0x03, 0x93, 0x15, 0xCD, 0x46)
/* FAFCAFC3-BAE8-11D6-B4A8-00039315CD46 */

#define kAudioHardwarePlugInInterface2ID \
	CFUUIDGetConstantUUIDWithBytes(NULL, 0x5D, 0x80, 0xCB, 0x6C, 0x48, 0x4F, 0x11, 0xD7, 0x85, 0x71, 0x00, 0x0A, 0x95, 0x77, 0x12, 0x82)
/* 5D80CB6C-484F-11D7-8571-000A95771282 */

//=============================================================================
//	AudioHardwarePlugInInterface
//
//	This is the CFPlugIn interface presented by a HAL plug-in. The HAL will
//	create only one instance of each interface. This instance is responsible
//	for providing all required services on behalf of as many devices of the
//	kind it implements.
//
//	The Initialize method is called to allow the plug-in to set itself up.
//	At this time any devices of it's kind and their streams can be presented
//	to the system using AudioHardwareDevicesCreated and AudioHardwareStreamsCreated.
//	The plug-in is also responsible for managing it's own notifications, and
//	may install any CFRunLoopSources it needs using AudioHardwaerAddRunLoopSource
//	at this time as well.
//
//	Teardown is called when the HAL is unloading itself and the plug-in should
//	dispose of any devices and streams it has created using AudioHardwareDevicesDied
//	and AudioHardareStreamsDied.
//
//	The rest of the methods in this interface correspond to the semantics
//	of their similarly named counterparts in <CoreAudio/AudioHardware.h>.
//	The HAL basically passes these calls directly to the plug-in in this fashion.
//
//	Plug-ins do not have to manage device or stream property listener procs. Instead,
//	a plug-in can call AudioHardwareDevicePropertyChanged or AudioHardwareStreamPropertyChanged
//	and the HAL will take care of calling all the appropriate listeners.
//=============================================================================

struct	AudioHardwarePlugInInterface
{

//	IUnknown stuff
	IUNKNOWN_C_GUTS;

//	Construction/Destruction
	OSStatus	(*Initialize)(AudioHardwarePlugInRef inSelf);
	OSStatus	(*Teardown)(AudioHardwarePlugInRef inSelf);

//	IO Management
	OSStatus	(*DeviceAddIOProc)(AudioHardwarePlugInRef inSelf, AudioDeviceID inDevice, AudioDeviceIOProc inProc, void* inClientData);
	OSStatus	(*DeviceRemoveIOProc)(AudioHardwarePlugInRef inSelf, AudioDeviceID inDevice, AudioDeviceIOProc inProc);
	OSStatus	(*DeviceStart)(AudioHardwarePlugInRef inSelf, AudioDeviceID inDevice, AudioDeviceIOProc inProc);
	OSStatus	(*DeviceStop)(AudioHardwarePlugInRef inSelf, AudioDeviceID inDevice, AudioDeviceIOProc inProc);
	OSStatus	(*DeviceRead)(AudioHardwarePlugInRef inSelf, AudioDeviceID inDevice, const AudioTimeStamp* inStartTime, AudioBufferList* outData);

//	Time Management
	OSStatus	(*DeviceGetCurrentTime)(AudioHardwarePlugInRef inSelf, AudioDeviceID inDevice, AudioTimeStamp* outTime);
	OSStatus	(*DeviceTranslateTime)(AudioHardwarePlugInRef inSelf, AudioDeviceID inDevice, const AudioTimeStamp* inTime, AudioTimeStamp* outTime);

//	Device Property Management
	OSStatus	(*DeviceGetPropertyInfo)(AudioHardwarePlugInRef inSelf, AudioDeviceID inDevice, UInt32 inChannel, Boolean isInput, AudioDevicePropertyID inPropertyID, UInt32* outSize, Boolean* outWritable);
	OSStatus	(*DeviceGetProperty)(AudioHardwarePlugInRef inSelf, AudioDeviceID inDevice, UInt32 inChannel, Boolean isInput, AudioDevicePropertyID inPropertyID, UInt32* ioPropertyDataSize, void* outPropertyData);
	OSStatus	(*DeviceSetProperty)(AudioHardwarePlugInRef inSelf, AudioDeviceID inDevice, const AudioTimeStamp* inWhen, UInt32 inChannel, Boolean isInput, AudioDevicePropertyID inPropertyID, UInt32 inPropertyDataSize, const void* inPropertyData);

//	Stream Property Management
	OSStatus	(*StreamGetPropertyInfo)(AudioHardwarePlugInRef inSelf, AudioStreamID inStream, UInt32 inChannel, AudioDevicePropertyID inPropertyID, UInt32* outSize, Boolean* outWritable);
	OSStatus	(*StreamGetProperty)(AudioHardwarePlugInRef inSelf, AudioStreamID inStream, UInt32 inChannel, AudioDevicePropertyID inPropertyID, UInt32* ioPropertyDataSize, void* outPropertyData);
	OSStatus	(*StreamSetProperty)(AudioHardwarePlugInRef inSelf, AudioStreamID inStream, const AudioTimeStamp* inWhen, UInt32 inChannel, AudioDevicePropertyID inPropertyID, UInt32 inPropertyDataSize, const void* inPropertyData);

//	Version 2 Methods
	OSStatus	(*DeviceStartAtTime)(AudioHardwarePlugInRef inSelf, AudioDeviceID inDevice, AudioDeviceIOProc inProc, AudioTimeStamp* ioRequestedStartTime, UInt32 inFlags);
	OSStatus	(*DeviceGetNearestStartTime)(AudioHardwarePlugInRef inSelf, AudioDeviceID inDevice, AudioTimeStamp* ioRequestedStartTime, UInt32 inFlags);

};

enum
{
	kAudioHardwarePropertyProcessIsMaster					= 'mast'
		//	A UInt32 where 1 means this process contains the master
		//	instance of the HAL. The master instance of the HAL is
		//	the only instance in which the plug-ins should restore their
		//	device's settings when the device is first presented to
		//	the system. 
};

//=============================================================================
//	Plug-In Support Routines
//	
//	These are routines that plug-ins have to call in order to interface
//	with the HAL properly.
//=============================================================================

extern OSStatus
AudioHardwareAddRunLoopSource(CFRunLoopSourceRef inRunLoopSource)											AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern OSStatus
AudioHardwareRemoveRunLoopSource(CFRunLoopSourceRef inRunLoopSource)										AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern OSStatus
AudioHardwareClaimAudioDeviceID(AudioHardwarePlugInRef inOwner, AudioDeviceID* outAudioDeviceID)			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern OSStatus
AudioHardwareDevicesCreated(	AudioHardwarePlugInRef  inOwner,
								UInt32					inNumberDevices,
								const AudioDeviceID*	inAudioDeviceIDs)									AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern OSStatus
AudioHardwareDevicesDied(   AudioHardwarePlugInRef  inOwner,
							UInt32					inNumberDevices,
							const AudioDeviceID*	inAudioDeviceIDs)										AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern OSStatus
AudioHardwareDevicePropertyChanged( AudioHardwarePlugInRef  inOwner,
									AudioDeviceID			inDeviceID,
									UInt32					inChannel,
									Boolean					isInput,
									AudioDevicePropertyID   inPropertyID)									AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern OSStatus
AudioHardwareClaimAudioStreamID(	AudioHardwarePlugInRef  inOwner,
									AudioDeviceID			inOwningDeviceID,
									AudioStreamID*			outAudioStreamID)								AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern OSStatus
AudioHardwareStreamsCreated(	AudioHardwarePlugInRef  inOwner,
								AudioDeviceID			inOwningDeviceID,
								UInt32					inNumberStreams,
								const AudioStreamID*	inAudioStreamIDs)									AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern OSStatus
AudioHardwareStreamsDied(   AudioHardwarePlugInRef  inOwner,
							AudioDeviceID			inOwningDeviceID,
							UInt32					inNumberStreams,
							const AudioStreamID*	inAudioStreamIDs)										AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern OSStatus
AudioHardwareStreamPropertyChanged( AudioHardwarePlugInRef  inOwner,
									AudioDeviceID			inOwningDeviceID,
									AudioStreamID			inStreamID,
									UInt32					inChannel,
									AudioDevicePropertyID   inPropertyID)									AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

#if defined(__cplusplus)
}
#endif

#if PRAGMA_ENUM_ALWAYSINT
	#pragma enumsalwaysint reset
#endif

#endif
