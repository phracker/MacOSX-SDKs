//
//  INBillPayee.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INSpeakableString;

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("INBillPayee is deprecated. There is no replacement", ios(10.3, 15.0), watchos(3.2, 8.0))
API_UNAVAILABLE(macos, tvos)
@interface INBillPayee : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithNickname:(INSpeakableString *)nickname
                                   number:(nullable NSString *)number
                         organizationName:(nullable INSpeakableString *)organizationName NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *nickname;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *accountNumber;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *organizationName;

@end

NS_ASSUME_NONNULL_END
