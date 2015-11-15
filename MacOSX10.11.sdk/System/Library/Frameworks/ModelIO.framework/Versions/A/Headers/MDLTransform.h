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

@property (nonatomic, readonly) NSTimeInterval minimumTime;
@property (nonatomic, readonly) NSTimeInterval maximumTime;

@optional
- (void)setLocalTransform:(matrix_float4x4)transform forTime:(NSTimeInterval)time;

/**
 Resets any timing information, and makes transform valid at all times 
 */
- (void)setLocalTransform:(matrix_float4x4)transform;


/** returns the transform governing this transformable at the specified time
    in the transformable's parent's space.
    If non-animated, all frame values will return the same result. 
 */
- (matrix_float4x4)localTransformAtTime:(NSTimeInterval)time;

/** returns the transform governing this transformable at the specified frame in 
    the asset's space. If there is no parent, identity will be returned 
 */
+ (matrix_float4x4)globalTransformWithObject:(MDLObject *)object atTime:(NSTimeInterval)time;

@end


/**
 Concrete implementation of <MDLTransformComponent>.
 For more complex transform components create a class that conforms to 
 <MDLTransformComponent>.
 
 @discussion Setting any of scale, translation, or rotation individually will 
 set the matrix property, and clear any timing information.
 
 Initialization with a matrix assumes the matrix does not include any projective
 components. Checks are not made against those components, and retrieving 
 transform components after initialization with such a matrix will yield
 unexpected results.
 
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLTransform : NSObject <MDLTransformComponent>

- (instancetype)initWithIdentity NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithTransformComponent:(id<MDLTransformComponent>)component;
- (instancetype)initWithMatrix:(matrix_float4x4)matrix;

/**
 Set all transform components to identity
 */
- (void)setIdentity;

- (vector_float3)scaleAtTime:(NSTimeInterval)time;
- (vector_float3)translationAtTime:(NSTimeInterval)time;
- (vector_float3)rotationAtTime:(NSTimeInterval)time;
- (void)setScale:(vector_float3)scale forTime:(NSTimeInterval)time;
- (void)setTranslation:(vector_float3)translation forTime:(NSTimeInterval)time;
- (void)setRotation:(vector_float3)rotation forTime:(NSTimeInterval)time;

/**
 If these properties are read, the earliest value is returned.
 If written, all timing information is removed. To retain or add timing information,
 use the set:forTime selectors instead.
 */
@property (nonatomic, readwrite) vector_float3 scale;
@property (nonatomic, readwrite) vector_float3 translation;
@property (nonatomic, readwrite) vector_float3 rotation;     // Euler XYZ

@end

NS_ASSUME_NONNULL_END
