//
//  SCNConstraint.h
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

/*!
 @class SCNConstraint
 @abstract A SCNConstraint is an abstract class that represents a single constraint that can be applied to a node.
 */

SCENEKIT_CLASS_AVAILABLE(10_9, NA)
@interface SCNConstraint : NSObject <NSCopying, SCNAnimatable>
{
@protected
	id _constraintReserved;
}
@end

/*!
 @class SCNLookAtConstraint
 @abstract A SCNLookAtConstraint applies on a node's orientation so that it always look at another node.
 */

SCENEKIT_CLASS_AVAILABLE(10_9, NA)
@interface SCNLookAtConstraint : SCNConstraint
{
@private
	id _reserved;
}

/*!
 @method lookAtConstraintWithTarget:
 @abstract Creates and returns a SCNLookAtConstraint object with the specified target.
 @param target The target node to look at.
 */
+ (instancetype)lookAtConstraintWithTarget:(SCNNode *)target;

/*!
 @property target
 @abstract Defines the target node to look at.
 */
@property(nonatomic, readonly) SCNNode *target;

/*!
 @property gimbalLockEnabled
 @abstract Specifies whether the receiver enables the gimbal lock. Defaults to NO.
 @discussion Enabling the gimbal lock prevents the receiver from rotating the constrained node around to roll axis.
 */
@property(nonatomic) BOOL gimbalLockEnabled;

@end

/*!
 @class SCNTransformConstraint
 @abstract A SCNTransformConstraint applies on the transform of a node via a custom block.
 */
SCENEKIT_CLASS_AVAILABLE(10_9, NA)
@interface SCNTransformConstraint : SCNConstraint
{
@private
	id _reserved;
}

/*!
 @method transformConstraintInWorldSpace:withBlock:
 @abstract Creates and returns a SCNTransformConstraint object with the specified parameters.
 @param world Determines whether the constraint is evaluated in world or local space.
 @param block The custom block to call to evaluate the constraint.
 @discussion The node and its transform are passed to the block. The transform returned by the block will be used to render the node.
 */
+ (instancetype)transformConstraintInWorldSpace:(BOOL)world withBlock:(CATransform3D(^)(SCNNode *node, CATransform3D transform))block;

@end
