/*
     File:       QuickTime/ImageCompression.h
 
     Contains:   QuickTime Image Compression Interfaces.
 
     Version:    QuickTime 7.2.1
 
     Copyright:  © 1990-2006 by Apple Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __IMAGECOMPRESSION__
#define __IMAGECOMPRESSION__

#ifndef __CARBON__
#include <Carbon/Carbon.h>
#endif


#include <OpenGL/OpenGL.h>
#include <QuartzCore/CoreVideo.h>


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)


#ifndef AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER
#define AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER       WEAK_IMPORT_ATTRIBUTE
#endif
#ifndef AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5
#define AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER
#endif
#ifndef AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5
#define AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5       AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER
#endif
#ifndef AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5
#define AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER
#endif
#ifndef AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5
#define AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5       AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER
#endif
#ifndef AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5
#define AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER
#endif

/* QuickTime is not available to 64-bit clients */

#if !__LP64__

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
  kDVCNTSCCodecType             = 'dvc ', /* DV - NTSC and DVCPRO NTSC (available in QuickTime 6.0 or later)*/
                                        /* NOTE: kDVCProNTSCCodecType is deprecated.  */
                                        /* Use kDVCNTSCCodecType instead -- as far as the codecs are concerned, */
                                        /* the two data formats are identical.*/
  kDVCPALCodecType              = 'dvcp',
  kDVCProPALCodecType           = 'dvpp', /* available in QuickTime 6.0 or later*/
  kDVCPro50NTSCCodecType        = 'dv5n',
  kDVCPro50PALCodecType         = 'dv5p',
  kDVCPro100NTSCCodecType       = 'dv1n',
  kDVCPro100PALCodecType        = 'dv1p',
  kDVCPROHD720pCodecType        = 'dvhp',
  kDVCPROHD1080i60CodecType     = 'dvh6',
  kDVCPROHD1080i50CodecType     = 'dvh5',
  kBaseCodecType                = 'base',
  kFLCCodecType                 = 'flic',
  kTargaCodecType               = 'tga ',
  kPNGCodecType                 = 'png ',
  kTIFFCodecType                = 'tiff', /* NOTE: despite what might seem obvious from the two constants*/
                                        /* below and their names, they really are correct. 'yuvu' really */
                                        /* does mean signed, and 'yuvs' really does mean unsigned. Really. */
  kComponentVideoSigned         = 'yuvu',
  kComponentVideoUnsigned       = 'yuvs',
  kCMYKCodecType                = 'cmyk',
  kMicrosoftVideo1CodecType     = 'msvc',
  kSorensonCodecType            = 'SVQ1',
  kSorenson3CodecType           = 'SVQ3', /* available in QuickTime 5 and later*/
  kIndeo4CodecType              = 'IV41',
  kMPEG4VisualCodecType         = 'mp4v',
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
  k4444YpCbCrA8RCodecType       = 'r408', /* Component Y'CbCrA 8-bit 4:4:4:4, rendering format. full range alpha, zero biased yuv*/
  kJPEG2000CodecType            = 'mjp2',
  kPixletCodecType              = 'pxlt',
  kH264CodecType                = 'avc1'
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
  kChannelCompositeEffectType   = 'chan',
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


/* Supported by QTNewGWorld in QuickTime 4.0 and later */
enum {
  kCMYKPixelFormat              = 'cmyk', /* CMYK, 8-bit */
  k64ARGBPixelFormat            = 'b64a', /* ARGB, 16-bit big-endian samples */
  k48RGBPixelFormat             = 'b48r', /* RGB, 16-bit big-endian samples */
  k32AlphaGrayPixelFormat       = 'b32a', /* AlphaGray, 16-bit big-endian samples */
  k16GrayPixelFormat            = 'b16g', /* Grayscale, 16-bit big-endian samples */
  k422YpCbCr8PixelFormat        = '2vuy' /* Component Y'CbCr 8-bit 4:2:2, ordered Cb Y'0 Cr Y'1 */
};

/* Supported by QTNewGWorld in QuickTime 4.1.2 and later */
enum {
  k4444YpCbCrA8PixelFormat      = 'v408', /* Component Y'CbCrA 8-bit 4:4:4:4, ordered Cb Y' Cr A */
  k4444YpCbCrA8RPixelFormat     = 'r408' /* Component Y'CbCrA 8-bit 4:4:4:4, rendering format. full range alpha, zero biased yuv, ordered A Y' Cb Cr */
};

/* Supported by QTNewGWorld in QuickTime 6.0 and later */
enum {
  kYUV420PixelFormat            = 'y420' /* Planar Component Y'CbCr 8-bit 4:2:0.  PixMap baseAddr points to a big-endian PlanarPixmapInfoYUV420 struct; see ImageCodec.i. */
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
  codecInfoDoesReorder          = (1L << 19), /* codec can rearrange frames during compression */
  codecInfoDoesWarp             = (1L << 20), /* codec can warp arbitrarily on decompress */
  codecInfoDoesMultiPass        = (1L << 20), /* codec can perform multi-pass compression */
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
  codecCompletionDropped        = (1 << 6), /* codec decided to drop this frame */
  codecCompletionDecoded        = (1 << 10), /* codec has decoded this frame; if it is cancelled and rescheduled, set icmFrameAlreadyDecoded in ICMFrameTimeRecord.flags */
  codecCompletionNotDisplayable = (1 << 11), /* the frame may still be scheduled for decode, but will not be able to be displayed because the buffer containing it will need to be recycled to display earlier frames. */
  codecCompletionNotDrawn       = (1 << 12) /* set in conjunction with codecCompletionDest to indicate that the frame was not drawn */
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
  graphicsModePreMulColorAlpha  = 261,
  graphicsModePerComponentAlpha = 272
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

/* Flags for ICMFrameTimeRecord.flags */
enum {
  icmFrameTimeHasVirtualStartTimeAndDuration = 1 << 0,
  icmFrameAlreadyDecoded        = 1 << 1,
  icmFrameTimeIsNonScheduledDisplayTime = 1 << 2,
  icmFrameTimeHasDecodeTime     = 1 << 3,
  icmFrameTimeDecodeImmediately = 1 << 4,
  icmFrameTimeDoNotDisplay      = 1 << 5
};

struct ICMFrameTimeRecord {
  wide                value;                  /* frame display time*/
  long                scale;                  /* timescale of value/duration fields*/
  void *              base;                   /* timebase*/

  long                duration;               /* duration frame is to be displayed (0 if unknown)*/
  Fixed               rate;                   /* rate of timebase relative to wall-time*/

  long                recordSize;             /* total number of bytes in ICMFrameTimeRecord*/

  long                frameNumber;            /* number of frame, zero if not known*/

  long                flags;

  wide                virtualStartTime;       /* conceptual start time*/
  long                virtualDuration;        /* conceptual duration*/

                                              /* The following fields only exist for QuickTime 7.0 and greater. */
  TimeValue64         decodeTime;             /* suggested decode time, if icmFrameTimeHasDecodeTime is set in flags*/
};
typedef struct ICMFrameTimeRecord       ICMFrameTimeRecord;
typedef ICMFrameTimeRecord *            ICMFrameTimePtr;
#ifndef __QTUUID__
#define __QTUUID__ 1
/* QuickTime flavor of universally unique identifier (uuid)*/
struct QTUUID {
  UInt32              data1;
  UInt16              data2;
  UInt16              data3;
  UInt8               data4[8];
};
typedef struct QTUUID                   QTUUID;
typedef QTUUID                          QTMediaContextID;
#endif  /* !defined(__QTUUID__) */

/* See Movies.h for the flags themselves. */
typedef UInt32                          MediaSampleFlags;
/*
 *  NewICMDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ICMDataUPP
NewICMDataUPP(ICMDataProcPtr userRoutine)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewICMFlushUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ICMFlushUPP
NewICMFlushUPP(ICMFlushProcPtr userRoutine)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewICMCompletionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ICMCompletionUPP
NewICMCompletionUPP(ICMCompletionProcPtr userRoutine)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewICMProgressUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ICMProgressUPP
NewICMProgressUPP(ICMProgressProcPtr userRoutine)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewStdPixUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern StdPixUPP
NewStdPixUPP(StdPixProcPtr userRoutine)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQDPixUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDPixUPP
NewQDPixUPP(QDPixProcPtr userRoutine)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewICMAlignmentUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ICMAlignmentUPP
NewICMAlignmentUPP(ICMAlignmentProcPtr userRoutine)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewICMCursorShieldedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ICMCursorShieldedUPP
NewICMCursorShieldedUPP(ICMCursorShieldedProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewICMMemoryDisposedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ICMMemoryDisposedUPP
NewICMMemoryDisposedUPP(ICMMemoryDisposedProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewICMConvertDataFormatUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ICMConvertDataFormatUPP
NewICMConvertDataFormatUPP(ICMConvertDataFormatProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeICMDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeICMDataUPP(ICMDataUPP userUPP)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeICMFlushUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeICMFlushUPP(ICMFlushUPP userUPP)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeICMCompletionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeICMCompletionUPP(ICMCompletionUPP userUPP)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeICMProgressUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeICMProgressUPP(ICMProgressUPP userUPP)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeStdPixUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeStdPixUPP(StdPixUPP userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQDPixUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDPixUPP(QDPixUPP userUPP)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeICMAlignmentUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeICMAlignmentUPP(ICMAlignmentUPP userUPP)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeICMCursorShieldedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeICMCursorShieldedUPP(ICMCursorShieldedUPP userUPP)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeICMMemoryDisposedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeICMMemoryDisposedUPP(ICMMemoryDisposedUPP userUPP)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeICMConvertDataFormatUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeICMConvertDataFormatUPP(ICMConvertDataFormatUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  ICMDataUPP  userUPP)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  ICMFlushUPP  userUPP)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  ICMCompletionUPP  userUPP)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  ICMProgressUPP  userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  StdPixUPP       userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  QDPixUPP        userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  ICMAlignmentUPP  userUPP)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  ICMCursorShieldedUPP  userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  ICMMemoryDisposedUPP  userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
  ICMConvertDataFormatUPP  userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

#if __MACH__
  #ifdef __cplusplus
    inline ICMDataUPP                                           NewICMDataUPP(ICMDataProcPtr userRoutine) { return userRoutine; }
    inline ICMFlushUPP                                          NewICMFlushUPP(ICMFlushProcPtr userRoutine) { return userRoutine; }
    inline ICMCompletionUPP                                     NewICMCompletionUPP(ICMCompletionProcPtr userRoutine) { return userRoutine; }
    inline ICMProgressUPP                                       NewICMProgressUPP(ICMProgressProcPtr userRoutine) { return userRoutine; }
    inline StdPixUPP                                            NewStdPixUPP(StdPixProcPtr userRoutine) { return userRoutine; }
    inline QDPixUPP                                             NewQDPixUPP(QDPixProcPtr userRoutine) { return userRoutine; }
    inline ICMAlignmentUPP                                      NewICMAlignmentUPP(ICMAlignmentProcPtr userRoutine) { return userRoutine; }
    inline ICMCursorShieldedUPP                                 NewICMCursorShieldedUPP(ICMCursorShieldedProcPtr userRoutine) { return userRoutine; }
    inline ICMMemoryDisposedUPP                                 NewICMMemoryDisposedUPP(ICMMemoryDisposedProcPtr userRoutine) { return userRoutine; }
    inline ICMConvertDataFormatUPP                              NewICMConvertDataFormatUPP(ICMConvertDataFormatProcPtr userRoutine) { return userRoutine; }
    inline void                                                 DisposeICMDataUPP(ICMDataUPP) { }
    inline void                                                 DisposeICMFlushUPP(ICMFlushUPP) { }
    inline void                                                 DisposeICMCompletionUPP(ICMCompletionUPP) { }
    inline void                                                 DisposeICMProgressUPP(ICMProgressUPP) { }
    inline void                                                 DisposeStdPixUPP(StdPixUPP) { }
    inline void                                                 DisposeQDPixUPP(QDPixUPP) { }
    inline void                                                 DisposeICMAlignmentUPP(ICMAlignmentUPP) { }
    inline void                                                 DisposeICMCursorShieldedUPP(ICMCursorShieldedUPP) { }
    inline void                                                 DisposeICMMemoryDisposedUPP(ICMMemoryDisposedUPP) { }
    inline void                                                 DisposeICMConvertDataFormatUPP(ICMConvertDataFormatUPP) { }
    inline OSErr                                                InvokeICMDataUPP(Ptr * dataP, long bytesNeeded, long refcon, ICMDataUPP userUPP) { return (*userUPP)(dataP, bytesNeeded, refcon); }
    inline OSErr                                                InvokeICMFlushUPP(Ptr data, long bytesAdded, long refcon, ICMFlushUPP userUPP) { return (*userUPP)(data, bytesAdded, refcon); }
    inline void                                                 InvokeICMCompletionUPP(OSErr result, short flags, long refcon, ICMCompletionUPP userUPP) { (*userUPP)(result, flags, refcon); }
    inline OSErr                                                InvokeICMProgressUPP(short message, Fixed completeness, long refcon, ICMProgressUPP userUPP) { return (*userUPP)(message, completeness, refcon); }
    inline void                                                 InvokeStdPixUPP(PixMap * src, Rect * srcRect, MatrixRecord * matrix, short mode, RgnHandle mask, PixMap * matte, Rect * matteRect, short flags, StdPixUPP userUPP) { (*userUPP)(src, srcRect, matrix, mode, mask, matte, matteRect, flags); }
    inline void                                                 InvokeQDPixUPP(PixMap * src, Rect * srcRect, MatrixRecord * matrix, short mode, RgnHandle mask, PixMap * matte, Rect * matteRect, short flags, QDPixUPP userUPP) { (*userUPP)(src, srcRect, matrix, mode, mask, matte, matteRect, flags); }
    inline void                                                 InvokeICMAlignmentUPP(Rect * rp, long refcon, ICMAlignmentUPP userUPP) { (*userUPP)(rp, refcon); }
    inline void                                                 InvokeICMCursorShieldedUPP(const Rect * r, void * refcon, long flags, ICMCursorShieldedUPP userUPP) { (*userUPP)(r, refcon, flags); }
    inline void                                                 InvokeICMMemoryDisposedUPP(Ptr memoryBlock, void * refcon, ICMMemoryDisposedUPP userUPP) { (*userUPP)(memoryBlock, refcon); }
    inline OSErr                                                InvokeICMConvertDataFormatUPP(void * refCon, long flags, Handle desiredFormat, Handle sourceDataFormat, void * srcData, long srcDataSize, void ** dstData, long * dstDataSize, ICMConvertDataFormatUPP userUPP) { return (*userUPP)(refCon, flags, desiredFormat, sourceDataFormat, srcData, srcDataSize, dstData, dstDataSize); }
  #else
    #define NewICMDataUPP(userRoutine)                          ((ICMDataUPP)userRoutine)
    #define NewICMFlushUPP(userRoutine)                         ((ICMFlushUPP)userRoutine)
    #define NewICMCompletionUPP(userRoutine)                    ((ICMCompletionUPP)userRoutine)
    #define NewICMProgressUPP(userRoutine)                      ((ICMProgressUPP)userRoutine)
    #define NewStdPixUPP(userRoutine)                           ((StdPixUPP)userRoutine)
    #define NewQDPixUPP(userRoutine)                            ((QDPixUPP)userRoutine)
    #define NewICMAlignmentUPP(userRoutine)                     ((ICMAlignmentUPP)userRoutine)
    #define NewICMCursorShieldedUPP(userRoutine)                ((ICMCursorShieldedUPP)userRoutine)
    #define NewICMMemoryDisposedUPP(userRoutine)                ((ICMMemoryDisposedUPP)userRoutine)
    #define NewICMConvertDataFormatUPP(userRoutine)             ((ICMConvertDataFormatUPP)userRoutine)
    #define DisposeICMDataUPP(userUPP)
    #define DisposeICMFlushUPP(userUPP)
    #define DisposeICMCompletionUPP(userUPP)
    #define DisposeICMProgressUPP(userUPP)
    #define DisposeStdPixUPP(userUPP)
    #define DisposeQDPixUPP(userUPP)
    #define DisposeICMAlignmentUPP(userUPP)
    #define DisposeICMCursorShieldedUPP(userUPP)
    #define DisposeICMMemoryDisposedUPP(userUPP)
    #define DisposeICMConvertDataFormatUPP(userUPP)
    #define InvokeICMDataUPP(dataP, bytesNeeded, refcon, userUPP) (*userUPP)(dataP, bytesNeeded, refcon)
    #define InvokeICMFlushUPP(data, bytesAdded, refcon, userUPP) (*userUPP)(data, bytesAdded, refcon)
    #define InvokeICMCompletionUPP(result, flags, refcon, userUPP) (*userUPP)(result, flags, refcon)
    #define InvokeICMProgressUPP(message, completeness, refcon, userUPP) (*userUPP)(message, completeness, refcon)
    #define InvokeStdPixUPP(src, srcRect, matrix, mode, mask, matte, matteRect, flags, userUPP) (*userUPP)(src, srcRect, matrix, mode, mask, matte, matteRect, flags)
    #define InvokeQDPixUPP(src, srcRect, matrix, mode, mask, matte, matteRect, flags, userUPP) (*userUPP)(src, srcRect, matrix, mode, mask, matte, matteRect, flags)
    #define InvokeICMAlignmentUPP(rp, refcon, userUPP)          (*userUPP)(rp, refcon)
    #define InvokeICMCursorShieldedUPP(r, refcon, flags, userUPP) (*userUPP)(r, refcon, flags)
    #define InvokeICMMemoryDisposedUPP(memoryBlock, refcon, userUPP) (*userUPP)(memoryBlock, refcon)
    #define InvokeICMConvertDataFormatUPP(refCon, flags, desiredFormat, sourceDataFormat, srcData, srcDataSize, dstData, dstDataSize, userUPP) (*userUPP)(refCon, flags, desiredFormat, sourceDataFormat, srcData, srcDataSize, dstData, dstDataSize)
  #endif
#endif

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
CodecManagerVersion(long * version)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  short                   showAll)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
DisposeCodecNameList(CodecNameSpecListPtr list)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  CodecComponent   codec)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long *                size)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long *          size)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long *       compressTime)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Ptr                      data)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Ptr                        data)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  RgnHandle                mask)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMProgressProcRecordPtr   progressProc)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* For video compression, consider using ICMCompressionSessionCreate etc. instead of CompressSequenceBegin etc. */
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
  ImageDescriptionHandle   desc)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMCompletionProcRecordPtr   asyncCompletionProc)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* For video decompression, consider using ICMDecompressionSessionCreate etc. instead of DecompressSequenceBegin etc. */
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
  DecompressorComponent    codec)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* For video decompression, consider using ICMDecompressionSessionCreate etc. instead of DecompressSequenceBeginS etc. */
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
  DecompressorComponent    codec)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMCompletionProcRecordPtr   asyncCompletionProc)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMCompletionProcRecordPtr   asyncCompletionProc)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  const ICMFrameTimeRecord *   frameTime)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
CDSequenceFlush(ImageSequence seqID)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  MatrixRecordPtr   matrix)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  MatrixRecordPtr   matrix)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  const Rect *    matteRect)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  RgnHandle       mask)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  const RGBColor *  opColor)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long                   bufferSize)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  CodecQ          accuracy)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  const Rect *    srcRect)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long            flagsMask)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


enum {
  codecDSequenceDisableOverlaySurface = (1L << 5),
  codecDSequenceSingleField     = (1L << 6),
  codecDSequenceBidirectionalPrediction = (1L << 7),
  codecDSequenceFlushInsteadOfDirtying = (1L << 8),
  codecDSequenceEnableSubPixelPositioning = (1L << 9),
  codecDSequenceDeinterlaceFields = (1L << 10)
};

typedef CodecComponent *                CodecComponentPtr;
typedef CodecComponentPtr *             CodecComponentHandle;
/* selectors for ICMSequenceGet/SetInfo*/
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
  void *          data)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Size            dataSize)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  GWorldPtr *     gworld)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  GWorldPtr *     gworld)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  CodecQ          temporalQuality)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  const Rect *    prevRect)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long                    bufferSize)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long            keyFrameRate)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long *          keyFrameRate)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  GWorldPtr *     gworld)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
CDSequenceBusy(ImageSequence seqID)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
CDSequenceEnd(ImageSequence seqID)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Boolean *                equivalent)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Boolean *                canSwitch)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ImageDescriptionHandle   newDesc)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long *                   dataSize)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Fixed *                  similarity)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  CTabHandle *             ctable)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  CTabHandle               ctable)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long                     index)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long                     idType)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long                     index)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long *                   count)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long *                   idType)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  DecompressorComponent *  decompressor)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  CodecType   cType)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  CompressorComponent        codec)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  CodecType   cType)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  CompressorComponent        codec)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  OpenCPicParams *  header)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMProgressProcRecordPtr   progressProc)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMProgressProcRecordPtr   progressProc)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMProgressProcRecordPtr   progressProc)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMProgressProcRecordPtr   progressProc)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMProgressProcRecordPtr   progressProc)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMProgressProcRecordPtr   progressProc)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMProgressProcRecordPtr   progressProc)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Ptr                      dstData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMProgressProcRecord *   progressProc)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMProgressProcRecordPtr   progressProc)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  short             flags)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  RgnHandle         rgn)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMProgressProcRecordPtr   progress)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Handle   previewData)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMAlignmentProcRecordPtr   alignmentProc)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMAlignmentProcRecordPtr   alignmentProc)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMAlignmentProcRecordPtr   alignmentProc)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMAlignmentProcRecordPtr   alignmentProc)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  DataRateParamsPtr   params)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long            frameNumber)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long            preferredPacketSizeInBytes)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  GWorldFlags              flags)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  DataRateParamsPtr   params)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long *          frameNumber)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Rect *      rp)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMProgressProcRecord *  progressProc)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Fixed *    scale)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  short *    flags)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  short      flags)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
ICMShieldSequenceCursor(ImageSequence seqID)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMCompletionProcRecordPtr   completionRtn)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMCompletionProcRecordPtr   completionRtn)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long            flags)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long            flags)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


enum {
  kICMPixelFormatIsPlanarMask   = 0x0F, /* these bits in formatFlags indicate how many planes there are; they're 0 if chunky*/
  kICMPixelFormatIsIndexed      = (1L << 4),
  kICMPixelFormatIsSupportedByQD = (1L << 5),
  kICMPixelFormatIsMonochrome   = (1L << 6),
  kICMPixelFormatHasAlphaChannel = (1L << 7)
};

struct ICMPixelFormatInfo {
  long                size;                   /* caller MUST fill this in with sizeof(ICMPixelFormatInfo) before calling ICMGet/SetPixelFormatInfo*/
  unsigned long       formatFlags;
  short               bitsPerPixel[14];       /* list each plane's bits per pixel separately if planar*/
                                              /* new field for QuickTime 4.1*/
  Fixed               defaultGammaLevel;
                                              /* new fields for QuickTime 6.0*/
  short               horizontalSubsampling[14]; /* per plane; use 1 if plane is not subsampled*/
  short               verticalSubsampling[14]; /* per plane; use 1 if plane is not subsampled*/
                                              /* new fields for QuickTime 6.5*/
  short               cmpCount;               /* for use in PixMap.cmpCount*/
  short               cmpSize;                /* for use in PixMap.cmpSize*/
};
typedef struct ICMPixelFormatInfo       ICMPixelFormatInfo;
typedef ICMPixelFormatInfo *            ICMPixelFormatInfoPtr;
/* IMPORTANT: Fill in theInfo->size with sizeof(ICMPixelFormatInfo) before calling ICMGetPixelFormatInfo */
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
  ICMPixelFormatInfoPtr   theInfo)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* IMPORTANT: Fill in theInfo->size with sizeof(ICMPixelFormatInfo) before calling ICMSetPixelFormatInfo */
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
  ICMPixelFormatInfoPtr   theInfo)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long             flags)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  void *          timeCodeTime)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  void *                 refCon)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Ptr             data)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  void *                     refCon)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
CDSequenceDisposeDataSource(ImageSequenceDataSource sourceID) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long                      dataSize)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
CDSequenceChangedSourceData(ImageSequenceDataSource sourceID) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  QHdrPtr                   dataQueue)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long                       sourceInputNumber)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Boolean *       hit)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long            hitFlags)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDSequenceNonScheduledDisplayTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSErr 
SetDSequenceNonScheduledDisplayTime(
  ImageSequence   sequence,
  TimeValue64     displayTime,
  TimeScale       displayTimeScale,
  UInt32          flags)                                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetDSequenceNonScheduledDisplayTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSErr 
GetDSequenceNonScheduledDisplayTime(
  ImageSequence   sequence,
  TimeValue64 *   displayTime,
  TimeScale *     displayTimeScale)                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  SetDSequenceNonScheduledDisplayDirection()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSErr 
SetDSequenceNonScheduledDisplayDirection(
  ImageSequence   sequence,
  Fixed           rate)                                       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetDSequenceNonScheduledDisplayDirection()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSErr 
GetDSequenceNonScheduledDisplayDirection(
  ImageSequence   sequence,
  Fixed *         rate)                                       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


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
  ComponentInstance *  gi)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ComponentInstance *  gi)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long                 flags)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long                 flags)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  OSType *                extension)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



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
  long                      dataSize)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
ImageTranscodeSequenceEnd(ImageTranscodeSequence its)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long *                   dstDataSize)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  void *                   dstData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  RgnHandle       invalRgn)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  void *          base)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ImageDescriptionHandle   descOut)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long *               outDataSize)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
ImageFieldSequenceEnd(ImageFieldSequence ifs)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  GWorldFlags   flags)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long          rowBytes)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  GWorldFlags   flags)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ImageDescriptionHandle *  idh)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ImageDescriptionHandle *  idh)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
QTGetPixelSize(OSType PixelFormat)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTGetPixelFormatDepthForImageDescription()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern short 
QTGetPixelFormatDepthForImageDescription(OSType PixelFormat)  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


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
QTGetPixMapPtrRowBytes(PixMapPtr pm)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
QTGetPixMapHandleRowBytes(PixMapHandle pm)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long        rowBytes)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long           rowBytes)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
QTGetPixMapPtrGammaLevel(PixMapPtr pm)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Fixed       gammaLevel)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
QTGetPixMapHandleGammaLevel(PixMapHandle pm)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Fixed          gammaLevel)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
QTGetPixMapPtrRequestedGammaLevel(PixMapPtr pm)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Fixed       requestedGammaLevel)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
QTGetPixMapHandleRequestedGammaLevel(PixMapHandle pm)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Fixed          requestedGammaLevel)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  MatrixRecord *  map)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




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
GetMatrixType(const MatrixRecord * m)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  MatrixRecord *        m2)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  const MatrixRecord *  m2)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
SetIdentityMatrix(MatrixRecord * matrix)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Fixed           deltaV)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Fixed           aboutY)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Fixed           aboutY)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Fixed           aboutY)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long                  count)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long                  count)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  FixedPoint *          fpp)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  FixedPoint *          fpp)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  MatrixRecord *        im)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  MatrixRecord *        b)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  const Rect *    dstRect)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  const Rect *    toRect)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;








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
  wide *  dst)                                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  wide *  dst)                                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
CompNeg(wide * dst)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  short   shift)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  wide *  dst)                                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long *  remainder)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  wide *  compDst)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long    divisor)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long *  remainder)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  const wide *  minusb)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
CompSquareRoot(const wide * src)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Fixed   divisor)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Fixed   divisor)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Fract *  cosOut)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
FixExp2(Fixed src)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
FixLog2(Fixed src)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Fixed   exp)                                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;





typedef ComponentInstance               GraphicsImportComponent;
enum {
  GraphicsImporterComponentType = 'grip'
};

/* Component flags for Graphics Importer components */
enum {
  graphicsImporterIsBaseImporter = 1L << 0,
  graphicsImporterCanValidateFile = 1L << 9,
  graphicsImporterSubTypeIsFileExtension = 1L << 12,
  graphicsImporterHasMIMEList   = 1L << 14,
  graphicsImporterUsesImageDecompressor = 1L << 23
};

/* Atom types for QuickTime Image files */
enum {
  quickTimeImageFileImageDescriptionAtom = 'idsc',
  quickTimeImageFileImageDataAtom = 'idat',
  quickTimeImageFileMetaDataAtom = 'meta',
  quickTimeImageFileColorSyncProfileAtom = 'iicc'
};

/* Flags for GraphicsImportDoesDrawAllPixels */
enum {
  graphicsImporterDrawsAllPixels = 0,
  graphicsImporterDoesntDrawAllPixels = 1,
  graphicsImporterDontKnowIfDrawAllPixels = 2
};

/* Flags for GraphicsImportSetFlags */
enum {
  kGraphicsImporterDontDoGammaCorrection = 1L << 0,
  kGraphicsImporterTrustResolutionFromFile = 1L << 1,
  kGraphicsImporterEnableSubPixelPositioning = 1L << 2,
  kGraphicsImporterDontUseColorMatching = 1L << 3 /* set this flag (*before* calling GraphicsImportGetColorSyncProfile) if you do matching yourself */
};

/* Flags for GraphicsImportCreateCGImage */
enum {
  kGraphicsImportCreateCGImageUsingCurrentSettings = 1L << 0
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
  kQTPhotoshopLayerName         = (long)0xA96C6E6D/*'©lnm' */, /* Text */
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

/* Found in TIFF and Exif JPEG files */
enum {
  kQTTIFFUserDataOrientation    = 0x74690112, /* 1 SHORT */
  kQTTIFFUserDataTransferFunction = 0x7469012D, /* n SHORTs */
  kQTTIFFUserDataWhitePoint     = 0x7469013E, /* 2 RATIONALs */
  kQTTIFFUserDataPrimaryChromaticities = 0x7469013F, /* 6 RATIONALs */
  kQTTIFFUserDataTransferRange  = 0x74690156, /* 6 SHORTs */
  kQTTIFFUserDataYCbCrPositioning = 0x74690213, /* 1 SHORT */
  kQTTIFFUserDataReferenceBlackWhite = 0x74690214 /* n LONGs */
};

/* Found in GeoTIFF files; defined in the GeoTIFF 1.0 spec */
enum {
  kQTTIFFUserDataModelPixelScale = 0x7469830E, /* 3 DOUBLEs */
  kQTTIFFUserDataModelTransformation = 0x746985D8, /* 16 DOUBLEs */
  kQTTIFFUserDataModelTiepoint  = 0x74698482, /* n DOUBLEs */
  kQTTIFFUserDataGeoKeyDirectory = 0x746987AF, /* n SHORTs */
  kQTTIFFUserDataGeoDoubleParams = 0x746987B0, /* n DOUBLEs */
  kQTTIFFUserDataGeoAsciiParams = 0x746987B1, /* n ASCIIs */
  kQTTIFFUserDataIntergraphMatrix = 0x74698480 /* 16 or 17 DOUBLEs */
};

/* Found in Exif TIFF and Exif JPEG files; defined in the Exif 2.1 spec */
enum {
  kQTExifUserDataExifVersion    = 0x65789000, /* 4 bytes (import only) */
  kQTExifUserDataFlashPixVersion = 0x6578A000, /* 4 bytes */
  kQTExifUserDataColorSpace     = 0x6578A001, /* 1 SHORT */
  kQTExifUserDataComponentsConfiguration = 0x65789101, /* 4 bytes */
  kQTExifUserDataCompressedBitsPerPixel = 0x65789102, /* 1 RATIONAL */
  kQTExifUserDataPixelXDimension = 0x6578A002, /* 1 SHORT or LONG */
  kQTExifUserDataPixelYDimension = 0x6578A003, /* 1 SHORT or LONG */
  kQTExifUserDataMakerNote      = 0x6578927C, /* n bytes */
  kQTExifUserDataUserComment    = 0x65789286, /* n bytes (Note: this constant was erroneously 0x6578928C)*/
  kQTExifUserDataRelatedSoundFile = 0x6578A004, /* 13 ASCIIs*/
  kQTExifUserDataDateTimeOriginal = 0x65789003, /* 20 ASCIIs */
  kQTExifUserDataDateTimeDigitized = 0x65789004, /* 20 ASCIIs */
  kQTExifUserDataSubSecTime     = 0x65789290, /* n ASCIIs */
  kQTExifUserDataSubSecTimeOriginal = 0x65789291, /* n ASCIIs */
  kQTExifUserDataSubSecTimeDigitized = 0x65789292, /* n ASCIIs */
  kQTExifUserDataExposureTime   = 0x6578829A, /* 1 RATIONAL */
  kQTExifUserDataFNumber        = 0x6578829D, /* 1 RATIONAL */
  kQTExifUserDataExposureProgram = 0x65788822, /* 1 SHORT */
  kQTExifUserDataSpectralSensitivity = 0x65788824, /* n ASCIIs */
  kQTExifUserDataISOSpeedRatings = 0x65788827, /* n SHORTs */
  kQTExifUserDataShutterSpeedValue = 0x65789201, /* 1 SIGNED RATIONAL */
  kQTExifUserDataApertureValue  = 0x65789202, /* 1 RATIONAL */
  kQTExifUserDataBrightnessValue = 0x65789203, /* 1 SIGNED RATIONAL */
  kQTExifUserDataExposureBiasValue = 0x65789204, /* 1 SIGNED RATIONAL */
  kQTExifUserDataMaxApertureValue = 0x65789205, /* 1 RATIONAL */
  kQTExifUserDataSubjectDistance = 0x65789206, /* 1 RATIONAL */
  kQTExifUserDataMeteringMode   = 0x65789207, /* 1 SHORT */
  kQTExifUserDataLightSource    = 0x65789208, /* 1 SHORT */
  kQTExifUserDataFlash          = 0x65789209, /* 1 SHORT */
  kQTExifUserDataFocalLength    = 0x6578920A, /* 1 RATIONAL */
  kQTExifUserDataFlashEnergy    = 0x6578A20B, /* 1 RATIONAL */
  kQTExifUserDataFocalPlaneXResolution = 0x6578A20E, /* 1 RATIONAL */
  kQTExifUserDataFocalPlaneYResolution = 0x6578A20F, /* 1 RATIONAL */
  kQTExifUserDataFocalPlaneResolutionUnit = 0x6578A210, /* 1 SHORT */
  kQTExifUserDataSubjectLocation = 0x6578A214, /* 1 SHORT */
  kQTExifUserDataExposureIndex  = 0x6578A215, /* 1 RATIONAL */
  kQTExifUserDataSensingMethod  = 0x6578A217, /* 1 SHORT */
  kQTExifUserDataFileSource     = 0x6578A300, /* 1 UNDEFINED */
  kQTExifUserDataSceneType      = 0x6578A301 /* 1 UNDEFINED */
};

/* Found in some Exif TIFF and Exif JPEG files; defined in the Exif 2.1 spec */
/* Note: these were wrong in the QuickTime 6.0 headers -- the high two bytes were 0x677 instead of 0x6770. */
enum {
  kQTExifUserDataGPSVersionID   = 0x67700000, /* 4 BYTEs */
  kQTExifUserDataGPSLatitudeRef = 0x67700001, /* 2 ASCIIs*/
  kQTExifUserDataGPSLatitude    = 0x67700002, /* 3 RATIONALs */
  kQTExifUserDataGPSLongitudeRef = 0x67700003, /* 2 ASCIIs */
  kQTExifUserDataGPSLongitude   = 0x67700004, /* 3 RATIONALs */
  kQTExifUserDataGPSAltitudeRef = 0x67700005, /* 1 BYTE */
  kQTExifUserDataGPSAltitude    = 0x67700006, /* 1 RATIONAL */
  kQTExifUserDataGPSTimeStamp   = 0x67700007, /* 3 RATIONALs */
  kQTExifUserDataGPSSatellites  = 0x67700008, /* n ASCIIs */
  kQTExifUserDataGPSStatus      = 0x67700009, /* 2 ASCIIs */
  kQTExifUserDataGPSMeasureMode = 0x6770000A, /* 2 ASCIIs */
  kQTExifUserDataGPSDOP         = 0x6770000B, /* 1 RATIONAL */
  kQTExifUserDataGPSSpeedRef    = 0x6770000C, /* 2 ASCIIs */
  kQTExifUserDataGPSSpeed       = 0x6770000D, /* 1 RATIONAL */
  kQTExifUserDataGPSTrackRef    = 0x6770000E, /* 2 ASCIIs */
  kQTExifUserDataGPSTrack       = 0x6770000F, /* 1 RATIONAL */
  kQTExifUserDataGPSImgDirectionRef = 0x67700010, /* 2 ASCIIs */
  kQTExifUserDataGPSImgDirection = 0x67700011, /* 1 RATIONAL */
  kQTExifUserDataGPSMapDatum    = 0x67700012, /* n ASCII */
  kQTExifUserDataGPSDestLatitudeRef = 0x67700013, /* 2 ASCIIs */
  kQTExifUserDataGPSDestLatitude = 0x67700014, /* 3 RATIONALs */
  kQTExifUserDataGPSDestLongitudeRef = 0x67700015, /* 2 ASCIIs */
  kQTExifUserDataGPSDestLongitude = 0x67700016, /* 3 RATIONALs */
  kQTExifUserDataGPSDestBearingRef = 0x67700017, /* 2 ASCIIs */
  kQTExifUserDataGPSDestBearing = 0x67700018, /* 1 RATIONAL */
  kQTExifUserDataGPSDestDistanceRef = 0x67700019, /* 2 ASCIIs */
  kQTExifUserDataGPSDestDistance = 0x6770001A /* 1 RATIONAL */
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
  OSType                    dataReType)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  OSType *                  dataReType)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  const FSSpec *            theFile)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  FSSpec *                  theFile)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Handle                    h)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Handle *                  h)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ImageDescriptionHandle *  desc)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long *           size)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long             dataSize)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  RgnHandle                 clipRgn)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  RgnHandle *               clipRgn)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  const Rect *              sourceRect)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Rect *                    sourceRect)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Rect *                    naturalBounds)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
GraphicsImportDraw(GraphicsImportComponent ci)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  GDHandle                  gd)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  GDHandle *                gd)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  const MatrixRecord *      matrix)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  MatrixRecord *            matrix)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  const Rect *              bounds)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Rect *                    bounds)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ScriptCode                scriptTag)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  const RGBColor *          opColor)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  RGBColor *                opColor)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  CodecQ                    quality)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  CodecQ *                  quality)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ScriptCode                scriptTag)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long             limit)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long *           limit)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  OSType *                  dataRefType)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Boolean *                 valid)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  void *                    userData)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  void *                    qtAtomContainerPtr)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  short *                   drawsAllPixels)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  PicHandle *               picture)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ScriptCode                scriptTag)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  void *                    qtAtomContainerPtr)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ScriptCode *              outScriptTag)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  void *                    qtAtomContainerPtr)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  void *                    qtAtomContainer)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMProgressProcRecordPtr   progressProc)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMProgressProcRecordPtr   progressProc)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long *           imageCount)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long             imageIndex)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long *           imageIndex)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  wide *                    size)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long             dataSize)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  const wide *              limit)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  wide *                    limit)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  MatrixRecord *            defaultMatrix)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  RgnHandle *               defaultRgn)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  RGBColor *                defaultOpColor)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Rect *                    defaultSourceRect)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Handle *                  profile)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  const Rect *              destRect)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Rect *                    destRect)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long                      flags)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long *                    flags)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  wide *                    size)                             AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  GraphicsImportSetImageIndexToThumbnail()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern ComponentResult 
GraphicsImportSetImageIndexToThumbnail(GraphicsImportComponent ci) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


#if TARGET_API_MAC_OSX
/*
 *  GraphicsImportCreateCGImage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
GraphicsImportCreateCGImage(
  GraphicsImportComponent   ci,
  CGImageRef *              imageRefOut,
  UInt32                    flags)                            AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


#endif  /* TARGET_API_MAC_OSX */

/*
 *  GraphicsImportSaveAsPictureToDataRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern ComponentResult 
GraphicsImportSaveAsPictureToDataRef(
  GraphicsImportComponent   ci,
  Handle                    dataRef,
  OSType                    dataRefType)                      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  GraphicsImportSaveAsQuickTimeImageFileToDataRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern ComponentResult 
GraphicsImportSaveAsQuickTimeImageFileToDataRef(
  GraphicsImportComponent   ci,
  Handle                    dataRef,
  OSType                    dataRefType)                      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  GraphicsImportExportImageFileToDataRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern ComponentResult 
GraphicsImportExportImageFileToDataRef(
  GraphicsImportComponent   ci,
  OSType                    fileType,
  OSType                    fileCreator,
  Handle                    dataRef,
  OSType                    dataRefType)                      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  GraphicsImportDoExportImageFileToDataRefDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern ComponentResult 
GraphicsImportDoExportImageFileToDataRefDialog(
  GraphicsImportComponent   ci,
  Handle                    inDataRef,
  OSType                    inDataRefType,
  CFStringRef               prompt,
  ModalFilterYDUPP          filterProc,
  OSType *                  outExportedType,
  Handle *                  outDataRef,
  OSType *                  outDataRefType)                   AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


#if TARGET_API_MAC_OSX
/* NOTE: If the source override ColorSync profile is NULL, then the image's ColorSync profile may be used if available, otherwise a generic ColorSync profile may be used. */
/*
 *  GraphicsImportSetOverrideSourceColorSyncProfileRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
GraphicsImportSetOverrideSourceColorSyncProfileRef(
  GraphicsImportComponent   ci,
  CMProfileRef              newOverrideSourceProfileRef)      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  GraphicsImportGetOverrideSourceColorSyncProfileRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
GraphicsImportGetOverrideSourceColorSyncProfileRef(
  GraphicsImportComponent   ci,
  CMProfileRef *            outOverrideSourceProfileRef)      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/* NOTE: If the destination ColorSync profile is NULL, then a generic ColorSync profile may be used. */
/*
 *  GraphicsImportSetDestinationColorSyncProfileRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
GraphicsImportSetDestinationColorSyncProfileRef(
  GraphicsImportComponent   ci,
  CMProfileRef              newDestinationProfileRef)         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  GraphicsImportGetDestinationColorSyncProfileRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
GraphicsImportGetDestinationColorSyncProfileRef(
  GraphicsImportComponent   ci,
  CMProfileRef *            destinationProfileRef)            AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


#endif  /* TARGET_API_MAC_OSX */

/*
 *  GraphicsImportWillUseColorMatching()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern ComponentResult 
GraphicsImportWillUseColorMatching(
  GraphicsImportComponent   ci,
  Boolean *                 outWillMatch)                     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


#if TARGET_API_MAC_OSX
/* This convenience API is implemented by the base graphics importer for format-specific importers. */
/*
 *  GraphicsImportGetGenericColorSyncProfile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
GraphicsImportGetGenericColorSyncProfile(
  GraphicsImportComponent   ci,
  OSType                    pixelFormat,
  void *                    reservedSetToNULL,
  UInt32                    flags,
  Handle *                  genericColorSyncProfileOut)       AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


#endif  /* TARGET_API_MAC_OSX */

/* Format-specific importers that implement GetColorSyncProfile and that want the base graphics 
   importer to automatically support ColorSync matching should:
   (a) implement GraphicsImportSetReturnGenericColorSyncProfile; when it is called, set an internal flag
   (b) change GraphicsImportGetColorSyncProfile so that, if this internal flag is set,
       when the source image file contains a profile 
       and the kGraphicsImporterDontUseColorMatching flag is NOT set,
       it returns a generic profile of the appropriate colorspace instead.
   Other importers should *not* implement GraphicsImportSetReturnGenericColorSyncProfile. */
/* WARNING: Applications should not call this API; it is internal graphics importer plumbing.
   Set kGraphicsImporterDontUseColorMatching instead. */
/*
 *  GraphicsImportSetReturnGenericColorSyncProfile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern ComponentResult 
GraphicsImportSetReturnGenericColorSyncProfile(
  GraphicsImportComponent   ci,
  Boolean                   returnGenericProfilesUnlessDontMatchFlagSet) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/* WARNING: Applications should not call this API; it is internal graphics importer plumbing. */
/*
 *  GraphicsImportGetReturnGenericColorSyncProfile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern ComponentResult 
GraphicsImportGetReturnGenericColorSyncProfile(
  GraphicsImportComponent   ci,
  Boolean *                 returnGenericProfilesUnlessDontMatchFlagSet) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;




typedef ComponentInstance               GraphicsExportComponent;
enum {
  GraphicsExporterComponentType = 'grex',
  kBaseGraphicsExporterSubType  = 'base'
};

/* Component flags for Graphics Exporter components */
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

enum {
  kQTJPEGQuantizationTables     = 'jpqt',
  kQTJPEGHuffmanTables          = 'jpht'
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
  unsigned long *           actualSizeWritten)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Boolean *                 canTranscode)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
GraphicsExportDoTranscode(GraphicsExportComponent ci)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  void *                    codecSettingsAtomContainerPtr)    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ImageDescriptionHandle *  outDesc)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
GraphicsExportDoStandaloneExport(GraphicsExportComponent ci)  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  OSType *                  fileCreator)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  OSType *                  fileNameExtension)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  void *                    qtAtomContainerPtr)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* (1 unused selector) */
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
  void *                    yourDataProc)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  void *                    qtAtomContainer)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  void *                    qtAtomContainerPtr)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Handle *                  theText)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Boolean                   dontRecompress)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Boolean *                 dontRecompress)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long             interlaceStyle)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long *           interlaceStyle)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  void *                    userData)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  void *                    userData)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long             targetDataSize)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long *           targetDataSize)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long                      compressionMethod)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long *                    compressionMethod)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  CodecQ                    spatialQuality)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  CodecQ *                  spatialQuality)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Fixed                     verticalResolution)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Fixed *                   verticalResolution)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long                      depth)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long *                    depth)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* (2 unused selectors) */
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
  Handle                    colorSyncProfile)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Handle *                  colorSyncProfile)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMProgressProcRecordPtr   progressProc)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ICMProgressProcRecordPtr   progressProc)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ImageDescriptionHandle    desc)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  OSType *                  dataRefType)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ImageDescriptionHandle    desc)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  FSSpec *                  theFile)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ImageDescriptionHandle    desc)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Handle *                  h)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ImageDescriptionHandle    desc)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long *           size)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  GraphicsImportComponent   grip)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  GraphicsImportComponent *  grip)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  PicHandle                 picture)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  PicHandle *               picture)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  GWorldPtr                 gworld)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  GWorldPtr *               gworld)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  PixMapHandle              pixmap)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  PixMapHandle *            pixmap)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long             limit)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long *           limit)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Boolean *                 mayReadInputData)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long *           size)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long             dataSize)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ImageDescriptionHandle *  desc)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Rect *                    dimensions)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long *                    inputDepth)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  const Rect *              dstRect)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  OSType                    dataRefType)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  OSType *                  dataRefType)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  const FSSpec *            theFile)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  FSSpec *                  theFile)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Handle                    h)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Handle *                  h)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Boolean                   truncateFile)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Boolean *                 truncateFile)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  OSType                    fileCreator)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  OSType *                  fileCreator)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long             dataSize)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long             mark)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long *           mark)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  unsigned long             dataSize)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long                      maxThumbnailHeight)               AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


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
  long *                    maxThumbnailHeight)               AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


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
  Boolean                   enableExif)                       AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


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
  Boolean *                 exifEnabled)                      AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


#if TARGET_API_MAC_OSX
/*
 *  GraphicsExportSetInputCGImage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
GraphicsExportSetInputCGImage(
  GraphicsExportComponent   ci,
  CGImageRef                imageRef)                         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  GraphicsExportGetInputCGImage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
GraphicsExportGetInputCGImage(
  GraphicsExportComponent   ci,
  CGImageRef *              imageRefOut)                      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  GraphicsExportSetInputCGBitmapContext()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
GraphicsExportSetInputCGBitmapContext(
  GraphicsExportComponent   ci,
  CGContextRef              bitmapContextRef)                 AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  GraphicsExportGetInputCGBitmapContext()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
GraphicsExportGetInputCGBitmapContext(
  GraphicsExportComponent   ci,
  CGContextRef *            bitmapContextRefOut)              AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


#endif  /* TARGET_API_MAC_OSX */

/*
 *  GraphicsExportSetFlags()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
GraphicsExportSetFlags(
  GraphicsExportComponent   ci,
  UInt32                    flags)                            AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  GraphicsExportGetFlags()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
GraphicsExportGetFlags(
  GraphicsExportComponent   ci,
  UInt32 *                  flagsOut)                         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;




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
  long                       dataSize)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long *                     dstDataSize)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  void *                     dstData)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
ImageTranscoderEndSequence(ImageTranscoderComponent itc)      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




#if (MAC_OS_X_VERSION_MAX_ALLOWED == MAC_OS_X_VERSION_10_2) || !defined(kComponentPropertyListenerCollectionContextVersion)



/* MixedMode ProcInfo constants for component property calls */
enum {
    uppCallComponentGetComponentPropertyInfoProcInfo = 0x0003FFF0,
    uppCallComponentGetComponentPropertyProcInfo = 0x0003FFF0,
    uppCallComponentSetComponentPropertyProcInfo = 0x0000FFF0,
    uppCallComponentAddComponentPropertyListenerProcInfo = 0x0000FFF0,
    uppCallComponentRemoveComponentPropertyListenerProcInfo = 0x0000FFF0
};



/* == CallComponentGetComponentPropertyInfo flags == */
enum {
  kComponentPropertyFlagCanSetLater = (1L << 0),
  kComponentPropertyFlagCanSetNow = (1L << 1),
  kComponentPropertyFlagCanGetLater = (1L << 2),
  kComponentPropertyFlagCanGetNow = (1L << 3),
  kComponentPropertyFlagHasExtendedInfo = (1L << 4),
  kComponentPropertyFlagValueMustBeReleased = (1L << 5),
  kComponentPropertyFlagValueIsCFTypeRef = (1L << 6),
  kComponentPropertyFlagGetBufferMustBeInitialized = (1L << 7),
  kComponentPropertyFlagWillNotifyListeners = (1L << 8)
};


typedef OSType                          ComponentPropertyClass;
typedef OSType                          ComponentPropertyID;
typedef OSType                          ComponentValueType;
typedef void *                          ComponentValuePtr;
typedef const void *                    ConstComponentValuePtr;

/* == standard property class constants == */
enum {
  kComponentPropertyClassPropertyInfo = 'pnfo', /* property info class */
                                        /* property info property IDs */
  kComponentPropertyInfoList    = 'list', /* array of ComponentPropertyInfo (CFData), one for each property */
  kComponentPropertyCacheSeed   = 'seed', /* property cache seed value */
  kComponentPropertyCacheFlags  = 'flgs', /* see kComponentPropertyCache flags */
  kComponentPropertyExtendedInfo = 'meta' /* CFDictionary with extended property information*/
};


/* values for kComponentPropertyClassPropertyInfo/kComponentPropertyCacheFlags standard component property */
enum {
  kComponentPropertyCacheFlagNotPersistent = (1L << 0), /* property metadata should not be saved in persistent cache*/
  kComponentPropertyCacheFlagIsDynamic = (1L << 1) /* property metadata should not cached at all*/
};


struct ComponentPropertyInfo {
  ComponentPropertyClass  propClass;
  ComponentPropertyID  propID;
  ComponentValueType  propType;
  ByteCount           propSize;
  UInt32              propFlags;
};
typedef struct ComponentPropertyInfo    ComponentPropertyInfo;


#endif  /* #MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED */ 



/* == "QT" prefixed Component Property calls == */

typedef CALLBACK_API( void , QTComponentPropertyListenerProcPtr )(ComponentInstance inComponent, ComponentPropertyClass inPropClass, ComponentPropertyID inPropID, void *inUserData);
typedef STACK_UPP_TYPE(QTComponentPropertyListenerProcPtr)      QTComponentPropertyListenerUPP;




/*
 *  QTGetComponentPropertyInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
QTGetComponentPropertyInfo(
  ComponentInstance        inComponent,
  ComponentPropertyClass   inPropClass,
  ComponentPropertyID      inPropID,
  ComponentValueType *     outPropType,            /* can be NULL */
  ByteCount *              outPropValueSize,       /* can be NULL */
  UInt32 *                 outPropertyFlags)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QTGetComponentProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
QTGetComponentProperty(
  ComponentInstance        inComponent,
  ComponentPropertyClass   inPropClass,
  ComponentPropertyID      inPropID,
  ByteCount                inPropValueSize,
  ComponentValuePtr        outPropValueAddress,
  ByteCount *              outPropValueSizeUsed)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QTSetComponentProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
QTSetComponentProperty(
  ComponentInstance        inComponent,
  ComponentPropertyClass   inPropClass,
  ComponentPropertyID      inPropID,
  ByteCount                inPropValueSize,
  ConstComponentValuePtr   inPropValueAddress)                AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  QTAddComponentPropertyListener()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
QTAddComponentPropertyListener(
  ComponentInstance                inComponent,
  ComponentPropertyClass           inPropClass,
  ComponentPropertyID              inPropID,
  QTComponentPropertyListenerUPP   inDispatchProc,
  void *                           inUserData)           /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QTRemoveComponentPropertyListener()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
QTRemoveComponentPropertyListener(
  ComponentInstance                inComponent,
  ComponentPropertyClass           inPropClass,
  ComponentPropertyID              inPropID,
  QTComponentPropertyListenerUPP   inDispatchProc,
  void *                           inUserData)           /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;




/* == "QT" prefixed Component Property Listener helpers == */


typedef CFTypeRef                       QTComponentPropertyListenersRef;
typedef struct QTComponentPropertyListenerCollectionContext  QTComponentPropertyListenerCollectionContext;
typedef CALLBACK_API( Boolean , QTComponentPropertyListenerFilterProcPtr )(QTComponentPropertyListenersRef inCollection, const QTComponentPropertyListenerCollectionContext *inCollectionContext, ComponentInstance inNotifier, ComponentPropertyClass inPropClass, ComponentPropertyID inPropID, QTComponentPropertyListenerUPP inListenerCallbackProc, const void *inListenerProcRefCon, const void *inFilterProcRefCon);
typedef STACK_UPP_TYPE(QTComponentPropertyListenerFilterProcPtr)  QTComponentPropertyListenerFilterUPP;
#define kQTComponentPropertyListenerCollectionContextVersion 1
struct QTComponentPropertyListenerCollectionContext {
  UInt32              version;                /* struct version */
  QTComponentPropertyListenerFilterUPP  filterProcUPP;
  void *              filterProcData;
};

/*
 *  NewQTComponentPropertyListenerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QTComponentPropertyListenerUPP
NewQTComponentPropertyListenerUPP(QTComponentPropertyListenerProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  NewQTComponentPropertyListenerFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QTComponentPropertyListenerFilterUPP
NewQTComponentPropertyListenerFilterUPP(QTComponentPropertyListenerFilterProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  DisposeQTComponentPropertyListenerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQTComponentPropertyListenerUPP(QTComponentPropertyListenerUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  DisposeQTComponentPropertyListenerFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQTComponentPropertyListenerFilterUPP(QTComponentPropertyListenerFilterUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  InvokeQTComponentPropertyListenerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQTComponentPropertyListenerUPP(
  ComponentInstance               inComponent,
  ComponentPropertyClass          inPropClass,
  ComponentPropertyID             inPropID,
  void *                          inUserData,
  QTComponentPropertyListenerUPP  userUPP)                    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  InvokeQTComponentPropertyListenerFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeQTComponentPropertyListenerFilterUPP(
  QTComponentPropertyListenersRef                       inCollection,
  const QTComponentPropertyListenerCollectionContext *  inCollectionContext,
  ComponentInstance                                     inNotifier,
  ComponentPropertyClass                                inPropClass,
  ComponentPropertyID                                   inPropID,
  QTComponentPropertyListenerUPP                        inListenerCallbackProc,
  const void *                                          inListenerProcRefCon,
  const void *                                          inFilterProcRefCon,
  QTComponentPropertyListenerFilterUPP                  userUPP) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

#if __MACH__
  #ifdef __cplusplus
    inline QTComponentPropertyListenerUPP                       NewQTComponentPropertyListenerUPP(QTComponentPropertyListenerProcPtr userRoutine) { return userRoutine; }
    inline QTComponentPropertyListenerFilterUPP                 NewQTComponentPropertyListenerFilterUPP(QTComponentPropertyListenerFilterProcPtr userRoutine) { return userRoutine; }
    inline void                                                 DisposeQTComponentPropertyListenerUPP(QTComponentPropertyListenerUPP) { }
    inline void                                                 DisposeQTComponentPropertyListenerFilterUPP(QTComponentPropertyListenerFilterUPP) { }
    inline void                                                 InvokeQTComponentPropertyListenerUPP(ComponentInstance inComponent, ComponentPropertyClass inPropClass, ComponentPropertyID inPropID, void * inUserData, QTComponentPropertyListenerUPP userUPP) { (*userUPP)(inComponent, inPropClass, inPropID, inUserData); }
    inline Boolean                                              InvokeQTComponentPropertyListenerFilterUPP(QTComponentPropertyListenersRef inCollection, const QTComponentPropertyListenerCollectionContext * inCollectionContext, ComponentInstance inNotifier, ComponentPropertyClass inPropClass, ComponentPropertyID inPropID, QTComponentPropertyListenerUPP inListenerCallbackProc, const void * inListenerProcRefCon, const void * inFilterProcRefCon, QTComponentPropertyListenerFilterUPP userUPP) { return (*userUPP)(inCollection, inCollectionContext, inNotifier, inPropClass, inPropID, inListenerCallbackProc, inListenerProcRefCon, inFilterProcRefCon); }
  #else
    #define NewQTComponentPropertyListenerUPP(userRoutine)      ((QTComponentPropertyListenerUPP)userRoutine)
    #define NewQTComponentPropertyListenerFilterUPP(userRoutine) ((QTComponentPropertyListenerFilterUPP)userRoutine)
    #define DisposeQTComponentPropertyListenerUPP(userUPP)
    #define DisposeQTComponentPropertyListenerFilterUPP(userUPP)
    #define InvokeQTComponentPropertyListenerUPP(inComponent, inPropClass, inPropID, inUserData, userUPP) (*userUPP)(inComponent, inPropClass, inPropID, inUserData)
    #define InvokeQTComponentPropertyListenerFilterUPP(inCollection, inCollectionContext, inNotifier, inPropClass, inPropID, inListenerCallbackProc, inListenerProcRefCon, inFilterProcRefCon, userUPP) (*userUPP)(inCollection, inCollectionContext, inNotifier, inPropClass, inPropID, inListenerCallbackProc, inListenerProcRefCon, inFilterProcRefCon)
  #endif
#endif

/*
 *  QTComponentPropertyListenerCollectionCreate()
 *  
 *  Summary:
 *    Create a collection to use with the functions
 *    ComponentPropertyListenerCollectionAddListener,
 *    ComponentPropertyListenerCollectionRemoveListener,
 *    ComponentPropertyListenerCollectionNotifyListeners,
 *    ComponentPropertyListenerCollectionIsEmpty, and
 *    ComponentPropertyListenerCollectionHasListenersForProperty.
 *  
 *  Parameters:
 *    
 *    outCollection:
 *      Returns the new, empty, listener collection.
 *    
 *    inAllocator:
 *      Allocator used to create the collection and it's contents.
 *    
 *    inContext:
 *      The listener collection context. May be NULL.  A copy of the
 *      contents of the structure is made, so a pointer to a structure
 *      on the stack can be passed.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QTComponentPropertyListenerCollectionCreate(
  CFAllocatorRef                                        inAllocator,         /* can be NULL */
  const QTComponentPropertyListenerCollectionContext *  inContext,           /* can be NULL */
  QTComponentPropertyListenersRef *                     outCollection) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  QTComponentPropertyListenerCollectionAddListener()
 *  
 *  Summary:
 *    Add a listener callback for the specified property class and ID
 *    to a property listener collection.
 *  
 *  Parameters:
 *    
 *    inCollection:
 *      The property listener collection.
 *    
 *    inPropClass:
 *      The property class.
 *    
 *    inPropID:
 *      The property ID.
 *    
 *    inListenerProc:
 *      The property listener callback function.
 *    
 *    inListenerProcRefCon:
 *      The data parameter to pass to the listener callback function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QTComponentPropertyListenerCollectionAddListener(
  QTComponentPropertyListenersRef   inCollection,
  ComponentPropertyClass            inPropClass,
  ComponentPropertyID               inPropID,
  QTComponentPropertyListenerUPP    inListenerProc,
  const void *                      inListenerProcRefCon)     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QTComponentPropertyListenerCollectionRemoveListener()
 *  
 *  Summary:
 *    Remove a listener callback for the specified property class and
 *    ID from a property listener collection.
 *  
 *  Parameters:
 *    
 *    inCollection:
 *      The property listener collection.
 *    
 *    inPropClass:
 *      The property class.
 *    
 *    inPropID:
 *      The property ID.
 *    
 *    inListenerProc:
 *      The property listener callback function.
 *    
 *    inListenerProcRefCon:
 *      The data parameter to pass to the listener callback function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QTComponentPropertyListenerCollectionRemoveListener(
  QTComponentPropertyListenersRef   inCollection,
  ComponentPropertyClass            inPropClass,
  ComponentPropertyID               inPropID,
  QTComponentPropertyListenerUPP    inListenerProc,
  const void *                      inListenerProcRefCon)     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QTComponentPropertyListenerCollectionNotifyListeners()
 *  
 *  Summary:
 *    Call all listener callbacks in the collection registered for the
 *    specified property class and ID.
 *  
 *  Discussion:
 *    If the "filterProcUPP" in the collection's context is non-NULL,
 *    the filter function will be called before each registered
 *    listener that matches the specified property class and ID. If the
 *    filter function return false, the listener proc will not be
 *    called. This is intended to allow a component to change the
 *    calling semantics (call another thread, etc), to use a different
 *    listener callback signature, etc.
 *  
 *  Parameters:
 *    
 *    inCollection:
 *      The property listener collection.
 *    
 *    inNotifier:
 *      The calling ComponentInstance.
 *    
 *    inPropClass:
 *      The property class.
 *    
 *    inPropID:
 *      The property ID.
 *    
 *    inFilterProcRefCon:
 *      The data parameter to pass to the filter function.
 *    
 *    inFlags:
 *      Flags.  Must be set to 0.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QTComponentPropertyListenerCollectionNotifyListeners(
  QTComponentPropertyListenersRef   inCollection,
  ComponentInstance                 inNotifier,
  ComponentPropertyClass            inPropClass,
  ComponentPropertyID               inPropID,
  const void *                      inFilterProcRefCon,       /* can be NULL */
  UInt32                            inFlags)                  AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QTComponentPropertyListenerCollectionIsEmpty()
 *  
 *  Summary:
 *    Return true if the listener collection is empty.
 *  
 *  Parameters:
 *    
 *    inCollection:
 *      The property listener collection.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
QTComponentPropertyListenerCollectionIsEmpty(QTComponentPropertyListenersRef inCollection) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QTComponentPropertyListenerCollectionHasListenersForProperty()
 *  
 *  Summary:
 *    Returns true if there are any listeners registered for the
 *    specified property class and ID.
 *  
 *  Parameters:
 *    
 *    inCollection:
 *      The property listener collection.
 *    
 *    inPropClass:
 *      The property class.
 *    
 *    inPropID:
 *      The property ID.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
QTComponentPropertyListenerCollectionHasListenersForProperty(
  QTComponentPropertyListenersRef   inCollection,
  ComponentPropertyClass            inPropClass,
  ComponentPropertyID               inPropID)                 AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/* DRM properties*/
enum {
  kQTPropertyClass_DRM          = 'drm '
};

enum {
  kQTDRMPropertyID_InteractWithUser = 'shui', /* Boolean**/
  kQTDRMPropertyID_IsProtected  = 'prot', /* Boolean**/
  kQTDRMPropertyID_IsAuthorized = 'auth' /* Boolean**/
};



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
    kGraphicsImportSetImageIndexToThumbnailSelect = 0x003E,
    kGraphicsImportCreateCGImageSelect         = 0x003F,
    kGraphicsImportSaveAsPictureToDataRefSelect = 0x0040,
    kGraphicsImportSaveAsQuickTimeImageFileToDataRefSelect = 0x0041,
    kGraphicsImportExportImageFileToDataRefSelect = 0x0042,
    kGraphicsImportDoExportImageFileToDataRefDialogSelect = 0x0043,
    kGraphicsImportSetOverrideSourceColorSyncProfileRefSelect = 0x0044,
    kGraphicsImportGetOverrideSourceColorSyncProfileRefSelect = 0x0045,
    kGraphicsImportSetDestinationColorSyncProfileRefSelect = 0x0046,
    kGraphicsImportGetDestinationColorSyncProfileRefSelect = 0x0047,
    kGraphicsImportWillUseColorMatchingSelect  = 0x0048,
    kGraphicsImportGetGenericColorSyncProfileSelect = 0x0049,
    kGraphicsImportSetReturnGenericColorSyncProfileSelect = 0x004A,
    kGraphicsImportGetReturnGenericColorSyncProfileSelect = 0x004B,
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
    kGraphicsExportSetInputCGImageSelect       = 0x0050,
    kGraphicsExportGetInputCGImageSelect       = 0x0051,
    kGraphicsExportSetInputCGBitmapContextSelect = 0x0052,
    kGraphicsExportGetInputCGBitmapContextSelect = 0x0053,
    kGraphicsExportSetFlagsSelect              = 0x0054,
    kGraphicsExportGetFlagsSelect              = 0x0055,
    kImageTranscoderBeginSequenceSelect        = 0x0001,
    kImageTranscoderConvertSelect              = 0x0002,
    kImageTranscoderDisposeDataSelect          = 0x0003,
    kImageTranscoderEndSequenceSelect          = 0x0004,
    kQTGetComponentPropertyInfoSelect          = -11,
    kQTGetComponentPropertySelect              = -12,
    kQTSetComponentPropertySelect              = -13,
    kQTAddComponentPropertyListenerSelect      = -14,
    kQTRemoveComponentPropertyListenerSelect   = -15
};
/* Aperture modes */

/*
 *  Summary:
 *    Aperture modes
 *  
 *  Discussion:
 *    You can set the aperture mode property on a movie to indicate
 *    whether aspect ratio and clean aperture correction should be
 *    performed (kQTPropertyClass_Visual /
 *    kQTVisualPropertyID_ApertureMode). When a movie is in clean,
 *    production or encoded pixels aperture mode, each track's
 *    dimensions are overriden by special dimensions for that mode. The
 *    original track dimensions are preserved and can be restored by
 *    setting the movie into classic aperture mode. Aperture modes are
 *    not saved in movies. 
 *    You can set the aperture mode property on a decompression session
 *    options object to indicate whether pixel buffers should be tagged
 *    to enable aspect ratio and clean aperture correction
 *    (kQTPropertyClass_ICMDecompressionSessionOptions /
 *    kICMDecompressionSessionOptionsPropertyID_ApertureMode).
 */
enum {

  /*
   * An aperture mode which gives compatibility with behavior in
   * QuickTime 7.0.x and earlier. 
   * A movie in classic aperture mode uses track dimensions as set in
   * NewMovieTrack and SetTrackDimensions. 
   * A decompression session in classic aperture mode does not set the
   * clean aperture or pixel aspect ratio attachments on emitted pixel
   * buffers. 
   * Movies default to classic aperture mode. If you call
   * SetTrackDimensions on a track, the movie is automatically switched
   * into classic aperture mode.
   */
  kQTApertureMode_Classic       = 'clas',

  /*
   * An aperture mode for general display. 
   * Where possible, video will be displayed at the correct pixel
   * aspect ratio, trimmed to the clean aperture. A movie in clean
   * aperture mode sets each track's dimensions to match its
   * kQTVisualPropertyID_CleanApertureDimensions. 
   * A decompression session in clean aperture mode sets the clean
   * aperture and pixel aspect ratio attachments on emitted pixel
   * buffers based on the image description.
   */
  kQTApertureMode_CleanAperture = 'clea',

  /*
   * An aperture mode for modal use in authoring applications. 
   *  Where possible, video will be displayed at the correct pixel
   * aspect ratio, but without trimming to the clean aperture so that
   * the edge processing region can be viewed. A movie in production
   * aperture mode sets each track's dimensions to match its
   * kQTVisualPropertyID_ProductionApertureDimensions. 
   * A decompression session in production aperture mode sets the pixel
   * aspect ratio attachments on emitted pixel buffers based on the
   * image description.
   */
  kQTApertureMode_ProductionAperture = 'prod',

  /*
   * An aperture mode for technical use. 
   * Displays all encoded pixels with no aspect ratio or clean aperture
   * compensation. A movie in encoded pixels aperture mode sets each
   * track's dimensions to match its
   * kQTVisualPropertyID_EncodedPixelsDimensions. 
   * A decompression session in encoded pixels aperture mode does not
   * set the clean aperture or pixel aspect ratio attachments on
   * emitted pixel buffers.
   */
  kQTApertureMode_EncodedPixels = 'enco'
};

/* Property interface for Image Descriptions */

/*
 *  Summary:
 *    Properties of image descriptions.
 */
enum {

  /*
   * Class identifier for image description properties.
   */
  kQTPropertyClass_ImageDescription = 'idsc',

  /*
   * The width of the encoded image. Usually, but not always, this is
   * the ImageDescription's width field.
   */
  kICMImageDescriptionPropertyID_EncodedWidth = 'encw', /* SInt32, Read/Write */

  /*
   * The height of the encoded image. Usually, but not always, this is
   * the ImageDescription's height field.
   */
  kICMImageDescriptionPropertyID_EncodedHeight = 'ench', /* SInt32, Read/Write */

  /*
   * Describes the clean aperture of the buffer. If not specified
   * explicitly in the image description, the default clean aperture
   * (full encoded width and height) will be returned.
   */
  kICMImageDescriptionPropertyID_CleanAperture = 'clap', /* Native-endian CleanApertureImageDescriptionExtension, Read/Write */

  /*
   * Describes the pixel aspect ratio. If not specified explicitly in
   * the image description, a square (1:1) pixel aspect ratio will be
   * returned.
   */
  kICMImageDescriptionPropertyID_PixelAspectRatio = 'pasp', /* Native-endian PixelAspectRatioImageDescriptionExtension, Read/Write */

  /*
   * Dimensions at which the image could be displayed on a square-pixel
   * display, generally calculated using the clean aperture and pixel
   * aspect ratio. 
   * Note that this value is returned as a FixedPoint; the width and
   * height can also be read separately as rounded SInt32s via
   * kICMImageDescriptionPropertyID_CleanApertureDisplayWidth and
   * kICMImageDescriptionPropertyID_CleanApertureDisplayHeight.
   */
  kICMImageDescriptionPropertyID_CleanApertureDisplayDimensions = 'cadi', /* FixedPoint, Read */

  /*
   * Dimensions at which the image could be displayed on a square-pixel
   * display, disregarding any clean aperture but honoring the pixel
   * aspect ratio. This may be useful for authoring applications that
   * want to expose the edge processing region. For general viewing,
   * use kICMImageDescriptionPropertyID_CleanApertureDimensions
   * instead. 
   * Note that this value is returned as a FixedPoint; the width and
   * height can also be read separately as rounded SInt32s via
   * kICMImageDescriptionPropertyID_ProductionApertureDisplayWidth and
   * kICMImageDescriptionPropertyID_ProductionApertureDisplayHeight.
   */
  kICMImageDescriptionPropertyID_ProductionApertureDisplayDimensions = 'prdi', /* FixedPoint, Read */

  /*
   * Dimensions of the encoded image. 
   * Note that this value is returned as a FixedPoint for convenience;
   * the width and height can also be read separately as SInt32s via
   * kICMImageDescriptionPropertyID_EncodedWidth and
   * kICMImageDescriptionPropertyID_EncodedHeight.
   */
  kICMImageDescriptionPropertyID_EncodedPixelsDimensions = 'endi', /* FixedPoint, Read */

  /*
   * A width at which the image could be displayed on a square-pixel
   * display, possibly calculated using the clean aperture and pixel
   * aspect ratio.
   */
  kICMImageDescriptionPropertyID_CleanApertureDisplayWidth = 'disw', /* SInt32, Read */

  /*
   * A height at which the image could be displayed on a square-pixel
   * display, possibly calculated using the clean aperture and pixel
   * aspect ratio.
   */
  kICMImageDescriptionPropertyID_CleanApertureDisplayHeight = 'dish', /* SInt32, Read */

  /*
   * A width at which the image could be displayed on a square-pixel
   * display, disregarding any clean aperture but honoring the pixel
   * aspect ratio. This may be useful for authoring applications that
   * want to expose the edge processing region. For general viewing,
   * use kICMImageDescriptionPropertyID_CleanApertureDisplayWidth
   * instead.
   */
  kICMImageDescriptionPropertyID_ProductionApertureDisplayWidth = 'pdsw', /* SInt32, Read */

  /*
   * A height at which the image could be displayed on a square-pixel
   * display, disregarding any clean aperture but honoring the pixel
   * aspect ratio. This may be useful for authoring applications that
   * want to expose the edge processing region. For general viewing,
   * use kICMImageDescriptionPropertyID_CleanApertureDisplayHeight
   * instead.
   */
  kICMImageDescriptionPropertyID_ProductionApertureDisplayHeight = 'pdsh', /* SInt32, Read */

  /*
   * Synonym for
   * kICMImageDescriptionPropertyID_CleanApertureDisplayWidth.
   */
  kICMImageDescriptionPropertyID_DisplayWidth = 'disw', /* SInt32, Read */

  /*
   * Synonym for
   * kICMImageDescriptionPropertyID_CleanApertureDisplayHeight.
   */
  kICMImageDescriptionPropertyID_DisplayHeight = 'dish', /* SInt32, Read */

  /*
   * Synonym for
   * kICMImageDescriptionPropertyID_ProductionApertureDisplayWidth.
   */
  kICMImageDescriptionPropertyID_ProductionDisplayWidth = 'pdsw', /* SInt32, Read */

  /*
   * Synonym for
   * kICMImageDescriptionPropertyID_ProductionApertureDisplayHeight.
   */
  kICMImageDescriptionPropertyID_ProductionDisplayHeight = 'pdsh', /* SInt32, Read */

  /*
   * Color information, if available in the
   * NCLCColorInfoImageDescriptionExtension format.
   */
  kICMImageDescriptionPropertyID_NCLCColorInfo = 'nclc', /* Native-endian NCLCColorInfoImageDescriptionExtension, Read/Write */

  /*
   * A CGColorSpaceRef for the colorspace described by the image
   * description, constructed from video color info or ICC Profile.
   * IMPORTANT NOTE: The YCbCr matrix from the video color info is not
   * represented in the CGColorSpaceRef. The caller of GetProperty is
   * responsible for releasing this, eg, by calling
   * CGColorSpaceRelease. Only supported on Mac OS X.
   */
  kICMImageDescriptionPropertyID_CGColorSpace = 'cgcs', /* CGColorSpaceRef, Read -- caller of GetProperty must call CGColorSpaceRelease */

  /*
   * A CFDataRef containing the serialized ICC profile described by the
   * image description. The caller of GetProperty is responsible for
   * releasing this, eg, by calling CFRelease.
   */
  kICMImageDescriptionPropertyID_ICCProfile = 'iccp', /* CFDataRef, Read/Write -- caller of GetProperty must call CFRelease */

  /*
   * The gamma level described by the image description.
   */
  kICMImageDescriptionPropertyID_GammaLevel = 'gama', /* Fixed, Read/Write */

  /*
   * Information about the number and order of fields, if available.
   */
  kICMImageDescriptionPropertyID_FieldInfo = 'fiel', /* FieldInfoImageDescriptionExtension2, Read/Write */

  /*
   * The offset in bytes from the start of one row to the next. Only
   * valid if the codec type is a chunky pixel format.
   */
  kICMImageDescriptionPropertyID_RowBytes = 'rowb', /* SInt32, Read/Write */

  /*
   * A track width suitable for passing to NewMovieTrack when creating
   * a new track to hold this image data.
   */
  kICMImageDescriptionPropertyID_ClassicTrackWidth = 'claw', /* Fixed, Read */

  /*
   * A track height suitable for passing to NewMovieTrack when creating
   * a new track to hold this image data.
   */
  kICMImageDescriptionPropertyID_ClassicTrackHeight = 'clah', /* Fixed, Read */

  /*
   * Defines a duration for quantizing time. This is applicable for
   * cases where a single media sample generates visual output that
   * varies continuously through its duration. By interpreting this
   * property, such a sample may be considered to have internal "step
   * points" at multiples of the stepping duration. This can be used to
   * throttle frame generation during playback, and when stepping using
   * InterestingTime APIs. Setting a step duration with value zero
   * removes any current step duration.
   */
  kICMImageDescriptionPropertyID_StepDuration = 'step', /* TimeRecord (base ignored), Read/Write */

  /*
   * The clean aperture as a FixedRect in source coordinates, within
   * the rectangle defined by the image description width and height,
   * suitable for use as a source rectangle in a decompression
   * sequence. 
   * For historical reasons, the DVCPROHD codecs store the production
   * aperture display dimensions in the image description width and
   * height; the actual encoded dimensions are smaller. For DVCPROHD,
   * the clip rect will be relative to the image description width and
   * height, not the encoded dimensions.
   */
  kICMImageDescriptionPropertyID_CleanApertureClipRect = 'cacr', /* FixedRect, Read */

  /*
   * A matrix transforming the clean aperture clip rect to the origin,
   * scaled to the clean aperture display dimensions. 
   * For historical reasons, the DVCPROHD codecs store the production
   * aperture display dimensions in the image description width and
   * height; the actual encoded dimensions are smaller. For DVCPROHD,
   * the matrix will be relative to the image description width and
   * height, not the encoded dimensions.
   */
  kICMImageDescriptionPropertyID_CleanApertureMatrix = 'camx', /* MatrixRecord, Read */

  /*
   * A matrix transforming the image to the origin, scaled to the
   * production aperture display dimensions. 
   * For historical reasons, the DVCPROHD codecs store the production
   * aperture display dimensions in the image description width and
   * height; the actual encoded dimensions are smaller. For DVCPROHD,
   * the matrix will be relative to the image description width and
   * height, not the encoded dimensions.
   */
  kICMImageDescriptionPropertyID_ProductionApertureMatrix = 'pamx', /* MatrixRecord, Read */

  /*
   * A localized, human readable string summarizing the image as a
   * CFString, ie: "Apple DV, 720 x 480 (640 x 480), Millions". 
   *  The elements are: the codec name, the encoded pixels dimensions,
   * then parenthetically the clean aperture mode dimensions, but only
   * if they are different from the encoded pixels dimensions; then the
   * depth. 
   * The codec name shall be from the localized decompressor component
   * name string if exactly one decompressor with the correct cType is
   * available; otherwise the string in the image description shall be
   * used. The caller of GetProperty is responsible for releasing this
   * CFString, eg, by calling CFRelease.
   */
  kICMImageDescriptionPropertyID_SummaryString = 'isum' /* CFStringRef, Read - caller of GetProperty must call CFRelease*/
};

/*
 *  ICMImageDescriptionGetPropertyInfo()
 *  
 *  Summary:
 *    Gets info about a particular property of a ImageDescription.
 *  
 *  Parameters:
 *    
 *    inDesc:
 *      ImageDescriptionHandle being interrogated
 *    
 *    inPropClass:
 *      The class of property being requested
 *    
 *    inPropID:
 *      The ID of the property being requested
 *    
 *    outPropType:
 *      The type of property is returned here (can be NULL)
 *    
 *    outPropValueSize:
 *      The size of property is returned here (can be NULL)
 *    
 *    outPropertyFlags:
 *      The property flags are returned here (can be NULL)
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMImageDescriptionGetPropertyInfo(
  ImageDescriptionHandle   inDesc,
  ComponentPropertyClass   inPropClass,
  ComponentPropertyID      inPropID,
  ComponentValueType *     outPropType,            /* can be NULL */
  ByteCount *              outPropValueSize,       /* can be NULL */
  UInt32 *                 outPropertyFlags)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMImageDescriptionGetProperty()
 *  
 *  Summary:
 *    Gets a particular property of a ImageDescriptionHandle.
 *  
 *  Parameters:
 *    
 *    inDesc:
 *      ImageDescriptionHandle being interrogated
 *    
 *    inPropClass:
 *      The class of property being requested
 *    
 *    inPropID:
 *      The ID of the property being requested
 *    
 *    inPropValueSize:
 *      The size of the property value buffer
 *    
 *    outPropValueAddress:
 *      Points to the buffer to receive the property value
 *    
 *    outPropValueSizeUsed:
 *      Points to a variable to receive the actual size of returned
 *      property value (can be NULL)
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMImageDescriptionGetProperty(
  ImageDescriptionHandle   inDesc,
  ComponentPropertyClass   inPropClass,
  ComponentPropertyID      inPropID,
  ByteCount                inPropValueSize,
  ComponentValuePtr        outPropValueAddress,
  ByteCount *              outPropValueSizeUsed)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMImageDescriptionSetProperty()
 *  
 *  Summary:
 *    Sets a particular property of a ImageDescriptionHandle.
 *  
 *  Parameters:
 *    
 *    inDesc:
 *      ImageDescriptionHandle being modified
 *    
 *    inPropClass:
 *      The class of property being set
 *    
 *    inPropID:
 *      The ID of the property being set
 *    
 *    inPropValueSize:
 *      The size of property value
 *    
 *    inPropValueAddress:
 *      Points to the property value buffer
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMImageDescriptionSetProperty(
  ImageDescriptionHandle   inDesc,
  ComponentPropertyClass   inPropClass,
  ComponentPropertyID      inPropID,
  ByteCount                inPropValueSize,
  ConstComponentValuePtr   inPropValueAddress)                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;




/*
 *  ICMValidTimeFlags
 *  
 *  Summary:
 *    Flags to describe which time values are valid.
 */
typedef UInt32 ICMValidTimeFlags;
enum {

  /*
   * Indicates that a display time stamp is valid.
   */
  kICMValidTime_DisplayTimeStampIsValid = 1L << 0,

  /*
   * Indicates that a display duration is valid.
   */
  kICMValidTime_DisplayDurationIsValid = 1L << 1,

  /*
   * Indicates that a decode time stamp is valid.
   */
  kICMValidTime_DecodeTimeStampIsValid = 1L << 2,

  /*
   * Indicates that a decode duration is valid.
   */
  kICMValidTime_DecodeDurationIsValid = 1L << 3,

  /*
   * Indicates that a display offset (the offset from a decode time
   * stamp to a display time stamp) is valid.
   */
  kICMValidTime_DisplayOffsetIsValid = 1L << 4
};


/*
 *  ICMDecompressionSessionRef
 *  
 *  Summary:
 *    Represents a decompression session that emits CVPixelBufferRefs
 *    containing frames, tagged with display times.
 *  
 *  Discussion:
 *    ICMDecompressionSession does not support source extraction,
 *    matrix transformations, graphics transfer modes, region-based
 *    clipping or data-loading procedures. Note that the pixel buffers
 *    may be output out of display order, provided that the client opts
 *    in.
 */
typedef struct OpaqueICMDecompressionSession*  ICMDecompressionSessionRef;

/*
 *  QTVisualContextRef
 *  
 *  Summary:
 *    Represents a destination visual rendering environment.
 *  
 *  Discussion:
 *    The QTVisualContextRef type encapsulates a connection to a
 *    generic visual destination. A single visual context object may
 *    not be associated with more than one movie at a time.
 */
typedef struct OpaqueQTVisualContext*   QTVisualContextRef;

/*
 *  ICMDecompressionSessionOptionsRef
 *  
 *  Summary:
 *    Holds options for a decompression session.
 */
typedef struct OpaqueICMDecompressionSessionOptions*  ICMDecompressionSessionOptionsRef;

/*
 *  ICMDecompressionFrameOptionsRef
 *  
 *  Summary:
 *    Holds options for decompressing an individual frame.
 */
typedef struct OpaqueICMDecompressionFrameOptions*  ICMDecompressionFrameOptionsRef;

/*
 *  ICMDecompressionTrackingFlags
 *  
 *  Summary:
 *    Describes changes in state of a frame queued with an ICM
 *    decompression session.
 */
typedef UInt32 ICMDecompressionTrackingFlags;
enum {

  /*
   * Indicates that this is the last call for this sourceFrameRefCon.
   */
  kICMDecompressionTracking_LastCall = 1L << 0,

  /*
   * Indicates that the session no longer needs the source data pointer.
   */
  kICMDecompressionTracking_ReleaseSourceData = 1L << 1,

  /*
   * Indicates that a frame is being emitted. The pixelBuffer parameter
   * contains the decompressed frame. If the decompression session is
   * targetting a visual context, the frame has not yet been sent to
   * the visual context but will be after the callback returns.
   */
  kICMDecompressionTracking_EmittingFrame = 1L << 2,

  /*
   * Indicates that this frame was decoded.
   */
  kICMDecompressionTracking_FrameDecoded = 1L << 3,

  /*
   * Indicates that the codec decided to drop this frame.
   */
  kICMDecompressionTracking_FrameDropped = 1L << 4,

  /*
   * Indicates that this frame will not be able to be displayed unless
   * it is queued for redecode (also known as FrameNotDisplayable).
   */
  kICMDecompressionTracking_FrameNeedsRequeueing = 1L << 5
};


/*
 *  ICMDecompressionTrackingCallback
 *  
 *  Summary:
 *    The callback through which a client of an ICM decompression
 *    session receives decoded frames and information about decoding.
 *  
 *  Discussion:
 *    The client may retain the emitted pixel buffers as long as it
 *    needs; they will not be reused before the client releases them.
 *  
 *  Parameters:
 *    
 *    decompressionTrackingRefCon:
 *      The callback's reference value, copied from the
 *      decompressionTrackingRefCon field of the
 *      ICMDecompressionTrackingCallbackRecord structure.
 *    
 *    result:
 *      Indicates whether there was an error in decompression.
 *    
 *    decompressionTrackingFlags:
 *      One or more flags describing the a frame's state transitions.
 *    
 *    pixelBuffer:
 *      When the kICMDecompressionTracking_EmittingFrame flag is set in
 *      decompressionTrackingFlags, a pixel buffer containing the
 *      decompressed frame.  Otherwise, NULL.
 *    
 *    displayTime:
 *      If kICMValidTime_DisplayTimeStampIsValid is set in
 *      validTimeFlags, the display time of the frame.
 *    
 *    displayDuration:
 *      If kICMValidTime_DisplayDurationIsValid is set in
 *      validTimeFlags, the display duration of the frame.
 *    
 *    validTimeFlags:
 *      Indicates which of displayTime and displayDuration is valid.
 *    
 *    reserved:
 *      Reserved for future use.  Ignore the value of this parameter.
 *    
 *    sourceFrameRefCon:
 *      The frame's reference value, copied from the sourceFrameRefCon
 *      parameter to ICMDecompressionSessionDecodeFrame.
 */
typedef CALLBACK_API_C( void , ICMDecompressionTrackingCallback )(void *decompressionTrackingRefCon, OSStatus result, ICMDecompressionTrackingFlags decompressionTrackingFlags, CVPixelBufferRef pixelBuffer, TimeValue64 displayTime, TimeValue64 displayDuration, ICMValidTimeFlags validTimeFlags, void *reserved, void *sourceFrameRefCon);

/*
 *  ICMDecompressionTrackingCallbackRecord
 *  
 *  Summary:
 *    A tracking callback for an ICM decompression session.
 */
struct ICMDecompressionTrackingCallbackRecord {

  /*
   * The callback function pointer.
   */
  ICMDecompressionTrackingCallback  decompressionTrackingCallback;

  /*
   * The callback's reference value.
   */
  void *              decompressionTrackingRefCon;
};
typedef struct ICMDecompressionTrackingCallbackRecord ICMDecompressionTrackingCallbackRecord;
/*
 *  ICMDecompressionSessionCreate()
 *  
 *  Summary:
 *    Creates a session for decompressing video frames.
 *  
 *  Discussion:
 *    Frames will be output through calls to trackingCallback.
 *  
 *  Parameters:
 *    
 *    allocator:
 *      An allocator for the session.  Pass NULL to use the default
 *      allocator.
 *    
 *    desc:
 *      An image description for the source frames.
 *    
 *    decompressionOptions:
 *      Options for the session. The session will retain this options
 *      object. You may change some options during the session by
 *      modifying the object.
 *    
 *    destinationPixelBufferAttributes:
 *      Describes requirements for emitted pixel buffers.
 *    
 *    trackingCallback:
 *      The callback to be called with information about queued frames,
 *      and pixel buffers containing the decompressed frames.
 *    
 *    decompressionSessionOut:
 *      Points to a variable to receive the new decompression session.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMDecompressionSessionCreate(
  CFAllocatorRef                            allocator,                              /* can be NULL */
  ImageDescriptionHandle                    desc,
  ICMDecompressionSessionOptionsRef         decompressionOptions,                   /* can be NULL */
  CFDictionaryRef                           destinationPixelBufferAttributes,       /* can be NULL */
  ICMDecompressionTrackingCallbackRecord *  trackingCallback,
  ICMDecompressionSessionRef *              decompressionSessionOut) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionSessionCreateForVisualContext()
 *  
 *  Summary:
 *    Creates a session for decompressing video frames.
 *  
 *  Discussion:
 *    Frames will be output to a visual context.  If desired, the
 *    trackingCallback may attach additional data to pixel buffers
 *    before they are sent to the visual context.
 *  
 *  Parameters:
 *    
 *    allocator:
 *      An allocator for the session.  Pass NULL to use the default
 *      allocator.
 *    
 *    desc:
 *      An image description for the source frames.
 *    
 *    decompressionOptions:
 *      Options for the session. The session will retain this options
 *      object. You may change some options during the session by
 *      modifying the object.
 *    
 *    visualContext:
 *      The target visual context.
 *    
 *    trackingCallback:
 *      The callback to be called with information about queued frames,
 *      and pixel buffers containing the decompressed frames.
 *    
 *    decompressionSessionOut:
 *      Points to a variable to receive the new decompression session.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMDecompressionSessionCreateForVisualContext(
  CFAllocatorRef                            allocator,                     /* can be NULL */
  ImageDescriptionHandle                    desc,
  ICMDecompressionSessionOptionsRef         decompressionOptions,          /* can be NULL */
  QTVisualContextRef                        visualContext,
  ICMDecompressionTrackingCallbackRecord *  trackingCallback,
  ICMDecompressionSessionRef *              decompressionSessionOut) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionSessionRetain()
 *  
 *  Summary:
 *    Increments the retain count of a decompression session.
 *  
 *  Discussion:
 *    If you pass NULL to this function, nothing happens.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ICMDecompressionSessionRef 
ICMDecompressionSessionRetain(ICMDecompressionSessionRef session) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionSessionRelease()
 *  
 *  Summary:
 *    Decrements the retain count of a decompression session.  If it
 *    drops to zero, the session is disposed.
 *  
 *  Discussion:
 *    If you pass NULL to this function, nothing happens.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
ICMDecompressionSessionRelease(ICMDecompressionSessionRef session) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionSessionGetTypeID()
 *  
 *  Summary:
 *    Returns the CFTypeID for decompression sessions.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFTypeID 
ICMDecompressionSessionGetTypeID(void)                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionSessionDecodeFrame()
 *  
 *  Summary:
 *    Queues a frame for decompression.
 *  
 *  Parameters:
 *    
 *    session:
 *      The decompression session.
 *    
 *    data:
 *      Points to the compressed data for this frame. The data must
 *      remain in this location until the tracking callback is called
 *      with the kICMDecompressionTracking_ReleaseSourceData flag set
 *      in decompressionTrackingFlags.
 *    
 *    dataSize:
 *      The number of bytes of compressed data. You may not pass zero
 *      in this parameter.
 *    
 *    frameOptions:
 *      Options for this frame.
 *    
 *    frameTime:
 *      Points to a structure describing the frame's timing information.
 *    
 *    sourceFrameRefCon:
 *      Your reference value for the frame.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMDecompressionSessionDecodeFrame(
  ICMDecompressionSessionRef        session,
  const UInt8 *                     data,
  ByteCount                         dataSize,
  ICMDecompressionFrameOptionsRef   frameOptions,            /* can be NULL */
  const ICMFrameTimeRecord *        frameTime,
  void *                            sourceFrameRefCon)        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionSessionGetPropertyInfo()
 *  
 *  Summary:
 *    Retrieves information about properties of a decompression session.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMDecompressionSessionGetPropertyInfo(
  ICMDecompressionSessionRef   session,
  ComponentPropertyClass       inPropClass,
  ComponentPropertyID          inPropID,
  ComponentValueType *         outPropType,            /* can be NULL */
  ByteCount *                  outPropValueSize,       /* can be NULL */
  UInt32 *                     outPropertyFlags)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionSessionGetProperty()
 *  
 *  Summary:
 *    Retrieves the value of a specific property of a decompression
 *    session.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMDecompressionSessionGetProperty(
  ICMDecompressionSessionRef   session,
  ComponentPropertyClass       inPropClass,
  ComponentPropertyID          inPropID,
  ByteCount                    inPropValueSize,
  ComponentValuePtr            outPropValueAddress,
  ByteCount *                  outPropValueSizeUsed)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionSessionSetProperty()
 *  
 *  Summary:
 *    Sets the value of a specific property of a decompression session.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMDecompressionSessionSetProperty(
  ICMDecompressionSessionRef   session,
  ComponentPropertyClass       inPropClass,
  ComponentPropertyID          inPropID,
  ByteCount                    inPropValueSize,
  ConstComponentValuePtr       inPropValueAddress)            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  ICMNonScheduledDisplayTime
 *  
 *  Discussion:
 *    The display time for a decompression session.
 */
struct ICMNonScheduledDisplayTime {

  /*
   * A display time.  Usually this is the display time of a
   * non-scheduled queued frame.
   */
  TimeValue64         displayTime;

  /*
   * The timescale according to which displayTime should be interpreted.
   */
  TimeScale           displayTimeScale;

  /*
   * Reserved, set to zero.
   */
  UInt32              flags;
};
typedef struct ICMNonScheduledDisplayTime ICMNonScheduledDisplayTime;

/*
 *  Summary:
 *    Properties of decompression sessions.
 */
enum {

  /*
   * Class identifier for decompression session properties.
   */
  kQTPropertyClass_ICMDecompressionSession = 'icds',

  /*
   * The non-scheduled display time for a decompression session.
   * Setting this requests display of the non-scheduled queued frame at
   * that display time, if there is one. 
   * See ICMDecompressionSessionSetNonScheduledDisplayTime.
   */
  kICMDecompressionSessionPropertyID_NonScheduledDisplayTime = 'nsti', /* ICMNonScheduledDisplayTime, Read/Write */

  /*
   * The direction for non-scheduled display time. 
   * See ICMDecompressionSessionSetNonScheduledDisplayDirection.
   */
  kICMDecompressionSessionPropertyID_NonScheduledDisplayDirection = 'nsdu', /* Fixed, Read/Write */

  /*
   * The pixel buffer pool from which emitted pixel buffers are
   * allocated. Getting this does not change the retain count of the
   * pool.
   */
  kICMDecompressionSessionPropertyID_PixelBufferPool = 'pool', /* CVPixelBufferPoolRef, Read */

  /*
   * Indicates whether the a common pixel buffer pool is shared between
   * the decompressor and the session client. This is false if separate
   * pools are used because the decompressor's and the client's pixel
   * buffer attributes were incompatible.
   */
  kICMDecompressionSessionPropertyID_PixelBufferPoolIsShared = 'plsh' /* Boolean, Read */
};

/*
 *  ICMDecompressionSessionSetNonScheduledDisplayTime()
 *  
 *  Summary:
 *    Sets the display time for a decompression session, and requests
 *    display of the non-scheduled queued frame at that display time,
 *    if there is one.
 *  
 *  Discussion:
 *    Call ICMDecompressionSessionSetNonScheduledDisplayTime after
 *    queueing non-scheduled frames with
 *    ICMDecompressionSessionDecodeFrame with the
 *    icmFrameTimeIsNonScheduledDisplayTime flag set to request display
 *    of the frame at a particular display time. 
 *    If there is no queued non-scheduled frame with this display time,
 *    the frame with the next earlier display time is displayed. (Which
 *    of two display times is earlier is determined using the
 *    non-scheduled display time direction, which you can set with
 *    ICMDecompressionSessionSetNonScheduledDisplayDirection.) If there
 *    is no such frame, nothing happens. 
 *    This has no effect if frames are scheduled against a timebase.
 *  
 *  Parameters:
 *    
 *    session:
 *      The decompression session.
 *    
 *    displayTime:
 *      A display time.  Usually this is the display time of a
 *      non-scheduled queued frame.
 *    
 *    displayTimeScale:
 *      The timescale according to which displayTime should be
 *      interpreted.
 *    
 *    flags:
 *      Reserved, set to zero.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMDecompressionSessionSetNonScheduledDisplayTime(
  ICMDecompressionSessionRef   session,
  TimeValue64                  displayTime,
  TimeScale                    displayTimeScale,
  UInt32                       flags)                         AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionSessionSetNonScheduledDisplayDirection()
 *  
 *  Summary:
 *    Sets the direction for non-scheduled display time.
 *  
 *  Discussion:
 *    If rate is zero or positive, direction is forwards.  If negative,
 *    direction is backwards. 
 *    Any frames queued under the opposite direction will be flushed.
 *    
 *    The non-scheduled display direction defaults to forwards (rate
 *    1.0).
 *  
 *  Parameters:
 *    
 *    session:
 *      The decompression session.
 *    
 *    rate:
 *      Indicates the direction.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMDecompressionSessionSetNonScheduledDisplayDirection(
  ICMDecompressionSessionRef   session,
  Fixed                        rate)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionSessionFlush()
 *  
 *  Summary:
 *    Flushes frames queued with a decompression session.
 *  
 *  Discussion:
 *    The tracking callback will be called for each frame with the
 *    result -1.
 *  
 *  Parameters:
 *    
 *    session:
 *      The decompression session.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMDecompressionSessionFlush(ICMDecompressionSessionRef session) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;




/*
 *  ICMDecompressionSessionOptionsCreate()
 *  
 *  Summary:
 *    Creates a decompression session options object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMDecompressionSessionOptionsCreate(
  CFAllocatorRef                       allocator,       /* can be NULL */
  ICMDecompressionSessionOptionsRef *  options)               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionSessionOptionsCreateCopy()
 *  
 *  Summary:
 *    Copies a decompression session options object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMDecompressionSessionOptionsCreateCopy(
  CFAllocatorRef                       allocator,             /* can be NULL */
  ICMDecompressionSessionOptionsRef    originalOptions,
  ICMDecompressionSessionOptionsRef *  copiedOptions)         AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionSessionOptionsRetain()
 *  
 *  Summary:
 *    Increments the retain count of a decompression session options
 *    object.
 *  
 *  Discussion:
 *    If you pass NULL to this function, nothing happens.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ICMDecompressionSessionOptionsRef 
ICMDecompressionSessionOptionsRetain(ICMDecompressionSessionOptionsRef options) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionSessionOptionsRelease()
 *  
 *  Summary:
 *    Decrements the retain count of a decompression session options
 *    object.  If it drops to zero, the object is disposed.
 *  
 *  Discussion:
 *    If you pass NULL to this function, nothing happens.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
ICMDecompressionSessionOptionsRelease(ICMDecompressionSessionOptionsRef options) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionSessionOptionsGetTypeID()
 *  
 *  Summary:
 *    Returns the CFTypeID for decompression session options objects.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFTypeID 
ICMDecompressionSessionOptionsGetTypeID(void)                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionSessionOptionsGetPropertyInfo()
 *  
 *  Summary:
 *    Retrieves information about properties of a decompression session
 *    options object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMDecompressionSessionOptionsGetPropertyInfo(
  ICMDecompressionSessionOptionsRef   options,
  ComponentPropertyClass              inPropClass,
  ComponentPropertyID                 inPropID,
  ComponentValueType *                outPropType,            /* can be NULL */
  ByteCount *                         outPropValueSize,       /* can be NULL */
  UInt32 *                            outPropertyFlags)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionSessionOptionsGetProperty()
 *  
 *  Summary:
 *    Retrieves the value of a specific property of a decompression
 *    session options object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMDecompressionSessionOptionsGetProperty(
  ICMDecompressionSessionOptionsRef   options,
  ComponentPropertyClass              inPropClass,
  ComponentPropertyID                 inPropID,
  ByteCount                           inPropValueSize,
  ComponentValuePtr                   outPropValueAddress,
  ByteCount *                         outPropValueSizeUsed)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionSessionOptionsSetProperty()
 *  
 *  Summary:
 *    Sets the value of a specific property of a decompression session
 *    options object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMDecompressionSessionOptionsSetProperty(
  ICMDecompressionSessionOptionsRef   options,
  ComponentPropertyClass              inPropClass,
  ComponentPropertyID                 inPropID,
  ByteCount                           inPropValueSize,
  ConstComponentValuePtr              inPropValueAddress)     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  Summary:
 *    Properties of decompression session options objects.
 */
enum {

  /*
   * Class identifier for decompression session options object
   * properties.
   */
  kQTPropertyClass_ICMDecompressionSessionOptions = 'idso',

  /*
   * By default, this is true, meaning that frames must be output in
   * display order. Set this to false to allow frames to be output in
   * decode order rather than in display order.
   */
  kICMDecompressionSessionOptionsPropertyID_DisplayOrderRequired = 'dorq', /* Boolean, Read/Write */

  /*
   * A specific decompressor component or component instance to be
   * used, or one of the wildcards anyCodec, bestSpeedCodec,
   * bestFidelityCodec, or bestCompressionCodec. 
   * By default, this is anyCodec.
   */
  kICMDecompressionSessionOptionsPropertyID_DecompressorComponent = 'imdc', /* DecompressorComponent, Read/Write */

  /*
   * The decompression accuracy. 
   * The default accuracy is codecNormalQuality.
   */
  kICMDecompressionSessionOptionsPropertyID_Accuracy = 'acur', /* CodecQ, Read/Write */

  /*
   * Requests special handling of fields. Not all codecs will obey this
   * request; some codecs will only handle it at certain accuracy
   * levels. Ignored for non-interlaced content.
   */
  kICMDecompressionSessionOptionsPropertyID_FieldMode = 'fiel', /* ICMFieldMode, Read/Write */

  /*
   * The maximum number of buffers ahead of the current time that
   * should be decompressed. Used in sessions that target visual
   * contexts. By default, the number of buffers will be determined
   * from the visual context.
   */
  kICMDecompressionSessionOptionsPropertyID_MaxBufferCount = 'm#bf', /* UInt32, Read/Write */

  /*
   * The minimum time ahead of the current time that frames should be
   * decompressed. Used in sessions that target visual contexts. By
   * default, the output-ahead time will be determined from the visual
   * context.
   */
  kICMDecompressionSessionOptionsPropertyID_OutputAheadTime = 'futu', /* TimeRecord, Read/Write */

  /*
   * You can set the aperture mode property on a decompression session
   * options object to indicate whether pixel buffers should be tagged
   * to enable aspect ratio and clean aperture correction. The default
   * aperture mode for a decompression session is clean aperture mode.
   */
  kICMDecompressionSessionOptionsPropertyID_ApertureMode = 'apmd' /* OSType, Read/Write */
};


/*
 *  ICMFieldMode
 *  
 *  Summary:
 *    Describes special field handling.
 */
typedef UInt32 ICMFieldMode;
enum {

  /*
   * Both fields should be decompressed.
   */
  kICMFieldMode_BothFields      = 0,

  /*
   * Only the top field should be decompressed, producing a half-height
   * image.
   */
  kICMFieldMode_TopFieldOnly    = 1,

  /*
   * Only the bottom field should be decompressed, producing a
   * half-height image.
   */
  kICMFieldMode_BottomFieldOnly = 2,

  /*
   * Both fields should be decompressed, and then filtered to reduce
   * interlacing artifacts.
   */
  kICMFieldMode_DeinterlaceFields = 3
};


/*
 *  ICMDecompressionFrameOptionsCreate()
 *  
 *  Summary:
 *    Creates a frame decompression options object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMDecompressionFrameOptionsCreate(
  CFAllocatorRef                     allocator,       /* can be NULL */
  ICMDecompressionFrameOptionsRef *  options)                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionFrameOptionsCreateCopy()
 *  
 *  Summary:
 *    Copies a frame decompression options object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMDecompressionFrameOptionsCreateCopy(
  CFAllocatorRef                     allocator,             /* can be NULL */
  ICMDecompressionFrameOptionsRef    originalOptions,
  ICMDecompressionFrameOptionsRef *  copiedOptions)           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionFrameOptionsRetain()
 *  
 *  Summary:
 *    Increments the retain count of a frame decompression options
 *    object.
 *  
 *  Discussion:
 *    If you pass NULL to this function, nothing happens.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ICMDecompressionFrameOptionsRef 
ICMDecompressionFrameOptionsRetain(ICMDecompressionFrameOptionsRef options) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionFrameOptionsRelease()
 *  
 *  Summary:
 *    Decrements the retain count of a frame decompression options
 *    object.  If it drops to zero, the object is disposed.
 *  
 *  Discussion:
 *    If you pass NULL to this function, nothing happens.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
ICMDecompressionFrameOptionsRelease(ICMDecompressionFrameOptionsRef options) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionFrameOptionsGetTypeID()
 *  
 *  Summary:
 *    Returns the CFTypeID for frame decompression options objects.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFTypeID 
ICMDecompressionFrameOptionsGetTypeID(void)                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionFrameOptionsGetPropertyInfo()
 *  
 *  Summary:
 *    Retrieves information about properties of a decompression frame
 *    options object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMDecompressionFrameOptionsGetPropertyInfo(
  ICMDecompressionFrameOptionsRef   options,
  ComponentPropertyClass            inPropClass,
  ComponentPropertyID               inPropID,
  ComponentValueType *              outPropType,            /* can be NULL */
  ByteCount *                       outPropValueSize,       /* can be NULL */
  UInt32 *                          outPropertyFlags)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionFrameOptionsGetProperty()
 *  
 *  Summary:
 *    Retrieves the value of a specific property of a decompression
 *    frame options object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMDecompressionFrameOptionsGetProperty(
  ICMDecompressionFrameOptionsRef   options,
  ComponentPropertyClass            inPropClass,
  ComponentPropertyID               inPropID,
  ByteCount                         inPropValueSize,
  ComponentValuePtr                 outPropValueAddress,
  ByteCount *                       outPropValueSizeUsed)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMDecompressionFrameOptionsSetProperty()
 *  
 *  Summary:
 *    Sets the value of a specific property of a decompression frame
 *    options object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMDecompressionFrameOptionsSetProperty(
  ICMDecompressionFrameOptionsRef   options,
  ComponentPropertyClass            inPropClass,
  ComponentPropertyID               inPropID,
  ByteCount                         inPropValueSize,
  ConstComponentValuePtr            inPropValueAddress)       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  Summary:
 *    Properties of decompression frame options objects.
 */
enum {

  /*
   * Class identifier for decompression frame options object properties.
   */
  kQTPropertyClass_ICMDecompressionFrameOptions = 'idfo',

  /*
   * A specific pixel buffer that the frame should be decompressed
   * into. Setting this circumvents the pixel buffer pool mechanism. If
   * this buffer is not compatible with the codec's pixel buffer
   * requirements, decompression will fail.
   */
  kICMDecompressionFrameOptionsPropertyID_DestinationPixelBuffer = 'cvpb' /* CVPixelBufferRef, Read/Write */
};


/*
 *  ICMCompressionSessionRef
 *  
 *  Summary:
 *    Represents a compression session for a sequence of images. 
 *    B-frame capable.
 */
typedef struct OpaqueICMCompressionSession*  ICMCompressionSessionRef;

/*
 *  ICMEncodedFrameRef
 *  
 *  Summary:
 *    Represents a frame encoded by a compressor component and emitted
 *    by a compression session.
 *  
 *  Discussion:
 *    Compressor components have access to the mutable flavor of
 *    encoded frame object (ICMMutableEncodedFrameRef); compression
 *    session clients receive the read-only flavor
 *    (ICMMutableEncodedFrameRef).
 */
typedef const struct OpaqueICMEncodedFrame*  ICMEncodedFrameRef;
typedef struct OpaqueICMEncodedFrame*   ICMMutableEncodedFrameRef;

/*
 *  ICMCompressionSessionOptionsRef
 *  
 *  Summary:
 *    An opaque struct which holds options to configure a compression
 *    session.
 */
typedef struct OpaqueICMCompressionSessionOptions*  ICMCompressionSessionOptionsRef;

/*
 *  ICMCompressionFrameOptionsRef
 *  
 *  Summary:
 *    A token which holds options to configure an individual frame
 *    during a compression session.
 */
typedef struct OpaqueICMCompressionFrameOptions*  ICMCompressionFrameOptionsRef;

/*
 *  ICMMultiPassStorageRef
 *  
 *  Summary:
 *    A mechanism for storing information for each frame of a multipass
 *    compression session.
 *  
 *  Discussion:
 *    The ICM provides default storage mechanisms using temporary
 *    files, but clients may override this with custom mechanisms.
 */
typedef struct OpaqueICMMultiPassStorage*  ICMMultiPassStorageRef;

/*
 *  ICMEncodedFrameOutputCallback
 *  
 *  Summary:
 *    The callback through which a client of an ICM compression session
 *    receives encoded frames.
 *  
 *  Discussion:
 *    During the encoded frame output callback, the ICM has a reference
 *    to the passed ICMEncodedFrame, but the ICM will release that
 *    reference afterwards; the callback should retain the encoded
 *    frame if the client wants to keep it after the callback returns.
 *  
 *  Parameters:
 *    
 *    encodedFrameOutputRefCon:
 *      The callback's reference value, copied from the
 *      encodedFrameOutputRefCon field of the
 *      ICMEncodedFrameOutputRecord.
 *    
 *    session:
 *      The compression session.
 *    
 *    error:
 *      Indicates whether there was an error.
 *    
 *    frame:
 *      The encoded frame.
 *    
 *    reserved:
 *      Reserved for future use.  Ignore the value of this parameter.
 *  
 *  Result:
 *    If the callback returns an error, the compressor and ICM will
 *    stop emitting frames so that the error can be propogated back to
 *    the caller of ICMCompressionSessionEncodeFrame or
 *    ICMCompressionSessionCompleteFrames.
 */
typedef CALLBACK_API_C( OSStatus , ICMEncodedFrameOutputCallback )(void *encodedFrameOutputRefCon, ICMCompressionSessionRef session, OSStatus error, ICMEncodedFrameRef frame, void *reserved);

/*
 *  ICMEncodedFrameOutputRecord
 *  
 *  Summary:
 *    Holds an encoded frame callback and reference value.
 */
struct ICMEncodedFrameOutputRecord {

  /*
   * An encoded frame callback.
   */
  ICMEncodedFrameOutputCallback  encodedFrameOutputCallback;

  /*
   * The reference value for the encoded frame callback.
   */
  void *              encodedFrameOutputRefCon;

  /*
   * The allocator for encoded frame data. Pass NULL if you do not need
   * a specific allocator.
   */
  CFAllocatorRef      frameDataAllocator;
};
typedef struct ICMEncodedFrameOutputRecord ICMEncodedFrameOutputRecord;

/*
 *  ICMSourceTrackingFlags
 *  
 */
typedef UInt32 ICMSourceTrackingFlags;
enum {

  /*
   * Indicates that this is the last call for this sourceFrameRefCon.
   */
  kICMSourceTracking_LastCall   = 1L << 0,

  /*
   * Indicates that the session is done with the source pixel buffer
   * and has released any reference to it that it had.
   */
  kICMSourceTracking_ReleasedPixelBuffer = 1L << 1,

  /*
   * Indicates that this frame was encoded.
   */
  kICMSourceTracking_FrameWasEncoded = 1L << 2,

  /*
   * Indicates that this frame was dropped.
   */
  kICMSourceTracking_FrameWasDropped = 1L << 3,

  /*
   * Indicates that this frame was merged into other frames.
   */
  kICMSourceTracking_FrameWasMerged = 1L << 4,

  /*
   * Indicates that the time stamp of this frame was modified.
   */
  kICMSourceTracking_FrameTimeWasChanged = 1L << 5,

  /*
   * Indicates that the ICM has copied the image from the source pixel
   * buffer into another pixel buffer because the source pixel buffer
   * was not compatible with the compressor's required pixel buffer
   * attributes.
   */
  kICMSourceTracking_CopiedPixelBuffer = 1L << 6
};


/*
 *  ICMSourceTrackingCallback
 *  
 *  Summary:
 *    A callback which the ICM calls to provide information about the
 *    status of a frame that was passed to
 *    ICMCompressionSessionEncodeFrame.
 *  
 *  Discussion:
 *    Note that this callback may be called several times.
 *  
 *  Parameters:
 *    
 *    sourceTrackingRefCon:
 *      The callback's reference value, copied from the
 *      sourceTrackingRefCon field of ICMSourceTrackingCallbackRecord.
 *    
 *    sourceTrackingFlags:
 *      Flags describing what has happened to the frame.
 *    
 *    sourceFrameRefCon:
 *      The frame's reference value, copied from the sourceFrameRefCon
 *      parameter to ICMCompressionSessionEncodeFrame.
 *    
 *    reserved:
 *      Reserved for future use.  Ignore the value of this parameter.
 */
typedef CALLBACK_API_C( void , ICMSourceTrackingCallback )(void *sourceTrackingRefCon, ICMSourceTrackingFlags sourceTrackingFlags, void *sourceFrameRefCon, void *reserved);

/*
 *  ICMSourceTrackingCallbackRecord
 *  
 *  Summary:
 *    A tracking callback for an ICM compression session.
 */
struct ICMSourceTrackingCallbackRecord {

  /*
   * The callback function pointer.
   */
  ICMSourceTrackingCallback  sourceTrackingCallback;

  /*
   * The callback's reference value.
   */
  void *              sourceTrackingRefCon;
};
typedef struct ICMSourceTrackingCallbackRecord ICMSourceTrackingCallbackRecord;

/*
 *  ICMFrameType
 *  
 *  Summary:
 *    Informally identifies a type of frame.
 *  
 *  Discussion:
 *    Do not assume that there are no other frame types beyond I, P and
 *    B.
 */
typedef UInt16 ICMFrameType;
enum {
  kICMFrameType_I               = 'I',
  kICMFrameType_P               = 'P',
  kICMFrameType_B               = 'B',
  kICMFrameType_Unknown         = 0
};


/* ICMCompressionSessionRef routines */
/*
 *  ICMCompressionSessionCreate()
 *  
 *  Summary:
 *    Creates a compression session for the given codec type.
 *  
 *  Discussion:
 *    Some compressors do not support arbitrary source dimensions, and
 *    may override the suggested width and height.
 *  
 *  Parameters:
 *    
 *    allocator:
 *      An allocator for the session.  Pass NULL to use the default
 *      allocator.
 *    
 *    width:
 *      The width of frames.
 *    
 *    height:
 *      The height of frames.
 *    
 *    cType:
 *      The codec type.
 *    
 *    timescale:
 *      The timescale to be used for all timestamps and durations used
 *      in the session.
 *    
 *    compressionOptions:
 *      Settings configuring the session.
 *    
 *    sourcePixelBufferAttributes:
 *      Required attributes for source pixel buffers, used when
 *      creating a pixel buffer pool for source frames. If you do not
 *      want the ICM to create one for you, pass NULL. (Using pixel
 *      buffers not allocated by the ICM may increase the chance that
 *      it will be necessary to copy image data.)
 *    
 *    encodedFrameOutputRecord:
 *      The callback that will receive encoded frames.
 *    
 *    compressionSessionOut:
 *      Points to a variable to receive the created session object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionSessionCreate(
  CFAllocatorRef                    allocator,                         /* can be NULL */
  int                               width,
  int                               height,
  CodecType                         cType,
  TimeScale                         timescale,
  ICMCompressionSessionOptionsRef   compressionOptions,                /* can be NULL */
  CFDictionaryRef                   sourcePixelBufferAttributes,       /* can be NULL */
  ICMEncodedFrameOutputRecord *     encodedFrameOutputRecord,
  ICMCompressionSessionRef *        compressionSessionOut)    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionRetain()
 *  
 *  Summary:
 *    Increments the retain count of a compression session.
 *  
 *  Discussion:
 *    If you pass NULL to this function, nothing happens.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ICMCompressionSessionRef 
ICMCompressionSessionRetain(ICMCompressionSessionRef session) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionRelease()
 *  
 *  Summary:
 *    Decrements the retain count of a compression session.  If it
 *    drops to zero, the session is disposed.
 *  
 *  Discussion:
 *    If you pass NULL to this function, nothing happens. Remember to
 *    call ICMCompressionSessionCompleteFrames first if you want to
 *    ensure any pending frames are emitted.  If you do not, they will
 *    be discarded.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
ICMCompressionSessionRelease(ICMCompressionSessionRef session) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionGetTypeID()
 *  
 *  Summary:
 *    Returns the CFTypeID for compression sessions.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFTypeID 
ICMCompressionSessionGetTypeID(void)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionGetPropertyInfo()
 *  
 *  Summary:
 *    Retrieves information about properties of a compression session.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionSessionGetPropertyInfo(
  ICMCompressionSessionRef   session,
  ComponentPropertyClass     inPropClass,
  ComponentPropertyID        inPropID,
  ComponentValueType *       outPropType,            /* can be NULL */
  ByteCount *                outPropValueSize,       /* can be NULL */
  UInt32 *                   outPropertyFlags)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionGetProperty()
 *  
 *  Summary:
 *    Retrieves the value of a specific property of a compression
 *    session.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionSessionGetProperty(
  ICMCompressionSessionRef   session,
  ComponentPropertyClass     inPropClass,
  ComponentPropertyID        inPropID,
  ByteCount                  inPropValueSize,
  ComponentValuePtr          outPropValueAddress,
  ByteCount *                outPropValueSizeUsed)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionSetProperty()
 *  
 *  Summary:
 *    Sets the value of a specific property of a compression session.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionSessionSetProperty(
  ICMCompressionSessionRef   session,
  ComponentPropertyClass     inPropClass,
  ComponentPropertyID        inPropID,
  ByteCount                  inPropValueSize,
  ConstComponentValuePtr     inPropValueAddress)              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  Summary:
 *    Properties of compression sessions.
 */
enum {

  /*
   * Class identifier for compression session properties.
   */
  kQTPropertyClass_ICMCompressionSession = 'icse',

  /*
   * The time scale for the compression session.
   */
  kICMCompressionSessionPropertyID_TimeScale = 'tscl', /* TimeScale, Read */

  /*
   * The compressor's pixel buffer attributes for the compression
   * session. You can use these to create a pixel buffer pool for
   * source pixel buffers. Note that this is not the same as the
   * sourcePixelBufferAttributes passed in to
   * ICMCompressionSessionCreate. Getting this property does not change
   * its retain count.
   */
  kICMCompressionSessionPropertyID_CompressorPixelBufferAttributes = 'batt', /* CFDictionaryRef, Read */

  /*
   * A pool that can provide ideal source pixel buffers for a
   * compression session. The compression session creates this pixel
   * buffer pool based on the compressor's pixel buffer attributes and
   * any pixel buffer attributes passed in to
   * ICMCompressionSessionCreate. If the source pixel buffer attributes
   * and the compressor pixel buffer attributes can not be reconciled,
   * the pool is based on the source pixel buffer attributes and the
   * ICM converts each CVPixelBuffer internally.
   */
  kICMCompressionSessionPropertyID_PixelBufferPool = 'pool', /* CVPixelBufferPoolRef, Read */

  /*
   * The image description for the compression session. For some
   * codecs, the image description may not be available before the
   * first frame is compressed. Multiple calls to retrieve this
   * property will return the same handle. The ICM will dispose this
   * handle when the compression session is disposed. 
   * IMPORTANT: The caller must NOT dispose this handle.
   */
  kICMCompressionSessionPropertyID_ImageDescription = 'idsc' /* ImageDescriptionHandle, Read */
};

/*
 *  ICMCompressionSessionGetTimeScale()
 *  
 *  Summary:
 *    Retrieves the time scale for the compression session.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern TimeScale 
ICMCompressionSessionGetTimeScale(ICMCompressionSessionRef session) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionGetPixelBufferPool()
 *  
 *  Summary:
 *    Returns a pool that can provide ideal source pixel buffers for a
 *    compression session.
 *  
 *  Discussion:
 *    The compression session creates this pixel buffer pool based on
 *    the compressor's pixel buffer attributes and any pixel buffer
 *    attributes passed in to ICMCompressionSessionCreate. If the
 *    source pixel buffer attributes and the compressor pixel buffer
 *    attributes can not be reconciled, the pool is based on the source
 *    pixel buffer attributes and the ICM converts each CVPixelBuffer
 *    internally.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CVPixelBufferPoolRef 
ICMCompressionSessionGetPixelBufferPool(ICMCompressionSessionRef session) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionGetImageDescription()
 *  
 *  Summary:
 *    Retrieves the image description for the compression session.
 *  
 *  Discussion:
 *    For some codecs, this may fail if called before the first frame
 *    is compressed. Multiple calls to
 *    ICMCompressionSessionGetImageDescription will return the same
 *    handle. The ICM will dispose this handle when the compression
 *    session is disposed. 
 *    IMPORTANT: The caller must NOT dispose this handle.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionSessionGetImageDescription(
  ICMCompressionSessionRef   session,
  ImageDescriptionHandle *   imageDescOut)                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* ICMCompressionSessionRef encoding routines */
/*
 *  ICMCompressionSessionEncodeFrame()
 *  
 *  Summary:
 *    Call this function to present frames to the compression session.
 *    Encoded frames may or may not be output before the function
 *    returns.
 *  
 *  Discussion:
 *    The session will retain the pixel buffer as long as necessary;
 *    the client should not modify the pixel data until the session
 *    releases it. (The most practical way to deal with this is by
 *    allocating pixel buffers from a pool.) 
 *    The client may fill in both, either or neither of
 *    displayTimeStamp and displayDuration, but should set the
 *    appropriate flags to indicate which is valid. If the client needs
 *    to track the progress of a source frame, it should provide a
 *    sourceTrackingCallback. 
 *    Note: If multipass compression is enabled, calls to
 *    ICMCompressionSessionEncodeFrame must be bracketed by
 *    ICMCompressionSessionBeginPass ... ICMCompressionSessionEndPass.
 *  
 *  Parameters:
 *    
 *    session:
 *      Identifies the compression session.
 *    
 *    pixelBuffer:
 *      Contains the source image to be compressed. PixelBuffer must
 *      have a nonzero reference count. The session will retain it as
 *      long as necessary. The client should not modify pixel buffer's
 *      pixels until the pixel buffer release callback is called. In a
 *      multipass encoding session pass where the compressor suggested
 *      the flag kICMCompressionPassMode_NoSourceFrames, you may pass
 *      NULL for pixelBuffer.
 *    
 *    displayTimeStamp:
 *      The display timestamp of the frame, using the timescale passed
 *      to ICMCompressionSessionCreate. If you pass a valid value, set
 *      the kICMValidTime_DisplayTimeStampIsValid flag in
 *      validTimeFlags.
 *    
 *    displayDuration:
 *      The display duration of the frame, using the timescale passed
 *      to ICMCompressionSessionCreate. If you pass a valid value, set
 *      the kICMValidTime_DisplayDurationIsValid flag in validTimeFlags.
 *    
 *    validTimeFlags:
 *      Flags to indicate which of displayTimeStamp and displayDuration
 *      are valid.
 *    
 *    frameOptions:
 *      Options for this frame.
 *    
 *    sourceTrackingCallback:
 *      A callback to be notified about the status of this source
 *      frame. Pass NULL if you do not require notification.
 *    
 *    sourceFrameRefCon:
 *      Your reference to the source frame.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionSessionEncodeFrame(
  ICMCompressionSessionRef           session,
  CVPixelBufferRef                   pixelBuffer,
  TimeValue64                        displayTimeStamp,
  TimeValue64                        displayDuration,
  ICMValidTimeFlags                  validTimeFlags,
  ICMCompressionFrameOptionsRef      frameOptions,                 /* can be NULL */
  ICMSourceTrackingCallbackRecord *  sourceTrackingCallback,       /* can be NULL */
  void *                             sourceFrameRefCon)       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  ICMCompressionSessionCompleteFrames()
 *  
 *  Discussion:
 *    Call this function to force the compression session to complete
 *    encoding frames. Set completeAllFrames to direct the session to
 *    complete all pending frames. 
 *    If completeAllFrames is false, only frames with display time
 *    stamps up to and including completeUntilDisplayTimeStamp. 
 *    If ICMCompressionSessionOptionsSetDurationsNeeded is true and you
 *    are passing valid display timestamps but not display durations to
 *    ICMCompressionSessionEncodeFrame, pass the display timestamp of
 *    the next frame that would be passed to EncodeFrame in
 *    nextDisplayTimeStamp. 
 *    Note: This function might return before frames are completed if
 *    the encoded frame callback returns an error.
 *  
 *  Parameters:
 *    
 *    session:
 *      Identifies the compression session.
 *    
 *    completeAllFrames:
 *      Set to direct the session to complete all pending frames.
 *    
 *    completeUntilDisplayTimeStamp:
 *      If completeAllFrames is false, the display timestamp to
 *      complete frames up to. Ignored if completeAllFrames is true.
 *    
 *    nextDisplayTimeStamp:
 *      See above. Ignored unless
 *      ICMCompressionSessionOptionsSetDurationsNeeded set true and
 *      kICMValidTime_DisplayDurationIsValid was clear in
 *      validTimeFlags in last call to ICMCompressionSessionEncodeFrame.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionSessionCompleteFrames(
  ICMCompressionSessionRef   session,
  Boolean                    completeAllFrames,
  TimeValue64                completeUntilDisplayTimeStamp,
  TimeValue64                nextDisplayTimeStamp)            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/* ICMCompressionSessionRef multipass support routines */

/*
 *  ICMCompressionPassModeFlags
 *  
 *  Summary:
 *    Flags describing how a compressor should behave in a given pass
 *    of multipass encoding.
 */
typedef UInt32 ICMCompressionPassModeFlags;
enum {

  /*
   * In this pass the compressor shall output encoded frames.
   */
  kICMCompressionPassMode_OutputEncodedFrames = 1L << 0,

  /*
   * In this pass the client need not provide source frame buffers.
   */
  kICMCompressionPassMode_NoSourceFrames = 1L << 1,

  /*
   * In this pass the compressor may write private data to multipass
   * storage.
   */
  kICMCompressionPassMode_WriteToMultiPassStorage = 1L << 2,

  /*
   * In this pass the compressor may read private data from multipass
   * storage.
   */
  kICMCompressionPassMode_ReadFromMultiPassStorage = 1L << 3,

  /*
   * The compressor will set this flag to indicate that it will not be
   * able to output encoded frames in the coming pass. If this flag is
   * not set, then the client is allowed to set the
   * kICMCompressionPassMode_OutputEncodedFrames flag when calling
   * ICMCompressionSessionBeginPass.
   */
  kICMCompressionPassMode_NotReadyToOutputEncodedFrames = 1L << 4
};

/*
 *  ICMCompressionSessionSupportsMultiPassEncoding()
 *  
 *  Summary:
 *    Queries whether a compression session supports multipass encoding.
 *  
 *  Discussion:
 *    Even if this function returns false, if you set the
 *    kICMCompressionSessionOptionsPropertyID_MultiPassStorage property
 *    on the CompressionSessionOptions, you must call
 *    ICMCompressionSessionBeginPass and ICMCompressionSessionEndPass.
 *  
 *  Parameters:
 *    
 *    session:
 *      The compression session.
 *    
 *    multiPassStyleFlags:
 *      Reserved.  Set to zero.
 *    
 *    firstPassModeFlagsOut:
 *      Points to a variable to receive the session's requested mode
 *      flags for the first pass. The client may modify these flags,
 *      but should not set kICMCompressionPassMode_NoSourceFrames. Pass
 *      NULL if you do not want this information.
 *  
 *  Result:
 *    true if the session supports multipass encoding, false otherwise.
 *    If the session does not support multipass encoding,
 *    *firstPassModeFlagsOut will be set to
 *    kICMCompressionPassMode_OutputEncodedFrames.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
ICMCompressionSessionSupportsMultiPassEncoding(
  ICMCompressionSessionRef       session,
  UInt32                         multiPassStyleFlags,
  ICMCompressionPassModeFlags *  firstPassModeFlagsOut)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionBeginPass()
 *  
 *  Summary:
 *    Call to announce the start of a specific compression pass.
 *  
 *  Discussion:
 *    The source frames and frame options for each display timestamp
 *    should be the same across passes. 
 *    During multipass compression, valid displayTimeStamps must be
 *    passed to ICMCompressionSessionEncodeFrame since they are used to
 *    index the compressor's stored state. 
 *    During an analysis pass
 *    (kICMCompressionPassMode_WriteToMultiPassStorage), the compressor
 *    does not output encoded frames, but records compressor-private
 *    information for each frame. 
 *    During repeated analysis passes and the encoding pass
 *    (kICMCompressionPassMode_ReadFromMultiPassStorage), the
 *    compressor may refer to this information for other frames and use
 *    it to improve encoding. 
 *    During an encoding pass
 *    (kICMCompressionPassMode_OutputEncodedFrames), the compressor
 *    must output encoded frames. 
 *    If the compressor set the kICMCompressionPassMode_NoSourceFrames
 *    flag for the pass, the client may pass NULL pixel buffers to
 *    ICMCompressionSessionEncodeFrame. 
 *    By default, the ICM provides local storage that lasts only until
 *    the compression session is disposed. If the client provides
 *    custom multipass storage, pass may be performed at different
 *    times or on different machines; segments of each pass may even be
 *    distributed.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionSessionBeginPass(
  ICMCompressionSessionRef      session,
  ICMCompressionPassModeFlags   passModeFlags,
  UInt32                        flags)                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionEndPass()
 *  
 *  Summary:
 *    Call to announce the end of a pass.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionSessionEndPass(ICMCompressionSessionRef session) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionProcessBetweenPasses()
 *  
 *  Summary:
 *    Lets the compressor perform processing between passes.
 *  
 *  Discussion:
 *    Call this function repeatedly, until the compressor sets
 *    *interpassProcessingDoneOut to true to indicate that it is done
 *    with this round of interpass processing. 
 *    When done, the compressor will indicate its preferred mode for
 *    the next pass. 
 *    The client may choose to begin an encoding pass (by ORing in the
 *    kICMCompressionPassMode_OutputEncodedFrames flag) regardless of
 *    the compressor's request.
 *  
 *  Parameters:
 *    
 *    session:
 *      The compression session.
 *    
 *    flags:
 *      Reserved.  Set to zero.
 *    
 *    interpassProcessingDoneOut:
 *      Points to a Boolean that will be set to false if
 *      ICMCompressionSessionProcessBetweenPasses should be called
 *      again, true if not
 *    
 *    requestedNextPassModeFlagsOut:
 *      Points to ICMCompressionPassModeFlags that will be set to the
 *      codec's recommended mode flags for the next pass.
 *      kICMCompressionPassMode_OutputEncodedFrames will only be set if
 *      it recommends that the next pass be the final one.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionSessionProcessBetweenPasses(
  ICMCompressionSessionRef       session,
  UInt32                         flags,
  Boolean *                      interpassProcessingDoneOut,
  ICMCompressionPassModeFlags *  requestedNextPassModeFlagsOut) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/* ICMCompressionSessionOptionsRef routines */
/*
 *  ICMCompressionSessionOptionsCreate()
 *  
 *  Summary:
 *    Creates a compression session options object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionSessionOptionsCreate(
  CFAllocatorRef                     allocator,       /* can be NULL */
  ICMCompressionSessionOptionsRef *  options)                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionOptionsCreateCopy()
 *  
 *  Summary:
 *    Copies a compression session options object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionSessionOptionsCreateCopy(
  CFAllocatorRef                     allocator,             /* can be NULL */
  ICMCompressionSessionOptionsRef    originalOptions,
  ICMCompressionSessionOptionsRef *  copiedOptions)           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionOptionsRetain()
 *  
 *  Summary:
 *    Increments the retain count of a compression session options
 *    object.
 *  
 *  Discussion:
 *    If you pass NULL to this function, nothing happens.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ICMCompressionSessionOptionsRef 
ICMCompressionSessionOptionsRetain(ICMCompressionSessionOptionsRef options) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionOptionsRelease()
 *  
 *  Summary:
 *    Decrements the retain count of a compression session options
 *    object.  If it drops to zero, the object is disposed.
 *  
 *  Discussion:
 *    If you pass NULL to this function, nothing happens.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
ICMCompressionSessionOptionsRelease(ICMCompressionSessionOptionsRef options) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionOptionsGetTypeID()
 *  
 *  Summary:
 *    Returns the CFTypeID for compression session options objects.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFTypeID 
ICMCompressionSessionOptionsGetTypeID(void)                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionOptionsGetPropertyInfo()
 *  
 *  Summary:
 *    Retrieves information about properties of a compression session
 *    options object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionSessionOptionsGetPropertyInfo(
  ICMCompressionSessionOptionsRef   options,
  ComponentPropertyClass            inPropClass,
  ComponentPropertyID               inPropID,
  ComponentValueType *              outPropType,            /* can be NULL */
  ByteCount *                       outPropValueSize,       /* can be NULL */
  UInt32 *                          outPropertyFlags)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionOptionsGetProperty()
 *  
 *  Summary:
 *    Retrieves the value of a specific property of a compression
 *    session options object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionSessionOptionsGetProperty(
  ICMCompressionSessionOptionsRef   options,
  ComponentPropertyClass            inPropClass,
  ComponentPropertyID               inPropID,
  ByteCount                         inPropValueSize,
  ComponentValuePtr                 outPropValueAddress,
  ByteCount *                       outPropValueSizeUsed)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionOptionsSetProperty()
 *  
 *  Summary:
 *    Sets the value of a specific property of a compression session
 *    options object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionSessionOptionsSetProperty(
  ICMCompressionSessionOptionsRef   options,
  ComponentPropertyClass            inPropClass,
  ComponentPropertyID               inPropID,
  ByteCount                         inPropValueSize,
  ConstComponentValuePtr            inPropValueAddress)       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 */
enum {

  /*
   * Indicates no limit on the number of frames in the compression
   * window.
   */
  kICMUnlimitedFrameDelayCount  = -1L,

  /*
   * Indicates no time limit on the number of frames in the compression
   * window.
   */
  kICMUnlimitedFrameDelayTime   = -1L,

  /*
   * Indicates no CPU time limit on compression.
   */
  kICMUnlimitedCPUTimeBudget    = -1L
};


/*
 *  ICMDataRateLimit
 *  
 *  Summary:
 *    A hard limit on the data rate.
 *  
 *  Discussion:
 *    A hard limit is described by a data size in bytes and a duration
 *    in seconds, and requires that the total size of compressed data
 *    for any continuous segment of that duration (in decode time) must
 *    not exceed the provided data size.
 */
struct ICMDataRateLimit {

  /*
   * The number of bytes.
   */
  SInt32              dataSize;

  /*
   * The number of seconds.
   */
  Float32             dataDuration;
};
typedef struct ICMDataRateLimit         ICMDataRateLimit;

/*
 *  Summary:
 *    Scaling modes
 *  
 *  Discussion:
 *    These constants indicate how source frames to a compression
 *    session should be scaled if the dimensions and/or display aspect
 *    ratio do not match.
 */
enum {

  /*
   * The full width and height of source frames shall be scaled to the
   * full width and height of the destination. This is the default if
   * no other scaling mode is specified.
   */
  kICMScalingMode_StretchProductionAperture = 'sp2p',

  /*
   * The clean aperture of the source frames shall be scaled to the
   * clean aperture of the destination.
   */
  kICMScalingMode_StretchCleanAperture = 'sc2c',

  /*
   * The clean aperture of the source frames shall be scaled to fit
   * inside the clean aperture of the destination, preserving the
   * original display aspect ratio. If the display aspect ratios are
   * different, the source frames will be centered with black bars
   * above and below, or to the left and right.
   */
  kICMScalingMode_Letterbox     = 'lett',

  /*
   * The clean aperture of the source frames shall be scaled to cover
   * the clean aperture of the destination, preserving the original
   * display aspect ratio. If the display aspect ratios are different,
   * the source frames will be centered and cropped.
   */
  kICMScalingMode_Trim          = 'trim'
};


/*
 *  ICMSimpleBoundaryConditions
 *  
 *  Summary:
 *    Indicates whether and how a compression session's frames will be
 *    concatenated with other compressed frames to form a longer series.
 *  
 *  Discussion:
 *    Some clients divide a long series of frames into several shorter
 *    segments, each of which is then compressed by an independent
 *    compression session. Boundary conditions tell the compressor
 *    about how each session fits into the greater series: does this
 *    session stand alone, or will it be used to encode the first
 *    segment, a middle segment, or the last segment in a longer
 *    continuum? 
 *    This information enables compressors to ensure that compressed
 *    segments can be concatenated smoothly -- for example, avoiding
 *    data rate spikes where segments are joined. 
 *    By default, a session is assumed to stand alone.
 */
struct ICMSimpleBoundaryConditions {

  /*
   * True if frames compressed in a separate session will be
   * concatenated before the beginning of this one. False if this is a
   * stand-alone session, or if this session will encode the first
   * segment of a multi-segment compression. By default, false.
   */
  Boolean             moreFramesBeforeStart;

  /*
   * True if frames compressed in a separate session will be
   * concatenated following the end of this one. False if this is a
   * stand-alone session, or if this session will encode the last
   * segment of a multi-segment compression. By default, false.
   */
  Boolean             moreFramesAfterEnd;
};
typedef struct ICMSimpleBoundaryConditions ICMSimpleBoundaryConditions;

/*
 *  Summary:
 *    Properties of compression sessions options objects.
 */
enum {

  /*
   * Class identifier for compression session options object properties.
   */
  kQTPropertyClass_ICMCompressionSessionOptions = 'icso',

  /*
   * Enables temporal compression. By default, temporal compression is
   * disabled. 
   * IMPORTANT: If you want temporal compression (P frames and/or B
   * frames) you must set this to true.
   */
  kICMCompressionSessionOptionsPropertyID_AllowTemporalCompression = 'p ok', /* Boolean, Read/Write */

  /*
   * Enables frame reordering. 
   * In order to encode B frames, a compressor must reorder frames,
   * which means that the order in which they will be emitted and
   * stored (the decode order) is different from the order in which
   * they were presented to the compressor (the display order). 
   * By default, frame reordering is disabled. 
   * IMPORTANT: In order to encode using B frames, you must enable
   * frame reordering.
   */
  kICMCompressionSessionOptionsPropertyID_AllowFrameReordering = 'b ok', /* Boolean, Read/Write */

  /*
   * Indicates that durations of emitted frames are needed. 
   * If this flag is set and source frames are provided with times but
   * not durations, then frames will be delayed so that durations can
   * be calculated as the difference between one frame's time stamp and
   * the next frame's time stamp. 
   * By default, this flag is clear, so frames will not be delayed in
   * order to calculate durations. 
   * IMPORTANT: If you will be passing encoded frames to
   * AddMediaSampleFromEncodedFrame, you must set this flag to true.
   */
  kICMCompressionSessionOptionsPropertyID_DurationsNeeded = 'need', /* Boolean, Read/Write */

  /*
   * The maximum interval between key frames, also known as the key
   * frame rate. 
   * Key frames, also known as sync frames, reset inter-frame
   * dependencies; decoding a key frame is sufficient to prepare a
   * decompressor for correctly decoding the difference frames that
   * follow. 
   * Compressors are allowed to generate key frames more frequently if
   * this would result in more efficient compression. 
   * The default key frame interval is 0, which indicates that the
   * compressor should choose where to place all key frames. A key
   * frame interval of 1 indicates that every frame must be a key
   * frame, 2 indicates that at least every other frame must be a key
   * frame, etc.
   */
  kICMCompressionSessionOptionsPropertyID_MaxKeyFrameInterval = 'kyfr', /* SInt32, Read/Write */

  /*
   * The requested maximum interval between partial sync frames. If the
   * interval is n, any sequence of n successive frames must include at
   * least one key or partial sync frame. 
   * Where supported, partial sync frames perform a partial reset of
   * inter-frame dependencies; decoding two partial sync frames and the
   * non-droppable difference frames between them is sufficient to
   * prepare a decompressor for correctly decoding the difference
   * frames that follow. 
   * Compressors are allowed to generate partial sync frames more
   * frequently if this would result in more efficient compression.
   * 
   * The default partial sync frame interval is 0, which indicates that
   * the compressor should choose where to place partial sync frames. A
   * partial sync frame interval of 1 means there can be no difference
   * frames, so it is equivalent to a key frame interval of 1. A
   * partial sync frame interval of 2 means that every other frame must
   * be a key frame or a partial sync frame. 
   * Compressors that do not support partial sync frames will ignore
   * this setting.
   */
  kICMCompressionSessionOptionsPropertyID_MaxPartialSyncFrameInterval = 'psfr', /* SInt32, Read/Write */

  /*
   * Enables the compressor to modify frame times. 
   * Some compressors are able to identify and coalesce runs of
   * identical frames and output single frames with longer duration, or
   * output frames at a different frame rate from the original. This
   * feature is controlled by the "allow frame time changes" flag. By
   * default, this flag is set to false, which forces compressors to
   * emit one encoded frame for every source frame, and to preserve
   * frame display times. 
   * (Note: this feature replaces the practice of having compressors
   * return special high similarity values to indicate that frames
   * could be dropped.) 
   * If you want to allow the compressor to modify frame times in order
   * to improve compression performance, enable frame time changes.
   */
  kICMCompressionSessionOptionsPropertyID_AllowFrameTimeChanges = '+ ok', /* Boolean, Read/Write */

  /*
   * Enables the compressor to call the encoded-frame callback from a
   * different thread. 
   * By default, the flag is false, which means that the compressor
   * must call the encoded-frame callback from the same thread that
   * ICMCompressionSessionEncodeFrame and
   * ICMCompressionSessionCompleteFrames were called on.
   */
  kICMCompressionSessionOptionsPropertyID_AllowAsyncCompletion = 'asok', /* Boolean, Read/Write */

  /*
   * The maximum frame delay count is the maximum number of frames that
   * a compressor is allowed to hold before it must output a compressed
   * frame. It limits the number of frames that may be held in the
   * "compression window". If the maximum frame delay count is M, then
   * before the call to encode frame N returns, frame N-M must have
   * been emitted. 
   * The default is kICMUnlimitedFrameDelayCount, which sets no limit
   * on the compression window.
   */
  kICMCompressionSessionOptionsPropertyID_MaxFrameDelayCount = 'cwin', /* SInt32, Read/Write */

  /*
   * The maximum frame delay time is the maximum difference between a
   * source frame's display time and the corresponding encoded frame's
   * decode time. It limits the span of display time that may be held
   * in the "compression window". If the maximum frame delay time is
   * TM, then before the call to encode a frame with display time TN
   * returns, all frames with display times up to and including TN-TM
   * must have been emitted. 
   * The default is kICMUnlimitedFrameDelayTime, which sets no time
   * limit on the compression window.
   */
  kICMCompressionSessionOptionsPropertyID_MaxFrameDelayTime = 'cwit', /* TimeValue64, Read/Write */

  /*
   * Sets a specific compressor component or component instance to be
   * used, or one of the wildcards anyCodec, bestSpeedCodec,
   * bestFidelityCodec, or bestCompressionCodec. 
   * Use this API to force the Image Compression Manager to use a
   * specific compressor component or compressor component instance. 
   * (If you pass in a component instance that you opened, the ICM will
   * not close that instance; you must do so after the compression
   * session is released.) To allow the Image Compression Manager to
   * choose the compressor component, set the compressorComponent to
   * anyCodec (the default), bestSpeedCodec, bestFidelityCodec or
   * bestCompressionCodec.
   */
  kICMCompressionSessionOptionsPropertyID_CompressorComponent = 'imco', /* CompressorComponent, Read/Write */

  /*
   * A handle containing compressor settings. The compressor will be
   * configured with these settings (by a call to
   * ImageCodecSetSettings) during ICMCompressionSessionCreate.
   */
  kICMCompressionSessionOptionsPropertyID_CompressorSettings = 'cost', /* Handle, Read/Write */

  /*
   * The depth for compression. 
   * If a compressor does not support a specific depth, the closest
   * supported depth will be used (preferring deeper depths to
   * shallower depths). The default depth is k24RGBPixelFormat.
   */
  kICMCompressionSessionOptionsPropertyID_Depth = 'deep', /* UInt32, Read/Write */

  /*
   * The color table for compression.  Used with indexed-color depths.
   * 
   * Clients who get this property are responsible for disposing the
   * returned CTabHandle.
   */
  kICMCompressionSessionOptionsPropertyID_ColorTable = 'clut', /* CTabHandle, Read/Write*/

  /*
   * The compression quality. 
   * This value is always used to set the spatialQuality; if temporal
   * compression is enabled, it is also used to set temporalQuality.
   * <BR> The default quality is codecNormalQuality.
   */
  kICMCompressionSessionOptionsPropertyID_Quality = 'qual', /* CodecQ, Read/Write */

  /*
   * The long-term desired average data rate in bytes per second. 
   *  This is not a hard limit. 
   * The default data rate is zero, which indicates that the quality
   * setting should determine the size of compressed data. 
   * Note that data rate settings only have an effect when timing
   * information is provided for source frames, and that some codecs do
   * not support limiting to specified data rates.
   */
  kICMCompressionSessionOptionsPropertyID_AverageDataRate = 'aver', /* SInt32, Read/Write */

  /*
   * Zero, one or two hard limits on data rate. 
   * Each hard limit is described by a data size in bytes and a
   * duration in seconds, and requires that the total size of
   * compressed data for any contiguous segment of that duration (in
   * decode time) must not exceed the data size. 
   * By default, no data rate limits are set. 
   * When setting this property, the inPropValueSize parameter should
   * be the number of data rate limits multiplied by
   * sizeof(ICMDataRateLimit). 
   * Note that data rate settings only have an effect when timing
   * information is provided for source frames, and that some codecs do
   * not support limiting to specified data rates.
   */
  kICMCompressionSessionOptionsPropertyID_DataRateLimits = 'hard', /* C array of ICMDataRateLimit struct, Read/Write */

  /*
   * The current number of data rate limits.
   */
  kICMCompressionSessionOptionsPropertyID_DataRateLimitCount = 'har#', /* UInt32, Read */

  /*
   * The maximum allowed number of data rate limits.  (Currently 2.)
   */
  kICMCompressionSessionOptionsPropertyID_MaxDataRateLimits = 'mhar', /* UInt32, Read */

  /*
   * Indicates that the source was previously compressed. 
   * This property is purely an optional, informational hint to the
   * compressor; by default it is false.
   */
  kICMCompressionSessionOptionsPropertyID_WasCompressed = 'wasc', /* Boolean, Read/Write */

  /*
   * Recommends a CPU time budget for the compressor in microseconds
   * per frame. 
   * Zero means to go as fast as possible. 
   * By default, this is set to kICMUnlimitedCPUTimeBudget, which sets
   * no limit. 
   * This is an advisory hint to the compressor, and some compressors
   * may ignore it. Multithreaded compressors may use this amount of
   * CPU time on each processor. 
   * Compressors should not feel compelled to use the full time budget
   * if they complete ahead of time!
   */
  kICMCompressionSessionOptionsPropertyID_CPUTimeBudget = 'cput', /* UInt32, Read/Write */

  /*
   * Storage for multi-pass compression. 
   * To enable multipass compression, the client must provide a storage
   * location for multipass data.  Use
   * ICMMultiPassStorageCreateWithTemporaryFile to have the ICM store
   * it in a temporary file.  Use
   * ICMMultiPassStorageCreateWithCallbacks to manage the storage
   * yourself. 
   * Note that the amount of multipass data to be stored can be
   * substantial; it could be greater than the size of the output movie
   * file. 
   * If this property is not NULL, the client must call
   * ICMCompressionSessionBeginPass and ICMCompressionSessionEndPass
   * around groups of calls to ICMCompressionSessionEncodeFrame. 
   *  By default, this property is NULL and multipass compression is
   * not enabled. The compression session options object retains the
   * multipass storage object, when one is set.
   */
  kICMCompressionSessionOptionsPropertyID_MultiPassStorage = 'imps', /* ICMMultiPassStorageRef, Read/Write */

  /*
   * Indicates the number of source frames, if known. If nonzero, this
   * should be the exact number of times that the client calls
   * ICMCompressionSessionEncodeFrame in each pass. 
   * The default is 0, which indicates that the number of source frames
   * is not known.
   */
  kICMCompressionSessionOptionsPropertyID_SourceFrameCount = 'frco', /* UInt64, Read/Write */

  /*
   * Indicates the expected frame rate, if known. The frame rate is
   * measured in frames per second. This is not used to control the
   * frame rate; it is provided as a hint to the compressor so that it
   * can set up internal configuration before compression begins. The
   * actual frame rate will depend on frame durations and may vary. By
   * default, this is zero, indicating "unknown".
   */
  kICMCompressionSessionOptionsPropertyID_ExpectedFrameRate = 'fran', /* Fixed, Read/Write */

  /*
   * Indicates how source frames to a compression session should be
   * scaled if the dimensions and/or display aspect ratio do not match.
   */
  kICMCompressionSessionOptionsPropertyID_ScalingMode = 'scam', /* OSType, Read/Write */

  /*
   * Describes the clean aperture for compressed frames. Note that if
   * the compressor enforces a clean aperture, it will override this
   * setting. The clean aperture will be set on the output image
   * description and may affect scaling in some scaling modes. By
   * default, this is all zeros, meaning unset.
   */
  kICMCompressionSessionOptionsPropertyID_CleanAperture = 'clap', /* Native-endian CleanApertureImageDescriptionExtension, Read/Write */

  /*
   * Describes the pixel aspect ratio for compressed frames. Note that
   * if the compressor enforces a pixel aspect ratio, it will override
   * this setting. The pixel aspect ratio will be set on the output
   * image description and may affect scaling in some scaling modes. By
   * default, this is all zeros, meaning unset.
   */
  kICMCompressionSessionOptionsPropertyID_PixelAspectRatio = 'pasp', /* Native-endian PixelAspectRatioImageDescriptionExtension, Read/Write */

  /*
   * Describes the number and order of fields for compressed frames.
   * Note that if the compressor enforces field info, it will override
   * this setting. The field info will be set on the output image
   * description and may affect scaling in some scaling modes. By
   * default, this is all zeros, meaning unset.
   */
  kICMCompressionSessionOptionsPropertyID_FieldInfo = 'fiel', /* FieldInfoImageDescriptionExtension2, Read/Write */

  /*
   * Indicates whether and how a compression session's frames will be
   * concatenated with other compressed frames to form a longer series.
   */
  kICMCompressionSessionOptionsPropertyID_SimpleBoundaryConditions = 'ends', /* ICMSimpleBoundaryConditions struct, Read/Write */

  /*
   * Requests additional distortion to be applied to the aspect ratio
   * in the kICMScalingMode_Letterbox and kICMScalingMode_Trim scaling
   * modes. Values greater than fixed1 mean wider, values less than
   * fixed1 mean narrower. For example, a value of X2Fix(2.0) would
   * make the picture aspect ratio twice as wide.
   */
  kICMCompressionSessionOptionsPropertyID_ExtraAspectRatioStretchFactor = 'exsf' /* Fixed, Default fixed1, Read/Write */
};


/*
 *  ICMCompressionSessionOptionsSetAllowTemporalCompression()
 *  
 *  Summary:
 *    Enables temporal compression.
 *  
 *  Discussion:
 *    By default, temporal compression is disabled. 
 *    IMPORTANT: If you want temporal compression (P frames and/or B
 *    frames) you must set this to true.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionSessionOptionsSetAllowTemporalCompression(
  ICMCompressionSessionOptionsRef   options,
  Boolean                           allowTemporalCompression) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionOptionsGetAllowTemporalCompression()
 *  
 *  Summary:
 *    Retrieves the allow temporal compression flag.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
ICMCompressionSessionOptionsGetAllowTemporalCompression(ICMCompressionSessionOptionsRef options) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionOptionsSetAllowFrameReordering()
 *  
 *  Summary:
 *    Enables frame reordering.
 *  
 *  Discussion:
 *    In order to encode B frames, a compressor must reorder frames,
 *    which means that the order in which they will be emitted and
 *    stored (the decode order) is different from the order in which
 *    they were presented to the compressor (the display order). 
 *     By default, frame reordering is disabled. 
 *    IMPORTANT: In order to encode using B frames, you must enable
 *    frame reordering.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionSessionOptionsSetAllowFrameReordering(
  ICMCompressionSessionOptionsRef   options,
  Boolean                           allowFrameReordering)     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionOptionsGetAllowFrameReordering()
 *  
 *  Summary:
 *    Retrieves the allow frame reordering flag.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
ICMCompressionSessionOptionsGetAllowFrameReordering(ICMCompressionSessionOptionsRef options) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionOptionsSetDurationsNeeded()
 *  
 *  Summary:
 *    Indicates that durations of emitted frames are needed.
 *  
 *  Discussion:
 *    If this flag is set and source frames are provided with times but
 *    not durations, then frames will be delayed so that durations can
 *    be calculated as the difference between one frame's time stamp
 *    and the next frame's time stamp. 
 *    By default, this flag is clear, so frames will not be delayed in
 *    order to calculate durations. 
 *    IMPORTANT: If you will be passing encoded frames to
 *    AddMediaSampleFromEncodedFrame, you must set this flag to true.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionSessionOptionsSetDurationsNeeded(
  ICMCompressionSessionOptionsRef   options,
  Boolean                           decodeDurationsNeeded)    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionOptionsGetDurationsNeeded()
 *  
 *  Summary:
 *    Retrieves the "durations needed" flag.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
ICMCompressionSessionOptionsGetDurationsNeeded(ICMCompressionSessionOptionsRef options) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionOptionsSetMaxKeyFrameInterval()
 *  
 *  Summary:
 *    Sets the maximum interval between key frames (also known as the
 *    key frame rate).
 *  
 *  Discussion:
 *    Compressors are allowed to generate key frames more frequently if
 *    this would result in more efficient compression. 
 *    The default key frame interval is 0, which indicates that the
 *    compressor should choose where to place all key frames. 
 *     (Note: this is a break with previous practice, which used a key
 *    frame rate of zero to disable temporal compression.)
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionSessionOptionsSetMaxKeyFrameInterval(
  ICMCompressionSessionOptionsRef   options,
  SInt32                            maxKeyFrameInterval)      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionOptionsGetMaxKeyFrameInterval()
 *  
 *  Summary:
 *    Retrieves the maximum key frame interval.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern SInt32 
ICMCompressionSessionOptionsGetMaxKeyFrameInterval(ICMCompressionSessionOptionsRef options) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionOptionsSetAllowFrameTimeChanges()
 *  
 *  Summary:
 *    Enables the compressor to modify frame times.
 *  
 *  Discussion:
 *    Some compressors are able to identify and coalesce runs of
 *    identical frames and output single frames with longer duration,
 *    or output frames at a different frame rate from the original.
 *    This feature is controlled by the "allow frame time changes"
 *    flag. By default, this flag is set to false, which forces
 *    compressors to emit one encoded frame for every source frame, and
 *    to preserve frame display times. 
 *    (Note: this feature replaces the practice of having compressors
 *    return special high similarity values to indicate that frames
 *    could be dropped.) 
 *    If you want to allow the compressor to modify frame times in
 *    order to improve compression performance, enable frame time
 *    changes.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionSessionOptionsSetAllowFrameTimeChanges(
  ICMCompressionSessionOptionsRef   options,
  Boolean                           allowFrameTimeChanges)    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionSessionOptionsGetAllowFrameTimeChanges()
 *  
 *  Summary:
 *    Retrieves the allow frame time changes flag.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
ICMCompressionSessionOptionsGetAllowFrameTimeChanges(ICMCompressionSessionOptionsRef options) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;




/* ICMMultiPassStorageRef routines */

/*
 *  ICMMultiPassStorageCreationFlags
 *  
 */
typedef UInt32 ICMMultiPassStorageCreationFlags;
enum {

  /*
   * Indicates that the temporary file should not be deleted when the
   * multipass storage is released.
   */
  kICMMultiPassStorage_DoNotDeleteWhenDone = 1L << 0
};

/*
 *  ICMMultiPassStorageCreateWithTemporaryFile()
 *  
 *  Summary:
 *    Creates a multipass storage using a temporary file.
 *  
 *  Discussion:
 *    If you pass NULL for directoryRef, the ICM will use the user's
 *    temporary items folder. 
 *    If you pass NULL for fileName, the ICM will pick a unique name.
 *    
 *    The file will be deleted when the multipass storage is released,
 *    unless you set the kICMMultiPassStorage_DoNotDeleteWhenDone flag.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMMultiPassStorageCreateWithTemporaryFile(
  CFAllocatorRef                     allocator,                 /* can be NULL */
  FSRef *                            directoryRef,              /* can be NULL */
  CFStringRef                        fileName,                  /* can be NULL */
  ICMMultiPassStorageCreationFlags   flags,
  ICMMultiPassStorageRef *           multiPassStorageOut)     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  ICMMultiPassStorageStep
 *  
 *  Summary:
 *    Indicates a jump in time stamps used to index multipass storage.
 */
typedef UInt32 ICMMultiPassStorageStep;
enum {

  /*
   * Requests the first time stamp at which a value is stored.
   */
  kICMMultiPassStorage_GetFirstTimeStamp = 1,

  /*
   * Requests the previous time stamp before the given time stamp at
   * which a value is stored.
   */
  kICMMultiPassStorage_GetPreviousTimeStamp = 2,

  /*
   * Requests the next time stamp after the given time stamp at which a
   * value is stored.
   */
  kICMMultiPassStorage_GetNextTimeStamp = 3,

  /*
   * Requests the last time stamp at which a value is stored.
   */
  kICMMultiPassStorage_GetLastTimeStamp = 4
};



/*
 *  ICMMultiPassSetDataAtTimeStampCallback
 *  
 *  Summary:
 *    Stores a value at a given time stamp.
 *  
 *  Discussion:
 *    The new data should replace any previous data held at that
 *    timestamp with that index.
 *  
 *  Parameters:
 *    
 *    storageRefCon:
 *      The callbacks' reference value.
 *    
 *    timeStamp:
 *      The time stamp at which the value should be stored.
 *    
 *    index:
 *      An index by which multiple values may be stored at a time
 *      stamp. The meaning of individual indexes is private to the
 *      compressor.
 *    
 *    data:
 *      The data to be stored, or NULL to delete the value. The
 *      contents are private to the compressor component.
 */
typedef CALLBACK_API_C( OSStatus , ICMMultiPassSetDataAtTimeStampCallback )(void *storageRefCon, TimeValue64 timeStamp, long index, CFDataRef data);

/*
 *  ICMMultiPassGetTimeStampCallback
 *  
 *  Summary:
 *    Retrieves a time stamp for which a value is stored.
 *  
 *  Parameters:
 *    
 *    storageRefCon:
 *      The callbacks' reference value.
 *    
 *    fromTimeStamp:
 *      The initial time stamp.  Ignored for some values of step.
 *    
 *    step:
 *      Indicates the kind of time stamp search to perform.
 *    
 *    timeStampOut:
 *      Points to a TimeValue64 to receive the found time stamp. Set to
 *      -1 if no time stamp is found.
 */
typedef CALLBACK_API_C( OSStatus , ICMMultiPassGetTimeStampCallback )(void *storageRefCon, TimeValue64 fromTimeStamp, ICMMultiPassStorageStep step, TimeValue64 *timeStampOut);

/*
 *  ICMMultiPassCopyDataAtTimeStampCallback
 *  
 *  Summary:
 *    Retrieves a value at a given time stamp and index.
 *  
 *  Parameters:
 *    
 *    storageRefCon:
 *      The callbacks' reference value.
 *    
 *    timeStamp:
 *      The time stamp at which the value should be retrieved.
 *    
 *    index:
 *      An index by which multiple values may be stored at a time
 *      stamp. The meaning of individual indexes is private to the
 *      compressor.
 *    
 *    dataOut:
 *      Points to a variable to receive the value. Set to a
 *      newly-created CFMutableData containing the value for the given
 *      time stamp and index, or set to NULL if no value is at that
 *      time stamp and index. It will be the callers responsibility to
 *      release the CFMutableData.
 */
typedef CALLBACK_API_C( OSStatus , ICMMultiPassCopyDataAtTimeStampCallback )(void *storageRefCon, TimeValue64 timeStamp, long index, CFMutableDataRef *dataOut);

/*
 *  ICMMultiPassReleaseCallback
 *  
 *  Summary:
 *    Called when the multipass storage's retain count drops to zero.
 *  
 *  Parameters:
 *    
 *    storageRefCon:
 *      The callbacks' reference value.
 */
typedef CALLBACK_API_C( OSStatus , ICMMultiPassReleaseCallback )(void * storageRefCon);

/*
 *  ICMMultiPassStorageCallbacks
 *  
 *  Summary:
 *    A collection of callbacks for creating a custom multipass storage
 *    object.
 */
struct ICMMultiPassStorageCallbacks {

  /*
   * The version of the struct.  Set to
   * kICMMultiPassStorageCallbacksVersionOne.
   */
  UInt32              version;

  /*
   * The callbacks' reference value.
   */
  void *              storageRefCon;

  /*
   * The callback for storing values.
   */
  ICMMultiPassSetDataAtTimeStampCallback  setDataAtTimeStampCallback;

  /*
   * The callback for finding time stamps.
   */
  ICMMultiPassGetTimeStampCallback  getTimeStampCallback;

  /*
   * The callback for retrieving values.
   */
  ICMMultiPassCopyDataAtTimeStampCallback  copyDataAtTimeStampCallback;

  /*
   * The callback for disposing the callback's state when done.
   */
  ICMMultiPassReleaseCallback  releaseCallback;
};
typedef struct ICMMultiPassStorageCallbacks ICMMultiPassStorageCallbacks;
enum {
  kICMMultiPassStorageCallbacksVersionOne = 1
};

/*
 *  ICMMultiPassStorageCreateWithCallbacks()
 *  
 *  Summary:
 *    Assembles a multipass storage mechanism from callbacks.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMMultiPassStorageCreateWithCallbacks(
  CFAllocatorRef                  allocator,                 /* can be NULL */
  ICMMultiPassStorageCallbacks *  callbacks,
  ICMMultiPassStorageRef *        multiPassStorageOut)        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMMultiPassStorageRetain()
 *  
 *  Summary:
 *    Increments the retain count of a multipass storage object.
 *  
 *  Discussion:
 *    If you pass NULL to this function, nothing happens.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ICMMultiPassStorageRef 
ICMMultiPassStorageRetain(ICMMultiPassStorageRef multiPassStorage) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMMultiPassStorageRelease()
 *  
 *  Summary:
 *    Decrements the retain count of a multipass storage object.  If it
 *    drops to zero, the object is disposed.
 *  
 *  Discussion:
 *    If you pass NULL to this function, nothing happens.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
ICMMultiPassStorageRelease(ICMMultiPassStorageRef multiPassStorage) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMMultiPassStorageGetTypeID()
 *  
 *  Summary:
 *    Returns the CFTypeID for multipass storage objects.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFTypeID 
ICMMultiPassStorageGetTypeID(void)                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/* ICMCompressionFrameOptionsRef routines */
/*
 *  ICMCompressionFrameOptionsCreate()
 *  
 *  Summary:
 *    Creates a frame compression options object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionFrameOptionsCreate(
  CFAllocatorRef                   allocator,       /* can be NULL */
  ICMCompressionSessionRef         session,
  ICMCompressionFrameOptionsRef *  options)                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionFrameOptionsCreateCopy()
 *  
 *  Summary:
 *    Copies a frame compression options object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionFrameOptionsCreateCopy(
  CFAllocatorRef                   allocator,             /* can be NULL */
  ICMCompressionFrameOptionsRef    originalOptions,
  ICMCompressionFrameOptionsRef *  copiedOptions)             AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionFrameOptionsRetain()
 *  
 *  Summary:
 *    Increments the retain count of a frame compression options object.
 *  
 *  Discussion:
 *    If you pass NULL to this function, nothing happens.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ICMCompressionFrameOptionsRef 
ICMCompressionFrameOptionsRetain(ICMCompressionFrameOptionsRef options) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionFrameOptionsRelease()
 *  
 *  Summary:
 *    Decrements the retain count of a frame compression options
 *    object.  If it drops to zero, the object is disposed.
 *  
 *  Discussion:
 *    If you pass NULL to this function, nothing happens.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
ICMCompressionFrameOptionsRelease(ICMCompressionFrameOptionsRef options) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionFrameOptionsGetTypeID()
 *  
 *  Summary:
 *    Returns the CFTypeID for frame compression options objects.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFTypeID 
ICMCompressionFrameOptionsGetTypeID(void)                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionFrameOptionsGetPropertyInfo()
 *  
 *  Summary:
 *    Retrieves information about properties of a compression frame
 *    options object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionFrameOptionsGetPropertyInfo(
  ICMCompressionFrameOptionsRef   options,
  ComponentPropertyClass          inPropClass,
  ComponentPropertyID             inPropID,
  ComponentValueType *            outPropType,            /* can be NULL */
  ByteCount *                     outPropValueSize,       /* can be NULL */
  UInt32 *                        outPropertyFlags)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionFrameOptionsGetProperty()
 *  
 *  Summary:
 *    Retrieves the value of a specific property of a compression frame
 *    options object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionFrameOptionsGetProperty(
  ICMCompressionFrameOptionsRef   options,
  ComponentPropertyClass          inPropClass,
  ComponentPropertyID             inPropID,
  ByteCount                       inPropValueSize,
  ComponentValuePtr               outPropValueAddress,
  ByteCount *                     outPropValueSizeUsed)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionFrameOptionsSetProperty()
 *  
 *  Summary:
 *    Sets the value of a specific property of a compression frame
 *    options object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionFrameOptionsSetProperty(
  ICMCompressionFrameOptionsRef   options,
  ComponentPropertyClass          inPropClass,
  ComponentPropertyID             inPropID,
  ByteCount                       inPropValueSize,
  ConstComponentValuePtr          inPropValueAddress)         AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  Summary:
 *    Properties of compression frame options objects.
 */
enum {

  /*
   * Class identifier for compression frame options object properties.
   */
  kQTPropertyClass_ICMCompressionFrameOptions = 'icfo',

  /*
   * Forces frames to be compressed as key frames. 
   * The compressor must obey the "force key frame" flag if set. By
   * default this property is false.
   */
  kICMCompressionFrameOptionsPropertyID_ForceKeyFrame = 'keyf', /* Boolean, Read/Write */

  /*
   * Requests a frame be compressed as a particular frame type. 
   *  The frame type setting may be ignored by the compressor if not
   * appropriate. 
   * By default this is set to kICMFrameType_Unknown. 
   * Do not assume that kICMFrameType_I means a key frame; if you need
   * a key frame, set the "force key frame" property.
   */
  kICMCompressionFrameOptionsPropertyID_FrameType = 'frty' /* ICMFrameType, Read/Write */
};

/*
 *  ICMCompressionFrameOptionsSetForceKeyFrame()
 *  
 *  Summary:
 *    Forces frames to be compressed as key frames.
 *  
 *  Discussion:
 *    The compressor must obey the "force key frame" flag if set. By
 *    default this is set false.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionFrameOptionsSetForceKeyFrame(
  ICMCompressionFrameOptionsRef   options,
  Boolean                         forceKeyFrame)              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionFrameOptionsGetForceKeyFrame()
 *  
 *  Summary:
 *    Retrieves the "force key frame" flag.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
ICMCompressionFrameOptionsGetForceKeyFrame(ICMCompressionFrameOptionsRef options) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionFrameOptionsSetFrameType()
 *  
 *  Summary:
 *    Requests a frame be compressed as a particular frame type.
 *  
 *  Discussion:
 *    The frame type setting may be ignored by the compressor if not
 *    appropriate. 
 *    By default this is set to kICMFrameType_Unknown. 
 *    Do not assume that kICMFrameType_I means a key frame; if you need
 *    a key frame, set forceKeyFrame.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressionFrameOptionsSetFrameType(
  ICMCompressionFrameOptionsRef   options,
  ICMFrameType                    frameType)                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressionFrameOptionsGetFrameType()
 *  
 *  Summary:
 *    Retrieves the frame type setting.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ICMFrameType 
ICMCompressionFrameOptionsGetFrameType(ICMCompressionFrameOptionsRef options) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/* ICMEncodedFrameRef routines */
/*
 *  ICMEncodedFrameRetain()
 *  
 *  Summary:
 *    Increments the retain count of an encoded frame object.
 *  
 *  Discussion:
 *    If you pass NULL to this function, nothing happens.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ICMEncodedFrameRef 
ICMEncodedFrameRetain(ICMEncodedFrameRef frame)               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameRelease()
 *  
 *  Summary:
 *    Decrements the retain count of an encoded frame object.  If it
 *    drops to zero, the object is disposed.
 *  
 *  Discussion:
 *    If you pass NULL to this function, nothing happens.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
ICMEncodedFrameRelease(ICMEncodedFrameRef frame)              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameGetTypeID()
 *  
 *  Summary:
 *    Returns the CFTypeID for encoded frame objects.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFTypeID 
ICMEncodedFrameGetTypeID(void)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameGetDataPtr()
 *  
 *  Summary:
 *    Gets the data buffer.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern UInt8 * 
ICMEncodedFrameGetDataPtr(ICMEncodedFrameRef frame)           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameGetBufferSize()
 *  
 *  Summary:
 *    Gets the size of the data buffer.
 *  
 *  Discussion:
 *    This is the physical size of the buffer.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ByteCount 
ICMEncodedFrameGetBufferSize(ICMEncodedFrameRef frame)        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameGetDataSize()
 *  
 *  Summary:
 *    Gets the data size of the compressed frame in the buffer.
 *  
 *  Discussion:
 *    This is the logical size of the frame data. It may be less than
 *    the physical size of the buffer.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ByteCount 
ICMEncodedFrameGetDataSize(ICMEncodedFrameRef frame)          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameSetDataSize()
 *  
 *  Summary:
 *    Sets the data size of the compressed frame in the buffer.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMEncodedFrameSetDataSize(
  ICMMutableEncodedFrameRef   frame,
  ByteCount                   dataSize)                       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameGetDecodeNumber()
 *  
 *  Summary:
 *    Retrieves the decode number.
 *  
 *  Discussion:
 *    The ICM automatically stamps ascending decode numbers on frames
 *    after the compressor emits them. The first decode number in a
 *    session is 1. 
 *    Note: Compressors should not call this function.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern UInt32 
ICMEncodedFrameGetDecodeNumber(ICMEncodedFrameRef frame)      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameGetTimeScale()
 *  
 *  Summary:
 *    Retrieves the timescale.
 *  
 *  Discussion:
 *    This is always the same as the timescale of the compression
 *    session.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern TimeScale 
ICMEncodedFrameGetTimeScale(ICMEncodedFrameRef frame)         AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameGetImageDescription()
 *  
 *  Summary:
 *    Retrieves the image description.
 *  
 *  Discussion:
 *    Returns the same image description handle as
 *    ICMCompressionSessionGetImageDescription. 
 *    IMPORTANT: The caller should NOT dispose this handle.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMEncodedFrameGetImageDescription(
  ICMEncodedFrameRef        frame,
  ImageDescriptionHandle *  imageDescOut)                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameGetValidTimeFlags()
 *  
 *  Summary:
 *    Retrieves flags indicating which of the time stamps and durations
 *    are valid.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ICMValidTimeFlags 
ICMEncodedFrameGetValidTimeFlags(ICMEncodedFrameRef frame)    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameGetDecodeTimeStamp()
 *  
 *  Summary:
 *    Retrieves the frame's decode time stamp.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern TimeValue64 
ICMEncodedFrameGetDecodeTimeStamp(ICMEncodedFrameRef frame)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameGetDisplayTimeStamp()
 *  
 *  Summary:
 *    Retrieves the frame's display time stamp.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern TimeValue64 
ICMEncodedFrameGetDisplayTimeStamp(ICMEncodedFrameRef frame)  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameGetDisplayOffset()
 *  
 *  Summary:
 *    Retrieves the frame's display offset, which is the offset from
 *    decode time stamp to display time stamp.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern TimeValue64 
ICMEncodedFrameGetDisplayOffset(ICMEncodedFrameRef frame)     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameGetDecodeDuration()
 *  
 *  Summary:
 *    Retrieves the frame's decode duration.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern TimeValue64 
ICMEncodedFrameGetDecodeDuration(ICMEncodedFrameRef frame)    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameGetDisplayDuration()
 *  
 *  Summary:
 *    Retrieves the frame's display duration.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern TimeValue64 
ICMEncodedFrameGetDisplayDuration(ICMEncodedFrameRef frame)   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  ICMEncodedFrameSetValidTimeFlags()
 *  
 *  Summary:
 *    Sets flags that indicate which of the time stamps and durations
 *    are valid.
 *  
 *  Discussion:
 *    Note that setting the (decode/display) (timestamp/duration)
 *    automatically sets the corresponding valid time flags. For
 *    example, calling ICMEncodedFrameSetDecodeTimeStamp sets
 *    kICMValidTime_DisplayTimeStampIsValid. If both decode timestamp
 *    and display timestamp are valid,
 *    kICMValidTime_DisplayOffsetIsValid is automatically set.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMEncodedFrameSetValidTimeFlags(
  ICMMutableEncodedFrameRef   frame,
  ICMValidTimeFlags           validTimeFlags)                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameSetDecodeTimeStamp()
 *  
 *  Summary:
 *    Sets the decode time stamp.
 *  
 *  Discussion:
 *    This automatically sets the kICMValidTime_DecodeTimeStampIsValid
 *    flag. If the display timestamp is valid, it also sets the
 *    kICMValidTime_DisplayOffsetIsValid flag.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMEncodedFrameSetDecodeTimeStamp(
  ICMMutableEncodedFrameRef   frame,
  TimeValue64                 decodeTimeStamp)                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameSetDisplayTimeStamp()
 *  
 *  Summary:
 *    Sets the display time stamp.
 *  
 *  Discussion:
 *    This automatically sets the kICMValidTime_DisplayTimeStampIsValid
 *    flag. If the decode timestamp is valid, it also sets the
 *    kICMValidTime_DisplayOffsetIsValid flag.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMEncodedFrameSetDisplayTimeStamp(
  ICMMutableEncodedFrameRef   frame,
  TimeValue64                 displayTimeStamp)               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameSetDecodeDuration()
 *  
 *  Summary:
 *    Sets the decode duration.
 *  
 *  Discussion:
 *    This automatically sets the kICMValidTime_DecodeDurationIsValid
 *    flag.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMEncodedFrameSetDecodeDuration(
  ICMMutableEncodedFrameRef   frame,
  TimeValue64                 decodeDuration)                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameSetDisplayDuration()
 *  
 *  Summary:
 *    Sets the display duration.
 *  
 *  Discussion:
 *    This automatically sets the kICMValidTime_DisplayDurationIsValid
 *    flag.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMEncodedFrameSetDisplayDuration(
  ICMMutableEncodedFrameRef   frame,
  TimeValue64                 displayDuration)                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameGetMediaSampleFlags()
 *  
 *  Summary:
 *    Retrieves the media sample flags for an encoded frame.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern MediaSampleFlags 
ICMEncodedFrameGetMediaSampleFlags(ICMEncodedFrameRef frame)  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameSetMediaSampleFlags()
 *  
 *  Summary:
 *    Sets the media sample flags for an encoded frame.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMEncodedFrameSetMediaSampleFlags(
  ICMMutableEncodedFrameRef   frame,
  MediaSampleFlags            mediaSampleFlags)               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameGetFrameType()
 *  
 *  Summary:
 *    Retrieves the frame type for an encoded frame.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ICMFrameType 
ICMEncodedFrameGetFrameType(ICMEncodedFrameRef frame)         AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameSetFrameType()
 *  
 *  Summary:
 *    Sets the frame type for an encoded frame.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMEncodedFrameSetFrameType(
  ICMMutableEncodedFrameRef   frame,
  ICMFrameType                frameType)                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameGetSimilarity()
 *  
 *  Summary:
 *    Retrieves the similarity for an encoded frame.
 *  
 *  Discussion:
 *    1.0 means identical.  0.0 means not at all alike. By default,
 *    this is set to -1.0, which means unknown.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern Float32 
ICMEncodedFrameGetSimilarity(ICMEncodedFrameRef frame)        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameSetSimilarity()
 *  
 *  Summary:
 *    Sets the similarity for an encoded frame.
 *  
 *  Discussion:
 *    1.0 means identical.  0.0 means not at all alike.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMEncodedFrameSetSimilarity(
  ICMMutableEncodedFrameRef   frame,
  Float32                     similarity)                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameGetSourceFrameRefCon()
 *  
 *  Summary:
 *    Retrieves the source frame reference value.
 *  
 *  Discussion:
 *    This is copied from the sourceFrameRefCon parameter to
 *    ICMCompressionSessionEncodeFrame.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void * 
ICMEncodedFrameGetSourceFrameRefCon(ICMEncodedFrameRef frame) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* ICMCompressorSession interface for compressor components */

/*
 *  ICMCompressorSessionRef
 *  
 *  Summary:
 *    Represents the session between the ICM and an image compressor
 *    component.
 *  
 *  Discussion:
 *    (Do not confuse this with ICMCompressionSessionRef, which is the
 *    session between the client and the ICM.) Note: compressors do not
 *    need to make any retain or release calls on this token.
 */
typedef struct OpaqueICMCompressorSession*  ICMCompressorSessionRef;

/*
 *  ICMCompressorSourceFrameRef
 *  
 *  Summary:
 *    An opaque token that represents a frame that has been passed to
 *    ICMCompressionSessionEncodeFrame.
 *  
 *  Discussion:
 *    Such tokens are passed to the compressor component, which may
 *    retain a window of them in order to perform out-of-order encoding.
 */
typedef struct OpaqueICMCompressorSourceFrame*  ICMCompressorSourceFrameRef;
/*
 *  ICMCompressorSourceFrameRetain()
 *  
 *  Summary:
 *    Increments the retain count of a source frame object.
 *  
 *  Discussion:
 *    If you pass NULL to this function, nothing happens.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ICMCompressorSourceFrameRef 
ICMCompressorSourceFrameRetain(ICMCompressorSourceFrameRef sourceFrame) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressorSourceFrameRelease()
 *  
 *  Summary:
 *    Decrements the retain count of a source frame object.  If it
 *    drops to zero, the object is disposed.
 *  
 *  Discussion:
 *    If you pass NULL to this function, nothing happens.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
ICMCompressorSourceFrameRelease(ICMCompressorSourceFrameRef sourceFrame) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressorSourceFrameGetTypeID()
 *  
 *  Summary:
 *    Returns the CFTypeID for source frame objects.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFTypeID 
ICMCompressorSourceFrameGetTypeID(void)                       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressorSourceFrameGetPixelBuffer()
 *  
 *  Summary:
 *    Retrieves a source frame's pixel buffer.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CVPixelBufferRef 
ICMCompressorSourceFrameGetPixelBuffer(ICMCompressorSourceFrameRef sourceFrame) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressorSourceFrameGetDisplayNumber()
 *  
 *  Summary:
 *    Retrieves a source frame's display number.
 *  
 *  Discussion:
 *    The ICM tags source frames with display numbers in the order they
 *    are passed to ICMCompressionSessionEncodeFrame; the first display
 *    number is 1. Compressors may compare these numbers to work out
 *    whether prediction is forward or backward even when display times
 *    are not provided.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern long 
ICMCompressorSourceFrameGetDisplayNumber(ICMCompressorSourceFrameRef sourceFrame) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressorSourceFrameGetDisplayTimeStampAndDuration()
 *  
 *  Summary:
 *    Retrieves the display time stamp and duration of a source frame.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressorSourceFrameGetDisplayTimeStampAndDuration(
  ICMCompressorSourceFrameRef   sourceFrame,
  TimeValue64 *                 displayTimeStampOut,       /* can be NULL */
  TimeValue64 *                 displayDurationOut,        /* can be NULL */
  TimeScale *                   timeScaleOut,              /* can be NULL */
  ICMValidTimeFlags *           validTimeFlagsOut)         /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressorSourceFrameGetFrameOptions()
 *  
 *  Summary:
 *    Retrieves the frame compression options for a source frame.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ICMCompressionFrameOptionsRef 
ICMCompressorSourceFrameGetFrameOptions(ICMCompressorSourceFrameRef sourceFrame) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressorSourceFrameDetachPixelBuffer()
 *  
 *  Summary:
 *    Disconnects the pixel buffer from the source frame and allows it
 *    to be released.
 *  
 *  Discussion:
 *    Compressor components often need to hold onto
 *    ICMCompressorSourceFrameRefs for some time after they are done
 *    with the pixel buffers. In order to allow pixel buffer memory to
 *    be released earlier, they may call
 *    ICMCompressorSourceFrameDetachPixelBuffer to declare that they
 *    have no further need for the source frame's pixel buffer. After
 *    calling this, ICMCompressorSourceFrameGetPixelBuffer will return
 *    NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressorSourceFrameDetachPixelBuffer(ICMCompressorSourceFrameRef sourceFrame) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  ICMCompressorSessionDropFrame()
 *  
 *  Summary:
 *    Called by a compressor to indicate that sourceFrame has been
 *    dropped and will not contribute to any encoded frames.
 *  
 *  Discussion:
 *    Calling this function does not automatically release the source
 *    frame; if the compressor called ICMCompressorSourceFrameRetain it
 *    should still call ICMCompressorSourceFrameRelease.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressorSessionDropFrame(
  ICMCompressorSessionRef       session,
  ICMCompressorSourceFrameRef   sourceFrame)                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMCompressorSessionEmitEncodedFrame()
 *  
 *  Summary:
 *    Called by a compressor to output an encoded frame corresponding
 *    to one (or more) source frames.
 *  
 *  Discussion:
 *    (Encoded frames may only correspond to more than one source frame
 *    if allowFrameTimeChanges is set in the
 *    compressionSessionOptions.) 
 *    After calling this, the compressor should release the encoded
 *    frame by calling ICMEncodedFrameRelease. 
 *    Calling this function does not automatically release the source
 *    frames; if the compressor called ICMCompressorSourceFrameRetain
 *    it should still call ICMCompressorSourceFrameRelease.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMCompressorSessionEmitEncodedFrame(
  ICMCompressorSessionRef       session,
  ICMMutableEncodedFrameRef     encodedFrame,
  long                          numberOfSourceFrames,
  ICMCompressorSourceFrameRef   sourceFrames[])               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMEncodedFrameCreateMutable()
 *  
 *  Summary:
 *    Called by a compressor to create an encoded-frame token
 *    corresponding to a given source frame.
 *  
 *  Discussion:
 *    The encoded frame will initially have zero mediaSampleFlags; if
 *    the frame is not a key frame, the compressor must call
 *    ICMEncodedFrameSetMediaSampleFlags to set mediaSampleNotSync. If
 *    the frame is droppable, the compressor should set
 *    mediaSampleDroppable. If the frame is a partial key frame, the
 *    compressor should set mediaSamplePartialSync. 
 *    The encoded frame will initially have undefined decodeTimeStamp
 *    and decodeDuration. The compressor may set these directly by
 *    calling ICMEncodedFrameSetDecodeTimeStamp and/or
 *    ICMEncodedFrameSetDecodeDuration. If these are not set by the
 *    compressor, the ICM will attempt to derive them.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMEncodedFrameCreateMutable(
  ICMCompressorSessionRef       session,
  ICMCompressorSourceFrameRef   sourceFrame,
  ByteCount                     bufferSize,
  ICMMutableEncodedFrameRef *   frameOut)                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Multi-pass storage access routines for compressor components */
/*
 *  ICMMultiPassStorageSetDataAtTimeStamp()
 *  
 *  Summary:
 *    Called by a multipass-capable compressor to store data at a given
 *    timestamp.
 *  
 *  Discussion:
 *    The new data replaces any previous data held at that timestamp.
 *    If data is NULL, the data for that timestamp is deleted. The
 *    format of the data is private to the compressor.
 *  
 *  Parameters:
 *    
 *    multiPassStorage:
 *      The multipass storage object.
 *    
 *    timeStamp:
 *      The time stamp at which the value should be stored.
 *    
 *    index:
 *      An index by which multiple values may be stored at a time
 *      stamp. The meaning of individual indexes is private to the
 *      compressor.
 *    
 *    data:
 *      The data to be stored, or NULL to delete the value.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMMultiPassStorageSetDataAtTimeStamp(
  ICMMultiPassStorageRef   multiPassStorage,
  TimeValue64              timeStamp,
  long                     index,
  CFDataRef                data)                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMMultiPassStorageGetTimeStamp()
 *  
 *  Summary:
 *    Called by a multipass-capable compressor to retrieve a time stamp
 *    for which a value is stored.
 *  
 *  Parameters:
 *    
 *    multiPassStorage:
 *      The multipass storage object.
 *    
 *    fromTimeStamp:
 *      The initial time stamp.  Ignored for some values of step.
 *    
 *    step:
 *      Indicates the kind of time stamp search to perform.
 *    
 *    timeStampOut:
 *      Points to a TimeValue64 to receive the found time stamp. It
 *      will be set to -1 if no time stamp is found.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMMultiPassStorageGetTimeStamp(
  ICMMultiPassStorageRef    multiPassStorage,
  TimeValue64               fromTimeStamp,
  ICMMultiPassStorageStep   step,
  TimeValue64 *             timeStampOut)                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  ICMMultiPassStorageCopyDataAtTimeStamp()
 *  
 *  Summary:
 *    Called by a multipass-capable compressor to retrieve data at a
 *    given timestamp.
 *  
 *  Parameters:
 *    
 *    multiPassStorage:
 *      The multipass storage object.
 *    
 *    timeStamp:
 *      The time stamp at which the value should be retrieved.
 *    
 *    index:
 *      An index by which multiple values may be stored at a time
 *      stamp. The meaning of individual indexes is private to the
 *      compressor.
 *    
 *    dataOut:
 *      Points to a CFMutableDataRef to receive the value. It will be
 *      set to a newly-created CFMutableData containing the value for
 *      the given time stamp and index, or set to NULL if no value is
 *      at that time stamp and index. It is the caller's responsibility
 *      to release the CFMutableData.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ICMMultiPassStorageCopyDataAtTimeStamp(
  ICMMultiPassStorageRef   multiPassStorage,
  TimeValue64              timeStamp,
  long                     index,
  CFMutableDataRef *       dataOut)                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;




/*
 *  kQTVisualContextTypeKey
 *  
 *  Summary:
 *    Read-only CFStringRef: Type of the visual context.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kQTVisualContextTypeKey                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kQTVisualContextType_PixelBuffer
 *  
 *  Summary:
 *    Value for kQTVisualContextTypeKey for pixel buffer visual
 *    contexts.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kQTVisualContextType_PixelBuffer            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kQTVisualContextType_OpenGLTexture
 *  
 *  Summary:
 *    Value for kQTVisualContextTypeKey for OpenGL texture visual
 *    contexts.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kQTVisualContextType_OpenGLTexture          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kQTVisualContextWorkingColorSpaceKey
 *  
 *  Summary:
 *    CGColorSpaceRef: Color space in which QuickTime will perform
 *    image processing. If this attribute is not set, images will be
 *    processed in the output color space.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kQTVisualContextWorkingColorSpaceKey        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kQTVisualContextOutputColorSpaceKey
 *  
 *  Summary:
 *    CGColorSpaceRef: Color space of images produced by this visual
 *    context. If this attribute is not set, images may be in any color
 *    space.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kQTVisualContextOutputColorSpaceKey         AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kQTVisualContextExpectedReadAheadKey
 *  
 *  Summary:
 *    CFNumberRef: Number of seconds ahead of real-time that the client
 *    expects to pull images out of the visual context.  Applications
 *    using the CoreVideo display link should set this attribute
 *    according to value returned from
 *    CVDisplayLinkGetOutputVideoLatency().
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kQTVisualContextExpectedReadAheadKey        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kQTVisualContextPixelBufferAttributesKey
 *  
 *  Summary:
 *    CFDictionaryRef: Dictionary containing pixel buffer attributes as
 *    described for the CoreVideo pixel buffer pool.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kQTVisualContextPixelBufferAttributesKey    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kQTVisualContextTargetDimensionsKey
 *  
 *  Summary:
 *    CFDictionaryRef: Dictionary containing
 *    kQTVisualContextTargetDimensions_WidthKey and
 *    kQTVisualContextTargetDimensions_HeightKey.  This is only a hint
 *    to optimize certain media types, such as text, that can render at
 *    any resolution. If this attribute is not set, the movie will
 *    render at its native resolution.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kQTVisualContextTargetDimensionsKey         AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kQTVisualContextTargetDimensions_WidthKey
 *  
 *  Summary:
 *    CFNumberRef: Width, in pixels, of the rendering target.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kQTVisualContextTargetDimensions_WidthKey   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kQTVisualContextTargetDimensions_HeightKey
 *  
 *  Summary:
 *    CFNumberRef: Height, in pixels, of the rendering target.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kQTVisualContextTargetDimensions_HeightKey  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  QTVisualContextRetain()
 *  
 *  Summary:
 *    Increments the visual context's reference count.
 *  
 *  Discussion:
 *    The same visual context is returned for convenience. If
 *    visualContext is NULL, nothing happens.
 *  
 *  Parameters:
 *    
 *    visualContext:
 *      [in] The visual context to retain.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern QTVisualContextRef 
QTVisualContextRetain(QTVisualContextRef visualContext)       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTVisualContextRelease()
 *  
 *  Summary:
 *    Decrements the visual context's reference count.
 *  
 *  Discussion:
 *    If the retain count decreases to zero, the visual context is
 *    disposed. If visualContext is NULL, nothing happens.
 *  
 *  Parameters:
 *    
 *    visualContext:
 *      [in] The visual context to release.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
QTVisualContextRelease(QTVisualContextRef visualContext)      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTVisualContextGetTypeID()
 *  
 *  Summary:
 *    Returns the CFTypeID for QTVisualContextRef.
 *  
 *  Discussion:
 *    You could use this to test whether a CFTypeRef that extracted
 *    from a CF container such as a CFArray was a QTVisualContextRef. 
 *    All visual contexts have the same CFTypeID.  If you need to
 *    distinguish between different types of visual contexts (eg.
 *    PixelBuffer vs. OpenGLTexture), query for kQTVisualContextTypeKey
 *    with QTVisualContextGetAttribute().
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFTypeID 
QTVisualContextGetTypeID(void)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTVisualContextSetAttribute()
 *  
 *  Summary:
 *    Sets a visual context attribute.
 *  
 *  Parameters:
 *    
 *    visualContext:
 *      [in] The visual context.
 *    
 *    attributeKey:
 *      [in] Identifier of attribute to set.
 *    
 *    attributeValue:
 *      [in] Value of attribute to set, or NULL to remove a value.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QTVisualContextSetAttribute(
  QTVisualContextRef   visualContext,
  CFStringRef          attributeKey,
  CFTypeRef            attributeValue)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTVisualContextGetAttribute()
 *  
 *  Summary:
 *    Gets a visual context attribute.
 *  
 *  Parameters:
 *    
 *    visualContext:
 *      [in]  The visual context.
 *    
 *    attributeKey:
 *      [in]  Identifier of attribute to get.
 *    
 *    attributeValueOut:
 *      [out] Pointer to variable that will receive the attribute
 *      value, or NULL if the attribute is not set.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QTVisualContextGetAttribute(
  QTVisualContextRef   visualContext,
  CFStringRef          attributeKey,
  CFTypeRef *          attributeValueOut)                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  QTVisualContextImageAvailableCallback
 *  
 *  Summary:
 *    User-defined callback function to recieve notifications when a
 *    new image becomes available.
 *  
 *  Discussion:
 *    Due to unpredictible activity, such as user seeks or the arrival
 *    of streaming video packets from a network, new images may become
 *    available for times supposedly occupied by previous images. 
 *    Applications using the CoreVideo display link to drive rendering
 *    probably do not need to install a callback of this type since
 *    they will already be checking for new images at a sufficient rate.
 *  
 *  Parameters:
 *    
 *    visualContext:
 *      [in] The visual context invoking the callback.
 *    
 *    timeStamp:
 *      [in] Time for which a new image has become available.
 *    
 *    refCon:
 *      [in] User-defined value passed to
 *      QTVisualContextSetImageAvailableCallback.
 */
typedef CALLBACK_API_C( void , QTVisualContextImageAvailableCallback )(QTVisualContextRef visualContext, const CVTimeStamp *timeStamp, void *refCon);
/*
 *  QTVisualContextSetImageAvailableCallback()
 *  
 *  Summary:
 *    Installs user-defined callback to be notified when new images
 *    become available.
 *  
 *  Discussion:
 *    This routine installs the user defined
 *    QTVisualContextImageAvailableCallback callback. There can only be
 *    one callback associated with a QTVisualContext at a given time.
 *  
 *  Parameters:
 *    
 *    visualContext:
 *      [in] The visual context.
 *    
 *    imageAvailableCallback:
 *      [in] User-defined callback function to recieve notifications.
 *      Pass NULL to remove any existing callback.
 *    
 *    refCon:
 *      [in] User-defined value to pass to
 *      QTVisualContextImageAvailableCallback.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QTVisualContextSetImageAvailableCallback(
  QTVisualContextRef                      visualContext,
  QTVisualContextImageAvailableCallback   imageAvailableCallback,       /* can be NULL */
  void *                                  refCon)                       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTVisualContextIsNewImageAvailable()
 *  
 *  Summary:
 *    Queries whether a new image is available for a given time.
 *  
 *  Discussion:
 *    This function returns true if there is a image available for the
 *    specified time that is different from the last image retrieved
 *    from QTVisualContextCopyImageForTime. See
 *    QTVisualContextCopyImageForTime for restrictions on time-stamps.
 *  
 *  Parameters:
 *    
 *    visualContext:
 *      [in] The visual context.
 *    
 *    timeStamp:
 *      [in] Time in question.  Pass NULL to request the image at the
 *      current time.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
QTVisualContextIsNewImageAvailable(
  QTVisualContextRef   visualContext,
  const CVTimeStamp *  timeStamp)           /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTVisualContextCopyImageForTime()
 *  
 *  Summary:
 *    Retrieves an image buffer from the visual context, indexed by the
 *    provided timestamp.
 *  
 *  Discussion:
 *    You should not request image buffers further ahead of the current
 *    time than the read-ahead time specified with the
 *    kQTVisualContextExpectedReadAheadKey attribute.  You may skip
 *    images by passing later times, but you may not pass an earlier
 *    time than passed to a previous call to this function.
 *  
 *  Parameters:
 *    
 *    visualContext:
 *      [in]  The visual context.
 *    
 *    allocator:
 *      [in]  Allocator used to create new CVImageBufferRef.
 *    
 *    timeStamp:
 *      [in]  Time in question.  Pass NULL to request the image at the
 *      current time.
 *    
 *    newImage:
 *      [out] Points to variable to receive new image. If there is no
 *      video at the requested time, this variable will be set to NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QTVisualContextCopyImageForTime(
  QTVisualContextRef   visualContext,
  CFAllocatorRef       allocator,           /* can be NULL */
  const CVTimeStamp *  timeStamp,           /* can be NULL */
  CVImageBufferRef *   newImage)                              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTVisualContextTask()
 *  
 *  Summary:
 *    Causes visual context to release internally held resources for
 *    later re-use.
 *  
 *  Discussion:
 *    For optimal resource management, this function should be called
 *    in every rendering pass, after old images have been released, new
 *    images have been used and all rendering has been flushed to the
 *    screen.  This call is not mandatory.
 *  
 *  Parameters:
 *    
 *    visualContext:
 *      [in] The visual context.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
QTVisualContextTask(QTVisualContextRef visualContext)         AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTOpenGLTextureContextCreate()
 *  
 *  Summary:
 *    Creates a new OpenGL texture context for the given OpenGL context
 *    and pixel format.
 *  
 *  Discussion:
 *    This function will fail if the graphics hardware is insufficient.
 *  
 *  Parameters:
 *    
 *    allocator:
 *      [in]  Allocator used to create the texture context.
 *    
 *    cglContext:
 *      [in]  OpenGL context used to create textures.
 *    
 *    cglPixelFormat:
 *      [in]  OpenGL pixel format used to create the OpenGL context.
 *    
 *    attributes:
 *      [in]  Dictionary of attributes.
 *    
 *    newTextureContext:
 *      [out] Points to a variable to recieve the new OpenGL texture
 *      context.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QTOpenGLTextureContextCreate(
  CFAllocatorRef        allocator,               /* can be NULL */
  CGLContextObj         cglContext,
  CGLPixelFormatObj     cglPixelFormat,
  CFDictionaryRef       attributes,              /* can be NULL */
  QTVisualContextRef *  newTextureContext)                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTPixelBufferContextCreate()
 *  
 *  Summary:
 *    Creates a new pixel buffer context with the given attributes.
 *  
 *  Discussion:
 *    This function will fail if the graphics hardware is insufficient.
 *  
 *  Parameters:
 *    
 *    allocator:
 *      [in]  Allocator used to create the pixel buffer context.
 *    
 *    attributes:
 *      [in]  Dictionary of attributes.
 *    
 *    newPixelBufferContext:
 *      [out] Points to a variable to recieve the new pixel buffer
 *      context.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QTPixelBufferContextCreate(
  CFAllocatorRef        allocator,                   /* can be NULL */
  CFDictionaryRef       attributes,                  /* can be NULL */
  QTVisualContextRef *  newPixelBufferContext)                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


#if TARGET_OS_WIN32
/*
 *  QTDirect3DTextureContextCreate()
 *  
 *  Summary:
 *    Creates a new Direct3D texture context for the given Direct3D
 *    device and pixel format.
 *  
 *  Discussion:
 *    This function will fail if the graphics hardware is insufficient.
 *  
 *  Parameters:
 *    
 *    allocator:
 *      [in]  Allocator used to create the texture context.
 *    
 *    d3dDevice:
 *      [in]  Direct3D device used to create textures.
 *    
 *    d3dPixelFormat:
 *      [in]  Direct3D pixel format used to create the Direct3D device.
 *    
 *    attributes:
 *      [in]  Dictionary of attributes.
 *    
 *    newTextureContext:
 *      [out] Points to a variable to recieve the new Direct3D texture
 *      context.
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.6 and later
 */


#endif  /* TARGET_OS_WIN32 */


#endif // !__LP64__



#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* __IMAGECOMPRESSION__ */

