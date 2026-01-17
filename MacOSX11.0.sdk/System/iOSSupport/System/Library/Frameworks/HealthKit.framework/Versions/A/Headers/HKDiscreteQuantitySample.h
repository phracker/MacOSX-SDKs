//
//  HKDiscreteQuantitySample.h
//  HealthKit
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <HealthKit/HKQuantitySample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKQuantity;

/*!
 @class         HKDiscreteQuantitySample
 @abstract      An HKQuantitySample subclass representing a quantity measurement with
                discrete aggregation style.
 */
HK_EXTERN API_AVAILABLE(ios(13.0), watchos(6.0))
@interface HKDiscreteQuantitySample : HKQuantitySample

/*!
 @property      minimumQuantity
 @abstract      The minimum of the receiver's quantities
 */
@property (readonly, copy) HKQuantity *minimumQuantity;

/*!
 @property      averageQuantity
 @abstract      The average of the receiver's quantities
 */
@property (readonly, copy) HKQuantity *averageQuantity;

/*!
 @property      maximumQuantity
 @abstract      The maximum of the receiver's quantities
 */
@property (readonly, copy) HKQuantity *maximumQuantity;

/*!
 @property      mostRecentQuantity
 @abstract      The receiver's quantity with most recent date interval
 */
@property (readonly, copy) HKQuantity *mostRecentQuantity;

/*!
 @property      mostRecentQuantityDateInterval
 @abstract      The date interval for the receiver's most recent quantity
 */
@property (readonly, copy) NSDateInterval *mostRecentQuantityDateInterval;

@end

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathMin API_AVAILABLE(ios(13.0), watchos(6.0));
HK_EXTERN NSString * const HKPredicateKeyPathAverage API_AVAILABLE(ios(13.0), watchos(6.0));
HK_EXTERN NSString * const HKPredicateKeyPathMax API_AVAILABLE(ios(13.0), watchos(6.0));
HK_EXTERN NSString * const HKPredicateKeyPathMostRecent API_AVAILABLE(ios(13.0), watchos(6.0));
HK_EXTERN NSString * const HKPredicateKeyPathMostRecentStartDate API_AVAILABLE(ios(13.0), watchos(6.0));
HK_EXTERN NSString * const HKPredicateKeyPathMostRecentEndDate API_AVAILABLE(ios(13.0), watchos(6.0));
HK_EXTERN NSString * const HKPredicateKeyPathMostRecentDuration API_AVAILABLE(ios(13.0), watchos(6.0));

NS_ASSUME_NONNULL_END
