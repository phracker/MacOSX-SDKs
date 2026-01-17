/*
     File:       MusicDevice.h
 
     Contains:   MusicDevice Interfaces
 
     Version:    Technology: System 9
                 Release:    Mac OS X
 
     Copyright:  (c) 2000 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
/*.#endif forMasterInterfaces*/
/*.#ifndef forMergedInterfaces*/
#ifndef __MUSICDEVICE__
#define __MUSICDEVICE__

#include <AudioUnit/AudioUnit.h>


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

/*.#endif forMergedInterfaces*/

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



/*
   it's possible to call AudioUnitGetProperty(kMusicDeviceProperty_InstrumentName, instrumentID) to
   get the instrument name 
*/
typedef UInt32                          MusicDeviceInstrumentID;
/* "varargs" structure for passing parameters to MusicDevice instruments*/

struct MusicDeviceNoteParams {
  UInt32              argCount;
  float               args[1];
};
typedef struct MusicDeviceNoteParams    MusicDeviceNoteParams;
typedef MusicDeviceNoteParams *         MusicDeviceNoteParamsPtr;
/* this is normally used for packing in MIDI note params (note number, velocity)*/

struct MusicDeviceNoteParams3 {
  UInt32              argCount;
  float               args[3];
};
typedef struct MusicDeviceNoteParams3   MusicDeviceNoteParams3;

struct MusicDeviceNoteParams16 {
  UInt32              argCount;
  float               args[16];
};
typedef struct MusicDeviceNoteParams16  MusicDeviceNoteParams16;

typedef UInt32                          MusicDeviceGroupID;
typedef UInt32                          NoteInstanceID;
typedef ComponentInstance               MusicDeviceComponent;
/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        two sets of event API's (MIDI and extended ):
            - the MIDI API's address the device using the standardized MIDI semantics
                    MusicDeviceMIDIEvent()
                    MusicDeviceSysEx()
            - the extended API's allow more sophisticated control of notes, but would
                not be available for all MusicDevices (external MIDI devices)
                    MusicDeviceStartNote()
                    MusicDeviceStopNote()
                    AudioUnitSetParameter()   (for group control changes...)
*/

/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   any arbitrary MIDI event should be possible with MusicDeviceMIDIEvent() and MusicDeviceSysEx(),
   and they MUST be implemented by the MusicDevice developer
*/

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
  UInt8 *                inData,
  UInt32                 inLength)                            FIVEWORDINLINE(0x2F3C, 0x0008, 0x0102, 0x7000, 0xA82A);




/*
   allows MusicDevice to prepare the instrument for play (loading any required resources,
   for example, sample data from hard-disk)
*/
EXTERN_API( ComponentResult )
MusicDevicePrepareInstrument(
  MusicDeviceComponent      ci,
  MusicDeviceInstrumentID   inInstrument)                     FIVEWORDINLINE(0x2F3C, 0x0004, 0x0103, 0x7000, 0xA82A);


/* allows MusicDevice to release any resources used by the instrument*/
EXTERN_API( ComponentResult )
MusicDeviceReleaseInstrument(
  MusicDeviceComponent      ci,
  MusicDeviceInstrumentID   inInstrument)                     FIVEWORDINLINE(0x2F3C, 0x0004, 0x0104, 0x7000, 0xA82A);


/* */
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




/*.#ifndef forMergedInterfaces*/

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

/*.#endif forMergedInterfaces*/

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

