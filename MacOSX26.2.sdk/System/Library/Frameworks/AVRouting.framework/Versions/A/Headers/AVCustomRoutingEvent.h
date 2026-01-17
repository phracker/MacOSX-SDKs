/*
    File:  AVCustomRoutingEvent.h
    
    Framework:  AVRouting
    
    Copyright © 2022 Apple Inc. All rights reserved.
    
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AVCustomDeviceRoute;

/// Values that indicate the reason for a routing event.
typedef NS_ENUM(NSInteger, AVCustomRoutingEventReason) {


/// A value that indicates that a user selects a route in the picker.
	AVCustomRoutingEventReasonActivate = 0,

/// A value that indicates that a user deselects a route in the picker.
	AVCustomRoutingEventReasonDeactivate,

/// A value that indicates to reactivate a route a user authorized previously.
	AVCustomRoutingEventReasonReactivate,
};

/*!
	@class		AVCustomRoutingEvent
	@abstract	This class represents an event that occurs on a route.
	@discussion	Depending on the reason for the event, clients are expected to establish or tear down the connection to the given route.
 */

/// An object that represents an event that occurs on a route.
///
/// Depending on the route’s reason, apps establish or tear down a connection to
/// a specified route.
API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos)
NS_SWIFT_SENDABLE @interface AVCustomRoutingEvent : NSObject

/*!
	@property 	reason
	@abstract	The reason for the event.
 */

/// A reason for an event, such as a user request to activate or deactivate a
/// route.
@property (nonatomic, readonly) AVCustomRoutingEventReason reason API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

/*!
	@property 	route
	@abstract	The route associated with the event.
 */

/// A route for the event.
@property (nonatomic, readonly) AVCustomDeviceRoute *route API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

@end

NS_ASSUME_NONNULL_END
