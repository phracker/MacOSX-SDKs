//
//  HKContactsPrescription.h
//  HealthKit
//
//  Copyright © 2022 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKVisionPrescription.h>

@class HKContactsLensSpecification;
@class HKDevice;

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKContactsPrescription
 @abstract      An object representing a contacts prescription
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0))
@interface HKContactsPrescription: HKVisionPrescription <NSSecureCoding, NSCopying>

/*!
 @property      rightEye
 @abstract      The right eye lens specification
 */
@property (nonatomic, copy, readonly, nullable) HKContactsLensSpecification *rightEye;

/*!
 @property      leftEye
 @abstract      The left eye lens specification
 */
@property (nonatomic, copy, readonly, nullable) HKContactsLensSpecification *leftEye;

/*!
 @property      brand
 @abstract      The prescribed brand after contact lens fitting
 */
@property (nonatomic, copy, readonly) NSString *brand;

/*!
 @method        prescriptionWithRightEyeSpecification:leftEyeSpecification:brand:dateIssued:expirationDate:device:metadata

 @param         rightEyeSpecification  The right eye specification
 @param         leftEyeSpecification   The left eye specification
 @param         brand                  The prescribed brand after contact lens fitting
 @param         dateIssued             The date the prescription was issued
 @param         expirationDate         The date the prescription expires
 @param         device                 The device that generated the sample
 @param         metadata               The metadata for the sample
 */
+ (instancetype)prescriptionWithRightEyeSpecification:(nullable HKContactsLensSpecification *)rightEyeSpecification
                                 leftEyeSpecification:(nullable HKContactsLensSpecification *)leftEyeSpecification
                                                brand:(NSString *)brand
                                           dateIssued:(NSDate *)dateIssued
                                       expirationDate:(nullable NSDate *)expirationDate
                                               device:(nullable HKDevice *)device
                                             metadata:(nullable NSDictionary<NSString *, id> *)metadata;


- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
+ (instancetype)prescriptionWithType:(HKVisionPrescriptionType)type
                          dateIssued:(NSDate *)dateIssued
                      expirationDate:(nullable NSDate *)expirationDate
                              device:(nullable HKDevice *)device
                            metadata:(nullable NSDictionary<NSString *, id> *)metadata NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
