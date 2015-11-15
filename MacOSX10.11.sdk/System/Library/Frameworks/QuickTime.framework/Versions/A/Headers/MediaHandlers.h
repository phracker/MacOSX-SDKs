/*
     File:       QuickTime/MediaHandlers.h
 
     Contains:   QuickTime Interfaces.
 
     Version:    QuickTime 7.7.3
 
     Copyright:  © 1990-2015 by Apple Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*
  QuickTime has been deprecated in 10.9.

  AVFoundation and AVKit are the frameworks recommended for all new development 
  involving time-based audiovisual media on OS X.
*/

#ifndef __MEDIAHANDLERS__
#define __MEDIAHANDLERS__

#ifndef __CARBON__
#include <Carbon/Carbon.h>
#endif

#ifndef __MOVIES__
#include <QuickTime/Movies.h>
#endif




#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)

/* QuickTime is not available to 64-bit clients */

#if !__LP64__

typedef CALLBACK_API( void , PrePrerollCompleteProcPtr )(MediaHandler mh, OSErr err, void *refcon);
typedef STACK_UPP_TYPE(PrePrerollCompleteProcPtr)               PrePrerollCompleteUPP;
/* derived media handler capability flags */
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
  QTMediaContextID    mediaContextID;
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
 *  CallComponentExecuteWiredAction()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in QTMLClient.lib 4.0 and later
 */
extern ComponentResult 
CallComponentExecuteWiredAction(
  ComponentInstance         ci,
  QTAtomContainer           actionContainer,
  QTAtom                    actionAtom,
  QTCustomActionTargetPtr   target,
  QTEventRecordPtr          event)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;



/* MediaCallRange2 */
/* These are unique to each type of media handler */
/* They are also included in the public interfaces */


/* Flags for MediaSetChunkManagementFlags*/
enum {
  kEmptyPurgableChunksOverAllowance = 1
};

/*
 *  MediaSetChunkManagementFlags()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in QTMLClient.lib 6.0 and later
 */
extern ComponentResult 
MediaSetChunkManagementFlags(
  MediaHandler   mh,
  UInt32         flags,
  UInt32         flagsMask)                                   AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetChunkManagementFlags()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in QTMLClient.lib 6.0 and later
 */
extern ComponentResult 
MediaGetChunkManagementFlags(
  MediaHandler   mh,
  UInt32 *       flags)                                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetPurgeableChunkMemoryAllowance()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in QTMLClient.lib 6.0 and later
 */
extern ComponentResult 
MediaSetPurgeableChunkMemoryAllowance(
  MediaHandler   mh,
  Size           allowance)                                   AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetPurgeableChunkMemoryAllowance()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in QTMLClient.lib 6.0 and later
 */
extern ComponentResult 
MediaGetPurgeableChunkMemoryAllowance(
  MediaHandler   mh,
  Size *         allowance)                                   AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaEmptyAllPurgeableChunks()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in QTMLClient.lib 6.0 and later
 */
extern ComponentResult 
MediaEmptyAllPurgeableChunks(MediaHandler mh)                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/***** These are the calls for dealing with the Generic media handler *****/
/*
 *  MediaInitialize()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaInitialize(
  MediaHandler              mh,
  GetMovieCompleteParams *  gmc)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetHandlerCapabilities()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetHandlerCapabilities(
  MediaHandler   mh,
  long           flags,
  long           flagsMask)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaIdle()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaIdle(
  MediaHandler        mh,
  TimeValue           atMediaTime,
  long                flagsIn,
  long *              flagsOut,
  const TimeRecord *  movieTime)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetMediaInfo()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetMediaInfo(
  MediaHandler   mh,
  Handle         h)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaPutMediaInfo()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaPutMediaInfo(
  MediaHandler   mh,
  Handle         h)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetActive()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetActive(
  MediaHandler   mh,
  Boolean        enableMedia)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetRate()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetRate(
  MediaHandler   mh,
  Fixed          rate)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGGetStatus()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGGetStatus(
  MediaHandler       mh,
  ComponentResult *  statusErr)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaTrackEdited()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaTrackEdited(MediaHandler mh)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetMediaTimeScale()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetMediaTimeScale(
  MediaHandler   mh,
  TimeScale      newTimeScale)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetMovieTimeScale()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetMovieTimeScale(
  MediaHandler   mh,
  TimeScale      newTimeScale)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetGWorld()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetGWorld(
  MediaHandler   mh,
  CGrafPtr       aPort,
  GDHandle       aGD)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetDimensions()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetDimensions(
  MediaHandler   mh,
  Fixed          width,
  Fixed          height)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetClip()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetClip(
  MediaHandler   mh,
  RgnHandle      theClip)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetMatrix()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetMatrix(
  MediaHandler    mh,
  MatrixRecord *  trackMovieMatrix)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetTrackOpaque()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetTrackOpaque(
  MediaHandler   mh,
  Boolean *      trackIsOpaque)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetGraphicsMode()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetGraphicsMode(
  MediaHandler      mh,
  long              mode,
  const RGBColor *  opColor)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetGraphicsMode()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetGraphicsMode(
  MediaHandler   mh,
  long *         mode,
  RGBColor *     opColor)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGSetVolume()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGSetVolume(
  MediaHandler   mh,
  short          volume)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetSoundBalance()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetSoundBalance(
  MediaHandler   mh,
  short          balance)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetSoundBalance()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetSoundBalance(
  MediaHandler   mh,
  short *        balance)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetNextBoundsChange()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetNextBoundsChange(
  MediaHandler   mh,
  TimeValue *    when)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetSrcRgn()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetSrcRgn(
  MediaHandler   mh,
  RgnHandle      rgn,
  TimeValue      atMediaTime)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaPreroll()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaPreroll(
  MediaHandler   mh,
  TimeValue      time,
  Fixed          rate)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSampleDescriptionChanged()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSampleDescriptionChanged(
  MediaHandler   mh,
  long           index)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaHasCharacteristic()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaHasCharacteristic(
  MediaHandler   mh,
  OSType         characteristic,
  Boolean *      hasIt)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetOffscreenBufferSize()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetOffscreenBufferSize(
  MediaHandler   mh,
  Rect *         bounds,
  short          depth,
  CTabHandle     ctab)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetHints()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetHints(
  MediaHandler   mh,
  long           hints)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetName()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetName(
  MediaHandler   mh,
  Str255         name,
  long           requestedLanguage,
  long *         actualLanguage)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaForceUpdate()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaForceUpdate(
  MediaHandler   mh,
  long           forceUpdateFlags)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetDrawingRgn()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetDrawingRgn(
  MediaHandler   mh,
  RgnHandle *    partialRgn)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGSetActiveSegment()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGSetActiveSegment(
  MediaHandler   mh,
  TimeValue      activeStart,
  TimeValue      activeDuration)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaInvalidateRegion()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaInvalidateRegion(
  MediaHandler   mh,
  RgnHandle      invalRgn)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetNextStepTime()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetNextStepTime(
  MediaHandler   mh,
  short          flags,
  TimeValue      mediaTimeIn,
  TimeValue *    mediaTimeOut,
  Fixed          rate)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetNonPrimarySourceData()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
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
  void *                       refCon)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaChangedNonPrimarySource()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaChangedNonPrimarySource(
  MediaHandler   mh,
  long           inputIndex)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaTrackReferencesChanged()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaTrackReferencesChanged(MediaHandler mh)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetSampleDataPointer()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetSampleDataPointer(
  MediaHandler   mh,
  long           sampleNum,
  Ptr *          dataPtr,
  long *         dataSize,
  long *         sampleDescIndex)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaReleaseSampleDataPointer()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaReleaseSampleDataPointer(
  MediaHandler   mh,
  long           sampleNum)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaTrackPropertyAtomChanged()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaTrackPropertyAtomChanged(MediaHandler mh)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetTrackInputMapReference()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetTrackInputMapReference(
  MediaHandler      mh,
  QTAtomContainer   inputMap)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;



/*
 *  MediaSetVideoParam()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetVideoParam(
  MediaHandler      mh,
  long              whichParam,
  unsigned short *  value)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetVideoParam()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetVideoParam(
  MediaHandler      mh,
  long              whichParam,
  unsigned short *  value)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaCompare()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaCompare(
  MediaHandler        mh,
  Boolean *           isOK,
  Media               srcMedia,
  ComponentInstance   srcMediaComponent)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetClock()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetClock(
  MediaHandler         mh,
  ComponentInstance *  clock)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetSoundOutputComponent()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetSoundOutputComponent(
  MediaHandler   mh,
  Component      outputComponent)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetSoundOutputComponent()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetSoundOutputComponent(
  MediaHandler   mh,
  Component *    outputComponent)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetSoundLocalizationData()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetSoundLocalizationData(
  MediaHandler   mh,
  Handle         data)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;



/*
 *  MediaGetInvalidRegion()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetInvalidRegion(
  MediaHandler   mh,
  RgnHandle      rgn)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;



/*
 *  MediaSampleDescriptionB2N()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSampleDescriptionB2N(
  MediaHandler              mh,
  SampleDescriptionHandle   sampleDescriptionH)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSampleDescriptionN2B()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSampleDescriptionN2B(
  MediaHandler              mh,
  SampleDescriptionHandle   sampleDescriptionH)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaQueueNonPrimarySourceData()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
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
  void *                       refCon)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaFlushNonPrimarySourceData()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaFlushNonPrimarySourceData(
  MediaHandler   mh,
  long           inputIndex)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;



/*
 *  MediaGetURLLink()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetURLLink(
  MediaHandler   mh,
  Point          displayWhere,
  Handle *       urlLink)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;



/*
 *  MediaMakeMediaTimeTable()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
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
  long *         retDataRefSkew)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaHitTestForTargetRefCon()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaHitTestForTargetRefCon(
  MediaHandler   mh,
  long           flags,
  Point          loc,
  long *         targetRefCon)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaHitTestTargetRefCon()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaHitTestTargetRefCon(
  MediaHandler   mh,
  long           targetRefCon,
  long           flags,
  Point          loc,
  Boolean *      wasHit)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetActionsForQTEvent()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaGetActionsForQTEvent(
  MediaHandler       mh,
  QTEventRecordPtr   event,
  long               targetRefCon,
  QTAtomContainer *  container,
  QTAtom *           atom)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaDisposeTargetRefCon()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaDisposeTargetRefCon(
  MediaHandler   mh,
  long           targetRefCon)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaTargetRefConsEqual()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaTargetRefConsEqual(
  MediaHandler   mh,
  long           firstRefCon,
  long           secondRefCon,
  Boolean *      equal)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetActionsCallback()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaSetActionsCallback(
  MediaHandler   mh,
  ActionsUPP     actionsCallbackProc,
  void *         refcon)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaPrePrerollBegin()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaPrePrerollBegin(
  MediaHandler            mh,
  TimeValue               time,
  Fixed                   rate,
  PrePrerollCompleteUPP   completeProc,
  void *                  refcon)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaPrePrerollCancel()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaPrePrerollCancel(
  MediaHandler   mh,
  void *         refcon)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaEnterEmptyEdit()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaEnterEmptyEdit(MediaHandler mh)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaCurrentMediaQueuedData()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in QTMLClient.lib 3.0 and later
 */
extern ComponentResult 
MediaCurrentMediaQueuedData(
  MediaHandler   mh,
  long *         milliSecs)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetEffectiveVolume()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in QTMLClient.lib 4.0 and later
 */
extern ComponentResult 
MediaGetEffectiveVolume(
  MediaHandler   mh,
  short *        volume)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaResolveTargetRefCon()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in QTMLClient.lib 4.0 and later
 */
extern ComponentResult 
MediaResolveTargetRefCon(
  MediaHandler      mh,
  QTAtomContainer   container,
  QTAtom            atom,
  long *            targetRefCon)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetSoundLevelMeteringEnabled()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in QTMLClient.lib 4.0 and later
 */
extern ComponentResult 
MediaGetSoundLevelMeteringEnabled(
  MediaHandler   mh,
  Boolean *      enabled)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetSoundLevelMeteringEnabled()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in QTMLClient.lib 4.0 and later
 */
extern ComponentResult 
MediaSetSoundLevelMeteringEnabled(
  MediaHandler   mh,
  Boolean        enable)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetSoundLevelMeterInfo()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in QTMLClient.lib 4.0 and later
 */
extern ComponentResult 
MediaGetSoundLevelMeterInfo(
  MediaHandler        mh,
  LevelMeterInfoPtr   levelInfo)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetEffectiveSoundBalance()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in QTMLClient.lib 4.0 and later
 */
extern ComponentResult 
MediaGetEffectiveSoundBalance(
  MediaHandler   mh,
  short *        balance)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetScreenLock()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in QTMLClient.lib 4.0 and later
 */
extern ComponentResult 
MediaSetScreenLock(
  MediaHandler   mh,
  Boolean        lockIt)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetDoMCActionCallback()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in QTMLClient.lib 4.0 and later
 */
extern ComponentResult 
MediaSetDoMCActionCallback(
  MediaHandler    mh,
  DoMCActionUPP   doMCActionCallbackProc,
  void *          refcon)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetErrorString()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in QTMLClient.lib 4.0 and later
 */
extern ComponentResult 
MediaGetErrorString(
  MediaHandler      mh,
  ComponentResult   theError,
  Str255            errorString)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetSoundEqualizerBands()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in QTMLClient.lib 4.0 and later
 */
extern ComponentResult 
MediaGetSoundEqualizerBands(
  MediaHandler                    mh,
  MediaEQSpectrumBandsRecordPtr   spectrumInfo)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetSoundEqualizerBands()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in QTMLClient.lib 4.0 and later
 */
extern ComponentResult 
MediaSetSoundEqualizerBands(
  MediaHandler                    mh,
  MediaEQSpectrumBandsRecordPtr   spectrumInfo)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetSoundEqualizerBandLevels()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in QTMLClient.lib 4.0 and later
 */
extern ComponentResult 
MediaGetSoundEqualizerBandLevels(
  MediaHandler   mh,
  UInt8 *        bandLevels)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaDoIdleActions()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in QTMLClient.lib 4.0 and later
 */
extern ComponentResult 
MediaDoIdleActions(MediaHandler mh)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetSoundBassAndTreble()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in QTMLClient.lib 4.0 and later
 */
extern ComponentResult 
MediaSetSoundBassAndTreble(
  MediaHandler   mh,
  short          bass,
  short          treble)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetSoundBassAndTreble()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in QTMLClient.lib 4.0 and later
 */
extern ComponentResult 
MediaGetSoundBassAndTreble(
  MediaHandler   mh,
  short *        bass,
  short *        treble)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaTimeBaseChanged()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in QTMLClient.lib 4.0 and later
 */
extern ComponentResult 
MediaTimeBaseChanged(MediaHandler mh)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaMCIsPlayerEvent()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in QTMLClient.lib 4.1 and later
 */
extern ComponentResult 
MediaMCIsPlayerEvent(
  MediaHandler         mh,
  const EventRecord *  e,
  Boolean *            handledIt)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetMediaLoadState()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in QTMLClient.lib 4.1 and later
 */
extern ComponentResult 
MediaGetMediaLoadState(
  MediaHandler   mh,
  long *         mediaLoadState)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaVideoOutputChanged()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in QTMLClient.lib 5.0 and later
 */
extern ComponentResult 
MediaVideoOutputChanged(
  MediaHandler        mh,
  ComponentInstance   vout)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaEmptySampleCache()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in QTMLClient.lib 5.0 and later
 */
extern ComponentResult 
MediaEmptySampleCache(
  MediaHandler   mh,
  long           sampleNum,
  long           sampleCount)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetPublicInfo()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in QTMLClient.lib 5.0 and later
 */
extern ComponentResult 
MediaGetPublicInfo(
  MediaHandler   mh,
  OSType         infoSelector,
  void *         infoDataPtr,
  Size *         ioDataSize)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetPublicInfo()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in QTMLClient.lib 5.0 and later
 */
extern ComponentResult 
MediaSetPublicInfo(
  MediaHandler   mh,
  OSType         infoSelector,
  void *         infoDataPtr,
  Size           dataSize)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetUserPreferredCodecs()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in QTMLClient.lib 5.0 and later
 */
extern ComponentResult 
MediaGetUserPreferredCodecs(
  MediaHandler            mh,
  CodecComponentHandle *  userPreferredCodecs)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaSetUserPreferredCodecs()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in QTMLClient.lib 5.0 and later
 */
extern ComponentResult 
MediaSetUserPreferredCodecs(
  MediaHandler           mh,
  CodecComponentHandle   userPreferredCodecs)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/* Keyboard Focus Support*/

/*
 *  MediaRefConSetProperty()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in QTMLClient.lib 6.0 and later
 */
extern ComponentResult 
MediaRefConSetProperty(
  MediaHandler   mh,
  long           refCon,
  long           propertyType,
  void *         propertyValue)                               AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaRefConGetProperty()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in QTMLClient.lib 6.0 and later
 */
extern ComponentResult 
MediaRefConGetProperty(
  MediaHandler   mh,
  long           refCon,
  long           propertyType,
  void *         propertyValue)                               AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaNavigateTargetRefCon()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in QTMLClient.lib 6.0 and later
 */
extern ComponentResult 
MediaNavigateTargetRefCon(
  MediaHandler   mh,
  long           navigation,
  long *         refCon)                                      AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;



/*
 *  MediaGGetIdleManager()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in QTMLClient.lib 6.0 and later
 */
extern ComponentResult 
MediaGGetIdleManager(
  MediaHandler   mh,
  IdleManager *  pim)                                         AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGSetIdleManager()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in QTMLClient.lib 6.0 and later
 */
extern ComponentResult 
MediaGSetIdleManager(
  MediaHandler   mh,
  IdleManager    im)                                          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGGetLatency()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in QTMLClient.lib 6.5 and later
 */
extern ComponentResult 
MediaGGetLatency(
  MediaHandler   mh,
  TimeRecord *   latency)                                     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/* Aperture Mode Support*/

/*
 *  MediaSetTrackApertureModeDimensionsUsingSampleDescription()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Sets the three aperture mode dimension properties on the track,
 *    calculating the values using the provided sample description.
 *  
 *  Parameters:
 *    
 *    mh:
 *      [in] The media handler.
 *    
 *    sampleDesc:
 *      [in] The sample description handle.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 (or QuickTime 7.1) and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
MediaSetTrackApertureModeDimensionsUsingSampleDescription(
  MediaHandler              mh,
  SampleDescriptionHandle   sampleDesc)                       AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetApertureModeClipRectForSampleDescriptionIndex()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Calculates a source clip rectangle appropriate for the current
 *    aperture mode and the given sample description.
 *  
 *  Discussion:
 *    If the track's aperture mode is kQTApertureMode_CleanAperture,
 *    the rectangle should be the clean aperture as described by the
 *    sample description (see
 *    kICMImageDescriptionPropertyID_CleanApertureClipRect); otherwise
 *    it should be the full dimensions of the sample description.
 *  
 *  Parameters:
 *    
 *    mh:
 *      [in] The media handler.
 *    
 *    sampleDescIndex:
 *      [in] Indicates the sample description index of sample
 *      description in the media
 *    
 *    clipFixedRectOut:
 *      [out] Points to a variable to receive the clip rectangle.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 (or QuickTime 7.1) and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
MediaGetApertureModeClipRectForSampleDescriptionIndex(
  MediaHandler   mh,
  long           sampleDescIndex,
  FixedRect *    clipFixedRectOut)                            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGetApertureModeMatrixForSampleDescriptionIndex()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Calculates a matrix appropriate for the current aperture mode and
 *    the given sample description.
 *  
 *  Discussion:
 *    If the track's aperture mode is kQTApertureMode_CleanAperture or
 *    kQTApertureMode_ProductionAperture, the matrix should scale
 *    horizontally to compensate for the pixel aspect ratio. Otherwise
 *    the matrix should be identity. If the track's aperture mode is
 *    kQTApertureMode_CleanAperture, the matrix should translate the
 *    top-left point of the clean aperture to the origin. (See
 *    kICMImageDescriptionPropertyID_CleanApertureMatrix and
 *    kICMImageDescriptionPropertyID_ProductionApertureMatrix.)
 *  
 *  Parameters:
 *    
 *    mh:
 *      [in] The media handler.
 *    
 *    sampleDescIndex:
 *      [in] Indicates the sample description index of sample
 *      description in the media
 *    
 *    matrixOut:
 *      [out] Points to a variable to receive the matrix.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 (or QuickTime 7.1) and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
MediaGetApertureModeMatrixForSampleDescriptionIndex(
  MediaHandler    mh,
  long            sampleDescIndex,
  MatrixRecord *  matrixOut)                                  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  MediaGenerateApertureModeDimensions()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Examines a movie and sets up track aperture mode dimensions.
 *  
 *  Discussion:
 *    If the sample descriptions tracks lack tags describing clean
 *    aperture and pixel aspect ratio information, the media data may
 *    be scanned to see if the correct values can be divined and
 *    attached. Then the aperture mode dimensions should be calculated
 *    and set, as by
 *    MediaSetTrackApertureModeDimensionsUsingSampleDescription.
 *  
 *  Parameters:
 *    
 *    mh:
 *      [in] The media handler.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 (or QuickTime 7.1) and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
MediaGenerateApertureModeDimensions(MediaHandler mh)          AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;






/* selectors for component calls */
enum {
    kCallComponentExecuteWiredActionSelect     = -9,
    kMediaSetChunkManagementFlagsSelect        = 0x0415,
    kMediaGetChunkManagementFlagsSelect        = 0x0416,
    kMediaSetPurgeableChunkMemoryAllowanceSelect = 0x0417,
    kMediaGetPurgeableChunkMemoryAllowanceSelect = 0x0418,
    kMediaEmptyAllPurgeableChunksSelect        = 0x0419,
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
    kMediaSetUserPreferredCodecsSelect         = 0x0568,
    kMediaRefConSetPropertySelect              = 0x0569,
    kMediaRefConGetPropertySelect              = 0x056A,
    kMediaNavigateTargetRefConSelect           = 0x056B,
    kMediaGGetIdleManagerSelect                = 0x056C,
    kMediaGSetIdleManagerSelect                = 0x056D,
    kMediaGGetLatencySelect                    = 0x0571,
    kMediaSetTrackApertureModeDimensionsUsingSampleDescriptionSelect = 0x0579,
    kMediaGetApertureModeClipRectForSampleDescriptionIndexSelect = 0x057A,
    kMediaGetApertureModeMatrixForSampleDescriptionIndexSelect = 0x057B,
    kMediaGenerateApertureModeDimensionsSelect = 0x057C
};
/*
 *  NewPrePrerollCompleteUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern PrePrerollCompleteUPP
NewPrePrerollCompleteUPP(PrePrerollCompleteProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

/*
 *  DisposePrePrerollCompleteUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposePrePrerollCompleteUPP(PrePrerollCompleteUPP userUPP)   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

/*
 *  InvokePrePrerollCompleteUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokePrePrerollCompleteUPP(
  MediaHandler           mh,
  OSErr                  err,
  void *                 refcon,
  PrePrerollCompleteUPP  userUPP)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

#if __MACH__
  #ifdef __cplusplus
    inline PrePrerollCompleteUPP                                NewPrePrerollCompleteUPP(PrePrerollCompleteProcPtr userRoutine) { return userRoutine; }
    inline void                                                 DisposePrePrerollCompleteUPP(PrePrerollCompleteUPP) { }
    inline void                                                 InvokePrePrerollCompleteUPP(MediaHandler mh, OSErr err, void * refcon, PrePrerollCompleteUPP userUPP) { (*userUPP)(mh, err, refcon); }
  #else
    #define NewPrePrerollCompleteUPP(userRoutine)               ((PrePrerollCompleteUPP)userRoutine)
    #define DisposePrePrerollCompleteUPP(userUPP)
    #define InvokePrePrerollCompleteUPP(mh, err, refcon, userUPP) (*userUPP)(mh, err, refcon)
  #endif
#endif


#endif // !__LP64__



#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* __MEDIAHANDLERS__ */

