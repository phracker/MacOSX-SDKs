/*
     File:       AudioOutputUnit.h
 
     Contains:   AudioOutputUnit Interfaces
 
     Copyright:  © 2000-2008 by Apple, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __AUDIOOUTPUTUNIT__
#define __AUDIOOUTPUTUNIT__

#include <Availability.h>
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
//	Start/stop methods for output units
//-----------------------------------------------------------------------------
extern OSStatus
AudioOutputUnitStart(	AudioUnit	ci)											__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

extern OSStatus
AudioOutputUnitStop(	AudioUnit	ci)											__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

//-----------------------------------------------------------------------------
//	Selectors for component and audio plugin calls
//-----------------------------------------------------------------------------
enum {
	kAudioOutputUnitRange						= 0x0200,	// selector range
	kAudioOutputUnitStartSelect					= 0x0201,
	kAudioOutputUnitStopSelect					= 0x0202
};

/*!
*/
typedef OSStatus	(*AudioOutputUnitStartProc) (void *self);

/*!
*/
typedef OSStatus	(*AudioOutputUnitStopProc) (void *self);


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

#endif /* __AUDIOOUTPUTUNIT__ */

