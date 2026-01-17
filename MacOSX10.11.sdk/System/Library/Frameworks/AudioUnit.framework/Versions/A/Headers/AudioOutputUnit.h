/*!
	@file		AudioOutputUnit.h
 	@framework	AudioUnit.framework
 	@copyright	(c) 2000-2015 Apple, Inc. All rights reserved.
	@brief		Additional Audio Unit API for audio input/output units.
*/

#ifndef AudioUnit_AudioOutputUnit_h
#define AudioUnit_AudioOutputUnit_h

#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <AudioUnit/AUComponent.h>
#else
	#include <AUComponent.h>
#endif

CF_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
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

#ifdef __cplusplus
}
#endif

CF_ASSUME_NONNULL_END

#endif /* AudioUnit_AudioOutputUnit_h */
