#if !__has_include(<AVFCapture/AVCaptureSpatialAudioMetadataSampleGenerator.h>)
/*
    File:		AVCaptureSpatialAudioMetadataSampleGenerator.h
 
    Framework:  AVFoundation
 
    Copyright 2025 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>

#import <CoreMedia/CMSampleBuffer.h>

NS_ASSUME_NONNULL_BEGIN

/// An interface for generating a spatial audio timed metadata sample.
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureSpatialAudioMetadataSampleGenerator : NSObject

/// Returns the format description of the sample buffer returned from the ``newTimedMetadataSampleBufferAndResetAnalyzer`` method.
///
/// Use this format description when creating your ``AVAssetWriter`` track for spatial audio timed metadata.
@property(readonly, nonatomic) CMFormatDescriptionRef timedMetadataSampleBufferFormatDescription;

/// Analyzes the provided audio sample buffer for its contribution to the spatial audio timed metadata value.
///
/// - Parameter sbuf: a sample buffer containing spatial audio.
/// - Returns: `noErr` if the sample is successfully analyzed, otherwise a non-zero error code.
///
/// You must call this method with each and every spatial audio buffer you provide to ``AVAssetWriter``, so it can be analyzed for the generation of a proper spatial audio timed metadata value.
- (OSStatus)analyzeAudioSample:(CMSampleBufferRef)sbuf;

/// Creates a sample buffer containing a spatial audio timed metadata sample computed from all analyzed audio buffers, and resets the analyzer to its initial state.
///
/// - Returns: a ``CMSampleBufferRef`` containing the spatial audio timed metadata sample, or `NULL` if no value can be computed.
///
/// Call this method after you pass the last audio sample buffer of your recording to ``analyzeAudioSample:``. Then pass the returned ``CMSampleBufferRef`` directly to your ``AVAssetWriterInput`` to add the sample to your recording's audio timed metadata track. Note that ``AVAssetWriter`` expects one and only one spatial audio metadata sample buffer to be present in the timed metadata track.
///
/// - Note: Calling this method also resets the analyzer, making it ready for another run of audio sample buffers. Thus one generator can be re-used for multiple recordings.
- (nullable CMSampleBufferRef)newTimedMetadataSampleBufferAndResetAnalyzer;

/// Calling this method resets the analyzer to its initial state so that a new run of audio sample buffers can be analyzed.
///
/// Call this method if you need to abort generating the audio timed metadata buffer for audio already provided to ``analyzeAudioSample:``.
- (void)resetAnalyzer;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVCaptureSpatialAudioMetadataSampleGenerator.h>
#endif
