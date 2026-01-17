//
//  ARMeshAnchor.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>

NS_ASSUME_NONNULL_BEGIN

@class ARMeshGeometry;

/*
 An anchor representing a mesh in the world.
 */
API_AVAILABLE(ios(13.4))
@interface ARMeshAnchor : ARAnchor

/**
 Geometry of the mesh in anchor's coordinate system.
 */
@property (nonatomic, readonly) ARMeshGeometry *geometry;

/** Unavailable */
- (instancetype)initWithTransform:(simd_float4x4)transform NS_UNAVAILABLE;
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
