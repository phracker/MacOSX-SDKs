//
//  EKRecurrenceEnd.h
//  EventKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <EventKit/EventKitDefines.h>

/*!
    @class      EKRecurrenceEnd
    @abstract   Class which represents when a recurrence should end.
    @discussion EKRecurrenceEnd is an attribute of EKRecurrenceRule that defines how long
                the recurrence is scheduled to repeat. The recurrence can be defined either
                with an NSUInteger that indicates the total number times it repeats, or with
                an NSDate, after which it no longer repeats. An event which is set to never
                end should have its EKRecurrenceEnd set to nil.
                 
                If the end of the pattern is defines with an NSDate, the client must pass a
                valid NSDate, nil cannot be passed. If the end of the pattern is defined as
                terms of a number of occurrences, the occurrenceCount passed to the initializer
                must be positive, it cannot be 0. If the client attempts to initialize a
                EKRecurrenceEnd with a nil NSDate or OccurrenceCount of 0, an exception is raised.
                 
                A EKRecurrenceEnd initialized with an end date will return 0 for occurrenceCount.
                One initialized with a number of occurrences will return nil for its endDate.
*/
EVENTKIT_CLASS_AVAILABLE(10_8, 4_0)
@interface EKRecurrenceEnd : NSObject <NSCopying> {
}

/*!
    @method     recurrenceEndWithEndDate:
    @abstract   Creates an autoreleased recurrence end with a specific end date.
*/
+ (id)recurrenceEndWithEndDate:(NSDate *)endDate;

/*!
    @method     recurrenceEndWithOccurrenceCount:
    @abstract   Creates an autoreleased recurrence end with a maximum occurrence count.
*/
+ (id)recurrenceEndWithOccurrenceCount:(NSUInteger)occurrenceCount;

/*!
    @property   endDate
    @abstract   The end date of this recurrence, or nil if it's count-based.
*/
@property(nonatomic, readonly) NSDate *endDate;

/*!
    @property   occurrenceCount
    @abstract   The maximum occurrence count, or 0 if it's date-based.
*/
@property(nonatomic, readonly) NSUInteger occurrenceCount;

@end
