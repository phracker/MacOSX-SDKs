/*
     File:       AudioUnit.h
 
     Contains:   AudioUnit Interfaces
 
     Version:    Technology: System 9, X
                 Release:    Mac OS X
 
     Copyright:  © 2000-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
/*·#endif forMasterInterfaces*/
/*·#ifndef forMergedInterfaces*/
#ifndef __AUDIOUNIT__
#define __AUDIOUNIT__

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

/*·#endif forMergedInterfaces*/




/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   ranges
*/

enum {
  kAudioUnitRange               = 0x0000
};

/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   AudioUnit stuff
*/

typedef ComponentInstance               AudioUnit;
/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   AudioUnit component types and subtypes
*/
enum {
  kAudioUnitComponentType       = FOUR_CHAR_CODE('aunt'),
  kAudioUnitSubType_Output      = FOUR_CHAR_CODE('out '),
  kAudioUnitID_HALOutput        = FOUR_CHAR_CODE('ahal'),
  kAudioUnitID_DefaultOutput    = FOUR_CHAR_CODE('def '),
  kAudioUnitID_SystemOutput     = FOUR_CHAR_CODE('sys '),
  kAudioUnitSubType_MusicDevice = FOUR_CHAR_CODE('musd'),
  kAudioUnitID_DLSSynth         = FOUR_CHAR_CODE('dls '),
  kAudioUnitSubType_Encoder     = FOUR_CHAR_CODE('aenc'),
  kAudioUnitSubType_Decoder     = FOUR_CHAR_CODE('adec'),
  kAudioUnitSubType_SampleRateConverter = FOUR_CHAR_CODE('srcv'),
  kAudioUnitID_PolyphaseSRC     = FOUR_CHAR_CODE('poly'),
  kAudioUnitSubType_FormatConverter = FOUR_CHAR_CODE('fmtc'),
  kAudioUnitID_Interleaver      = FOUR_CHAR_CODE('inlv'),
  kAudioUnitID_Deinterleaver    = FOUR_CHAR_CODE('dnlv'),
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
  kAudioUnitSubType_Adapter     = FOUR_CHAR_CODE('adpt')
};

/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   Render flags
*/


enum {
  kAudioUnitRenderAction_Accumulate = (1 << 0),
  kAudioUnitRenderAction_UseProvidedBuffer = (1 << 1),
  kAudioUnitRenderAction_PreRender = (1 << 2),
  kAudioUnitRenderAction_PostRender = (1 << 3)
};

typedef UInt32                          AudioUnitRenderActionFlags;
/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
  kAudioUnitErr_Uninitialized   = -10867
};


/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   Properties
*/

enum {
  kAudioUnitScope_Global        = 0,
  kAudioUnitScope_Input         = 1,
  kAudioUnitScope_Output        = 2,
  kAudioUnitScope_Group         = 3
};

typedef UInt32                          AudioUnitPropertyID;
typedef UInt32                          AudioUnitParameterID;
typedef UInt32                          AudioUnitScope;
typedef UInt32                          AudioUnitElement;
/*
    This is a callback that an AudioUnit can make from its RenderSlice function.
    It can be used as a RenderNotify callback for the owner (usually the AUGraph)
    to get called back before and after rendering.
    
    It can also be used as an InputCallback to provide a buffer of audio input
    to one of the AudioUnit's inputs.
    
    Essentially the same arguments that are passed to AudioUnitRenderSlice() are
    passed on to the callback here.
 */
typedef CALLBACK_API_C( OSStatus , AudioUnitRenderCallback )(void *inRefCon, AudioUnitRenderActionFlags inActionFlags, const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber, AudioBuffer *ioData);
typedef CALLBACK_API_C( void , AudioUnitPropertyListenerProc )(void *inRefCon, AudioUnit ci, AudioUnitPropertyID inID, AudioUnitScope inScope, AudioUnitElement inElement);
/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Initialization
        No substantial allocation of resources should occur when the AudioUnit component
        is opened.  Instead, only access to basic properties is allowed.  To fully
        initialize the AudioUnit, call AudioUnitInitialize().
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

EXTERN_API( ComponentResult )
AudioUnitInitialize(AudioUnit ci)                             FIVEWORDINLINE(0x2F3C, 0x0000, 0x0001, 0x7000, 0xA82A);


EXTERN_API( ComponentResult )
AudioUnitUninitialize(AudioUnit ci)                           FIVEWORDINLINE(0x2F3C, 0x0000, 0x0002, 0x7000, 0xA82A);




/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Property Management
    Properties describe or control some aspect of an AudioUnit that does
    not vary in time. Properties are addressed via their ID, scope, and
    element. The ID identifies the property and describes the structure of
    its data. The scope identifies the functional area of the AudioUnit
    of interest. The element identifies the specific part of the scope of
    interest.
    Examples of properties include user readable names, stream format, data
    sources, and one shot configuration information.
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

EXTERN_API( ComponentResult )
AudioUnitGetPropertyInfo(
  AudioUnit             ci,
  AudioUnitPropertyID   inID,
  AudioUnitScope        inScope,
  AudioUnitElement      inElement,
  UInt32 *              outDataSize,
  Boolean *             outWritable)                          FIVEWORDINLINE(0x2F3C, 0x0014, 0x0003, 0x7000, 0xA82A);



/*
   can pass in NULL for outData, to determine how much memory to allocate
   for variable size properties...
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
  void *                inData,
  UInt32                inDataSize)                           FIVEWORDINLINE(0x2F3C, 0x0014, 0x0005, 0x7000, 0xA82A);




EXTERN_API( ComponentResult )
AudioUnitSetRenderNotification(
  AudioUnit                 ci,
  AudioUnitRenderCallback   inProc,
  void *                    inProcRefCon)                     FIVEWORDINLINE(0x2F3C, 0x0008, 0x000C, 0x7000, 0xA82A);


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


/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Parameter Management
    Parameters control a specific aspect of the processing of an AudioUnit
    that can vary in time. Further, parameters are represented as single
    floating point values. Parameters are addressed by their ID, scope
    and element similar to properties.
    Since parameters vary in time, AudioUnits must support some notion of
    scheduling. That said, it is not the intent of this API to force an
    AudioUnit to support full blown scheduling and history. It is assumed
    that the general workload of an AudioUnit's scheduler will revolve around
    scheduling events at most a few buffers into the future. Further, the event
    density is generally expected to be light. Therefore, the client of an
    AudioUnit should take care in the number of events it schedules as it
    could drastically affect performance.
    Examples of parameters include volume, panning, filter cutoff, delay time
    LFO spead, rate multiplier, etc.
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

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




/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    IO Management
    AudioUnits use a pull IO model. A unit specifies through its properties
    the number and format of its inputs and ouputs. Each output is in itself a
    whole stream of N interleaved audio channels. Connections between units
    are also managed via properties. This means that the only routines necessary
    are the ones to specify how to get data out of a specific output (AudioUnitRenderSlice() )
    The inActionFlags parameter tells the unit additional operations to
    perform:
        kAudioUnitRenderAction_Accumulate
            The unit should sum its output into the given buffer, rather
            than replace it. This action is only valid for formats that
            support easy stream mixing like linear PCM. Further, a buffer
            will always be supplied.
        kAudioUnitRenderAction_UseProvidedBuffer
            This flag indicates that the rendered audio must be placed in the
            buffer pointed to by the mData member of the ioData argument passed
            into AudioUnitRenderSlice().  In this case mData must, of course, point to a valid
            piece of allocated memory.  If this flag is not set, then the mData
            member of ioData may possibly be changed upon return from AudioUnitRenderSlice(),
            pointing to a different buffer (owned by the AudioUnit ).
            In any case, upon return from AudioUnitRenderSlice(), mData points to
            the rendered audio.
    The inTimeStamp parameter gives the AudioUnit information about what the time
    is for the start of the rendered audio output.
    The inOutputBusNumber parameter requests that audio be rendered for a particular
    audio output of the AudioUnit.  AudioUnitRenderSlice() must be called separately
    to get rendered audio for each of its outputs.  The AudioUnit is expected to cache
    its rendered audio for each output in the case that AudioUnitRenderSlice() is called
    more than once for the same output (inOutputBusNumber is the same) at the same time
    (inTimeStamp is the same).  This solves the "fanout" problem.
    The ioData parameter is of special note.  The client must pass a pointer to a
    AudioBuffer structure filled out completely.  If the ioData mData member is NULL,
    then AudioUnitRenderSlice()
    will set mData to a buffer owned by the AudioUnit.  Or, the client
    may pass in his own buffer to render to if the mData member is non-NULL.
    In any case, when AudioUnitRenderSlice() returns, the mData value points to the buffer data
    where audio was rendered for the given audio output bus.
    See also, the description for the kAudioUnitRenderAction_UseProvidedBuffer flag.
    
    The audio data in a buffer can be in an arbitrary format, but mono 32bit floating point 
    is the "canonical" form used by most AudioUnits for a single output.  If using the
    canonical output format, then stereo may be implemented as two AudioUnit outputs
    (each mono 32bit floating point).
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/


EXTERN_API( ComponentResult )
AudioUnitRenderSlice(
  AudioUnit                    ci,
  AudioUnitRenderActionFlags   inActionFlags,
  const AudioTimeStamp *       inTimeStamp,
  UInt32                       inOutputBusNumber,
  AudioBuffer *                ioData)                        FIVEWORDINLINE(0x2F3C, 0x0010, 0x0008, 0x7000, 0xA82A);



/* if scope is global then reinitializes a device to its "default" state*/
EXTERN_API( ComponentResult )
AudioUnitReset(
  AudioUnit          ci,
  AudioUnitScope     inScope,
  AudioUnitElement   inElement)                               FIVEWORDINLINE(0x2F3C, 0x0008, 0x0009, 0x7000, 0xA82A);




/*·#ifndef forMergedInterfaces*/

/* UPP call backs */

/* selectors for component calls */
enum {
    kAudioUnitInitializeSelect                 = 0x0001,
    kAudioUnitUninitializeSelect               = 0x0002,
    kAudioUnitGetPropertyInfoSelect            = 0x0003,
    kAudioUnitGetPropertySelect                = 0x0004,
    kAudioUnitSetPropertySelect                = 0x0005,
    kAudioUnitSetRenderNotificationSelect      = 0x000C,
    kAudioUnitAddPropertyListenerSelect        = 0x000A,
    kAudioUnitRemovePropertyListenerSelect     = 0x000B,
    kAudioUnitGetParameterSelect               = 0x0006,
    kAudioUnitSetParameterSelect               = 0x0007,
    kAudioUnitRenderSliceSelect                = 0x0008,
    kAudioUnitResetSelect                      = 0x0009
};
/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   Let's define some function pointers for the functions where performance is an issue.
   We can use our kAudioUnitProperty_FastDispatch property to get a function pointer
   pointing directly to our implementation to avoid the sometimes high cost of dispatching
   through the Component Manager.
*/

typedef CALLBACK_API_C( ComponentResult , AudioUnitGetParameterProc )(void *inComponentStorage, AudioUnitParameterID inID, AudioUnitScope inScope, AudioUnitElement inElement, Float32 *outValue);
typedef CALLBACK_API_C( ComponentResult , AudioUnitSetParameterProc )(void *inComponentStorage, AudioUnitParameterID inID, AudioUnitScope inScope, AudioUnitElement inElement, Float32 inValue, UInt32 inBufferOffsetInFrames);
typedef CALLBACK_API_C( ComponentResult , AudioUnitRenderSliceProc )(void *inComponentStorage, AudioUnitRenderActionFlags inActionFlags, const AudioTimeStamp *inTimeStamp, UInt32 inOutputBusNumber, AudioBuffer *ioData);
/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   Finally, at the end, let's be nice and define all of our standard properties and parameters
*/
#include <AudioUnit/AudioUnitProperties.h>
#include <AudioUnit/MusicDevice.h>
#include <AudioUnit/AudioOutputUnit.h>


/*·#endif forMergedInterfaces*/

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

#endif /* __AUDIOUNIT__ */

