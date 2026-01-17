//
//  SCNPhysicsShape.h
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

@class SCNGeometry;
@class SCNNode;

//Type of the physics shape. Default is SCNPhysicsShapeTypeConvexHull.
//See below for the list of shape types.
SCN_EXTERN NSString * const SCNPhysicsShapeTypeKey;

//The possible values for the key SCNPhysicsShapeGeometryTypeKey
SCN_EXTERN NSString * const SCNPhysicsShapeTypeBoundingBox;
SCN_EXTERN NSString * const SCNPhysicsShapeTypeConvexHull;
SCN_EXTERN NSString * const SCNPhysicsShapeTypeConcavePolyhedron;

//A boolean to decide if a hierarchy is kept as a compound of shapes or flattened as one single volume. Default is true.
SCN_EXTERN NSString * const SCNPhysicsShapeKeepAsCompoundKey;

//Local scaling of the physics shape (as an SCNVector3 wrapped in a NSValue)
SCN_EXTERN NSString * const SCNPhysicsShapeScaleKey;

/*!
 @class SCNPhysicsShape
 @abstract SCNPhysicsShape represents the shape of a physics body.
 */
SCENEKIT_CLASS_AVAILABLE(10_10, 8_0)
@interface SCNPhysicsShape : NSObject <NSCopying, NSSecureCoding>
{
@private
    id _reserved;
}

//Creates an instance of a physics shape based on a geometry. see above for the possible options.
+ (instancetype)shapeWithGeometry:(SCNGeometry *)geometry options:(NSDictionary *)options;

//Creates an instance of a physics shape based on a node hierachy. The hierarchy must contain geometries at some point to create a valid shape. see above for the possible options.
+ (instancetype)shapeWithNode:(SCNNode *)node options:(NSDictionary *)options;

//Creates an instance of a physics shape based on several sub shapes, associated with transforms. The transforms are to be passed as an array of NSValue wrapping SCNMatrix4
+ (instancetype)shapeWithShapes:(NSArray *)shapes transforms:(NSArray *)transforms;

@end
