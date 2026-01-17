/*
     File:       QuickTime/QTStreamingComponents.h
 
     Contains:   QuickTime Interfaces.
 
     Version:    QuickTime 7.2.1
 
     Copyright:  © 1990-2006 by Apple Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __QTSTREAMINGCOMPONENTS__
#define __QTSTREAMINGCOMPONENTS__

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

/*============================================================================
        Stream Sourcer
============================================================================*/
enum {
  kQTSSourcerType               = 'srcr'
};

typedef ComponentInstance               QTSSourcer;
enum {
  kQTSSGChannelSourcerType      = 'sgch',
  kQTSMovieTrackSourcerType     = 'trak',
  kQTSPushDataSourcerType       = 'push'
};

/* flags for sourcer data */
enum {
  kQTSSourcerDataFlag_SyncSample = 0x00000001,
  kQTSPushDataSourcerFlag_SampleTimeIsValid = (long)0x80000000
};


enum {
  kQTSSourcerInitParamsVersion1 = 1
};

struct QTSSourcerInitParams {
  SInt32              version;
  SInt32              flags;
  OSType              dataType;
  void *              data;
  UInt32              dataLength;
};
typedef struct QTSSourcerInitParams     QTSSourcerInitParams;
/*
 *  QTSNewSourcer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 */
extern OSErr 
QTSNewSourcer(
  void *                        params,
  const QTSSourcerInitParams *  inInitParams,
  SInt32                        inFlags,
  ComponentInstance *           outSourcer)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* info selectors for sourcers - get and set */
enum {
  kQTSInfo_Track                = 'trak', /* QTSTrackParams* */
  kQTSInfo_Loop                 = 'loop', /* QTSLoopParams* */
  kQTSInfo_SourcerTiming        = 'stim', /* QTSSourcerTimingParams* */
  kQTSInfo_TargetFrameRate      = 'tfps', /* Fixed * in frames per second */
  kQTSInfo_PushData             = 'push', /* QTSPushDataParams* */
  kQTSInfo_SourcerCallbackProc  = 'scbp', /* QTSSourcerCallbackProcParams* */
  kQTSInfo_TargetDataRate       = 'tdrt', /* UInt32 * in bytes per second */
  kQTSInfo_AudioAutoGainOnOff   = 'agc ', /* Boolean*  - error if unavailable*/
  kQTSInfo_AudioGain            = 'gain', /* Fixed* kFixed1 is unity gain */
  kQTSInfo_CroppedInputRect     = 'crpr', /* Rect* - defined relative to kQTSInfo_FullInputRect below */
  kQTSInfo_SpatialSettings      = 'sptl', /* pointer to SCSpatialSettings struct*/
  kQTSInfo_TemporalSettings     = 'tprl', /* pointer to SCTemporalSettings struct*/
  kQTSInfo_DataRateSettings     = 'drat', /* pointer to SCDataRateSettings struct*/
  kQTSInfo_CodecFlags           = 'cflg', /* pointer to CodecFlags*/
  kQTSInfo_CodecSettings        = 'cdec', /* pointer to Handle*/
  kQTSInfo_ForceKeyValue        = 'ksim', /* pointer to long*/
  kQTSInfo_SoundSampleRate      = 'ssrt', /* pointer to UnsignedFixed*/
  kQTSInfo_SoundSampleSize      = 'ssss', /* pointer to short*/
  kQTSInfo_SoundChannelCount    = 'sscc', /* pointer to short*/
  kQTSInfo_SoundCompression     = 'ssct', /* pointer to OSType*/
  kQTSInfo_CompressionList      = 'ctyl', /* pointer to OSType Handle*/
  kQTSInfo_VideoHue             = 'hue ', /* UInt16* */
  kQTSInfo_VideoSaturation      = 'satr', /* UInt16* */
  kQTSInfo_VideoContrast        = 'trst', /* UInt16* */
  kQTSInfo_VideoBrightness      = 'brit', /* UInt16* */
  kQTSInfo_VideoSharpness       = 'shrp', /* UInt16* */
  kQTSInfo_TimeScale            = 'scal', /* UInt32* */
  kQTSInfo_SGChannelDeviceName  = 'innm', /* Handle* */
  kQTSInfo_SGChannelDeviceList  = 'srdl', /* SGDeviceList* */
  kQTSInfo_SGChannelDeviceInput = 'sdii', /* short* */
  kQTSInfo_SGChannelSettings    = 'sesg', /* QTSSGChannelSettingsParams */
  kQTSInfo_PreviewWhileRecordingMode = 'srpr', /* Boolean* */
  kQTSInfo_CompressionParams    = 'sccp' /* QTAtomContainer* */
};

/* info selectors for sourcers - get only*/
enum {
  kQTSInfo_SGChannel            = 'sgch', /* SGChannel* */
  kQTSInfo_SGChannelInputName   = 'srnm', /* Handle* */
  kQTSInfo_FullInputRect        = 'fulr' /* Rect* */
};

/* loop flags */
enum {
  kQTSLoopFlag_Loop             = 0x00000001
};

enum {
  kQTSLoopParamsVersion1        = 1
};

struct QTSLoopParams {
  SInt32              version;
  SInt32              flags;
  SInt32              loopFlags;
  SInt32              flagsMask;
  SInt32              numLoops;
};
typedef struct QTSLoopParams            QTSLoopParams;
enum {
  kQTSTrackParamsVersion1       = 1
};

struct QTSTrackParams {
  SInt32              version;
  SInt32              flags;
  Track               track;
  TimeValue64         trackStartOffset;       /* to start other than at the beginning otherwise set to 0*/
  TimeValue64         duration;               /* to limit the duration otherwise set to 0*/
  QTSLoopParams *     loopParams;             /* set to NULL if not using; default is no looping */
};
typedef struct QTSTrackParams           QTSTrackParams;
enum {
  kQTSSourcerTimingParamsVersion1 = 1
};

struct QTSSourcerTimingParams {
  SInt32              version;
  SInt32              flags;
  TimeScale           timeScale;
  TimeValue64         presentationStartTime;
  TimeValue64         presentationEndTime;
  TimeValue64         presentationCurrentTime;
  TimeValue64         localStartTime;
  TimeValue64         localEndTime;
  TimeValue64         localCurrentTime;
};
typedef struct QTSSourcerTimingParams   QTSSourcerTimingParams;
enum {
  kQTSPushDataParamsVersion1    = 1
};

enum {
  kQTSPushDataFlag_SampleTimeIsValid = 0x00000001,
  kQTSPushDataFlag_DurationIsValid = 0x00000002
};

struct QTSPushDataParams {
  SInt32              version;
  SInt32              flags;
  SampleDescriptionHandle  sampleDescription; /* caller owns the handle */
  UInt32              sampleDescSeed;
  TimeValue64         sampleTime;             /* also set flag if you set this */
  TimeValue64         duration;               /* also set flag if you set this */
  UInt32              dataLength;
  void *              dataPtr;                /* this does not have to be a real macintosh Ptr */
};
typedef struct QTSPushDataParams        QTSPushDataParams;
enum {
  kQTSSourcerCallbackProcParamsVersion1 = 1
};


struct QTSSourcerCallbackProcParams {
  SInt32              version;
  SInt32              flags;
  QTSNotificationUPP  proc;
  void *              refCon;
};
typedef struct QTSSourcerCallbackProcParams QTSSourcerCallbackProcParams;
/* track sourcer callback selectors*/
enum {
  kQTSSourcerCallback_Done      = 'done' /* QTSSourcerDoneParams* */
};


/* push data sourcer callback selectors*/
enum {
  kQTSPushDataSourcerCallback_HasCharacteristic = 0x050D, /* QTSPushDataHasCharacteristicParams* */
  kQTSPushDataSourcerCallback_SetInfo = 0x0507, /* QTSPushDataInfoParams* */
  kQTSPushDataSourcerCallback_GetInfo = 0x0508 /* QTSPushDataInfoParams* */
};

struct QTSPushDataHasCharacteristicParams {
  SInt32              version;
  SInt32              flags;
  OSType              characteristic;
  Boolean             returnedHasIt;
  char                reserved1;
  char                reserved2;
  char                reserved3;
};
typedef struct QTSPushDataHasCharacteristicParams QTSPushDataHasCharacteristicParams;
struct QTSPushDataInfoParams {
  SInt32              version;
  SInt32              flags;
  OSType              selector;
  void *              ioParams;
};
typedef struct QTSPushDataInfoParams    QTSPushDataInfoParams;
enum {
  kQTSSourcerDoneParamsVersion1 = 1
};

struct QTSSourcerDoneParams {
  SInt32              version;
  SInt32              flags;
  ComponentInstance   sourcer;
};
typedef struct QTSSourcerDoneParams     QTSSourcerDoneParams;
struct QTSSGChannelSettingsParams {
  UserData            settings;
  SInt32              flags;
};
typedef struct QTSSGChannelSettingsParams QTSSGChannelSettingsParams;

/*-----------------------------------------
    Stream Sourcer Selectors
-----------------------------------------*/
enum {
  kQTSSourcerInitializeSelect   = 0x0500,
  kQTSSourcerSetEnableSelect    = 0x0503,
  kQTSSourcerGetEnableSelect    = 0x0504,
  kQTSSourcerSetInfoSelect      = 0x0507,
  kQTSSourcerGetInfoSelect      = 0x0508,
  kQTSSourcerSetTimeScaleSelect = 0x050E,
  kQTSSourcerGetTimeScaleSelect = 0x050F,
  kQTSSourcerIdleSelect         = 0x0516
};

/*-----------------------------------------
    Stream Sourcer Prototypes
-----------------------------------------*/
/*
 *  QTSSourcerInitialize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0.1 and later
 */
extern ComponentResult 
QTSSourcerInitialize(
  QTSSourcer                    inSourcer,
  const QTSSourcerInitParams *  inInitParams)                 AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  QTSSourcerIdle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 */
extern ComponentResult 
QTSSourcerIdle(
  QTSSourcer           inSourcer,
  const TimeValue64 *  inTime,
  SInt32               inFlags,
  SInt32 *             outFlags)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTSSourcerSetEnable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 */
extern ComponentResult 
QTSSourcerSetEnable(
  QTSSourcer   inSourcer,
  Boolean      inEnableMode,
  SInt32       inFlags)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTSSourcerGetEnable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 */
extern ComponentResult 
QTSSourcerGetEnable(
  QTSSourcer   inSourcer,
  Boolean *    outEnableMode,
  SInt32       inFlags)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTSSourcerSetTimeScale()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 */
extern ComponentResult 
QTSSourcerSetTimeScale(
  QTSSourcer   inSourcer,
  TimeScale    inTimeScale)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTSSourcerGetTimeScale()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 */
extern ComponentResult 
QTSSourcerGetTimeScale(
  QTSSourcer   inSourcer,
  TimeScale *  outTimeScale)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTSSourcerSetInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 */
extern ComponentResult 
QTSSourcerSetInfo(
  QTSSourcer   inSourcer,
  OSType       inSelector,
  void *       ioParams)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTSSourcerGetInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 */
extern ComponentResult 
QTSSourcerGetInfo(
  QTSSourcer   inSourcer,
  OSType       inSelector,
  void *       ioParams)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



enum {
  kQTSInfo_InputDeviceName      = 'innm', /* Handle* */
  kQTSInfo_InputSourceName      = 'srnm' /* Handle* */
};


/*============================================================================
        Stream Handler
============================================================================*/

/*
    Server edits are only valid for the current chunk
*/
struct SHServerEditParameters {
  UInt32              version;
  Fixed               editRate;
  TimeValue64         dataStartTime_mediaAxis;
  TimeValue64         dataEndTime_mediaAxis;
};
typedef struct SHServerEditParameters   SHServerEditParameters;
enum {
  kSHNoChunkDispatchFlags       = 0,
  kSHChunkFlagSyncSample        = 1 << 2,
  kSHChunkFlagDataLoss          = 1 << 4,
  kSHChunkFlagExtended          = 1 << 5
};

struct SHChunkRecord {
  UInt32              version;
  long                reserved1;
  SInt32              flags;
  UInt32              dataSize;
  UInt8 *             dataPtr;
  long                reserved2;
  long                reserved3;
  TimeValue64         presentationTime;

  long                reserved4;
  long                reserved5;
  const SHServerEditParameters * serverEditParameters;
  long                reserved6;
  long                reserved7;
};
typedef struct SHChunkRecord            SHChunkRecord;
enum {
  kSHNumExtendedDataLongs       = 10
};

enum {
  kSHExtendedChunkFlag_HasSampleCount = 1 << 0,
  kSHExtendedChunkFlag_HasFrameLengths = 1 << 1
};

struct SHExtendedChunkRecord {
  SHChunkRecord       chunk;
  SInt32              extendedFlags;
  SInt32              extendedData[10];
};
typedef struct SHExtendedChunkRecord    SHExtendedChunkRecord;

/*============================================================================
        RTP Components
============================================================================*/

typedef UInt32                          RTPSSRC;
enum {
  kRTPInvalidSSRC               = 0
};


/* RTP standard content encodings for audio */
enum {
  kRTPPayload_PCMU              = 0,    /* 8kHz PCM mu-law mono */
  kRTPPayload_1016              = 1,    /* 8kHz CELP (Fed Std 1016) mono */
  kRTPPayload_G721              = 2,    /* 8kHz G.721 ADPCM mono */
  kRTPPayload_GSM               = 3,    /* 8kHz GSM mono */
  kRTPPayload_G723              = 4,    /* 8kHz G.723 ADPCM mono */
  kRTPPayload_DVI_8             = 5,    /* 8kHz Intel DVI ADPCM mono */
  kRTPPayload_DVI_16            = 6,    /* 16kHz Intel DVI ADPCM mono */
  kRTPPayload_LPC               = 7,    /* 8kHz LPC */
  kRTPPayload_PCMA              = 8,    /* 8kHz PCM a-law mono */
  kRTPPayload_L16_44_2          = 10,   /* 44.1kHz 16-bit linear stereo */
  kRTPPayload_L16_44_1          = 11,   /* 44.1kHz 16-bit linear mono */
  kRTPPayload_PureVoice         = 12,   /* 8kHz PureVoice mono (QCELP) */
  kRTPPayload_MPEGAUDIO         = 14,   /* MPEG I and II audio */
  kRTPPayload_DVI_11            = 16,   /* 11kHz Intel DVI ADPCM mono */
  kRTPPayload_DVI_22            = 17    /* 22kHz Intel DVI ADPCM mono */
};

/* RTP standard content encodings for video */
enum {
  kRTPPayload_CELLB             = 25,   /* Sun CellB */
  kRTPPayload_JPEG              = 26,   /* JPEG */
  kRTPPayload_CUSEEME           = 27,   /* Cornell CU-SeeMe */
  kRTPPayload_NV                = 28,   /* Xerox PARC nv */
  kRTPPayload_PICWIN            = 29,   /* BBN Picture Window */
  kRTPPayload_CPV               = 30,   /* Bolter CPV */
  kRTPPayload_H261              = 31,   /* CCITT H.261 */
  kRTPPayload_MPEGVIDEO         = 32,   /* MPEG I and II video */
  kRTPPayload_H263              = 34    /* CCITT H.263 */
};

/* Other RTP standard content encodings */
enum {
  kRTPPayload_MPEG2T            = 33    /* MPEG 2 Transport */
};

/* Dynamic encodings */
enum {
  kRTPPayload_FirstDynamic      = 96,
  kRTPPayload_LastDynamic       = 127,
  kRTPPayload_Unknown           = 0xFF
};



/*
-----------------------------------------
    RTP Info selectors
-----------------------------------------
*/
/* ----- these are get and set ----- */
enum {
  kRTPInfo_SSRC                 = 'ssrc', /* UInt32* */
  kRTPInfo_NextSeqNum           = 'rnsn' /* UInt16* */
};

/*-----------------------------------------
    RTP Statistics
-----------------------------------------*/
enum {
  kRTPTotalReceivedPktsStat     = 'trcp',
  kRTPTotalLostPktsStat         = 'tlsp',
  kRTPTotalProcessedPktsStat    = 'tprp',
  kRTPTotalDroppedPktsStat      = 'tdrp',
  kRTPBadHeaderDroppedPktsStat  = 'bhdp',
  kRTPOurHeaderDroppedPktsStat  = 'ohdp',
  kRTPNotReceivingSenderDroppedPktsStat = 'nsdp',
  kRTPNotProcessingDroppedPktsStat = 'npdp',
  kRTPBadSeqDroppedPktsStat     = 'bsdp',
  kRTPArriveTooLatePktsStat     = 'artl',
  kRTPWaitForSeqDroppedPktsStat = 'wsdp',
  kRTPBadStateDroppedPktsStat   = 'stdp',
  kRTPBadPayloadDroppedPktsStat = 'bpdp',
  kRTPNoTimeScaleDroppedPktsStat = 'ntdp',
  kRTPDupSeqNumDroppedPktsStat  = 'dsdp',
  kRTPLostPktsPercentStat       = 'lspp',
  kRTPDroppedPktsPercentStat    = 'dppp',
  kRTPTotalUnprocessedPktsPercentStat = 'tupp',
  kRTPRTCPDataRateStat          = 'rrcd',
  kRTPPayloadIDStat             = 'rpid',
  kRTPPayloadNameStat           = 'rpnm',
  kRTPNumPktsInQueueStat        = 'rnpq',
  kRTPTotalPktsInQueueStat      = 'rtpq',
  kRTPTotalOutOfOrderPktsStat   = 'rtoo',
  kRTPRetransmissionStat        = 'rrtx'
};


/*-----------------------------------------
    Payload Info
-----------------------------------------*/
enum {
  kRTPPayloadSpeedTag           = 'sped', /* 0-255, 255 is fastest*/
  kRTPPayloadLossRecoveryTag    = 'loss', /* 0-255, 0 can't handle any loss, 128 can handle 50% packet loss*/
  kRTPPayloadConformanceTag     = 'conf' /* more than one of these can be present*/
};

struct RTPPayloadCharacteristic {
  OSType              tag;
  long                value;
};
typedef struct RTPPayloadCharacteristic RTPPayloadCharacteristic;
/*
    pass RTPPayloadSortRequest to QTSFindMediaPacketizer or QTSFindMediaPacketizerForTrack.
    define the characteristics to sort by. tag is key to sort on. value is positive for ascending
    sort (low value first), negative for descending sort (high value first).
*/
struct RTPPayloadSortRequest {
  long                characteristicCount;
  RTPPayloadCharacteristic  characteristic[1]; /* tag is key to sort on, value is + for ascending, - for descending*/
};
typedef struct RTPPayloadSortRequest    RTPPayloadSortRequest;
typedef RTPPayloadSortRequest *         RTPPayloadSortRequestPtr;
/* flags for RTPPayloadInfo */
enum {
  kRTPPayloadTypeStaticFlag     = 0x00000001,
  kRTPPayloadTypeDynamicFlag    = 0x00000002
};

struct RTPPayloadInfo {
  long                payloadFlags;
  UInt8               payloadID;
  char                reserved1;
  char                reserved2;
  char                reserved3;
  char                payloadName[1];
};
typedef struct RTPPayloadInfo           RTPPayloadInfo;
typedef RTPPayloadInfo *                RTPPayloadInfoPtr;
typedef RTPPayloadInfoPtr *             RTPPayloadInfoHandle;
/*============================================================================
        RTP Reassembler
============================================================================*/
typedef ComponentInstance               RTPReassembler;
enum {
  kRTPReassemblerType           = 'rtpr'
};

enum {
  kRTPBaseReassemblerType       = 'gnrc',
  kRTP261ReassemblerType        = 'h261',
  kRTP263ReassemblerType        = 'h263',
  kRTP263PlusReassemblerType    = '263+',
  kRTPAudioReassemblerType      = 'soun',
  kRTPQTReassemblerType         = 'qtim',
  kRTPPureVoiceReassemblerType  = 'Qclp',
  kRTPJPEGReassemblerType       = 'jpeg',
  kRTPQDesign2ReassemblerType   = 'QDM2',
  kRTPSorensonReassemblerType   = 'SVQ1',
  kRTPMP3ReassemblerType        = 'mp3 ',
  kRTPMPEG4AudioReassemblerType = 'mp4a',
  kRTPMPEG4VideoReassemblerType = 'mp4v',
  kRTPAMRReassemblerType        = 'amr '
};

struct RTPRssmInitParams {
  RTPSSRC             ssrc;
  UInt8               payloadType;
  UInt8               reserved1;
  UInt8               reserved2;
  UInt8               reserved3;
  TimeBase            timeBase;
  TimeScale           timeScale;
};
typedef struct RTPRssmInitParams        RTPRssmInitParams;
struct RTPDescParams {
  QTAtomContainer     container;
  QTAtom              presentationParentAtom;
  QTAtom              streamParentAtom;
};
typedef struct RTPDescParams            RTPDescParams;
struct RTPRssmMoreInitParams {
  RTPRssmInitParams   initParams;
  SInt32              version;
  RTPDescParams       desc;
};
typedef struct RTPRssmMoreInitParams    RTPRssmMoreInitParams;
enum {
  kRTPRssmMoreInitParamsVersion1 = 1
};


/* get/set info selectors*/
enum {
  kRTPRssmInfo_MoreInitParams   = 'rrmi'
};


struct RTPRssmPacket {
  struct RTPRssmPacket * next;
  struct RTPRssmPacket * prev;
  QTSStreamBuffer *   streamBuffer;
  Boolean             paramsFilledIn;
  UInt8               reserved;
  UInt16              sequenceNum;
  UInt32              transportHeaderLength;  /* filled in by base*/
  UInt32              payloadHeaderLength;    /* derived adjusts this */
  UInt32              dataLength;
  SHServerEditParameters  serverEditParams;
  TimeValue64         timeStamp;              /* lower 32 bits is original rtp timestamp*/
  SInt32              chunkFlags;             /* these are or'd together*/
  SInt32              flags;

};
typedef struct RTPRssmPacket            RTPRssmPacket;
/* flags for RTPRssmPacket struct*/
enum {
  kRTPRssmPacketHasMarkerBitSet = 0x00000001,
  kRTPRssmPacketHasServerEditFlag = 0x00010000
};

/* flags for RTPRssmSendStreamBufferRange*/
enum {
  kRTPRssmCanRefStreamBuffer    = 0x00000001
};

/* flags for RTPRssmSendPacketList*/
enum {
  kRTPRssmLostSomePackets       = 0x00000001
};

/* flags for RTPRssmSetFlags*/
enum {
  kRTPRssmEveryPacketAChunkFlag = 0x00000001,
  kRTPRssmQueueAndUseMarkerBitFlag = 0x00000002,
  kRTPRssmTrackLostPacketsFlag  = 0x00010000,
  kRTPRssmNoReorderingRequiredFlag = 0x00020000
};


struct RTPSendStreamBufferRangeParams {
  QTSStreamBuffer *   streamBuffer;
  TimeValue64         presentationTime;
  UInt32              chunkStartPosition;
  UInt32              numDataBytes;
  SInt32              chunkFlags;
  SInt32              flags;
  const SHServerEditParameters * serverEditParams; /* NULL if no edit*/
};
typedef struct RTPSendStreamBufferRangeParams RTPSendStreamBufferRangeParams;
/* characteristics*/
enum {
  kRTPCharacteristic_RequiresOrderedPackets = 'rrop',
  kRTPCharacteristic_TimeStampsNotMonoIncreasing = 'tsmi'
};


enum {
  kRTPReassemblerInfoResType    = 'rsmi'
};

struct RTPReassemblerInfo {
  long                characteristicCount;
  RTPPayloadCharacteristic  characteristic[1];

                                              /* after the last characteristic, the payload name (defined by the MediaPacketizerPayloadInfo*/
                                              /* structure) is present. */
};
typedef struct RTPReassemblerInfo       RTPReassemblerInfo;
typedef RTPReassemblerInfo *            RTPReassemblerInfoPtr;
typedef RTPReassemblerInfoPtr *         RTPReassemblerInfoHandle;
#define RTPReassemblerInfoToPayloadInfo(_rsmi) ((RTPPayloadInfoPtr)(&((_rsmi)->characteristic[(_rsmi)->characteristicCount])))
/* RTPReassemblerInfoElement structs are padded to 32 bits */
enum {
  kRTPReassemblerInfoPadUpToBytes = 4
};


/*
 *  QTSFindReassemblerForPayloadID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSFindReassemblerForPayloadID(
  UInt8                    inPayloadID,
  RTPPayloadSortRequest *  inSortInfo,
  QTAtomContainer *        outReassemblerList)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTSFindReassemblerForPayloadName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSFindReassemblerForPayloadName(
  const char *             inPayloadName,
  RTPPayloadSortRequest *  inSortInfo,
  QTAtomContainer *        outReassemblerList)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*-----------------------------------------
    RTP Reassembler Selectors
-----------------------------------------*/
enum {
  kRTPRssmSetCapabilitiesSelect = 0x0100,
  kRTPRssmGetCapabilitiesSelect = 0x0101,
  kRTPRssmSetPayloadHeaderLengthSelect = 0x0102,
  kRTPRssmGetPayloadHeaderLengthSelect = 0x0103,
  kRTPRssmSetTimeScaleSelect    = 0x0104,
  kRTPRssmGetTimeScaleSelect    = 0x0105,
  kRTPRssmNewStreamHandlerSelect = 0x0106,
  kRTPRssmSetStreamHandlerSelect = 0x0107,
  kRTPRssmGetStreamHandlerSelect = 0x0108,
  kRTPRssmSendStreamHandlerChangedSelect = 0x0109,
  kRTPRssmSetSampleDescriptionSelect = 0x010A,
  kRTPRssmGetChunkAndIncrRefCountSelect = 0x010D,
  kRTPRssmSendChunkAndDecrRefCountSelect = 0x010E,
  kRTPRssmSendLostChunkSelect   = 0x010F,
  kRTPRssmSendStreamBufferRangeSelect = 0x0110,
  kRTPRssmClearCachedPackets    = 0x0111,
  kRTPRssmFillPacketListParamsSelect = 0x0113,
  kRTPRssmReleasePacketListSelect = 0x0114,
  kRTPRssmIncrChunkRefCountSelect = 0x0115,
  kRTPRssmDecrChunkRefCountSelect = 0x0116,
  kRTPRssmGetExtChunkAndIncrRefCountSelect = 0x0117,
  kRTPRssmInitializeSelect      = 0x0500,
  kRTPRssmHandleNewPacketSelect = 0x0501,
  kRTPRssmComputeChunkSizeSelect = 0x0502,
  kRTPRssmAdjustPacketParamsSelect = 0x0503,
  kRTPRssmCopyDataToChunkSelect = 0x0504,
  kRTPRssmSendPacketListSelect  = 0x0505,
  kRTPRssmGetTimeScaleFromPacketSelect = 0x0506,
  kRTPRssmSetInfoSelect         = 0x0509,
  kRTPRssmGetInfoSelect         = 0x050A,
  kRTPRssmHasCharacteristicSelect = 0x050B,
  kRTPRssmResetSelect           = 0x050C
};

/*-----------------------------------------
    RTP Reassembler functions - base to derived
-----------------------------------------*/

/*
 *  RTPRssmInitialize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmInitialize(
  RTPReassembler       rtpr,
  RTPRssmInitParams *  inInitParams)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmHandleNewPacket()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmHandleNewPacket(
  RTPReassembler     rtpr,
  QTSStreamBuffer *  inStreamBuffer,
  SInt32             inNumWraparounds)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmComputeChunkSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmComputeChunkSize(
  RTPReassembler   rtpr,
  RTPRssmPacket *  inPacketListHead,
  SInt32           inFlags,
  UInt32 *         outChunkDataSize)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmAdjustPacketParams()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmAdjustPacketParams(
  RTPReassembler   rtpr,
  RTPRssmPacket *  inPacket,
  SInt32           inFlags)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmCopyDataToChunk()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmCopyDataToChunk(
  RTPReassembler   rtpr,
  RTPRssmPacket *  inPacketListHead,
  UInt32           inMaxChunkDataSize,
  SHChunkRecord *  inChunk,
  SInt32           inFlags)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmSendPacketList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmSendPacketList(
  RTPReassembler       rtpr,
  RTPRssmPacket *      inPacketListHead,
  const TimeValue64 *  inLastChunkPresentationTime,
  SInt32               inFlags)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmGetTimeScaleFromPacket()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmGetTimeScaleFromPacket(
  RTPReassembler     rtpr,
  QTSStreamBuffer *  inStreamBuffer,
  TimeScale *        outTimeScale)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmSetInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmSetInfo(
  RTPReassembler   rtpr,
  OSType           inSelector,
  void *           ioParams)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmGetInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmGetInfo(
  RTPReassembler   rtpr,
  OSType           inSelector,
  void *           ioParams)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmHasCharacteristic()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmHasCharacteristic(
  RTPReassembler   rtpr,
  OSType           inCharacteristic,
  Boolean *        outHasIt)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmReset()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmReset(
  RTPReassembler   rtpr,
  SInt32           inFlags)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*-----------------------------------------
    RTP Reassembler functions - derived to base
-----------------------------------------*/
/* ----- setup*/
/*
 *  RTPRssmSetCapabilities()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmSetCapabilities(
  RTPReassembler   rtpr,
  SInt32           inFlags,
  SInt32           inFlagsMask)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmGetCapabilities()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmGetCapabilities(
  RTPReassembler   rtpr,
  SInt32 *         outFlags)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmSetPayloadHeaderLength()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmSetPayloadHeaderLength(
  RTPReassembler   rtpr,
  UInt32           inPayloadHeaderLength)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmGetPayloadHeaderLength()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmGetPayloadHeaderLength(
  RTPReassembler   rtpr,
  UInt32 *         outPayloadHeaderLength)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmSetTimeScale()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmSetTimeScale(
  RTPReassembler   rtpr,
  TimeScale        inSHTimeScale)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmGetTimeScale()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmGetTimeScale(
  RTPReassembler   rtpr,
  TimeScale *      outSHTimeScale)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmNewStreamHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmNewStreamHandler(
  RTPReassembler            rtpr,
  OSType                    inSHType,
  SampleDescriptionHandle   inSampleDescription,
  TimeScale                 inSHTimeScale,
  ComponentInstance *       outHandler)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmSetStreamHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmSetStreamHandler(
  RTPReassembler      rtpr,
  ComponentInstance   inStreamHandler)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmGetStreamHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmGetStreamHandler(
  RTPReassembler       rtpr,
  ComponentInstance *  outStreamHandler)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  RTPRssmSendStreamHandlerChanged()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmSendStreamHandlerChanged(RTPReassembler rtpr)          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmSetSampleDescription()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmSetSampleDescription(
  RTPReassembler            rtpr,
  SampleDescriptionHandle   inSampleDescription)              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ----- manually sending chunks*/
/*
 *  RTPRssmGetChunkAndIncrRefCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmGetChunkAndIncrRefCount(
  RTPReassembler       rtpr,
  UInt32               inChunkDataSize,
  const TimeValue64 *  inChunkPresentationTime,
  SHChunkRecord **     outChunk)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmGetExtChunkAndIncrRefCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QTStreamLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern ComponentResult 
RTPRssmGetExtChunkAndIncrRefCount(
  RTPReassembler            rtpr,
  UInt32                    inChunkDataSize,
  const TimeValue64 *       inChunkPresentationTime,
  SInt32                    inFlags,
  SHExtendedChunkRecord **  outChunk)                         AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  RTPRssmSendChunkAndDecrRefCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmSendChunkAndDecrRefCount(
  RTPReassembler                  rtpr,
  SHChunkRecord *                 inChunk,
  const SHServerEditParameters *  inServerEdit)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmSendLostChunk()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmSendLostChunk(
  RTPReassembler       rtpr,
  const TimeValue64 *  inChunkPresentationTime)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmSendStreamBufferRange()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmSendStreamBufferRange(
  RTPReassembler                    rtpr,
  RTPSendStreamBufferRangeParams *  inParams)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmClearCachedPackets()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmClearCachedPackets(
  RTPReassembler   rtpr,
  SInt32           inFlags)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmFillPacketListParams()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmFillPacketListParams(
  RTPReassembler   rtpr,
  RTPRssmPacket *  inPacketListHead,
  SInt32           inNumWraparounds,
  SInt32           inFlags)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmReleasePacketList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmReleasePacketList(
  RTPReassembler   rtpr,
  RTPRssmPacket *  inPacketListHead)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmIncrChunkRefCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmIncrChunkRefCount(
  RTPReassembler   rtpr,
  SHChunkRecord *  inChunk)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPRssmDecrChunkRefCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPRssmDecrChunkRefCount(
  RTPReassembler   rtpr,
  SHChunkRecord *  inChunk)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*============================================================================
        RTP Media Packetizer
============================================================================*/
enum {
  kRTPMediaPacketizerType       = 'rtpm'
};

typedef ComponentInstance               RTPMediaPacketizer;
enum {
  kRTPBaseMediaPacketizerType   = 'gnrc',
  kRTP261MediaPacketizerType    = 'h261',
  kRTP263PlusMediaPacketizerType = '263+',
  kRTPAudioMediaPacketizerType  = 'soun',
  kRTPQTMediaPacketizerType     = 'qtim',
  kRTPPureVoiceMediaPacketizerType = 'Qclp',
  kRTPJPEGMediaPacketizerType   = 'jpeg',
  kRTPQDesign2MediaPacketizerType = 'QDM2',
  kRTPSorensonMediaPacketizerType = 'SVQ1',
  kRTPMP3MediaPacketizerType    = 'mp3 ',
  kRTPMPEG4AudioMediaPacketizerType = 'mp4a',
  kRTPMPEG4VideoMediaPacketizerType = 'mp4v',
  kRTPAMRMediaPacketizerType    = 'amr '
};

typedef UInt32                          RTPMPSampleRef;
typedef CALLBACK_API( void , RTPMPDataReleaseProcPtr )(UInt8 *inData, void *inRefCon);
typedef STACK_UPP_TYPE(RTPMPDataReleaseProcPtr)                 RTPMPDataReleaseUPP;
enum {
  kMediaPacketizerCanPackEditRate = 1 << 0,
  kMediaPacketizerCanPackLayer  = 1 << 1,
  kMediaPacketizerCanPackVolume = 1 << 2,
  kMediaPacketizerCanPackBalance = 1 << 3,
  kMediaPacketizerCanPackGraphicsMode = 1 << 4,
  kMediaPacketizerCanPackEmptyEdit = 1 << 5
};


struct MediaPacketizerRequirements {
  OSType              mediaType;              /* media type supported (0 for all)*/
  OSType              dataFormat;             /* data format (e.g., compression) supported (0 for all)*/
  UInt32              capabilityFlags;        /* ability to handle non-standard track characteristics*/
  UInt8               canPackMatrixType;      /* can pack any matrix type up to this (identityMatrixType for identity only)*/
  UInt8               reserved1;
  UInt8               reserved2;
  UInt8               reserved3;
};
typedef struct MediaPacketizerRequirements MediaPacketizerRequirements;
typedef MediaPacketizerRequirements *   MediaPacketizerRequirementsPtr;
struct MediaPacketizerInfo {
  OSType              mediaType;              /* media type supported (0 for all)*/
  OSType              dataFormat;             /* data format (e.g., compression) supported (0 for all)*/
  OSType              vendor;                 /* manufacturer of this packetizer (e.g., 'appl' for Apple)*/
  UInt32              capabilityFlags;        /* ability to handle non-standard track characteristics*/
  UInt8               canPackMatrixType;      /* can pack any matrix type up to this (identityMatrixType for identity only)*/
  UInt8               reserved1;
  UInt8               reserved2;
  UInt8               reserved3;
  long                characteristicCount;
  RTPPayloadCharacteristic  characteristic[1];

                                              /* after the last characteristic, the payload name (defined by the RTPPayloadInfo*/
                                              /* structure) is present. */
};
typedef struct MediaPacketizerInfo      MediaPacketizerInfo;
typedef MediaPacketizerInfo *           MediaPacketizerInfoPtr;
typedef MediaPacketizerInfoPtr *        MediaPacketizerInfoHandle;
#define MediaPacketizerInfoToPayloadInfo(_mpi) ((RTPPayloadInfoPtr)(&((_mpi)->characteristic[(_mpi)->characteristicCount])))
/* MediaPacketizerInfo structs are padded to 32 bits */
enum {
  kMediaPacketizerInfoPadUpToBytes = 4
};

enum {
  kRTPMediaPacketizerInfoRezType = 'pcki'
};


/*
 *  QTSFindMediaPacketizer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSFindMediaPacketizer(
  MediaPacketizerRequirementsPtr   inPacketizerinfo,
  SampleDescriptionHandle          inSampleDescription,
  RTPPayloadSortRequestPtr         inSortInfo,
  QTAtomContainer *                outPacketizerList)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTSFindMediaPacketizerForTrack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSFindMediaPacketizerForTrack(
  Track                      inTrack,
  long                       inSampleDescriptionIndex,
  RTPPayloadSortRequestPtr   inSortInfo,
  QTAtomContainer *          outPacketizerList)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTSFindMediaPacketizerForPayloadID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSFindMediaPacketizerForPayloadID(
  long                       payloadID,
  RTPPayloadSortRequestPtr   inSortInfo,
  QTAtomContainer *          outPacketizerList)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTSFindMediaPacketizerForPayloadName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern OSErr 
QTSFindMediaPacketizerForPayloadName(
  const char *               payloadName,
  RTPPayloadSortRequestPtr   inSortInfo,
  QTAtomContainer *          outPacketizerList)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* flags for RTPMPInitialize*/
enum {
  kRTPMPRealtimeModeFlag        = 0x00000001
};

/* flags for RTPMPSampleDataParams*/
enum {
  kRTPMPSyncSampleFlag          = 0x00000001,
  kRTPMPRespectDurationFlag     = 0x00000002
};

struct RTPMPSampleDataParams {
  UInt32              version;
  UInt32              timeStamp;
  UInt32              duration;               /* 0 = unknown duration*/
  UInt32              playOffset;
  Fixed               playRate;
  SInt32              flags;
  UInt32              sampleDescSeed;
  Handle              sampleDescription;
  RTPMPSampleRef      sampleRef;
  UInt32              dataLength;
  const UInt8 *       data;
  RTPMPDataReleaseUPP  releaseProc;
  void *              refCon;
};
typedef struct RTPMPSampleDataParams    RTPMPSampleDataParams;
/* out flags for idle, RTPMPSetSampleData, and RTPMPFlush*/
enum {
  kRTPMPStillProcessingData     = 0x00000001 /* not done with data you've got*/
};

struct RTPMPPayloadTypeParams {
  UInt32              flags;
  UInt32              payloadNumber;
  short               nameLength;             /* in: size of payloadName buffer (counting null terminator) -- this will be reset to needed length and paramErr returned if too small */
  char *              payloadName;            /* caller must provide buffer */
};
typedef struct RTPMPPayloadTypeParams   RTPMPPayloadTypeParams;
/*-----------------------------------------
    RTP Media Packetizer Info selectors
-----------------------------------------*/
/* info selectors - get only */
enum {
  kRTPMPPayloadTypeInfo         = 'rtpp', /* RTPMPPayloadTypeParams* */
  kRTPMPRTPTimeScaleInfo        = 'rtpt', /* TimeScale* */
  kRTPMPRequiredSampleDescriptionInfo = 'sdsc', /* SampleDescriptionHandle* */
  kRTPMPMinPayloadSize          = 'mins', /* UInt32* in bytes, does not include rtp header; default is 0 */
  kRTPMPMinPacketDuration       = 'mind', /* UInt3* in milliseconds; default is no min required */
  kRTPMPSuggestedRepeatPktCountInfo = 'srpc', /* UInt32* */
  kRTPMPSuggestedRepeatPktSpacingInfo = 'srps', /* UInt32* in milliseconds */
  kRTPMPMaxPartialSampleSizeInfo = 'mpss', /* UInt32* in bytes */
  kRTPMPPreferredBufferDelayInfo = 'prbd', /* UInt32* in milliseconds */
  kRTPMPPayloadNameInfo         = 'name', /* StringPtr */
  kRTPInfo_FormatString         = 'fmtp' /* char **, caller allocates ptr, callee disposes */
};

/*-----------------------------------------
    RTP Media Packetizer Characteristics
-----------------------------------------*/
/* also supports relevant ones in Movies.h and QTSToolbox.h */
enum {
  kRTPMPNoSampleDataRequiredCharacteristic = 'nsdr',
  kRTPMPHasUserSettingsDialogCharacteristic = 'sdlg',
  kRTPMPPrefersReliableTransportCharacteristic = 'rely',
  kRTPMPRequiresOutOfBandDimensionsCharacteristic = 'robd',
  kRTPMPReadsPartialSamplesCharacteristic = 'rpsp'
};

/*-----------------------------------------
    RTP Media Packetizer selectors
-----------------------------------------*/
enum {
  kRTPMPInitializeSelect        = 0x0500,
  kRTPMPPreflightMediaSelect    = 0x0501,
  kRTPMPIdleSelect              = 0x0502,
  kRTPMPSetSampleDataSelect     = 0x0503,
  kRTPMPFlushSelect             = 0x0504,
  kRTPMPResetSelect             = 0x0505,
  kRTPMPSetInfoSelect           = 0x0506,
  kRTPMPGetInfoSelect           = 0x0507,
  kRTPMPSetTimeScaleSelect      = 0x0508,
  kRTPMPGetTimeScaleSelect      = 0x0509,
  kRTPMPSetTimeBaseSelect       = 0x050A,
  kRTPMPGetTimeBaseSelect       = 0x050B,
  kRTPMPHasCharacteristicSelect = 0x050C,
  kRTPMPSetPacketBuilderSelect  = 0x050E,
  kRTPMPGetPacketBuilderSelect  = 0x050F,
  kRTPMPSetMediaTypeSelect      = 0x0510,
  kRTPMPGetMediaTypeSelect      = 0x0511,
  kRTPMPSetMaxPacketSizeSelect  = 0x0512,
  kRTPMPGetMaxPacketSizeSelect  = 0x0513,
  kRTPMPSetMaxPacketDurationSelect = 0x0514,
  kRTPMPGetMaxPacketDurationSelect = 0x0515, /* for export component and apps who want to*/
                                        /* access dialogs for Media-specific settings*/
                                        /* (such as Pure Voice interleave factor)*/
  kRTPMPDoUserDialogSelect      = 0x0516,
  kRTPMPSetSettingsFromAtomContainerAtAtomSelect = 0x0517,
  kRTPMPGetSettingsIntoAtomContainerAtAtomSelect = 0x0518,
  kRTPMPGetSettingsAsTextSelect = 0x0519,
  kRTPMPGetSettingsSelect       = 0x051C,
  kRTPMPSetSettingsSelect       = 0x051D
};

/*-----------------------------------------
    RTP Media Packetizer functions
-----------------------------------------*/

/*
 *  RTPMPInitialize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPInitialize(
  RTPMediaPacketizer   rtpm,
  SInt32               inFlags)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* return noErr if you can handle this media */
/*
 *  RTPMPPreflightMedia()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPPreflightMedia(
  RTPMediaPacketizer        rtpm,
  OSType                    inMediaType,
  SampleDescriptionHandle   inSampleDescription)              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
   do work here if you need to - give up time periodically
   if you're doing time consuming operations
*/
/*
 *  RTPMPIdle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPIdle(
  RTPMediaPacketizer   rtpm,
  SInt32               inFlags,
  SInt32 *             outFlags)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
   caller owns the RTPMPSampleDataParams struct
   media Packetizer must copy any fields of the struct it wants to keep
   media Packetizer must call release proc when done with the data
   you can do the processing work here if it does not take up too
   much cpu time - otherwise do it in idle
*/
/*
 *  RTPMPSetSampleData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPSetSampleData(
  RTPMediaPacketizer             rtpm,
  const RTPMPSampleDataParams *  inSampleData,
  SInt32 *                       outFlags)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
   send everything you have buffered - you will get idles while
   you set the kRTPMPStillProcessingData flag here and in idle
*/
/*
 *  RTPMPFlush()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPFlush(
  RTPMediaPacketizer   rtpm,
  SInt32               inFlags,
  SInt32 *             outFlags)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
   dispose of anything buffered and get rid of state
   do not send the buffered data (because presumably
   there is no connection for you to send on)
   state should be the same as if you were just initialized
*/
/*
 *  RTPMPReset()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPReset(
  RTPMediaPacketizer   rtpm,
  SInt32               inFlags)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*-----------------------------------------
    RTP Media Packetizer get / set functions
-----------------------------------------*/
/*
 *  RTPMPSetInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPSetInfo(
  RTPMediaPacketizer   rtpm,
  OSType               inSelector,
  const void *         ioParams)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPMPGetInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPGetInfo(
  RTPMediaPacketizer   rtpm,
  OSType               inSelector,
  void *               ioParams)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPMPSetTimeScale()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPSetTimeScale(
  RTPMediaPacketizer   rtpm,
  TimeScale            inTimeScale)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPMPGetTimeScale()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPGetTimeScale(
  RTPMediaPacketizer   rtpm,
  TimeScale *          outTimeScale)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPMPSetTimeBase()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPSetTimeBase(
  RTPMediaPacketizer   rtpm,
  TimeBase             inTimeBase)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPMPGetTimeBase()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPGetTimeBase(
  RTPMediaPacketizer   rtpm,
  TimeBase *           outTimeBase)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPMPHasCharacteristic()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPHasCharacteristic(
  RTPMediaPacketizer   rtpm,
  OSType               inSelector,
  Boolean *            outHasIt)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPMPSetPacketBuilder()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPSetPacketBuilder(
  RTPMediaPacketizer   rtpm,
  ComponentInstance    inPacketBuilder)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPMPGetPacketBuilder()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPGetPacketBuilder(
  RTPMediaPacketizer   rtpm,
  ComponentInstance *  outPacketBuilder)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPMPSetMediaType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPSetMediaType(
  RTPMediaPacketizer   rtpm,
  OSType               inMediaType)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPMPGetMediaType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPGetMediaType(
  RTPMediaPacketizer   rtpm,
  OSType *             outMediaType)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* size is in bytes*/
/*
 *  RTPMPSetMaxPacketSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPSetMaxPacketSize(
  RTPMediaPacketizer   rtpm,
  UInt32               inMaxPacketSize)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPMPGetMaxPacketSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPGetMaxPacketSize(
  RTPMediaPacketizer   rtpm,
  UInt32 *             outMaxPacketSize)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* duration is in milliseconds*/
/*
 *  RTPMPSetMaxPacketDuration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPSetMaxPacketDuration(
  RTPMediaPacketizer   rtpm,
  UInt32               inMaxPacketDuration)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPMPGetMaxPacketDuration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPGetMaxPacketDuration(
  RTPMediaPacketizer   rtpm,
  UInt32 *             outMaxPacketDuration)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPMPDoUserDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPDoUserDialog(
  RTPMediaPacketizer   rtpm,
  ModalFilterUPP       inFilterUPP,
  Boolean *            canceled)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPMPSetSettingsFromAtomContainerAtAtom()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPSetSettingsFromAtomContainerAtAtom(
  RTPMediaPacketizer   rtpm,
  QTAtomContainer      inContainer,
  QTAtom               inParentAtom)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPMPGetSettingsIntoAtomContainerAtAtom()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPGetSettingsIntoAtomContainerAtAtom(
  RTPMediaPacketizer   rtpm,
  QTAtomContainer      inOutContainer,
  QTAtom               inParentAtom)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPMPGetSettingsAsText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPMPGetSettingsAsText(
  RTPMediaPacketizer   rtpm,
  Handle *             text)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  RTPMPGetSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 *    Windows:          in QTSClient.lib 5.0 and later
 */
extern ComponentResult 
RTPMPGetSettings(
  RTPMediaPacketizer   rtpm,
  QTAtomContainer *    outSettings,
  SInt32               inFlags)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPMPSetSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 *    Windows:          in QTSClient.lib 5.0 and later
 */
extern ComponentResult 
RTPMPSetSettings(
  RTPMediaPacketizer   rtpm,
  QTAtomSpecPtr        inSettings,
  SInt32               inFlags)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*============================================================================
        RTP Packet Builder
============================================================================*/
enum {
  kRTPPacketBuilderType         = 'rtpb'
};


typedef ComponentInstance               RTPPacketBuilder;
typedef struct OpaqueRTPPacketGroupRef*  RTPPacketGroupRef;
typedef struct OpaqueRTPPacketRef*      RTPPacketRef;
typedef struct OpaqueRTPPacketRepeatedDataRef*  RTPPacketRepeatedDataRef;
/* flags for RTPPBBegin/EndPacket, RTPPBBegin/EndPacketGroup*/
enum {
  kRTPPBSetMarkerFlag           = 0x00000001,
  kRTPPBRepeatPacketFlag        = 0x00000002,
  kRTPPBSyncSampleFlag          = 0x00010000,
  kRTPPBBFrameFlag              = 0x00020000,
  kRTPPBDontSendFlag            = 0x10000000 /* when set in EndPacketGroup, will not add group*/
};

enum {
  kRTPPBUnknownPacketMediaDataLength = 0
};

/* flags for RTPPBGetSampleData*/
enum {
  kRTPPBEndOfDataFlag           = 0x00000001
};


typedef CALLBACK_API( void , RTPPBCallbackProcPtr )(OSType inSelector, void *ioParams, void *inRefCon);
typedef STACK_UPP_TYPE(RTPPBCallbackProcPtr)                    RTPPBCallbackUPP;
/*-----------------------------------------
    RTP Packet Builder selectors
-----------------------------------------*/
enum {
  kRTPPBBeginPacketGroupSelect  = 0x0500,
  kRTPPBEndPacketGroupSelect    = 0x0501,
  kRTPPBBeginPacketSelect       = 0x0502,
  kRTPPBEndPacketSelect         = 0x0503,
  kRTPPBAddPacketLiteralDataSelect = 0x0504,
  kRTPPBAddPacketSampleDataSelect = 0x0505,
  kRTPPBAddPacketRepeatedDataSelect = 0x0506,
  kRTPPBReleaseRepeatedDataSelect = 0x0507,
  kRTPPBSetPacketSequenceNumberSelect = 0x0508,
  kRTPPBGetPacketSequenceNumberSelect = 0x0509,
  kRTPPBSetCallbackSelect       = 0x050A,
  kRTPPBGetCallbackSelect       = 0x050B,
  kRTPPBSetInfoSelect           = 0x050C,
  kRTPPBGetInfoSelect           = 0x050D,
  kRTPPBSetPacketTimeStampOffsetSelect = 0x050E,
  kRTPPBGetPacketTimeStampOffsetSelect = 0x050F,
  kRTPPBAddPacketSampleData64Select = 0x0510,
  kRTPPBGetSampleDataSelect     = 0x0511,
  kRTPPBAddRepeatPacketSelect   = 0x0512
};

/*-----------------------------------------
    RTP Packet Builder functions
-----------------------------------------*/
/*
 *  RTPPBBeginPacketGroup()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPPBBeginPacketGroup(
  RTPPacketBuilder     rtpb,
  SInt32               inFlags,
  UInt32               inTimeStamp,
  RTPPacketGroupRef *  outPacketGroup)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPPBEndPacketGroup()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPPBEndPacketGroup(
  RTPPacketBuilder    rtpb,
  SInt32              inFlags,
  RTPPacketGroupRef   inPacketGroup)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPPBBeginPacket()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPPBBeginPacket(
  RTPPacketBuilder    rtpb,
  SInt32              inFlags,
  RTPPacketGroupRef   inPacketGroup,
  UInt32              inPacketMediaDataLength,
  RTPPacketRef *      outPacket)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPPBEndPacket()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPPBEndPacket(
  RTPPacketBuilder    rtpb,
  SInt32              inFlags,
  RTPPacketGroupRef   inPacketGroup,
  RTPPacketRef        inPacket,
  UInt32              inTransmissionTimeOffset,
  UInt32              inDuration)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
   non-NULL RTPPacketRepeatedDataRef means this data will be repeated later
   pb must return a repeated data ref
*/
/*
 *  RTPPBAddPacketLiteralData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPPBAddPacketLiteralData(
  RTPPacketBuilder            rtpb,
  SInt32                      inFlags,
  RTPPacketGroupRef           inPacketGroup,
  RTPPacketRef                inPacket,
  UInt8 *                     inData,
  UInt32                      inDataLength,
  RTPPacketRepeatedDataRef *  outDataRef)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
   non-NULL RTPPacketRepeatedDataRef means this data will be repeated later
   pb must return a repeated data ref
*/
/*
 *  RTPPBAddPacketSampleData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPPBAddPacketSampleData(
  RTPPacketBuilder            rtpb,
  SInt32                      inFlags,
  RTPPacketGroupRef           inPacketGroup,
  RTPPacketRef                inPacket,
  RTPMPSampleDataParams *     inSampleDataParams,
  UInt32                      inSampleOffset,
  UInt32                      inSampleDataLength,
  RTPPacketRepeatedDataRef *  outDataRef)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
   non-NULL RTPPacketRepeatedDataRef means this data will be repeated later
   pb must return a repeated data ref
*/
/*
 *  RTPPBAddPacketSampleData64()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 *    Windows:          in QTSClient.lib 5.0 and later
 */
extern ComponentResult 
RTPPBAddPacketSampleData64(
  RTPPacketBuilder            rtpb,
  SInt32                      inFlags,
  RTPPacketGroupRef           inPacketGroup,
  RTPPacketRef                inPacket,
  RTPMPSampleDataParams *     inSampleDataParams,
  const UInt64 *              inSampleOffset,
  UInt32                      inSampleDataLength,
  RTPPacketRepeatedDataRef *  outDataRef)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
   call to add the repeated data using the ref you got from
   RTPPBAddPacketLiteralData or RTPPBAddPacketSampleData
*/
/*
 *  RTPPBAddPacketRepeatedData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPPBAddPacketRepeatedData(
  RTPPacketBuilder           rtpb,
  SInt32                     inFlags,
  RTPPacketGroupRef          inPacketGroup,
  RTPPacketRef               inPacket,
  RTPPacketRepeatedDataRef   inDataRef)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* call when done with repeated data*/
/*
 *  RTPPBReleaseRepeatedData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPPBReleaseRepeatedData(
  RTPPacketBuilder           rtpb,
  RTPPacketRepeatedDataRef   inDataRef)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
   seq number is just relative seq number
   don't call if you don't care when seq # is used
*/
/*
 *  RTPPBSetPacketSequenceNumber()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPPBSetPacketSequenceNumber(
  RTPPacketBuilder    rtpb,
  SInt32              inFlags,
  RTPPacketGroupRef   inPacketGroup,
  RTPPacketRef        inPacket,
  UInt32              inSequenceNumber)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPPBGetPacketSequenceNumber()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPPBGetPacketSequenceNumber(
  RTPPacketBuilder    rtpb,
  SInt32              inFlags,
  RTPPacketGroupRef   inPacketGroup,
  RTPPacketRef        inPacket,
  UInt32 *            outSequenceNumber)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPPBSetPacketTimeStampOffset()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 *    Windows:          in QTSClient.lib 5.0 and later
 */
extern ComponentResult 
RTPPBSetPacketTimeStampOffset(
  RTPPacketBuilder    rtpb,
  SInt32              inFlags,
  RTPPacketGroupRef   inPacketGroup,
  RTPPacketRef        inPacket,
  SInt32              inTimeStampOffset)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPPBGetPacketTimeStampOffset()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 *    Windows:          in QTSClient.lib 5.0 and later
 */
extern ComponentResult 
RTPPBGetPacketTimeStampOffset(
  RTPPacketBuilder    rtpb,
  SInt32              inFlags,
  RTPPacketGroupRef   inPacketGroup,
  RTPPacketRef        inPacket,
  SInt32 *            outTimeStampOffset)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPPBAddRepeatPacket()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 *    Windows:          in QTSClient.lib 5.0 and later
 */
extern ComponentResult 
RTPPBAddRepeatPacket(
  RTPPacketBuilder    rtpb,
  SInt32              inFlags,
  RTPPacketGroupRef   inPacketGroup,
  RTPPacketRef        inPacket,
  TimeValue           inTransmissionOffset,
  UInt32              inSequenceNumber)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
   used for communicating with the caller of the media packetizers if needed
   NOT used for communicating with the media packetizers themselves
*/
/*
 *  RTPPBSetCallback()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPPBSetCallback(
  RTPPacketBuilder   rtpb,
  RTPPBCallbackUPP   inCallback,
  void *             inRefCon)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPPBGetCallback()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPPBGetCallback(
  RTPPacketBuilder    rtpb,
  RTPPBCallbackUPP *  outCallback,
  void **             outRefCon)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPPBSetInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPPBSetInfo(
  RTPPacketBuilder   rtpb,
  OSType             inSelector,
  void *             ioParams)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPPBGetInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QTStreamLib 4.0 and later
 *    Windows:          in QTSClient.lib 4.0 and later
 */
extern ComponentResult 
RTPPBGetInfo(
  RTPPacketBuilder   rtpb,
  OSType             inSelector,
  void *             ioParams)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RTPPBGetSampleData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QTStreamLib 5.0 and later
 *    Windows:          in QTSClient.lib 5.0 and later
 */
extern ComponentResult 
RTPPBGetSampleData(
  RTPPacketBuilder         rtpb,
  RTPMPSampleDataParams *  inParams,
  const UInt64 *           inStartOffset,
  UInt8 *                  outDataBuffer,
  UInt32                   inBytesToRead,
  UInt32 *                 outBytesRead,
  SInt32 *                 outFlags)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* UPP call backs */
/*
 *  NewRTPMPDataReleaseUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern RTPMPDataReleaseUPP
NewRTPMPDataReleaseUPP(RTPMPDataReleaseProcPtr userRoutine)   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewRTPPBCallbackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern RTPPBCallbackUPP
NewRTPPBCallbackUPP(RTPPBCallbackProcPtr userRoutine)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeRTPMPDataReleaseUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeRTPMPDataReleaseUPP(RTPMPDataReleaseUPP userUPP)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeRTPPBCallbackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeRTPPBCallbackUPP(RTPPBCallbackUPP userUPP)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeRTPMPDataReleaseUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeRTPMPDataReleaseUPP(
  UInt8 *              inData,
  void *               inRefCon,
  RTPMPDataReleaseUPP  userUPP)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeRTPPBCallbackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeRTPPBCallbackUPP(
  OSType            inSelector,
  void *            ioParams,
  void *            inRefCon,
  RTPPBCallbackUPP  userUPP)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

#if __MACH__
  #ifdef __cplusplus
    inline RTPMPDataReleaseUPP                                  NewRTPMPDataReleaseUPP(RTPMPDataReleaseProcPtr userRoutine) { return userRoutine; }
    inline RTPPBCallbackUPP                                     NewRTPPBCallbackUPP(RTPPBCallbackProcPtr userRoutine) { return userRoutine; }
    inline void                                                 DisposeRTPMPDataReleaseUPP(RTPMPDataReleaseUPP) { }
    inline void                                                 DisposeRTPPBCallbackUPP(RTPPBCallbackUPP) { }
    inline void                                                 InvokeRTPMPDataReleaseUPP(UInt8 * inData, void * inRefCon, RTPMPDataReleaseUPP userUPP) { (*userUPP)(inData, inRefCon); }
    inline void                                                 InvokeRTPPBCallbackUPP(OSType inSelector, void * ioParams, void * inRefCon, RTPPBCallbackUPP userUPP) { (*userUPP)(inSelector, ioParams, inRefCon); }
  #else
    #define NewRTPMPDataReleaseUPP(userRoutine)                 ((RTPMPDataReleaseUPP)userRoutine)
    #define NewRTPPBCallbackUPP(userRoutine)                    ((RTPPBCallbackUPP)userRoutine)
    #define DisposeRTPMPDataReleaseUPP(userUPP)
    #define DisposeRTPPBCallbackUPP(userUPP)
    #define InvokeRTPMPDataReleaseUPP(inData, inRefCon, userUPP) (*userUPP)(inData, inRefCon)
    #define InvokeRTPPBCallbackUPP(inSelector, ioParams, inRefCon, userUPP) (*userUPP)(inSelector, ioParams, inRefCon)
  #endif
#endif


#endif // !__LP64__



#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* __QTSTREAMINGCOMPONENTS__ */

