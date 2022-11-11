//
//  HKClinicalType.h
//  HealthKit
//
//  Copyright (c) 2018 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>
#import <HealthKit/HKObjectType.h>

NS_ASSUME_NONNULL_BEGIN

@class HKClinicalType;

typedef NSString *HKClinicalTypeIdentifier NS_TYPED_ENUM API_AVAILABLE(ios(12.0), watchos(5.0));

HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierAllergyRecord API_AVAILABLE(ios(12.0), watchos(5.0));
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierConditionRecord API_AVAILABLE(ios(12.0), watchos(5.0));
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierImmunizationRecord API_AVAILABLE(ios(12.0), watchos(5.0));
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierLabResultRecord API_AVAILABLE(ios(12.0), watchos(5.0));
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierMedicationRecord API_AVAILABLE(ios(12.0), watchos(5.0));
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierProcedureRecord API_AVAILABLE(ios(12.0), watchos(5.0));
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierVitalSignRecord API_AVAILABLE(ios(12.0), watchos(5.0));
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierCoverageRecord API_AVAILABLE(ios(14.0), watchos(7.0));

@interface HKObjectType (ClinicalType)
#if __swift__
+ (nullable HKClinicalType *)clinicalTypeForIdentifier:(HKClinicalTypeIdentifier)identifier API_DEPRECATED_WITH_REPLACEMENT("HKClinicalType(_:)", ios(12.0, API_TO_BE_DEPRECATED), watchos(5.0, API_TO_BE_DEPRECATED));
#else
+ (nullable HKClinicalType *)clinicalTypeForIdentifier:(HKClinicalTypeIdentifier)identifier API_AVAILABLE(ios(12.0), watchos(5.0));
#endif
@end

HK_EXTERN
API_AVAILABLE(ios(12.0), watchos(5.0))
@interface HKClinicalType : HKSampleType
@end

NS_ASSUME_NONNULL_END
