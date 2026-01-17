//
//  HKQuantitySample.h
//  HealthKit
//
//  Copyright (c) 2013-2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKSample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKQuantity;
@class HKQuantityType;

/*!
 @class         HKQuantitySample
 @abstract      An abstract HKSample subclass representing a quantity measurement.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0))
@interface HKQuantitySample : HKSample

@property (readonly, copy) HKQuantityType *quantityType;
@property (readonly, copy) HKQuantity *quantity;

/*!
 @property      count
 @abstract      The number of individual values making up the receiver's quantity.
 @discussion    Requests for the individual series quantities can be made using HKQuantitySeriesSampleQuery.
 */
@property (readonly, assign) NSInteger count API_AVAILABLE(ios(12.0), watchos(5.0), macCatalyst(13.0), macos(13.0));

/*!
 @method        quantitySampleWithType:quantity:startDate:endDate:
 @abstract      Creates a new HKQuantitySample with the given type, quantity, start date, and end date.
 @discussion    The quantity must have a unit that is compatible with the given quantity type.
                See -[HKQuantityType isCompatibleWithUnit:].
 */
+ (instancetype)quantitySampleWithType:(HKQuantityType *)quantityType
                              quantity:(HKQuantity *)quantity
                             startDate:(NSDate *)startDate
                               endDate:(NSDate *)endDate;

/*!
 @method        quantitySampleWithType:quantity:startDate:endDate:metadata:
 @abstract      Creates a new HKQuantitySample with the given type, quantity, start date, end date, and metadata.
 @discussion    The quantity must have a unit that is compatible with the given quantity type.
                See -[HKQuantityType isCompatibleWithUnit:].
 */
+ (instancetype)quantitySampleWithType:(HKQuantityType *)quantityType
                              quantity:(HKQuantity *)quantity
                             startDate:(NSDate *)startDate
                               endDate:(NSDate *)endDate
                              metadata:(nullable NSDictionary<NSString *, id> *)metadata;

/*!
 @method        quantitySampleWithType:quantity:startDate:endDate:device:metadata:
 @abstract      Creates a new HKQuantitySample with the given type, quantity, start date, end date, and metadata.
 @param         quantityType    The type of the sample.
 @param         startDate       The start date of the sample.
 @param         endDate         The end date of the sample.
 @param         device          The HKDevice that generated the sample (optional).
 @param         metadata        Metadata for the sample (optional).
 @discussion    The quantity must have a unit that is compatible with the given quantity type.
                See -[HKQuantityType isCompatibleWithUnit:].
 */
+ (instancetype)quantitySampleWithType:(HKQuantityType *)quantityType
                              quantity:(HKQuantity *)quantity
                             startDate:(NSDate *)startDate
                               endDate:(NSDate *)endDate
                                device:(nullable HKDevice *)device
                              metadata:(nullable NSDictionary<NSString *, id> *)metadata API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

@end

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathQuantity API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));
HK_EXTERN NSString * const HKPredicateKeyPathCount API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0));

NS_ASSUME_NONNULL_END
