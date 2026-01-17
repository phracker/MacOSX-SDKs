//
//  MLAllComputeDevices.h
//  CoreML_framework
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <CoreML/MLExport.h>

@protocol MLComputeDeviceProtocol;

NS_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif
    /*!
     * @abstract Returns an array containing all compute devices.
     *
     * @discussion The returned array contains all compute devices that are accessible. If a compute
     * device becomes inaccessible for some reason (for e.g. if an external GPU is unplugged)
     * then the subsequent call to`MLAllComputeDevices` will return an array without the compute device.
     *
     */
    ML_EXPORT NSArray<id<MLComputeDeviceProtocol>> *MLAllComputeDevices(void) API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0)) NS_REFINED_FOR_SWIFT;
#ifdef __cplusplus
}
#endif

NS_ASSUME_NONNULL_END
