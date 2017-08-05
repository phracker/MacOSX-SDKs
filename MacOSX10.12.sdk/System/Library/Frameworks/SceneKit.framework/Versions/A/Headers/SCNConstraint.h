//
//  SCNConstraint.h
//
//  Copyright (c) 2013-2016 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>
#import <SceneKit/SCNAnimation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;

/*!
 @class SCNConstraint
 @abstract A SCNConstraint is an abstract class that represents a single constraint that can be applied to a node.
 */

API_AVAILABLE(macosx(10.9))
@interface SCNConstraint : NSObject <NSCopying, NSSecureCoding, SCNAnimatable>

/*!
 @property influenceFactor
 @abstract Specifies the inflence factor of the receiver. Defaults to 1. Animatable
 */
@property(nonatomic) CGFloat influenceFactor API_AVAILABLE(macosx(10.10));

@end

/*!
 @class SCNLookAtConstraint
 @abstract A SCNLookAtConstraint applies on a node's orientation so that it always look at another node.
 */

API_AVAILABLE(macosx(10.9))
@interface SCNLookAtConstraint : SCNConstraint

/*!
 @method lookAtConstraintWithTarget:
 @abstract Creates and returns a SCNLookAtConstraint object with the specified target.
 @param target The target node to look at.
 */
+ (instancetype)lookAtConstraintWithTarget:(nullable SCNNode *)target;

/*!
 @property target
 @abstract Defines the target node to look at.
 */
@property(nonatomic, retain, nullable) SCNNode *target;
- (nullable SCNNode *)target;
- (void)setTarget:(nullable SCNNode *)target API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @property gimbalLockEnabled
 @abstract Specifies whether the receiver enables the gimbal lock. Defaults to NO.
 @discussion Enabling the gimbal lock prevents the receiver from rotating the constrained node around to roll axis.
 */
@property(nonatomic) BOOL gimbalLockEnabled;

@end

typedef NS_OPTIONS(NSUInteger, SCNBillboardAxis) {
    SCNBillboardAxisX = 0x1 << 0,
    SCNBillboardAxisY = 0x1 << 1,
    SCNBillboardAxisZ = 0x1 << 2,
    SCNBillboardAxisAll = SCNBillboardAxisX | SCNBillboardAxisY | SCNBillboardAxisZ
};

API_AVAILABLE(macosx(10.11), ios(9.0))
@interface SCNBillboardConstraint : SCNConstraint

/*!
 @method billboardConstraint:
 @abstract Creates and returns a SCNBillboardConstraint constraint.
 @discussion A billboard constraint forces the receiver to look into the direction of the current point of view.
 */
+ (instancetype)billboardConstraint;

/*!
 @property freeAxes
 @abstract Specifies the axes on which the billboarding orientation operates. Defaults to SCNBillboardAxisAll.
 */
@property(nonatomic) SCNBillboardAxis freeAxes;

@end

/*!
 @class SCNTransformConstraint
 @abstract A SCNTransformConstraint applies on the transform of a node via a custom block.
 */
API_AVAILABLE(macosx(10.9))
@interface SCNTransformConstraint : SCNConstraint

/*!
 @method transformConstraintInWorldSpace:withBlock:
 @abstract Creates and returns a SCNTransformConstraint object with the specified parameters.
 @param world Determines whether the constraint is evaluated in world or local space.
 @param block The custom block to call to evaluate the constraint.
 @discussion The node and its transform are passed to the block. The transform returned by the block will be used to render the node.
 */
+ (instancetype)transformConstraintInWorldSpace:(BOOL)world withBlock:(SCNMatrix4 (^)(SCNNode *node, SCNMatrix4 transform))block;

@end


/*!
 @class SCNIKConstraint
 @abstract A SCNIKConstraint applies an inverse kinematics constraint
 */
API_AVAILABLE(macosx(10.10))
@interface SCNIKConstraint : SCNConstraint

/*!
 @method initWithChainRootNode:
 @abstract Creates and returns a SCNIKConstraint object with the specified parameter.
 @param chainRootNode The root node of the kinematic chain.
 @discussion "chainRootNode" must be an ancestor of the node on which the constraint is applied.
 */
- (instancetype)initWithChainRootNode:(SCNNode *)chainRootNode API_AVAILABLE(macosx(10.11), ios(9.0));

/*!
 @method inverseKinematicsConstraintWithChainRootNode:
 @abstract Creates and returns a SCNIKConstraint object with the specified parameter.
 @param chainRootNode The root node of the kinematic chain.
 @discussion "chainRootNode" must be an ancestor of the node on which the constraint is applied.
*/
+ (instancetype)inverseKinematicsConstraintWithChainRootNode:(SCNNode *)chainRootNode;

/*!
 @property chainRootNode
 @abstract Specifies the root node of the kinematic chain.
 */
@property(nonatomic, readonly) SCNNode *chainRootNode;

/*!
 @property target
 @abstract Specifies the target position (in world space coordinates) of the end joint (i.e the node that owns the IK constraint). Defaults to (0,0,0). Animatable.
 */
@property(nonatomic) SCNVector3 targetPosition;

/*!
 @method setMaxAllowedRotationAngle:forJoint:
 @abstract Specifies the maximum rotation allowed (in degrees) for the specified joint from its initial orientation. Defaults to 180.
 */
- (void)setMaxAllowedRotationAngle:(CGFloat)angle forJoint:(SCNNode *)node;
- (CGFloat)maxAllowedRotationAngleForJoint:(SCNNode *)node;

@end

NS_ASSUME_NONNULL_END
