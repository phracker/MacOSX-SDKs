/*
     File:       AudioUnit.k.h
 
     Contains:   AudioUnit Interfaces
 
     Version:    Technology: System 9, X
                 Release:    Mac OS X
 
     Copyright:  © 2000-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __AUDIOUNIT_K__
#define __AUDIOUNIT_K__

#include <AudioUnit.h>

/*
	Example usage:

		#define AUDIOUNIT_BASENAME()	Fred
		#define AUDIOUNIT_GLOBALS()	FredGlobalsHandle
		#include <AudioUnit.k.h>

	To specify that your component implementation does not use globals, do not #define AUDIOUNIT_GLOBALS
*/
#ifdef AUDIOUNIT_BASENAME
	#ifndef AUDIOUNIT_GLOBALS
		#define AUDIOUNIT_GLOBALS() 
		#define ADD_AUDIOUNIT_COMMA 
	#else
		#define ADD_AUDIOUNIT_COMMA ,
	#endif
	#define AUDIOUNIT_GLUE(a,b) a##b
	#define AUDIOUNIT_STRCAT(a,b) AUDIOUNIT_GLUE(a,b)
	#define ADD_AUDIOUNIT_BASENAME(name) AUDIOUNIT_STRCAT(AUDIOUNIT_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_AUDIOUNIT_BASENAME(Initialize) (AUDIOUNIT_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_AUDIOUNIT_BASENAME(Uninitialize) (AUDIOUNIT_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_AUDIOUNIT_BASENAME(GetPropertyInfo) (AUDIOUNIT_GLOBALS() ADD_AUDIOUNIT_COMMA AudioUnitPropertyID  inID, AudioUnitScope  inScope, AudioUnitElement  inElement, UInt32 * outDataSize, Boolean * outWritable);

	EXTERN_API( ComponentResult  ) ADD_AUDIOUNIT_BASENAME(GetProperty) (AUDIOUNIT_GLOBALS() ADD_AUDIOUNIT_COMMA AudioUnitPropertyID  inID, AudioUnitScope  inScope, AudioUnitElement  inElement, void * outData, UInt32 * ioDataSize);

	EXTERN_API( ComponentResult  ) ADD_AUDIOUNIT_BASENAME(SetProperty) (AUDIOUNIT_GLOBALS() ADD_AUDIOUNIT_COMMA AudioUnitPropertyID  inID, AudioUnitScope  inScope, AudioUnitElement  inElement, void * inData, UInt32  inDataSize);

	EXTERN_API( ComponentResult  ) ADD_AUDIOUNIT_BASENAME(SetRenderNotification) (AUDIOUNIT_GLOBALS() ADD_AUDIOUNIT_COMMA AudioUnitRenderCallback  inProc, void * inProcRefCon);

	EXTERN_API( ComponentResult  ) ADD_AUDIOUNIT_BASENAME(AddPropertyListener) (AUDIOUNIT_GLOBALS() ADD_AUDIOUNIT_COMMA AudioUnitPropertyID  inID, AudioUnitPropertyListenerProc  inProc, void * inProcRefCon);

	EXTERN_API( ComponentResult  ) ADD_AUDIOUNIT_BASENAME(RemovePropertyListener) (AUDIOUNIT_GLOBALS() ADD_AUDIOUNIT_COMMA AudioUnitPropertyID  inID, AudioUnitPropertyListenerProc  inProc);

	EXTERN_API( ComponentResult  ) ADD_AUDIOUNIT_BASENAME(GetParameter) (AUDIOUNIT_GLOBALS() ADD_AUDIOUNIT_COMMA AudioUnitParameterID  inID, AudioUnitScope  inScope, AudioUnitElement  inElement, Float32 * outValue);

	EXTERN_API( ComponentResult  ) ADD_AUDIOUNIT_BASENAME(SetParameter) (AUDIOUNIT_GLOBALS() ADD_AUDIOUNIT_COMMA AudioUnitParameterID  inID, AudioUnitScope  inScope, AudioUnitElement  inElement, Float32  inValue, UInt32  inBufferOffsetInFrames);

	EXTERN_API( ComponentResult  ) ADD_AUDIOUNIT_BASENAME(RenderSlice) (AUDIOUNIT_GLOBALS() ADD_AUDIOUNIT_COMMA AudioUnitRenderActionFlags  inActionFlags, const AudioTimeStamp * inTimeStamp, UInt32  inOutputBusNumber, AudioBuffer * ioData);

	EXTERN_API( ComponentResult  ) ADD_AUDIOUNIT_BASENAME(Reset) (AUDIOUNIT_GLOBALS() ADD_AUDIOUNIT_COMMA AudioUnitScope  inScope, AudioUnitElement  inElement);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppAudioUnitInitializeProcInfo = 0x000000F0,
		uppAudioUnitUninitializeProcInfo = 0x000000F0,
		uppAudioUnitGetPropertyInfoProcInfo = 0x0003FFF0,
		uppAudioUnitGetPropertyProcInfo = 0x0003FFF0,
		uppAudioUnitSetPropertyProcInfo = 0x0003FFF0,
		uppAudioUnitSetRenderNotificationProcInfo = 0x00000FF0,
		uppAudioUnitAddPropertyListenerProcInfo = 0x00003FF0,
		uppAudioUnitRemovePropertyListenerProcInfo = 0x00000FF0,
		uppAudioUnitGetParameterProcInfo = 0x0000FFF0,
		uppAudioUnitSetParameterProcInfo = 0x0003FFF0,
		uppAudioUnitRenderSliceProcInfo = 0x0000FFF0,
		uppAudioUnitResetProcInfo = 0x00000FF0
	};

#endif	/* AUDIOUNIT_BASENAME */


#endif /* __AUDIOUNIT_K__ */

