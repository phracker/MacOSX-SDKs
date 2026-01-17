//
//  HKObjectType.h
//  HealthKit
//
//  Copyright (c) 2013-2017 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>
#import <HealthKit/HKTypeIdentifiers.h>
#import <HealthKit/HKQuantityAggregationStyle.h>

NS_ASSUME_NONNULL_BEGIN

@class HKActivitySummaryType;
@class HKAudiogramSampleType;
@class HKCategoryType;
@class HKCharacteristicType;
@class HKCorrelationType;
@class HKDocumentType;
@class HKElectrocardiogramType;
@class HKQuantityType;
@class HKSeriesType;
@class HKUnit;
@class HKWorkoutType;

/*!
 @class         HKObjectType
 @abstract      An abstract class representing a type of object that can be stored by HealthKit.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKObjectType : NSObject <NSSecureCoding, NSCopying>

/*!
 @property      identifier
 @abstract      A unique string identifying a type of health object.
 @discussion    See HKTypeIdentifiers.h for possible values.
 */
@property (readonly, strong) NSString *identifier;

- (instancetype)init NS_UNAVAILABLE;

+ (nullable HKQuantityType *)quantityTypeForIdentifier:(HKQuantityTypeIdentifier)identifier;
+ (nullable HKCategoryType *)categoryTypeForIdentifier:(HKCategoryTypeIdentifier)identifier;
+ (nullable HKCharacteristicType *)characteristicTypeForIdentifier:(HKCharacteristicTypeIdentifier)identifier;
+ (nullable HKCorrelationType *)correlationTypeForIdentifier:(HKCorrelationTypeIdentifier)identifier;
+ (nullable HKDocumentType *)documentTypeForIdentifier:(HKDocumentTypeIdentifier)identifier API_AVAILABLE(ios(10.0), watchos(3.0));
+ (nullable HKSeriesType *)seriesTypeForIdentifier:(NSString *)identifier API_AVAILABLE(ios(11.0), watchos(4.0));
+ (HKWorkoutType *)workoutType;
+ (HKActivitySummaryType *)activitySummaryType API_AVAILABLE(ios(9.3), watchos(2.2));
+ (HKAudiogramSampleType *)audiogramSampleType API_AVAILABLE(ios(13.0), watchos(6.0));
+ (HKElectrocardiogramType *)electrocardiogramType API_AVAILABLE(ios(14.0), watchos(7.0));

@end

/*!
 @class         HKCharacteristicType
 @abstract      Represents a type of object that describes a characteristic of the user (such as date of birth).
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKCharacteristicType : HKObjectType
@end

/*!
 @class         HKSampleType
 @abstract      Represents a type of HKSample.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKSampleType : HKObjectType

/*!
 @property      isMaximumDurationRestricted
 @abstract      Returns YES if the start and end date for samples of this type are restricted by a maximum duration.
 */
@property (nonatomic, readonly) BOOL isMaximumDurationRestricted API_AVAILABLE(ios(13.0), watchos(6.0));

/*!
 @property      maximumAllowedDuration
 @abstract      When the duration is restricted for samples of this type, returns the maximum duration allowed,
                calculated as the difference between end and start dates.
 @discussion    Throws an exception if there is no maximum restriction on duration for samples of this type.
 */
@property (nonatomic, readonly) NSTimeInterval maximumAllowedDuration API_AVAILABLE(ios(13.0), watchos(6.0));

/*!
 @property      isMinimumDurationRestricted
 @abstract      Returns YES if the start and end date for samples of this type are restricted by a minimum duration.
 */
@property (nonatomic, readonly) BOOL isMinimumDurationRestricted API_AVAILABLE(ios(13.0), watchos(6.0));

/*!
 @property      minimumAllowedDuration
 @abstract      When the duration is restricted for samples of this type, returns the minimum duration allowed,
                calculated as the difference between end and start dates.
 @discussion    Throws an exception if there is no minimum restriction on duration for samples of this type.
 */
@property (nonatomic, readonly) NSTimeInterval minimumAllowedDuration API_AVAILABLE(ios(13.0), watchos(6.0));

@end

/*!
 @class         HKCategoryType
 @abstract      Represent a type of HKCategorySample.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKCategoryType : HKSampleType
@end

/*!
 @class         HKCorrelationType
 @abstract      Represents a type of HKCorrelation
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKCorrelationType : HKSampleType
@end

/*!
 @class         HKDocumentType
 @abstract      Represents a type of HKDocument.
 */
HK_EXTERN API_AVAILABLE(ios(10.0))
@interface HKDocumentType : HKSampleType
@end

/*!
 @class         HKQuantityType
 @abstract      Represents types of HKQuantitySamples.
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKQuantityType : HKSampleType

@property (readonly) HKQuantityAggregationStyle aggregationStyle;

/*!
 @method        isCompatibleWithUnit:
 @abstract      Returns YES if the type of HKQuantitySample represented by the receiver can be created with quantities 
                of the given unit.
 */
- (BOOL)isCompatibleWithUnit:(HKUnit *)unit;

@end

/*!
 @class         HKWorkoutType
 @abstract      Represents a workout or exercise
 */
HK_EXTERN API_AVAILABLE(ios(8.0), watchos(2.0))
@interface HKWorkoutType : HKSampleType
@end

/*!
 @class         HKSeriesType
 @abstract      Represents a type of HKSeriesSample
 */
HK_EXTERN API_AVAILABLE(ios(11.0), watchos(4.0))
@interface HKSeriesType : HKSampleType

+ (instancetype)workoutRouteType;
+ (instancetype)heartbeatSeriesType API_AVAILABLE(ios(13.0), watchos(6.0));

@end

/*!
 @class         HKActivitySummaryType
 @abstract      Represents an HKActivitySummary
 */
HK_EXTERN API_AVAILABLE(ios(9.3), watchos(2.2))
@interface HKActivitySummaryType : HKObjectType
@end

/*!
 @class    HKAudiogramSampleType
 @abstract Represents an audiogram sample.
 */
HK_EXTERN API_AVAILABLE(ios(13.0), watchos(6.0))
@interface HKAudiogramSampleType : HKSampleType
@end

/*!
 @class    HKElectrocardiogramType
 @abstract Represents an electrocardiogram sample.
 */
HK_EXTERN API_AVAILABLE(ios(14.0), watchos(7.0))
@interface HKElectrocardiogramType : HKSampleType
@end

NS_ASSUME_NONNULL_END
