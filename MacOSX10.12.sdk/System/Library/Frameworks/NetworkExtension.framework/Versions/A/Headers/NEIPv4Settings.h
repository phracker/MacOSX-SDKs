/*
 * Copyright (c) 2013-2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEIPv4Settings.h
 * @discussion This file declares the NEIPv4Settings API. The NEIPv4Settings API is used to specify IPv4 settings for VPN tunnels.
 *
 * This API is part of NetworkExtension.framework
 */

@class NEIPv4Route;

/*!
 * @interface NEIPv4Settings
 * @discussion The NEIPv4Settings class declares the programmatic interface for an object that contains IPv4 settings.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEIPv4Settings : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithAddresses:subnetMasks:
 * @discussion Initialize a newly-allocated NEIPv4Settings object.
 * @param addresses An array of IPv4 addresses represented as dotted decimal strings.
 * @param subnetMasks An array of IPv4 subnet masks represented as dotted decimal strings.
 * @return The initialized object.
 */
- (instancetype)initWithAddresses:(NSArray<NSString *> *)addresses subnetMasks:(NSArray<NSString *> *)subnetMasks NS_AVAILABLE(10_11, 9_0);

/*!
 * @property addresses
 * @discussion An array of IPv4 addresses represented as dotted decimal strings. These addresses will be set on the virtual interface used by the VPN tunnel.
 */
@property (readonly) NSArray<NSString *> *addresses NS_AVAILABLE(10_11, 9_0);

/*!
 * @property subnetMasks
 * @discussion An array of IPv4 subnet masks represented as dotted decimal strings. These subnet masks will be set along with their corresponding addresses from the addresses array on the virtual interface used by the VPN tunnel.
 */
@property (readonly) NSArray<NSString *> *subnetMasks NS_AVAILABLE(10_11, 9_0);

/*!
 * @property includedRoutes
 * @discussion An array of NEIPv4Route objects. Traffic matching these routes will be routed through the virtual interface used by the VPN tunnel.
 */
@property (copy, nullable) NSArray<NEIPv4Route *> *includedRoutes NS_AVAILABLE(10_11, 9_0);

/*!
 * @property excludedRoutes
 * @discussion An array of NEIPv4Route objects. Traffic matching these routes will be routed through the current primary physical interface of the device.
 */
@property (copy, nullable) NSArray<NEIPv4Route *> *excludedRoutes NS_AVAILABLE(10_11, 9_0);

@end

/*!
 * @interface NEIPv4Route
 * @discussion The NEIPv4Route class declares the programmatic interface for an object that contains settings for an IPv4 route.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEIPv4Route : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithDestinationAddress:subnetMask:
 * @discussion Initialize a newly-allocated NEIPv4Route.
 * @param address The IPv4 address of the destination network.
 * @param subnetMask The subnet mask of the destination network.
 * @return The initialized NEIPv4Route.
 */
- (instancetype)initWithDestinationAddress:(NSString *)address subnetMask:(NSString *)subnetMask NS_AVAILABLE(10_11, 9_0);

/*!
 * @property destinationAddress
 * @discussion An IPv4 address represented as a dotted decimal string. 
 */
@property (readonly) NSString *destinationAddress NS_AVAILABLE(10_11, 9_0);

/*!
 * @property destinationSubnetMask
 * @discussion An IPv4 subnet mask represented as a dotted decimal string. This mask in combination with the destinationAddress property is used to determine the destination network of the route.
 */
@property (readonly) NSString *destinationSubnetMask NS_AVAILABLE(10_11, 9_0);

/*!
 * @property gatewayAddress
 * @discussion The IPv4 address of the route's gateway. If this property is nil then the route's gateway will be set to the tunnel's virtual interface.
 */
@property (copy, nullable) NSString *gatewayAddress NS_AVAILABLE(10_11, 9_0);

/*!
 * @method defaultRoute
 * @return A route object that represents the IPv4 default route.
 */
+ (NEIPv4Route * const)defaultRoute NS_AVAILABLE(10_11, 9_0);
@end

NS_ASSUME_NONNULL_END

