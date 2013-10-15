/*
     File:       MediaHandlers.k.h
 
     Contains:   QuickTime Interfaces.
 
     Version:    QuickTime 7.2.1
 
     Copyright:  © 1990-2006 by Apple Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __MEDIAHANDLERS_K__
#define __MEDIAHANDLERS_K__

#include <QuickTime/MediaHandlers.h>
/*
	Example usage:

		#define CALLCOMPONENT_BASENAME()	Fred
		#define CALLCOMPONENT_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/MediaHandlers.k.h>

	To specify that your component implementation does not use globals, do not #define CALLCOMPONENT_GLOBALS
*/
#ifdef CALLCOMPONENT_BASENAME
	#ifndef CALLCOMPONENT_GLOBALS
		#define CALLCOMPONENT_GLOBALS() 
		#define ADD_CALLCOMPONENT_COMMA 
	#else
		#define ADD_CALLCOMPONENT_COMMA ,
	#endif
	#define CALLCOMPONENT_GLUE(a,b) a##b
	#define CALLCOMPONENT_STRCAT(a,b) CALLCOMPONENT_GLUE(a,b)
	#define ADD_CALLCOMPONENT_BASENAME(name) CALLCOMPONENT_STRCAT(CALLCOMPONENT_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_CALLCOMPONENT_BASENAME(ExecuteWiredAction) (CALLCOMPONENT_GLOBALS() ADD_CALLCOMPONENT_COMMA QTAtomContainer  actionContainer, QTAtom  actionAtom, QTCustomActionTargetPtr  target, QTEventRecordPtr  event);

#endif	/* CALLCOMPONENT_BASENAME */

/*
	Example usage:

		#define MEDIA_BASENAME()	Fred
		#define MEDIA_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/MediaHandlers.k.h>

	To specify that your component implementation does not use globals, do not #define MEDIA_GLOBALS
*/
#ifdef MEDIA_BASENAME
	#ifndef MEDIA_GLOBALS
		#define MEDIA_GLOBALS() 
		#define ADD_MEDIA_COMMA 
	#else
		#define ADD_MEDIA_COMMA ,
	#endif
	#define MEDIA_GLUE(a,b) a##b
	#define MEDIA_STRCAT(a,b) MEDIA_GLUE(a,b)
	#define ADD_MEDIA_BASENAME(name) MEDIA_STRCAT(MEDIA_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetChunkManagementFlags) (MEDIA_GLOBALS() ADD_MEDIA_COMMA UInt32  flags, UInt32  flagsMask);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetChunkManagementFlags) (MEDIA_GLOBALS() ADD_MEDIA_COMMA UInt32 * flags);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetPurgeableChunkMemoryAllowance) (MEDIA_GLOBALS() ADD_MEDIA_COMMA Size  allowance);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetPurgeableChunkMemoryAllowance) (MEDIA_GLOBALS() ADD_MEDIA_COMMA Size * allowance);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(EmptyAllPurgeableChunks) (MEDIA_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(Initialize) (MEDIA_GLOBALS() ADD_MEDIA_COMMA GetMovieCompleteParams * gmc);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetHandlerCapabilities) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  flags, long  flagsMask);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(Idle) (MEDIA_GLOBALS() ADD_MEDIA_COMMA TimeValue  atMediaTime, long  flagsIn, long * flagsOut, const TimeRecord * movieTime);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetMediaInfo) (MEDIA_GLOBALS() ADD_MEDIA_COMMA Handle  h);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(PutMediaInfo) (MEDIA_GLOBALS() ADD_MEDIA_COMMA Handle  h);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetActive) (MEDIA_GLOBALS() ADD_MEDIA_COMMA Boolean  enableMedia);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetRate) (MEDIA_GLOBALS() ADD_MEDIA_COMMA Fixed  rate);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GGetStatus) (MEDIA_GLOBALS() ADD_MEDIA_COMMA ComponentResult * statusErr);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(TrackEdited) (MEDIA_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetMediaTimeScale) (MEDIA_GLOBALS() ADD_MEDIA_COMMA TimeScale  newTimeScale);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetMovieTimeScale) (MEDIA_GLOBALS() ADD_MEDIA_COMMA TimeScale  newTimeScale);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetGWorld) (MEDIA_GLOBALS() ADD_MEDIA_COMMA CGrafPtr  aPort, GDHandle  aGD);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetDimensions) (MEDIA_GLOBALS() ADD_MEDIA_COMMA Fixed  width, Fixed  height);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetClip) (MEDIA_GLOBALS() ADD_MEDIA_COMMA RgnHandle  theClip);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetMatrix) (MEDIA_GLOBALS() ADD_MEDIA_COMMA MatrixRecord * trackMovieMatrix);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetTrackOpaque) (MEDIA_GLOBALS() ADD_MEDIA_COMMA Boolean * trackIsOpaque);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetGraphicsMode) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  mode, const RGBColor * opColor);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetGraphicsMode) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long * mode, RGBColor * opColor);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GSetVolume) (MEDIA_GLOBALS() ADD_MEDIA_COMMA short  volume);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetSoundBalance) (MEDIA_GLOBALS() ADD_MEDIA_COMMA short  balance);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetSoundBalance) (MEDIA_GLOBALS() ADD_MEDIA_COMMA short * balance);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetNextBoundsChange) (MEDIA_GLOBALS() ADD_MEDIA_COMMA TimeValue * when);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetSrcRgn) (MEDIA_GLOBALS() ADD_MEDIA_COMMA RgnHandle  rgn, TimeValue  atMediaTime);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(Preroll) (MEDIA_GLOBALS() ADD_MEDIA_COMMA TimeValue  time, Fixed  rate);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SampleDescriptionChanged) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  index);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(HasCharacteristic) (MEDIA_GLOBALS() ADD_MEDIA_COMMA OSType  characteristic, Boolean * hasIt);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetOffscreenBufferSize) (MEDIA_GLOBALS() ADD_MEDIA_COMMA Rect * bounds, short  depth, CTabHandle  ctab);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetHints) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  hints);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetName) (MEDIA_GLOBALS() ADD_MEDIA_COMMA Str255  name, long  requestedLanguage, long * actualLanguage);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(ForceUpdate) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  forceUpdateFlags);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetDrawingRgn) (MEDIA_GLOBALS() ADD_MEDIA_COMMA RgnHandle * partialRgn);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GSetActiveSegment) (MEDIA_GLOBALS() ADD_MEDIA_COMMA TimeValue  activeStart, TimeValue  activeDuration);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(InvalidateRegion) (MEDIA_GLOBALS() ADD_MEDIA_COMMA RgnHandle  invalRgn);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetNextStepTime) (MEDIA_GLOBALS() ADD_MEDIA_COMMA short  flags, TimeValue  mediaTimeIn, TimeValue * mediaTimeOut, Fixed  rate);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetNonPrimarySourceData) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  inputIndex, long  dataDescriptionSeed, Handle  dataDescription, void * data, long  dataSize, ICMCompletionProcRecordPtr  asyncCompletionProc, ICMConvertDataFormatUPP  transferProc, void * refCon);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(ChangedNonPrimarySource) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  inputIndex);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(TrackReferencesChanged) (MEDIA_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetSampleDataPointer) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  sampleNum, Ptr * dataPtr, long * dataSize, long * sampleDescIndex);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(ReleaseSampleDataPointer) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  sampleNum);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(TrackPropertyAtomChanged) (MEDIA_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetTrackInputMapReference) (MEDIA_GLOBALS() ADD_MEDIA_COMMA QTAtomContainer  inputMap);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetVideoParam) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  whichParam, unsigned short * value);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetVideoParam) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  whichParam, unsigned short * value);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(Compare) (MEDIA_GLOBALS() ADD_MEDIA_COMMA Boolean * isOK, Media  srcMedia, ComponentInstance  srcMediaComponent);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetClock) (MEDIA_GLOBALS() ADD_MEDIA_COMMA ComponentInstance * clock);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetSoundOutputComponent) (MEDIA_GLOBALS() ADD_MEDIA_COMMA Component  outputComponent);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetSoundOutputComponent) (MEDIA_GLOBALS() ADD_MEDIA_COMMA Component * outputComponent);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetSoundLocalizationData) (MEDIA_GLOBALS() ADD_MEDIA_COMMA Handle  data);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetInvalidRegion) (MEDIA_GLOBALS() ADD_MEDIA_COMMA RgnHandle  rgn);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SampleDescriptionB2N) (MEDIA_GLOBALS() ADD_MEDIA_COMMA SampleDescriptionHandle  sampleDescriptionH);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SampleDescriptionN2B) (MEDIA_GLOBALS() ADD_MEDIA_COMMA SampleDescriptionHandle  sampleDescriptionH);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(QueueNonPrimarySourceData) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  inputIndex, long  dataDescriptionSeed, Handle  dataDescription, void * data, long  dataSize, ICMCompletionProcRecordPtr  asyncCompletionProc, const ICMFrameTimeRecord * frameTime, ICMConvertDataFormatUPP  transferProc, void * refCon);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(FlushNonPrimarySourceData) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  inputIndex);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetURLLink) (MEDIA_GLOBALS() ADD_MEDIA_COMMA Point  displayWhere, Handle * urlLink);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(MakeMediaTimeTable) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long ** offsets, TimeValue  startTime, TimeValue  endTime, TimeValue  timeIncrement, short  firstDataRefIndex, short  lastDataRefIndex, long * retDataRefSkew);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(HitTestForTargetRefCon) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  flags, Point  loc, long * targetRefCon);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(HitTestTargetRefCon) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  targetRefCon, long  flags, Point  loc, Boolean * wasHit);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetActionsForQTEvent) (MEDIA_GLOBALS() ADD_MEDIA_COMMA QTEventRecordPtr  event, long  targetRefCon, QTAtomContainer * container, QTAtom * atom);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(DisposeTargetRefCon) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  targetRefCon);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(TargetRefConsEqual) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  firstRefCon, long  secondRefCon, Boolean * equal);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetActionsCallback) (MEDIA_GLOBALS() ADD_MEDIA_COMMA ActionsUPP  actionsCallbackProc, void * refcon);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(PrePrerollBegin) (MEDIA_GLOBALS() ADD_MEDIA_COMMA TimeValue  time, Fixed  rate, PrePrerollCompleteUPP  completeProc, void * refcon);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(PrePrerollCancel) (MEDIA_GLOBALS() ADD_MEDIA_COMMA void * refcon);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(EnterEmptyEdit) (MEDIA_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(CurrentMediaQueuedData) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long * milliSecs);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetEffectiveVolume) (MEDIA_GLOBALS() ADD_MEDIA_COMMA short * volume);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(ResolveTargetRefCon) (MEDIA_GLOBALS() ADD_MEDIA_COMMA QTAtomContainer  container, QTAtom  atom, long * targetRefCon);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetSoundLevelMeteringEnabled) (MEDIA_GLOBALS() ADD_MEDIA_COMMA Boolean * enabled);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetSoundLevelMeteringEnabled) (MEDIA_GLOBALS() ADD_MEDIA_COMMA Boolean  enable);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetSoundLevelMeterInfo) (MEDIA_GLOBALS() ADD_MEDIA_COMMA LevelMeterInfoPtr  levelInfo);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetEffectiveSoundBalance) (MEDIA_GLOBALS() ADD_MEDIA_COMMA short * balance);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetScreenLock) (MEDIA_GLOBALS() ADD_MEDIA_COMMA Boolean  lockIt);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetDoMCActionCallback) (MEDIA_GLOBALS() ADD_MEDIA_COMMA DoMCActionUPP  doMCActionCallbackProc, void * refcon);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetErrorString) (MEDIA_GLOBALS() ADD_MEDIA_COMMA ComponentResult  theError, Str255  errorString);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetSoundEqualizerBands) (MEDIA_GLOBALS() ADD_MEDIA_COMMA MediaEQSpectrumBandsRecordPtr  spectrumInfo);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetSoundEqualizerBands) (MEDIA_GLOBALS() ADD_MEDIA_COMMA MediaEQSpectrumBandsRecordPtr  spectrumInfo);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetSoundEqualizerBandLevels) (MEDIA_GLOBALS() ADD_MEDIA_COMMA UInt8 * bandLevels);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(DoIdleActions) (MEDIA_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetSoundBassAndTreble) (MEDIA_GLOBALS() ADD_MEDIA_COMMA short  bass, short  treble);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetSoundBassAndTreble) (MEDIA_GLOBALS() ADD_MEDIA_COMMA short * bass, short * treble);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(TimeBaseChanged) (MEDIA_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(MCIsPlayerEvent) (MEDIA_GLOBALS() ADD_MEDIA_COMMA const EventRecord * e, Boolean * handledIt);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetMediaLoadState) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long * mediaLoadState);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(VideoOutputChanged) (MEDIA_GLOBALS() ADD_MEDIA_COMMA ComponentInstance  vout);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(EmptySampleCache) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  sampleNum, long  sampleCount);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetPublicInfo) (MEDIA_GLOBALS() ADD_MEDIA_COMMA OSType  infoSelector, void * infoDataPtr, Size * ioDataSize);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetPublicInfo) (MEDIA_GLOBALS() ADD_MEDIA_COMMA OSType  infoSelector, void * infoDataPtr, Size  dataSize);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetUserPreferredCodecs) (MEDIA_GLOBALS() ADD_MEDIA_COMMA CodecComponentHandle * userPreferredCodecs);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetUserPreferredCodecs) (MEDIA_GLOBALS() ADD_MEDIA_COMMA CodecComponentHandle  userPreferredCodecs);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(RefConSetProperty) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  refCon, long  propertyType, void * propertyValue);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(RefConGetProperty) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  refCon, long  propertyType, void * propertyValue);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(NavigateTargetRefCon) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  navigation, long * refCon);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GGetIdleManager) (MEDIA_GLOBALS() ADD_MEDIA_COMMA IdleManager * pim);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GSetIdleManager) (MEDIA_GLOBALS() ADD_MEDIA_COMMA IdleManager  im);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GGetLatency) (MEDIA_GLOBALS() ADD_MEDIA_COMMA TimeRecord * latency);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(SetTrackApertureModeDimensionsUsingSampleDescription) (MEDIA_GLOBALS() ADD_MEDIA_COMMA SampleDescriptionHandle  sampleDesc);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetApertureModeClipRectForSampleDescriptionIndex) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  sampleDescIndex, FixedRect * clipFixedRectOut);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GetApertureModeMatrixForSampleDescriptionIndex) (MEDIA_GLOBALS() ADD_MEDIA_COMMA long  sampleDescIndex, MatrixRecord * matrixOut);

	EXTERN_API( ComponentResult  ) ADD_MEDIA_BASENAME(GenerateApertureModeDimensions) (MEDIA_GLOBALS());

#endif	/* MEDIA_BASENAME */


/* MixedMode ProcInfo constants for component calls */
enum {
	uppCallComponentExecuteWiredActionProcInfo = 0x0000FFF0,
	uppMediaSetChunkManagementFlagsProcInfo = 0x00000FF0,
	uppMediaGetChunkManagementFlagsProcInfo = 0x000003F0,
	uppMediaSetPurgeableChunkMemoryAllowanceProcInfo = 0x000003F0,
	uppMediaGetPurgeableChunkMemoryAllowanceProcInfo = 0x000003F0,
	uppMediaEmptyAllPurgeableChunksProcInfo = 0x000000F0,
	uppMediaInitializeProcInfo = 0x000003F0,
	uppMediaSetHandlerCapabilitiesProcInfo = 0x00000FF0,
	uppMediaIdleProcInfo = 0x0000FFF0,
	uppMediaGetMediaInfoProcInfo = 0x000003F0,
	uppMediaPutMediaInfoProcInfo = 0x000003F0,
	uppMediaSetActiveProcInfo = 0x000001F0,
	uppMediaSetRateProcInfo = 0x000003F0,
	uppMediaGGetStatusProcInfo = 0x000003F0,
	uppMediaTrackEditedProcInfo = 0x000000F0,
	uppMediaSetMediaTimeScaleProcInfo = 0x000003F0,
	uppMediaSetMovieTimeScaleProcInfo = 0x000003F0,
	uppMediaSetGWorldProcInfo = 0x00000FF0,
	uppMediaSetDimensionsProcInfo = 0x00000FF0,
	uppMediaSetClipProcInfo = 0x000003F0,
	uppMediaSetMatrixProcInfo = 0x000003F0,
	uppMediaGetTrackOpaqueProcInfo = 0x000003F0,
	uppMediaSetGraphicsModeProcInfo = 0x00000FF0,
	uppMediaGetGraphicsModeProcInfo = 0x00000FF0,
	uppMediaGSetVolumeProcInfo = 0x000002F0,
	uppMediaSetSoundBalanceProcInfo = 0x000002F0,
	uppMediaGetSoundBalanceProcInfo = 0x000003F0,
	uppMediaGetNextBoundsChangeProcInfo = 0x000003F0,
	uppMediaGetSrcRgnProcInfo = 0x00000FF0,
	uppMediaPrerollProcInfo = 0x00000FF0,
	uppMediaSampleDescriptionChangedProcInfo = 0x000003F0,
	uppMediaHasCharacteristicProcInfo = 0x00000FF0,
	uppMediaGetOffscreenBufferSizeProcInfo = 0x00003BF0,
	uppMediaSetHintsProcInfo = 0x000003F0,
	uppMediaGetNameProcInfo = 0x00003FF0,
	uppMediaForceUpdateProcInfo = 0x000003F0,
	uppMediaGetDrawingRgnProcInfo = 0x000003F0,
	uppMediaGSetActiveSegmentProcInfo = 0x00000FF0,
	uppMediaInvalidateRegionProcInfo = 0x000003F0,
	uppMediaGetNextStepTimeProcInfo = 0x0000FEF0,
	uppMediaSetNonPrimarySourceDataProcInfo = 0x00FFFFF0,
	uppMediaChangedNonPrimarySourceProcInfo = 0x000003F0,
	uppMediaTrackReferencesChangedProcInfo = 0x000000F0,
	uppMediaGetSampleDataPointerProcInfo = 0x0000FFF0,
	uppMediaReleaseSampleDataPointerProcInfo = 0x000003F0,
	uppMediaTrackPropertyAtomChangedProcInfo = 0x000000F0,
	uppMediaSetTrackInputMapReferenceProcInfo = 0x000003F0,
	uppMediaSetVideoParamProcInfo = 0x00000FF0,
	uppMediaGetVideoParamProcInfo = 0x00000FF0,
	uppMediaCompareProcInfo = 0x00003FF0,
	uppMediaGetClockProcInfo = 0x000003F0,
	uppMediaSetSoundOutputComponentProcInfo = 0x000003F0,
	uppMediaGetSoundOutputComponentProcInfo = 0x000003F0,
	uppMediaSetSoundLocalizationDataProcInfo = 0x000003F0,
	uppMediaGetInvalidRegionProcInfo = 0x000003F0,
	uppMediaSampleDescriptionB2NProcInfo = 0x000003F0,
	uppMediaSampleDescriptionN2BProcInfo = 0x000003F0,
	uppMediaQueueNonPrimarySourceDataProcInfo = 0x03FFFFF0,
	uppMediaFlushNonPrimarySourceDataProcInfo = 0x000003F0,
	uppMediaGetURLLinkProcInfo = 0x00000FF0,
	uppMediaMakeMediaTimeTableProcInfo = 0x003AFFF0,
	uppMediaHitTestForTargetRefConProcInfo = 0x00003FF0,
	uppMediaHitTestTargetRefConProcInfo = 0x0000FFF0,
	uppMediaGetActionsForQTEventProcInfo = 0x0000FFF0,
	uppMediaDisposeTargetRefConProcInfo = 0x000003F0,
	uppMediaTargetRefConsEqualProcInfo = 0x00003FF0,
	uppMediaSetActionsCallbackProcInfo = 0x00000FF0,
	uppMediaPrePrerollBeginProcInfo = 0x0000FFF0,
	uppMediaPrePrerollCancelProcInfo = 0x000003F0,
	uppMediaEnterEmptyEditProcInfo = 0x000000F0,
	uppMediaCurrentMediaQueuedDataProcInfo = 0x000003F0,
	uppMediaGetEffectiveVolumeProcInfo = 0x000003F0,
	uppMediaResolveTargetRefConProcInfo = 0x00003FF0,
	uppMediaGetSoundLevelMeteringEnabledProcInfo = 0x000003F0,
	uppMediaSetSoundLevelMeteringEnabledProcInfo = 0x000001F0,
	uppMediaGetSoundLevelMeterInfoProcInfo = 0x000003F0,
	uppMediaGetEffectiveSoundBalanceProcInfo = 0x000003F0,
	uppMediaSetScreenLockProcInfo = 0x000001F0,
	uppMediaSetDoMCActionCallbackProcInfo = 0x00000FF0,
	uppMediaGetErrorStringProcInfo = 0x00000FF0,
	uppMediaGetSoundEqualizerBandsProcInfo = 0x000003F0,
	uppMediaSetSoundEqualizerBandsProcInfo = 0x000003F0,
	uppMediaGetSoundEqualizerBandLevelsProcInfo = 0x000003F0,
	uppMediaDoIdleActionsProcInfo = 0x000000F0,
	uppMediaSetSoundBassAndTrebleProcInfo = 0x00000AF0,
	uppMediaGetSoundBassAndTrebleProcInfo = 0x00000FF0,
	uppMediaTimeBaseChangedProcInfo = 0x000000F0,
	uppMediaMCIsPlayerEventProcInfo = 0x00000FF0,
	uppMediaGetMediaLoadStateProcInfo = 0x000003F0,
	uppMediaVideoOutputChangedProcInfo = 0x000003F0,
	uppMediaEmptySampleCacheProcInfo = 0x00000FF0,
	uppMediaGetPublicInfoProcInfo = 0x00003FF0,
	uppMediaSetPublicInfoProcInfo = 0x00003FF0,
	uppMediaGetUserPreferredCodecsProcInfo = 0x000003F0,
	uppMediaSetUserPreferredCodecsProcInfo = 0x000003F0,
	uppMediaRefConSetPropertyProcInfo = 0x00003FF0,
	uppMediaRefConGetPropertyProcInfo = 0x00003FF0,
	uppMediaNavigateTargetRefConProcInfo = 0x00000FF0,
	uppMediaGGetIdleManagerProcInfo = 0x000003F0,
	uppMediaGSetIdleManagerProcInfo = 0x000003F0,
	uppMediaGGetLatencyProcInfo = 0x000003F0,
	uppMediaSetTrackApertureModeDimensionsUsingSampleDescriptionProcInfo = 0x000003F0,
	uppMediaGetApertureModeClipRectForSampleDescriptionIndexProcInfo = 0x00000FF0,
	uppMediaGetApertureModeMatrixForSampleDescriptionIndexProcInfo = 0x00000FF0,
	uppMediaGenerateApertureModeDimensionsProcInfo = 0x000000F0
};


#endif /* __MEDIAHANDLERS_K__ */

