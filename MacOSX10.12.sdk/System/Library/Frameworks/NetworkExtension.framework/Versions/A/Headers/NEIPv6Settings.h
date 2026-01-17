/*
 * Copyright (c) 2013-2015 Apple Inc.
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
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEIPv6Settings : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithAddresses:networkPrefixLengths:
 * @discussion Initialize a newly-allocated NEIPv6Settings object.
 * @param addresses An array of IPv6 addresses represented as dotted decimal strings.
 * @param networkPrefixLengths An array of NSNumber objects each containing the length in bits of the network prefix of the corresponding address in the addresses parameter.
 * @return The initialized object.
 */
- (instancetype)initWithAddresses:(NSArray<NSString *> *)addresses networkPrefixLengths:(NSArray<NSNumber *> *)networkPrefixLengths NS_AVAILABLE(10_11, 9_0);

/*!
 * @property addresses
 * @discussion An array of IPv6 addresses represented strings. These addresses will be set on the virtual interface used by the VPN tunnel.
 */
@property (readonly) NSArray<NSString *> *addresses NS_AVAILABLE(10_11, 9_0);

/*!
 * @property networkPrefixLengths
 * @discussion An array of NSNumber objects each representing the length in bits of the network prefix of the corresponding address in the addresses property.
 */
@property (readonly) NSArray<NSNumber *> *networkPrefixLengths NS_AVAILABLE(10_11, 9_0);

/*!
 * @property includedRoutes
 * @discussion An array of NEIPv6Route objects. Traffic matching these routes will be routed through the virtual interface used by the VPN tunnel.
 */
@property (copy, nullable) NSArray<NEIPv6Route *> *includedRoutes NS_AVAILABLE(10_11, 9_0);

/*!
 * @property excludedRoutes
 * @discussion An array of NEIPv6Route objects. Traffic matching these routes will be routed through the current primary physical interface of the device.
 */
@property (copy, nullable) NSArray<NEIPv6Route *> *excludedRoutes NS_AVAILABLE(10_11, 9_0);

@end

/*!
 * @interface NEIPv6Route
 * @discussion The NEIPv6Route class declares the programmatic interface for an object that contains settings for an IPv6 route.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEIPv6Route : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithDestinationAddress:networkPrefixLength:
 * @discussion Initialize a newly-allocated NEIPv6Route.
 * @param address The IPv6 address of the destination network.
 * @param networkPrefixLength A number containing the length in bits of the network prefix of the destination network.
 * @return The initialized NEIPv6Route.
 */
- (instancetype)initWithDestinationAddress:(NSString *)address networkPrefixLength:(NSNumber *)networkPrefixLength NS_AVAILABLE(10_11, 9_0);

/*!
 * @property destinationAddress
 * @discussion An IPv6 address represented as a string.
 */
@property (readonly) NSString *destinationAddress NS_AVAILABLE(10_11, 9_0);

/*!
 * @property destinationNetworkPrefixLength
 * @discussion A number containing the length in bits of the network prefix of the destination network. This prefix in combination with the destinationAddress property is used to determine the destination network of the route.
 */
@property (readonly) NSNumber *destinationNetworkPrefixLength NS_AVAILABLE(10_11, 9_0);

/*!
 * @property gatewayAddress
 * @discussion The IPv6 address of the route's gateway. If this property is nil then the route's gateway will be set to the tunnel's virtual interface.
 */
@property (copy, nullable) NSString *gatewayAddress NS_AVAILABLE(10_11, 9_0);

/*!
 * @method defaultRoute
 * @return A route object that represents the IPv6 default route.
 */
+ (NEIPv6Route * const)defaultRoute NS_AVAILABLE(10_11, 9_0);
@end

NS_ASSUME_NONNULL_END

