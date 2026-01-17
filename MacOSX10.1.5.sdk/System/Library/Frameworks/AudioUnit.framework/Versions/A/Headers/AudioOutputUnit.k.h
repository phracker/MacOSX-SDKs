/*
     File:       AudioOutputUnit.k.h
 
     Contains:   AudioOutputUnit Interfaces
 
     Version:    Technology: System 9, X
                 Release:    Mac OS X
 
     Copyright:  © 2000 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __AUDIOOUTPUTUNIT_K__
#define __AUDIOOUTPUTUNIT_K__

#include <AudioOutputUnit.h>

/*
	Example usage:

		#define AUDIOOUTPUTUNIT_BASENAME()	Fred
		#define AUDIOOUTPUTUNIT_GLOBALS()	FredGlobalsHandle
		#include <AudioOutputUnit.k.h>

	To specify that your component implementation does not use globals, do not #define AUDIOOUTPUTUNIT_GLOBALS
*/
#ifdef AUDIOOUTPUTUNIT_BASENAME
	#ifndef AUDIOOUTPUTUNIT_GLOBALS
		#define AUDIOOUTPUTUNIT_GLOBALS() 
		#define ADD_AUDIOOUTPUTUNIT_COMMA 
	#else
		#define ADD_AUDIOOUTPUTUNIT_COMMA ,
	#endif
	#define AUDIOOUTPUTUNIT_GLUE(a,b) a##b
	#define AUDIOOUTPUTUNIT_STRCAT(a,b) AUDIOOUTPUTUNIT_GLUE(a,b)
	#define ADD_AUDIOOUTPUTUNIT_BASENAME(name) AUDIOOUTPUTUNIT_STRCAT(AUDIOOUTPUTUNIT_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_AUDIOOUTPUTUNIT_BASENAME(Start) (AUDIOOUTPUTUNIT_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_AUDIOOUTPUTUNIT_BASENAME(Stop) (AUDIOOUTPUTUNIT_GLOBALS());


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppAudioOutputUnitStartProcInfo = 0x000000F0,
		uppAudioOutputUnitStopProcInfo = 0x000000F0
	};

#endif	/* AUDIOOUTPUTUNIT_BASENAME */


#endif /* __AUDIOOUTPUTUNIT_K__ */

