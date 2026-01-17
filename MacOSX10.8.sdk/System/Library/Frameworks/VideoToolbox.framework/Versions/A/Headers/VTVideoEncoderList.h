/*
	File:  VTVideoEncoderList.h
 
	Framework:  VideoToolbox
 
	Copyright 2012 Apple Inc. All rights reserved.
 
*/

#ifndef VTVIDEOENCODERLIST_H
#define VTVIDEOENCODERLIST_H

#include <CoreMedia/CMBase.h>
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
	CFDictionaryRef options, // pass NULL
	CFArrayRef *listOfVideoEncodersOut ) AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER;

// returns CFArray of CFDictionaries with following keys:
VT_EXPORT const CFStringRef kVTVideoEncoderList_CodecType AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // CFNumber for four-char-code (eg, 'avc1')
VT_EXPORT const CFStringRef kVTVideoEncoderList_EncoderID AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // CFString, reverse-DNS-style unique identifier for this encoder; may be passed as kVTVideoEncoderSpecification_EncoderID
VT_EXPORT const CFStringRef kVTVideoEncoderList_CodecName AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // CFString, for display to user (eg, "H.264")
VT_EXPORT const CFStringRef kVTVideoEncoderList_EncoderName AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // CFString, for display to user (eg, "Apple H.264")
VT_EXPORT const CFStringRef kVTVideoEncoderList_DisplayName AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER; // CFString (same as CodecName if there is only one encoder for that format, otherwise same as EncoderName)


#pragma pack(pop)

#if defined(__cplusplus)
}
#endif

#endif // VTVIDEOENCODERLIST_H
