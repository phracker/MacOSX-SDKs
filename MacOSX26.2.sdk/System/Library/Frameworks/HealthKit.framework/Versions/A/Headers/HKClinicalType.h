//
//  HKClinicalType.h
//  HealthKit
//
//  Copyright (c) 2018-2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKObjectType.h>

NS_ASSUME_NONNULL_BEGIN

@class HKClinicalType;

typedef NSString *HKClinicalTypeIdentifier NS_TYPED_ENUM API_AVAILABLE(ios(12.0), watchos(5.0), macCatalyst(13.0), macos(13.0));

/// A type identifier for records of allergies or intolerances.
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierAllergyRecord API_AVAILABLE(ios(12.0), watchos(5.0), macCatalyst(13.0), macos(13.0));

/// A type identifier for records that represent clinical notes.
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierClinicalNoteRecord API_AVAILABLE(ios(16.4), watchos(9.4), macCatalyst(16.4), macos(13.3));

/// A type identifier for records of a condition, problem, or diagnosis.
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierConditionRecord API_AVAILABLE(ios(12.0), watchos(5.0), macCatalyst(13.0), macos(13.0));

/// A type identifier for records of vaccine administration.
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierImmunizationRecord API_AVAILABLE(ios(12.0), watchos(5.0), macCatalyst(13.0), macos(13.0));

/// A type identifier for records of lab results.
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierLabResultRecord API_AVAILABLE(ios(12.0), watchos(5.0), macCatalyst(13.0), macos(13.0));

/// A type identifier for records of medication prescription, intake, or administration.
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierMedicationRecord API_AVAILABLE(ios(12.0), watchos(5.0), macCatalyst(13.0), macos(13.0));

/// A type identifier for records of clinical procedures.
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierProcedureRecord API_AVAILABLE(ios(12.0), watchos(5.0), macCatalyst(13.0), macos(13.0));

/// A type identifier for records of vital signs.
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierVitalSignRecord API_AVAILABLE(ios(12.0), watchos(5.0), macCatalyst(13.0), macos(13.0));

/// A type identifier for records containing information about the user’s insurance coverage.
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierCoverageRecord API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0));


@interface HKObjectType (ClinicalType)

/*!
 @method        clinicalTypeForIdentifier
 @abstract      Returns the clinical type given a valid clinical type identifier.
 */
#if defined(__swift__) && __swift__
+ (nullable HKClinicalType *)clinicalTypeForIdentifier:(HKClinicalTypeIdentifier)identifier API_DEPRECATED_WITH_REPLACEMENT("HKClinicalType(_:)", ios(12.0, API_TO_BE_DEPRECATED), watchos(5.0, API_TO_BE_DEPRECATED));
#else
+ (nullable HKClinicalType *)clinicalTypeForIdentifier:(HKClinicalTypeIdentifier)identifier API_AVAILABLE(ios(12.0), watchos(5.0), macCatalyst(13.0), macos(13.0));
#endif // defined(__swift__) && __swift__
@end

/*!
 @class         HKClinicalType
 @abstract      A type that identifies samples that contain clinical record data.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(12.0), watchos(5.0), macCatalyst(13.0), macos(13.0))
@interface HKClinicalType : HKSampleType
@end

NS_ASSUME_NONNULL_END
