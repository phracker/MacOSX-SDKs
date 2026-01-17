//
//  NWHostEndpoint.h
//  Network
//
//  Copyright (c) 2014-2016 Apple Inc. All rights reserved.
//

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif // __NE_INDIRECT__

#ifndef __NWHostEndpoint_h_
#define __NWHostEndpoint_h_


NS_ASSUME_NONNULL_BEGIN

/*!
 * @interface NWHostEndpoint
 * @discussion NWHostEndpoint is a subclass of NWEndpoint. It represents an endpoint backed by a
 *		hostname and port. Note that a hostname string may be an IP or IPv6 address.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NWHostEndpoint : NWEndpoint

/*!
 * @method endpointWithHostname:port:
 * @param hostname A string representation of the hostname or address, such as www.apple.com or 10.0.0.1.
 * @param port A string containing the port on the host, such as 80.
 * @return An initialized NWHostEndpoint object.
 */
+ (instancetype)endpointWithHostname:(NSString *)hostname
								port:(NSString *)port NS_AVAILABLE(10_11, 9_0);

/*!
 * @property hostname
 * @discussion The endpoint's hostname.
 */
@property (readonly) NSString *hostname NS_AVAILABLE(10_11, 9_0);

/*!
 * @property port
 * @discussion The endpoint's port.
 */
@property (readonly) NSString *port NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

#endif // __NWHostEndpoint_h_
