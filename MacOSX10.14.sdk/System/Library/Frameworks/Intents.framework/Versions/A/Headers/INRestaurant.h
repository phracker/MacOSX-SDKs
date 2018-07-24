//
//  INRestaurant.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntent.h>
#import <CoreLocation/CoreLocation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INRestaurant : NSObject <NSSecureCoding, NSCopying>

- (instancetype)initWithLocation:(CLLocation *)location name:(NSString *)name vendorIdentifier:(NSString *)vendorIdentifier restaurantIdentifier:(NSString *)restaurantIdentifier NS_DESIGNATED_INITIALIZER;

@property (copy, NS_NONATOMIC_IOSONLY) CLLocation *location;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *name;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *vendorIdentifier; // provider's vendor identifier
@property (copy, NS_NONATOMIC_IOSONLY) NSString *restaurantIdentifier; // vendor specific restaurant identifier. should match what Maps is ingesting through its data pipeline for the vendor.

@end
NS_ASSUME_NONNULL_END
