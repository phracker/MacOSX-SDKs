/*
	File:  VTVideoEncoderList.h
 
	Framework:  VideoToolbox
 
	Copyright 2012-2013 Apple Inc. All rights reserved.
 
*/

#ifndef VTVIDEOENCODERLIST_H
#define VTVIDEOENCODERLIST_H

#include <CoreMedia/CMBase.h>
#include <VideoToolbox/VTBase.h>
#include <CoreMedia/CMFormatDescription.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)

/*!
	@function	VTCopyVideoEncoderList
	@abstract	Builds a list of available video encoders.
	@discussion
		The caller must CFRelease the returned list.
*/
VT_EXPORT OSStatus VTCopyVideoEncoderList( 
	CM_NULLABLE CFDictionaryRef			options,
	CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE CFArrayRef * CM_NONNULL listOfVideoEncodersOut ) API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
	
CM_ASSUME_NONNULL_BEGIN
// keys for options dictionary:
VT_EXPORT const CFStringRef kVTVideoEncoderListOption_IncludeStandardDefinitionDVEncoders API_AVAILABLE(macosx(12.0), ios(15.0), tvos(15.0)); // optional. CFBoolean.  By default, DV encoders will not be included in the list.  If present and set to kCFBooleanTrue, DV encoders will be included.

// returns CFArray of CFDictionaries with following keys:
VT_EXPORT const CFStringRef kVTVideoEncoderList_CodecType API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // CFNumber for four-char-code (eg, 'avc1')
VT_EXPORT const CFStringRef kVTVideoEncoderList_EncoderID API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // CFString, reverse-DNS-style unique identifier for this encoder; may be passed as kVTVideoEncoderSpecification_EncoderID
VT_EXPORT const CFStringRef kVTVideoEncoderList_CodecName API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // CFString, for display to user (eg, "H.264")
VT_EXPORT const CFStringRef kVTVideoEncoderList_EncoderName API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // CFString, for display to user (eg, "Apple H.264")
VT_EXPORT const CFStringRef kVTVideoEncoderList_DisplayName API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // CFString (same as CodecName if there is only one encoder for that format, otherwise same as EncoderName)
VT_EXPORT const CFStringRef kVTVideoEncoderList_GPURegistryID API_AVAILABLE(macosx(10.14)); // optional. CFNumberRef.  If encoder is associated with a specific GPU, this corresponds to the GPU registryID as reported by [MTLDevice registryID].
VT_EXPORT const CFStringRef kVTVideoEncoderList_SupportedSelectionProperties API_AVAILABLE(macosx(10.14), ios(13.0), tvos(13.0)); // optional. CFDictionary.  If present, represents a subset of supported properties that may be useful during encoder selection
VT_EXPORT const CFStringRef kVTVideoEncoderList_PerformanceRating API_AVAILABLE(macosx(10.14), ios(13.0), tvos(13.0)); // optional. CFNumber.  If present, indicates a relative rating value for the encoder compared to other encoders of the same format.
VT_EXPORT const CFStringRef kVTVideoEncoderList_QualityRating API_AVAILABLE(macosx(10.14), ios(13.0), tvos(13.0)); // optional. CFNumber.  If present, indicates a Quality Rating value for the encoder relative to other encoders of the same format.  This is a highly generalized value and different encoders may have strengths at different resolutions and bitrates.
VT_EXPORT const CFStringRef kVTVideoEncoderList_InstanceLimit API_AVAILABLE(macosx(10.14), ios(13.0), tvos(13.0)); // optional. CFBoolean.  If present and set to kCFBooleanTrue, there is a global instance limit cap on this encoder.  Indicates that an encoder is a scarce resource which may potentially be unavailable.
VT_EXPORT const CFStringRef kVTVideoEncoderList_IsHardwareAccelerated API_AVAILABLE(macosx(10.14), ios(13.0), tvos(13.0)); // optional. CFBoolean.  If present and set to kCFBooleanTrue, indicates that the encoder is hardware accelerated.
VT_EXPORT const CFStringRef kVTVideoEncoderList_SupportsFrameReordering API_AVAILABLE(macosx(11.0), ios(14.0), tvos(14.0)); // optional. CFBoolean.  By default, this is assumed to be true if not present.  If present and set to kCFBooleanFalse, indicates that the encoder will not use B frames.
VT_EXPORT const CFStringRef kVTVideoEncoderList_SupportsMultiPass API_UNAVAILABLE(macosx, ios, tvos); // optional. CFBoolean.  By default, this is assumed to be false if not present. If present and set to kCFBooleanTrue, indicates that the encoder supports multipass.
CM_ASSUME_NONNULL_END

/*!
	@function	VTCopySupportedPropertyDictionaryForEncoder
	@abstract	Builds a list of supported properties and encoder ID for an encoder
	@discussion
		The caller must CFRelease the returned supported properties and encoder ID.
*/
VT_EXPORT OSStatus VTCopySupportedPropertyDictionaryForEncoder(
		int32_t						width,
		int32_t						height,
		CMVideoCodecType			codecType,
		CM_NULLABLE CFDictionaryRef	encoderSpecification,
		CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE CFStringRef		* CM_NULLABLE encoderIDOut,
		CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE CFDictionaryRef	* CM_NULLABLE supportedPropertiesOut ) API_AVAILABLE(macosx(10.13), ios(11.0), tvos(11.0));
	
#pragma pack(pop)

#if defined(__cplusplus)
}
#endif

#endif // VTVIDEOENCODERLIST_H
