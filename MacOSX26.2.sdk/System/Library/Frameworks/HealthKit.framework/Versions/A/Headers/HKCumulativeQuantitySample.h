//
//  HKCumulativeQuantitySample.h
//  HealthKit
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKQuantitySample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKQuantity;

/*!
 @class         HKCumulativeQuantitySample
 @abstract      An HKQuantitySample subclass representing a quantity measurement with cumulative aggregation style.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0))
@interface HKCumulativeQuantitySample : HKQuantitySample

/*!
 @property      sumQuantity
 @abstract      The sum of quantities represented by the receiver.
 */
@property (readonly, copy) HKQuantity *sumQuantity;

@end

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathSum API_AVAILABLE(ios(12.0), watchos(5.0), macCatalyst(13.0), macos(13.0));

NS_ASSUME_NONNULL_END
