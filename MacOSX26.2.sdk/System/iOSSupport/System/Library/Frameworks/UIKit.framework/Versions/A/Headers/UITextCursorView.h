#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextCursorView.h>)
//
//  UITextCursorView.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <UIKit/UIView.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// @protocol   UITextCursorView
/// @abstract   A view that displays a flashing cursor (aka "caret") view.
/// @discussion When a selection is not ranged (or has a zero-length), a cursor view is displayed.
UIKIT_EXTERN API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UITextCursorView <UICoordinateSpace>

/// Enables the blink animation. Disabled by default.
@property (nonatomic, readwrite, getter=isBlinking) BOOL blinking;

/// Call this when the cursor is moving (i.e., during typing) to make sure the cursor doesn't blink while text is being inserted.
- (void)resetBlinkAnimation;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITextCursorView.h>
#endif
