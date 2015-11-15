/*
 * Copyright (c) 2013-2015 Apple Inc.
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
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEDNSSettings : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithServers:
 * @discussion Initialize a newly-allocated NEDNSSettings object.
 * @param servers An array of DNS server IP address strings.
 */
- (instancetype)initWithServers:(NSArray<NSString *> *)servers NS_AVAILABLE(10_11, 9_0);

/*!
 * @property servers
 * @discussion An array of DNS server address strings.
 */
@property (readonly) NSArray<NSString *> *servers NS_AVAILABLE(10_11, 9_0);

/*! 
 * @property searchDomains
 * @discussion An array of DNS server search domain strings.
 */
@property (copy, nullable) NSArray<NSString *> *searchDomains NS_AVAILABLE(10_11, 9_0);

/*!
 * @property domainName
 * @discussion A string containing the DNS domain.
 */
@property (copy, nullable) NSString *domainName NS_AVAILABLE(10_11, 9_0);

/*!
 * @property matchDomains
 * @discussion An array of strings containing domain strings. If this property is non-nil, the DNS settings will only be used to resolve host names within the specified domains.
 */
@property (copy, nullable) NSArray<NSString *> *matchDomains NS_AVAILABLE(10_11, 9_0);

/*!
 * @property matchDomainsNoSearch
 * @discussion A boolean indicating if the match domains should be appended to the search domain list.  Default is NO (match domains will be appended to the search domain list).
 */
@property BOOL matchDomainsNoSearch NS_AVAILABLE(10_11, 9_0);
@end

NS_ASSUME_NONNULL_END

