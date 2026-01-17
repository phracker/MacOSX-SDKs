//
//  INUserContext.h
//  Intents
//
//  Copyright (c) 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(tvos, macosx)
@interface INUserContext : NSObject<NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

/// Each call replaces previous context object of the same underlying type. Use this only in your iOS/watchOS app. Do not try to set the user context as current from your Intents extension or Intents UI extension.
- (void)becomeCurrent NS_EXTENSION_UNAVAILABLE_IOS("User context is not available in extensions");

@end

NS_ASSUME_NONNULL_END
