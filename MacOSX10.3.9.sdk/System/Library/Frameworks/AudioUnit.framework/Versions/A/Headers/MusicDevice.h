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

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

//-----------------------------------------------------------------------------
//	A MusicDevice can control far more independent instruments than the 16
//	channels of MIDI, through the use of the extended APIs.
//	AudioUnitSetParameter is used with the kAudioUnitScope_Group to use these
//	extended control facilities. See documentation for further details.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//	MusicDevice types and structures
//-----------------------------------------------------------------------------

typedef UInt32                          MusicDeviceInstrumentID;
	/* this is normally used for packing in MIDI note params (note number, velocity)*/

struct MusicDeviceStdNoteParams
{
	UInt32							argCount;		/* should be 2*/
	Float32							mPitch;
	Float32							mVelocity;
};
typedef struct MusicDeviceStdNoteParams		MusicDeviceStdNoteParams;

struct NoteParamsControlValue
{
	UInt32							mID;
	Float32							mValue;
};
typedef struct NoteParamsControlValue		NoteParamsControlValue;


//-----------------------------------------------------------------------------
//	MusicDeviceNoteParams
//
//	This is the structure that should be used as the
//	const MusicDeviceNoteParams  *inParams argument with MusicDeviceStartNote.
//	
//	This argument has 2 flavours
//	(1) MusicDeviceStdNoteParams
//		where argCount is 2, and the first argument is pitch (defined as
//		0 < 128 MIDI NoteNum), the second velocity (0 < 128)
//	
//	(2) ExtendedNoteParams
//		where argCount is 2 + the number of contained
//		NoteParamsControlValue structures - so the size of the mControls
//		array is (argCount - 2)
//-----------------------------------------------------------------------------

struct MusicDeviceNoteParams
{
	UInt32							argCount;
	Float32							mPitch;
	Float32							mVelocity;
	NoteParamsControlValue			mControls[1];				/* arbitrary length */
};
typedef struct MusicDeviceNoteParams    MusicDeviceNoteParams;

/*
   The instrumentID that is passed in to the MusicDeviceStartNote can
   specify a specific intrument ID. The constant
   kMusicNoteEvent_UseGroupInstrument can alternatively be passed to use
   the current instrument defined for that group. In MIDI this is the
   typical usage of a bank and patch set for a specific channel where
   all notes that start on that channel use that instrument.
*/
enum {
	kMusicNoteEvent_UseGroupInstrument = 0xFFFFFFFF
};


typedef UInt32                          MusicDeviceGroupID;
typedef UInt32                          NoteInstanceID;
typedef ComponentInstance               MusicDeviceComponent;


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


extern ComponentResult
MusicDevicePrepareInstrument(	MusicDeviceComponent		ci,
								MusicDeviceInstrumentID		inInstrument)			AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


extern ComponentResult
MusicDeviceReleaseInstrument(	MusicDeviceComponent		ci,
								MusicDeviceInstrumentID		inInstrument)			AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


extern ComponentResult
MusicDeviceStartNote(	MusicDeviceComponent				ci,
						MusicDeviceInstrumentID				inInstrument,
						MusicDeviceGroupID					inGroupID,
						NoteInstanceID *					outNoteInstanceID,
						UInt32								inOffsetSampleFrame,
						const MusicDeviceNoteParams *	 	inParams)				AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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


#if PRAGMA_STRUCT_ALIGN
    #pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
    #pragma pack()
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

