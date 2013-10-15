/*
     File:       QuickTimeMusic.k.h
 
     Contains:   QuickTime Interfaces.
 
     Version:    QuickTime 7.2.1
 
     Copyright:  © 1990-2006 by Apple Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __QUICKTIMEMUSIC_K__
#define __QUICKTIMEMUSIC_K__

#include <QuickTime/QuickTimeMusic.h>
/*
	Example usage:

		#define QTMIDI_BASENAME()	Fred
		#define QTMIDI_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeMusic.k.h>

	To specify that your component implementation does not use globals, do not #define QTMIDI_GLOBALS
*/
#ifdef QTMIDI_BASENAME
	#ifndef QTMIDI_GLOBALS
		#define QTMIDI_GLOBALS() 
		#define ADD_QTMIDI_COMMA 
	#else
		#define ADD_QTMIDI_COMMA ,
	#endif
	#define QTMIDI_GLUE(a,b) a##b
	#define QTMIDI_STRCAT(a,b) QTMIDI_GLUE(a,b)
	#define ADD_QTMIDI_BASENAME(name) QTMIDI_STRCAT(QTMIDI_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_QTMIDI_BASENAME(GetMIDIPorts) (QTMIDI_GLOBALS() ADD_QTMIDI_COMMA QTMIDIPortListHandle * inputPorts, QTMIDIPortListHandle * outputPorts);

	EXTERN_API( ComponentResult  ) ADD_QTMIDI_BASENAME(UseSendPort) (QTMIDI_GLOBALS() ADD_QTMIDI_COMMA long  portIndex, long  inUse);

	EXTERN_API( ComponentResult  ) ADD_QTMIDI_BASENAME(SendMIDI) (QTMIDI_GLOBALS() ADD_QTMIDI_COMMA long  portIndex, MusicMIDIPacket * mp);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppQTMIDIGetMIDIPortsProcInfo = 0x00000FF0,
		uppQTMIDIUseSendPortProcInfo = 0x00000FF0,
		uppQTMIDISendMIDIProcInfo = 0x00000FF0
	};

#endif	/* QTMIDI_BASENAME */

/*
	Example usage:

		#define MUSIC_BASENAME()	Fred
		#define MUSIC_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeMusic.k.h>

	To specify that your component implementation does not use globals, do not #define MUSIC_GLOBALS
*/
#ifdef MUSIC_BASENAME
	#ifndef MUSIC_GLOBALS
		#define MUSIC_GLOBALS() 
		#define ADD_MUSIC_COMMA 
	#else
		#define ADD_MUSIC_COMMA ,
	#endif
	#define MUSIC_GLUE(a,b) a##b
	#define MUSIC_STRCAT(a,b) MUSIC_GLUE(a,b)
	#define ADD_MUSIC_BASENAME(name) MUSIC_STRCAT(MUSIC_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GetDescription) (MUSIC_GLOBALS() ADD_MUSIC_COMMA SynthesizerDescription * sd);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GetPart) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  part, long * midiChannel, long * polyphony);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(SetPart) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  part, long  midiChannel, long  polyphony);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(SetPartInstrumentNumber) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  part, long  instrumentNumber);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GetPartInstrumentNumber) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  part);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(StorePartInstrument) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  part, long  instrumentNumber);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GetPartAtomicInstrument) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  part, AtomicInstrument * ai, long  flags);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(SetPartAtomicInstrument) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  part, AtomicInstrumentPtr  aiP, long  flags);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GetPartKnob) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  part, long  knobID);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(SetPartKnob) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  part, long  knobID, long  knobValue);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GetKnob) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  knobID);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(SetKnob) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  knobID, long  knobValue);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GetPartName) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  part, StringPtr  name);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(SetPartName) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  part, StringPtr  name);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(FindTone) (MUSIC_GLOBALS() ADD_MUSIC_COMMA ToneDescription * td, long * libraryIndexOut, unsigned long * fit);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(PlayNote) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  part, long  pitch, long  velocity);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(ResetPart) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  part);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(SetPartController) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  part, MusicController  controllerNumber, long  controllerValue);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GetPartController) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  part, MusicController  controllerNumber);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GetMIDIProc) (MUSIC_GLOBALS() ADD_MUSIC_COMMA MusicMIDISendUPP * midiSendProc, long * refCon);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(SetMIDIProc) (MUSIC_GLOBALS() ADD_MUSIC_COMMA MusicMIDISendUPP  midiSendProc, long  refCon);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GetInstrumentNames) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  modifiableInstruments, Handle * instrumentNames, Handle * instrumentCategoryLasts, Handle * instrumentCategoryNames);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GetDrumNames) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  modifiableInstruments, Handle * instrumentNumbers, Handle * instrumentNames);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GetMasterTune) (MUSIC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(SetMasterTune) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  masterTune);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GetInstrumentAboutInfo) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  part, InstrumentAboutInfo * iai);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GetDeviceConnection) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  index, long * id1, long * id2);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(UseDeviceConnection) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  id1, long  id2);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GetKnobSettingStrings) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  knobIndex, long  isGlobal, Handle * settingsNames, Handle * settingsCategoryLasts, Handle * settingsCategoryNames);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GetMIDIPorts) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long * inputPortCount, long * outputPortCount);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(SendMIDI) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  portIndex, MusicMIDIPacket * mp);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(StartOffline) (MUSIC_GLOBALS() ADD_MUSIC_COMMA unsigned long * numChannels, UnsignedFixed * sampleRate, unsigned short * sampleSize, MusicOfflineDataUPP  dataProc, long  dataProcRefCon);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(SetOfflineTimeTo) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  newTimeStamp);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GetInstrumentKnobDescription) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  knobIndex, KnobDescription * mkd);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GetDrumKnobDescription) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  knobIndex, KnobDescription * mkd);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GetKnobDescription) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  knobIndex, KnobDescription * mkd);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GetInfoText) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  selector, Handle * textH, Handle * styleH);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GetInstrumentInfo) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  getInstrumentInfoFlags, InstrumentInfoListHandle * infoListH);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(Task) (MUSIC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(SetPartInstrumentNumberInterruptSafe) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  part, long  instrumentNumber);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(SetPartSoundLocalization) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  part, Handle  data);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GenericConfigure) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  mode, long  flags, long  baseResID);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GenericGetPart) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  partNumber, GCPart ** part);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GenericGetKnobList) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  knobType, GenericKnobDescriptionListHandle * gkdlH);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(GenericSetResourceNumbers) (MUSIC_GLOBALS() ADD_MUSIC_COMMA Handle  resourceIDH);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(DerivedMIDISend) (MUSIC_GLOBALS() ADD_MUSIC_COMMA MusicMIDIPacket * packet);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(DerivedSetKnob) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  knobType, long  knobNumber, long  knobValue, long  partNumber, GCPart * p, GenericKnobDescription * gkd);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(DerivedSetPart) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  partNumber, GCPart * p);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(DerivedSetInstrument) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  partNumber, GCPart * p);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(DerivedSetPartInstrumentNumber) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  partNumber, GCPart * p);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(DerivedSetMIDI) (MUSIC_GLOBALS() ADD_MUSIC_COMMA MusicMIDISendUPP  midiProc, long  refcon, long  midiChannel);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(DerivedStorePartInstrument) (MUSIC_GLOBALS() ADD_MUSIC_COMMA long  partNumber, GCPart * p, long  instrumentNumber);

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(DerivedOpenResFile) (MUSIC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_MUSIC_BASENAME(DerivedCloseResFile) (MUSIC_GLOBALS() ADD_MUSIC_COMMA short  resRefNum);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppMusicGetDescriptionProcInfo = 0x000003F0,
		uppMusicGetPartProcInfo = 0x00003FF0,
		uppMusicSetPartProcInfo = 0x00003FF0,
		uppMusicSetPartInstrumentNumberProcInfo = 0x00000FF0,
		uppMusicGetPartInstrumentNumberProcInfo = 0x000003F0,
		uppMusicStorePartInstrumentProcInfo = 0x00000FF0,
		uppMusicGetPartAtomicInstrumentProcInfo = 0x00003FF0,
		uppMusicSetPartAtomicInstrumentProcInfo = 0x00003FF0,
		uppMusicGetPartKnobProcInfo = 0x00000FF0,
		uppMusicSetPartKnobProcInfo = 0x00003FF0,
		uppMusicGetKnobProcInfo = 0x000003F0,
		uppMusicSetKnobProcInfo = 0x00000FF0,
		uppMusicGetPartNameProcInfo = 0x00000FF0,
		uppMusicSetPartNameProcInfo = 0x00000FF0,
		uppMusicFindToneProcInfo = 0x00003FF0,
		uppMusicPlayNoteProcInfo = 0x00003FF0,
		uppMusicResetPartProcInfo = 0x000003F0,
		uppMusicSetPartControllerProcInfo = 0x00003FF0,
		uppMusicGetPartControllerProcInfo = 0x00000FF0,
		uppMusicGetMIDIProcProcInfo = 0x00000FF0,
		uppMusicSetMIDIProcProcInfo = 0x00000FF0,
		uppMusicGetInstrumentNamesProcInfo = 0x0000FFF0,
		uppMusicGetDrumNamesProcInfo = 0x00003FF0,
		uppMusicGetMasterTuneProcInfo = 0x000000F0,
		uppMusicSetMasterTuneProcInfo = 0x000003F0,
		uppMusicGetInstrumentAboutInfoProcInfo = 0x00000FF0,
		uppMusicGetDeviceConnectionProcInfo = 0x00003FF0,
		uppMusicUseDeviceConnectionProcInfo = 0x00000FF0,
		uppMusicGetKnobSettingStringsProcInfo = 0x0003FFF0,
		uppMusicGetMIDIPortsProcInfo = 0x00000FF0,
		uppMusicSendMIDIProcInfo = 0x00000FF0,
		uppMusicStartOfflineProcInfo = 0x0003FFF0,
		uppMusicSetOfflineTimeToProcInfo = 0x000003F0,
		uppMusicGetInstrumentKnobDescriptionProcInfo = 0x00000FF0,
		uppMusicGetDrumKnobDescriptionProcInfo = 0x00000FF0,
		uppMusicGetKnobDescriptionProcInfo = 0x00000FF0,
		uppMusicGetInfoTextProcInfo = 0x00003FF0,
		uppMusicGetInstrumentInfoProcInfo = 0x00000FF0,
		uppMusicTaskProcInfo = 0x000000F0,
		uppMusicSetPartInstrumentNumberInterruptSafeProcInfo = 0x00000FF0,
		uppMusicSetPartSoundLocalizationProcInfo = 0x00000FF0,
		uppMusicGenericConfigureProcInfo = 0x00003FF0,
		uppMusicGenericGetPartProcInfo = 0x00000FF0,
		uppMusicGenericGetKnobListProcInfo = 0x00000FF0,
		uppMusicGenericSetResourceNumbersProcInfo = 0x000003F0,
		uppMusicDerivedMIDISendProcInfo = 0x000003F0,
		uppMusicDerivedSetKnobProcInfo = 0x000FFFF0,
		uppMusicDerivedSetPartProcInfo = 0x00000FF0,
		uppMusicDerivedSetInstrumentProcInfo = 0x00000FF0,
		uppMusicDerivedSetPartInstrumentNumberProcInfo = 0x00000FF0,
		uppMusicDerivedSetMIDIProcInfo = 0x00003FF0,
		uppMusicDerivedStorePartInstrumentProcInfo = 0x00003FF0,
		uppMusicDerivedOpenResFileProcInfo = 0x000000F0,
		uppMusicDerivedCloseResFileProcInfo = 0x000002F0
	};

#endif	/* MUSIC_BASENAME */

/*
	Example usage:

		#define NA_BASENAME()	Fred
		#define NA_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeMusic.k.h>

	To specify that your component implementation does not use globals, do not #define NA_GLOBALS
*/
#ifdef NA_BASENAME
	#ifndef NA_GLOBALS
		#define NA_GLOBALS() 
		#define ADD_NA_COMMA 
	#else
		#define ADD_NA_COMMA ,
	#endif
	#define NA_GLUE(a,b) a##b
	#define NA_STRCAT(a,b) NA_GLUE(a,b)
	#define ADD_NA_BASENAME(name) NA_STRCAT(NA_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(RegisterMusicDevice) (NA_GLOBALS() ADD_NA_COMMA OSType  synthType, Str31  name, SynthesizerConnections * connections);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(UnregisterMusicDevice) (NA_GLOBALS() ADD_NA_COMMA long  index);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(GetRegisteredMusicDevice) (NA_GLOBALS() ADD_NA_COMMA long  index, OSType * synthType, Str31  name, SynthesizerConnections * connections, MusicComponent * mc);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(SaveMusicConfiguration) (NA_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(NewNoteChannel) (NA_GLOBALS() ADD_NA_COMMA NoteRequest * noteRequest, NoteChannel * outChannel);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(DisposeNoteChannel) (NA_GLOBALS() ADD_NA_COMMA NoteChannel  noteChannel);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(GetNoteChannelInfo) (NA_GLOBALS() ADD_NA_COMMA NoteChannel  noteChannel, long * index, long * part);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(PrerollNoteChannel) (NA_GLOBALS() ADD_NA_COMMA NoteChannel  noteChannel);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(UnrollNoteChannel) (NA_GLOBALS() ADD_NA_COMMA NoteChannel  noteChannel);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(SetNoteChannelVolume) (NA_GLOBALS() ADD_NA_COMMA NoteChannel  noteChannel, Fixed  volume);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(ResetNoteChannel) (NA_GLOBALS() ADD_NA_COMMA NoteChannel  noteChannel);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(PlayNote) (NA_GLOBALS() ADD_NA_COMMA NoteChannel  noteChannel, long  pitch, long  velocity);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(SetController) (NA_GLOBALS() ADD_NA_COMMA NoteChannel  noteChannel, long  controllerNumber, long  controllerValue);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(SetKnob) (NA_GLOBALS() ADD_NA_COMMA NoteChannel  noteChannel, long  knobNumber, long  knobValue);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(FindNoteChannelTone) (NA_GLOBALS() ADD_NA_COMMA NoteChannel  noteChannel, ToneDescription * td, long * instrumentNumber);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(SetInstrumentNumber) (NA_GLOBALS() ADD_NA_COMMA NoteChannel  noteChannel, long  instrumentNumber);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(PickInstrument) (NA_GLOBALS() ADD_NA_COMMA ModalFilterUPP  filterProc, StringPtr  prompt, ToneDescription * sd, unsigned long  flags, long  refCon, long  reserved1, long  reserved2);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(PickArrangement) (NA_GLOBALS() ADD_NA_COMMA ModalFilterUPP  filterProc, StringPtr  prompt, long  zero1, long  zero2, Track  t, StringPtr  songName);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(StuffToneDescription) (NA_GLOBALS() ADD_NA_COMMA long  gmNumber, ToneDescription * td);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(CopyrightDialog) (NA_GLOBALS() ADD_NA_COMMA PicHandle  p, StringPtr  author, StringPtr  copyright, StringPtr  other, StringPtr  title, ModalFilterUPP  filterProc, long  refCon);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(GetIndNoteChannel) (NA_GLOBALS() ADD_NA_COMMA long  index, NoteChannel * nc, long * seed);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(GetMIDIPorts) (NA_GLOBALS() ADD_NA_COMMA QTMIDIPortListHandle * inputPorts, QTMIDIPortListHandle * outputPorts);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(GetNoteRequest) (NA_GLOBALS() ADD_NA_COMMA NoteChannel  noteChannel, NoteRequest * nrOut);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(SendMIDI) (NA_GLOBALS() ADD_NA_COMMA NoteChannel  noteChannel, MusicMIDIPacket * mp);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(PickEditInstrument) (NA_GLOBALS() ADD_NA_COMMA ModalFilterUPP  filterProc, StringPtr  prompt, long  refCon, NoteChannel  nc, AtomicInstrument  ai, long  flags);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(NewNoteChannelFromAtomicInstrument) (NA_GLOBALS() ADD_NA_COMMA AtomicInstrumentPtr  instrument, long  flags, NoteChannel * outChannel);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(SetAtomicInstrument) (NA_GLOBALS() ADD_NA_COMMA NoteChannel  noteChannel, AtomicInstrumentPtr  instrument, long  flags);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(GetKnob) (NA_GLOBALS() ADD_NA_COMMA NoteChannel  noteChannel, long  knobNumber, long * knobValue);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(Task) (NA_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(SetNoteChannelBalance) (NA_GLOBALS() ADD_NA_COMMA NoteChannel  noteChannel, long  balance);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(SetInstrumentNumberInterruptSafe) (NA_GLOBALS() ADD_NA_COMMA NoteChannel  noteChannel, long  instrumentNumber);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(SetNoteChannelSoundLocalization) (NA_GLOBALS() ADD_NA_COMMA NoteChannel  noteChannel, Handle  data);

	EXTERN_API( ComponentResult  ) ADD_NA_BASENAME(GetController) (NA_GLOBALS() ADD_NA_COMMA NoteChannel  noteChannel, long  controllerNumber, long * controllerValue);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppNARegisterMusicDeviceProcInfo = 0x00003FF0,
		uppNAUnregisterMusicDeviceProcInfo = 0x000003F0,
		uppNAGetRegisteredMusicDeviceProcInfo = 0x0003FFF0,
		uppNASaveMusicConfigurationProcInfo = 0x000000F0,
		uppNANewNoteChannelProcInfo = 0x00000FF0,
		uppNADisposeNoteChannelProcInfo = 0x000003F0,
		uppNAGetNoteChannelInfoProcInfo = 0x00003FF0,
		uppNAPrerollNoteChannelProcInfo = 0x000003F0,
		uppNAUnrollNoteChannelProcInfo = 0x000003F0,
		uppNASetNoteChannelVolumeProcInfo = 0x00000FF0,
		uppNAResetNoteChannelProcInfo = 0x000003F0,
		uppNAPlayNoteProcInfo = 0x00003FF0,
		uppNASetControllerProcInfo = 0x00003FF0,
		uppNASetKnobProcInfo = 0x00003FF0,
		uppNAFindNoteChannelToneProcInfo = 0x00003FF0,
		uppNASetInstrumentNumberProcInfo = 0x00000FF0,
		uppNAPickInstrumentProcInfo = 0x003FFFF0,
		uppNAPickArrangementProcInfo = 0x000FFFF0,
		uppNAStuffToneDescriptionProcInfo = 0x00000FF0,
		uppNACopyrightDialogProcInfo = 0x003FFFF0,
		uppNAGetIndNoteChannelProcInfo = 0x00003FF0,
		uppNAGetMIDIPortsProcInfo = 0x00000FF0,
		uppNAGetNoteRequestProcInfo = 0x00000FF0,
		uppNASendMIDIProcInfo = 0x00000FF0,
		uppNAPickEditInstrumentProcInfo = 0x000FFFF0,
		uppNANewNoteChannelFromAtomicInstrumentProcInfo = 0x00003FF0,
		uppNASetAtomicInstrumentProcInfo = 0x00003FF0,
		uppNAGetKnobProcInfo = 0x00003FF0,
		uppNATaskProcInfo = 0x000000F0,
		uppNASetNoteChannelBalanceProcInfo = 0x00000FF0,
		uppNASetInstrumentNumberInterruptSafeProcInfo = 0x00000FF0,
		uppNASetNoteChannelSoundLocalizationProcInfo = 0x00000FF0,
		uppNAGetControllerProcInfo = 0x00003FF0
	};

#endif	/* NA_BASENAME */

/*
	Example usage:

		#define TUNE_BASENAME()	Fred
		#define TUNE_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeMusic.k.h>

	To specify that your component implementation does not use globals, do not #define TUNE_GLOBALS
*/
#ifdef TUNE_BASENAME
	#ifndef TUNE_GLOBALS
		#define TUNE_GLOBALS() 
		#define ADD_TUNE_COMMA 
	#else
		#define ADD_TUNE_COMMA ,
	#endif
	#define TUNE_GLUE(a,b) a##b
	#define TUNE_STRCAT(a,b) TUNE_GLUE(a,b)
	#define ADD_TUNE_BASENAME(name) TUNE_STRCAT(TUNE_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(SetHeader) (TUNE_GLOBALS() ADD_TUNE_COMMA unsigned long * header);

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(GetTimeBase) (TUNE_GLOBALS() ADD_TUNE_COMMA TimeBase * tb);

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(SetTimeScale) (TUNE_GLOBALS() ADD_TUNE_COMMA TimeScale  scale);

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(GetTimeScale) (TUNE_GLOBALS() ADD_TUNE_COMMA TimeScale * scale);

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(GetIndexedNoteChannel) (TUNE_GLOBALS() ADD_TUNE_COMMA long  i, NoteChannel * nc);

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(Queue) (TUNE_GLOBALS() ADD_TUNE_COMMA unsigned long * tune, Fixed  tuneRate, unsigned long  tuneStartPosition, unsigned long  tuneStopPosition, unsigned long  queueFlags, TuneCallBackUPP  callBackProc, long  refCon);

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(Instant) (TUNE_GLOBALS() ADD_TUNE_COMMA unsigned long * tune, unsigned long  tunePosition);

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(GetStatus) (TUNE_GLOBALS() ADD_TUNE_COMMA TuneStatus * status);

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(Stop) (TUNE_GLOBALS() ADD_TUNE_COMMA long  stopFlags);

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(SetVolume) (TUNE_GLOBALS() ADD_TUNE_COMMA Fixed  volume);

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(GetVolume) (TUNE_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(Preroll) (TUNE_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(Unroll) (TUNE_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(SetNoteChannels) (TUNE_GLOBALS() ADD_TUNE_COMMA unsigned long  count, NoteChannel * noteChannelList, TunePlayCallBackUPP  playCallBackProc, long  refCon);

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(SetPartTranspose) (TUNE_GLOBALS() ADD_TUNE_COMMA unsigned long  part, long  transpose, long  velocityShift);

	EXTERN_API( NoteAllocator  ) ADD_TUNE_BASENAME(GetNoteAllocator) (TUNE_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(SetSofter) (TUNE_GLOBALS() ADD_TUNE_COMMA long  softer);

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(Task) (TUNE_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(SetBalance) (TUNE_GLOBALS() ADD_TUNE_COMMA long  balance);

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(SetSoundLocalization) (TUNE_GLOBALS() ADD_TUNE_COMMA Handle  data);

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(SetHeaderWithSize) (TUNE_GLOBALS() ADD_TUNE_COMMA unsigned long * header, unsigned long  size);

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(SetPartMix) (TUNE_GLOBALS() ADD_TUNE_COMMA unsigned long  partNumber, long  volume, long  balance, long  mixFlags);

	EXTERN_API( ComponentResult  ) ADD_TUNE_BASENAME(GetPartMix) (TUNE_GLOBALS() ADD_TUNE_COMMA unsigned long  partNumber, long * volumeOut, long * balanceOut, long * mixFlagsOut);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppTuneSetHeaderProcInfo = 0x000003F0,
		uppTuneGetTimeBaseProcInfo = 0x000003F0,
		uppTuneSetTimeScaleProcInfo = 0x000003F0,
		uppTuneGetTimeScaleProcInfo = 0x000003F0,
		uppTuneGetIndexedNoteChannelProcInfo = 0x00000FF0,
		uppTuneQueueProcInfo = 0x003FFFF0,
		uppTuneInstantProcInfo = 0x00000FF0,
		uppTuneGetStatusProcInfo = 0x000003F0,
		uppTuneStopProcInfo = 0x000003F0,
		uppTuneSetVolumeProcInfo = 0x000003F0,
		uppTuneGetVolumeProcInfo = 0x000000F0,
		uppTunePrerollProcInfo = 0x000000F0,
		uppTuneUnrollProcInfo = 0x000000F0,
		uppTuneSetNoteChannelsProcInfo = 0x0000FFF0,
		uppTuneSetPartTransposeProcInfo = 0x00003FF0,
		uppTuneGetNoteAllocatorProcInfo = 0x000000F0,
		uppTuneSetSofterProcInfo = 0x000003F0,
		uppTuneTaskProcInfo = 0x000000F0,
		uppTuneSetBalanceProcInfo = 0x000003F0,
		uppTuneSetSoundLocalizationProcInfo = 0x000003F0,
		uppTuneSetHeaderWithSizeProcInfo = 0x00000FF0,
		uppTuneSetPartMixProcInfo = 0x0000FFF0,
		uppTuneGetPartMixProcInfo = 0x0000FFF0
	};

#endif	/* TUNE_BASENAME */


#endif /* __QUICKTIMEMUSIC_K__ */

