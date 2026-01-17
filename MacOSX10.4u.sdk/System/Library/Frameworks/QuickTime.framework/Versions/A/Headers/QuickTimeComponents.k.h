/*
     File:       QuickTimeComponents.k.h
 
     Contains:   QuickTime Interfaces.
 
     Version:    QuickTime 7.2.1
 
     Copyright:  © 1990-2006 by Apple Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __QUICKTIMECOMPONENTS_K__
#define __QUICKTIMECOMPONENTS_K__

#include <QuickTime/QuickTimeComponents.h>
/*
	Example usage:

		#define CLOCK_BASENAME()	Fred
		#define CLOCK_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeComponents.k.h>

	To specify that your component implementation does not use globals, do not #define CLOCK_GLOBALS
*/
#ifdef CLOCK_BASENAME
	#ifndef CLOCK_GLOBALS
		#define CLOCK_GLOBALS() 
		#define ADD_CLOCK_COMMA 
	#else
		#define ADD_CLOCK_COMMA ,
	#endif
	#define CLOCK_GLUE(a,b) a##b
	#define CLOCK_STRCAT(a,b) CLOCK_GLUE(a,b)
	#define ADD_CLOCK_BASENAME(name) CLOCK_STRCAT(CLOCK_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_CLOCK_BASENAME(GetTime) (CLOCK_GLOBALS() ADD_CLOCK_COMMA TimeRecord * out);

	EXTERN_API( QTCallBack  ) ADD_CLOCK_BASENAME(NewCallBack) (CLOCK_GLOBALS() ADD_CLOCK_COMMA TimeBase  tb, short  callBackType);

	EXTERN_API( ComponentResult  ) ADD_CLOCK_BASENAME(DisposeCallBack) (CLOCK_GLOBALS() ADD_CLOCK_COMMA QTCallBack  cb);

	EXTERN_API( ComponentResult  ) ADD_CLOCK_BASENAME(CallMeWhen) (CLOCK_GLOBALS() ADD_CLOCK_COMMA QTCallBack  cb, long  param1, long  param2, long  param3);

	EXTERN_API( ComponentResult  ) ADD_CLOCK_BASENAME(CancelCallBack) (CLOCK_GLOBALS() ADD_CLOCK_COMMA QTCallBack  cb);

	EXTERN_API( ComponentResult  ) ADD_CLOCK_BASENAME(RateChanged) (CLOCK_GLOBALS() ADD_CLOCK_COMMA QTCallBack  cb);

	EXTERN_API( ComponentResult  ) ADD_CLOCK_BASENAME(TimeChanged) (CLOCK_GLOBALS() ADD_CLOCK_COMMA QTCallBack  cb);

	EXTERN_API( ComponentResult  ) ADD_CLOCK_BASENAME(SetTimeBase) (CLOCK_GLOBALS() ADD_CLOCK_COMMA TimeBase  tb);

	EXTERN_API( ComponentResult  ) ADD_CLOCK_BASENAME(StartStopChanged) (CLOCK_GLOBALS() ADD_CLOCK_COMMA QTCallBack  cb, Boolean  startChanged, Boolean  stopChanged);

	EXTERN_API( ComponentResult  ) ADD_CLOCK_BASENAME(GetRate) (CLOCK_GLOBALS() ADD_CLOCK_COMMA Fixed * rate);

	EXTERN_API( ComponentResult  ) ADD_CLOCK_BASENAME(GetTimesForRateChange) (CLOCK_GLOBALS() ADD_CLOCK_COMMA Fixed  fromRate, Fixed  toRate, TimeRecord * currentTime, TimeRecord * preferredTime, TimeRecord * safeIncrementForPreferredTime);

	EXTERN_API( ComponentResult  ) ADD_CLOCK_BASENAME(GetRateChangeConstraints) (CLOCK_GLOBALS() ADD_CLOCK_COMMA TimeRecord * minimumDelay, TimeRecord * maximumDelay);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppClockGetTimeProcInfo = 0x000003F0,
		uppClockNewCallBackProcInfo = 0x00000BF0,
		uppClockDisposeCallBackProcInfo = 0x000003F0,
		uppClockCallMeWhenProcInfo = 0x0000FFF0,
		uppClockCancelCallBackProcInfo = 0x000003F0,
		uppClockRateChangedProcInfo = 0x000003F0,
		uppClockTimeChangedProcInfo = 0x000003F0,
		uppClockSetTimeBaseProcInfo = 0x000003F0,
		uppClockStartStopChangedProcInfo = 0x000017F0,
		uppClockGetRateProcInfo = 0x000003F0,
		uppClockGetTimesForRateChangeProcInfo = 0x0003FFF0,
		uppClockGetRateChangeConstraintsProcInfo = 0x00000FF0
	};

#endif	/* CLOCK_BASENAME */

/*
	Example usage:

		#define SC_BASENAME()	Fred
		#define SC_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeComponents.k.h>

	To specify that your component implementation does not use globals, do not #define SC_GLOBALS
*/
#ifdef SC_BASENAME
	#ifndef SC_GLOBALS
		#define SC_GLOBALS() 
		#define ADD_SC_COMMA 
	#else
		#define ADD_SC_COMMA ,
	#endif
	#define SC_GLUE(a,b) a##b
	#define SC_STRCAT(a,b) SC_GLUE(a,b)
	#define ADD_SC_BASENAME(name) SC_STRCAT(SC_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(AudioInvokeLegacyCodecOptionsDialog) (SC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(AudioFillBuffer) (SC_GLOBALS() ADD_SC_COMMA SCAudioInputDataProc  inInputDataProc, void * inInputDataProcRefCon, UInt32 * ioOutputDataPacketSize, AudioBufferList * outOutputData, AudioStreamPacketDescription * outPacketDescription);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(AudioReset) (SC_GLOBALS());

#endif	/* SC_BASENAME */

/*
	Example usage:

		#define SC_BASENAME()	Fred
		#define SC_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeComponents.k.h>

	To specify that your component implementation does not use globals, do not #define SC_GLOBALS
*/
#ifdef SC_BASENAME
	#ifndef SC_GLOBALS
		#define SC_GLOBALS() 
		#define ADD_SC_COMMA 
	#else
		#define ADD_SC_COMMA ,
	#endif
	#define SC_GLUE(a,b) a##b
	#define SC_STRCAT(a,b) SC_GLUE(a,b)
	#define ADD_SC_BASENAME(name) SC_STRCAT(SC_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(GetCompressionExtended) (SC_GLOBALS() ADD_SC_COMMA SCParams * params, Point  where, SCModalFilterUPP  filterProc, SCModalHookUPP  hookProc, long  refcon, StringPtr  customName);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(PositionRect) (SC_GLOBALS() ADD_SC_COMMA Rect * rp, Point * where);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(PositionDialog) (SC_GLOBALS() ADD_SC_COMMA short  id, Point * where);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(SetTestImagePictHandle) (SC_GLOBALS() ADD_SC_COMMA PicHandle  testPict, Rect * testRect, short  testFlags);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(SetTestImagePictFile) (SC_GLOBALS() ADD_SC_COMMA short  testFileRef, Rect * testRect, short  testFlags);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(SetTestImagePixMap) (SC_GLOBALS() ADD_SC_COMMA PixMapHandle  testPixMap, Rect * testRect, short  testFlags);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(GetBestDeviceRect) (SC_GLOBALS() ADD_SC_COMMA Rect * r);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(RequestImageSettings) (SC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(CompressImage) (SC_GLOBALS() ADD_SC_COMMA PixMapHandle  src, const Rect * srcRect, ImageDescriptionHandle * desc, Handle * data);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(CompressPicture) (SC_GLOBALS() ADD_SC_COMMA PicHandle  srcPicture, PicHandle  dstPicture);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(CompressPictureFile) (SC_GLOBALS() ADD_SC_COMMA short  srcRefNum, short  dstRefNum);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(RequestSequenceSettings) (SC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(CompressSequenceBegin) (SC_GLOBALS() ADD_SC_COMMA PixMapHandle  src, const Rect * srcRect, ImageDescriptionHandle * desc);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(CompressSequenceFrame) (SC_GLOBALS() ADD_SC_COMMA PixMapHandle  src, const Rect * srcRect, Handle * data, long * dataSize, short * notSyncFlag);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(CompressSequenceEnd) (SC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(DefaultPictHandleSettings) (SC_GLOBALS() ADD_SC_COMMA PicHandle  srcPicture, short  motion);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(DefaultPictFileSettings) (SC_GLOBALS() ADD_SC_COMMA short  srcRef, short  motion);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(DefaultPixMapSettings) (SC_GLOBALS() ADD_SC_COMMA PixMapHandle  src, short  motion);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(GetInfo) (SC_GLOBALS() ADD_SC_COMMA OSType  infoType, void * info);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(SetInfo) (SC_GLOBALS() ADD_SC_COMMA OSType  infoType, void * info);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(NewGWorld) (SC_GLOBALS() ADD_SC_COMMA GWorldPtr * gwp, Rect * rp, GWorldFlags  flags);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(SetCompressFlags) (SC_GLOBALS() ADD_SC_COMMA long  flags);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(GetCompressFlags) (SC_GLOBALS() ADD_SC_COMMA long * flags);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(GetSettingsAsText) (SC_GLOBALS() ADD_SC_COMMA Handle * text);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(GetSettingsAsAtomContainer) (SC_GLOBALS() ADD_SC_COMMA QTAtomContainer * settings);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(SetSettingsFromAtomContainer) (SC_GLOBALS() ADD_SC_COMMA QTAtomContainer  settings);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(CompressSequenceFrameAsync) (SC_GLOBALS() ADD_SC_COMMA PixMapHandle  src, const Rect * srcRect, Handle * data, long * dataSize, short * notSyncFlag, ICMCompletionProcRecordPtr  asyncCompletionProc);

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(AsyncIdle) (SC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_SC_BASENAME(CopyCompressionSessionOptions) (SC_GLOBALS() ADD_SC_COMMA ICMCompressionSessionOptionsRef * outOptions);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppSCAudioInvokeLegacyCodecOptionsDialogProcInfo = 0x000000F0,
		uppSCAudioFillBufferProcInfo = 0x0003FFF0,
		uppSCAudioResetProcInfo = 0x000000F0,
		uppSCGetCompressionExtendedProcInfo = 0x000FFFF0,
		uppSCPositionRectProcInfo = 0x00000FF0,
		uppSCPositionDialogProcInfo = 0x00000EF0,
		uppSCSetTestImagePictHandleProcInfo = 0x00002FF0,
		uppSCSetTestImagePictFileProcInfo = 0x00002EF0,
		uppSCSetTestImagePixMapProcInfo = 0x00002FF0,
		uppSCGetBestDeviceRectProcInfo = 0x000003F0,
		uppSCRequestImageSettingsProcInfo = 0x000000F0,
		uppSCCompressImageProcInfo = 0x0000FFF0,
		uppSCCompressPictureProcInfo = 0x00000FF0,
		uppSCCompressPictureFileProcInfo = 0x00000AF0,
		uppSCRequestSequenceSettingsProcInfo = 0x000000F0,
		uppSCCompressSequenceBeginProcInfo = 0x00003FF0,
		uppSCCompressSequenceFrameProcInfo = 0x0003FFF0,
		uppSCCompressSequenceEndProcInfo = 0x000000F0,
		uppSCDefaultPictHandleSettingsProcInfo = 0x00000BF0,
		uppSCDefaultPictFileSettingsProcInfo = 0x00000AF0,
		uppSCDefaultPixMapSettingsProcInfo = 0x00000BF0,
		uppSCGetInfoProcInfo = 0x00000FF0,
		uppSCSetInfoProcInfo = 0x00000FF0,
		uppSCNewGWorldProcInfo = 0x00003FF0,
		uppSCSetCompressFlagsProcInfo = 0x000003F0,
		uppSCGetCompressFlagsProcInfo = 0x000003F0,
		uppSCGetSettingsAsTextProcInfo = 0x000003F0,
		uppSCGetSettingsAsAtomContainerProcInfo = 0x000003F0,
		uppSCSetSettingsFromAtomContainerProcInfo = 0x000003F0,
		uppSCCompressSequenceFrameAsyncProcInfo = 0x000FFFF0,
		uppSCAsyncIdleProcInfo = 0x000000F0,
		uppSCCopyCompressionSessionOptionsProcInfo = 0x000003F0
	};

#endif	/* SC_BASENAME */

/*
	Example usage:

		#define TWEENER_BASENAME()	Fred
		#define TWEENER_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeComponents.k.h>

	To specify that your component implementation does not use globals, do not #define TWEENER_GLOBALS
*/
#ifdef TWEENER_BASENAME
	#ifndef TWEENER_GLOBALS
		#define TWEENER_GLOBALS() 
		#define ADD_TWEENER_COMMA 
	#else
		#define ADD_TWEENER_COMMA ,
	#endif
	#define TWEENER_GLUE(a,b) a##b
	#define TWEENER_STRCAT(a,b) TWEENER_GLUE(a,b)
	#define ADD_TWEENER_BASENAME(name) TWEENER_STRCAT(TWEENER_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_TWEENER_BASENAME(Initialize) (TWEENER_GLOBALS() ADD_TWEENER_COMMA QTAtomContainer  container, QTAtom  tweenAtom, QTAtom  dataAtom);

	EXTERN_API( ComponentResult  ) ADD_TWEENER_BASENAME(DoTween) (TWEENER_GLOBALS() ADD_TWEENER_COMMA TweenRecord * tr);

	EXTERN_API( ComponentResult  ) ADD_TWEENER_BASENAME(Reset) (TWEENER_GLOBALS());


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppTweenerInitializeProcInfo = 0x00003FF0,
		uppTweenerDoTweenProcInfo = 0x000003F0,
		uppTweenerResetProcInfo = 0x000000F0
	};

#endif	/* TWEENER_BASENAME */

/*
	Example usage:

		#define TC_BASENAME()	Fred
		#define TC_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeComponents.k.h>

	To specify that your component implementation does not use globals, do not #define TC_GLOBALS
*/
#ifdef TC_BASENAME
	#ifndef TC_GLOBALS
		#define TC_GLOBALS() 
		#define ADD_TC_COMMA 
	#else
		#define ADD_TC_COMMA ,
	#endif
	#define TC_GLUE(a,b) a##b
	#define TC_STRCAT(a,b) TC_GLUE(a,b)
	#define ADD_TC_BASENAME(name) TC_STRCAT(TC_BASENAME(),name)

	EXTERN_API( HandlerError  ) ADD_TC_BASENAME(GetCurrentTimeCode) (TC_GLOBALS() ADD_TC_COMMA long * frameNum, TimeCodeDef * tcdef, TimeCodeRecord * tcrec, UserData * srcRefH);

	EXTERN_API( HandlerError  ) ADD_TC_BASENAME(GetTimeCodeAtTime) (TC_GLOBALS() ADD_TC_COMMA TimeValue  mediaTime, long * frameNum, TimeCodeDef * tcdef, TimeCodeRecord * tcdata, UserData * srcRefH);

	EXTERN_API( HandlerError  ) ADD_TC_BASENAME(TimeCodeToString) (TC_GLOBALS() ADD_TC_COMMA TimeCodeDef * tcdef, TimeCodeRecord * tcrec, StringPtr  tcStr);

	EXTERN_API( HandlerError  ) ADD_TC_BASENAME(TimeCodeToFrameNumber) (TC_GLOBALS() ADD_TC_COMMA TimeCodeDef * tcdef, TimeCodeRecord * tcrec, long * frameNumber);

	EXTERN_API( HandlerError  ) ADD_TC_BASENAME(FrameNumberToTimeCode) (TC_GLOBALS() ADD_TC_COMMA long  frameNumber, TimeCodeDef * tcdef, TimeCodeRecord * tcrec);

	EXTERN_API( HandlerError  ) ADD_TC_BASENAME(GetSourceRef) (TC_GLOBALS() ADD_TC_COMMA TimeCodeDescriptionHandle  tcdH, UserData * srefH);

	EXTERN_API( HandlerError  ) ADD_TC_BASENAME(SetSourceRef) (TC_GLOBALS() ADD_TC_COMMA TimeCodeDescriptionHandle  tcdH, UserData  srefH);

	EXTERN_API( HandlerError  ) ADD_TC_BASENAME(SetTimeCodeFlags) (TC_GLOBALS() ADD_TC_COMMA long  flags, long  flagsMask);

	EXTERN_API( HandlerError  ) ADD_TC_BASENAME(GetTimeCodeFlags) (TC_GLOBALS() ADD_TC_COMMA long * flags);

	EXTERN_API( HandlerError  ) ADD_TC_BASENAME(SetDisplayOptions) (TC_GLOBALS() ADD_TC_COMMA TCTextOptionsPtr  textOptions);

	EXTERN_API( HandlerError  ) ADD_TC_BASENAME(GetDisplayOptions) (TC_GLOBALS() ADD_TC_COMMA TCTextOptionsPtr  textOptions);

	EXTERN_API( HandlerError  ) ADD_TC_BASENAME(GetCurrentFrameAndTimeCodeDef) (TC_GLOBALS() ADD_TC_COMMA SInt64 * outFrameNum, TimeCodeDef * outTCDef);

	EXTERN_API( HandlerError  ) ADD_TC_BASENAME(GetFrameAndTimeCodeDefAtTime) (TC_GLOBALS() ADD_TC_COMMA const TimeValue64 * mediaTime, SInt64 * outFrameNum, TimeCodeDef * outTCDef);

	EXTERN_API( HandlerError  ) ADD_TC_BASENAME(TimeCodeTimeToString) (TC_GLOBALS() ADD_TC_COMMA const TimeCodeDef * tCDef, const SMPTETime * tCTime, CFStringRef * outTCStr);

	EXTERN_API( HandlerError  ) ADD_TC_BASENAME(TimeCodeCounterToString) (TC_GLOBALS() ADD_TC_COMMA const TimeCodeDef * tCDef, const TimeCode64Counter * tCCounter, CFStringRef * outTCStr);

	EXTERN_API( HandlerError  ) ADD_TC_BASENAME(TimeCodeTimeToFrameNumber) (TC_GLOBALS() ADD_TC_COMMA const TimeCodeDef * tCDef, const SMPTETime * tCTime, SInt64 * outFrameNum);

	EXTERN_API( HandlerError  ) ADD_TC_BASENAME(TimeCodeCounterToFrameNumber) (TC_GLOBALS() ADD_TC_COMMA const TimeCodeDef * tCDef, const TimeCode64Counter * tCCounter, SInt64 * outFrameNum);

	EXTERN_API( HandlerError  ) ADD_TC_BASENAME(FrameNumberToTimeCodeTime) (TC_GLOBALS() ADD_TC_COMMA const SInt64 * frameNumber, const TimeCodeDef * tCDef, SMPTETime * outTCTime);

	EXTERN_API( HandlerError  ) ADD_TC_BASENAME(FrameNumberToTimeCodeCounter) (TC_GLOBALS() ADD_TC_COMMA const SInt64 * frameNumber, const TimeCodeDef * tCDef, TimeCode64Counter * outTCCounter);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppTCGetCurrentTimeCodeProcInfo = 0x0000FFF0,
		uppTCGetTimeCodeAtTimeProcInfo = 0x0003FFF0,
		uppTCTimeCodeToStringProcInfo = 0x00003FF0,
		uppTCTimeCodeToFrameNumberProcInfo = 0x00003FF0,
		uppTCFrameNumberToTimeCodeProcInfo = 0x00003FF0,
		uppTCGetSourceRefProcInfo = 0x00000FF0,
		uppTCSetSourceRefProcInfo = 0x00000FF0,
		uppTCSetTimeCodeFlagsProcInfo = 0x00000FF0,
		uppTCGetTimeCodeFlagsProcInfo = 0x000003F0,
		uppTCSetDisplayOptionsProcInfo = 0x000003F0,
		uppTCGetDisplayOptionsProcInfo = 0x000003F0,
		uppTCGetCurrentFrameAndTimeCodeDefProcInfo = 0x00000FF0,
		uppTCGetFrameAndTimeCodeDefAtTimeProcInfo = 0x00003FF0,
		uppTCTimeCodeTimeToStringProcInfo = 0x00003FF0,
		uppTCTimeCodeCounterToStringProcInfo = 0x00003FF0,
		uppTCTimeCodeTimeToFrameNumberProcInfo = 0x00003FF0,
		uppTCTimeCodeCounterToFrameNumberProcInfo = 0x00003FF0,
		uppTCFrameNumberToTimeCodeTimeProcInfo = 0x00003FF0,
		uppTCFrameNumberToTimeCodeCounterProcInfo = 0x00003FF0
	};

#endif	/* TC_BASENAME */

/*
	Example usage:

		#define MOVIEIMPORT_BASENAME()	Fred
		#define MOVIEIMPORT_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeComponents.k.h>

	To specify that your component implementation does not use globals, do not #define MOVIEIMPORT_GLOBALS
*/
#ifdef MOVIEIMPORT_BASENAME
	#ifndef MOVIEIMPORT_GLOBALS
		#define MOVIEIMPORT_GLOBALS() 
		#define ADD_MOVIEIMPORT_COMMA 
	#else
		#define ADD_MOVIEIMPORT_COMMA ,
	#endif
	#define MOVIEIMPORT_GLUE(a,b) a##b
	#define MOVIEIMPORT_STRCAT(a,b) MOVIEIMPORT_GLUE(a,b)
	#define ADD_MOVIEIMPORT_BASENAME(name) MOVIEIMPORT_STRCAT(MOVIEIMPORT_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(Handle) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA Handle  dataH, Movie  theMovie, Track  targetTrack, Track * usedTrack, TimeValue  atTime, TimeValue * addedDuration, long  inFlags, long * outFlags);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(File) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA const FSSpec * theFile, Movie  theMovie, Track  targetTrack, Track * usedTrack, TimeValue  atTime, TimeValue * addedDuration, long  inFlags, long * outFlags);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(SetSampleDuration) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA TimeValue  duration, TimeScale  scale);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(SetSampleDescription) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA SampleDescriptionHandle  desc, OSType  mediaType);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(SetMediaFile) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA AliasHandle  alias);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(SetDimensions) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA Fixed  width, Fixed  height);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(SetChunkSize) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA long  chunkSize);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(SetProgressProc) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA MovieProgressUPP  proc, long  refcon);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(SetAuxiliaryData) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA Handle  data, OSType  handleType);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(SetFromScrap) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA Boolean  fromScrap);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(DoUserDialog) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA const FSSpec * theFile, Handle  theData, Boolean * canceled);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(SetDuration) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA TimeValue  duration);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(GetAuxiliaryDataType) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA OSType * auxType);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(Validate) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA const FSSpec * theFile, Handle  theData, Boolean * valid);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(GetFileType) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA OSType * fileType);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(DataRef) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA Handle  dataRef, OSType  dataRefType, Movie  theMovie, Track  targetTrack, Track * usedTrack, TimeValue  atTime, TimeValue * addedDuration, long  inFlags, long * outFlags);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(GetSampleDescription) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA SampleDescriptionHandle * desc, OSType * mediaType);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(GetMIMETypeList) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA QTAtomContainer * mimeInfo);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(SetOffsetAndLimit) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA unsigned long  offset, unsigned long  limit);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(GetSettingsAsAtomContainer) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA QTAtomContainer * settings);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(SetSettingsFromAtomContainer) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA QTAtomContainer  settings);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(SetOffsetAndLimit64) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA const wide * offset, const wide * limit);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(Idle) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA long  inFlags, long * outFlags);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(ValidateDataRef) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA Handle  dataRef, OSType  dataRefType, UInt8 * valid);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(GetLoadState) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA long * importerLoadState);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(GetMaxLoadedTime) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA TimeValue * time);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(EstimateCompletionTime) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA TimeRecord * time);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(SetDontBlock) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA Boolean  dontBlock);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(GetDontBlock) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA Boolean * willBlock);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(SetIdleManager) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA IdleManager  im);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(SetNewMovieFlags) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA long  newMovieFlags);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(GetDestinationMediaType) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA OSType * mediaType);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(SetMediaDataRef) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA Handle  dataRef, OSType  dataRefType);

	EXTERN_API( ComponentResult  ) ADD_MOVIEIMPORT_BASENAME(DoUserDialogDataRef) (MOVIEIMPORT_GLOBALS() ADD_MOVIEIMPORT_COMMA Handle  dataRef, OSType  dataRefType, Boolean * canceled);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppMovieImportHandleProcInfo = 0x00FFFFF0,
		uppMovieImportFileProcInfo = 0x00FFFFF0,
		uppMovieImportSetSampleDurationProcInfo = 0x00000FF0,
		uppMovieImportSetSampleDescriptionProcInfo = 0x00000FF0,
		uppMovieImportSetMediaFileProcInfo = 0x000003F0,
		uppMovieImportSetDimensionsProcInfo = 0x00000FF0,
		uppMovieImportSetChunkSizeProcInfo = 0x000003F0,
		uppMovieImportSetProgressProcProcInfo = 0x00000FF0,
		uppMovieImportSetAuxiliaryDataProcInfo = 0x00000FF0,
		uppMovieImportSetFromScrapProcInfo = 0x000001F0,
		uppMovieImportDoUserDialogProcInfo = 0x00003FF0,
		uppMovieImportSetDurationProcInfo = 0x000003F0,
		uppMovieImportGetAuxiliaryDataTypeProcInfo = 0x000003F0,
		uppMovieImportValidateProcInfo = 0x00003FF0,
		uppMovieImportGetFileTypeProcInfo = 0x000003F0,
		uppMovieImportDataRefProcInfo = 0x03FFFFF0,
		uppMovieImportGetSampleDescriptionProcInfo = 0x00000FF0,
		uppMovieImportGetMIMETypeListProcInfo = 0x000003F0,
		uppMovieImportSetOffsetAndLimitProcInfo = 0x00000FF0,
		uppMovieImportGetSettingsAsAtomContainerProcInfo = 0x000003F0,
		uppMovieImportSetSettingsFromAtomContainerProcInfo = 0x000003F0,
		uppMovieImportSetOffsetAndLimit64ProcInfo = 0x00000FF0,
		uppMovieImportIdleProcInfo = 0x00000FF0,
		uppMovieImportValidateDataRefProcInfo = 0x00003FF0,
		uppMovieImportGetLoadStateProcInfo = 0x000003F0,
		uppMovieImportGetMaxLoadedTimeProcInfo = 0x000003F0,
		uppMovieImportEstimateCompletionTimeProcInfo = 0x000003F0,
		uppMovieImportSetDontBlockProcInfo = 0x000001F0,
		uppMovieImportGetDontBlockProcInfo = 0x000003F0,
		uppMovieImportSetIdleManagerProcInfo = 0x000003F0,
		uppMovieImportSetNewMovieFlagsProcInfo = 0x000003F0,
		uppMovieImportGetDestinationMediaTypeProcInfo = 0x000003F0,
		uppMovieImportSetMediaDataRefProcInfo = 0x00000FF0,
		uppMovieImportDoUserDialogDataRefProcInfo = 0x00003FF0
	};

#endif	/* MOVIEIMPORT_BASENAME */

/*
	Example usage:

		#define MOVIEEXPORT_BASENAME()	Fred
		#define MOVIEEXPORT_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeComponents.k.h>

	To specify that your component implementation does not use globals, do not #define MOVIEEXPORT_GLOBALS
*/
#ifdef MOVIEEXPORT_BASENAME
	#ifndef MOVIEEXPORT_GLOBALS
		#define MOVIEEXPORT_GLOBALS() 
		#define ADD_MOVIEEXPORT_COMMA 
	#else
		#define ADD_MOVIEEXPORT_COMMA ,
	#endif
	#define MOVIEEXPORT_GLUE(a,b) a##b
	#define MOVIEEXPORT_STRCAT(a,b) MOVIEEXPORT_GLUE(a,b)
	#define ADD_MOVIEEXPORT_BASENAME(name) MOVIEEXPORT_STRCAT(MOVIEEXPORT_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_MOVIEEXPORT_BASENAME(ToHandle) (MOVIEEXPORT_GLOBALS() ADD_MOVIEEXPORT_COMMA Handle  dataH, Movie  theMovie, Track  onlyThisTrack, TimeValue  startTime, TimeValue  duration);

	EXTERN_API( ComponentResult  ) ADD_MOVIEEXPORT_BASENAME(ToFile) (MOVIEEXPORT_GLOBALS() ADD_MOVIEEXPORT_COMMA const FSSpec * theFile, Movie  theMovie, Track  onlyThisTrack, TimeValue  startTime, TimeValue  duration);

	EXTERN_API( ComponentResult  ) ADD_MOVIEEXPORT_BASENAME(GetAuxiliaryData) (MOVIEEXPORT_GLOBALS() ADD_MOVIEEXPORT_COMMA Handle  dataH, OSType * handleType);

	EXTERN_API( ComponentResult  ) ADD_MOVIEEXPORT_BASENAME(SetProgressProc) (MOVIEEXPORT_GLOBALS() ADD_MOVIEEXPORT_COMMA MovieProgressUPP  proc, long  refcon);

	EXTERN_API( ComponentResult  ) ADD_MOVIEEXPORT_BASENAME(SetSampleDescription) (MOVIEEXPORT_GLOBALS() ADD_MOVIEEXPORT_COMMA SampleDescriptionHandle  desc, OSType  mediaType);

	EXTERN_API( ComponentResult  ) ADD_MOVIEEXPORT_BASENAME(DoUserDialog) (MOVIEEXPORT_GLOBALS() ADD_MOVIEEXPORT_COMMA Movie  theMovie, Track  onlyThisTrack, TimeValue  startTime, TimeValue  duration, Boolean * canceled);

	EXTERN_API( ComponentResult  ) ADD_MOVIEEXPORT_BASENAME(GetCreatorType) (MOVIEEXPORT_GLOBALS() ADD_MOVIEEXPORT_COMMA OSType * creator);

	EXTERN_API( ComponentResult  ) ADD_MOVIEEXPORT_BASENAME(ToDataRef) (MOVIEEXPORT_GLOBALS() ADD_MOVIEEXPORT_COMMA Handle  dataRef, OSType  dataRefType, Movie  theMovie, Track  onlyThisTrack, TimeValue  startTime, TimeValue  duration);

	EXTERN_API( ComponentResult  ) ADD_MOVIEEXPORT_BASENAME(FromProceduresToDataRef) (MOVIEEXPORT_GLOBALS() ADD_MOVIEEXPORT_COMMA Handle  dataRef, OSType  dataRefType);

	EXTERN_API( ComponentResult  ) ADD_MOVIEEXPORT_BASENAME(AddDataSource) (MOVIEEXPORT_GLOBALS() ADD_MOVIEEXPORT_COMMA OSType  trackType, TimeScale  scale, long * trackID, MovieExportGetPropertyUPP  getPropertyProc, MovieExportGetDataUPP  getDataProc, void * refCon);

	EXTERN_API( ComponentResult  ) ADD_MOVIEEXPORT_BASENAME(Validate) (MOVIEEXPORT_GLOBALS() ADD_MOVIEEXPORT_COMMA Movie  theMovie, Track  onlyThisTrack, Boolean * valid);

	EXTERN_API( ComponentResult  ) ADD_MOVIEEXPORT_BASENAME(GetSettingsAsAtomContainer) (MOVIEEXPORT_GLOBALS() ADD_MOVIEEXPORT_COMMA QTAtomContainer * settings);

	EXTERN_API( ComponentResult  ) ADD_MOVIEEXPORT_BASENAME(SetSettingsFromAtomContainer) (MOVIEEXPORT_GLOBALS() ADD_MOVIEEXPORT_COMMA QTAtomContainer  settings);

	EXTERN_API( ComponentResult  ) ADD_MOVIEEXPORT_BASENAME(GetFileNameExtension) (MOVIEEXPORT_GLOBALS() ADD_MOVIEEXPORT_COMMA OSType * extension);

	EXTERN_API( ComponentResult  ) ADD_MOVIEEXPORT_BASENAME(GetShortFileTypeString) (MOVIEEXPORT_GLOBALS() ADD_MOVIEEXPORT_COMMA Str255  typeString);

	EXTERN_API( ComponentResult  ) ADD_MOVIEEXPORT_BASENAME(GetSourceMediaType) (MOVIEEXPORT_GLOBALS() ADD_MOVIEEXPORT_COMMA OSType * mediaType);

	EXTERN_API( ComponentResult  ) ADD_MOVIEEXPORT_BASENAME(SetGetMoviePropertyProc) (MOVIEEXPORT_GLOBALS() ADD_MOVIEEXPORT_COMMA MovieExportGetPropertyUPP  getPropertyProc, void * refCon);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppMovieExportToHandleProcInfo = 0x0003FFF0,
		uppMovieExportToFileProcInfo = 0x0003FFF0,
		uppMovieExportGetAuxiliaryDataProcInfo = 0x00000FF0,
		uppMovieExportSetProgressProcProcInfo = 0x00000FF0,
		uppMovieExportSetSampleDescriptionProcInfo = 0x00000FF0,
		uppMovieExportDoUserDialogProcInfo = 0x0003FFF0,
		uppMovieExportGetCreatorTypeProcInfo = 0x000003F0,
		uppMovieExportToDataRefProcInfo = 0x000FFFF0,
		uppMovieExportFromProceduresToDataRefProcInfo = 0x00000FF0,
		uppMovieExportAddDataSourceProcInfo = 0x000FFFF0,
		uppMovieExportValidateProcInfo = 0x00003FF0,
		uppMovieExportGetSettingsAsAtomContainerProcInfo = 0x000003F0,
		uppMovieExportSetSettingsFromAtomContainerProcInfo = 0x000003F0,
		uppMovieExportGetFileNameExtensionProcInfo = 0x000003F0,
		uppMovieExportGetShortFileTypeStringProcInfo = 0x000003F0,
		uppMovieExportGetSourceMediaTypeProcInfo = 0x000003F0,
		uppMovieExportSetGetMoviePropertyProcProcInfo = 0x00000FF0
	};

#endif	/* MOVIEEXPORT_BASENAME */

/*
	Example usage:

		#define TEXTEXPORT_BASENAME()	Fred
		#define TEXTEXPORT_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeComponents.k.h>

	To specify that your component implementation does not use globals, do not #define TEXTEXPORT_GLOBALS
*/
#ifdef TEXTEXPORT_BASENAME
	#ifndef TEXTEXPORT_GLOBALS
		#define TEXTEXPORT_GLOBALS() 
		#define ADD_TEXTEXPORT_COMMA 
	#else
		#define ADD_TEXTEXPORT_COMMA ,
	#endif
	#define TEXTEXPORT_GLUE(a,b) a##b
	#define TEXTEXPORT_STRCAT(a,b) TEXTEXPORT_GLUE(a,b)
	#define ADD_TEXTEXPORT_BASENAME(name) TEXTEXPORT_STRCAT(TEXTEXPORT_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_TEXTEXPORT_BASENAME(GetDisplayData) (TEXTEXPORT_GLOBALS() ADD_TEXTEXPORT_COMMA TextDisplayData * textDisplay);

	EXTERN_API( ComponentResult  ) ADD_TEXTEXPORT_BASENAME(GetTimeFraction) (TEXTEXPORT_GLOBALS() ADD_TEXTEXPORT_COMMA long * movieTimeFraction);

	EXTERN_API( ComponentResult  ) ADD_TEXTEXPORT_BASENAME(SetTimeFraction) (TEXTEXPORT_GLOBALS() ADD_TEXTEXPORT_COMMA long  movieTimeFraction);

	EXTERN_API( ComponentResult  ) ADD_TEXTEXPORT_BASENAME(GetSettings) (TEXTEXPORT_GLOBALS() ADD_TEXTEXPORT_COMMA long * setting);

	EXTERN_API( ComponentResult  ) ADD_TEXTEXPORT_BASENAME(SetSettings) (TEXTEXPORT_GLOBALS() ADD_TEXTEXPORT_COMMA long  setting);

#endif	/* TEXTEXPORT_BASENAME */

/*
	Example usage:

		#define MIDIIMPORT_BASENAME()	Fred
		#define MIDIIMPORT_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeComponents.k.h>

	To specify that your component implementation does not use globals, do not #define MIDIIMPORT_GLOBALS
*/
#ifdef MIDIIMPORT_BASENAME
	#ifndef MIDIIMPORT_GLOBALS
		#define MIDIIMPORT_GLOBALS() 
		#define ADD_MIDIIMPORT_COMMA 
	#else
		#define ADD_MIDIIMPORT_COMMA ,
	#endif
	#define MIDIIMPORT_GLUE(a,b) a##b
	#define MIDIIMPORT_STRCAT(a,b) MIDIIMPORT_GLUE(a,b)
	#define ADD_MIDIIMPORT_BASENAME(name) MIDIIMPORT_STRCAT(MIDIIMPORT_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_MIDIIMPORT_BASENAME(GetSettings) (MIDIIMPORT_GLOBALS() ADD_MIDIIMPORT_COMMA long * setting);

	EXTERN_API( ComponentResult  ) ADD_MIDIIMPORT_BASENAME(SetSettings) (MIDIIMPORT_GLOBALS() ADD_MIDIIMPORT_COMMA long  setting);

#endif	/* MIDIIMPORT_BASENAME */

/*
	Example usage:

		#define MOVIEEXPORT_BASENAME()	Fred
		#define MOVIEEXPORT_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeComponents.k.h>

	To specify that your component implementation does not use globals, do not #define MOVIEEXPORT_GLOBALS
*/
#ifdef MOVIEEXPORT_BASENAME
	#ifndef MOVIEEXPORT_GLOBALS
		#define MOVIEEXPORT_GLOBALS() 
		#define ADD_MOVIEEXPORT_COMMA 
	#else
		#define ADD_MOVIEEXPORT_COMMA ,
	#endif
	#define MOVIEEXPORT_GLUE(a,b) a##b
	#define MOVIEEXPORT_STRCAT(a,b) MOVIEEXPORT_GLUE(a,b)
	#define ADD_MOVIEEXPORT_BASENAME(name) MOVIEEXPORT_STRCAT(MOVIEEXPORT_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_MOVIEEXPORT_BASENAME(NewGetDataAndPropertiesProcs) (MOVIEEXPORT_GLOBALS() ADD_MOVIEEXPORT_COMMA OSType  trackType, TimeScale * scale, Movie  theMovie, Track  theTrack, TimeValue  startTime, TimeValue  duration, MovieExportGetPropertyUPP * getPropertyProc, MovieExportGetDataUPP * getDataProc, void ** refCon);

	EXTERN_API( ComponentResult  ) ADD_MOVIEEXPORT_BASENAME(DisposeGetDataAndPropertiesProcs) (MOVIEEXPORT_GLOBALS() ADD_MOVIEEXPORT_COMMA MovieExportGetPropertyUPP  getPropertyProc, MovieExportGetDataUPP  getDataProc, void * refCon);

#endif	/* MOVIEEXPORT_BASENAME */

/*
	Example usage:

		#define GRAPHICSIMAGEIMPORT_BASENAME()	Fred
		#define GRAPHICSIMAGEIMPORT_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeComponents.k.h>

	To specify that your component implementation does not use globals, do not #define GRAPHICSIMAGEIMPORT_GLOBALS
*/
#ifdef GRAPHICSIMAGEIMPORT_BASENAME
	#ifndef GRAPHICSIMAGEIMPORT_GLOBALS
		#define GRAPHICSIMAGEIMPORT_GLOBALS() 
		#define ADD_GRAPHICSIMAGEIMPORT_COMMA 
	#else
		#define ADD_GRAPHICSIMAGEIMPORT_COMMA ,
	#endif
	#define GRAPHICSIMAGEIMPORT_GLUE(a,b) a##b
	#define GRAPHICSIMAGEIMPORT_STRCAT(a,b) GRAPHICSIMAGEIMPORT_GLUE(a,b)
	#define ADD_GRAPHICSIMAGEIMPORT_BASENAME(name) GRAPHICSIMAGEIMPORT_STRCAT(GRAPHICSIMAGEIMPORT_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMAGEIMPORT_BASENAME(SetSequenceEnabled) (GRAPHICSIMAGEIMPORT_GLOBALS() ADD_GRAPHICSIMAGEIMPORT_COMMA Boolean  enable);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMAGEIMPORT_BASENAME(GetSequenceEnabled) (GRAPHICSIMAGEIMPORT_GLOBALS() ADD_GRAPHICSIMAGEIMPORT_COMMA Boolean * enable);

#endif	/* GRAPHICSIMAGEIMPORT_BASENAME */


/* MixedMode ProcInfo constants for component calls */
enum {
	uppTextExportGetDisplayDataProcInfo = 0x000003F0,
	uppTextExportGetTimeFractionProcInfo = 0x000003F0,
	uppTextExportSetTimeFractionProcInfo = 0x000003F0,
	uppTextExportGetSettingsProcInfo = 0x000003F0,
	uppTextExportSetSettingsProcInfo = 0x000003F0,
	uppMIDIImportGetSettingsProcInfo = 0x000003F0,
	uppMIDIImportSetSettingsProcInfo = 0x000003F0,
	uppMovieExportNewGetDataAndPropertiesProcsProcInfo = 0x03FFFFF0,
	uppMovieExportDisposeGetDataAndPropertiesProcsProcInfo = 0x00003FF0,
	uppGraphicsImageImportSetSequenceEnabledProcInfo = 0x000001F0,
	uppGraphicsImageImportGetSequenceEnabledProcInfo = 0x000003F0
};

/*
	Example usage:

		#define PREVIEW_BASENAME()	Fred
		#define PREVIEW_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeComponents.k.h>

	To specify that your component implementation does not use globals, do not #define PREVIEW_GLOBALS
*/
#ifdef PREVIEW_BASENAME
	#ifndef PREVIEW_GLOBALS
		#define PREVIEW_GLOBALS() 
		#define ADD_PREVIEW_COMMA 
	#else
		#define ADD_PREVIEW_COMMA ,
	#endif
	#define PREVIEW_GLUE(a,b) a##b
	#define PREVIEW_STRCAT(a,b) PREVIEW_GLUE(a,b)
	#define ADD_PREVIEW_BASENAME(name) PREVIEW_STRCAT(PREVIEW_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_PREVIEW_BASENAME(ShowData) (PREVIEW_GLOBALS() ADD_PREVIEW_COMMA OSType  dataType, Handle  data, const Rect * inHere);

	EXTERN_API( ComponentResult  ) ADD_PREVIEW_BASENAME(MakePreview) (PREVIEW_GLOBALS() ADD_PREVIEW_COMMA OSType * previewType, Handle * previewResult, const FSSpec * sourceFile, ICMProgressProcRecordPtr  progress);

	EXTERN_API( ComponentResult  ) ADD_PREVIEW_BASENAME(MakePreviewReference) (PREVIEW_GLOBALS() ADD_PREVIEW_COMMA OSType * previewType, short * resID, const FSSpec * sourceFile);

	EXTERN_API( ComponentResult  ) ADD_PREVIEW_BASENAME(Event) (PREVIEW_GLOBALS() ADD_PREVIEW_COMMA EventRecord * e, Boolean * handledEvent);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppPreviewShowDataProcInfo = 0x00003FF0,
		uppPreviewMakePreviewProcInfo = 0x0000FFF0,
		uppPreviewMakePreviewReferenceProcInfo = 0x00003FF0,
		uppPreviewEventProcInfo = 0x00000FF0
	};

#endif	/* PREVIEW_BASENAME */

/*
	Example usage:

		#define DATACODEC_BASENAME()	Fred
		#define DATACODEC_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeComponents.k.h>

	To specify that your component implementation does not use globals, do not #define DATACODEC_GLOBALS
*/
#ifdef DATACODEC_BASENAME
	#ifndef DATACODEC_GLOBALS
		#define DATACODEC_GLOBALS() 
		#define ADD_DATACODEC_COMMA 
	#else
		#define ADD_DATACODEC_COMMA ,
	#endif
	#define DATACODEC_GLUE(a,b) a##b
	#define DATACODEC_STRCAT(a,b) DATACODEC_GLUE(a,b)
	#define ADD_DATACODEC_BASENAME(name) DATACODEC_STRCAT(DATACODEC_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_DATACODEC_BASENAME(Decompress) (DATACODEC_GLOBALS() ADD_DATACODEC_COMMA void * srcData, UInt32  srcSize, void * dstData, UInt32  dstBufferSize);

	EXTERN_API( ComponentResult  ) ADD_DATACODEC_BASENAME(GetCompressBufferSize) (DATACODEC_GLOBALS() ADD_DATACODEC_COMMA UInt32  srcSize, UInt32 * dstSize);

	EXTERN_API( ComponentResult  ) ADD_DATACODEC_BASENAME(Compress) (DATACODEC_GLOBALS() ADD_DATACODEC_COMMA void * srcData, UInt32  srcSize, void * dstData, UInt32  dstBufferSize, UInt32 * actualDstSize, UInt32 * decompressSlop);

	EXTERN_API( ComponentResult  ) ADD_DATACODEC_BASENAME(BeginInterruptSafe) (DATACODEC_GLOBALS() ADD_DATACODEC_COMMA unsigned long  maxSrcSize);

	EXTERN_API( ComponentResult  ) ADD_DATACODEC_BASENAME(EndInterruptSafe) (DATACODEC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_DATACODEC_BASENAME(DecompressPartial) (DATACODEC_GLOBALS() ADD_DATACODEC_COMMA void ** next_in, unsigned long * avail_in, unsigned long * total_in, void ** next_out, unsigned long * avail_out, unsigned long * total_out, Boolean * didFinish);

	EXTERN_API( ComponentResult  ) ADD_DATACODEC_BASENAME(CompressPartial) (DATACODEC_GLOBALS() ADD_DATACODEC_COMMA void ** next_in, unsigned long * avail_in, unsigned long * total_in, void ** next_out, unsigned long * avail_out, unsigned long * total_out, Boolean  tryToFinish, Boolean * didFinish);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppDataCodecDecompressProcInfo = 0x0000FFF0,
		uppDataCodecGetCompressBufferSizeProcInfo = 0x00000FF0,
		uppDataCodecCompressProcInfo = 0x000FFFF0,
		uppDataCodecBeginInterruptSafeProcInfo = 0x000003F0,
		uppDataCodecEndInterruptSafeProcInfo = 0x000000F0,
		uppDataCodecDecompressPartialProcInfo = 0x003FFFF0,
		uppDataCodecCompressPartialProcInfo = 0x00DFFFF0
	};

#endif	/* DATACODEC_BASENAME */

/*
	Example usage:

		#define DATAH_BASENAME()	Fred
		#define DATAH_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeComponents.k.h>

	To specify that your component implementation does not use globals, do not #define DATAH_GLOBALS
*/
#ifdef DATAH_BASENAME
	#ifndef DATAH_GLOBALS
		#define DATAH_GLOBALS() 
		#define ADD_DATAH_COMMA 
	#else
		#define ADD_DATAH_COMMA ,
	#endif
	#define DATAH_GLUE(a,b) a##b
	#define DATAH_STRCAT(a,b) DATAH_GLUE(a,b)
	#define ADD_DATAH_BASENAME(name) DATAH_STRCAT(DATAH_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetData) (DATAH_GLOBALS() ADD_DATAH_COMMA Handle  h, long  hOffset, long  offset, long  size);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(PutData) (DATAH_GLOBALS() ADD_DATAH_COMMA Handle  h, long  hOffset, long * offset, long  size);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(FlushData) (DATAH_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(OpenForWrite) (DATAH_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(CloseForWrite) (DATAH_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(OpenForRead) (DATAH_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(CloseForRead) (DATAH_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(SetDataRef) (DATAH_GLOBALS() ADD_DATAH_COMMA Handle  dataRef);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetDataRef) (DATAH_GLOBALS() ADD_DATAH_COMMA Handle * dataRef);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(CompareDataRef) (DATAH_GLOBALS() ADD_DATAH_COMMA Handle  dataRef, Boolean * equal);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(Task) (DATAH_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(ScheduleData) (DATAH_GLOBALS() ADD_DATAH_COMMA Ptr  PlaceToPutDataPtr, long  FileOffset, long  DataSize, long  RefCon, DataHSchedulePtr  scheduleRec, DataHCompletionUPP  CompletionRtn);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(FinishData) (DATAH_GLOBALS() ADD_DATAH_COMMA Ptr  PlaceToPutDataPtr, Boolean  Cancel);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(FlushCache) (DATAH_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(ResolveDataRef) (DATAH_GLOBALS() ADD_DATAH_COMMA Handle  theDataRef, Boolean * wasChanged, Boolean  userInterfaceAllowed);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetFileSize) (DATAH_GLOBALS() ADD_DATAH_COMMA long * fileSize);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(CanUseDataRef) (DATAH_GLOBALS() ADD_DATAH_COMMA Handle  dataRef, long * useFlags);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetVolumeList) (DATAH_GLOBALS() ADD_DATAH_COMMA DataHVolumeList * volumeList);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(Write) (DATAH_GLOBALS() ADD_DATAH_COMMA Ptr  data, long  offset, long  size, DataHCompletionUPP  completion, long  refCon);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(Preextend) (DATAH_GLOBALS() ADD_DATAH_COMMA unsigned long  maxToAdd, unsigned long * spaceAdded);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(SetFileSize) (DATAH_GLOBALS() ADD_DATAH_COMMA long  fileSize);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetFreeSpace) (DATAH_GLOBALS() ADD_DATAH_COMMA unsigned long * freeSize);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(CreateFile) (DATAH_GLOBALS() ADD_DATAH_COMMA OSType  creator, Boolean  deleteExisting);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetPreferredBlockSize) (DATAH_GLOBALS() ADD_DATAH_COMMA long * blockSize);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetDeviceIndex) (DATAH_GLOBALS() ADD_DATAH_COMMA long * deviceIndex);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(IsStreamingDataHandler) (DATAH_GLOBALS() ADD_DATAH_COMMA Boolean * yes);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetDataInBuffer) (DATAH_GLOBALS() ADD_DATAH_COMMA long  startOffset, long * size);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetScheduleAheadTime) (DATAH_GLOBALS() ADD_DATAH_COMMA long * millisecs);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(SetCacheSizeLimit) (DATAH_GLOBALS() ADD_DATAH_COMMA Size  cacheSizeLimit);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetCacheSizeLimit) (DATAH_GLOBALS() ADD_DATAH_COMMA Size * cacheSizeLimit);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetMovie) (DATAH_GLOBALS() ADD_DATAH_COMMA Movie * theMovie, short * id);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(AddMovie) (DATAH_GLOBALS() ADD_DATAH_COMMA Movie  theMovie, short * id);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(UpdateMovie) (DATAH_GLOBALS() ADD_DATAH_COMMA Movie  theMovie, short  id);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(DoesBuffer) (DATAH_GLOBALS() ADD_DATAH_COMMA Boolean * buffersReads, Boolean * buffersWrites);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetFileName) (DATAH_GLOBALS() ADD_DATAH_COMMA Str255  str);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetAvailableFileSize) (DATAH_GLOBALS() ADD_DATAH_COMMA long * fileSize);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetMacOSFileType) (DATAH_GLOBALS() ADD_DATAH_COMMA OSType * fileType);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetMIMEType) (DATAH_GLOBALS() ADD_DATAH_COMMA Str255  mimeType);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(SetDataRefWithAnchor) (DATAH_GLOBALS() ADD_DATAH_COMMA Handle  anchorDataRef, OSType  dataRefType, Handle  dataRef);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetDataRefWithAnchor) (DATAH_GLOBALS() ADD_DATAH_COMMA Handle  anchorDataRef, OSType  dataRefType, Handle * dataRef);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(SetMacOSFileType) (DATAH_GLOBALS() ADD_DATAH_COMMA OSType  fileType);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(SetTimeBase) (DATAH_GLOBALS() ADD_DATAH_COMMA TimeBase  tb);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetInfoFlags) (DATAH_GLOBALS() ADD_DATAH_COMMA UInt32 * flags);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(ScheduleData64) (DATAH_GLOBALS() ADD_DATAH_COMMA Ptr  PlaceToPutDataPtr, const wide * FileOffset, long  DataSize, long  RefCon, DataHSchedulePtr  scheduleRec, DataHCompletionUPP  CompletionRtn);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(Write64) (DATAH_GLOBALS() ADD_DATAH_COMMA Ptr  data, const wide * offset, long  size, DataHCompletionUPP  completion, long  refCon);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetFileSize64) (DATAH_GLOBALS() ADD_DATAH_COMMA wide * fileSize);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(Preextend64) (DATAH_GLOBALS() ADD_DATAH_COMMA const wide * maxToAdd, wide * spaceAdded);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(SetFileSize64) (DATAH_GLOBALS() ADD_DATAH_COMMA const wide * fileSize);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetFreeSpace64) (DATAH_GLOBALS() ADD_DATAH_COMMA wide * freeSize);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(Append64) (DATAH_GLOBALS() ADD_DATAH_COMMA void * data, wide * fileOffset, unsigned long  size);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(ReadAsync) (DATAH_GLOBALS() ADD_DATAH_COMMA void * dataPtr, UInt32  dataSize, const wide * dataOffset, DataHCompletionUPP  completion, long  refCon);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(PollRead) (DATAH_GLOBALS() ADD_DATAH_COMMA void * dataPtr, UInt32 * dataSizeSoFar);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetDataAvailability) (DATAH_GLOBALS() ADD_DATAH_COMMA long  offset, long  len, long * missing_offset, long * missing_len);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetFileSizeAsync) (DATAH_GLOBALS() ADD_DATAH_COMMA wide * fileSize, DataHCompletionUPP  completionRtn, long  refCon);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetDataRefAsType) (DATAH_GLOBALS() ADD_DATAH_COMMA OSType  requestedType, Handle * dataRef);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(SetDataRefExtension) (DATAH_GLOBALS() ADD_DATAH_COMMA Handle  extension, OSType  idType);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetDataRefExtension) (DATAH_GLOBALS() ADD_DATAH_COMMA Handle * extension, OSType  idType);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetMovieWithFlags) (DATAH_GLOBALS() ADD_DATAH_COMMA Movie * theMovie, short * id, short  flags);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetFileTypeOrdering) (DATAH_GLOBALS() ADD_DATAH_COMMA DataHFileTypeOrderingHandle * orderingListHandle);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(CreateFileWithFlags) (DATAH_GLOBALS() ADD_DATAH_COMMA OSType  creator, Boolean  deleteExisting, UInt32  flags);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetMIMETypeAsync) (DATAH_GLOBALS() ADD_DATAH_COMMA Str255  mimeType, DataHCompletionUPP  completionRtn, long  refCon);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetInfo) (DATAH_GLOBALS() ADD_DATAH_COMMA OSType  what, void * info);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(SetIdleManager) (DATAH_GLOBALS() ADD_DATAH_COMMA IdleManager  im);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(DeleteFile) (DATAH_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(SetMovieUsageFlags) (DATAH_GLOBALS() ADD_DATAH_COMMA long  flags);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(UseTemporaryDataRef) (DATAH_GLOBALS() ADD_DATAH_COMMA long  inFlags);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetTemporaryDataRefCapabilities) (DATAH_GLOBALS() ADD_DATAH_COMMA long * outUnderstoodFlags);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(RenameFile) (DATAH_GLOBALS() ADD_DATAH_COMMA Handle  newDataRef);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetAvailableFileSize64) (DATAH_GLOBALS() ADD_DATAH_COMMA wide * fileSize);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetDataAvailability64) (DATAH_GLOBALS() ADD_DATAH_COMMA const wide * offset, long  len, wide * missing_offset, long * missing_len);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(PlaybackHints) (DATAH_GLOBALS() ADD_DATAH_COMMA long  flags, unsigned long  minFileOffset, unsigned long  maxFileOffset, long  bytesPerSecond);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(PlaybackHints64) (DATAH_GLOBALS() ADD_DATAH_COMMA long  flags, const wide * minFileOffset, const wide * maxFileOffset, long  bytesPerSecond);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(GetDataRate) (DATAH_GLOBALS() ADD_DATAH_COMMA long  flags, long * bytesPerSecond);

	EXTERN_API( ComponentResult  ) ADD_DATAH_BASENAME(SetTimeHints) (DATAH_GLOBALS() ADD_DATAH_COMMA long  flags, long  bandwidthPriority, TimeScale  scale, TimeValue  minTime, TimeValue  maxTime);

#endif	/* DATAH_BASENAME */

/*
	Example usage:

		#define VD_BASENAME()	Fred
		#define VD_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeComponents.k.h>

	To specify that your component implementation does not use globals, do not #define VD_GLOBALS
*/
#ifdef VD_BASENAME
	#ifndef VD_GLOBALS
		#define VD_GLOBALS() 
		#define ADD_VD_COMMA 
	#else
		#define ADD_VD_COMMA ,
	#endif
	#define VD_GLUE(a,b) a##b
	#define VD_STRCAT(a,b) VD_GLUE(a,b)
	#define ADD_VD_BASENAME(name) VD_STRCAT(VD_BASENAME(),name)

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetMaxSrcRect) (VD_GLOBALS() ADD_VD_COMMA short  inputStd, Rect * maxSrcRect);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetActiveSrcRect) (VD_GLOBALS() ADD_VD_COMMA short  inputStd, Rect * activeSrcRect);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetDigitizerRect) (VD_GLOBALS() ADD_VD_COMMA Rect * digitizerRect);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetDigitizerRect) (VD_GLOBALS() ADD_VD_COMMA Rect * digitizerRect);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetVBlankRect) (VD_GLOBALS() ADD_VD_COMMA short  inputStd, Rect * vBlankRect);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetMaskPixMap) (VD_GLOBALS() ADD_VD_COMMA PixMapHandle  maskPixMap);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetPlayThruDestination) (VD_GLOBALS() ADD_VD_COMMA PixMapHandle * dest, Rect * destRect, MatrixRecord * m, RgnHandle * mask);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(UseThisCLUT) (VD_GLOBALS() ADD_VD_COMMA CTabHandle  colorTableHandle);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetInputGammaValue) (VD_GLOBALS() ADD_VD_COMMA Fixed  channel1, Fixed  channel2, Fixed  channel3);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetInputGammaValue) (VD_GLOBALS() ADD_VD_COMMA Fixed * channel1, Fixed * channel2, Fixed * channel3);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetBrightness) (VD_GLOBALS() ADD_VD_COMMA unsigned short * brightness);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetBrightness) (VD_GLOBALS() ADD_VD_COMMA unsigned short * brightness);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetContrast) (VD_GLOBALS() ADD_VD_COMMA unsigned short * contrast);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetHue) (VD_GLOBALS() ADD_VD_COMMA unsigned short * hue);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetSharpness) (VD_GLOBALS() ADD_VD_COMMA unsigned short * sharpness);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetSaturation) (VD_GLOBALS() ADD_VD_COMMA unsigned short * saturation);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetContrast) (VD_GLOBALS() ADD_VD_COMMA unsigned short * contrast);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetHue) (VD_GLOBALS() ADD_VD_COMMA unsigned short * hue);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetSharpness) (VD_GLOBALS() ADD_VD_COMMA unsigned short * sharpness);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetSaturation) (VD_GLOBALS() ADD_VD_COMMA unsigned short * saturation);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GrabOneFrame) (VD_GLOBALS());

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetMaxAuxBuffer) (VD_GLOBALS() ADD_VD_COMMA PixMapHandle * pm, Rect * r);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetDigitizerInfo) (VD_GLOBALS() ADD_VD_COMMA DigitizerInfo * info);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetCurrentFlags) (VD_GLOBALS() ADD_VD_COMMA long * inputCurrentFlag, long * outputCurrentFlag);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetKeyColor) (VD_GLOBALS() ADD_VD_COMMA long  index);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetKeyColor) (VD_GLOBALS() ADD_VD_COMMA long * index);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(AddKeyColor) (VD_GLOBALS() ADD_VD_COMMA long * index);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetNextKeyColor) (VD_GLOBALS() ADD_VD_COMMA long  index);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetKeyColorRange) (VD_GLOBALS() ADD_VD_COMMA RGBColor * minRGB, RGBColor * maxRGB);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetKeyColorRange) (VD_GLOBALS() ADD_VD_COMMA RGBColor * minRGB, RGBColor * maxRGB);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetDigitizerUserInterrupt) (VD_GLOBALS() ADD_VD_COMMA long  flags, VdigIntUPP  userInterruptProc, long  refcon);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetInputColorSpaceMode) (VD_GLOBALS() ADD_VD_COMMA short  colorSpaceMode);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetInputColorSpaceMode) (VD_GLOBALS() ADD_VD_COMMA short * colorSpaceMode);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetClipState) (VD_GLOBALS() ADD_VD_COMMA short  clipEnable);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetClipState) (VD_GLOBALS() ADD_VD_COMMA short * clipEnable);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetClipRgn) (VD_GLOBALS() ADD_VD_COMMA RgnHandle  clipRegion);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(ClearClipRgn) (VD_GLOBALS() ADD_VD_COMMA RgnHandle  clipRegion);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetCLUTInUse) (VD_GLOBALS() ADD_VD_COMMA CTabHandle * colorTableHandle);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetPLLFilterType) (VD_GLOBALS() ADD_VD_COMMA short  pllType);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetPLLFilterType) (VD_GLOBALS() ADD_VD_COMMA short * pllType);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetMaskandValue) (VD_GLOBALS() ADD_VD_COMMA unsigned short  blendLevel, long * mask, long * value);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetMasterBlendLevel) (VD_GLOBALS() ADD_VD_COMMA unsigned short * blendLevel);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetPlayThruDestination) (VD_GLOBALS() ADD_VD_COMMA PixMapHandle  dest, RectPtr  destRect, MatrixRecordPtr  m, RgnHandle  mask);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetPlayThruOnOff) (VD_GLOBALS() ADD_VD_COMMA short  state);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetFieldPreference) (VD_GLOBALS() ADD_VD_COMMA short  fieldFlag);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetFieldPreference) (VD_GLOBALS() ADD_VD_COMMA short * fieldFlag);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(PreflightDestination) (VD_GLOBALS() ADD_VD_COMMA Rect * digitizerRect, PixMap ** dest, RectPtr  destRect, MatrixRecordPtr  m);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(PreflightGlobalRect) (VD_GLOBALS() ADD_VD_COMMA GrafPtr  theWindow, Rect * globalRect);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetPlayThruGlobalRect) (VD_GLOBALS() ADD_VD_COMMA GrafPtr  theWindow, Rect * globalRect);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetInputGammaRecord) (VD_GLOBALS() ADD_VD_COMMA VDGamRecPtr  inputGammaPtr);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetInputGammaRecord) (VD_GLOBALS() ADD_VD_COMMA VDGamRecPtr * inputGammaPtr);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetBlackLevelValue) (VD_GLOBALS() ADD_VD_COMMA unsigned short * blackLevel);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetBlackLevelValue) (VD_GLOBALS() ADD_VD_COMMA unsigned short * blackLevel);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetWhiteLevelValue) (VD_GLOBALS() ADD_VD_COMMA unsigned short * whiteLevel);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetWhiteLevelValue) (VD_GLOBALS() ADD_VD_COMMA unsigned short * whiteLevel);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetVideoDefaults) (VD_GLOBALS() ADD_VD_COMMA unsigned short * blackLevel, unsigned short * whiteLevel, unsigned short * brightness, unsigned short * hue, unsigned short * saturation, unsigned short * contrast, unsigned short * sharpness);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetNumberOfInputs) (VD_GLOBALS() ADD_VD_COMMA short * inputs);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetInputFormat) (VD_GLOBALS() ADD_VD_COMMA short  input, short * format);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetInput) (VD_GLOBALS() ADD_VD_COMMA short  input);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetInput) (VD_GLOBALS() ADD_VD_COMMA short * input);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetInputStandard) (VD_GLOBALS() ADD_VD_COMMA short  inputStandard);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetupBuffers) (VD_GLOBALS() ADD_VD_COMMA VdigBufferRecListHandle  bufferList);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GrabOneFrameAsync) (VD_GLOBALS() ADD_VD_COMMA short  buffer);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(Done) (VD_GLOBALS() ADD_VD_COMMA short  buffer);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetCompression) (VD_GLOBALS() ADD_VD_COMMA OSType  compressType, short  depth, Rect * bounds, CodecQ  spatialQuality, CodecQ  temporalQuality, long  keyFrameRate);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(CompressOneFrameAsync) (VD_GLOBALS());

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(CompressDone) (VD_GLOBALS() ADD_VD_COMMA UInt8 * queuedFrameCount, Ptr * theData, long * dataSize, UInt8 * similarity, TimeRecord * t);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(ReleaseCompressBuffer) (VD_GLOBALS() ADD_VD_COMMA Ptr  bufferAddr);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetImageDescription) (VD_GLOBALS() ADD_VD_COMMA ImageDescriptionHandle  desc);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(ResetCompressSequence) (VD_GLOBALS());

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetCompressionOnOff) (VD_GLOBALS() ADD_VD_COMMA Boolean  state);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetCompressionTypes) (VD_GLOBALS() ADD_VD_COMMA VDCompressionListHandle  h);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetTimeBase) (VD_GLOBALS() ADD_VD_COMMA TimeBase  t);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetFrameRate) (VD_GLOBALS() ADD_VD_COMMA Fixed  framesPerSecond);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetDataRate) (VD_GLOBALS() ADD_VD_COMMA long * milliSecPerFrame, Fixed * framesPerSecond, long * bytesPerSecond);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetSoundInputDriver) (VD_GLOBALS() ADD_VD_COMMA Str255  soundDriverName);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetDMADepths) (VD_GLOBALS() ADD_VD_COMMA long * depthArray, long * preferredDepth);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetPreferredTimeScale) (VD_GLOBALS() ADD_VD_COMMA TimeScale * preferred);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(ReleaseAsyncBuffers) (VD_GLOBALS());

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetDataRate) (VD_GLOBALS() ADD_VD_COMMA long  bytesPerSecond);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetTimeCode) (VD_GLOBALS() ADD_VD_COMMA TimeRecord * atTime, void * timeCodeFormat, void * timeCodeTime);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(UseSafeBuffers) (VD_GLOBALS() ADD_VD_COMMA Boolean  useSafeBuffers);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetSoundInputSource) (VD_GLOBALS() ADD_VD_COMMA long  videoInput, long * soundInput);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetCompressionTime) (VD_GLOBALS() ADD_VD_COMMA OSType  compressionType, short  depth, Rect * srcRect, CodecQ * spatialQuality, CodecQ * temporalQuality, unsigned long * compressTime);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetPreferredPacketSize) (VD_GLOBALS() ADD_VD_COMMA long  preferredPacketSizeInBytes);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetPreferredImageDimensions) (VD_GLOBALS() ADD_VD_COMMA long  width, long  height);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetPreferredImageDimensions) (VD_GLOBALS() ADD_VD_COMMA long * width, long * height);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetInputName) (VD_GLOBALS() ADD_VD_COMMA long  videoInput, Str255  name);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SetDestinationPort) (VD_GLOBALS() ADD_VD_COMMA CGrafPtr  destPort);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetDeviceNameAndFlags) (VD_GLOBALS() ADD_VD_COMMA Str255  outName, UInt32 * outNameFlags);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(CaptureStateChanging) (VD_GLOBALS() ADD_VD_COMMA UInt32  inStateFlags);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(GetUniqueIDs) (VD_GLOBALS() ADD_VD_COMMA UInt64 * outDeviceID, UInt64 * outInputID);

	EXTERN_API( VideoDigitizerError  ) ADD_VD_BASENAME(SelectUniqueIDs) (VD_GLOBALS() ADD_VD_COMMA const UInt64 * inDeviceID, const UInt64 * inInputID);

	EXTERN_API( ComponentResult  ) ADD_VD_BASENAME(CopyPreferredAudioDevice) (VD_GLOBALS() ADD_VD_COMMA CFStringRef * outAudioDeviceUID);

#endif	/* VD_BASENAME */


/* MixedMode ProcInfo constants for component calls */
enum {
	uppDataHGetDataProcInfo = 0x0000FFF0,
	uppDataHPutDataProcInfo = 0x0000FFF0,
	uppDataHFlushDataProcInfo = 0x000000F0,
	uppDataHOpenForWriteProcInfo = 0x000000F0,
	uppDataHCloseForWriteProcInfo = 0x000000F0,
	uppDataHOpenForReadProcInfo = 0x000000F0,
	uppDataHCloseForReadProcInfo = 0x000000F0,
	uppDataHSetDataRefProcInfo = 0x000003F0,
	uppDataHGetDataRefProcInfo = 0x000003F0,
	uppDataHCompareDataRefProcInfo = 0x00000FF0,
	uppDataHTaskProcInfo = 0x000000F0,
	uppDataHScheduleDataProcInfo = 0x000FFFF0,
	uppDataHFinishDataProcInfo = 0x000007F0,
	uppDataHFlushCacheProcInfo = 0x000000F0,
	uppDataHResolveDataRefProcInfo = 0x00001FF0,
	uppDataHGetFileSizeProcInfo = 0x000003F0,
	uppDataHCanUseDataRefProcInfo = 0x00000FF0,
	uppDataHGetVolumeListProcInfo = 0x000003F0,
	uppDataHWriteProcInfo = 0x0003FFF0,
	uppDataHPreextendProcInfo = 0x00000FF0,
	uppDataHSetFileSizeProcInfo = 0x000003F0,
	uppDataHGetFreeSpaceProcInfo = 0x000003F0,
	uppDataHCreateFileProcInfo = 0x000007F0,
	uppDataHGetPreferredBlockSizeProcInfo = 0x000003F0,
	uppDataHGetDeviceIndexProcInfo = 0x000003F0,
	uppDataHIsStreamingDataHandlerProcInfo = 0x000003F0,
	uppDataHGetDataInBufferProcInfo = 0x00000FF0,
	uppDataHGetScheduleAheadTimeProcInfo = 0x000003F0,
	uppDataHSetCacheSizeLimitProcInfo = 0x000003F0,
	uppDataHGetCacheSizeLimitProcInfo = 0x000003F0,
	uppDataHGetMovieProcInfo = 0x00000FF0,
	uppDataHAddMovieProcInfo = 0x00000FF0,
	uppDataHUpdateMovieProcInfo = 0x00000BF0,
	uppDataHDoesBufferProcInfo = 0x00000FF0,
	uppDataHGetFileNameProcInfo = 0x000003F0,
	uppDataHGetAvailableFileSizeProcInfo = 0x000003F0,
	uppDataHGetMacOSFileTypeProcInfo = 0x000003F0,
	uppDataHGetMIMETypeProcInfo = 0x000003F0,
	uppDataHSetDataRefWithAnchorProcInfo = 0x00003FF0,
	uppDataHGetDataRefWithAnchorProcInfo = 0x00003FF0,
	uppDataHSetMacOSFileTypeProcInfo = 0x000003F0,
	uppDataHSetTimeBaseProcInfo = 0x000003F0,
	uppDataHGetInfoFlagsProcInfo = 0x000003F0,
	uppDataHScheduleData64ProcInfo = 0x000FFFF0,
	uppDataHWrite64ProcInfo = 0x0003FFF0,
	uppDataHGetFileSize64ProcInfo = 0x000003F0,
	uppDataHPreextend64ProcInfo = 0x00000FF0,
	uppDataHSetFileSize64ProcInfo = 0x000003F0,
	uppDataHGetFreeSpace64ProcInfo = 0x000003F0,
	uppDataHAppend64ProcInfo = 0x00003FF0,
	uppDataHReadAsyncProcInfo = 0x0003FFF0,
	uppDataHPollReadProcInfo = 0x00000FF0,
	uppDataHGetDataAvailabilityProcInfo = 0x0000FFF0,
	uppDataHGetFileSizeAsyncProcInfo = 0x00003FF0,
	uppDataHGetDataRefAsTypeProcInfo = 0x00000FF0,
	uppDataHSetDataRefExtensionProcInfo = 0x00000FF0,
	uppDataHGetDataRefExtensionProcInfo = 0x00000FF0,
	uppDataHGetMovieWithFlagsProcInfo = 0x00002FF0,
	uppDataHGetFileTypeOrderingProcInfo = 0x000003F0,
	uppDataHCreateFileWithFlagsProcInfo = 0x000037F0,
	uppDataHGetMIMETypeAsyncProcInfo = 0x00003FF0,
	uppDataHGetInfoProcInfo = 0x00000FF0,
	uppDataHSetIdleManagerProcInfo = 0x000003F0,
	uppDataHDeleteFileProcInfo = 0x000000F0,
	uppDataHSetMovieUsageFlagsProcInfo = 0x000003F0,
	uppDataHUseTemporaryDataRefProcInfo = 0x000003F0,
	uppDataHGetTemporaryDataRefCapabilitiesProcInfo = 0x000003F0,
	uppDataHRenameFileProcInfo = 0x000003F0,
	uppDataHGetAvailableFileSize64ProcInfo = 0x000003F0,
	uppDataHGetDataAvailability64ProcInfo = 0x0000FFF0,
	uppDataHPlaybackHintsProcInfo = 0x0000FFF0,
	uppDataHPlaybackHints64ProcInfo = 0x0000FFF0,
	uppDataHGetDataRateProcInfo = 0x00000FF0,
	uppDataHSetTimeHintsProcInfo = 0x0003FFF0,
	uppVDGetMaxSrcRectProcInfo = 0x00000EF0,
	uppVDGetActiveSrcRectProcInfo = 0x00000EF0,
	uppVDSetDigitizerRectProcInfo = 0x000003F0,
	uppVDGetDigitizerRectProcInfo = 0x000003F0,
	uppVDGetVBlankRectProcInfo = 0x00000EF0,
	uppVDGetMaskPixMapProcInfo = 0x000003F0,
	uppVDGetPlayThruDestinationProcInfo = 0x0000FFF0,
	uppVDUseThisCLUTProcInfo = 0x000003F0,
	uppVDSetInputGammaValueProcInfo = 0x00003FF0,
	uppVDGetInputGammaValueProcInfo = 0x00003FF0,
	uppVDSetBrightnessProcInfo = 0x000003F0,
	uppVDGetBrightnessProcInfo = 0x000003F0,
	uppVDSetContrastProcInfo = 0x000003F0,
	uppVDSetHueProcInfo = 0x000003F0,
	uppVDSetSharpnessProcInfo = 0x000003F0,
	uppVDSetSaturationProcInfo = 0x000003F0,
	uppVDGetContrastProcInfo = 0x000003F0,
	uppVDGetHueProcInfo = 0x000003F0,
	uppVDGetSharpnessProcInfo = 0x000003F0,
	uppVDGetSaturationProcInfo = 0x000003F0,
	uppVDGrabOneFrameProcInfo = 0x000000F0,
	uppVDGetMaxAuxBufferProcInfo = 0x00000FF0,
	uppVDGetDigitizerInfoProcInfo = 0x000003F0,
	uppVDGetCurrentFlagsProcInfo = 0x00000FF0,
	uppVDSetKeyColorProcInfo = 0x000003F0,
	uppVDGetKeyColorProcInfo = 0x000003F0,
	uppVDAddKeyColorProcInfo = 0x000003F0,
	uppVDGetNextKeyColorProcInfo = 0x000003F0,
	uppVDSetKeyColorRangeProcInfo = 0x00000FF0,
	uppVDGetKeyColorRangeProcInfo = 0x00000FF0,
	uppVDSetDigitizerUserInterruptProcInfo = 0x00003FF0,
	uppVDSetInputColorSpaceModeProcInfo = 0x000002F0,
	uppVDGetInputColorSpaceModeProcInfo = 0x000003F0,
	uppVDSetClipStateProcInfo = 0x000002F0,
	uppVDGetClipStateProcInfo = 0x000003F0,
	uppVDSetClipRgnProcInfo = 0x000003F0,
	uppVDClearClipRgnProcInfo = 0x000003F0,
	uppVDGetCLUTInUseProcInfo = 0x000003F0,
	uppVDSetPLLFilterTypeProcInfo = 0x000002F0,
	uppVDGetPLLFilterTypeProcInfo = 0x000003F0,
	uppVDGetMaskandValueProcInfo = 0x00003EF0,
	uppVDSetMasterBlendLevelProcInfo = 0x000003F0,
	uppVDSetPlayThruDestinationProcInfo = 0x0000FFF0,
	uppVDSetPlayThruOnOffProcInfo = 0x000002F0,
	uppVDSetFieldPreferenceProcInfo = 0x000002F0,
	uppVDGetFieldPreferenceProcInfo = 0x000003F0,
	uppVDPreflightDestinationProcInfo = 0x0000FFF0,
	uppVDPreflightGlobalRectProcInfo = 0x00000FF0,
	uppVDSetPlayThruGlobalRectProcInfo = 0x00000FF0,
	uppVDSetInputGammaRecordProcInfo = 0x000003F0,
	uppVDGetInputGammaRecordProcInfo = 0x000003F0,
	uppVDSetBlackLevelValueProcInfo = 0x000003F0,
	uppVDGetBlackLevelValueProcInfo = 0x000003F0,
	uppVDSetWhiteLevelValueProcInfo = 0x000003F0,
	uppVDGetWhiteLevelValueProcInfo = 0x000003F0,
	uppVDGetVideoDefaultsProcInfo = 0x003FFFF0,
	uppVDGetNumberOfInputsProcInfo = 0x000003F0,
	uppVDGetInputFormatProcInfo = 0x00000EF0,
	uppVDSetInputProcInfo = 0x000002F0,
	uppVDGetInputProcInfo = 0x000003F0,
	uppVDSetInputStandardProcInfo = 0x000002F0,
	uppVDSetupBuffersProcInfo = 0x000003F0,
	uppVDGrabOneFrameAsyncProcInfo = 0x000002F0,
	uppVDDoneProcInfo = 0x000002F0,
	uppVDSetCompressionProcInfo = 0x000FFBF0,
	uppVDCompressOneFrameAsyncProcInfo = 0x000000F0,
	uppVDCompressDoneProcInfo = 0x0003FFF0,
	uppVDReleaseCompressBufferProcInfo = 0x000003F0,
	uppVDGetImageDescriptionProcInfo = 0x000003F0,
	uppVDResetCompressSequenceProcInfo = 0x000000F0,
	uppVDSetCompressionOnOffProcInfo = 0x000001F0,
	uppVDGetCompressionTypesProcInfo = 0x000003F0,
	uppVDSetTimeBaseProcInfo = 0x000003F0,
	uppVDSetFrameRateProcInfo = 0x000003F0,
	uppVDGetDataRateProcInfo = 0x00003FF0,
	uppVDGetSoundInputDriverProcInfo = 0x000003F0,
	uppVDGetDMADepthsProcInfo = 0x00000FF0,
	uppVDGetPreferredTimeScaleProcInfo = 0x000003F0,
	uppVDReleaseAsyncBuffersProcInfo = 0x000000F0,
	uppVDSetDataRateProcInfo = 0x000003F0,
	uppVDGetTimeCodeProcInfo = 0x00003FF0,
	uppVDUseSafeBuffersProcInfo = 0x000001F0,
	uppVDGetSoundInputSourceProcInfo = 0x00000FF0,
	uppVDGetCompressionTimeProcInfo = 0x000FFBF0,
	uppVDSetPreferredPacketSizeProcInfo = 0x000003F0,
	uppVDSetPreferredImageDimensionsProcInfo = 0x00000FF0,
	uppVDGetPreferredImageDimensionsProcInfo = 0x00000FF0,
	uppVDGetInputNameProcInfo = 0x00000FF0,
	uppVDSetDestinationPortProcInfo = 0x000003F0,
	uppVDGetDeviceNameAndFlagsProcInfo = 0x00000FF0,
	uppVDCaptureStateChangingProcInfo = 0x000003F0,
	uppVDGetUniqueIDsProcInfo = 0x00000FF0,
	uppVDSelectUniqueIDsProcInfo = 0x00000FF0,
	uppVDCopyPreferredAudioDeviceProcInfo = 0x000003F0
};

/*
	Example usage:

		#define VDIIDC_BASENAME()	Fred
		#define VDIIDC_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeComponents.k.h>

	To specify that your component implementation does not use globals, do not #define VDIIDC_GLOBALS
*/
#ifdef VDIIDC_BASENAME
	#ifndef VDIIDC_GLOBALS
		#define VDIIDC_GLOBALS() 
		#define ADD_VDIIDC_COMMA 
	#else
		#define ADD_VDIIDC_COMMA ,
	#endif
	#define VDIIDC_GLUE(a,b) a##b
	#define VDIIDC_STRCAT(a,b) VDIIDC_GLUE(a,b)
	#define ADD_VDIIDC_BASENAME(name) VDIIDC_STRCAT(VDIIDC_BASENAME(),name)

	EXTERN_API( VideoDigitizerError  ) ADD_VDIIDC_BASENAME(GetFeatures) (VDIIDC_GLOBALS() ADD_VDIIDC_COMMA QTAtomContainer * container);

	EXTERN_API( VideoDigitizerError  ) ADD_VDIIDC_BASENAME(SetFeatures) (VDIIDC_GLOBALS() ADD_VDIIDC_COMMA QTAtomContainer  container);

	EXTERN_API( VideoDigitizerError  ) ADD_VDIIDC_BASENAME(GetDefaultFeatures) (VDIIDC_GLOBALS() ADD_VDIIDC_COMMA QTAtomContainer * container);

	EXTERN_API( VideoDigitizerError  ) ADD_VDIIDC_BASENAME(GetCSRData) (VDIIDC_GLOBALS() ADD_VDIIDC_COMMA Boolean  offsetFromUnitBase, UInt32  offset, UInt32 * data);

	EXTERN_API( VideoDigitizerError  ) ADD_VDIIDC_BASENAME(SetCSRData) (VDIIDC_GLOBALS() ADD_VDIIDC_COMMA Boolean  offsetFromUnitBase, UInt32  offset, UInt32  data);

	EXTERN_API( VideoDigitizerError  ) ADD_VDIIDC_BASENAME(GetFeaturesForSpecifier) (VDIIDC_GLOBALS() ADD_VDIIDC_COMMA OSType  specifier, QTAtomContainer * container);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppVDIIDCGetFeaturesProcInfo = 0x000003F0,
		uppVDIIDCSetFeaturesProcInfo = 0x000003F0,
		uppVDIIDCGetDefaultFeaturesProcInfo = 0x000003F0,
		uppVDIIDCGetCSRDataProcInfo = 0x00003DF0,
		uppVDIIDCSetCSRDataProcInfo = 0x00003DF0,
		uppVDIIDCGetFeaturesForSpecifierProcInfo = 0x00000FF0
	};

#endif	/* VDIIDC_BASENAME */

/*
	Example usage:

		#define XMLPARSE_BASENAME()	Fred
		#define XMLPARSE_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeComponents.k.h>

	To specify that your component implementation does not use globals, do not #define XMLPARSE_GLOBALS
*/
#ifdef XMLPARSE_BASENAME
	#ifndef XMLPARSE_GLOBALS
		#define XMLPARSE_GLOBALS() 
		#define ADD_XMLPARSE_COMMA 
	#else
		#define ADD_XMLPARSE_COMMA ,
	#endif
	#define XMLPARSE_GLUE(a,b) a##b
	#define XMLPARSE_STRCAT(a,b) XMLPARSE_GLUE(a,b)
	#define ADD_XMLPARSE_BASENAME(name) XMLPARSE_STRCAT(XMLPARSE_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_XMLPARSE_BASENAME(DataRef) (XMLPARSE_GLOBALS() ADD_XMLPARSE_COMMA Handle  dataRef, OSType  dataRefType, long  parseFlags, XMLDoc * document);

	EXTERN_API( ComponentResult  ) ADD_XMLPARSE_BASENAME(File) (XMLPARSE_GLOBALS() ADD_XMLPARSE_COMMA ConstFSSpecPtr  fileSpec, long  parseFlags, XMLDoc * document);

	EXTERN_API( ComponentResult  ) ADD_XMLPARSE_BASENAME(DisposeXMLDoc) (XMLPARSE_GLOBALS() ADD_XMLPARSE_COMMA XMLDoc  document);

	EXTERN_API( ComponentResult  ) ADD_XMLPARSE_BASENAME(GetDetailedParseError) (XMLPARSE_GLOBALS() ADD_XMLPARSE_COMMA long * errorLine, StringPtr  errDesc);

	EXTERN_API( ComponentResult  ) ADD_XMLPARSE_BASENAME(AddElement) (XMLPARSE_GLOBALS() ADD_XMLPARSE_COMMA char * elementName, UInt32  nameSpaceID, UInt32 * elementID, long  elementFlags);

	EXTERN_API( ComponentResult  ) ADD_XMLPARSE_BASENAME(AddAttribute) (XMLPARSE_GLOBALS() ADD_XMLPARSE_COMMA UInt32  elementID, UInt32  nameSpaceID, char * attributeName, UInt32 * attributeID);

	EXTERN_API( ComponentResult  ) ADD_XMLPARSE_BASENAME(AddMultipleAttributes) (XMLPARSE_GLOBALS() ADD_XMLPARSE_COMMA UInt32  elementID, UInt32 * nameSpaceIDs, char * attributeNames, UInt32 * attributeIDs);

	EXTERN_API( ComponentResult  ) ADD_XMLPARSE_BASENAME(AddAttributeAndValue) (XMLPARSE_GLOBALS() ADD_XMLPARSE_COMMA UInt32  elementID, UInt32  nameSpaceID, char * attributeName, UInt32 * attributeID, UInt32  attributeValueKind, void * attributeValueKindInfo);

	EXTERN_API( ComponentResult  ) ADD_XMLPARSE_BASENAME(AddMultipleAttributesAndValues) (XMLPARSE_GLOBALS() ADD_XMLPARSE_COMMA UInt32  elementID, UInt32 * nameSpaceIDs, char * attributeNames, UInt32 * attributeIDs, UInt32 * attributeValueKinds, void ** attributeValueKindInfos);

	EXTERN_API( ComponentResult  ) ADD_XMLPARSE_BASENAME(AddAttributeValueKind) (XMLPARSE_GLOBALS() ADD_XMLPARSE_COMMA UInt32  elementID, UInt32  attributeID, UInt32  attributeValueKind, void * attributeValueKindInfo);

	EXTERN_API( ComponentResult  ) ADD_XMLPARSE_BASENAME(AddNameSpace) (XMLPARSE_GLOBALS() ADD_XMLPARSE_COMMA char * nameSpaceURL, UInt32 * nameSpaceID);

	EXTERN_API( ComponentResult  ) ADD_XMLPARSE_BASENAME(SetOffsetAndLimit) (XMLPARSE_GLOBALS() ADD_XMLPARSE_COMMA UInt32  offset, UInt32  limit);

	EXTERN_API( ComponentResult  ) ADD_XMLPARSE_BASENAME(SetEventParseRefCon) (XMLPARSE_GLOBALS() ADD_XMLPARSE_COMMA long  refcon);

	EXTERN_API( ComponentResult  ) ADD_XMLPARSE_BASENAME(SetStartDocumentHandler) (XMLPARSE_GLOBALS() ADD_XMLPARSE_COMMA StartDocumentHandlerUPP  startDocument);

	EXTERN_API( ComponentResult  ) ADD_XMLPARSE_BASENAME(SetEndDocumentHandler) (XMLPARSE_GLOBALS() ADD_XMLPARSE_COMMA EndDocumentHandlerUPP  endDocument);

	EXTERN_API( ComponentResult  ) ADD_XMLPARSE_BASENAME(SetStartElementHandler) (XMLPARSE_GLOBALS() ADD_XMLPARSE_COMMA StartElementHandlerUPP  startElement);

	EXTERN_API( ComponentResult  ) ADD_XMLPARSE_BASENAME(SetEndElementHandler) (XMLPARSE_GLOBALS() ADD_XMLPARSE_COMMA EndElementHandlerUPP  endElement);

	EXTERN_API( ComponentResult  ) ADD_XMLPARSE_BASENAME(SetCharDataHandler) (XMLPARSE_GLOBALS() ADD_XMLPARSE_COMMA CharDataHandlerUPP  charData);

	EXTERN_API( ComponentResult  ) ADD_XMLPARSE_BASENAME(SetPreprocessInstructionHandler) (XMLPARSE_GLOBALS() ADD_XMLPARSE_COMMA PreprocessInstructionHandlerUPP  preprocessInstruction);

	EXTERN_API( ComponentResult  ) ADD_XMLPARSE_BASENAME(SetCommentHandler) (XMLPARSE_GLOBALS() ADD_XMLPARSE_COMMA CommentHandlerUPP  comment);

	EXTERN_API( ComponentResult  ) ADD_XMLPARSE_BASENAME(SetCDataHandler) (XMLPARSE_GLOBALS() ADD_XMLPARSE_COMMA CDataHandlerUPP  cdata);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppXMLParseDataRefProcInfo = 0x0000FFF0,
		uppXMLParseFileProcInfo = 0x00003FF0,
		uppXMLParseDisposeXMLDocProcInfo = 0x000003F0,
		uppXMLParseGetDetailedParseErrorProcInfo = 0x00000FF0,
		uppXMLParseAddElementProcInfo = 0x0000FFF0,
		uppXMLParseAddAttributeProcInfo = 0x0000FFF0,
		uppXMLParseAddMultipleAttributesProcInfo = 0x0000FFF0,
		uppXMLParseAddAttributeAndValueProcInfo = 0x000FFFF0,
		uppXMLParseAddMultipleAttributesAndValuesProcInfo = 0x000FFFF0,
		uppXMLParseAddAttributeValueKindProcInfo = 0x0000FFF0,
		uppXMLParseAddNameSpaceProcInfo = 0x00000FF0,
		uppXMLParseSetOffsetAndLimitProcInfo = 0x00000FF0,
		uppXMLParseSetEventParseRefConProcInfo = 0x000003F0,
		uppXMLParseSetStartDocumentHandlerProcInfo = 0x000003F0,
		uppXMLParseSetEndDocumentHandlerProcInfo = 0x000003F0,
		uppXMLParseSetStartElementHandlerProcInfo = 0x000003F0,
		uppXMLParseSetEndElementHandlerProcInfo = 0x000003F0,
		uppXMLParseSetCharDataHandlerProcInfo = 0x000003F0,
		uppXMLParseSetPreprocessInstructionHandlerProcInfo = 0x000003F0,
		uppXMLParseSetCommentHandlerProcInfo = 0x000003F0,
		uppXMLParseSetCDataHandlerProcInfo = 0x000003F0
	};

#endif	/* XMLPARSE_BASENAME */

/*
	Example usage:

		#define SG_BASENAME()	Fred
		#define SG_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeComponents.k.h>

	To specify that your component implementation does not use globals, do not #define SG_GLOBALS
*/
#ifdef SG_BASENAME
	#ifndef SG_GLOBALS
		#define SG_GLOBALS() 
		#define ADD_SG_COMMA 
	#else
		#define ADD_SG_COMMA ,
	#endif
	#define SG_GLUE(a,b) a##b
	#define SG_STRCAT(a,b) SG_GLUE(a,b)
	#define ADD_SG_BASENAME(name) SG_STRCAT(SG_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(Initialize) (SG_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetDataOutput) (SG_GLOBALS() ADD_SG_COMMA const FSSpec * movieFile, long  whereFlags);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetDataOutput) (SG_GLOBALS() ADD_SG_COMMA FSSpec * movieFile, long * whereFlags);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetGWorld) (SG_GLOBALS() ADD_SG_COMMA CGrafPtr  gp, GDHandle  gd);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetGWorld) (SG_GLOBALS() ADD_SG_COMMA CGrafPtr * gp, GDHandle * gd);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(NewChannel) (SG_GLOBALS() ADD_SG_COMMA OSType  channelType, SGChannel * ref);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(DisposeChannel) (SG_GLOBALS() ADD_SG_COMMA SGChannel  c);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(StartPreview) (SG_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(StartRecord) (SG_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(Idle) (SG_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(Stop) (SG_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(Pause) (SG_GLOBALS() ADD_SG_COMMA Byte  pause);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(Prepare) (SG_GLOBALS() ADD_SG_COMMA Boolean  prepareForPreview, Boolean  prepareForRecord);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(Release) (SG_GLOBALS());

	EXTERN_API( Movie  ) ADD_SG_BASENAME(GetMovie) (SG_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetMaximumRecordTime) (SG_GLOBALS() ADD_SG_COMMA unsigned long  ticks);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetMaximumRecordTime) (SG_GLOBALS() ADD_SG_COMMA unsigned long * ticks);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetStorageSpaceRemaining) (SG_GLOBALS() ADD_SG_COMMA unsigned long * bytes);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetTimeRemaining) (SG_GLOBALS() ADD_SG_COMMA long * ticksLeft);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GrabPict) (SG_GLOBALS() ADD_SG_COMMA PicHandle * p, const Rect * bounds, short  offscreenDepth, long  grabPictFlags);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetLastMovieResID) (SG_GLOBALS() ADD_SG_COMMA short * resID);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetFlags) (SG_GLOBALS() ADD_SG_COMMA long  sgFlags);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetFlags) (SG_GLOBALS() ADD_SG_COMMA long * sgFlags);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetDataProc) (SG_GLOBALS() ADD_SG_COMMA SGDataUPP  proc, long  refCon);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(NewChannelFromComponent) (SG_GLOBALS() ADD_SG_COMMA SGChannel * newChannel, Component  sgChannelComponent);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(DisposeDeviceList) (SG_GLOBALS() ADD_SG_COMMA SGDeviceList  list);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(AppendDeviceListToMenu) (SG_GLOBALS() ADD_SG_COMMA SGDeviceList  list, MenuRef  mh);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetSettings) (SG_GLOBALS() ADD_SG_COMMA UserData  ud, long  flags);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetSettings) (SG_GLOBALS() ADD_SG_COMMA UserData * ud, long  flags);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetIndChannel) (SG_GLOBALS() ADD_SG_COMMA short  index, SGChannel * ref, OSType * chanType);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(Update) (SG_GLOBALS() ADD_SG_COMMA RgnHandle  updateRgn);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetPause) (SG_GLOBALS() ADD_SG_COMMA Byte * paused);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SettingsDialog) (SG_GLOBALS() ADD_SG_COMMA SGChannel  c, short  numPanels, ConstComponentListPtr  panelList, long  flags, SGModalFilterUPP  proc, long  procRefNum);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetAlignmentProc) (SG_GLOBALS() ADD_SG_COMMA ICMAlignmentProcRecordPtr  alignmentProc);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetChannelSettings) (SG_GLOBALS() ADD_SG_COMMA SGChannel  c, UserData  ud, long  flags);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetChannelSettings) (SG_GLOBALS() ADD_SG_COMMA SGChannel  c, UserData * ud, long  flags);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetMode) (SG_GLOBALS() ADD_SG_COMMA Boolean * previewMode, Boolean * recordMode);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetDataRef) (SG_GLOBALS() ADD_SG_COMMA Handle  dataRef, OSType  dataRefType, long  whereFlags);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetDataRef) (SG_GLOBALS() ADD_SG_COMMA Handle * dataRef, OSType * dataRefType, long * whereFlags);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(NewOutput) (SG_GLOBALS() ADD_SG_COMMA Handle  dataRef, OSType  dataRefType, long  whereFlags, SGOutput * sgOut);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(DisposeOutput) (SG_GLOBALS() ADD_SG_COMMA SGOutput  sgOut);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetOutputFlags) (SG_GLOBALS() ADD_SG_COMMA SGOutput  sgOut, long  whereFlags);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetChannelOutput) (SG_GLOBALS() ADD_SG_COMMA SGChannel  c, SGOutput  sgOut);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetDataOutputStorageSpaceRemaining) (SG_GLOBALS() ADD_SG_COMMA SGOutput  sgOut, unsigned long * space);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(HandleUpdateEvent) (SG_GLOBALS() ADD_SG_COMMA const EventRecord * event, Boolean * handled);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetOutputNextOutput) (SG_GLOBALS() ADD_SG_COMMA SGOutput  sgOut, SGOutput  nextOut);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetOutputNextOutput) (SG_GLOBALS() ADD_SG_COMMA SGOutput  sgOut, SGOutput * nextOut);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetOutputMaximumOffset) (SG_GLOBALS() ADD_SG_COMMA SGOutput  sgOut, const wide * maxOffset);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetOutputMaximumOffset) (SG_GLOBALS() ADD_SG_COMMA SGOutput  sgOut, wide * maxOffset);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetOutputDataReference) (SG_GLOBALS() ADD_SG_COMMA SGOutput  sgOut, Handle * dataRef, OSType * dataRefType);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(WriteExtendedMovieData) (SG_GLOBALS() ADD_SG_COMMA SGChannel  c, Ptr  p, long  len, wide * offset, SGOutput * sgOut);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetStorageSpaceRemaining64) (SG_GLOBALS() ADD_SG_COMMA wide * bytes);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetDataOutputStorageSpaceRemaining64) (SG_GLOBALS() ADD_SG_COMMA SGOutput  sgOut, wide * space);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(WriteMovieData) (SG_GLOBALS() ADD_SG_COMMA SGChannel  c, Ptr  p, long  len, long * offset);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(AddFrameReference) (SG_GLOBALS() ADD_SG_COMMA SeqGrabFrameInfoPtr  frameInfo);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetNextFrameReference) (SG_GLOBALS() ADD_SG_COMMA SeqGrabFrameInfoPtr  frameInfo, TimeValue * frameDuration, long * frameNumber);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetTimeBase) (SG_GLOBALS() ADD_SG_COMMA TimeBase * tb);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SortDeviceList) (SG_GLOBALS() ADD_SG_COMMA SGDeviceList  list);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(AddMovieData) (SG_GLOBALS() ADD_SG_COMMA SGChannel  c, Ptr  p, long  len, long * offset, long  chRefCon, TimeValue  time, short  writeType);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(ChangedSource) (SG_GLOBALS() ADD_SG_COMMA SGChannel  c);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(AddExtendedFrameReference) (SG_GLOBALS() ADD_SG_COMMA SeqGrabExtendedFrameInfoPtr  frameInfo);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetNextExtendedFrameReference) (SG_GLOBALS() ADD_SG_COMMA SeqGrabExtendedFrameInfoPtr  frameInfo, TimeValue * frameDuration, long * frameNumber);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(AddExtendedMovieData) (SG_GLOBALS() ADD_SG_COMMA SGChannel  c, Ptr  p, long  len, wide * offset, long  chRefCon, TimeValue  time, short  writeType, SGOutput * whichOutput);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(AddOutputDataRefToMedia) (SG_GLOBALS() ADD_SG_COMMA SGOutput  sgOut, Media  theMedia, SampleDescriptionHandle  desc);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetSettingsSummary) (SG_GLOBALS() ADD_SG_COMMA Handle  summaryText);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetChannelUsage) (SG_GLOBALS() ADD_SG_COMMA long  usage);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetChannelUsage) (SG_GLOBALS() ADD_SG_COMMA long * usage);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetChannelBounds) (SG_GLOBALS() ADD_SG_COMMA const Rect * bounds);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetChannelBounds) (SG_GLOBALS() ADD_SG_COMMA Rect * bounds);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetChannelVolume) (SG_GLOBALS() ADD_SG_COMMA short  volume);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetChannelVolume) (SG_GLOBALS() ADD_SG_COMMA short * volume);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetChannelInfo) (SG_GLOBALS() ADD_SG_COMMA long * channelInfo);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetChannelPlayFlags) (SG_GLOBALS() ADD_SG_COMMA long  playFlags);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetChannelPlayFlags) (SG_GLOBALS() ADD_SG_COMMA long * playFlags);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetChannelMaxFrames) (SG_GLOBALS() ADD_SG_COMMA long  frameCount);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetChannelMaxFrames) (SG_GLOBALS() ADD_SG_COMMA long * frameCount);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetChannelRefCon) (SG_GLOBALS() ADD_SG_COMMA long  refCon);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetChannelClip) (SG_GLOBALS() ADD_SG_COMMA RgnHandle  theClip);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetChannelClip) (SG_GLOBALS() ADD_SG_COMMA RgnHandle * theClip);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetChannelSampleDescription) (SG_GLOBALS() ADD_SG_COMMA Handle  sampleDesc);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetChannelDeviceList) (SG_GLOBALS() ADD_SG_COMMA long  selectionFlags, SGDeviceList * list);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetChannelDevice) (SG_GLOBALS() ADD_SG_COMMA StringPtr  name);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetChannelMatrix) (SG_GLOBALS() ADD_SG_COMMA const MatrixRecord * m);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetChannelMatrix) (SG_GLOBALS() ADD_SG_COMMA MatrixRecord * m);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetChannelTimeScale) (SG_GLOBALS() ADD_SG_COMMA TimeScale * scale);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(ChannelPutPicture) (SG_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(ChannelSetRequestedDataRate) (SG_GLOBALS() ADD_SG_COMMA long  bytesPerSecond);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(ChannelGetRequestedDataRate) (SG_GLOBALS() ADD_SG_COMMA long * bytesPerSecond);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(ChannelSetDataSourceName) (SG_GLOBALS() ADD_SG_COMMA ConstStr255Param  name, ScriptCode  scriptTag);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(ChannelGetDataSourceName) (SG_GLOBALS() ADD_SG_COMMA Str255  name, ScriptCode * scriptTag);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(ChannelSetCodecSettings) (SG_GLOBALS() ADD_SG_COMMA Handle  settings);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(ChannelGetCodecSettings) (SG_GLOBALS() ADD_SG_COMMA Handle * settings);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetChannelTimeBase) (SG_GLOBALS() ADD_SG_COMMA TimeBase * tb);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetChannelRefCon) (SG_GLOBALS() ADD_SG_COMMA long * refCon);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetChannelDeviceAndInputNames) (SG_GLOBALS() ADD_SG_COMMA Str255  outDeviceName, Str255  outInputName, short * outInputNumber);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetChannelDeviceInput) (SG_GLOBALS() ADD_SG_COMMA short  inInputNumber);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetChannelSettingsStateChanging) (SG_GLOBALS() ADD_SG_COMMA UInt32  inFlags);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(InitChannel) (SG_GLOBALS() ADD_SG_COMMA SeqGrabComponent  owner);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(WriteSamples) (SG_GLOBALS() ADD_SG_COMMA Movie  m, AliasHandle  theFile);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetDataRate) (SG_GLOBALS() ADD_SG_COMMA long * bytesPerSecond);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(AlignChannelRect) (SG_GLOBALS() ADD_SG_COMMA Rect * r);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(PanelGetDitl) (SG_GLOBALS() ADD_SG_COMMA Handle * ditl);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(PanelGetTitle) (SG_GLOBALS() ADD_SG_COMMA Str255  title);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(PanelCanRun) (SG_GLOBALS() ADD_SG_COMMA SGChannel  c);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(PanelInstall) (SG_GLOBALS() ADD_SG_COMMA SGChannel  c, DialogRef  d, short  itemOffset);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(PanelEvent) (SG_GLOBALS() ADD_SG_COMMA SGChannel  c, DialogRef  d, short  itemOffset, const EventRecord * theEvent, short * itemHit, Boolean * handled);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(PanelItem) (SG_GLOBALS() ADD_SG_COMMA SGChannel  c, DialogRef  d, short  itemOffset, short  itemNum);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(PanelRemove) (SG_GLOBALS() ADD_SG_COMMA SGChannel  c, DialogRef  d, short  itemOffset);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(PanelSetGrabber) (SG_GLOBALS() ADD_SG_COMMA SeqGrabComponent  sg);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(PanelSetResFile) (SG_GLOBALS() ADD_SG_COMMA short  resRef);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(PanelGetSettings) (SG_GLOBALS() ADD_SG_COMMA SGChannel  c, UserData * ud, long  flags);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(PanelSetSettings) (SG_GLOBALS() ADD_SG_COMMA SGChannel  c, UserData  ud, long  flags);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(PanelValidateInput) (SG_GLOBALS() ADD_SG_COMMA Boolean * ok);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(PanelSetEventFilter) (SG_GLOBALS() ADD_SG_COMMA SGModalFilterUPP  proc, long  refCon);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(PanelGetDITLForSize) (SG_GLOBALS() ADD_SG_COMMA Handle * ditl, Point * requestedSize);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetSrcVideoBounds) (SG_GLOBALS() ADD_SG_COMMA Rect * r);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetVideoRect) (SG_GLOBALS() ADD_SG_COMMA const Rect * r);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetVideoRect) (SG_GLOBALS() ADD_SG_COMMA Rect * r);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetVideoCompressorType) (SG_GLOBALS() ADD_SG_COMMA OSType * compressorType);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetVideoCompressorType) (SG_GLOBALS() ADD_SG_COMMA OSType  compressorType);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetVideoCompressor) (SG_GLOBALS() ADD_SG_COMMA short  depth, CompressorComponent  compressor, CodecQ  spatialQuality, CodecQ  temporalQuality, long  keyFrameRate);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetVideoCompressor) (SG_GLOBALS() ADD_SG_COMMA short * depth, CompressorComponent * compressor, CodecQ * spatialQuality, CodecQ * temporalQuality, long * keyFrameRate);

	EXTERN_API( ComponentInstance  ) ADD_SG_BASENAME(GetVideoDigitizerComponent) (SG_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetVideoDigitizerComponent) (SG_GLOBALS() ADD_SG_COMMA ComponentInstance  vdig);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(VideoDigitizerChanged) (SG_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetVideoBottlenecks) (SG_GLOBALS() ADD_SG_COMMA VideoBottles * vb);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetVideoBottlenecks) (SG_GLOBALS() ADD_SG_COMMA VideoBottles * vb);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GrabFrame) (SG_GLOBALS() ADD_SG_COMMA short  bufferNum);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GrabFrameComplete) (SG_GLOBALS() ADD_SG_COMMA short  bufferNum, Boolean * done);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(DisplayFrame) (SG_GLOBALS() ADD_SG_COMMA short  bufferNum, const MatrixRecord * mp, RgnHandle  clipRgn);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(CompressFrame) (SG_GLOBALS() ADD_SG_COMMA short  bufferNum);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(CompressFrameComplete) (SG_GLOBALS() ADD_SG_COMMA short  bufferNum, Boolean * done, SGCompressInfo * ci);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(AddFrame) (SG_GLOBALS() ADD_SG_COMMA short  bufferNum, TimeValue  atTime, TimeScale  scale, const SGCompressInfo * ci);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(TransferFrameForCompress) (SG_GLOBALS() ADD_SG_COMMA short  bufferNum, const MatrixRecord * mp, RgnHandle  clipRgn);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetCompressBuffer) (SG_GLOBALS() ADD_SG_COMMA short  depth, const Rect * compressSize);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetCompressBuffer) (SG_GLOBALS() ADD_SG_COMMA short * depth, Rect * compressSize);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetBufferInfo) (SG_GLOBALS() ADD_SG_COMMA short  bufferNum, PixMapHandle * bufferPM, Rect * bufferRect, GWorldPtr * compressBuffer, Rect * compressBufferRect);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetUseScreenBuffer) (SG_GLOBALS() ADD_SG_COMMA Boolean  useScreenBuffer);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetUseScreenBuffer) (SG_GLOBALS() ADD_SG_COMMA Boolean * useScreenBuffer);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GrabCompressComplete) (SG_GLOBALS() ADD_SG_COMMA UInt8 * queuedFrameCount, SGCompressInfo * ci, TimeRecord * tr);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(DisplayCompress) (SG_GLOBALS() ADD_SG_COMMA Ptr  dataPtr, ImageDescriptionHandle  desc, MatrixRecord * mp, RgnHandle  clipRgn);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetFrameRate) (SG_GLOBALS() ADD_SG_COMMA Fixed  frameRate);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetFrameRate) (SG_GLOBALS() ADD_SG_COMMA Fixed * frameRate);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetPreferredPacketSize) (SG_GLOBALS() ADD_SG_COMMA long  preferredPacketSizeInBytes);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetPreferredPacketSize) (SG_GLOBALS() ADD_SG_COMMA long * preferredPacketSizeInBytes);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetUserVideoCompressorList) (SG_GLOBALS() ADD_SG_COMMA Handle  compressorTypes);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetUserVideoCompressorList) (SG_GLOBALS() ADD_SG_COMMA Handle * compressorTypes);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetSoundInputDriver) (SG_GLOBALS() ADD_SG_COMMA ConstStr255Param  driverName);

	EXTERN_API( long  ) ADD_SG_BASENAME(GetSoundInputDriver) (SG_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SoundInputDriverChanged) (SG_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetSoundRecordChunkSize) (SG_GLOBALS() ADD_SG_COMMA long  seconds);

	EXTERN_API( long  ) ADD_SG_BASENAME(GetSoundRecordChunkSize) (SG_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetSoundInputRate) (SG_GLOBALS() ADD_SG_COMMA Fixed  rate);

	EXTERN_API( Fixed  ) ADD_SG_BASENAME(GetSoundInputRate) (SG_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetSoundInputParameters) (SG_GLOBALS() ADD_SG_COMMA short  sampleSize, short  numChannels, OSType  compressionType);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetSoundInputParameters) (SG_GLOBALS() ADD_SG_COMMA short * sampleSize, short * numChannels, OSType * compressionType);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetAdditionalSoundRates) (SG_GLOBALS() ADD_SG_COMMA Handle  rates);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetAdditionalSoundRates) (SG_GLOBALS() ADD_SG_COMMA Handle * rates);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetFontName) (SG_GLOBALS() ADD_SG_COMMA StringPtr  pstr);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetFontSize) (SG_GLOBALS() ADD_SG_COMMA short  fontSize);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetTextForeColor) (SG_GLOBALS() ADD_SG_COMMA RGBColor * theColor);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetTextBackColor) (SG_GLOBALS() ADD_SG_COMMA RGBColor * theColor);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetJustification) (SG_GLOBALS() ADD_SG_COMMA short  just);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetTextReturnToSpaceValue) (SG_GLOBALS() ADD_SG_COMMA short * rettospace);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetTextReturnToSpaceValue) (SG_GLOBALS() ADD_SG_COMMA short  rettospace);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(GetInstrument) (SG_GLOBALS() ADD_SG_COMMA ToneDescription * td);

	EXTERN_API( ComponentResult  ) ADD_SG_BASENAME(SetInstrument) (SG_GLOBALS() ADD_SG_COMMA ToneDescription * td);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppSGInitializeProcInfo = 0x000000F0,
		uppSGSetDataOutputProcInfo = 0x00000FF0,
		uppSGGetDataOutputProcInfo = 0x00000FF0,
		uppSGSetGWorldProcInfo = 0x00000FF0,
		uppSGGetGWorldProcInfo = 0x00000FF0,
		uppSGNewChannelProcInfo = 0x00000FF0,
		uppSGDisposeChannelProcInfo = 0x000003F0,
		uppSGStartPreviewProcInfo = 0x000000F0,
		uppSGStartRecordProcInfo = 0x000000F0,
		uppSGIdleProcInfo = 0x000000F0,
		uppSGStopProcInfo = 0x000000F0,
		uppSGPauseProcInfo = 0x000001F0,
		uppSGPrepareProcInfo = 0x000005F0,
		uppSGReleaseProcInfo = 0x000000F0,
		uppSGGetMovieProcInfo = 0x000000F0,
		uppSGSetMaximumRecordTimeProcInfo = 0x000003F0,
		uppSGGetMaximumRecordTimeProcInfo = 0x000003F0,
		uppSGGetStorageSpaceRemainingProcInfo = 0x000003F0,
		uppSGGetTimeRemainingProcInfo = 0x000003F0,
		uppSGGrabPictProcInfo = 0x0000EFF0,
		uppSGGetLastMovieResIDProcInfo = 0x000003F0,
		uppSGSetFlagsProcInfo = 0x000003F0,
		uppSGGetFlagsProcInfo = 0x000003F0,
		uppSGSetDataProcProcInfo = 0x00000FF0,
		uppSGNewChannelFromComponentProcInfo = 0x00000FF0,
		uppSGDisposeDeviceListProcInfo = 0x000003F0,
		uppSGAppendDeviceListToMenuProcInfo = 0x00000FF0,
		uppSGSetSettingsProcInfo = 0x00000FF0,
		uppSGGetSettingsProcInfo = 0x00000FF0,
		uppSGGetIndChannelProcInfo = 0x00003EF0,
		uppSGUpdateProcInfo = 0x000003F0,
		uppSGGetPauseProcInfo = 0x000003F0,
		uppSGSettingsDialogProcInfo = 0x000FFBF0,
		uppSGGetAlignmentProcProcInfo = 0x000003F0,
		uppSGSetChannelSettingsProcInfo = 0x00003FF0,
		uppSGGetChannelSettingsProcInfo = 0x00003FF0,
		uppSGGetModeProcInfo = 0x00000FF0,
		uppSGSetDataRefProcInfo = 0x00003FF0,
		uppSGGetDataRefProcInfo = 0x00003FF0,
		uppSGNewOutputProcInfo = 0x0000FFF0,
		uppSGDisposeOutputProcInfo = 0x000003F0,
		uppSGSetOutputFlagsProcInfo = 0x00000FF0,
		uppSGSetChannelOutputProcInfo = 0x00000FF0,
		uppSGGetDataOutputStorageSpaceRemainingProcInfo = 0x00000FF0,
		uppSGHandleUpdateEventProcInfo = 0x00000FF0,
		uppSGSetOutputNextOutputProcInfo = 0x00000FF0,
		uppSGGetOutputNextOutputProcInfo = 0x00000FF0,
		uppSGSetOutputMaximumOffsetProcInfo = 0x00000FF0,
		uppSGGetOutputMaximumOffsetProcInfo = 0x00000FF0,
		uppSGGetOutputDataReferenceProcInfo = 0x00003FF0,
		uppSGWriteExtendedMovieDataProcInfo = 0x0003FFF0,
		uppSGGetStorageSpaceRemaining64ProcInfo = 0x000003F0,
		uppSGGetDataOutputStorageSpaceRemaining64ProcInfo = 0x00000FF0,
		uppSGWriteMovieDataProcInfo = 0x0000FFF0,
		uppSGAddFrameReferenceProcInfo = 0x000003F0,
		uppSGGetNextFrameReferenceProcInfo = 0x00003FF0,
		uppSGGetTimeBaseProcInfo = 0x000003F0,
		uppSGSortDeviceListProcInfo = 0x000003F0,
		uppSGAddMovieDataProcInfo = 0x002FFFF0,
		uppSGChangedSourceProcInfo = 0x000003F0,
		uppSGAddExtendedFrameReferenceProcInfo = 0x000003F0,
		uppSGGetNextExtendedFrameReferenceProcInfo = 0x00003FF0,
		uppSGAddExtendedMovieDataProcInfo = 0x00EFFFF0,
		uppSGAddOutputDataRefToMediaProcInfo = 0x00003FF0,
		uppSGSetSettingsSummaryProcInfo = 0x000003F0,
		uppSGSetChannelUsageProcInfo = 0x000003F0,
		uppSGGetChannelUsageProcInfo = 0x000003F0,
		uppSGSetChannelBoundsProcInfo = 0x000003F0,
		uppSGGetChannelBoundsProcInfo = 0x000003F0,
		uppSGSetChannelVolumeProcInfo = 0x000002F0,
		uppSGGetChannelVolumeProcInfo = 0x000003F0,
		uppSGGetChannelInfoProcInfo = 0x000003F0,
		uppSGSetChannelPlayFlagsProcInfo = 0x000003F0,
		uppSGGetChannelPlayFlagsProcInfo = 0x000003F0,
		uppSGSetChannelMaxFramesProcInfo = 0x000003F0,
		uppSGGetChannelMaxFramesProcInfo = 0x000003F0,
		uppSGSetChannelRefConProcInfo = 0x000003F0,
		uppSGSetChannelClipProcInfo = 0x000003F0,
		uppSGGetChannelClipProcInfo = 0x000003F0,
		uppSGGetChannelSampleDescriptionProcInfo = 0x000003F0,
		uppSGGetChannelDeviceListProcInfo = 0x00000FF0,
		uppSGSetChannelDeviceProcInfo = 0x000003F0,
		uppSGSetChannelMatrixProcInfo = 0x000003F0,
		uppSGGetChannelMatrixProcInfo = 0x000003F0,
		uppSGGetChannelTimeScaleProcInfo = 0x000003F0,
		uppSGChannelPutPictureProcInfo = 0x000000F0,
		uppSGChannelSetRequestedDataRateProcInfo = 0x000003F0,
		uppSGChannelGetRequestedDataRateProcInfo = 0x000003F0,
		uppSGChannelSetDataSourceNameProcInfo = 0x00000BF0,
		uppSGChannelGetDataSourceNameProcInfo = 0x00000FF0,
		uppSGChannelSetCodecSettingsProcInfo = 0x000003F0,
		uppSGChannelGetCodecSettingsProcInfo = 0x000003F0,
		uppSGGetChannelTimeBaseProcInfo = 0x000003F0,
		uppSGGetChannelRefConProcInfo = 0x000003F0,
		uppSGGetChannelDeviceAndInputNamesProcInfo = 0x00003FF0,
		uppSGSetChannelDeviceInputProcInfo = 0x000002F0,
		uppSGSetChannelSettingsStateChangingProcInfo = 0x000003F0,
		uppSGInitChannelProcInfo = 0x000003F0,
		uppSGWriteSamplesProcInfo = 0x00000FF0,
		uppSGGetDataRateProcInfo = 0x000003F0,
		uppSGAlignChannelRectProcInfo = 0x000003F0,
		uppSGPanelGetDitlProcInfo = 0x000003F0,
		uppSGPanelGetTitleProcInfo = 0x000003F0,
		uppSGPanelCanRunProcInfo = 0x000003F0,
		uppSGPanelInstallProcInfo = 0x00002FF0,
		uppSGPanelEventProcInfo = 0x000FEFF0,
		uppSGPanelItemProcInfo = 0x0000AFF0,
		uppSGPanelRemoveProcInfo = 0x00002FF0,
		uppSGPanelSetGrabberProcInfo = 0x000003F0,
		uppSGPanelSetResFileProcInfo = 0x000002F0,
		uppSGPanelGetSettingsProcInfo = 0x00003FF0,
		uppSGPanelSetSettingsProcInfo = 0x00003FF0,
		uppSGPanelValidateInputProcInfo = 0x000003F0,
		uppSGPanelSetEventFilterProcInfo = 0x00000FF0,
		uppSGPanelGetDITLForSizeProcInfo = 0x00000FF0,
		uppSGGetSrcVideoBoundsProcInfo = 0x000003F0,
		uppSGSetVideoRectProcInfo = 0x000003F0,
		uppSGGetVideoRectProcInfo = 0x000003F0,
		uppSGGetVideoCompressorTypeProcInfo = 0x000003F0,
		uppSGSetVideoCompressorTypeProcInfo = 0x000003F0,
		uppSGSetVideoCompressorProcInfo = 0x0003FEF0,
		uppSGGetVideoCompressorProcInfo = 0x0003FFF0,
		uppSGGetVideoDigitizerComponentProcInfo = 0x000000F0,
		uppSGSetVideoDigitizerComponentProcInfo = 0x000003F0,
		uppSGVideoDigitizerChangedProcInfo = 0x000000F0,
		uppSGSetVideoBottlenecksProcInfo = 0x000003F0,
		uppSGGetVideoBottlenecksProcInfo = 0x000003F0,
		uppSGGrabFrameProcInfo = 0x000002F0,
		uppSGGrabFrameCompleteProcInfo = 0x00000EF0,
		uppSGDisplayFrameProcInfo = 0x00003EF0,
		uppSGCompressFrameProcInfo = 0x000002F0,
		uppSGCompressFrameCompleteProcInfo = 0x00003EF0,
		uppSGAddFrameProcInfo = 0x0000FEF0,
		uppSGTransferFrameForCompressProcInfo = 0x00003EF0,
		uppSGSetCompressBufferProcInfo = 0x00000EF0,
		uppSGGetCompressBufferProcInfo = 0x00000FF0,
		uppSGGetBufferInfoProcInfo = 0x0003FEF0,
		uppSGSetUseScreenBufferProcInfo = 0x000001F0,
		uppSGGetUseScreenBufferProcInfo = 0x000003F0,
		uppSGGrabCompressCompleteProcInfo = 0x00003FF0,
		uppSGDisplayCompressProcInfo = 0x0000FFF0,
		uppSGSetFrameRateProcInfo = 0x000003F0,
		uppSGGetFrameRateProcInfo = 0x000003F0,
		uppSGSetPreferredPacketSizeProcInfo = 0x000003F0,
		uppSGGetPreferredPacketSizeProcInfo = 0x000003F0,
		uppSGSetUserVideoCompressorListProcInfo = 0x000003F0,
		uppSGGetUserVideoCompressorListProcInfo = 0x000003F0,
		uppSGSetSoundInputDriverProcInfo = 0x000003F0,
		uppSGGetSoundInputDriverProcInfo = 0x000000F0,
		uppSGSoundInputDriverChangedProcInfo = 0x000000F0,
		uppSGSetSoundRecordChunkSizeProcInfo = 0x000003F0,
		uppSGGetSoundRecordChunkSizeProcInfo = 0x000000F0,
		uppSGSetSoundInputRateProcInfo = 0x000003F0,
		uppSGGetSoundInputRateProcInfo = 0x000000F0,
		uppSGSetSoundInputParametersProcInfo = 0x00003AF0,
		uppSGGetSoundInputParametersProcInfo = 0x00003FF0,
		uppSGSetAdditionalSoundRatesProcInfo = 0x000003F0,
		uppSGGetAdditionalSoundRatesProcInfo = 0x000003F0,
		uppSGSetFontNameProcInfo = 0x000003F0,
		uppSGSetFontSizeProcInfo = 0x000002F0,
		uppSGSetTextForeColorProcInfo = 0x000003F0,
		uppSGSetTextBackColorProcInfo = 0x000003F0,
		uppSGSetJustificationProcInfo = 0x000002F0,
		uppSGGetTextReturnToSpaceValueProcInfo = 0x000003F0,
		uppSGSetTextReturnToSpaceValueProcInfo = 0x000002F0,
		uppSGGetInstrumentProcInfo = 0x000003F0,
		uppSGSetInstrumentProcInfo = 0x000003F0
	};

#endif	/* SG_BASENAME */

/*
	Example usage:

		#define QTVIDEOOUTPUT_BASENAME()	Fred
		#define QTVIDEOOUTPUT_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/QuickTimeComponents.k.h>

	To specify that your component implementation does not use globals, do not #define QTVIDEOOUTPUT_GLOBALS
*/
#ifdef QTVIDEOOUTPUT_BASENAME
	#ifndef QTVIDEOOUTPUT_GLOBALS
		#define QTVIDEOOUTPUT_GLOBALS() 
		#define ADD_QTVIDEOOUTPUT_COMMA 
	#else
		#define ADD_QTVIDEOOUTPUT_COMMA ,
	#endif
	#define QTVIDEOOUTPUT_GLUE(a,b) a##b
	#define QTVIDEOOUTPUT_STRCAT(a,b) QTVIDEOOUTPUT_GLUE(a,b)
	#define ADD_QTVIDEOOUTPUT_BASENAME(name) QTVIDEOOUTPUT_STRCAT(QTVIDEOOUTPUT_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_QTVIDEOOUTPUT_BASENAME(GetDisplayModeList) (QTVIDEOOUTPUT_GLOBALS() ADD_QTVIDEOOUTPUT_COMMA QTAtomContainer * outputs);

	EXTERN_API( ComponentResult  ) ADD_QTVIDEOOUTPUT_BASENAME(GetCurrentClientName) (QTVIDEOOUTPUT_GLOBALS() ADD_QTVIDEOOUTPUT_COMMA Str255  str);

	EXTERN_API( ComponentResult  ) ADD_QTVIDEOOUTPUT_BASENAME(SetClientName) (QTVIDEOOUTPUT_GLOBALS() ADD_QTVIDEOOUTPUT_COMMA ConstStr255Param  str);

	EXTERN_API( ComponentResult  ) ADD_QTVIDEOOUTPUT_BASENAME(GetClientName) (QTVIDEOOUTPUT_GLOBALS() ADD_QTVIDEOOUTPUT_COMMA Str255  str);

	EXTERN_API( ComponentResult  ) ADD_QTVIDEOOUTPUT_BASENAME(Begin) (QTVIDEOOUTPUT_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_QTVIDEOOUTPUT_BASENAME(End) (QTVIDEOOUTPUT_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_QTVIDEOOUTPUT_BASENAME(SetDisplayMode) (QTVIDEOOUTPUT_GLOBALS() ADD_QTVIDEOOUTPUT_COMMA long  displayModeID);

	EXTERN_API( ComponentResult  ) ADD_QTVIDEOOUTPUT_BASENAME(GetDisplayMode) (QTVIDEOOUTPUT_GLOBALS() ADD_QTVIDEOOUTPUT_COMMA long * displayModeID);

	EXTERN_API( ComponentResult  ) ADD_QTVIDEOOUTPUT_BASENAME(CustomConfigureDisplay) (QTVIDEOOUTPUT_GLOBALS() ADD_QTVIDEOOUTPUT_COMMA ModalFilterUPP  filter);

	EXTERN_API( ComponentResult  ) ADD_QTVIDEOOUTPUT_BASENAME(SaveState) (QTVIDEOOUTPUT_GLOBALS() ADD_QTVIDEOOUTPUT_COMMA QTAtomContainer * state);

	EXTERN_API( ComponentResult  ) ADD_QTVIDEOOUTPUT_BASENAME(RestoreState) (QTVIDEOOUTPUT_GLOBALS() ADD_QTVIDEOOUTPUT_COMMA QTAtomContainer  state);

	EXTERN_API( ComponentResult  ) ADD_QTVIDEOOUTPUT_BASENAME(GetGWorld) (QTVIDEOOUTPUT_GLOBALS() ADD_QTVIDEOOUTPUT_COMMA GWorldPtr * gw);

	EXTERN_API( ComponentResult  ) ADD_QTVIDEOOUTPUT_BASENAME(GetGWorldParameters) (QTVIDEOOUTPUT_GLOBALS() ADD_QTVIDEOOUTPUT_COMMA Ptr * baseAddr, long * rowBytes, CTabHandle * colorTable);

	EXTERN_API( ComponentResult  ) ADD_QTVIDEOOUTPUT_BASENAME(GetIndSoundOutput) (QTVIDEOOUTPUT_GLOBALS() ADD_QTVIDEOOUTPUT_COMMA long  index, Component * outputComponent);

	EXTERN_API( ComponentResult  ) ADD_QTVIDEOOUTPUT_BASENAME(GetClock) (QTVIDEOOUTPUT_GLOBALS() ADD_QTVIDEOOUTPUT_COMMA ComponentInstance * clock);

	EXTERN_API( ComponentResult  ) ADD_QTVIDEOOUTPUT_BASENAME(SetEchoPort) (QTVIDEOOUTPUT_GLOBALS() ADD_QTVIDEOOUTPUT_COMMA CGrafPtr  echoPort);

	EXTERN_API( ComponentResult  ) ADD_QTVIDEOOUTPUT_BASENAME(GetIndImageDecompressor) (QTVIDEOOUTPUT_GLOBALS() ADD_QTVIDEOOUTPUT_COMMA long  index, Component * codec);

	EXTERN_API( ComponentResult  ) ADD_QTVIDEOOUTPUT_BASENAME(BaseSetEchoPort) (QTVIDEOOUTPUT_GLOBALS() ADD_QTVIDEOOUTPUT_COMMA CGrafPtr  echoPort);

	EXTERN_API( ComponentResult  ) ADD_QTVIDEOOUTPUT_BASENAME(CopyIndAudioOutputDeviceUID) (QTVIDEOOUTPUT_GLOBALS() ADD_QTVIDEOOUTPUT_COMMA long  index, CFStringRef * audioDeviceUID);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppQTVideoOutputGetDisplayModeListProcInfo = 0x000003F0,
		uppQTVideoOutputGetCurrentClientNameProcInfo = 0x000003F0,
		uppQTVideoOutputSetClientNameProcInfo = 0x000003F0,
		uppQTVideoOutputGetClientNameProcInfo = 0x000003F0,
		uppQTVideoOutputBeginProcInfo = 0x000000F0,
		uppQTVideoOutputEndProcInfo = 0x000000F0,
		uppQTVideoOutputSetDisplayModeProcInfo = 0x000003F0,
		uppQTVideoOutputGetDisplayModeProcInfo = 0x000003F0,
		uppQTVideoOutputCustomConfigureDisplayProcInfo = 0x000003F0,
		uppQTVideoOutputSaveStateProcInfo = 0x000003F0,
		uppQTVideoOutputRestoreStateProcInfo = 0x000003F0,
		uppQTVideoOutputGetGWorldProcInfo = 0x000003F0,
		uppQTVideoOutputGetGWorldParametersProcInfo = 0x00003FF0,
		uppQTVideoOutputGetIndSoundOutputProcInfo = 0x00000FF0,
		uppQTVideoOutputGetClockProcInfo = 0x000003F0,
		uppQTVideoOutputSetEchoPortProcInfo = 0x000003F0,
		uppQTVideoOutputGetIndImageDecompressorProcInfo = 0x00000FF0,
		uppQTVideoOutputBaseSetEchoPortProcInfo = 0x000003F0,
		uppQTVideoOutputCopyIndAudioOutputDeviceUIDProcInfo = 0x00000FF0
	};

#endif	/* QTVIDEOOUTPUT_BASENAME */


#endif /* __QUICKTIMECOMPONENTS_K__ */

