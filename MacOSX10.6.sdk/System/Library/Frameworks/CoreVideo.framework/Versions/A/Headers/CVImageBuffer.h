/*
 *  CVImageBuffer.h
 *  CoreVideo
 *
 *  Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
 *
 */
 
 /*! @header CVImageBuffer.h
	@copyright 2004 Apple Computer, Inc. All rights reserved.
	@availability Mac OS X 10.4 or later
    @discussion CVImageBufferRef types are abstract and define various attachments and convenience
		calls for retreiving image related bits of data.
		   
*/

#if !defined(__COREVIDEO_CVIMAGEBUFFER_H__)
#define __COREVIDEO_CVIMAGEBUFFER_H__ 1

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE
#include <CoreGraphics/CoreGraphics.h>
#else
#include <ApplicationServices/ApplicationServices.h>
#endif
#include <CoreVideo/CVBuffer.h>

#if defined(__cplusplus)
extern "C" {
#endif

#pragma mark CVImageBufferRef attachment keys

CV_EXPORT const CFStringRef kCVImageBufferCGColorSpaceKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;				// CGColorSpaceRef

CV_EXPORT const CFStringRef kCVImageBufferCleanApertureKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;				// CFDictionary containing the following four keys
CV_EXPORT const CFStringRef	kCVImageBufferCleanApertureWidthKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;			// CFNumber
CV_EXPORT const CFStringRef	kCVImageBufferCleanApertureHeightKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;			// CFNumber
CV_EXPORT const CFStringRef	kCVImageBufferCleanApertureHorizontalOffsetKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;		// CFNumber
CV_EXPORT const CFStringRef	kCVImageBufferCleanApertureVerticalOffsetKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;		// CFNumber
CV_EXPORT const CFStringRef kCVImageBufferPreferredCleanApertureKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;			// CFDictionary containing same keys as kCVImageBufferCleanApertureKey

CV_EXPORT const CFStringRef kCVImageBufferFieldCountKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;				// CFNumber
CV_EXPORT const CFStringRef kCVImageBufferFieldDetailKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;				// CFString with one of the following four values
CV_EXPORT const CFStringRef	kCVImageBufferFieldDetailTemporalTopFirst AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;		// CFString
CV_EXPORT const CFStringRef	kCVImageBufferFieldDetailTemporalBottomFirst AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;		// CFString
CV_EXPORT const CFStringRef	kCVImageBufferFieldDetailSpatialFirstLineEarly AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;		// CFString
CV_EXPORT const CFStringRef	kCVImageBufferFieldDetailSpatialFirstLineLate AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;		// CFString

CV_EXPORT const CFStringRef kCVImageBufferPixelAspectRatioKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;				// CFDictionary with the following two keys
CV_EXPORT const CFStringRef	kCVImageBufferPixelAspectRatioHorizontalSpacingKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// CFNumber
CV_EXPORT const CFStringRef	kCVImageBufferPixelAspectRatioVerticalSpacingKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// CFNumber

CV_EXPORT const CFStringRef kCVImageBufferDisplayDimensionsKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;				// CFDictionary with the following two keys
CV_EXPORT const CFStringRef	kCVImageBufferDisplayWidthKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;				// CFNumber
CV_EXPORT const CFStringRef	kCVImageBufferDisplayHeightKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;				// CFNumber

CV_EXPORT const CFStringRef kCVImageBufferGammaLevelKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;				// CFNumber describing the gamma level, used in absence of (or ignorance of) kCVImageBufferTransferFunctionKey

CV_EXPORT const CFStringRef kCVImageBufferICCProfileKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;				// CFData representation of the ICC profile

CV_EXPORT const CFStringRef kCVImageBufferYCbCrMatrixKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;				// CFString describing the color matrix for YCbCr->RGB. This key can be one of the following values:
CV_EXPORT const CFStringRef	kCVImageBufferYCbCrMatrix_ITU_R_709_2 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;			// CFString
CV_EXPORT const CFStringRef	kCVImageBufferYCbCrMatrix_ITU_R_601_4 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;			// CFString
CV_EXPORT const CFStringRef	kCVImageBufferYCbCrMatrix_SMPTE_240M_1995 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;		// CFString

CV_EXPORT const CFStringRef kCVImageBufferColorPrimariesKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;				// CFString describing the color primaries. This key can be one of the following values
CV_EXPORT const CFStringRef	kCVImageBufferColorPrimaries_ITU_R_709_2 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CV_EXPORT const CFStringRef	kCVImageBufferColorPrimaries_EBU_3213 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CV_EXPORT const CFStringRef	kCVImageBufferColorPrimaries_SMPTE_C AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

CV_EXPORT const CFStringRef kCVImageBufferTransferFunctionKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;				// CFString describing the transfer function. This key can be one of the following values
CV_EXPORT const CFStringRef	kCVImageBufferTransferFunction_ITU_R_709_2 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CV_EXPORT const CFStringRef	kCVImageBufferTransferFunction_SMPTE_240M_1995 AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
CV_EXPORT const CFStringRef	kCVImageBufferTransferFunction_UseGamma AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
CV_EXPORT const CFStringRef	kCVImageBufferTransferFunction_EBU_3213 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER_BUT_DEPRECATED;			// Should not be used.
CV_EXPORT const CFStringRef	kCVImageBufferTransferFunction_SMPTE_C AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER_BUT_DEPRECATED;			// Should not be used.

/* Chroma siting information. For progressive images, only the TopField value is used. */
CV_EXPORT const CFStringRef kCVImageBufferChromaLocationTopFieldKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;			// CFString with one of the following CFString values
CV_EXPORT const CFStringRef kCVImageBufferChromaLocationBottomFieldKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;		// CFString with one of the following CFString values
CV_EXPORT const CFStringRef	kCVImageBufferChromaLocation_Left AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;			    // Chroma sample is horizontally co-sited with the left column of luma samples, but centered vertically.
CV_EXPORT const CFStringRef	kCVImageBufferChromaLocation_Center AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;			    // Chroma sample is fully centered
CV_EXPORT const CFStringRef	kCVImageBufferChromaLocation_TopLeft AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;			    // Chroma sample is co-sited with the top-left luma sample.
CV_EXPORT const CFStringRef	kCVImageBufferChromaLocation_Top AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;			    // Chroma sample is horizontally centered, but co-sited with the top row of luma samples.
CV_EXPORT const CFStringRef	kCVImageBufferChromaLocation_BottomLeft AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;		    // Chroma sample is co-sited with the bottom-left luma sample.
CV_EXPORT const CFStringRef	kCVImageBufferChromaLocation_Bottom AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;			    // Chroma sample is horizontally centered, but co-sited with the bottom row of luma samples.
CV_EXPORT const CFStringRef	kCVImageBufferChromaLocation_DV420 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;			    // Cr and Cb samples are alternately co-sited with the left luma samples of the same field.

// These describe the format of the original subsampled data before conversion to 422/2vuy.   In order to use
// these tags, the data must have been converted to 4:2:2 via simple pixel replication.
CV_EXPORT const CFStringRef kCVImageBufferChromaSubsamplingKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;		// CFString/CFNumber with one of the following values
CV_EXPORT const CFStringRef	kCVImageBufferChromaSubsampling_420 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CV_EXPORT const CFStringRef	kCVImageBufferChromaSubsampling_422 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CV_EXPORT const CFStringRef	kCVImageBufferChromaSubsampling_411 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

#pragma mark CVImageBufferRef

/*!
    @typedef	CVImageBufferRef
    @abstract   Base type for all CoreVideo image buffers

*/
typedef CVBufferRef CVImageBufferRef;

/*!
    @function   CVImageBufferGetEncodedSize
    @abstract   Returns the full encoded dimensions of a CVImageBuffer.  For example, for an NTSC DV frame this would be 720x480
    @discussion Note: When creating a CIImage from a CVImageBuffer, this is the call you should use for retrieving the image size.
    @param      imageBuffer A CVImageBuffer that you wish to retrieve the encoded size from.
    @result     A CGSize returning the full encoded size of the buffer
		Returns zero size if called with a non-CVImageBufferRef type or NULL.
*/
CV_EXPORT CGSize CVImageBufferGetEncodedSize(CVImageBufferRef imageBuffer) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVImageBufferGetDisplaySize
    @abstract   Returns the nominal output display size (in square pixels) of a CVImageBuffer.  
                For example, for an NTSC DV frame this would be 640x480
    @param      imageBuffer A CVImageBuffer that you wish to retrieve the display size from.
    @result     A CGSize returning the nominal display size of the buffer
		Returns zero size if called with a non-CVImageBufferRef type or NULL.
*/
CV_EXPORT CGSize CVImageBufferGetDisplaySize(CVImageBufferRef imageBuffer) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVImageBufferGetCleanRect
    @abstract   Returns the source rectangle of a CVImageBuffer that represents the clean aperture
		of the buffer in encoded pixels.    For example, an NTSC DV frame would return a CGRect with an
		origin of 8,0 and a size of 704,480.		
		Note that the origin of this rect always the lower left	corner.   This is the same coordinate system as
		used by CoreImage.
    @param      imageBuffer A CVImageBuffer that you wish to retrieve the display size from.
    @result     A CGSize returning the nominal display size of the buffer
		Returns zero rect if called with a non-CVImageBufferRef type or NULL.
*/
CV_EXPORT CGRect CVImageBufferGetCleanRect(CVImageBufferRef imageBuffer) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVImageBufferGetColorSpace
    @abstract   Returns the color space of a CVImageBuffer.
    @param      imageBuffer A CVImageBuffer that you wish to retrieve the color space from.
    @result     A CGColorSpaceRef representing the color space of the buffer.
		Returns NULL if called with a non-CVImageBufferRef type or NULL.
*/
CV_EXPORT CGColorSpaceRef CVImageBufferGetColorSpace(CVImageBufferRef imageBuffer) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

#if defined(__cplusplus)
}
#endif

#endif
