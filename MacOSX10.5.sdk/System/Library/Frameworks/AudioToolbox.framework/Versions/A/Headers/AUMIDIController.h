/*=============================================================================
	AUMIDIController.h
	
	Copyright (c) 2002 Apple Computer, Inc.  All Rights Reserved
=============================================================================*/


#ifndef __AUMIDIController_h__
#define __AUMIDIController_h__

#if !__LP64__
// This API set is not available for 64-bit

#include <AudioUnit/AudioUnit.h>
#include <CoreMIDI/CoreMIDI.h>
#include <AudioToolbox/AudioUnitUtilities.h>

typedef struct OpaqueAUMIDIController *AUMIDIControllerRef;


#ifdef __cplusplus
extern "C" {
#endif


/*
	inVirtualDestinationName is null to create no virtual destination
*/
extern OSStatus
AUMIDIControllerCreate(			CFStringRef				inVirtualDestinationName,
								AUMIDIControllerRef *	outController)				
	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

extern OSStatus
AUMIDIControllerDispose(		AUMIDIControllerRef		inController)			
	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

extern OSStatus
AUMIDIControllerMapChannelToAU(	AUMIDIControllerRef		inController,
								SInt32					inSourceMIDIChannel,
								AudioUnit				inAudioUnit,
								SInt32					inDestMIDIChannel,
								Boolean					inCreateDefaultControlMappings)
	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


extern OSStatus
AUMIDIControllerMapEventToParameter(	AUMIDIControllerRef		inController,
										UInt8					inMIDIStatusByte,
										UInt16					inMIDIControl,
										const AudioUnitParameter *inParameter)	
	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

// this will remove any mapping held by this controller
// to the specified audio unit - whether those are:
// (1) default mappings (AUMIDIControllerMapChannelToAU) 
// (2) custom mappings (AUMIDIControllerMapEventToParameter)

// Typically, this is done when (and should be done) when an AU no longer
// should receive MIDI events for its parameters (or the AU is being disposed)
extern OSStatus
AUMIDIControllerUnmapAudioUnit(		AUMIDIControllerRef		inController,
									AudioUnit				inAudioUnit)		
	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
										
/*
	$$$ need description of timestamps in the packets (if any) are treated -- needs
	to factor in the AU's latency $$$
*/
extern OSStatus
AUMIDIControllerHandleMIDI(			AUMIDIControllerRef		inController,
									const MIDIPacketList *	inMIDIPacketList)	
	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


extern OSStatus
AUMIDIControllerConnectSource(		AUMIDIControllerRef		inController,
									MIDIEndpointRef			inSource)			
	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

extern OSStatus
AUMIDIControllerDisconnectSource(	AUMIDIControllerRef		inController,
									MIDIEndpointRef			inSource)			
	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

/*
	Tells an AUMIDIController to generate an XML description of the control/NRPN 
	mapping.  Returns a (local file) URL to the file written.  $$$ If the AUMIDIController
	has a virtual destination associated with it, the AUMIDIController will
	call MIDIObjectSetNameConfiguration to publish those names as the current
	ones for that destination.
*/
extern OSStatus
AUMIDIControllerExportXMLNames(		AUMIDIControllerRef		inController,
									CFURLRef *				outXMLFileURL)		
	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


#ifdef __cplusplus
}
#endif

#endif // !__LP64__

#endif // __AUMIDIController_h__

