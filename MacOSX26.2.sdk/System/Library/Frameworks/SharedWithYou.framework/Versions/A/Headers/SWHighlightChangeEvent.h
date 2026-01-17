#import <TargetConditionals.h>
#if !TARGET_OS_TV
//  Copyright (c) 2022 Apple. All rights reserved.

#import <Foundation/Foundation.h>
#import <SharedWithYou/SWHighlight.h>
#import <SharedWithYou/SWHighlightEvent.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SWHighlightChangeEventTrigger) {
    SWHighlightChangeEventTriggerEdit = 1,
    SWHighlightChangeEventTriggerComment = 2,
} API_AVAILABLE(ios(16.0), macos(13.0));

/*!
 @class SWHighlightChangeEvent
 @abstract A model object representing activity that has happened on some content.
 */
API_AVAILABLE(ios(16.0), macos(13.0))
SW_EXTERN @interface SWHighlightChangeEvent : NSObject <SWHighlightEvent>

// The type of change event for the highlight.
@property (nonatomic, readonly, assign) SWHighlightChangeEventTrigger changeEventTrigger;

/// Initializes a highlight change event object to represent changes to a highlight.
/// @param highlight The object on which the event occurred.
/// @param trigger The trigger change event for the highlight.
- (instancetype)initWithHighlight:(SWHighlight *)highlight trigger:(SWHighlightChangeEventTrigger)trigger;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, readonly, copy) NSURL *highlightURL;

@end

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_TV
