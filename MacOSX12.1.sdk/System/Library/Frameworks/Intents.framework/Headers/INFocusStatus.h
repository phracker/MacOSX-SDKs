//
//  INFocusStatus.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(15.0), macos(12.0), watchos(8.0))
API_UNAVAILABLE(tvos)
@interface INFocusStatus : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithIsFocused:(nullable NSNumber *)isFocused NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *isFocused NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
