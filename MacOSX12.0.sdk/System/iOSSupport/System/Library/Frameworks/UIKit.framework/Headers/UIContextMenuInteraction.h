#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIContextMenuInteraction.h>)
//
//  UIContextMenuInteraction.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>

#import <Foundation/Foundation.h>
#import <UIKit/UIInteraction.h>
#import <UIKit/UIContextMenuConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@class UITargetedPreview;
@protocol UIContextMenuInteractionDelegate;

typedef NS_ENUM(NSInteger, UIContextMenuInteractionCommitStyle) {
    UIContextMenuInteractionCommitStyleDismiss = 0,
    UIContextMenuInteractionCommitStylePop,
} API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos);

typedef NS_ENUM(NSInteger, UIContextMenuInteractionAppearance) {
    UIContextMenuInteractionAppearanceUnknown = 0,
    UIContextMenuInteractionAppearanceRich,            // Modal "rich" menu with optional preview.
    UIContextMenuInteractionAppearanceCompact,         // Non-modal, compact menu with no preview.
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos);

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIContextMenuInteraction : NSObject <UIInteraction>

/// The interaction's delegate.
@property (nonatomic, weak, readonly) id<UIContextMenuInteractionDelegate> delegate;

/// Appearance of the menu this interaction has presented or is about to present. Since it may be
/// dependent on the user's input method, the appearance is only known while the interaction is active.
@property (nonatomic, readonly) UIContextMenuInteractionAppearance menuAppearance API_AVAILABLE(ios(14.0));

- (instancetype)initWithDelegate:(id<UIContextMenuInteractionDelegate>)delegate NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 * @abstract Returns the interaction's location within the given view.
 *
 * @param view The view in which to locate the interaction.
 */
- (CGPoint)locationInView:(nullable UIView *)view;

/*!
 * @abstract Call to update the currently visible menu. This method does nothing if called before a menu is presented.
 *
 * @param block  Called with a mutable copy of the currently visible menu. Modify and return this menu (or an entirely
 *               new one) to change the currently visible menu items. Starting in iOS 15, this block is called once for
 *               every visible submenu. For example, in the following hierarchy:
 *
 *               *- Root Menu
 *                  *- Submenu A
 *                     *- Submenu B
 *                  *- Submenu C
 *
 *               If Submenu A is visible, the block is called twice (once for the Root Menu and once for Submenu A).
 *               If both A and B are visible, it's called 3 times (for the Root Menu, A, and B).
 */
- (void)updateVisibleMenuWithBlock:(UIMenu *(NS_NOESCAPE ^)(UIMenu *visibleMenu))block API_AVAILABLE(ios(14.0));

/*!
 * @abstract Dismisses the currently presented menu (if there is one).
 */
- (void)dismissMenu;

@end


UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@protocol UIContextMenuInteractionAnimating <NSObject>

/// Displayed preview view controller.
@property (nonatomic, readonly, nullable) UIViewController *previewViewController;

- (void)addAnimations:(void (^)(void))animations;
- (void)addCompletion:(void (^)(void))completion NS_SWIFT_DISABLE_ASYNC;

@end

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@protocol UIContextMenuInteractionCommitAnimating <UIContextMenuInteractionAnimating>

/// Preferred animation style for the menu's commit action. Triggered when the user taps the preview.
@property (nonatomic) UIContextMenuInteractionCommitStyle preferredCommitStyle;

@end


UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@protocol UIContextMenuInteractionDelegate <NSObject>

/*!
 * @abstract Called when the interaction begins.
 *
 * @param interaction  The UIContextMenuInteraction.
 * @param location     The location of the interaction in its view.
 *
 * @return A UIContextMenuConfiguration describing the menu to be presented. Return nil to prevent the interaction from beginning.
 *         Returning an empty configuration causes the interaction to begin then fail with a cancellation effect. You might use this
 *         to indicate to users that it's possible for a menu to be presented from this view, but that there are no actions to
 *         present at this particular time.
 */
- (nullable UIContextMenuConfiguration *)contextMenuInteraction:(UIContextMenuInteraction *)interaction configurationForMenuAtLocation:(CGPoint)location;

@optional

/*!
 * @abstract Called when the interaction begins. Return a UITargetedPreview describing the desired highlight preview.
 *
 * @param interaction    The UIContextMenuInteraction requesting a highlighting preview.
 * @param configuration  The configuration of the menu about to be displayed by this interaction.
 */
- (nullable UITargetedPreview *)contextMenuInteraction:(UIContextMenuInteraction *)interaction previewForHighlightingMenuWithConfiguration:(UIContextMenuConfiguration *)configuration;

/*!
 * @abstract Called when the interaction is about to dismiss. Return a UITargetedPreview describing the desired dismissal target.
 * The interaction will animate the presented menu to the target. Use this to customize the dismissal animation.
 *
 * @param interaction    The UIContextMenuInteraction requesting a dismissal preview.
 * @param configuration  The configuration of the menu displayed by this interaction.
 *
 * @return Return a UITargetedPreview describing the desired dismissal target. Return nil to cause the menu to
 *         animate away without morphing into a specific view.
 */
- (nullable UITargetedPreview *)contextMenuInteraction:(UIContextMenuInteraction *)interaction previewForDismissingMenuWithConfiguration:(UIContextMenuConfiguration *)configuration;

/*!
 * @abstract Called when the interaction is about to "commit" in response to the user tapping the preview.
 *
 * @param interaction    The UIContextMenuInteraction.
 * @param configuration  Configuration of the currently displayed menu.
 * @param animator       Commit animator. Add animations to this object to run them alongside the commit transition.
 */
- (void)contextMenuInteraction:(UIContextMenuInteraction *)interaction willPerformPreviewActionForMenuWithConfiguration:(UIContextMenuConfiguration *)configuration animator:(id<UIContextMenuInteractionCommitAnimating>)animator;

/*!
 * @abstract Called when the interaction is about to display a menu.
 *
 * @param interaction    The UIContextMenuInteraction.
 * @param configuration  The configuration of the menu about to be displayed by this interaction.
 * @param animator       Appearance animator. Add animations to run them alongside the appearance transition.
 */
- (void)contextMenuInteraction:(UIContextMenuInteraction *)interaction willDisplayMenuForConfiguration:(UIContextMenuConfiguration *)configuration animator:(nullable id<UIContextMenuInteractionAnimating>)animator;

/*!
 * @abstract Called when the interaction is about to end.
 *
 * @param interaction    The UIContextMenuInteraction.
 * @param configuration  Ending configuration.
 * @param animator       Disappearance animator. Add animations to run them alongside the disappearance transition.
 */
- (void)contextMenuInteraction:(UIContextMenuInteraction *)interaction willEndForConfiguration:(UIContextMenuConfiguration *)configuration animator:(nullable id<UIContextMenuInteractionAnimating>)animator;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIContextMenuInteraction.h>
#endif
