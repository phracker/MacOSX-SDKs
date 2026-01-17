//  
//  CalTask.h
//	CalendarStore Framework
//  
//  Copyright 2006 Apple Inc. All rights reserved.
//  
//  This class allows the client to access data about a specific CalTask.
//
//  The CalendarStore framework is deprecated.  Please use the EventKit framework instead.


#import <CalendarStore/CalCalendarItem.h>

//  The iCalendar specification allows priority to be specified with an integer in the range of 0-9, with 0 representing
//  an undefined priority, 1 the highest priority, and 9 the lowest priority. When a user sets the priority to high, 
//  medium or low in iCal saves the priority as 1, 5, or 9 respectively. Clients are encouraged to use these values when
//  setting a task's priority, but is is possible to specify any integer value from 0 to 9. In iCal, a task with a 
//  priority in the range of 1-4 will show up as high priority, a task with a priority of 5 will be displayed as having
//  medium priority, and 6-9 will be  displayed as having a low priority.

enum {
    CalPriorityNone     = 0,
    CalPriorityHigh     = 1,
    CalPriorityMedium   = 5,
    CalPriorityLow      = 9
};

typedef NSUInteger CalPriority;

@interface CalTask : CalCalendarItem {
    @private
    NSDate *_dueDate;
    CalPriority _priority;
    NSDate *_completedDate;
}

//  The calendar property must be set before calling saveTask on a new task
+ (id)task;

@property(copy) NSDate *dueDate NS_DEPRECATED_MAC(10_5, 10_8);
@property CalPriority priority NS_DEPRECATED_MAC(10_5, 10_8);

//  These two properties are inextricably linked.  Setting isCompleted to be YES, will set the completedDate to be now,
//  and setting any completedDate will change isCompleted to be YES. Similarly, setting isCompleted to be NO will set
//  the completedDate to be nil, and setting the completedDate changes isCompleted to NO.
@property BOOL isCompleted NS_DEPRECATED_MAC(10_5, 10_8);
@property(copy) NSDate *completedDate NS_DEPRECATED_MAC(10_5, 10_8);

@end
