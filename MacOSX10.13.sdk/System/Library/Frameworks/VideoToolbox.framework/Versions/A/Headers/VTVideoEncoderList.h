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

// returns CFArray of CFDictionaries with following keys:
VT_EXPORT const CFStringRef kVTVideoEncoderList_CodecType API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // CFNumber for four-char-code (eg, 'avc1')
VT_EXPORT const CFStringRef kVTVideoEncoderList_EncoderID API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // CFString, reverse-DNS-style unique identifier for this encoder; may be passed as kVTVideoEncoderSpecification_EncoderID
VT_EXPORT const CFStringRef kVTVideoEncoderList_CodecName API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // CFString, for display to user (eg, "H.264")
VT_EXPORT const CFStringRef kVTVideoEncoderList_EncoderName API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // CFString, for display to user (eg, "Apple H.264")
VT_EXPORT const CFStringRef kVTVideoEncoderList_DisplayName API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // CFString (same as CodecName if there is only one encoder for that format, otherwise same as EncoderName)

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
		CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE CFStringRef		* CM_NULLABLE outEncoderID,
		CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE CFDictionaryRef	* CM_NULLABLE outSupportedProperties ) API_AVAILABLE(macosx(10.13), ios(11.0), tvos(11.0));
	
#pragma pack(pop)

#if defined(__cplusplus)
}
#endif

#endif // VTVIDEOENCODERLIST_H
