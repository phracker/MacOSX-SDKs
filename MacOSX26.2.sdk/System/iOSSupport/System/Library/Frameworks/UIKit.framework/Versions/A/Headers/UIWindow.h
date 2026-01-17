#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIWindow.h>)
//
//  UIWindow.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIApplication.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef CGFloat UIWindowLevel NS_TYPED_EXTENSIBLE_ENUM API_UNAVAILABLE(watchos);

@class UIEvent, UIScreen, NSUndoManager, UIViewController, UIWindowScene;

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIWindow : UIView

// instantiate a UIWindow already associated with a given UIWindowScene instance, with matching frame & interface orientations.
- (instancetype)initWithWindowScene:(UIWindowScene *)windowScene NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

- (instancetype)initWithFrame:(CGRect)frame NS_DESIGNATED_INITIALIZER API_DEPRECATED("Use init(windowScene:) instead.", ios(2.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);
- (instancetype)init API_DEPRECATED("Use init(windowScene:) instead.", ios(2.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

// If nil, window will not appear on any screen.
// changing the UIWindowScene may be an expensive operation and should not be done in performance-sensitive code
@property(nullable, nonatomic, weak) UIWindowScene *windowScene API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

// Indicates whether content should drive the size of arbitrarily resizable windows (which are currently present only on macOS).
@property(nonatomic, setter=setCanResizeToFitContent:) BOOL canResizeToFitContent API_AVAILABLE(macCatalyst(13.0)) API_UNAVAILABLE(watchos);

@property(nonatomic,strong) UIScreen *screen API_AVAILABLE(ios(3.2)) API_UNAVAILABLE(visionos);  // default is [UIScreen mainScreen]. changing the screen may be an expensive operation and should not be done in performance-sensitive code
- (void)setScreen:(UIScreen *)screen API_DEPRECATED_WITH_REPLACEMENT("setWindowScene:", ios(3.2, 13.0)) API_UNAVAILABLE(visionos);

@property(nonatomic) UIWindowLevel windowLevel;                   // default = 0.0

// In apps built against the iOS 15 or tvOS 15 SDK (or later), this property returns YES if
// the window is its scene's key window. For apps built against earlier SDKs, this property
// returns YES if the window is the application's key window.
@property(nonatomic,readonly,getter=isKeyWindow) BOOL keyWindow;

// Default is YES. Return NO to indicate the window cannot become the key window.
@property (nonatomic, readonly) BOOL canBecomeKeyWindow API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos);

// Override point for subclasses. Do not call directly. Informs the window it has become the
// key window. In apps built against the iOS 15 or tvOS 15 SDK (or later), this method will
// be called when the window becomes its scene's key window. For apps built against earlier
// SDKs, this method will be called when the window becomes the application's key window.
- (void)becomeKeyWindow;

// Override point for subclasses. Do not call directly. Informs the window it has resigned key
// window status. In apps built against the iOS 15 or tvOS 15 SDK (or later), this method will
// be called when the window resigns key in its scene. For apps built against earlier SDKs,
// this method will be called when the window resigns key in the application.
- (void)resignKeyWindow;

// Make the window key without changing visibility.
- (void)makeKeyWindow;

// Convenience. Most apps call this to show a window and also make it key.
// To make the window visible without becoming key, just use UIView's hidden property.
- (void)makeKeyAndVisible;

@property(nullable, nonatomic,strong) UIViewController *rootViewController API_AVAILABLE(ios(4.0));  // default is nil

- (void)sendEvent:(UIEvent *)event;                    // called by UIApplication to dispatch events to views inside the window

- (CGPoint)convertPoint:(CGPoint)point toWindow:(nullable UIWindow *)window;    // can be used to convert to another window
- (CGPoint)convertPoint:(CGPoint)point fromWindow:(nullable UIWindow *)window;  // pass in nil to mean screen
- (CGRect)convertRect:(CGRect)rect toWindow:(nullable UIWindow *)window;
- (CGRect)convertRect:(CGRect)rect fromWindow:(nullable UIWindow *)window;

@end

API_UNAVAILABLE(watchos) @protocol UILayoutGuideAspectFitting <NSObject>

/// Update the aspect ratio (width / height) for the given content
/// Defaults to 1.0. Must be > 0.0 and values may be clamped within a reasonable range of approximately 1:100 to 100:1.
@property (nonatomic, readwrite) CGFloat aspectRatio;

@end

@interface UIWindow(UIWindowLayout)

/// This layout guide is designed specifically for full-screen media content, and attaching constraints from deep in the window's view hierarchy will raise an exception.
///
/// This guide provides a layout area for placing media content of a given aspect ratio (width over height) such that the content will be completely visible within the window.
/// Compared to the standard `safeAreaLayoutGuide` on a view, this guide takes into account the aspect ratio of the content, allowing it the maximum size within the window's
/// true safe area, including the actual shape of the screen when that is the only factor contributing to the safe area. The rect defined by this guide will be centered within the
/// window.
///
/// This layout guide should only be used for fixed aspect ratio content that is intended to fill the window (such as image or video content) and is not a replacement for the
/// standard `safeAreaLayoutGuide` on each UIView which should be used for most content layout. The `safeAreaAspectFitLayoutGuide` should only be used with views
/// that are direct subviews of, or very close descendants of, the guide's window. Creating constraints from this layout guide to views deeper in the view hierarchy or across
/// views owned by child view controllers can significantly degrade performance and possibly raise an exception. Additionally, the safe area insets added by child view
/// controllers will not be reflected in these cases. For anything other than full-screen/window media content, the standard `safeAreaLayoutGuide` on UIView should be used.
@property(nonatomic,readonly,strong) UILayoutGuide<UILayoutGuideAspectFitting> *safeAreaAspectFitLayoutGuide API_AVAILABLE(ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

@end

UIKIT_EXTERN const UIWindowLevel UIWindowLevelNormal API_UNAVAILABLE(watchos);
UIKIT_EXTERN const UIWindowLevel UIWindowLevelAlert API_UNAVAILABLE(watchos);
UIKIT_EXTERN const UIWindowLevel UIWindowLevelStatusBar API_UNAVAILABLE(tvos, watchos);

// Posted when the window becomes visible with a nil userInfo dictionary.
UIKIT_EXTERN NSNotificationName const UIWindowDidBecomeVisibleNotification API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;

// Posted when the window becomes hidden with a nil userInfo dictionary.
UIKIT_EXTERN NSNotificationName const UIWindowDidBecomeHiddenNotification API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;

// Posted when the window becomes the key window with a nil userInfo dictionary. In apps built
// against the iOS 15 or tvOS 15 SDK (or later), this notification will be posted when the window
// becomes its scene's key window. For apps built against earlier SDKs, it will be posted when
// the window becomes the application's key window.
UIKIT_EXTERN NSNotificationName const UIWindowDidBecomeKeyNotification API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;

// Posted when the window resigns key window status with a nil userInfo dictionary. In apps built
// against the iOS 15 or tvOS 15 SDK (or later), this notification will be posted when the window
// resigns key in its scene. For apps built against earlier SDKs, it will be posted when the window
// resigns key in the application.
UIKIT_EXTERN NSNotificationName const UIWindowDidResignKeyNotification API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;

// The notification object is the UIScreen that contains the keyboard. Each notification includes 
// a userInfo dictionary containing the beginning and ending keyboard frame in screen coordinates.
// Use the various UICoordinateSpace convertRect facilities to get the frame in the desired coordinate system.
// Animation key/value pairs are only available for the "will" family of notification.
UIKIT_EXTERN NSNotificationName const UIKeyboardWillShowNotification API_UNAVAILABLE(tvos, watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UIKeyboardDidShowNotification API_UNAVAILABLE(tvos, watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UIKeyboardWillHideNotification API_UNAVAILABLE(tvos, watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UIKeyboardDidHideNotification API_UNAVAILABLE(tvos, watchos) NS_SWIFT_NONISOLATED;

UIKIT_EXTERN NSString *const UIKeyboardFrameBeginUserInfoKey        API_AVAILABLE(ios(3.2)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_NONISOLATED; // NSValue of CGRect
UIKIT_EXTERN NSString *const UIKeyboardFrameEndUserInfoKey          API_AVAILABLE(ios(3.2)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_NONISOLATED; // NSValue of CGRect
UIKIT_EXTERN NSString *const UIKeyboardAnimationDurationUserInfoKey API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_NONISOLATED; // NSNumber of double
UIKIT_EXTERN NSString *const UIKeyboardAnimationCurveUserInfoKey    API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_NONISOLATED; // NSNumber of NSUInteger (UIViewAnimationCurve)
UIKIT_EXTERN NSString *const UIKeyboardIsLocalUserInfoKey           API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_NONISOLATED; // NSNumber of BOOL

// Like the standard keyboard notifications above, these additional notifications include
// a nil object and begin/end frames of the keyboard in screen coordinates in the userInfo dictionary.
UIKIT_EXTERN NSNotificationName const UIKeyboardWillChangeFrameNotification  API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UIKeyboardDidChangeFrameNotification   API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_NONISOLATED;

// These keys are superseded by UIKeyboardFrameBeginUserInfoKey and UIKeyboardFrameEndUserInfoKey.
UIKIT_EXTERN NSString *const UIKeyboardCenterBeginUserInfoKey   API_DEPRECATED("", ios(2.0, 3.2)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSString *const UIKeyboardCenterEndUserInfoKey     API_DEPRECATED("", ios(2.0, 3.2)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSString *const UIKeyboardBoundsUserInfoKey        API_DEPRECATED("", ios(2.0, 3.2)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos) NS_SWIFT_NONISOLATED;

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIWindow.h>
#endif
