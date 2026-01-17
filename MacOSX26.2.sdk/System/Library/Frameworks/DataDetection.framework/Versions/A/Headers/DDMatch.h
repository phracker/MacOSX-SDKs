//
//  DDMatch.h
//  DataDetection
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <DataDetection/DataDetectionBase.h>

NS_ASSUME_NONNULL_BEGIN

/// A base class for common types of data that the data detection system
/// matches.
///
/// The DataDetection framework returns results in objects that are subclasses
/// of `DDMatch`, which are specific to the type of matching data. Each object
/// contains the matched string.
_DD_EXTERN API_AVAILABLE(ios(15.0)) @interface DDMatch : NSObject

/// A substring that the data detection system identifies from an original
/// string as a common type of data.
///
/// Use `DDMatch` subclasses that the data detection system provides for a
/// semantic interpretation of this string.
@property(nonatomic, readonly) NSString *matchedString;

- (instancetype)init NS_UNAVAILABLE;
@end

/// An object that contains a web link that the data detection system matches.
///
/// The DataDetection framework returns a link match in a `DDMatchLink` object, which contains a
/// <doc://com.apple.documentation/documentation/foundation/url> (Swift) or
/// <doc://com.apple.documentation/documentation/foundation/nsurl> (Objective-C).
_DD_EXTERN API_AVAILABLE(ios(15.0)) @interface DDMatchLink : DDMatch

/// An address for a web resource, such as a webpage or image.
@property(nonatomic, readonly) NSURL *URL;
@end

/// An object that contains a phone number that the data detection system
/// matches.
///
/// The DataDetection framework returns a phone number match in a
/// `DDMatchPhoneNumber` object, which contains a phone number, and optionally a
/// label that categorizes the phone number.
_DD_EXTERN API_AVAILABLE(ios(15.0)) @interface DDMatchPhoneNumber : DDMatch

/// A string that represents a phone number.
@property(nonatomic, readonly) NSString *phoneNumber;

/// A string that categorizes a phone number, such as Home or Work.
@property(nonatomic, readonly, nullable) NSString *label;
@end

/// An object that contains an email address that the data detection system
/// matches.
///
/// The DataDetection framework returns an email match in a
/// `DDMatchEmailAddress` object, which includes an email address, and
/// optionally a label that categorizes the email address.
_DD_EXTERN API_AVAILABLE(ios(15.0)) @interface DDMatchEmailAddress : DDMatch

/// A string that represents an email address.
@property(nonatomic, readonly) NSString *emailAddress;

/// A string that categorizes an email address, such as Home or Work.
@property(nonatomic, readonly, nullable) NSString *label;
@end

/// An object that contains a postal address that the data detection system
/// matches.
///
/// The DataDetection framework returns a postal address match in a
/// `DDMatchPostalAddress` object, which optionally contains the matching parts
/// of a postal address: street, city, state, postal code, and country.
_DD_EXTERN API_AVAILABLE(ios(15.0)) @interface DDMatchPostalAddress : DDMatch

/// The street name in a postal address.
@property(nonatomic, readonly, nullable) NSString *street;

/// The city name in a postal address.
@property(nonatomic, readonly, nullable) NSString *city;

/// The state name in a postal address.
@property(nonatomic, readonly, nullable) NSString *state;

/// The postal code in a postal address.
@property(nonatomic, readonly, nullable) NSString *postalCode;

/// The country or region name in a postal address.
@property(nonatomic, readonly, nullable) NSString *country;
@end

/// An object that represents a calendar date or date range that the data
/// detection system matches.
///
/// The DataDetection framework returns a calendar event match in a
/// `DDMatchCalendarEvent` object, which has only a beginning date, only an end
/// date, or both a beginning date and an end date.
_DD_EXTERN API_AVAILABLE(ios(15.0)) @interface DDMatchCalendarEvent : DDMatch

/// A Boolean value that indicates whether the event is an all-day event.
@property(nonatomic, readonly, getter=isAllDay) BOOL allDay;

/// A date that represents the start of the event.
@property(nonatomic, readonly, nullable) NSDate *startDate;

/// The time zone for the event’s start date.
@property(nonatomic, readonly, nullable) NSTimeZone *startTimeZone;

/// A date that represents the end of the event.
@property(nonatomic, readonly, nullable) NSDate *endDate;

/// The time zone for the event’s end date.
@property(nonatomic, readonly, nullable) NSTimeZone *endTimeZone;
@end

/// An object that contains parcel tracking information that the data detection
/// system matches.
///
/// The DataDetection framework returns a shipment tracking number match in a
/// `DDMatchShipmentTrackingNumber` object, which contains a carrier name and
/// tracking identifier.
_DD_EXTERN API_AVAILABLE(ios(15.0)) @interface DDMatchShipmentTrackingNumber : DDMatch

/// The name of a parcel carrier.
@property(nonatomic, readonly) NSString *carrier;

/// A string that represents a carrier’s tracking identifier for a parcel.
@property(nonatomic, readonly) NSString *trackingNumber;
@end

/// An object that contains a flight number that the data detection system
/// matches.
///
/// The DataDetection framework returns a flight number match in a
/// `DDMatchFlightNumber` object, which contains an airline name and flight
/// number.
_DD_EXTERN API_AVAILABLE(ios(15.0)) @interface DDMatchFlightNumber : DDMatch

/// The name of an airline.
@property(nonatomic, readonly) NSString *airline;

/// A string that represents a flight number.
@property(nonatomic, readonly) NSString *flightNumber;
@end

/// An object that contains an amount of money that the data detection system
/// matches.
///
/// The DataDetection framework returns a match for an amount of money in a
/// `DDMatchMoneyAmount` object, which contains an amount of money and an ISO
/// currency code.
_DD_EXTERN API_AVAILABLE(ios(15.0)) @interface DDMatchMoneyAmount : DDMatch

/// A string that contains an ISO currency code, which the data detection system
/// identifies from the matched string and user preferences.
@property(nonatomic, readonly) NSString *currency;

/// A number that represents an amount of money.
@property(nonatomic, readonly) double amount;
@end

NS_ASSUME_NONNULL_END
