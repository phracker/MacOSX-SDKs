/*
     File:       QuickTime/QTSMovie.h
 
     Contains:   QuickTime Interfaces.
 
     Version:    QuickTime 7.2.1
 
     Copyright:  © 1990-2006 by Apple Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __QTSMOVIE__
#define __QTSMOVIE__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __MOVIES__
#include <QuickTime/Movies.h>
#endif

#ifndef __QUICKTIMESTREAMING__
#include <QuickTime/QuickTimeStreaming.h>
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

enum {
  kQTSStreamMediaType           = 'strm'
};

struct QTSSampleDescription {
  long                descSize;
  long                dataFormat;
  long                resvd1;                 /* set to 0*/
  short               resvd2;                 /* set to 0*/
  short               dataRefIndex;
  UInt32              version;
  UInt32              resvd3;                 /* set to 0*/
  SInt32              flags;
                                              /* qt atoms follow:*/
                                              /*      long size, long type, some data*/
                                              /*      repeat as necessary*/
};
typedef struct QTSSampleDescription     QTSSampleDescription;
typedef QTSSampleDescription *          QTSSampleDescriptionPtr;
typedef QTSSampleDescriptionPtr *       QTSSampleDescriptionHandle;
enum {
  kQTSSampleDescriptionVersion1 = 1L
};

enum {
  kQTSDefaultMediaTimeScale     = 600L
};

/* sample description flags*/
enum {
  kQTSSampleDescPassSampleDataAsHandleFlag = 0x00000001
};


/*============================================================================
        Stream Media Handler
============================================================================*/
/*-----------------------------------------
    Info Selectors
-----------------------------------------*/
/* all indexes start at 1 */

enum {
  kQTSMediaPresentationInfo     = 'pres', /* QTSMediaPresentationParams* */
  kQTSMediaNotificationInfo     = 'noti', /* QTSMediaNotificationParams* */
  kQTSMediaTotalDataRateInfo    = 'dtrt', /* UInt32*, bits/sec */
  kQTSMediaLostPercentInfo      = 'lspc', /* Fixed* */
  kQTSMediaNumStreamsInfo       = 'nstr', /* UInt32* */
  kQTSMediaIndSampleDescriptionInfo = 'isdc' /* QTSMediaIndSampleDescriptionParams* */
};


struct QTSMediaPresentationParams {
  QTSPresentation     presentationID;
};
typedef struct QTSMediaPresentationParams QTSMediaPresentationParams;
struct QTSMediaNotificationParams {
  QTSNotificationUPP  notificationProc;
  void *              notificationRefCon;
  SInt32              flags;
};
typedef struct QTSMediaNotificationParams QTSMediaNotificationParams;
struct QTSMediaIndSampleDescriptionParams {
  SInt32              index;
  OSType              returnedMediaType;
  SampleDescriptionHandle  returnedSampleDescription;
};
typedef struct QTSMediaIndSampleDescriptionParams QTSMediaIndSampleDescriptionParams;
/*-----------------------------------------
    QTS Media Handler Selectors
-----------------------------------------*/
enum {
  kQTSMediaSetInfoSelect        = 0x0100,
  kQTSMediaGetInfoSelect        = 0x0101,
  kQTSMediaSetIndStreamInfoSelect = 0x0102,
  kQTSMediaGetIndStreamInfoSelect = 0x0103
};

/*-----------------------------------------
    QTS Media Handler functions
-----------------------------------------*/
/*
 *  QTSMediaSetInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
QTSMediaSetInfo(
  MediaHandler   mh,
  OSType         inSelector,
  void *         ioParams)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTSMediaGetInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
QTSMediaGetInfo(
  MediaHandler   mh,
  OSType         inSelector,
  void *         ioParams)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTSMediaSetIndStreamInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
QTSMediaSetIndStreamInfo(
  MediaHandler   mh,
  SInt32         inIndex,
  OSType         inSelector,
  void *         ioParams)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTSMediaGetIndStreamInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
QTSMediaGetIndStreamInfo(
  MediaHandler   mh,
  SInt32         inIndex,
  OSType         inSelector,
  void *         ioParams)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*============================================================================
        Hint Media Handler
============================================================================*/
enum {
  kQTSHintMediaType             = 'hint'
};

enum {
  kQTSHintTrackReference        = 'hint'
};





/* MixedMode ProcInfo constants for component calls */
enum {
    uppQTSMediaSetInfoProcInfo                 = 0x00000FF0,
    uppQTSMediaGetInfoProcInfo                 = 0x00000FF0,
    uppQTSMediaSetIndStreamInfoProcInfo        = 0x00003FF0,
    uppQTSMediaGetIndStreamInfoProcInfo        = 0x00003FF0
};

#endif // !__LP64__


#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* __QTSMOVIE__ */

