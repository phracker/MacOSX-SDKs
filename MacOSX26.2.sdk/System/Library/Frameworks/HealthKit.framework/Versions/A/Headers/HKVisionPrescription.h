//
//  HKVisionPrescription.h
//  HealthKit
//
//  Copyright © 2022 Apple. All rights reserved.
//



#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>
#import <HealthKit/HKSample.h>

@class HKDevice;

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum          HKVisionPrescriptionType
 @abstract      Represents a vision prescription type
 */
typedef NS_ENUM(NSUInteger, HKVisionPrescriptionType) {
    HKVisionPrescriptionTypeGlasses = 1,
    HKVisionPrescriptionTypeContacts,
} API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0));

/*!
 @class         HKVisionPrescription
 @abstract      HKSample subclass representing a vision prescription
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0))
@interface HKVisionPrescription : HKSample <NSSecureCoding, NSCopying>

/*!
 @property      prescriptionType
 @abstract      A vision prescription type (glasses or contacts)
 */
@property (nonatomic, assign, readonly) HKVisionPrescriptionType prescriptionType;

/*!
 @property      dateIssued
 @abstract      The date the prescription was issued
 */
@property (nonatomic, copy, readonly) NSDate *dateIssued;

/*!
 @property      expirationDate
 @abstract      The date the prescription will expire
 */
@property (nonatomic, copy, readonly, nullable) NSDate *expirationDate;


/*!
 @method        prescriptionWithType:dateIssued:expirationDate:device:metadata

 @param         type           The prescription type
 @param         dateIssued     The date the prescription was issued
 @param         expirationDate The date the prescription expires
 @param         device         The device that generated the sample
 @param         metadata       The metadata for the sample
 */
+ (instancetype)prescriptionWithType:(HKVisionPrescriptionType)type
                          dateIssued:(NSDate *)dateIssued
                      expirationDate:(nullable NSDate *)expirationDate
                              device:(nullable HKDevice *)device
                            metadata:(nullable NSDictionary<NSString *, id> *)metadata;


- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
