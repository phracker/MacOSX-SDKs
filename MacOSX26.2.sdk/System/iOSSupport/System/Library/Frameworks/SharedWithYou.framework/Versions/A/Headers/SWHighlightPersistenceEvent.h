#import <TargetConditionals.h>
#if !TARGET_OS_TV
//  Copyright (c) 2022 Apple. All rights reserved.


#import <Foundation/Foundation.h>
#import <SharedWithYou/SWHighlight.h>
#import <SharedWithYou/SWHighlightEvent.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SWHighlightPersistenceEventTrigger) {
    SWHighlightPersistenceEventTriggerCreated = 1,
    SWHighlightPersistenceEventTriggerDeleted = 2,
    SWHighlightPersistenceEventTriggerRenamed = 3,
    SWHighlightPersistenceEventTriggerMoved = 4,
} API_AVAILABLE(ios(16.0), macos(13.0));

/*!
 @class SWHighlightPersistenceEvent
 @abstract A model object representing a persistence event that has happened on some content.
 */
API_AVAILABLE(ios(16.0), macos(13.0))
SW_EXTERN @interface SWHighlightPersistenceEvent : NSObject <SWHighlightEvent>

// The type of persistence event for the highlight.
@property (nonatomic, readonly, assign) SWHighlightPersistenceEventTrigger persistenceEventTrigger;

/// Initializes a highlight persistence event object when the highlight persistence is changed.
/// @param highlight The object on which the event occurred.
/// @param trigger The trigger persistence event for the highlight.
- (instancetype)initWithHighlight:(SWHighlight *)highlight trigger:(SWHighlightPersistenceEventTrigger)trigger;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_TV
