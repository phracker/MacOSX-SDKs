#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIDevice.h>)
//
//  UIDevice.h
//  UIKit
//
//  Copyright (c) 2007-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UIDeviceOrientation) {
    UIDeviceOrientationUnknown,
    UIDeviceOrientationPortrait,            // Device oriented vertically, home button on the bottom
    UIDeviceOrientationPortraitUpsideDown,  // Device oriented vertically, home button on the top
    UIDeviceOrientationLandscapeLeft,       // Device oriented horizontally, home button on the right
    UIDeviceOrientationLandscapeRight,      // Device oriented horizontally, home button on the left
    UIDeviceOrientationFaceUp,              // Device oriented flat, face up
    UIDeviceOrientationFaceDown             // Device oriented flat, face down
} API_UNAVAILABLE(tvos);

typedef NS_ENUM(NSInteger, UIDeviceBatteryState) {
    UIDeviceBatteryStateUnknown,
    UIDeviceBatteryStateUnplugged,   // on battery, discharging
    UIDeviceBatteryStateCharging,    // plugged in, less than 100%
    UIDeviceBatteryStateFull,        // plugged in, at 100%
} API_UNAVAILABLE(tvos);              // available in iPhone 3.0

typedef NS_ENUM(NSInteger, UIUserInterfaceIdiom) {
    UIUserInterfaceIdiomUnspecified = -1,
    UIUserInterfaceIdiomPhone API_AVAILABLE(ios(3.2)), // iPhone and iPod touch style UI
    UIUserInterfaceIdiomPad API_AVAILABLE(ios(3.2)), // iPad style UI
    UIUserInterfaceIdiomTV API_AVAILABLE(ios(9.0)), // Apple TV style UI
    UIUserInterfaceIdiomCarPlay API_AVAILABLE(ios(9.0)), // CarPlay style UI
};

static inline BOOL UIDeviceOrientationIsPortrait(UIDeviceOrientation orientation)  API_UNAVAILABLE(tvos) {
    return ((orientation) == UIDeviceOrientationPortrait || (orientation) == UIDeviceOrientationPortraitUpsideDown);
}

static inline BOOL UIDeviceOrientationIsLandscape(UIDeviceOrientation orientation)  API_UNAVAILABLE(tvos) {
    return ((orientation) == UIDeviceOrientationLandscapeLeft || (orientation) == UIDeviceOrientationLandscapeRight);
}

static inline __attribute__((always_inline)) BOOL UIDeviceOrientationIsFlat(UIDeviceOrientation orientation)  API_UNAVAILABLE(tvos) {
    return ((orientation) == UIDeviceOrientationFaceUp || (orientation) == UIDeviceOrientationFaceDown);
}

static inline __attribute__((always_inline)) BOOL UIDeviceOrientationIsValidInterfaceOrientation(UIDeviceOrientation orientation)  API_UNAVAILABLE(tvos) {
    return ((orientation) == UIDeviceOrientationPortrait || (orientation) == UIDeviceOrientationPortraitUpsideDown || (orientation) == UIDeviceOrientationLandscapeLeft || (orientation) == UIDeviceOrientationLandscapeRight);
}

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) @interface UIDevice : NSObject

@property(class, nonatomic, readonly) UIDevice *currentDevice;

@property(nonatomic,readonly,strong) NSString    *name;              // e.g. "My iPhone"
@property(nonatomic,readonly,strong) NSString    *model;             // e.g. @"iPhone", @"iPod touch"
@property(nonatomic,readonly,strong) NSString    *localizedModel;    // localized version of model
@property(nonatomic,readonly,strong) NSString    *systemName;        // e.g. @"iOS"
@property(nonatomic,readonly,strong) NSString    *systemVersion;     // e.g. @"4.0"
@property(nonatomic,readonly) UIDeviceOrientation orientation API_UNAVAILABLE(tvos);       // return current device orientation.  this will return UIDeviceOrientationUnknown unless device orientation notifications are being generated.

@property(nullable, nonatomic,readonly,strong) NSUUID      *identifierForVendor API_AVAILABLE(ios(6.0));      // a UUID that may be used to uniquely identify the device, same across apps from a single vendor.

@property(nonatomic,readonly,getter=isGeneratingDeviceOrientationNotifications) BOOL generatesDeviceOrientationNotifications API_UNAVAILABLE(tvos);
- (void)beginGeneratingDeviceOrientationNotifications API_UNAVAILABLE(tvos);      // nestable
- (void)endGeneratingDeviceOrientationNotifications API_UNAVAILABLE(tvos);

@property(nonatomic,getter=isBatteryMonitoringEnabled) BOOL batteryMonitoringEnabled API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(tvos);  // default is NO
@property(nonatomic,readonly) UIDeviceBatteryState          batteryState API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(tvos);  // UIDeviceBatteryStateUnknown if monitoring disabled
@property(nonatomic,readonly) float                         batteryLevel API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(tvos);  // 0 .. 1.0. -1.0 if UIDeviceBatteryStateUnknown

@property(nonatomic,getter=isProximityMonitoringEnabled) BOOL proximityMonitoringEnabled API_AVAILABLE(ios(3.0)); // default is NO
@property(nonatomic,readonly)                            BOOL proximityState API_AVAILABLE(ios(3.0));  // always returns NO if no proximity detector

@property(nonatomic,readonly,getter=isMultitaskingSupported) BOOL multitaskingSupported API_AVAILABLE(ios(4.0));

@property(nonatomic,readonly) UIUserInterfaceIdiom userInterfaceIdiom API_AVAILABLE(ios(3.2));

- (void)playInputClick API_AVAILABLE(ios(4.2));  // Plays a click only if an enabling input view is on-screen and user has enabled input clicks.

@end

@protocol UIInputViewAudioFeedback <NSObject>
@optional

@property (nonatomic, readonly) BOOL enableInputClicksWhenVisible; // If YES, an input view will enable playInputClick.

@end

/* The UI_USER_INTERFACE_IDIOM() function is provided for use when deploying to a version of the iOS less than 3.2. If the earliest version of iPhone/iOS that you will be deploying for is 3.2 or greater, you may use -[UIDevice userInterfaceIdiom] directly.
 */
static inline UIUserInterfaceIdiom UI_USER_INTERFACE_IDIOM() API_DEPRECATED("Use -[UIDevice userInterfaceIdiom] directly.", ios(2.0, 13.0), tvos(9.0, 11.0)) {
    return ([[UIDevice currentDevice] respondsToSelector:@selector(userInterfaceIdiom)] ?
            [[UIDevice currentDevice] userInterfaceIdiom] :
            UIUserInterfaceIdiomPhone);
}

UIKIT_EXTERN NSNotificationName const UIDeviceOrientationDidChangeNotification API_UNAVAILABLE(tvos);
UIKIT_EXTERN NSNotificationName const UIDeviceBatteryStateDidChangeNotification   API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(tvos);
UIKIT_EXTERN NSNotificationName const UIDeviceBatteryLevelDidChangeNotification   API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(tvos);
UIKIT_EXTERN NSNotificationName const UIDeviceProximityStateDidChangeNotification API_AVAILABLE(ios(3.0));

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIDevice.h>
#endif
