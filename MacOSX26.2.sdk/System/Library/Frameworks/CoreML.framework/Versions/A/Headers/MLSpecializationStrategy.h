//
//  MLSpecializationStrategy.h
//  CoreML_framework
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/// The optimization strategy for the model specialization.
typedef NS_ENUM(NSInteger, MLSpecializationStrategy) {
  /// The strategy that works well for most applications.
  MLSpecializationStrategyDefault = 0,

  /// Prefer the prediction latency at the potential cost of specialization time, memory footprint, and the disk space usage of specialized artifacts.
  MLSpecializationStrategyFastPrediction = 1,
} API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0)) NS_REFINED_FOR_SWIFT;
