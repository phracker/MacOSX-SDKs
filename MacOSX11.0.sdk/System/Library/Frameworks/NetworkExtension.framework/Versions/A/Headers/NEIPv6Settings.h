/*
 * Copyright (c) 2013-2015, 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEIPv6Settings
 * @discussion This file declares the NEIPv6Settings API. The NEIPv6Settings API is used to specify the IPv6 settings for VPN tunnels.
 *
 * This API is part of NetworkExtension.framework
 */

@class NEIPv6Route;

/*!
 * @interface NEIPv6Settings
 * @discussion The NEIPv6Settings class declares the programmatic interface for an object that contains IPv6 settings.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface NEIPv6Settings : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithAddresses:networkPrefixLengths:
 * @discussion Initialize a newly-allocated NEIPv6Settings object.
 * @param addresses An array of IPv6 addresses represented as dotted decimal strings.
 * @param networkPrefixLengths An array of NSNumber objects each containing the length in bits of the network prefix of the corresponding address in the addresses parameter.
 * @return The initialized object.
 */
- (instancetype)initWithAddresses:(NSArray<NSString *> *)addresses networkPrefixLengths:(NSArray<NSNumber *> *)networkPrefixLengths API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property addresses
 * @discussion An array of IPv6 addresses represented strings. These addresses will be set on the virtual interface used by the VPN tunnel.
 */
@property (readonly) NSArray<NSString *> *addresses API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property networkPrefixLengths
 * @discussion An array of NSNumber objects each representing the length in bits of the network prefix of the corresponding address in the addresses property.
 */
@property (readonly) NSArray<NSNumber *> *networkPrefixLengths API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property includedRoutes
 * @discussion An array of NEIPv6Route objects. Traffic matching these routes will be routed through the virtual interface used by the VPN tunnel.
 */
@property (copy, nullable) NSArray<NEIPv6Route *> *includedRoutes API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property excludedRoutes
 * @discussion An array of NEIPv6Route objects. Traffic matching these routes will be routed through the current primary physical interface of the device.
 */
@property (copy, nullable) NSArray<NEIPv6Route *> *excludedRoutes API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

@end

/*!
 * @interface NEIPv6Route
 * @discussion The NEIPv6Route class declares the programmatic interface for an object that contains settings for an IPv6 route.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(9.0))
@interface NEIPv6Route : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithDestinationAddress:networkPrefixLength:
 * @discussion Initialize a newly-allocated NEIPv6Route.
 * @param address The IPv6 address of the destination network.
 * @param networkPrefixLength A number containing the length in bits of the network prefix of the destination network.
 * @return The initialized NEIPv6Route.
 */
- (instancetype)initWithDestinationAddress:(NSString *)address networkPrefixLength:(NSNumber *)networkPrefixLength API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property destinationAddress
 * @discussion An IPv6 address represented as a string.
 */
@property (readonly) NSString *destinationAddress API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property destinationNetworkPrefixLength
 * @discussion A number containing the length in bits of the network prefix of the destination network. This prefix in combination with the destinationAddress property is used to determine the destination network of the route.
 */
@property (readonly) NSNumber *destinationNetworkPrefixLength API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property gatewayAddress
 * @discussion The IPv6 address of the route's gateway. If this property is nil then the route's gateway will be set to the tunnel's virtual interface.
 */
@property (copy, nullable) NSString *gatewayAddress API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method defaultRoute
 * @return A route object that represents the IPv6 default route.
 */
+ (NEIPv6Route * const)defaultRoute API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;
@end

NS_ASSUME_NONNULL_END

