/*
	File:  VTFrameProcessorErrors.h
 
	Framework:  VideoToolbox
 
	Copyright © 2023-2024 Apple Inc. All rights reserved.
 
*/

#ifndef VTFRAMEPROCESSORERRORS_H
#define VTFRAMEPROCESSORERRORS_H

#ifdef __OBJC__

#import <CoreMedia/CMBase.h>
#import <Foundation/Foundation.h>

API_AVAILABLE(macos(15.4), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos)

extern NSErrorDomain _Nonnull const VTFrameProcessorErrorDomain;


/// `VTFrameProcessor` error codes.
///
/// These error codes are returned in the `NSError` object in the event a method fails.
typedef NS_ERROR_ENUM(VTFrameProcessorErrorDomain, VTFrameProcessorError)
{
	/// Returned if the processor failed for unknown reason.
	VTFrameProcessorUnknownError				= -19730,
	/// Returned if the processor failed due to an unsupported resolution.
	VTFrameProcessorUnsupportedResolution		= -19731,
	/// Returned if the session is used to process frames without being started.
	VTFrameProcessorSessionNotStarted			= -19732,
	/// Returned if a `startSessionWithConfiguration` call is made on a session which has already been started.
	VTFrameProcessorSessionAlreadyActive		= -19733,
	/// Returned if a fatal error is encoutnered during processing.
	VTFrameProcessorFatalError					= -19734,
	/// Returned if processing failed and current session should be stopped.
	VTFrameProcessorSessionLevelError			= -19735,
	/// Returned if the session failed to initialize the processing pipeline.
	VTFrameProcessorInitializationFailed		= -19736,
	/// Returned to indicate that one or more frames is in a format which is not supproted by the processor.
	VTFrameProcessorUnsupportedInput			= -19737,
	/// Returned if the session or processor is unable to allocate required memory.
	VTFrameProcessorMemoryAllocationFailure		= -19738,
	/// Returned if the specifed revision is not supported by the configured processor.
	VTFrameProcessorRevisionNotSupported		= -19739,
	/// Returned if the processor encountered an issue preventing it from processing the provided frame.
	VTFrameProcessorProcessingError				= -19740,
	/// Returned if one of the provided parameters is not valid.
	VTFrameProcessorInvalidParameterError		= -19741,
	/// Returned if one of the provided `VTFrameProcessorFrame` objects has a presentation time which is not supported by the processor, either invalid or out-of-order.
	VTFrameProcessorInvalidFrameTiming			= -19742,
	/// Returned if download of a required model asset for the processor failed
	VTFrameProcessorAssetDownloadFailed			= -19743,
};

#endif // __OBJC__

#endif // VTFRAMEPROCESSORERRORS_H
