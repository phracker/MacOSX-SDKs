/*
 * Copyright (c) 2019 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NETunnelNetworkSettings.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NETransparentProxyNetworkSettings.h
 * @discussion This file declares the NETransparentProxyNetworkSettings API. The NETransparentProxyNetworkSettings API is used to specify the network traffic that will be routed through a transparent proxy.
 *
 * This API is part of NetworkExtension.framework
 */

@class NENetworkRule;

/*!
 * @interface NETransparentProxyNetworkSettings
 * @discussion The NETransparentProxyNetworkSettings class declares the programmatic interface for an object that contains network settings.
 *
 * NETransparentProxyNetworkSettings is used by NEAppProxyProviders to communicate the desired network settings for the proxy to the framework. The framework takes care of applying the contained settings to the system.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED
@interface NETransparentProxyNetworkSettings : NETunnelNetworkSettings

/*!
 * @property includedNetworkRules
 * @discussion An array of NENetworkRule objects that collectively specify the traffic that will be routed through the transparent proxy. The following restrictions
 *    apply to each NENetworkRule in this list:
 *    Restrictions for rules with an address endpoint:
 *        If the port string of the endpoint is "0" or is the empty string, then the address of the endpoint must be a non-wildcard address (i.e. "0.0.0.0" or "::").
 *        If the address is a wildcard address (i.e. "0.0.0.0" or "::"), then the port string of the endpoint must be non-empty and must not be "0".
 *        A port string of "53" is not allowed. Destination Domain-based rules must be used to match DNS traffic.
 *        The matchLocalNetwork property must be nil.
 *        The matchDirection property must be NETrafficDirectionOutbound.
 */
@property (copy, nullable) NSArray<NENetworkRule *> *includedNetworkRules API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property excludedNetworkRules
 * @discussion An array of NENetworkRule objects that collectively specify the traffic that will not be routed through the transparent proxy. The following restrictions
 *    apply to each NENetworkRule in this list:
 *    Restrictions for rules with an address endpoint:
 *        If the port string of the endpoint is "0" or is the empty string, then the address of the endpoint must be a non-wildcard address (i.e. "0.0.0.0" or "::").
 *        If the address is a wildcard address (i.e. "0.0.0.0" or "::"), then the port string of the endpoint must be non-empty and must not be "0".
 *        A port string of "53" is not allowed. Destination Domain-based rules must be used to match DNS traffic.
 *        The matchLocalNetwork property must be nil.
 *        The matchDirection property must be NETrafficDirectionOutbound.
 */
@property (copy, nullable) NSArray<NENetworkRule *> *excludedNetworkRules API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
