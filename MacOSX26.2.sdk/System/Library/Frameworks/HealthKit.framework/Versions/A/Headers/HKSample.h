//
//  HKSample.h
//  HealthKit
//
//  Copyright (c) 2014-2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKObject.h>

NS_ASSUME_NONNULL_BEGIN

@class HKSampleType;

/*!
 @class         HKSample
 @abstract      An abstract class representing measurements taken over a period of time.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0))
@interface HKSample : HKObject

@property (readonly, copy) HKSampleType *sampleType;

@property (readonly, strong) NSDate *startDate;
@property (readonly, strong) NSDate *endDate;

/*!
 @property      hasUndeterminedDuration
 @abstract      Indicates whether a sample has an undetermined duration.
 @discussion    Computed based on the endDate of a sample.
 */
@property (readonly) BOOL hasUndeterminedDuration API_AVAILABLE(ios(14.3), watchos(7.2), macCatalyst(14.3), macos(13.0));


@end

// Sort Identifiers
HK_EXTERN NSString * const HKSampleSortIdentifierStartDate API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));
HK_EXTERN NSString * const HKSampleSortIdentifierEndDate API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathStartDate API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));
HK_EXTERN NSString * const HKPredicateKeyPathEndDate API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

NS_ASSUME_NONNULL_END
