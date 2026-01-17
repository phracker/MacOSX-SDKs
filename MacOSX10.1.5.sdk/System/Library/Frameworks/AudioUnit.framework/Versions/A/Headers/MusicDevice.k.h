/*
     File:       MusicDevice.k.h
 
     Contains:   MusicDevice Interfaces
 
     Version:    Technology: System 9
                 Release:    Mac OS X
 
     Copyright:  © 2000 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __MUSICDEVICE_K__
#define __MUSICDEVICE_K__

#include <MusicDevice.h>

/*
	Example usage:

		#define MUSICDEVICE_BASENAME()	Fred
		#define MUSICDEVICE_GLOBALS()	FredGlobalsHandle
		#include <MusicDevice.k.h>

	To specify that your component implementation does not use globals, do not #define MUSICDEVICE_GLOBALS
*/
#ifdef MUSICDEVICE_BASENAME
	#ifndef MUSICDEVICE_GLOBALS
		#define MUSICDEVICE_GLOBALS() 
		#define ADD_MUSICDEVICE_COMMA 
	#else
		#define ADD_MUSICDEVICE_COMMA ,
	#endif
	#define MUSICDEVICE_GLUE(a,b) a##b
	#define MUSICDEVICE_STRCAT(a,b) MUSICDEVICE_GLUE(a,b)
	#define ADD_MUSICDEVICE_BASENAME(name) MUSICDEVICE_STRCAT(MUSICDEVICE_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_MUSICDEVICE_BASENAME(MIDIEvent) (MUSICDEVICE_GLOBALS() ADD_MUSICDEVICE_COMMA UInt32  inStatus, UInt32  inData1, UInt32  inData2, UInt32  inOffsetSampleFrame);

	EXTERN_API( ComponentResult  ) ADD_MUSICDEVICE_BASENAME(SysEx) (MUSICDEVICE_GLOBALS() ADD_MUSICDEVICE_COMMA UInt8 * inData, UInt32  inLength);

	EXTERN_API( ComponentResult  ) ADD_MUSICDEVICE_BASENAME(PrepareInstrument) (MUSICDEVICE_GLOBALS() ADD_MUSICDEVICE_COMMA MusicDeviceInstrumentID  inInstrument);

	EXTERN_API( ComponentResult  ) ADD_MUSICDEVICE_BASENAME(ReleaseInstrument) (MUSICDEVICE_GLOBALS() ADD_MUSICDEVICE_COMMA MusicDeviceInstrumentID  inInstrument);

	EXTERN_API( ComponentResult  ) ADD_MUSICDEVICE_BASENAME(StartNote) (MUSICDEVICE_GLOBALS() ADD_MUSICDEVICE_COMMA MusicDeviceInstrumentID  inInstrument, MusicDeviceGroupID  inGroupID, NoteInstanceID * outNoteInstanceID, UInt32  inOffsetSampleFrame, const MusicDeviceNoteParams * inParams);

	EXTERN_API( ComponentResult  ) ADD_MUSICDEVICE_BASENAME(StopNote) (MUSICDEVICE_GLOBALS() ADD_MUSICDEVICE_COMMA MusicDeviceGroupID  inGroupID, NoteInstanceID  inNoteInstanceID, UInt32  inOffsetSampleFrame);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppMusicDeviceMIDIEventProcInfo = 0x0000FFF0,
		uppMusicDeviceSysExProcInfo = 0x00000FF0,
		uppMusicDevicePrepareInstrumentProcInfo = 0x000003F0,
		uppMusicDeviceReleaseInstrumentProcInfo = 0x000003F0,
		uppMusicDeviceStartNoteProcInfo = 0x0003FFF0,
		uppMusicDeviceStopNoteProcInfo = 0x00003FF0
	};

#endif	/* MUSICDEVICE_BASENAME */


#endif /* __MUSICDEVICE_K__ */

