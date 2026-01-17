/*
 * Copyright (c) 2022 Apple Inc.
 * All rights reserved.
 */

#import <NetworkExtension/NEPacketTunnelNetworkSettings.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEEthernetTunnelNetworkSettings.h
 * @discussion This file declares the NEEthernetTunnelNetworkSettings API. The NEEthernetTunnelNetworkSettings API is used to specify network settings for VPN tunnels.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NEEthernetTunnelNetworkSettings
 * @discussion The NEEthernetTunnelNetworkSettings class declares the programmatic interface for an object that contains network settings.
 *
 * NEEthernetTunnelNetworkSettings is used by NEEthernetTunnelProviders to communicate the desired network settings for the packet tunnel to the framework. The framework takes care of applying the contained settings to the system.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(13.0)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NEEthernetTunnelNetworkSettings : NEPacketTunnelNetworkSettings

/*!
 * @method initWithTunnelRemoteAddress:
 * @discussion This function initializes a newly-allocated NEEthernetTunnelNetworkSettings object with a given tunnel remote address and MAC address.
 * @param address The address of the remote endpoint that is providing the tunnel service.
 * @param ethernetAddress The ethernet address to be assigned to the tunnel interface. This string should be in the format "xx:xx:xx:xx:xx:xx", where each xx is a hexidecimal number between 0 and ff.
 * @param mtu The MTU (Maxium Transmission Unit) in bytes to be assigned to the tunnel interface.
 */
- (instancetype)initWithTunnelRemoteAddress:(NSString *)address ethernetAddress:(NSString *)ethernetAddress mtu:(NSInteger)mtu API_AVAILABLE(macos(13.0)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property ethernetAddress
 * @discussion An NSString object containing the ethernet address of the tunnel interface.
 */
@property (readonly) NSString *ethernetAddress API_AVAILABLE(macos(13.0)) API_UNAVAILABLE(ios, watchos, tvos);

@end

NS_ASSUME_NONNULL_END
