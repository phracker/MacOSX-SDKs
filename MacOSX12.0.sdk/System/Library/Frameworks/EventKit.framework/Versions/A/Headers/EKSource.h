//
//  EKSource.h
//  EventKit
//
//  Copyright 2009-2011 Apple Inc. All rights reserved.
//

#import <EventKit/EventKitDefines.h>
#import <EventKit/EKObject.h>
#import <EventKit/EKTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class EKCalendar;

NS_CLASS_AVAILABLE(10_8, 5_0)
@interface EKSource : EKObject

@property(nonatomic, readonly) NSString        *sourceIdentifier;
@property(nonatomic, readonly) EKSourceType     sourceType;
@property(nonatomic, readonly) NSString        *title;
/*!
 @property    calendars
 @abstract    This is now deprecated in favor of -[EKSource calendarsForEntityType:]
 */
@property(nonatomic, readonly) NSSet<EKCalendar *> *calendars NS_DEPRECATED(NA, NA, 4_0, 6_0);


/*!
 @method      calendarsForEntityType
 @abstract    Returns the calendars that belong to this source that 
              support a given entity type (reminders, events)
 */
- (NSSet<EKCalendar *> *)calendarsForEntityType:(EKEntityType)entityType NS_AVAILABLE(10_8, 6_0);

@end

NS_ASSUME_NONNULL_END
