/*
     File:       MusicDevice.h
 
     Contains:   MusicDevice Interfaces
 
     Version:    Mac OS X
 
     Copyright:  © 2000-2004 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __MUSICDEVICE__
#define __MUSICDEVICE__

#include <AvailabilityMacros.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <CoreServices/CoreServices.h>
	#include <AudioUnit/AUComponent.h>
	#include <CoreAudio/CoreAudio.h>
#else
	#include <Components.h>
	#include <AUComponent.h>
	#include <CoreAudioTypes.h>
#endif

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_IMPORT
#pragma import on
#endif

#if !__LP64__
	#if PRAGMA_STRUCT_ALIGN
		#pragma options align=mac68k
	#elif PRAGMA_STRUCT_PACKPUSH
		#pragma pack(push, 2)
	#elif PRAGMA_STRUCT_PACK
		#pragma pack(2)
	#endif
#endif

//-----------------------------------------------------------------------------
//	A MusicDevice can control many more independent instruments than the 16
//	channels of MIDI, through the use of the extended APIs.
//	AudioUnitSetParameter is used with the kAudioUnitScope_Group to use these
//	extended control facilities. See documentation for further details.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//	MusicDevice types and structures
//-----------------------------------------------------------------------------

typedef UInt32                          MusicDeviceInstrumentID;
	/* Typically used for packing in MIDI note parameters (note number, velocity)*/

struct MusicDeviceStdNoteParams
{
	UInt32							argCount;		/* should be 2*/
	Float32							mPitch;
	Float32							mVelocity;
};
typedef struct MusicDeviceStdNoteParams		MusicDeviceStdNoteParams;

struct NoteParamsControlValue
{
	AudioUnitParameterID			mID;
	AudioUnitParameterValue			mValue;
};
typedef struct NoteParamsControlValue		NoteParamsControlValue;


/*-----------------------------------------------------------------------------
	MusicDeviceNoteParams

	Used to hold the value of the inParams parameter for the MusicDeviceStartNote function.
	
	This argument has 2 flavors:
	(1) MusicDeviceStdNoteParams
		where argCount is 2, and the first argument is pitch (fractional values may be used)
		(defined as 0 < 128 MIDI NoteNum), the second velocity (0 < 128)
	
	(2) ExtendedNoteParams
		where argCount is 2 + the number of contained
		NoteParamsControlValue structures - so the size of the mControls
		array is (argCount - 2)
-----------------------------------------------------------------------------*/

struct MusicDeviceNoteParams
{
	UInt32							argCount;
	Float32							mPitch;
	Float32							mVelocity;
	NoteParamsControlValue			mControls[1];				/* arbitrary length */
};
typedef struct MusicDeviceNoteParams    MusicDeviceNoteParams;

enum {
	kMusicNoteEvent_UseGroupInstrument  = 0xFFFFFFFF,
	kMusicNoteEvent_Unused				= 0xFFFFFFFF
};


typedef UInt32                          MusicDeviceGroupID;
typedef UInt32                          NoteInstanceID;
typedef ComponentInstance               MusicDeviceComponent;

/*
	Notes can be created/started with one of two methods. To stop a note
	it must be stopped with the same API as was used to start it:
	
	(1) the MIDI Note on event (MusicDeviceMIDIEvent)
		- notes must be stopped with the MIDI note off event (MusicDeviceMIDIEvent)
		
		The MIDI Note number is used to turn the note off for the specified channel
		
	(2) the extended Note API (MusicDeviceStartNote). This API returns a note instance ID.
		This is unique and can be used with the new kAudioUnitScope_Note.
		
		It is also used to turn the note off MusicDeviceStopNote
	
	Notes started with one API cannot be stopped with the other
*/

extern ComponentResult
MusicDeviceMIDIEvent(	MusicDeviceComponent	ci,
						UInt32					inStatus,
						UInt32					inData1,
						UInt32					inData2,
						UInt32					inOffsetSampleFrame)				AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern ComponentResult
MusicDeviceSysEx(		MusicDeviceComponent	ci,
						const UInt8 *			inData,
						UInt32					inLength)							AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
	The notion of instruments (separate voices assigned to different control groups) is a deprecated concept.
	
	Going forward, multitimbral synths are implemented using Part Scopes.
	
	Thus, the Prepare and Release Instrument API calls are deprecated (see also MusicDeviceStartNote)

*/
extern ComponentResult
MusicDevicePrepareInstrument(	MusicDeviceComponent		ci,
								MusicDeviceInstrumentID		inInstrument)		AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER
																				DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;


extern ComponentResult
MusicDeviceReleaseInstrument(	MusicDeviceComponent		ci,
								MusicDeviceInstrumentID		inInstrument)		AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER
																				DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
	MusicDeviceStartNote's inInstrument parameter should be set to kMusicNoteEvent_Unused.
	The instrument on a given group is set using either the
	patch/bank semantics of MIDI or the assignment of a Part to a given group ID.
	
	You must provide outNoteInstanceID or it is a paramErr
	
	The provided note instance MUST be unique for each note it renders
	The note instance ID must also be a non-zero value
*/
extern ComponentResult
MusicDeviceStartNote(	MusicDeviceComponent				ci,
						MusicDeviceInstrumentID				inInstrument,
						MusicDeviceGroupID					inGroupID,
						NoteInstanceID *					outNoteInstanceID,
						UInt32								inOffsetSampleFrame,
						const MusicDeviceNoteParams *	 	inParams)				AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
	This call can be used in one of two ways:
		(1) specify kMusicNoteEvent_Unused as the note instance ID 
			- each note on the specified group ID is turned off
		(2) a valid note instance ID, turns off that note 
			- the groupID is not used in this case and should be set to kMusicNoteEvent_Unused
*/
extern ComponentResult
MusicDeviceStopNote(	MusicDeviceComponent	ci,
						MusicDeviceGroupID		inGroupID,
						NoteInstanceID			inNoteInstanceID,
						UInt32					inOffsetSampleFrame)				AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


//-----------------------------------------------------------------------------
//	Selectors for component calls
//-----------------------------------------------------------------------------
enum {
		kMusicDeviceRange						= 0x0100,	// range of selectors for MusicDevices
		kMusicDeviceMIDIEventSelect				= 0x0101,
		kMusicDeviceSysExSelect					= 0x0102,
		kMusicDevicePrepareInstrumentSelect		= 0x0103,
		kMusicDeviceReleaseInstrumentSelect		= 0x0104,
		kMusicDeviceStartNoteSelect				= 0x0105,
		kMusicDeviceStopNoteSelect				= 0x0106
};

//-----------------------------------------------------------------------------
//	Fast-dispatch function pointer types
//	
//	For functions where performance may be an issue, a client may use
//	the kAudioUnitProperty_FastDispatch property to get a function
//	pointer pointing directly to the AudioUnit's implementation, to
//	avoid the cost of dispatching through the Component Manager. (Note
//	that AudioUnits are not required to implement this, but should.)
//-----------------------------------------------------------------------------

typedef ComponentResult
(*MusicDeviceMIDIEventProc)(	void *					inComponentStorage,
								UInt32					inStatus,
								UInt32					inData1,
								UInt32					inData2,
								UInt32					inOffsetSampleFrame);

#if !__LP64__
	#if PRAGMA_STRUCT_ALIGN
		#pragma options align=reset
	#elif PRAGMA_STRUCT_PACKPUSH
		#pragma pack(pop)
	#elif PRAGMA_STRUCT_PACK
		#pragma pack()
	#endif
#endif

#ifdef PRAGMA_IMPORT_OFF
#pragma import off
#elif PRAGMA_IMPORT
#pragma import reset
#endif

#ifdef __cplusplus
}
#endif

#endif /* __MUSICDEVICE__ */

