#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextLoupeSession.h>)
//
//  UITextLoupeSession.h
//  UIKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <UIKit/UIView.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(visionos, watchos) NS_SWIFT_UI_ACTOR
@interface UITextLoupeSession : NSObject

/// Begins a loupe session at the specified point. The system will animate the presentation of the loupe, as well as its position and hierarchy.
///
/// @param at   The point in @c view's coordinate space where the loupe should begin.
/// @param widgetView   Optionally, a system-provided selection view that the animation can start from.
/// @param view         The coordinate space that all subsequent movement updates are provided in.
+ (nullable instancetype)beginLoupeSessionAtPoint:(CGPoint)point
                          fromSelectionWidgetView:(nullable UIView *)selectionWidget
                                           inView:(UIView *)interactionView;

/// Call this when a text selection gesture moves to a particular point.
///
/// @param point    The center point of the touch tracked by the gesture recognizer.
/// @param caretRect    The current position of the caret/range handle. Pass in CGRectNull if there is no current selection/no caret rect visible.
/// @param trackingCaret    Provide YES if the loupe should track the caret instead of the touch.
- (void)moveToPoint:(CGPoint)point withCaretRect:(CGRect)caretRect trackingCaret:(BOOL)tracksCaret;

/// Invalidates the loupe session. Hides the loupe and cleans up transient state.
- (void)invalidate;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITextLoupeSession.h>
#endif
