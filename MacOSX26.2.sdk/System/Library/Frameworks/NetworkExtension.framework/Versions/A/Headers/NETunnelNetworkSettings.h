/*
 * Copyright (c) 2015, 2018 Apple Inc.
 * All rights reserved.
 */

NS_ASSUME_NONNULL_BEGIN

@class NEDNSSettings;
@class NEProxySettings;

/*!
 * @file NETunnelNetworkSettings
 * @discussion This file declares the NETunnelNetworkSettings API. The NETunnelNetworkSettings API is used to specify network settings for tunnel provider by NetworkExtension providers.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NETunnelNetworkSettings
 * @discussion The NETunnelNetworkSettings class declares the programmatic interface for an object that contains network settings.
 *
 * NETunnelNetworkSettings is used by NETunnelProviders to communicate the desired network settings for the tunnel to the framework. The framework takes care of applying the contained settings to the system.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface NETunnelNetworkSettings : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithTunnelRemoteAddress:
 * @discussion This function initializes a newly-allocated NETunnelNetworkSettings object with a given tunnel remote address.
 * @param address The address of the remote endpoint that is providing the tunnel service.
 */
- (instancetype)initWithTunnelRemoteAddress:(NSString *)address API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property tunnelRemoteAddress
 * @discussion A string containing the IP address of the remote endpoint that is providing the tunnel service.
 */
@property (readonly) NSString *tunnelRemoteAddress API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property DNSSettings
 * @discussion An NEDNSSettings object that contains the desired tunnel DNS settings.
 */
@property (copy, nullable) NEDNSSettings *DNSSettings API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property proxySettings
 * @discussion An NEProxySettings object that contains the desired tunnel proxy settings.
 */
@property (copy, nullable) NEProxySettings *proxySettings API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

