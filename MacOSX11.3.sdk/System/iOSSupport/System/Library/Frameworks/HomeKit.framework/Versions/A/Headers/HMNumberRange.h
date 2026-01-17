//
//  HMNumberRange.h
//  HomeKit
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This class describes a range of numbers: [min, max]
 *
 */
HM_EXTERN API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMNumberRange : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Initializes a new range of numbers
 *
 * @param minValue The minimum value of the range.
 *
 * @param maxValue The maximum value of the range.
 */
+ (instancetype)numberRangeWithMinValue:(NSNumber *)minValue maxValue:(NSNumber *)maxValue;

/*!
 * @brief Initializes a new range of numbers. The maximum value is set to a large value.
 *
 * @param minValue The minimum value of the range.
 *
 */
+ (instancetype)numberRangeWithMinValue:(NSNumber *)minValue;

/*!
 * @brief Initializes a new range of numbers. The minimum value is set to a small value.
 *
 * @param maxValue The maximum value of the range.
 *
 */
+ (instancetype)numberRangeWithMaxValue:(NSNumber *)maxValue;

/*!
 * @brief The minimum value of the range.
 */
@property(nullable, readonly, strong, nonatomic) NSNumber *minValue;

/*!
 * @brief The maximum value of the range.
 */
@property(nullable, readonly, strong, nonatomic) NSNumber *maxValue;

@end

NS_ASSUME_NONNULL_END
