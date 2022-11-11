//
//  HKVerifiableClinicalRecordSubject.h
//  HealthKit
//
//  Copyright © 2021 Apple. All rights reserved.
//

#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class     HKVerifiableClinicalRecordSubject
 @abstract  An NSObject that represents a verifiable clinical record subject.
 */
HK_EXTERN API_AVAILABLE(ios(15.0)) __WATCHOS_PROHIBITED
@interface HKVerifiableClinicalRecordSubject : NSObject <NSSecureCoding, NSCopying>

/*!
 @property     fullName
 @abstract     The subject's full name.
 */
@property (readonly, copy) NSString *fullName;

/*!
 @property     dateOfBirthComponents
 @abstract     The subject's date of birth components.
 */
@property (readonly, copy, nullable) NSDateComponents *dateOfBirthComponents;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
