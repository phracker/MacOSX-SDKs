#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIScreen.h>)
//
//  UIScreen.h
//  UIKit
//
//  Copyright (c) 2007-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UITraitCollection.h>
#import <UIKit/UIView.h>

NS_ASSUME_NONNULL_BEGIN

@class UIScreenMode, CADisplayLink, UIView;

// Object is the UIScreen that represents the new screen. Connection notifications are not sent for screens present when the application is first launched
UIKIT_EXTERN NSNotificationName const UIScreenDidConnectNotification API_AVAILABLE(ios(3.2));
// Object is the UIScreen that represented the disconnected screen.
UIKIT_EXTERN NSNotificationName const UIScreenDidDisconnectNotification API_AVAILABLE(ios(3.2));
// Object is the UIScreen which changed. [object currentMode] is the new UIScreenMode.
UIKIT_EXTERN NSNotificationName const UIScreenModeDidChangeNotification API_AVAILABLE(ios(3.2));
UIKIT_EXTERN NSNotificationName const UIScreenBrightnessDidChangeNotification API_AVAILABLE(ios(5.0));
// Object is the UIScreen which changed. [object isCaptured] is the new value of captured property.
UIKIT_EXTERN NSNotificationName const UIScreenCapturedDidChangeNotification API_AVAILABLE(ios(11.0));

// when the connected screen is overscanning, UIScreen can attempt to compensate for the overscan to avoid clipping
typedef NS_ENUM(NSInteger, UIScreenOverscanCompensation) {
    UIScreenOverscanCompensationScale,                           // the final composited framebuffer for the screen is scaled to avoid clipping
    UIScreenOverscanCompensationInsetBounds,                     // the screen's bounds will be inset in the framebuffer to avoid clipping. no scaling will occur
    UIScreenOverscanCompensationNone API_AVAILABLE(ios(9.0)), // no scaling will occur. use overscanCompensationInsets to determine the necessary insets to avoid clipping
    
    UIScreenOverscanCompensationInsetApplicationFrame NS_ENUM_DEPRECATED_IOS(5_0, 9_0, "Use UIScreenOverscanCompensationNone") = 2,
};

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) @interface UIScreen : NSObject <UITraitEnvironment>

@property(class, nonatomic, readonly) NSArray<UIScreen *> *screens API_AVAILABLE(ios(3.2));          // all screens currently attached to the device
@property(class, nonatomic, readonly) UIScreen *mainScreen;      // the device's internal screen

@property(nonatomic,readonly) CGRect  bounds;                // Bounds of entire screen in points
@property(nonatomic,readonly) CGFloat scale API_AVAILABLE(ios(4.0));

@property(nonatomic,readonly,copy) NSArray<UIScreenMode *> *availableModes API_AVAILABLE(ios(3.2)) API_UNAVAILABLE(tvos);             // The list of modes that this screen supports
@property(nullable, nonatomic,readonly,strong) UIScreenMode *preferredMode API_AVAILABLE(ios(4.3)) API_UNAVAILABLE(tvos);       // Preferred mode of this screen. Choosing this mode will likely produce the best results
#if TARGET_OS_TV
@property(nullable,nonatomic,readonly,strong) UIScreenMode *currentMode API_AVAILABLE(ios(3.2));                  // Current mode of this screen
#else
@property(nullable,nonatomic,strong) UIScreenMode *currentMode API_AVAILABLE(ios(3.2));                  // Current mode of this screen
#endif
@property(nonatomic) UIScreenOverscanCompensation overscanCompensation API_AVAILABLE(ios(5.0)); // Default is UIScreenOverscanCompensationScale. Determines how the screen behaves if the connected display is overscanning

@property(nonatomic,readonly) UIEdgeInsets overscanCompensationInsets API_AVAILABLE(ios(9.0));  // The amount that should be inset to avoid clipping

@property(nullable, nonatomic,readonly,strong) UIScreen *mirroredScreen API_AVAILABLE(ios(4.3));          // The screen being mirrored by the receiver. nil if mirroring is disabled or unsupported. Moving a UIWindow to this screen will disable mirroring
@property(nonatomic,readonly,getter=isCaptured) BOOL captured API_AVAILABLE(ios(11.0)); // True if this screen is being captured (e.g. recorded, AirPlayed, mirrored, etc.)

@property(nonatomic) CGFloat brightness API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(tvos);        // 0 .. 1.0, where 1.0 is maximum brightness. Only supported by main screen.
@property(nonatomic) BOOL wantsSoftwareDimming API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(tvos); // Default is NO. If YES, brightness levels lower than that of which the hardware is capable are emulated in software, if necessary. Having enabled may entail performance cost.

@property (readonly) id <UICoordinateSpace> coordinateSpace API_AVAILABLE(ios(8.0));
@property (readonly) id <UICoordinateSpace> fixedCoordinateSpace API_AVAILABLE(ios(8.0));

@property(nonatomic,readonly) CGRect  nativeBounds API_AVAILABLE(ios(8.0));  // Native bounds of the physical screen in pixels
@property(nonatomic,readonly) CGFloat nativeScale  API_AVAILABLE(ios(8.0));  // Native scale factor of the physical screen

- (nullable CADisplayLink *)displayLinkWithTarget:(id)target selector:(SEL)sel API_AVAILABLE(ios(4.0));

@property (readonly) NSInteger maximumFramesPerSecond  API_AVAILABLE(ios(10.3)); // The maximumFramesPerSecond this screen is capable of

// The latency of the display hardware associated with this screen.
// Can be used along with CoreAudio devices' kAudioDeviceLatencyProperty to
// achieve A/V sync when writing custom video playback software.
// Will be `0` if display latency has not been calibrated by the user.
@property(nonatomic, readonly) CFTimeInterval calibratedLatency API_AVAILABLE(ios(13.0));

@property (nullable, nonatomic, weak, readonly) id<UIFocusItem> focusedItem API_AVAILABLE(ios(10.0)); // Returns the focused item for this screen's focus system. Use UIFocusSystem's focusedItem property instead – this property will be deprecated in a future release.
@property (nullable, nonatomic, weak, readonly) UIView *focusedView API_AVAILABLE(ios(9.0)); // If focusedItem is not a view, this returns that item's containing view. Otherwise they are equal. Use UIFocusSystem's focusedItem property instead – this property will be deprecated in a future release.
@property (readonly, nonatomic) BOOL supportsFocus API_AVAILABLE(ios(9.0));

@property(nonatomic,readonly) CGRect applicationFrame API_DEPRECATED_WITH_REPLACEMENT("bounds", ios(2.0, 9.0)) API_UNAVAILABLE(tvos);

@end

@interface UIScreen (UISnapshotting)
// Please see snapshotViewAfterScreenUpdates: in UIView.h for some important details on the behavior of this method when called from layoutSubviews.
- (UIView *)snapshotViewAfterScreenUpdates:(BOOL)afterUpdates API_AVAILABLE(ios(7.0));
@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIScreen.h>
#endif
