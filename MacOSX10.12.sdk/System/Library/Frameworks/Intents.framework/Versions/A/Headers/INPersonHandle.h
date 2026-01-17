//
//  INPersonHandle.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INPersonHandleLabel.h>

typedef NS_ENUM(NSInteger, INPersonHandleType) {
    INPersonHandleTypeUnknown = 0,
    INPersonHandleTypeEmailAddress,
    INPersonHandleTypePhoneNumber,
} API_AVAILABLE(macosx(10.12), ios(10.0));

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INPersonHandle : NSObject <NSCopying, NSSecureCoding>

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *value;
@property (readonly, NS_NONATOMIC_IOSONLY) INPersonHandleType type;
@property (readonly, nullable, NS_NONATOMIC_IOSONLY) INPersonHandleLabel label API_AVAILABLE(ios(10.2), macosx(10.12.2));

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithValue:(NSString *)value type:(INPersonHandleType)type label:(nullable INPersonHandleLabel)label NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithValue:(NSString *)value type:(INPersonHandleType)type;

@end

NS_ASSUME_NONNULL_END
