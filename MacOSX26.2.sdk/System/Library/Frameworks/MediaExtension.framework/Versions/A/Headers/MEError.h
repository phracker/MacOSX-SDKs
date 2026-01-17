/*
	File:  MEError.h

	Framework:	MediaExtension

	Copyright © 2023 Apple Inc. All rights reserved.
 
	To report bugs, go to:  http://developer.apple.com/bugreporter/

*/

#ifndef MEError_h
#define MEError_h

#import <Foundation/Foundation.h>
#import <CoreMedia/CMBase.h>

#pragma mark - MEFormatReader Error codes

ME_EXPORT NSErrorDomain const MediaExtensionErrorDomain     API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@enum       	MEError
	@abstract		MediaExtension framework error codes.
	@discussion		These error codes are returned in the NSError object in the event a method fails.
	@constant		MEErrorUnsupportedFeature
		Returned if the extension does not support an aspect of the media.
	@constant		MEErrorAllocationFailure
		Returned if the extension cannot allocate memory.
	@constant		MEErrorInvalidParameter
		Returned if the extension received an invalid parameter.
	@constant		MEErrorParsingFailure
		Returned if any type of error occurred while parsing the media.
	@constant		MEErrorInternalFailure
		Returned if the extension encountered an internal operation failure (e.g. code loading).
	@constant		MEErrorPropertyNotSupported
		Returned if the extension encountered a property it does not support reading/writing to.
	@constant		MEErrorNoSuchEdit
		Returned if the plugin track reader is requested to return an edit that is out of range.
	@constant		MEErrorNoSamples
		Returned if the plugin sample cursor cannot be created because there are no samples in the track, or if a loadSampleBufferContainingSamplesToEndCursor request is made that cannot be satisfied.
	@constant		MEErrorLocationNotAvailable
		Returned to indicate a specific sample is not contiguous, spans more than one file, or is for some other reason unsuitable for reading directly from a file. For such samples, clients must call loadSampleBufferContainingSamplesToEndCursor.
	@constant		MEErrorEndOfStream
		Returned if the end of the source file has been reached.
	@constant		MEErrorPermissionDenied
		Returned if an invalid operation is requested by the client on a byte source.
	@constant		MEErrorReferenceMissing
		Returned if a decoder is asked to decode a sample without decoding the required reference frame dependencies first.
*/
typedef NS_ERROR_ENUM(MediaExtensionErrorDomain, MEError) {
	MEErrorUnsupportedFeature			= -19320,
	MEErrorAllocationFailure			= -19321,
	MEErrorInvalidParameter				= -19322,
	MEErrorParsingFailure				= -19323,
	MEErrorInternalFailure				= -19324,
	MEErrorPropertyNotSupported			= -19325,

	MEErrorNoSuchEdit					= -19326,
	MEErrorNoSamples					= -19327,
	MEErrorLocationNotAvailable			= -19328,

	MEErrorEndOfStream					= -19329,
	MEErrorPermissionDenied				= -19330,

	MEErrorReferenceMissing				= -19331,
} API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

#endif /* MEError_h */
