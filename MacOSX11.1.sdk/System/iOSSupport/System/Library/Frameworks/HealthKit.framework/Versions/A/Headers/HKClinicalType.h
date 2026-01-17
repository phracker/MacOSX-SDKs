// LOCKED FILE: 3eaa97ca8031b323157948edc14ed29e
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
#if HK_ENABLE_CHR_ADDITIONAL_DSTU2_TYPES
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierDeviceRecord API_AVAILABLE(ios(14.0), watchos(7.0));
#endif // HK_ENABLE_CHR_ADDITIONAL_DSTU2_TYPES
#if HK_ENABLE_CHR_ADDITIONAL_DSTU2_TYPES
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierCarePlanRecord API_AVAILABLE(ios(14.0), watchos(7.0));
#endif // HK_ENABLE_CHR_ADDITIONAL_DSTU2_TYPES
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierCoverageRecord API_AVAILABLE(ios(14.0), watchos(7.0));
#if HK_ENABLE_CHR_LIFESTYLE
HK_EXTERN HKClinicalTypeIdentifier const HKClinicalTypeIdentifierSocialHistoryRecord API_AVAILABLE(ios(14.0), watchos(7.0));
#endif // HK_ENABLE_CHR_LIFESTYLE

@interface HKObjectType (ClinicalType)
+ (nullable HKClinicalType *)clinicalTypeForIdentifier:(HKClinicalTypeIdentifier)identifier API_AVAILABLE(ios(12.0), watchos(5.0));
@end

HK_EXTERN
API_AVAILABLE(ios(12.0), watchos(5.0))
@interface HKClinicalType : HKSampleType
@end

NS_ASSUME_NONNULL_END
