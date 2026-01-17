/*=============================================================================
	AUMIDIController.h
	
	Copyright (c) 2002 Apple Computer, Inc.  All Rights Reserved
=============================================================================*/


#ifndef __AUMIDIController_h__
#define __AUMIDIController_h__

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
								AUMIDIControllerRef *	outController);

extern OSStatus
AUMIDIControllerDispose(		AUMIDIControllerRef		inController);

extern OSStatus
AUMIDIControllerMapChannelToAU(	AUMIDIControllerRef		inController,
								SInt32					inSourceMIDIChannel,
								AudioUnit				inAudioUnit,
								SInt32					inDestMIDIChannel,
								Boolean					inCreateDefaultControlMappings);


extern OSStatus
AUMIDIControllerMapEventToParameter(	AUMIDIControllerRef		inController,
										UInt8					inMIDIStatusByte,
										UInt16					inMIDIControl,
										const AudioUnitParameter *inParameter);

// this will remove any mapping held by this controller
// to the specified audio unit - whether those are:
// (1) default mappings (AUMIDIControllerMapChannelToAU) 
// (2) custom mappings (AUMIDIControllerMapEventToParameter)

// Typically, this is done when (and should be done) when an AU no longer
// should receive MIDI events for its parameters (or the AU is being disposed)
extern OSStatus
AUMIDIControllerUnmapAudioUnit(	AUMIDIControllerRef		inController,
								AudioUnit				inAudioUnit);
										
/*
	$$$ need description of timestamps in the packets (if any) are treated -- needs
	to factor in the AU's latency $$$
*/
extern OSStatus
AUMIDIControllerHandleMIDI(		AUMIDIControllerRef		inController,
								const MIDIPacketList *	inMIDIPacketList);


extern OSStatus
AUMIDIControllerConnectSource(		AUMIDIControllerRef	inController,
									MIDIEndpointRef		inSource);

extern OSStatus
AUMIDIControllerDisconnectSource(	AUMIDIControllerRef	inController,
									MIDIEndpointRef		inSource);

/*
	Tells an AUMIDIController to generate an XML description of the control/NRPN 
	mapping.  Returns a (local file) URL to the file written.  $$$ If the AUMIDIController
	has a virtual destination associated with it, the AUMIDIController will
	call MIDIObjectSetNameConfiguration to publish those names as the current
	ones for that destination.
*/
extern OSStatus
AUMIDIControllerExportXMLNames(	AUMIDIControllerRef		inController,
								CFURLRef *				outXMLFileURL);


#ifdef __cplusplus
}
#endif

#endif // __AUMIDIController_h__

