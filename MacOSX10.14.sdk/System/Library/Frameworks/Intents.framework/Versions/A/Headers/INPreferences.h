//
//  INPreferences.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INSiriAuthorizationStatus.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx)
@interface INPreferences : NSObject

+ (INSiriAuthorizationStatus)siriAuthorizationStatus NS_EXTENSION_UNAVAILABLE("siriAuthorizationStatus is not available to extensions. The main app is responsible for Siri authorization.") API_UNAVAILABLE(watchos);
+ (void)requestSiriAuthorization:(void (^)(INSiriAuthorizationStatus status))handler NS_EXTENSION_UNAVAILABLE("requestSiriAuthorization is not available to extensions. The main app is responsible for Siri authorization.") API_UNAVAILABLE(watchos);
+ (NSString *)siriLanguageCode;

@end

NS_ASSUME_NONNULL_END
