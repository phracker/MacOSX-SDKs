//
//  HKQuantityAggregationStyle.h
//  HealthKit
//
//  Copyright (c) 2013-2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum          HKQuantityAggregationStyle
 @discussion    Describes how quantities can be aggregated over time.
 
 @constant      HKQuantityAggregationStyleCumulative                        Samples may be summed over a time interval.
 @constant      HKQuantityAggregationStyleDiscreteArithmetic                Samples may be averaged over a time interval using the arithmetic mean
 @constant      HKQuantityAggregationStyleDiscreteTemporallyWeighted        Samples may be averaged over a time interval using a temporally weighted integration function
 @constant      HKQuantityAggregationStyleDiscreteEquivalentContinuousLevel Samples may be combined over a time interval by computing the equivalent continuous sound level; see IEC 61672-1

 */
typedef NS_ENUM(NSInteger, HKQuantityAggregationStyle) {
    HKQuantityAggregationStyleCumulative = 0,
    HKQuantityAggregationStyleDiscreteArithmetic API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0)),
    HKQuantityAggregationStyleDiscrete API_DEPRECATED_WITH_REPLACEMENT("HKQuantityAggregationStyleDiscreteArithmetic", ios(8.0, 13.0), watchos(2.0, 6.0)) = HKQuantityAggregationStyleDiscreteArithmetic,
    HKQuantityAggregationStyleDiscreteTemporallyWeighted API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0)),
    HKQuantityAggregationStyleDiscreteEquivalentContinuousLevel API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0)),
} API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

NS_ASSUME_NONNULL_END
