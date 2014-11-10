/*
	File:  CMFormatDescriptionBridge.h

	Framework:  CoreMedia

	Copyright 2006-2014 Apple Inc. All rights reserved.

*/

#ifndef CMFORMATDESCRIPTIONBRIDGE_H
#define CMFORMATDESCRIPTIONBRIDGE_H

/*!
	@header
	@abstract	API for converting between CoreMedia's CMFormatDescription objects and the legacy QuickTime framework's sample description data structures.
	@discussion	Most developers will not need to use these functions.
				They are provided for advanced developers who need to work directly with QuickTime Movie or ISO family files, or to interface with the legacy QuickTime framework.
				There are functions for converting between big-endian buffers and CoreMedia format descriptions because sample descriptions are big-endian in the current file formats.
				There are also functions for converting between big-endian buffers and the host-endian layouts exposed in QuickTime APIs.
*/

#include <CoreMedia/CMFormatDescription.h>
#include <CoreMedia/CMBlockBuffer.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 4)

/*!
	@enum CMFormatDescriptionBridge Errors
	@discussion OSStatus errors returned by CMFormatDescriptionBridge APIs.
	@constant	kCMFormatDescriptionBridgeError_InvalidParameter Invalid parameter.
	@constant	kCMFormatDescriptionBridgeError_AllocationFailed Returned when an allocation fails.
	@constant	kCMFormatDescriptionBridgeError_InvalidSerializedSampleDescription Returned when the sample description is invalid (e.g. invalid size).
	@constant	kCMFormatDescriptionBridgeError_InvalidFormatDescription Returned when the format description is invalid (e.g. invalid size).
	@constant	kCMFormatDescriptionBridgeError_IncompatibleFormatDescription Returned when the format description has an incompatible format (e.g. unknown format / incompatible atom).
	@constant	kCMFormatDescriptionBridgeError_UnsupportedSampleDescriptionFlavor Returned when the sample description is unsupported for the specified format flavor.
	@constant	kCMFormatDescriptionBridgeError_InvalidSlice Returned when the slice has an invalid value.
*/
enum {
	kCMFormatDescriptionBridgeError_InvalidParameter					= -12712,
	kCMFormatDescriptionBridgeError_AllocationFailed					= -12713,
	kCMFormatDescriptionBridgeError_InvalidSerializedSampleDescription	= -12714,
	kCMFormatDescriptionBridgeError_InvalidFormatDescription			= -12715,
	kCMFormatDescriptionBridgeError_IncompatibleFormatDescription		= -12716,
	kCMFormatDescriptionBridgeError_UnsupportedSampleDescriptionFlavor	= -12717,
	kCMFormatDescriptionBridgeError_InvalidSlice						= -12719,
};

/*! 
	@functiongroup	CMVideoFormatDescription and ImageDescription bridge functions
*/

/*!
	@constant	kCMImageDescriptionFlavor_QuickTimeMovie
	@abstract	Chooses the QuickTime Movie Image Description format.
	@discussion	Passing NULL is equivalent to passing this constant.

	@constant	kCMImageDescriptionFlavor_ISOFamily
	@abstract	Chooses the ISO family sample description format, used in MP4, M4V, etc.

	@constant	kCMImageDescriptionFlavor_3GPFamily
	@abstract	Chooses the 3GP family sample description format.
	@discussion	This implies kCMImageDescriptionFlavor_ISOFamily and adds additional rules specific to the 3GP family.
*/
CM_EXPORT const CFStringRef kCMImageDescriptionFlavor_QuickTimeMovie	__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);	// equivalent to NULL
CM_EXPORT const CFStringRef kCMImageDescriptionFlavor_ISOFamily			__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);	// MP4, etc
CM_EXPORT const CFStringRef kCMImageDescriptionFlavor_3GPFamily			__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);	// 3GPP (implies ISO)

/*!
	@function	CMVideoFormatDescriptionCreateFromBigEndianImageDescriptionData
	@abstract	Creates a CMVideoFormatDescription from a big-endian ImageDescription data structure.

	@param	allocator						Allocator to use for allocating the CMVideoFormatDescription object. May be NULL.
	@param	imageDescriptionData			ImageDescription data structure in big-endian byte ordering.
	@param	imageDescriptionSize			Size of ImageDescription data structure.
	@param	imageDescriptionStringEncoding	Pass CFStringGetSystemEncoding() or GetApplicationTextEncoding().
	@param	imageDescriptionFlavor			kCMImageDescriptionFlavor constant or NULL for QuickTimeMovie flavor.
	@param	videoFormatDescriptionOut		Receives new CMVideoFormatDescription.
*/
CM_EXPORT OSStatus CMVideoFormatDescriptionCreateFromBigEndianImageDescriptionData(
		CFAllocatorRef allocator,
		const uint8_t *imageDescriptionData,
		size_t imageDescriptionSize,
		CFStringEncoding imageDescriptionStringEncoding,
		CFStringRef imageDescriptionFlavor,
		CMVideoFormatDescriptionRef *videoFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMVideoFormatDescriptionCreateFromBigEndianImageDescriptionBlockBuffer
	@abstract	Creates a CMVideoFormatDescription from a big-endian ImageDescription data structure in a CMBlockBuffer.

	@param	allocator						Allocator to use for allocating the CMVideoFormatDescription object. May be NULL.
	@param	imageDescriptionBlockBuffer		CMBlockBuffer containing ImageDescription data structure in big-endian byte ordering.
	@param	imageDescriptionStringEncoding	Pass CFStringGetSystemEncoding() or GetApplicationTextEncoding().
	@param	imageDescriptionFlavor			kCMImageDescriptionFlavor constant or NULL for QuickTimeMovie flavor.
	@param	videoFormatDescriptionOut		Receives new CMVideoFormatDescription.
*/
CM_EXPORT OSStatus CMVideoFormatDescriptionCreateFromBigEndianImageDescriptionBlockBuffer(
		CFAllocatorRef allocator,
		CMBlockBufferRef imageDescriptionBlockBuffer,
		CFStringEncoding imageDescriptionStringEncoding,
		CFStringRef imageDescriptionFlavor,
		CMVideoFormatDescriptionRef *videoFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMVideoFormatDescriptionCopyAsBigEndianImageDescriptionBlockBuffer
	@abstract	Copies the contents of a CMVideoFormatDescription to a CMBlockBuffer in big-endian byte ordering.
	@discussion	On return, the caller owns the returned CMBlockBuffer, and must release it when done with it.
                Note that the dataRefIndex field of the SampleDescription is intentionally filled with
                garbage values (0xFFFF).  The caller must overwrite these values with a valid dataRefIndex
                if writing the SampleDescription to a QuickTime/ISO file.

	@param	allocator						Allocator to use for allocating the CMBlockBuffer object. May be NULL.
	@param	videoFormatDescription			CMVideoFormatDescription to be copied.
	@param	imageDescriptionStringEncoding	Pass CFStringGetSystemEncoding() or GetApplicationTextEncoding().
	@param	imageDescriptionFlavor			kCMImageDescriptionFlavor constant or NULL for QuickTimeMovie flavor.
	@param	imageDescriptionBlockBufferOut	Receives new CMBlockBuffer containing ImageDescription data structure in big-endian byte ordering.
*/
CM_EXPORT OSStatus CMVideoFormatDescriptionCopyAsBigEndianImageDescriptionBlockBuffer(
		CFAllocatorRef allocator,
		CMVideoFormatDescriptionRef videoFormatDescription,
		CFStringEncoding imageDescriptionStringEncoding,
		CFStringRef imageDescriptionFlavor,
		CMBlockBufferRef *imageDescriptionBlockBufferOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#if TARGET_RT_LITTLE_ENDIAN

/*!
	@function	CMSwapBigEndianImageDescriptionToHost
	@abstract	Converts an ImageDescription data structure from big-endian to host-endian in place.

	@param	imageDescriptionData			ImageDescription data structure in big-endian byte ordering to be converted to host-endian byte ordering.
	@param	imageDescriptionSize			Size of ImageDescription data structure.
*/
CM_EXPORT OSStatus CMSwapBigEndianImageDescriptionToHost(
		uint8_t *imageDescriptionData,
		size_t imageDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMSwapHostEndianImageDescriptionToBig
	@abstract	Converts an ImageDescription data structure from host-endian to big-endian in place.

	@param	imageDescriptionData			ImageDescription data structure in host-endian byte ordering to be converted to big-endian byte ordering.
	@param	imageDescriptionSize			Size of ImageDescription data structure.
*/
CM_EXPORT OSStatus CMSwapHostEndianImageDescriptionToBig(
		uint8_t *imageDescriptionData,
		size_t imageDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#else // TARGET_RT_BIG_ENDIAN

#define CMSwapBigEndianImageDescriptionToHost(d,s) (noErr)
#define CMSwapHostEndianImageDescriptionToBig(d,s) (noErr)

#endif // TARGET_RT_BIG_ENDIAN

/*! 
	@functiongroup	CMAudioFormatDescription and SoundDescription bridge functions
*/

/*!
	@constant	kCMSoundDescriptionFlavor_QuickTimeMovie
	@abstract	Chooses the most backwards-compatible QuickTime Movie Sound Description format.
	@discussion	A V1 sound description will be written if possible.
				If a V1 sound description is written for CBR or PCM audio, the sample tables will need to use the legacy CBR layout.

	@constant	kCMSoundDescriptionFlavor_QuickTimeMovieV2
	@abstract	Chooses the QuickTime Movie Sound Description V2 format.
	@discussion	A V2 sound description will be written.
				V2 Sound Descriptions contain no legacy CBR layout, and use 'lpcm' for all flavors of PCM.

	@constant	kCMSoundDescriptionFlavor_ISOFamily
	@abstract	Chooses the ISO family sample description format, used in MP4, M4A, etc.

	@constant	kCMSoundDescriptionFlavor_3GPFamily
	@abstract	Chooses the 3GP family sample description format.
	@discussion	This implies kCMSoundDescriptionFlavor_ISOFamily and adds additional rules specific to the 3GP family.
*/
CM_EXPORT const CFStringRef kCMSoundDescriptionFlavor_QuickTimeMovie	__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);	// equivalent to NULL
CM_EXPORT const CFStringRef kCMSoundDescriptionFlavor_QuickTimeMovieV2	__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMSoundDescriptionFlavor_ISOFamily			__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);	// MP4, etc
CM_EXPORT const CFStringRef kCMSoundDescriptionFlavor_3GPFamily			__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);	// 3GPP (implies ISO)

/*!
	@function	CMAudioFormatDescriptionCreateFromBigEndianSoundDescriptionData
	@abstract	Creates a CMAudioFormatDescription from a big-endian SoundDescription data structure.

	@param	allocator						Allocator to use for allocating the CMAudioFormatDescription object. May be NULL.
	@param	soundDescriptionData			SoundDescription data structure in big-endian byte ordering.
	@param	soundDescriptionSize			Size of SoundDescription data structure.
	@param	soundDescriptionFlavor			kCMSoundDescriptionFlavor constant or NULL for QuickTimeMovie flavor.
	@param	audioFormatDescriptionOut		Receives new CMAudioFormatDescription.
*/
CM_EXPORT OSStatus CMAudioFormatDescriptionCreateFromBigEndianSoundDescriptionData(
		CFAllocatorRef allocator,
		const uint8_t *soundDescriptionData,
		size_t soundDescriptionSize,
		CFStringRef soundDescriptionFlavor,
		CMAudioFormatDescriptionRef *audioFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMAudioFormatDescriptionCreateFromBigEndianSoundDescriptionBlockBuffer
	@abstract	Creates a CMAudioFormatDescription from a big-endian SoundDescription data structure in a CMBlockBuffer.

	@param	allocator						Allocator to use for allocating the CMAudioFormatDescription object. May be NULL.
	@param	soundDescriptionBlockBuffer		CMBlockBuffer containing SoundDescription data structure in big-endian byte ordering.
	@param	soundDescriptionFlavor			kCMSoundDescriptionFlavor constant or NULL for QuickTimeMovie flavor.
	@param	audioFormatDescriptionOut		Receives new CMAudioFormatDescription.
*/
CM_EXPORT OSStatus CMAudioFormatDescriptionCreateFromBigEndianSoundDescriptionBlockBuffer(
		CFAllocatorRef allocator,
		CMBlockBufferRef soundDescriptionBlockBuffer,
		CFStringRef soundDescriptionFlavor,
		CMAudioFormatDescriptionRef *audioFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMAudioFormatDescriptionCopyAsBigEndianSoundDescriptionBlockBuffer
	@abstract	Copies the contents of a CMAudioFormatDescription to a CMBlockBuffer in big-endian byte ordering.
	@discussion	On return, the caller owns the returned CMBlockBuffer, and must release it when done with it.
                Note that the dataRefIndex field of the SampleDescription is intentionally filled with
                garbage values (0xFFFF).  The caller must overwrite these values with a valid dataRefIndex
                if writing the SampleDescription to a QuickTime/ISO file.

	@param	allocator						Allocator to use for allocating the CMBlockBuffer object. May be NULL.
	@param	audioFormatDescription			CMAudioFormatDescription to be copied.
	@param	soundDescriptionFlavor			kCMSoundDescriptionFlavor constant or NULL for QuickTimeMovie flavor.
	@param	soundDescriptionBlockBufferOut	Receives new CMBlockBuffer containing SoundDescription data structure in big-endian byte ordering.
*/
CM_EXPORT OSStatus CMAudioFormatDescriptionCopyAsBigEndianSoundDescriptionBlockBuffer(
		CFAllocatorRef allocator,
		CMAudioFormatDescriptionRef audioFormatDescription,
		CFStringRef soundDescriptionFlavor,
		CMBlockBufferRef *soundDescriptionBlockBufferOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMDoesBigEndianSoundDescriptionRequireLegacyCBRSampleTableLayout
	@abstract	Examine a big-endian SoundDescription data structure in a CMBlockBuffer, and report whether the sample tables will need to use the legacy CBR layout.

	@param	soundDescriptionBlockBuffer		CMBlockBuffer containing SoundDescription data structure in big-endian byte ordering.
	@param	soundDescriptionFlavor			kCMSoundDescriptionFlavor constant or NULL for QuickTimeMovie flavor.
*/
CM_EXPORT Boolean CMDoesBigEndianSoundDescriptionRequireLegacyCBRSampleTableLayout(
		CMBlockBufferRef soundDescriptionBlockBuffer,
		CFStringRef soundDescriptionFlavor )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#if TARGET_RT_LITTLE_ENDIAN

/*!
	@function	CMSwapBigEndianSoundDescriptionToHost
	@abstract	Converts a SoundDescription data structure from big-endian to host-endian in place.

	@param	soundDescriptionData			SoundDescription data structure in big-endian byte ordering to be converted to host-endian byte ordering.
	@param	soundDescriptionSize			Size of SoundDescription data structure.
*/
CM_EXPORT OSStatus CMSwapBigEndianSoundDescriptionToHost(
		uint8_t *soundDescriptionData,
		size_t soundDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMSwapHostEndianSoundDescriptionToBig
	@abstract	Converts a SoundDescription data structure from host-endian to big-endian in place.

	@param	soundDescriptionData			SoundDescription data structure in host-endian byte ordering to be converted to big-endian byte ordering.
	@param	soundDescriptionSize			Size of SoundDescription data structure.
*/
CM_EXPORT OSStatus CMSwapHostEndianSoundDescriptionToBig(
		uint8_t *soundDescriptionData,
		size_t soundDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#else // TARGET_RT_BIG_ENDIAN

#define CMSwapBigEndianSoundDescriptionToHost(d,s) (noErr)
#define CMSwapHostEndianSoundDescriptionToBig(d,s) (noErr)

#endif // TARGET_RT_BIG_ENDIAN

/*! 
	@functiongroup	CMTextFormatDescription and TextDescription bridge functions
*/

/*!
	@function	CMTextFormatDescriptionCreateFromBigEndianTextDescriptionData
	@abstract	Creates a CMTextFormatDescription from a big-endian TextDescription data structure.

	@param	allocator						Allocator to use for allocating the CMTextFormatDescription object. May be NULL.
	@param	textDescriptionData				TextDescription data structure in big-endian byte ordering.
	@param	textDescriptionSize				Size of TextDescription data structure.
	@param	textDescriptionFlavor			Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	mediaType,						Pass kCMMediaType_Text or kCMMediaType_Subtitle.
	@param	textFormatDescriptionOut		Receives new CMTextFormatDescription.
*/
CM_EXPORT OSStatus CMTextFormatDescriptionCreateFromBigEndianTextDescriptionData(
		CFAllocatorRef allocator,
		const uint8_t *textDescriptionData,
		size_t textDescriptionSize,
		CFStringRef textDescriptionFlavor,
		CMMediaType mediaType,
		CMTextFormatDescriptionRef *textFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMTextFormatDescriptionCreateFromBigEndianTextDescriptionBlockBuffer
	@abstract	Creates a CMTextFormatDescription from a big-endian TextDescription data structure in a CMBlockBuffer.

	@param	allocator						Allocator to use for allocating the CMTextFormatDescription object. May be NULL.
	@param	textDescriptionBlockBuffer		CMBlockBuffer containing TextDescription data structure in big-endian byte ordering.
	@param	textDescriptionFlavor			Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	mediaType,						Pass kCMMediaType_Text or kCMMediaType_Subtitle.
	@param	textFormatDescriptionOut		Receives new CMTextFormatDescription.
*/
CM_EXPORT OSStatus CMTextFormatDescriptionCreateFromBigEndianTextDescriptionBlockBuffer(
		CFAllocatorRef allocator,
		CMBlockBufferRef textDescriptionBlockBuffer,
		CFStringRef textDescriptionFlavor,
		CMMediaType mediaType,
		CMTextFormatDescriptionRef *textFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMTextFormatDescriptionCopyAsBigEndianTextDescriptionBlockBuffer
	@abstract	Copies the contents of a CMTextFormatDescription to a CMBlockBuffer in big-endian byte ordering.
	@discussion	On return, the caller owns the returned CMBlockBuffer, and must release it when done with it.
                Note that the dataRefIndex field of the SampleDescription is intentionally filled with
                garbage values (0xFFFF).  The caller must overwrite these values with a valid dataRefIndex
                if writing the SampleDescription to a QuickTime/ISO file.

	@param	allocator						Allocator to use for allocating the CMBlockBuffer object. May be NULL.
	@param	textFormatDescription			CMTextFormatDescription to be copied.
	@param	textDescriptionFlavor			Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	textDescriptionBlockBufferOut	Receives new CMBlockBuffer containing TextDescription data structure in big-endian byte ordering.
*/
CM_EXPORT OSStatus CMTextFormatDescriptionCopyAsBigEndianTextDescriptionBlockBuffer(
		CFAllocatorRef allocator,
		CMTextFormatDescriptionRef textFormatDescription,
		CFStringRef textDescriptionFlavor,
		CMBlockBufferRef *textDescriptionBlockBufferOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#if TARGET_RT_LITTLE_ENDIAN

/*!
	@function	CMSwapBigEndianTextDescriptionToHost
	@abstract	Converts a TextDescription data structure from big-endian to host-endian in place.

	@param	textDescriptionData				TextDescription data structure in big-endian byte ordering to be converted to host-endian byte ordering.
	@param	textDescriptionSize				Size of TextDescription data structure.
*/
CM_EXPORT OSStatus CMSwapBigEndianTextDescriptionToHost(
		uint8_t *textDescriptionData,
		size_t textDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMSwapHostEndianTextDescriptionToBig
	@abstract	Converts a TextDescription data structure from host-endian to big-endian in place.

	@param	textDescriptionData				TextDescription data structure in host-endian byte ordering to be converted to big-endian byte ordering.
	@param	textDescriptionSize				Size of TextDescription data structure.
*/
CM_EXPORT OSStatus CMSwapHostEndianTextDescriptionToBig(
		uint8_t *textDescriptionData,
		size_t textDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#else // TARGET_RT_BIG_ENDIAN

#define CMSwapBigEndianTextDescriptionToHost(d,s) (noErr)
#define CMSwapHostEndianTextDescriptionToBig(d,s) (noErr)

#endif // TARGET_RT_BIG_ENDIAN

/*! 
	@functiongroup	CMClosedCaptionFormatDescription and ClosedCaptionDescription bridge functions
*/

/*!
	@function	CMClosedCaptionFormatDescriptionCreateFromBigEndianClosedCaptionDescriptionData
	@abstract	Creates a CMClosedCaptionFormatDescription from a big-endian ClosedCaptionDescription data structure.

	@param	allocator							Allocator to use for allocating the CMClosedCaptionFormatDescription object. May be NULL.
	@param	closedCaptionDescriptionData		ClosedCaptionDescription data structure in big-endian byte ordering.
	@param	closedCaptionDescriptionSize		Size of ClosedCaptionDescription data structure.
	@param	closedCaptionDescriptionFlavor		Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	closedCaptionFormatDescriptionOut	Receives new CMClosedCaptionFormatDescription.
*/
CM_EXPORT OSStatus CMClosedCaptionFormatDescriptionCreateFromBigEndianClosedCaptionDescriptionData(
		CFAllocatorRef allocator,
		const uint8_t *closedCaptionDescriptionData,
		size_t closedCaptionDescriptionSize,
		CFStringRef closedCaptionDescriptionFlavor,
		CMClosedCaptionFormatDescriptionRef *closedCaptionFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMClosedCaptionFormatDescriptionCreateFromBigEndianClosedCaptionDescriptionBlockBuffer
	@abstract	Creates a CMClosedCaptionFormatDescription from a big-endian ClosedCaptionDescription data structure in a CMBlockBuffer.

	@param	allocator							Allocator to use for allocating the CMClosedCaptionFormatDescription object. May be NULL.
	@param	closedCaptionDescriptionBlockBuffer	CMBlockBuffer containing ClosedCaptionDescription data structure in big-endian byte ordering.
	@param	closedCaptionDescriptionFlavor		Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	closedCaptionFormatDescriptionOut	Receives new CMClosedCaptionFormatDescription.
*/
CM_EXPORT OSStatus CMClosedCaptionFormatDescriptionCreateFromBigEndianClosedCaptionDescriptionBlockBuffer(
		CFAllocatorRef allocator,
		CMBlockBufferRef closedCaptionDescriptionBlockBuffer,
		CFStringRef closedCaptionDescriptionFlavor,
		CMClosedCaptionFormatDescriptionRef *closedCaptionFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMClosedCaptionFormatDescriptionCopyAsBigEndianClosedCaptionDescriptionBlockBuffer
	@abstract	Copies the contents of a CMClosedCaptionFormatDescription to a CMBlockBuffer in big-endian byte ordering.
	@discussion	On return, the caller owns the returned CMBlockBuffer, and must release it when done with it.
                Note that the dataRefIndex field of the SampleDescription is intentionally filled with
                garbage values (0xFFFF).  The caller must overwrite these values with a valid dataRefIndex
                if writing the SampleDescription to a QuickTime/ISO file.

	@param	allocator								Allocator to use for allocating the CMBlockBuffer object. May be NULL.
	@param	closedCaptionFormatDescription			CMClosedCaptionFormatDescription to be copied.
	@param	closedCaptionDescriptionFlavor			Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	closedCaptionDescriptionBlockBufferOut	Receives new CMBlockBuffer containing ClosedCaptionDescription data structure in big-endian byte ordering.
*/
CM_EXPORT OSStatus CMClosedCaptionFormatDescriptionCopyAsBigEndianClosedCaptionDescriptionBlockBuffer(
		CFAllocatorRef allocator,
		CMClosedCaptionFormatDescriptionRef closedCaptionFormatDescription,
		CFStringRef closedCaptionDescriptionFlavor,
		CMBlockBufferRef *closedCaptionDescriptionBlockBufferOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#if TARGET_RT_LITTLE_ENDIAN

/*!
	@function	CMSwapBigEndianClosedCaptionDescriptionToHost
	@abstract	Converts a ClosedCaptionDescription data structure from big-endian to host-endian in place.

	@param	closedCaptionDescriptionData	ClosedCaptionDescription data structure in big-endian byte ordering to be converted to host-endian byte ordering.
	@param	closedCaptionDescriptionSize	Size of ClosedCaptionDescription data structure.
*/
CM_EXPORT OSStatus CMSwapBigEndianClosedCaptionDescriptionToHost(
		uint8_t *closedCaptionDescriptionData,
		size_t closedCaptionDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMSwapHostEndianClosedCaptionDescriptionToBig
	@abstract	Converts a ClosedCaptionDescription data structure from host-endian to big-endian in place.

	@param	closedCaptionDescriptionData	ClosedCaptionDescription data structure in host-endian byte ordering to be converted to big-endian byte ordering.
	@param	closedCaptionDescriptionSize	Size of ClosedCaptionDescription data structure.
*/
CM_EXPORT OSStatus CMSwapHostEndianClosedCaptionDescriptionToBig(
		uint8_t *closedCaptionDescriptionData,
		size_t closedCaptionDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#else // TARGET_RT_BIG_ENDIAN

#define CMSwapBigEndianClosedCaptionDescriptionToHost(d,s) (noErr)
#define CMSwapHostEndianClosedCaptionDescriptionToBig(d,s) (noErr)

#endif // TARGET_RT_BIG_ENDIAN

/*! 
	@functiongroup	CMTimeCodeFormatDescription and TimeCodeDescription bridge functions
*/

/*!
	@function	CMTimeCodeFormatDescriptionCreateFromBigEndianTimeCodeDescriptionData
	@abstract	Creates a CMTimeCodeFormatDescription from a big-endian TimeCodeDescription data structure.

	@param	allocator						Allocator to use for allocating the CMTimeCodeFormatDescription object. May be NULL.
	@param	timeCodeDescriptionData			TimeCodeDescription data structure in big-endian byte ordering.
	@param	timeCodeDescriptionSize			Size of TimeCodeDescription data structure.
	@param	timeCodeDescriptionFlavor		Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	timeCodeFormatDescriptionOut	Receives new CMTimeCodeFormatDescription.
*/
CM_EXPORT OSStatus CMTimeCodeFormatDescriptionCreateFromBigEndianTimeCodeDescriptionData(
		CFAllocatorRef allocator,
		const uint8_t *timeCodeDescriptionData,
		size_t timeCodeDescriptionSize, 
		CFStringRef timeCodeDescriptionFlavor,
		CMTimeCodeFormatDescriptionRef *timeCodeFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMTimeCodeFormatDescriptionCreateFromBigEndianTimeCodeDescriptionBlockBuffer
	@abstract	Creates a CMTimeCodeFormatDescription from a big-endian TimeCodeDescription data structure in a CMBlockBuffer.

	@param	allocator						Allocator to use for allocating the CMTimeCodeFormatDescription object. May be NULL.
	@param	timeCodeDescriptionBlockBuffer	CMBlockBuffer containing TimeCodeDescription data structure in big-endian byte ordering.
	@param	timeCodeDescriptionFlavor		Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	timeCodeFormatDescriptionOut	Receives new CMTimeCodeFormatDescription.
*/
CM_EXPORT OSStatus CMTimeCodeFormatDescriptionCreateFromBigEndianTimeCodeDescriptionBlockBuffer(
		CFAllocatorRef allocator,
		CMBlockBufferRef timeCodeDescriptionBlockBuffer,
		CFStringRef timeCodeDescriptionFlavor,
		CMTimeCodeFormatDescriptionRef *timeCodeFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMTimeCodeFormatDescriptionCopyAsBigEndianTimeCodeDescriptionBlockBuffer
	@abstract	Copies the contents of a CMTimeCodeFormatDescription to a CMBlockBuffer in big-endian byte ordering.
	@discussion	On return, the caller owns the returned CMBlockBuffer, and must release it when done with it.
                Note that the dataRefIndex field of the SampleDescription is intentionally filled with
                garbage values (0xFFFF).  The caller must overwrite these values with a valid dataRefIndex
                if writing the SampleDescription to a QuickTime/ISO file.

	@param	allocator							Allocator to use for allocating the CMBlockBuffer object. May be NULL.
	@param	timeCodeFormatDescription			CMTimeCodeFormatDescription to be copied.
	@param	timeCodeDescriptionFlavor			Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	timeCodeDescriptionBlockBufferOut	Receives new CMBlockBuffer containing TimeCodeDescription data structure in big-endian byte ordering.
*/
CM_EXPORT OSStatus CMTimeCodeFormatDescriptionCopyAsBigEndianTimeCodeDescriptionBlockBuffer(
		CFAllocatorRef allocator,
		CMTimeCodeFormatDescriptionRef timeCodeFormatDescription,
		CFStringRef timeCodeDescriptionFlavor,
		CMBlockBufferRef *timeCodeDescriptionBlockBufferOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#if TARGET_RT_LITTLE_ENDIAN

/*!
	@function	CMSwapBigEndianTimeCodeDescriptionToHost
	@abstract	Converts a TimeCodeDescription data structure from big-endian to host-endian in place.

	@param	timeCodeDescriptionData			TimeCodeDescription data structure in big-endian byte ordering to be converted to host-endian byte ordering.
	@param	timeCodeDescriptionSize			Size of TimeCodeDescription data structure.
*/
CM_EXPORT OSStatus CMSwapBigEndianTimeCodeDescriptionToHost(
		uint8_t *timeCodeDescriptionData,
		size_t timeCodeDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMSwapHostEndianTimeCodeDescriptionToBig
	@abstract	Converts a TimeCodeDescription data structure from host-endian to big-endian in place.

	@param	timeCodeDescriptionData			TimeCodeDescription data structure in host-endian byte ordering to be converted to big-endian byte ordering.
	@param	timeCodeDescriptionSize			Size of TimeCodeDescription data structure.
*/
CM_EXPORT OSStatus CMSwapHostEndianTimeCodeDescriptionToBig(
		uint8_t *timeCodeDescriptionData,
		size_t timeCodeDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#else // TARGET_RT_BIG_ENDIAN

#define CMSwapBigEndianTimeCodeDescriptionToHost(d,s) (noErr)
#define CMSwapHostEndianTimeCodeDescriptionToBig(d,s) (noErr)

#endif // TARGET_RT_BIG_ENDIAN

/*! 
	@functiongroup	CMMetadataFormatDescription and MetadataDescription bridge functions
*/

/*!
	@function	CMMetadataFormatDescriptionCreateFromBigEndianMetadataDescriptionData
	@abstract	Creates a CMMetadataFormatDescription from a big-endian MetadataDescription data structure.

	@param	allocator						Allocator to use for allocating the CMMetadataFormatDescription object. May be NULL.
	@param	metadataDescriptionData			MetadataDescription data structure in big-endian byte ordering.
	@param	metadataDescriptionSize			Size of MetadataDescription data structure.
	@param	metadataDescriptionFlavor		Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	metadataFormatDescriptionOut	Receives new CMMetadataFormatDescriptionRef.
*/
CM_EXPORT OSStatus CMMetadataFormatDescriptionCreateFromBigEndianMetadataDescriptionData(
		CFAllocatorRef allocator,
		const uint8_t *metadataDescriptionData,
		size_t metadataDescriptionSize,
		CFStringRef metadataDescriptionFlavor,
		CMMetadataFormatDescriptionRef *metadataFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMMetadataFormatDescriptionCreateFromBigEndianMetadataDescriptionBlockBuffer
	@abstract	Creates a CMMetadataFormatDescription from a big-endian MetadataDescription data structure in a CMBlockBuffer.

	@param	allocator						Allocator to use for allocating the CMMetadataFormatDescription object. May be NULL.
	@param	metadataDescriptionBlockBuffer	CMBlockBuffer containing MetadataDescription data structure in big-endian byte ordering.
	@param	metadataDescriptionFlavor		Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	metadataFormatDescriptionOut	Receives new CMMetadataFormatDescriptionRef.
*/
CM_EXPORT OSStatus CMMetadataFormatDescriptionCreateFromBigEndianMetadataDescriptionBlockBuffer(
		CFAllocatorRef allocator,
		CMBlockBufferRef metadataDescriptionBlockBuffer,
		CFStringRef metadataDescriptionFlavor,
		CMMetadataFormatDescriptionRef *metadataFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMMetadataFormatDescriptionCopyAsBigEndianMetadataDescriptionBlockBuffer
	@abstract	Copies the contents of a CMMetadataFormatDescription to a CMBlockBuffer in big-endian byte ordering.
	@discussion	On return, the caller owns the returned CMBlockBuffer, and must release it when done with it.
                Note that the dataRefIndex field of the SampleDescription is intentionally filled with
                garbage values (0xFFFF).  The caller must overwrite these values with a valid dataRefIndex
                if writing the SampleDescription to a QuickTime/ISO file.

	@param	allocator							Allocator to use for allocating the CMBlockBuffer object. May be NULL.
	@param	metadataFormatDescription			CMMetadataFormatDescriptionRef to be copied.
	@param	metadataDescriptionFlavor			Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	metadataDescriptionBlockBufferOut	Receives new CMBlockBuffer containing MetadataDescription data structure in big-endian byte ordering.
*/
CM_EXPORT OSStatus CMMetadataFormatDescriptionCopyAsBigEndianMetadataDescriptionBlockBuffer(
		CFAllocatorRef allocator,
		CMMetadataFormatDescriptionRef metadataFormatDescription,
		CFStringRef metadataDescriptionFlavor,
		CMBlockBufferRef *metadataDescriptionBlockBufferOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#if TARGET_RT_LITTLE_ENDIAN

/*!
	@function	CMSwapBigEndianMetadataDescriptionToHost
	@abstract	Converts a MetadataDescription data structure from big-endian to host-endian in place.

	@param	metadataDescriptionData			MetadataDescription data structure in big-endian byte ordering to be converted to host-endian byte ordering.
	@param	metadataDescriptionSize			Size of MetadataDescription data structure.
*/
CM_EXPORT OSStatus CMSwapBigEndianMetadataDescriptionToHost(
		uint8_t *metadataDescriptionData,
		size_t metadataDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMSwapHostEndianMetadataDescriptionToBig
	@abstract	Converts a MetadataDescription data structure from host-endian to big-endian in place.

	@param	metadataDescriptionData			MetadataDescription data structure in host-endian byte ordering to be converted to big-endian byte ordering.
	@param	metadataDescriptionSize			Size of MetadataDescription data structure.
*/
CM_EXPORT OSStatus CMSwapHostEndianMetadataDescriptionToBig(
		uint8_t *metadataDescriptionData,
		size_t metadataDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#else // TARGET_RT_BIG_ENDIAN

#define CMSwapBigEndianMetadataDescriptionToHost(d,s) (noErr)
#define CMSwapHostEndianMetadataDescriptionToBig(d,s) (noErr)

#endif // TARGET_RT_BIG_ENDIAN

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif // CMFORMATDESCRIPTIONBRIDGE_H
