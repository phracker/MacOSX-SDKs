/*
 *  CVImageBuffer.h
 *  CoreVideo
 *
 *  Copyright (c) 2004-2021 Apple Inc. All rights reserved.
 *
 */
 
 /*! @header CVImageBuffer.h
	@copyright 2004-2015 Apple Inc. All rights reserved.
	@availability Mac OS X 10.4 or later, and iOS 4.0 or later
    @discussion CVImageBufferRef types are abstract and define various attachments and convenience
		calls for retreiving image related bits of data.
		
*/

#if !defined(__COREVIDEO_CVIMAGEBUFFER_H__)
#define __COREVIDEO_CVIMAGEBUFFER_H__ 1

#include <TargetConditionals.h>
#include <Availability.h>
#include <AvailabilityMacros.h>

// For legacy reasons CVImageBuffer.h includes CoreGraphics.h and ApplicationServices.h
#if TARGET_OS_IPHONE || TARGET_OS_WIN32
#include <CoreGraphics/CoreGraphics.h>
#else
#if __has_include(<ApplicationServices/ApplicationServices.h>)
#include <ApplicationServices/ApplicationServices.h>
#endif
#endif
#if __has_include(<CoreGraphics/CGColorSpace.h>)
#include <CoreGraphics/CGColorSpace.h>
#include <CoreGraphics/CGGeometry.h>
#endif

#include <CoreVideo/CVBuffer.h>

#if defined(__cplusplus)
extern "C" {
#endif

#pragma mark CVImageBufferRef attachment keys

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferCGColorSpaceKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);				// CGColorSpaceRef

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferCleanApertureKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);				// CFDictionary containing the following four keys
CV_EXPORT const CFStringRef CV_NONNULL	kCVImageBufferCleanApertureWidthKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);			// CFNumber
CV_EXPORT const CFStringRef CV_NONNULL	kCVImageBufferCleanApertureHeightKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);			// CFNumber
CV_EXPORT const CFStringRef CV_NONNULL	kCVImageBufferCleanApertureHorizontalOffsetKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);		// CFNumber, horizontal offset from center of image buffer
CV_EXPORT const CFStringRef CV_NONNULL	kCVImageBufferCleanApertureVerticalOffsetKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);		// CFNumber, vertical offset from center of image buffer
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferPreferredCleanApertureKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);			// CFDictionary containing same keys as kCVImageBufferCleanApertureKey

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferFieldCountKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);				// CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferFieldDetailKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);				// CFString with one of the following four values
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferFieldDetailTemporalTopFirst __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);		// CFString
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferFieldDetailTemporalBottomFirst __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);		// CFString
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferFieldDetailSpatialFirstLineEarly __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);		// CFString
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferFieldDetailSpatialFirstLineLate __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);		// CFString

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferPixelAspectRatioKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);				// CFDictionary with the following two keys
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferPixelAspectRatioHorizontalSpacingKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);	// CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferPixelAspectRatioVerticalSpacingKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);	// CFNumber

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferDisplayDimensionsKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);				// CFDictionary with the following two keys
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferDisplayWidthKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);				// CFNumber
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferDisplayHeightKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);				// CFNumber

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferGammaLevelKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);				// CFNumber describing the gamma level, used in absence of (or ignorance of) kCVImageBufferTransferFunctionKey

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferICCProfileKey __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_4_0);				// CFData representation of the ICC profile

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferYCbCrMatrixKey __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);				// CFString describing the color matrix for YCbCr->RGB. This key can be one of the following values:
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferYCbCrMatrix_ITU_R_709_2 __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);			// CFString
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferYCbCrMatrix_ITU_R_601_4 __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);			// CFString
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferYCbCrMatrix_SMPTE_240M_1995 __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);		// CFString
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferYCbCrMatrix_DCI_P3 API_DEPRECATED("kCVImageBufferYCbCrMatrix_DCI_P3 no longer supported.", macos(10.11, 11.0), ios(9.0, 14.0));		// CFString
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferYCbCrMatrix_P3_D65 API_DEPRECATED("kCVImageBufferYCbCrMatrix_P3_D65 no longer supported.", macos(10.11, 11.0), ios(9.0, 14.0));		// CFString
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferYCbCrMatrix_ITU_R_2020 __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);		// CFString

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferColorPrimariesKey __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);				// CFString describing the color primaries. This key can be one of the following values
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferColorPrimaries_ITU_R_709_2 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferColorPrimaries_EBU_3213 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferColorPrimaries_SMPTE_C __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferColorPrimaries_P22 __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferColorPrimaries_DCI_P3 __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferColorPrimaries_P3_D65 __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferColorPrimaries_ITU_R_2020 __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferTransferFunctionKey __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);				// CFString describing the transfer function. This key can be one of the following values
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferTransferFunction_ITU_R_709_2 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferTransferFunction_SMPTE_240M_1995 __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferTransferFunction_UseGamma __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferTransferFunction_EBU_3213 __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_5,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);			// Should not be used.
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferTransferFunction_SMPTE_C __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_5,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);			// Should not be used.
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferTransferFunction_sRGB __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_11_0);			// IEC 61966-2-1 sRGB or sYCC
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferTransferFunction_ITU_R_2020 __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0); // note: kCVImageBufferTransferFunction_ITU_R_709_2 is equivalent, and preferred
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferTransferFunction_SMPTE_ST_428_1 __OSX_AVAILABLE_STARTING(__MAC_10_12,__IPHONE_10_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferTransferFunction_SMPTE_ST_2084_PQ __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_11_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferTransferFunction_ITU_R_2100_HLG __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_11_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferTransferFunction_Linear __OSX_AVAILABLE_STARTING(__MAC_10_14,__IPHONE_12_0);
	
/* Chroma siting information. For progressive images, only the TopField value is used. */
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaLocationTopFieldKey __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);			// CFString with one of the following CFString values
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaLocationBottomFieldKey __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);		// CFString with one of the following CFString values
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaLocation_Left __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);			    // Chroma sample is horizontally co-sited with the left column of luma samples, but centered vertically.
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaLocation_Center __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);			    // Chroma sample is fully centered
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaLocation_TopLeft __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);			    // Chroma sample is co-sited with the top-left luma sample.
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaLocation_Top __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);			    // Chroma sample is horizontally centered, but co-sited with the top row of luma samples.
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaLocation_BottomLeft __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);		    // Chroma sample is co-sited with the bottom-left luma sample.
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaLocation_Bottom __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);			    // Chroma sample is horizontally centered, but co-sited with the bottom row of luma samples.
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaLocation_DV420 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);			    // Cr and Cb samples are alternately co-sited with the left luma samples of the same field.

// These describe the format of the original subsampled data before conversion to 422/2vuy.   In order to use
// these tags, the data must have been converted to 4:2:2 via simple pixel replication.
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaSubsamplingKey __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);		// CFString/CFNumber with one of the following values
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaSubsampling_420 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaSubsampling_422 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferChromaSubsampling_411 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_4_0);

// Can be set to kCFBooleanTrue as a hint that the alpha channel is fully opaque.  Not used if the pixel format type has no alpha channel.
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferAlphaChannelIsOpaque __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferAlphaChannelModeKey API_AVAILABLE(macosx(10.15), ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferAlphaChannelMode_StraightAlpha API_AVAILABLE(macosx(10.15), ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferAlphaChannelMode_PremultipliedAlpha API_AVAILABLE(macosx(10.15), ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

// Used to attach processing metadata to buffers transferred between video decoders and RAW processors.
// Sequence metadata is expected to be invariant over the entire movie, while frame metadata can vary with each frame.
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferPostDecodeProcessingSequenceMetadataKey API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos, visionos);	// CFDictionary
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferPostDecodeProcessingFrameMetadataKey API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos, visionos);	// CFDictionary


// Returns the standard integer code point corresponding to a given CoreVideo YCbCrMatrix constant string (in the kCVImageBufferYCbCrMatrix_... family).  Returns 2 (the code point for "unknown") if the string is NULL or not recognized.
CV_EXPORT int CVYCbCrMatrixGetIntegerCodePointForString( CV_NULLABLE CFStringRef yCbCrMatrixString ) API_AVAILABLE(macosx(10.13), ios(11.0), tvos(11.0), watchos(4.0));
// Returns the standard integer code point corresponding to a given CoreVideo ColorPrimaries constant string (in the kCVImageBufferColorPrimaries_... family).  Returns 2 (the code point for "unknown") if the string is NULL or not recognized.
CV_EXPORT int CVColorPrimariesGetIntegerCodePointForString( CV_NULLABLE CFStringRef colorPrimariesString ) API_AVAILABLE(macosx(10.13), ios(11.0), tvos(11.0), watchos(4.0));
// Returns the standard integer code point corresponding to a given CoreVideo TransferFunction constant string (in the kCVImageBufferTransferFunction_... family).  Returns 2 (the code point for "unknown") if the string is NULL or not recognized.
CV_EXPORT int CVTransferFunctionGetIntegerCodePointForString( CV_NULLABLE CFStringRef transferFunctionString ) API_AVAILABLE(macosx(10.13), ios(11.0), tvos(11.0), watchos(4.0));

// Returns the CoreVideo YCbCrMatrix constant string (in the kCVImageBufferYCbCrMatrix_... family) corresponding to a given standard integer code point.  Returns NULL if the code point is not recognized, or if it is 2 (the code point for "unknown").
CV_EXPORT CV_NULLABLE CFStringRef CVYCbCrMatrixGetStringForIntegerCodePoint( int yCbCrMatrixCodePoint ) API_AVAILABLE(macosx(10.13), ios(11.0), tvos(11.0), watchos(4.0));
// Returns the CoreVideo ColorPrimaries constant string (in the kCVImageBufferColorPrimaries_... family) corresponding to a given standard integer code point.  Returns NULL if the code point is not recognized, or if it is 2 (the code point for "unknown").
CV_EXPORT CV_NULLABLE CFStringRef CVColorPrimariesGetStringForIntegerCodePoint( int colorPrimariesCodePoint ) API_AVAILABLE(macosx(10.13), ios(11.0), tvos(11.0), watchos(4.0));
// Returns the CoreVideo TransferFunction constant string (in the kCVImageBufferTransferFunction_... family) corresponding to a given standard integer code point.  Returns NULL if the code point is not recognized, or if it is 2 (the code point for "unknown").
CV_EXPORT CV_NULLABLE CFStringRef CVTransferFunctionGetStringForIntegerCodePoint( int transferFunctionCodePoint ) API_AVAILABLE(macosx(10.13), ios(11.0), tvos(11.0), watchos(4.0));

#pragma mark CVImageBufferRef

/*!
    @typedef	CVImageBufferRef
    @abstract   Base type for all CoreVideo image buffers

*/
typedef CVBufferRef CVImageBufferRef;

/*!
    @function   CVImageBufferGetEncodedSize
    @abstract   Returns the full encoded dimensions of a CVImageBuffer.  For example, for an NTSC DV frame this would be 720x480
    @param      imageBuffer A CVImageBuffer that you wish to retrieve the encoded size from.
    @result     A CGSize returning the full encoded size of the buffer
		Returns zero size if called with a non-CVImageBufferRef type or NULL.
*/
CV_EXPORT CGSize CVImageBufferGetEncodedSize( CVImageBufferRef CV_NONNULL imageBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVImageBufferGetDisplaySize
    @abstract   Returns the nominal output display size (in square pixels) of a CVImageBuffer.  
                For example, for an NTSC DV frame this would be 640x480
    @param      imageBuffer A CVImageBuffer that you wish to retrieve the display size from.
    @result     A CGSize returning the nominal display size of the buffer
		Returns zero size if called with a non-CVImageBufferRef type or NULL.
*/
CV_EXPORT CGSize CVImageBufferGetDisplaySize( CVImageBufferRef CV_NONNULL imageBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

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
CV_EXPORT CGRect CVImageBufferGetCleanRect( CVImageBufferRef CV_NONNULL imageBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
    @function   CVImageBufferIsFlipped
    @abstract   Returns whether the image is flipped vertically or not.
    @param      imageBuffer target
    @result     True if 0,0 in the texture is upper left, false if 0,0 is lower left.
*/
CV_EXPORT Boolean CVImageBufferIsFlipped( CVImageBufferRef CV_NONNULL imageBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);


#if __has_include(<CoreGraphics/CGColorSpace.h>)
/*!
    @function   CVImageBufferGetColorSpace
    @abstract   Returns the color space of a CVImageBuffer.
    @param      imageBuffer A CVImageBuffer that you wish to retrieve the color space from.
    @result     A CGColorSpaceRef representing the color space of the buffer.
		Returns NULL if called with a non-CVImageBufferRef type or NULL.
*/
CV_EXPORT CGColorSpaceRef CV_NULLABLE CVImageBufferGetColorSpace( CVImageBufferRef CV_NONNULL imageBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);

/*!
   @function   CVImageBufferCreateColorSpaceFromAttachments
   @abstract   Attempts to synthesize a CGColorSpace from an image buffer's attachments.
   @param      attachments A CFDictionary of attachments for an image buffer, obtained using CVBufferCopyAttachments().
   @result     A CGColorSpaceRef representing the color space of the buffer.
		Returns NULL if the attachments dictionary does not contain the information required to synthesize a CGColorSpace.
   @discussion
	To generate a CGColorSpace, the attachments dictionary should include values for either:
		1. kCVImageBufferICCProfile
		2. kCVImageBufferColorPrimariesKey, kCVImageBufferTransferFunctionKey, and kCVImageBufferYCbCrMatrixKey (and possibly kCVImageBufferGammaLevelKey)
	The client is responsible for releasing the CGColorSpaceRef when it is done with it (CGColorSpaceRelease() or CFRelease())
		
*/
CV_EXPORT CGColorSpaceRef CV_NULLABLE CVImageBufferCreateColorSpaceFromAttachments( CFDictionaryRef CV_NONNULL attachments ) __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_10_0);

#endif // __has_include(<CoreGraphics/CGColorSpace.h>)

// CFData (24 bytes) containing big-endian data matching payload of ISO/IEC 23008-2:2015(E), D.2.28 Mastering display colour volume SEI message
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferMasteringDisplayColorVolumeKey __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_11_0);

	// CFData (4 bytes) containing big-endian data matching payload of Content Light Level Information SEI message
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferContentLightLevelInfoKey __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_11_0);

// CFData (8 bytes) containing big-endian data matching payload of Ambient Viewing Environment SEI message
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferAmbientViewingEnvironmentKey API_AVAILABLE(macosx(12.0), ios(15.0), tvos(15.0), watchos(8.0));

// CFNumberRef integer value in millilux
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferSceneIlluminationKey API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

/*!
	@constant    kCVImageBufferRegionOfInterestKey
	@abstract
		Specifies region of interest that image statistics cover.
	@discussion
		This value should be a CGRect dictionary created by CGRectCreateDictionaryRepresentation(). The origin in the CGRect represents the x,y coordinate within the CVPixelBuffer where region of interest is located.
*/
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferRegionOfInterestKey           API_AVAILABLE(macosx(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/*!
  @constant    kCVImageBufferLogTransferFunctionKey
	Indicates that the transfer function or gamma of the content is a log format and identifies the specific log curve.
  @discussion
	The value is a CFString holding fully specified reverse DNS identifier.
	Log is a specific video format usually processed in a camera's ISP. A Log video format usually defines:
		 Scene-referred color primaries designed to preserve the chromaticity range captured by a camera sensor. In cinematography, "scene-referred" color primaries refers to a color space designed to accurately preserve the chromaticity and dynamic range directly captured by a camera sensor.
		 A specific gamma curve (or transfer characteristic) tailored to capturing the full dynamic range from the sensor. This gamma curve is usually shaped like a log curve (hence the name Log).
		 A set of matrix transforms to go from RGB to Y'CbCr (Y'CbCr being the most common format used to store the bits compressed into a file).
		 As described above, a Log video format defines a whole color space (even though the “log” part of the name comes only from the “transfer characteristic” or gamma curve)
		 Content captured in Apple Log will have this key set to kCVImageBufferLogTransferFunction_AppleLog or kCVImageBufferLogTransferFunction_AppleLog2.
  @constant    kCVImageBufferLogTransferFunction_AppleLog
	Indicates the Apple Log identifier.
  @constant    kCVImageBufferLogTransferFunction_AppleLog2
	Indicates the Apple Log 2 identifier.
	To use Apple Log 2, set other color attachments as follows:
		kCVImageBufferColorPrimariesKey = undefined or absent
		kCVImageBufferTransferFunctionKey = undefined or absent
		kCVImageBufferYCbCrMatrixKey = kCVImageBufferYCbCrMatrix_ITU_R_2020
	https://developer.apple.com/download/all/?q=Apple%20log%20profile
  @discussion
	You can download the Apple Log Profile White Paper from the Apple Developer Downloads website.
*/
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferLogTransferFunctionKey API_AVAILABLE(macosx(14.2), ios(17.2), tvos(17.2), watchos(10.2), visionos(1.1));

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferLogTransferFunction_AppleLog API_AVAILABLE(macosx(14.2), ios(17.2), tvos(17.2), watchos(10.2), visionos(1.1));

CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferLogTransferFunction_AppleLog2 API_AVAILABLE(macosx(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/*!
    @constant    kCVImageBufferDisplayMaskRectangleKey
    @abstract
        Specifies the rectangular display area within the image. The left, width, top and height are specified relative to a reference raster width and height that should be scaled to the image buffer dimensions.
    @discussion
        Value is a dictionary containing these keys for the raster rectangle:
            kCVImageBufferDisplayMaskRectangle_ReferenceRasterWidthKey
            kCVImageBufferDisplayMaskRectangle_ReferenceRasterHeightKey
            kCVImageBufferDisplayMaskRectangle_RectangleLeftKey
            kCVImageBufferDisplayMaskRectangle_RectangleWidthKey
            kCVImageBufferDisplayMaskRectangle_RectangleTopKey
            kCVImageBufferDisplayMaskRectangle_RectangleHeightKey
*/
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferDisplayMaskRectangleKey API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0)); // CFDictionary

/*!
    @constant    kCVImageBufferDisplayMaskRectangle_ReferenceRasterWidthKey
    @abstract
        Specifies the width in pixels of the 2D coordinate system to define the rectangle. 0,0 origin is the top-left. The raster width value is a CFNumber of unsigned 16-bit integer. Usually matches the width of the video or the output device.
 */
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferDisplayMaskRectangle_ReferenceRasterWidthKey API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0)); // CFNumber(uint16_t)

/*!
    @constant    kCVImageBufferDisplayMaskRectangle_ReferenceRasterHeightKey
    @abstract
        Specifies the height in pixels of the 2D coordinate system to define the rectangle. 0,0 origin is the top-left. The raster height value is a CFNumber of unsigned 16-bit integer. Usually matches the height of the video or the output device.
 */
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferDisplayMaskRectangle_ReferenceRasterHeightKey API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0)); // CFNumber(uint16_t)

/*!
    @constant    kCVImageBufferDisplayMaskRectangle_RectangleLeftKey
    @abstract
        Specifies the horizontal pixel offset of the rectangle from the left of the bounding raster. The left offset value is a CFNumber of unsigned 16-bit integer that is less than the reference raster width value.
 */
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferDisplayMaskRectangle_RectangleLeftKey API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0)); // CFNumber(uint16_t)

/*!
    @constant    kCVImageBufferDisplayMaskRectangle_RectangleWidthKey
    @abstract
        Specifies the width of the rectangle starting at rectangle's left offset toward the rectangle's right edge. The width value is a CFNumber of unsigned 16-bit integer.
 */
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferDisplayMaskRectangle_RectangleWidthKey API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0)); // CFNumber(uint16_t)

/*!
    @constant    kCVImageBufferDisplayMaskRectangle_RectangleTopKey
    @abstract
        Specifies the vertical pixel offset of the rectangle from the top of the bounding raster. The top offset value is a CFNumber of unsigned 16-bit integer that is less than the reference raster height value.
 */
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferDisplayMaskRectangle_RectangleTopKey API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0)); // CFNumber(uint16_t)

/*!
    @constant    kCVImageBufferDisplayMaskRectangle_RectangleHeightKey
    @abstract
        Specifies the height of the rectangle starting at rectangle's top offset toward the rectangle's bottom edge. The height value is a CFNumber of unsigned 16-bit integer.
 */
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferDisplayMaskRectangle_RectangleHeightKey API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0)); // CFNumber(uint16_t)

/*!
    @constant    kCVImageBufferDisplayMaskRectangleStereoLeftKey
    @abstract
        Specifies the rectangular display area within the left eye view of stereo images, using the same keys as with kCVImageBufferDisplayMaskRectangleKey. To address window violations in stereo video, points insetting the left and right edges of the rectangle are supported through additional keys, allowing the description of the "extended raster rectangle".
    @discussion
        Value is a dictionary containing these keys for the extended raster rectangle:
            kCVImageBufferDisplayMaskRectangle_ReferenceRasterWidthKey
            kCVImageBufferDisplayMaskRectangle_ReferenceRasterHeightKey
            kCVImageBufferDisplayMaskRectangle_RectangleLeftKey
            kCVImageBufferDisplayMaskRectangle_RectangleWidthKey
            kCVImageBufferDisplayMaskRectangle_RectangleTopKey
            kCVImageBufferDisplayMaskRectangle_RectangleHeightKey
            kCVImageBufferDisplayMaskRectangle_LeftEdgePointsKey
            kCVImageBufferDisplayMaskRectangle_RightEdgePointsKey
*/
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferDisplayMaskRectangleStereoLeftKey API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0)); // CFDictionary

/*!
    @constant    kCVImageBufferDisplayMaskRectangleStereoRightKey
    @abstract
        Specifies the rectangular display area within the right eye view of stereo images, using the same keys as with kCVImageBufferDisplayMaskRectangleKey. To address window violations in stereo video, points insetting the left and right edges of the rectangle are supported through additional keys, allowing the description of the "extended raster rectangle".
    @discussion
        Value is a dictionary containing these keys for the extended raster rectangle:
            kCVImageBufferDisplayMaskRectangle_ReferenceRasterWidthKey
            kCVImageBufferDisplayMaskRectangle_ReferenceRasterHeightKey
            kCVImageBufferDisplayMaskRectangle_RectangleLeftKey
            kCVImageBufferDisplayMaskRectangle_RectangleWidthKey
            kCVImageBufferDisplayMaskRectangle_RectangleTopKey
            kCVImageBufferDisplayMaskRectangle_RectangleHeightKey
            kCVImageBufferDisplayMaskRectangle_LeftEdgePointsKey
            kCVImageBufferDisplayMaskRectangle_RightEdgePointsKey
*/
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferDisplayMaskRectangleStereoRightKey API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0)); // CFDictionary

/*!
    @constant    kCVImageBufferDisplayMaskRectangle_LeftEdgePointsKey
    @abstract
        Specifies inset points on the left vertical edge of the rectangle. The points are CFArray of unsigned 16-bit integer CFNumber pairs alternating between inset X and inset Y. Inset X is an unsigned offset from left edge (0) towards the right edge (width). Inset Y is an unsigned offset from top edge (0) towards the bottom edge (height)
 */
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferDisplayMaskRectangle_LeftEdgePointsKey API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0)); // CFArray( CFNumber(uint16_t) pairs)

/*!
    @constant    kCVImageBufferDisplayMaskRectangle_RightEdgePointsKey
    @abstract
        Specifies inset points on the right vertical edge of the rectangle. The points are CFArray of unsigned 16-bit integer CFNumber pairs alternating between inset X and inset Y. Inset X is an unsigned offset from right edge (0) towards the left edge (width). Inset Y is an unsigned offset from top edge (0) towards the bottom edge (height)
 */
CV_EXPORT const CFStringRef CV_NONNULL kCVImageBufferDisplayMaskRectangle_RightEdgePointsKey API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0)); // CFArray(  CFNumber(uint16_t) pairs)

#if defined(__cplusplus)
}
#endif

#endif
