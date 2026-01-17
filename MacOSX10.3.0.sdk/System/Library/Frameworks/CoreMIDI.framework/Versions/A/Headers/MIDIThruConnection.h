/*
 	File:   	CoreMIDI/MIDIThruConnection.h
 
 	Contains:   Routines for creating MIDI play-through connections.
 
 	Version:	Technology: Mac OS X
 				Release:	Mac OS X
 
 	Copyright:  (c) 2002 by Apple Computer, Inc., all rights reserved.
 
 	Bugs?:  	For bug reports, consult the following page on
 				the World Wide Web:
 
 					http://developer.apple.com/bugreporter/
 
*/

#ifndef __MIDIThruConnection_h__
#define __MIDIThruConnection_h__

#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>	// for basic types
#include <CoreMIDI/MIDIServices.h>

//  -----------------------------------------------------------------------------
/*!
	@header MIDIThruConnection

	This header defines functions to create MIDI play-through connections
	between the MIDI sources and destinations.  These connections may be
	persistent or transitory, owned by a client.
	
	By using connections instead of doing MIDI Thru operations themselves,
	the overhead of moving MIDI messages between the server and the client
	for thru-ing is reduced.
	
	The aim of these functions is to permit as flexible a set of transformations 
	as possible while keeping the API and data structures relatively simple.	
*/
//  -----------------------------------------------------------------------------

/*!
	@typedef		MIDIThruConnectionRef
	
	@discussion		An opaque reference to a play-through connection.
*/
typedef struct OpaqueMIDIThruConnection *		MIDIThruConnectionRef;

/*!
	@typedef		MIDIValueMap
	
	@discussion		A custom mapping function to transform MIDI 7-bit values,
					as contained in note numbers, velocities, control values,
					etc.  y = value[x], where x is the input MIDI value, y the
					output.
*/
struct MIDIValueMap {
	UInt8			value[128];
};
typedef struct MIDIValueMap MIDIValueMap;

enum {
	kMIDITransform_None = 0,		// no param
	kMIDITransform_FilterOut = 1,	// filter out event type, no param
	kMIDITransform_MapControl = 2,	// param is remapped control number
	kMIDITransform_Add = 8,			// param is value to add
	kMIDITransform_Scale = 9,		// param is amount to scale by: fixed point bbbb.bbbb bbbb bbbb
	kMIDITransform_MinValue = 10,
	kMIDITransform_MaxValue = 11,
	kMIDITransform_MapValue = 12	// param is index of map in connection's map array
};

enum {
	kMIDIThruConnection_MaxEndpoints = 8
};

// control types
// (implementation note: some code tests bits of these values)
enum {
	kMIDIControlType_7Bit = 0,		// control numbers may be 0-127
	kMIDIControlType_14Bit = 1,		// control numbers may be 0-31
	kMIDIControlType_7BitRPN = 2,	// control numbers may be 0-16383
	kMIDIControlType_14BitRPN = 3,
	kMIDIControlType_7BitNRPN = 4,
	kMIDIControlType_14BitNRPN = 5
};

struct MIDITransform {
	UInt16				transform;
	SInt16				param;
};
typedef struct MIDITransform MIDITransform;

// Note: must order control transforms appropriately -- first, filter out and remap.
// Further transforms can follow, and will apply to the remapped control number (if any).
// N.B. All transformations are done using 14-bit control values, so, when doing an add/min/max
// transform on a 7-bit value, the parameter must be a 14-bit value, e.g. to add n, param
// must be n << 7.
struct MIDIControlTransform {
	UInt8				controlType;
	UInt8				remappedControlType;	// only used when transform is kMIDITransform_MapControl
	UInt16				controlNumber;
	UInt16				transform;
	SInt16				param;
};
typedef struct MIDIControlTransform MIDIControlTransform;

// When filling one of these out, clients can leave uniqueID 0 if the endpoint exists.
// When when one is provided back to the client, the endpoint may be null if it doesn't
// exist, but the uniqueID will always be non-zero.
struct MIDIThruConnectionEndpoint {
	MIDIEndpointRef			endpointRef;
	MIDIUniqueID			uniqueID;
};
typedef struct MIDIThruConnectionEndpoint MIDIThruConnectionEndpoint;

struct MIDIThruConnectionParams {
	UInt32						version;			// must be 0
	UInt32						numSources;
	MIDIThruConnectionEndpoint	sources[kMIDIThruConnection_MaxEndpoints];
	UInt32						numDestinations;
	MIDIThruConnectionEndpoint	destinations[kMIDIThruConnection_MaxEndpoints];
	
	// map each of the source 16 MIDI channels to channel 0-15 (1-16) or 0xFF to filter out
	UInt8					channelMap[16];
	
	UInt8					reserved1[2];		// must be 0
	UInt8					lowNote, highNote;	// ignored if mapping
												// if highNote < lowNote, then 0..highNote and lowNote..127
												// are passed
	MIDITransform			noteNumber;
	MIDITransform			velocity;
	MIDITransform			keyPressure;
	MIDITransform			channelPressure;
	MIDITransform			programChange;
	MIDITransform			pitchBend;
	
	UInt8					filterOutSysEx;
	UInt8					filterOutMTC;
	UInt8					filterOutBeatClock;
	UInt8					filterOutTuneRequest;
	UInt8					reserved2[3];		// must be 0
	UInt8					filterOutAllControls;
	
	UInt16					numControlTransforms;
	UInt16					numMaps;
	UInt16					reserved3[4];		// must be 0

	// remainder of structure is variable-length:
	//		MIDIControlTransform	controls[];
	//		MIDIValueMap			maps[];
};
typedef struct MIDIThruConnectionParams MIDIThruConnectionParams;

#ifdef __cplusplus
extern "C" {
#endif

// Convenience function to fill the connection structure with default values:
// no endpoints, no transformations (mostly zeroes except for the channel map).
// Then just filling in the source and adding one destination will create a simple, 
// unmodified thru connection.
extern void
MIDIThruConnectionParamsInitialize(
							MIDIThruConnectionParams *		inConnectionParams );

// if inPersistentOwnerID is null, then the connection is marked as owned by the client
// and will be automatically disposed with the client.  if it is non-null, then it
// should be a unique identifier, e.g. "com.mycompany.MyCoolProgram".
extern OSStatus
MIDIThruConnectionCreate(	CFStringRef						inPersistentOwnerID,
							CFDataRef						inConnectionParams,
							MIDIThruConnectionRef *			outConnection );

extern OSStatus
MIDIThruConnectionDispose(	MIDIThruConnectionRef			connection );

// The returned CFDataRef contains a MIDIThruConnectionParams structure; client is responsible
// for releasing it.
extern OSStatus
MIDIThruConnectionGetParams(MIDIThruConnectionRef			connection,
							CFDataRef *						outConnectionParams );

// The supplied CFDataRef contains a MIDIThruConnectionParams structure; reference is not consumed.
extern OSStatus
MIDIThruConnectionSetParams(MIDIThruConnectionRef			connection,
							CFDataRef						inConnectionParams );

// the returned CFDataRef is an array of MIDIThruConnectionRef's containing all of the 
// connections created by the specified owner.
extern OSStatus
MIDIThruConnectionFind(		CFStringRef						inPersistentOwnerID,
							CFDataRef *						outConnectionList );

#ifdef __cplusplus
}
#endif

#endif /* __MIDIThruConnection_h__ */
