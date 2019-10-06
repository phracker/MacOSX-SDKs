//
//  AUViewController.h
//	Framework: CoreAudioKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//
#if __OBJC2__

#import <AudioUnit/AudioUnit.h>
#import <Foundation/NSExtensionRequestHandling.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
typedef UIViewController AUViewControllerBase;
#else
#import <AppKit/AppKit.h>
typedef NSViewController AUViewControllerBase;
#endif

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos)
@interface AUViewController : AUViewControllerBase <NSExtensionRequestHandling>
@end

/*!	@class	AUAudioUnitViewConfiguration
	@brief	Properties of the configuration that a host uses to embed the view of an audio unit.
	@discussion
		Hosts may support embedding the view of an audio unit in different configurations. These
		configurations may vary in the size reserved for the audio unit's view and the additional 
		control surfaces that are displayed along with it. The host can propose several view 
		configurations and the audio unit should report the ones which it supports.

		See the documentation for supportedViewConfigurations.
*/
API_AVAILABLE(macos(10.13), ios(11.0)) API_UNAVAILABLE(watchos)
@interface AUAudioUnitViewConfiguration : NSObject <NSSecureCoding>

/*!	@method		initWithWidth
	@brief		Designated initializer.
	@param		width
		The width associated with this view configuration.
	@param		height
		The height associated with this view configuration.
	@param		hostHasController
		This property controls whether the host shows its own control surface in this view 
		configuration.
	@return		Returns the newly created view configuration object.
*/
- (instancetype)initWithWidth:(CGFloat)width height:(CGFloat)height hostHasController:(BOOL)hostHasController;

/*!	@property	width
	@brief		The width of the view, measured in points.
	@discussion
		Setting the width to 0 will match any width.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) CGFloat width;

/*!	@property	height
	@brief		The height of the view, measured in points.
	@discussion
		Setting the height to 0 will match any height.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) CGFloat height;

/*!	@property	hostHasController
	@brief		Boolean property specifying whether the host displays its own control surface
				when showing the view of the audio unit.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL hostHasController;

@end

API_AVAILABLE(macos(10.12), ios(10.0)) API_UNAVAILABLE(watchos)
@interface AUAudioUnit (AUAudioUnit_ViewController)
/*!	@method	requestViewControllerWithCompletionHandler:
	@brief	Obtains an audio unit's view controller (and thereby a view).
	@discussion
		Asynchronously requests the audio unit's view controller. This method will later call the
		completion handler, in a thread/dispatch queue context internal to the implementation, with
		a view controller, or nil in the case of an audio unit without a custom view controller.
*/
- (void)requestViewControllerWithCompletionHandler:(void (^)(AUViewControllerBase * __nullable viewController))completionHandler;

/*!	@method		supportedViewConfigurations
	@param		availableViewConfigurations
		The list of all available view configurations supported by the host.
	@return
		A set of indices of view configurations from the availableViewConfigurations array that the
		audio unit supports.
	@brief      Query the list of supported view configurations.
	@discussion
		The host can query the audio unit for all the view configurations it supports.
		Hosts can support multiple configurations in which they can display the user interfaces of
		audio units (for example: full screen, normal, live mode, etc). These configurations can be
		of different sizes and the host might display its own control surfaces along with the view
		of the audio unit. The host will call this method and pass an array of supported
		configurations.

		The audio unit should override this method and implement its own logic to report all the 
		view configurations it supports. The size of the view in the selected configuration should 
		be large enough to fit the view of the audio unit, otherwise it might be truncated and a 
		scroll bar might be necessary to navigate it.

		In case an empty set is returned from this method, it is considered that the plugin only 
		supports the largest available view configuration.
*/
- (NSIndexSet *)supportedViewConfigurations:(NSArray<AUAudioUnitViewConfiguration *> *)availableViewConfigurations API_AVAILABLE(macosx(10.13), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!	@method		selectViewConfiguration
	@param		viewConfiguration
        The requested view configuration.

        The view configuration passed to this method should be one which was indicated as supported 
        via supportedViewConfigurations. If any other, unsupported, view configuration is passed or 
        if supportedViewConfigurations returns an empty set, the audio unit implementation should 
        fall back to its default (largest available) view configuration.

	@brief		Request a view configuration from the audio unit.
	@discussion
		The host can use this method to switch the audio unit's view into a new configuration.
		Audio Units should override this method with the logic needed to adapt their view controller 
		to the requested configuration.
*/
- (void)selectViewConfiguration:(AUAudioUnitViewConfiguration *)viewConfiguration API_AVAILABLE(macosx(10.13), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

#endif

