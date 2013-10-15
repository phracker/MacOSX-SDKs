/*
     File:       AUNTComponent.h
 
     Contains:   AudioUnit Version 1 Specific Interfaces
 
     Version:    Technology: System 9, X
                 Release:    Mac OS X
 
     Copyright:  © 2002-2003 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
/*
	All of the API and structs in this file are deprecated. See AUComponent.h for the Replacement AU V2 API 
	that should be used instead
*/
#ifndef __AUNTCOMPONENT__
#define __AUNTCOMPONENT__

#include <AvailabilityMacros.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <AudioUnit/AUComponent.h>
#else
	#include <AUComponent.h>
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
//	AudioUnit v1 component types and subtypes
//-----------------------------------------------------------------------------
enum
{
	kAudioUnitComponentType					= 'aunt',
	kAudioUnitSubType_Output				= 'out ',
	kAudioUnitID_HALOutput					= 'ahal',
	kAudioUnitID_DefaultOutput				= 'def ',
	kAudioUnitID_SystemOutput				= 'sys ',
	kAudioUnitID_GenericOutput				= 'genr',
	kAudioUnitSubType_MusicDevice 			= 'musd',
	kAudioUnitID_DLSSynth					= 'dls ',
	kAudioUnitSubType_SampleRateConverter	= 'srcv',
	kAudioUnitID_PolyphaseSRC				= 'poly',
	kAudioUnitSubType_FormatConverter 		= 'fmtc',
	kAudioUnitID_Interleaver				= 'inlv',
	kAudioUnitID_Deinterleaver				= 'dnlv',
	kAudioUnitID_AUConverter				= 'conv',
	kAudioUnitSubType_Effect				= 'efct',
	kAudioUnitID_MatrixReverb				= 'mrev',
	kAudioUnitID_Delay						= 'dely',
	kAudioUnitID_LowPassFilter				= 'lpas',
	kAudioUnitID_HighPassFilter				= 'hpas',
	kAudioUnitID_BandPassFilter				= 'bpas',
	kAudioUnitID_PeakLimiter				= 'lmtr',
	kAudioUnitID_DynamicsProcessor			= 'dcmp',
	kAudioUnitSubType_Mixer					= 'mixr',
	kAudioUnitID_StereoMixer				= 'smxr',
	kAudioUnitID_3DMixer					= '3dmx'
};

typedef OSStatus
(*AudioUnitRenderCallback)(	void *						inRefCon,
							AudioUnitRenderActionFlags	inActionFlags,
							const AudioTimeStamp *		inTimeStamp,
							UInt32						inBusNumber,
							AudioBuffer *				ioData);

extern ComponentResult
AudioUnitSetRenderNotification(		AudioUnit					ci,
									AudioUnitRenderCallback		inProc,
									void *						inProcRefCon)		AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER DEPRECATED_IN_MAC_OS_X_VERSION_10_3_AND_LATER;


extern ComponentResult
AudioUnitRemoveRenderNotification(	AudioUnit					ci,
									AudioUnitRenderCallback		inProc,
									void *						inProcRefCon)		AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER DEPRECATED_IN_MAC_OS_X_VERSION_10_3_AND_LATER;


extern ComponentResult
AudioUnitRenderSlice(				AudioUnit					ci,
									AudioUnitRenderActionFlags	inActionFlags,
									const AudioTimeStamp *		inTimeStamp,
									UInt32						inOutputBusNumber,
									AudioBuffer *				ioData)				AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER DEPRECATED_IN_MAC_OS_X_VERSION_10_3_AND_LATER;

//-----------------------------------------------------------------------------
//	Selectors for component calls
//-----------------------------------------------------------------------------
enum
{
    kAudioUnitSetRenderNotificationSelect      = 0x000C,
    kAudioUnitRemoveRenderNotificationSelect   = 0x000D,
    kAudioUnitRenderSliceSelect                = 0x0008
};

typedef ComponentResult
(*AudioUnitRenderSliceProc)(	void *						inComponentStorage,
								AudioUnitRenderActionFlags	inActionFlags,
								const AudioTimeStamp *		inTimeStamp,
								UInt32 						inOutputBusNumber,
								AudioBuffer *				ioData);


//-----------------------------------------------------------------------------
//	Properties that are unique to V1 'aunt' type AudioUnits
//-----------------------------------------------------------------------------

/* This defines a callback function which renders audio into an input of an AudioUnit*/
struct AudioUnitInputCallback
{
	AudioUnitRenderCallback		inputProc;
	void *              		inputProcRefCon;
};
typedef struct AudioUnitInputCallback   AudioUnitInputCallback;

enum
{
	kAudioUnitProperty_SetInputCallback = 7
};



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

#endif /* __AUNTCOMPONENT__ */

