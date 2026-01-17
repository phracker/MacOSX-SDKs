#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIFocus.h>)
//
//  UIFocus.h
//  UIKit
//
//  Copyright © 2015-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIFocusDefines.h>

#import <UIKit/UIFocusGuide.h>
#import <UIKit/UIFocusAnimationCoordinator.h>
@class UIFocusEffect;

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
    UIFocusHeadingFirst API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos) = 1 << 8,
    UIFocusHeadingLast API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos) = 1 << 9,
} API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIFocusItemDeferralMode) {
    /// Use the system default behavior.
    UIFocusItemDeferralModeAutomatic,
    /// Always defer focus for this item, even if deferral is disabled right now.
    /// This means a programmatic update to this item would result in focus
    /// disappearing until the user interacts with the focus engine again.
    UIFocusItemDeferralModeAlways,
    /// Never defer focus for this item. When a programmatic focus update
    /// lands on this item, it will always be and appear focused even if focus
    /// deferral is currently enabled.
    UIFocusItemDeferralModeNever,
} API_AVAILABLE(ios(18.0), tvos(18.0)) API_UNAVAILABLE(watchos);

typedef NSString * UIFocusSoundIdentifier NS_TYPED_EXTENSIBLE_ENUM API_UNAVAILABLE(watchos);

/// These are focus group priorities that the system uses and that clients can use to make an item
/// more or less important than these system states. Any priority below 0 will be ignored.
typedef NSInteger UIFocusGroupPriority NS_TYPED_EXTENSIBLE_ENUM API_UNAVAILABLE(watchos);
static const UIFocusGroupPriority UIFocusGroupPriorityIgnored API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, watchos) = 0;
static const UIFocusGroupPriority UIFocusGroupPriorityPreviouslyFocused API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, watchos) = 1000;
static const UIFocusGroupPriority UIFocusGroupPriorityPrioritized API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, watchos) = 2000;
static const UIFocusGroupPriority UIFocusGroupPriorityCurrentlyFocused API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, watchos) = NSIntegerMax;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Objects conforming to UIFocusEnvironment influence and respond to focus behavior within a specific area of the screen that they control.
UIKIT_EXTERN API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UIFocusEnvironment <NSObject>

/// The preferred focus environments define where to search for the default focused item in an environment, such as when focus updates programmatically.
/// Starting from the target environment, each preferred focus environment is recursively searched in the order of the array until an eligible, focusable item is found.
/// Preferred focus environments can include focusable and non-focusable items, in addition to non-item environments. Returning an empty array is equivalent to returning an array containing only 'self'.
@property (nonatomic, readonly, copy) NSArray<id<UIFocusEnvironment>> *preferredFocusEnvironments;

/// The parent focus environment of this environment, or nil if no parent exists.
/// NOTE: If you implement this method, you must return a non-nil value for parent focus environment, otherwise your focus environment will not participate in focus interactions.
@property (nonatomic, weak, readonly, nullable) id<UIFocusEnvironment> parentFocusEnvironment NS_SWIFT_NAME(parentFocusEnvironment) API_AVAILABLE(tvos(12.0), ios(12.0)) API_UNAVAILABLE(watchos);

/// The container of any child focus items in this focus environment, or nil if no container exists.
@property (nonatomic, readonly, nullable, strong) id<UIFocusItemContainer> focusItemContainer API_AVAILABLE(tvos(12.0), ios(12.0)) API_UNAVAILABLE(watchos);

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
- (nullable UIFocusSoundIdentifier)soundIdentifierForFocusUpdateInContext:(UIFocusUpdateContext *)context API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios, watchos, visionos);

@property (nonatomic, weak, readonly, nullable) UIView *preferredFocusedView API_DEPRECATED_WITH_REPLACEMENT("preferredFocusEnvironments", ios(9.0, 10.0)) API_UNAVAILABLE(visionos, watchos);

/// The identifier of the focus group that this view belongs to. If this is nil, subviews inherit their superview's focus group.
 @property (nonatomic, readonly, nullable, copy) NSString *focusGroupIdentifier API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos, watchos);

@end


/// Objects conforming to UIFocusItem are considered capable of participating in focus. Only UIFocusItems can ever be focused.
UIKIT_EXTERN API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UIFocusItem <UIFocusEnvironment>

/// Indicates whether or not this item is currently allowed to become focused.
/// Returning NO restricts the item from being focusable, even if it is visible in the user interface. For example, UIControls return NO if they are disabled.
@property(nonatomic, readonly) BOOL canBecomeFocused;

/// The geometric frame of this item, represented in the `coordinateSpace` of the UIFocusItemContainer in which it is contained.
@property (nonatomic, readonly) CGRect frame API_AVAILABLE(tvos(12.0), ios(12.0)) API_UNAVAILABLE(watchos);

@optional

/// Describes a visual effect to apply when this item is focused. When not implemented, the system may create a default effect for this item.
/// Returning nil indicates that the system should not apply any visual effects, and that the app will handle applying the appropriate visuals.
@property (nonatomic, nullable, readonly, copy) UIFocusEffect *focusEffect API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos);

/// The priority this item has in its focus group. The higher the priority, the more likely it is to get picked when focus moves into this group.
/// Note: this method can only be used to increase an item's priority, not decrease it. For example if an item is currently selected, the actual priority of this item will be determined by MAX(focusGroupPriority, UIFocusGroupPrioritySelected).
@property (nonatomic, readonly) UIFocusGroupPriority focusGroupPriority API_AVAILABLE(ios(15.0))  API_UNAVAILABLE(tvos, watchos);

/// If this property is present and returns `UIFocusItemDeferralModeNever`, the focus deferral will not be enabled again
/// after the user engagement timeout has expired if this item is currently focused and programmatic focus updates pointing
/// to this item will be executed immediatly. If it returns `UIFocusItemDeferralModeAlways` focus will always be deferred
/// when this item is supposed to be focused.
/// Does nothing when focus deferral is not supported on the platform.
@property (nonatomic, readonly) UIFocusItemDeferralMode focusItemDeferralMode;

/// If this returns YES, the focus item is considered transparent in terms of occlusion. Items that are behind it are focusable.
/// This value is ignored when the item is focusable, in which case the item is never considered transparent.
@property (nonatomic, readonly) BOOL isTransparentFocusItem API_AVAILABLE(ios(15.0), tvos(18.0)) API_UNAVAILABLE(watchos);

/// Called whenever this focus item is hinting to the user a focus movement might occur.
/// The provided object is mutated by the focus engine whenever the user's finger moves.
- (void)didHintFocusMovement:(UIFocusMovementHint *)hint API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos);

@end


/// Objects conforming to UIFocusItemContainer are responsible for providing which focus items they
/// contain and where they are.
UIKIT_EXTERN API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UIFocusItemContainer <NSObject>

/// The coordinate space of the focus items contained in this container. The focus items returned by focusItemsInRect: should report their frames in this coordinate space.
/// If you are implementing this protocol, you may find it convenient to return the UIScreen as your coordinate space, and ensure that your contained items report their frames in screen space.
/// Similarly, you might find that your focus items' containing UIView or UIWindow is the most convenient coordinate space to use.
/// You may also choose to implement your own object that conforms to UICoordinateSpace, if that is the most natural solution for your architecture.
@property (nonatomic, readonly, strong) id<UICoordinateSpace> coordinateSpace;

/// Returns an array of all focus items within this container that intersect with the provided rect. `rect` is expressed in `coordinateSpace`.
/// Note: starting in iOS & tvOS 16.0, UIView will return its subviews from this method. If you override this method in a UIView subclass, it will be your responsibility to call super and merge your array of custom focus items with UIView's default focus items.
- (NSArray<id<UIFocusItem>> *)focusItemsInRect:(CGRect)rect;

@end


/// Objects conforming to UIFocusItemScrollableContainer are updated accordingly to ensure the
/// focused item remains visible on the screen.
UIKIT_EXTERN API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UIFocusItemScrollableContainer <UIFocusItemContainer>

/// The current content offset of this scrollable container. If the scrollable container has a `bounds` property, `bounds.origin` must be equal to `contentOffset`.
@property (nonatomic, readwrite) CGPoint contentOffset;

/// The total size of the content contained by this container. If this size exceeds the size of
/// this container's visible size, then scrolling is possible.
@property (nonatomic, readonly) CGSize contentSize;

/// The visible size of this scrollable container.
@property (nonatomic, readonly) CGSize visibleSize;

@end


/// UIFocusUpdateContexts provide information relevant to a specific focus update from one view to another. They are ephemeral objects that are usually discarded after the update is finished.
UIKIT_EXTERN API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIFocusUpdateContext : NSObject

/// The item that was focused before the update, i.e. where focus is updating from. May be nil if no item was focused, such as when focus is initially set.
@property (nonatomic, weak, readonly, nullable) id<UIFocusItem> previouslyFocusedItem API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos);

/// The item that is focused after the update, i.e. where focus is updating to. May be nil if no item is being focused, meaning focus is being lost.
@property (nonatomic, weak, readonly, nullable) id<UIFocusItem> nextFocusedItem API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos);

/// The focus heading in which the update is occurring.
@property (nonatomic, assign, readonly) UIFocusHeading focusHeading;

@end


UIKIT_EXTERN NSNotificationName const UIFocusDidUpdateNotification API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UIFocusMovementDidFailNotification API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;

UIKIT_EXTERN NSString * const UIFocusUpdateContextKey API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);
UIKIT_EXTERN NSString * const UIFocusUpdateAnimationCoordinatorKey API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

/// Sound identifier for disabling sound during a focus update.
UIKIT_EXTERN UIFocusSoundIdentifier const UIFocusSoundIdentifierNone API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios, watchos, visionos);

/// Sound identifier for playing the default sound during a focus update.
UIKIT_EXTERN UIFocusSoundIdentifier const UIFocusSoundIdentifierDefault API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios, watchos, visionos);

NS_HEADER_AUDIT_END(nullability, sendability)

#import <UIKit/UIFocusUpdateContext+UIKitAdditions.h>

#else
#import <UIKitCore/UIFocus.h>
#endif
