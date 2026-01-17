//
//  CNChangeHistoryEvent.h
//  Contacts
//
//  Copyright (c) 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CNChangeHistoryEventVisitor;
@class CNContact;
@class CNGroup;

API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0))
@interface CNChangeHistoryEvent : NSObject <NSCopying, NSSecureCoding>

- (void)acceptEventVisitor:(id<CNChangeHistoryEventVisitor>)visitor;

@end

/// Drop all cached information your app has persisted
API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0))
@interface CNChangeHistoryDropEverythingEvent : CNChangeHistoryEvent
@end

/// A contact was added
API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0))
@interface CNChangeHistoryAddContactEvent : CNChangeHistoryEvent
@property (readonly, strong, nonatomic) CNContact * contact;
@property (readonly, strong, nonatomic, nullable) NSString * containerIdentifier;
@end

/// A contact was updated
API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0))
@interface CNChangeHistoryUpdateContactEvent : CNChangeHistoryEvent
@property (readonly, strong, nonatomic) CNContact * contact;
@end

/// A contact was removed
API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0))
@interface CNChangeHistoryDeleteContactEvent : CNChangeHistoryEvent
@property (readonly, strong, nonatomic) NSString * contactIdentifier;
@end

/// A group was added
API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0))
@interface CNChangeHistoryAddGroupEvent : CNChangeHistoryEvent
@property (readonly, strong, nonatomic) CNGroup * group;
@property (readonly, strong, nonatomic) NSString * containerIdentifier;
@end

/// A group was updated
API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0))
@interface CNChangeHistoryUpdateGroupEvent : CNChangeHistoryEvent
@property (readonly, strong, nonatomic) CNGroup * group;
@end

/// A group was deleted
API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0))
@interface CNChangeHistoryDeleteGroupEvent : CNChangeHistoryEvent
@property (readonly, strong, nonatomic) NSString * groupIdentifier;
@end

/// A contact was added to a group
API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0))
@interface CNChangeHistoryAddMemberToGroupEvent : CNChangeHistoryEvent
@property (readonly, strong, nonatomic) CNContact * member;
@property (readonly, strong, nonatomic) CNGroup * group;
@end

/// A contact was removed from a group
API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0))
@interface CNChangeHistoryRemoveMemberFromGroupEvent : CNChangeHistoryEvent
@property (readonly, strong, nonatomic) CNContact * member;
@property (readonly, strong, nonatomic) CNGroup * group;
@end

/// A subgroup was added to a group
API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0))
@interface CNChangeHistoryAddSubgroupToGroupEvent : CNChangeHistoryEvent
@property (readonly, strong, nonatomic) CNGroup * subgroup;
@property (readonly, strong, nonatomic) CNGroup * group;
@end

/// A subgroup was removed from a group
API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0))
@interface CNChangeHistoryRemoveSubgroupFromGroupEvent : CNChangeHistoryEvent
@property (readonly, strong, nonatomic) CNGroup * subgroup;
@property (readonly, strong, nonatomic) CNGroup * group;
@end


API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0))
@protocol CNChangeHistoryEventVisitor <NSObject>

- (void)visitDropEverythingEvent:(CNChangeHistoryDropEverythingEvent *)event;

- (void)visitAddContactEvent:(CNChangeHistoryAddContactEvent *)event;
- (void)visitUpdateContactEvent:(CNChangeHistoryUpdateContactEvent *)event;
- (void)visitDeleteContactEvent:(CNChangeHistoryDeleteContactEvent *)event;

@optional
- (void)visitAddGroupEvent:(CNChangeHistoryAddGroupEvent *)event;
- (void)visitUpdateGroupEvent:(CNChangeHistoryUpdateGroupEvent *)event;
- (void)visitDeleteGroupEvent:(CNChangeHistoryDeleteGroupEvent *)event;

- (void)visitAddMemberToGroupEvent:(CNChangeHistoryAddMemberToGroupEvent *)event;
- (void)visitRemoveMemberFromGroupEvent:(CNChangeHistoryRemoveMemberFromGroupEvent *)event;
- (void)visitAddSubgroupToGroupEvent:(CNChangeHistoryAddSubgroupToGroupEvent *)event;
- (void)visitRemoveSubgroupFromGroupEvent:(CNChangeHistoryRemoveSubgroupFromGroupEvent *)event;

@end

NS_ASSUME_NONNULL_END
