//
//	CalAlarm.h
//	Calendar Store Framework
//
//	Copyright 2006 Apple Computer, Inc. All rights reserved.

extern NSString * const CalAlarmActionDisplay;
extern NSString * const CalAlarmActionEmail;
extern NSString * const CalAlarmActionProcedure;
extern NSString * const CalAlarmActionSound;

@interface CalAlarm : NSObject <NSCopying>
{
    @private
    id _objectID;
    void *_reserved;
    NSString *_action;
    NSString *_sound;
    NSString *_emailAddress; 
    NSURL *_url;
    NSTimeInterval _relativeTrigger;
    NSDate *_absoluteTrigger;
}

+ (id)alarm;

@property(copy) NSString *action;

//  Setting a sound will also set the action to CalAlarmSound as well as set the emailAddress and URL to nil.  Expects 
//  the name of a system alert. See NSSound.
@property(copy) NSString *sound;

//  Setting an emailAddress will also set the action to CalAlarmEmail as well as set the sound and URL to nil.
@property(copy) NSString *emailAddress; 

//  Setting a URL will also set the action to CalAlarmProcedure as well as set the emailAddress and sound to nil.  The 
//  URL must be a file URL.
@property(copy) NSURL *url;

//  The time that an alarm goes off is referred to as the trigger. Alarms have either a relative trigger, which means 
//  the alarm fires a certain number of seconds before an alarm occurs, or an absolute trigger, which specifies the 
//  exact time the alarm will trigger off.

//  Setting a relativeTrigger will also set the absoluteTrigger to nil.
@property NSTimeInterval relativeTrigger;

//  Setting an absoluteTrigger will also set the relativeTrigger to nil.
@property(copy) NSDate *absoluteTrigger;

- (NSDate *)triggerDateRelativeTo:(NSDate *)date;

@end
