//
//  ARPlaneGeometry.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNGeometry.h>
#import <simd/simd.h>
#if __has_include(<ARKit/ARSCNPlaneGeometry.h>)
#import <ARKit/ARSCNPlaneGeometry.h>
#endif

@protocol MTLDevice;

NS_ASSUME_NONNULL_BEGIN

/**
 Object representing the geometry of a plane.
 @discussion The plane geometry will have a growing number of triangles
 and vertices updated from frame to frame.
 */
API_AVAILABLE(ios(11.3))
@interface ARPlaneGeometry : NSObject<NSSecureCoding>

/**
 The number of mesh vertices of the geometry.
 */
@property (nonatomic, readonly) NSUInteger vertexCount NS_REFINED_FOR_SWIFT;

/**
 The mesh vertices of the geometry.
 */
@property (nonatomic, readonly) const simd_float3 *vertices NS_REFINED_FOR_SWIFT;

/**
 The number of texture coordinates of the geometry.
 */
@property (nonatomic, readonly) NSUInteger textureCoordinateCount NS_REFINED_FOR_SWIFT;

/**
 The texture coordinates of the geometry.
 */
@property (nonatomic, readonly) const simd_float2 *textureCoordinates NS_REFINED_FOR_SWIFT;

/**
 The number of triangles of the geometry.
 */
@property (nonatomic, readonly) NSUInteger triangleCount;

/**
 The triangle indices of the geometry.
 */
@property (nonatomic, readonly) const int16_t *triangleIndices NS_REFINED_FOR_SWIFT;

/**
 The number of boundary vertices of the geometry.
 */
@property (nonatomic, readonly) NSUInteger boundaryVertexCount NS_REFINED_FOR_SWIFT;

/**
 The vertices of the geometry's outermost boundary.
 */
@property (nonatomic, readonly) const simd_float3 *boundaryVertices NS_REFINED_FOR_SWIFT;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
