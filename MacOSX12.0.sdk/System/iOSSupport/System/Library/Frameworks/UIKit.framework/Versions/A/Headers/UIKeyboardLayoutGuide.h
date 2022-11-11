#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIKeyboardLayoutGuide.h>)
//
//  UIKeyboardLayoutGuide.h
//  UIKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>
#import <UIKit/UITrackingLayoutGuide.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIKeyboardLayoutGuide : UITrackingLayoutGuide

/// The automatic behavior is to track the keyboard only when docked. When offscreen or undocked, the topAnchor is tied to the safeAreaLayoutGuide's bottomAnchor. To instead follow all keyboard anchors even when undocked or floating, set followsUndockedKeyboard to YES. 
@property (nonatomic, readwrite) BOOL followsUndockedKeyboard;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIKeyboardLayoutGuide.h>
#endif
