/*!
 @header MDLTransform.h
 @framework ModelIO
 @abstract Time sampled transformation of elements in 3d assets
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */


#import <ModelIO/MDLObject.h>
#import <ModelIO/MDLTypes.h>
#import <Foundation/Foundation.h>
#include <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

@class MDLObject;

/** MDLTransformComponent
    @summary a container for a time sampled local transformation
 
    @discussion Accessors to get the local transform and the global transform
    for a particular MDLObject are provided.
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@protocol MDLTransformComponent <MDLComponent>
@required

/** The matrix, at minimumTime */
@property (nonatomic, assign) matrix_float4x4 matrix;

/** if YES, this transform is intended to be in global space, not parent space */
@property (nonatomic, assign) BOOL resetsTransform;

/** If no animation data is present, minimumTime and maximumTime will be zero */
@property (nonatomic, readonly) NSTimeInterval minimumTime;
@property (nonatomic, readonly) NSTimeInterval maximumTime;

/** An array of sample times for which a key has been stored
    If no animation data is present, the array will contain a single value of zero */
@property (nonatomic, readonly, copy) NSArray<NSNumber*> *keyTimes;

@optional
- (void)setLocalTransform:(matrix_float4x4)transform forTime:(NSTimeInterval)time;

/**
 Resets any timing information, and makes transform valid at all times 
 */
- (void)setLocalTransform:(matrix_float4x4)transform;


/** Returns the transform governing this transformable at the specified time
    in the transformable's parent's space.
    If non-animated, all frame values will return the same result. 
 */
- (matrix_float4x4)localTransformAtTime:(NSTimeInterval)time;

/** Returns the transform governing this transformable at the specified frame in
    world space. If there is no parent, identity will be returned
 */
+ (matrix_float4x4)globalTransformWithObject:(MDLObject *)object atTime:(NSTimeInterval)time;

@end


/**
 Concrete implementation of <MDLTransformComponent>.
 For more complex transform components create a class that conforms to 
 <MDLTransformComponent>.
 
 @discussion Setting any of scale, translation, or rotation individually will 
 set the matrix property, and clear any timing information.
 
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLTransform : NSObject <NSCopying, MDLTransformComponent>

- (instancetype)initWithIdentity NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithTransformComponent:(id<MDLTransformComponent>)component;
- (instancetype)initWithTransformComponent:(id<MDLTransformComponent>)component
                           resetsTransform:(BOOL)resetsTransform;

/**
 Initialization with a matrix assumes the matrix is an invertible, homogeneous 
 affine transform matrix. Retrieving transform components after initialization 
 with a non-affine matrix will yield those of the identity transform.
 */
- (instancetype)initWithMatrix:(matrix_float4x4)matrix;
- (instancetype)initWithMatrix:(matrix_float4x4)matrix resetsTransform:(BOOL)resetsTransform;

/**
 Set all transform components to identity
 */
- (void)setIdentity;

- (vector_float3)translationAtTime:(NSTimeInterval)time;
- (vector_float3)rotationAtTime:(NSTimeInterval)time;
- (vector_float3)shearAtTime:(NSTimeInterval)time;
- (vector_float3)scaleAtTime:(NSTimeInterval)time;

- (void)setMatrix:(matrix_float4x4)matrix forTime:(NSTimeInterval)time;
- (void)setTranslation:(vector_float3)translation forTime:(NSTimeInterval)time;
- (void)setRotation:(vector_float3)rotation forTime:(NSTimeInterval)time;
- (void)setShear:(vector_float3)shear forTime:(NSTimeInterval)time;
- (void)setScale:(vector_float3)scale forTime:(NSTimeInterval)time;

/**
 Construct a right handed rotation matrix at the specified time
 */
- (matrix_float4x4)rotationMatrixAtTime:(NSTimeInterval)time;

/**
 If these properties are read and animation data exists the earliest value is returned.
 Otherwise, if there is no animation data, the value of the property is the same at all times and that value is returned.
 If written, timing information for said property is removed. To retain or add timing information, use the set:forTime selectors instead.
 */
@property (nonatomic, readwrite) vector_float3 translation;
@property (nonatomic, readwrite) vector_float3 rotation;     // Euler XYZ radians
@property (nonatomic, readwrite) vector_float3 shear;
@property (nonatomic, readwrite) vector_float3 scale;

@end

NS_ASSUME_NONNULL_END
