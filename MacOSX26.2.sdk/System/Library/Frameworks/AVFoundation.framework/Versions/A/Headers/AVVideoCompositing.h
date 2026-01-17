#if !__has_include(<AVFCore/AVVideoCompositing.h>)
/*
	File:  AVVideoCompositing.h

	Framework:  AVFoundation
 
	Copyright 2013-2016 Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVTimedMetadataGroup.h>
#import <AVFoundation/AVSpatialVideoConfiguration.h>
#import <CoreVideo/CVPixelBufferPool.h>
#import <CoreMedia/CMTimeRange.h>
#import <CoreMedia/CMSampleBuffer.h>
#import <CoreMedia/CMTaggedBufferGroup.h>

NS_ASSUME_NONNULL_BEGIN

typedef struct {
	NSInteger	horizontalSpacing;
	NSInteger	verticalSpacing;
} AVPixelAspectRatio;

typedef struct {
	CGFloat		left;
	CGFloat		top;
	CGFloat		right;
	CGFloat		bottom;
} AVEdgeWidths;

@class AVVideoComposition;
@class AVAsynchronousVideoCompositionRequest;
@protocol AVVideoCompositionInstruction;

@class AVVideoCompositionRenderContextInternal;

/// The AVVideoCompositionRenderContext class defines the context within which custom compositors render new output pixels buffers.
/// 
/// An instance of AVVideoCompositionRenderContext provides size and scaling information and offers a service for efficiently providing pixel buffers from a managed pool of buffers.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVVideoCompositionRenderContext : NSObject {
@private
	AVVideoCompositionRenderContextInternal	*_internal;
}

/// Indicates the width and height for rendering frames.
@property (nonatomic, readonly) CGSize size;

/// Transform to apply to the source image to incorporate renderScale, pixelAspectRatio, edgeWidths.
/// The coordinate system origin is the top left corner of the buffer.
@property (nonatomic, readonly) CGAffineTransform renderTransform; // incorporates renderScale, pixelAspectRatio, edgeWidths

/// Indicates a scaling ratio that should be applied when rendering frames.
@property (nonatomic, readonly) float renderScale;

/// Indicates the pixel aspect ratio for rendered frames.
@property (nonatomic, readonly) AVPixelAspectRatio pixelAspectRatio;

/// Indicates the thickness of the edge processing region on the left, top, right and bottom edges, in pixels.
@property (nonatomic, readonly) AVEdgeWidths edgeWidths;

/// Hints the custom compositor that it may use higher quality, potentially slower algorithms.
/// Generally true for non real time use cases.
@property (nonatomic, readonly) BOOL highQualityRendering;

/// The AVVideoComposition being rendered.
@property (nonatomic, readonly) AVVideoComposition *videoComposition;

/// Vends a CVPixelBuffer to use for rendering
/// 
/// The buffer will have its kCVImageBufferCleanApertureKey and kCVImageBufferPixelAspectRatioKey attachments set to match the current composition processor properties.
- (nullable CVPixelBufferRef)newPixelBuffer CF_RETURNS_RETAINED // caller must CFRelease
#if __swift__
API_DEPRECATED("Use newReadOnlyPixelBuffer() instead", macos(10.9, API_TO_BE_DEPRECATED), ios(7.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos)
#endif
;

@end

@class AVVideoCompositionRenderHintInternal;

/// An AVVideoCompositionRenderHint instance contains the information necessary for announcing upcoming rendering request time ranges.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVVideoCompositionRenderHint : NSObject {
@private
	AVVideoCompositionRenderHintInternal *_internal;
}

/// The start time of the upcoming composition requests.
@property (nonatomic, readonly) CMTime startCompositionTime;

/// The end time of the upcoming composition requests.
@property (nonatomic, readonly) CMTime endCompositionTime;

@end

/// Defines properties and methods for custom video compositors
/// 
/// For each AVFoundation object of class AVPlayerItem, AVAssetExportSession, AVAssetImageGenerator, or AVAssetReaderVideoCompositionOutput that has a non-nil value for its videoComposition property, when the value of the customVideoCompositorClass property of the AVVideoComposition is not Nil, AVFoundation creates and uses an instance of that custom video compositor class to process the instructions contained in the AVVideoComposition. The custom video compositor instance will be created when you invoke -setVideoComposition: with an instance of AVVideoComposition that's associated with a different custom video compositor class than the object was previously using.
/// 
/// When creating instances of custom video compositors, AVFoundation initializes them by calling -init and then makes them available to you for further set-up or communication, if any is needed, as the value of the customVideoCompositor property of the object on which -setVideoComposition: was invoked.
/// 
/// Custom video compositor instances will then be retained by the AVFoundation object for as long as the value of its videoComposition property indicates that an instance of the same custom video compositor class should be used, even if the value is changed from one instance of AVVideoComposition to another instance that's associated with the same custom video compositor class.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@protocol AVVideoCompositing<NSObject>

@required

/// Indicates the kinds of source frame pixel buffer attributes a video compositor can accept as input.
///
/// The property is required to provide kCVPixelBufferPixelFormatTypeKey along with the attributes for which the compositor needs specific values to work properly. If the attribute kCVPixelBufferPixelFormatTypeKey is missing an exception will be raised. If the custom compositor is meant to be used with an AVVideoCompositionCoreAnimationTool created using the videoCompositionCoreAnimationToolWithAdditionalLayer constructor, kCVPixelFormatType_32BGRA should be indicated as one of the supported pixel format types.
///
/// Missing attributes will be set by the composition engine to values allowing the best performance. This property is queried once before any composition request is sent to the compositor. Changing source buffer attributes afterwards is not supported.
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> NS_SWIFT_SENDABLE *sourcePixelBufferAttributes;

/// Indicates the pixel buffer attributes required by the video compositor for new buffers that it creates for processing.
///
/// The property is required to provide kCVPixelBufferPixelFormatTypeKey along with attributes for which the compositor needs specific values to work properly. Omitted attributes will be supplied by the composition engine to allow for the best performance. If the attribute kCVPixelBufferPixelFormatTypeKey is missing an exception will be raised. The getter for requiredPixelBufferAttributesForRenderContext is typically invoked prior to the creation of a new render context; the combination of the attributes in the returned value and the additional attributes supplied by the composition engine will be used in the creation of subsequent render context's pixelBuffers.
///
/// This property is queried once before any composition request is sent to the compositor. Changing required buffer attributes afterwards is not supported.
@property (nonatomic, readonly) NSDictionary<NSString *, id> NS_SWIFT_SENDABLE *requiredPixelBufferAttributesForRenderContext;

/// Called to notify the custom compositor that a composition will switch to a different render context
/// 
/// Instances of classes implementing the AVVideoComposting protocol can implement this method to be notified when
/// the AVVideoCompositionRenderContext instance handing a video composition changes. AVVideoCompositionRenderContext instances
/// being immutable, such a change will occur every time there is a change in the video composition parameters.
/// 
/// - Parameter newRenderContext: The render context that will be handling the video composition from this point
- (void)renderContextChanged:(AVVideoCompositionRenderContext *)newRenderContext;

/// Directs a custom video compositor object to create a new pixel buffer composed asynchronously from a collection of sources.
/// 
/// The custom compositor is expected to invoke, either subsequently or immediately, either:
/// -[AVAsynchronousVideoCompositionRequest finishWithComposedVideoFrame:] or
/// -[AVAsynchronousVideoCompositionRequest finishWithError:]. If you intend to finish rendering the frame after your
/// handling of this message returns, you must retain the instance of AVAsynchronousVideoCompositionRequest until after composition is finished.
/// Note that if the custom compositor's implementation of -startVideoCompositionRequest: returns without finishing the composition immediately,
/// it may be invoked again with another composition request before the prior request is finished; therefore in such cases the custom compositor should
/// be prepared to manage multiple composition requests.
/// 
/// If the rendered frame is exactly the same as one of the source frames, with no letterboxing, pillboxing or cropping needed,
/// then the appropriate source pixel buffer may be returned (after CFRetain has been called on it).
/// 
/// - Parameter asyncVideoCompositionRequest: An instance of AVAsynchronousVideoCompositionRequest that provides context for the requested composition.
- (void)startVideoCompositionRequest:(AVAsynchronousVideoCompositionRequest *)asyncVideoCompositionRequest;

@optional

/// Directs a custom video compositor object to cancel or finish all pending video composition requests
/// 
/// When receiving this message, a custom video compositor must block until it has either cancelled all pending frame requests,
/// and called the finishCancelledRequest callback for each of them, or, if cancellation is not possible, finished processing of all the frames
/// and called the finishWithComposedVideoFrame: or finishWithComposedTaggedBufferGroup: callback for each of them.
- (void)cancelAllPendingVideoCompositionRequests;

/// Indicates that clients can handle frames that contains wide color properties.
/// 
/// Controls whether the client will receive frames that contain wide color information. Care should be taken to avoid clamping.
@property (nonatomic, readonly) BOOL supportsWideColorSourceFrames API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Indicates that the client's video compositor can handle frames that contain high dynamic range (HDR) properties.
/// 
/// Controls whether the client will receive frames that contain HDR information.
/// If this field is omitted or set to NO, the framework will convert HDR frames to standard dynamic range (SDR) with BT.709 transfer function before sending to the client.
/// If this field is set to YES, the value of supportsWideColorSourceFrames will be ignored and assumed to be YES.
@property (nonatomic, readonly) BOOL supportsHDRSourceFrames API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Indicates that the custom compositor can support source tagged buffers.
/// 
/// When this property is YES, tagged buffers will be available to the custom compositor with sourceTaggedBuffers(byTrackID:) in Swift and sourceTaggedBufferGroupByTrackID: in Objective-C if the track contains tagged buffers.
/// When this property is NO, only monoscopic frames are supported.
/// If a custom compositor does not implement this property, it is considered the same as returning NO.
@optional
@property (nonatomic, readonly) BOOL supportsSourceTaggedBuffers API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/// Indicates that the custom compositor can conform supported sources to the composition color space by performing color conversions internally.
/// 
/// When the composition engine sees this property set to YES, it will not convert source pixel buffers that meet the custom compositor's processing requirements, as indicated via its
/// implementation of the AVVideoCompositing protocol, including the values it provides for sourcePixelBufferAttributes and supportsWideColorSourceFrames.
/// Source pixel buffers that do not meet its processing requirements will be converted. This includes cases where:
/// 
/// 1. supportsWideColorSourceFrames is set to NO and supportsHDRSourceFrames is set to NO or not implemented, and any source has a wide color gamut. In this case the source color space will be converted to BT.709 color space by the composition engine before it passes the source pixel buffer to the custom compositor. Note that if supportsHDRSourceFrames is YES, supportsWideColorSourceFrames is assumed to be YES.
/// 
/// 2. supportsHDRSourceFrames is set to NO and any source has HDR color. In this case the source color space will be converted to the composition color space by the composition engine before it passes the source pixel buffer to the custom compositor
/// 
/// 3. The source frame's pixel format is not in the list specified in sourcePixelBufferAttributes. In this case the composition engine will convert the pixel format to one of the supported formats, AND convert the color space to the composition color space.
/// 
/// If a custom compositor does not implement this property, it is considered the same as returning NO.
@optional
@property (nonatomic, readonly) BOOL canConformColorOfSourceFrames API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/// Informs a custom video compositor about upcoming rendering requests.
/// 
/// In the method the compositor can load composition resources such as overlay images which will be needed in the anticipated rendering time range.
/// 
/// Unlike -startVideoCompositionRequest, which is invoked only when the frame compositing is necessary, the framework typically calls this method every frame duration. It allows the custom compositor to load and unload a composition resource such as overlay images at an appropriate timing.
/// 
/// In forward playback, renderHint's startCompositionTime is less than endCompositionTime. In reverse playback, its endCompositionTime is less than startCompositionTime. For seeking, startCompositionTime == endCompositionTime, which means the upcoming composition request time range is unknown and the compositor shouldn’t preload time associated composition resources eagerly.
/// 
/// The method is guaranteed to be called before -startVideoCompositionRequest: for a given composition time.
/// 
/// The method is synchronous. The implementation should return quickly because otherwise the playback would stall and cause frame drops.
/// 
/// - Parameter renderHint: Information about the upcoming composition requests.
- (void)anticipateRenderingUsingHint:(AVVideoCompositionRenderHint *)renderHint API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Tell a custom video compositor to perform any work in prerolling phase.
/// 
/// The framework may perform prerolling to load media data to prime the render pipelines for smoother playback. This method is called in the prerolling phase so that the compositor can load composition resources such as overlay images which will be needed as soon as the playback starts.
/// 
/// Not all rendering scenarios use prerolling. For example, the method won't be called while seeking.
/// 
/// If called, the method is guaranteed to be invoked before the first -startVideoCompositionRequest: call.
/// 
/// The method is synchronous. The prerolling won't finish until the method returns.
/// 
/// - Parameter renderHint: Information about the upcoming composition requests.
-(void)prerollForRenderingUsingHint:(AVVideoCompositionRenderHint *)renderHint API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos);

@end

@class AVAsynchronousVideoCompositionRequestInternal;

/// An AVAsynchronousVideoCompositionRequest instance contains the information necessary for a video compositor to render an output pixel buffer. The video compositor must implement the AVVideoCompositing protocol.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVAsynchronousVideoCompositionRequest : NSObject <NSCopying> {
@private
	AVAsynchronousVideoCompositionRequestInternal *_internal;
}

/// The AVVideoCompositionRenderContext making the request
@property (nonatomic, readonly) AVVideoCompositionRenderContext *renderContext;

/// The time for which the frame should be composed
@property (nonatomic, readonly) CMTime compositionTime;

/// Track IDs of all the source video buffers that are available to compose the frame.
@property (nonatomic, readonly) NSArray<NSNumber *> *sourceTrackIDs;

/// Track IDs of all the source sample data buffers that are available to compose the frame.
@property (nonatomic, readonly) NSArray<NSNumber *> *sourceSampleDataTrackIDs API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// The AVVideoCompositionInstruction to use to compose the frame.
@property (nonatomic, readonly) id<AVVideoCompositionInstruction> videoCompositionInstruction;

/// Returns the source CVPixelBufferRef for the given track ID
/// 
/// If the track contains tagged buffers, a pixel buffer from one of the tagged buffers will be returned.
/// 
/// - Parameter trackID: The track ID for the requested source frame
- (nullable CVPixelBufferRef)sourceFrameByTrackID:(CMPersistentTrackID)trackID CF_RETURNS_NOT_RETAINED
#if __swift__
API_DEPRECATED("Use sourceReadOnlyPixelBuffer(byTrackID:) instead", macos(10.9, API_TO_BE_DEPRECATED), ios(7.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos)
#endif
;

/// Returns the source CMSampleBufferRef for the given track ID
/// 
/// - Parameter trackID: The track ID for the requested source sample buffer
- (nullable CMSampleBufferRef)sourceSampleBufferByTrackID:(CMPersistentTrackID)trackID CF_RETURNS_NOT_RETAINED
#if __swift__
API_DEPRECATED("Use sourceReadySampleBuffer(byTrackID:) instead", macos(10.9, API_TO_BE_DEPRECATED), ios(7.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos)
#endif
;

/// Returns the source AVTimedMetadataGroup * for the given track ID
/// 
/// - Parameter trackID: The track ID for the requested source timed metadata group.
- (nullable AVTimedMetadataGroup *)sourceTimedMetadataByTrackID:(CMPersistentTrackID)trackID API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// The method that the custom compositor calls when composition succeeds.
/// 
/// - Parameter composedVideoFrame: The video frame to finish with. Call finishWithComposedTaggedBufferGroup: instead if outputBufferDescription is non-nil.
- (void)finishWithComposedVideoFrame:(CVPixelBufferRef)composedVideoFrame
#if __swift__
API_DEPRECATED("Use finish(withComposedVideoFrame: CVReadOnlyPixelBuffer) instead", macos(10.9, API_TO_BE_DEPRECATED), ios(7.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos)
#endif
;

/// callback the custom compositor should call when composition failed. The error parameter should describe the actual error.
- (void)finishWithError:(NSError *)error;

/// callback the custom compositor should call for a request that has been cancelled.
- (void)finishCancelledRequest;

/// Returns the source CMTaggedBufferGroupRef for the given track ID.
/// 
/// Returns nil if the video track does not contain tagged buffers. Returns nil if the track does not contain video. This function should only be called when supportsSourceTaggedBuffers is YES.
/// 
/// - Parameter trackID: The track ID for the requested source tagged buffer group.
- (nullable CMTaggedBufferGroupRef)sourceTaggedBufferGroupByTrackID:(CMPersistentTrackID)trackID NS_REFINED_FOR_SWIFT CF_RETURNS_NOT_RETAINED API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/// The method that the custom compositor calls when composition succeeds.
/// 
/// - Parameter taggedBufferGroup: The tagged buffer group containing the composed tagged buffers. The tagged buffers must be compatible with the outputBufferDescription specified in the video composition. The outputBufferDescription must not be nil when calling this function.
/// NOTE: If ``AVVideoComposition/spatialConfigurations`` is not empty, then ``attach(spatialVideoConfiguration:to:)`` must be called with one of the spatial configurations. An exception will be thrown otherwise. Also, all pixel buffers must be associated with the same spatial configuration. An exception will be thrown otherwise.
- (void)finishWithComposedTaggedBufferGroup:(CMTaggedBufferGroupRef)taggedBufferGroup NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

/// Associates the pixel buffer with the specified spatial configuration.
/// - Parameters:
///   - spatialVideoConfiguration: The spatial configuration to associate with the pixel buffer.
///   - pixelBuffer: The pixel buffer to associate with the spatial configuration.
/// NOTE: The spatial configuration must be one of the spatial configurations specified in the ``AVVideoComposition/spatialConfigurations`` property. An exception will be thrown otherwise.
/// NOTE: All pixel buffers from the custom compositor must be associated with the same spatial configuration. An exception will be thrown otherwise.
/// A spatial configuration with all nil values indicates the video is not spatial. A nil spatial configuration also indicates the video is not spatial. The value can be nil, which indicates the output will not be spatial, but a spatial configuration with all nil values must be in the ``AVVideoComposition/spatialConfigurations`` property or an exception will be thrown.
- (void)attachSpatialVideoConfiguration:(nullable AVSpatialVideoConfiguration *)spatialVideoConfiguration toPixelBuffer:(CVPixelBufferRef)pixelBuffer NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);
@end

@class AVAsynchronousCIImageFilteringRequestInternal;
@class CIImage;
@class CIContext;

/// An AVAsynchronousCIImageFilteringRequest instance contains the information necessary for a filter to render an output CIImage.
#if __swift__
API_DEPRECATED("Use AVCIImageFilteringParameters instead", macos(10.11, API_TO_BE_DEPRECATED), ios(9.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos)
#else
API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
#endif
@interface AVAsynchronousCIImageFilteringRequest : NSObject <NSCopying> {
@private
	AVAsynchronousCIImageFilteringRequestInternal *_internal;
}

/// Width and height for rendering frames.
@property (nonatomic, readonly) CGSize renderSize;

/// The time for which the frame should be filtered
@property (nonatomic, readonly) CMTime compositionTime;

/// CIImage for the first enabled source video track. Unlike AVAsynchronousVideoCompositionRequest, renderContext.renderTransform is already applied to the source image.
@property (nonatomic, readonly) CIImage *sourceImage;

///Callback the filter should call when filtering succeeded. If context is nil then a default context will be used, GPU-accelerated if possible.
///
///It is safe to pass in the sourceImage in which case the filter will appear to have no effect, essentially functioning as a pass-through.
- (void)finishWithImage:(CIImage *)filteredImage context:(nullable CIContext *)context;

/// Callback the filter should call when filtering failed. The error parameter should describe the actual error.
- (void)finishWithError:(NSError *)error;

@end

/// The AVVideoCompositionInstruction protocol is implemented by objects to represent operations to be performed by a compositor. Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@protocol AVVideoCompositionInstruction<NSObject>

@required

/// Indicates the timeRange during which the instruction is effective. Note requirements for the timeRanges of instructions described in connection with AVVideoComposition's instructions key above.
@property (nonatomic, readonly) CMTimeRange timeRange;

/// If NO, indicates that post-processing should be skipped for the duration of this instruction.
/// See +[AVVideoCompositionCoreAnimationTool videoCompositionToolWithPostProcessingAsVideoLayer:inLayer:].
@property (nonatomic, readonly) BOOL enablePostProcessing;

/// If YES, rendering a frame from the same source buffers and the same composition instruction at 2 different compositionTime may yield different output frames. If NO, 2 such compositions would yield the same frame. The media pipeline may be able to avoid some duplicate processing when containsTweening is NO
@property (nonatomic, readonly) BOOL containsTweening;

/// List of video track IDs required to compose frames for this instruction. If the value of this property is nil, all source tracks will be considered required for composition
@property (nonatomic, readonly, nullable) NSArray<NSValue *> *requiredSourceTrackIDs;

/// If for the duration of the instruction, the video composition result is one of the source frames, this property should return the corresponding track ID. The compositor won't be run for the duration of the instruction and the proper source frame will be used instead. The dimensions, clean aperture and pixel aspect ratio of the source buffer will be matched to the required values automatically
@property (nonatomic, readonly) CMPersistentTrackID passthroughTrackID; // kCMPersistentTrackID_Invalid if not a passthrough instruction


@optional

/// List of sample data track IDs required to compose frames for this instruction.  An empty array indicates that no sample data is required for this instruction.
@property (nonatomic, readonly) NSArray<NSNumber *> *requiredSourceSampleDataTrackIDs API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);


@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVVideoCompositing.h>
#endif
