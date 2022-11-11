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

NS_ASSUME_NONNULL_BEGIN

typedef CGFloat UIWindowLevel NS_TYPED_EXTENSIBLE_ENUM;

@class UIEvent, UIScreen, NSUndoManager, UIViewController, UIWindowScene;

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) NS_SWIFT_UI_ACTOR
@interface UIWindow : UIView

// instantiate a UIWindow already associated with a given UIWindowScene instance, with matching frame & interface orientations.
- (instancetype)initWithWindowScene:(UIWindowScene *)windowScene API_AVAILABLE(ios(13.0));

// If nil, window will not appear on any screen.
// changing the UIWindowScene may be an expensive operation and should not be done in performance-sensitive code
@property(nullable, nonatomic, weak) UIWindowScene *windowScene API_AVAILABLE(ios(13.0));

// Indicates whether content should drive the size of arbitrarily resizable windows (which are currently present only on macOS).
@property(nonatomic, setter=setCanResizeToFitContent:) BOOL canResizeToFitContent API_AVAILABLE(macCatalyst(13.0));

@property(nonatomic,strong) UIScreen *screen API_AVAILABLE(ios(3.2));  // default is [UIScreen mainScreen]. changing the screen may be an expensive operation and should not be done in performance-sensitive code
- (void)setScreen:(UIScreen *)screen API_DEPRECATED_WITH_REPLACEMENT("setWindowScene:", ios(3.2, 13.0));

@property(nonatomic) UIWindowLevel windowLevel;                   // default = 0.0

// In apps built against the iOS 15 or tvOS 15 SDK (or later), this property returns YES if
// the window is its scene's key window. For apps built against earlier SDKs, this property
// returns YES if the window is the application's key window.
@property(nonatomic,readonly,getter=isKeyWindow) BOOL keyWindow;

// Default is YES. Return NO to indicate the window cannot become the key window.
@property (nonatomic, readonly) BOOL canBecomeKeyWindow API_AVAILABLE(ios(15.0));

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

UIKIT_EXTERN const UIWindowLevel UIWindowLevelNormal;
UIKIT_EXTERN const UIWindowLevel UIWindowLevelAlert;
UIKIT_EXTERN const UIWindowLevel UIWindowLevelStatusBar API_UNAVAILABLE(tvos);

// Posted when the window becomes visible with a nil userInfo dictionary.
UIKIT_EXTERN NSNotificationName const UIWindowDidBecomeVisibleNotification;

// Posted when the window becomes hidden with a nil userInfo dictionary.
UIKIT_EXTERN NSNotificationName const UIWindowDidBecomeHiddenNotification;

// Posted when the window becomes the key window with a nil userInfo dictionary. In apps built
// against the iOS 15 or tvOS 15 SDK (or later), this notification will be posted when the window
// becomes its scene's key window. For apps built against earlier SDKs, it will be posted when
// the window becomes the application's key window.
UIKIT_EXTERN NSNotificationName const UIWindowDidBecomeKeyNotification;

// Posted when the window resigns key window status with a nil userInfo dictionary. In apps built
// against the iOS 15 or tvOS 15 SDK (or later), this notification will be posted when the window
// resigns key in its scene. For apps built against earlier SDKs, it will be posted when the window
// resigns key in the application.
UIKIT_EXTERN NSNotificationName const UIWindowDidResignKeyNotification;

// Each notification includes a nil object and a userInfo dictionary containing the
// beginning and ending keyboard frame in screen coordinates. Use the various UIView and
// UIWindow convertRect facilities to get the frame in the desired coordinate system.
// Animation key/value pairs are only available for the "will" family of notification.
UIKIT_EXTERN NSNotificationName const UIKeyboardWillShowNotification API_UNAVAILABLE(tvos);
UIKIT_EXTERN NSNotificationName const UIKeyboardDidShowNotification API_UNAVAILABLE(tvos);
UIKIT_EXTERN NSNotificationName const UIKeyboardWillHideNotification API_UNAVAILABLE(tvos);
UIKIT_EXTERN NSNotificationName const UIKeyboardDidHideNotification API_UNAVAILABLE(tvos);

UIKIT_EXTERN NSString *const UIKeyboardFrameBeginUserInfoKey        API_AVAILABLE(ios(3.2)) API_UNAVAILABLE(tvos); // NSValue of CGRect
UIKIT_EXTERN NSString *const UIKeyboardFrameEndUserInfoKey          API_AVAILABLE(ios(3.2)) API_UNAVAILABLE(tvos); // NSValue of CGRect
UIKIT_EXTERN NSString *const UIKeyboardAnimationDurationUserInfoKey API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(tvos); // NSNumber of double
UIKIT_EXTERN NSString *const UIKeyboardAnimationCurveUserInfoKey    API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(tvos); // NSNumber of NSUInteger (UIViewAnimationCurve)
UIKIT_EXTERN NSString *const UIKeyboardIsLocalUserInfoKey           API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(tvos); // NSNumber of BOOL

// Like the standard keyboard notifications above, these additional notifications include
// a nil object and begin/end frames of the keyboard in screen coordinates in the userInfo dictionary.
UIKIT_EXTERN NSNotificationName const UIKeyboardWillChangeFrameNotification  API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(tvos);
UIKIT_EXTERN NSNotificationName const UIKeyboardDidChangeFrameNotification   API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(tvos);

// These keys are superseded by UIKeyboardFrameBeginUserInfoKey and UIKeyboardFrameEndUserInfoKey.
UIKIT_EXTERN NSString *const UIKeyboardCenterBeginUserInfoKey   API_DEPRECATED("", ios(2.0, 3.2)) API_UNAVAILABLE(tvos);
UIKIT_EXTERN NSString *const UIKeyboardCenterEndUserInfoKey     API_DEPRECATED("", ios(2.0, 3.2)) API_UNAVAILABLE(tvos);
UIKIT_EXTERN NSString *const UIKeyboardBoundsUserInfoKey        API_DEPRECATED("", ios(2.0, 3.2)) API_UNAVAILABLE(tvos);

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIWindow.h>
#endif
