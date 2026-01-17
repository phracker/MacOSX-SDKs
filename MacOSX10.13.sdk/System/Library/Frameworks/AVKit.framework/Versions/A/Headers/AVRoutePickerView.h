/*
	File:  AVRoutePickerView.h
	
	Framework:  AVKit
	
	Copyright © 2017 Apple Inc. All rights reserved.
	
 */

#import <Cocoa/Cocoa.h>

@protocol AVRoutePickerViewDelegate;

NS_ASSUME_NONNULL_BEGIN

/*!
	@class		AVRoutePickerView
	@abstract	AVRoutePickerView is a subclass of NSView that displays controls for picking playback routes.
 */

API_AVAILABLE(macosx(10.13))
@interface AVRoutePickerView : NSView

/*!
	@property	delegate
	@abstract	The route picker view's delegate.
 */
@property (nullable, weak) id<AVRoutePickerViewDelegate> delegate;

/*!
	@constant	AVRoutePickerViewButtonStateNormal
				Normal or default state of the picker.
	@constant	AVRoutePickerViewButtonStateNormalHighlighted
				Highlighted state of the picker. The picker has this state when a mouse-down event occurs inside the button. It loses this highlight when a mouse-up event occurs.
	@constant	AVRoutePickerViewButtonStateActive
				Active state of the picker. The picker has this state when AirPlay is active.
	@constant	AVRoutePickerViewButtonStateActiveHighlighted
				Highlighted state of the active picker. The picker has this state when it is highlighted and AirPlay is active.
 */
typedef NS_ENUM(NSInteger, AVRoutePickerViewButtonState) {
	AVRoutePickerViewButtonStateNormal,
	AVRoutePickerViewButtonStateNormalHighlighted,
	AVRoutePickerViewButtonStateActive,
	AVRoutePickerViewButtonStateActiveHighlighted
} API_AVAILABLE(macosx(10.13));

/*!
	@method		routePickerButtonColorForState:
	@param		state
				The state for which to get the picker button color.
	@abstract	Returns the color of the picker button for a given state.
 */
- (NSColor *)routePickerButtonColorForState:(AVRoutePickerViewButtonState)state;

/*!
	@method		setRoutePickerButtonColor:forState:
	@param		color
				The color the button should have for a given state.
	@param		state
				The state for which to set the color of the button image.
	@abstract	Sets the color of the picker button for a given state.
	@discussion	If set to nil, the default color will be used for the given state.
 */
- (void)setRoutePickerButtonColor:(nullable NSColor *)color forState:(AVRoutePickerViewButtonState)state;

/*!
	@property	routePickerButtonBordered
	@abstract	Whether or not the picker button has a border. Default is YES.
 */
@property (getter = isRoutePickerButtonBordered) BOOL routePickerButtonBordered;

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
