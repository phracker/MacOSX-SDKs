//
//  INIntentResolution.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), macos(11.0), watchos(3.2), tvos(14.0))
@interface INIntentResolutionResult : NSObject

- (instancetype)init NS_UNAVAILABLE;

// This result is to tell Siri that the user must provide a non-nil value for this parameter in order to continue
+ (instancetype)needsValue NS_SWIFT_NAME(needsValue());

// This result is to tell Siri to continue regardless of whether the user has provided a value for this parameter or not
+ (instancetype)notRequired NS_SWIFT_NAME(notRequired());

// This result is for informing Siri that this value is unsupported
+ (instancetype)unsupported NS_SWIFT_NAME(unsupported());

@end

NS_ASSUME_NONNULL_END
