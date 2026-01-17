//
//  INIntentResolution.h
//  Intents
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INIntentResolutionResult<ObjectType> : NSObject

- (instancetype)init NS_UNAVAILABLE;

// This result is to tell Siri that the user must provide a non-nil value for this parameter in order to continue
+ (instancetype)needsValue NS_SWIFT_NAME(needsValue());

// This result is to tell Siri to continue whether or the user has provided a value for this parameter
+ (instancetype)notRequired NS_SWIFT_NAME(notRequired());

// This result is for informing Siri that this value is unsupported
+ (instancetype)unsupported NS_SWIFT_NAME(unsupported());

@end

NS_ASSUME_NONNULL_END
