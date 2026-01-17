/*
     File:       Sound.k.h
 
     Contains:   Sound Manager Interfaces.
 
     Version:    CarbonSound-73~1
 
     Copyright:  © 1986-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __SOUND_K__
#define __SOUND_K__

#include <CarbonSound/Sound.h>
/*
	Example usage:

		#define SOUNDCOMPONENT_BASENAME()	Fred
		#define SOUNDCOMPONENT_GLOBALS()	FredGlobalsHandle
		#include <Sound.k.h>

	To specify that your component implementation does not use globals, do not #define SOUNDCOMPONENT_GLOBALS
*/
#ifdef SOUNDCOMPONENT_BASENAME
	#ifndef SOUNDCOMPONENT_GLOBALS
		#define SOUNDCOMPONENT_GLOBALS() 
		#define ADD_SOUNDCOMPONENT_COMMA 
	#else
		#define ADD_SOUNDCOMPONENT_COMMA ,
	#endif
	#define SOUNDCOMPONENT_GLUE(a,b) a##b
	#define SOUNDCOMPONENT_STRCAT(a,b) SOUNDCOMPONENT_GLUE(a,b)
	#define ADD_SOUNDCOMPONENT_BASENAME(name) SOUNDCOMPONENT_STRCAT(SOUNDCOMPONENT_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_SOUNDCOMPONENT_BASENAME(InitOutputDevice) (SOUNDCOMPONENT_GLOBALS() ADD_SOUNDCOMPONENT_COMMA long  actions);

	EXTERN_API( ComponentResult  ) ADD_SOUNDCOMPONENT_BASENAME(SetSource) (SOUNDCOMPONENT_GLOBALS() ADD_SOUNDCOMPONENT_COMMA SoundSource  sourceID, ComponentInstance  source);

	EXTERN_API( ComponentResult  ) ADD_SOUNDCOMPONENT_BASENAME(GetSource) (SOUNDCOMPONENT_GLOBALS() ADD_SOUNDCOMPONENT_COMMA SoundSource  sourceID, ComponentInstance * source);

	EXTERN_API( ComponentResult  ) ADD_SOUNDCOMPONENT_BASENAME(GetSourceData) (SOUNDCOMPONENT_GLOBALS() ADD_SOUNDCOMPONENT_COMMA SoundComponentDataPtr * sourceData);

	EXTERN_API( ComponentResult  ) ADD_SOUNDCOMPONENT_BASENAME(SetOutput) (SOUNDCOMPONENT_GLOBALS() ADD_SOUNDCOMPONENT_COMMA SoundComponentDataPtr  requested, SoundComponentDataPtr * actual);

	EXTERN_API( ComponentResult  ) ADD_SOUNDCOMPONENT_BASENAME(AddSource) (SOUNDCOMPONENT_GLOBALS() ADD_SOUNDCOMPONENT_COMMA SoundSource * sourceID);

	EXTERN_API( ComponentResult  ) ADD_SOUNDCOMPONENT_BASENAME(RemoveSource) (SOUNDCOMPONENT_GLOBALS() ADD_SOUNDCOMPONENT_COMMA SoundSource  sourceID);

	EXTERN_API( ComponentResult  ) ADD_SOUNDCOMPONENT_BASENAME(GetInfo) (SOUNDCOMPONENT_GLOBALS() ADD_SOUNDCOMPONENT_COMMA SoundSource  sourceID, OSType  selector, void * infoPtr);

	EXTERN_API( ComponentResult  ) ADD_SOUNDCOMPONENT_BASENAME(SetInfo) (SOUNDCOMPONENT_GLOBALS() ADD_SOUNDCOMPONENT_COMMA SoundSource  sourceID, OSType  selector, void * infoPtr);

	EXTERN_API( ComponentResult  ) ADD_SOUNDCOMPONENT_BASENAME(StartSource) (SOUNDCOMPONENT_GLOBALS() ADD_SOUNDCOMPONENT_COMMA short  count, SoundSource * sources);

	EXTERN_API( ComponentResult  ) ADD_SOUNDCOMPONENT_BASENAME(StopSource) (SOUNDCOMPONENT_GLOBALS() ADD_SOUNDCOMPONENT_COMMA short  count, SoundSource * sources);

	EXTERN_API( ComponentResult  ) ADD_SOUNDCOMPONENT_BASENAME(PauseSource) (SOUNDCOMPONENT_GLOBALS() ADD_SOUNDCOMPONENT_COMMA short  count, SoundSource * sources);

	EXTERN_API( ComponentResult  ) ADD_SOUNDCOMPONENT_BASENAME(PlaySourceBuffer) (SOUNDCOMPONENT_GLOBALS() ADD_SOUNDCOMPONENT_COMMA SoundSource  sourceID, SoundParamBlockPtr  pb, long  actions);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppSoundComponentInitOutputDeviceProcInfo = 0x000003F0,
		uppSoundComponentSetSourceProcInfo = 0x00000FF0,
		uppSoundComponentGetSourceProcInfo = 0x00000FF0,
		uppSoundComponentGetSourceDataProcInfo = 0x000003F0,
		uppSoundComponentSetOutputProcInfo = 0x00000FF0,
		uppSoundComponentAddSourceProcInfo = 0x000003F0,
		uppSoundComponentRemoveSourceProcInfo = 0x000003F0,
		uppSoundComponentGetInfoProcInfo = 0x00003FF0,
		uppSoundComponentSetInfoProcInfo = 0x00003FF0,
		uppSoundComponentStartSourceProcInfo = 0x00000EF0,
		uppSoundComponentStopSourceProcInfo = 0x00000EF0,
		uppSoundComponentPauseSourceProcInfo = 0x00000EF0,
		uppSoundComponentPlaySourceBufferProcInfo = 0x00003FF0
	};

#endif	/* SOUNDCOMPONENT_BASENAME */

/*
	Example usage:

		#define AUDIO_BASENAME()	Fred
		#define AUDIO_GLOBALS()	FredGlobalsHandle
		#include <Sound.k.h>

	To specify that your component implementation does not use globals, do not #define AUDIO_GLOBALS
*/
#ifdef AUDIO_BASENAME
	#ifndef AUDIO_GLOBALS
		#define AUDIO_GLOBALS() 
		#define ADD_AUDIO_COMMA 
	#else
		#define ADD_AUDIO_COMMA ,
	#endif
	#define AUDIO_GLUE(a,b) a##b
	#define AUDIO_STRCAT(a,b) AUDIO_GLUE(a,b)
	#define ADD_AUDIO_BASENAME(name) AUDIO_STRCAT(AUDIO_BASENAME(),name)

#endif	/* AUDIO_BASENAME */

#if TARGET_API_MAC_CARBON
/*
	Example usage:

		#define SNDINPUT_BASENAME()	Fred
		#define SNDINPUT_GLOBALS()	FredGlobalsHandle
		#include <Sound.k.h>

	To specify that your component implementation does not use globals, do not #define SNDINPUT_GLOBALS
*/
#ifdef SNDINPUT_BASENAME
	#ifndef SNDINPUT_GLOBALS
		#define SNDINPUT_GLOBALS() 
		#define ADD_SNDINPUT_COMMA 
	#else
		#define ADD_SNDINPUT_COMMA ,
	#endif
	#define SNDINPUT_GLUE(a,b) a##b
	#define SNDINPUT_STRCAT(a,b) SNDINPUT_GLUE(a,b)
	#define ADD_SNDINPUT_BASENAME(name) SNDINPUT_STRCAT(SNDINPUT_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_SNDINPUT_BASENAME(ReadAsync) (SNDINPUT_GLOBALS() ADD_SNDINPUT_COMMA SndInputCmpParamPtr  SICParmPtr);

	EXTERN_API( ComponentResult  ) ADD_SNDINPUT_BASENAME(ReadSync) (SNDINPUT_GLOBALS() ADD_SNDINPUT_COMMA SndInputCmpParamPtr  SICParmPtr);

	EXTERN_API( ComponentResult  ) ADD_SNDINPUT_BASENAME(PauseRecording) (SNDINPUT_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_SNDINPUT_BASENAME(ResumeRecording) (SNDINPUT_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_SNDINPUT_BASENAME(StopRecording) (SNDINPUT_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_SNDINPUT_BASENAME(GetStatus) (SNDINPUT_GLOBALS() ADD_SNDINPUT_COMMA short * recordingStatus, unsigned long * totalSamplesToRecord, unsigned long * numberOfSamplesRecorded);

	EXTERN_API( ComponentResult  ) ADD_SNDINPUT_BASENAME(GetDeviceInfo) (SNDINPUT_GLOBALS() ADD_SNDINPUT_COMMA OSType  infoType, void * infoData);

	EXTERN_API( ComponentResult  ) ADD_SNDINPUT_BASENAME(SetDeviceInfo) (SNDINPUT_GLOBALS() ADD_SNDINPUT_COMMA OSType  infoType, void * infoData);

	EXTERN_API( ComponentResult  ) ADD_SNDINPUT_BASENAME(InitHardware) (SNDINPUT_GLOBALS());


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppSndInputReadAsyncProcInfo = 0x000003F0,
		uppSndInputReadSyncProcInfo = 0x000003F0,
		uppSndInputPauseRecordingProcInfo = 0x000000F0,
		uppSndInputResumeRecordingProcInfo = 0x000000F0,
		uppSndInputStopRecordingProcInfo = 0x000000F0,
		uppSndInputGetStatusProcInfo = 0x00003FF0,
		uppSndInputGetDeviceInfoProcInfo = 0x00000FF0,
		uppSndInputSetDeviceInfoProcInfo = 0x00000FF0,
		uppSndInputInitHardwareProcInfo = 0x000000F0
	};

#endif	/* SNDINPUT_BASENAME */

#endif  /* TARGET_API_MAC_CARBON */


#endif /* __SOUND_K__ */

