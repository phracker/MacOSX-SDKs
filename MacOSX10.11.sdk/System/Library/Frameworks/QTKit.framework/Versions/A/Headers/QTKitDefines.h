/*
	File:		QTKitDefines.h

	Copyright:	(c)2004-2012 by Apple Inc., all rights reserved.

*/

/*
  QTKit has been deprecated in 10.9.

  AVFoundation and AVKit are the frameworks recommended for all new development 
  involving time-based audiovisual media on OS X.  In order to transition your 
  project from QTKit to AVFoundation please refer to:
  "Technical Note TN2300 Transitioning QTKit code to AV Foundation".
*/

#ifndef AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER
#define AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER       WEAK_IMPORT_ATTRIBUTE
#endif
#ifndef AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER
#define AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER       WEAK_IMPORT_ATTRIBUTE
#endif
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
#ifndef AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_6
#define AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_6       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER
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

#ifndef MAC_OS_X_VERSION_10_6
#define MAC_OS_X_VERSION_10_6		1060
#else
#undef MAC_OS_X_VERSION_10_6
#define MAC_OS_X_VERSION_10_6		1060
#endif

#ifndef MAC_OS_X_VERSION_10_7
#define MAC_OS_X_VERSION_10_7		1070
#else
#undef MAC_OS_X_VERSION_10_7
#define MAC_OS_X_VERSION_10_7		1070
#endif

/*
 QTKit Availability Macros
 
 These macros allow applications to target specific versions of QTKit independently
 of the OS on which the application is built. To target one or more versions of
 QTKit, you can use the QTKIT_VERSION_MIN_REQUIRED and the QTKIT_VERSION_MAX_ALLOWED
 macros in a way that is analagous to MAC_OS_X_VERSION_MIN_REQUIRED and
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
 
 */

#define QTKIT_VERSION_7_0           70000
#define QTKIT_VERSION_7_2           70200
#define QTKIT_VERSION_7_6_3         70603
#define QTKIT_VERSION_7_6_6         70606
#define QTKIT_VERSION_7_7           70700
#define QTKIT_VERSION_7_7_2         70702
#define QTKIT_VERSION_7_7_3         70703

#ifndef QTKIT_VERSION_MIN_REQUIRED
    #if MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_9
        #define QTKIT_VERSION_MIN_REQUIRED QTKIT_VERSION_7_7_2
    #elif MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_7
        #define QTKIT_VERSION_MIN_REQUIRED QTKIT_VERSION_7_7
    #elif MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_6
        #define QTKIT_VERSION_MIN_REQUIRED QTKIT_VERSION_7_6_3
    #elif MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_5
        #define QTKIT_VERSION_MIN_REQUIRED QTKIT_VERSION_7_2
    #else
        #define QTKIT_VERSION_MIN_REQUIRED QTKIT_VERSION_7_0
    #endif
#endif

#ifndef QTKIT_VERSION_MAX_ALLOWED
    #define QTKIT_VERSION_MAX_ALLOWED QTKIT_VERSION_7_7_3
#endif

// error on bad values
#if QTKIT_VERSION_MAX_ALLOWED < QTKIT_VERSION_MIN_REQUIRED
    #error QTKIT_VERSION_MAX_ALLOWED must be >= QTKIT_VERSION_MIN_REQUIRED
#endif
#if QTKIT_VERSION_MIN_REQUIRED < QTKIT_VERSION_7_0
    #error QTKIT_VERSION_MIN_REQUIRED must be >= QTKIT_VERSION_7_0
#endif

/*
 * AVAILABLE_QTKIT_VERSION_7_0_AND_LATER
 * 
 * Used on declarations introduced in QTKit 7.0 
 */
#if MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_4
	/* QTKit 7.0 or later is not installed on all versions of Mac OS prior to 10.4 */
	#define AVAILABLE_QTKIT_VERSION_7_0_AND_LATER WEAK_IMPORT_ATTRIBUTE
#else
	#define AVAILABLE_QTKIT_VERSION_7_0_AND_LATER
#endif

/*
 * AVAILABLE_QTKIT_VERSION_7_2_AND_LATER
 * 
 * Used on declarations introduced in QTKit 7.2
 */
#if QTKIT_VERSION_MAX_ALLOWED < QTKIT_VERSION_7_2
	#define AVAILABLE_QTKIT_VERSION_7_2_AND_LATER UNAVAILABLE_ATTRIBUTE
#elif (QTKIT_VERSION_MIN_REQUIRED < QTKIT_VERSION_7_2) || (MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_5)
	/* QTKit 7.2 or later is not installed on all versions of Mac OS prior to 10.5 */
	#define AVAILABLE_QTKIT_VERSION_7_2_AND_LATER WEAK_IMPORT_ATTRIBUTE
#else
	#define AVAILABLE_QTKIT_VERSION_7_2_AND_LATER
#endif

/*
 * AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_2
 * 
 * Used on declarations introduced in QTKit 7.0, 
 * but later deprecated in QTKit 7.2
 */
#if QTKIT_VERSION_MIN_REQUIRED >= QTKIT_VERSION_7_2
	#define AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_2 DEPRECATED_ATTRIBUTE
#else
	#define AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_2 AVAILABLE_QTKIT_VERSION_7_0_AND_LATER
#endif

/*
 * AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER
 * 
 * Used on declarations introduced in QTKit 7.5.7
 */
#if QTKIT_VERSION_MAX_ALLOWED < QTKIT_VERSION_7_6_3
	#define AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER UNAVAILABLE_ATTRIBUTE
#elif (QTKIT_VERSION_MIN_REQUIRED < QTKIT_VERSION_7_6_3) || (MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_6)
	/* QTKit 7.5.7 or later is not installed on all versions of Mac OS prior to 10.6 */
	#define AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER WEAK_IMPORT_ATTRIBUTE
#else
	#define AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER
#endif

/*
 * AVAILABLE_QTKIT_VERSION_7_6_6_AND_LATER
 * 
 * Used on declarations introduced in QTKit 7.6.6
 */
#if QTKIT_VERSION_MAX_ALLOWED < QTKIT_VERSION_7_6_6
	#define AVAILABLE_QTKIT_VERSION_7_6_6_AND_LATER UNAVAILABLE_ATTRIBUTE
#elif (QTKIT_VERSION_MIN_REQUIRED < QTKIT_VERSION_7_6_6) || (MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_6)
	#define AVAILABLE_QTKIT_VERSION_7_6_6_AND_LATER WEAK_IMPORT_ATTRIBUTE
#else
	#define AVAILABLE_QTKIT_VERSION_7_6_6_AND_LATER
#endif

/*
 * AVAILABLE_QTKIT_VERSION_7_7_AND_LATER
 * 
 * Used on declarations introduced in QTKit 7.7
 */
#if QTKIT_VERSION_MAX_ALLOWED < QTKIT_VERSION_7_7
	#define AVAILABLE_QTKIT_VERSION_7_7_AND_LATER UNAVAILABLE_ATTRIBUTE
#elif (QTKIT_VERSION_MIN_REQUIRED < QTKIT_VERSION_7_7) || (MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_7)
	#define AVAILABLE_QTKIT_VERSION_7_7_AND_LATER WEAK_IMPORT_ATTRIBUTE
#else
	#define AVAILABLE_QTKIT_VERSION_7_7_AND_LATER
#endif

/*
 * AVAILABLE_QTKIT_VERSION_7_7_2_AND_LATER
 * 
 * Used on declarations introduced in QTKit 7.7.2
 */
#if QTKIT_VERSION_MAX_ALLOWED < QTKIT_VERSION_7_7_2
	#define AVAILABLE_QTKIT_VERSION_7_7_2_AND_LATER UNAVAILABLE_ATTRIBUTE
#elif (QTKIT_VERSION_MIN_REQUIRED < QTKIT_VERSION_7_7_2) || (MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_9)
	#define AVAILABLE_QTKIT_VERSION_7_7_2_AND_LATER WEAK_IMPORT_ATTRIBUTE
#else
	#define AVAILABLE_QTKIT_VERSION_7_7_2_AND_LATER
#endif

/*
 * AVAILABLE_QTKIT_VERSION_7_7_3_AND_LATER
 * 
 * Used on declarations introduced in QTKit 7.7.3
 */
#if QTKIT_VERSION_MAX_ALLOWED < QTKIT_VERSION_7_7_3
	#define AVAILABLE_QTKIT_VERSION_7_7_3_AND_LATER UNAVAILABLE_ATTRIBUTE
#elif (QTKIT_VERSION_MIN_REQUIRED < QTKIT_VERSION_7_7_3) || (MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_9)
	#define AVAILABLE_QTKIT_VERSION_7_7_3_AND_LATER WEAK_IMPORT_ATTRIBUTE
#else
	#define AVAILABLE_QTKIT_VERSION_7_7_3_AND_LATER
#endif

/*
 * AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_6_3
 * 
 * Used on declarations introduced in QTKit 7.2, 
 * but later deprecated in QTKit 7.5.7
 */
#if QTKIT_VERSION_MIN_REQUIRED >= QTKIT_VERSION_7_6_3
	#define AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_6_3 DEPRECATED_ATTRIBUTE
#else
	#define AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_6_3 AVAILABLE_QTKIT_VERSION_7_0_AND_LATER
#endif

/*
 * AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_6_3
 * 
 * Used on declarations introduced in QTKit 7.2, 
 * but later deprecated in QTKit 7.5.7
 */
#if QTKIT_VERSION_MIN_REQUIRED >= QTKIT_VERSION_7_6_3
	#define AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_6_3 DEPRECATED_ATTRIBUTE
#else
	#define AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_6_3 AVAILABLE_QTKIT_VERSION_7_2_AND_LATER
#endif

/*
 * AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7
 * 
 * Used on declarations introduced in QTKit 7.2, 
 * but later deprecated in QTKit 7.7
 */
#if QTKIT_VERSION_MIN_REQUIRED >= QTKIT_VERSION_7_7_2
	#define AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7 DEPRECATED_ATTRIBUTE
#else
	#define AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7 AVAILABLE_QTKIT_VERSION_7_2_AND_LATER
#endif

/*
 * AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3
 * 
 * Used on declarations introduced in QTKit 7.0, 
 * but later deprecated in QTKit 7.7.2
 */
#if QTKIT_VERSION_MIN_REQUIRED >= QTKIT_VERSION_7_7_2
	#define AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3 DEPRECATED_ATTRIBUTE
#else
	#define AVAILABLE_QTKIT_VERSION_7_0_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3 AVAILABLE_QTKIT_VERSION_7_0_AND_LATER
#endif

/*
 * AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3
 * 
 * Used on declarations introduced in QTKit 7.2, 
 * but later deprecated in QTKit 7.7.2
 */
#if QTKIT_VERSION_MIN_REQUIRED >= QTKIT_VERSION_7_7_2
	#define AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3 DEPRECATED_ATTRIBUTE
#else
	#define AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3 AVAILABLE_QTKIT_VERSION_7_2_AND_LATER
#endif

/*
 * AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3
 * 
 * Used on declarations introduced in QTKit 7.6.3, 
 * but later deprecated in QTKit 7.7.2
 */
#if QTKIT_VERSION_MIN_REQUIRED >= QTKIT_VERSION_7_7_2
	#define AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3 DEPRECATED_ATTRIBUTE
#else
	#define AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3 AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER
#endif

/*
 * AVAILABLE_QTKIT_VERSION_7_6_6_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3
 * 
 * Used on declarations introduced in QTKit 7.6.6, 
 * but later deprecated in QTKit 7.7.2
 */
#if QTKIT_VERSION_MIN_REQUIRED >= QTKIT_VERSION_7_7_2
	#define AVAILABLE_QTKIT_VERSION_7_6_6_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3 DEPRECATED_ATTRIBUTE
#else
	#define AVAILABLE_QTKIT_VERSION_7_6_6_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3 AVAILABLE_QTKIT_VERSION_7_6_6_AND_LATER
#endif

/*
 * AVAILABLE_QTKIT_VERSION_7_7_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3
 * 
 * Used on declarations introduced in QTKit 7.7, 
 * but later deprecated in QTKit 7.7.2
 */
#if QTKIT_VERSION_MIN_REQUIRED >= QTKIT_VERSION_7_7_2
	#define AVAILABLE_QTKIT_VERSION_7_7_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3 DEPRECATED_ATTRIBUTE
#else
	#define AVAILABLE_QTKIT_VERSION_7_7_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3 AVAILABLE_QTKIT_VERSION_7_7_AND_LATER
#endif

#ifdef __cplusplus
#define QTKIT_EXTERN extern "C"
#else
#define QTKIT_EXTERN extern
#endif

#define QTKIT_HIDDEN __attribute__((visibility("hidden")))

#ifdef __OBJC__
#import <Foundation/NSObjCRuntime.h>
#endif  /* __OBJC__ */

#if __LP64__
// constants and data types defined in the 32-bit QuickTime headers that may be required for some QTKit APIs

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
	graphicsModeStraightAlpha			= 256,
	graphicsModePreWhiteAlpha			= 257,
	graphicsModePreBlackAlpha			= 258,
	graphicsModeComposition				= 259,
	graphicsModeStraightAlphaBlend		= 260,
	graphicsModePreMulColorAlpha		= 261,
	graphicsModePerComponentAlpha		= 272
};

#endif	/* __LP64__ */
