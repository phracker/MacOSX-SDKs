//
//  HKClinicalRecord.h
//  HealthKit
//
//  Copyright (c) 2018-2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKSample.h>

@class HKClinicalType;
@class HKFHIRResource;

NS_ASSUME_NONNULL_BEGIN

HK_EXTERN NSString * const HKPredicateKeyPathClinicalRecordFHIRResourceIdentifier API_AVAILABLE(ios(12.0), macCatalyst(13.0), macos(13.0)) __WATCHOS_PROHIBITED;
HK_EXTERN NSString * const HKPredicateKeyPathClinicalRecordFHIRResourceType API_AVAILABLE(ios(12.0), macCatalyst(13.0), macos(13.0)) __WATCHOS_PROHIBITED;

/*!
 @class		   HKClinicalRecord
 @abstract     An HKObject subclass representing a health record.
 @discussion   The startDate and endDate properties (inherited from HKSample) are set to the date the sample was
               added to Health. Unlike other HKObject subclasses, UUID is not a stable identifier
               for a given sample. Use a combination of HKSource, FHIRResource.resourceType, and
               FHIRResource.identifier instead.
*/
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(12.0), macCatalyst(13.0), macos(13.0)) __WATCHOS_PROHIBITED
@interface HKClinicalRecord : HKSample <NSSecureCoding, NSCopying>

@property (readonly, copy) HKClinicalType *clinicalType;

/*!
 @property     displayName
 @abstract     The primary display name used in Health.
 @discussion   The display name is not localized, and is generally expected to be US English.
 */
@property (copy, readonly) NSString *displayName;

/*!
 @property     FHIRResource
 @abstract     The FHIR resource (where applicable) backing this sample.
 */
@property (copy, readonly, nullable) HKFHIRResource *FHIRResource;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
