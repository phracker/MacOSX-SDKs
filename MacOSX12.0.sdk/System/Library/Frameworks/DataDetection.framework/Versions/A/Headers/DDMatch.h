//
//  DDMatch.h
//  DataDetection
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <DataDetection/DataDetectionBase.h>

NS_ASSUME_NONNULL_BEGIN

DD_EXTERN API_AVAILABLE(ios(15.0)) @interface DDMatch : NSObject
@property(nonatomic, readonly) NSString *matchedString;
- (instancetype)init NS_UNAVAILABLE;
@end

DD_EXTERN API_AVAILABLE(ios(15.0)) @interface DDMatchLink : DDMatch
@property(nonatomic, readonly) NSURL *URL;
@end

DD_EXTERN API_AVAILABLE(ios(15.0)) @interface DDMatchPhoneNumber : DDMatch
@property(nonatomic, readonly) NSString *phoneNumber;
@property(nonatomic, readonly, nullable) NSString *label;
@end

DD_EXTERN API_AVAILABLE(ios(15.0)) @interface DDMatchEmailAddress : DDMatch
@property(nonatomic, readonly) NSString *emailAddress;
@property(nonatomic, readonly, nullable) NSString *label;
@end

DD_EXTERN API_AVAILABLE(ios(15.0)) @interface DDMatchPostalAddress : DDMatch
@property(nonatomic, readonly, nullable) NSString *street;
@property(nonatomic, readonly, nullable) NSString *city;
@property(nonatomic, readonly, nullable) NSString *state;
@property(nonatomic, readonly, nullable) NSString *postalCode;
@property(nonatomic, readonly, nullable) NSString *country;
@end

DD_EXTERN API_AVAILABLE(ios(15.0)) @interface DDMatchCalendarEvent : DDMatch
@property(nonatomic, readonly, getter=isAllDay) BOOL allDay;
@property(nonatomic, readonly, nullable) NSDate *startDate;
@property(nonatomic, readonly, nullable) NSTimeZone *startTimeZone;
@property(nonatomic, readonly, nullable) NSDate *endDate;
@property(nonatomic, readonly, nullable) NSTimeZone *endTimeZone;
@end

DD_EXTERN API_AVAILABLE(ios(15.0)) @interface DDMatchShipmentTrackingNumber : DDMatch
@property(nonatomic, readonly) NSString *carrier;
@property(nonatomic, readonly) NSString *trackingNumber;
@end

DD_EXTERN API_AVAILABLE(ios(15.0)) @interface DDMatchFlightNumber : DDMatch
@property(nonatomic, readonly) NSString *airline;
@property(nonatomic, readonly) NSString *flightNumber;
@end

DD_EXTERN API_AVAILABLE(ios(15.0)) @interface DDMatchMoneyAmount : DDMatch
@property(nonatomic, readonly) NSString *currency;
@property(nonatomic, readonly) double amount;
@end

NS_ASSUME_NONNULL_END
