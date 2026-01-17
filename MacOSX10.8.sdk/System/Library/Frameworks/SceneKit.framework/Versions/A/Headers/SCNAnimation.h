//
//  SCNAnimation.h
//
//  Copyright 2012 Apple Inc. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

/*!
 @protocol SCNAnimatable
 @abstract The SCNAnimatable protocol defines an animatable property. Objects that implement this protocol can be animated through these methods.
*/
@protocol SCNAnimatable

/*!
 @method addAnimation:forKey:
 @abstract Add an animation.
 @param animation Added animation.
 @param key May be any string such that only one animation per unique key is added per animatable object. The nil pointer is a valid key.
 */
- (void)addAnimation:(CAAnimation *)animation forKey:(NSString *)key;

/*!
 @method removeAllAnimations
 @abstract Remove all animations.
 */
- (void)removeAllAnimations;

/*!
 @method removeAnimationForKey
 @abstract Remove the animation with the given identifier.
 @param key The identifier for the animation to remove.
 */
- (void)removeAnimationForKey:(NSString *)key;

/*!
 @method animationKeys
 @abstract Returns an array containing the keys of all animations currently attached to the receiver.
 */
- (NSArray *)animationKeys;

/*!
 @method animationForKey:
 @abstract Returns the animation with the given identifier
 @param key The identifier for the animation to retrieve.
 @discussion This will return nil if no such animation exists.
			 Attempting to modify any properties of the returned object will result in undefined behavior.
 */
- (CAAnimation *)animationForKey:(NSString *)key;

@end


/*!
 @category CAAnimation (CAAnimation)
 @abstract Extends the CAAnimation class for SceneKit explicit animations.
 */
@interface CAAnimation (SceneKitAdditions)

/*!
 @property usesSceneTimeBase
 @abstract Determines whether the receiver is evaluated using the scene time or the system time. Defaults to NO.
 @discussion A scene-time based animation is evaluated using the "currentTime" value of the renderer that renders the scene.
 */
@property BOOL usesSceneTimeBase;

@end
