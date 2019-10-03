// LOCKED FILE: 5e764a4873227e12cf95dcc73197a547
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

@interface HKObjectType (ClinicalType)
+ (nullable HKClinicalType *)clinicalTypeForIdentifier:(HKClinicalTypeIdentifier)identifier API_AVAILABLE(ios(12.0), watchos(5.0));
@end

HK_EXTERN
API_AVAILABLE(ios(12.0), watchos(5.0))
@interface HKClinicalType : HKSampleType
@end

NS_ASSUME_NONNULL_END
