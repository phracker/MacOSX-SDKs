//
//  HKVerifiableClinicalRecord.h
//  HealthKit
//
//  Copyright © 2021 Apple. All rights reserved.
//

#import <HealthKit/HKSample.h>

@class HKVerifiableClinicalRecordSubject;

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKVerifiableClinicalRecord
 @abstract      An NSObject that represents a verifiable clinical record.
 */
HK_EXTERN API_AVAILABLE(ios(15.0)) __WATCHOS_PROHIBITED
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
@property (readonly, copy) NSArray<NSString*> *itemNames;

/*!
 @property      JWSRepresentation
 @abstract      The record's entirety as JSON Web Signature (JWS) data.
 */
@property (readonly, copy) NSData *JWSRepresentation;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
