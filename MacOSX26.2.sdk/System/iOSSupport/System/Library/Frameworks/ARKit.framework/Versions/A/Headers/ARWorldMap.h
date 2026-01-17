//
//  ARWorldMap.h
//  ARKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

@class ARAnchor;
@class ARPointCloud;

NS_ASSUME_NONNULL_BEGIN

/**
 Object representing the mapping of a physical 3D space.
 @discussion ARWorldMap supports archiving and unarchiving across devices
 and versions with NSDecodingFailurePolicySetErrorAndReturn, providing an error
 if the map format is not supported.
 */
API_AVAILABLE(ios(12.0))
@interface ARWorldMap : NSObject <NSCopying, NSSecureCoding>

/**
 The position of the center of the mapped world in meters.
 */
@property (nonatomic, readonly) simd_float3 center;

/**
 The extent of the mapped world in meters.
 */
@property (nonatomic, readonly) simd_float3 extent;

/**
 A list of anchors in the map.
 */
@property (nonatomic, copy) NSArray<__kindof ARAnchor *> *anchors;

/**
 The feature points in the map.
 */
@property (nonatomic, strong, readonly) ARPointCloud *rawFeaturePoints;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
