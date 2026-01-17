//
//  INRestaurantGuest.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INPerson.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macos, watchos, tvos)
@interface INRestaurantGuest : INPerson

- (instancetype)initWithNameComponents:(nullable NSPersonNameComponents *)nameComponents phoneNumber:(nullable NSString *)phoneNumber emailAddress:(nullable NSString *)emailAddress NS_DESIGNATED_INITIALIZER;

@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *phoneNumber;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *emailAddress;

@end
NS_ASSUME_NONNULL_END
