//
//  HKAudiogramSensitivityPointClampingRange.h
//  HealthKit
//
//  Copyright © 2023-2024 Apple. All rights reserved.
//



#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

@class HKQuantity;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Clamping Support

/// Defines the range within which an ear's sensitivity point may have been clamped, if any.
///
/// At times, it may be required to indicate that a sensitivity point has been clamped to a range. These reasons include but
/// are not limited to user safety, hardware limitations, or algorithm features.
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(18.1), watchos(11.1), macCatalyst(18.1), macos(15.1), visionos(2.1))
@interface HKAudiogramSensitivityPointClampingRange: NSObject  <NSSecureCoding, NSCopying>

/**
 @property lowerBound
 @abstract The lower bound of the clamping range, if any, in dBHL.
 */
@property(nonatomic, readonly, copy, nullable) HKQuantity *lowerBound;

/**
 @property upperBound
 @abstract The upper bound of the clamping range, if any, in dBHL.
 */
@property(nonatomic, readonly, copy, nullable) HKQuantity *upperBound;

- (instancetype)init NS_UNAVAILABLE;

/*!
 @method                    clampingRangeWithLowerBound:upperBound:error:
 @abstract                  Creates a clamping range from a given lower and upper bound. At least one bound must be specified. If both bounds are provided, the lower bound must be less than the upper bound.
 @param lowerBound          The lower bound of the clamping range (if any)
 @param upperBound          The upper bound of the clamping range (if any)
 @param errorOut            If there was a problem creating this instance this will contain the error.
 @return                    New instance of a clamping range or nil if there were problems
                            creating the instance.  Errors may include not having any bound or lower bound is greater than the upper bound
 */
+ (nullable instancetype)clampingRangeWithLowerBound:(nullable NSNumber *)lowerBound upperBound:(nullable NSNumber *)upperBound error:(NSError **)errorOut;
@end

NS_ASSUME_NONNULL_END
