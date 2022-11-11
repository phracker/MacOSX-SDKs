#if !__has_include(<AVFCore/AVSynchronizedLayer.h>)
/*
	File:  AVSynchronizedLayer.h

	Framework:  AVFoundation
 
	Copyright 2010-2021 Apple Inc. All rights reserved.

*/

/*!
    @class			AVSynchronizedLayer

    @abstract		AVSynchronizedLayer is a subclass of CALayer with layer timing that synchronized with a specific AVPlayerItem.

	@discussion		Note that arbitrary numbers of AVSynchronizedLayers can be created with the same AVPlayerItem.
	
					An AVSynchronizedLayer is similar to a CATransformLayer in that it doesn't display anything itself but only
					confers state upon its layer subtree. AVSynchronizedLayer confers is timing state, synchronizing the
					timing of layers in its subtree with that of an AVPlayerItem.					

					Any CoreAnimation layer with animation property set that is added as a sublayer of AVSynchronizedLayer should 
					set animation beginTime to a non-zero positive value so animations will be interpreted on the AVPlayerItem's 
					timeline, not real-time. CoreAnimation replaces default beginTime of 0.0 with CACurrentMediaTime(). 
					To start the animation from time 0, use a small positive value like AVCoreAnimationBeginTimeAtZero.
					
					Set the removedOnCompletion property to NO on CAAnimations you attach to AVSynchronizedLayer or 
					its sublayers to prevent CoreAnimation from automatically removing them.

					Usage example:
					
					AVPlayerItem *playerItem = ...;
					
					// .. set up an AVSynchronizedLayer, to sync the layer timing of its subtree
					// with the playback of the playerItem
					
					CALayer *superlayer = ...;
					AVSynchronizedLayer *syncLayer = [AVSynchronizedLayer synchronizedLayerWithPlayerItem:playerItem];
					
					[syncLayer addSublayer:...];	// These sublayers will be synchronized
					
					[superlayer addSublayer:syncLayer];
*/

#import <AVFoundation/AVBase.h>

#if __has_include(<QuartzCore/CoreAnimation.h>)
#import <QuartzCore/CAAnimation.h>

@class AVPlayerItem;
@class AVSynchronizedLayerInternal;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVSynchronizedLayer : CALayer
{
@private
	AVSynchronizedLayerInternal		*_syncLayer;
}

/*!
	@method			synchronizedLayerWithPlayerItem:
	@abstract		Returns an instance of AVSynchronizedLayer with timing synchronized with the specified AVPlayerItem.
	@result			An instance of AVSynchronizedLayer.
*/
+ (AVSynchronizedLayer *)synchronizedLayerWithPlayerItem:(AVPlayerItem *)playerItem;

/*!
	@property		playerItem
	@abstract		Indicates the instance of AVPlayerItem to which the timing of the AVSynchronizedLayer is synchronized.
	@discussion		This property must be accessed on the main thread/queue.
*/
@property (nonatomic, retain, nullable) AVPlayerItem *playerItem NS_SWIFT_UI_ACTOR;

@end

NS_ASSUME_NONNULL_END

#endif  // __has_include(<QuartzCore/CoreAnimation.h>)

#else
#import <AVFCore/AVSynchronizedLayer.h>
#endif
