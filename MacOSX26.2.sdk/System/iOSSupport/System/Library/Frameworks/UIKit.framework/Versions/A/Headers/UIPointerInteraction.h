#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPointerInteraction.h>)
//
//  UIPointerInteraction.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIInteraction.h>
#import <UIKit/UIPointerRegion.h>
#import <UIKit/UIPointerStyle.h>

@class UIPointerRegionRequest;
@protocol UIPointerInteractionDelegate, UIPointerInteractionAnimating;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIPointerInteraction : NSObject <UIInteraction>

@property (nonatomic, weak, readonly, nullable) id<UIPointerInteractionDelegate> delegate;
@property (nonatomic, getter=isEnabled) BOOL enabled;

- (instancetype)initWithDelegate:(nullable id<UIPointerInteractionDelegate>)delegate NS_DESIGNATED_INITIALIZER;

/*!
 * @abstract  Call this method to cause the interaction to update the pointer in response to some event.
 */
- (void)invalidate;

@end


UIKIT_EXTERN API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@protocol UIPointerInteractionDelegate <NSObject>

@optional

/*!
 * @abstract Called as the pointer moves within the interaction's view.
 *
 * @param interaction    This UIPointerInteraction.
 * @param request        Request object describing the pointer's location in the interaction's view.
 * @param defaultRegion  Region representing the entire surface of the interaction's view.
 *
 * @return A UIPointerRegion in which to apply a pointer style. Return nil to indicate that this interaction should not customize the pointer for the current location.
 */
- (nullable UIPointerRegion *)pointerInteraction:(UIPointerInteraction *)interaction regionForRequest:(UIPointerRegionRequest *)request defaultRegion:(UIPointerRegion *)defaultRegion;

/*!
 * @abstract Called after the interaction receives a new UIPointerRegion from pointerInteraction:regionForRequest:defaultRegion:.
 *
 * @param interaction  This UIPointerInteraction.
 * @param region       The UIPointerRegion for which a style is being requested.
 *
 * @return A UIPointerStyle describing the desired hover effect or pointer appearance for the given UIPointerRegion.
 */
- (nullable UIPointerStyle *)pointerInteraction:(UIPointerInteraction *)interaction styleForRegion:(UIPointerRegion *)region;

/*!
 * @abstract Called when the pointer enters a given region.
 *
 * @param interaction  This UIPointerInteraction.
 * @param region       The UIPointerRegion the pointer is about to enter.
 * @param animator     Region entrance animator. Add animations to run them alongside the pointer's entrance animation.
 */
- (void)pointerInteraction:(UIPointerInteraction *)interaction willEnterRegion:(UIPointerRegion *)region animator:(id<UIPointerInteractionAnimating>)animator;

/*!
 * @abstract Called when the pointer exists a given region.
 *
 * @param interaction  This UIPointerInteraction.
 * @param region       The UIPointerRegion the pointer is about to exit.
 * @param animator     Region exit animator. Add animations to run them alongside the pointer's exit animation.
 */
- (void)pointerInteraction:(UIPointerInteraction *)interaction willExitRegion:(UIPointerRegion *)region animator:(id<UIPointerInteractionAnimating>)animator NS_SWIFT_NAME(pointerInteraction(_:willExit:animator:));

@end


UIKIT_EXTERN API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIPointerRegionRequest : NSObject

/// The location of the pointer in the interaction's view's coordinate space.
@property (nonatomic, readonly) CGPoint location;

/// Key modifier flags representing keyboard keys pressed by the user at the time of this request.
@property (nonatomic, readonly) UIKeyModifierFlags modifiers;

@end


UIKIT_EXTERN API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@protocol UIPointerInteractionAnimating <NSObject>

- (void)addAnimations:(void (^)(void))animations;
- (void)addCompletion:(void (^)(BOOL finished))completion NS_SWIFT_DISABLE_ASYNC;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIPointerInteraction.h>
#endif
