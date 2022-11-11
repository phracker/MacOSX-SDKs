//
//  HKFHIRResource.h
//  HealthKit
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

@class HKFHIRVersion;

NS_ASSUME_NONNULL_BEGIN

typedef NSString * HKFHIRResourceType NS_TYPED_ENUM API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos);

HK_EXTERN HKFHIRResourceType const HKFHIRResourceTypeAllergyIntolerance API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos);
HK_EXTERN HKFHIRResourceType const HKFHIRResourceTypeCondition API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos);
HK_EXTERN HKFHIRResourceType const HKFHIRResourceTypeCoverage API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);
HK_EXTERN HKFHIRResourceType const HKFHIRResourceTypeImmunization API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos);
HK_EXTERN HKFHIRResourceType const HKFHIRResourceTypeMedicationDispense API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos);
HK_EXTERN HKFHIRResourceType const HKFHIRResourceTypeMedicationOrder API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos);
HK_EXTERN HKFHIRResourceType const HKFHIRResourceTypeMedicationRequest API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);
HK_EXTERN HKFHIRResourceType const HKFHIRResourceTypeMedicationStatement API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos);
HK_EXTERN HKFHIRResourceType const HKFHIRResourceTypeObservation API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos);
HK_EXTERN HKFHIRResourceType const HKFHIRResourceTypeProcedure API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos);

/*!
 @class         HKFHIRResource
 @abstract      The HKFHIRResource class encapsulates a FHIR (Fast Healthcare Interoperability Resources) resource.
 */
HK_EXTERN API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos)
@interface HKFHIRResource : NSObject <NSSecureCoding, NSCopying>

/*!
 @property      FHIRVersion
 @abstract      The FHIR version of the resource data.
 */
@property (readonly, copy) HKFHIRVersion *FHIRVersion API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

/*!
 @property      resourceType
 @abstract      The resource type, corresponding to the 'resourceType' field in the resource's JSON representation.
 @discussion    May be one of 8 FHIR resource types supported within HealthKit: AllergyIntolerance, Condition,
                Immunization, MedicationDispense, MedicationOrder, MedicationStatement, Observation, and Procedure.
 */
@property (readonly, copy) HKFHIRResourceType resourceType;

/*!
 @property      identifier
 @abstract      The identifier of the resource, corresponding to the 'id' field in the resource's JSON representation.
 @discussion    Unique within a given resource type and FHIR end-point, as represented by an HKSource.
 */
@property (readonly, copy) NSString *identifier;

/*!
 @property      data
 @abstract      The JSON representation of the FHIR resource.
 @discussion    Conforms to the HL7 Argonaut Project resource type definitions.
 */
@property (readonly, copy) NSData *data;

/*!
 @property      sourceURL
 @abstract      The fully specified source URL of the FHIR resource.
 @discussion    This URL can be used to help determine the provenance of the resource. Direct access is protected by
                OAuth: querying without suitable authorization will result in an authorization error.
 */
@property (readonly, copy, nullable) NSURL *sourceURL;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
