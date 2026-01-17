/*
     File:       AUComponent.h
 
     Contains:   AudioUnit Interfaces
 
     Version:    Mac OS X
 
     Copyright:  © 2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __AUCOMPONENT__
#define __AUCOMPONENT__

#include <CoreServices/CoreServices.h>
#include <CoreAudio/CoreAudioTypes.h>


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
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   ranges
*/

enum {
  kAudioUnitRange               = 0x0000
};

/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   AudioUnit stuff
*/

typedef ComponentInstance               AudioUnit;
/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   AudioUnit component types and subtypes
*/
enum {
  kAudioUnitType_Output         = FOUR_CHAR_CODE('auou'),
  kAudioUnitSubType_HALOutput   = FOUR_CHAR_CODE('ahal'),
  kAudioUnitSubType_DefaultOutput = FOUR_CHAR_CODE('def '),
  kAudioUnitSubType_SystemOutput = FOUR_CHAR_CODE('sys '),
  kAudioUnitSubType_GenericOutput = FOUR_CHAR_CODE('genr'),
  kAudioUnitType_MusicDevice    = FOUR_CHAR_CODE('aumu'),
  kAudioUnitSubType_DLSSynth    = FOUR_CHAR_CODE('dls '),
  kAudioUnitType_MusicEffect    = FOUR_CHAR_CODE('aumf'),
  kAudioUnitType_FormatConverter = FOUR_CHAR_CODE('aufc'),
  kAudioUnitSubType_AUConverter = FOUR_CHAR_CODE('conv'),
  kAudioUnitSubType_Varispeed   = FOUR_CHAR_CODE('vari'),
  kAudioUnitType_Effect         = FOUR_CHAR_CODE('aufx'),
  kAudioUnitSubType_Delay       = FOUR_CHAR_CODE('dely'),
  kAudioUnitSubType_LowPassFilter = FOUR_CHAR_CODE('lpas'),
  kAudioUnitSubType_HighPassFilter = FOUR_CHAR_CODE('hpas'),
  kAudioUnitSubType_BandPassFilter = FOUR_CHAR_CODE('bpas'),
  kAudioUnitSubType_HighShelfFilter = FOUR_CHAR_CODE('hshf'),
  kAudioUnitSubType_LowShelfFilter = FOUR_CHAR_CODE('lshf'),
  kAudioUnitSubType_ParametricEQ = FOUR_CHAR_CODE('pmeq'),
  kAudioUnitSubType_GraphicEQ   = FOUR_CHAR_CODE('greq'),
  kAudioUnitSubType_PeakLimiter = FOUR_CHAR_CODE('lmtr'),
  kAudioUnitSubType_DynamicsProcessor = FOUR_CHAR_CODE('dcmp'),
  kAudioUnitSubType_MultiBandCompressor = FOUR_CHAR_CODE('mcmp'),
  kAudioUnitSubType_MatrixReverb = FOUR_CHAR_CODE('mrev'),
  kAudioUnitType_Mixer          = FOUR_CHAR_CODE('aumx'),
  kAudioUnitSubType_StereoMixer = FOUR_CHAR_CODE('smxr'),
  kAudioUnitSubType_3DMixer     = FOUR_CHAR_CODE('3dmx'),
  kAudioUnitSubType_MatrixMixer = FOUR_CHAR_CODE('mxmx'),
  kAudioUnitType_Panner         = FOUR_CHAR_CODE('aupn'),
  kAudioUnitType_OfflineEffect  = FOUR_CHAR_CODE('auol'),
  kAudioUnitManufacturer_Apple  = FOUR_CHAR_CODE('appl')
};

/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   Render flags
*/

enum {
                                        /* these are obsolete, were never implemented:*/
                                        /*    kAudioUnitRenderAction_Accumulate         = (1 << 0),*/
                                        /*    kAudioUnitRenderAction_UseProvidedBuffer   = (1 << 1),*/
  kAudioUnitRenderAction_PreRender = (1 << 2),
  kAudioUnitRenderAction_PostRender = (1 << 3),
  kAudioUnitRenderAction_OutputIsSilence = (1 << 4), /* provides hint on return from Render(): if set the buffer contains all zeroes*/
  kAudioOfflineUnitRenderAction_Preflight = (1 << 5),
  kAudioOfflineUnitRenderAction_Render = (1 << 6),
  kAudioOfflineUnitRenderAction_Complete = (1 << 7)
};

typedef UInt32                          AudioUnitRenderActionFlags;
/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   Errors
*/
enum {
  kAudioUnitErr_InvalidProperty = -10879,
  kAudioUnitErr_InvalidParameter = -10878,
  kAudioUnitErr_InvalidElement  = -10877,
  kAudioUnitErr_NoConnection    = -10876,
  kAudioUnitErr_FailedInitialization = -10875,
  kAudioUnitErr_TooManyFramesToProcess = -10874,
  kAudioUnitErr_IllegalInstrument = -10873,
  kAudioUnitErr_InstrumentTypeNotFound = -10872,
  kAudioUnitErr_InvalidFile     = -10871,
  kAudioUnitErr_UnknownFileType = -10870,
  kAudioUnitErr_FileNotSpecified = -10869,
  kAudioUnitErr_FormatNotSupported = -10868,
  kAudioUnitErr_Uninitialized   = -10867,
  kAudioUnitErr_InvalidScope    = -10866,
  kAudioUnitErr_PropertyNotWritable = -10865,
  kAudioUnitErr_InvalidPropertyValue = -10851,
  kAudioUnitErr_PropertyNotInUse = -10850,
  kAudioUnitErr_Initialized     = -10849, /*returned if the operation cannot be performed because the AU is initialized*/
  kAudioUnitErr_InvalidOfflineRender = -10848,
  kAudioUnitErr_Unauthorized    = -10847
};

/*
   same error code but different calling context
   as kAUGraphErr_CannotDoInCurrentContext  
*/
enum {
  kAudioUnitErr_CannotDoInCurrentContext = -10863
};

/*
   Special note:
   A value of 0xFFFFFFFF should never be used for a real scope, paramID or element
   as this value is reserved for use with the AUParameterListener APIs to do wild card searches
   Apple reserves the range of 0->1024 for Specifying Scopes..., any custom scope values should
   lie outside of this range.
*/
typedef UInt32                          AudioUnitPropertyID;
typedef UInt32                          AudioUnitParameterID;
typedef UInt32                          AudioUnitScope;
typedef UInt32                          AudioUnitElement;
/*
   these are actually not used in the AudioUnit framework, but are used by AudioUnit/AudioUnitCarbonView
   and AudioToolbox/AudioUnitUtilities.
*/
struct AudioUnitParameter {
  AudioUnit           mAudioUnit;
  AudioUnitParameterID  mParameterID;
  AudioUnitScope      mScope;
  AudioUnitElement    mElement;
};
typedef struct AudioUnitParameter       AudioUnitParameter;
struct AudioUnitProperty {
  AudioUnit           mAudioUnit;
  AudioUnitPropertyID  mPropertyID;
  AudioUnitScope      mScope;
  AudioUnitElement    mElement;
};
typedef struct AudioUnitProperty        AudioUnitProperty;
typedef CALLBACK_API_C( OSStatus , AURenderCallback )(void *inRefCon, AudioUnitRenderActionFlags *ioActionFlags, const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber, UInt32 inNumberFrames, AudioBufferList *ioData);
typedef CALLBACK_API_C( void , AudioUnitPropertyListenerProc )(void *inRefCon, AudioUnit ci, AudioUnitPropertyID inID, AudioUnitScope inScope, AudioUnitElement inElement);
EXTERN_API( ComponentResult )
AudioUnitInitialize(AudioUnit ci)                             FIVEWORDINLINE(0x2F3C, 0x0000, 0x0001, 0x7000, 0xA82A);


EXTERN_API( ComponentResult )
AudioUnitUninitialize(AudioUnit ci)                           FIVEWORDINLINE(0x2F3C, 0x0000, 0x0002, 0x7000, 0xA82A);



EXTERN_API( ComponentResult )
AudioUnitGetPropertyInfo(
  AudioUnit             ci,
  AudioUnitPropertyID   inID,
  AudioUnitScope        inScope,
  AudioUnitElement      inElement,
  UInt32 *              outDataSize,
  Boolean *             outWritable)                          FIVEWORDINLINE(0x2F3C, 0x0014, 0x0003, 0x7000, 0xA82A);



/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   can pass in NULL for outData, to determine how much memory to allocate
   for variable size properties...
   ioDataSize must be a pointer to a UInt32 value containing the size of the expected
   result.  Upon return this value will contain the real size copied.
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
EXTERN_API( ComponentResult )
AudioUnitGetProperty(
  AudioUnit             ci,
  AudioUnitPropertyID   inID,
  AudioUnitScope        inScope,
  AudioUnitElement      inElement,
  void *                outData,
  UInt32 *              ioDataSize)                           FIVEWORDINLINE(0x2F3C, 0x0014, 0x0004, 0x7000, 0xA82A);



EXTERN_API( ComponentResult )
AudioUnitSetProperty(
  AudioUnit             ci,
  AudioUnitPropertyID   inID,
  AudioUnitScope        inScope,
  AudioUnitElement      inElement,
  const void *          inData,
  UInt32                inDataSize)                           FIVEWORDINLINE(0x2F3C, 0x0014, 0x0005, 0x7000, 0xA82A);



EXTERN_API( ComponentResult )
AudioUnitAddPropertyListener(
  AudioUnit                       ci,
  AudioUnitPropertyID             inID,
  AudioUnitPropertyListenerProc   inProc,
  void *                          inProcRefCon)               FIVEWORDINLINE(0x2F3C, 0x000C, 0x000A, 0x7000, 0xA82A);


EXTERN_API( ComponentResult )
AudioUnitRemovePropertyListener(
  AudioUnit                       ci,
  AudioUnitPropertyID             inID,
  AudioUnitPropertyListenerProc   inProc)                     FIVEWORDINLINE(0x2F3C, 0x0008, 0x000B, 0x7000, 0xA82A);



EXTERN_API( ComponentResult )
AudioUnitAddRenderNotify(
  AudioUnit          ci,
  AURenderCallback   inProc,
  void *             inProcRefCon)                            FIVEWORDINLINE(0x2F3C, 0x0008, 0x000F, 0x7000, 0xA82A);


EXTERN_API( ComponentResult )
AudioUnitRemoveRenderNotify(
  AudioUnit          ci,
  AURenderCallback   inProc,
  void *             inProcRefCon)                            FIVEWORDINLINE(0x2F3C, 0x0008, 0x0010, 0x7000, 0xA82A);


EXTERN_API( ComponentResult )
AudioUnitGetParameter(
  AudioUnit              ci,
  AudioUnitParameterID   inID,
  AudioUnitScope         inScope,
  AudioUnitElement       inElement,
  Float32 *              outValue)                            FIVEWORDINLINE(0x2F3C, 0x0010, 0x0006, 0x7000, 0xA82A);



EXTERN_API( ComponentResult )
AudioUnitSetParameter(
  AudioUnit              ci,
  AudioUnitParameterID   inID,
  AudioUnitScope         inScope,
  AudioUnitElement       inElement,
  Float32                inValue,
  UInt32                 inBufferOffsetInFrames)              FIVEWORDINLINE(0x2F3C, 0x0014, 0x0007, 0x7000, 0xA82A);


enum {
  kParameterEvent_Immediate     = 1,
  kParameterEvent_Ramped        = 2
};


typedef UInt32                          AUParameterEventType;
struct AudioUnitParameterEvent {
  AudioUnitScope      scope;
  AudioUnitElement    element;
  AudioUnitParameterID  parameter;

  AUParameterEventType  eventType;

  union {
    struct {
      SInt32              startBufferOffset;
      UInt32              durationInFrames;
      Float32             startValue;
      Float32             endValue;
    }                       ramp;

    struct {
      UInt32              bufferOffset;
      Float32             value;
    }                       immediate;

  }                       eventValues;
};
typedef struct AudioUnitParameterEvent  AudioUnitParameterEvent;
EXTERN_API( ComponentResult )
AudioUnitScheduleParameters(
  AudioUnit                        ci,
  const AudioUnitParameterEvent *  inParameterEvent,
  UInt32                           inNumParamEvents)          FIVEWORDINLINE(0x2F3C, 0x0008, 0x0011, 0x7000, 0xA82A);



EXTERN_API( ComponentResult )
AudioUnitRender(
  AudioUnit                     ci,
  AudioUnitRenderActionFlags *  ioActionFlags,
  const AudioTimeStamp *        inTimeStamp,
  UInt32                        inOutputBusNumber,
  UInt32                        inNumberFrames,
  AudioBufferList *             ioData)                       FIVEWORDINLINE(0x2F3C, 0x0014, 0x000E, 0x7000, 0xA82A);


EXTERN_API( ComponentResult )
AudioUnitReset(
  AudioUnit          ci,
  AudioUnitScope     inScope,
  AudioUnitElement   inElement)                               FIVEWORDINLINE(0x2F3C, 0x0008, 0x0009, 0x7000, 0xA82A);





/* UPP call backs */

/* selectors for component calls */
enum {
    kAudioUnitInitializeSelect                 = 0x0001,
    kAudioUnitUninitializeSelect               = 0x0002,
    kAudioUnitGetPropertyInfoSelect            = 0x0003,
    kAudioUnitGetPropertySelect                = 0x0004,
    kAudioUnitSetPropertySelect                = 0x0005,
    kAudioUnitAddPropertyListenerSelect        = 0x000A,
    kAudioUnitRemovePropertyListenerSelect     = 0x000B,
    kAudioUnitAddRenderNotifySelect            = 0x000F,
    kAudioUnitRemoveRenderNotifySelect         = 0x0010,
    kAudioUnitGetParameterSelect               = 0x0006,
    kAudioUnitSetParameterSelect               = 0x0007,
    kAudioUnitScheduleParametersSelect         = 0x0011,
    kAudioUnitRenderSelect                     = 0x000E,
    kAudioUnitResetSelect                      = 0x0009
};
/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   Define some function pointers for the functions where performance is an issue.
   Use the kAudioUnitProperty_FastDispatch property to get a function pointer
   pointing directly to our implementation to avoid the cost of dispatching
   through the Component Manager.
*/

typedef CALLBACK_API_C( ComponentResult , AudioUnitGetParameterProc )(void *inComponentStorage, AudioUnitParameterID inID, AudioUnitScope inScope, AudioUnitElement inElement, Float32 *outValue);
typedef CALLBACK_API_C( ComponentResult , AudioUnitSetParameterProc )(void *inComponentStorage, AudioUnitParameterID inID, AudioUnitScope inScope, AudioUnitElement inElement, Float32 inValue, UInt32 inBufferOffsetInFrames);
typedef CALLBACK_API_C( ComponentResult , AudioUnitRenderProc )(void *inComponentStorage, AudioUnitRenderActionFlags *ioActionFlags, const AudioTimeStamp *inTimeStamp, UInt32 inOutputBusNumber, UInt32 inNumberFrames, AudioBufferList *ioData);


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

#endif /* __AUCOMPONENT__ */

