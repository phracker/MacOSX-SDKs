//
//  EKSource.h
//  EventKit
//
//  Copyright 2009-2011 Apple Inc. All rights reserved.
//

#import <EventKit/EventKitDefines.h>
#import <EventKit/EKObject.h>
#import <EventKit/EKTypes.h>

EVENTKIT_CLASS_AVAILABLE(10_8, 5_0)
@interface EKSource : EKObject

@property(nonatomic, readonly) NSString        *sourceIdentifier;
@property(nonatomic, readonly) EKSourceType     sourceType;
@property(nonatomic, readonly) NSString        *title;

/*!
    @method     calendarsForEntityType
    @abstract   Returns the calendars that belong to this source that 
                support a given entity type (reminders, events)
 */
- (NSSet *)calendarsForEntityType:(EKEntityType)entityType __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);

@end
