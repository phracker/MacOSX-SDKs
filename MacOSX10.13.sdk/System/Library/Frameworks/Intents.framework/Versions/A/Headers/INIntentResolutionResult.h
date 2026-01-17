//
//  INIntentResolution.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INIntentResolutionResult<ObjectType> : NSObject

- (instancetype)init NS_UNAVAILABLE;

// This result is to tell Siri that the user must provide a non-nil value for this parameter in order to continue
+ (instancetype)needsValue NS_SWIFT_NAME(needsValue());

// This result is to tell Siri to continue regardless of whether the user has provided a value for this parameter or not
+ (instancetype)notRequired NS_SWIFT_NAME(notRequired());

// This result is for informing Siri that this value is unsupported
+ (instancetype)unsupported NS_SWIFT_NAME(unsupported());

@end

NS_ASSUME_NONNULL_END
