#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIFocus.h>)
//
//  UIFocus.h
//  UIKit
//
//  Copyright © 2015-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIFocusGuide.h>
#import <UIKit/UIFocusAnimationCoordinator.h>
#import <UIKit/UIKitDefines.h>

@class UIView, UIFocusUpdateContext, UIFocusMovementHint;
@protocol UICoordinateSpace, UIFocusItemContainer;

typedef NS_OPTIONS(NSUInteger, UIFocusHeading) {
    UIFocusHeadingNone          = 0,
    UIFocusHeadingUp            = 1 << 0,
    UIFocusHeadingDown          = 1 << 1,
    UIFocusHeadingLeft          = 1 << 2,
    UIFocusHeadingRight         = 1 << 3,
    UIFocusHeadingNext          = 1 << 4,
    UIFocusHeadingPrevious      = 1 << 5,
} API_AVAILABLE(ios(9.0));

typedef NSString * UIFocusSoundIdentifier NS_TYPED_EXTENSIBLE_ENUM;

NS_ASSUME_NONNULL_BEGIN

/// Objects conforming to UIFocusEnvironment influence and respond to focus behavior within a specific area of the screen that they control.
UIKIT_EXTERN API_AVAILABLE(ios(9.0)) @protocol UIFocusEnvironment <NSObject>

/// The preferred focus environments define where to search for the default focused item in an environment, such as when focus updates programmatically.
/// Starting from the target environment, each preferred focus environment is recursively searched in the order of the array until an eligible, focusable item is found.
/// Preferred focus environments can include focusable and non-focusable items, in addition to non-item environments. Returning an empty array is equivalent to returning an array containing only 'self'.
@property (nonatomic, copy, readonly) NSArray<id<UIFocusEnvironment>> *preferredFocusEnvironments;

/// The parent focus environment of this environment, or nil if no parent exists.
/// NOTE: If you implement this method, you must return a non-nil value for parent focus environment, otherwise your focus environment will not participate in focus interactions.
@property (nonatomic, weak, readonly, nullable) id<UIFocusEnvironment> parentFocusEnvironment NS_SWIFT_NAME(parentFocusEnvironment) API_AVAILABLE(tvos(12.0), ios(12.0));

/// The container of any child focus items in this focus environment, or nil if no container exists.
@property (nonatomic, readonly, nullable) id<UIFocusItemContainer> focusItemContainer API_AVAILABLE(tvos(12.0), ios(12.0));

/// Marks this environment as needing a focus update, which if accepted will attempt to reset focus to this environment, or one of its preferred focus environments, on the next update cycle. If this environment does not currently contain the focused item, then calling this method has no effect. If a parent of this environment is also requesting focus, then this environment's request is rejected in favor of the parent's.
/// NOTE: If you provide your own implementation, it must call `[[UIFocusSystem focusSystemForEnvironment:self] requestFocusUpdateToEnvironment:self]`;
- (void)setNeedsFocusUpdate;

/// Forces focus to be updated immediately. If there is an environment that has requested a focus update via -setNeedsFocusUpdate, and the request was accepted, then focus will be updated to that environment or one of its preferred focus environments.
/// NOTE: If you provide your own implementation, it must call `[[UIFocusSystem focusSystemForEnvironment:self] updateFocusIfNeeded];`.
- (void)updateFocusIfNeeded;

/// Asks whether the system should allow a focus update to occur.
- (BOOL)shouldUpdateFocusInContext:(UIFocusUpdateContext *)context;

/// Called when the screen’s focused item has been updated to a new item. Use the animation coordinator to schedule focus-related animations in response to the update.
- (void)didUpdateFocusInContext:(UIFocusUpdateContext *)context withAnimationCoordinator:(UIFocusAnimationCoordinator *)coordinator;

@optional

/// Specifies an identifier corresponding to a sound that should be played for a focus update.
/// Return UIFocusSoundIdentifierNone to opt out of sounds, UIFocusSoundIdentifierDefault for the system
/// default sounds, a previously registered identifier for a custom sound, or nil to defer the decision
/// to the parent.
- (nullable UIFocusSoundIdentifier)soundIdentifierForFocusUpdateInContext:(UIFocusUpdateContext *)context API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios, watchos);

@property (nonatomic, weak, readonly, nullable) UIView *preferredFocusedView API_DEPRECATED_WITH_REPLACEMENT("preferredFocusEnvironments", ios(9.0, 10.0));

@end


/// Objects conforming to UIFocusItem are considered capable of participating in focus. Only UIFocusItems can ever be focused.
UIKIT_EXTERN API_AVAILABLE(ios(10.0)) @protocol UIFocusItem <UIFocusEnvironment>

/// Indicates whether or not this item is currently allowed to become focused.
/// Returning NO restricts the item from being focusable, even if it is visible in the user interface. For example, UIControls return NO if they are disabled.
@property(nonatomic, readonly) BOOL canBecomeFocused;

/// The geometric frame of this item, represented in the `coordinateSpace` of the UIFocusItemContainer in which it is contained.
@property (nonatomic, readonly) CGRect frame API_AVAILABLE(tvos(12.0), ios(12.0));

@optional

/// Called whenever this focus item is hinting to the user a focus movement might occur.
/// The provided object is mutated by the focus engine whenever the user's finger moves.
- (void)didHintFocusMovement:(UIFocusMovementHint *)hint API_AVAILABLE(ios(12.0));

@end


/// Objects conforming to UIFocusItemContainer are responsible for providing which focus items they
/// contain and where they are.
UIKIT_EXTERN API_AVAILABLE(ios(12.0)) @protocol UIFocusItemContainer <NSObject>

/// The coordinate space of the focus items contained in this container. The focus items returned by focusItemsInRect: should report their frames in this coordinate space.
/// If you are implementing this protocol, you may find it convenient to return the UIScreen as your coordinate space, and ensure that your contained items report their frames in screen space.
/// Similarly, you might find that your focus items' containing UIView or UIWindow is the most convenient coordinate space to use.
/// You may also choose to implement your own object that conforms to UICoordinateSpace, if that is the most natural solution for your architecture.
@property (nonatomic, readonly) id<UICoordinateSpace> coordinateSpace;

/// Returns an array of all focus items within this container that intersect with the provided rect. `rect` is expressed in `coordinateSpace`.
- (NSArray<id<UIFocusItem>> *)focusItemsInRect:(CGRect)rect;

@end


/// Objects conforming to UIFocusItemScrollableContainer are updated accordingly to ensure the
/// focused item remains visible on the screen.
UIKIT_EXTERN API_AVAILABLE(ios(12.0)) @protocol UIFocusItemScrollableContainer <UIFocusItemContainer>

/// The current content offset of this scrollable container. If the scrollable container has a `bounds` property, `bounds.origin` must be equal to `contentOffset`.
@property (nonatomic, readwrite) CGPoint contentOffset;

/// The total size of the content contained by this container. If this size exceeds the size of
/// this container's visible size, then scrolling is possible.
@property (nonatomic, readonly) CGSize contentSize;

/// The visible size of this scrollable container.
@property (nonatomic, readonly) CGSize visibleSize;

@end


/// UIFocusUpdateContexts provide information relevant to a specific focus update from one view to another. They are ephemeral objects that are usually discarded after the update is finished.
UIKIT_EXTERN API_AVAILABLE(ios(9.0)) @interface UIFocusUpdateContext : NSObject

/// The item that was focused before the update, i.e. where focus is updating from. May be nil if no item was focused, such as when focus is initially set.
@property (nonatomic, weak, readonly, nullable) id<UIFocusItem> previouslyFocusedItem API_AVAILABLE(ios(10.0));

/// The item that is focused after the update, i.e. where focus is updating to. May be nil if no item is being focused, meaning focus is being lost.
@property (nonatomic, weak, readonly, nullable) id<UIFocusItem> nextFocusedItem API_AVAILABLE(ios(10.0));

/// The view that was focused before the update. May be nil if no view was focused, such as when setting initial focus.
/// If previouslyFocusedItem is not a view, this returns that item's containing view, otherwise they are equal.
/// NOTE: This property will be deprecated in a future release. Use previouslyFocusedItem instead.
@property (nonatomic, weak, readonly, nullable) UIView *previouslyFocusedView;

/// The view that will be focused after the update. May be nil if no view will be focused.
/// If nextFocusedItem is not a view, this returns that item's containing view, otherwise they are equal.
/// NOTE: This property will be deprecated in a future release. Use nextFocusedItem instead.
@property (nonatomic, weak, readonly, nullable) UIView *nextFocusedView;

/// The focus heading in which the update is occuring.
@property (nonatomic, assign, readonly) UIFocusHeading focusHeading;

@end


UIKIT_EXTERN NSNotificationName const UIFocusDidUpdateNotification API_AVAILABLE(ios(11.0), tvos(11.0));
UIKIT_EXTERN NSNotificationName const UIFocusMovementDidFailNotification API_AVAILABLE(ios(11.0), tvos(11.0));

UIKIT_EXTERN NSString * const UIFocusUpdateContextKey API_AVAILABLE(ios(11.0), tvos(11.0));
UIKIT_EXTERN NSString * const UIFocusUpdateAnimationCoordinatorKey API_AVAILABLE(ios(11.0), tvos(11.0));

/// Sound identifier for disabling sound during a focus update.
UIKIT_EXTERN UIFocusSoundIdentifier const UIFocusSoundIdentifierNone API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios, watchos);

/// Sound identifier for playing the default sound during a focus update.
UIKIT_EXTERN UIFocusSoundIdentifier const UIFocusSoundIdentifierDefault API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios, watchos);

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIFocus.h>
#endif
