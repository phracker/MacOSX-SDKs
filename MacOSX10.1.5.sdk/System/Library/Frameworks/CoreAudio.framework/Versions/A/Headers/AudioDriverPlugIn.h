/*
     File:       CoreAudio/AudioDriverPlugIn.h

     Contains:   API for the CFBundle a driver can specify for the HAL to use
                 to provide implemenation for device specific properties.

     Version:    Technology: Mac OS X
                 Release:    Mac OS X

     Copyright:  (c) 1985-2001 by Apple Computer, Inc., all rights reserved.

     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:

                     http://developer.apple.com/bugreporter/

*/
#if !defined(__AudioDriverPlugIn_h__)
#define __AudioDriverPlugIn_h__

//=============================================================================
//	Includes
//=============================================================================

#include <CoreAudio/AudioHardware.h>
#include <IOKit/IOKitLib.h>

#if defined(__cplusplus)
extern "C"
{
#endif

//=============================================================================
//	Theory of Operation
//
//	Drivers can specify a CFBundle in order to implement device specific
//	properties on behalf of the HAL. The CFBundle provides routines for
//	opening and closing the device as well as the property management
//	routines. The mechanism by which the driver specifies which CFBundle
//	to load is defined by the IOAudio driver family in IOKit. The following
//	routines are loaded by name from the CFBundle.
//=============================================================================

//=============================================================================
//	Types
//=============================================================================

//-----------------------------------------------------------------------------
//	AudioDriverPlugInDevicePropertyChangedProc
//
//	A plug-in calls this routine to notify the HAL's implementation that
//	one of it's device's properties has changed. From there, the HAL will notify
//	the client listeners. The address of the specific routine is supplied
//	to the plug-in when it is opened.
//-----------------------------------------------------------------------------

typedef OSStatus
(*AudioDriverPlugInDevicePropertyChangedProc)(	AudioDeviceID			inDevice,
												UInt32					inChannel,
												Boolean					isInput,
												AudioDevicePropertyID	inPropertyID);

//-----------------------------------------------------------------------------
//	AudioDriverPlugInDevicePropertyChangedProc
//
//	A plug-in calls this routine to notify the HAL's implementation that
//	one of it's stream's properties has changed. From there, the HAL will notify
//	the client listeners. The address of the specific routine is supplied
//	to the plug-in when it is opened.
//-----------------------------------------------------------------------------

typedef OSStatus
(*AudioDriverPlugInStreamPropertyChangedProc)(	AudioDeviceID			inDevice,
												io_object_t				inIOAudioStream,
												UInt32					inChannel,
												AudioDevicePropertyID	inPropertyID);

//-----------------------------------------------------------------------------
//	AudioDriverPlugInHostInfo
//
//	This structure provides the plug-in with all the info it needs
//	with respect to communicating with the HAL's implementation.
//-----------------------------------------------------------------------------

struct AudioDriverPlugInHostInfo
{
	AudioDeviceID								mDeviceID;
	io_object_t									mIOAudioDevice;
	io_object_t									mIOAudioEngine;
	AudioDriverPlugInDevicePropertyChangedProc	mDevicePropertyChangedProc;
	AudioDriverPlugInStreamPropertyChangedProc	mStreamPropertyChangedProc;
};
typedef struct AudioDriverPlugInHostInfo	AudioDriverPlugInHostInfo;

//=============================================================================
//	Life Cycle Management
//=============================================================================

extern OSStatus
AudioDriverPlugInOpen(AudioDriverPlugInHostInfo* inHostInfo);

extern OSStatus
AudioDriverPlugInClose(AudioDeviceID inDevice);

//=============================================================================
//	Property Management
//
//	Accessing all the properties of a device requires specific knowledge
//	of how the device works. Therefore, it is necessary to provide a
//	mechanism for the driver to implement those properties through the HAL.
//	
//	The following routines all correspond to the semantics described for
//	their companion routines in CoreAudio/AudioHardware.h.
//=============================================================================

extern OSStatus
AudioDriverPlugInDeviceGetPropertyInfo(	AudioDeviceID			inDevice,
										UInt32					inChannel,
										Boolean					isInput,
										AudioDevicePropertyID	inPropertyID,
										UInt32*					outSize,
										Boolean*				outWritable);

extern OSStatus
AudioDriverPlugInDeviceGetProperty(	AudioDeviceID			inDevice,
									UInt32					inChannel,
									Boolean					isInput,
									AudioDevicePropertyID	inPropertyID,
									UInt32*					ioPropertyDataSize,
									void*					outPropertyData);

extern OSStatus
AudioDriverPlugInDeviceSetProperty(	AudioDeviceID			inDevice,
									const AudioTimeStamp*	inWhen,
									UInt32					inChannel,
									Boolean					isInput,
									AudioDevicePropertyID	inPropertyID,
									UInt32					inPropertyDataSize,
									const void*				inPropertyData);

extern OSStatus
AudioDriverPlugInStreamGetPropertyInfo(	AudioDeviceID			inDevice,
										io_object_t				inIOAudioStream,
										UInt32					inChannel,
										AudioDevicePropertyID	inPropertyID,
										UInt32*					outSize,
										Boolean*				outWritable);

extern OSStatus
AudioDriverPlugInStreamGetProperty(	AudioDeviceID			inDevice,
									io_object_t				inIOAudioStream,
									UInt32					inChannel,
									AudioDevicePropertyID	inPropertyID,
									UInt32*					ioPropertyDataSize,
									void*					outPropertyData);

extern OSStatus
AudioDriverPlugInStreamSetProperty(	AudioDeviceID			inDevice,
									io_object_t				inIOAudioStream,
									const AudioTimeStamp*	inWhen,
									UInt32					inChannel,
									AudioDevicePropertyID	inPropertyID,
									UInt32					inPropertyDataSize,
									const void*				inPropertyData);

#if defined(__cplusplus)
}
#endif

#endif
