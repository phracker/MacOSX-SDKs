//
//  MLMetricKey.h
//  CoreML
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <CoreML/CoreML.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * A class to specify list of supported model update metrics.
 */
ML_EXPORT
API_AVAILABLE(macos(10.15), ios(13.0), tvos(14.0))
@interface MLMetricKey : MLKey

// Float metric indicating the current loss
@property (class, readonly, nonatomic) MLMetricKey *lossValue;

// Int64 metric indicating the index of the epoch
@property (class, readonly, nonatomic) MLMetricKey *epochIndex;

// Int64 metric indicating the index of mini batches in the current epoch
@property (class, readonly, nonatomic) MLMetricKey *miniBatchIndex;

// cannot construct MLMetricKey without parameters.
- (instancetype)init NS_UNAVAILABLE;

// cannot construct MLMetricKey without parameters.
+ (id)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

