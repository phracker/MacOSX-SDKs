//
//  MLComputeDeviceProtocol.h
//  CoreML_framework
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * Protocol for representing a compute device. The represented device
 * is capable of running machine learning computations and other tasks like
 * analysis and processing of images, sound, etc.
 *
 */
API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
ML_EXPORT
@protocol MLComputeDeviceProtocol <NSObject>

@end

NS_ASSUME_NONNULL_END
