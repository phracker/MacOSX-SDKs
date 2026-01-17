//
//	CalAlarm.h
//	Calendar Store Framework
//
//	Copyright 2006 Apple Inc. All rights reserved.
//
//  The Calendar Store framework is deprecated.  Please use the Event Kit framework instead.

extern NSString * const CalAlarmActionDisplay NS_DEPRECATED_MAC(10_5, 10_8);
extern NSString * const CalAlarmActionEmail NS_DEPRECATED_MAC(10_5, 10_8);
extern NSString * const CalAlarmActionProcedure NS_DEPRECATED_MAC(10_5, 10_8);
extern NSString * const CalAlarmActionSound NS_DEPRECATED_MAC(10_5, 10_8);


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

+ (id)alarm NS_DEPRECATED_MAC(10_5, 10_8);

- (void)setAcknowledged:(NSDate *)date NS_DEPRECATED_MAC(10_5, 10_8);
- (NSDate *)acknowledged NS_DEPRECATED_MAC(10_5, 10_8);
- (void)setRelatedTo:(NSString *)relatedTo NS_DEPRECATED_MAC(10_5, 10_8);
- (NSString *)relatedTo NS_DEPRECATED_MAC(10_5, 10_8);

@property(copy, nonatomic) NSString *action NS_DEPRECATED_MAC(10_5, 10_8);

//  Setting a sound will also set the action to CalAlarmSound as well as set the emailAddress and URL to nil.  Expects 
//  the name of a system alert. See NSSound.
@property(copy, nonatomic) NSString *sound NS_DEPRECATED_MAC(10_5, 10_8);

//  Setting an emailAddress will also set the action to CalAlarmEmail as well as set the sound and URL to nil.
@property(copy, nonatomic) NSString *emailAddress NS_DEPRECATED_MAC(10_5, 10_8);

//  Setting a URL will also set the action to CalAlarmProcedure as well as set the emailAddress and sound to nil.  The 
//  URL must be a file URL.
@property(copy, nonatomic) NSURL *url NS_DEPRECATED_MAC(10_5, 10_8);

//  The time that an alarm goes off is referred to as the trigger. Alarms have either a relative trigger, which means 
//  the alarm fires a certain number of seconds before an alarm occurs, or an absolute trigger, which specifies the 
//  exact time the alarm will trigger off.

//  Setting a relativeTrigger will also set the absoluteTrigger to nil.
@property (nonatomic) NSTimeInterval relativeTrigger NS_DEPRECATED_MAC(10_5, 10_8);

//  Setting an absoluteTrigger will also set the relativeTrigger to nil.
@property(copy, nonatomic) NSDate *absoluteTrigger NS_DEPRECATED_MAC(10_5, 10_8);

- (NSDate *)triggerDateRelativeTo:(NSDate *)date NS_DEPRECATED_MAC(10_5, 10_8);

@end
