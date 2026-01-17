/*
 * Copyright (c) 2013-2015 Apple Inc.
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
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEFilterProviderConfiguration : NSObject <NSSecureCoding,NSCopying>

/*!
 * @property filterBrowsers
 * @discussion If YES, the filter plugin will be allowed to filter browser traffic. If NO, the filter plugin will not see any browser flows. Defaults to NO. At least one of filterBrowsers and filterSockets should be set to YES to make the filter take effect.
 */
@property BOOL filterBrowsers NS_AVAILABLE(10_11, 9_0);

/*!
 * @property filterSockets
 * @discussion If YES, the filter plugin will be allowed to filter socket traffic. If NO, the filter plugin will not see any socket flows. Defaults to NO. At least one of filterBrowsers and filterSockets should be set to YES to make the filter take effect.
 */
@property BOOL filterSockets NS_AVAILABLE(10_11, 9_0);

/*!
 * @property vendorConfiguration
 * @discussion An optional dictionary of plugin-specific keys to be passed to the plugin.
 */
@property (copy, nullable) NSDictionary<NSString *,id> *vendorConfiguration NS_AVAILABLE(10_11, 9_0);

/*!
 * @property serverAddress
 * @discussion The optional address of the server used to support the filter.
 */
@property (copy, nullable) NSString *serverAddress NS_AVAILABLE(10_11, 9_0);

/*!
 * @property username
 * @discussion The optional username associated with the filter.
 */
@property (copy, nullable) NSString *username NS_AVAILABLE(10_11, 9_0);

/*!
 * @property organization
 * @discussion The optional organization associated with the filter.
 */
@property (copy, nullable) NSString *organization NS_AVAILABLE(10_11, 9_0);

/*!
 * @property passwordReference
 * @discussion The optional password keychain reference associated with the filter.
 */
@property (copy, nullable) NSData *passwordReference NS_AVAILABLE(10_11, 9_0);

/*!
 * @property identityReference
 * @discussion The optional certificate identity keychain reference associated with the filter.
 */
@property (copy, nullable) NSData *identityReference NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

