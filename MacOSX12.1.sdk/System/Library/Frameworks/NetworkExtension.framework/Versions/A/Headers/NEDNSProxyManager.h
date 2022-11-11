/*
 * Copyright (c) 2017-2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEDNSProxyManager.h
 * @discussion This file declares the NEDNSProxyManager API. The NEDNSProxyManager API is used to configure and control DNS proxies.
 *
 * This API is part of NetworkExtension.framework.
 *
 * This API is used to create DNS proxy configurations.
 */

#if defined(__cplusplus)
#define NEDNSPROXY_EXPORT extern "C"
#else
#define NEDNSPROXY_EXPORT extern
#endif

@class NEDNSProxyProviderProtocol;

/*!
 * @typedef NEDNSProxyError
 * @abstract DNS proxy error codes
 */
typedef NS_ENUM(NSInteger, NEDNSProxyManagerError) {
	/*! @const NEDNSProxyManagerErrorConfigurationInvalid The DNS proxy configuration is invalid */
	NEDNSProxyManagerErrorConfigurationInvalid = 1,
	/*! @const NEDNSProxyManagerErrorConfigurationDisabled The DNS proxy configuration is not enabled. */
	NEDNSProxyManagerErrorConfigurationDisabled = 2,
	/*! @const NEDNSProxyManagerErrorConfigurationStale The DNS proxy configuration needs to be loaded. */
	NEDNSProxyManagerErrorConfigurationStale = 3,
	/*! @const NEDNSProxyManagerErrorConfigurationCannotBeRemoved The DNS proxy configuration cannot be removed. */
	NEDNSProxyManagerErrorConfigurationCannotBeRemoved = 4,
} API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*! @const NEDNSProxyManagerErrorDomain The DNS proxy error domain */
NEDNSPROXY_EXPORT NSString * const NEDNSProxyErrorDomain API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*! @const NEDNSProxyConfigurationDidChangeNotification Name of the NSNotification that is posted when the DNS proxy configuration changes. */
NEDNSPROXY_EXPORT NSString * const NEDNSProxyConfigurationDidChangeNotification API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @interface NEDNSProxyManager
 * @discussion The NEDNSProxyManager class declares the programmatic interface for an object that manages DNS proxy configurations.
 *
 * NEDNSProxyManager declares methods and properties for configuring and controlling a DNS proxy.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface NEDNSProxyManager : NSObject

/*!
 * @method sharedManager
 * @return The singleton NEDNSProxyManager object for the calling process.
 */
+ (NEDNSProxyManager *)sharedManager API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method loadFromPreferencesWithCompletionHandler:
 * @discussion This function loads the current DNS proxy configuration from the caller's DNS proxy preferences.
 * @param completionHandler A block that will be called when the load operation is completed. The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
- (void)loadFromPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method removeFromPreferencesWithCompletionHandler:
 * @discussion This function removes the DNS proxy configuration from the caller's DNS proxy preferences. If the DNS proxy is enabled, the DNS proxy becomes disabled.
 * @param completionHandler A block that will be called when the remove operation is completed. The NSError passed to this block will be nil if the remove operation succeeded, non-nil otherwise.
 */
- (void)removeFromPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method saveToPreferencesWithCompletionHandler:
 * @discussion This function saves the DNS proxy configuration in the caller's DNS proxy preferences. If the DNS proxy is enabled, it will become active.
 * @param completionHandler A block that will be called when the save operation is completed. The NSError passed to this block will be nil if the save operation succeeded, non-nil otherwise.
 */
- (void)saveToPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property localizedDescription
 * @discussion A string containing a description of the DNS proxy.
 */
@property (copy, nullable) NSString *localizedDescription API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property providerProtocol
 * @discussion An NEDNSProxyProviderProtocol object containing the provider-specific portion of the DNS proxy configuration.
 */
@property (strong, nullable) NEDNSProxyProviderProtocol *providerProtocol API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property enabled
 * @discussion Toggles the enabled status of the DNS proxy. Setting this property will disable DNS proxy configurations of other apps. This property will be set to NO when other DNS proxy configurations are enabled.
 */
@property (getter=isEnabled) BOOL enabled API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END

