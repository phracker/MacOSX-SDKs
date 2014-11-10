//
//  CalAttendee.h
//	Calendar Store Framework
//
//  Copyright 2006 Apple Inc. All rights reserved.
//
//  The Calendar Store framework is deprecated.  Please use the Event Kit framework instead.

//  These constants are used to describe the user's confirmation status for an attendee. For now, it is not possible to 
//  modify an event's attendees or the attendees themselves.

extern NSString * const CalAttendeeStatusNeedsAction;   // This is the default status for an attendee
extern NSString * const CalAttendeeStatusAccepted;
extern NSString * const CalAttendeeStatusDeclined;
extern NSString * const CalAttendeeStatusTentative;

@interface CalAttendee : NSObject <NSCopying>
{
    @private
    id _objectID;
    void *_reserved;
    NSURL *_address;
    NSString *_commonName;  // The user-entered name of the attendee. 
    NSString *_status;      // The attendee status, one of the CalAttendeeStatuses defined above
}

@property(readonly) NSURL *address NS_DEPRECATED_MAC(10_5, 10_8);
@property(readonly) NSString *commonName NS_DEPRECATED_MAC(10_5, 10_8);  // The user-entered name of the attendee. 
@property(readonly) NSString *status NS_DEPRECATED_MAC(10_5, 10_8);      // The attendee status, one of the CalAttendeeStatuses defined above

@end
