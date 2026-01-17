//
//  CalendarErrors.h
//  CalendarStore Framework
//
//  Copyright 2006 Apple Inc. All rights reserved.
//
//  The CalendarStore framework is deprecated.  Please use the EventKit framework instead.

#import <Foundation/Foundation.h>

extern NSString *const CalCalendarStoreErrorDomain NS_DEPRECATED_MAC(10_5, 10_8);

enum {
	// Calendar saving and modification errors
	CalCalendarNotEditableError = 1025,     //  Events and tasks cannot be added to an uneditable calendar
	CalDateInvalidError = 1026,             //  The start date of an event must be earlier than its end date
    CalCalendarNotInRepository = 1027,      //  Events' and tasks' calendar property must be a calendar in the user's calendar store
	CalCalendarTitleNotUniqueError = 1028   //  Calendar titles must be unique
};
