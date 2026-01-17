#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIFocusAnimationCoordinator.h>)
//
//  UIFocusAnimationCoordinator.h
//  UIKit
//
//  Copyright © 2015-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)


/// UIFocusAnimationContext is used to provide UIKit-determined context about animations that are related to a focus update.
UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UIFocusAnimationContext <NSObject>

/// The duration of the main animations in seconds.
@property (nonatomic, readonly) NSTimeInterval duration;

@end

/// UIFocusAnimationCoordinator is used to coordinate disparate animations that are related to a focus update.
UIKIT_EXTERN API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIFocusAnimationCoordinator : NSObject

/**
 Specifies focus-related animations that should be coordinated with the animations of the focusing or un-focusing view.
 
 Any animations specified will be run in the same animation context as the main animation. The completion block is invoked after the main animation completes.
 (Note that this may not be after all the coordinated animations specified by the call complete if the duration is not inherited.)
 
 It is perfectly legitimate to only specify a completion block.
 */
- (void)addCoordinatedAnimations:(nullable void (^)(void))animations completion:(nullable void (^)(void))completion NS_SWIFT_DISABLE_ASYNC;

/**
 Specifies focus-related animations that should be coordinated with the animations of the focusing item.

 Any animations specified will be run in the same animation context as the main animation. The completion block is invoked after the UIKit-defined animations complete.

 It is perfectly legitimate to only specify a completion block.

 A context object is provided in the animation block with details of the UIKit-defined animations being run for the focusing item.
 */
- (void)addCoordinatedFocusingAnimations:(void (^ _Nullable)(id<UIFocusAnimationContext> animationContext))animations completion:(void (^ _Nullable)(void))completion NS_SWIFT_DISABLE_ASYNC API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

/**
 Specifies focus-related animations that should be coordinated with the animations of the un-focusing item.

 Any animations specified will be run in the same animation context as the main animation. The completion block is invoked after the UIKit-defined animations complete.

 It is perfectly legitimate to only specify a completion block.

 A context object is provided in the animation block with details of the UIKit-defined animations being run for the un-focusing item.
 */
- (void)addCoordinatedUnfocusingAnimations:(void (^ _Nullable)(id<UIFocusAnimationContext> animationContext))animations completion:(void (^ _Nullable)(void))completion NS_SWIFT_DISABLE_ASYNC API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIFocusAnimationCoordinator.h>
#endif
