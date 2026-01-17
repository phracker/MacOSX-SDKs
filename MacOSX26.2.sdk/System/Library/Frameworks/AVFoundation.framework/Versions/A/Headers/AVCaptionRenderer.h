#if !__has_include(<AVFCore/AVCaptionRenderer.h>)
/*
	File:  AVCaptionRenderer.h

	Framework:  AVFoundation
 
	Copyright 2016-2023 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#if ( TARGET_OS_OSX || ( TARGET_OS_IOS && ! TARGET_OS_VISION ) )

#import <Foundation/Foundation.h>
#import <AVFoundation/AVCaption.h>
#import <QuartzCore/QuartzCore.h>
#import <AVFoundation/AVTextStyleRule.h>

NS_ASSUME_NONNULL_BEGIN

@class AVCaptionRendererScene;
@class AVCaptionRendererInternal;

#pragma mark --- AVCaptionRenderer ---

/*!
 @class AVCaptionRenderer
 @abstract
	An instance of AVCaptionRenderer represents a service that can render the captions for a particular time
 @discussion
	An instance of AVCaptionRenderer performs drawing of a caption "scene" from a population of captions given a time. If there are no captions or no captions at the specified time, "emptiness" will still be drawn (e.g., flood filling with zero alpha or a color).
 */
NS_SWIFT_NONSENDABLE
API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos)
@interface AVCaptionRenderer : NSObject
{
@private
	AVCaptionRendererInternal * _internal;
}

/*!
 @property captions
 @abstract
	A NSArray holding captions to consider for rendering.
 @discussion
	This is the array of AVCaptions to consider when drawing. The array can contain no captions.
 */
@property (nonatomic, copy) NSArray<AVCaption *> * captions;

/*!
 @property bounds
 @abstract
	A CGRect holding bounds for the drawing of caption scene(s).
 @discussion
	This is a CGRect indicating where captions are drawn using renderInContext:atTime: Once established, this CGRect is used in each call to renderInContext:atTime: until it is changed to another value. This should be set up earlier than drawing.
 */
@property (nonatomic) CGRect bounds;

/*!
 @method		captionSceneChangesInRange:
 @abstract		Determine render time ranges within an enclosing time range to account for visual changes among captions.
 @result		An NSArray of AVCaptionRendererScenes; perhaps empty if there are no captions intersecting with the consideredTimeRange
 @discussion	
	This is an optional service useful for optimizing drawing. A client can perform drawing without it.
 
	As captions may become active and inactive throughout the timeline, this method will return a NSArray holding scene objects with time ranges on whose edges there's a visual change. The client can use the ranges of time between these edges with -renderInContext:atTime: to ensure all visual changes are rendered. The returned time ranges consider activation/deactivation of captions, temporal overlapping, and intra-caption timing requirements (e.g., character reveal animations). Time ranges may be returned where no captions are active as this is also a change in the caption "scene".
				
	The returned NSArray contains AVCaptionRendererScenes, each holding the CMTimeRange of that scene but potentially other information that may be useful to the client during renderering.
				
	The consideredTimeRange parameter is a CMTimeRange expressing the limits for consideration. The extent of this range does not need to correspond to the timing of captions. It might be the range from 0 to some duration. For efficiency, the range can be limited to a window of time. It is also possible to use the range anchored at a time and extending in the direction of playback.
 */
- (NSArray<AVCaptionRendererScene *> *)captionSceneChangesInRange:(CMTimeRange)consideredTimeRange;


/*!
 @method		renderInContext:forTime:
 @abstract		Draw the captions corresponding to a time established by the AVCaptions to a CGContext.
 @discussion	Captions are drawn into the CGContextRef based upon their activation at the specified time. If there are no captions or no captions at the specified time, "emptiness" will still be drawn (e.g., flood filling with zero alpha or a color).
 */
- (void)renderInContext:(CGContextRef)ctx forTime:(CMTime)time;

@end

#pragma mark --- AVCaptionRendererScene ---

@class AVCaptionRendererSceneInternal;

/*!
 @class AVCaptionRendererScene
 @abstract
	An instance of AVCaptionRendererScene holds a time range and associated state indicating when the AVCaptionRenderer will draw different output.
 @discussion
	In rendering the timeline established by the captions referenced by an AVCaptionRenderer, there are considerations such as temporal overlapping of captions, the existence of captions and other graphical elements like regions, and whether captions may be animated (e.g., scrolling in regions, character reveal in a caption). To communicate to the AVCaptionRenderer client the minimal set of time ranges where there are any visual differences, AVCaptionRendererScenes can be requested from -[AVCaptionRenderer captionSceneChangesInRange:]. A client wanting to optimize drawing performance may use this timing information to draw scenes only once per scene. Alternatively, clients can ignore scenes and repeatedly call renderInContext:atTime: but this may have additional performance impact.
	
	Other information about the rendering of a caption scene can be communicated through the AVCaptionRendererScene. For example, if captions are animated, an AVCaptionRendererScene with the time range and an indication of the animation occurring will be returned. There should be no inference from the number of scenes to the number of captions. Even a single caption with internal animations in part of its duration could result in multiple AVCaptionRendererScenes being produced.
 
	Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos)
@interface AVCaptionRendererScene : NSObject <NSCopying>
{
@private
	AVCaptionRendererSceneInternal * _internal;
}
AV_INIT_UNAVAILABLE

/*!
 @property timeRange
 @abstract
	The time range during which new captions will not be introduced into or existing captions will be retired from the caption scene
 */
@property (nonatomic, readonly) CMTimeRange timeRange;

/*!
 @property hasActiveCaptions
 @abstract
	The scene contains one or more active captions. 
 @discussion
	Clients should not use this to restrict their drawing and should call renderInContext:atTime: to draw "emptiness". However, this information may be useful for purposes such as scrubbing to times where captions are present, skipping scenes in which no captions are present.
 */
@property (nonatomic, readonly) BOOL hasActiveCaptions;

/*!
 @property needsPeriodicRefresh
 @abstract
	The scene may have embedded animations or other state where periodic redrawing while playing through this scene is needed.
 @discussion
 	This property indicates if refreshing should occur if the client is progressing through the content. If the client is not progressing (i.e., it is treating playback as though the rate is 0.0), a single render at the current render time suffices. This property does not prescribe a refresh rate. A client is free to choose a refresh rate corresponding to rates of associated video frames or other timing appropriate for the client.
 */
@property (nonatomic, readonly) BOOL needsPeriodicRefresh;

@end


NS_ASSUME_NONNULL_END

#endif // ( TARGET_OS_OSX || ( TARGET_OS_IOS && ! TARGET_OS_VISION ) )


#else
#import <AVFCore/AVCaptionRenderer.h>
#endif
