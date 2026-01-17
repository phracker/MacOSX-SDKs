/*
 * Copyright (c) 2015, 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NETunnelNetworkSettings.h>

NS_ASSUME_NONNULL_BEGIN

@class NEIPv4Settings;
@class NEIPv6Settings;

/*!
 * @file NEPacketTunnelNetworkSettings
 * @discussion This file declares the NEPacketTunnelNetworkSettings API. The NEPacketTunnelNetworkSettings API is used to specify IP network settings for VPN tunnels.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NEPacketTunnelNetworkSettings
 * @discussion The NEPacketTunnelNetworkSettings class declares the programmatic interface for an object that contains IP network settings.
 *
 * NEPacketTunnelNetworkSettings is used by NEPacketTunnelProviders to communicate the desired IP network settings for the packet tunnel to the framework. The framework takes care of applying the contained settings to the system.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface NEPacketTunnelNetworkSettings : NETunnelNetworkSettings

/*!
 * @property IPv4Settings
 * @discussion An NEIPv4Settings object that contains the desired tunnel IPv4 settings.
 */
@property (copy, nullable) NEIPv4Settings *IPv4Settings API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property IPv6Settings
 * @discussion An NEIPv6Settings object that contains the desired tunnel IPv6 settings.
 */
@property (copy, nullable) NEIPv6Settings *IPv6Settings API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property tunnelOverheadBytes
 * @discussion An NSNumber object containing the number of bytes of overhead appended to each outbound packet through the tunnel. The MTU for the TUN interface is computed by subtracting this value from the MTU of the primary physical interface.
 */
@property (copy, nullable) NSNumber *tunnelOverheadBytes API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property MTU
 * @discussion An NSNumber object containing the Maximum Transmission Unit (MTU) size in bytes to assign to the TUN interface. If this property is set, the tunnelOverheadBytes property is ignored.
 */
@property (copy, nullable) NSNumber *MTU API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

