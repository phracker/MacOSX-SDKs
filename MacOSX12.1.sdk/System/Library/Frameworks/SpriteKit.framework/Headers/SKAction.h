/**
 @header
 
 Actions are executed by nodes in a scene in order to change the structure
 and/or content to which they are attached.
 
 @copyright 2011 Apple Inc. All rights reserved.
 
 */

#import <Foundation/Foundation.h>
#import <SpriteKit/SpriteKitBase.h>

@class SKNode;
@class SKTexture;

/** Adjust the timing of an action
 
 @enum SKActionTimingLinear Specifies linear pacing. Linear pacing causes an
 animation to occur evenly over its duration.
 @enum SKActionTimingEaseIn Specifies ease-in pacing. Ease-in pacing causes the
 animation to begin slowly, and then speed up as it progresses.
 @enum SKActionTimingEaseOut Specifies ease-out pacing. Ease-out pacing causes
 the animation to begin quickly, and then slow as it completes.
 @enum SKActionTimingEaseInEaseOut Specifies ease-in ease-out pacing. An
 ease-in ease-out animation begins slowly, accelerates through the middle
 of its duration, and then slows again before completing.
 */
typedef NS_ENUM(NSInteger, SKActionTimingMode) {
    SKActionTimingLinear,
    SKActionTimingEaseIn,
    SKActionTimingEaseOut,
    SKActionTimingEaseInEaseOut
} NS_ENUM_AVAILABLE(10_9, 7_0);

/**
 A custom timing function for SKActions. Input time will be linear 0.0-1.0
 over the duration of the action. Return values must be 0.0-1.0 and increasing
 and the function must return 1.0 when the input time reaches 1.0.
 */
typedef float (^SKActionTimingFunction)(float time);



/**
 An SKAction object is an action that is executed by a node in the scene.
 Actions are most often used to change the structure and content of the node to
 which they are attached, but can also make other changes to the scene. When
 the scene processes its nodes, actions associated with those nodes are evaluated.
 */

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT @interface SKAction : NSObject <NSCopying, NSSecureCoding>

/** The duration required to complete an action, in seconds. */
@property (nonatomic) NSTimeInterval duration;

/** The timing mode used to execute an action
 @see SKActionTimingMode
 */
@property (nonatomic) SKActionTimingMode timingMode;

/** When set, prodives a custom timing via a block. Applies after
 the 'timingMode' property is taken into account, defaults to nil
 @see SKActionTimingFunction
 */
@property (nonatomic) SKActionTimingFunction timingFunction API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/** A speed factor that modifies how fast an action runs. Default value is 1.0 */
@property (nonatomic) CGFloat speed;

/** Creates an action that reverses the behavior of another action
 
 @return This method always returns an action object; however, not all actions
 are reversible
 */
- (SKAction *)reversedAction;

@end

@interface SKAction (SKActions)

/** Creates an action that moves a node relative to its current position
 @param delta A vector that describes the change to apply to the node’s position
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)moveBy:(CGVector)delta duration:(NSTimeInterval)duration;
+ (SKAction *)moveByX:(CGFloat)deltaX y:(CGFloat)deltaY duration:(NSTimeInterval)duration;

/** Creates an action that moves a node to a new position
 @param location The coordinates for the node’s new position
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)moveTo:(CGPoint)location duration:(NSTimeInterval)duration;
+ (SKAction *)moveToX:(CGFloat)x duration:(NSTimeInterval)duration;
+ (SKAction *)moveToY:(CGFloat)y duration:(NSTimeInterval)duration;

/** Creates an action that rotates the node by a relative value
 @param radians The amount to rotate the node, in radians
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)rotateByAngle:(CGFloat)radians duration:(NSTimeInterval)duration;

/** Creates an action that rotates the node counterclockwise to an absolute angle
 @param radians The angle to rotate the node to, in radians
 @param duration The duration of the animation
 */
+ (SKAction *)rotateToAngle:(CGFloat)radians duration:(NSTimeInterval)duration;

/** Creates an action that rotates the node to an absolute value
 @param radians The angle to rotate the node to, in radians
 @param duration The duration of the animation, in seconds
 @param shortestUnitArc If YES, then the rotation is performed in whichever
 direction results in the smallest rotation. If NO, then the rotation
 is interpolated
 */
+ (SKAction *)rotateToAngle:(CGFloat)radians duration:(NSTimeInterval)duration shortestUnitArc:(BOOL)shortestUnitArc;

/** Creates an action that adjusts the size of a sprite
 @param width The amount to add to the sprite’s width
 @param height The amount to add to the sprite’s height
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)resizeByWidth:(CGFloat)width height:(CGFloat)height duration:(NSTimeInterval)duration;

/** Creates an action that changes the width and height of a sprite to a new absolute value
 @param width The new width of the sprite
 @param height The new height of the sprite
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)resizeToWidth:(CGFloat)width height:(CGFloat)height duration:(NSTimeInterval)duration;
+ (SKAction *)resizeToWidth:(CGFloat)width duration:(NSTimeInterval)duration;
+ (SKAction *)resizeToHeight:(CGFloat)height duration:(NSTimeInterval)duration;

/** Creates an action that changes the x and y scale values of a node by a relative value
 @param scale The amount to modify to the node’s x and y scale values
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)scaleBy:(CGFloat)scale duration:(NSTimeInterval)duration;
+ (SKAction *)scaleXBy:(CGFloat)xScale y:(CGFloat)yScale duration:(NSTimeInterval)duration;

/** Creates an action that changes the x and y scale values of a node by a relative value
 @param scale The new value for the node’s x and y scale values
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)scaleTo:(CGFloat)scale duration:(NSTimeInterval)duration;
+ (SKAction *)scaleXTo:(CGFloat)xScale y:(CGFloat)yScale duration:(NSTimeInterval)duration;
+ (SKAction *)scaleXTo:(CGFloat)scale duration:(NSTimeInterval)duration;
+ (SKAction *)scaleYTo:(CGFloat)scale duration:(NSTimeInterval)duration;

/**
 Adjust the sprite's xScale & yScale to achieve the desired size (in parent's coordinate space)
 @param duration The duration of the animation, in seconds
*/
+ (SKAction *)scaleToSize:(CGSize)size duration:(NSTimeInterval)duration API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

/** Creates an action that runs a collection of actions sequentially
 @param actions An array of SKAction objects
 
 @discussion When the action executes, the first action in the sequence starts
 and runs to completion. Subsequent actions in the sequence run in a
 similar fashion until all of the actions in the sequence have executed.
 The duration of the sequence action is the sum of the durations of the
 actions in the sequence.
 
 This action is reversible; it creates a new sequence action that reverses
 the order of the actions. Each action in the reversed sequence is itself
 reversed. For example, if an action sequence is {1,2,3}, the reversed
 sequence would be {3R,2R,1R}.
 */
+ (SKAction *)sequence:(NSArray<SKAction*> *)actions;

/** Creates an action that runs a collection of actions concurrently
 @param actions An array of SKAction objects
 
 @discussion When the action executes, the actions that comprise the group
 all start immediately and run in parallel. The duration of the group
 action is the longest duration among the collection of actions. If an
 action in the group has a duration less than the group’s duration, the
 action completes, then idles until the group completes the remaining
 actions. This matters most when creating a repeating action that repeats
 a group.
 */
+ (SKAction *)group:(NSArray<SKAction*> *)actions;

/** Creates an action that repeats another action a specified number of times
 @param action The action to execute
 @param count The number of times to execute the action
 */
+ (SKAction *)repeatAction:(SKAction *)action count:(NSUInteger)count;

/** Creates an action that repeats forever
 @param action The action to execute
 */
+ (SKAction *)repeatActionForever:(SKAction *)action;

/** Creates an action that changes the alpha value of the node to 1.0
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)fadeInWithDuration:(NSTimeInterval)duration;

/** Creates an action that changes the alpha value of the node to 0.0
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)fadeOutWithDuration:(NSTimeInterval)duration;

/** Creates an action that adjusts the alpha value of a node by a relative value
 @param factor The amount to modify the node’s alpha value
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)fadeAlphaBy:(CGFloat)factor duration:(NSTimeInterval)duration;

/** Creates an action that adjusts the alpha value of a node to a new value
 @param alpha The new value of the node’s alpha
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)fadeAlphaTo:(CGFloat)alpha duration:(NSTimeInterval)duration;

/** Creates an action that hides a node */
+ (SKAction *)hide API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/** Creates an action that unhides a node */
+ (SKAction *)unhide API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/** Creates an action that changes a sprite’s texture
 @param texture The new texture to use on the sprite
 */
+ (SKAction *)setTexture:(SKTexture *)texture API_AVAILABLE(ios(7.1), tvos(7.1), watchos(1.0), macos(10.10));
+ (SKAction *)setNormalTexture:(SKTexture *)texture API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));;

/** Creates an action that changes a sprite’s texture, possibly resizing the sprite
 @param texture The new texture to use on the sprite
 @param resize If YES, the sprite is resized to match the new texture.
 If NO, the size of the sprite is unchanged.
 */
+ (SKAction *)setTexture:(SKTexture *)texture resize:(BOOL)resize API_AVAILABLE(ios(7.1), tvos(7.1), watchos(1.0), macos(10.10));
+ (SKAction *)setNormalTexture:(SKTexture *)texture resize:(BOOL)resize API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

/** Creates an action that animates changes to a sprite’s texture
 @param textures An array of textures to use when animating a sprite
 @param sec The amount of time that each texture is displayed
 */
+ (SKAction *)animateWithTextures:(NSArray<SKTexture*> *)textures timePerFrame:(NSTimeInterval)sec;
+ (SKAction *)animateWithNormalTextures:(NSArray<SKTexture*> *)textures timePerFrame:(NSTimeInterval)sec API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

/** Creates an action that animates changes to a sprite’s texture
 @param textures An array of textures to use when animating a sprite
 @param sec The amount of time that each texture is displayed
 @param resize If YES, the sprite is resized to match each new texture.
 If NO, the size of the sprite remains at a constant size.
 @param restore If YES, When the action completes, the sprite’s texture is restored
 to the texture it had before the action completed. (If the
 resize parameter is YES, the sprite is resized to match the
 size of the original texture.
 If NO, when the action completes the sprite’s texture remains
 set to the final texture in the array.
 */
+ (SKAction *)animateWithTextures:(NSArray<SKTexture*> *)textures timePerFrame:(NSTimeInterval)sec resize:(BOOL)resize restore:(BOOL)restore;
+ (SKAction *)animateWithNormalTextures:(NSArray<SKTexture*> *)textures timePerFrame:(NSTimeInterval)sec resize:(BOOL)resize restore:(BOOL)restore API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

/** Creates an action that plays a sound
 @param soundFile The name of a sound file in the app’s bundle
 @param wait If YES, then the duration of this action is the same
 as the length of the audio playback. If NO, the action is considered
 to have completed immediately.
 
 @discussion The file name must be the name or path of a file of a platform
 supported audio file format. Use a LinearPCM format audio file with 8 or 16 bits
 per channel for best performance */
+ (SKAction *)playSoundFileNamed:(NSString*)soundFile waitForCompletion:(BOOL)wait;

/** Creates an animation that animates a sprite’s color and blend factor
 @param color The new color for the sprite
 @param colorBlendFactor The new blend factor for the sprite
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)colorizeWithColor:(SKColor *)color colorBlendFactor:(CGFloat)colorBlendFactor duration:(NSTimeInterval)duration;
+ (SKAction *)colorizeWithColorBlendFactor:(CGFloat)colorBlendFactor duration:(NSTimeInterval)sec;

/** Creates an action that sets the falloff of a field
 @param falloff The new value for falloff
 @param duration The duration of the animation, in seconds
 @see SKFieldNode
 */
+ (SKAction *)falloffTo:(float)falloff duration:(NSTimeInterval)duration API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/** Creates an action that sets the falloff of a field
 @param falloff The value to modify falloff by
 @param duration The duration of the animation, in seconds
 @see SKFieldNode
 */
+ (SKAction *)falloffBy:(float)falloff duration:(NSTimeInterval)duration API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));


/** Creates an action that moves the node along a relative path, orienting the
 node to the path
 
 @param path A Core Graphics path whose coordinates are relative to the node’s
 current position
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)followPath:(CGPathRef)path duration:(NSTimeInterval)duration;

/** Creates an action that moves the node along a path
 
 @param path A Core Graphics path whose coordinates are relative to the node’s
 current position
 @param offset If YES, the points in the path are relative offsets to the
 node’s starting position. If NO, the points in the node are absolute
 coordinate values.
 @param orient If YES, the node’s zRotation property animates so that
 the node turns to follow the path. If NO, the zRotation property of
 the node is unchanged.
 @param duration The duration of the animation
 */
+ (SKAction *)followPath:(CGPathRef)path asOffset:(BOOL)offset orientToPath:(BOOL)orient duration:(NSTimeInterval)duration;

/** Creates an action that moves the node along a relative path, orienting the
 node to the path
 
 @param path A Core Graphics path whose coordinates are relative to the node’s
 current position
 @param speed The speed in pixels per second to move along the path
 */
+ (SKAction *)followPath:(CGPathRef)path speed:(CGFloat)speed;
+ (SKAction *)followPath:(CGPathRef)path asOffset:(BOOL)offset orientToPath:(BOOL)orient speed:(CGFloat)speed;

/** Creates an action that changes how fast the node executes actions by a
 relative value
 @param speed amount to modify the speed by
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)speedBy:(CGFloat)speed duration:(NSTimeInterval)duration;

/** Creates an action that changes how fast the node executes actions
 @param speed The new value for the node’s speed
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)speedTo:(CGFloat)speed duration:(NSTimeInterval)duration;

/** Creates an action that performs an inverse kinematic reach.
 This action must be run on a descendent of the rootNode for animation to occur.
 Running this action on the rootNode itself will not cause any animation to occur.
 @param position The position (in screen space) to reach for
 @param root Where to start the inverse kinematic operation from
 @param duration The duration of the animation, in seconds
 */
+ (SKAction *)reachTo:(CGPoint)position rootNode:(SKNode *)root duration:(NSTimeInterval)duration API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/** Creates an action that performs an inverse kinematic reach.
 This action must be run on a descendent of the rootNode for animation to occur.
 Running this action on the rootNode itself will not cause any animation to occur.
 @param position The position (in screen space) to reach for
 @param root Where to start the inverse kinematic operation from
 @param velocity The speed in points per second of the end node in the chain
 */
+ (SKAction *)reachTo:(CGPoint)position rootNode:(SKNode *)root velocity:(CGFloat)velocity API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/** Creates an action that performs an inverse kinematic reach.
 This action must be run on a descendent of the rootNode for animation to occur.
 Running this action on the rootNode itself will not cause any animation to occur.
 @param node The node to reach for
 @param root Where to start the inverse kinematic operation from
 @param sec The duration of the animation, in seconds
 */
+ (SKAction *)reachToNode:(SKNode *)node rootNode:(SKNode *)root duration:(NSTimeInterval)sec API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/** Creates an action that performs an inverse kinematic reach.
 This action must be run on a descendent of the rootNode for animation to occur.
 Running this action on the rootNode itself will not cause any animation to occur.
 @param node The node to reach for
 @param root Where to start the inverse kinematic operation from
 @param velocity The speed in points per second of the end node in the chain
 */
+ (SKAction *)reachToNode:(SKNode *)node rootNode:(SKNode *)root velocity:(CGFloat)velocity API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/** Creates an action that sets the strength of a field
 @param strength The new value for strength
 @param duration The duration of the animation, in seconds
 @see SKFieldNode
 */
+ (SKAction *)strengthTo:(float)strength duration:(NSTimeInterval)duration API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/** Creates an action that sets the strength of a field
 @param strength The value to modify strength by
 @param duration The duration of the animation, in seconds
 @see SKFieldNode
 */
+ (SKAction *)strengthBy:(float)strength duration:(NSTimeInterval)duration API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/** Creates an action that idles for a specified period of time
 @param duration The duration of the idle, in seconds
 */
+ (SKAction *)waitForDuration:(NSTimeInterval)duration;

/** Creates an action that idles for a randomized period of time
 @param duration The duration of the idle, in seconds
 @param durationRange The range of possible values for the duration
 */
+ (SKAction *)waitForDuration:(NSTimeInterval)duration withRange:(NSTimeInterval)durationRange;

/** Creates an action that removes the node from its parent */
+ (SKAction *)removeFromParent;

/** Creates an action that calls a method on an object
 @param selector The selector of the method to call
 @param target The target object
 */
+ (SKAction *)performSelector:(SEL)selector onTarget:(id)target;

/** Creates an action that executes a block
 @param block The block to run
 */
+ (SKAction *)runBlock:(dispatch_block_t)block;

/** Creates an action that executes a block
 @param block The block to run
 @param queue The queue to perform the action on
 */
+ (SKAction *)runBlock:(dispatch_block_t)block queue:(dispatch_queue_t)queue;

/** Creates an action that runs an action on a named child object
 @param action the action to run
 @param name the name of a child object
 @see SKNode.name
 */
+ (SKAction *)runAction:(SKAction *)action onChildWithName:(NSString*)name;

/** Creates an action that executes a block over a duration
 @param duration The duration of the animation, in seconds
 @param block The block to run. The block takes the following parameters:
 node The node on which the action is running.
 elapsedTime The amount of time that has passed in the animation.
 */
+ (SKAction *)customActionWithDuration:(NSTimeInterval)duration actionBlock:(void (^)(SKNode *node, CGFloat elapsedTime))block;

/** Creates an action of the given name from an action file.
 @param name The name of the action
 */
+ (nullable SKAction *)actionNamed:(NSString *)name API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

/** Creates an action of the given name from an action file with a new duration.
 @param name The name of the action
 @param duration The duration of the action
 */
+ (nullable SKAction *)actionNamed:(NSString *)name duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

/** Creates an action of the given name from an action file.
 @param name The name of the action
 @param url The url of the file containing the action
 */
+ (nullable SKAction *)actionNamed:(NSString *)name fromURL:(NSURL *)url API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

/** Creates an action of the given name from an action file with a new duration.
 @param name The name of the action
 @param url The url of the file containing the action
 @param duration The duration of the action
 */
+ (nullable SKAction *)actionNamed:(NSString *)name fromURL:(NSURL *)url duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

@end

@interface SKAction (NodeWithPhysicsBody)

+ (SKAction *)changeChargeTo:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));
+ (SKAction *)changeChargeBy:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

+ (SKAction *)changeMassTo:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));
+ (SKAction *)changeMassBy:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

+ (SKAction *)applyForce:(CGVector)force duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));;
+ (SKAction *)applyForce:(CGVector)force atPoint:(CGPoint)point duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

+ (SKAction *)applyTorque:(CGFloat)torque duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

+ (SKAction *)applyImpulse:(CGVector)impulse duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));
+ (SKAction *)applyImpulse:(CGVector)impulse atPoint:(CGPoint)point duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

+ (SKAction *)applyAngularImpulse:(CGFloat)impulse duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));;

@end

@interface SKAction (PlaybackControl)

+ (SKAction *)play API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));
+ (SKAction *)pause API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));
+ (SKAction *)stop API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

+ (SKAction *)changePlaybackRateTo:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));;
+ (SKAction *)changePlaybackRateBy:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));;

@end

@interface SKAction (MixerControl)

+ (SKAction *)changeVolumeTo:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));;
+ (SKAction *)changeVolumeBy:(float)v duration:(NSTimeInterval)duration API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));;

@end

NS_ASSUME_NONNULL_END
