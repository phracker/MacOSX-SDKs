//
//  HKVerifiableClinicalRecordSubject.h
//  HealthKit
//
//  Copyright © 2021-2022 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class     HKVerifiableClinicalRecordSubject
 @abstract  An NSObject that represents a verifiable clinical record subject.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(15.0), macCatalyst(15.0), macos(13.0)) __WATCHOS_PROHIBITED
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
