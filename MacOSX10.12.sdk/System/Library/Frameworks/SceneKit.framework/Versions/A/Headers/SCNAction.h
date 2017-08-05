//
//  SCNAction.h
//
//  Copyright (c) 2014-2015 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;
@class SCNAction;
@class SCNAudioSource;

/*! @enum SCNActionTimingMode
 @abstract The modes that an action can use to adjust the apparent timing of the action.
 */
typedef NS_ENUM(NSInteger, SCNActionTimingMode) {
    SCNActionTimingModeLinear,
    SCNActionTimingModeEaseIn,
    SCNActionTimingModeEaseOut,
    SCNActionTimingModeEaseInEaseOut
} NS_ENUM_AVAILABLE(10_10, 8_0);

/**
 A custom timing function for SCNActions. Input time will be between 0.0 and 1.0
 over the duration of the action. Return values must be 0.0-1.0 and increasing
 and the function must return 1.0 when the input time reaches 1.0.
 */
typedef float (^SCNActionTimingFunction)(float time);

@protocol SCNActionable <NSObject>

/*!
 @method runAction:
 @abstract Adds an action to the list of actions executed by the node.
 */
- (void)runAction:(SCNAction *)action NS_AVAILABLE(10_10, 8_0);

/*!
 @method runAction:completionHandler:
 @abstract Adds an action to the list of actions executed by the node. Your block is called when the action completes.
 */
- (void)runAction:(SCNAction *)action completionHandler:(nullable void (^)())block NS_AVAILABLE(10_10, 8_0);

/*!
 @method runAction:forKey:
 @abstract Adds an identifiable action to the list of actions executed by the node.
 */
- (void)runAction:(SCNAction *)action forKey:(nullable NSString *)key NS_AVAILABLE(10_10, 8_0);

/*!
 @method runAction:forKey:completionHandler:
 @abstract Adds an identifiable action to the list of actions executed by the node. Your block is called when the action completes.
 */
- (void)runAction:(SCNAction *)action forKey:(nullable NSString *)key completionHandler:(nullable void (^)())block NS_AVAILABLE(10_10, 8_0);

/*!
 @method hasActions
 @abstract Returns a Boolean value that indicates whether the node is executing actions.
 */
@property(nonatomic, readonly) BOOL hasActions NS_AVAILABLE(10_10, 8_0);

/*!
 @method actionForKey:
 @abstract Returns an action associated with a specific key.
 */
- (nullable SCNAction *)actionForKey:(NSString *)key NS_AVAILABLE(10_10, 8_0);

/*!
 @method removeActionForKey:
 @abstract Removes an action associated with a specific key.
 */
- (void)removeActionForKey:(NSString *)key NS_AVAILABLE(10_10, 8_0);

/*!
 @method removeAllActions
 @abstract Ends and removes all actions from the node.
 */
- (void)removeAllActions NS_AVAILABLE(10_10, 8_0);

/*!
 @method actionKeys
 @abstract Returns an array containing the keys of all actions currently attached to the receiver.
 */
@property(nonatomic, readonly) NSArray<NSString *> *actionKeys NS_AVAILABLE(10_10, 8_0);

@end


NS_CLASS_AVAILABLE(10_10, 8_0)
@interface SCNAction : NSObject <NSCopying, NSSecureCoding>

/*!
 @property duration
 @abstract This is the expected duration of an action’s animation. The actual time an action takes to complete is modified by the speed property of the action.
 */
@property(nonatomic) NSTimeInterval duration;

/*!
 @property timingMode
 @abstract The timing mode used to execute an action.
 */
@property(nonatomic) SCNActionTimingMode timingMode;

/** When set, prodives a custom timing via a block. Applies after
 the 'timingMode' property is taken into account, defaults to nil
 @see SCNActionTimingFunction
 */
@property(nonatomic, nullable) SCNActionTimingFunction timingFunction;

/*!
 @property speed
 @abstract A speed factor that modifies how fast an action runs. Defaults to 1.
 */
@property(nonatomic) CGFloat speed;

/*!
 @method reversedAction
 @abstract Creates an action that reverses the behavior of another action.
 */
- (SCNAction *)reversedAction;

//Creates an action that moves a node relative to its current position.
+ (SCNAction *)moveByX:(CGFloat)deltaX y:(CGFloat)deltaY z:(CGFloat)deltaZ duration:(NSTimeInterval)duration;
+ (SCNAction *)moveBy:(SCNVector3)delta duration:(NSTimeInterval)duration;

//Creates an action that moves a node to a new position.
+ (SCNAction *)moveTo:(SCNVector3)location duration:(NSTimeInterval)duration;

//Creates an action that rotates the node by a relative value.
+ (SCNAction *)rotateByX:(CGFloat)xAngle y:(CGFloat)yAngle z:(CGFloat)zAngle duration:(NSTimeInterval)duration;

//Creates an action that rotates the node to an absolute angle.
+ (SCNAction *)rotateToX:(CGFloat)xAngle y:(CGFloat)yAngle z:(CGFloat)zAngle duration:(NSTimeInterval)duration;
+ (SCNAction *)rotateToX:(CGFloat)xAngle y:(CGFloat)yAngle z:(CGFloat)zAngle duration:(NSTimeInterval)duration shortestUnitArc:(BOOL)shortestUnitArc;

//Creates an action that rotates the node arond an axis by the specified angle
+ (SCNAction *)rotateByAngle:(CGFloat)angle aroundAxis:(SCNVector3)axis duration:(NSTimeInterval)duration;
+ (SCNAction *)rotateToAxisAngle:(SCNVector4)axisAngle duration:(NSTimeInterval)duration;

//Creates an action that changes the x, y and z scale values of a node by a relative value.
+ (SCNAction *)scaleBy:(CGFloat)scale duration:(NSTimeInterval)sec;

//Creates an action that changes the x, y and z scale values of a node.
+ (SCNAction *)scaleTo:(CGFloat)scale duration:(NSTimeInterval)sec;

//Creates an action that runs a collection of actions sequentially.
+ (SCNAction *)sequence:(NSArray<SCNAction *> *)actions;

//Creates an action that runs a collection of actions in parallel.
+ (SCNAction *)group:(NSArray<SCNAction *> *)actions;

//Creates an action that repeats another action a specified number of times.
+ (SCNAction *)repeatAction:(SCNAction *)action count:(NSUInteger)count;

//Creates an action that repeats another action forever.
+ (SCNAction *)repeatActionForever:(SCNAction *)action;

//Creates an action that changes the opacity value of the node to 1.0
+ (SCNAction *)fadeInWithDuration:(NSTimeInterval)sec;

//Creates an action that changes the opacity value of the node to 0.0
+ (SCNAction *)fadeOutWithDuration:(NSTimeInterval)sec;

//Creates an action that adjusts the opacity value of a node by a relative value.
+ (SCNAction *)fadeOpacityBy:(CGFloat)factor duration:(NSTimeInterval)sec;

//Creates an action that adjusts the opacity value of a node to a new value.
+ (SCNAction *)fadeOpacityTo:(CGFloat)opacity duration:(NSTimeInterval)sec;

//Creates an action that hides a node
+ (SCNAction *)hide NS_AVAILABLE(10_11, 9_0);

//Creates an action that unhides a node
+ (SCNAction *)unhide NS_AVAILABLE(10_11, 9_0);

//Creates an action that idles for a specified period of time.
+ (SCNAction *)waitForDuration:(NSTimeInterval)sec;

//Creates an action that idles for a randomized period of time.
+ (SCNAction *)waitForDuration:(NSTimeInterval)sec withRange:(NSTimeInterval)durationRange;

//Creates an action that removes the node from its parent node.
+ (SCNAction *)removeFromParentNode;

//Creates an action that executes a block.
+ (SCNAction *)runBlock:(void (^)(SCNNode *node))block;
+ (SCNAction *)runBlock:(void (^)(SCNNode *node))block queue:(dispatch_queue_t)queue;

//Creates an action that runs a javascript script over a duration. the node can be accessed from javascript via the "node" symbol and the elapsed time (between 0 and 1 relative to the duration) via the "elapsedTime" symbol.
+ (SCNAction *)javaScriptActionWithScript:(NSString *)script duration:(NSTimeInterval)seconds;

//Creates an action that executes a block over a duration.
+ (SCNAction *)customActionWithDuration:(NSTimeInterval)seconds actionBlock:(void (^)(SCNNode *node, CGFloat elapsedTime))block;

/** Creates an action that plays a sound
 @param source The audio source to play (see SCNAudioSource.h)
 @param waitForCompletion If YES, then the duration of this action is the same
 as the length of the audio playback. If NO, the action is considered
 to have completed immediately.*/
+ (SCNAction *)playAudioSource:(SCNAudioSource *)source waitForCompletion:(BOOL)wait NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END
