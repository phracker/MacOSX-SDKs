/*
     File:       AUNTComponent.h
 
     Contains:   AudioUnit Version 1 Specific Interfaces
 
     Version:    Technology: System 9, X
                 Release:    Mac OS X
 
     Copyright:  © 2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __AUNTCOMPONENT__
#define __AUNTCOMPONENT__

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
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   AudioUnit component types and subtypes
*/
enum {
  kAudioUnitComponentType       = FOUR_CHAR_CODE('aunt'),
  kAudioUnitSubType_Output      = FOUR_CHAR_CODE('out '),
  kAudioUnitID_HALOutput        = FOUR_CHAR_CODE('ahal'),
  kAudioUnitID_DefaultOutput    = FOUR_CHAR_CODE('def '),
  kAudioUnitID_SystemOutput     = FOUR_CHAR_CODE('sys '),
  kAudioUnitID_GenericOutput    = FOUR_CHAR_CODE('genr'),
  kAudioUnitSubType_MusicDevice = FOUR_CHAR_CODE('musd'),
  kAudioUnitID_DLSSynth         = FOUR_CHAR_CODE('dls '),
  kAudioUnitSubType_SampleRateConverter = FOUR_CHAR_CODE('srcv'),
  kAudioUnitID_PolyphaseSRC     = FOUR_CHAR_CODE('poly'),
  kAudioUnitSubType_FormatConverter = FOUR_CHAR_CODE('fmtc'),
  kAudioUnitID_Interleaver      = FOUR_CHAR_CODE('inlv'),
  kAudioUnitID_Deinterleaver    = FOUR_CHAR_CODE('dnlv'),
  kAudioUnitID_AUConverter      = FOUR_CHAR_CODE('conv'),
  kAudioUnitSubType_Effect      = FOUR_CHAR_CODE('efct'),
  kAudioUnitID_MatrixReverb     = FOUR_CHAR_CODE('mrev'),
  kAudioUnitID_Delay            = FOUR_CHAR_CODE('dely'),
  kAudioUnitID_LowPassFilter    = FOUR_CHAR_CODE('lpas'),
  kAudioUnitID_HighPassFilter   = FOUR_CHAR_CODE('hpas'),
  kAudioUnitID_BandPassFilter   = FOUR_CHAR_CODE('bpas'),
  kAudioUnitID_PeakLimiter      = FOUR_CHAR_CODE('lmtr'),
  kAudioUnitID_DynamicsProcessor = FOUR_CHAR_CODE('dcmp'),
  kAudioUnitSubType_Mixer       = FOUR_CHAR_CODE('mixr'),
  kAudioUnitID_StereoMixer      = FOUR_CHAR_CODE('smxr'),
  kAudioUnitID_3DMixer          = FOUR_CHAR_CODE('3dmx')
};


typedef CALLBACK_API_C( OSStatus , AudioUnitRenderCallback )(void *inRefCon, AudioUnitRenderActionFlags inActionFlags, const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber, AudioBuffer *ioData);
EXTERN_API( ComponentResult )
AudioUnitSetRenderNotification(
  AudioUnit                 ci,
  AudioUnitRenderCallback   inProc,
  void *                    inProcRefCon)                     FIVEWORDINLINE(0x2F3C, 0x0008, 0x000C, 0x7000, 0xA82A);


EXTERN_API( ComponentResult )
AudioUnitRemoveRenderNotification(
  AudioUnit                 ci,
  AudioUnitRenderCallback   inProc,
  void *                    inProcRefCon)                     FIVEWORDINLINE(0x2F3C, 0x0008, 0x000D, 0x7000, 0xA82A);



EXTERN_API( ComponentResult )
AudioUnitRenderSlice(
  AudioUnit                    ci,
  AudioUnitRenderActionFlags   inActionFlags,
  const AudioTimeStamp *       inTimeStamp,
  UInt32                       inOutputBusNumber,
  AudioBuffer *                ioData)                        FIVEWORDINLINE(0x2F3C, 0x0010, 0x0008, 0x7000, 0xA82A);




/* UPP call backs */

/* selectors for component calls */
enum {
    kAudioUnitSetRenderNotificationSelect      = 0x000C,
    kAudioUnitRemoveRenderNotificationSelect   = 0x000D,
    kAudioUnitRenderSliceSelect                = 0x0008
};
typedef CALLBACK_API_C( ComponentResult , AudioUnitRenderSliceProc )(void *inComponentStorage, AudioUnitRenderActionFlags inActionFlags, const AudioTimeStamp *inTimeStamp, UInt32 inOutputBusNumber, AudioBuffer *ioData);
/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    These are the properties that are unique to V1 'aunt' type AudioUnits
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

/* This defines a callback function which renders audio into an input of an AudioUnit*/
struct AudioUnitInputCallback {
  AudioUnitRenderCallback  inputProc;
  void *              inputProcRefCon;
};
typedef struct AudioUnitInputCallback   AudioUnitInputCallback;
enum {
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

