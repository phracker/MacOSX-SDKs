//
//  MLModel+MLComputeDevice.h
//  CoreML
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <CoreML/MLModel.h>

@protocol MLComputeDeviceProtocol;

NS_ASSUME_NONNULL_BEGIN

/// MLModel (MLComputeDevice)
///
/// Class with utilties for getting the available compute devices.
API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
@interface MLModel (MLComputeDevice)

/// The list of available compute devices for CoreML.
///
/// Use the method to get the list of compute devices that MLModel's prediction can use.
///
/// Some compute devices on the hardware are exclusive to the domain ML frameworks such as Vision and SoundAnalysis and
/// not available to CoreML. See also `MLComputeDevice.allComputeDevices`.
@property (class, readonly, nonatomic, copy) NSArray<id<MLComputeDeviceProtocol>> *availableComputeDevices API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0)) NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
