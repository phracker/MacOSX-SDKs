//
//  INSetProfileInCarIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INSetProfileInCarIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INSetProfileInCarIntent (Deprecated)

- (instancetype)initWithProfileNumber:(nullable NSNumber *)profileNumber
                         profileLabel:(nullable NSString *)profileLabel
                       defaultProfile:(nullable NSNumber *)defaultProfile API_DEPRECATED_WITH_REPLACEMENT("-initWithProfileNumber:profileName:defaultProfile:", ios(10.0, 10.2)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;

- (instancetype)initWithProfileNumber:(nullable NSNumber *)profileNumber
                          profileName:(nullable NSString *)profileName
                       defaultProfile:(nullable NSNumber *)defaultProfile API_DEPRECATED_WITH_REPLACEMENT("-initWithProfileNumber:profileName:defaultProfile:carName:", ios(10.2, 12.0)) NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *profileLabel API_DEPRECATED_WITH_REPLACEMENT("profileName", ios(10.0, 10.2)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END
