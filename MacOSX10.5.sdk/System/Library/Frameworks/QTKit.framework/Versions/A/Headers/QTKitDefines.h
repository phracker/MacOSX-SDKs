/*
	File:		QTKitDefines.h

	Copyright:	(c)2004-2007 by Apple Inc., all rights reserved.

*/


#ifndef _QTKITDEFINES_H
#define _QTKITDEFINES_H

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

#ifndef MAC_OS_X_VERSION_10_4
#define MAC_OS_X_VERSION_10_4		1040
#else
#undef MAC_OS_X_VERSION_10_4
#define MAC_OS_X_VERSION_10_4		1040
#endif

#ifndef MAC_OS_X_VERSION_10_5
#define MAC_OS_X_VERSION_10_5		1050
#else
#undef MAC_OS_X_VERSION_10_5
#define MAC_OS_X_VERSION_10_5		1050
#endif

/*
 QTKit Availability Macros
 
 These macros allow applications to target specific versions of QTKit independently
 of the OS on which the application is built. To target one or more versions of
 QTKit, you can use the QTKIT_VERSION_MIN_REQUIRED and the QTKIT_VERSION_MAX_ALLOWED
 macros in a a way that is analagous to MAC_OS_X_VERSION_MIN_REQUIRED and
 MAC_OS_X_VERSION_MAX_ALLOWED as described in /usr/include/AvailabilityMacros.h. By
 default, the macros are configured to weak-link to symbols as necessary for the
 application to run on all target versions of Max OS X.
 
 IMPORTANT: These macros only properly expose or restrict the available API at
 compile and link time. Since QTKit is released for multiple versions of Mac OS X,
 some of which may not have a given version installed by default, applications must
 also verify whether or not an API exists at run time. It is recommended that
 applications do this by checking which version of QuickTime is installed. Such a
 check also allows applications to ensure they are running against the latest version
 of QTKit in which an API is supported. For example, applications targeting APIs
 introduced for QTKit 7.2 should make sure they are running against QuickTime 7.2.1
 or later, which is the first release for which the QuickTime 7.2 SDK is supported.
 One way to check the QuickTime version is use the Gestalt API. For example, to use
 an API that first became supported in QTKit 7.2, an application would do the
 following:
 
 OSErr err;
 UInt32 qtVersion;
 
 err = Gestalt(gestaltQuickTimeVersion, &qtVersion);
 if ((err == noErr) && (qtVersion >= 0x07210000)) {
     // Use API introduced in QTKit 7.2.1
 }
 
 */

#define QTKIT_VERSION_7_0           70000
#define QTKIT_VERSION_7_2           70200

#ifndef QTKIT_VERSION_MIN_REQUIRED
    #if MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_5
        #define QTKIT_VERSION_MIN_REQUIRED QTKIT_VERSION_7_2
    #else
        #define QTKIT_VERSION_MIN_REQUIRED QTKIT_VERSION_7_0
    #endif
#endif

#ifndef QTKIT_VERSION_MAX_ALLOWED
    #define QTKIT_VERSION_MAX_ALLOWED QTKIT_VERSION_7_2
#endif

// error on bad values
#if QTKIT_VERSION_MAX_ALLOWED < QTKIT_VERSION_MIN_REQUIRED
    #error QTKIT_VERSION_MAX_ALLOWED must be >= QTKIT_VERSION_MIN_REQUIRED
#endif
#if QTKIT_VERSION_MIN_REQUIRED < QTKIT_VERSION_7_0
    #error QTKIT_VERSION_MIN_REQUIRED must be >= QTKIT_VERSION_7_0
#endif

#ifdef __cplusplus
#define QTKIT_EXTERN extern "C"
#else
#define QTKIT_EXTERN extern
#endif

#define QTKIT_HIDDEN __attribute__((visibility("hidden")))

#ifndef NSINTEGER_DEFINED

#if __LP64__ || NS_BUILD_32_LIKE_64
typedef long NSInteger;
typedef unsigned long NSUInteger;
#else
typedef int NSInteger;
typedef unsigned int NSUInteger;
#endif


#define NSIntegerMax    LONG_MAX
#define NSIntegerMin    LONG_MIN
#define NSUIntegerMax   ULONG_MAX

#define NSINTEGER_DEFINED 1

#endif	/* NSINTEGER_DEFINED */

#if __LP64__
// constants and data types defined in the 32-bit QuickTime headers that may be required for some QTKit APIs
	// from Movies.h
enum {
	VideoMediaType						= 'vide',
	SoundMediaType						= 'soun',
	TextMediaType						= 'text',
	BaseMediaType						= 'gnrc',
	MPEGMediaType						= 'MPEG',
	MusicMediaType						= 'musi',
	TimeCodeMediaType					= 'tmcd',
	SpriteMediaType						= 'sprt',
	FlashMediaType						= 'flsh',
	MovieMediaType						= 'moov',
	TweenMediaType						= 'twen',
	ThreeDeeMediaType					= 'qd3d',
	SkinMediaType						= 'skin',
	HandleDataHandlerSubType			= 'hndl',
	PointerDataHandlerSubType			= 'ptr ',
	NullDataHandlerSubType				= 'null',
	ResourceDataHandlerSubType			= 'rsrc',
	URLDataHandlerSubType				= 'url ',
	AliasDataHandlerSubType				= 'alis',
	WiredActionHandlerType				= 'wire',
	kQTQuartzComposerMediaType			= 'qtz ',
	TimeCode64MediaType					= 'tc64'
};

	// from QuickTimeComponents.h
enum {
	kQTFileTypeAIFF						= 'AIFF',
	kQTFileTypeAIFC						= 'AIFC',
	kQTFileTypeDVC						= 'dvc!',
	kQTFileTypeMIDI						= 'Midi',
	kQTFileTypePicture					= 'PICT',
	kQTFileTypeMovie					= 'MooV',
	kQTFileTypeText						= 'TEXT',
	kQTFileTypeWave						= 'WAVE',
	kQTFileTypeSystemSevenSound			= 'sfil',
	kQTFileTypeMuLaw					= 'ULAW',
	kQTFileTypeAVI						= 'VfW ',
	kQTFileTypeSoundDesignerII			= 'Sd2f',
	kQTFileTypeAudioCDTrack				= 'trak',
	kQTFileTypePICS						= 'PICS',
	kQTFileTypeGIF						= 'GIFf',
	kQTFileTypePNG						= 'PNGf',
	kQTFileTypeTIFF						= 'TIFF',
	kQTFileTypePhotoShop				= '8BPS',
	kQTFileTypeSGIImage					= '.SGI',
	kQTFileTypeBMP						= 'BMPf',
	kQTFileTypeJPEG						= 'JPEG',
	kQTFileTypeJFIF						= 'JPEG',
	kQTFileTypeMacPaint					= 'PNTG',
	kQTFileTypeTargaImage				= 'TPIC',
	kQTFileTypeQuickDrawGXPicture		= 'qdgx',
	kQTFileTypeQuickTimeImage			= 'qtif',
	kQTFileType3DMF						= '3DMF',
	kQTFileTypeFLC						= 'FLC ',
	kQTFileTypeFlash					= 'SWFL',
	kQTFileTypeFlashPix					= 'FPix',
	kQTFileTypeMP4						= 'mpg4',
	kQTFileTypePDF						= 'PDF ',
	kQTFileType3GPP						= '3gpp',
	kQTFileTypeAMR						= 'amr ',
	kQTFileTypeSDV						= 'sdv ',
	kQTFileType3GP2						= '3gp2',
	kQTFileTypeAMC						= 'amc ',
	kQTFileTypeJPEG2000					= 'jp2 '
};

	// from ImageCompression.h
enum {
	codecLosslessQuality				= 0x00000400,
	codecMaxQuality						= 0x000003FF,
	codecMinQuality						= 0x00000000,
	codecLowQuality						= 0x00000100,
	codecNormalQuality					= 0x00000200,
	codecHighQuality					= 0x00000300
};

enum {
	kRawCodecType						= 'raw ',
	kCinepakCodecType 					= 'cvid',
	kGraphicsCodecType					= 'smc ',
	kAnimationCodecType 				= 'rle ',
	kVideoCodecType 					= 'rpza',
	kComponentVideoCodecType			= 'yuv2',
	kJPEGCodecType						= 'jpeg',
	kMotionJPEGACodecType 				= 'mjpa',
	kMotionJPEGBCodecType 				= 'mjpb',
	kSGICodecType 						= '.SGI',
	kPlanarRGBCodecType 				= '8BPS',
	kMacPaintCodecType					= 'PNTG',
	kGIFCodecType 						= 'gif ',
	kPhotoCDCodecType 					= 'kpcd',
	kQuickDrawGXCodecType 				= 'qdgx',
	kAVRJPEGCodecType 					= 'avr ',
	kOpenDMLJPEGCodecType 				= 'dmb1',
	kBMPCodecType 						= 'WRLE',
	kWindowsRawCodecType				= 'WRAW',
	kVectorCodecType					= 'path',
	kQuickDrawCodecType 				= 'qdrw',
	kWaterRippleCodecType 				= 'ripl',
	kFireCodecType						= 'fire',
	kCloudCodecType 					= 'clou',
	kH261CodecType						= 'h261',
	kH263CodecType						= 'h263',
	kDVCNTSCCodecType					= 'dvc ',	/* DV - NTSC and DVCPRO NTSC (available in QuickTime 6.0 or later)*/
													/* NOTE: kDVCProNTSCCodecType is deprecated.	*/
													/* Use kDVCNTSCCodecType instead -- as far as the codecs are concerned, */
													/* the two data formats are identical.*/
	kDVCPALCodecType					= 'dvcp',
	kDVCProPALCodecType 				= 'dvpp',	/* available in QuickTime 6.0 or later*/
	kDVCPro50NTSCCodecType				= 'dv5n',
	kDVCPro50PALCodecType 				= 'dv5p',
	kDVCPro100NTSCCodecType 			= 'dv1n',
	kDVCPro100PALCodecType				= 'dv1p',
	kDVCPROHD720pCodecType				= 'dvhp',
	kDVCPROHD1080i60CodecType			= 'dvh6',
	kDVCPROHD1080i50CodecType			= 'dvh5',
	kBaseCodecType						= 'base',
	kFLCCodecType 						= 'flic',
	kTargaCodecType 					= 'tga ',
	kPNGCodecType 						= 'png ',
	kTIFFCodecType						= 'tiff',	/* NOTE: despite what might seem obvious from the two constants*/
													/* below and their names, they really are correct. 'yuvu' really */
													/* does mean signed, and 'yuvs' really does mean unsigned. Really. */
	kComponentVideoSigned 				= 'yuvu',
	kComponentVideoUnsigned 			= 'yuvs',
	kCMYKCodecType						= 'cmyk',
	kMicrosoftVideo1CodecType			= 'msvc',
	kSorensonCodecType					= 'SVQ1',
	kSorenson3CodecType 				= 'SVQ3',	/* available in QuickTime 5 and later*/
	kIndeo4CodecType					= 'IV41',
	kMPEG4VisualCodecType 				= 'mp4v',
	k64ARGBCodecType					= 'b64a',
	k48RGBCodecType 					= 'b48r',
	k32AlphaGrayCodecType 				= 'b32a',
	k16GrayCodecType					= 'b16g',
	kMpegYUV420CodecType				= 'myuv',
	kYUV420CodecType					= 'y420',
	kSorensonYUV9CodecType				= 'syv9',
	k422YpCbCr8CodecType				= '2vuy',	/* Component Y'CbCr 8-bit 4:2:2	*/
	k444YpCbCr8CodecType				= 'v308',	/* Component Y'CbCr 8-bit 4:4:4	*/
	k4444YpCbCrA8CodecType				= 'v408',	/* Component Y'CbCrA 8-bit 4:4:4:4 */
	k422YpCbCr16CodecType 				= 'v216',	/* Component Y'CbCr 10,12,14,16-bit 4:2:2*/
	k422YpCbCr10CodecType 				= 'v210',	/* Component Y'CbCr 10-bit 4:2:2 */
	k444YpCbCr10CodecType 				= 'v410',	/* Component Y'CbCr 10-bit 4:4:4 */
	k4444YpCbCrA8RCodecType 			= 'r408',	/* Component Y'CbCrA 8-bit 4:4:4:4, rendering format. full range alpha, zero biased yuv*/
	kJPEG2000CodecType					= 'mjp2',
	kPixletCodecType					= 'pxlt',
	kH264CodecType						= 'avc1'
};

enum {
	graphicsModeStraightAlpha			= 256,
	graphicsModePreWhiteAlpha			= 257,
	graphicsModePreBlackAlpha			= 258,
	graphicsModeComposition				= 259,
	graphicsModeStraightAlphaBlend		= 260,
	graphicsModePreMulColorAlpha		= 261,
	graphicsModePerComponentAlpha		= 272
};

#endif	/* __LP64__ */


#endif	/* _QTKITDEFINES_H */
