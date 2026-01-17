/*
	File:  VTUtilities.h
 
	Framework:  VideoToolbox
 
	Copyright © 2013-2014 Apple Inc. All rights reserved.
 
*/

#ifndef VTUTILITIES_H
#define VTUTILITIES_H

#include <VideoToolbox/VTBase.h>
#include <CoreVideo/CoreVideo.h>
#include <CoreGraphics/CoreGraphics.h>
#include <CoreMedia/CMBase.h>
#include <CoreMedia/CMFormatDescription.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)

/*!
	@function VTCreateCGImageFromCVPixelBuffer
	@abstract Creates a CGImage using the provided CVPixelBuffer
	@param	pixelBuffer
		The pixelBuffer to be used as the image data source for the CGImage.
	@param	options
		no options currently.  pass NULL.
	@param	imageOut
		pointer to an address to receive the newly created CGImage.
	@discussion
		This routine creates a CGImage representation of the image data contained in
		the provided CVPixelBuffer.
		The source CVPixelBuffer may be retained for the lifetime of the CGImage.  Changes
		to the CVPixelBuffer after making this call (other than releasing it) will have 
		undefined results.
		Not all CVPixelBuffer pixel formats will support conversion into a CGImage compatible
		pixel format.
*/
VT_EXPORT OSStatus 
VTCreateCGImageFromCVPixelBuffer(
	CM_NONNULL CVPixelBufferRef			pixelBuffer,
	CM_NULLABLE CFDictionaryRef			options,
	CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE CGImageRef * CM_NONNULL imageOut ) API_AVAILABLE(macos(10.11), ios(9.0), tvos(10.2), visionos(1.0)) API_UNAVAILABLE(watchos);


/*!
	@function	VTRegisterSupplementalVideoDecoderIfAvailable
	@abstract	Requests that a video decoder, if available, be registered for the specified CMVideoCodecType
	@param	codecType
		The CMVideoCodecType corresponding the format being requested
	@discussion
 		This call will register a video decoder for the provided CMVideoCodecType if such a decoder is present on the system but not registered by default.
 		You can call VTIsHardwareDecodeAvailable to confirm availability of the decoder after calling VTRegisterSupplementalVideoDecoderIfAvailable.
 		Supplemental video decoders registered through this API will not work in applications which have not performed this opt in.  For broadest ecosystem compatibility, we encourage use of platform-standard formats such as H.264, HEVC, and AV1.
*/
VT_EXPORT void VTRegisterSupplementalVideoDecoderIfAvailable( CMVideoCodecType codecType ) API_AVAILABLE(macos(11.0), ios(26.2), tvos(26.2), visionos(26.2)) API_UNAVAILABLE(watchos);

/*!
	@function		VTCopyVideoDecoderExtensionProperties
	@abstract		Returns information about the Media Extension video decoder required to decode the specified format.
	@discussion		If a Media Extension video decoder will be used to decode the specified format, this function will return information about the Media Extension that will be used.
	@param			formatDesc
		The format description for the video format for which information is being requested.
	@param			mediaExtensionPropertiesOut
		If a Media Extension video decoder will be used to decode the specified format, this pointer will return a dictionary with a set of properties describing the extension video decoder. The dictionary keys are VTExtensionPropertiesKey values.
	@result			If the function succeeds and a Media Extension video decoder will be used to decode this format, the return value will be noErr. If the function succeeds but a Media Extension video decoder will not be used to decode this format, the return value will be kVTCouldNotFindExtensionErr. If a Media Extension video decoder for the format was found but is disabled, the function will return kVTExtensionDisabledErr. Otherwise, the return value will be an error code describing the failure.
*/
VT_EXPORT OSStatus VTCopyVideoDecoderExtensionProperties( CMFormatDescriptionRef CM_NONNULL formatDesc, CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE CFDictionaryRef * CM_NONNULL mediaExtensionPropertiesOut ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@function		VTCopyRAWProcessorExtensionProperties
	@abstract		Returns information about the Media Extension RAW processor supporting the specified format.
	@discussion		If a Media Extension RAW processor will be used to process the specified format, this function will return information about the Media Extension that will be used.
	@param			formatDesc
		The format description for the video format for which information is being requested.
	@param			mediaExtensionPropertiesOut
		If a Media Extension RAW processor  will be used to process the specified format, this pointer will return a dictionary with a set of properties describing the extension RAW processor. The dictionary keys VTExtensionPropertiesKey values.
	@result			If the function succeeds and a Media Extension RAW processor will be used to process this format, the return value will be noErr. If the function succeeds but a Media Extension RAW processor will not be used to process this format, the return value will be kVTCouldNotFindExtensionErr. If a Media Extension RAW processor for the format was found but is disabled, the function will return kVTExtensionDisabledErr. Otherwise, the return value will be an error code describing the failure.
*/
VT_EXPORT OSStatus VTCopyRAWProcessorExtensionProperties( CMFormatDescriptionRef CM_NONNULL formatDesc, CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE CFDictionaryRef * CM_NONNULL mediaExtensionPropertiesOut ) CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@typedef		VTExtensionPropertiesKey
	@abstract		A key in a Media Extension extension properties dictionary.
*/
typedef CFStringRef VTExtensionPropertiesKey CF_TYPED_ENUM API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

CM_ASSUME_NONNULL_BEGIN

/*!
	@constant		kVTExtensionProperties_ExtensionIdentifierKey
	@abstract		A CFDictionary key for the video decoder extension identifier.
	@discussion		This key points to a CFStringRef value with the extension identifier, corresponding to the ClassImplementationID value from the EXAppExtensionAttributes dictionary in the Info.plist file.
*/
VT_EXPORT VTExtensionPropertiesKey const kVTExtensionProperties_ExtensionIdentifierKey API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos) CF_SWIFT_NAME(extensionIdentifier);

/*!
	@constant		kVTExtensionProperties_ExtensionNameKey
	@abstract		A CFDictionary key for the localized extension name.
	@discussion		This key points to a CFStringRef value with the localized extension name.
*/
VT_EXPORT VTExtensionPropertiesKey const kVTExtensionProperties_ExtensionNameKey API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos) CF_SWIFT_NAME(extensionName);

/*!
	@constant		kVTExtensionProperties_ContainingBundleNameKey
	@abstract		A CFDictionary key for the extension host application localized name.
	@discussion		This key points to a CFStringRef value with the localized name of the application hosting the extension.
*/
VT_EXPORT VTExtensionPropertiesKey const kVTExtensionProperties_ContainingBundleNameKey API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos) CF_SWIFT_NAME(containingBundleName);

/*!
	@constant		kVTExtensionProperties_ExtensionURLKey
	@abstract		A CFDictionary key for the URL of the extension.
	@discussion 	This key points to a CFURLRef value with the URL for the extension.
*/
VT_EXPORT VTExtensionPropertiesKey const kVTExtensionProperties_ExtensionURLKey API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos) CF_SWIFT_NAME(extensionURL);

/*!
	@constant		kVTExtensionProperties_ContainingBundleURLKey
	@abstract		A CFDictionary key for the URL of the extension host application.
	@discussion		This key points to a CFURLRef value with the URL of the extension host application.
*/
VT_EXPORT VTExtensionPropertiesKey const kVTExtensionProperties_ContainingBundleURLKey API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos) CF_SWIFT_NAME(containingBundleURL);

/*!
	@constant		kVTExtensionProperties_CodecNameKey
	@abstract		A CFDictionary key for the user readable name string of the codec.
	@discussion		This key points to a CFStringRef with the name of the codec from the supplied format description. This name will be the one listed in the extension CodecInfo array with the key CodecName.
*/
VT_EXPORT VTExtensionPropertiesKey const kVTExtensionProperties_CodecNameKey API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);


CM_ASSUME_NONNULL_END

#pragma pack(pop)

#if defined(__cplusplus)
}
#endif

#endif // VTUTILITIES_H
