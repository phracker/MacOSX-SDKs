//
//  INSaveProfileInCarIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INSaveProfileInCarIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INSaveProfileInCarIntent (Deprecated)

- (instancetype)initWithProfileNumber:(nullable NSNumber *)profileNumber
                         profileLabel:(nullable NSString *)profileLabel API_DEPRECATED("Use `-initWithProfileNumber:profileName:` method instead.", ios(10.0, 10.2)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *profileLabel API_DEPRECATED("Use `profileName` property instead.", ios(10.0, 10.2)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END
