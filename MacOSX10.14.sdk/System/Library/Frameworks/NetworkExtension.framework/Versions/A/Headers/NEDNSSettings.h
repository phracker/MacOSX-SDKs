/*
 * Copyright (c) 2013-2015, 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEDNSSettings.h
 * @discussion This file declares the NEDNSSettings API. The NEDNSSettings API is used to specify DNS settings for Network Extensions.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NEDNSSettings
 * @discussion The NEDNSSettings class declares the programmatic interface for an object that contains DNS settings.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEDNSSettings : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithServers:
 * @discussion Initialize a newly-allocated NEDNSSettings object.
 * @param servers An array of DNS server IP address strings.
 */
- (instancetype)initWithServers:(NSArray<NSString *> *)servers API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property servers
 * @discussion An array of DNS server address strings.
 */
@property (readonly) NSArray<NSString *> *servers API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*! 
 * @property searchDomains
 * @discussion An array of DNS server search domain strings.
 */
@property (copy, nullable) NSArray<NSString *> *searchDomains API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property domainName
 * @discussion A string containing the DNS domain.
 */
@property (copy, nullable) NSString *domainName API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property matchDomains
 * @discussion An array of strings containing domain strings. If this property is non-nil, the DNS settings will only be used to resolve host names within the specified domains.
 */
@property (copy, nullable) NSArray<NSString *> *matchDomains API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property matchDomainsNoSearch
 * @discussion A boolean indicating if the match domains should be appended to the search domain list.  Default is NO (match domains will be appended to the search domain list).
 */
@property BOOL matchDomainsNoSearch API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);
@end

NS_ASSUME_NONNULL_END

