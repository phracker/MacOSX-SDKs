//
//  NWHostEndpoint.h
//  Network
//
//  Copyright (c) 2014-2016, 2018 Apple Inc. All rights reserved.
//

#ifndef __NE_TAPI__

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif // __NE_INDIRECT__

#ifndef __NWHostEndpoint_h_
#define __NWHostEndpoint_h_

/**
 * DEPRECATION NOTICE
 *
 * NW object wrappers are hidden in Swift 6. To continue accessing them, you
 * can prepend double underscores to the symbol name.
 */

NS_ASSUME_NONNULL_BEGIN

/*!
 * @interface NWHostEndpoint
 * @discussion NWHostEndpoint is a subclass of NWEndpoint. It represents an endpoint backed by a
 *		hostname and port. Note that a hostname string may be an IP or IPv6 address.
 */
API_DEPRECATED("Use `nw_endpoint_t` in Network framework instead, see deprecation notice in <NetworkExtension/NWHostEndpoint.h>", macos(10.11, 15.0), ios(9.0, 18.0), tvos(17.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos)
@interface NWHostEndpoint : NWEndpoint

/*!
 * @method endpointWithHostname:port:
 * @param hostname A string representation of the hostname or address, such as www.apple.com or 10.0.0.1.
 * @param port A string containing the port on the host, such as 80.
 * @return An initialized NWHostEndpoint object.
 */
+ (instancetype)endpointWithHostname:(NSString *)hostname
								port:(NSString *)port
API_DEPRECATED("Use `nw_endpoint_create_host` in Network framework instead, see deprecation notice in <NetworkExtension/NWHostEndpoint.h>", macos(10.11, 15.0), ios(9.0, 18.0), tvos(17.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos);

/*!
 * @property hostname
 * @discussion The endpoint's hostname.
 */
@property (nonatomic, readonly) NSString *hostname
API_DEPRECATED("Use `nw_endpoint_get_hostname` in Network framework instead, see deprecation notice in <NetworkExtension/NWHostEndpoint.h>", macos(10.11, 15.0), ios(9.0, 18.0), tvos(17.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos);

/*!
 * @property port
 * @discussion The endpoint's port.
 */
@property (nonatomic, readonly) NSString *port
API_DEPRECATED("Use `nw_endpoint_get_port` in Network framework instead, see deprecation notice in <NetworkExtension/NWHostEndpoint.h>", macos(10.11, 15.0), ios(9.0, 18.0), tvos(17.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

#endif // __NWHostEndpoint_h_

#endif // __NE_TAPI__
