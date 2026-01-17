//
//  SCNCAAnimationExtensions.h
//  SceneKit
//
//  Copyright © 2012-2020 Apple Inc. All rights reserved.
//

#import <SceneKit/SCNAnimation.h>

NS_ASSUME_NONNULL_BEGIN

@interface CAAnimation (SCNAnimation) <SCNAnimation>
@end

/*!
 @category CAAnimation (SceneKitAdditions)
 @abstract Extends the CAAnimation class for SceneKit explicit animations.
 */
@interface CAAnimation (SceneKitAdditions)

/*! 
 Bridge with SCNAnimation
*/
/**
 Initializes a CoreAnimation animation from a SCNAnimation
 */
+ (CAAnimation *)animationWithSCNAnimation:(SCNAnimation *)animation API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

/*!
 @property usesSceneTimeBase
 @abstract Determines whether the receiver is evaluated using the scene time or the system time. Defaults to NO.
 @discussion A scene-time based animation is evaluated using the "sceneTime" value of the renderer that renders the scene.
 */
@property BOOL usesSceneTimeBase;

/*!
 @property fadeInDuration
 @abstract Determines the receiver's fade-in duration.
 @discussion When the fadeInDuration is greater than zero, the effect of the animation progressively increase from 0% to 100% during the specified duration.
 */
@property CGFloat fadeInDuration API_AVAILABLE(macos(10.9));
 
/*!
 @property fadeOutDuration
 @abstract Determines the receiver's fade-out duration.
 @discussion When the fadeOutDuration is greater than zero, the effect of the animation progressively decrease from 100% to 0% at the end of the animation duration.
 */
@property CGFloat fadeOutDuration API_AVAILABLE(macos(10.9));

/*!
 @property animationEvents
 @abstract Specifies the animation events attached to the receiver.
 */
@property(nonatomic, copy, nullable) NSArray<SCNAnimationEvent *> *animationEvents API_AVAILABLE(macos(10.9));

@end

NS_ASSUME_NONNULL_END
