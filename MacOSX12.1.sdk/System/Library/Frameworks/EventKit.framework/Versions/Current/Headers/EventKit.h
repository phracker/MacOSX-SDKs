/*
 *  EventKit.h
 *  EventKit
 *
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#import <TargetConditionals.h>
#import <Availability.h>

#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED || !TARGET_OS_IPHONE

#import <EventKit/EventKitDefines.h>
#import <EventKit/EKTypes.h>
#import <EventKit/EKAlarm.h>
#import <EventKit/EKEventStore.h>
#import <EventKit/EKCalendar.h>
#import <EventKit/EKError.h>
#import <EventKit/EKEvent.h>
#import <EventKit/EKParticipant.h>
#import <EventKit/EKRecurrenceRule.h>
#import <EventKit/EKReminder.h>
#import <EventKit/EKSource.h>
#import <EventKit/EKStructuredLocation.h>
#import <EventKit/EKVirtualConferenceProvider.h>

#endif //#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED

