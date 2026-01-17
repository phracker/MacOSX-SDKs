//
//  HKVerifiableClinicalRecord.h
//  HealthKit
//
//  Copyright © 2021-2022 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKSample.h>

@class HKVerifiableClinicalRecordSubject;

NS_ASSUME_NONNULL_BEGIN

typedef NSString * HKVerifiableClinicalRecordSourceType NS_TYPED_ENUM API_AVAILABLE(ios(15.4), macCatalyst(15.4), macos(13.0));

/*!
 @constant      HKVerifiableClinicalRecordSourceTypeSMARTHealthCard
 @abstract      Represents a SMART Health Card source type for a verifiable record.
 */
HK_EXTERN HKVerifiableClinicalRecordSourceType const HKVerifiableClinicalRecordSourceTypeSMARTHealthCard API_AVAILABLE(ios(15.4), macCatalyst(15.4), macos(13.0));

/*!
 @constant      HKVerifiableClinicalRecordSourceTypeEUDigitalCOVIDCertificate
 @abstract      Represents a EU Digital COVID Certificate source type for a verifiable record.
 */
HK_EXTERN HKVerifiableClinicalRecordSourceType const HKVerifiableClinicalRecordSourceTypeEUDigitalCOVIDCertificate API_AVAILABLE(ios(15.4), macCatalyst(15.4), macos(13.0));

typedef NSString * HKVerifiableClinicalRecordCredentialType NS_TYPED_ENUM API_AVAILABLE(ios(15.4), macCatalyst(15.4), macos(13.0));

/*!
 @constant      HKVerifiableClinicalRecordCredentialTypeCOVID19
 @abstract      Represents the COVID-19 credential type for a verifiable record.
 */
HK_EXTERN HKVerifiableClinicalRecordCredentialType const HKVerifiableClinicalRecordCredentialTypeCOVID19 NS_SWIFT_NAME(covid19) API_AVAILABLE(ios(15.4), macCatalyst(15.4), macos(13.0));

/*!
 @constant      HKVerifiableClinicalRecordCredentialTypeImmunization
 @abstract      Represents the immunization credential type for a verifiable record.
 */
HK_EXTERN HKVerifiableClinicalRecordCredentialType const HKVerifiableClinicalRecordCredentialTypeImmunization API_AVAILABLE(ios(15.4), macCatalyst(15.4), macos(13.0));

/*!
 @constant      HKVerifiableClinicalRecordCredentialTypeLaboratory
 @abstract      Represents the laboratory credential type for a verifiable record.
 */
HK_EXTERN HKVerifiableClinicalRecordCredentialType const HKVerifiableClinicalRecordCredentialTypeLaboratory API_AVAILABLE(ios(15.4), macCatalyst(15.4), macos(13.0));

/*!
 @constant      HKVerifiableClinicalRecordCredentialTypeRecovery
 @abstract      Represents the recovery credential type for a verifiable record.
 */
HK_EXTERN HKVerifiableClinicalRecordCredentialType const HKVerifiableClinicalRecordCredentialTypeRecovery API_AVAILABLE(ios(15.4), macCatalyst(15.4), macos(13.0));

/*!
 @class         HKVerifiableClinicalRecord
 @abstract      An NSObject that represents a verifiable clinical record.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(15.0), macCatalyst(15.0), macos(13.0)) __WATCHOS_PROHIBITED
@interface HKVerifiableClinicalRecord : HKSample

/*!
 @property      recordTypes
 @abstract      The types present in this record.
 */
@property (readonly, copy) NSArray<NSString *> *recordTypes;

/*!
 @property      issuerIdentifier
 @abstract      The identifier for the issuer of this record.
 */
@property (readonly, copy) NSString *issuerIdentifier;

/*!
 @property      subject
 @abstract      The subject of this record.
 */
@property (readonly, copy) HKVerifiableClinicalRecordSubject *subject;

/*!
 @property      issuedDate
 @abstract      The date this record was issued.
 */
@property (readonly, copy) NSDate *issuedDate;

/*!
 @property      relevantDate
 @abstract      A date most relevant to this record, like when a vaccine was
 administered or a test was performed.
 */
@property (readonly, copy) NSDate *relevantDate;

/*!
 @property      expirationDate
 @abstract      The date this record expires.
 */
@property (readonly, copy, nullable) NSDate *expirationDate;

/*!
 @property      itemNames
 @abstract      A list of display names for each item contained in this record.
 */
@property (readonly, copy) NSArray<NSString *> *itemNames;

/*!
 @property      sourceType
 @abstract      The type of the source leading to this verifiable record.
 */
@property (readonly, copy, nullable) HKVerifiableClinicalRecordSourceType sourceType API_AVAILABLE(ios(15.4), macCatalyst(15.4), macos(13.0));

/*!
 @property      dataRepresentation
 @abstract      The record's data representation, determined by source type.
 */
@property (readonly, copy) NSData *dataRepresentation API_AVAILABLE(ios(15.4), macCatalyst(15.4), macos(13.0));

/*!
 @property      JWSRepresentation
 @abstract      The record's entirety as JSON Web Signature (JWS) data.
 */
@property (readonly, copy) NSData *JWSRepresentation API_DEPRECATED_WITH_REPLACEMENT("dataRepresentation", ios(15.0, 15.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
