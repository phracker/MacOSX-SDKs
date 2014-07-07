/*
     File:       QuickTime/MediaHandlers.h
 
     Contains:   QuickTime Interfaces.
 
     Version:    QuickTime-142~1
 
     Copyright:  © 1990-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __MEDIAHANDLERS__
#define __MEDIAHANDLERS__

#ifndef __CARBON__
#include <Carbon/Carbon.h>
#endif

#ifndef __MOVIES__
#include <QuickTime/Movies.h>
#endif





#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

typedef CALLBACK_API( void , PrePrerollCompleteProcPtr )(MediaHandler mh, OSErr err, void *refcon);
typedef STACK_UPP_TYPE(PrePrerollCompleteProcPtr)               PrePrerollCompleteUPP;
enum {
  handlerHasSpatial             = 1 << 0,
  handlerCanClip                = 1 << 1,
  handlerCanMatte               = 1 << 2,
  handlerCanTransferMode        = 1 << 3,
  handlerNeedsBuffer            = 1 << 4,
  handlerNoIdle                 = 1 << 5,
  handlerNoScheduler            = 1 << 6,
  handlerWantsTime              = 1 << 7,
  handlerCGrafPortOnly          = 1 << 8,
  handlerCanSend                = 1 << 9,
  handlerCanHandleComplexMatrix = 1 << 10,
  handlerWantsDestinationPixels = 1 << 11,
  handlerCanSendImageData       = 1 << 12,
  handlerCanPicSave             = 1 << 13
};

/* media task flags */
enum {
  mMustDraw                     = 1 << 3,
  mAtEnd                        = 1 << 4,
  mPreflightDraw                = 1 << 5,
  mSyncDrawing                  = 1 << 6,
  mPrecompositeOnly             = 1 << 9,
  mSoundOnly                    = 1 << 10,
  mDoIdleActionsBeforeDraws     = 1 << 11,
  mDisableIdleActions           = 1 << 12
};

/* media task result flags */
enum {
  mDidDraw                      = 1 << 0,
  mNeedsToDraw                  = 1 << 2,
  mDrawAgain                    = 1 << 3,
  mPartialDraw                  = 1 << 4,
  mWantIdleActions              = 1 << 5
};

enum {
  forceUpdateRedraw             = 1 << 0,
  forceUpdateNewBuffer          = 1 << 1
};

/* media hit test flags */
enum {
  mHitTestBounds                = 1L << 0, /*    point must only be within targetRefCon's bounding box */
  mHitTestImage                 = 1L << 1, /*  point must be within the shape of the targetRefCon's image */
  mHitTestInvisible             = 1L << 2, /*  invisible targetRefCon's may be hit tested */
  mHitTestIsClick               = 1L << 3 /*  for codecs that want mouse events */
};

/* media is opaque flags */
enum {
  mOpaque                       = 1L << 0,
  mInvisible                    = 1L << 1
};


/* MediaSetPublicInfo/MediaGetPublicInfo selectors */
enum {
  kMediaQTIdleFrequencySelector = 'idfq'
};




struct GetMovieCompleteParams {
  short               version;
  Movie               theMovie;
  Track               theTrack;
  Media               theMedia;
  TimeScale           movieScale;
  TimeScale           mediaScale;
  TimeValue           movieDuration;
  TimeValue           trackDuration;
  TimeValue           mediaDuration;
  Fixed               effectiveRate;
  TimeBase            timeBase;
  short               volume;
  Fixed               width;
  Fixed               height;
  MatrixRecord        trackMovieMatrix;
  CGrafPtr            moviePort;
  GDHandle            movieGD;
  PixMapHandle        trackMatte;
  QTAtomContainer     inputMap;
};
typedef struct GetMovieCompleteParams   GetMovieCompleteParams;
enum {
  kMediaVideoParamBrightness    = 1,
  kMediaVideoParamContrast      = 2,
  kMediaVideoParamHue           = 3,
  kMediaVideoParamSharpness     = 4,
  kMediaVideoParamSaturation    = 5,
  kMediaVideoParamBlackLevel    = 6,
  kMediaVideoParamWhiteLevel    = 7
};

/* These are for MediaGetInfo() and MediaSetInfo().*/
enum {
  kMHInfoEncodedFrameRate       = 'orat' /* Parameter is a MHInfoEncodedFrameRateRecord*.*/
};

/* This holds the frame rate at which the track was encoded.*/
struct MHInfoEncodedFrameRateRecord {
  Fixed               encodedFrameRate;
};
typedef struct MHInfoEncodedFrameRateRecord MHInfoEncodedFrameRateRecord;

typedef Handle *                        dataHandlePtr;
typedef dataHandlePtr *                 dataHandleHandle;

struct QTCustomActionTargetRecord {
  Movie               movie;
  DoMCActionUPP       doMCActionCallbackProc;
  long                callBackRefcon;
  Track               track;
  long                trackObjectRefCon;
  Track               defaultTrack;
  long                defaultObjectRefCon;
  long                reserved1;
  long                reserved2;
};
typedef struct QTCustomActionTargetRecord QTCustomActionTargetRecord;
typedef QTCustomActionTargetRecord *    QTCustomActionTargetPtr;
struct MediaEQSpectrumBandsRecord {
  short               count;
  UnsignedFixedPtr    frequency;              /* pointer to array of frequencies*/
};
typedef struct MediaEQSpectrumBandsRecord MediaEQSpectrumBandsRecord;
typedef MediaEQSpectrumBandsRecord *    MediaEQSpectrumBandsRecordPtr;
/*
 *  CallComponentExecuteWiredAction()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
CallComponentExecuteWiredAction(
  ComponentInstance         ci,
  QTAtomContainer           actionContainer,
  QTAtom                    actionAtom,
  QTCustomActionTargetPtr   target,
  QTEventRecordPtr          event);



/* MediaCallRange2 */
/* These are unique to each type of media handler */
/* They are also included in the public interfaces */


/***** These are the calls for dealing with the Generic media handler *****/
/*
 *  MediaInitialize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaInitialize(
  MediaHandler              mh,
  GetMovieCompleteParams *  gmc);


/*
 *  MediaSetHandlerCapabilities()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetHandlerCapabilities(
  MediaHandler   mh,
  long           flags,
  long           flagsMask);


/*
 *  MediaIdle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaIdle(
  MediaHandler        mh,
  TimeValue           atMediaTime,
  long                flagsIn,
  long *              flagsOut,
  const TimeRecord *  movieTime);


/*
 *  MediaGetMediaInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetMediaInfo(
  MediaHandler   mh,
  Handle         h);


/*
 *  MediaPutMediaInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaPutMediaInfo(
  MediaHandler   mh,
  Handle         h);


/*
 *  MediaSetActive()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetActive(
  MediaHandler   mh,
  Boolean        enableMedia);


/*
 *  MediaSetRate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetRate(
  MediaHandler   mh,
  Fixed          rate);


/*
 *  MediaGGetStatus()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGGetStatus(
  MediaHandler       mh,
  ComponentResult *  statusErr);


/*
 *  MediaTrackEdited()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaTrackEdited(MediaHandler mh);


/*
 *  MediaSetMediaTimeScale()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetMediaTimeScale(
  MediaHandler   mh,
  TimeScale      newTimeScale);


/*
 *  MediaSetMovieTimeScale()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetMovieTimeScale(
  MediaHandler   mh,
  TimeScale      newTimeScale);


/*
 *  MediaSetGWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetGWorld(
  MediaHandler   mh,
  CGrafPtr       aPort,
  GDHandle       aGD);


/*
 *  MediaSetDimensions()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetDimensions(
  MediaHandler   mh,
  Fixed          width,
  Fixed          height);


/*
 *  MediaSetClip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetClip(
  MediaHandler   mh,
  RgnHandle      theClip);


/*
 *  MediaSetMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetMatrix(
  MediaHandler    mh,
  MatrixRecord *  trackMovieMatrix);


/*
 *  MediaGetTrackOpaque()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetTrackOpaque(
  MediaHandler   mh,
  Boolean *      trackIsOpaque);


/*
 *  MediaSetGraphicsMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetGraphicsMode(
  MediaHandler      mh,
  long              mode,
  const RGBColor *  opColor);


/*
 *  MediaGetGraphicsMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetGraphicsMode(
  MediaHandler   mh,
  long *         mode,
  RGBColor *     opColor);


/*
 *  MediaGSetVolume()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGSetVolume(
  MediaHandler   mh,
  short          volume);


/*
 *  MediaSetSoundBalance()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetSoundBalance(
  MediaHandler   mh,
  short          balance);


/*
 *  MediaGetSoundBalance()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetSoundBalance(
  MediaHandler   mh,
  short *        balance);


/*
 *  MediaGetNextBoundsChange()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetNextBoundsChange(
  MediaHandler   mh,
  TimeValue *    when);


/*
 *  MediaGetSrcRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetSrcRgn(
  MediaHandler   mh,
  RgnHandle      rgn,
  TimeValue      atMediaTime);


/*
 *  MediaPreroll()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaPreroll(
  MediaHandler   mh,
  TimeValue      time,
  Fixed          rate);


/*
 *  MediaSampleDescriptionChanged()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSampleDescriptionChanged(
  MediaHandler   mh,
  long           index);


/*
 *  MediaHasCharacteristic()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaHasCharacteristic(
  MediaHandler   mh,
  OSType         characteristic,
  Boolean *      hasIt);


/*
 *  MediaGetOffscreenBufferSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetOffscreenBufferSize(
  MediaHandler   mh,
  Rect *         bounds,
  short          depth,
  CTabHandle     ctab);


/*
 *  MediaSetHints()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetHints(
  MediaHandler   mh,
  long           hints);


/*
 *  MediaGetName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetName(
  MediaHandler   mh,
  Str255         name,
  long           requestedLanguage,
  long *         actualLanguage);


/*
 *  MediaForceUpdate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaForceUpdate(
  MediaHandler   mh,
  long           forceUpdateFlags);


/*
 *  MediaGetDrawingRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetDrawingRgn(
  MediaHandler   mh,
  RgnHandle *    partialRgn);


/*
 *  MediaGSetActiveSegment()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGSetActiveSegment(
  MediaHandler   mh,
  TimeValue      activeStart,
  TimeValue      activeDuration);


/*
 *  MediaInvalidateRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaInvalidateRegion(
  MediaHandler   mh,
  RgnHandle      invalRgn);


/*
 *  MediaGetNextStepTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetNextStepTime(
  MediaHandler   mh,
  short          flags,
  TimeValue      mediaTimeIn,
  TimeValue *    mediaTimeOut,
  Fixed          rate);


/*
 *  MediaSetNonPrimarySourceData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetNonPrimarySourceData(
  MediaHandler                 mh,
  long                         inputIndex,
  long                         dataDescriptionSeed,
  Handle                       dataDescription,
  void *                       data,
  long                         dataSize,
  ICMCompletionProcRecordPtr   asyncCompletionProc,
  ICMConvertDataFormatUPP      transferProc,
  void *                       refCon);


/*
 *  MediaChangedNonPrimarySource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaChangedNonPrimarySource(
  MediaHandler   mh,
  long           inputIndex);


/*
 *  MediaTrackReferencesChanged()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaTrackReferencesChanged(MediaHandler mh);


/*
 *  MediaGetSampleDataPointer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetSampleDataPointer(
  MediaHandler   mh,
  long           sampleNum,
  Ptr *          dataPtr,
  long *         dataSize,
  long *         sampleDescIndex);


/*
 *  MediaReleaseSampleDataPointer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaReleaseSampleDataPointer(
  MediaHandler   mh,
  long           sampleNum);


/*
 *  MediaTrackPropertyAtomChanged()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaTrackPropertyAtomChanged(MediaHandler mh);


/*
 *  MediaSetTrackInputMapReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetTrackInputMapReference(
  MediaHandler      mh,
  QTAtomContainer   inputMap);



/*
 *  MediaSetVideoParam()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetVideoParam(
  MediaHandler      mh,
  long              whichParam,
  unsigned short *  value);


/*
 *  MediaGetVideoParam()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetVideoParam(
  MediaHandler      mh,
  long              whichParam,
  unsigned short *  value);


/*
 *  MediaCompare()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaCompare(
  MediaHandler        mh,
  Boolean *           isOK,
  Media               srcMedia,
  ComponentInstance   srcMediaComponent);


/*
 *  MediaGetClock()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetClock(
  MediaHandler         mh,
  ComponentInstance *  clock);


/*
 *  MediaSetSoundOutputComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetSoundOutputComponent(
  MediaHandler   mh,
  Component      outputComponent);


/*
 *  MediaGetSoundOutputComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetSoundOutputComponent(
  MediaHandler   mh,
  Component *    outputComponent);


/*
 *  MediaSetSoundLocalizationData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetSoundLocalizationData(
  MediaHandler   mh,
  Handle         data);





/*
 *  MediaGetInvalidRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetInvalidRegion(
  MediaHandler   mh,
  RgnHandle      rgn);



/*
 *  MediaSampleDescriptionB2N()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSampleDescriptionB2N(
  MediaHandler              mh,
  SampleDescriptionHandle   sampleDescriptionH);


/*
 *  MediaSampleDescriptionN2B()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSampleDescriptionN2B(
  MediaHandler              mh,
  SampleDescriptionHandle   sampleDescriptionH);


/*
 *  MediaQueueNonPrimarySourceData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaQueueNonPrimarySourceData(
  MediaHandler                 mh,
  long                         inputIndex,
  long                         dataDescriptionSeed,
  Handle                       dataDescription,
  void *                       data,
  long                         dataSize,
  ICMCompletionProcRecordPtr   asyncCompletionProc,
  const ICMFrameTimeRecord *   frameTime,
  ICMConvertDataFormatUPP      transferProc,
  void *                       refCon);


/*
 *  MediaFlushNonPrimarySourceData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaFlushNonPrimarySourceData(
  MediaHandler   mh,
  long           inputIndex);



/*
 *  MediaGetURLLink()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetURLLink(
  MediaHandler   mh,
  Point          displayWhere,
  Handle *       urlLink);



/*
 *  MediaMakeMediaTimeTable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaMakeMediaTimeTable(
  MediaHandler   mh,
  long **        offsets,
  TimeValue      startTime,
  TimeValue      endTime,
  TimeValue      timeIncrement,
  short          firstDataRefIndex,
  short          lastDataRefIndex,
  long *         retDataRefSkew);


/*
 *  MediaHitTestForTargetRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaHitTestForTargetRefCon(
  MediaHandler   mh,
  long           flags,
  Point          loc,
  long *         targetRefCon);


/*
 *  MediaHitTestTargetRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaHitTestTargetRefCon(
  MediaHandler   mh,
  long           targetRefCon,
  long           flags,
  Point          loc,
  Boolean *      wasHit);


/*
 *  MediaGetActionsForQTEvent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetActionsForQTEvent(
  MediaHandler       mh,
  QTEventRecordPtr   event,
  long               targetRefCon,
  QTAtomContainer *  container,
  QTAtom *           atom);


/*
 *  MediaDisposeTargetRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaDisposeTargetRefCon(
  MediaHandler   mh,
  long           targetRefCon);


/*
 *  MediaTargetRefConsEqual()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaTargetRefConsEqual(
  MediaHandler   mh,
  long           firstRefCon,
  long           secondRefCon,
  Boolean *      equal);


/*
 *  MediaSetActionsCallback()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetActionsCallback(
  MediaHandler   mh,
  ActionsUPP     actionsCallbackProc,
  void *         refcon);


/*
 *  MediaPrePrerollBegin()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaPrePrerollBegin(
  MediaHandler            mh,
  TimeValue               time,
  Fixed                   rate,
  PrePrerollCompleteUPP   completeProc,
  void *                  refcon);


/*
 *  MediaPrePrerollCancel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaPrePrerollCancel(
  MediaHandler   mh,
  void *         refcon);


/*
 *  MediaEnterEmptyEdit()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaEnterEmptyEdit(MediaHandler mh);


/*
 *  MediaCurrentMediaQueuedData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MediaCurrentMediaQueuedData(
  MediaHandler   mh,
  long *         milliSecs);


/*
 *  MediaGetEffectiveVolume()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
MediaGetEffectiveVolume(
  MediaHandler   mh,
  short *        volume);


/*
 *  MediaResolveTargetRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
MediaResolveTargetRefCon(
  MediaHandler      mh,
  QTAtomContainer   container,
  QTAtom            atom,
  long *            targetRefCon);


/*
 *  MediaGetSoundLevelMeteringEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
MediaGetSoundLevelMeteringEnabled(
  MediaHandler   mh,
  Boolean *      enabled);


/*
 *  MediaSetSoundLevelMeteringEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
MediaSetSoundLevelMeteringEnabled(
  MediaHandler   mh,
  Boolean        enable);


/*
 *  MediaGetSoundLevelMeterInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
MediaGetSoundLevelMeterInfo(
  MediaHandler        mh,
  LevelMeterInfoPtr   levelInfo);


/*
 *  MediaGetEffectiveSoundBalance()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
MediaGetEffectiveSoundBalance(
  MediaHandler   mh,
  short *        balance);


/*
 *  MediaSetScreenLock()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
MediaSetScreenLock(
  MediaHandler   mh,
  Boolean        lockIt);


/*
 *  MediaSetDoMCActionCallback()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
MediaSetDoMCActionCallback(
  MediaHandler    mh,
  DoMCActionUPP   doMCActionCallbackProc,
  void *          refcon);


/*
 *  MediaGetErrorString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
MediaGetErrorString(
  MediaHandler      mh,
  ComponentResult   theError,
  Str255            errorString);


/*
 *  MediaGetSoundEqualizerBands()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
MediaGetSoundEqualizerBands(
  MediaHandler                    mh,
  MediaEQSpectrumBandsRecordPtr   spectrumInfo);


/*
 *  MediaSetSoundEqualizerBands()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
MediaSetSoundEqualizerBands(
  MediaHandler                    mh,
  MediaEQSpectrumBandsRecordPtr   spectrumInfo);


/*
 *  MediaGetSoundEqualizerBandLevels()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
MediaGetSoundEqualizerBandLevels(
  MediaHandler   mh,
  UInt8 *        bandLevels);


/*
 *  MediaDoIdleActions()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
MediaDoIdleActions(MediaHandler mh);


/*
 *  MediaSetSoundBassAndTreble()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
MediaSetSoundBassAndTreble(
  MediaHandler   mh,
  short          bass,
  short          treble);


/*
 *  MediaGetSoundBassAndTreble()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
MediaGetSoundBassAndTreble(
  MediaHandler   mh,
  short *        bass,
  short *        treble);


/*
 *  MediaTimeBaseChanged()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
MediaTimeBaseChanged(MediaHandler mh);


/*
 *  MediaMCIsPlayerEvent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern ComponentResult 
MediaMCIsPlayerEvent(
  MediaHandler         mh,
  const EventRecord *  e,
  Boolean *            handledIt);


/*
 *  MediaGetMediaLoadState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern ComponentResult 
MediaGetMediaLoadState(
  MediaHandler   mh,
  long *         mediaLoadState);


/*
 *  MediaVideoOutputChanged()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern ComponentResult 
MediaVideoOutputChanged(
  MediaHandler        mh,
  ComponentInstance   vout);


/*
 *  MediaEmptySampleCache()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern ComponentResult 
MediaEmptySampleCache(
  MediaHandler   mh,
  long           sampleNum,
  long           sampleCount);


/*
 *  MediaGetPublicInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern ComponentResult 
MediaGetPublicInfo(
  MediaHandler   mh,
  OSType         infoSelector,
  void *         infoDataPtr,
  Size *         ioDataSize);


/*
 *  MediaSetPublicInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern ComponentResult 
MediaSetPublicInfo(
  MediaHandler   mh,
  OSType         infoSelector,
  void *         infoDataPtr,
  Size           dataSize);


/*
 *  MediaGetUserPreferredCodecs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern ComponentResult 
MediaGetUserPreferredCodecs(
  MediaHandler            mh,
  CodecComponentHandle *  userPreferredCodecs);


/*
 *  MediaSetUserPreferredCodecs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern ComponentResult 
MediaSetUserPreferredCodecs(
  MediaHandler           mh,
  CodecComponentHandle   userPreferredCodecs);





/* selectors for component calls */
enum {
    kCallComponentExecuteWiredActionSelect     = -9,
    kMediaInitializeSelect                     = 0x0501,
    kMediaSetHandlerCapabilitiesSelect         = 0x0502,
    kMediaIdleSelect                           = 0x0503,
    kMediaGetMediaInfoSelect                   = 0x0504,
    kMediaPutMediaInfoSelect                   = 0x0505,
    kMediaSetActiveSelect                      = 0x0506,
    kMediaSetRateSelect                        = 0x0507,
    kMediaGGetStatusSelect                     = 0x0508,
    kMediaTrackEditedSelect                    = 0x0509,
    kMediaSetMediaTimeScaleSelect              = 0x050A,
    kMediaSetMovieTimeScaleSelect              = 0x050B,
    kMediaSetGWorldSelect                      = 0x050C,
    kMediaSetDimensionsSelect                  = 0x050D,
    kMediaSetClipSelect                        = 0x050E,
    kMediaSetMatrixSelect                      = 0x050F,
    kMediaGetTrackOpaqueSelect                 = 0x0510,
    kMediaSetGraphicsModeSelect                = 0x0511,
    kMediaGetGraphicsModeSelect                = 0x0512,
    kMediaGSetVolumeSelect                     = 0x0513,
    kMediaSetSoundBalanceSelect                = 0x0514,
    kMediaGetSoundBalanceSelect                = 0x0515,
    kMediaGetNextBoundsChangeSelect            = 0x0516,
    kMediaGetSrcRgnSelect                      = 0x0517,
    kMediaPrerollSelect                        = 0x0518,
    kMediaSampleDescriptionChangedSelect       = 0x0519,
    kMediaHasCharacteristicSelect              = 0x051A,
    kMediaGetOffscreenBufferSizeSelect         = 0x051B,
    kMediaSetHintsSelect                       = 0x051C,
    kMediaGetNameSelect                        = 0x051D,
    kMediaForceUpdateSelect                    = 0x051E,
    kMediaGetDrawingRgnSelect                  = 0x051F,
    kMediaGSetActiveSegmentSelect              = 0x0520,
    kMediaInvalidateRegionSelect               = 0x0521,
    kMediaGetNextStepTimeSelect                = 0x0522,
    kMediaSetNonPrimarySourceDataSelect        = 0x0523,
    kMediaChangedNonPrimarySourceSelect        = 0x0524,
    kMediaTrackReferencesChangedSelect         = 0x0525,
    kMediaGetSampleDataPointerSelect           = 0x0526,
    kMediaReleaseSampleDataPointerSelect       = 0x0527,
    kMediaTrackPropertyAtomChangedSelect       = 0x0528,
    kMediaSetTrackInputMapReferenceSelect      = 0x0529,
    kMediaSetVideoParamSelect                  = 0x052B,
    kMediaGetVideoParamSelect                  = 0x052C,
    kMediaCompareSelect                        = 0x052D,
    kMediaGetClockSelect                       = 0x052E,
    kMediaSetSoundOutputComponentSelect        = 0x052F,
    kMediaGetSoundOutputComponentSelect        = 0x0530,
    kMediaSetSoundLocalizationDataSelect       = 0x0531,
    kMediaGetInvalidRegionSelect               = 0x053C,
    kMediaSampleDescriptionB2NSelect           = 0x053E,
    kMediaSampleDescriptionN2BSelect           = 0x053F,
    kMediaQueueNonPrimarySourceDataSelect      = 0x0540,
    kMediaFlushNonPrimarySourceDataSelect      = 0x0541,
    kMediaGetURLLinkSelect                     = 0x0543,
    kMediaMakeMediaTimeTableSelect             = 0x0545,
    kMediaHitTestForTargetRefConSelect         = 0x0546,
    kMediaHitTestTargetRefConSelect            = 0x0547,
    kMediaGetActionsForQTEventSelect           = 0x0548,
    kMediaDisposeTargetRefConSelect            = 0x0549,
    kMediaTargetRefConsEqualSelect             = 0x054A,
    kMediaSetActionsCallbackSelect             = 0x054B,
    kMediaPrePrerollBeginSelect                = 0x054C,
    kMediaPrePrerollCancelSelect               = 0x054D,
    kMediaEnterEmptyEditSelect                 = 0x054F,
    kMediaCurrentMediaQueuedDataSelect         = 0x0550,
    kMediaGetEffectiveVolumeSelect             = 0x0551,
    kMediaResolveTargetRefConSelect            = 0x0552,
    kMediaGetSoundLevelMeteringEnabledSelect   = 0x0553,
    kMediaSetSoundLevelMeteringEnabledSelect   = 0x0554,
    kMediaGetSoundLevelMeterInfoSelect         = 0x0555,
    kMediaGetEffectiveSoundBalanceSelect       = 0x0556,
    kMediaSetScreenLockSelect                  = 0x0557,
    kMediaSetDoMCActionCallbackSelect          = 0x0558,
    kMediaGetErrorStringSelect                 = 0x0559,
    kMediaGetSoundEqualizerBandsSelect         = 0x055A,
    kMediaSetSoundEqualizerBandsSelect         = 0x055B,
    kMediaGetSoundEqualizerBandLevelsSelect    = 0x055C,
    kMediaDoIdleActionsSelect                  = 0x055D,
    kMediaSetSoundBassAndTrebleSelect          = 0x055E,
    kMediaGetSoundBassAndTrebleSelect          = 0x055F,
    kMediaTimeBaseChangedSelect                = 0x0560,
    kMediaMCIsPlayerEventSelect                = 0x0561,
    kMediaGetMediaLoadStateSelect              = 0x0562,
    kMediaVideoOutputChangedSelect             = 0x0563,
    kMediaEmptySampleCacheSelect               = 0x0564,
    kMediaGetPublicInfoSelect                  = 0x0565,
    kMediaSetPublicInfoSelect                  = 0x0566,
    kMediaGetUserPreferredCodecsSelect         = 0x0567,
    kMediaSetUserPreferredCodecsSelect         = 0x0568
};
/*
 *  NewPrePrerollCompleteUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  DisposePrePrerollCompleteUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  InvokePrePrerollCompleteUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */


#if PRAGMA_STRUCT_ALIGN
    #pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif /* __MEDIAHANDLERS__ */

