//
//  SCNPhysicsShape.h
//
//  Copyright (c) 2014-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNGeometry;
@class SCNNode;

#if defined(SWIFT_SDK_OVERLAY2_SCENEKIT_EPOCH) && SWIFT_SDK_OVERLAY2_SCENEKIT_EPOCH >= 3
typedef NSString * SCNPhysicsShapeOption NS_STRING_ENUM;
#else
typedef NSString * SCNPhysicsShapeOption;
#endif

FOUNDATION_EXTERN SCNPhysicsShapeOption const SCNPhysicsShapeTypeKey               API_AVAILABLE(macosx(10.10));                        // Type of the physics shape. Default is SCNPhysicsShapeTypeConvexHull. See below for the list of shape types.
FOUNDATION_EXTERN SCNPhysicsShapeOption const SCNPhysicsShapeKeepAsCompoundKey     API_AVAILABLE(macosx(10.10));                        // A boolean to decide if a hierarchy is kept as a compound of shapes or flattened as one single volume. Default is true.
FOUNDATION_EXTERN SCNPhysicsShapeOption const SCNPhysicsShapeScaleKey              API_AVAILABLE(macosx(10.10));                        // Local scaling of the physics shape (as an SCNVector3 wrapped in a NSValue)
FOUNDATION_EXTERN SCNPhysicsShapeOption const SCNPhysicsShapeOptionCollisionMargin API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0)); // Collision margin of the physics shape (as an NSNumber)

#define SCNPhysicsShapeOptionType           SCNPhysicsShapeTypeKey
#define SCNPhysicsShapeOptionKeepAsCompound SCNPhysicsShapeKeepAsCompoundKey
#define SCNPhysicsShapeOptionScale          SCNPhysicsShapeScaleKey

// Values for SCNPhysicsShapeOptionType
#if defined(SWIFT_SDK_OVERLAY2_SCENEKIT_EPOCH) && SWIFT_SDK_OVERLAY2_SCENEKIT_EPOCH >= 3
typedef NSString * SCNPhysicsShapeType NS_STRING_ENUM;
#else
typedef NSString * SCNPhysicsShapeType;
#endif

FOUNDATION_EXTERN SCNPhysicsShapeType const SCNPhysicsShapeTypeBoundingBox API_AVAILABLE(macosx(10.10));
FOUNDATION_EXTERN SCNPhysicsShapeType const SCNPhysicsShapeTypeConvexHull API_AVAILABLE(macosx(10.10));
FOUNDATION_EXTERN SCNPhysicsShapeType const SCNPhysicsShapeTypeConcavePolyhedron API_AVAILABLE(macosx(10.10));

/*!
 @class SCNPhysicsShape
 @abstract SCNPhysicsShape represents the shape of a physics body.
 */
API_AVAILABLE(macosx(10.10))
@interface SCNPhysicsShape : NSObject <NSCopying, NSSecureCoding>

//Creates an instance of a physics shape based on a geometry. see above for the possible options.
+ (instancetype)shapeWithGeometry:(SCNGeometry *)geometry options:(nullable NSDictionary<SCNPhysicsShapeOption, id> *)options;

//Creates an instance of a physics shape based on a node hierachy. The hierarchy must contain geometries at some point to create a valid shape. see above for the possible options.
+ (instancetype)shapeWithNode:(SCNNode *)node options:(nullable NSDictionary<SCNPhysicsShapeOption, id> *)options;

//Creates an instance of a physics shape based on several sub shapes, associated with transforms. The transforms are to be passed as an array of NSValue wrapping SCNMatrix4
+ (instancetype)shapeWithShapes:(NSArray<SCNPhysicsShape *> *)shapes transforms:(nullable NSArray<NSValue *> *)transforms;

// Returns the options requested at init time
@property(readonly, nonatomic, nullable) NSDictionary<SCNPhysicsShapeOption, id> *options API_AVAILABLE(macosx(10.11), ios(9.0));

// Returns the object from which this physics shape was created. It can be an SCNGeometry*, an SCNNode* or in NSArray* of subshapes.
@property(readonly, nonatomic) id sourceObject API_AVAILABLE(macosx(10.11), ios(9.0));

// If the physics shape was created from an array of sub shapes, transforms contains the associated transforms as SCNMatrix4 wrapped in NSValue.
@property(readonly, nonatomic, nullable) NSArray<NSValue *> *transforms API_AVAILABLE(macosx(10.11), ios(9.0));

@end

NS_ASSUME_NONNULL_END
