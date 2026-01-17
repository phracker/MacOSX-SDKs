//
//  INTermsAndConditions.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macos, watchos, tvos)
@interface INTermsAndConditions : NSObject <NSSecureCoding, NSCopying>

- (instancetype)initWithLocalizedTermsAndConditionsText:(NSString *)localizedTermsAndConditionsText privacyPolicyURL:(nullable NSURL*)privacyPolicyURL termsAndConditionsURL:(nullable NSURL *)termsAndConditionsURL NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) NSString *localizedTermsAndConditionsText; // A string that contains a summary of the vendor's terms and conditions.
@property (readonly, nullable, NS_NONATOMIC_IOSONLY) NSURL *privacyPolicyURL; // An optional URL that links to the vendor's privacy policy.
@property (readonly, nullable, NS_NONATOMIC_IOSONLY) NSURL *termsAndConditionsURL; // An optional URL that links to the vendor's full terms and conditions.

@end
NS_ASSUME_NONNULL_END
