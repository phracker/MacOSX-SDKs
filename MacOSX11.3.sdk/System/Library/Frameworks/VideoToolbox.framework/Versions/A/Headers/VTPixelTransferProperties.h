/*
	File:  VTPixelTransferProperties.h
	
	Framework:  VideoToolbox
 
    Copyright 2006-2013 Apple Inc. All rights reserved.
  
	Standard Video Toolbox pixel transfer properties.
*/

#ifndef VTPIXELTRANSFERPROPERTIES_H
#define VTPIXELTRANSFERPROPERTIES_H

#include <CoreMedia/CMBase.h>
#include <VideoToolbox/VTBase.h>

#include <CoreFoundation/CoreFoundation.h>

#ifndef VT_SUPPORT_COLORSYNC_PIXEL_TRANSFER
#if TARGET_OS_TV
	#if (__TV_OS_VERSION_MIN_REQUIRED >= 93000)
		#define VT_SUPPORT_COLORSYNC_PIXEL_TRANSFER COREMEDIA_TRUE
	#endif
#elif TARGET_OS_WATCH
	#define VT_SUPPORT_COLORSYNC_PIXEL_TRANSFER COREMEDIA_TRUE
#elif TARGET_OS_IPHONE
	#if (__IPHONE_OS_VERSION_MIN_REQUIRED >= 93000)
		#define VT_SUPPORT_COLORSYNC_PIXEL_TRANSFER COREMEDIA_TRUE
	#endif
#elif TARGET_OS_MAC
	#if (__MAC_OS_X_VERSION_MIN_REQUIRED >= 1080)
		#define VT_SUPPORT_COLORSYNC_PIXEL_TRANSFER COREMEDIA_TRUE
	#endif
#endif
#endif
#ifndef VT_SUPPORT_COLORSYNC_PIXEL_TRANSFER
	#define VT_SUPPORT_COLORSYNC_PIXEL_TRANSFER COREMEDIA_FALSE
#endif

#if defined(__cplusplus)
extern "C"
{
#endif

#pragma pack(push, 4)
	
CM_ASSUME_NONNULL_BEGIN
    
/*!
	@header
	@abstract
		Standard Video Toolbox pixel transfer properties
		
	@discussion
		This file defines standard properties used to describe and configure pixel transfer 
		operations managed by the video toolbox.  
		
		Clients can query supported properties by calling VTSessionCopySupportedPropertyDictionary.
*/

// Properties for various scaling and cropping configurations

/*!
	@constant	kVTPixelTransferPropertyKey_ScalingMode
	@abstract
		Indicates how images should be scaled.
	@discussion
		Depending on the scaling mode, scaling may take into account:
		the full image buffer width and height of the source and destination, 
		the clean aperture attachment (kCVImageBufferCleanApertureKey) on the source image buffer, 
		the pixel aspect ratio attachment (kCVImageBufferPixelAspectRatioKey) on the source image buffer,
		the destination clean aperture (kVTPixelTransferPropertyKey_DestinationCleanAperture), and/or
		the destination pixel aspect ratio (kVTPixelTransferPropertyKey_DestinationPixelAspectRatio).
		The destination image buffer's clean aperture and pixel aspect ratio attachments are not
		taken into account, and will be overwritten.
 */
VT_EXPORT const CFStringRef kVTPixelTransferPropertyKey_ScalingMode API_AVAILABLE(macosx(10.8), ios(9.0), tvos(10.2)); // Read/write, CFStringRef, one of kVTScalingMode_*

/*
	@constant	kVTScalingMode_Normal
	@abstract
		The full width and height of the source image buffer is stretched to the full width
		and height of the destination image buffer.
	@discussion
		The source image buffer's clean aperture and pixel aspect ratio attachments are stretched
		the same way as the image with the image, and attached to the destination image buffer.
		This is the default scaling mode.
 */
VT_EXPORT const CFStringRef kVTScalingMode_Normal API_AVAILABLE(macosx(10.8), ios(9.0), tvos(10.2)); // Copy full width and height.  Write adjusted clean aperture and pixel aspect ratios to compensate for any change in dimensions.

/*
	@constant	kVTScalingMode_CropSourceToCleanAperture
	@abstract
		The source image buffer's clean aperture is scaled to the destination clean aperture.
	@discussion
		The destination pixel aspect ratio is set on the destination image buffer.
 */
VT_EXPORT const CFStringRef kVTScalingMode_CropSourceToCleanAperture API_AVAILABLE(macosx(10.8), ios(9.0), tvos(10.2)); // Crop to remove edge processing region; scale remainder to destination clean aperture.

/*
	@constant	kVTScalingMode_Letterbox
	@abstract
		The source image buffer's clean aperture is scaled to a rectangle fitted inside the
		destination clean aperture that preserves the source picture aspect ratio.
	@discussion
		The remainder of the destination image buffer is filled with black.
		If a destination pixel aspect ratio is not set, the source image's pixel aspect ratio is used.
		The pixel aspect ratio used is set on the destination image buffer.
 */
VT_EXPORT const CFStringRef kVTScalingMode_Letterbox API_AVAILABLE(macosx(10.8), ios(9.0), tvos(10.2)); // Preserve aspect ratio of the source, and fill remaining areas with black in to fit destination dimensions

/*
	@constant	kVTScalingMode_Trim
	@abstract
		The source image buffer's clean aperture is scaled to a rectangle that completely fills
		the destination clean aperture and preserves the source picture aspect ratio.
	@discussion
		If a destination pixel aspect ratio is not set, the source image's pixel aspect ratio is used.
		The pixel aspect ratio used is set on the destination image buffer.
 */
VT_EXPORT const CFStringRef kVTScalingMode_Trim API_AVAILABLE(macosx(10.8), ios(9.0), tvos(10.2)); // Preserve aspect ratio of the source, and crop picture to fit destination dimensions

/*!
	@constant	kVTPixelTransferPropertyKey_DestinationCleanAperture
	@abstract
		Specifies the clean aperture for destination image buffers.  
	@discussion
		The value of this property is a CFDictionary with same keys as used in the 
		kCVImageBufferCleanApertureKey dictionary.  
		This property is ignored in kVTScalingMode_Normal.  
		This property defaults to NULL, meaning the clean aperture is the full width and height.
*/
VT_EXPORT const CFStringRef kVTPixelTransferPropertyKey_DestinationCleanAperture API_AVAILABLE(macosx(10.8), ios(9.0), tvos(10.2)); // Read/write, CFDictionary with same keys as used in kCVImageBufferCleanApertureKey dictionary.  Used as applicable to current kVTPixelTransferPropertyKey_ScalingMode value.

/*!
	@constant	kVTPixelTransferPropertyKey_DestinationPixelAspectRatio
	@abstract
		Specifies the pixel aspect ratio for destination image buffers.  
	@discussion
		The value of this property is a CFDictionary with same keys as used in the
		kCVImageBufferPixelAspectRatioKey dictionary.
		This property is ignored in kVTScalingMode_Normal.  
		This property defaults to NULL, meaning 1:1 (for kVTScalingMode_CropSourceToCleanAperture) 
		or no change in pixel aspect ratio (for kVTScalingMode_Letterbox and kVTScalingMode_Trim).
*/
VT_EXPORT const CFStringRef kVTPixelTransferPropertyKey_DestinationPixelAspectRatio API_AVAILABLE(macosx(10.8), ios(9.0), tvos(10.2)); // Read/write, CFDictionary with same keys as used in kCVImageBufferPixelAspectRatioKey dictionary.  Used as applicable to current kVTPixelTransferPropertyKey_ScalingMode value.

// Properties for configuring up/down sampling

/*!
	@constant	kVTPixelTransferPropertyKey_DownsamplingMode
	@abstract
		Requests a specific chroma downsampling technique be used.
	@discussion
		This property is ignored if chroma downsampling is not performed.
*/
VT_EXPORT const CFStringRef kVTPixelTransferPropertyKey_DownsamplingMode API_AVAILABLE(macosx(10.8), ios(9.0), tvos(10.2)); // Read/write, CFStringRef, one of:
VT_EXPORT const CFStringRef kVTDownsamplingMode_Decimate API_AVAILABLE(macosx(10.8), ios(9.0), tvos(10.2)); // Default, decimate extra samples
VT_EXPORT const CFStringRef kVTDownsamplingMode_Average API_AVAILABLE(macosx(10.8), ios(9.0), tvos(10.2)); // Average missing samples (default center)

// Properties for color information

/*!
	@constant	kVTPixelTransferPropertyKey_DestinationColorPrimaries
	@abstract
		Specifies the color primaries to be used for destination image buffers.  
	@discussion
		Specifying this value may lead to performance degradation, as a color
		matching operation may need to be performed between the source and
		the destination.
*/
VT_EXPORT const CFStringRef kVTPixelTransferPropertyKey_DestinationColorPrimaries API_AVAILABLE(macosx(10.8), ios(9.0), tvos(10.2)); // Read/write, CFString (see kCMFormatDescriptionExtension_ColorPrimaries), Optional

/*!
	@constant	kVTPixelTransferPropertyKey_DestinationTransferFunction
	@abstract
		Specifies the color transfer function to be used for destination image buffers.  
	@discussion
		Specifying this value may lead to performance degradation, as a color
		matching operation may need to be performed between the source and
		the destination.
*/
VT_EXPORT const CFStringRef kVTPixelTransferPropertyKey_DestinationTransferFunction API_AVAILABLE(macosx(10.8), ios(9.0), tvos(10.2)); // Read/write, CFString (see kCMFormatDescriptionExtension_TransferFunction), Optional
	
/*!
	@constant	kVTPixelTransferPropertyKey_DestinationICCProfile
	@abstract
		Specifies the ICC profile for destination image buffers.  
	@discussion
		Specifying this value may lead to performance degradation, as a color
		matching operation may need to be performed between the source and
		the destination.
*/
VT_EXPORT const CFStringRef kVTPixelTransferPropertyKey_DestinationICCProfile API_AVAILABLE(macosx(10.8), ios(9.0), tvos(10.2)); // Read/write, CFData (see kCMFormatDescriptionExtension_ICCProfile), Optional
    
/*!
	@constant	kVTPixelTransferPropertyKey_DestinationYCbCrMatrix
	@abstract
		Specifies the color matrix to be used for YCbCr->RGB conversions
		involving the destination image buffers.
	@discussion
		Specifying this value may lead to performance degradation, as a color
		matching operation may need to be performed between the source and
		the destination.
*/
VT_EXPORT const CFStringRef kVTPixelTransferPropertyKey_DestinationYCbCrMatrix API_AVAILABLE(macosx(10.8), ios(9.0), tvos(10.2)); // Read/write, CFString (see kCMFormatDescriptionExtension_YCbCrMatrix), Optional

/*!
    @constant   kVTPixelTransferPropertyKey_RealTime
    @abstract
        Hints the transfer session that the operation is, or is not, being performed in real time.
    @discussion
        Set this property to kCFBooleanTrue to indicate that the transfer is part of realtime operation.  If set to
        true, the VTPixelTransferSession may be given precedence over non-realtime tasks.  This can be set to false
        for transfers being performed as part of background operations.
        By default this value is NULL indicating that it is unspecified.
*/
VT_EXPORT const CFStringRef kVTPixelTransferPropertyKey_RealTime; // Read/write, CFBoolean, default NULL

	
CM_ASSUME_NONNULL_END

#pragma pack(pop)

#if defined(__cplusplus)
}
#endif

#endif // VTPIXELTRANSFERPROPERTIES_H
