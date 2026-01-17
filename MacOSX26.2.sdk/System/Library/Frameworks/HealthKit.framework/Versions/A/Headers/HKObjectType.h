//
//  HKObjectType.h
//  HealthKit
//
//  Copyright (c) 2013-2025 Apple Inc. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKQuantityAggregationStyle.h>
#import <HealthKit/HKTypeIdentifiers.h>

NS_ASSUME_NONNULL_BEGIN

@class HKActivitySummaryType;
@class HKAudiogramSampleType;
@class HKCategoryType;
@class HKCharacteristicType;
@class HKCorrelationType;
@class HKDocumentType;
@class HKElectrocardiogramType;
@class HKMedicationDoseEventType;
@class HKQuantityType;
@class HKSeriesType;
@class HKStateOfMindType;
@class HKUnit;
@class HKUserAnnotatedMedicationType;
@class HKPrescriptionType;
@class HKWorkoutType;
@class HKScoredAssessmentType;

/*!
 @class         HKObjectType
 @abstract      An abstract class representing a type of object that can be stored by HealthKit.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0))
@interface HKObjectType : NSObject <NSSecureCoding, NSCopying>

/*!
 @property      identifier
 @abstract      A unique string identifying a type of health object.
 @discussion    See HKTypeIdentifiers.h for possible values.
 */
@property (readonly, strong) NSString *identifier;

- (instancetype)init NS_UNAVAILABLE;

#if defined(__swift__) && __swift__
+ (nullable HKQuantityType *)quantityTypeForIdentifier:(HKQuantityTypeIdentifier)identifier API_DEPRECATED_WITH_REPLACEMENT("HKQuantityType(_:)", ios(8.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED));
+ (nullable HKCategoryType *)categoryTypeForIdentifier:(HKCategoryTypeIdentifier)identifier API_DEPRECATED_WITH_REPLACEMENT("HKCategoryType(_:)", ios(8.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED));
+ (nullable HKCharacteristicType *)characteristicTypeForIdentifier:(HKCharacteristicTypeIdentifier)identifier API_DEPRECATED_WITH_REPLACEMENT("HKCharacteristicType(_:)", ios(8.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED));
+ (nullable HKCorrelationType *)correlationTypeForIdentifier:(HKCorrelationTypeIdentifier)identifier API_DEPRECATED_WITH_REPLACEMENT("HKCorrelationType(_:)", ios(8.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED));
+ (nullable HKDocumentType *)documentTypeForIdentifier:(HKDocumentTypeIdentifier)identifier API_DEPRECATED_WITH_REPLACEMENT("HKDocumentType(_:)", ios(10.0, API_TO_BE_DEPRECATED), watchos(3.0, API_TO_BE_DEPRECATED));
#else
+ (nullable HKQuantityType *)quantityTypeForIdentifier:(HKQuantityTypeIdentifier)identifier;
+ (nullable HKCategoryType *)categoryTypeForIdentifier:(HKCategoryTypeIdentifier)identifier;
+ (nullable HKCharacteristicType *)characteristicTypeForIdentifier:(HKCharacteristicTypeIdentifier)identifier;
+ (nullable HKCorrelationType *)correlationTypeForIdentifier:(HKCorrelationTypeIdentifier)identifier;
+ (nullable HKDocumentType *)documentTypeForIdentifier:(HKDocumentTypeIdentifier)identifier API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0));
+ (nullable HKScoredAssessmentType *)scoredAssessmentTypeForIdentifier:(HKScoredAssessmentTypeIdentifier)identifier API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));
#endif // defined(__swift__) && __swift__

+ (nullable HKSeriesType *)seriesTypeForIdentifier:(NSString *)identifier API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0));
+ (HKWorkoutType *)workoutType;
+ (HKActivitySummaryType *)activitySummaryType API_AVAILABLE(ios(9.3), watchos(2.2), macCatalyst(13.0), macos(13.0));
+ (HKAudiogramSampleType *)audiogramSampleType API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0));
+ (HKElectrocardiogramType *)electrocardiogramType API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0));
+ (HKMedicationDoseEventType *)medicationDoseEventType API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0));
+ (HKPrescriptionType *)visionPrescriptionType API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));
+ (HKStateOfMindType *)stateOfMindType API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0));
+ (HKUserAnnotatedMedicationType *)userAnnotatedMedicationType API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0));

/*!
 @method        requiresPerObjectAuthorization
 @abstract      Returns YES if the authorization for the object type needs to be requested on per object basis.
 */
- (BOOL)requiresPerObjectAuthorization API_AVAILABLE(ios(16.0), macCatalyst(16.0), macos(13.0));

@end

/*!
 @class         HKCharacteristicType
 @abstract      Represents a type of object that describes a characteristic of the user (such as date of birth).
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0))
@interface HKCharacteristicType : HKObjectType
@end

/*!
 @class         HKSampleType
 @abstract      Represents a type of HKSample.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0))
@interface HKSampleType : HKObjectType

/*!
 @property      isMaximumDurationRestricted
 @abstract      Returns YES if the start and end date for samples of this type are restricted by a maximum duration.
 */
@property (nonatomic, readonly) BOOL isMaximumDurationRestricted API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0));

/*!
 @property      maximumAllowedDuration
 @abstract      When the duration is restricted for samples of this type, returns the maximum duration allowed,
                calculated as the difference between end and start dates.
 @discussion    Throws an exception if there is no maximum restriction on duration for samples of this type.
 */
@property (nonatomic, readonly) NSTimeInterval maximumAllowedDuration API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0));

/*!
 @property      isMinimumDurationRestricted
 @abstract      Returns YES if the start and end date for samples of this type are restricted by a minimum duration.
 */
@property (nonatomic, readonly) BOOL isMinimumDurationRestricted API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0));

/*!
 @property      minimumAllowedDuration
 @abstract      When the duration is restricted for samples of this type, returns the minimum duration allowed,
                calculated as the difference between end and start dates.
 @discussion    Throws an exception if there is no minimum restriction on duration for samples of this type.
 */
@property (nonatomic, readonly) NSTimeInterval minimumAllowedDuration API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0));

/*!
 @property      allowsRecalibrationForEstimates
 @abstract      Returns YES if first-party samples of this type are produced using a prediction algorithm, and that algorithm supports recalibration. To recalibrate the
                estimates for a sample type, see -[HKHealthStore recalibrateEstimatesForSampleType:atDate:completion:]
 */
@property (nonatomic, readonly) BOOL allowsRecalibrationForEstimates API_AVAILABLE(ios(15.0), watchos(8.0), macCatalyst(15.0), macos(13.0));

@end

/*!
 @class         HKCategoryType
 @abstract      Represent a type of HKCategorySample.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0))
@interface HKCategoryType : HKSampleType
@end

/*!
 @class         HKCorrelationType
 @abstract      Represents a type of HKCorrelation
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0))
@interface HKCorrelationType : HKSampleType
@end

/*!
 @class         HKDocumentType
 @abstract      Represents a type of HKDocument.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(10.0), macCatalyst(13.0), macos(13.0))
@interface HKDocumentType : HKSampleType
@end

/*!
 @class         HKQuantityType
 @abstract      Represents types of HKQuantitySamples.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0))
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
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0))
@interface HKWorkoutType : HKSampleType
@end

/*!
 @class         HKSeriesType
 @abstract      Represents a type of HKSeriesSample
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0))
@interface HKSeriesType : HKSampleType

+ (instancetype)workoutRouteType;
+ (instancetype)heartbeatSeriesType API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0));

@end

/*!
 @class         HKActivitySummaryType
 @abstract      Represents an HKActivitySummary
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(9.3), watchos(2.2), macCatalyst(13.0), macos(13.0))
@interface HKActivitySummaryType : HKObjectType
@end

/*!
 @class    HKAudiogramSampleType
 @abstract Represents an audiogram sample.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0))
@interface HKAudiogramSampleType : HKSampleType
@end

/*!
 @class    HKElectrocardiogramType
 @abstract Represents an electrocardiogram sample.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0))
@interface HKElectrocardiogramType : HKSampleType
@end

/*!
 @class         HKMedicationDoseEventType
 @abstract      Represents a recorded log of a specific medication, represented by HKMedicationDoseEvent samples.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0))
@interface HKMedicationDoseEventType : HKSampleType
@end

/*!
 @class         HKPrescriptionType
 @abstract      Represents a prescription type
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0))
@interface HKPrescriptionType : HKSampleType
@end

/*!
 @class    HKScoredAssessmentType
 @abstract Represents a scored assessment sample
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0))
@interface HKScoredAssessmentType : HKSampleType
@end

/*!
 @class    HKStateOfMindType
 @abstract Represents an experienced feeling and its surrounding context.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(18.0), watchos(11.0), macCatalyst(18.0), macos(15.0), visionos(2.0))
@interface HKStateOfMindType : HKSampleType
@end


/*!
 @class         HKUserAnnotatedMedicationType
 @abstract      Represents the set of authorizeable HKUserAnnotatedMedications.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.0), watchos(26.0), macCatalyst(26.0), macos(26.0), visionos(26.0))
@interface HKUserAnnotatedMedicationType : HKObjectType
@end
NS_ASSUME_NONNULL_END
