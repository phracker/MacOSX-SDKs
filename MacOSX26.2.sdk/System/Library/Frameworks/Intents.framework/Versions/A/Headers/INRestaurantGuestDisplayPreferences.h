//
//  INRestaurantGuestDisplayPreferences.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Foundation/Foundation.h>

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macos, watchos, tvos)
@interface INRestaurantGuestDisplayPreferences : NSObject <NSSecureCoding, NSCopying>

@property (NS_NONATOMIC_IOSONLY) BOOL nameFieldFirstNameOptional; // indicates whether first name field is marked optional, defaults to NO
@property (NS_NONATOMIC_IOSONLY) BOOL nameFieldLastNameOptional; // indicates whether last name field is marked optional, defaults to NO

@property (NS_NONATOMIC_IOSONLY) BOOL nameFieldShouldBeDisplayed; // indicates whether name input field should be displayed, defaults to YES
@property (NS_NONATOMIC_IOSONLY) BOOL emailAddressFieldShouldBeDisplayed; // indicates whether email address input field should be displayed, defaults to YES
@property (NS_NONATOMIC_IOSONLY) BOOL phoneNumberFieldShouldBeDisplayed; // indicates whether phone number field should be displayed, defaults to YES

@property (NS_NONATOMIC_IOSONLY) BOOL nameEditable; // indicates whether the name field should be user editable, defaults to YES
@property (NS_NONATOMIC_IOSONLY) BOOL emailAddressEditable; // indicates whether the email address field should be user editable, defaults to YES
@property (NS_NONATOMIC_IOSONLY) BOOL phoneNumberEditable; // indicates whether the phone number field should be user editable, defaults to YES

@end
