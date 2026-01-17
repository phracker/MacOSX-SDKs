/*
    File:  AVCustomDeviceRoute.h
    
    Framework:  AVRouting
    
    Copyright © 2022 Apple Inc. All rights reserved.
    
 */

#import <Foundation/Foundation.h>
#import <Network/Network.h>

NS_ASSUME_NONNULL_BEGIN

/*!
	@class		AVCustomDeviceRoute
	@abstract	This class represents a custom device route.
	@discussion	Clients can use the receiver's networkEndpoint or bluetoothIdentifier to establish a connection to the device.
                Usually, either the network endpoint or the Bluetooth identifier will be nil, depending on what type of device it is.
                In certain scenarios both can be non-nil, in which case the client can decide which one to use.
 */

/// An object that represents a custom device route.
///
/// Use the value of a route’s ``AVCustomDeviceRoute/networkEndpoint`` or
/// ``AVCustomDeviceRoute/bluetoothIdentifier`` property to establish a
/// connection to a device. Typically, only one of the properties provides a
/// valid value, depending on the type of device. In certain cases, both
/// properties might provide valid values, in which case your app determines which
/// one to use.
API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos)
NS_SWIFT_SENDABLE @interface AVCustomDeviceRoute : NSObject

/*!
	@property 	networkEndpoint
	@abstract	An `nw_endpoint_t` to which clients can establish a connection.
	@discussion Use Network.opaque() to convert an `nw_endpoint_t` to an NWEndpoint in Swift.
 */

/// A local or remote endpoint to connect to.
@property (nonatomic, nullable, readonly) nw_endpoint_t networkEndpoint API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

/*!
	@property 	bluetoothIdentifier
	@abstract	A bluetooth identifier which clients can use to establish a connection to a bluetooth device.
 */

/// An identifier to use to establish a connection to a Bluetooth device.
@property (nonatomic, nullable, readonly) NSUUID *bluetoothIdentifier API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

@end

NS_ASSUME_NONNULL_END
