#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIFocusSystem.h>)
//
//  UIFocusSystem.h
//  UIKit
//
//  Copyright © 2016-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIFocus.h>
#import <UIKit/UIFocusDefines.h>


NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// UIFocusSystem instances manage focus state within a part of the user interface. They are in charge of tracking the current focused item, as well as processing focus updates.
UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIFocusSystem : NSObject

/// The currently focused item in this focus system.
@property (nonatomic, weak, readonly, nullable) id<UIFocusItem> focusedItem API_AVAILABLE(tvos(12.0), ios(12.0)) API_UNAVAILABLE(watchos);

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// Return the focus system that the provided environment is contained in. Returns nil if focus
/// interaction is not supported, or if the environment is not associated with any focus system.
#if __swift__
+ (nullable UIFocusSystem *)focusSystemForEnvironment:(id<UIFocusEnvironment>)environment API_DEPRECATED("Use UIFocusSystem.focusSystem(for:) instead.", tvos(12.0, 15.0), ios(12.0, 15.0), visionos(1.0, 1.0));
#else
+ (nullable UIFocusSystem *)focusSystemForEnvironment:(id<UIFocusEnvironment>)environment API_AVAILABLE(tvos(12.0), ios(12.0)) API_UNAVAILABLE(watchos);
#endif

/// Requests a focus update to the specified environment. If accepted, the focus update will happen
/// in the next run loop cycle.
- (void)requestFocusUpdateToEnvironment:(id<UIFocusEnvironment>)environment API_AVAILABLE(tvos(12.0), ios(12.0)) API_UNAVAILABLE(watchos);

/// Forces any pending focus update to be committed immediately.
- (void)updateFocusIfNeeded API_AVAILABLE(tvos(12.0), ios(12.0)) API_UNAVAILABLE(watchos);

/// Returns true if `environment` is an ancestor of `otherEnvironment`, or false if otherwise.
+ (BOOL)environment:(id<UIFocusEnvironment>)environment containsEnvironment:(id<UIFocusEnvironment>)otherEnvironment;

@end

NS_HEADER_AUDIT_END(nullability, sendability)


#import <UIKit/UIFocusSystem+UIKitAdditions.h>

#else
#import <UIKitCore/UIFocusSystem.h>
#endif
