/*
 * Copyright (c) 2017 Apple Inc.
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
NS_CLASS_AVAILABLE(10_13, 11_0)
@interface NEDNSProxyProviderProtocol : NEVPNProtocol

/*!
 * @property providerConfiguration
 * @discussion A dictionary containing NEDNSProxyProvider vendor-specific configuration parameters. This dictionary is passed as-is to NEDNSProxyProviders when a DNS proxy is started.
 */
@property (copy, nullable) NSDictionary<NSString *,id> *providerConfiguration NS_AVAILABLE(10_13, 11_0);

/*!
 * @property providerBundleIdentifier
 * @discussion A string containing the bundle identifier of the NEDNSProxyProvider to be used by this configuration.
 */
@property (copy, nullable) NSString *providerBundleIdentifier NS_AVAILABLE(10_13, 11_0);

@end

NS_ASSUME_NONNULL_END

