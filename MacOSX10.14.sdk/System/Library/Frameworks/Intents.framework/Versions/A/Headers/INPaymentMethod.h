//
//  INPaymentMethod.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INPaymentMethodType.h>

@class INImage;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INPaymentMethod : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithType:(INPaymentMethodType)type
                        name:(nullable NSString *)name
          identificationHint:(nullable NSString *)identificationHint
                        icon:(nullable INImage *)icon NS_DESIGNATED_INITIALIZER;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INPaymentMethodType type;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *name;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INImage *icon;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identificationHint;

// This payment method represents Apple Pay. Its .type will be INPaymentMethodTypeApplePay. The .name, .identificationHint and .icon properties are not significant for this type of payment method.
+ (instancetype)applePayPaymentMethod;

@end

NS_ASSUME_NONNULL_END
