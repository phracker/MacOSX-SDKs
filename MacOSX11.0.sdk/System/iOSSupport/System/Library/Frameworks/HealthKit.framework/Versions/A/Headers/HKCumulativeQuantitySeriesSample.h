//
//  HKCumulativeQuantitySeriesSample.h
//  HealthKit
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <HealthKit/HKCumulativeQuantitySample.h>

NS_ASSUME_NONNULL_BEGIN

HK_EXTERN API_DEPRECATED_WITH_REPLACEMENT("HKCumulativeQuantitySample", ios(12.0, 13.0), watchos(5.0, 6.0))
@interface HKCumulativeQuantitySeriesSample : HKCumulativeQuantitySample

@property (readonly, copy) HKQuantity *sum;

@end

NS_ASSUME_NONNULL_END
