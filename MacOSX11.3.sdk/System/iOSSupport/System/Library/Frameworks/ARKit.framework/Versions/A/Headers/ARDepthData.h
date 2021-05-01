//
//  ARDepthData.h
//  ARKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>

NS_ASSUME_NONNULL_BEGIN
/**
 Constants indicating the confidence level of per-pixel depth data.
 */
typedef NS_ENUM(NSInteger, ARConfidenceLevel) {
    ARConfidenceLevelLow,
    ARConfidenceLevelMedium,
    ARConfidenceLevelHigh,
} API_AVAILABLE(ios(14.0));

/**
 A container for depth data and its associated confidence.
 */
API_AVAILABLE(ios(14.0))
@interface ARDepthData : NSObject

/**
 A pixel buffer that contains per-pixel depth data (in meters).
 */
@property (nonatomic, assign, readonly) CVPixelBufferRef depthMap;

/**
 A pixel buffer containing the confidence level for each depth value in the `depthMap`.
 @see ARConfidenceLevel
 */
@property (nonatomic, assign, nullable, readonly) CVPixelBufferRef confidenceMap;

@end
NS_ASSUME_NONNULL_END
