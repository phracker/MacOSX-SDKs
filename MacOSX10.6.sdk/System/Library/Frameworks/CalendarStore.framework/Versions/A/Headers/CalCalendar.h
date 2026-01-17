//	
//	CalCalendar.h
//	Calendar Store Framework
//	
//  Copyright 2006 Apple Computer, Inc. All rights reserved.
//	
//	This class can be used to get attributes of a calendar, but cannot be used to get the list of events or tasks in a calendar. 
//	Instead use CalCalendarStore's eventsFromPredicate: and tasksFromPredicate: methods.

@class NSColor;

extern NSString * const CalCalendarTypeBirthday;
extern NSString * const CalCalendarTypeCalDAV;
extern NSString * const CalCalendarTypeLocal;
extern NSString * const CalCalendarTypeSubscription;
extern NSString * const CalCalendarTypeIMAP;
extern NSString * const CalCalendarTypeExchange AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@interface CalCalendar : NSObject <NSCopying>
{
    @private
    id _objectID;
	id _group;
    void *_reserved;
	NSColor *_color;
	NSString *_notes;
	NSString *_title;
	NSString *_type;
	NSString *_uid;
	BOOL _isEditable;
}

//  All calendars created with this API will be of type CalCalendarTypeLocal
+ (id)calendar;

@property(copy) NSColor *color;
@property(copy) NSString *notes;
@property(copy) NSString *title;
@property(readonly) NSString *type;
@property(readonly) NSString *uid;
@property(readonly) BOOL isEditable;

@end
