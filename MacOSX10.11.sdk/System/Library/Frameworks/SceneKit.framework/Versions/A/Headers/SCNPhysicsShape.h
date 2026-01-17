//
//  SCNPhysicsShape.h
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

@class SCNGeometry;
@class SCNNode;

//Type of the physics shape. Default is SCNPhysicsShapeTypeConvexHull.
//See below for the list of shape types.
SCN_EXTERN NSString * const SCNPhysicsShapeTypeKey NS_AVAILABLE(10_10, 8_0);

//The possible values for the key SCNPhysicsShapeGeometryTypeKey
SCN_EXTERN NSString * const SCNPhysicsShapeTypeBoundingBox NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN NSString * const SCNPhysicsShapeTypeConvexHull NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN NSString * const SCNPhysicsShapeTypeConcavePolyhedron NS_AVAILABLE(10_10, 8_0);

//A boolean to decide if a hierarchy is kept as a compound of shapes or flattened as one single volume. Default is true.
SCN_EXTERN NSString * const SCNPhysicsShapeKeepAsCompoundKey NS_AVAILABLE(10_10, 8_0);

//Local scaling of the physics shape (as an SCNVector3 wrapped in a NSValue)
SCN_EXTERN NSString * const SCNPhysicsShapeScaleKey NS_AVAILABLE(10_10, 8_0);

/*!
 @class SCNPhysicsShape
 @abstract SCNPhysicsShape represents the shape of a physics body.
 */
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface SCNPhysicsShape : NSObject <NSCopying, NSSecureCoding>

//Creates an instance of a physics shape based on a geometry. see above for the possible options.
+ (instancetype)shapeWithGeometry:(SCNGeometry *)geometry options:(nullable NSDictionary<NSString *, id> *)options;

//Creates an instance of a physics shape based on a node hierachy. The hierarchy must contain geometries at some point to create a valid shape. see above for the possible options.
+ (instancetype)shapeWithNode:(SCNNode *)node options:(nullable NSDictionary<NSString *, id> *)options;

//Creates an instance of a physics shape based on several sub shapes, associated with transforms. The transforms are to be passed as an array of NSValue wrapping SCNMatrix4
+ (instancetype)shapeWithShapes:(NSArray<SCNPhysicsShape *> *)shapes transforms:(nullable NSArray<NSValue *> *)transforms;

// Returns the options requested at init time
@property(readonly, nonatomic, nullable) NSDictionary<NSString *, id> *options NS_AVAILABLE(10_11, 9_0);

// Returns the object from which this physics shape was created. It can be an SCNGeometry*, an SCNNode* or in NSArray* of subshapes.
@property(readonly, nonatomic) id sourceObject NS_AVAILABLE(10_11, 9_0);

// If the physics shape was created from an array of sub shapes, transforms contains the associated transforms as SCNMatrix4 wrapped in NSValue.
@property(readonly, nonatomic, nullable) NSArray<NSValue *> *transforms NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END
