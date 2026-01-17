//
//  NSExtensionContext+ShareExtension.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class INIntent;

@interface NSExtensionContext (ShareExtension)

@property (readonly, strong, nullable, NS_NONATOMIC_IOSONLY) INIntent *intent API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macos, tvos);

@end

NS_ASSUME_NONNULL_END
