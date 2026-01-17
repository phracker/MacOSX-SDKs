/*
	File:  AVPlayerLayer.h

	Framework:  AVFoundation
 
	Copyright 2010-2012 Apple Inc. All rights reserved.

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
#import <QuartzCore/CoreAnimation.h>

@class AVPlayer;
@class AVPlayerLayerInternal;

NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVPlayerLayer : CALayer
{
	AVPlayerLayerInternal		*_playerLayer;
}

/*!
	@method		layerWithPlayer:
	@abstract		Returns an instance of AVPlayerLayer to display the visual output of the specified AVPlayer.
	@result		An instance of AVPlayerLayer.
*/
+ (AVPlayerLayer *)playerLayerWithPlayer:(AVPlayer *)player;

/*! 
	@property		player
	@abstract		Indicates the instance of AVPlayer for which the AVPlayerLayer displays visual output
*/
@property (nonatomic, retain) AVPlayer *player;

/*!
	@property		videoGravity
	@abstract		A string defining how the video is displayed within an AVPlayerLayer bounds rect.
	@discusssion	Options are AVLayerVideoGravityResizeAspect, AVLayerVideoGravityResizeAspectFill 
 					and AVLayerVideoGravityResize. AVLayerVideoGravityResizeAspect is default. 
					See <AVFoundation/AVAnimation.h> for a description of these options.
 */
@property(copy) NSString *videoGravity;

/*!
	 @property		readyForDisplay
	 @abstract		Boolean indicating that the first video frame has been made ready for display for the current item of the associated AVPlayer.
	 @discusssion	Use this property as an indicator of when best to show or animate-in an AVPlayerLayer into view. 
					An AVPlayerLayer may be displayed, or made visible, while this propoerty is NO, however the layer will not have any 
					user-visible content until the value becomes YES. 
					This property remains NO for an AVPlayer currentItem whose AVAsset contains no enabled video tracks.
 */
@property(nonatomic, readonly, getter=isReadyForDisplay) BOOL readyForDisplay;

@end
