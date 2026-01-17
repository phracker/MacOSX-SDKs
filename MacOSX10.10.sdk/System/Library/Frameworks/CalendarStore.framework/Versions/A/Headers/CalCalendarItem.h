//
//  CalCalendarItem.h
//	Calendar Store Framework
//
//  Copyright 2006 Apple Inc. All rights reserved.
//
//  This class and its subclasses should be used to get information about CalEvent and CalTasks. Accessors for 
//  properties common to both of these classes are included here.
//
//  The Calendar Store framework is deprecated.  Please use the Event Kit framework instead.

@class CalAlarm;
@class CalCalendar;

@interface CalCalendarItem : NSObject <NSCopying> {
    @protected
	id _objectID;
    void *_reserved;
    CalCalendar *_calendar;
    NSString *_notes;
    NSURL *_url;
    NSString *_title;
    NSString *_uid;
    NSDate *_dateStamp;
    NSArray *_alarms;
}

- (BOOL)hasAlarm NS_DEPRECATED_MAC(10_5, 10_8);
- (NSDate *)nextAlarmDate NS_DEPRECATED_MAC(10_5, 10_8);

@property(retain) CalCalendar *calendar NS_DEPRECATED_MAC(10_5, 10_8);
@property(copy) NSString *notes NS_DEPRECATED_MAC(10_5, 10_8);
@property(copy) NSURL *url NS_DEPRECATED_MAC(10_5, 10_8);
@property(copy) NSString *title NS_DEPRECATED_MAC(10_5, 10_8);

@property(copy, readonly) NSString *uid NS_DEPRECATED_MAC(10_5, 10_8);
@property(copy, readonly) NSDate *dateStamp NS_DEPRECATED_MAC(10_5, 10_8);

@property(copy) NSArray *alarms NS_DEPRECATED_MAC(10_5, 10_8);                // An array of CalAlarms

- (void) addAlarm:(CalAlarm *)alarm NS_DEPRECATED_MAC(10_5, 10_8);
- (void) addAlarms:(NSArray *)alarms NS_DEPRECATED_MAC(10_5, 10_8);
- (void) removeAlarm:(CalAlarm *)alarm NS_DEPRECATED_MAC(10_5, 10_8);
- (void) removeAlarms:(NSArray *)alarms NS_DEPRECATED_MAC(10_5, 10_8);

@end
