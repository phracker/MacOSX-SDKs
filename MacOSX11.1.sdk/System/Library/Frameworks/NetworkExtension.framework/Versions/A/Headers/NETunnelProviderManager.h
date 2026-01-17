/*
 * Copyright (c) 2015, 2018, 2020 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEVPNManager.h>
#import <NetworkExtension/NETunnelProvider.h>

NS_ASSUME_NONNULL_BEGIN

@class NEAppRule;

/*!
 * @file NETunnelProviderManager
 * @discussion This file declares the NETunnelProviderManager API. The NETunnelProviderManager API is used to configure and control network tunnels provided by NETunnelProviders.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NETunnelProviderManager
 * @discussion The NETunnelProviderManager class declares the programmatic interface for an object that is used to configure and control network tunnels provided by NETunnelProviders.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface NETunnelProviderManager : NEVPNManager

/*!
 * @method loadAllFromPreferencesWithCompletionHandler:
 * @discussion This function asynchronously reads all of the NETunnelProvider configurations created by the calling app that have previously been saved to disk and returns them as NETunnelProviderManager objects.
 * @param completionHandler A block that takes an array NETunnelProviderManager objects. The array passed to the block may be empty if no NETunnelProvider configurations were successfully read from the disk.  The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
+ (void)loadAllFromPreferencesWithCompletionHandler:(void (^)(NSArray<NETunnelProviderManager *> * __nullable managers, NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method forPerAppVPN
 * @discussion Create a NETunnelProviderManager instance that is used to manage a per-app VPN configuration.
 */
+ (instancetype)forPerAppVPN API_AVAILABLE(macos(10.15.4)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @method copyAppRules
 * @discussion This function returns an array of NEAppRule objects.
 */
- (nullable NSArray<NEAppRule *> *)copyAppRules API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property routingMethod
 * @discussion The method by which network traffic is routed to the tunnel. The default is NETunnelProviderRoutingMethodDestinationIP.
 */
@property (readonly) NETunnelProviderRoutingMethod routingMethod API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property safariDomains
 * @discussion An array of domain strings. Only applies to per-app VPN configurations. When the per-app VPN is enabled and the user navigates in Safari to a web site within one of these domains,
 * 	the web site network traffic is routed through the per-app VPN.
 */
@property (copy) NSArray<NSString *> *safariDomains API_AVAILABLE(macos(10.15.4)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property mailDomains
 * @discussion An array of domain strings. Only applies to per-app VPN configurations. When the per-app VPN is enabled, connections from the Mail app to mail servers within
 * 	one of these domains are routed through the per-app VPN.
 */
@property (copy) NSArray<NSString *> *mailDomains API_AVAILABLE(macos(10.15.4)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property calendarDomains
 * @discussion An array of domain strings. Only applies to per-app VPN configurations. When the per-app VPN is enabled, connections from the Calendar app to calendar servers within one of
 * 	these domains are routed through the per-app VPN.
 */
@property (copy) NSArray<NSString *> *calendarDomains API_AVAILABLE(macos(10.15.4)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property contactsDomains
 * @discussion An array of domain strings. Only applies to per-app VPN configurations. When the per-app VPN is enabled, connections from the Contacts app to contacts servers within one of these
 * 	domains are routed through the per-app VPN.
 */
@property (copy) NSArray<NSString *> *contactsDomains API_AVAILABLE(macos(10.15.4)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property appRules
 * @property An array of NEAppRule objects. Only applies to per-app VPN configurations. Network traffic originating from apps matching one of these rules is routed through the per-app VPN.
 */
@property (copy) NSArray<NEAppRule *> *appRules API_AVAILABLE(macos(10.15.4)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property excludedDomains
 * @property An array of domain strings. Only applies to per-app VPN configurations. When the per-app VPN is enabled, connections to servers within one of these domains are excluded from the
 *   per-app VPN.
 */
@property (copy) NSArray<NSString *> *excludedDomains API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property associatedDomains
 * @property An array of domain strings. Only applies to per-app VPN configurations. HTTP requests to download the Apple App Site Association files for domains in this list are routed through the per-app VPN.
 */
@property (copy) NSArray<NSString *> *associatedDomains API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END

