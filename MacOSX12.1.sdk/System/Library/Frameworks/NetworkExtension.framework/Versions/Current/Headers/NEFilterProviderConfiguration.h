/*
 * Copyright (c) 2013-2015, 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @interface NEFilterProviderConfiguration
 * @discussion The NEFilterProviderConfiguration class declares the programmatic interface of an object that configures a plugin-based content filter.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface NEFilterProviderConfiguration : NSObject <NSSecureCoding,NSCopying>

/*!
 * @property filterBrowsers
 * @discussion If YES, the filter plugin will be allowed to filter browser traffic. If NO, the filter plugin will not see any browser flows. Defaults to NO. At least one of filterBrowsers and filterSockets should be set to YES to make the filter take effect.
 */
@property BOOL filterBrowsers API_DEPRECATED("filterBrowsers is not supported on macOS", macos(10.11, 10.15)) API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property filterSockets
 * @discussion If YES, the filter plugin will be allowed to filter socket traffic. If NO, the filter plugin will not see any socket flows. Defaults to NO. At least one of filterBrowsers and filterSockets should be set to YES to make the filter take effect.
 */
@property BOOL filterSockets API_AVAILABLE(ios(9.0), macos(10.15)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property filterPackets
 * @discussion If YES, a NEFilterPacketProvider will be instantiated and will be allowed to filter packets.
 */
@property BOOL filterPackets API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property vendorConfiguration
 * @discussion An optional dictionary of plugin-specific keys to be passed to the plugin.
 */
@property (copy, nullable) NSDictionary<NSString *,id> *vendorConfiguration API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property serverAddress
 * @discussion The optional address of the server used to support the filter.
 */
@property (copy, nullable) NSString *serverAddress API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property username
 * @discussion The optional username associated with the filter.
 */
@property (copy, nullable) NSString *username API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property organization
 * @discussion The optional organization associated with the filter.
 */
@property (copy, nullable) NSString *organization API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property passwordReference
 * @discussion The optional password keychain reference associated with the filter.
 */
@property (copy, nullable) NSData *passwordReference API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property identityReference
 * @discussion The optional certificate identity keychain reference associated with the filter.
 */
@property (copy, nullable) NSData *identityReference API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property filterDataProviderBundleIdentifier
 * @discussion A string containing the bundle identifier of the NEFilterDataProvider app extension or system extension.
 *     If this property is nil, then the bundle identifier of the NEFilterDataProvider extension in the calling app's
 *     bundle is used, and if the calling app's bundle contains more than one NEFilterDataProvider extension then which one will
 *     be used is undefined.
 */
@property (copy, nullable) NSString *filterDataProviderBundleIdentifier API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property filterPacketProviderBundleIdentifier
 * @discussion A string containing the bundle identifier of the NEFilterPacketProvider app extension or system extension.
 *     If this property is nil, then the bundle identifier of the NEFilterPacketProvider extension in the calling app's
 *     bundle is used, and if the calling app's bundle contains more than one NEFilterPacketProvider extension then which one will
 *     be used is undefined.
 */
@property (copy, nullable) NSString *filterPacketProviderBundleIdentifier API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END

