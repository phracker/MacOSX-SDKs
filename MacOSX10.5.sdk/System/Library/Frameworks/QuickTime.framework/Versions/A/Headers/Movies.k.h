/*
     File:       Movies.k.h
 
     Contains:   QuickTime Interfaces.
 
     Version:    QuickTime 7.2.1
 
     Copyright:  © 1990-2006 by Apple Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __MOVIES_K__
#define __MOVIES_K__

#include <QuickTime/Movies.h>
/*
	Example usage:

		#define VIDEOMEDIA_BASENAME()	Fred
		#define VIDEOMEDIA_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/Movies.k.h>

	To specify that your component implementation does not use globals, do not #define VIDEOMEDIA_GLOBALS
*/
#ifdef VIDEOMEDIA_BASENAME
	#ifndef VIDEOMEDIA_GLOBALS
		#define VIDEOMEDIA_GLOBALS() 
		#define ADD_VIDEOMEDIA_COMMA 
	#else
		#define ADD_VIDEOMEDIA_COMMA ,
	#endif
	#define VIDEOMEDIA_GLUE(a,b) a##b
	#define VIDEOMEDIA_STRCAT(a,b) VIDEOMEDIA_GLUE(a,b)
	#define ADD_VIDEOMEDIA_BASENAME(name) VIDEOMEDIA_STRCAT(VIDEOMEDIA_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_VIDEOMEDIA_BASENAME(ResetStatistics) (VIDEOMEDIA_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_VIDEOMEDIA_BASENAME(GetStatistics) (VIDEOMEDIA_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_VIDEOMEDIA_BASENAME(GetStallCount) (VIDEOMEDIA_GLOBALS() ADD_VIDEOMEDIA_COMMA unsigned long * stalls);

	EXTERN_API( ComponentResult  ) ADD_VIDEOMEDIA_BASENAME(SetCodecParameter) (VIDEOMEDIA_GLOBALS() ADD_VIDEOMEDIA_COMMA CodecType  cType, OSType  parameterID, long  parameterChangeSeed, void * dataPtr, long  dataSize);

	EXTERN_API( ComponentResult  ) ADD_VIDEOMEDIA_BASENAME(GetCodecParameter) (VIDEOMEDIA_GLOBALS() ADD_VIDEOMEDIA_COMMA CodecType  cType, OSType  parameterID, Handle  outParameterData);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppVideoMediaResetStatisticsProcInfo = 0x000000F0,
		uppVideoMediaGetStatisticsProcInfo = 0x000000F0,
		uppVideoMediaGetStallCountProcInfo = 0x000003F0,
		uppVideoMediaSetCodecParameterProcInfo = 0x0003FFF0,
		uppVideoMediaGetCodecParameterProcInfo = 0x00003FF0
	};

#endif	/* VIDEOMEDIA_BASENAME */

/*
	Example usage:

		#define TEXTMEDIA_BASENAME()	Fred
		#define TEXTMEDIA_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/Movies.k.h>

	To specify that your component implementation does not use globals, do not #define TEXTMEDIA_GLOBALS
*/
#ifdef TEXTMEDIA_BASENAME
	#ifndef TEXTMEDIA_GLOBALS
		#define TEXTMEDIA_GLOBALS() 
		#define ADD_TEXTMEDIA_COMMA 
	#else
		#define ADD_TEXTMEDIA_COMMA ,
	#endif
	#define TEXTMEDIA_GLUE(a,b) a##b
	#define TEXTMEDIA_STRCAT(a,b) TEXTMEDIA_GLUE(a,b)
	#define ADD_TEXTMEDIA_BASENAME(name) TEXTMEDIA_STRCAT(TEXTMEDIA_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_TEXTMEDIA_BASENAME(SetTextProc) (TEXTMEDIA_GLOBALS() ADD_TEXTMEDIA_COMMA TextMediaUPP  TextProc, long  refcon);

	EXTERN_API( ComponentResult  ) ADD_TEXTMEDIA_BASENAME(AddTextSample) (TEXTMEDIA_GLOBALS() ADD_TEXTMEDIA_COMMA Ptr  text, unsigned long  size, short  fontNumber, short  fontSize, Style  textFace, RGBColor * textColor, RGBColor * backColor, short  textJustification, Rect * textBox, long  displayFlags, TimeValue  scrollDelay, short  hiliteStart, short  hiliteEnd, RGBColor * rgbHiliteColor, TimeValue  duration, TimeValue * sampleTime);

	EXTERN_API( ComponentResult  ) ADD_TEXTMEDIA_BASENAME(AddTESample) (TEXTMEDIA_GLOBALS() ADD_TEXTMEDIA_COMMA TEHandle  hTE, RGBColor * backColor, short  textJustification, Rect * textBox, long  displayFlags, TimeValue  scrollDelay, short  hiliteStart, short  hiliteEnd, RGBColor * rgbHiliteColor, TimeValue  duration, TimeValue * sampleTime);

	EXTERN_API( ComponentResult  ) ADD_TEXTMEDIA_BASENAME(AddHiliteSample) (TEXTMEDIA_GLOBALS() ADD_TEXTMEDIA_COMMA short  hiliteStart, short  hiliteEnd, RGBColor * rgbHiliteColor, TimeValue  duration, TimeValue * sampleTime);

	EXTERN_API( ComponentResult  ) ADD_TEXTMEDIA_BASENAME(DrawRaw) (TEXTMEDIA_GLOBALS() ADD_TEXTMEDIA_COMMA GWorldPtr  gw, GDHandle  gd, void * data, long  dataSize, TextDescriptionHandle  tdh);

	EXTERN_API( ComponentResult  ) ADD_TEXTMEDIA_BASENAME(SetTextProperty) (TEXTMEDIA_GLOBALS() ADD_TEXTMEDIA_COMMA TimeValue  atMediaTime, long  propertyType, void * data, long  dataSize);

	EXTERN_API( ComponentResult  ) ADD_TEXTMEDIA_BASENAME(RawSetup) (TEXTMEDIA_GLOBALS() ADD_TEXTMEDIA_COMMA GWorldPtr  gw, GDHandle  gd, void * data, long  dataSize, TextDescriptionHandle  tdh, TimeValue  sampleDuration);

	EXTERN_API( ComponentResult  ) ADD_TEXTMEDIA_BASENAME(RawIdle) (TEXTMEDIA_GLOBALS() ADD_TEXTMEDIA_COMMA GWorldPtr  gw, GDHandle  gd, TimeValue  sampleTime, long  flagsIn, long * flagsOut);

	EXTERN_API( ComponentResult  ) ADD_TEXTMEDIA_BASENAME(GetTextProperty) (TEXTMEDIA_GLOBALS() ADD_TEXTMEDIA_COMMA TimeValue  atMediaTime, long  propertyType, void * data, long  dataSize);

	EXTERN_API( ComponentResult  ) ADD_TEXTMEDIA_BASENAME(FindNextText) (TEXTMEDIA_GLOBALS() ADD_TEXTMEDIA_COMMA Ptr  text, long  size, short  findFlags, TimeValue  startTime, TimeValue * foundTime, TimeValue * foundDuration, long * offset);

	EXTERN_API( ComponentResult  ) ADD_TEXTMEDIA_BASENAME(HiliteTextSample) (TEXTMEDIA_GLOBALS() ADD_TEXTMEDIA_COMMA TimeValue  sampleTime, short  hiliteStart, short  hiliteEnd, RGBColor * rgbHiliteColor);

	EXTERN_API( ComponentResult  ) ADD_TEXTMEDIA_BASENAME(SetTextSampleData) (TEXTMEDIA_GLOBALS() ADD_TEXTMEDIA_COMMA void * data, OSType  dataType);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppTextMediaSetTextProcProcInfo = 0x00000FF0,
		uppTextMediaAddTESampleProcInfo = 0x3FAFEFF0,
		uppTextMediaAddHiliteSampleProcInfo = 0x0003FAF0,
		uppTextMediaDrawRawProcInfo = 0x0003FFF0,
		uppTextMediaSetTextPropertyProcInfo = 0x0000FFF0,
		uppTextMediaRawSetupProcInfo = 0x000FFFF0,
		uppTextMediaRawIdleProcInfo = 0x0003FFF0,
		uppTextMediaGetTextPropertyProcInfo = 0x0000FFF0,
		uppTextMediaFindNextTextProcInfo = 0x003FEFF0,
		uppTextMediaHiliteTextSampleProcInfo = 0x0000EBF0,
		uppTextMediaSetTextSampleDataProcInfo = 0x00000FF0
	};

#endif	/* TEXTMEDIA_BASENAME */

#ifdef TEXTMEDIA_BASENAME
enum {
 uppTextMediaAddTextSampleProcInfo = SPECIAL_CASE_PROCINFO(specialTextMediaAddTextSample)
};
#endif  /* TEXTMEDIA_BASENAME */
/*
	Example usage:

		#define SPRITEMEDIA_BASENAME()	Fred
		#define SPRITEMEDIA_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/Movies.k.h>

	To specify that your component implementation does not use globals, do not #define SPRITEMEDIA_GLOBALS
*/
#ifdef SPRITEMEDIA_BASENAME
	#ifndef SPRITEMEDIA_GLOBALS
		#define SPRITEMEDIA_GLOBALS() 
		#define ADD_SPRITEMEDIA_COMMA 
	#else
		#define ADD_SPRITEMEDIA_COMMA ,
	#endif
	#define SPRITEMEDIA_GLUE(a,b) a##b
	#define SPRITEMEDIA_STRCAT(a,b) SPRITEMEDIA_GLUE(a,b)
	#define ADD_SPRITEMEDIA_BASENAME(name) SPRITEMEDIA_STRCAT(SPRITEMEDIA_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(SetProperty) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA short  spriteIndex, long  propertyType, void * propertyValue);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(GetProperty) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA short  spriteIndex, long  propertyType, void * propertyValue);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(HitTestSprites) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA long  flags, Point  loc, short * spriteHitIndex);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(CountSprites) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA short * numSprites);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(CountImages) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA short * numImages);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(GetIndImageDescription) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA short  imageIndex, ImageDescriptionHandle  imageDescription);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(GetDisplayedSampleNumber) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA long * sampleNum);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(GetSpriteName) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA QTAtomID  spriteID, Str255  spriteName);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(GetImageName) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA short  imageIndex, Str255  imageName);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(SetSpriteProperty) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA QTAtomID  spriteID, long  propertyType, void * propertyValue);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(GetSpriteProperty) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA QTAtomID  spriteID, long  propertyType, void * propertyValue);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(HitTestAllSprites) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA long  flags, Point  loc, QTAtomID * spriteHitID);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(HitTestOneSprite) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA QTAtomID  spriteID, long  flags, Point  loc, Boolean * wasHit);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(SpriteIndexToID) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA short  spriteIndex, QTAtomID * spriteID);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(SpriteIDToIndex) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA QTAtomID  spriteID, short * spriteIndex);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(GetSpriteActionsForQTEvent) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA QTEventRecordPtr  event, QTAtomID  spriteID, QTAtomContainer * container, QTAtom * atom);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(SetActionVariable) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA QTAtomID  variableID, const float * value);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(GetActionVariable) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA QTAtomID  variableID, float * value);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(GetIndImageProperty) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA short  imageIndex, long  imagePropertyType, void * imagePropertyValue);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(NewSprite) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA QTRuntimeSpriteDescPtr  newSpriteDesc);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(DisposeSprite) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA QTAtomID  spriteID);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(SetActionVariableToString) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA QTAtomID  variableID, Ptr  theCString);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(GetActionVariableAsString) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA QTAtomID  variableID, Handle * theCString);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(NewImage) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA Handle  dataRef, OSType  dataRefType, QTAtomID  desiredID);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(DisposeImage) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA short  imageIndex);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(ImageIndexToID) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA short  imageIndex, QTAtomID * imageID);

	EXTERN_API( ComponentResult  ) ADD_SPRITEMEDIA_BASENAME(ImageIDToIndex) (SPRITEMEDIA_GLOBALS() ADD_SPRITEMEDIA_COMMA QTAtomID  imageID, short * imageIndex);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppSpriteMediaSetPropertyProcInfo = 0x00003EF0,
		uppSpriteMediaGetPropertyProcInfo = 0x00003EF0,
		uppSpriteMediaHitTestSpritesProcInfo = 0x00003FF0,
		uppSpriteMediaCountSpritesProcInfo = 0x000003F0,
		uppSpriteMediaCountImagesProcInfo = 0x000003F0,
		uppSpriteMediaGetIndImageDescriptionProcInfo = 0x00000EF0,
		uppSpriteMediaGetDisplayedSampleNumberProcInfo = 0x000003F0,
		uppSpriteMediaGetSpriteNameProcInfo = 0x00000FF0,
		uppSpriteMediaGetImageNameProcInfo = 0x00000EF0,
		uppSpriteMediaSetSpritePropertyProcInfo = 0x00003FF0,
		uppSpriteMediaGetSpritePropertyProcInfo = 0x00003FF0,
		uppSpriteMediaHitTestAllSpritesProcInfo = 0x00003FF0,
		uppSpriteMediaHitTestOneSpriteProcInfo = 0x0000FFF0,
		uppSpriteMediaSpriteIndexToIDProcInfo = 0x00000EF0,
		uppSpriteMediaSpriteIDToIndexProcInfo = 0x00000FF0,
		uppSpriteMediaGetSpriteActionsForQTEventProcInfo = 0x0000FFF0,
		uppSpriteMediaSetActionVariableProcInfo = 0x00000FF0,
		uppSpriteMediaGetActionVariableProcInfo = 0x00000FF0,
		uppSpriteMediaGetIndImagePropertyProcInfo = 0x00003EF0,
		uppSpriteMediaNewSpriteProcInfo = 0x000003F0,
		uppSpriteMediaDisposeSpriteProcInfo = 0x000003F0,
		uppSpriteMediaSetActionVariableToStringProcInfo = 0x00000FF0,
		uppSpriteMediaGetActionVariableAsStringProcInfo = 0x00000FF0,
		uppSpriteMediaNewImageProcInfo = 0x00003FF0,
		uppSpriteMediaDisposeImageProcInfo = 0x000002F0,
		uppSpriteMediaImageIndexToIDProcInfo = 0x00000EF0,
		uppSpriteMediaImageIDToIndexProcInfo = 0x00000FF0
	};

#endif	/* SPRITEMEDIA_BASENAME */

/*
	Example usage:

		#define FLASHMEDIA_BASENAME()	Fred
		#define FLASHMEDIA_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/Movies.k.h>

	To specify that your component implementation does not use globals, do not #define FLASHMEDIA_GLOBALS
*/
#ifdef FLASHMEDIA_BASENAME
	#ifndef FLASHMEDIA_GLOBALS
		#define FLASHMEDIA_GLOBALS() 
		#define ADD_FLASHMEDIA_COMMA 
	#else
		#define ADD_FLASHMEDIA_COMMA ,
	#endif
	#define FLASHMEDIA_GLUE(a,b) a##b
	#define FLASHMEDIA_STRCAT(a,b) FLASHMEDIA_GLUE(a,b)
	#define ADD_FLASHMEDIA_BASENAME(name) FLASHMEDIA_STRCAT(FLASHMEDIA_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_FLASHMEDIA_BASENAME(SetPan) (FLASHMEDIA_GLOBALS() ADD_FLASHMEDIA_COMMA short  xPercent, short  yPercent);

	EXTERN_API( ComponentResult  ) ADD_FLASHMEDIA_BASENAME(SetZoom) (FLASHMEDIA_GLOBALS() ADD_FLASHMEDIA_COMMA short  factor);

	EXTERN_API( ComponentResult  ) ADD_FLASHMEDIA_BASENAME(SetZoomRect) (FLASHMEDIA_GLOBALS() ADD_FLASHMEDIA_COMMA long  left, long  top, long  right, long  bottom);

	EXTERN_API( ComponentResult  ) ADD_FLASHMEDIA_BASENAME(GetRefConBounds) (FLASHMEDIA_GLOBALS() ADD_FLASHMEDIA_COMMA long  refCon, long * left, long * top, long * right, long * bottom);

	EXTERN_API( ComponentResult  ) ADD_FLASHMEDIA_BASENAME(GetRefConID) (FLASHMEDIA_GLOBALS() ADD_FLASHMEDIA_COMMA long  refCon, long * refConID);

	EXTERN_API( ComponentResult  ) ADD_FLASHMEDIA_BASENAME(IDToRefCon) (FLASHMEDIA_GLOBALS() ADD_FLASHMEDIA_COMMA long  refConID, long * refCon);

	EXTERN_API( ComponentResult  ) ADD_FLASHMEDIA_BASENAME(GetDisplayedFrameNumber) (FLASHMEDIA_GLOBALS() ADD_FLASHMEDIA_COMMA long * flashFrameNumber);

	EXTERN_API( ComponentResult  ) ADD_FLASHMEDIA_BASENAME(FrameNumberToMovieTime) (FLASHMEDIA_GLOBALS() ADD_FLASHMEDIA_COMMA long  flashFrameNumber, TimeValue * movieTime);

	EXTERN_API( ComponentResult  ) ADD_FLASHMEDIA_BASENAME(FrameLabelToMovieTime) (FLASHMEDIA_GLOBALS() ADD_FLASHMEDIA_COMMA Ptr  theLabel, TimeValue * movieTime);

	EXTERN_API( ComponentResult  ) ADD_FLASHMEDIA_BASENAME(GetFlashVariable) (FLASHMEDIA_GLOBALS() ADD_FLASHMEDIA_COMMA char * path, char * name, Handle * theVariableCStringOut);

	EXTERN_API( ComponentResult  ) ADD_FLASHMEDIA_BASENAME(SetFlashVariable) (FLASHMEDIA_GLOBALS() ADD_FLASHMEDIA_COMMA char * path, char * name, char * value, Boolean  updateFocus);

	EXTERN_API( ComponentResult  ) ADD_FLASHMEDIA_BASENAME(DoButtonActions) (FLASHMEDIA_GLOBALS() ADD_FLASHMEDIA_COMMA char * path, long  buttonID, long  transition);

	EXTERN_API( ComponentResult  ) ADD_FLASHMEDIA_BASENAME(GetSupportedSwfVersion) (FLASHMEDIA_GLOBALS() ADD_FLASHMEDIA_COMMA unsigned char * swfVersion);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppFlashMediaSetPanProcInfo = 0x00000AF0,
		uppFlashMediaSetZoomProcInfo = 0x000002F0,
		uppFlashMediaSetZoomRectProcInfo = 0x0000FFF0,
		uppFlashMediaGetRefConBoundsProcInfo = 0x0003FFF0,
		uppFlashMediaGetRefConIDProcInfo = 0x00000FF0,
		uppFlashMediaIDToRefConProcInfo = 0x00000FF0,
		uppFlashMediaGetDisplayedFrameNumberProcInfo = 0x000003F0,
		uppFlashMediaFrameNumberToMovieTimeProcInfo = 0x00000FF0,
		uppFlashMediaFrameLabelToMovieTimeProcInfo = 0x00000FF0,
		uppFlashMediaGetFlashVariableProcInfo = 0x00003FF0,
		uppFlashMediaSetFlashVariableProcInfo = 0x00007FF0,
		uppFlashMediaDoButtonActionsProcInfo = 0x00003FF0,
		uppFlashMediaGetSupportedSwfVersionProcInfo = 0x000003F0
	};

#endif	/* FLASHMEDIA_BASENAME */

/*
	Example usage:

		#define MOVIEMEDIA_BASENAME()	Fred
		#define MOVIEMEDIA_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/Movies.k.h>

	To specify that your component implementation does not use globals, do not #define MOVIEMEDIA_GLOBALS
*/
#ifdef MOVIEMEDIA_BASENAME
	#ifndef MOVIEMEDIA_GLOBALS
		#define MOVIEMEDIA_GLOBALS() 
		#define ADD_MOVIEMEDIA_COMMA 
	#else
		#define ADD_MOVIEMEDIA_COMMA ,
	#endif
	#define MOVIEMEDIA_GLUE(a,b) a##b
	#define MOVIEMEDIA_STRCAT(a,b) MOVIEMEDIA_GLUE(a,b)
	#define ADD_MOVIEMEDIA_BASENAME(name) MOVIEMEDIA_STRCAT(MOVIEMEDIA_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_MOVIEMEDIA_BASENAME(GetChildDoMCActionCallback) (MOVIEMEDIA_GLOBALS() ADD_MOVIEMEDIA_COMMA DoMCActionUPP * doMCActionCallbackProc, long * refcon);

	EXTERN_API( ComponentResult  ) ADD_MOVIEMEDIA_BASENAME(GetDoMCActionCallback) (MOVIEMEDIA_GLOBALS() ADD_MOVIEMEDIA_COMMA DoMCActionUPP * doMCActionCallbackProc, long * refcon);

	EXTERN_API( ComponentResult  ) ADD_MOVIEMEDIA_BASENAME(GetCurrentMovieProperty) (MOVIEMEDIA_GLOBALS() ADD_MOVIEMEDIA_COMMA OSType  whichProperty, void * value);

	EXTERN_API( ComponentResult  ) ADD_MOVIEMEDIA_BASENAME(GetCurrentTrackProperty) (MOVIEMEDIA_GLOBALS() ADD_MOVIEMEDIA_COMMA long  trackID, OSType  whichProperty, void * value);

	EXTERN_API( ComponentResult  ) ADD_MOVIEMEDIA_BASENAME(GetChildMovieDataReference) (MOVIEMEDIA_GLOBALS() ADD_MOVIEMEDIA_COMMA QTAtomID  dataRefID, short  dataRefIndex, OSType * dataRefType, Handle * dataRef, QTAtomID * dataRefIDOut, short * dataRefIndexOut);

	EXTERN_API( ComponentResult  ) ADD_MOVIEMEDIA_BASENAME(SetChildMovieDataReference) (MOVIEMEDIA_GLOBALS() ADD_MOVIEMEDIA_COMMA QTAtomID  dataRefID, OSType  dataRefType, Handle  dataRef);

	EXTERN_API( ComponentResult  ) ADD_MOVIEMEDIA_BASENAME(LoadChildMovieFromDataReference) (MOVIEMEDIA_GLOBALS() ADD_MOVIEMEDIA_COMMA QTAtomID  dataRefID);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppMovieMediaGetChildDoMCActionCallbackProcInfo = 0x00000FF0,
		uppMovieMediaGetDoMCActionCallbackProcInfo = 0x00000FF0,
		uppMovieMediaGetCurrentMoviePropertyProcInfo = 0x00000FF0,
		uppMovieMediaGetCurrentTrackPropertyProcInfo = 0x00003FF0,
		uppMovieMediaGetChildMovieDataReferenceProcInfo = 0x000FFBF0,
		uppMovieMediaSetChildMovieDataReferenceProcInfo = 0x00003FF0,
		uppMovieMediaLoadChildMovieFromDataReferenceProcInfo = 0x000003F0
	};

#endif	/* MOVIEMEDIA_BASENAME */

/*
	Example usage:

		#define MEDIA3D_BASENAME()	Fred
		#define MEDIA3D_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/Movies.k.h>

	To specify that your component implementation does not use globals, do not #define MEDIA3D_GLOBALS
*/
#ifdef MEDIA3D_BASENAME
	#ifndef MEDIA3D_GLOBALS
		#define MEDIA3D_GLOBALS() 
		#define ADD_MEDIA3D_COMMA 
	#else
		#define ADD_MEDIA3D_COMMA ,
	#endif
	#define MEDIA3D_GLUE(a,b) a##b
	#define MEDIA3D_STRCAT(a,b) MEDIA3D_GLUE(a,b)
	#define ADD_MEDIA3D_BASENAME(name) MEDIA3D_STRCAT(MEDIA3D_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_MEDIA3D_BASENAME(GetNamedObjectList) (MEDIA3D_GLOBALS() ADD_MEDIA3D_COMMA QTAtomContainer * objectList);

	EXTERN_API( ComponentResult  ) ADD_MEDIA3D_BASENAME(GetRendererList) (MEDIA3D_GLOBALS() ADD_MEDIA3D_COMMA QTAtomContainer * rendererList);

	EXTERN_API( ComponentResult  ) ADD_MEDIA3D_BASENAME(GetCurrentGroup) (MEDIA3D_GLOBALS() ADD_MEDIA3D_COMMA void * group);

	EXTERN_API( ComponentResult  ) ADD_MEDIA3D_BASENAME(TranslateNamedObjectTo) (MEDIA3D_GLOBALS() ADD_MEDIA3D_COMMA char * objectName, Fixed  x, Fixed  y, Fixed  z);

	EXTERN_API( ComponentResult  ) ADD_MEDIA3D_BASENAME(ScaleNamedObjectTo) (MEDIA3D_GLOBALS() ADD_MEDIA3D_COMMA char * objectName, Fixed  xScale, Fixed  yScale, Fixed  zScale);

	EXTERN_API( ComponentResult  ) ADD_MEDIA3D_BASENAME(RotateNamedObjectTo) (MEDIA3D_GLOBALS() ADD_MEDIA3D_COMMA char * objectName, Fixed  xDegrees, Fixed  yDegrees, Fixed  zDegrees);

	EXTERN_API( ComponentResult  ) ADD_MEDIA3D_BASENAME(SetCameraData) (MEDIA3D_GLOBALS() ADD_MEDIA3D_COMMA void * cameraData);

	EXTERN_API( ComponentResult  ) ADD_MEDIA3D_BASENAME(GetCameraData) (MEDIA3D_GLOBALS() ADD_MEDIA3D_COMMA void * cameraData);

	EXTERN_API( ComponentResult  ) ADD_MEDIA3D_BASENAME(SetCameraAngleAspect) (MEDIA3D_GLOBALS() ADD_MEDIA3D_COMMA QTFloatSingle  fov, QTFloatSingle  aspectRatioXToY);

	EXTERN_API( ComponentResult  ) ADD_MEDIA3D_BASENAME(GetCameraAngleAspect) (MEDIA3D_GLOBALS() ADD_MEDIA3D_COMMA QTFloatSingle * fov, QTFloatSingle * aspectRatioXToY);

	EXTERN_API( ComponentResult  ) ADD_MEDIA3D_BASENAME(SetCameraRange) (MEDIA3D_GLOBALS() ADD_MEDIA3D_COMMA void * tQ3CameraRange);

	EXTERN_API( ComponentResult  ) ADD_MEDIA3D_BASENAME(GetCameraRange) (MEDIA3D_GLOBALS() ADD_MEDIA3D_COMMA void * tQ3CameraRange);

	EXTERN_API( ComponentResult  ) ADD_MEDIA3D_BASENAME(GetViewObject) (MEDIA3D_GLOBALS() ADD_MEDIA3D_COMMA void * tq3viewObject);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppMedia3DGetNamedObjectListProcInfo = 0x000003F0,
		uppMedia3DGetRendererListProcInfo = 0x000003F0,
		uppMedia3DGetCurrentGroupProcInfo = 0x000003F0,
		uppMedia3DTranslateNamedObjectToProcInfo = 0x0000FFF0,
		uppMedia3DScaleNamedObjectToProcInfo = 0x0000FFF0,
		uppMedia3DRotateNamedObjectToProcInfo = 0x0000FFF0,
		uppMedia3DSetCameraDataProcInfo = 0x000003F0,
		uppMedia3DGetCameraDataProcInfo = 0x000003F0,
		uppMedia3DSetCameraAngleAspectProcInfo = 0x00000FF0,
		uppMedia3DGetCameraAngleAspectProcInfo = 0x00000FF0,
		uppMedia3DSetCameraRangeProcInfo = 0x000003F0,
		uppMedia3DGetCameraRangeProcInfo = 0x000003F0,
		uppMedia3DGetViewObjectProcInfo = 0x000003F0
	};

#endif	/* MEDIA3D_BASENAME */

/*
	Example usage:

		#define MC_BASENAME()	Fred
		#define MC_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/Movies.k.h>

	To specify that your component implementation does not use globals, do not #define MC_GLOBALS
*/
#ifdef MC_BASENAME
	#ifndef MC_GLOBALS
		#define MC_GLOBALS() 
		#define ADD_MC_COMMA 
	#else
		#define ADD_MC_COMMA ,
	#endif
	#define MC_GLUE(a,b) a##b
	#define MC_STRCAT(a,b) MC_GLUE(a,b)
	#define ADD_MC_BASENAME(name) MC_STRCAT(MC_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(SetMovie) (MC_GLOBALS() ADD_MC_COMMA Movie  theMovie, WindowRef  movieWindow, Point  where);

	EXTERN_API( Movie  ) ADD_MC_BASENAME(GetIndMovie) (MC_GLOBALS() ADD_MC_COMMA short  index);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(RemoveAllMovies) (MC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(RemoveAMovie) (MC_GLOBALS() ADD_MC_COMMA Movie  m);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(RemoveMovie) (MC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(IsPlayerEvent) (MC_GLOBALS() ADD_MC_COMMA const EventRecord * e);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(SetActionFilter) (MC_GLOBALS() ADD_MC_COMMA MCActionFilterUPP  blob);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(DoAction) (MC_GLOBALS() ADD_MC_COMMA short  action, void * params);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(SetControllerAttached) (MC_GLOBALS() ADD_MC_COMMA Boolean  attach);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(IsControllerAttached) (MC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(SetControllerPort) (MC_GLOBALS() ADD_MC_COMMA CGrafPtr  gp);

	EXTERN_API( CGrafPtr  ) ADD_MC_BASENAME(GetControllerPort) (MC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(SetVisible) (MC_GLOBALS() ADD_MC_COMMA Boolean  visible);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(GetVisible) (MC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(GetControllerBoundsRect) (MC_GLOBALS() ADD_MC_COMMA Rect * bounds);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(SetControllerBoundsRect) (MC_GLOBALS() ADD_MC_COMMA const Rect * bounds);

	EXTERN_API( RgnHandle  ) ADD_MC_BASENAME(GetControllerBoundsRgn) (MC_GLOBALS());

	EXTERN_API( RgnHandle  ) ADD_MC_BASENAME(GetWindowRgn) (MC_GLOBALS() ADD_MC_COMMA WindowRef  w);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(MovieChanged) (MC_GLOBALS() ADD_MC_COMMA Movie  m);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(SetDuration) (MC_GLOBALS() ADD_MC_COMMA TimeValue  duration);

	EXTERN_API( TimeValue  ) ADD_MC_BASENAME(GetCurrentTime) (MC_GLOBALS() ADD_MC_COMMA TimeScale * scale);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(NewAttachedController) (MC_GLOBALS() ADD_MC_COMMA Movie  theMovie, WindowRef  w, Point  where);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(Draw) (MC_GLOBALS() ADD_MC_COMMA WindowRef  w);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(Activate) (MC_GLOBALS() ADD_MC_COMMA WindowRef  w, Boolean  activate);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(Idle) (MC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(Key) (MC_GLOBALS() ADD_MC_COMMA SInt8  key, long  modifiers);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(Click) (MC_GLOBALS() ADD_MC_COMMA WindowRef  w, Point  where, long  when, long  modifiers);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(EnableEditing) (MC_GLOBALS() ADD_MC_COMMA Boolean  enabled);

	EXTERN_API( long  ) ADD_MC_BASENAME(IsEditingEnabled) (MC_GLOBALS());

	EXTERN_API( Movie  ) ADD_MC_BASENAME(Copy) (MC_GLOBALS());

	EXTERN_API( Movie  ) ADD_MC_BASENAME(Cut) (MC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(Paste) (MC_GLOBALS() ADD_MC_COMMA Movie  srcMovie);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(Clear) (MC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(Undo) (MC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(PositionController) (MC_GLOBALS() ADD_MC_COMMA const Rect * movieRect, const Rect * controllerRect, long  someFlags);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(GetControllerInfo) (MC_GLOBALS() ADD_MC_COMMA long * someFlags);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(SetClip) (MC_GLOBALS() ADD_MC_COMMA RgnHandle  theClip, RgnHandle  movieClip);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(GetClip) (MC_GLOBALS() ADD_MC_COMMA RgnHandle * theClip, RgnHandle * movieClip);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(DrawBadge) (MC_GLOBALS() ADD_MC_COMMA RgnHandle  movieRgn, RgnHandle * badgeRgn);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(SetUpEditMenu) (MC_GLOBALS() ADD_MC_COMMA long  modifiers, MenuRef  mh);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(GetMenuString) (MC_GLOBALS() ADD_MC_COMMA long  modifiers, short  item, Str255  aString);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(SetActionFilterWithRefCon) (MC_GLOBALS() ADD_MC_COMMA MCActionFilterWithRefConUPP  blob, long  refCon);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(PtInController) (MC_GLOBALS() ADD_MC_COMMA Point  thePt, Boolean * inController);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(Invalidate) (MC_GLOBALS() ADD_MC_COMMA WindowRef  w, RgnHandle  invalidRgn);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(AdjustCursor) (MC_GLOBALS() ADD_MC_COMMA WindowRef  w, Point  where, long  modifiers);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(GetInterfaceElement) (MC_GLOBALS() ADD_MC_COMMA MCInterfaceElement  whichElement, void * element);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(GetDoActionsProc) (MC_GLOBALS() ADD_MC_COMMA DoMCActionUPP * doMCActionProc, long * doMCActionRefCon);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(AddMovieSegment) (MC_GLOBALS() ADD_MC_COMMA Movie  srcMovie, Boolean  scaled);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(TrimMovieSegment) (MC_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(SetIdleManager) (MC_GLOBALS() ADD_MC_COMMA IdleManager  im);

	EXTERN_API( ComponentResult  ) ADD_MC_BASENAME(SetControllerCapabilities) (MC_GLOBALS() ADD_MC_COMMA long  flags, long  flagsMask);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppMCSetMovieProcInfo = 0x00003FF0,
		uppMCGetIndMovieProcInfo = 0x000002F0,
		uppMCRemoveAllMoviesProcInfo = 0x000000F0,
		uppMCRemoveAMovieProcInfo = 0x000003F0,
		uppMCRemoveMovieProcInfo = 0x000000F0,
		uppMCIsPlayerEventProcInfo = 0x000003F0,
		uppMCSetActionFilterProcInfo = 0x000003F0,
		uppMCDoActionProcInfo = 0x00000EF0,
		uppMCSetControllerAttachedProcInfo = 0x000001F0,
		uppMCIsControllerAttachedProcInfo = 0x000000F0,
		uppMCSetControllerPortProcInfo = 0x000003F0,
		uppMCGetControllerPortProcInfo = 0x000000F0,
		uppMCSetVisibleProcInfo = 0x000001F0,
		uppMCGetVisibleProcInfo = 0x000000F0,
		uppMCGetControllerBoundsRectProcInfo = 0x000003F0,
		uppMCSetControllerBoundsRectProcInfo = 0x000003F0,
		uppMCGetControllerBoundsRgnProcInfo = 0x000000F0,
		uppMCGetWindowRgnProcInfo = 0x000003F0,
		uppMCMovieChangedProcInfo = 0x000003F0,
		uppMCSetDurationProcInfo = 0x000003F0,
		uppMCGetCurrentTimeProcInfo = 0x000003F0,
		uppMCNewAttachedControllerProcInfo = 0x00003FF0,
		uppMCDrawProcInfo = 0x000003F0,
		uppMCActivateProcInfo = 0x000007F0,
		uppMCIdleProcInfo = 0x000000F0,
		uppMCKeyProcInfo = 0x00000DF0,
		uppMCClickProcInfo = 0x0000FFF0,
		uppMCEnableEditingProcInfo = 0x000001F0,
		uppMCIsEditingEnabledProcInfo = 0x000000F0,
		uppMCCopyProcInfo = 0x000000F0,
		uppMCCutProcInfo = 0x000000F0,
		uppMCPasteProcInfo = 0x000003F0,
		uppMCClearProcInfo = 0x000000F0,
		uppMCUndoProcInfo = 0x000000F0,
		uppMCPositionControllerProcInfo = 0x00003FF0,
		uppMCGetControllerInfoProcInfo = 0x000003F0,
		uppMCSetClipProcInfo = 0x00000FF0,
		uppMCGetClipProcInfo = 0x00000FF0,
		uppMCDrawBadgeProcInfo = 0x00000FF0,
		uppMCSetUpEditMenuProcInfo = 0x00000FF0,
		uppMCGetMenuStringProcInfo = 0x00003BF0,
		uppMCSetActionFilterWithRefConProcInfo = 0x00000FF0,
		uppMCPtInControllerProcInfo = 0x00000FF0,
		uppMCInvalidateProcInfo = 0x00000FF0,
		uppMCAdjustCursorProcInfo = 0x00003FF0,
		uppMCGetInterfaceElementProcInfo = 0x00000FF0,
		uppMCGetDoActionsProcProcInfo = 0x00000FF0,
		uppMCAddMovieSegmentProcInfo = 0x000007F0,
		uppMCTrimMovieSegmentProcInfo = 0x000000F0,
		uppMCSetIdleManagerProcInfo = 0x000003F0,
		uppMCSetControllerCapabilitiesProcInfo = 0x00000FF0
	};

#endif	/* MC_BASENAME */

/*
	Example usage:

		#define MUSICMEDIA_BASENAME()	Fred
		#define MUSICMEDIA_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/Movies.k.h>

	To specify that your component implementation does not use globals, do not #define MUSICMEDIA_GLOBALS
*/
#ifdef MUSICMEDIA_BASENAME
	#ifndef MUSICMEDIA_GLOBALS
		#define MUSICMEDIA_GLOBALS() 
		#define ADD_MUSICMEDIA_COMMA 
	#else
		#define ADD_MUSICMEDIA_COMMA ,
	#endif
	#define MUSICMEDIA_GLUE(a,b) a##b
	#define MUSICMEDIA_STRCAT(a,b) MUSICMEDIA_GLUE(a,b)
	#define ADD_MUSICMEDIA_BASENAME(name) MUSICMEDIA_STRCAT(MUSICMEDIA_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_MUSICMEDIA_BASENAME(GetIndexedTunePlayer) (MUSICMEDIA_GLOBALS() ADD_MUSICMEDIA_COMMA long  sampleDescIndex, ComponentInstance * tp);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppMusicMediaGetIndexedTunePlayerProcInfo = 0x00000FF0
	};

#endif	/* MUSICMEDIA_BASENAME */


#endif /* __MOVIES_K__ */

