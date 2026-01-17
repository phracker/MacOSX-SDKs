//
//  BEDragInteraction.h
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <BrowserEngineKit/BEMacros.h>

#if BROWSERENGINEKIT_HAS_UIVIEW
#import <UIKit/UIDragInteraction.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class BEDragInteraction;

API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@protocol BEDragInteractionDelegate <UIDragInteractionDelegate>

@optional

/**
 *  Called when the drag interaction has begun, to allow the delegate to prepare for the drag session before
 *  the system requests drag items through `-dragInteraction:itemsForBeginningSession:`.
 *
 *  You should call the `completion` block as soon as the drag session is prepared, as to minimize the delay
 *  from the user interaction from the drag gesture. There is a system-defined timeout before the drag session is
 *  failed if the `completion` is not called in time. The `completion` block returns `YES` if the drag session did
 *  prepare successfully prepare, and `NO` otherwise, to allow clients to perform any clean-up if necessary.
 */
- (void)dragInteraction:(BEDragInteraction *)dragInteraction prepareDragSession:(id<UIDragSession>)session completion:(BOOL(^)(void))completion;

/**
 *  The asynchronous counterpart to `-dragInteraction:itemsForAddingToSession:withTouchAtPoint:` to allow
 *  touches on this view to add items to an existing drag session. Please refer to the aforementioned delegate method for its full
 *  documentation.
 *
 *  If this method is implemented, then the `UIDragInteractionDelegate` counterpart method will no longer be called.
 *
 *  You should call the `completion` block as soon as the items are ready. There is a system-defined
 *  timeout before the system will treat the delegate call as returning an empty array. The `completion` block
 *  returns `YES` if the drag session did add items to the session successfully, and `NO` otherwise, to allow
 *  clients to perform any clean-up if necessary.
 */
- (void)dragInteraction:(BEDragInteraction *)dragInteraction itemsForAddingToSession:(id<UIDragSession>)session forTouchAtPoint:(CGPoint)point completion:(BOOL(^)(NSArray<UIDragItem *> *))completion;

@end

/// A `UIDragInteraction` subclass with features specific to browsers to enable asynchronous preparations and behaviours.
BROWSERENGINE_EXTERN API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface BEDragInteraction: UIDragInteraction

/// The object that manages the drag interaction lifecycle.
@property (nonatomic, readonly, weak, nullable) id<BEDragInteractionDelegate> delegate;

/// Creates an drag interaction with the specified delegate.
- (instancetype)initWithDelegate:(id<BEDragInteractionDelegate>)delegate NS_DESIGNATED_INITIALIZER;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#endif // BROWSERENGINEKIT_HAS_UIVIEW
