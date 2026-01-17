/*
	File:  VTRAWProcessingProperties.h
	
	Framework:  VideoToolbox
	
	Copyright 2013-2024 Apple Inc. All rights reserved.
	
*/

#ifndef VTRAWPROCESSINGPROPERTIES_H
#define VTRAWPROCESSINGPROPERTIES_H

#include <CoreMedia/CMBase.h>
#include <VideoToolbox/VTBase.h>

#include <CoreFoundation/CoreFoundation.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)    

/*!
	@header
	@abstract
		Standard Video Toolbox RAWProcessing properties
		
	@discussion
		This file defines standard properties used to describe and configure RAWProcessing
		operations managed by the video toolbox.
		
		The video toolbox will provide direct support for some of these properties.
		Some properties are supported by individual RAW processors.
		
		Clients can query supported properties by calling VTSessionCopySupportedPropertyDictionary.
*/


/*!
	@constant	kVTRAWProcessingPropertyKey_MetalDeviceRegistryID
	@abstract
		This property, if supported, requests that the Metal device corresponding to the specified registryID be used for any Metal related processing
	@discussion
		This property is not supported by all RAWProcessors
 
*/
VT_EXPORT const CFStringRef kVTRAWProcessingPropertyKey_MetalDeviceRegistryID CF_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos); // ReadWrite, uint64_t 


/*!
	@constant	kVTRAWProcessingPropertyKey_OutputColorAttachments
	@abstract
		Returns the color-related CVImageBuffer keys and values that will be attachments to the returned pixel buffers.
	@discussion
		This property may not be supported by all RAW Processors. Only color-related keys from CVImageBuffer.h are permitted in the returned dictionary.
*/
VT_EXPORT const CFStringRef kVTRAWProcessingPropertyKey_OutputColorAttachments API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, tvos, watchos); // Read Only, CFDictionaryRef

/*!
	@constant   kVTRAWProcessingPropertyKey_MetadataForSidecarFile
	@abstract
		This property, if supported, returns the current processing metadata on the RAW Processor. The returned value can be used by the caller to create, or overwrite an existing sidecar file.
	@discussion
		This property is not supported by all RAWProcessors. The metadata returned represents a fully-formed sidecar file, and should be compatible with the MediaExtension FormatReader.
*/
VT_EXPORT const CFStringRef kVTRAWProcessingPropertyKey_MetadataForSidecarFile API_AVAILABLE(macos(26.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos); // Read Only, CFData

#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif // VTRAWPROCESSINGPROPERTIES_H
