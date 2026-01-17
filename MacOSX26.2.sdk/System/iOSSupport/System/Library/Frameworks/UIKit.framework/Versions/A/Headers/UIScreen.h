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

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIScreenMode, CADisplayLink, UIView;

// Object is the UIScreen that represents the new screen. Connection notifications are not sent for screens present when the application is first launched
UIKIT_EXTERN NSNotificationName const UIScreenDidConnectNotification API_DEPRECATED("Use UISceneDelegate or related notifications to be informed of connecting scenes from other screens", ios(3.2, 16.0)) API_UNAVAILABLE(visionos, watchos) NS_SWIFT_NONISOLATED;
// Object is the UIScreen that represented the disconnected screen.
UIKIT_EXTERN NSNotificationName const UIScreenDidDisconnectNotification API_DEPRECATED("Use UISceneDelegate or related notifications to be informed of disconnecting scenes from other screens", ios(3.2, 16.0)) API_UNAVAILABLE(visionos, watchos) NS_SWIFT_NONISOLATED;
// Object is the UIScreen which changed. [object currentMode] is the new UIScreenMode.
UIKIT_EXTERN NSNotificationName const UIScreenModeDidChangeNotification API_AVAILABLE(ios(3.2)) API_UNAVAILABLE(visionos, watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UIScreenBrightnessDidChangeNotification API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(visionos, watchos) NS_SWIFT_NONISOLATED;
// Object is the UIScreen which changed. [object isCaptured] is the new value of captured property.
UIKIT_EXTERN NSNotificationName const UIScreenCapturedDidChangeNotification API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(visionos, watchos) NS_SWIFT_NONISOLATED;
// Object is the UIScreen which changed. [object referenceDisplayModeStatus] is the screen's new reference display mode status.
UIKIT_EXTERN NSNotificationName const UIScreenReferenceDisplayModeStatusDidChangeNotification API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(visionos, watchos) NS_SWIFT_NONISOLATED;


// when the connected screen is overscanning, UIScreen can attempt to compensate for the overscan to avoid clipping
typedef NS_ENUM(NSInteger, UIScreenOverscanCompensation) {
    UIScreenOverscanCompensationScale,                           // the final composited framebuffer for the screen is scaled to avoid clipping
    UIScreenOverscanCompensationInsetBounds,                     // the screen's bounds will be inset in the framebuffer to avoid clipping. no scaling will occur
    UIScreenOverscanCompensationNone API_AVAILABLE(ios(9.0)), // no scaling will occur. use overscanCompensationInsets to determine the necessary insets to avoid clipping
    
    UIScreenOverscanCompensationInsetApplicationFrame API_DEPRECATED_WITH_REPLACEMENT("UIScreenOverscanCompensationNone", ios(5.0, 9.0)) API_UNAVAILABLE(visionos, watchos) = 2,
} API_UNAVAILABLE(visionos, watchos);

// Describes the screen's reference display mode ability
typedef NS_ENUM(NSInteger, UIScreenReferenceDisplayModeStatus) {
    // Reference display modes are not supported on this display
    UIScreenReferenceDisplayModeStatusNotSupported,
    // Reference display modes are supported on this display but have not been enabled by the user
    UIScreenReferenceDisplayModeStatusNotEnabled,
    // A reference display mode is enabled, but temporarily can not be achieved. This may be due to thermal or power constraints.
    UIScreenReferenceDisplayModeStatusLimited,
    // A reference display mode is enabled and being displayed accurately
    UIScreenReferenceDisplayModeStatusEnabled
} API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(visionos, watchos);

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(visionos, watchos) NS_SWIFT_UI_ACTOR
@interface UIScreen : NSObject <UITraitEnvironment>

@property(class, nonatomic, readonly) NSArray<UIScreen *> *screens API_DEPRECATED("Use UIApplication.shared.openSessions to find open sessions with scenes from other screens", ios(3.2, 16.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos); // all screens currently attached to the device
@property(class, nonatomic, readonly) UIScreen *mainScreen API_DEPRECATED("Use a UIScreen instance found through context instead (i.e, view.window.windowScene.screen), or for properties like UIScreen.scale with trait equivalents, use a traitCollection found through context.", ios(2.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0)) API_UNAVAILABLE(watchos);

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
@property(nonatomic,readonly,getter=isCaptured) BOOL captured API_DEPRECATED("Use the sceneCaptureState in UITraitCollection instead.", ios(11.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos); // True if this screen is being captured (e.g. recorded, AirPlayed, mirrored, etc.)

@property(nonatomic) CGFloat brightness API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(tvos);        // 0 .. 1.0, where 1.0 is maximum brightness. Only supported by main screen.
@property(nonatomic) BOOL wantsSoftwareDimming API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(tvos); // Default is NO. If YES, brightness levels lower than that of which the hardware is capable are emulated in software, if necessary. Having enabled may entail performance cost.

@property (readonly) id <UICoordinateSpace> coordinateSpace API_AVAILABLE(ios(8.0));
@property (readonly) id <UICoordinateSpace> fixedCoordinateSpace API_AVAILABLE(ios(8.0));

@property(nonatomic,readonly) CGRect  nativeBounds API_AVAILABLE(ios(8.0));  // Native bounds of the physical screen in pixels
@property(nonatomic,readonly) CGFloat nativeScale  API_AVAILABLE(ios(8.0));  // Native scale factor of the physical screen

- (nullable CADisplayLink *)displayLinkWithTarget:(id)target selector:(SEL)sel API_AVAILABLE(ios(4.0));

@property (readonly) NSInteger maximumFramesPerSecond  API_AVAILABLE(ios(10.3)) API_UNAVAILABLE(watchos); // The maximumFramesPerSecond this screen is capable of

// The latency of the display hardware associated with this screen.
// Can be used along with CoreAudio devices' kAudioDeviceLatencyProperty to
// achieve A/V sync when writing custom video playback software.
// Will be `0` if display latency has not been calibrated by the user.
@property(nonatomic, readonly) CFTimeInterval calibratedLatency API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

@property (nonatomic, readonly) UIScreenReferenceDisplayModeStatus referenceDisplayModeStatus API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos);

// Headroom is the ratio of the luminance of the brightest white the display can currently produce to the luminance of SDR white, in the display's native color space.
// The screen’s current headroom can change depending on the display configuration and whether it is currently displaying any EDR content.
// If any onscreen layer has `wantsExtendedDynamicRangeContent == YES` set, all rendered content is limited to the screen's currentEDRHeadroom value.
@property (nonatomic, readonly) CGFloat currentEDRHeadroom API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos);
// Returns the maximum potential EDR headroom the screen is capable of displaying when EDR is enabled, regardless of whether EDR is currently enabled.
// The potential EDR headroom may change depending on the display configuration. For example, this may change when referenceDisplayModeStatus changes.
@property (nonatomic, readonly) CGFloat potentialEDRHeadroom API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos);


@property (nullable, nonatomic, weak, readonly) id<UIFocusItem> focusedItem API_DEPRECATED("Use -[UIWindowScene focusSystem].focusedItem instead", ios(10.0, 15.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);
@property (nullable, nonatomic, weak, readonly) UIView *focusedView API_DEPRECATED("Use -[UIWindowScene focusSystem].focusedItem instead", ios(9.0, 15.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);
@property (readonly, nonatomic) BOOL supportsFocus API_DEPRECATED("Use -[UIWindowScene focusSystem] != nil instead", ios(9.0, 15.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);

@property(nonatomic,readonly) CGRect applicationFrame API_DEPRECATED_WITH_REPLACEMENT("bounds", ios(2.0, 9.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos);

@end

@interface UIScreen (UISnapshotting)
// Please see snapshotViewAfterScreenUpdates: in UIView.h for some important details on the behavior of this method when called from layoutSubviews.
- (UIView *)snapshotViewAfterScreenUpdates:(BOOL)afterUpdates API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(visionos);
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIScreen.h>
#endif
