//
//  MLNeuralEngineComputeDevice.h
//  CoreML_framework
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <CoreML/MLComputeDeviceProtocol.h>

/*!
 * Represents a NeuralEngine compute device for inference of machine learning models.
 *
 */
API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
ML_EXPORT NS_SWIFT_SENDABLE
__attribute__((objc_subclassing_restricted))
@interface MLNeuralEngineComputeDevice : NSObject<MLComputeDeviceProtocol>

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

/// The total number of cores in the NeuralEngine.
@property (readonly, assign, nonatomic) NSInteger totalCoreCount;

@end
