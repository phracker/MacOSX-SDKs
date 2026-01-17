/*
    File:  AVCustomRoutingController.h
    
    Framework:  AVRouting
    
    Copyright © 2022 Apple Inc. All rights reserved.
    
 */

#import <Foundation/Foundation.h>

#import <AVRouting/AVRoutingDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class AVCustomDeviceRoute;
@class AVCustomRoutingEvent;
@class AVCustomRoutingActionItem;
@class AVCustomRoutingPartialIP;
@protocol AVCustomRoutingControllerDelegate;

/*!
	@constant	AVCustomRoutingControllerAuthorizedRoutesDidChangeNotification
	@abstract	Posted when the value of authorizedRoutes changes.
 */

/// A notification the system posts when the list of authorized routes changes.
AVROUTING_EXTERN NSNotificationName const AVCustomRoutingControllerAuthorizedRoutesDidChangeNotification NS_SWIFT_NAME(AVCustomRoutingController.authorizedRoutesDidChange) API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

/*!
	@class		AVCustomRoutingController
	@abstract	When a user selects / deselects a 3rd party device in the route picker, this class delegates the activation / deactivation of that device to the client of this class via AVCustomRoutingEvents.
	@discussion	This class also informs the client which routes have been previously authorized, allowing them to reconnect if appropriate.
 */

/// An object that manages the connection from a device to a destination.
///
/// A routing controller also informs its ``AVCustomRoutingController/delegate``
/// object about which routes the user previously authorized, so it can
/// reconnect, if appropriate.
API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos)
@interface AVCustomRoutingController : NSObject

/*!
	@property 	delegate
	@abstract	The receiver's delegate.
 */

/// A delegate object for a routing controller.
@property (nonatomic, weak, nullable) id<AVCustomRoutingControllerDelegate> delegate API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

/*!
	@property 	authorizedRoutes
	@abstract	The list of authorized routes. Once a route has been activated, it remains authorized for a certain amount of time even if the connection to the route temporarily goes down.
				The app may reactivate any one of these routes if they deem it appropriate, but must inform the system by calling -setActive:forRoute:.
 */

/// A list of authorized routes.
///
/// After a user activates a route, it remains authorized for a certain amount
/// of time even if the connection to the route is temporarily unavailable. Your
/// app may reactivate any one of these routes when appropriate, but it needs to
/// inform the system by calling
/// ``AVCustomRoutingController/setActive:forRoute:``.
@property (nonatomic, readonly) NSArray<AVCustomDeviceRoute *> *authorizedRoutes API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

/**
 An array of route addresses known to be on the local network.
 */
@property (nonatomic, strong) NSArray<AVCustomRoutingPartialIP *> *knownRouteIPs API_AVAILABLE(ios(16.1)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

/*!
    @property   customActionItems
    @abstract   An array of custom action items to be added in the picker.
 */

/// An array of custom action items to add to a route picker.
@property (nonatomic, strong) NSArray<AVCustomRoutingActionItem *> *customActionItems API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

/*!
	@method     invalidateAuthorization
	@param		route
				The route for which to invalidate authorization.
	@abstract	Calling this method revokes the app's authorization to connect to a route. The route will only become authorized again if the user selects it via the route picker.
 */

/// Revokes an app’s authorization to connect to a route.
///
/// The route only becomes authorized again if the user selects it using the
/// route picker.
///
/// - Parameters:
///   - route: The route to invalidate authorization for.
- (void)invalidateAuthorizationForRoute:(AVCustomDeviceRoute *)route;

/*!
    @method     setActive:forRoute:
    @param      active
                Whether or not the route is active.
    @param      route
                The route to set as active or inactive.
    @abstract   Set this to NO if the connection to the route temporarily drops, and set it to YES once the connection is reestablished.
 */

/// Sets the active state of a route.
///
/// Set the value to <doc://com.apple.documentation/documentation/objectivec/no>
/// if the connection to the route becomes unavailable, and set it to
/// <doc://com.apple.documentation/documentation/objectivec/yes> after you
/// reestablish the connection.
///
/// - Parameters:
///   - active: A Boolean value that indicates whether the route is active.
///
///   - route: A route to change the active state for.
- (void)setActive:(BOOL)active forRoute:(AVCustomDeviceRoute *)route;

/*!
    @method     isRouteActive:
    @param      route
                The route for which to check active status.
    @abstract   Returns whether or not the given route is active.
 */

/// Returns a Boolean value that indicates whether a route is active.
///
/// - Parameters:
///   - route: A route for determining its active state.
///
/// - Returns: <doc://com.apple.documentation/documentation/objectivec/yes> if
/// the route is in an active state; otherwise,
/// <doc://com.apple.documentation/documentation/objectivec/no>.
- (BOOL )isRouteActive:(AVCustomDeviceRoute *)route;

@end


/*!
	@protocol	AVCustomRoutingControllerDelegate
	@abstract	A protocol for delegates of AVCustomRoutingController.
 */
API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos)

/// A protocol for delegates of a custom routing controller.
NS_SWIFT_SENDABLE @protocol AVCustomRoutingControllerDelegate <NSObject>

/*!
	@method		customRoutingController:handleEvent:completionHandler:
	@param		controller
				The custom routing controller.
	@param		event
				The route event for the delegate to process.
	@param		completionHandler
				The completion handler the delegate needs to call after the event has been processed. Pass YES to the completion handler if the activation, reactivation or deactivation of the route was successful, and NO otherwise.
	@abstract	The delegate needs to implement this method in order to both establish and tear down connection to a device when a user requests it through the picker.
 */

/// Connects to, or disconnects from, a device when a user requests it in the
/// picker.
///
/// - Parameters:
///   - controller: A custom routing controller.
///
///   - event: The routing event to handle.
///
///   - completionHandler: A completion handler to call after processing the
/// event. Pass <doc://com.apple.documentation/documentation/objectivec/yes> to
/// the completion handler if the activation, reactivation, or deactivation of
/// the route succeeds, and
/// <doc://com.apple.documentation/documentation/objectivec/no>, otherwise.
- (void)customRoutingController:(AVCustomRoutingController *)controller handleEvent:(AVCustomRoutingEvent *)event completionHandler:(void (^)(BOOL success))completionHandler;


@optional

/*!
	@method		customRoutingController:eventDidTimeOut:
	@param		controller
                The custom routing controller.
	@param		event
				The route event that timed out.
	@abstract	The delegate can implement this method in order know when a route event timed out. This gives them a chance to clean up any connection attempts that are currently in flight.
 */

/// Tells the delegate when a routing event times out.
///
/// Adopt this method to clean up any in-progress connection attempts.
///
/// - Parameters:
///   - controller: A custom routing controller.
///
///   - event: An event that times out.
- (void)customRoutingController:(AVCustomRoutingController *)controller eventDidTimeOut:(AVCustomRoutingEvent *)event;

/*!
    @method     customRoutingController:didSelectItem:
    @abstract   Informs the delegate that the user selected a custom item in the route picker.
 */

/// Tells the delegate when a user selects a custom item in the route picker.
///
/// - Parameters:
///   - controller: A custom routing controller.
///
///   - customActionItem: The selected action item.
- (void)customRoutingController:(AVCustomRoutingController *)controller didSelectItem:(AVCustomRoutingActionItem *)customActionItem;

@end


/*!
    @class      AVCustomRoutingPartialIP
    @abstract   Represents a full or partial IP address. To be used in conjunction with AVCustomRoutingController.knownRouteIPs
 */
API_AVAILABLE(ios(16.1)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos)
/// Represents a full or partial IP address.
///
/// Use this class in conjunction with ``knownRouteIPs``.
NS_SWIFT_SENDABLE @interface AVCustomRoutingPartialIP : NSObject

/// A full or partial IP address for a device known to be on the network.
///
/// Use the following code to create a full known IP address.
///
/// ```var anIPAddressInBytes:[Byte] = [192, 168, 10, 5]
///var address = Data(bytes: anAddressInBytes, length: anAddressInBytes.count)
///var aMaskInBytes:[Byte] = [255, 255, 255, 255]
///var mask = Data(bytes: aMaskInBytes, length: aMaskInBytes.count)
///var partialIP = AVCustomRoutingPartialIP(address: address, mask: mask)
///```

@property (readonly, copy, nonatomic) NSData *address API_AVAILABLE(ios(16.1)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

/** A mask representing how many octets of the IP  address to respect.
 
 Use this mask to pass the last two bytes of the IP address instead of passing all four bytes.
 
 ```var anIPAddressInBytes:[Byte] = [0, 0, 10, 5]
 var address = Data(bytes: anAddressInBytes, length: anAddressInBytes.count)
 var aMaskInBytes:[Byte] = [0, 0, 255, 255]
 var mask = Data(bytes: aMaskInBytes, length: aMaskInBytes.count)
 var partialIP =AVCustomRoutingPartialIP(address: address, mask: mask)
 ```
*/
@property (readonly, copy, nonatomic) NSData *mask API_AVAILABLE(ios(16.1)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

/**
 Creates an IP fragment.
  - Parameters:
    - address: The IP address.
    - mask: The address mask.
 */
- (instancetype)initWithAddress:(NSData *)address mask:(NSData *)mask API_AVAILABLE(ios(16.1)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
