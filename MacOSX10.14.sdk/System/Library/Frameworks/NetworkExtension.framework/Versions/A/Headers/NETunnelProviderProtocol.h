/*
 * Copyright (c) 2015, 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEVPNProtocol.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NETunnelProviderProtocol.h
 * @discussion This file declares the NETunnelProviderProtocol API. The NETunnelProviderProtocol API is used to specify configuration settings that are specific to Network Extensions provided by NETunnelProviders.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NETunnelProviderProtocol
 * @discussion The NETunnelProviderProtocol class declares the programmatic interface for an object that contains NETunnelProvider-specific configuration settings.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NETunnelProviderProtocol : NEVPNProtocol

/*!
 * @property providerConfiguration
 * @discussion A dictionary containing NETunnelProvider vendor-specific configuration parameters. This dictionary is passed as-is to NETunnelProviders when a tunnel is started.
 */
@property (copy, nullable) NSDictionary<NSString *,id> *providerConfiguration API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property providerBundleIdentifier
 * @discussion A string containing the bundle identifier of the NETunnelProvider to be used by this configuration.
 */
@property (copy, nullable) NSString *providerBundleIdentifier API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

