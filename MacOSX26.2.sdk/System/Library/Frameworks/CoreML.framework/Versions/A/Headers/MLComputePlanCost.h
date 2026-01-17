//
//  MLComputePlanCost.h
//  CoreML_framework
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/// A class representing the estimated cost of executing a layer/operation.
__attribute__((objc_subclassing_restricted))
ML_EXPORT NS_REFINED_FOR_SWIFT NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.4), ios(17.4), watchos(10.4), tvos(17.4))
@interface MLComputePlanCost : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

/// The estimated workload of executing the operation over the total model execution. The value is between [0.0, 1.0].
@property (readonly, assign, nonatomic) double weight;

@end

NS_ASSUME_NONNULL_END
