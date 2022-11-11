//
//  ARObjectAnchor.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>

NS_ASSUME_NONNULL_BEGIN

@class ARReferenceObject;


/**
 An anchor representing an object in the world.
 */
API_AVAILABLE(ios(12.0))
@interface ARObjectAnchor : ARAnchor

/**
 Reference to the detected object.
 */
@property (nonatomic, strong, readonly) ARReferenceObject *referenceObject;


/** Unavailable */
- (instancetype)initWithTransform:(simd_float4x4)transform NS_UNAVAILABLE;
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
