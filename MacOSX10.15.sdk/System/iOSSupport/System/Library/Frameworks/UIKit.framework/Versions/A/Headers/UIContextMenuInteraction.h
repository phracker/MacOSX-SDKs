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



UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos) @interface UIContextMenuInteraction : NSObject <UIInteraction>

/// The interaction's delegate.
@property (nonatomic, weak, readonly) id<UIContextMenuInteractionDelegate> delegate;

- (instancetype)initWithDelegate:(id<UIContextMenuInteractionDelegate>)delegate NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 * @abstract Returns the interaction's location within the given view.
 *
 * @param view The view in which to locate the interaction.
 */
- (CGPoint)locationInView:(nullable UIView *)view;

@end


UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos) @protocol UIContextMenuInteractionAnimating <NSObject>

/// Displayed preview view controller.
@property (nonatomic, readonly, nullable) UIViewController *previewViewController;

- (void)addAnimations:(void (^)(void))animations;
- (void)addCompletion:(void (^)(void))completion;

@end

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos) @protocol UIContextMenuInteractionCommitAnimating <UIContextMenuInteractionAnimating>

/// Preferred animation style for the menu's commit action. Triggered when the user taps the preview.
@property (nonatomic) UIContextMenuInteractionCommitStyle preferredCommitStyle;

@end


UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos) @protocol UIContextMenuInteractionDelegate <NSObject>

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





- (void)contextMenuInteraction:(UIContextMenuInteraction *)interaction willCommitWithAnimator:(id<UIContextMenuInteractionCommitAnimating>)animator API_DEPRECATED_WITH_REPLACEMENT("contextMenuInteraction:willPerformPreviewActionForMenuWithConfiguration:animator:", ios(13.0, 13.0));

- (void)contextMenuInteractionWillPresent:(UIContextMenuInteraction *)interaction API_DEPRECATED_WITH_REPLACEMENT("contextMenuInteraction:willDisplayMenuForConfiguration:animator:", ios(13.0, 13.0));

- (void)contextMenuInteractionDidEnd:(UIContextMenuInteraction *)interaction API_DEPRECATED_WITH_REPLACEMENT("contextMenuInteraction:willEndForConfiguration:animator:", ios(13.0, 13.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIContextMenuInteraction.h>
#endif
