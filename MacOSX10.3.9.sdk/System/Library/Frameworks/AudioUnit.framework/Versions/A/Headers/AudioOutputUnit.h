/*
     File:       AudioOutputUnit.h
 
     Contains:   AudioOutputUnit Interfaces
 
     Version:    Mac OS X
 
     Copyright:  © 2000-2004 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __AUDIOOUTPUTUNIT__
#define __AUDIOOUTPUTUNIT__

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
//	Start/stop methods for audio output units
//-----------------------------------------------------------------------------
extern ComponentResult
AudioOutputUnitStart(	AudioUnit	ci)											AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern ComponentResult
AudioOutputUnitStop(	AudioUnit	ci)											AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

//-----------------------------------------------------------------------------
//	Selectors for component calls
//-----------------------------------------------------------------------------
enum {
	kAudioOutputUnitRange						= 0x0200,	// selector range
	kAudioOutputUnitStartSelect					= 0x0201,
	kAudioOutputUnitStopSelect					= 0x0202
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

#endif /* __AUDIOOUTPUTUNIT__ */

