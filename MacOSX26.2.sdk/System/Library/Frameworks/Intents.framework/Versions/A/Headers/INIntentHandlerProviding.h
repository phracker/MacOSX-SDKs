//
//  INIntentHandlerProviding.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INIntent;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), macos(11.0), watchos(3.2), tvos(14.0))
@protocol INIntentHandlerProviding <NSObject>

// Override this function to provide classes other than the extension's principal class to handle a given intent
- (nullable id)handlerForIntent:(INIntent *)intent;

@end

NS_ASSUME_NONNULL_END
