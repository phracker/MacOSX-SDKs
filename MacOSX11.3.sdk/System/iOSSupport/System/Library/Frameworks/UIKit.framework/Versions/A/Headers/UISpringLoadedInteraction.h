#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISpringLoadedInteraction.h>)
//
//  UISpringLoadedInteraction.h
//  UIKit
//
//  Copyright © 2017-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIInteraction.h>

NS_ASSUME_NONNULL_BEGIN

/**
 An object conforming to UISpringLoadedInteractionEffect uses UISpringLoadedInteractionEffectState
 to style the interaction view for the current springloading state.
 
 - UISpringLoadedInteractionEffectStateInactive: the view is not engaged in springloading and should be displayed with its default style.
 - UISpringLoadedInteractionEffectStatePossible: the view may springload and should provide a visual cue to the user. The default effect highlights the view.
 - UISpringLoadedInteractionEffectStateActivating: the view is about to springload. The default effect will briefly flash while in this state.
 - UISpringLoadedInteractionEffectStateActivated: the view springloaded and the activation handler is called. The default effect will restore the view to its original appearance.
 */
typedef NS_ENUM(NSInteger, UISpringLoadedInteractionEffectState) {
    UISpringLoadedInteractionEffectStateInactive,
    UISpringLoadedInteractionEffectStatePossible,
    UISpringLoadedInteractionEffectStateActivating,
    UISpringLoadedInteractionEffectStateActivated,
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

@protocol UISpringLoadedInteractionBehavior, UISpringLoadedInteractionEffect, UISpringLoadedInteractionContext;

UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@interface UISpringLoadedInteraction : NSObject <UIInteraction>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;


/**
 The designated `UISpringLoadedInteraction` initializer.
 
 @param interactionBehavior The interaction behavior object controlling the springloaded interaction activation. If nil, the default behavior will be used.
 @param interactionEffect The interaction effect object styling the interaction's view. If nil, the default effect will be used.
 @param handler The handler to be performed when springloading is activated.
 @return An initialized springloaded interaction object or `nil` if the springloaded interaction could not be initialized.
 */
- (instancetype)initWithInteractionBehavior:(nullable id<UISpringLoadedInteractionBehavior>)interactionBehavior interactionEffect:(nullable id<UISpringLoadedInteractionEffect>)interactionEffect activationHandler:(void(^)(UISpringLoadedInteraction *interaction, id<UISpringLoadedInteractionContext> context))handler NS_DESIGNATED_INITIALIZER;


/**
 A springloaded interaction with the default interaction behavior and effect.
 
 @param handler The handler to be performed when springloading is activated.
 @return An initialized springloaded interaction object or `nil` if the springloaded interaction could not be initialized.
 */
- (instancetype)initWithActivationHandler:(void(^)(UISpringLoadedInteraction *interaction, id<UISpringLoadedInteractionContext> context))handler;

@property (nonatomic, strong, readonly) id<UISpringLoadedInteractionBehavior> interactionBehavior;
@property (nonatomic, strong, readonly) id<UISpringLoadedInteractionEffect> interactionEffect;

@end

/**
 The interaction behavior of a `UISpringLoadedInteraction` object must adopt the `UISpringLoadedInteractionBehavior` protocol.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos)
@protocol UISpringLoadedInteractionBehavior <NSObject>

@required

/**
 Returns whether springloading should begin or continue for a given interaction.
 
 @param interaction The springloaded interaction object requesting this information
 @param context An object that provides information about the current drag.
 @return true if the interaction should begin or continue springloading.
 */
- (BOOL)shouldAllowInteraction:(UISpringLoadedInteraction *)interaction withContext:(id<UISpringLoadedInteractionContext>)context;

@optional
/**
 Informs the behavior that springloading for a given interaction was cancelled or activated.
 
 @param interaction The springloaded interaction object providing this information.
 */
- (void)interactionDidFinish:(UISpringLoadedInteraction *)interaction;

@end

/**
 The interaction effect of a `UISpringLoadedInteraction` object must adopt the `UISpringLoadedInteractionEffect` protocol.
 It is responsible for styling the interaction view according to the current springloading state.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos)
@protocol UISpringLoadedInteractionEffect <NSObject>

@required

/**
 Informs the effect that the springloading state changed.
 
 @param interaction The springloaded interaction providing this information.
 @param context An object that provides information about the current springloading state.
 */
- (void)interaction:(UISpringLoadedInteraction *)interaction didChangeWithContext:(id<UISpringLoadedInteractionContext>)context;

@end


/**
 UISpringLoadedContext supplies information about the springloading state and current drag.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos)
@protocol UISpringLoadedInteractionContext <NSObject>

/**
 The state that describes the current springloading style.
 */
@property (nonatomic, readonly) UISpringLoadedInteractionEffectState state;

/**
 The view to which the interaction effect is applied. Defaults to the interaction's view.
 */
@property (nonatomic, strong, nullable) UIView *targetView;

/**
 The `targetItem` allows to distinguish a region of the view on which the interaction is installed.
 It is convenient to set this property to a model object associated to `targetView`.
 */
@property (nonatomic, strong, nullable) id targetItem;

/**
 Returns the point computed as the location of the current drag in a given view.
 
 @param view A view on which the drag is taking place. Specify nil to indicate the window.
 @return A point in the local coordinate system of `view`.
 */
- (CGPoint)locationInView:(nullable UIView *)view;

@end

NS_ASSUME_NONNULL_END


#else
#import <UIKitCore/UISpringLoadedInteraction.h>
#endif
