#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIFocusSystem+UIKitAdditions.h>)
//
//  UIFocusSystem+UIKitAdditions.h
//  UIKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <UIKit/UIFocusSystem.h>
#import <UIKit/UIWindowScene.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@interface UIFocusSystem (Sound)

/// Registers a sound file for a given identifier.
+ (void)registerURL:(NSURL *)soundFileURL forSoundIdentifier:(UIFocusSoundIdentifier)identifier API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios, watchos);

@end


@interface UIWindowScene (UIFocusSystem)
/// Returns the focus system that is responsible for this scene or nil if this scene does not support focus.
@property (nullable, nonatomic, readonly) UIFocusSystem *focusSystem API_AVAILABLE(ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIFocusSystem+UIKitAdditions.h>
#endif
