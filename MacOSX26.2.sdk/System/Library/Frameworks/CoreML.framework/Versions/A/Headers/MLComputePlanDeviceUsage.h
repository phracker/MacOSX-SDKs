//
//  MLComputePlanDeviceUsage.h
//  CoreML_framework
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <CoreML/CoreML.h>

NS_ASSUME_NONNULL_BEGIN

/// The anticipated compute devices that would be used for executing a layer/operation.
__attribute__((objc_subclassing_restricted))
ML_EXPORT NS_REFINED_FOR_SWIFT NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.4), ios(17.4), watchos(10.4), tvos(17.4))
@interface MLComputePlanDeviceUsage : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

/// The compute devices that can execute the layer/operation.
@property (readonly, copy, nonatomic) NSArray<id<MLComputeDeviceProtocol>> *supportedComputeDevices NS_SWIFT_NAME(supported);
/// The compute device that the framework prefers to execute the layer/operation.
@property (readonly, strong, nonatomic) id<MLComputeDeviceProtocol> preferredComputeDevice NS_SWIFT_NAME(preferred);

@end

NS_ASSUME_NONNULL_END
