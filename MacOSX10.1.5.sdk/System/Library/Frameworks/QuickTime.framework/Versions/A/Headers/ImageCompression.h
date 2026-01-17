/*
     File:       QuickTime/ImageCompression.h
 
     Contains:   QuickTime Image Compression Interfaces.
 
     Version:    QuickTime-142~1
 
     Copyright:  © 1990-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __IMAGECOMPRESSION__
#define __IMAGECOMPRESSION__

#ifndef __CARBON__
#include <Carbon/Carbon.h>
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

struct MatrixRecord {
  Fixed               matrix[3][3];
};
typedef struct MatrixRecord             MatrixRecord;
typedef MatrixRecord *                  MatrixRecordPtr;
enum {
  kRawCodecType                 = 'raw ',
  kCinepakCodecType             = 'cvid',
  kGraphicsCodecType            = 'smc ',
  kAnimationCodecType           = 'rle ',
  kVideoCodecType               = 'rpza',
  kComponentVideoCodecType      = 'yuv2',
  kJPEGCodecType                = 'jpeg',
  kMotionJPEGACodecType         = 'mjpa',
  kMotionJPEGBCodecType         = 'mjpb',
  kSGICodecType                 = '.SGI',
  kPlanarRGBCodecType           = '8BPS',
  kMacPaintCodecType            = 'PNTG',
  kGIFCodecType                 = 'gif ',
  kPhotoCDCodecType             = 'kpcd',
  kQuickDrawGXCodecType         = 'qdgx',
  kAVRJPEGCodecType             = 'avr ',
  kOpenDMLJPEGCodecType         = 'dmb1',
  kBMPCodecType                 = 'WRLE',
  kWindowsRawCodecType          = 'WRAW',
  kVectorCodecType              = 'path',
  kQuickDrawCodecType           = 'qdrw',
  kWaterRippleCodecType         = 'ripl',
  kFireCodecType                = 'fire',
  kCloudCodecType               = 'clou',
  kH261CodecType                = 'h261',
  kH263CodecType                = 'h263',
  kDVCNTSCCodecType             = 'dvc ',
  kDVCPALCodecType              = 'dvcp',
  kDVCProNTSCCodecType          = 'dvpn',
  kDVCProPALCodecType           = 'dvpp',
  kBaseCodecType                = 'base',
  kFLCCodecType                 = 'flic',
  kTargaCodecType               = 'tga ',
  kPNGCodecType                 = 'png ',
  kTIFFCodecType                = 'tiff', /*    NOTE: despite what might seem obvious from the two constants*/
                                        /*    below and their names, they really are correct. 'yuvu' really */
                                        /*    does mean signed, and 'yuvs' really does mean unsigned. Really. */
  kComponentVideoSigned         = 'yuvu',
  kComponentVideoUnsigned       = 'yuvs',
  kCMYKCodecType                = 'cmyk',
  kMicrosoftVideo1CodecType     = 'msvc',
  kSorensonCodecType            = 'SVQ1',
  kSorenson3CodecType           = 'SVQ3', /* available in QuickTime 5 and later*/
  kIndeo4CodecType              = 'IV41',
  k64ARGBCodecType              = 'b64a',
  k48RGBCodecType               = 'b48r',
  k32AlphaGrayCodecType         = 'b32a',
  k16GrayCodecType              = 'b16g',
  kMpegYUV420CodecType          = 'myuv',
  kYUV420CodecType              = 'y420',
  kSorensonYUV9CodecType        = 'syv9',
  k422YpCbCr8CodecType          = '2vuy', /* Component Y'CbCr 8-bit 4:2:2  */
  k444YpCbCr8CodecType          = 'v308', /* Component Y'CbCr 8-bit 4:4:4  */
  k4444YpCbCrA8CodecType        = 'v408', /* Component Y'CbCrA 8-bit 4:4:4:4 */
  k422YpCbCr16CodecType         = 'v216', /* Component Y'CbCr 10,12,14,16-bit 4:2:2*/
  k422YpCbCr10CodecType         = 'v210', /* Component Y'CbCr 10-bit 4:2:2 */
  k444YpCbCr10CodecType         = 'v410', /* Component Y'CbCr 10-bit 4:4:4 */
  k4444YpCbCrA8RCodecType       = 'r408' /* Component Y'CbCrA 8-bit 4:4:4:4, rendering format. full range alpha, zero biased yuv*/
};


/* one source effects */
enum {
  kBlurImageFilterType          = 'blur',
  kSharpenImageFilterType       = 'shrp',
  kEdgeDetectImageFilterType    = 'edge',
  kEmbossImageFilterType        = 'embs',
  kConvolveImageFilterType      = 'genk',
  kAlphaGainImageFilterType     = 'gain',
  kRGBColorBalanceImageFilterType = 'rgbb',
  kHSLColorBalanceImageFilterType = 'hslb',
  kColorSyncImageFilterType     = 'sync',
  kFilmNoiseImageFilterType     = 'fmns',
  kSolarizeImageFilterType      = 'solr',
  kColorTintImageFilterType     = 'tint',
  kLensFlareImageFilterType     = 'lens',
  kBrightnessContrastImageFilterType = 'brco'
};

/* two source effects */
enum {
  kAlphaCompositorTransitionType = 'blnd',
  kCrossFadeTransitionType      = 'dslv',
  kChromaKeyTransitionType      = 'ckey',
  kImplodeTransitionType        = 'mplo',
  kExplodeTransitionType        = 'xplo',
  kGradientTransitionType       = 'matt',
  kPushTransitionType           = 'push',
  kSlideTransitionType          = 'slid',
  kWipeTransitionType           = 'smpt',
  kIrisTransitionType           = 'smp2',
  kRadialTransitionType         = 'smp3',
  kMatrixTransitionType         = 'smp4',
  kZoomTransitionType           = 'zoom'
};

/* three source effects */
enum {
  kTravellingMatteEffectType    = 'trav'
};

/* These are the bits that are set in the Component flags, and also in the codecInfo struct. */
enum {
  codecInfoDoes1                = (1L << 0), /* codec can work with 1-bit pixels */
  codecInfoDoes2                = (1L << 1), /* codec can work with 2-bit pixels */
  codecInfoDoes4                = (1L << 2), /* codec can work with 4-bit pixels */
  codecInfoDoes8                = (1L << 3), /* codec can work with 8-bit pixels */
  codecInfoDoes16               = (1L << 4), /* codec can work with 16-bit pixels */
  codecInfoDoes32               = (1L << 5), /* codec can work with 32-bit pixels */
  codecInfoDoesDither           = (1L << 6), /* codec can do ditherMode */
  codecInfoDoesStretch          = (1L << 7), /* codec can stretch to arbitrary sizes */
  codecInfoDoesShrink           = (1L << 8), /* codec can shrink to arbitrary sizes */
  codecInfoDoesMask             = (1L << 9), /* codec can mask to clipping regions */
  codecInfoDoesTemporal         = (1L << 10), /* codec can handle temporal redundancy */
  codecInfoDoesDouble           = (1L << 11), /* codec can stretch to double size exactly */
  codecInfoDoesQuad             = (1L << 12), /* codec can stretch to quadruple size exactly */
  codecInfoDoesHalf             = (1L << 13), /* codec can shrink to half size */
  codecInfoDoesQuarter          = (1L << 14), /* codec can shrink to quarter size */
  codecInfoDoesRotate           = (1L << 15), /* codec can rotate on decompress */
  codecInfoDoesHorizFlip        = (1L << 16), /* codec can flip horizontally on decompress */
  codecInfoDoesVertFlip         = (1L << 17), /* codec can flip vertically on decompress */
  codecInfoHasEffectParameterList = (1L << 18), /* codec implements get effects parameter list call, once was codecInfoDoesSkew */
  codecInfoDoesBlend            = (1L << 19), /* codec can blend on decompress */
  codecInfoDoesWarp             = (1L << 20), /* codec can warp arbitrarily on decompress */
  codecInfoDoesRecompress       = (1L << 21), /* codec can recompress image without accumulating errors */
  codecInfoDoesSpool            = (1L << 22), /* codec can spool image data */
  codecInfoDoesRateConstrain    = (1L << 23) /* codec can data rate constrain */
};


enum {
  codecInfoDepth1               = (1L << 0), /* compressed data at 1 bpp depth available */
  codecInfoDepth2               = (1L << 1), /* compressed data at 2 bpp depth available */
  codecInfoDepth4               = (1L << 2), /* compressed data at 4 bpp depth available */
  codecInfoDepth8               = (1L << 3), /* compressed data at 8 bpp depth available */
  codecInfoDepth16              = (1L << 4), /* compressed data at 16 bpp depth available */
  codecInfoDepth32              = (1L << 5), /* compressed data at 32 bpp depth available */
  codecInfoDepth24              = (1L << 6), /* compressed data at 24 bpp depth available */
  codecInfoDepth33              = (1L << 7), /* compressed data at 1 bpp monochrome depth  available */
  codecInfoDepth34              = (1L << 8), /* compressed data at 2 bpp grayscale depth available */
  codecInfoDepth36              = (1L << 9), /* compressed data at 4 bpp grayscale depth available */
  codecInfoDepth40              = (1L << 10), /* compressed data at 8 bpp grayscale depth available */
  codecInfoStoresClut           = (1L << 11), /* compressed data can have custom cluts */
  codecInfoDoesLossless         = (1L << 12), /* compressed data can be stored in lossless format */
  codecInfoSequenceSensitive    = (1L << 13) /* compressed data is sensitive to out of sequence decoding */
};


/* input sequence flags*/
enum {
  codecFlagUseImageBuffer       = (1L << 0), /* decompress*/
  codecFlagUseScreenBuffer      = (1L << 1), /* decompress*/
  codecFlagUpdatePrevious       = (1L << 2), /* compress*/
  codecFlagNoScreenUpdate       = (1L << 3), /* decompress*/
  codecFlagWasCompressed        = (1L << 4), /* compress*/
  codecFlagDontOffscreen        = (1L << 5), /* decompress*/
  codecFlagUpdatePreviousComp   = (1L << 6), /* compress*/
  codecFlagForceKeyFrame        = (1L << 7), /* compress*/
  codecFlagOnlyScreenUpdate     = (1L << 8), /* decompress*/
  codecFlagLiveGrab             = (1L << 9), /* compress*/
  codecFlagDiffFrame            = (1L << 9), /* decompress*/
  codecFlagDontUseNewImageBuffer = (1L << 10), /* decompress*/
  codecFlagInterlaceUpdate      = (1L << 11), /* decompress*/
  codecFlagCatchUpDiff          = (1L << 12), /* decompress*/
  codecFlagSupportDisable       = (1L << 13), /* decompress*/
  codecFlagReenable             = (1L << 14) /* decompress*/
};


/* output sequence flags*/
enum {
  codecFlagOutUpdateOnNextIdle  = (1L << 9),
  codecFlagOutUpdateOnDataSourceChange = (1L << 10),
  codecFlagSequenceSensitive    = (1L << 11),
  codecFlagOutUpdateOnTimeChange = (1L << 12),
  codecFlagImageBufferNotSourceImage = (1L << 13),
  codecFlagUsedNewImageBuffer   = (1L << 14),
  codecFlagUsedImageBuffer      = (1L << 15)
};



enum {
                                        /* The minimum data size for spooling in or out data */
  codecMinimumDataSize          = 32768L
};



enum {
  compressorComponentType       = 'imco', /* the type for "Components" which compress images */
  decompressorComponentType     = 'imdc' /* the type for "Components" which decompress images */
};

typedef Component                       CompressorComponent;
typedef Component                       DecompressorComponent;
typedef Component                       CodecComponent;
#define anyCodec                ((CodecComponent)0)
#define bestSpeedCodec          ((CodecComponent)-1)
#define bestFidelityCodec       ((CodecComponent)-2)
#define bestCompressionCodec    ((CodecComponent)-3)
typedef OSType                          CodecType;
typedef unsigned short                  CodecFlags;
typedef unsigned long                   CodecQ;
enum {
  codecLosslessQuality          = 0x00000400,
  codecMaxQuality               = 0x000003FF,
  codecMinQuality               = 0x00000000,
  codecLowQuality               = 0x00000100,
  codecNormalQuality            = 0x00000200,
  codecHighQuality              = 0x00000300
};

enum {
  codecLockBitsShieldCursor     = (1 << 0) /* shield cursor */
};

enum {
  codecCompletionSource         = (1 << 0), /* asynchronous codec is done with source data */
  codecCompletionDest           = (1 << 1), /* asynchronous codec is done with destination data */
  codecCompletionDontUnshield   = (1 << 2), /* on dest complete don't unshield cursor */
  codecCompletionWentOffscreen  = (1 << 3), /* codec used offscreen buffer */
  codecCompletionUnlockBits     = (1 << 4), /* on dest complete, call ICMSequenceUnlockBits */
  codecCompletionForceChainFlush = (1 << 5), /* ICM needs to flush the whole chain */
  codecCompletionDropped        = (1 << 6) /* codec decided to drop this frame */
};

enum {
  codecProgressOpen             = 0,
  codecProgressUpdatePercent    = 1,
  codecProgressClose            = 2
};

typedef CALLBACK_API( OSErr , ICMDataProcPtr )(Ptr *dataP, long bytesNeeded, long refcon);
typedef CALLBACK_API( OSErr , ICMFlushProcPtr )(Ptr data, long bytesAdded, long refcon);
typedef CALLBACK_API( void , ICMCompletionProcPtr )(OSErr result, short flags, long refcon);
typedef CALLBACK_API( OSErr , ICMProgressProcPtr )(short message, Fixed completeness, long refcon);
typedef CALLBACK_API( void , StdPixProcPtr )(PixMap *src, Rect *srcRect, MatrixRecord *matrix, short mode, RgnHandle mask, PixMap *matte, Rect *matteRect, short flags);
typedef CALLBACK_API( void , QDPixProcPtr )(PixMap *src, Rect *srcRect, MatrixRecord *matrix, short mode, RgnHandle mask, PixMap *matte, Rect *matteRect, short flags);
typedef CALLBACK_API( void , ICMAlignmentProcPtr )(Rect *rp, long refcon);
typedef CALLBACK_API( void , ICMCursorShieldedProcPtr )(const Rect *r, void *refcon, long flags);
typedef CALLBACK_API( void , ICMMemoryDisposedProcPtr )(Ptr memoryBlock, void *refcon);
typedef void *                          ICMCursorNotify;
typedef CALLBACK_API( OSErr , ICMConvertDataFormatProcPtr )(void *refCon, long flags, Handle desiredFormat, Handle sourceDataFormat, void *srcData, long srcDataSize, void **dstData, long *dstDataSize);
typedef STACK_UPP_TYPE(ICMDataProcPtr)                          ICMDataUPP;
typedef STACK_UPP_TYPE(ICMFlushProcPtr)                         ICMFlushUPP;
typedef STACK_UPP_TYPE(ICMCompletionProcPtr)                    ICMCompletionUPP;
typedef STACK_UPP_TYPE(ICMProgressProcPtr)                      ICMProgressUPP;
typedef STACK_UPP_TYPE(StdPixProcPtr)                           StdPixUPP;
typedef STACK_UPP_TYPE(QDPixProcPtr)                            QDPixUPP;
typedef STACK_UPP_TYPE(ICMAlignmentProcPtr)                     ICMAlignmentUPP;
typedef STACK_UPP_TYPE(ICMCursorShieldedProcPtr)                ICMCursorShieldedUPP;
typedef STACK_UPP_TYPE(ICMMemoryDisposedProcPtr)                ICMMemoryDisposedUPP;
typedef STACK_UPP_TYPE(ICMConvertDataFormatProcPtr)             ICMConvertDataFormatUPP;
typedef long                            ImageSequence;
typedef long                            ImageSequenceDataSource;
typedef long                            ImageTranscodeSequence;
typedef long                            ImageFieldSequence;
struct ICMProgressProcRecord {
  ICMProgressUPP      progressProc;
  long                progressRefCon;
};
typedef struct ICMProgressProcRecord    ICMProgressProcRecord;
typedef ICMProgressProcRecord *         ICMProgressProcRecordPtr;
struct ICMCompletionProcRecord {
  ICMCompletionUPP    completionProc;
  long                completionRefCon;
};
typedef struct ICMCompletionProcRecord  ICMCompletionProcRecord;
typedef ICMCompletionProcRecord *       ICMCompletionProcRecordPtr;
struct ICMDataProcRecord {
  ICMDataUPP          dataProc;
  long                dataRefCon;
};
typedef struct ICMDataProcRecord        ICMDataProcRecord;
typedef ICMDataProcRecord *             ICMDataProcRecordPtr;
struct ICMFlushProcRecord {
  ICMFlushUPP         flushProc;
  long                flushRefCon;
};
typedef struct ICMFlushProcRecord       ICMFlushProcRecord;
typedef ICMFlushProcRecord *            ICMFlushProcRecordPtr;
struct ICMAlignmentProcRecord {
  ICMAlignmentUPP     alignmentProc;
  long                alignmentRefCon;
};
typedef struct ICMAlignmentProcRecord   ICMAlignmentProcRecord;
typedef ICMAlignmentProcRecord *        ICMAlignmentProcRecordPtr;
struct DataRateParams {
  long                dataRate;
  long                dataOverrun;
  long                frameDuration;
  long                keyFrameRate;
  CodecQ              minSpatialQuality;
  CodecQ              minTemporalQuality;
};
typedef struct DataRateParams           DataRateParams;
typedef DataRateParams *                DataRateParamsPtr;
struct ImageDescription {
  long                idSize;                 /* total size of ImageDescription including extra data ( CLUTs and other per sequence data ) */
  CodecType           cType;                  /* what kind of codec compressed this data */
  long                resvd1;                 /* reserved for Apple use */
  short               resvd2;                 /* reserved for Apple use */
  short               dataRefIndex;           /* set to zero  */
  short               version;                /* which version is this data */
  short               revisionLevel;          /* what version of that codec did this */
  long                vendor;                 /* whose  codec compressed this data */
  CodecQ              temporalQuality;        /* what was the temporal quality factor  */
  CodecQ              spatialQuality;         /* what was the spatial quality factor */
  short               width;                  /* how many pixels wide is this data */
  short               height;                 /* how many pixels high is this data */
  Fixed               hRes;                   /* horizontal resolution */
  Fixed               vRes;                   /* vertical resolution */
  long                dataSize;               /* if known, the size of data for this image descriptor */
  short               frameCount;             /* number of frames this description applies to */
  Str31               name;                   /* name of codec ( in case not installed )  */
  short               depth;                  /* what depth is this data (1-32) or ( 33-40 grayscale ) */
  short               clutID;                 /* clut id or if 0 clut follows  or -1 if no clut */
};
typedef struct ImageDescription         ImageDescription;
typedef ImageDescription *              ImageDescriptionPtr;
typedef ImageDescriptionPtr *           ImageDescriptionHandle;
struct CodecInfo {
  Str31               typeName;               /* name of the codec type i.e.: 'Apple Image Compression' */
  short               version;                /* version of the codec data that this codec knows about */
  short               revisionLevel;          /* revision level of this codec i.e: 0x00010001 (1.0.1) */
  long                vendor;                 /* Maker of this codec i.e: 'appl' */
  long                decompressFlags;        /* codecInfo flags for decompression capabilities */
  long                compressFlags;          /* codecInfo flags for compression capabilities */
  long                formatFlags;            /* codecInfo flags for compression format details */
  UInt8               compressionAccuracy;    /* measure (1-255) of accuracy of this codec for compress (0 if unknown) */
  UInt8               decompressionAccuracy;  /* measure (1-255) of accuracy of this codec for decompress (0 if unknown) */
  unsigned short      compressionSpeed;       /* ( millisecs for compressing 320x240 on base mac II) (0 if unknown)  */
  unsigned short      decompressionSpeed;     /* ( millisecs for decompressing 320x240 on mac II)(0 if unknown)  */
  UInt8               compressionLevel;       /* measure (1-255) of compression level of this codec (0 if unknown)  */
  UInt8               resvd;                  /* pad */
  short               minimumHeight;          /* minimum height of image (block size) */
  short               minimumWidth;           /* minimum width of image (block size) */
  short               decompressPipelineLatency; /* in milliseconds ( for asynchronous codecs ) */
  short               compressPipelineLatency; /* in milliseconds ( for asynchronous codecs ) */
  long                privateData;
};
typedef struct CodecInfo                CodecInfo;
struct CodecNameSpec {
  CodecComponent      codec;
  CodecType           cType;
  Str31               typeName;
  Handle              name;
};
typedef struct CodecNameSpec            CodecNameSpec;
struct CodecNameSpecList {
  short               count;
  CodecNameSpec       list[1];
};
typedef struct CodecNameSpecList        CodecNameSpecList;
typedef CodecNameSpecList *             CodecNameSpecListPtr;
enum {
  defaultDither                 = 0,
  forceDither                   = 1,
  suppressDither                = 2,
  useColorMatching              = 4
};

enum {
  callStdBits                   = 1,
  callOldBits                   = 2,
  noDefaultOpcodes              = 4
};

enum {
  graphicsModeStraightAlpha     = 256,
  graphicsModePreWhiteAlpha     = 257,
  graphicsModePreBlackAlpha     = 258,
  graphicsModeComposition       = 259,
  graphicsModeStraightAlphaBlend = 260,
  graphicsModePreMulColorAlpha  = 261
};

enum {
  evenField1ToEvenFieldOut      = 1 << 0,
  evenField1ToOddFieldOut       = 1 << 1,
  oddField1ToEvenFieldOut       = 1 << 2,
  oddField1ToOddFieldOut        = 1 << 3,
  evenField2ToEvenFieldOut      = 1 << 4,
  evenField2ToOddFieldOut       = 1 << 5,
  oddField2ToEvenFieldOut       = 1 << 6,
  oddField2ToOddFieldOut        = 1 << 7
};

enum {
  icmFrameTimeHasVirtualStartTimeAndDuration = 1 << 0
};

struct ICMFrameTimeRecord {
  wide                value;                  /* frame time*/
  long                scale;                  /* timescale of value/duration fields*/
  void *              base;                   /* timebase*/

  long                duration;               /* duration frame is to be displayed (0 if unknown)*/
  Fixed               rate;                   /* rate of timebase relative to wall-time*/

  long                recordSize;             /* total number of bytes in ICMFrameTimeRecord*/

  long                frameNumber;            /* number of frame, zero if not known*/

  long                flags;

  wide                virtualStartTime;       /* conceptual start time*/
  long                virtualDuration;        /* conceptual duration*/
};
typedef struct ICMFrameTimeRecord       ICMFrameTimeRecord;
typedef ICMFrameTimeRecord *            ICMFrameTimePtr;
/*
 *  NewICMDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ICMDataUPP
NewICMDataUPP(ICMDataProcPtr userRoutine);

/*
 *  NewICMFlushUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ICMFlushUPP
NewICMFlushUPP(ICMFlushProcPtr userRoutine);

/*
 *  NewICMCompletionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ICMCompletionUPP
NewICMCompletionUPP(ICMCompletionProcPtr userRoutine);

/*
 *  NewICMProgressUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ICMProgressUPP
NewICMProgressUPP(ICMProgressProcPtr userRoutine);

/*
 *  NewStdPixUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern StdPixUPP
NewStdPixUPP(StdPixProcPtr userRoutine);

/*
 *  NewQDPixUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDPixUPP
NewQDPixUPP(QDPixProcPtr userRoutine);

/*
 *  NewICMAlignmentUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ICMAlignmentUPP
NewICMAlignmentUPP(ICMAlignmentProcPtr userRoutine);

/*
 *  NewICMCursorShieldedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ICMCursorShieldedUPP
NewICMCursorShieldedUPP(ICMCursorShieldedProcPtr userRoutine);

/*
 *  NewICMMemoryDisposedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ICMMemoryDisposedUPP
NewICMMemoryDisposedUPP(ICMMemoryDisposedProcPtr userRoutine);

/*
 *  NewICMConvertDataFormatUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ICMConvertDataFormatUPP
NewICMConvertDataFormatUPP(ICMConvertDataFormatProcPtr userRoutine);

/*
 *  DisposeICMDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeICMDataUPP(ICMDataUPP userUPP);

/*
 *  DisposeICMFlushUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeICMFlushUPP(ICMFlushUPP userUPP);

/*
 *  DisposeICMCompletionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeICMCompletionUPP(ICMCompletionUPP userUPP);

/*
 *  DisposeICMProgressUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeICMProgressUPP(ICMProgressUPP userUPP);

/*
 *  DisposeStdPixUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeStdPixUPP(StdPixUPP userUPP);

/*
 *  DisposeQDPixUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDPixUPP(QDPixUPP userUPP);

/*
 *  DisposeICMAlignmentUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeICMAlignmentUPP(ICMAlignmentUPP userUPP);

/*
 *  DisposeICMCursorShieldedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeICMCursorShieldedUPP(ICMCursorShieldedUPP userUPP);

/*
 *  DisposeICMMemoryDisposedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeICMMemoryDisposedUPP(ICMMemoryDisposedUPP userUPP);

/*
 *  DisposeICMConvertDataFormatUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeICMConvertDataFormatUPP(ICMConvertDataFormatUPP userUPP);

/*
 *  InvokeICMDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeICMDataUPP(
  Ptr *       dataP,
  long        bytesNeeded,
  long        refcon,
  ICMDataUPP  userUPP);

/*
 *  InvokeICMFlushUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeICMFlushUPP(
  Ptr          data,
  long         bytesAdded,
  long         refcon,
  ICMFlushUPP  userUPP);

/*
 *  InvokeICMCompletionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeICMCompletionUPP(
  OSErr             result,
  short             flags,
  long              refcon,
  ICMCompletionUPP  userUPP);

/*
 *  InvokeICMProgressUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeICMProgressUPP(
  short           message,
  Fixed           completeness,
  long            refcon,
  ICMProgressUPP  userUPP);

/*
 *  InvokeStdPixUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeStdPixUPP(
  PixMap *        src,
  Rect *          srcRect,
  MatrixRecord *  matrix,
  short           mode,
  RgnHandle       mask,
  PixMap *        matte,
  Rect *          matteRect,
  short           flags,
  StdPixUPP       userUPP);

/*
 *  InvokeQDPixUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDPixUPP(
  PixMap *        src,
  Rect *          srcRect,
  MatrixRecord *  matrix,
  short           mode,
  RgnHandle       mask,
  PixMap *        matte,
  Rect *          matteRect,
  short           flags,
  QDPixUPP        userUPP);

/*
 *  InvokeICMAlignmentUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeICMAlignmentUPP(
  Rect *           rp,
  long             refcon,
  ICMAlignmentUPP  userUPP);

/*
 *  InvokeICMCursorShieldedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeICMCursorShieldedUPP(
  const Rect *          r,
  void *                refcon,
  long                  flags,
  ICMCursorShieldedUPP  userUPP);

/*
 *  InvokeICMMemoryDisposedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeICMMemoryDisposedUPP(
  Ptr                   memoryBlock,
  void *                refcon,
  ICMMemoryDisposedUPP  userUPP);

/*
 *  InvokeICMConvertDataFormatUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeICMConvertDataFormatUPP(
  void *                   refCon,
  long                     flags,
  Handle                   desiredFormat,
  Handle                   sourceDataFormat,
  void *                   srcData,
  long                     srcDataSize,
  void **                  dstData,
  long *                   dstDataSize,
  ICMConvertDataFormatUPP  userUPP);

/*
 *  CodecManagerVersion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CodecManagerVersion(long * version);


/*
 *  GetCodecNameList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetCodecNameList(
  CodecNameSpecListPtr *  list,
  short                   showAll);


/*
 *  DisposeCodecNameList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
DisposeCodecNameList(CodecNameSpecListPtr list);


/*
 *  GetCodecInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetCodecInfo(
  CodecInfo *      info,
  CodecType        cType,
  CodecComponent   codec);


/*
 *  GetMaxCompressionSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetMaxCompressionSize(
  PixMapHandle          src,
  const Rect *          srcRect,
  short                 colorDepth,
  CodecQ                quality,
  CodecType             cType,
  CompressorComponent   codec,
  long *                size);


/*
 *  GetCSequenceMaxCompressionSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetCSequenceMaxCompressionSize(
  ImageSequence   seqID,
  PixMapHandle    src,
  long *          size);


/*
 *  GetCompressionTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetCompressionTime(
  PixMapHandle          src,
  const Rect *          srcRect,
  short                 colorDepth,
  CodecType             cType,
  CompressorComponent   codec,
  CodecQ *              spatialQuality,
  CodecQ *              temporalQuality,
  unsigned long *       compressTime);


/*
 *  CompressImage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CompressImage(
  PixMapHandle             src,
  const Rect *             srcRect,
  CodecQ                   quality,
  CodecType                cType,
  ImageDescriptionHandle   desc,
  Ptr                      data);


/*
 *  FCompressImage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
FCompressImage(
  PixMapHandle               src,
  const Rect *               srcRect,
  short                      colorDepth,
  CodecQ                     quality,
  CodecType                  cType,
  CompressorComponent        codec,
  CTabHandle                 ctable,
  CodecFlags                 flags,
  long                       bufferSize,
  ICMFlushProcRecordPtr      flushProc,
  ICMProgressProcRecordPtr   progressProc,
  ImageDescriptionHandle     desc,
  Ptr                        data);


/*
 *  DecompressImage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
DecompressImage(
  Ptr                      data,
  ImageDescriptionHandle   desc,
  PixMapHandle             dst,
  const Rect *             srcRect,
  const Rect *             dstRect,
  short                    mode,
  RgnHandle                mask);


/*
 *  FDecompressImage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
FDecompressImage(
  Ptr                        data,
  ImageDescriptionHandle     desc,
  PixMapHandle               dst,
  const Rect *               srcRect,
  MatrixRecordPtr            matrix,
  short                      mode,
  RgnHandle                  mask,
  PixMapHandle               matte,
  const Rect *               matteRect,
  CodecQ                     accuracy,
  DecompressorComponent      codec,
  long                       bufferSize,
  ICMDataProcRecordPtr       dataProc,
  ICMProgressProcRecordPtr   progressProc);


/*
 *  CompressSequenceBegin()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CompressSequenceBegin(
  ImageSequence *          seqID,
  PixMapHandle             src,
  PixMapHandle             prev,
  const Rect *             srcRect,
  const Rect *             prevRect,
  short                    colorDepth,
  CodecType                cType,
  CompressorComponent      codec,
  CodecQ                   spatialQuality,
  CodecQ                   temporalQuality,
  long                     keyFrameRate,
  CTabHandle               ctable,
  CodecFlags               flags,
  ImageDescriptionHandle   desc);


/*
 *  CompressSequenceFrame()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CompressSequenceFrame(
  ImageSequence                seqID,
  PixMapHandle                 src,
  const Rect *                 srcRect,
  CodecFlags                   flags,
  Ptr                          data,
  long *                       dataSize,
  UInt8 *                      similarity,
  ICMCompletionProcRecordPtr   asyncCompletionProc);


/*
 *  DecompressSequenceBegin()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
DecompressSequenceBegin(
  ImageSequence *          seqID,
  ImageDescriptionHandle   desc,
  CGrafPtr                 port,
  GDHandle                 gdh,
  const Rect *             srcRect,
  MatrixRecordPtr          matrix,
  short                    mode,
  RgnHandle                mask,
  CodecFlags               flags,
  CodecQ                   accuracy,
  DecompressorComponent    codec);


/*
 *  DecompressSequenceBeginS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
DecompressSequenceBeginS(
  ImageSequence *          seqID,
  ImageDescriptionHandle   desc,
  Ptr                      data,
  long                     dataSize,
  CGrafPtr                 port,
  GDHandle                 gdh,
  const Rect *             srcRect,
  MatrixRecordPtr          matrix,
  short                    mode,
  RgnHandle                mask,
  CodecFlags               flags,
  CodecQ                   accuracy,
  DecompressorComponent    codec);


/*
 *  DecompressSequenceFrame()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
DecompressSequenceFrame(
  ImageSequence                seqID,
  Ptr                          data,
  CodecFlags                   inFlags,
  CodecFlags *                 outFlags,
  ICMCompletionProcRecordPtr   asyncCompletionProc);


/*
 *  DecompressSequenceFrameS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
DecompressSequenceFrameS(
  ImageSequence                seqID,
  Ptr                          data,
  long                         dataSize,
  CodecFlags                   inFlags,
  CodecFlags *                 outFlags,
  ICMCompletionProcRecordPtr   asyncCompletionProc);


/*
 *  DecompressSequenceFrameWhen()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
DecompressSequenceFrameWhen(
  ImageSequence                seqID,
  Ptr                          data,
  long                         dataSize,
  CodecFlags                   inFlags,
  CodecFlags *                 outFlags,
  ICMCompletionProcRecordPtr   asyncCompletionProc,
  const ICMFrameTimeRecord *   frameTime);


/*
 *  CDSequenceFlush()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CDSequenceFlush(ImageSequence seqID);


/*
 *  SetDSequenceMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetDSequenceMatrix(
  ImageSequence     seqID,
  MatrixRecordPtr   matrix);


/*
 *  GetDSequenceMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
GetDSequenceMatrix(
  ImageSequence     seqID,
  MatrixRecordPtr   matrix);


/*
 *  SetDSequenceMatte()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetDSequenceMatte(
  ImageSequence   seqID,
  PixMapHandle    matte,
  const Rect *    matteRect);


/*
 *  SetDSequenceMask()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetDSequenceMask(
  ImageSequence   seqID,
  RgnHandle       mask);


/*
 *  SetDSequenceTransferMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetDSequenceTransferMode(
  ImageSequence     seqID,
  short             mode,
  const RGBColor *  opColor);


/*
 *  SetDSequenceDataProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetDSequenceDataProc(
  ImageSequence          seqID,
  ICMDataProcRecordPtr   dataProc,
  long                   bufferSize);


/*
 *  SetDSequenceAccuracy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetDSequenceAccuracy(
  ImageSequence   seqID,
  CodecQ          accuracy);


/*
 *  SetDSequenceSrcRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetDSequenceSrcRect(
  ImageSequence   seqID,
  const Rect *    srcRect);


/*
 *  SetDSequenceFlags()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
SetDSequenceFlags(
  ImageSequence   seqID,
  long            flags,
  long            flagsMask);


enum {
  codecDSequenceSingleField     = (1L << 6)
};

typedef CodecComponent *                CodecComponentPtr;
typedef CodecComponentPtr *             CodecComponentHandle;
enum {
  kICMSequenceTaskWeight        = 'twei', /* data is pointer to UInt32*/
  kICMSequenceTaskName          = 'tnam', /* data is pointer to OSType*/
  kICMSequenceUserPreferredCodecs = 'punt' /* data is pointer to CodecComponentHandle*/
};

/*
 *  ICMSequenceGetInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern OSErr 
ICMSequenceGetInfo(
  ImageSequence   seqID,
  OSType          which,
  void *          data);


/*
 *  ICMSequenceSetInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern OSErr 
ICMSequenceSetInfo(
  ImageSequence   seqID,
  OSType          which,
  void *          data,
  Size            dataSize);


/*
 *  GetDSequenceImageBuffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetDSequenceImageBuffer(
  ImageSequence   seqID,
  GWorldPtr *     gworld);


/*
 *  GetDSequenceScreenBuffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetDSequenceScreenBuffer(
  ImageSequence   seqID,
  GWorldPtr *     gworld);


/*
 *  SetCSequenceQuality()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetCSequenceQuality(
  ImageSequence   seqID,
  CodecQ          spatialQuality,
  CodecQ          temporalQuality);


/*
 *  SetCSequencePrev()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetCSequencePrev(
  ImageSequence   seqID,
  PixMapHandle    prev,
  const Rect *    prevRect);


/*
 *  SetCSequenceFlushProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetCSequenceFlushProc(
  ImageSequence           seqID,
  ICMFlushProcRecordPtr   flushProc,
  long                    bufferSize);


/*
 *  SetCSequenceKeyFrameRate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetCSequenceKeyFrameRate(
  ImageSequence   seqID,
  long            keyFrameRate);


/*
 *  GetCSequenceKeyFrameRate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetCSequenceKeyFrameRate(
  ImageSequence   seqID,
  long *          keyFrameRate);


/*
 *  GetCSequencePrevBuffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetCSequencePrevBuffer(
  ImageSequence   seqID,
  GWorldPtr *     gworld);


/*
 *  CDSequenceBusy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CDSequenceBusy(ImageSequence seqID);


/*
 *  CDSequenceEnd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CDSequenceEnd(ImageSequence seqID);


/*
 *  CDSequenceEquivalentImageDescription()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CDSequenceEquivalentImageDescription(
  ImageSequence            seqID,
  ImageDescriptionHandle   newDesc,
  Boolean *                equivalent);


/*
 *  CDSequenceEquivalentImageDescriptionS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern OSErr 
CDSequenceEquivalentImageDescriptionS(
  ImageSequence            seqID,
  ImageDescriptionHandle   newDesc,
  Boolean *                equivalent,
  Boolean *                canSwitch);


/*
 *  ReplaceDSequenceImageDescription()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern OSErr 
ReplaceDSequenceImageDescription(
  ImageSequence            seqID,
  ImageDescriptionHandle   newDesc);


/*
 *  GetCompressedImageSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetCompressedImageSize(
  ImageDescriptionHandle   desc,
  Ptr                      data,
  long                     bufferSize,
  ICMDataProcRecordPtr     dataProc,
  long *                   dataSize);


/*
 *  GetSimilarity()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetSimilarity(
  PixMapHandle             src,
  const Rect *             srcRect,
  ImageDescriptionHandle   desc,
  Ptr                      data,
  Fixed *                  similarity);


enum {
  kImageDescriptionSampleFormat = 'idfm', /* image description extension describing sample format*/
  kImageDescriptionClassicAtomFormat = 'atom', /* sample contains classic atom structure (ie, GX codec and Curve codec)*/
  kImageDescriptionQTAtomFormat = 'qtat', /* sample contains QT atom structure*/
  kImageDescriptionEffectDataFormat = 'fxat', /* sample describes an effect (as QTAtoms)*/
  kImageDescriptionPrivateDataFormat = 'priv', /* sample is in a private codec specific format*/
  kImageDescriptionAlternateCodec = 'subs', /* image description extension containing the OSType of a substitute codec should the main codec not be available*/
  kImageDescriptionColorSpace   = 'cspc' /* image description extension containing an OSType naming the native pixel format of an image (only used for pixel formats not supported by classic Color QuickDraw)*/
};

/*
 *  GetImageDescriptionCTable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetImageDescriptionCTable(
  ImageDescriptionHandle   desc,
  CTabHandle *             ctable);


/*
 *  SetImageDescriptionCTable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetImageDescriptionCTable(
  ImageDescriptionHandle   desc,
  CTabHandle               ctable);


/*
 *  GetImageDescriptionExtension()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetImageDescriptionExtension(
  ImageDescriptionHandle   desc,
  Handle *                 extension,
  long                     idType,
  long                     index);


/*
 *  AddImageDescriptionExtension()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
AddImageDescriptionExtension(
  ImageDescriptionHandle   desc,
  Handle                   extension,
  long                     idType);


/*
 *  RemoveImageDescriptionExtension()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
RemoveImageDescriptionExtension(
  ImageDescriptionHandle   desc,
  long                     idType,
  long                     index);


/*
 *  CountImageDescriptionExtensionType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CountImageDescriptionExtensionType(
  ImageDescriptionHandle   desc,
  long                     idType,
  long *                   count);


/*
 *  GetNextImageDescriptionExtensionType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetNextImageDescriptionExtensionType(
  ImageDescriptionHandle   desc,
  long *                   idType);


/*
 *  FindCodec()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
FindCodec(
  CodecType                cType,
  CodecComponent           specCodec,
  CompressorComponent *    compressor,
  DecompressorComponent *  decompressor);


/*
 *  CompressPicture()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CompressPicture(
  PicHandle   srcPicture,
  PicHandle   dstPicture,
  CodecQ      quality,
  CodecType   cType);


/*
 *  FCompressPicture()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
FCompressPicture(
  PicHandle                  srcPicture,
  PicHandle                  dstPicture,
  short                      colorDepth,
  CTabHandle                 ctable,
  CodecQ                     quality,
  short                      doDither,
  short                      compressAgain,
  ICMProgressProcRecordPtr   progressProc,
  CodecType                  cType,
  CompressorComponent        codec);


/*
 *  CompressPictureFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CompressPictureFile(
  short       srcRefNum,
  short       dstRefNum,
  CodecQ      quality,
  CodecType   cType);


/*
 *  FCompressPictureFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
FCompressPictureFile(
  short                      srcRefNum,
  short                      dstRefNum,
  short                      colorDepth,
  CTabHandle                 ctable,
  CodecQ                     quality,
  short                      doDither,
  short                      compressAgain,
  ICMProgressProcRecordPtr   progressProc,
  CodecType                  cType,
  CompressorComponent        codec);


/*
 *  GetPictureFileHeader()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetPictureFileHeader(
  short             refNum,
  Rect *            frame,
  OpenCPicParams *  header);


/*
 *  DrawPictureFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
DrawPictureFile(
  short                      refNum,
  const Rect *               frame,
  ICMProgressProcRecordPtr   progressProc);


/*
 *  DrawTrimmedPicture()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
DrawTrimmedPicture(
  PicHandle                  srcPicture,
  const Rect *               frame,
  RgnHandle                  trimMask,
  short                      doDither,
  ICMProgressProcRecordPtr   progressProc);


/*
 *  DrawTrimmedPictureFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
DrawTrimmedPictureFile(
  short                      srcRefnum,
  const Rect *               frame,
  RgnHandle                  trimMask,
  short                      doDither,
  ICMProgressProcRecordPtr   progressProc);


/*
 *  MakeThumbnailFromPicture()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
MakeThumbnailFromPicture(
  PicHandle                  picture,
  short                      colorDepth,
  PicHandle                  thumbnail,
  ICMProgressProcRecordPtr   progressProc);


/*
 *  MakeThumbnailFromPictureFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
MakeThumbnailFromPictureFile(
  short                      refNum,
  short                      colorDepth,
  PicHandle                  thumbnail,
  ICMProgressProcRecordPtr   progressProc);


/*
 *  MakeThumbnailFromPixMap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
MakeThumbnailFromPixMap(
  PixMapHandle               src,
  const Rect *               srcRect,
  short                      colorDepth,
  PicHandle                  thumbnail,
  ICMProgressProcRecordPtr   progressProc);


/*
 *  TrimImage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
TrimImage(
  ImageDescriptionHandle     desc,
  Ptr                        inData,
  long                       inBufferSize,
  ICMDataProcRecordPtr       dataProc,
  Ptr                        outData,
  long                       outBufferSize,
  ICMFlushProcRecordPtr      flushProc,
  Rect *                     trimRect,
  ICMProgressProcRecordPtr   progressProc);


/*
 *  ConvertImage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ConvertImage(
  ImageDescriptionHandle   srcDD,
  Ptr                      srcData,
  short                    colorDepth,
  CTabHandle               ctable,
  CodecQ                   accuracy,
  CodecQ                   quality,
  CodecType                cType,
  CodecComponent           codec,
  ImageDescriptionHandle   dstDD,
  Ptr                      dstData);


/*
 *  GetCompressedPixMapInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetCompressedPixMapInfo(
  PixMapPtr                 pix,
  ImageDescriptionHandle *  desc,
  Ptr *                     data,
  long *                    bufferSize,
  ICMDataProcRecord *       dataProc,
  ICMProgressProcRecord *   progressProc);


/*
 *  SetCompressedPixMapInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetCompressedPixMapInfo(
  PixMapPtr                  pix,
  ImageDescriptionHandle     desc,
  Ptr                        data,
  long                       bufferSize,
  ICMDataProcRecordPtr       dataProc,
  ICMProgressProcRecordPtr   progressProc);


/*
 *  StdPix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
StdPix(
  PixMapPtr         src,
  const Rect *      srcRect,
  MatrixRecordPtr   matrix,
  short             mode,
  RgnHandle         mask,
  PixMapPtr         matte,
  const Rect *      matteRect,
  short             flags);


/*
 *  TransformRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
TransformRgn(
  MatrixRecordPtr   matrix,
  RgnHandle         rgn);


/***********
    preview stuff
***********/
/*
 *  SFGetFilePreview()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
 *  SFPGetFilePreview()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
 *  StandardGetFilePreview()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
 *  CustomGetFilePreview()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
 *  MakeFilePreview()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
MakeFilePreview(
  short                      resRefNum,
  ICMProgressProcRecordPtr   progress);


/*
 *  AddFilePreview()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
AddFilePreview(
  short    resRefNum,
  OSType   previewType,
  Handle   previewData);


struct PreviewResourceRecord {
  unsigned long       modDate;
  short               version;
  OSType              resType;
  short               resID;
};
typedef struct PreviewResourceRecord    PreviewResourceRecord;
typedef PreviewResourceRecord *         PreviewResourcePtr;
typedef PreviewResourcePtr *            PreviewResource;
/*
 *  AlignScreenRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
AlignScreenRect(
  Rect *                      rp,
  ICMAlignmentProcRecordPtr   alignmentProc);


/*
 *  AlignWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
AlignWindow(
  WindowRef                   wp,
  Boolean                     front,
  const Rect *                alignmentRect,
  ICMAlignmentProcRecordPtr   alignmentProc);


/*
 *  DragAlignedWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
DragAlignedWindow(
  WindowRef                   wp,
  Point                       startPt,
  Rect *                      boundsRect,
  Rect *                      alignmentRect,
  ICMAlignmentProcRecordPtr   alignmentProc);


/*
 *  DragAlignedGrayRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
DragAlignedGrayRgn(
  RgnHandle                   theRgn,
  Point                       startPt,
  Rect *                      boundsRect,
  Rect *                      slopRect,
  short                       axis,
  UniversalProcPtr            actionProc,
  Rect *                      alignmentRect,
  ICMAlignmentProcRecordPtr   alignmentProc);


/*
 *  SetCSequenceDataRateParams()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetCSequenceDataRateParams(
  ImageSequence       seqID,
  DataRateParamsPtr   params);


/*
 *  SetCSequenceFrameNumber()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetCSequenceFrameNumber(
  ImageSequence   seqID,
  long            frameNumber);


/*
 *  SetCSequencePreferredPacketSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetCSequencePreferredPacketSize(
  ImageSequence   seqID,
  long            preferredPacketSizeInBytes);


/*
 *  NewImageGWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
NewImageGWorld(
  GWorldPtr *              gworld,
  ImageDescriptionHandle   idh,
  GWorldFlags              flags);


/*
 *  GetCSequenceDataRateParams()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetCSequenceDataRateParams(
  ImageSequence       seqID,
  DataRateParamsPtr   params);


/*
 *  GetCSequenceFrameNumber()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetCSequenceFrameNumber(
  ImageSequence   seqID,
  long *          frameNumber);


/*
 *  GetBestDeviceRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetBestDeviceRect(
  GDHandle *  gdh,
  Rect *      rp);


/*
 *  SetSequenceProgressProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetSequenceProgressProc(
  ImageSequence            seqID,
  ICMProgressProcRecord *  progressProc);


/*
 *  GDHasScale()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GDHasScale(
  GDHandle   gdh,
  short      depth,
  Fixed *    scale);


/*
 *  GDGetScale()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GDGetScale(
  GDHandle   gdh,
  Fixed *    scale,
  short *    flags);


/*
 *  GDSetScale()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GDSetScale(
  GDHandle   gdh,
  Fixed      scale,
  short      flags);


/*
 *  ICMShieldSequenceCursor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ICMShieldSequenceCursor(ImageSequence seqID);


/*
 *  ICMDecompressComplete()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
ICMDecompressComplete(
  ImageSequence                seqID,
  OSErr                        err,
  short                        flag,
  ICMCompletionProcRecordPtr   completionRtn);


/*
 *  ICMDecompressCompleteS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ICMDecompressCompleteS(
  ImageSequence                seqID,
  OSErr                        err,
  short                        flag,
  ICMCompletionProcRecordPtr   completionRtn);


/*
 *  ICMSequenceLockBits()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ICMSequenceLockBits(
  ImageSequence   seqID,
  PixMapPtr       dst,
  long            flags);


/*
 *  ICMSequenceUnlockBits()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ICMSequenceUnlockBits(
  ImageSequence   seqID,
  long            flags);


enum {
  kICMPixelFormatIsPlanarMask   = 0x0F,
  kICMPixelFormatIsIndexed      = (1L << 4),
  kICMPixelFormatIsSupportedByQD = (1L << 5)
};

struct ICMPixelFormatInfo {
  long                size;
  unsigned long       formatFlags;
  short               bitsPerPixel[14];
                                              /* new field for QuickTime 4.1*/
  Fixed               defaultGammaLevel;
};
typedef struct ICMPixelFormatInfo       ICMPixelFormatInfo;
typedef ICMPixelFormatInfo *            ICMPixelFormatInfoPtr;
/*
 *  ICMGetPixelFormatInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ICMGetPixelFormatInfo(
  OSType                  PixelFormat,
  ICMPixelFormatInfoPtr   theInfo);


/*
 *  ICMSetPixelFormatInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ICMSetPixelFormatInfo(
  OSType                  PixelFormat,
  ICMPixelFormatInfoPtr   theInfo);


enum {
  kICMGetChainUltimateParent    = 0,
  kICMGetChainParent            = 1,
  kICMGetChainChild             = 2,
  kICMGetChainUltimateChild     = 3
};

/*
 *  ICMSequenceGetChainMember()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ICMSequenceGetChainMember(
  ImageSequence    seqID,
  ImageSequence *  retSeqID,
  long             flags);


/*
 *  SetDSequenceTimeCode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetDSequenceTimeCode(
  ImageSequence   seqID,
  void *          timeCodeFormat,
  void *          timeCodeTime);


/*
 *  CDSequenceNewMemory()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CDSequenceNewMemory(
  ImageSequence          seqID,
  Ptr *                  data,
  Size                   dataSize,
  long                   dataUse,
  ICMMemoryDisposedUPP   memoryGoneProc,
  void *                 refCon);


/*
 *  CDSequenceDisposeMemory()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CDSequenceDisposeMemory(
  ImageSequence   seqID,
  Ptr             data);


/*
 *  CDSequenceNewDataSource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CDSequenceNewDataSource(
  ImageSequence              seqID,
  ImageSequenceDataSource *  sourceID,
  OSType                     sourceType,
  long                       sourceInputNumber,
  Handle                     dataDescription,
  ICMConvertDataFormatUPP    transferProc,
  void *                     refCon);


/*
 *  CDSequenceDisposeDataSource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CDSequenceDisposeDataSource(ImageSequenceDataSource sourceID);


/*
 *  CDSequenceSetSourceData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CDSequenceSetSourceData(
  ImageSequenceDataSource   sourceID,
  void *                    data,
  long                      dataSize);


/*
 *  CDSequenceChangedSourceData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CDSequenceChangedSourceData(ImageSequenceDataSource sourceID);


/*
 *  CDSequenceSetSourceDataQueue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CDSequenceSetSourceDataQueue(
  ImageSequenceDataSource   sourceID,
  QHdrPtr                   dataQueue);


/*
 *  CDSequenceGetDataSource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CDSequenceGetDataSource(
  ImageSequence              seqID,
  ImageSequenceDataSource *  sourceID,
  OSType                     sourceType,
  long                       sourceInputNumber);


/*
 *  PtInDSequenceData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
PtInDSequenceData(
  ImageSequence   seqID,
  void *          data,
  Size            dataSize,
  Point           where,
  Boolean *       hit);


/*
 *  HitTestDSequenceData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
HitTestDSequenceData(
  ImageSequence   seqID,
  void *          data,
  Size            dataSize,
  Point           where,
  long *          hit,
  long            hitFlags);


/*
 *  GetGraphicsImporterForFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetGraphicsImporterForFile(
  const FSSpec *       theFile,
  ComponentInstance *  gi);


/*
 *  GetGraphicsImporterForDataRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetGraphicsImporterForDataRef(
  Handle               dataRef,
  OSType               dataRefType,
  ComponentInstance *  gi);


enum {
  kDontUseValidateToFindGraphicsImporter = 1L << 0
};

/*
 *  GetGraphicsImporterForFileWithFlags()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetGraphicsImporterForFileWithFlags(
  const FSSpec *       theFile,
  ComponentInstance *  gi,
  long                 flags);


/*
 *  GetGraphicsImporterForDataRefWithFlags()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetGraphicsImporterForDataRefWithFlags(
  Handle               dataRef,
  OSType               dataRefType,
  ComponentInstance *  gi,
  long                 flags);


/*
 *  QTGetFileNameExtension()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTGetFileNameExtension(
  ConstStrFileNameParam   fileName,
  OSType                  fileType,
  OSType *                extension);



/*
 *  ImageTranscodeSequenceBegin()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ImageTranscodeSequenceBegin(
  ImageTranscodeSequence *  its,
  ImageDescriptionHandle    srcDesc,
  OSType                    destType,
  ImageDescriptionHandle *  dstDesc,
  void *                    data,
  long                      dataSize);


/*
 *  ImageTranscodeSequenceEnd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ImageTranscodeSequenceEnd(ImageTranscodeSequence its);


/*
 *  ImageTranscodeFrame()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ImageTranscodeFrame(
  ImageTranscodeSequence   its,
  void *                   srcData,
  long                     srcDataSize,
  void **                  dstData,
  long *                   dstDataSize);


/*
 *  ImageTranscodeDisposeFrameData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ImageTranscodeDisposeFrameData(
  ImageTranscodeSequence   its,
  void *                   dstData);


/*
 *  CDSequenceInvalidate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CDSequenceInvalidate(
  ImageSequence   seqID,
  RgnHandle       invalRgn);


/*
 *  CDSequenceSetTimeBase()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CDSequenceSetTimeBase(
  ImageSequence   seqID,
  void *          base);


/*
 *  ImageFieldSequenceBegin()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ImageFieldSequenceBegin(
  ImageFieldSequence *     ifs,
  ImageDescriptionHandle   desc1,
  ImageDescriptionHandle   desc2,
  ImageDescriptionHandle   descOut);


/*
 *  ImageFieldSequenceExtractCombine()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ImageFieldSequenceExtractCombine(
  ImageFieldSequence   ifs,
  long                 fieldFlags,
  void *               data1,
  long                 dataSize1,
  void *               data2,
  long                 dataSize2,
  void *               outputData,
  long *               outDataSize);


/*
 *  ImageFieldSequenceEnd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ImageFieldSequenceEnd(ImageFieldSequence ifs);


enum {
  kICMTempThenAppMemory         = 1L << 12,
  kICMAppThenTempMemory         = 1L << 13
};

/*
 *  QTNewGWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTNewGWorld(
  GWorldPtr *   offscreenGWorld,
  OSType        PixelFormat,
  const Rect *  boundsRect,
  CTabHandle    cTable,
  GDHandle      aGDevice,
  GWorldFlags   flags);


/*
 *  QTNewGWorldFromPtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
QTNewGWorldFromPtr(
  GWorldPtr *   gw,
  OSType        pixelFormat,
  const Rect *  boundsRect,
  CTabHandle    cTable,
  GDHandle      aGDevice,
  GWorldFlags   flags,
  void *        baseAddr,
  long          rowBytes);


/*
 *  QTUpdateGWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern GWorldFlags 
QTUpdateGWorld(
  GWorldPtr *   offscreenGWorld,
  OSType        PixelFormat,
  const Rect *  boundsRect,
  CTabHandle    cTable,
  GDHandle      aGDevice,
  GWorldFlags   flags);


/*
 *  MakeImageDescriptionForPixMap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
MakeImageDescriptionForPixMap(
  PixMapHandle              pixmap,
  ImageDescriptionHandle *  idh);


/*
 *  MakeImageDescriptionForEffect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
MakeImageDescriptionForEffect(
  OSType                    effectType,
  ImageDescriptionHandle *  idh);


/*
 *  QTGetPixelSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern short 
QTGetPixelSize(OSType PixelFormat);


/*
 *  QTGetPixMapPtrRowBytes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern long 
QTGetPixMapPtrRowBytes(PixMapPtr pm);


/*
 *  QTGetPixMapHandleRowBytes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern long 
QTGetPixMapHandleRowBytes(PixMapHandle pm);


/*
 *  QTSetPixMapPtrRowBytes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
QTSetPixMapPtrRowBytes(
  PixMapPtr   pm,
  long        rowBytes);


/*
 *  QTSetPixMapHandleRowBytes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
QTSetPixMapHandleRowBytes(
  PixMapHandle   pm,
  long           rowBytes);


enum {
  kQTUsePlatformDefaultGammaLevel = 0,  /* When decompressing into this PixMap, gamma-correct to the platform's standard gamma. */
  kQTUseSourceGammaLevel        = -1L,  /* When decompressing into this PixMap, don't perform gamma-correction. */
  kQTCCIR601VideoGammaLevel     = 0x00023333 /* 2.2, standard television video gamma.*/
};

/*
 *  QTGetPixMapPtrGammaLevel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern Fixed 
QTGetPixMapPtrGammaLevel(PixMapPtr pm);


/*
 *  QTSetPixMapPtrGammaLevel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern OSErr 
QTSetPixMapPtrGammaLevel(
  PixMapPtr   pm,
  Fixed       gammaLevel);


/*
 *  QTGetPixMapHandleGammaLevel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern Fixed 
QTGetPixMapHandleGammaLevel(PixMapHandle pm);


/*
 *  QTSetPixMapHandleGammaLevel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern OSErr 
QTSetPixMapHandleGammaLevel(
  PixMapHandle   pm,
  Fixed          gammaLevel);


/*
 *  QTGetPixMapPtrRequestedGammaLevel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern Fixed 
QTGetPixMapPtrRequestedGammaLevel(PixMapPtr pm);


/*
 *  QTSetPixMapPtrRequestedGammaLevel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern OSErr 
QTSetPixMapPtrRequestedGammaLevel(
  PixMapPtr   pm,
  Fixed       requestedGammaLevel);


/*
 *  QTGetPixMapHandleRequestedGammaLevel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern Fixed 
QTGetPixMapHandleRequestedGammaLevel(PixMapHandle pm);


/*
 *  QTSetPixMapHandleRequestedGammaLevel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern OSErr 
QTSetPixMapHandleRequestedGammaLevel(
  PixMapHandle   pm,
  Fixed          requestedGammaLevel);


/*
 *  QuadToQuadMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
QuadToQuadMatrix(
  const Fixed *   source,
  const Fixed *   dest,
  MatrixRecord *  map);




enum {
  identityMatrixType            = 0x00, /* result if matrix is identity */
  translateMatrixType           = 0x01, /* result if matrix translates */
  scaleMatrixType               = 0x02, /* result if matrix scales */
  scaleTranslateMatrixType      = 0x03, /* result if matrix scales and translates */
  linearMatrixType              = 0x04, /* result if matrix is general 2 x 2 */
  linearTranslateMatrixType     = 0x05, /* result if matrix is general 2 x 2 and translates */
  perspectiveMatrixType         = 0x06  /* result if matrix is general 3 x 3 */
};

typedef unsigned short                  MatrixFlags;
/*
 *  GetMatrixType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern short 
GetMatrixType(const MatrixRecord * m);


/*
 *  CopyMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
CopyMatrix(
  const MatrixRecord *  m1,
  MatrixRecord *        m2);


/*
 *  EqualMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Boolean 
EqualMatrix(
  const MatrixRecord *  m1,
  const MatrixRecord *  m2);


/*
 *  SetIdentityMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetIdentityMatrix(MatrixRecord * matrix);


/*
 *  TranslateMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
TranslateMatrix(
  MatrixRecord *  m,
  Fixed           deltaH,
  Fixed           deltaV);


/*
 *  RotateMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
RotateMatrix(
  MatrixRecord *  m,
  Fixed           degrees,
  Fixed           aboutX,
  Fixed           aboutY);


/*
 *  ScaleMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
ScaleMatrix(
  MatrixRecord *  m,
  Fixed           scaleX,
  Fixed           scaleY,
  Fixed           aboutX,
  Fixed           aboutY);


/*
 *  SkewMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SkewMatrix(
  MatrixRecord *  m,
  Fixed           skewX,
  Fixed           skewY,
  Fixed           aboutX,
  Fixed           aboutY);


/*
 *  TransformFixedPoints()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
TransformFixedPoints(
  const MatrixRecord *  m,
  FixedPoint *          fpt,
  long                  count);


/*
 *  TransformPoints()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
TransformPoints(
  const MatrixRecord *  mp,
  Point *               pt1,
  long                  count);


/*
 *  TransformFixedRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Boolean 
TransformFixedRect(
  const MatrixRecord *  m,
  FixedRect *           fr,
  FixedPoint *          fpp);


/*
 *  TransformRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Boolean 
TransformRect(
  const MatrixRecord *  m,
  Rect *                r,
  FixedPoint *          fpp);


/*
 *  InverseMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Boolean 
InverseMatrix(
  const MatrixRecord *  m,
  MatrixRecord *        im);


/*
 *  ConcatMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
ConcatMatrix(
  const MatrixRecord *  a,
  MatrixRecord *        b);


/*
 *  RectMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
RectMatrix(
  MatrixRecord *  matrix,
  const Rect *    srcRect,
  const Rect *    dstRect);


/*
 *  MapMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
MapMatrix(
  MatrixRecord *  matrix,
  const Rect *    fromRect,
  const Rect *    toRect);








/*
 *  CompAdd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
CompAdd(
  wide *  src,
  wide *  dst);


/*
 *  CompSub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
CompSub(
  wide *  src,
  wide *  dst);


/*
 *  CompNeg()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
CompNeg(wide * dst);


/*
 *  CompShift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
CompShift(
  wide *  src,
  short   shift);


/*
 *  CompMul()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
CompMul(
  long    src1,
  long    src2,
  wide *  dst);


/*
 *  CompDiv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
CompDiv(
  wide *  numerator,
  long    denominator,
  long *  remainder);


/*
 *  CompFixMul()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
CompFixMul(
  wide *  compSrc,
  Fixed   fixSrc,
  wide *  compDst);


/*
 *  CompMulDiv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
CompMulDiv(
  wide *  co,
  long    mul,
  long    divisor);


/*
 *  CompMulDivTrunc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
CompMulDivTrunc(
  wide *  co,
  long    mul,
  long    divisor,
  long *  remainder);


/*
 *  CompCompare()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
CompCompare(
  const wide *  a,
  const wide *  minusb);


/*
 *  CompSquareRoot()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern unsigned long 
CompSquareRoot(const wide * src);


/*
 *  FixMulDiv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Fixed 
FixMulDiv(
  Fixed   src,
  Fixed   mul,
  Fixed   divisor);


/*
 *  UnsignedFixMulDiv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Fixed 
UnsignedFixMulDiv(
  Fixed   src,
  Fixed   mul,
  Fixed   divisor);


/*
 *  FracSinCos()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Fract 
FracSinCos(
  Fixed    degree,
  Fract *  cosOut);


/*
 *  FixExp2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Fixed 
FixExp2(Fixed src);


/*
 *  FixLog2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Fixed 
FixLog2(Fixed src);


/*
 *  FixPow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Fixed 
FixPow(
  Fixed   base,
  Fixed   exp);





typedef ComponentInstance               GraphicsImportComponent;
enum {
  GraphicsImporterComponentType = 'grip'
};

enum {
  graphicsImporterUsesImageDecompressor = 1L << 23
};

enum {
  quickTimeImageFileImageDescriptionAtom = 'idsc',
  quickTimeImageFileImageDataAtom = 'idat',
  quickTimeImageFileMetaDataAtom = 'meta',
  quickTimeImageFileColorSyncProfileAtom = 'iicc'
};

enum {
  graphicsImporterDrawsAllPixels = 0,
  graphicsImporterDoesntDrawAllPixels = 1,
  graphicsImporterDontKnowIfDrawAllPixels = 2
};

/* Flags for GraphicsImportSetFlags */
enum {
  kGraphicsImporterDontDoGammaCorrection = 1L
};

enum {
  kGraphicsExportGroup          = 'expo',
  kGraphicsExportFileType       = 'ftyp',
  kGraphicsExportMIMEType       = 'mime',
  kGraphicsExportExtension      = 'ext ',
  kGraphicsExportDescription    = 'desc'
};

/* User data types for layers of Photoshop files */
enum {
  kQTPhotoshopLayerMode         = 'lmod', /* OSType */
  kQTPhotoshopLayerOpacity      = 'lopa', /* UInt8, 0 = transparent .. 255 = opaque */
  kQTPhotoshopLayerClipping     = 'lclp', /* UInt8, 0 = base, 1 = non-base */
  kQTPhotoshopLayerFlags        = 'lflg', /* UInt8 */
  kQTPhotoshopLayerName         = '©lnm', /* Text */
  kQTPhotoshopLayerUnicodeName  = 'luni' /* Unicode characters, not terminated */
};

/* User data returned by graphics importers to suggest intended use for indexed images */
enum {
  kQTIndexedImageType           = 'nth?', /* 1 or more OSTypes, such as the following values: */
  kQTIndexedImageIsThumbnail    = 'n=th', /* The image at this index is a thumbnail. */
  kQTIndexedImageIsLayer        = 'n=ly', /* The image at this index is a layer. */
  kQTIndexedImageIsPage         = 'n=pg', /* The image at this index is a page. */
  kQTIndexedImageIsMultiResolution = 'n=rs' /* The image at this index is one of several identical images at different resolutions. */
};

/* Other user data types returned by graphics importers */
enum {
  kQTTIFFUserDataPrefix         = 0x74690000, /* Added to some tag values in TIFF IFDs to generate user data codes.  (0x7469 is 'ti'.) */
                                        /* For example, YCbCrPositioning is tag 0x0213, so its user data code is 0x74690213. */
  kQTTIFFExifUserDataPrefix     = 0x65780000, /* Added to tag values in Exif IFDs to generate user data codes.  (0x6578 is 'ex'.) */
                                        /* For example, DateTimeOriginal is tag 0x9003, so its user data code is 0x65789003. */
  kQTTIFFExifGPSUserDataPrefix  = 0x67700000, /* Added to tag values in Exif GPS IFDs to generate user data codes.  (0x6770 is 'gp'.) */
                                        /* For example, GPSAltitude is tag 0x0006, so its user data code is 0x6770006. */
  kQTAlphaMode                  = 'almo', /* UInt32; eg, graphicsModeStraightAlpha or graphicsModePreBlackAlpha */
  kQTAlphaModePreMulColor       = 'almp', /* RGBColor; used if kQTAlphaMode is graphicsModePreMulColorAlpha */
  kUserDataIPTC                 = 'iptc'
};


/** These are GraphicsImport procedures **/
/*
 *  GraphicsImportSetDataReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportSetDataReference(
  GraphicsImportComponent   ci,
  Handle                    dataRef,
  OSType                    dataReType);


/*
 *  GraphicsImportGetDataReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportGetDataReference(
  GraphicsImportComponent   ci,
  Handle *                  dataRef,
  OSType *                  dataReType);


/*
 *  GraphicsImportSetDataFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportSetDataFile(
  GraphicsImportComponent   ci,
  const FSSpec *            theFile);


/*
 *  GraphicsImportGetDataFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportGetDataFile(
  GraphicsImportComponent   ci,
  FSSpec *                  theFile);


/*
 *  GraphicsImportSetDataHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportSetDataHandle(
  GraphicsImportComponent   ci,
  Handle                    h);


/*
 *  GraphicsImportGetDataHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportGetDataHandle(
  GraphicsImportComponent   ci,
  Handle *                  h);


/*
 *  GraphicsImportGetImageDescription()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportGetImageDescription(
  GraphicsImportComponent   ci,
  ImageDescriptionHandle *  desc);


/*
 *  GraphicsImportGetDataOffsetAndSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportGetDataOffsetAndSize(
  GraphicsImportComponent   ci,
  unsigned long *           offset,
  unsigned long *           size);


/*
 *  GraphicsImportReadData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportReadData(
  GraphicsImportComponent   ci,
  void *                    dataPtr,
  unsigned long             dataOffset,
  unsigned long             dataSize);


/*
 *  GraphicsImportSetClip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportSetClip(
  GraphicsImportComponent   ci,
  RgnHandle                 clipRgn);


/*
 *  GraphicsImportGetClip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportGetClip(
  GraphicsImportComponent   ci,
  RgnHandle *               clipRgn);


/*
 *  GraphicsImportSetSourceRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportSetSourceRect(
  GraphicsImportComponent   ci,
  const Rect *              sourceRect);


/*
 *  GraphicsImportGetSourceRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportGetSourceRect(
  GraphicsImportComponent   ci,
  Rect *                    sourceRect);


/*
 *  GraphicsImportGetNaturalBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportGetNaturalBounds(
  GraphicsImportComponent   ci,
  Rect *                    naturalBounds);


/*
 *  GraphicsImportDraw()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportDraw(GraphicsImportComponent ci);


/*
 *  GraphicsImportSetGWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportSetGWorld(
  GraphicsImportComponent   ci,
  CGrafPtr                  port,
  GDHandle                  gd);


/*
 *  GraphicsImportGetGWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportGetGWorld(
  GraphicsImportComponent   ci,
  CGrafPtr *                port,
  GDHandle *                gd);


/*
 *  GraphicsImportSetMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportSetMatrix(
  GraphicsImportComponent   ci,
  const MatrixRecord *      matrix);


/*
 *  GraphicsImportGetMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportGetMatrix(
  GraphicsImportComponent   ci,
  MatrixRecord *            matrix);


/*
 *  GraphicsImportSetBoundsRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportSetBoundsRect(
  GraphicsImportComponent   ci,
  const Rect *              bounds);


/*
 *  GraphicsImportGetBoundsRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportGetBoundsRect(
  GraphicsImportComponent   ci,
  Rect *                    bounds);


/*
 *  GraphicsImportSaveAsPicture()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportSaveAsPicture(
  GraphicsImportComponent   ci,
  const FSSpec *            fss,
  ScriptCode                scriptTag);


/*
 *  GraphicsImportSetGraphicsMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportSetGraphicsMode(
  GraphicsImportComponent   ci,
  long                      graphicsMode,
  const RGBColor *          opColor);


/*
 *  GraphicsImportGetGraphicsMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportGetGraphicsMode(
  GraphicsImportComponent   ci,
  long *                    graphicsMode,
  RGBColor *                opColor);


/*
 *  GraphicsImportSetQuality()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportSetQuality(
  GraphicsImportComponent   ci,
  CodecQ                    quality);


/*
 *  GraphicsImportGetQuality()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportGetQuality(
  GraphicsImportComponent   ci,
  CodecQ *                  quality);


/*
 *  GraphicsImportSaveAsQuickTimeImageFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportSaveAsQuickTimeImageFile(
  GraphicsImportComponent   ci,
  const FSSpec *            fss,
  ScriptCode                scriptTag);


/*
 *  GraphicsImportSetDataReferenceOffsetAndLimit()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportSetDataReferenceOffsetAndLimit(
  GraphicsImportComponent   ci,
  unsigned long             offset,
  unsigned long             limit);


/*
 *  GraphicsImportGetDataReferenceOffsetAndLimit()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportGetDataReferenceOffsetAndLimit(
  GraphicsImportComponent   ci,
  unsigned long *           offset,
  unsigned long *           limit);


/*
 *  GraphicsImportGetAliasedDataReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportGetAliasedDataReference(
  GraphicsImportComponent   ci,
  Handle *                  dataRef,
  OSType *                  dataRefType);


/*
 *  GraphicsImportValidate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportValidate(
  GraphicsImportComponent   ci,
  Boolean *                 valid);


/*
 *  GraphicsImportGetMetaData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportGetMetaData(
  GraphicsImportComponent   ci,
  void *                    userData);


/*
 *  GraphicsImportGetMIMETypeList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportGetMIMETypeList(
  GraphicsImportComponent   ci,
  void *                    qtAtomContainerPtr);


/*
 *  GraphicsImportDoesDrawAllPixels()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportDoesDrawAllPixels(
  GraphicsImportComponent   ci,
  short *                   drawsAllPixels);


/*
 *  GraphicsImportGetAsPicture()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportGetAsPicture(
  GraphicsImportComponent   ci,
  PicHandle *               picture);


/*
 *  GraphicsImportExportImageFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportExportImageFile(
  GraphicsImportComponent   ci,
  OSType                    fileType,
  OSType                    fileCreator,
  const FSSpec *            fss,
  ScriptCode                scriptTag);


/*
 *  GraphicsImportGetExportImageTypeList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportGetExportImageTypeList(
  GraphicsImportComponent   ci,
  void *                    qtAtomContainerPtr);


/*
 *  GraphicsImportDoExportImageFileDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportDoExportImageFileDialog(
  GraphicsImportComponent   ci,
  const FSSpec *            inDefaultSpec,
  StringPtr                 prompt,
  ModalFilterYDUPP          filterProc,
  OSType *                  outExportedType,
  FSSpec *                  outExportedSpec,
  ScriptCode *              outScriptTag);


/*
 *  GraphicsImportGetExportSettingsAsAtomContainer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportGetExportSettingsAsAtomContainer(
  GraphicsImportComponent   ci,
  void *                    qtAtomContainerPtr);


/*
 *  GraphicsImportSetExportSettingsFromAtomContainer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportSetExportSettingsFromAtomContainer(
  GraphicsImportComponent   ci,
  void *                    qtAtomContainer);


/*
 *  GraphicsImportSetProgressProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportSetProgressProc(
  GraphicsImportComponent    ci,
  ICMProgressProcRecordPtr   progressProc);


/*
 *  GraphicsImportGetProgressProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GraphicsImportGetProgressProc(
  GraphicsImportComponent    ci,
  ICMProgressProcRecordPtr   progressProc);


/*
 *  GraphicsImportGetImageCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsImportGetImageCount(
  GraphicsImportComponent   ci,
  unsigned long *           imageCount);


/*
 *  GraphicsImportSetImageIndex()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsImportSetImageIndex(
  GraphicsImportComponent   ci,
  unsigned long             imageIndex);


/*
 *  GraphicsImportGetImageIndex()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsImportGetImageIndex(
  GraphicsImportComponent   ci,
  unsigned long *           imageIndex);


/*
 *  GraphicsImportGetDataOffsetAndSize64()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsImportGetDataOffsetAndSize64(
  GraphicsImportComponent   ci,
  wide *                    offset,
  wide *                    size);


/*
 *  GraphicsImportReadData64()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsImportReadData64(
  GraphicsImportComponent   ci,
  void *                    dataPtr,
  const wide *              dataOffset,
  unsigned long             dataSize);


/*
 *  GraphicsImportSetDataReferenceOffsetAndLimit64()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsImportSetDataReferenceOffsetAndLimit64(
  GraphicsImportComponent   ci,
  const wide *              offset,
  const wide *              limit);


/*
 *  GraphicsImportGetDataReferenceOffsetAndLimit64()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsImportGetDataReferenceOffsetAndLimit64(
  GraphicsImportComponent   ci,
  wide *                    offset,
  wide *                    limit);


/*
 *  GraphicsImportGetDefaultMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsImportGetDefaultMatrix(
  GraphicsImportComponent   ci,
  MatrixRecord *            defaultMatrix);


/*
 *  GraphicsImportGetDefaultClip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsImportGetDefaultClip(
  GraphicsImportComponent   ci,
  RgnHandle *               defaultRgn);


/*
 *  GraphicsImportGetDefaultGraphicsMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsImportGetDefaultGraphicsMode(
  GraphicsImportComponent   ci,
  long *                    defaultGraphicsMode,
  RGBColor *                defaultOpColor);


/*
 *  GraphicsImportGetDefaultSourceRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsImportGetDefaultSourceRect(
  GraphicsImportComponent   ci,
  Rect *                    defaultSourceRect);


/*
 *  GraphicsImportGetColorSyncProfile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsImportGetColorSyncProfile(
  GraphicsImportComponent   ci,
  Handle *                  profile);


/*
 *  GraphicsImportSetDestRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsImportSetDestRect(
  GraphicsImportComponent   ci,
  const Rect *              destRect);


/*
 *  GraphicsImportGetDestRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsImportGetDestRect(
  GraphicsImportComponent   ci,
  Rect *                    destRect);


/*
 *  GraphicsImportSetFlags()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsImportSetFlags(
  GraphicsImportComponent   ci,
  long                      flags);


/*
 *  GraphicsImportGetFlags()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsImportGetFlags(
  GraphicsImportComponent   ci,
  long *                    flags);


/* 2 private selectors */
/*
 *  GraphicsImportGetBaseDataOffsetAndSize64()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0.2 and later
 *    Windows:          in qtmlClient.lib 5.0.2 and later
 */
extern ComponentResult 
GraphicsImportGetBaseDataOffsetAndSize64(
  GraphicsImportComponent   ci,
  wide *                    offset,
  wide *                    size);




typedef ComponentInstance               GraphicsExportComponent;
enum {
  GraphicsExporterComponentType = 'grex',
  kBaseGraphicsExporterSubType  = 'base'
};

enum {
  graphicsExporterIsBaseExporter = 1L << 0,
  graphicsExporterCanTranscode  = 1L << 1,
  graphicsExporterUsesImageCompressor = 1L << 2
};

struct QTResolutionSettings {
  Fixed               horizontalResolution;
  Fixed               verticalResolution;
};
typedef struct QTResolutionSettings     QTResolutionSettings;
struct QTTargetDataSize {
  unsigned long       targetDataSize;
};
typedef struct QTTargetDataSize         QTTargetDataSize;
struct QTThumbnailSettings {
  long                enableThumbnail;        /* a thoroughly padded Boolean*/
  long                maxThumbnailWidth;      /* set to zero to let someone else decide*/
  long                maxThumbnailHeight;     /* set to zero to let someone else decide*/
};
typedef struct QTThumbnailSettings      QTThumbnailSettings;
enum {
  kQTResolutionSettings         = 'reso',
  kQTTargetDataSize             = 'dasz',
  kQTDontRecompress             = 'dntr',
  kQTInterlaceStyle             = 'ilac',
  kQTColorSyncProfile           = 'iccp',
  kQTThumbnailSettings          = 'thum',
  kQTEnableExif                 = 'exif', /* UInt8 (boolean)*/
  kQTMetaData                   = 'meta'
};

enum {
  kQTTIFFCompressionMethod      = 'tifc', /* UInt32*/
  kQTTIFFCompression_None       = 1,
  kQTTIFFCompression_PackBits   = 32773L,
  kQTTIFFLittleEndian           = 'tife' /* UInt8 (boolean)*/
};

enum {
  kQTPNGFilterPreference        = 'pngf', /* UInt32*/
  kQTPNGFilterBestForColorType  = 'bflt',
  kQTPNGFilterNone              = 0,
  kQTPNGFilterSub               = 1,
  kQTPNGFilterUp                = 2,
  kQTPNGFilterAverage           = 3,
  kQTPNGFilterPaeth             = 4,
  kQTPNGFilterAdaptivePerRow    = 'aflt',
  kQTPNGInterlaceStyle          = 'ilac', /* UInt32*/
  kQTPNGInterlaceNone           = 0,
  kQTPNGInterlaceAdam7          = 1
};


/** These are GraphicsExport procedures **/
/* To use: set the input and output (and other settings as desired) and call GEDoExport. */
/*
 *  GraphicsExportDoExport()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportDoExport(
  GraphicsExportComponent   ci,
  unsigned long *           actualSizeWritten);


/* Used for internal communication between the base and format-specific graphics exporter: */
/*
 *  GraphicsExportCanTranscode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportCanTranscode(
  GraphicsExportComponent   ci,
  Boolean *                 canTranscode);


/*
 *  GraphicsExportDoTranscode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportDoTranscode(GraphicsExportComponent ci);


/*
 *  GraphicsExportCanUseCompressor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportCanUseCompressor(
  GraphicsExportComponent   ci,
  Boolean *                 canUseCompressor,
  void *                    codecSettingsAtomContainerPtr);


/*
 *  GraphicsExportDoUseCompressor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportDoUseCompressor(
  GraphicsExportComponent   ci,
  void *                    codecSettingsAtomContainer,
  ImageDescriptionHandle *  outDesc);


/*
 *  GraphicsExportDoStandaloneExport()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportDoStandaloneExport(GraphicsExportComponent ci);


/* Queries applications can make of a format-specific graphics exporter: */
/*
 *  GraphicsExportGetDefaultFileTypeAndCreator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetDefaultFileTypeAndCreator(
  GraphicsExportComponent   ci,
  OSType *                  fileType,
  OSType *                  fileCreator);


/*
 *  GraphicsExportGetDefaultFileNameExtension()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetDefaultFileNameExtension(
  GraphicsExportComponent   ci,
  OSType *                  fileNameExtension);


/*
 *  GraphicsExportGetMIMETypeList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetMIMETypeList(
  GraphicsExportComponent   ci,
  void *                    qtAtomContainerPtr);


/* GraphicsExportIsTranscodePossibleFromCurrentInput is removed; call GraphicsExportCanTranscode instead */
/* Graphics exporter settings: */
/*
 *  GraphicsExportRequestSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportRequestSettings(
  GraphicsExportComponent   ci,
  ModalFilterYDUPP          filterProc,
  void *                    yourDataProc);


/*
 *  GraphicsExportSetSettingsFromAtomContainer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetSettingsFromAtomContainer(
  GraphicsExportComponent   ci,
  void *                    qtAtomContainer);


/*
 *  GraphicsExportGetSettingsAsAtomContainer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetSettingsAsAtomContainer(
  GraphicsExportComponent   ci,
  void *                    qtAtomContainerPtr);


/*
 *  GraphicsExportGetSettingsAsText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetSettingsAsText(
  GraphicsExportComponent   ci,
  Handle *                  theText);


/* Graphics exporters may implement some or none of the following: */
/*
 *  GraphicsExportSetDontRecompress()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetDontRecompress(
  GraphicsExportComponent   ci,
  Boolean                   dontRecompress);


/*
 *  GraphicsExportGetDontRecompress()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetDontRecompress(
  GraphicsExportComponent   ci,
  Boolean *                 dontRecompress);


/*
 *  GraphicsExportSetInterlaceStyle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetInterlaceStyle(
  GraphicsExportComponent   ci,
  unsigned long             interlaceStyle);


/*
 *  GraphicsExportGetInterlaceStyle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetInterlaceStyle(
  GraphicsExportComponent   ci,
  unsigned long *           interlaceStyle);


/*
 *  GraphicsExportSetMetaData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetMetaData(
  GraphicsExportComponent   ci,
  void *                    userData);


/*
 *  GraphicsExportGetMetaData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetMetaData(
  GraphicsExportComponent   ci,
  void *                    userData);


/*
 *  GraphicsExportSetTargetDataSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetTargetDataSize(
  GraphicsExportComponent   ci,
  unsigned long             targetDataSize);


/*
 *  GraphicsExportGetTargetDataSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetTargetDataSize(
  GraphicsExportComponent   ci,
  unsigned long *           targetDataSize);


/*
 *  GraphicsExportSetCompressionMethod()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetCompressionMethod(
  GraphicsExportComponent   ci,
  long                      compressionMethod);


/*
 *  GraphicsExportGetCompressionMethod()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetCompressionMethod(
  GraphicsExportComponent   ci,
  long *                    compressionMethod);


/*
 *  GraphicsExportSetCompressionQuality()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetCompressionQuality(
  GraphicsExportComponent   ci,
  CodecQ                    spatialQuality);


/*
 *  GraphicsExportGetCompressionQuality()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetCompressionQuality(
  GraphicsExportComponent   ci,
  CodecQ *                  spatialQuality);


/*
 *  GraphicsExportSetResolution()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetResolution(
  GraphicsExportComponent   ci,
  Fixed                     horizontalResolution,
  Fixed                     verticalResolution);


/*
 *  GraphicsExportGetResolution()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetResolution(
  GraphicsExportComponent   ci,
  Fixed *                   horizontalResolution,
  Fixed *                   verticalResolution);


/*
 *  GraphicsExportSetDepth()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetDepth(
  GraphicsExportComponent   ci,
  long                      depth);


/*
 *  GraphicsExportGetDepth()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetDepth(
  GraphicsExportComponent   ci,
  long *                    depth);


/*
 *  GraphicsExportSetColorSyncProfile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetColorSyncProfile(
  GraphicsExportComponent   ci,
  Handle                    colorSyncProfile);


/*
 *  GraphicsExportGetColorSyncProfile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetColorSyncProfile(
  GraphicsExportComponent   ci,
  Handle *                  colorSyncProfile);


/* Always implemented by the base graphics exporter: */
/*
 *  GraphicsExportSetProgressProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetProgressProc(
  GraphicsExportComponent    ci,
  ICMProgressProcRecordPtr   progressProc);


/*
 *  GraphicsExportGetProgressProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetProgressProc(
  GraphicsExportComponent    ci,
  ICMProgressProcRecordPtr   progressProc);


/* Sources for the input image: */
/*
 *  GraphicsExportSetInputDataReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetInputDataReference(
  GraphicsExportComponent   ci,
  Handle                    dataRef,
  OSType                    dataRefType,
  ImageDescriptionHandle    desc);


/*
 *  GraphicsExportGetInputDataReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetInputDataReference(
  GraphicsExportComponent   ci,
  Handle *                  dataRef,
  OSType *                  dataRefType);


/*
 *  GraphicsExportSetInputFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetInputFile(
  GraphicsExportComponent   ci,
  const FSSpec *            theFile,
  ImageDescriptionHandle    desc);


/*
 *  GraphicsExportGetInputFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetInputFile(
  GraphicsExportComponent   ci,
  FSSpec *                  theFile);


/*
 *  GraphicsExportSetInputHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetInputHandle(
  GraphicsExportComponent   ci,
  Handle                    h,
  ImageDescriptionHandle    desc);


/*
 *  GraphicsExportGetInputHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetInputHandle(
  GraphicsExportComponent   ci,
  Handle *                  h);


/*
 *  GraphicsExportSetInputPtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetInputPtr(
  GraphicsExportComponent   ci,
  Ptr                       p,
  unsigned long             size,
  ImageDescriptionHandle    desc);


/*
 *  GraphicsExportGetInputPtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetInputPtr(
  GraphicsExportComponent   ci,
  Ptr *                     p,
  unsigned long *           size);


/*
 *  GraphicsExportSetInputGraphicsImporter()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetInputGraphicsImporter(
  GraphicsExportComponent   ci,
  GraphicsImportComponent   grip);


/*
 *  GraphicsExportGetInputGraphicsImporter()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetInputGraphicsImporter(
  GraphicsExportComponent    ci,
  GraphicsImportComponent *  grip);


/*
 *  GraphicsExportSetInputPicture()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetInputPicture(
  GraphicsExportComponent   ci,
  PicHandle                 picture);


/*
 *  GraphicsExportGetInputPicture()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetInputPicture(
  GraphicsExportComponent   ci,
  PicHandle *               picture);


/*
 *  GraphicsExportSetInputGWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetInputGWorld(
  GraphicsExportComponent   ci,
  GWorldPtr                 gworld);


/*
 *  GraphicsExportGetInputGWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetInputGWorld(
  GraphicsExportComponent   ci,
  GWorldPtr *               gworld);


/*
 *  GraphicsExportSetInputPixmap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetInputPixmap(
  GraphicsExportComponent   ci,
  PixMapHandle              pixmap);


/*
 *  GraphicsExportGetInputPixmap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetInputPixmap(
  GraphicsExportComponent   ci,
  PixMapHandle *            pixmap);


/* Only applicable when the input is a data reference, file, handle or ptr: */
/*
 *  GraphicsExportSetInputOffsetAndLimit()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetInputOffsetAndLimit(
  GraphicsExportComponent   ci,
  unsigned long             offset,
  unsigned long             limit);


/*
 *  GraphicsExportGetInputOffsetAndLimit()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetInputOffsetAndLimit(
  GraphicsExportComponent   ci,
  unsigned long *           offset,
  unsigned long *           limit);


/* Used by format-specific graphics exporters when transcoding: */
/*
 *  GraphicsExportMayExporterReadInputData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportMayExporterReadInputData(
  GraphicsExportComponent   ci,
  Boolean *                 mayReadInputData);


/*
 *  GraphicsExportGetInputDataSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetInputDataSize(
  GraphicsExportComponent   ci,
  unsigned long *           size);


/*
 *  GraphicsExportReadInputData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportReadInputData(
  GraphicsExportComponent   ci,
  void *                    dataPtr,
  unsigned long             dataOffset,
  unsigned long             dataSize);


/* Used by format-specific graphics exporters, especially when doing standalone export: */
/*
 *  GraphicsExportGetInputImageDescription()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetInputImageDescription(
  GraphicsExportComponent   ci,
  ImageDescriptionHandle *  desc);


/*
 *  GraphicsExportGetInputImageDimensions()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetInputImageDimensions(
  GraphicsExportComponent   ci,
  Rect *                    dimensions);


/*
 *  GraphicsExportGetInputImageDepth()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetInputImageDepth(
  GraphicsExportComponent   ci,
  long *                    inputDepth);


/*
 *  GraphicsExportDrawInputImage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportDrawInputImage(
  GraphicsExportComponent   ci,
  CGrafPtr                  gw,
  GDHandle                  gd,
  const Rect *              srcRect,
  const Rect *              dstRect);


/* Destinations for the output image: */
/*
 *  GraphicsExportSetOutputDataReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetOutputDataReference(
  GraphicsExportComponent   ci,
  Handle                    dataRef,
  OSType                    dataRefType);


/*
 *  GraphicsExportGetOutputDataReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetOutputDataReference(
  GraphicsExportComponent   ci,
  Handle *                  dataRef,
  OSType *                  dataRefType);


/*
 *  GraphicsExportSetOutputFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetOutputFile(
  GraphicsExportComponent   ci,
  const FSSpec *            theFile);


/*
 *  GraphicsExportGetOutputFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetOutputFile(
  GraphicsExportComponent   ci,
  FSSpec *                  theFile);


/*
 *  GraphicsExportSetOutputHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetOutputHandle(
  GraphicsExportComponent   ci,
  Handle                    h);


/*
 *  GraphicsExportGetOutputHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetOutputHandle(
  GraphicsExportComponent   ci,
  Handle *                  h);


/*
 *  GraphicsExportSetOutputOffsetAndMaxSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetOutputOffsetAndMaxSize(
  GraphicsExportComponent   ci,
  unsigned long             offset,
  unsigned long             maxSize,
  Boolean                   truncateFile);


/*
 *  GraphicsExportGetOutputOffsetAndMaxSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetOutputOffsetAndMaxSize(
  GraphicsExportComponent   ci,
  unsigned long *           offset,
  unsigned long *           maxSize,
  Boolean *                 truncateFile);


/*
 *  GraphicsExportSetOutputFileTypeAndCreator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetOutputFileTypeAndCreator(
  GraphicsExportComponent   ci,
  OSType                    fileType,
  OSType                    fileCreator);


/*
 *  GraphicsExportGetOutputFileTypeAndCreator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetOutputFileTypeAndCreator(
  GraphicsExportComponent   ci,
  OSType *                  fileType,
  OSType *                  fileCreator);


/* Used by format-specific graphics exporters: */
/*
 *  GraphicsExportWriteOutputData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportWriteOutputData(
  GraphicsExportComponent   ci,
  const void *              dataPtr,
  unsigned long             dataSize);


/*
 *  GraphicsExportSetOutputMark()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportSetOutputMark(
  GraphicsExportComponent   ci,
  unsigned long             mark);


/*
 *  GraphicsExportGetOutputMark()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportGetOutputMark(
  GraphicsExportComponent   ci,
  unsigned long *           mark);


/*
 *  GraphicsExportReadOutputData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
GraphicsExportReadOutputData(
  GraphicsExportComponent   ci,
  void *                    dataPtr,
  unsigned long             dataOffset,
  unsigned long             dataSize);


/* Allows embedded thumbnail creation, if supported. */
/*
 *  GraphicsExportSetThumbnailEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0.2 and later
 *    Windows:          in qtmlClient.lib 5.0.2 and later
 */
extern ComponentResult 
GraphicsExportSetThumbnailEnabled(
  GraphicsExportComponent   ci,
  Boolean                   enableThumbnail,
  long                      maxThumbnailWidth,
  long                      maxThumbnailHeight);


/*
 *  GraphicsExportGetThumbnailEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0.2 and later
 *    Windows:          in qtmlClient.lib 5.0.2 and later
 */
extern ComponentResult 
GraphicsExportGetThumbnailEnabled(
  GraphicsExportComponent   ci,
  Boolean *                 thumbnailEnabled,
  long *                    maxThumbnailWidth,
  long *                    maxThumbnailHeight);


/* Allows export of Exif files, if supported.  This disables Exif-incompatible settings such as grayscale JPEG and compressed TIFF, and enables export of Exif metadata. */
/*
 *  GraphicsExportSetExifEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0.2 and later
 *    Windows:          in qtmlClient.lib 5.0.2 and later
 */
extern ComponentResult 
GraphicsExportSetExifEnabled(
  GraphicsExportComponent   ci,
  Boolean                   enableExif);


/*
 *  GraphicsExportGetExifEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0.2 and later
 *    Windows:          in qtmlClient.lib 5.0.2 and later
 */
extern ComponentResult 
GraphicsExportGetExifEnabled(
  GraphicsExportComponent   ci,
  Boolean *                 exifEnabled);




typedef ComponentInstance               ImageTranscoderComponent;
enum {
  ImageTranscodererComponentType = 'imtc'
};


/** These are ImageTranscoder procedures **/
/*
 *  ImageTranscoderBeginSequence()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
ImageTranscoderBeginSequence(
  ImageTranscoderComponent   itc,
  ImageDescriptionHandle     srcDesc,
  ImageDescriptionHandle *   dstDesc,
  void *                     data,
  long                       dataSize);


/*
 *  ImageTranscoderConvert()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
ImageTranscoderConvert(
  ImageTranscoderComponent   itc,
  void *                     srcData,
  long                       srcDataSize,
  void **                    dstData,
  long *                     dstDataSize);


/*
 *  ImageTranscoderDisposeData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
ImageTranscoderDisposeData(
  ImageTranscoderComponent   itc,
  void *                     dstData);


/*
 *  ImageTranscoderEndSequence()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
ImageTranscoderEndSequence(ImageTranscoderComponent itc);


/* UPP call backs */

/* selectors for component calls */
enum {
    kGraphicsImportSetDataReferenceSelect      = 0x0001,
    kGraphicsImportGetDataReferenceSelect      = 0x0002,
    kGraphicsImportSetDataFileSelect           = 0x0003,
    kGraphicsImportGetDataFileSelect           = 0x0004,
    kGraphicsImportSetDataHandleSelect         = 0x0005,
    kGraphicsImportGetDataHandleSelect         = 0x0006,
    kGraphicsImportGetImageDescriptionSelect   = 0x0007,
    kGraphicsImportGetDataOffsetAndSizeSelect  = 0x0008,
    kGraphicsImportReadDataSelect              = 0x0009,
    kGraphicsImportSetClipSelect               = 0x000A,
    kGraphicsImportGetClipSelect               = 0x000B,
    kGraphicsImportSetSourceRectSelect         = 0x000C,
    kGraphicsImportGetSourceRectSelect         = 0x000D,
    kGraphicsImportGetNaturalBoundsSelect      = 0x000E,
    kGraphicsImportDrawSelect                  = 0x000F,
    kGraphicsImportSetGWorldSelect             = 0x0010,
    kGraphicsImportGetGWorldSelect             = 0x0011,
    kGraphicsImportSetMatrixSelect             = 0x0012,
    kGraphicsImportGetMatrixSelect             = 0x0013,
    kGraphicsImportSetBoundsRectSelect         = 0x0014,
    kGraphicsImportGetBoundsRectSelect         = 0x0015,
    kGraphicsImportSaveAsPictureSelect         = 0x0016,
    kGraphicsImportSetGraphicsModeSelect       = 0x0017,
    kGraphicsImportGetGraphicsModeSelect       = 0x0018,
    kGraphicsImportSetQualitySelect            = 0x0019,
    kGraphicsImportGetQualitySelect            = 0x001A,
    kGraphicsImportSaveAsQuickTimeImageFileSelect = 0x001B,
    kGraphicsImportSetDataReferenceOffsetAndLimitSelect = 0x001C,
    kGraphicsImportGetDataReferenceOffsetAndLimitSelect = 0x001D,
    kGraphicsImportGetAliasedDataReferenceSelect = 0x001E,
    kGraphicsImportValidateSelect              = 0x001F,
    kGraphicsImportGetMetaDataSelect           = 0x0020,
    kGraphicsImportGetMIMETypeListSelect       = 0x0021,
    kGraphicsImportDoesDrawAllPixelsSelect     = 0x0022,
    kGraphicsImportGetAsPictureSelect          = 0x0023,
    kGraphicsImportExportImageFileSelect       = 0x0024,
    kGraphicsImportGetExportImageTypeListSelect = 0x0025,
    kGraphicsImportDoExportImageFileDialogSelect = 0x0026,
    kGraphicsImportGetExportSettingsAsAtomContainerSelect = 0x0027,
    kGraphicsImportSetExportSettingsFromAtomContainerSelect = 0x0028,
    kGraphicsImportSetProgressProcSelect       = 0x0029,
    kGraphicsImportGetProgressProcSelect       = 0x002A,
    kGraphicsImportGetImageCountSelect         = 0x002B,
    kGraphicsImportSetImageIndexSelect         = 0x002C,
    kGraphicsImportGetImageIndexSelect         = 0x002D,
    kGraphicsImportGetDataOffsetAndSize64Select = 0x002E,
    kGraphicsImportReadData64Select            = 0x002F,
    kGraphicsImportSetDataReferenceOffsetAndLimit64Select = 0x0030,
    kGraphicsImportGetDataReferenceOffsetAndLimit64Select = 0x0031,
    kGraphicsImportGetDefaultMatrixSelect      = 0x0032,
    kGraphicsImportGetDefaultClipSelect        = 0x0033,
    kGraphicsImportGetDefaultGraphicsModeSelect = 0x0034,
    kGraphicsImportGetDefaultSourceRectSelect  = 0x0035,
    kGraphicsImportGetColorSyncProfileSelect   = 0x0036,
    kGraphicsImportSetDestRectSelect           = 0x0037,
    kGraphicsImportGetDestRectSelect           = 0x0038,
    kGraphicsImportSetFlagsSelect              = 0x0039,
    kGraphicsImportGetFlagsSelect              = 0x003A,
    kGraphicsImportGetBaseDataOffsetAndSize64Select = 0x003D,
    kGraphicsExportDoExportSelect              = 0x0001,
    kGraphicsExportCanTranscodeSelect          = 0x0002,
    kGraphicsExportDoTranscodeSelect           = 0x0003,
    kGraphicsExportCanUseCompressorSelect      = 0x0004,
    kGraphicsExportDoUseCompressorSelect       = 0x0005,
    kGraphicsExportDoStandaloneExportSelect    = 0x0006,
    kGraphicsExportGetDefaultFileTypeAndCreatorSelect = 0x0007,
    kGraphicsExportGetDefaultFileNameExtensionSelect = 0x0008,
    kGraphicsExportGetMIMETypeListSelect       = 0x0009,
    kGraphicsExportRequestSettingsSelect       = 0x000B,
    kGraphicsExportSetSettingsFromAtomContainerSelect = 0x000C,
    kGraphicsExportGetSettingsAsAtomContainerSelect = 0x000D,
    kGraphicsExportGetSettingsAsTextSelect     = 0x000E,
    kGraphicsExportSetDontRecompressSelect     = 0x000F,
    kGraphicsExportGetDontRecompressSelect     = 0x0010,
    kGraphicsExportSetInterlaceStyleSelect     = 0x0011,
    kGraphicsExportGetInterlaceStyleSelect     = 0x0012,
    kGraphicsExportSetMetaDataSelect           = 0x0013,
    kGraphicsExportGetMetaDataSelect           = 0x0014,
    kGraphicsExportSetTargetDataSizeSelect     = 0x0015,
    kGraphicsExportGetTargetDataSizeSelect     = 0x0016,
    kGraphicsExportSetCompressionMethodSelect  = 0x0017,
    kGraphicsExportGetCompressionMethodSelect  = 0x0018,
    kGraphicsExportSetCompressionQualitySelect = 0x0019,
    kGraphicsExportGetCompressionQualitySelect = 0x001A,
    kGraphicsExportSetResolutionSelect         = 0x001B,
    kGraphicsExportGetResolutionSelect         = 0x001C,
    kGraphicsExportSetDepthSelect              = 0x001D,
    kGraphicsExportGetDepthSelect              = 0x001E,
    kGraphicsExportSetColorSyncProfileSelect   = 0x0021,
    kGraphicsExportGetColorSyncProfileSelect   = 0x0022,
    kGraphicsExportSetProgressProcSelect       = 0x0023,
    kGraphicsExportGetProgressProcSelect       = 0x0024,
    kGraphicsExportSetInputDataReferenceSelect = 0x0025,
    kGraphicsExportGetInputDataReferenceSelect = 0x0026,
    kGraphicsExportSetInputFileSelect          = 0x0027,
    kGraphicsExportGetInputFileSelect          = 0x0028,
    kGraphicsExportSetInputHandleSelect        = 0x0029,
    kGraphicsExportGetInputHandleSelect        = 0x002A,
    kGraphicsExportSetInputPtrSelect           = 0x002B,
    kGraphicsExportGetInputPtrSelect           = 0x002C,
    kGraphicsExportSetInputGraphicsImporterSelect = 0x002D,
    kGraphicsExportGetInputGraphicsImporterSelect = 0x002E,
    kGraphicsExportSetInputPictureSelect       = 0x002F,
    kGraphicsExportGetInputPictureSelect       = 0x0030,
    kGraphicsExportSetInputGWorldSelect        = 0x0031,
    kGraphicsExportGetInputGWorldSelect        = 0x0032,
    kGraphicsExportSetInputPixmapSelect        = 0x0033,
    kGraphicsExportGetInputPixmapSelect        = 0x0034,
    kGraphicsExportSetInputOffsetAndLimitSelect = 0x0035,
    kGraphicsExportGetInputOffsetAndLimitSelect = 0x0036,
    kGraphicsExportMayExporterReadInputDataSelect = 0x0037,
    kGraphicsExportGetInputDataSizeSelect      = 0x0038,
    kGraphicsExportReadInputDataSelect         = 0x0039,
    kGraphicsExportGetInputImageDescriptionSelect = 0x003A,
    kGraphicsExportGetInputImageDimensionsSelect = 0x003B,
    kGraphicsExportGetInputImageDepthSelect    = 0x003C,
    kGraphicsExportDrawInputImageSelect        = 0x003D,
    kGraphicsExportSetOutputDataReferenceSelect = 0x003E,
    kGraphicsExportGetOutputDataReferenceSelect = 0x003F,
    kGraphicsExportSetOutputFileSelect         = 0x0040,
    kGraphicsExportGetOutputFileSelect         = 0x0041,
    kGraphicsExportSetOutputHandleSelect       = 0x0042,
    kGraphicsExportGetOutputHandleSelect       = 0x0043,
    kGraphicsExportSetOutputOffsetAndMaxSizeSelect = 0x0044,
    kGraphicsExportGetOutputOffsetAndMaxSizeSelect = 0x0045,
    kGraphicsExportSetOutputFileTypeAndCreatorSelect = 0x0046,
    kGraphicsExportGetOutputFileTypeAndCreatorSelect = 0x0047,
    kGraphicsExportWriteOutputDataSelect       = 0x0048,
    kGraphicsExportSetOutputMarkSelect         = 0x0049,
    kGraphicsExportGetOutputMarkSelect         = 0x004A,
    kGraphicsExportReadOutputDataSelect        = 0x004B,
    kGraphicsExportSetThumbnailEnabledSelect   = 0x004C,
    kGraphicsExportGetThumbnailEnabledSelect   = 0x004D,
    kGraphicsExportSetExifEnabledSelect        = 0x004E,
    kGraphicsExportGetExifEnabledSelect        = 0x004F,
    kImageTranscoderBeginSequenceSelect        = 0x0001,
    kImageTranscoderConvertSelect              = 0x0002,
    kImageTranscoderDisposeDataSelect          = 0x0003,
    kImageTranscoderEndSequenceSelect          = 0x0004
};

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

#endif /* __IMAGECOMPRESSION__ */

