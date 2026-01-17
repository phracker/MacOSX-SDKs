//
//  SCNPhysicsContact.h
//  SceneKit
//
//  Copyright © 2014-2019 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;

/*!
 @class SCNPhysicsContact
 @abstract SCNPhysicsContact contains information about a physics contact.
 */
SCN_EXPORT API_AVAILABLE(macos(10.10))
@interface SCNPhysicsContact : NSObject

//The two nodes in contact
@property(nonatomic, readonly) SCNNode *nodeA;
@property(nonatomic, readonly) SCNNode *nodeB;

//The contact point, impulse and distance in world space coordinates.
@property(nonatomic, readonly) SCNVector3 contactPoint;
@property(nonatomic, readonly) SCNVector3 contactNormal;
@property(nonatomic, readonly) CGFloat    collisionImpulse; // the collision impulse on nodeA
@property(nonatomic, readonly) CGFloat    penetrationDistance;
@property(nonatomic, readonly) CGFloat    sweepTestFraction API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)); // Value between 0 and 1 giving the relative position of the physic shape when performing a convex sweep test.

@end

NS_ASSUME_NONNULL_END
