/*
	File:  AVVideoCompositing.h

	Framework:  AVFoundation
 
	Copyright 2013-2016 Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AVFoundation/AVBase.h>
#import <CoreVideo/CVPixelBufferPool.h>
#import <CoreMedia/CMTimeRange.h>

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

/*!
	@class		AVVideoCompositionRenderContext
 
	@abstract	The AVVideoCompositionRenderContext class defines the context within which custom compositors render new output pixels buffers.
 
	@discussion
		An instance of AVVideoCompositionRenderContext provides size and scaling information and offers a service for efficiently providing pixel buffers from a managed pool of buffers.
*/

@class AVVideoComposition;
@class AVAsynchronousVideoCompositionRequest;
@protocol AVVideoCompositionInstruction;

@class AVVideoCompositionRenderContextInternal;

API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVVideoCompositionRenderContext : NSObject {
@private
	AVVideoCompositionRenderContextInternal	*_internal;
}

/* indicates the width and height for rendering frames. */
@property (nonatomic, readonly) CGSize size;

/* Transform to apply to the source image to incorporate renderScale, pixelAspectRatio, edgeWidths.
   The coordinate system origin is the top left corner of the buffer. */
@property (nonatomic, readonly) CGAffineTransform renderTransform; // incorporates renderScale, pixelAspectRatio, edgeWidths

/* indicates a scaling ratio that should be applied when rendering frames. */
@property (nonatomic, readonly) float renderScale;

/* indicates the pixel aspect ratio for rendered frames. */
@property (nonatomic, readonly) AVPixelAspectRatio pixelAspectRatio;

/* indicates the thickness of the edge processing region on the left, top, right and bottom edges, in pixels. */
@property (nonatomic, readonly) AVEdgeWidths edgeWidths;

/* hints the custom compositor that it may use higher quality, potentially slower algorithms.
   Generally true for non real time use cases. */
@property (nonatomic, readonly) BOOL highQualityRendering;

/* The AVVideoComposition being rendered. */
@property (nonatomic, readonly) AVVideoComposition *videoComposition;

/*!
	@method			newPixelBuffer
	@abstract		Vends a CVPixelBuffer to use for rendering
	@discussion
					The buffer will have its kCVImageBufferCleanApertureKey and kCVImageBufferPixelAspectRatioKey attachments set to match the current composition processor properties.
					 
*/
- (nullable CVPixelBufferRef)newPixelBuffer CF_RETURNS_RETAINED; // caller must CFRelease

@end

/*!
	@class		AVVideoCompositionRenderHint
	@abstract	An AVVideoCompositionRenderHint instance contains the information necessary for announcing upcoming rendering request time ranges.
*/

@class AVVideoCompositionRenderHintInternal;

API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos)
@interface AVVideoCompositionRenderHint : NSObject {
@private
	AVVideoCompositionRenderHintInternal *_internal;
}

/*! The start time of the upcoming composition requests. */
@property (nonatomic, readonly) CMTime startCompositionTime;

/*! The end time of the upcoming composition requests. */
@property (nonatomic, readonly) CMTime endCompositionTime;

@end

/*!
	@protocol		AVVideoCompositing
	@abstract		Defines properties and methods for custom video compositors
	@discussion
		For each AVFoundation object of class AVPlayerItem, AVAssetExportSession, AVAssetImageGenerator, or AVAssetReaderVideoCompositionOutput that has a non-nil value for its videoComposition property, when the value of the customVideoCompositorClass property of the AVVideoComposition is not Nil, AVFoundation creates and uses an instance of that custom video compositor class to process the instructions contained in the AVVideoComposition. The custom video compositor instance will be created when you invoke -setVideoComposition: with an instance of AVVideoComposition that's associated with a different custom video compositor class than the object was previously using.

		When creating instances of custom video compositors, AVFoundation initializes them by calling -init and then makes them available to you for further set-up or communication, if any is needed, as the value of the customVideoCompositor property of the object on which -setVideoComposition: was invoked.

		Custom video compositor instances will then be retained by the AVFoundation object for as long as the value of its videoComposition property indicates that an instance of the same custom video compositor class should be used, even if the value is changed from one instance of AVVideoComposition to another instance that's associated with the same custom video compositor class.
*/
API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@protocol AVVideoCompositing<NSObject>

@required

/* Indicates the kinds of source frame pixel buffer attributes a video compositor can accept as input.
   The property is required to provide kCVPixelBufferPixelFormatTypeKey along with the attributes
   for which the compositor needs specific values to work properly. If the attribute kCVPixelBufferPixelFormatTypeKey
   is missing an exception will be raised. If the custom compositor is meant to be used with an AVVideoCompositionCoreAnimationTool
   created using the videoCompositionCoreAnimationToolWithAdditionalLayer constructor, kCVPixelFormatType_32BGRA 
   should be indicated as one of the supported pixel format types.
   Missing attributes will be set by the composition engine to values allowing the best performance.
   This property is queried once before any composition request is sent to the compositor. Changing
   source buffer attributes afterwards is not supported.
*/
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *sourcePixelBufferAttributes;

/* Indicates the pixel buffer attributes required by the video compositor for new buffers that it creates
 for processing. The property is required to provide kCVPixelBufferPixelFormatTypeKey along with attributes for which the compositor needs specific values to work properly. Omitted attributes will be supplied by the composition engine to allow for the best performance. If the attribute kCVPixelBufferPixelFormatTypeKey is missing an exception will be raised.
 The getter for requiredPixelBufferAttributesForRenderContext is typically invoked prior to the creation of
 a new render context; the combination of the attributes in the returned value and the additional attributes
 supplied by the composition engine will be used in the creation of subsequent render context's pixelBuffers.
 This property is queried once before any composition request is sent to the compositor. Changing
 required buffer attributes afterwards is not supported.
 */
@property (nonatomic, readonly) NSDictionary<NSString *, id> *requiredPixelBufferAttributesForRenderContext;

/*!
    @method			renderContextChanged:
	@abstract       Called to notify the custom compositor that a composition will switch to a different render context
	@param			newRenderContext
					The render context that will be handling the video composition from this point
    @discussion
					Instances of classes implementing the AVVideoComposting protocol can implement this method to be notified when
					the AVVideoCompositionRenderContext instance handing a video composition changes. AVVideoCompositionRenderContext instances
					being immutable, such a change will occur every time there is a change in the video composition parameters.
*/
- (void)renderContextChanged:(AVVideoCompositionRenderContext *)newRenderContext;

/*!
	@method			startVideoCompositionRequest:
	@abstract		Directs a custom video compositor object to create a new pixel buffer composed asynchronously from a collection of sources.
	@param			asyncVideoCompositionRequest
    				An instance of AVAsynchronousVideoCompositionRequest that provides context for the requested composition.
	@discussion
		The custom compositor is expected to invoke, either subsequently or immediately, either:
		-[AVAsynchronousVideoCompositionRequest finishWithComposedVideoFrame:] or
		-[AVAsynchronousVideoCompositionRequest finishWithError:]. If you intend to finish rendering the frame after your
		handling of this message returns, you must retain the instance of AVAsynchronousVideoCompositionRequest until after composition is finished.
		Note that if the custom compositor's implementation of -startVideoCompositionRequest: returns without finishing the composition immediately,
		it may be invoked again with another composition request before the prior request is finished; therefore in such cases the custom compositor should
		be prepared to manage multiple composition requests.

		If the rendered frame is exactly the same as one of the source frames, with no letterboxing, pillboxing or cropping needed,
		then the appropriate source pixel buffer may be returned (after CFRetain has been called on it).
*/
- (void)startVideoCompositionRequest:(AVAsynchronousVideoCompositionRequest *)asyncVideoCompositionRequest;

@optional

/*!
	@method			cancelAllPendingVideoCompositionRequests	
	@abstract		Directs a custom video compositor object to cancel or finish all pending video composition requests
	@discussion
		When receiving this message, a custom video compositor must block until it has either cancelled all pending frame requests,
		and called the finishCancelledRequest callback for each of them, or, if cancellation is not possible, finished processing of all the frames
		and called the finishWithComposedVideoFrame: callback for each of them.
*/
- (void)cancelAllPendingVideoCompositionRequests;

/*!
 @property supportsWideColorSourceFrames
 @abstract
	Indicates that clients can handle frames that contains wide color properties.
 
 @discussion 
	Controls whether the client will receive frames that contain wide color information. Care should be taken to avoid clamping.
 */
@property (nonatomic, readonly) BOOL supportsWideColorSourceFrames API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) API_UNAVAILABLE(watchos);

/*!
	@method			anticipateRenderingUsingHint:
	@abstract		Informs a custom video compositor about upcoming rendering requests.
	@param			renderHint
					Information about the upcoming composition requests.
	@discussion
		In the method the compositor can load composition resources such as overlay images which will be needed in the anticipated rendering time range.

		Unlike -startVideoCompositionRequest, which is invoked only when the frame compositing is necessary, the framework typically calls this method every frame duration. It allows the custom compositor to load and unload a composition resource such as overlay images at an appropriate timing.

		In forward playback, renderHint's startCompositionTime is less than endCompositionTime. In reverse playback, its endCompositionTime is less than startCompositionTime. For seeking, startCompositionTime == endCompositionTime, which means the upcoming composition request time range is unknown and the compositor shouldn’t preload time associated composition resources eagerly.

		The method is guaranteed to be called before -startVideoCompositionRequest: for a given composition time.

		The method is synchronous. The implementation should return quickly because otherwise the playback would stall and cause frame drops.
*/
- (void)anticipateRenderingUsingHint:(AVVideoCompositionRenderHint *)renderHint API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

/*!
	@method			prerollForRenderingUsingHint:
	@abstract		Tell a custom video compositor to perform any work in prerolling phase.
	@param			renderHint
					Information about the upcoming composition requests.
	@discussion
		The framework may perform prerolling to load media data to prime the render pipelines for smoother playback. This method is called in the prerolling phase so that the compositor can load composition resources such as overlay images which will be needed as soon as the playback starts.

		Not all rendering scenarios use prerolling. For example, the method won't be called while seeking.

		If called, the method is guaranteed to be invoked before the first -startVideoCompositionRequest: call.

		The method is synchronous. The prerolling won't finish until the method returns.
*/
-(void)prerollForRenderingUsingHint:(AVVideoCompositionRenderHint *)renderHint API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

@end

/*!
	@class		AVAsynchronousVideoCompositionRequest
 
	@abstract	An AVAsynchronousVideoCompositionRequest instance contains the information necessary for a video compositor to render an output pixel buffer. The video compositor must implement the AVVideoCompositing protocol.
*/

@class AVAsynchronousVideoCompositionRequestInternal;

API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVAsynchronousVideoCompositionRequest : NSObject <NSCopying> {
@private
	AVAsynchronousVideoCompositionRequestInternal *_internal;
}

/* The AVVideoCompositionRenderContext making the request */
@property (nonatomic, readonly) AVVideoCompositionRenderContext *renderContext;

/* The time for which the frame should be composed */
@property (nonatomic, readonly) CMTime compositionTime;

/* Track ID of all the source buffers that are available to compose the frame. */
@property (nonatomic, readonly) NSArray<NSNumber *> *sourceTrackIDs;

/* The AVVideoCompositionInstruction to use to compose the frame. */
@property (nonatomic, readonly) id<AVVideoCompositionInstruction> videoCompositionInstruction;

/*!
    @method			sourceFrameByTrackID:
	@abstract       Returns the source CVPixelBufferRef for the given track ID
	@param			trackID
					The track ID for the requested source frame
*/
- (nullable CVPixelBufferRef)sourceFrameByTrackID:(CMPersistentTrackID)trackID CF_RETURNS_NOT_RETAINED;

/* callback the custom compositor should call when composition succeeded */
- (void)finishWithComposedVideoFrame:(CVPixelBufferRef)composedVideoFrame;

/* callback the custom compositor should call when composition failed. The error parameter should describe the actual error. */
- (void)finishWithError:(NSError *)error;

/* callback the custom compositor should call for a request that has been cancelled. */
- (void)finishCancelledRequest;

@end

/*!
	@class		AVAsynchronousCIImageFilteringRequest
 
	@abstract	An AVAsynchronousCIImageFilteringRequest instance contains the information necessary for a filter to render an output CIImage.
*/

@class AVAsynchronousCIImageFilteringRequestInternal;
@class CIImage;
@class CIContext;

API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVAsynchronousCIImageFilteringRequest : NSObject <NSCopying> {
@private
	AVAsynchronousCIImageFilteringRequestInternal *_internal;
}

/* Width and height for rendering frames. */
@property (nonatomic, readonly) CGSize renderSize;

/* The time for which the frame should be filtered */
@property (nonatomic, readonly) CMTime compositionTime;

/* CIImage for the first enabled source video track. The pixel format will be kCIFormatBGRA8 (kCVPixelFormatType_32BGRA). Unlike AVAsynchronousVideoCompositionRequest, renderContext.renderTransform is already applied to the source image. */
@property (nonatomic, readonly) CIImage *sourceImage;

/*
Callback the filter should call when filtering succeeded. The pixel format of the filteredImage must be kCIFormatBGRA8 (kCVPixelFormatType_32BGRA). If context is nil then a default context will be used, GPU-accelerated if possible.

It is safe to pass in the sourceImage in which case the filter will appear to have no effect, essentially functioning as a pass-through.
*/
- (void)finishWithImage:(CIImage *)filteredImage context:(nullable CIContext *)context;

/* Callback the filter should call when filtering failed. The error parameter should describe the actual error. */
- (void)finishWithError:(NSError *)error;

@end


/*!
	@protocol	AVVideoCompositionInstruction
 
	@abstract	The AVVideoCompositionInstruction protocol is implemented by objects to represent operations to be performed by a compositor.
*/
API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@protocol AVVideoCompositionInstruction<NSObject>

@required

/* Indicates the timeRange during which the instruction is effective. Note requirements for the timeRanges of instructions described in connection with AVVideoComposition's instructions key above. */
@property (nonatomic, readonly) CMTimeRange timeRange;

/* If NO, indicates that post-processing should be skipped for the duration of this instruction.
   See +[AVVideoCompositionCoreAnimationTool videoCompositionToolWithPostProcessingAsVideoLayer:inLayer:].*/
@property (nonatomic, readonly) BOOL enablePostProcessing;

/* If YES, rendering a frame from the same source buffers and the same composition instruction at 2 different
   compositionTime may yield different output frames. If NO, 2 such compositions would yield the
   same frame. The media pipeline may me able to avoid some duplicate processing when containsTweening is NO */
@property (nonatomic, readonly) BOOL containsTweening;

/* List of video track IDs required to compose frames for this instruction. If the value of this property is nil, all source tracks will be considered required for composition */
@property (nonatomic, readonly, nullable) NSArray<NSValue *> *requiredSourceTrackIDs;

/* If for the duration of the instruction, the video composition result is one of the source frames, this property should
   return the corresponding track ID. The compositor won't be run for the duration of the instruction and the proper source
   frame will be used instead. The dimensions, clean aperture and pixel aspect ratio of the source buffer will be
   matched to the required values automatically */
@property (nonatomic, readonly) CMPersistentTrackID passthroughTrackID; // kCMPersistentTrackID_Invalid if not a passthrough instruction

@end

NS_ASSUME_NONNULL_END
