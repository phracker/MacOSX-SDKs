//
//  HKQuantity.h
//  HealthKit
//
//  Copyright (c) 2013-2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HKUnit;

/*!
 @class         HKQuantity
 @abstract      The HKQuantity class provides an encapsulation of a quantity value and the unit of measurement.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0))
@interface HKQuantity : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;

/*!
 @method        quantityWithUnit:doubleValue:
 @abstract      Returns a new object representing a quantity measurement with the given unit.
 */
+ (instancetype)quantityWithUnit:(HKUnit *)unit doubleValue:(double)value;

/*!
 @method        isCompatibleWithUnit:
 @abstract      Returns yes if the receiver's value can be converted to a value of the given unit.
 */
- (BOOL)isCompatibleWithUnit:(HKUnit *)unit;

/*!
 @method        doubleValueForUnit:
 @abstract      Returns the quantity value converted to the given unit.
 @discussion    Throws an exception if the receiver's value cannot be converted to one of the requested unit.
 */
- (double)doubleValueForUnit:(HKUnit *)unit;

/*!
 @method        compare:
 @abstract      Returns an NSComparisonResult value that indicates whether the receiver is greater than, equal to, or 
                less than a given quantity.
 @discussion    Throws an exception if the unit of the given quantity is not compatible with the receiver's unit.
 */
- (NSComparisonResult)compare:(HKQuantity *)quantity;

@end

NS_ASSUME_NONNULL_END
