/*
     File:       AudioOutputUnit.h
 
     Contains:   AudioOutputUnit Interfaces
 
     Version:    Technology: System 9, X
                 Release:    Mac OS X
 
     Copyright:  © 2000-2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __AUDIOOUTPUTUNIT__
#define __AUDIOOUTPUTUNIT__

#include <AudioUnit/AUComponent.h>




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


/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   ranges
*/

enum {
  kAudioOutputUnitRange         = 0x0200
};


/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Start/stop methods for audio output units
*/
EXTERN_API( ComponentResult )
AudioOutputUnitStart(AudioUnit ci)                            FIVEWORDINLINE(0x2F3C, 0x0000, 0x0201, 0x7000, 0xA82A);


EXTERN_API( ComponentResult )
AudioOutputUnitStop(AudioUnit ci)                             FIVEWORDINLINE(0x2F3C, 0x0000, 0x0202, 0x7000, 0xA82A);





/* UPP call backs */

/* selectors for component calls */
enum {
    kAudioOutputUnitStartSelect                = 0x0201,
    kAudioOutputUnitStopSelect                 = 0x0202
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

