//
//  INRestaurantReservationBooking.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Foundation/Foundation.h>
#import <Intents/INRestaurant.h>
#import <Intents/INRestaurantOffer.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
// represents a booking at a restaurant during a given time for a given party size
@interface INRestaurantReservationBooking : NSObject <NSSecureCoding, NSCopying>

- (instancetype)initWithRestaurant:(INRestaurant *)restaurant bookingDate:(NSDate *)bookingDate partySize:(NSUInteger)partySize bookingIdentifier:(NSString *)bookingIdentifier NS_DESIGNATED_INITIALIZER;

@property (copy, NS_NONATOMIC_IOSONLY) INRestaurant *restaurant;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *bookingDescription; // A nullable string describing the booking
@property (copy, NS_NONATOMIC_IOSONLY) NSDate *bookingDate;
@property (NS_NONATOMIC_IOSONLY) NSUInteger partySize;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *bookingIdentifier; // A vendor specific identifier that refers to this booking.
@property (getter = isBookingAvailable, NS_NONATOMIC_IOSONLY) BOOL bookingAvailable; // Boolean indicating whether timeslot is available for booking. Defaults to YES.
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSArray <INRestaurantOffer *> *offers;
@property (NS_NONATOMIC_IOSONLY) BOOL requiresManualRequest; // YES means restaurant must be contacted by phone before confirmation is given. Defaults to NO.
@property (NS_NONATOMIC_IOSONLY) BOOL requiresEmailAddress; // YES means an email address is required to book. Defaults to NO.
@property (NS_NONATOMIC_IOSONLY) BOOL requiresName; // YES means a name is required to book. Defaults to NO.
@property (NS_NONATOMIC_IOSONLY) BOOL requiresPhoneNumber; // YES means a phone number required to book. Defaults to NO.

@end
NS_ASSUME_NONNULL_END
