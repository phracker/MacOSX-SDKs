//
//  CalAttendee.h
//	CalendarStore Framework
//
//  Copyright 2006 Apple Inc. All rights reserved.
//
//  The CalendarStore framework is deprecated.  Please use the EventKit framework instead.

#import <Foundation/Foundation.h>

//  These constants are used to describe the user's confirmation status for an attendee. For now, it is not possible to 
//  modify an event's attendees or the attendees themselves.

extern NSString * const CalAttendeeStatusNeedsAction;   // This is the default status for an attendee
extern NSString * const CalAttendeeStatusAccepted;
extern NSString * const CalAttendeeStatusDeclined;
extern NSString * const CalAttendeeStatusTentative;

@interface CalAttendee : NSObject <NSCopying>

@property(readonly) NSURL *address NS_DEPRECATED_MAC(10_5, 10_8);
@property(readonly) NSString *commonName NS_DEPRECATED_MAC(10_5, 10_8);  // The user-entered name of the attendee. 
@property(readonly) NSString *status NS_DEPRECATED_MAC(10_5, 10_8);      // The attendee status, one of the CalAttendeeStatuses defined above

@end
