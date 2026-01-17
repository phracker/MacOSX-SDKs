#import <TargetConditionals.h>
#if !TARGET_OS_TV
//  Copyright (c) 2022 Apple. All rights reserved.

#import <Foundation/Foundation.h>
#import <SharedWithYou/SWHighlight.h>
#import <SharedWithYou/SWHighlightEvent.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SWHighlightMembershipEventTrigger) {
    SWHighlightMembershipEventTriggerAddedCollaborator = 1,
    SWHighlightMembershipEventTriggerRemovedCollaborator = 2,
} API_AVAILABLE(ios(16.0), macos(13.0));

/*!
 @class SWHighlightMembershipEvent
 @abstract A model object representing a membership event that has happened on some content.
 */
API_AVAILABLE(ios(16.0), macos(13.0))
SW_EXTERN @interface SWHighlightMembershipEvent : NSObject <SWHighlightEvent>

/// The type of membership event for the highlight.
@property (nonatomic, readonly, assign) SWHighlightMembershipEventTrigger membershipEventTrigger;

/// Initializes a highlight membership event object to represent changes to a highlight membership.
/// @param highlight The object on which the event occurred.
/// @param trigger The trigger membership event for the highlight.
- (instancetype)initWithHighlight:(SWHighlight *)highlight trigger:(SWHighlightMembershipEventTrigger)trigger;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_TV
