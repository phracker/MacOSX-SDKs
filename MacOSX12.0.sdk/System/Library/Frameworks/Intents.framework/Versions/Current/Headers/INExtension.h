//
//  INExtension.h
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INIntentHandlerProviding.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), macos(11.0), watchos(3.2), tvos(14.0))
@interface INExtension : NSObject <INIntentHandlerProviding>
@end

NS_ASSUME_NONNULL_END
