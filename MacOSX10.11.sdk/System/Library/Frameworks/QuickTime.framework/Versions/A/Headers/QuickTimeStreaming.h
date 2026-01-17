/*
     File:       QuickTime/QuickTimeStreaming.h
 
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

#ifndef __QUICKTIMESTREAMING__
#define __QUICKTIMESTREAMING__

#ifndef __APPLICATIONSERVICES__
#include <ApplicationServices/ApplicationServices.h>
#endif

#ifndef __MOVIES__
#include <QuickTime/Movies.h>
#endif

#ifndef __QUICKTIMECOMPONENTS__
#include <QuickTime/QuickTimeComponents.h>
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
  kQTSInfiniteDuration          = 0x7FFFFFFF,
  kQTSUnknownDuration           = 0x00000000,
  kQTSNormalForwardRate         = 0x00010000,
  kQTSStoppedRate               = 0x00000000
};

struct QTSPresentationRecord {
  long                data[1];
};
typedef struct QTSPresentationRecord    QTSPresentationRecord;
typedef QTSPresentationRecord *         QTSPresentation;
struct QTSStreamRecord {
  long                data[1];
};
typedef struct QTSStreamRecord          QTSStreamRecord;
typedef QTSStreamRecord *               QTSStream;
struct QTSEditEntry {
  TimeValue64         presentationDuration;
  TimeValue64         streamStartTime;
  Fixed               streamRate;
};
typedef struct QTSEditEntry             QTSEditEntry;
struct QTSEditList {
  SInt32              numEdits;
  QTSEditEntry        edits[1];
};
typedef struct QTSEditList              QTSEditList;
typedef QTSEditList *                   QTSEditListPtr;
typedef QTSEditListPtr *                QTSEditListHandle;
#define kQTSInvalidPresentation     (QTSPresentation)0L
#define kQTSAllPresentations        (QTSPresentation)0L
#define kQTSInvalidStream           (QTSStream)0L
#define kQTSAllStreams              (QTSStream)0L
typedef CALLBACK_API( ComponentResult , QTSNotificationProcPtr )(ComponentResult inErr, OSType inNotificationType, void *inNotificationParams, void *inRefCon);
typedef STACK_UPP_TYPE(QTSNotificationProcPtr)                  QTSNotificationUPP;
/*-----------------------------------------
    Get / Set Info
-----------------------------------------*/
enum {
  kQTSGetURLLink                = 'gull' /* QTSGetURLLinkRecord* */
};

/* get and set */
enum {
  kQTSTargetBufferDurationInfo  = 'bufr', /* Fixed* in seconds; expected, not actual */
  kQTSDurationInfo              = 'dura', /* QTSDurationAtom* */
  kQTSSoundLevelMeteringEnabledInfo = 'mtrn', /* Boolean* */
  kQTSSoundLevelMeterInfo       = 'levm', /* LevelMeterInfoPtr */
  kQTSSourceTrackIDInfo         = 'otid', /* UInt32* */
  kQTSSourceLayerInfo           = 'olyr', /* UInt16* */
  kQTSSourceLanguageInfo        = 'olng', /* UInt16* */
  kQTSSourceTrackFlagsInfo      = 'otfl', /* SInt32* */
  kQTSSourceDimensionsInfo      = 'odim', /* QTSDimensionParams* */
  kQTSSourceVolumesInfo         = 'ovol', /* QTSVolumesParams* */
  kQTSSourceMatrixInfo          = 'omat', /* MatrixRecord* */
  kQTSSourceClipRectInfo        = 'oclp', /* Rect* */
  kQTSSourceGraphicsModeInfo    = 'ogrm', /* QTSGraphicsModeParams* */
  kQTSSourceScaleInfo           = 'oscl', /* Point* */
  kQTSSourceBoundingRectInfo    = 'orct', /* Rect* */
  kQTSSourceUserDataInfo        = 'oudt', /* UserData */
  kQTSSourceInputMapInfo        = 'oimp', /* QTAtomContainer */
  kQTSInfo_DataProc             = 'datp', /* QTSDataProcParams* */
  kQTSInfo_SendDataExtras       = 'dext', /* QTSSendDataExtrasParams* */
  kQTSInfo_HintTrackID          = 'htid', /* long* */
  kQTSInfo_URL                  = 'url ', /* Handle*, cstring in handle */
  kQTSInfo_Authentication       = 'auup', /* QTSAuthenticationParams */
  kQTSInfo_MediaPacketizer      = 'rmpk' /* ComponentInstance */
};

/* get only */
enum {
  kQTSStatisticsInfo            = 'stat', /* QTSStatisticsParams* */
  kQTSMinStatusDimensionsInfo   = 'mstd', /* QTSDimensionParams* */
  kQTSNormalStatusDimensionsInfo = 'nstd', /* QTSDimensionParams* */
  kQTSTotalDataRateInfo         = 'drtt', /* UInt32*, add to what's there */
  kQTSTotalDataRateInInfo       = 'drti', /* UInt32*, add to what's there */
  kQTSTotalDataRateOutInfo      = 'drto', /* UInt32*, add to what's there */
  kQTSLostPercentInfo           = 'lpct', /* QTSLostPercentParams*, add to what's there */
  kQTSNumViewersInfo            = 'nviw', /* UInt32* */
  kQTSMediaTypeInfo             = 'mtyp', /* OSType* */
  kQTSNameInfo                  = 'name', /* QTSNameParams* */
  kQTSCanHandleSendDataType     = 'chsd', /* QTSCanHandleSendDataTypeParams* */
  kQTSAnnotationsInfo           = 'meta', /* QTAtomContainer */
  kQTSRemainingBufferTimeInfo   = 'btms', /* UInt32* remaining buffer time before playback, in microseconds */
  kQTSInfo_SettingsText         = 'sttx', /* QTSSettingsTextParams* */
  kQTSInfo_AverageFrameRate     = 'fps ' /* UnsignedFixed* */
};


struct QTSAuthenticationParams {
  SInt32              flags;
  const char *        userID;                 /* caller disposes of pointer*/
  const char *        password;               /* caller disposes of pointer*/
};
typedef struct QTSAuthenticationParams  QTSAuthenticationParams;
enum {
  kQTSTargetBufferDurationTimeScale = 1000
};

struct QTSPanelFilterParams {
  SInt32              version;
  QTSStream           inStream;
  OSType              inPanelType;
  OSType              inPanelSubType;
  QTAtomSpec          details;
};
typedef struct QTSPanelFilterParams     QTSPanelFilterParams;
/* return true to keep this panel*/
typedef CALLBACK_API( Boolean , QTSPanelFilterProcPtr )(QTSPanelFilterParams *inParams, void *inRefCon);
typedef STACK_UPP_TYPE(QTSPanelFilterProcPtr)                   QTSPanelFilterUPP;
enum {
  kQTSSettingsTextSummary       = 'set1',
  kQTSSettingsTextDetails       = 'setd'
};

struct QTSSettingsTextParams {
  SInt32              flags;                  /* None yet defined*/
  OSType              inSettingsSelector;     /* which kind of setting you want from enum above*/
  Handle              outSettingsAsText;      /* QTS allocates; Caller disposes*/
  QTSPanelFilterUPP   inPanelFilterProc;      /* To get a subset filter with this   */
  void *              inPanelFilterProcRefCon;
};
typedef struct QTSSettingsTextParams    QTSSettingsTextParams;
struct QTSCanHandleSendDataTypeParams {
  SInt32              modifierTypeOrInputID;
  Boolean             isModifierType;
  Boolean             returnedCanHandleSendDataType; /* callee sets to true if it can handle it*/
};
typedef struct QTSCanHandleSendDataTypeParams QTSCanHandleSendDataTypeParams;
struct QTSNameParams {
  SInt32              maxNameLength;
  SInt32              requestedLanguage;
  SInt32              returnedActualLanguage;
  unsigned char *     returnedName;           /* pascal string; caller supplies*/
};
typedef struct QTSNameParams            QTSNameParams;
struct QTSLostPercentParams {
  UInt32              receivedPkts;
  UInt32              lostPkts;
  Fixed               percent;
};
typedef struct QTSLostPercentParams     QTSLostPercentParams;
struct QTSDimensionParams {
  Fixed               width;
  Fixed               height;
};
typedef struct QTSDimensionParams       QTSDimensionParams;
struct QTSVolumesParams {
  SInt16              leftVolume;
  SInt16              rightVolume;
};
typedef struct QTSVolumesParams         QTSVolumesParams;
struct QTSGraphicsModeParams {
  SInt16              graphicsMode;
  RGBColor            opColor;
};
typedef struct QTSGraphicsModeParams    QTSGraphicsModeParams;
struct QTSGetURLLinkRecord {
  Point               displayWhere;
  Handle              returnedURLLink;
};
typedef struct QTSGetURLLinkRecord      QTSGetURLLinkRecord;
enum {
  kQTSDataProcParamsVersion1    = 1
};

enum {
  kQTSDataProcType_MediaSample  = 'mdia',
  kQTSDataProcType_HintSample   = 'hint'
};

struct QTSDataProcParams {
  SInt32              version;
  SInt32              flags;
  QTSStream           stream;
  OSType              procType;
  QTSNotificationUPP  proc;
  void *              procRefCon;
};
typedef struct QTSDataProcParams        QTSDataProcParams;
enum {
  kQTSDataProcSelector_SampleData = 'samp',
  kQTSDataProcSelector_UserData = 'user'
};

enum {
  kQTSSampleDataCallbackParamsVersion1 = 1
};

struct QTSSampleDataCallbackParams {
  SInt32              version;
  SInt32              flags;
  QTSStream           stream;
  OSType              procType;
  OSType              mediaType;
  TimeScale           mediaTimeScale;
  SampleDescriptionHandle  sampleDesc;
  UInt32              sampleDescSeed;
  TimeValue64         sampleTime;
  TimeValue64         duration;               /* could be 0 */
  SInt32              sampleFlags;
  UInt32              dataLength;
  const void *        data;
};
typedef struct QTSSampleDataCallbackParams QTSSampleDataCallbackParams;
enum {
  kQTSUserDataCallbackParamsVersion1 = 1
};

struct QTSUserDataCallbackParams {
  SInt32              version;
  SInt32              flags;
  QTSStream           stream;
  OSType              procType;
  OSType              userDataType;
  Handle              userDataHandle;         /* caller must make copy if it wants to keep the data around*/
};
typedef struct QTSUserDataCallbackParams QTSUserDataCallbackParams;
enum {
  kQTSSendDataExtrasParamsVersion1 = 1
};

struct QTSSendDataExtrasParams {
  SInt32              version;
  SInt32              flags;
  OSType              procType;
};
typedef struct QTSSendDataExtrasParams  QTSSendDataExtrasParams;
typedef CALLBACK_API( Boolean , QTSModalFilterProcPtr )(DialogPtr inDialog, const EventRecord *inEvent, SInt16 *ioItemHit, void *inRefCon);
typedef STACK_UPP_TYPE(QTSModalFilterProcPtr)                   QTSModalFilterUPP;
/*-----------------------------------------
    Characteristics
-----------------------------------------*/
/* characteristics in Movies.h work here too */
enum {
  kQTSSupportsPerStreamControlCharacteristic = 'psct'
};

struct QTSVideoParams {
  Fixed               width;
  Fixed               height;
  MatrixRecord        matrix;
  CGrafPtr            gWorld;
  GDHandle            gdHandle;
  RgnHandle           clip;
  short               graphicsMode;
  RGBColor            opColor;
};
typedef struct QTSVideoParams           QTSVideoParams;
struct QTSAudioParams {
  SInt16              leftVolume;
  SInt16              rightVolume;
  SInt16              bassLevel;
  SInt16              trebleLevel;
  short               frequencyBandsCount;
  void *              frequencyBands;
  Boolean             levelMeteringEnabled;
};
typedef struct QTSAudioParams           QTSAudioParams;
struct QTSMediaParams {
  QTSVideoParams      v;
  QTSAudioParams      a;
};
typedef struct QTSMediaParams           QTSMediaParams;
enum {
  kQTSMustDraw                  = 1 << 3,
  kQTSAtEnd                     = 1 << 4,
  kQTSPreflightDraw             = 1 << 5,
  kQTSSyncDrawing               = 1 << 6
};

/* media task result flags */
enum {
  kQTSDidDraw                   = 1 << 0,
  kQTSNeedsToDraw               = 1 << 2,
  kQTSDrawAgain                 = 1 << 3,
  kQTSPartialDraw               = 1 << 4
};

/*============================================================================
        Notifications
============================================================================*/
/* ------ notification types ------ */
enum {
  kQTSNullNotification          = 'null', /* NULL */
  kQTSErrorNotification         = 'err ', /* QTSErrorParams*, optional */
  kQTSNewPresDetectedNotification = 'newp', /* QTSNewPresDetectedParams* */
  kQTSPresBeginChangingNotification = 'prcb', /* NULL */
  kQTSPresDoneChangingNotification = 'prcd', /* NULL */
  kQTSPresentationChangedNotification = 'prch', /* NULL */
  kQTSNewStreamNotification     = 'stnw', /* QTSNewStreamParams* */
  kQTSStreamBeginChangingNotification = 'stcb', /* QTSStream */
  kQTSStreamDoneChangingNotification = 'stcd', /* QTSStream */
  kQTSStreamChangedNotification = 'stch', /* QTSStreamChangedParams* */
  kQTSStreamGoneNotification    = 'stgn', /* QTSStreamGoneParams* */
  kQTSPreviewAckNotification    = 'pvak', /* QTSStream */
  kQTSPrerollAckNotification    = 'pack', /* QTSStream */
  kQTSStartAckNotification      = 'sack', /* QTSStream */
  kQTSStopAckNotification       = 'xack', /* QTSStream */
  kQTSStatusNotification        = 'stat', /* QTSStatusParams* */
  kQTSURLNotification           = 'url ', /* QTSURLParams* */
  kQTSDurationNotification      = 'dura', /* QTSDurationAtom* */
  kQTSNewPresentationNotification = 'nprs', /* QTSPresentation */
  kQTSPresentationGoneNotification = 'xprs', /* QTSPresentation */
  kQTSPresentationDoneNotification = 'pdon', /* NULL */
  kQTSBandwidthAlertNotification = 'bwal', /* QTSBandwidthAlertParams* */
  kQTSAnnotationsChangedNotification = 'meta' /* NULL */
};


/* flags for QTSErrorParams */
enum {
  kQTSFatalErrorFlag            = 0x00000001
};

struct QTSErrorParams {
  const char *        errorString;
  SInt32              flags;
};
typedef struct QTSErrorParams           QTSErrorParams;
struct QTSNewPresDetectedParams {
  void *              data;
};
typedef struct QTSNewPresDetectedParams QTSNewPresDetectedParams;
struct QTSNewStreamParams {
  QTSStream           stream;
};
typedef struct QTSNewStreamParams       QTSNewStreamParams;
struct QTSStreamChangedParams {
  QTSStream           stream;
  ComponentInstance   mediaComponent;         /* could be NULL */
};
typedef struct QTSStreamChangedParams   QTSStreamChangedParams;
struct QTSStreamGoneParams {
  QTSStream           stream;
};
typedef struct QTSStreamGoneParams      QTSStreamGoneParams;
struct QTSStatusParams {
  UInt32              status;
  const char *        statusString;
  UInt32              detailedStatus;
  const char *        detailedStatusString;
};
typedef struct QTSStatusParams          QTSStatusParams;
struct QTSInfoParams {
  OSType              infoType;
  void *              infoParams;
};
typedef struct QTSInfoParams            QTSInfoParams;
struct QTSURLParams {
  UInt32              urlLength;
  const char *        url;
};
typedef struct QTSURLParams             QTSURLParams;
enum {
  kQTSBandwidthAlertNeedToStop  = 1 << 0,
  kQTSBandwidthAlertRestartAt   = 1 << 1
};

struct QTSBandwidthAlertParams {
  SInt32              flags;
  TimeValue           restartAt;              /* new field in QT 4.1*/
  void *              reserved;
};
typedef struct QTSBandwidthAlertParams  QTSBandwidthAlertParams;
/*============================================================================
        Presentation
============================================================================*/
/*-----------------------------------------
     Flags
-----------------------------------------*/
/* flags for NewPresentationFromData */
enum {
  kQTSAutoModeFlag              = 0x00000001,
  kQTSDontShowStatusFlag        = 0x00000008,
  kQTSSendMediaFlag             = 0x00010000,
  kQTSReceiveMediaFlag          = 0x00020000
};

struct QTSNewPresentationParams {
  OSType              dataType;
  const void *        data;
  UInt32              dataLength;
  QTSEditListHandle   editList;
  SInt32              flags;
  TimeScale           timeScale;              /* set to 0 for default timescale */
  QTSMediaParams *    mediaParams;
  QTSNotificationUPP  notificationProc;
  void *              notificationRefCon;
};
typedef struct QTSNewPresentationParams QTSNewPresentationParams;
struct QTSPresParams {
  UInt32              version;
  QTSEditListHandle   editList;
  SInt32              flags;
  TimeScale           timeScale;              /* set to 0 for default timescale */
  QTSMediaParams *    mediaParams;
  QTSNotificationUPP  notificationProc;
  void *              notificationRefCon;
};
typedef struct QTSPresParams            QTSPresParams;
enum {
  kQTSPresParamsVersion1        = 1
};

struct QTSPresIdleParams {
  QTSStream           stream;
  TimeValue64         movieTimeToDisplay;
  SInt32              flagsIn;
  SInt32              flagsOut;
};
typedef struct QTSPresIdleParams        QTSPresIdleParams;
enum {
  kQTSExportFlag_ShowDialog     = 0x00000001
};

enum {
  kQTSExportParamsVersion1      = 1
};

struct QTSExportParams {
  SInt32              version;
  OSType              exportType;
  void *              exportExtraData;
  OSType              destinationContainerType;
  void *              destinationContainerData;
  void *              destinationContainerExtras;
  SInt32              flagsIn;
  SInt32              flagsOut;
  QTSModalFilterUPP   filterProc;
  void *              filterProcRefCon;
  Component           exportComponent;        /* NULL unless you want to override */
};
typedef struct QTSExportParams          QTSExportParams;
/*-----------------------------------------
    Toolbox Init/Close
-----------------------------------------*/
/* all "apps" must call this */
/*
 *  InitializeQTS()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
InitializeQTS(void)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  TerminateQTS()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
TerminateQTS(void)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*-----------------------------------------
    Presentation Functions
-----------------------------------------*/
/*
 *  QTSNewPresentation()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSNewPresentation(
  const QTSNewPresentationParams *  inParams,
  QTSPresentation *                 outPresentation)          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSNewPresentationFromData()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 *    Windows:          in QTSClient.lib 5.0 and later
 */
extern OSErr 
QTSNewPresentationFromData(
  OSType                 inDataType,
  const void *           inData,
  const SInt64 *         inDataLength,
  const QTSPresParams *  inPresParams,
  QTSPresentation *      outPresentation)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSNewPresentationFromFile()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 *    Windows:          in QTSClient.lib 5.0 and later
 */
extern OSErr 
QTSNewPresentationFromFile(
  const FSSpec *         inFileSpec,
  const QTSPresParams *  inPresParams,
  QTSPresentation *      outPresentation)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSNewPresentationFromDataRef()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 *    Windows:          in QTSClient.lib 5.0 and later
 */
extern OSErr 
QTSNewPresentationFromDataRef(
  Handle                 inDataRef,
  OSType                 inDataRefType,
  const QTSPresParams *  inPresParams,
  QTSPresentation *      outPresentation)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSDisposePresentation()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSDisposePresentation(
  QTSPresentation   inPresentation,
  SInt32            inFlags)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresExport()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 *    Windows:          in QTSClient.lib 5.0 and later
 */
extern OSErr 
QTSPresExport(
  QTSPresentation    inPresentation,
  QTSStream          inStream,
  QTSExportParams *  inExportParams)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresIdle()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern void 
QTSPresIdle(
  QTSPresentation      inPresentation,
  QTSPresIdleParams *  ioParams)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresInvalidateRegion()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresInvalidateRegion(
  QTSPresentation   inPresentation,
  RgnHandle         inRegion)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*-----------------------------------------
    Presentation Configuration
-----------------------------------------*/
/*
 *  QTSPresSetFlags()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresSetFlags(
  QTSPresentation   inPresentation,
  SInt32            inFlags,
  SInt32            inFlagsMask)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetFlags()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresGetFlags(
  QTSPresentation   inPresentation,
  SInt32 *          outFlags)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetTimeBase()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresGetTimeBase(
  QTSPresentation   inPresentation,
  TimeBase *        outTimeBase)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetTimeScale()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresGetTimeScale(
  QTSPresentation   inPresentation,
  TimeScale *       outTimeScale)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresSetInfo()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresSetInfo(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  OSType            inSelector,
  void *            ioParam)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetInfo()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresGetInfo(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  OSType            inSelector,
  void *            ioParam)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresHasCharacteristic()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresHasCharacteristic(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  OSType            inCharacteristic,
  Boolean *         outHasIt)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresSetNotificationProc()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresSetNotificationProc(
  QTSPresentation      inPresentation,
  QTSNotificationUPP   inNotificationProc,
  void *               inRefCon)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetNotificationProc()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresGetNotificationProc(
  QTSPresentation       inPresentation,
  QTSNotificationUPP *  outNotificationProc,
  void **               outRefCon)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*-----------------------------------------
    Presentation Control
-----------------------------------------*/
/*
 *  QTSPresPreview()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 */
extern OSErr 
QTSPresPreview(
  QTSPresentation      inPresentation,
  QTSStream            inStream,
  const TimeValue64 *  inTimeValue,
  Fixed                inRate,
  SInt32               inFlags)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresPreroll()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresPreroll(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  UInt32            inTimeValue,
  Fixed             inRate,
  SInt32            inFlags)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresPreroll64()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.1 and later
 *    Windows:          in QTSClient.lib 4.1 and later
 */
extern OSErr 
QTSPresPreroll64(
  QTSPresentation      inPresentation,
  QTSStream            inStream,
  const TimeValue64 *  inPrerollTime,
  Fixed                inRate,
  SInt32               inFlags)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresStart()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresStart(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  SInt32            inFlags)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresSkipTo()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresSkipTo(
  QTSPresentation   inPresentation,
  UInt32            inTimeValue)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresSkipTo64()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.1 and later
 *    Windows:          in QTSClient.lib 4.1 and later
 */
extern OSErr 
QTSPresSkipTo64(
  QTSPresentation      inPresentation,
  const TimeValue64 *  inTimeValue)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresStop()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresStop(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  SInt32            inFlags)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*============================================================================
        Streams
============================================================================*/
/*-----------------------------------------
    Stream Functions
-----------------------------------------*/
/*
 *  QTSPresNewStream()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresNewStream(
  QTSPresentation   inPresentation,
  OSType            inDataType,
  const void *      inData,
  UInt32            inDataLength,
  SInt32            inFlags,
  QTSStream *       outStream)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSDisposeStream()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSDisposeStream(
  QTSStream   inStream,
  SInt32      inFlags)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetNumStreams()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern UInt32 
QTSPresGetNumStreams(QTSPresentation inPresentation)          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetIndStream()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern QTSStream 
QTSPresGetIndStream(
  QTSPresentation   inPresentation,
  UInt32            inIndex)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSGetStreamPresentation()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern QTSPresentation 
QTSGetStreamPresentation(QTSStream inStream)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresSetPreferredRate()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresSetPreferredRate(
  QTSPresentation   inPresentation,
  Fixed             inRate,
  SInt32            inFlags)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetPreferredRate()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresGetPreferredRate(
  QTSPresentation   inPresentation,
  Fixed *           outRate)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresSetEnable()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresSetEnable(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  Boolean           inEnableMode)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetEnable()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresGetEnable(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  Boolean *         outEnableMode)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresSetPresenting()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresSetPresenting(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  Boolean           inPresentingMode)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetPresenting()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresGetPresenting(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  Boolean *         outPresentingMode)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresSetActiveSegment()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.1 and later
 *    Windows:          in QTSClient.lib 4.1 and later
 */
extern OSErr 
QTSPresSetActiveSegment(
  QTSPresentation      inPresentation,
  QTSStream            inStream,
  const TimeValue64 *  inStartTime,
  const TimeValue64 *  inDuration)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetActiveSegment()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.1 and later
 *    Windows:          in QTSClient.lib 4.1 and later
 */
extern OSErr 
QTSPresGetActiveSegment(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  TimeValue64 *     outStartTime,
  TimeValue64 *     outDuration)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresSetPlayHints()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresSetPlayHints(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  SInt32            inFlags,
  SInt32            inFlagsMask)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetPlayHints()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresGetPlayHints(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  SInt32 *          outFlags)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*-----------------------------------------
    Stream Spatial Functions
-----------------------------------------*/
/*
 *  QTSPresSetGWorld()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresSetGWorld(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  CGrafPtr          inGWorld,
  GDHandle          inGDHandle)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetGWorld()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresGetGWorld(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  CGrafPtr *        outGWorld,
  GDHandle *        outGDHandle)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresSetClip()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresSetClip(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  RgnHandle         inClip)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetClip()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresGetClip(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  RgnHandle *       outClip)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresSetMatrix()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresSetMatrix(
  QTSPresentation       inPresentation,
  QTSStream             inStream,
  const MatrixRecord *  inMatrix)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetMatrix()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresGetMatrix(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  MatrixRecord *    outMatrix)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresSetDimensions()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresSetDimensions(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  Fixed             inWidth,
  Fixed             inHeight)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetDimensions()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresGetDimensions(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  Fixed *           outWidth,
  Fixed *           outHeight)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresSetGraphicsMode()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresSetGraphicsMode(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  short             inMode,
  const RGBColor *  inOpColor)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetGraphicsMode()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresGetGraphicsMode(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  short *           outMode,
  RGBColor *        outOpColor)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetPicture()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresGetPicture(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  PicHandle *       outPicture)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresSetVisualContext()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresSetVisualContext(
  QTSPresentation      inPresentation,
  QTSStream            inStream,
  QTVisualContextRef   inVisualContext)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetVisualContext()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresGetVisualContext(
  QTSPresentation       inPresentation,
  QTSStream             inStream,
  QTVisualContextRef *  outVisualContext)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*-----------------------------------------
    Stream Sound Functions
-----------------------------------------*/
/*
 *  QTSPresSetVolumes()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresSetVolumes(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  short             inLeftVolume,
  short             inRightVolume)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetVolumes()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSPresGetVolumes(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  short *           outLeftVolume,
  short *           outRightVolume)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*-----------------------------------------
    Sourcing
-----------------------------------------*/
/*
 *  QTSPresGetSettingsAsText()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0.1 and later
 */
extern OSErr 
QTSPresGetSettingsAsText(
  QTSPresentation     inPresentation,
  QTSStream           inStream,
  SInt32              inFlags,
  OSType              inSettingsType,
  Handle *            outText,
  QTSPanelFilterUPP   inPanelFilterProc,
  void *              inPanelFilterProcRefCon)                AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresSettingsDialog()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 */
extern OSErr 
QTSPresSettingsDialog(
  QTSPresentation     inPresentation,
  QTSStream           inStream,
  SInt32              inFlags,
  QTSModalFilterUPP   inFilterProc,
  void *              inFilterProcRefCon)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresSettingsDialogWithFilters()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0.1 and later
 */
extern OSErr 
QTSPresSettingsDialogWithFilters(
  QTSPresentation     inPresentation,
  QTSStream           inStream,
  SInt32              inFlags,
  QTSModalFilterUPP   inFilterProc,
  void *              inFilterProcRefCon,
  QTSPanelFilterUPP   inPanelFilterProc,
  void *              inPanelFilterProcRefCon)                AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresSetSettings()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 */
extern OSErr 
QTSPresSetSettings(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  QTAtomSpecPtr     inSettings,
  SInt32            inFlags)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetSettings()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 */
extern OSErr 
QTSPresGetSettings(
  QTSPresentation    inPresentation,
  QTSStream          inStream,
  QTAtomContainer *  outSettings,
  SInt32             inFlags)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresAddSourcer()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 */
extern OSErr 
QTSPresAddSourcer(
  QTSPresentation     inPresentation,
  QTSStream           inStream,
  ComponentInstance   inSourcer,
  SInt32              inFlags)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresRemoveSourcer()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 */
extern OSErr 
QTSPresRemoveSourcer(
  QTSPresentation     inPresentation,
  QTSStream           inStream,
  ComponentInstance   inSourcer,
  SInt32              inFlags)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetNumSourcers()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 */
extern UInt32 
QTSPresGetNumSourcers(
  QTSPresentation   inPresentation,
  QTSStream         inStream)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPresGetIndSourcer()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 */
extern OSErr 
QTSPresGetIndSourcer(
  QTSPresentation      inPresentation,
  QTSStream            inStream,
  UInt32               inIndex,
  ComponentInstance *  outSourcer)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*============================================================================
        Misc
============================================================================*/
/* flags for Get/SetNetworkAppName */
enum {
  kQTSNetworkAppNameIsFullNameFlag = 0x00000001
};

/*
 *  QTSSetNetworkAppName()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.1 and later
 *    Windows:          in QTSClient.lib 4.1 and later
 */
extern OSErr 
QTSSetNetworkAppName(
  const char *  inAppName,
  SInt32        inFlags)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSGetNetworkAppName()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.1 and later
 *    Windows:          in QTSClient.lib 4.1 and later
 */
extern OSErr 
QTSGetNetworkAppName(
  SInt32   inFlags,
  char **  outCStringPtr)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*-----------------------------------------
    Statistics Utilities
-----------------------------------------*/
struct QTSStatHelperRecord {
  long                data[1];
};
typedef struct QTSStatHelperRecord      QTSStatHelperRecord;
typedef QTSStatHelperRecord *           QTSStatHelper;
enum {
  kQTSInvalidStatHelper         = 0
};

/* flags for QTSStatHelperNextParams */
enum {
  kQTSStatHelperReturnPascalStringsFlag = 0x00000001
};

struct QTSStatHelperNextParams {
  SInt32              flags;
  OSType              returnedStatisticsType;
  QTSStream           returnedStream;
  UInt32              maxStatNameLength;
  char *              returnedStatName;       /* NULL if you don't want it*/
  UInt32              maxStatStringLength;
  char *              returnedStatString;     /* NULL if you don't want it*/
  UInt32              maxStatUnitLength;
  char *              returnedStatUnit;       /* NULL if you don't want it*/
};
typedef struct QTSStatHelperNextParams  QTSStatHelperNextParams;
struct QTSStatisticsParams {
  OSType              statisticsType;
  QTAtomContainer     container;
  QTAtom              parentAtom;
  SInt32              flags;
};
typedef struct QTSStatisticsParams      QTSStatisticsParams;
/* general statistics types */
enum {
  kQTSAllStatisticsType         = 'all ',
  kQTSShortStatisticsType       = 'shrt',
  kQTSSummaryStatisticsType     = 'summ'
};

/* statistics flags */
enum {
  kQTSGetNameStatisticsFlag     = 0x00000001,
  kQTSDontGetDataStatisticsFlag = 0x00000002,
  kQTSUpdateAtomsStatisticsFlag = 0x00000004,
  kQTSGetUnitsStatisticsFlag    = 0x00000008,
  kQTSUpdateAllIfNecessaryStatisticsFlag = 0x00010000
};

/* statistics atom types */
enum {
  kQTSStatisticsStreamAtomType  = 'strm',
  kQTSStatisticsNameAtomType    = 'name', /* chars only, no length or terminator */
  kQTSStatisticsDataFormatAtomType = 'frmt', /* OSType */
  kQTSStatisticsDataAtomType    = 'data',
  kQTSStatisticsUnitsAtomType   = 'unit', /* OSType */
  kQTSStatisticsUnitsNameAtomType = 'unin' /* chars only, no length or terminator */
};

/* statistics data formats */
enum {
  kQTSStatisticsSInt32DataFormat = 'si32',
  kQTSStatisticsUInt32DataFormat = 'ui32',
  kQTSStatisticsSInt16DataFormat = 'si16',
  kQTSStatisticsUInt16DataFormat = 'ui16',
  kQTSStatisticsFixedDataFormat = 'fixd',
  kQTSStatisticsUnsignedFixedDataFormat = 'ufix',
  kQTSStatisticsStringDataFormat = 'strg',
  kQTSStatisticsOSTypeDataFormat = 'ostp',
  kQTSStatisticsRectDataFormat  = 'rect',
  kQTSStatisticsPointDataFormat = 'pont'
};

/* statistics units types */
enum {
  kQTSStatisticsNoUnitsType     = 0,
  kQTSStatisticsPercentUnitsType = 'pcnt',
  kQTSStatisticsBitsPerSecUnitsType = 'bps ',
  kQTSStatisticsFramesPerSecUnitsType = 'fps '
};

/* specific statistics types */
enum {
  kQTSTotalDataRateStat         = 'drtt',
  kQTSTotalDataRateInStat       = 'drti',
  kQTSTotalDataRateOutStat      = 'drto',
  kQTSNetworkIDStringStat       = 'nids'
};

/*
 *  QTSNewStatHelper()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSNewStatHelper(
  QTSPresentation   inPresentation,
  QTSStream         inStream,
  OSType            inStatType,
  SInt32            inFlags,
  QTSStatHelper *   outStatHelper)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSDisposeStatHelper()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSDisposeStatHelper(QTSStatHelper inStatHelper)              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSStatHelperGetStats()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSStatHelperGetStats(QTSStatHelper inStatHelper)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSStatHelperResetIter()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSStatHelperResetIter(QTSStatHelper inStatHelper)            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSStatHelperNext()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern Boolean 
QTSStatHelperNext(
  QTSStatHelper              inStatHelper,
  QTSStatHelperNextParams *  ioParams)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSStatHelperGetNumStats()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern UInt32 
QTSStatHelperGetNumStats(QTSStatHelper inStatHelper)          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/* used by components to put statistics into the atom container */
/*
 *  QTSGetOrMakeStatAtomForStream()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSGetOrMakeStatAtomForStream(
  QTAtomContainer   inContainer,
  QTSStream         inStream,
  QTAtom *          outParentAtom)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSInsertStatistic()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSInsertStatistic(
  QTAtomContainer   inContainer,
  QTAtom            inParentAtom,
  OSType            inStatType,
  void *            inStatData,
  UInt32            inStatDataLength,
  OSType            inStatDataFormat,
  SInt32            inFlags)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSInsertStatisticName()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSInsertStatisticName(
  QTAtomContainer   inContainer,
  QTAtom            inParentAtom,
  OSType            inStatType,
  const char *      inStatName,
  UInt32            inStatNameLength)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSInsertStatisticUnits()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSInsertStatisticUnits(
  QTAtomContainer   inContainer,
  QTAtom            inParentAtom,
  OSType            inStatType,
  OSType            inUnitsType,
  const char *      inUnitsName,
  UInt32            inUnitsNameLength)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*============================================================================
        Data Formats
============================================================================*/
/*-----------------------------------------
    Data Types
-----------------------------------------*/
/* universal data types */
enum {
  kQTSNullDataType              = 'NULL',
  kQTSUnknownDataType           = 'huh?',
  kQTSAtomContainerDataType     = 'qtac', /* QTAtomContainer */
  kQTSAtomDataType              = 'qtat', /* QTSAtomContainerDataStruct* */
  kQTSAliasDataType             = 'alis',
  kQTSFileDataType              = 'fspc', /* FSSpec* */
  kQTSFileSpecDataType          = 'fspc', /* FSSpec* */
  kQTSHandleDataType            = 'hndl', /* Handle* */
  kQTSDataRefDataType           = 'dref' /* DataReferencePtr */
};

/* these data types are specific to presentations */
enum {
  kQTSRTSPDataType              = 'rtsp',
  kQTSSDPDataType               = 'sdp '
};

/*-----------------------------------------
    Atom IDs
-----------------------------------------*/
enum {
  kQTSAtomType_Presentation     = 'pres',
  kQTSAtomType_PresentationHeader = 'phdr', /* QTSPresentationHeaderAtom */
  kQTSAtomType_MediaStream      = 'mstr',
  kQTSAtomType_MediaStreamHeader = 'mshd', /* QTSMediaStreamHeaderAtom */
  kQTSAtomType_MediaDescriptionText = 'mdes', /* chars, no length */
  kQTSAtomType_ClipRect         = 'clip', /* QTSClipRectAtom */
  kQTSAtomType_Duration         = 'dura', /* QTSDurationAtom */
  kQTSAtomType_BufferTime       = 'bufr' /* QTSBufferTimeAtom */
};

struct QTSAtomContainerDataStruct {
  QTAtomContainer     container;
  QTAtom              parentAtom;
};
typedef struct QTSAtomContainerDataStruct QTSAtomContainerDataStruct;
/* flags for QTSPresentationHeaderAtom */
enum {
  kQTSPresHeaderTypeIsData      = 0x00000100,
  kQTSPresHeaderDataIsHandle    = 0x00000200
};

struct QTSPresentationHeaderAtom {
  SInt32              versionAndFlags;
  OSType              conductorOrDataType;
  OSType              dataAtomType;           /* where the data really is*/
};
typedef struct QTSPresentationHeaderAtom QTSPresentationHeaderAtom;
struct QTSMediaStreamHeaderAtom {
  SInt32              versionAndFlags;
  OSType              mediaTransportType;
  OSType              mediaTransportDataAID;  /* where the data really is*/
};
typedef struct QTSMediaStreamHeaderAtom QTSMediaStreamHeaderAtom;
struct QTSBufferTimeAtom {
  SInt32              versionAndFlags;
  Fixed               bufferTime;
};
typedef struct QTSBufferTimeAtom        QTSBufferTimeAtom;
struct QTSDurationAtom {
  SInt32              versionAndFlags;
  TimeScale           timeScale;
  TimeValue64         duration;
};
typedef struct QTSDurationAtom          QTSDurationAtom;
struct QTSClipRectAtom {
  SInt32              versionAndFlags;
  Rect                clipRect;
};
typedef struct QTSClipRectAtom          QTSClipRectAtom;
enum {
  kQTSEmptyEditStreamStartTime  = -1
};


typedef UInt32                          QTSStatus;
enum {
  kQTSNullStatus                = 0,
  kQTSUninitializedStatus       = 1,
  kQTSConnectingStatus          = 2,
  kQTSOpeningConnectionDetailedStatus = 3,
  kQTSMadeConnectionDetailedStatus = 4,
  kQTSNegotiatingStatus         = 5,
  kQTSGettingDescriptionDetailedStatus = 6,
  kQTSGotDescriptionDetailedStatus = 7,
  kQTSSentSetupCmdDetailedStatus = 8,
  kQTSReceivedSetupResponseDetailedStatus = 9,
  kQTSSentPlayCmdDetailedStatus = 10,
  kQTSReceivedPlayResponseDetailedStatus = 11,
  kQTSBufferingStatus           = 12,
  kQTSPlayingStatus             = 13,
  kQTSPausedStatus              = 14,
  kQTSAutoConfiguringStatus     = 15,
  kQTSDownloadingStatus         = 16,
  kQTSBufferingWithTimeStatus   = 17,
  kQTSWaitingDisconnectStatus   = 100
};

/*-----------------------------------------
    QuickTime Preferences Types
-----------------------------------------*/
enum {
  kQTSConnectionPrefsType       = 'stcm', /* root atom that all other atoms are contained in*/
                                        /*    kQTSNotUsedForProxyPrefsType = 'nopr',     //        comma-delimited list of URLs that are never used for proxies*/
  kQTSConnectionMethodPrefsType = 'mthd', /*      connection method (OSType that matches one of the following three)*/
  kQTSDirectConnectPrefsType    = 'drct', /*       used if direct connect (QTSDirectConnectPrefsRecord)*/
                                        /*    kQTSRTSPProxyPrefsType =     'rtsp',   //   used if RTSP Proxy (QTSProxyPrefsRecord)*/
  kQTSSOCKSPrefsType            = 'sock' /*       used if SOCKS Proxy (QTSProxyPrefsRecord)*/
};

enum {
  kQTSDirectConnectHTTPProtocol = 'http',
  kQTSDirectConnectRTSPProtocol = 'rtsp'
};

struct QTSDirectConnectPrefsRecord {
  UInt32              tcpPortID;
  OSType              protocol;
};
typedef struct QTSDirectConnectPrefsRecord QTSDirectConnectPrefsRecord;
struct QTSProxyPrefsRecord {
  Str255              serverNameStr;
  UInt32              portID;
};
typedef struct QTSProxyPrefsRecord      QTSProxyPrefsRecord;
#define kQTSTransAndProxyPrefsVersNum       2       /* prefs atom format version */
enum {
  kConnectionActive             = (1L << 0),
  kConnectionUseSystemPref      = (1L << 1)
};

struct QTSTransportPref {
  OSType              protocol;               /* udp, http, tcp, etc*/
  SInt32              portID;                 /* port to use for this connection type*/
  UInt32              flags;                  /* connection flags*/
  UInt32              seed;                   /* seed value last time this setting was read from system prefs*/
};
typedef struct QTSTransportPref         QTSTransportPref;
enum {
  kProxyActive                  = (1L << 0),
  kProxyUseSystemPref           = (1L << 1)
};

struct QTSProxyPref {
  UInt32              flags;                  /* proxy flags*/
  SInt32              portID;                 /* port to use for this connection type*/
  UInt32              seed;                   /* seed value last time this setting was read from system prefs*/
  Str255              serverNameStr;          /* proxy server url*/
};
typedef struct QTSProxyPref             QTSProxyPref;
enum {
  kNoProxyUseSystemPref         = (1L << 0)
};

struct QTSNoProxyPref {
  UInt32              flags;                  /* no-proxy flags*/
  UInt32              seed;                   /* seed value last time this setting was read from system prefs*/
  char                urlList[1];             /* NULL terminated, comma delimited list of urls*/
};
typedef struct QTSNoProxyPref           QTSNoProxyPref;
enum {
  kQTSInstantOnFlag_Enable      = (1L << 0), /* instant on is enabled (read/write)*/
  kQTSInstantOnFlag_Permitted   = (1L << 1) /* instant on is possible (read only)*/
};


struct QTSInstantOnPref {
  SInt32              flags;                  /* flags*/
  SInt32              factor;                 /*    0-100; default is 50*/
};
typedef struct QTSInstantOnPref         QTSInstantOnPref;
enum {
  kQTSTransAndProxyAtomType     = 'strp', /* transport/proxy prefs root atom*/
  kQTSConnectionPrefsVersion    = 'vers', /*   prefs format version*/
  kQTSTransportPrefsAtomType    = 'trns', /*   tranport prefs root atom*/
  kQTSConnectionAtomType        = 'conn', /*     connection prefs atom type, one for each transport type*/
  kQTSUDPTransportType          = 'udp ', /*     udp transport prefs*/
  kQTSHTTPTransportType         = 'http', /*     http transport prefs*/
  kQTSTCPTransportType          = 'tcp ', /*     tcp transport prefs    */
  kQTSProxyPrefsAtomType        = 'prxy', /*   proxy prefs root atom*/
  kQTSHTTPProxyPrefsType        = 'http', /*     http proxy settings*/
  kQTSRTSPProxyPrefsType        = 'rtsp', /*     rtsp proxy settings*/
  kQTSSOCKSProxyPrefsType       = 'sock', /*     socks proxy settings*/
  kQTSProxyUserInfoPrefsType    = 'user', /*   proxy username/password root atom*/
  kQTSDontProxyPrefsAtomType    = 'nopr', /*   no-proxy prefs root atom*/
  kQTSDontProxyDataType         = 'data', /*     no proxy settings*/
  kQTSInstantOnPrefsAtomType    = 'inon' /* instant on prefs*/
};

/*
 *  QTSPrefsAddProxySetting()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.1 and later
 *    Windows:          in QTSClient.lib 4.1 and later
 */
extern OSErr 
QTSPrefsAddProxySetting(
  OSType   proxyType,
  SInt32   portID,
  UInt32   flags,
  UInt32   seed,
  Str255   srvrURL)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPrefsFindProxyByType()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.1 and later
 *    Windows:          in QTSClient.lib 4.1 and later
 */
extern OSErr 
QTSPrefsFindProxyByType(
  OSType           proxyType,
  UInt32           flags,
  UInt32           flagsMask,
  QTSProxyPref **  proxyHndl,
  SInt16 *         count)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPrefsAddConnectionSetting()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.1 and later
 *    Windows:          in QTSClient.lib 4.1 and later
 */
extern OSErr 
QTSPrefsAddConnectionSetting(
  OSType   protocol,
  SInt32   portID,
  UInt32   flags,
  UInt32   seed)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPrefsFindConnectionByType()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.1 and later
 *    Windows:          in QTSClient.lib 4.1 and later
 */
extern OSErr 
QTSPrefsFindConnectionByType(
  OSType               protocol,
  UInt32               flags,
  UInt32               flagsMask,
  QTSTransportPref **  connectionHndl,
  SInt16 *             count)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPrefsGetActiveConnection()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.1 and later
 *    Windows:          in QTSClient.lib 4.1 and later
 */
extern OSErr 
QTSPrefsGetActiveConnection(
  OSType              protocol,
  QTSTransportPref *  connectInfo)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPrefsGetNoProxyURLs()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.1 and later
 *    Windows:          in QTSClient.lib 4.1 and later
 */
extern OSErr 
QTSPrefsGetNoProxyURLs(QTSNoProxyPref ** noProxyHndl)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPrefsSetNoProxyURLs()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.1 and later
 *    Windows:          in QTSClient.lib 4.1 and later
 */
extern OSErr 
QTSPrefsSetNoProxyURLs(
  char *   urls,
  UInt32   flags,
  UInt32   seed)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPrefsAddProxyUserInfo()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0.1 and later
 *    Windows:          in QTSClient.lib 5.0.1 and later
 */
extern OSErr 
QTSPrefsAddProxyUserInfo(
  OSType      proxyType,
  SInt32      flags,
  SInt32      flagsMask,
  StringPtr   username,
  StringPtr   password)                                       AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPrefsFindProxyUserInfoByType()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0.1 and later
 *    Windows:          in QTSClient.lib 5.0.1 and later
 */
extern OSErr 
QTSPrefsFindProxyUserInfoByType(
  OSType      proxyType,
  SInt32      flags,
  SInt32      flagsMask,
  StringPtr   username,
  StringPtr   password)                                       AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPrefsGetInstantOnSettings()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QTStreamLib 6.0 and later
 *    Windows:          in QTSClient.lib 6.0 and later
 */
extern OSErr 
QTSPrefsGetInstantOnSettings(
  QTSInstantOnPref *  outPref,
  SInt32              inFlags)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSPrefsSetInstantOnSettings()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QTStreamLib 6.0 and later
 *    Windows:          in QTSClient.lib 6.0 and later
 */
extern OSErr 
QTSPrefsSetInstantOnSettings(
  QTSInstantOnPref *  inPref,
  SInt32              inFlags)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;



/*============================================================================
        Memory Management Services
============================================================================*/
/*
   These routines allocate normal pointers and handles,
   but do the correct checking, etc.
   Dispose using the normal DisposePtr and DisposeHandle
   Call these routines for one time memory allocations.
   You do not need to set any hints to use these calls.
*/

/*
 *  QTSNewPtr()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern Ptr 
QTSNewPtr(
  UInt32    inByteCount,
  SInt32    inFlags,
  SInt32 *  outFlags)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSNewHandle()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern Handle 
QTSNewHandle(
  UInt32    inByteCount,
  SInt32    inFlags,
  SInt32 *  outFlags)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


#define QTSNewPtrClear(_s)      QTSNewPtr((_s), kQTSMemAllocClearMem, NULL)
#define QTSNewHandleClear(_s)   QTSNewHandle((_s), kQTSMemAllocClearMem, NULL)
/* flags in*/
enum {
  kQTSMemAllocClearMem          = 0x00000001,
  kQTSMemAllocDontUseTempMem    = 0x00000002,
  kQTSMemAllocTryTempMemFirst   = 0x00000004,
  kQTSMemAllocDontUseSystemMem  = 0x00000008,
  kQTSMemAllocTrySystemMemFirst = 0x00000010,
  kQTSMemAllocHoldMemory        = 0x00001000,
  kQTSMemAllocIsInterruptTime   = 0x01010000 /* currently not supported for alloc*/
};

/* flags out*/
enum {
  kQTSMemAllocAllocatedInTempMem = 0x00000001,
  kQTSMemAllocAllocatedInSystemMem = 0x00000002
};

typedef struct OpaqueQTSMemPtr*         QTSMemPtr;
/*
   These routines are for buffers that will be recirculated
   you must use QTReleaseMemPtr instead of DisposePtr
   QTSReleaseMemPtr can be used at interrupt time
   but QTSAllocMemPtr currently cannot 
*/
/*
 *  QTSAllocMemPtr()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern QTSMemPtr 
QTSAllocMemPtr(
  UInt32   inByteCount,
  SInt32   inFlags)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSReleaseMemPtr()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern void 
QTSReleaseMemPtr(
  QTSMemPtr   inMemPtr,
  SInt32      inFlags)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;



/*============================================================================
        Buffer Management Services
============================================================================*/

enum {
  kQTSStreamBufferVersion1      = 1
};

struct QTSStreamBuffer {
  struct QTSStreamBuffer * reserved1;
  struct QTSStreamBuffer * reserved2;
  struct QTSStreamBuffer * next;              /* next message block in a message */
  unsigned char *     rptr;                   /* first byte with real data in the DataBuffer */
  unsigned char *     wptr;                   /* last+1 byte with real data in the DataBuffer */
  SInt32              version;
  UInt32              metadata[4];            /* usage defined by message sender */
  SInt32              flags;                  /* reserved */
  long                reserved3;
  long                reserved4;
  long                reserved5;

  UInt32              moreMeta[8];
};
typedef struct QTSStreamBuffer          QTSStreamBuffer;
/* flags for QTSDuplicateMessage*/
enum {
  kQTSDuplicateBufferFlag_CopyData = 0x00000001,
  kQTSDuplicateBufferFlag_FlattenMessage = 0x00000002
};


/*
 *  QTSNewStreamBuffer()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 *    Windows:          in QTSClient.lib 5.0 and later
 */
extern OSErr 
QTSNewStreamBuffer(
  UInt32              inDataSize,
  SInt32              inFlags,
  QTSStreamBuffer **  outStreamBuffer)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSFreeMessage()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern void 
QTSFreeMessage(QTSStreamBuffer * inMessage)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
    kQTSDuplicateBufferFlag_CopyData - forces a copy of the data itself
    kQTSCopyBufferFlag_FlattenMessage - copies the data if it needs to be flattened
    QTSDuplicateMessage never frees the old message
*/
/*
 *  QTSDuplicateMessage()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 *    Windows:          in QTSClient.lib 5.0 and later
 */
extern OSErr 
QTSDuplicateMessage(
  QTSStreamBuffer *   inMessage,
  SInt32              inFlags,
  QTSStreamBuffer **  outDuplicatedMessage)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSMessageLength()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern UInt32 
QTSMessageLength(QTSStreamBuffer * inMessage)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSStreamBufferDataInfo()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 *    Windows:          in QTSClient.lib 5.0 and later
 */
extern void 
QTSStreamBufferDataInfo(
  QTSStreamBuffer *  inStreamBuffer,
  unsigned char **   outDataStart,
  UInt32 *           outDataMaxLength)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/* ---- old calls (don't use these)*/

/*
 *  QTSAllocBuffer()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern QTSStreamBuffer * 
QTSAllocBuffer(SInt32 inSize)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSDupMessage()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern QTSStreamBuffer * 
QTSDupMessage(QTSStreamBuffer * inMessage)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSCopyMessage()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern QTSStreamBuffer * 
QTSCopyMessage(QTSStreamBuffer * inMessage)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSFlattenMessage()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern QTSStreamBuffer * 
QTSFlattenMessage(QTSStreamBuffer * inMessage)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;




/*============================================================================
        Misc
============================================================================*/
/*
 *  QTSGetErrorString()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern Boolean 
QTSGetErrorString(
  SInt32   inErrorCode,
  UInt32   inMaxErrorStringLength,
  char *   outErrorString,
  SInt32   inFlags)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;


/*
 *  QTSInitializeMediaParams()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0.1 and later
 *    Windows:          in QTSClient.lib 5.0.1 and later
 */
extern OSErr 
QTSInitializeMediaParams(QTSMediaParams * inMediaParams)      AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;




/* UPP call backs */
/*
 *  NewQTSNotificationUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QTSNotificationUPP
NewQTSNotificationUPP(QTSNotificationProcPtr userRoutine)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

/*
 *  NewQTSPanelFilterUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QTSPanelFilterUPP
NewQTSPanelFilterUPP(QTSPanelFilterProcPtr userRoutine)       AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

/*
 *  NewQTSModalFilterUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QTSModalFilterUPP
NewQTSModalFilterUPP(QTSModalFilterProcPtr userRoutine)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

/*
 *  DisposeQTSNotificationUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQTSNotificationUPP(QTSNotificationUPP userUPP)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

/*
 *  DisposeQTSPanelFilterUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQTSPanelFilterUPP(QTSPanelFilterUPP userUPP)           AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

/*
 *  DisposeQTSModalFilterUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQTSModalFilterUPP(QTSModalFilterUPP userUPP)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

/*
 *  InvokeQTSNotificationUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ComponentResult
InvokeQTSNotificationUPP(
  ComponentResult     inErr,
  OSType              inNotificationType,
  void *              inNotificationParams,
  void *              inRefCon,
  QTSNotificationUPP  userUPP)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

/*
 *  InvokeQTSPanelFilterUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeQTSPanelFilterUPP(
  QTSPanelFilterParams *  inParams,
  void *                  inRefCon,
  QTSPanelFilterUPP       userUPP)                            AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

/*
 *  InvokeQTSModalFilterUPP()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.9
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeQTSModalFilterUPP(
  DialogPtr            inDialog,
  const EventRecord *  inEvent,
  SInt16 *             ioItemHit,
  void *               inRefCon,
  QTSModalFilterUPP    userUPP)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_9;

#if __MACH__
  #ifdef __cplusplus
    inline QTSNotificationUPP                                   NewQTSNotificationUPP(QTSNotificationProcPtr userRoutine) { return userRoutine; }
    inline QTSPanelFilterUPP                                    NewQTSPanelFilterUPP(QTSPanelFilterProcPtr userRoutine) { return userRoutine; }
    inline QTSModalFilterUPP                                    NewQTSModalFilterUPP(QTSModalFilterProcPtr userRoutine) { return userRoutine; }
    inline void                                                 DisposeQTSNotificationUPP(QTSNotificationUPP) { }
    inline void                                                 DisposeQTSPanelFilterUPP(QTSPanelFilterUPP) { }
    inline void                                                 DisposeQTSModalFilterUPP(QTSModalFilterUPP) { }
    inline ComponentResult                                      InvokeQTSNotificationUPP(ComponentResult inErr, OSType inNotificationType, void * inNotificationParams, void * inRefCon, QTSNotificationUPP userUPP) { return (*userUPP)(inErr, inNotificationType, inNotificationParams, inRefCon); }
    inline Boolean                                              InvokeQTSPanelFilterUPP(QTSPanelFilterParams * inParams, void * inRefCon, QTSPanelFilterUPP userUPP) { return (*userUPP)(inParams, inRefCon); }
    inline Boolean                                              InvokeQTSModalFilterUPP(DialogPtr inDialog, const EventRecord * inEvent, SInt16 * ioItemHit, void * inRefCon, QTSModalFilterUPP userUPP) { return (*userUPP)(inDialog, inEvent, ioItemHit, inRefCon); }
  #else
    #define NewQTSNotificationUPP(userRoutine)                  ((QTSNotificationUPP)userRoutine)
    #define NewQTSPanelFilterUPP(userRoutine)                   ((QTSPanelFilterUPP)userRoutine)
    #define NewQTSModalFilterUPP(userRoutine)                   ((QTSModalFilterUPP)userRoutine)
    #define DisposeQTSNotificationUPP(userUPP)
    #define DisposeQTSPanelFilterUPP(userUPP)
    #define DisposeQTSModalFilterUPP(userUPP)
    #define InvokeQTSNotificationUPP(inErr, inNotificationType, inNotificationParams, inRefCon, userUPP) (*userUPP)(inErr, inNotificationType, inNotificationParams, inRefCon)
    #define InvokeQTSPanelFilterUPP(inParams, inRefCon, userUPP) (*userUPP)(inParams, inRefCon)
    #define InvokeQTSModalFilterUPP(inDialog, inEvent, ioItemHit, inRefCon, userUPP) (*userUPP)(inDialog, inEvent, ioItemHit, inRefCon)
  #endif
#endif


#endif // !__LP64__



#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* __QUICKTIMESTREAMING__ */

