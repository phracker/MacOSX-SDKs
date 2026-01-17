//
//  CalCalendarItem.h
//	Calendar Store Framework
//
//  Copyright 2006 Apple Computer, Inc. All rights reserved.
//
//  This class and its subclasses should be used to get information about CalEvent and CalTasks. Accessors for 
//  properties common to both of these classes are included here.

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

- (BOOL)hasAlarm;
- (NSDate *)nextAlarmDate;

@property(retain) CalCalendar *calendar;
@property(copy) NSString *notes;
@property(copy) NSURL *url;
@property(copy) NSString *title;

@property(readonly) NSString *uid;
@property(readonly) NSDate *dateStamp;

@property(copy) NSArray *alarms;                // An array of CalAlarms

- (void) addAlarm:(CalAlarm *)alarm;
- (void) addAlarms:(NSArray *)alarms;
- (void) removeAlarm:(CalAlarm *)alarm;
- (void) removeAlarms:(NSArray *)alarms;

@end
