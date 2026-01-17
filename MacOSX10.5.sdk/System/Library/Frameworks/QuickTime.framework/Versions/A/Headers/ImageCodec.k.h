/*
     File:       ImageCodec.k.h
 
     Contains:   QuickTime Interfaces.
 
     Version:    QuickTime 7.2.1
 
     Copyright:  © 1990-2006 by Apple Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __IMAGECODEC_K__
#define __IMAGECODEC_K__

#include <QuickTime/ImageCodec.h>
/*
	Example usage:

		#define IMAGECODEC_BASENAME()	Fred
		#define IMAGECODEC_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/ImageCodec.k.h>

	To specify that your component implementation does not use globals, do not #define IMAGECODEC_GLOBALS
*/
#ifdef IMAGECODEC_BASENAME
	#ifndef IMAGECODEC_GLOBALS
		#define IMAGECODEC_GLOBALS() 
		#define ADD_IMAGECODEC_COMMA 
	#else
		#define ADD_IMAGECODEC_COMMA ,
	#endif
	#define IMAGECODEC_GLUE(a,b) a##b
	#define IMAGECODEC_STRCAT(a,b) IMAGECODEC_GLUE(a,b)
	#define ADD_IMAGECODEC_BASENAME(name) IMAGECODEC_STRCAT(IMAGECODEC_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(GetCodecInfo) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA CodecInfo * info);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(GetCompressionTime) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA PixMapHandle  src, const Rect * srcRect, short  depth, CodecQ * spatialQuality, CodecQ * temporalQuality, unsigned long * time);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(GetMaxCompressionSize) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA PixMapHandle  src, const Rect * srcRect, short  depth, CodecQ  quality, long * size);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(PreCompress) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA CodecCompressParams * params);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(BandCompress) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA CodecCompressParams * params);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(PreDecompress) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA CodecDecompressParams * params);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(BandDecompress) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA CodecDecompressParams * params);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(Busy) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA ImageSequence  seq);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(GetCompressedImageSize) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA ImageDescriptionHandle  desc, Ptr  data, long  bufferSize, ICMDataProcRecordPtr  dataProc, long * dataSize);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(GetSimilarity) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA PixMapHandle  src, const Rect * srcRect, ImageDescriptionHandle  desc, Ptr  data, Fixed * similarity);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(TrimImage) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA ImageDescriptionHandle  Desc, Ptr  inData, long  inBufferSize, ICMDataProcRecordPtr  dataProc, Ptr  outData, long  outBufferSize, ICMFlushProcRecordPtr  flushProc, Rect * trimRect, ICMProgressProcRecordPtr  progressProc);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(RequestSettings) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA Handle  settings, Rect * rp, ModalFilterUPP  filterProc);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(GetSettings) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA Handle  settings);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(SetSettings) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA Handle  settings);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(Flush) (IMAGECODEC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(SetTimeCode) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA void * timeCodeFormat, void * timeCodeTime);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(IsImageDescriptionEquivalent) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA ImageDescriptionHandle  newDesc, Boolean * equivalent);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(NewMemory) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA Ptr * data, Size  dataSize, long  dataUse, ICMMemoryDisposedUPP  memoryGoneProc, void * refCon);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(DisposeMemory) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA Ptr  data);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(HitTestData) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA ImageDescriptionHandle  desc, void * data, Size  dataSize, Point  where, Boolean * hit);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(NewImageBufferMemory) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA CodecDecompressParams * params, long  flags, ICMMemoryDisposedUPP  memoryGoneProc, void * refCon);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(ExtractAndCombineFields) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA long  fieldFlags, void * data1, long  dataSize1, ImageDescriptionHandle  desc1, void * data2, long  dataSize2, ImageDescriptionHandle  desc2, void * outputData, long * outDataSize, ImageDescriptionHandle  descOut);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(GetMaxCompressionSizeWithSources) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA PixMapHandle  src, const Rect * srcRect, short  depth, CodecQ  quality, CDSequenceDataSourcePtr  sourceData, long * size);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(SetTimeBase) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA void * base);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(SourceChanged) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA UInt32  majorSourceChangeSeed, UInt32  minorSourceChangeSeed, CDSequenceDataSourcePtr  sourceData, long * flagsOut);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(FlushFrame) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA UInt32  flags);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(GetSettingsAsText) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA Handle * text);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(GetParameterListHandle) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA Handle * parameterDescriptionHandle);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(GetParameterList) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA QTAtomContainer * parameterDescription);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(CreateStandardParameterDialog) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA QTAtomContainer  parameterDescription, QTAtomContainer  parameters, QTParameterDialogOptions  dialogOptions, DialogPtr  existingDialog, short  existingUserItem, QTParameterDialog * createdDialog);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(IsStandardParameterDialogEvent) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA EventRecord * pEvent, QTParameterDialog  createdDialog);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(DismissStandardParameterDialog) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA QTParameterDialog  createdDialog);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(StandardParameterDialogDoAction) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA QTParameterDialog  createdDialog, long  action, void * params);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(NewImageGWorld) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA CodecDecompressParams * params, GWorldPtr * newGW, long  flags);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(DisposeImageGWorld) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA GWorldPtr  theGW);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(HitTestDataWithFlags) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA ImageDescriptionHandle  desc, void * data, Size  dataSize, Point  where, long * hit, long  hitFlags);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(ValidateParameters) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA QTAtomContainer  parameters, QTParameterValidationOptions  validationFlags, StringPtr  errorString);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(GetBaseMPWorkFunction) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA ComponentMPWorkFunctionUPP * workFunction, void ** refCon, ImageCodecMPDrawBandUPP  drawProc, void * drawProcRefCon);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(LockBits) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA CGrafPtr  port);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(UnlockBits) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA CGrafPtr  port);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(RequestGammaLevel) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA Fixed  srcGammaLevel, Fixed  dstGammaLevel, long * codecCanMatch);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(GetSourceDataGammaLevel) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA Fixed * sourceDataGammaLevel);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(GetDecompressLatency) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA TimeRecord * latency);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(MergeFloatingImageOntoWindow) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA UInt32  flags);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(RemoveFloatingImage) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA UInt32  flags);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(GetDITLForSize) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA Handle * ditl, Point * requestedSize);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(DITLInstall) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA DialogRef  d, short  itemOffset);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(DITLEvent) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA DialogRef  d, short  itemOffset, const EventRecord * theEvent, short * itemHit, Boolean * handled);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(DITLItem) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA DialogRef  d, short  itemOffset, short  itemNum);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(DITLRemove) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA DialogRef  d, short  itemOffset);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(DITLValidateInput) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA Boolean * ok);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(GetPreferredChunkSizeAndAlignment) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA ImageDescriptionHandle  desc, Fixed  frameRate, UInt32  dataRate, long * bytesPerChunk, long * alignment);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(PrepareToCompressFrames) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA ICMCompressorSessionRef  session, ICMCompressionSessionOptionsRef  compressionSessionOptions, ImageDescriptionHandle  imageDescription, void * reserved, CFDictionaryRef * compressorPixelBufferAttributesOut);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(EncodeFrame) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA ICMCompressorSourceFrameRef  sourceFrame, UInt32  flags);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(CompleteFrame) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA ICMCompressorSourceFrameRef  sourceFrame, UInt32  flags);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(BeginPass) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA ICMCompressionPassModeFlags  passModeFlags, UInt32  flags, ICMMultiPassStorageRef  multiPassStorage);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(EndPass) (IMAGECODEC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(ProcessBetweenPasses) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA ICMMultiPassStorageRef  multiPassStorage, Boolean * interpassProcessingDoneOut, ICMCompressionPassModeFlags * requestedNextPassModeFlagsOut);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(Preflight) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA CodecDecompressParams * params);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(Initialize) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA ImageSubCodecDecompressCapabilities * cap);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(BeginBand) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA CodecDecompressParams * params, ImageSubCodecDecompressRecord * drp, long  flags);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(DrawBand) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA ImageSubCodecDecompressRecord * drp);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(EndBand) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA ImageSubCodecDecompressRecord * drp, OSErr  result, long  flags);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(QueueStarting) (IMAGECODEC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(QueueStopping) (IMAGECODEC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(DroppingFrame) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA const ImageSubCodecDecompressRecord * drp);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(ScheduleFrame) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA const ImageSubCodecDecompressRecord * drp, ImageCodecTimeTriggerUPP  triggerProc, void * triggerProcRefCon);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(CancelTrigger) (IMAGECODEC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(DecodeBand) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA ImageSubCodecDecompressRecord * drp, unsigned long  flags);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppImageCodecGetCodecInfoProcInfo = 0x000003F0,
		uppImageCodecGetCompressionTimeProcInfo = 0x000FEFF0,
		uppImageCodecGetMaxCompressionSizeProcInfo = 0x0003EFF0,
		uppImageCodecPreCompressProcInfo = 0x000003F0,
		uppImageCodecBandCompressProcInfo = 0x000003F0,
		uppImageCodecPreDecompressProcInfo = 0x000003F0,
		uppImageCodecBandDecompressProcInfo = 0x000003F0,
		uppImageCodecBusyProcInfo = 0x000003F0,
		uppImageCodecGetCompressedImageSizeProcInfo = 0x0003FFF0,
		uppImageCodecGetSimilarityProcInfo = 0x0003FFF0,
		uppImageCodecTrimImageProcInfo = 0x03FFFFF0,
		uppImageCodecRequestSettingsProcInfo = 0x00003FF0,
		uppImageCodecGetSettingsProcInfo = 0x000003F0,
		uppImageCodecSetSettingsProcInfo = 0x000003F0,
		uppImageCodecFlushProcInfo = 0x000000F0,
		uppImageCodecSetTimeCodeProcInfo = 0x00000FF0,
		uppImageCodecIsImageDescriptionEquivalentProcInfo = 0x00000FF0,
		uppImageCodecNewMemoryProcInfo = 0x0003FFF0,
		uppImageCodecDisposeMemoryProcInfo = 0x000003F0,
		uppImageCodecHitTestDataProcInfo = 0x0003FFF0,
		uppImageCodecNewImageBufferMemoryProcInfo = 0x0000FFF0,
		uppImageCodecExtractAndCombineFieldsProcInfo = 0x0FFFFFF0,
		uppImageCodecGetMaxCompressionSizeWithSourcesProcInfo = 0x000FEFF0,
		uppImageCodecSetTimeBaseProcInfo = 0x000003F0,
		uppImageCodecSourceChangedProcInfo = 0x0000FFF0,
		uppImageCodecFlushFrameProcInfo = 0x000003F0,
		uppImageCodecGetSettingsAsTextProcInfo = 0x000003F0,
		uppImageCodecGetParameterListHandleProcInfo = 0x000003F0,
		uppImageCodecGetParameterListProcInfo = 0x000003F0,
		uppImageCodecCreateStandardParameterDialogProcInfo = 0x000EFFF0,
		uppImageCodecIsStandardParameterDialogEventProcInfo = 0x00000FF0,
		uppImageCodecDismissStandardParameterDialogProcInfo = 0x000003F0,
		uppImageCodecStandardParameterDialogDoActionProcInfo = 0x00003FF0,
		uppImageCodecNewImageGWorldProcInfo = 0x00003FF0,
		uppImageCodecDisposeImageGWorldProcInfo = 0x000003F0,
		uppImageCodecHitTestDataWithFlagsProcInfo = 0x000FFFF0,
		uppImageCodecValidateParametersProcInfo = 0x00003FF0,
		uppImageCodecGetBaseMPWorkFunctionProcInfo = 0x0000FFF0,
		uppImageCodecLockBitsProcInfo = 0x000003F0,
		uppImageCodecUnlockBitsProcInfo = 0x000003F0,
		uppImageCodecRequestGammaLevelProcInfo = 0x00003FF0,
		uppImageCodecGetSourceDataGammaLevelProcInfo = 0x000003F0,
		uppImageCodecGetDecompressLatencyProcInfo = 0x000003F0,
		uppImageCodecMergeFloatingImageOntoWindowProcInfo = 0x000003F0,
		uppImageCodecRemoveFloatingImageProcInfo = 0x000003F0,
		uppImageCodecGetDITLForSizeProcInfo = 0x00000FF0,
		uppImageCodecDITLInstallProcInfo = 0x00000BF0,
		uppImageCodecDITLEventProcInfo = 0x0003FBF0,
		uppImageCodecDITLItemProcInfo = 0x00002BF0,
		uppImageCodecDITLRemoveProcInfo = 0x00000BF0,
		uppImageCodecDITLValidateInputProcInfo = 0x000003F0,
		uppImageCodecGetPreferredChunkSizeAndAlignmentProcInfo = 0x0003FFF0,
		uppImageCodecPrepareToCompressFramesProcInfo = 0x0003FFF0,
		uppImageCodecEncodeFrameProcInfo = 0x00000FF0,
		uppImageCodecCompleteFrameProcInfo = 0x00000FF0,
		uppImageCodecBeginPassProcInfo = 0x00003FF0,
		uppImageCodecEndPassProcInfo = 0x000000F0,
		uppImageCodecProcessBetweenPassesProcInfo = 0x00003FF0,
		uppImageCodecPreflightProcInfo = 0x000003F0,
		uppImageCodecInitializeProcInfo = 0x000003F0,
		uppImageCodecBeginBandProcInfo = 0x00003FF0,
		uppImageCodecDrawBandProcInfo = 0x000003F0,
		uppImageCodecEndBandProcInfo = 0x00003BF0,
		uppImageCodecQueueStartingProcInfo = 0x000000F0,
		uppImageCodecQueueStoppingProcInfo = 0x000000F0,
		uppImageCodecDroppingFrameProcInfo = 0x000003F0,
		uppImageCodecScheduleFrameProcInfo = 0x00003FF0,
		uppImageCodecCancelTriggerProcInfo = 0x000000F0,
		uppImageCodecDecodeBandProcInfo = 0x00000FF0
	};

#endif	/* IMAGECODEC_BASENAME */

/*
	Example usage:

		#define QTPHOTO_BASENAME()	Fred
		#define QTPHOTO_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/ImageCodec.k.h>

	To specify that your component implementation does not use globals, do not #define QTPHOTO_GLOBALS
*/
#ifdef QTPHOTO_BASENAME
	#ifndef QTPHOTO_GLOBALS
		#define QTPHOTO_GLOBALS() 
		#define ADD_QTPHOTO_COMMA 
	#else
		#define ADD_QTPHOTO_COMMA ,
	#endif
	#define QTPHOTO_GLUE(a,b) a##b
	#define QTPHOTO_STRCAT(a,b) QTPHOTO_GLUE(a,b)
	#define ADD_QTPHOTO_BASENAME(name) QTPHOTO_STRCAT(QTPHOTO_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_QTPHOTO_BASENAME(SetSampling) (QTPHOTO_GLOBALS() ADD_QTPHOTO_COMMA short  yH, short  yV, short  cbH, short  cbV, short  crH, short  crV);

	EXTERN_API( ComponentResult  ) ADD_QTPHOTO_BASENAME(SetRestartInterval) (QTPHOTO_GLOBALS() ADD_QTPHOTO_COMMA unsigned short  restartInterval);

	EXTERN_API( ComponentResult  ) ADD_QTPHOTO_BASENAME(DefineHuffmanTable) (QTPHOTO_GLOBALS() ADD_QTPHOTO_COMMA short  componentNumber, Boolean  isDC, unsigned char * lengthCounts, unsigned char * values);

	EXTERN_API( ComponentResult  ) ADD_QTPHOTO_BASENAME(DefineQuantizationTable) (QTPHOTO_GLOBALS() ADD_QTPHOTO_COMMA short  componentNumber, unsigned char * table);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppQTPhotoSetSamplingProcInfo = 0x000AAAF0,
		uppQTPhotoSetRestartIntervalProcInfo = 0x000002F0,
		uppQTPhotoDefineHuffmanTableProcInfo = 0x0000F6F0,
		uppQTPhotoDefineQuantizationTableProcInfo = 0x00000EF0
	};

#endif	/* QTPHOTO_BASENAME */

/*
	Example usage:

		#define IMAGECODEC_BASENAME()	Fred
		#define IMAGECODEC_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/ImageCodec.k.h>

	To specify that your component implementation does not use globals, do not #define IMAGECODEC_GLOBALS
*/
#ifdef IMAGECODEC_BASENAME
	#ifndef IMAGECODEC_GLOBALS
		#define IMAGECODEC_GLOBALS() 
		#define ADD_IMAGECODEC_COMMA 
	#else
		#define ADD_IMAGECODEC_COMMA ,
	#endif
	#define IMAGECODEC_GLUE(a,b) a##b
	#define IMAGECODEC_STRCAT(a,b) IMAGECODEC_GLUE(a,b)
	#define ADD_IMAGECODEC_BASENAME(name) IMAGECODEC_STRCAT(IMAGECODEC_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(EffectSetup) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA CodecDecompressParams * p);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(EffectBegin) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA CodecDecompressParams * p, EffectsFrameParamsPtr  ePtr);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(EffectRenderFrame) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA EffectsFrameParamsPtr  p);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(EffectConvertEffectSourceToFormat) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA EffectSourcePtr  sourceToConvert, ImageDescriptionHandle  requestedDesc);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(EffectCancel) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA EffectsFrameParamsPtr  p);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(EffectGetSpeed) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA QTAtomContainer  parameters, Fixed * pFPS);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(EffectPrepareSMPTEFrame) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA PixMapPtr  destPixMap, SMPTEFrameReference * returnValue);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(EffectDisposeSMPTEFrame) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA SMPTEFrameReference  frameRef);

	EXTERN_API( ComponentResult  ) ADD_IMAGECODEC_BASENAME(EffectRenderSMPTEFrame) (IMAGECODEC_GLOBALS() ADD_IMAGECODEC_COMMA PixMapPtr  destPixMap, SMPTEFrameReference  frameRef, Fixed  effectPercentageEven, Fixed  effectPercentageOdd, Rect * pSourceRect, MatrixRecord * matrixP, SMPTEWipeType  effectNumber, long  xRepeat, long  yRepeat, SMPTEFlags  flags, Fixed  penWidth, long  strokeValue);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppImageCodecEffectSetupProcInfo = 0x000003F0,
		uppImageCodecEffectBeginProcInfo = 0x00000FF0,
		uppImageCodecEffectRenderFrameProcInfo = 0x000003F0,
		uppImageCodecEffectConvertEffectSourceToFormatProcInfo = 0x00000FF0,
		uppImageCodecEffectCancelProcInfo = 0x000003F0,
		uppImageCodecEffectGetSpeedProcInfo = 0x00000FF0,
		uppImageCodecEffectPrepareSMPTEFrameProcInfo = 0x00000FF0,
		uppImageCodecEffectDisposeSMPTEFrameProcInfo = 0x000003F0,
		uppImageCodecEffectRenderSMPTEFrameProcInfo = 0xFFFFFFF0
	};

#endif	/* IMAGECODEC_BASENAME */

/*
	Example usage:

		#define CURVE_BASENAME()	Fred
		#define CURVE_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/ImageCodec.k.h>

	To specify that your component implementation does not use globals, do not #define CURVE_GLOBALS
*/
#ifdef CURVE_BASENAME
	#ifndef CURVE_GLOBALS
		#define CURVE_GLOBALS() 
		#define ADD_CURVE_COMMA 
	#else
		#define ADD_CURVE_COMMA ,
	#endif
	#define CURVE_GLUE(a,b) a##b
	#define CURVE_STRCAT(a,b) CURVE_GLUE(a,b)
	#define ADD_CURVE_BASENAME(name) CURVE_STRCAT(CURVE_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_CURVE_BASENAME(GetLength) (CURVE_GLOBALS() ADD_CURVE_COMMA gxPaths * target, long  index, wide * wideLength);

	EXTERN_API( ComponentResult  ) ADD_CURVE_BASENAME(LengthToPoint) (CURVE_GLOBALS() ADD_CURVE_COMMA gxPaths * target, long  index, Fixed  length, FixedPoint * location, FixedPoint * tangent);

	EXTERN_API( ComponentResult  ) ADD_CURVE_BASENAME(NewPath) (CURVE_GLOBALS() ADD_CURVE_COMMA Handle * pPath);

	EXTERN_API( ComponentResult  ) ADD_CURVE_BASENAME(CountPointsInPath) (CURVE_GLOBALS() ADD_CURVE_COMMA gxPaths * aPath, unsigned long  contourIndex, unsigned long * pCount);

	EXTERN_API( ComponentResult  ) ADD_CURVE_BASENAME(GetPathPoint) (CURVE_GLOBALS() ADD_CURVE_COMMA gxPaths * aPath, unsigned long  contourIndex, unsigned long  pointIndex, gxPoint * thePoint, Boolean * ptIsOnPath);

	EXTERN_API( ComponentResult  ) ADD_CURVE_BASENAME(InsertPointIntoPath) (CURVE_GLOBALS() ADD_CURVE_COMMA gxPoint * aPoint, Handle  thePath, unsigned long  contourIndex, unsigned long  pointIndex, Boolean  ptIsOnPath);

	EXTERN_API( ComponentResult  ) ADD_CURVE_BASENAME(SetPathPoint) (CURVE_GLOBALS() ADD_CURVE_COMMA gxPaths * aPath, unsigned long  contourIndex, unsigned long  pointIndex, gxPoint * thePoint, Boolean  ptIsOnPath);

	EXTERN_API( ComponentResult  ) ADD_CURVE_BASENAME(GetNearestPathPoint) (CURVE_GLOBALS() ADD_CURVE_COMMA gxPaths * aPath, FixedPoint * thePoint, unsigned long * contourIndex, unsigned long * pointIndex, Fixed * theDelta);

	EXTERN_API( ComponentResult  ) ADD_CURVE_BASENAME(PathPointToLength) (CURVE_GLOBALS() ADD_CURVE_COMMA gxPaths * aPath, Fixed  startDist, Fixed  endDist, FixedPoint * thePoint, Fixed * pLength);

	EXTERN_API( ComponentResult  ) ADD_CURVE_BASENAME(CreateVectorStream) (CURVE_GLOBALS() ADD_CURVE_COMMA Handle * pStream);

	EXTERN_API( ComponentResult  ) ADD_CURVE_BASENAME(AddAtomToVectorStream) (CURVE_GLOBALS() ADD_CURVE_COMMA OSType  atomType, Size  atomSize, void * pAtomData, Handle  vectorStream);

	EXTERN_API( ComponentResult  ) ADD_CURVE_BASENAME(AddPathAtomToVectorStream) (CURVE_GLOBALS() ADD_CURVE_COMMA Handle  pathData, Handle  vectorStream);

	EXTERN_API( ComponentResult  ) ADD_CURVE_BASENAME(AddZeroAtomToVectorStream) (CURVE_GLOBALS() ADD_CURVE_COMMA Handle  vectorStream);

	EXTERN_API( ComponentResult  ) ADD_CURVE_BASENAME(GetAtomDataFromVectorStream) (CURVE_GLOBALS() ADD_CURVE_COMMA Handle  vectorStream, long  atomType, long * dataSize, Ptr * dataPtr);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppCurveGetLengthProcInfo = 0x00003FF0,
		uppCurveLengthToPointProcInfo = 0x0003FFF0,
		uppCurveNewPathProcInfo = 0x000003F0,
		uppCurveCountPointsInPathProcInfo = 0x00003FF0,
		uppCurveGetPathPointProcInfo = 0x0003FFF0,
		uppCurveInsertPointIntoPathProcInfo = 0x0001FFF0,
		uppCurveSetPathPointProcInfo = 0x0001FFF0,
		uppCurveGetNearestPathPointProcInfo = 0x0003FFF0,
		uppCurvePathPointToLengthProcInfo = 0x0003FFF0,
		uppCurveCreateVectorStreamProcInfo = 0x000003F0,
		uppCurveAddAtomToVectorStreamProcInfo = 0x0000FFF0,
		uppCurveAddPathAtomToVectorStreamProcInfo = 0x00000FF0,
		uppCurveAddZeroAtomToVectorStreamProcInfo = 0x000003F0,
		uppCurveGetAtomDataFromVectorStreamProcInfo = 0x0000FFF0
	};

#endif	/* CURVE_BASENAME */


#endif /* __IMAGECODEC_K__ */

