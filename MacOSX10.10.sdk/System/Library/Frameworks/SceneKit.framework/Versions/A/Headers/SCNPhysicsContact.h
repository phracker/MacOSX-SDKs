//
//  SCNPhysicsContact.h
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

/*!
 @class SCNPhysicsContact
 @abstract SCNPhysicsContact contains information about a physics contact.
 */
SCENEKIT_CLASS_AVAILABLE(10_10, 8_0)
@interface SCNPhysicsContact : NSObject
{
@private
    id _reserved;
}

//The two nodes in contact
@property(nonatomic, readonly) SCNNode *nodeA;
@property(nonatomic, readonly) SCNNode *nodeB;

//The contact point, impulse and distance in world space coordinates.
@property(nonatomic, readonly) SCNVector3 contactPoint;
@property(nonatomic, readonly) SCNVector3 contactNormal;
@property(nonatomic, readonly) CGFloat    collisionImpulse; // the collision impulse on nodeA
@property(nonatomic, readonly) CGFloat    penetrationDistance; 

@end
