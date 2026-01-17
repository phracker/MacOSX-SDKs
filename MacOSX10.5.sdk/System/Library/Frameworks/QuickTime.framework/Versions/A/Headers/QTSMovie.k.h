/*
     File:       QTSMovie.k.h
 
     Contains:   QuickTime Interfaces.
 
     Version:    QuickTime 7.2.1
 
     Copyright:  © 1990-2006 by Apple Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __QTSMOVIE_K__
#define __QTSMOVIE_K__

#include <QuickTime/QTSMovie.h>
/*
	Example usage:

		#define QTSMEDIA_BASENAME()	Fred
		#define QTSMEDIA_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QTSMovie.k.h>

	To specify that your component implementation does not use globals, do not #define QTSMEDIA_GLOBALS
*/
#ifdef QTSMEDIA_BASENAME
	#ifndef QTSMEDIA_GLOBALS
		#define QTSMEDIA_GLOBALS() 
		#define ADD_QTSMEDIA_COMMA 
	#else
		#define ADD_QTSMEDIA_COMMA ,
	#endif
	#define QTSMEDIA_GLUE(a,b) a##b
	#define QTSMEDIA_STRCAT(a,b) QTSMEDIA_GLUE(a,b)
	#define ADD_QTSMEDIA_BASENAME(name) QTSMEDIA_STRCAT(QTSMEDIA_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_QTSMEDIA_BASENAME(SetInfo) (QTSMEDIA_GLOBALS() ADD_QTSMEDIA_COMMA OSType  inSelector, void * ioParams);

	EXTERN_API( ComponentResult  ) ADD_QTSMEDIA_BASENAME(GetInfo) (QTSMEDIA_GLOBALS() ADD_QTSMEDIA_COMMA OSType  inSelector, void * ioParams);

	EXTERN_API( ComponentResult  ) ADD_QTSMEDIA_BASENAME(SetIndStreamInfo) (QTSMEDIA_GLOBALS() ADD_QTSMEDIA_COMMA SInt32  inIndex, OSType  inSelector, void * ioParams);

	EXTERN_API( ComponentResult  ) ADD_QTSMEDIA_BASENAME(GetIndStreamInfo) (QTSMEDIA_GLOBALS() ADD_QTSMEDIA_COMMA SInt32  inIndex, OSType  inSelector, void * ioParams);

#endif	/* QTSMEDIA_BASENAME */


#endif /* __QTSMOVIE_K__ */

