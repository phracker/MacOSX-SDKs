#if !__has_include(<AVFCore/AVPlayerLayer.h>)
/*
	File:  AVPlayerLayer.h

	Framework:  AVFoundation
 
	Copyright 2010-2017 Apple Inc. All rights reserved.

*/


/*!
    @class			AVPlayerLayer

    @abstract		AVPlayerLayer is a subclass of CALayer to which an AVPlayer can direct its visual output.

	@discussion		To create an AVPlayerLayer instance:
					
					AVPlayer *player = ...;
					// ... set up an AVPlayer
					
					CALayer *superlayer = ...;
					AVPlayerLayer *playerLayer = [AVPlayerLayer playerLayerWithPlayer:player];
 
					// ... set up the AVPlayerLayer's geometry. For example: set the AVPlayerLayer frame according to the presentationSize of the AVPlayer's currentItem.
					
					[superlayer addSublayer:playerLayer];
					
					AVPlayerLayer provides a property 'videoGravity' that defines how the video content is displayed within the AVPlayerLayer property 'bounds' rect. 
					The value for the @"contents" key of an AVPlayerLayer is opaque and effectively read-only.

					Note that during playback AVPlayer may compensate for temporal drift between its visual output
					and its audible output to one or more independently-clocked audio output devices by adjusting the timing of its
					associated AVPlayerLayers. The effects of these adjustments are usually very minute; however, clients that
					wish to remain entirely unaffected by such adjustments may wish to place other layers for which timing is
					important into indepedently timed subtrees of their layer trees.
*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVAnimation.h>

#if __has_include(<QuartzCore/CoreAnimation.h>)
#import <QuartzCore/CoreAnimation.h>

@class AVPlayer;
@class AVPlayerLayerInternal;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVPlayerLayer : CALayer
{
@private
	AVPlayerLayerInternal		*_playerLayer;
}

/*!
	@method		layerWithPlayer:
	@abstract		Returns an instance of AVPlayerLayer to display the visual output of the specified AVPlayer.
	@result		An instance of AVPlayerLayer.
*/
+ (AVPlayerLayer *)playerLayerWithPlayer:(nullable AVPlayer *)player;

/*! 
	@property		player
	@abstract		Indicates the instance of AVPlayer for which the AVPlayerLayer displays visual output
*/
@property (nonatomic, retain, nullable) AVPlayer *player;

/*!
	@property		videoGravity
	@abstract		A string defining how the video is displayed within an AVPlayerLayer bounds rect.
	@discusssion	Options are AVLayerVideoGravityResizeAspect, AVLayerVideoGravityResizeAspectFill 
 					and AVLayerVideoGravityResize. AVLayerVideoGravityResizeAspect is default. 
					See <AVFoundation/AVAnimation.h> for a description of these options.
 */
@property(copy) AVLayerVideoGravity videoGravity;

/*!
	 @property		readyForDisplay
	 @abstract		Boolean indicating that the first video frame has been made ready for display for the current item of the associated AVPlayer.
	 @discusssion	Use this property as an indicator of when best to show or animate-in an AVPlayerLayer into view. 
					An AVPlayerLayer may be displayed, or made visible, while this propoerty is NO, however the layer will not have any user-visible content until the value becomes YES. Note that if an animation is added to an AVPlayerLayer before it becomes readyForDisplay the video image displayed inside might not animate with the receiver.
					This property remains NO for an AVPlayer currentItem whose AVAsset contains no enabled video tracks.
 */
@property(nonatomic, readonly, getter=isReadyForDisplay) BOOL readyForDisplay;

/*!
	@property		videoRect
	@abstract		The current size and position of the video image as displayed within the receiver's bounds.
 */
@property (nonatomic, readonly) CGRect videoRect API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
	@property		pixelBufferAttributes
	@abstract		The client requirements for the visual output displayed in AVPlayerLayer during playback.  	
	@discussion		Pixel buffer attribute keys are defined in <CoreVideo/CVPixelBuffer.h>
 */
@property (nonatomic, copy, nullable) NSDictionary<NSString *, id> *pixelBufferAttributes API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

#endif  // __has_include(<QuartzCore/CoreAnimation.h>)

#else
#import <AVFCore/AVPlayerLayer.h>
#endif
