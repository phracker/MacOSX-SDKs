//
//  MLOptimizationHints.h
//  CoreML_framework
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLExport.h>
#import <CoreML/MLReshapeFrequencyHint.h>
#import <CoreML/MLSpecializationStrategy.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * MLOptimizationHints
 *
 * An object to hold hints that CoreML could use for further optimization
 */
API_AVAILABLE(macos(14.4), ios(17.4), watchos(10.4), tvos(17.4))
ML_EXPORT NS_REFINED_FOR_SWIFT
@interface MLOptimizationHints : NSObject <NSCopying, NSSecureCoding>

/// The anticipated reshape frequency
///
/// CoreML framework needs to reshape the model with new shapes for models with flexible input.
/// Specify the anticipated reshape frequency (frequent or infrequent), so that the framework can optimize for
/// fast shape switching or fast prediction on seen shapes.
///
/// The default value is frequent, which means CoreML tries to switch to new shapes as fast as possible
@property (readwrite, assign, nonatomic) MLReshapeFrequencyHint reshapeFrequency;

/// Optimization strategy for the model specialization.
///
/// Core ML segments the model's compute graph and optimizes each segment for the
/// target compute device. This process can affect the model loading time and the prediction latency.
///
/// Use this option to tailor the specialization strategy for your application.
@property (readwrite, assign, nonatomic) MLSpecializationStrategy specializationStrategy API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

@end

NS_ASSUME_NONNULL_END


