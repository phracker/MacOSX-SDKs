/*
	File:  AVRoutePickerView.h
 
	Framework:  AVKit
 
	Copyright © 2017 Apple Inc. All rights reserved.
 
 */

#import <UIKit/UIKit.h>

@protocol AVRoutePickerViewDelegate;

NS_ASSUME_NONNULL_BEGIN

/*!
	@class		AVRoutePickerView
	@abstract	AVRoutePickerView is a subclass of UIView that displays controls for picking playback routes.
	@discussion	Media from AVPlayer or AVSampleBufferAudioRenderer can be routed to compatible AirPlay destinations.
 */

API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(macos, watchos)
@interface AVRoutePickerView : UIView

/*!
	@property	delegate
	@abstract	The route picker view's delegate.
 */
@property (nonatomic, weak, nullable) id<AVRoutePickerViewDelegate> delegate;

/*!
	@property	activeTintColor
	@abstract	The view's tint color when AirPlay is active.
 */
@property (nonatomic, strong, null_resettable) UIColor *activeTintColor;

/*!
	@constant	AVRoutePickerViewButtonStyleSystem
				A system style for the route picker button.
	@constant	AVRoutePickerViewButtonStylePlain
				A plain style for the route picker button, which has the same appearance as the system style without the blurred background view.
	@constant	AVRoutePickerViewButtonStyleCustom
				A custom style for the route picker button, which allows customizing the background view and focused appearance.
 */
typedef NS_ENUM(NSInteger, AVRoutePickerViewButtonStyle) {
	AVRoutePickerViewButtonStyleSystem,
	AVRoutePickerViewButtonStylePlain,
	AVRoutePickerViewButtonStyleCustom
} API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios);

/*!
	@property	routePickerButtonStyle
	@abstract	The route picker button style.
 */
@property (nonatomic) AVRoutePickerViewButtonStyle routePickerButtonStyle API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios);

/*!
 	@property	prioritizesVideoDevices
 	@abstract	Whether or not the route picker should sort video capable output devices to the top of the list. Setting this to YES will cause the route picker view to show a videocentric icon.
 */
@property (nonatomic) BOOL prioritizesVideoDevices API_AVAILABLE(ios(13.0), tvos(13.0));

@end


/*!
	@protocol	AVRoutePickerViewDelegate
	@abstract	Defines an interface for delegates of AVRoutePickerView.
 */

@protocol AVRoutePickerViewDelegate <NSObject>
@optional

/*!
	@method		routePickerViewWillBeginPresentingRoutes:
	@abstract	Informs the delegate that the route picker view will start presenting routes to the user.
 */
- (void)routePickerViewWillBeginPresentingRoutes:(AVRoutePickerView *)routePickerView;

/*!
	@method		routePickerViewDidEndPresentingRoutes:
	@abstract	Informs the delegate that the route picker view finished presenting routes to the user.
 */
- (void)routePickerViewDidEndPresentingRoutes:(AVRoutePickerView *)routePickerView;

@end

NS_ASSUME_NONNULL_END
