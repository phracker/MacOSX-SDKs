//
//  MLReshapeFrequencyHint.h
//  CoreML_framework
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/// The anticipated frequency of changing input shapes
typedef NS_ENUM(NSInteger, MLReshapeFrequencyHint) {
    /// The input shape is expected to change frequently on each prediction sent to this loaded model instance. Core ML will try to minimize the latency associated with shape changes and avoid expensive shape-specific optimizations prior to prediction computation. While prediction computation may be slower for each specific shape, switching between shapes should be faster.
    /// This is the default.
    MLReshapeFrequencyHintFrequent = 0,

    /// The input shape is expected to be stable and many/all predictions sent to this loaded model instance would use the same input shapes repeatedly. On the shape change, Core ML re-optimizes the internal engine for the new shape if possible. The re-optimization takes some time, but the subsequent predictions for the shape should run faster.
    MLReshapeFrequencyHintInfrequent = 1,
} API_AVAILABLE(macos(14.4), ios(17.4), watchos(10.4), tvos(17.4)) NS_REFINED_FOR_SWIFT;
