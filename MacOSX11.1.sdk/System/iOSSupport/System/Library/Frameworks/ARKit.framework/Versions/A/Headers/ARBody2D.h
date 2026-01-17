//
//  ARBody2D.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <ARKit/ARSkeleton.h>
#import <simd/simd.h>


NS_ASSUME_NONNULL_BEGIN

/**
 Representation of a body in 2D.
 */
API_AVAILABLE(ios(13.0))
@interface ARBody2D : NSObject

/**
 The body's skeleton.
 */
@property (nonatomic, readonly) ARSkeleton2D *skeleton;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
