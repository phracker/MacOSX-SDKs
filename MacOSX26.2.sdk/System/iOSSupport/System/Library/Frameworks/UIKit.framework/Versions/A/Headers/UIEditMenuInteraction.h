#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIEditMenuInteraction.h>)
//
//  UIEditMenuInteraction.h
//  UIKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <UIKit/UIInteraction.h>

NS_ASSUME_NONNULL_BEGIN

@protocol UIEditMenuInteractionDelegate;
@class UIMenuElement;

#pragma mark - UIEditMenuConfiguration

typedef NS_ENUM(NSInteger, UIEditMenuArrowDirection) {
    UIEditMenuArrowDirectionAutomatic   = 0,    // Determined by the placement of the menu (Either Up or Down)
    UIEditMenuArrowDirectionUp          = 1,
    UIEditMenuArrowDirectionDown        = 2,
    UIEditMenuArrowDirectionLeft        = 3,
    UIEditMenuArrowDirectionRight       = 4,
} API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

UIKIT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIEditMenuConfiguration : NSObject

/// The unique identifier of the configuration.
@property (nonatomic, copy, readonly) id<NSCopying> identifier;

/// The source location of the menu. The suggested actions menu elements will be derived from this location in the interaction's view.
/// By default, the menu will be presented from this location. You can change the presentation source of the menu with the delegate
/// method @c editMenuInteraction:targetRectForConfiguration:
@property (nonatomic, assign, readonly) CGPoint sourcePoint;

/// The preferred arrow direction of the edit menu. Default is @c UIEditMenuArrowDirectionAutomatic
@property (nonatomic, assign) UIEditMenuArrowDirection preferredArrowDirection;

/// Creates a new configuration with the specified source location.
+ (instancetype)configurationWithIdentifier:(nullable id<NSCopying>)identifier sourcePoint:(CGPoint)sourcePoint;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

#pragma mark - UIEditMenuInteraction

UIKIT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIEditMenuInteraction : NSObject <UIInteraction>

/// The object that defines the delegate of the interaction.
@property (nonatomic, weak, nullable, readonly) id<UIEditMenuInteractionDelegate> delegate;

/// Creates a new edit menu interaction with the specified delegate.
- (instancetype)initWithDelegate:(nullable id<UIEditMenuInteractionDelegate>)delegate;

/// Presents an edit menu with the specified @c configuration object.
/// If a menu is already presented, it will be dismissed automatically before the new menu is presented.
///
/// @NOTE: @c presentEditMenuWithConfiguration: is not supported on Mac Catalyst.
- (void)presentEditMenuWithConfiguration:(UIEditMenuConfiguration *)configuration;

/// Dismiss the currently active menu if one is currently presented.
- (void)dismissMenu;

/// Reloads the visible menu. This menu has no effect if there is no menu presented. This method will query
/// the menu again from the delegate method @c editMenuInteraction:menuForConfiguration:suggestedActions:
/// and refresh the UI with the updated menu.
- (void)reloadVisibleMenu;

/// Updates the position of the currently visible menu, with an option to animate the action. This method
/// has no effect if no menu is presented. This method will query the position from the delegate method
/// @c editMenuInteraction:targetRectForConfiguration: if it is implemented.
- (void)updateVisibleMenuPositionAnimated:(BOOL)animated;

/// Returns the interaction's location within the given view.
- (CGPoint)locationInView:(nullable UIView *)view;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

#pragma mark - UIEditMenuInteractionAnimating

API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)  NS_SWIFT_UI_ACTOR
@protocol UIEditMenuInteractionAnimating <NSObject>

- (void)addAnimations:(void (^)(void))animations;
- (void)addCompletion:(void (^)(void))completion NS_SWIFT_DISABLE_ASYNC;

@end

#pragma mark - UIEditMenuInteractionDelegate

API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
@protocol UIEditMenuInteractionDelegate<NSObject>

@optional

/**
 * @abstract Called when the interaction begins.
 *
 * @param interaction       The UIEditMenuInteraction.
 * @param configuration     The UIEditMenuConfiguration object used to present the menu.
 * @param suggestedActions  An array of suggested actions gathered from the UIResponder chain. You may
 *                          include these actions in the hierarchy to display them in the resulting menu.
 *
 * @return Return a UIMenu describing the desired menu hierarchy. Return @c nil to present the default system menu.
 */
- (nullable UIMenu *)editMenuInteraction:(UIEditMenuInteraction *)interaction menuForConfiguration:(UIEditMenuConfiguration *)configuration suggestedActions:(NSArray<UIMenuElement *> *)suggestedActions;

/**
 * @abstract Called when the interaction begins, or when @c updateVisibleMenuPosition(animated:) is called.
 *
 * @param interaction   The UIEditMenuInteraction.
 * @param configuration The UIEditMenuConfiguration object used to present the menu.
 *
 * @return Return a rectangle relative to the interaction's view. The menu will be displayed around
 *         target rect, space permitting, with the arrow pointing at the edge of the target rectangle
 *         for the specified arrow direction of the configuration. By default, an empty-sized rectangle
 *         centered at @c configuration.sourcePoint will be used if this method is not implemented. Return
 *         @c CGRectNull to use the default rect.
 */
- (CGRect)editMenuInteraction:(UIEditMenuInteraction *)interaction targetRectForConfiguration:(UIEditMenuConfiguration *)configuration;

/**
 * @abstract Called when the interaction is about to present the menu.
 *
 * @param interaction   The UIEditMenuInteraction.
 * @param configuration The configuration object of the menu about to be presented by this interaction.
 * @param animator      Appearance animator. Add animations to this object to run them alongside the appearance transition.
 */
 - (void)editMenuInteraction:(UIEditMenuInteraction *)interaction willPresentMenuForConfiguration:(UIEditMenuConfiguration *)configuration animator:(id<UIEditMenuInteractionAnimating>)animator;

/**
 * @abstract Called when the interaction is about to dismiss the menu.
 *
 * @param interaction   The UIEditMenuInteraction.
 * @param configuration The configuration object of the menu about to be dismissed by this interaction.
 * @param animator      Dismiss animator. Add animations to this object to run them alongside the dismiss transition.
 */
- (void)editMenuInteraction:(UIEditMenuInteraction *)interaction willDismissMenuForConfiguration:(UIEditMenuConfiguration *)configuration animator:(id<UIEditMenuInteractionAnimating>)animator;


@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIEditMenuInteraction.h>
#endif
