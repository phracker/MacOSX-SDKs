#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIControl.h>)
//
//  UIControl.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIContextMenuInteraction.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_OPTIONS(NSUInteger, UIControlEvents) {
    UIControlEventTouchDown                                         = 1 <<  0,      // on all touch downs
    UIControlEventTouchDownRepeat                                   = 1 <<  1,      // on multiple touchdowns (tap count > 1)
    UIControlEventTouchDragInside                                   = 1 <<  2,
    UIControlEventTouchDragOutside                                  = 1 <<  3,
    UIControlEventTouchDragEnter                                    = 1 <<  4,
    UIControlEventTouchDragExit                                     = 1 <<  5,
    UIControlEventTouchUpInside                                     = 1 <<  6,
    UIControlEventTouchUpOutside                                    = 1 <<  7,
    UIControlEventTouchCancel                                       = 1 <<  8,

    UIControlEventValueChanged                                      = 1 << 12,     // sliders, etc.
    UIControlEventPrimaryActionTriggered API_AVAILABLE(ios(9.0))    = 1 << 13,     // semantic action: for buttons, etc.
    UIControlEventMenuActionTriggered API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos)      = 1 << 14,     // triggered when the menu gesture fires but before the menu presents

    UIControlEventEditingDidBegin                                   = 1 << 16,     // UITextField
    UIControlEventEditingChanged                                    = 1 << 17,
    UIControlEventEditingDidEnd                                     = 1 << 18,
    UIControlEventEditingDidEndOnExit                               = 1 << 19,     // 'return key' ending editing

    UIControlEventAllTouchEvents                                    = 0x00000FFF,  // for touch events
    UIControlEventAllEditingEvents                                  = 0x000F0000,  // for UITextField
    UIControlEventApplicationReserved                               = 0x0F000000,  // range available for application use
    UIControlEventSystemReserved                                    = 0xF0000000,  // range reserved for internal framework use
    UIControlEventAllEvents                                         = 0xFFFFFFFF
} API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIControlContentVerticalAlignment) {
    UIControlContentVerticalAlignmentCenter        = 0,
    UIControlContentVerticalAlignmentTop           = 1,
    UIControlContentVerticalAlignmentBottom        = 2,
    UIControlContentVerticalAlignmentFill          = 3,
} API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIControlContentHorizontalAlignment) {
    UIControlContentHorizontalAlignmentCenter = 0,
    UIControlContentHorizontalAlignmentLeft   = 1,
    UIControlContentHorizontalAlignmentRight  = 2,
    UIControlContentHorizontalAlignmentFill   = 3,
    UIControlContentHorizontalAlignmentLeading  API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos) = 4,
    UIControlContentHorizontalAlignmentTrailing API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos) = 5,
} API_UNAVAILABLE(watchos);

typedef NS_OPTIONS(NSUInteger, UIControlState) {
    UIControlStateNormal       = 0,
    UIControlStateHighlighted  = 1 << 0,                  // used when UIControl isHighlighted is set
    UIControlStateDisabled     = 1 << 1,
    UIControlStateSelected     = 1 << 2,                  // flag usable by app (see below)
    UIControlStateFocused API_AVAILABLE(ios(9.0)) = 1 << 3, // Applicable only when the screen supports focus
    UIControlStateApplication  = 0x00FF0000,              // additional flags available for application use
    UIControlStateReserved     = 0xFF000000               // flags reserved for internal framework use
} API_UNAVAILABLE(watchos);

@class UITouch;
@class UIEvent;
@class UIToolTipInteraction;

//______________________________________________________

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIControl : UIView

- (instancetype)initWithFrame:(CGRect)frame NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// Initializes the control and adds primaryAction for the UIControlEventPrimaryActionTriggered control event. Subclasses of UIControl may alter or add behaviors around the usage of primaryAction, see subclass documentation of this initializer for additional information.
- (instancetype)initWithFrame:(CGRect)frame primaryAction:(nullable UIAction *)primaryAction API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

@property(nonatomic,getter=isEnabled) BOOL enabled;                                  // default is YES. if NO, ignores touch events and subclasses may draw differently
@property(nonatomic,getter=isSelected) BOOL selected;                                // default is NO may be used by some subclasses or by application
@property(nonatomic,getter=isHighlighted) BOOL highlighted;                          // default is NO. this gets set/cleared automatically when touch enters/exits during tracking and cleared on up
@property(nonatomic) UIControlContentVerticalAlignment contentVerticalAlignment;     // how to position content vertically inside control. default is center
@property(nonatomic) UIControlContentHorizontalAlignment contentHorizontalAlignment; // how to position content horizontally inside control. default is center
@property(nonatomic, readonly) UIControlContentHorizontalAlignment effectiveContentHorizontalAlignment; // how to position content horizontally inside control, guaranteed to return 'left' or 'right' for any 'leading' or 'trailing'

@property(nonatomic,readonly) UIControlState state;                  // could be more than one state (e.g. disabled|selected). synthesized from other flags.
@property(nonatomic,readonly,getter=isTracking) BOOL tracking;
@property(nonatomic,readonly,getter=isTouchInside) BOOL touchInside; // valid during tracking only

- (BOOL)beginTrackingWithTouch:(UITouch *)touch withEvent:(nullable UIEvent *)event;
- (BOOL)continueTrackingWithTouch:(UITouch *)touch withEvent:(nullable UIEvent *)event;
- (void)endTrackingWithTouch:(nullable UITouch *)touch withEvent:(nullable UIEvent *)event; // touch is sometimes nil if cancelTracking calls through to this.
- (void)cancelTrackingWithEvent:(nullable UIEvent *)event;   // event may be nil if cancelled for non-event reasons, e.g. removed from window

// add target/action for particular event. you can call this multiple times and you can specify multiple target/actions for a particular event.
// passing in nil as the target goes up the responder chain. The action may optionally include the sender and the event in that order
// the action cannot be NULL. Note that the target is not retained.
- (void)addTarget:(nullable id)target action:(SEL)action forControlEvents:(UIControlEvents)controlEvents;

// remove the target/action for a set of events. pass in NULL for the action to remove all actions for that target
- (void)removeTarget:(nullable id)target action:(nullable SEL)action forControlEvents:(UIControlEvents)controlEvents;

/// Adds the UIAction to a given event. UIActions are uniqued based on their identifier, and subsequent actions with the same identifier replace previously added actions. You may add multiple UIActions for corresponding controlEvents, and you may add the same action to multiple controlEvents.
- (void)addAction:(UIAction *)action forControlEvents:(UIControlEvents)controlEvents API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);
/// Removes the action from the set of passed control events.
- (void)removeAction:(UIAction *)action forControlEvents:(UIControlEvents)controlEvents API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);
/// Removes the action with the provided identifier from the set of passed control events.
- (void)removeActionForIdentifier:(UIActionIdentifier)actionIdentifier forControlEvents:(UIControlEvents)controlEvents API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

/// Performs the control's primary action.
- (void)performPrimaryAction API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos);

// get info about target & actions. this makes it possible to enumerate all target/actions by checking for each event kind
@property(nonatomic,readonly) NSSet *allTargets;                                           // set may include NSNull to indicate at least one nil target
@property(nonatomic,readonly) UIControlEvents allControlEvents;                            // list of all events that have at least one action

- (nullable NSArray<NSString *> *)actionsForTarget:(nullable id)target forControlEvent:(UIControlEvents)controlEvent;    // single event. returns NSArray of NSString selector names. returns nil if none

/// Iterate over the event handlers installed on this control at the time this method is called. For each call, either actionHandler or action will be non-nil. controlEvents is always non-zero. Setting *stop to YES will terminate the enumeration early. It is legal to manipulate the control's event handlers within the block.
- (void)enumerateEventHandlers:(void (NS_NOESCAPE ^)(UIAction * _Nullable actionHandler, id _Nullable target, SEL _Nullable action, UIControlEvents controlEvents, BOOL *stop))iterator API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

/// Dispatch the target-action pair. This method is called repeatedly by -sendActionsForControlEvents: and is a point at which you can observe or override behavior.
- (void)sendAction:(SEL)action to:(nullable id)target forEvent:(nullable UIEvent *)event;
/// Like -sendAction:to:forEvent:, this method is called by -sendActionsForControlEvents:. You may override this method to observe or modify behavior. If you override this method, you should call super precisely once to dispatch the action, or not call super to suppress sending that action.
- (void)sendAction:(UIAction *)action API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);
/// send all actions associated with the given control events
- (void)sendActionsForControlEvents:(UIControlEvents)controlEvents;

/// Returns a UIContextMenuInteraction with this control set as its delegate. Before constructing the UIContextMenuInteraction, UIControl verifies 'self' is a viable delegate. See 'Implementing UIControl Menus' below for more details.
@property (nonatomic, readonly, strong, nullable) UIContextMenuInteraction *contextMenuInteraction API_AVAILABLE(ios(14.0), tvos(17.0)) API_UNAVAILABLE(watchos);
/// Specifies if the context menu interaction is enabled. NO by default.
@property (nonatomic, readwrite, assign, getter = isContextMenuInteractionEnabled) BOOL contextMenuInteractionEnabled API_AVAILABLE(ios(14.0), tvos(17.0)) API_UNAVAILABLE(watchos);
/// If the contextMenuInteraction is the primary action of the control, invoked on touch-down. NO by default.
@property (nonatomic, readwrite, assign) BOOL showsMenuAsPrimaryAction API_AVAILABLE(ios(14.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/// Return a point in this control's coordinate space to which to attach the given configuration's menu.
- (CGPoint)menuAttachmentPointForConfiguration:(UIContextMenuConfiguration *)configuration API_AVAILABLE(ios(14.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/// Assigning a value to this property causes the tool tip to be displayed for the view. Setting the property to nil cancels the display of the tool tip for the view.
@property (nonatomic, copy, nullable) NSString *toolTip API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos);
/// Returns the control's default UIToolTipInteraction.
@property (nonatomic, readonly, strong, nullable) UIToolTipInteraction *toolTipInteraction API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos);

/// Whether or not symbol animations are enabled for this control.
/// The default value varies depending on the control.
@property (nonatomic, getter=isSymbolAnimationEnabled) BOOL symbolAnimationEnabled API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

@end

#if TARGET_OS_IOS || TARGET_OS_TV

/// Implementing UIControl Menus
/// UIControl will only create a UIContextMenuInteraction if you've created a subclass of UIControl with a minimum viable delegate implementation. UIControl extends the contract of UIContextMenuInteractionDelegate for these methods, see each method for more detail.
API_AVAILABLE(ios(14.0), tvos(17.0))
@interface UIControl() <UIContextMenuInteractionDelegate>

/// An override is required for UIControl to create a UIContextMenuInteraction. Direct UIControl subclasses do not need to call super.
- (nullable UIContextMenuConfiguration *)contextMenuInteraction:(UIContextMenuInteraction *)interaction configurationForMenuAtLocation:(CGPoint)location API_AVAILABLE(ios(14.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/// Direct UIControl subclasses do not need to call super.
- (nullable UITargetedPreview *)contextMenuInteraction:(UIContextMenuInteraction *)interaction previewForHighlightingMenuWithConfiguration:(UIContextMenuConfiguration *)configuration API_AVAILABLE(ios(14.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/// Direct UIControl subclasses do not need to call super.
- (nullable UITargetedPreview *)contextMenuInteraction:(UIContextMenuInteraction *)interaction previewForDismissingMenuWithConfiguration:(UIContextMenuConfiguration *)configuration API_AVAILABLE(ios(14.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/// UIControl subclasses should always call super.
- (void)contextMenuInteraction:(UIContextMenuInteraction *)interaction willDisplayMenuForConfiguration:(UIContextMenuConfiguration *)configuration animator:(nullable id<UIContextMenuInteractionAnimating>)animator NS_REQUIRES_SUPER API_AVAILABLE(ios(14.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/// UIControl subclasses should always call super.
- (void)contextMenuInteraction:(UIContextMenuInteraction *)interaction willEndForConfiguration:(UIContextMenuConfiguration *)configuration animator:(nullable id<UIContextMenuInteractionAnimating>)animator NS_REQUIRES_SUPER API_AVAILABLE(ios(14.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/// UIControl based menus do not display previews, so this method will not be called even if implemented. UIControl does not have an implementation.
- (void)contextMenuInteraction:(UIContextMenuInteraction *)interaction willPerformPreviewActionForMenuWithConfiguration:(UIContextMenuConfiguration *)configuration animator:(id<UIContextMenuInteractionCommitAnimating>)animator NS_UNAVAILABLE;

@end

#endif

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIControl.h>
#endif
