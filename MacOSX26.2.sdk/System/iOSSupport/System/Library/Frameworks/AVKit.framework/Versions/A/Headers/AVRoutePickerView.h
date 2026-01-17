/*
	File:  AVRoutePickerView.h
	
	Framework:  AVKit
	
	Copyright © 2013-2023 Apple Inc. All rights reserved.
	
	To report bugs, go to:  http://developer.apple.com/bugreporter/

 */

#import <AVFoundation/AVFoundation.h>

#if TARGET_OS_OSX || TARGET_OS_MACCATALYST
#import <AVKit/AVKitDefines.h>
#else
#import <AVKit/AVKitDefines.h>
#endif // TARGET_OS_OSX || TARGET_OS_MACCATALYST

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif // TARGET_OS_IPHONE


#ifndef AVKitPlatformViewClass
#if TARGET_OS_IPHONE
#define AVKitPlatformViewClass UIView
#else
#define AVKitPlatformViewClass NSView
#endif // TARGET_OS_IPHONE
#endif // AVKitPlatformViewClass

#ifndef AVKitPlatformColorClass
#if TARGET_OS_IPHONE
#define AVKitPlatformColorClass UIColor
#else
#define AVKitPlatformColorClass NSColor
#endif // TARGET_OS_IPHONE
#endif // AVKitPlatformColorClass


NS_ASSUME_NONNULL_BEGIN

@protocol AVRoutePickerViewDelegate;

@class AVCustomRoutingController;
@class AVKitPlatformColorClass;


/**
 @constant		AVRoutePickerViewButtonStateNormal
				Normal or default state of the picker.
 @constant		AVRoutePickerViewButtonStateNormalHighlighted
				Highlighted state of the picker. The picker has this state when a mouse-down event occurs inside the button. It loses this highlight when a mouse-up event occurs.
 @constant		AVRoutePickerViewButtonStateActive
				Active state of the picker. The picker has this state when AirPlay is active.
 @constant		AVRoutePickerViewButtonStateActiveHighlighted
				Highlighted state of the active picker. The picker has this state when it is highlighted and AirPlay is active.
 */
typedef NS_ENUM(NSInteger, AVRoutePickerViewButtonState) {
	AVRoutePickerViewButtonStateNormal = 0,
	AVRoutePickerViewButtonStateNormalHighlighted = 1,
	AVRoutePickerViewButtonStateActive = 2,
	AVRoutePickerViewButtonStateActiveHighlighted = 3
} NS_SWIFT_NAME(AVRoutePickerView.ButtonState) API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos, watchos, visionos);



#if TARGET_IS_AVKITMACHELPER
#define AVRoutePickerView AVMacHelperRoutePickerView
#endif // TARGET_IS_AVKITMACHELPER

/**
 @class			AVRoutePickerView
 @abstract		AVRoutePickerView is a view subclass that displays controls for picking playback routes.
 @discussion	Media from an AVPlayer, or from an AVSampleBufferAudioRenderer on iOS and tvOS, can be routed to compatible AirPlay destinations.
 */
#if !TARGET_IS_AVKITMACHELPER
API_AVAILABLE(macos(10.15), ios(11.0), tvos(11.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
#endif // !TARGET_IS_AVKITMACHELPER
@interface AVRoutePickerView : AVKitPlatformViewClass

/**
 @property		delegate
 @abstract		The route picker view's delegate.
 */
@property (nonatomic, nullable, weak) id<AVRoutePickerViewDelegate> delegate;


/**
 @property 		player
 @abstract		The player for which to perform routing operations.
 */
@property (nonatomic, strong, nullable) AVPlayer *player API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/**
 @method		routePickerButtonColorForState:
 @param			state
				The state for which to get the picker button color.
 @abstract		Returns the color of the picker button for a given state.
 */
- (AVKitPlatformColorClass *)routePickerButtonColorForState:(AVRoutePickerViewButtonState)state API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/**
 @method		setRoutePickerButtonColor:forState:
 @param			color
				The color the button should have for a given state.
 @param			state
				The state for which to set the color of the button image.
 @abstract		Sets the color of the picker button for a given state.
 @discussion	If set to nil, the default color will be used for the given state.
 */
- (void)setRoutePickerButtonColor:(nullable AVKitPlatformColorClass *)color forState:(AVRoutePickerViewButtonState)state API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/**
 @property		routePickerButtonBordered
 @abstract		Whether or not the picker button has a border. Default is YES.
 */
@property (nonatomic, getter = isRoutePickerButtonBordered) BOOL routePickerButtonBordered API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/**
 @property		activeTintColor
 @abstract		The view's tint color when AirPlay is active.
 */
@property (nonatomic, strong, null_resettable) AVKitPlatformColorClass *activeTintColor API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(macos, watchos);

/**
 @constant		AVRoutePickerViewButtonStyleSystem
				A system style for the route picker button.
 @constant		AVRoutePickerViewButtonStylePlain
				A plain style for the route picker button, which has the same appearance as the system style without the blurred background view.
 @constant		AVRoutePickerViewButtonStyleCustom
				A custom style for the route picker button, which allows customizing the background view and focused appearance.
 */
typedef NS_ENUM(NSInteger, AVRoutePickerViewButtonStyle) {
	AVRoutePickerViewButtonStyleSystem,
	AVRoutePickerViewButtonStylePlain,
	AVRoutePickerViewButtonStyleCustom
} API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(macos, ios, watchos, visionos);

/**
 @property		routePickerButtonStyle
 @abstract		The route picker button style.
 */
@property (nonatomic) AVRoutePickerViewButtonStyle routePickerButtonStyle API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(macos, ios, watchos, visionos);

/**
 @property		prioritizesVideoDevices
 @abstract		Whether or not the route picker should sort video capable output devices to the top of the list. Setting this to YES will cause the route picker view to show a videocentric icon.
 */
@property (nonatomic) BOOL prioritizesVideoDevices API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/**
 @property		customRoutingController
 @abstract		A controller which enables connection to 3rd party devices (non-airplay) via the picker.
 */
@property (nonatomic, retain, nullable) AVCustomRoutingController *customRoutingController API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, tvos, watchos, visionos);

@end


/**
 @protocol		AVRoutePickerViewDelegate
 @abstract		Defines an interface for delegates of AVRoutePickerView.
 */
API_AVAILABLE(macos(10.15), ios(11.0), tvos(11.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@protocol AVRoutePickerViewDelegate <NSObject>
@optional

/**
 @method		routePickerViewWillBeginPresentingRoutes:
 @abstract		Informs the delegate that the route picker view will start presenting routes to the user.
 */
- (void)routePickerViewWillBeginPresentingRoutes:(AVRoutePickerView *)routePickerView;

/**
 @method		routePickerViewDidEndPresentingRoutes:
 @abstract		Informs the delegate that the route picker view finished presenting routes to the user.
 */
- (void)routePickerViewDidEndPresentingRoutes:(AVRoutePickerView *)routePickerView;

@end

NS_ASSUME_NONNULL_END
