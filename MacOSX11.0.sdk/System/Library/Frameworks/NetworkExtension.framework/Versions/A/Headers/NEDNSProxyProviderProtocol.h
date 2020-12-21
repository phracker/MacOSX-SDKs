/*
 * Copyright (c) 2017-2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEVPNProtocol.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEDNSProxyProviderProtocol.h
 * @discussion This file declares the NEDNSProxyProviderProtocol API. The NEDNSProxyProviderProtocol API is used to specify configuration settings that are specific to Network Extensions provided by NEDNSProxyProviders.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NEDNSProxyProviderProtocol
 * @discussion The NEDNSProxyProviderProtocol class declares the programmatic interface for an object that contains NEDNSProxyProvider-specific configuration settings.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.13), ios(11.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface NEDNSProxyProviderProtocol : NEVPNProtocol

/*!
 * @property providerConfiguration
 * @discussion A dictionary containing NEDNSProxyProvider vendor-specific configuration parameters. This dictionary is passed as-is to NEDNSProxyProviders when a DNS proxy is started.
 */
@property (copy, nullable) NSDictionary<NSString *,id> *providerConfiguration API_AVAILABLE(macos(10.13), ios(11.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property providerBundleIdentifier
 * @discussion A string containing the bundle identifier of the NEDNSProxyProvider to be used by this configuration.
 */
@property (copy, nullable) NSString *providerBundleIdentifier API_AVAILABLE(macos(10.13), ios(11.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END

