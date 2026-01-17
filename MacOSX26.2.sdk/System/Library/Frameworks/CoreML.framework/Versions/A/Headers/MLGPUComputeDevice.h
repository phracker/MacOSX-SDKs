//
//  MLGPUComputeDevice.h
//  CoreML_framework
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <CoreML/MLComputeDeviceProtocol.h>

@protocol MTLDevice;

/*!
 * Represents a GPU compute device.
 *
 */
API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
ML_EXPORT NS_SWIFT_SENDABLE
__attribute__((objc_subclassing_restricted))
@interface MLGPUComputeDevice : NSObject<MLComputeDeviceProtocol>

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

/// The underlying metal device.
@property (strong, readonly, nonatomic) id<MTLDevice> metalDevice;

@end
