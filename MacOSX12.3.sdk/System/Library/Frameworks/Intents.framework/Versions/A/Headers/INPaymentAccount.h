//
//  INPaymentAccount.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INAccountType.h>

@class INBalanceAmount;
@class INSpeakableString;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@interface INPaymentAccount : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithNickname:(INSpeakableString *)nickname
                          number:(nullable NSString *)number
                     accountType:(INAccountType)accountType
                organizationName:(nullable INSpeakableString *)organizationName
                         balance:(nullable INBalanceAmount *)balance
                secondaryBalance:(nullable INBalanceAmount *)secondaryBalance NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(11.0), watchos(4.0));

- (nullable instancetype)initWithNickname:(INSpeakableString *)nickname
                                   number:(nullable NSString *)number
                              accountType:(INAccountType)accountType
                         organizationName:(nullable INSpeakableString *)organizationName API_DEPRECATED("Please use 'initWithNickname:number:accountType:organizationName:balance:secondaryBalance:' instead", ios(10.3, 11.0), watchos(3.2, 4.0));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *nickname;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *accountNumber;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INAccountType accountType;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *organizationName;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INBalanceAmount *balance API_AVAILABLE(ios(11.0), watchos(4.0));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INBalanceAmount *secondaryBalance API_AVAILABLE(ios(11.0), watchos(4.0));

@end

NS_ASSUME_NONNULL_END
