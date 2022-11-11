/*
	File:  CMFormatDescriptionBridge.h

	Framework:  CoreMedia

	Copyright © 2006-2018 Apple Inc. All rights reserved.

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
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : OSStatus
#else
enum
#endif
{
	kCMFormatDescriptionBridgeError_InvalidParameter					= -12712,
	kCMFormatDescriptionBridgeError_AllocationFailed					= -12713,
	kCMFormatDescriptionBridgeError_InvalidSerializedSampleDescription	= -12714,
	kCMFormatDescriptionBridgeError_InvalidFormatDescription			= -12715,
	kCMFormatDescriptionBridgeError_IncompatibleFormatDescription		= -12716,
	kCMFormatDescriptionBridgeError_UnsupportedSampleDescriptionFlavor	= -12717,
	kCMFormatDescriptionBridgeError_InvalidSlice						= -12719,
} API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
	
CM_ASSUME_NONNULL_BEGIN

typedef CFStringRef CMImageDescriptionFlavor CF_EXTENSIBLE_STRING_ENUM API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@constant	kCMImageDescriptionFlavor_QuickTimeMovie
	@abstract	Chooses the QuickTime Movie Image Description format.
	@discussion	Passing NULL is equivalent to passing this constant.
*/
CM_EXPORT const CMImageDescriptionFlavor kCMImageDescriptionFlavor_QuickTimeMovie		API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));	// equivalent to NULL
	
/*!
	@constant	kCMImageDescriptionFlavor_ISOFamily
	@abstract	Chooses the ISO family sample description format, used in MP4, M4V, etc.
*/
CM_EXPORT const CMImageDescriptionFlavor kCMImageDescriptionFlavor_ISOFamily			API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));	// MP4, etc
	
/*!
 	@constant	kCMImageDescriptionFlavor_3GPFamily
	@abstract	Chooses the 3GP family sample description format.
	@discussion	This implies kCMImageDescriptionFlavor_ISOFamily and adds additional rules specific to the 3GP family.
*/
CM_EXPORT const CMImageDescriptionFlavor kCMImageDescriptionFlavor_3GPFamily			API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));	// 3GPP (implies ISO)

CM_ASSUME_NONNULL_END
	
/*!
	@functiongroup	CMVideoFormatDescription and ImageDescription bridge functions
*/

/*!
	@function	CMVideoFormatDescriptionCreateFromBigEndianImageDescriptionData
	@abstract	Creates a CMVideoFormatDescription from a big-endian ImageDescription data structure.

	@param	allocator						Allocator to use for allocating the CMVideoFormatDescription object. May be NULL.
	@param	imageDescriptionData			ImageDescription data structure in big-endian byte ordering.
	@param	size							Size of ImageDescription data structure.
	@param	stringEncoding					Pass CFStringGetSystemEncoding() or GetApplicationTextEncoding().
	@param	flavor							kCMImageDescriptionFlavor constant or NULL for QuickTimeMovie flavor.
	@param	formatDescriptionOut			Receives new CMVideoFormatDescription.
*/
CM_EXPORT OSStatus CMVideoFormatDescriptionCreateFromBigEndianImageDescriptionData(
		CFAllocatorRef CM_NULLABLE allocator,
		const uint8_t * CM_NONNULL imageDescriptionData,
		size_t size,
		CFStringEncoding stringEncoding,
		CMImageDescriptionFlavor CM_NULLABLE flavor,
		CM_RETURNS_RETAINED_PARAMETER CMVideoFormatDescriptionRef CM_NULLABLE * CM_NONNULL formatDescriptionOut )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMVideoFormatDescriptionCreateFromBigEndianImageDescriptionBlockBuffer
	@abstract	Creates a CMVideoFormatDescription from a big-endian ImageDescription data structure in a CMBlockBuffer.

	@param	allocator						Allocator to use for allocating the CMVideoFormatDescription object. May be NULL.
	@param	imageDescriptionBlockBuffer		CMBlockBuffer containing ImageDescription data structure in big-endian byte ordering.
	@param	stringEncoding					Pass CFStringGetSystemEncoding() or GetApplicationTextEncoding().
	@param	flavor							kCMImageDescriptionFlavor constant or NULL for QuickTimeMovie flavor.
	@param	formatDescriptionOut			Receives new CMVideoFormatDescription.
*/
CM_EXPORT OSStatus CMVideoFormatDescriptionCreateFromBigEndianImageDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMBlockBufferRef CM_NONNULL imageDescriptionBlockBuffer,
		CFStringEncoding stringEncoding,
		CMImageDescriptionFlavor CM_NULLABLE flavor,
		CM_RETURNS_RETAINED_PARAMETER CMVideoFormatDescriptionRef CM_NULLABLE * CM_NONNULL formatDescriptionOut )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMVideoFormatDescriptionCopyAsBigEndianImageDescriptionBlockBuffer
	@abstract	Copies the contents of a CMVideoFormatDescription to a CMBlockBuffer in big-endian byte ordering.
	@discussion	On return, the caller owns the returned CMBlockBuffer, and must release it when done with it.
                Note that the dataRefIndex field of the SampleDescription is intentionally filled with
                garbage values (0xFFFF).  The caller must overwrite these values with a valid dataRefIndex
                if writing the SampleDescription to a QuickTime/ISO file.

	@param	allocator						Allocator to use for allocating the CMBlockBuffer object. May be NULL.
	@param	videoFormatDescription			CMVideoFormatDescription to be copied.
	@param	stringEncoding					Pass CFStringGetSystemEncoding() or GetApplicationTextEncoding().
	@param	flavor							kCMImageDescriptionFlavor constant or NULL for QuickTimeMovie flavor.
	@param	blockBufferOut					Receives new CMBlockBuffer containing ImageDescription data structure in big-endian byte ordering.
*/
CM_EXPORT OSStatus CMVideoFormatDescriptionCopyAsBigEndianImageDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMVideoFormatDescriptionRef CM_NONNULL videoFormatDescription,
		CFStringEncoding stringEncoding,
		CMImageDescriptionFlavor CM_NULLABLE flavor,
		CM_RETURNS_RETAINED_PARAMETER CMBlockBufferRef CM_NULLABLE * CM_NONNULL blockBufferOut )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

CF_IMPLICIT_BRIDGING_ENABLED

#if TARGET_RT_LITTLE_ENDIAN

/*!
	@function	CMSwapBigEndianImageDescriptionToHost
	@abstract	Converts an ImageDescription data structure from big-endian to host-endian in place.

	@param	imageDescriptionData			ImageDescription data structure in big-endian byte ordering to be converted to host-endian byte ordering.
	@param	imageDescriptionSize			Size of ImageDescription data structure.
*/
CM_EXPORT OSStatus CMSwapBigEndianImageDescriptionToHost(
		uint8_t * CM_NONNULL imageDescriptionData,
		size_t imageDescriptionSize )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMSwapHostEndianImageDescriptionToBig
	@abstract	Converts an ImageDescription data structure from host-endian to big-endian in place.

	@param	imageDescriptionData			ImageDescription data structure in host-endian byte ordering to be converted to big-endian byte ordering.
	@param	imageDescriptionSize			Size of ImageDescription data structure.
*/
CM_EXPORT OSStatus CMSwapHostEndianImageDescriptionToBig(
		uint8_t * CM_NONNULL imageDescriptionData,
		size_t imageDescriptionSize )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

#else // TARGET_RT_BIG_ENDIAN

#define CMSwapBigEndianImageDescriptionToHost(d,s) (noErr)
#define CMSwapHostEndianImageDescriptionToBig(d,s) (noErr)

#endif // TARGET_RT_BIG_ENDIAN

CF_IMPLICIT_BRIDGING_DISABLED

CM_ASSUME_NONNULL_BEGIN

typedef CFStringRef CMSoundDescriptionFlavor CF_EXTENSIBLE_STRING_ENUM API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@constant	kCMSoundDescriptionFlavor_QuickTimeMovie
	@abstract	Chooses the most backwards-compatible QuickTime Movie Sound Description format.
	@discussion	A V1 sound description will be written if possible.
				If a V1 sound description is written for CBR or PCM audio, the sample tables will need to use the legacy CBR layout.
*/
CM_EXPORT const CMSoundDescriptionFlavor kCMSoundDescriptionFlavor_QuickTimeMovie		API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));	// equivalent to NULL
	
/*!
 	@constant	kCMSoundDescriptionFlavor_QuickTimeMovieV2
	@abstract	Chooses the QuickTime Movie Sound Description V2 format.
	@discussion	A V2 sound description will be written.
				V2 Sound Descriptions contain no legacy CBR layout, and use 'lpcm' for all flavors of PCM.
*/
CM_EXPORT const CMSoundDescriptionFlavor kCMSoundDescriptionFlavor_QuickTimeMovieV2		API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
	
/*!
 	@constant	kCMSoundDescriptionFlavor_ISOFamily
	@abstract	Chooses the ISO family sample description format, used in MP4, M4A, etc.
*/
CM_EXPORT const CMSoundDescriptionFlavor kCMSoundDescriptionFlavor_ISOFamily			API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));	// MP4, etc
	
/*!
 	@constant	kCMSoundDescriptionFlavor_3GPFamily
	@abstract	Chooses the 3GP family sample description format.
	@discussion	This implies kCMSoundDescriptionFlavor_ISOFamily and adds additional rules specific to the 3GP family.
*/
CM_EXPORT const CMSoundDescriptionFlavor kCMSoundDescriptionFlavor_3GPFamily			API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));	// 3GPP (implies ISO)

CM_ASSUME_NONNULL_END

/*!
	@functiongroup	CMAudioFormatDescription and SoundDescription bridge functions
*/
	
/*!
	@function	CMAudioFormatDescriptionCreateFromBigEndianSoundDescriptionData
	@abstract	Creates a CMAudioFormatDescription from a big-endian SoundDescription data structure.

	@param	allocator						Allocator to use for allocating the CMAudioFormatDescription object. May be NULL.
	@param	soundDescriptionData			SoundDescription data structure in big-endian byte ordering.
	@param	size							Size of SoundDescription data structure.
	@param	flavor							kCMSoundDescriptionFlavor constant or NULL for QuickTimeMovie flavor.
	@param	formatDescriptionOut			Receives new CMAudioFormatDescription.
*/
CM_EXPORT OSStatus CMAudioFormatDescriptionCreateFromBigEndianSoundDescriptionData(
		CM_NULLABLE CFAllocatorRef allocator,
		const uint8_t * CM_NONNULL soundDescriptionData,
		size_t size,
		CMSoundDescriptionFlavor CM_NULLABLE flavor,
		CM_RETURNS_RETAINED_PARAMETER CMAudioFormatDescriptionRef CM_NULLABLE * CM_NONNULL  formatDescriptionOut )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMAudioFormatDescriptionCreateFromBigEndianSoundDescriptionBlockBuffer
	@abstract	Creates a CMAudioFormatDescription from a big-endian SoundDescription data structure in a CMBlockBuffer.

	@param	allocator						Allocator to use for allocating the CMAudioFormatDescription object. May be NULL.
	@param	soundDescriptionBlockBuffer		CMBlockBuffer containing SoundDescription data structure in big-endian byte ordering.
	@param	flavor			kCMSoundDescriptionFlavor constant or NULL for QuickTimeMovie flavor.
	@param	formatDescriptionOut		Receives new CMAudioFormatDescription.
*/
CM_EXPORT OSStatus CMAudioFormatDescriptionCreateFromBigEndianSoundDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMBlockBufferRef CM_NONNULL soundDescriptionBlockBuffer,
		CMSoundDescriptionFlavor CM_NULLABLE flavor,
		CM_RETURNS_RETAINED_PARAMETER CMAudioFormatDescriptionRef CM_NULLABLE * CM_NONNULL formatDescriptionOut )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMAudioFormatDescriptionCopyAsBigEndianSoundDescriptionBlockBuffer
	@abstract	Copies the contents of a CMAudioFormatDescription to a CMBlockBuffer in big-endian byte ordering.
	@discussion	On return, the caller owns the returned CMBlockBuffer, and must release it when done with it.
                Note that the dataRefIndex field of the SampleDescription is intentionally filled with
                garbage values (0xFFFF).  The caller must overwrite these values with a valid dataRefIndex
                if writing the SampleDescription to a QuickTime/ISO file.

	@param	allocator						Allocator to use for allocating the CMBlockBuffer object. May be NULL.
	@param	audioFormatDescription			CMAudioFormatDescription to be copied.
	@param	flavor							kCMSoundDescriptionFlavor constant or NULL for QuickTimeMovie flavor.
	@param	blockBufferOut					Receives new CMBlockBuffer containing SoundDescription data structure in big-endian byte ordering.
*/
CM_EXPORT OSStatus CMAudioFormatDescriptionCopyAsBigEndianSoundDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMAudioFormatDescriptionRef CM_NONNULL audioFormatDescription,
		CMSoundDescriptionFlavor CM_NULLABLE flavor,
		CM_RETURNS_RETAINED_PARAMETER CMBlockBufferRef CM_NULLABLE * CM_NONNULL blockBufferOut )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@function	CMDoesBigEndianSoundDescriptionRequireLegacyCBRSampleTableLayout
	@abstract	Examine a big-endian SoundDescription data structure in a CMBlockBuffer, and report whether the sample tables will need to use the legacy CBR layout.

	@param	soundDescriptionBlockBuffer		CMBlockBuffer containing SoundDescription data structure in big-endian byte ordering.
	@param	flavor							kCMSoundDescriptionFlavor constant or NULL for QuickTimeMovie flavor.
*/
CM_EXPORT Boolean CMDoesBigEndianSoundDescriptionRequireLegacyCBRSampleTableLayout(
		CMBlockBufferRef CM_NONNULL soundDescriptionBlockBuffer,
		CMSoundDescriptionFlavor CM_NULLABLE flavor )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

#if TARGET_RT_LITTLE_ENDIAN

/*!
	@function	CMSwapBigEndianSoundDescriptionToHost
	@abstract	Converts a SoundDescription data structure from big-endian to host-endian in place.

	@param	soundDescriptionData			SoundDescription data structure in big-endian byte ordering to be converted to host-endian byte ordering.
	@param	soundDescriptionSize			Size of SoundDescription data structure.
*/
CM_EXPORT OSStatus CMSwapBigEndianSoundDescriptionToHost(
		uint8_t * CM_NONNULL soundDescriptionData,
		size_t soundDescriptionSize )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMSwapHostEndianSoundDescriptionToBig
	@abstract	Converts a SoundDescription data structure from host-endian to big-endian in place.

	@param	soundDescriptionData			SoundDescription data structure in host-endian byte ordering to be converted to big-endian byte ordering.
	@param	soundDescriptionSize			Size of SoundDescription data structure.
*/
CM_EXPORT OSStatus CMSwapHostEndianSoundDescriptionToBig(
		uint8_t * CM_NONNULL soundDescriptionData,
		size_t soundDescriptionSize )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

#else // TARGET_RT_BIG_ENDIAN

#define CMSwapBigEndianSoundDescriptionToHost(d,s) (noErr)
#define CMSwapHostEndianSoundDescriptionToBig(d,s) (noErr)

#endif // TARGET_RT_BIG_ENDIAN

CF_IMPLICIT_BRIDGING_DISABLED

typedef CFStringRef CMTextDescriptionFlavor CF_EXTENSIBLE_STRING_ENUM API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
	
/*!
	@functiongroup	CMTextFormatDescription and TextDescription bridge functions
*/

/*!
	@function	CMTextFormatDescriptionCreateFromBigEndianTextDescriptionData
	@abstract	Creates a CMTextFormatDescription from a big-endian TextDescription data structure.

	@param	allocator						Allocator to use for allocating the CMTextFormatDescription object. May be NULL.
	@param	textDescriptionData				TextDescription data structure in big-endian byte ordering.
	@param	size							Size of TextDescription data structure.
	@param	flavor							Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	mediaType						Pass kCMMediaType_Text or kCMMediaType_Subtitle.
	@param	formatDescriptionOut			Receives new CMTextFormatDescription.
*/
CM_EXPORT OSStatus CMTextFormatDescriptionCreateFromBigEndianTextDescriptionData(
		CFAllocatorRef CM_NULLABLE allocator,
		const uint8_t * CM_NONNULL textDescriptionData,
		size_t size,
		CMTextDescriptionFlavor CM_NULLABLE flavor,
		CMMediaType mediaType,
		CM_RETURNS_RETAINED_PARAMETER CMTextFormatDescriptionRef CM_NULLABLE * CM_NONNULL formatDescriptionOut )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTextFormatDescriptionCreateFromBigEndianTextDescriptionBlockBuffer
	@abstract	Creates a CMTextFormatDescription from a big-endian TextDescription data structure in a CMBlockBuffer.

	@param	allocator						Allocator to use for allocating the CMTextFormatDescription object. May be NULL.
	@param	textDescriptionBlockBuffer		CMBlockBuffer containing TextDescription data structure in big-endian byte ordering.
	@param	flavor							Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	mediaType						Pass kCMMediaType_Text or kCMMediaType_Subtitle.
	@param	formatDescriptionOut			Receives new CMTextFormatDescription.
*/
CM_EXPORT OSStatus CMTextFormatDescriptionCreateFromBigEndianTextDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMBlockBufferRef CM_NONNULL textDescriptionBlockBuffer,
		CMTextDescriptionFlavor CM_NULLABLE flavor,
		CMMediaType mediaType,
		CM_RETURNS_RETAINED_PARAMETER CMTextFormatDescriptionRef CM_NULLABLE * CM_NONNULL formatDescriptionOut )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTextFormatDescriptionCopyAsBigEndianTextDescriptionBlockBuffer
	@abstract	Copies the contents of a CMTextFormatDescription to a CMBlockBuffer in big-endian byte ordering.
	@discussion	On return, the caller owns the returned CMBlockBuffer, and must release it when done with it.
                Note that the dataRefIndex field of the SampleDescription is intentionally filled with
                garbage values (0xFFFF).  The caller must overwrite these values with a valid dataRefIndex
                if writing the SampleDescription to a QuickTime/ISO file.

	@param	allocator						Allocator to use for allocating the CMBlockBuffer object. May be NULL.
	@param	textFormatDescription			CMTextFormatDescription to be copied.
	@param	flavor							Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	blockBufferOut					Receives new CMBlockBuffer containing TextDescription data structure in big-endian byte ordering.
*/
CM_EXPORT OSStatus CMTextFormatDescriptionCopyAsBigEndianTextDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMTextFormatDescriptionRef CM_NONNULL textFormatDescription,
		CMTextDescriptionFlavor CM_NULLABLE flavor,
		CM_RETURNS_RETAINED_PARAMETER CMBlockBufferRef CM_NULLABLE * CM_NONNULL blockBufferOut )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

CF_IMPLICIT_BRIDGING_ENABLED

#if TARGET_RT_LITTLE_ENDIAN

/*!
	@function	CMSwapBigEndianTextDescriptionToHost
	@abstract	Converts a TextDescription data structure from big-endian to host-endian in place.

	@param	textDescriptionData				TextDescription data structure in big-endian byte ordering to be converted to host-endian byte ordering.
	@param	textDescriptionSize				Size of TextDescription data structure.
*/
CM_EXPORT OSStatus CMSwapBigEndianTextDescriptionToHost(
		uint8_t * CM_NONNULL textDescriptionData,
		size_t textDescriptionSize )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMSwapHostEndianTextDescriptionToBig
	@abstract	Converts a TextDescription data structure from host-endian to big-endian in place.

	@param	textDescriptionData				TextDescription data structure in host-endian byte ordering to be converted to big-endian byte ordering.
	@param	textDescriptionSize				Size of TextDescription data structure.
*/
CM_EXPORT OSStatus CMSwapHostEndianTextDescriptionToBig(
		uint8_t * CM_NONNULL textDescriptionData,
		size_t textDescriptionSize )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

#else // TARGET_RT_BIG_ENDIAN

#define CMSwapBigEndianTextDescriptionToHost(d,s) (noErr)
#define CMSwapHostEndianTextDescriptionToBig(d,s) (noErr)

#endif // TARGET_RT_BIG_ENDIAN

CF_IMPLICIT_BRIDGING_DISABLED

typedef CFStringRef CMClosedCaptionDescriptionFlavor CF_EXTENSIBLE_STRING_ENUM API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@functiongroup	CMClosedCaptionFormatDescription and ClosedCaptionDescription bridge functions
*/
	
/*!
	@function	CMClosedCaptionFormatDescriptionCreateFromBigEndianClosedCaptionDescriptionData
	@abstract	Creates a CMClosedCaptionFormatDescription from a big-endian ClosedCaptionDescription data structure.

	@param	allocator							Allocator to use for allocating the CMClosedCaptionFormatDescription object. May be NULL.
	@param	closedCaptionDescriptionData		ClosedCaptionDescription data structure in big-endian byte ordering.
	@param	size								Size of ClosedCaptionDescription data structure.
	@param	flavor								Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	formatDescriptionOut				Receives new CMClosedCaptionFormatDescription.
*/
CM_EXPORT OSStatus CMClosedCaptionFormatDescriptionCreateFromBigEndianClosedCaptionDescriptionData(
		CFAllocatorRef CM_NULLABLE allocator,
		const uint8_t * CM_NONNULL closedCaptionDescriptionData,
		size_t size,
		CMClosedCaptionDescriptionFlavor CM_NULLABLE flavor,
		CM_RETURNS_RETAINED_PARAMETER CMClosedCaptionFormatDescriptionRef CM_NULLABLE * CM_NONNULL formatDescriptionOut )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMClosedCaptionFormatDescriptionCreateFromBigEndianClosedCaptionDescriptionBlockBuffer
	@abstract	Creates a CMClosedCaptionFormatDescription from a big-endian ClosedCaptionDescription data structure in a CMBlockBuffer.

	@param	allocator							Allocator to use for allocating the CMClosedCaptionFormatDescription object. May be NULL.
	@param	closedCaptionDescriptionBlockBuffer	CMBlockBuffer containing ClosedCaptionDescription data structure in big-endian byte ordering.
	@param	flavor								Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	formatDescriptionOut				Receives new CMClosedCaptionFormatDescription.
*/
CM_EXPORT OSStatus CMClosedCaptionFormatDescriptionCreateFromBigEndianClosedCaptionDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMBlockBufferRef CM_NONNULL closedCaptionDescriptionBlockBuffer,
		CMClosedCaptionDescriptionFlavor CM_NULLABLE flavor,
		CM_RETURNS_RETAINED_PARAMETER CMClosedCaptionFormatDescriptionRef CM_NULLABLE * CM_NONNULL formatDescriptionOut )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMClosedCaptionFormatDescriptionCopyAsBigEndianClosedCaptionDescriptionBlockBuffer
	@abstract	Copies the contents of a CMClosedCaptionFormatDescription to a CMBlockBuffer in big-endian byte ordering.
	@discussion	On return, the caller owns the returned CMBlockBuffer, and must release it when done with it.
                Note that the dataRefIndex field of the SampleDescription is intentionally filled with
                garbage values (0xFFFF).  The caller must overwrite these values with a valid dataRefIndex
                if writing the SampleDescription to a QuickTime/ISO file.

	@param	allocator							Allocator to use for allocating the CMBlockBuffer object. May be NULL.
	@param	closedCaptionFormatDescription		CMClosedCaptionFormatDescription to be copied.
	@param	flavor								Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	blockBufferOut						Receives new CMBlockBuffer containing ClosedCaptionDescription data structure in big-endian byte ordering.
*/
CM_EXPORT OSStatus CMClosedCaptionFormatDescriptionCopyAsBigEndianClosedCaptionDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMClosedCaptionFormatDescriptionRef CM_NONNULL closedCaptionFormatDescription,
		CMClosedCaptionDescriptionFlavor CM_NULLABLE flavor,
		CM_RETURNS_RETAINED_PARAMETER CMBlockBufferRef CM_NULLABLE * CM_NONNULL blockBufferOut )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

CF_IMPLICIT_BRIDGING_ENABLED

#if TARGET_RT_LITTLE_ENDIAN

/*!
	@function	CMSwapBigEndianClosedCaptionDescriptionToHost
	@abstract	Converts a ClosedCaptionDescription data structure from big-endian to host-endian in place.

	@param	closedCaptionDescriptionData	ClosedCaptionDescription data structure in big-endian byte ordering to be converted to host-endian byte ordering.
	@param	closedCaptionDescriptionSize	Size of ClosedCaptionDescription data structure.
*/
CM_EXPORT OSStatus CMSwapBigEndianClosedCaptionDescriptionToHost(
		uint8_t * CM_NONNULL closedCaptionDescriptionData,
		size_t closedCaptionDescriptionSize )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMSwapHostEndianClosedCaptionDescriptionToBig
	@abstract	Converts a ClosedCaptionDescription data structure from host-endian to big-endian in place.

	@param	closedCaptionDescriptionData	ClosedCaptionDescription data structure in host-endian byte ordering to be converted to big-endian byte ordering.
	@param	closedCaptionDescriptionSize	Size of ClosedCaptionDescription data structure.
*/
CM_EXPORT OSStatus CMSwapHostEndianClosedCaptionDescriptionToBig(
		uint8_t * CM_NONNULL closedCaptionDescriptionData,
		size_t closedCaptionDescriptionSize )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

#else // TARGET_RT_BIG_ENDIAN

#define CMSwapBigEndianClosedCaptionDescriptionToHost(d,s) (noErr)
#define CMSwapHostEndianClosedCaptionDescriptionToBig(d,s) (noErr)

#endif // TARGET_RT_BIG_ENDIAN

CF_IMPLICIT_BRIDGING_DISABLED

typedef CFStringRef CMTimeCodeDescriptionFlavor CF_EXTENSIBLE_STRING_ENUM API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@functiongroup	CMTimeCodeFormatDescription and TimeCodeDescription bridge functions
*/
	
/*!
	@function	CMTimeCodeFormatDescriptionCreateFromBigEndianTimeCodeDescriptionData
	@abstract	Creates a CMTimeCodeFormatDescription from a big-endian TimeCodeDescription data structure.

	@param	allocator						Allocator to use for allocating the CMTimeCodeFormatDescription object. May be NULL.
	@param	timeCodeDescriptionData			TimeCodeDescription data structure in big-endian byte ordering.
	@param	size							Size of TimeCodeDescription data structure.
	@param	flavor							Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	formatDescriptionOut			Receives new CMTimeCodeFormatDescription.
*/
CM_EXPORT OSStatus CMTimeCodeFormatDescriptionCreateFromBigEndianTimeCodeDescriptionData(
		CFAllocatorRef CM_NULLABLE allocator,
		const uint8_t * CM_NONNULL timeCodeDescriptionData,
		size_t size, 
		CMTimeCodeDescriptionFlavor CM_NULLABLE flavor,
		CM_RETURNS_RETAINED_PARAMETER CMTimeCodeFormatDescriptionRef CM_NULLABLE * CM_NONNULL formatDescriptionOut )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimeCodeFormatDescriptionCreateFromBigEndianTimeCodeDescriptionBlockBuffer
	@abstract	Creates a CMTimeCodeFormatDescription from a big-endian TimeCodeDescription data structure in a CMBlockBuffer.

	@param	allocator						Allocator to use for allocating the CMTimeCodeFormatDescription object. May be NULL.
	@param	timeCodeDescriptionBlockBuffer	CMBlockBuffer containing TimeCodeDescription data structure in big-endian byte ordering.
	@param	flavor							Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	formatDescriptionOut			Receives new CMTimeCodeFormatDescription.
*/
CM_EXPORT OSStatus CMTimeCodeFormatDescriptionCreateFromBigEndianTimeCodeDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMBlockBufferRef CM_NONNULL timeCodeDescriptionBlockBuffer,
		CMTimeCodeDescriptionFlavor CM_NULLABLE flavor,
		CM_RETURNS_RETAINED_PARAMETER CMTimeCodeFormatDescriptionRef CM_NULLABLE * CM_NONNULL formatDescriptionOut )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimeCodeFormatDescriptionCopyAsBigEndianTimeCodeDescriptionBlockBuffer
	@abstract	Copies the contents of a CMTimeCodeFormatDescription to a CMBlockBuffer in big-endian byte ordering.
	@discussion	On return, the caller owns the returned CMBlockBuffer, and must release it when done with it.
                Note that the dataRefIndex field of the SampleDescription is intentionally filled with
                garbage values (0xFFFF).  The caller must overwrite these values with a valid dataRefIndex
                if writing the SampleDescription to a QuickTime/ISO file.

	@param	allocator					Allocator to use for allocating the CMBlockBuffer object. May be NULL.
	@param	timeCodeFormatDescription	CMTimeCodeFormatDescription to be copied.
	@param	flavor						Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	blockBufferOut				Receives new CMBlockBuffer containing TimeCodeDescription data structure in big-endian byte ordering.
*/
CM_EXPORT OSStatus CMTimeCodeFormatDescriptionCopyAsBigEndianTimeCodeDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMTimeCodeFormatDescriptionRef CM_NONNULL timeCodeFormatDescription,
		CMTimeCodeDescriptionFlavor CM_NULLABLE flavor,
		CM_RETURNS_RETAINED_PARAMETER CMBlockBufferRef CM_NULLABLE * CM_NONNULL blockBufferOut )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

CF_IMPLICIT_BRIDGING_ENABLED

#if TARGET_RT_LITTLE_ENDIAN

/*!
	@function	CMSwapBigEndianTimeCodeDescriptionToHost
	@abstract	Converts a TimeCodeDescription data structure from big-endian to host-endian in place.

	@param	timeCodeDescriptionData			TimeCodeDescription data structure in big-endian byte ordering to be converted to host-endian byte ordering.
	@param	timeCodeDescriptionSize			Size of TimeCodeDescription data structure.
*/
CM_EXPORT OSStatus CMSwapBigEndianTimeCodeDescriptionToHost(
		uint8_t * CM_NONNULL timeCodeDescriptionData,
		size_t timeCodeDescriptionSize )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMSwapHostEndianTimeCodeDescriptionToBig
	@abstract	Converts a TimeCodeDescription data structure from host-endian to big-endian in place.

	@param	timeCodeDescriptionData			TimeCodeDescription data structure in host-endian byte ordering to be converted to big-endian byte ordering.
	@param	timeCodeDescriptionSize			Size of TimeCodeDescription data structure.
*/
CM_EXPORT OSStatus CMSwapHostEndianTimeCodeDescriptionToBig(
		uint8_t * CM_NONNULL timeCodeDescriptionData,
		size_t timeCodeDescriptionSize )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

#else // TARGET_RT_BIG_ENDIAN

#define CMSwapBigEndianTimeCodeDescriptionToHost(d,s) (noErr)
#define CMSwapHostEndianTimeCodeDescriptionToBig(d,s) (noErr)

#endif // TARGET_RT_BIG_ENDIAN

CF_IMPLICIT_BRIDGING_DISABLED

typedef CFStringRef CMMetadataDescriptionFlavor CF_EXTENSIBLE_STRING_ENUM API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@functiongroup	CMMetadataFormatDescription and MetadataDescription bridge functions
*/
	
/*!
	@function	CMMetadataFormatDescriptionCreateFromBigEndianMetadataDescriptionData
	@abstract	Creates a CMMetadataFormatDescription from a big-endian MetadataDescription data structure.

	@param	allocator					Allocator to use for allocating the CMMetadataFormatDescription object. May be NULL.
	@param	metadataDescriptionData		MetadataDescription data structure in big-endian byte ordering.
	@param	size						Size of MetadataDescription data structure.
	@param	flavor						Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	formatDescriptionOut		Receives new CMMetadataFormatDescriptionRef.
*/
CM_EXPORT OSStatus CMMetadataFormatDescriptionCreateFromBigEndianMetadataDescriptionData(
		CFAllocatorRef CM_NULLABLE allocator,
		const uint8_t * CM_NONNULL metadataDescriptionData,
		size_t size,
		CMMetadataDescriptionFlavor CM_NULLABLE flavor,
		CM_RETURNS_RETAINED_PARAMETER CMMetadataFormatDescriptionRef CM_NULLABLE * CM_NONNULL formatDescriptionOut )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMMetadataFormatDescriptionCreateFromBigEndianMetadataDescriptionBlockBuffer
	@abstract	Creates a CMMetadataFormatDescription from a big-endian MetadataDescription data structure in a CMBlockBuffer.

	@param	allocator						Allocator to use for allocating the CMMetadataFormatDescription object. May be NULL.
	@param	metadataDescriptionBlockBuffer	CMBlockBuffer containing MetadataDescription data structure in big-endian byte ordering.
	@param	flavor							Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	formatDescriptionOut			Receives new CMMetadataFormatDescriptionRef.
*/
CM_EXPORT OSStatus CMMetadataFormatDescriptionCreateFromBigEndianMetadataDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMBlockBufferRef CM_NONNULL metadataDescriptionBlockBuffer,
		CMMetadataDescriptionFlavor CM_NULLABLE flavor,
		CM_RETURNS_RETAINED_PARAMETER CMMetadataFormatDescriptionRef CM_NULLABLE * CM_NONNULL formatDescriptionOut )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMMetadataFormatDescriptionCopyAsBigEndianMetadataDescriptionBlockBuffer
	@abstract	Copies the contents of a CMMetadataFormatDescription to a CMBlockBuffer in big-endian byte ordering.
	@discussion	On return, the caller owns the returned CMBlockBuffer, and must release it when done with it.
                Note that the dataRefIndex field of the SampleDescription is intentionally filled with
                garbage values (0xFFFF).  The caller must overwrite these values with a valid dataRefIndex
                if writing the SampleDescription to a QuickTime/ISO file.

	@param	allocator					Allocator to use for allocating the CMBlockBuffer object. May be NULL.
	@param	metadataFormatDescription	CMMetadataFormatDescriptionRef to be copied.
	@param	flavor						Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	blockBufferOut				Receives new CMBlockBuffer containing MetadataDescription data structure in big-endian byte ordering.
*/
CM_EXPORT OSStatus CMMetadataFormatDescriptionCopyAsBigEndianMetadataDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMMetadataFormatDescriptionRef CM_NONNULL metadataFormatDescription,
		CMMetadataDescriptionFlavor CM_NULLABLE flavor,
		CM_RETURNS_RETAINED_PARAMETER CMBlockBufferRef CM_NULLABLE * CM_NONNULL blockBufferOut )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

CF_IMPLICIT_BRIDGING_ENABLED

#if TARGET_RT_LITTLE_ENDIAN

/*!
	@function	CMSwapBigEndianMetadataDescriptionToHost
	@abstract	Converts a MetadataDescription data structure from big-endian to host-endian in place.

	@param	metadataDescriptionData			MetadataDescription data structure in big-endian byte ordering to be converted to host-endian byte ordering.
	@param	metadataDescriptionSize			Size of MetadataDescription data structure.
*/
CM_EXPORT OSStatus CMSwapBigEndianMetadataDescriptionToHost(
		uint8_t * CM_NONNULL metadataDescriptionData,
		size_t metadataDescriptionSize )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMSwapHostEndianMetadataDescriptionToBig
	@abstract	Converts a MetadataDescription data structure from host-endian to big-endian in place.

	@param	metadataDescriptionData			MetadataDescription data structure in host-endian byte ordering to be converted to big-endian byte ordering.
	@param	metadataDescriptionSize			Size of MetadataDescription data structure.
*/
CM_EXPORT OSStatus CMSwapHostEndianMetadataDescriptionToBig(
		uint8_t * CM_NONNULL metadataDescriptionData,
		size_t metadataDescriptionSize )
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

#else // TARGET_RT_BIG_ENDIAN

#define CMSwapBigEndianMetadataDescriptionToHost(d,s) (noErr)
#define CMSwapHostEndianMetadataDescriptionToBig(d,s) (noErr)

#endif // TARGET_RT_BIG_ENDIAN

CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif // CMFORMATDESCRIPTIONBRIDGE_H
