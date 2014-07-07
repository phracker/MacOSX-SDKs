/*
     File:       MusicDevice.h
 
     Contains:   MusicDevice Interfaces
 
     Version:    Mac OS X
 
     Copyright:  © 2000-2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __MUSICDEVICE__
#define __MUSICDEVICE__

#include <CoreServices/CoreServices.h>
#include <AudioUnit/AUComponent.h>
#include <CoreAudio/CoreAudio.h>


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
   A music device can control far more independent instruments than the 16 channels of MIDI
   through the use of the extended APIs. AudioUnitSetParameter is used with the kAudioUnitScope_Group
   to use this extended control facilities. See documentation for further details.
*/


/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   ranges
*/

enum {
  kMusicDeviceRange             = 0x0100
};

/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   MusicDevice types and structures
*/



typedef UInt32                          MusicDeviceInstrumentID;
/* this is normally used for packing in MIDI note params (note number, velocity)*/
struct MusicDeviceStdNoteParams {
  UInt32              argCount;               /* should be 2*/
  Float32             mPitch;
  Float32             mVelocity;
};
typedef struct MusicDeviceStdNoteParams MusicDeviceStdNoteParams;
struct NoteParamsControlValue {
  UInt32              mID;
  Float32             mValue;
};
typedef struct NoteParamsControlValue   NoteParamsControlValue;
/*
   This is the official structure that should be used as the
   const MusicDeviceNoteParams  *inParams
   argument with MusicDeviceStartNote
*/
/*
   This argument has 2 flavours
   (1) MusicDeviceStdNoteParams
    - where argCount is 2, and the first argument is pitch (defined as 0 < 128 MIDI NoteNum), 
    the second velocity (0 < 128)
*/

/*
   (2) ExtendedNoteParams
    - where argCount is 2 + the number of contained NoteParamsControlValue structures
   - so the size of the mControls array is (argCount - 2)
*/

struct MusicDeviceNoteParams {
  UInt32              argCount;
  Float32             mPitch;
  Float32             mVelocity;
  NoteParamsControlValue  mControls[1];       /*arbitrary lengh*/
};
typedef struct MusicDeviceNoteParams    MusicDeviceNoteParams;
/*
   The instrumentID that is passed in to the MusicDeviceStartNote can specify a specific intrument ID.
   The constant kMusicNoteEvent_UseGroupInstrument can alternatively be passed to use the 
   current instrument defined for that group. In MIDI this is the typical usage of a bank
   and patch set for a specific channel where all notes that start on that channel use that instrument.
*/
enum {
  kMusicNoteEvent_UseGroupInstrument = (long)0xFFFFFFFF
};


typedef UInt32                          MusicDeviceGroupID;
typedef UInt32                          NoteInstanceID;
typedef ComponentInstance               MusicDeviceComponent;
EXTERN_API( ComponentResult )
MusicDeviceMIDIEvent(
  MusicDeviceComponent   ci,
  UInt32                 inStatus,
  UInt32                 inData1,
  UInt32                 inData2,
  UInt32                 inOffsetSampleFrame)                 FIVEWORDINLINE(0x2F3C, 0x0010, 0x0101, 0x7000, 0xA82A);



EXTERN_API( ComponentResult )
MusicDeviceSysEx(
  MusicDeviceComponent   ci,
  const UInt8 *          inData,
  UInt32                 inLength)                            FIVEWORDINLINE(0x2F3C, 0x0008, 0x0102, 0x7000, 0xA82A);


EXTERN_API( ComponentResult )
MusicDevicePrepareInstrument(
  MusicDeviceComponent      ci,
  MusicDeviceInstrumentID   inInstrument)                     FIVEWORDINLINE(0x2F3C, 0x0004, 0x0103, 0x7000, 0xA82A);


EXTERN_API( ComponentResult )
MusicDeviceReleaseInstrument(
  MusicDeviceComponent      ci,
  MusicDeviceInstrumentID   inInstrument)                     FIVEWORDINLINE(0x2F3C, 0x0004, 0x0104, 0x7000, 0xA82A);


EXTERN_API( ComponentResult )
MusicDeviceStartNote(
  MusicDeviceComponent           ci,
  MusicDeviceInstrumentID        inInstrument,
  MusicDeviceGroupID             inGroupID,
  NoteInstanceID *               outNoteInstanceID,
  UInt32                         inOffsetSampleFrame,
  const MusicDeviceNoteParams *  inParams)                    FIVEWORDINLINE(0x2F3C, 0x0014, 0x0105, 0x7000, 0xA82A);


EXTERN_API( ComponentResult )
MusicDeviceStopNote(
  MusicDeviceComponent   ci,
  MusicDeviceGroupID     inGroupID,
  NoteInstanceID         inNoteInstanceID,
  UInt32                 inOffsetSampleFrame)                 FIVEWORDINLINE(0x2F3C, 0x000C, 0x0106, 0x7000, 0xA82A);





/* UPP call backs */

/* selectors for component calls */
enum {
    kMusicDeviceMIDIEventSelect                = 0x0101,
    kMusicDeviceSysExSelect                    = 0x0102,
    kMusicDevicePrepareInstrumentSelect        = 0x0103,
    kMusicDeviceReleaseInstrumentSelect        = 0x0104,
    kMusicDeviceStartNoteSelect                = 0x0105,
    kMusicDeviceStopNoteSelect                 = 0x0106
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

#endif /* __MUSICDEVICE__ */

