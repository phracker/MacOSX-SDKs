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
 * @typedef NEDNSProtocol
 * @abstract DNS protocol variants
 */
typedef NS_ENUM(NSInteger, NEDNSProtocol) {
	/*! @const NEDNSProtocolCleartext Use traditional cleartext DNS over UDP and TCP port 53 */
	NEDNSProtocolCleartext = 1,
	/*! @const NEDNSProtocolTLS Use DNS-over-TLS */
	NEDNSProtocolTLS = 2,
	/*! @const NEDNSProtocolHTTPS Use DNS-over-HTTPS */
	NEDNSProtocolHTTPS = 3,
} API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @interface NEDNSSettings
 * @discussion The NEDNSSettings class declares the programmatic interface for an object that contains DNS settings.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface NEDNSSettings : NSObject <NSSecureCoding,NSCopying>

/*!
 * @property dnsProtocol
 * @discussion The DNS protocol used by the settings.
 */
@property (readonly) NEDNSProtocol dnsProtocol API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method initWithServers:
 * @discussion Initialize a newly-allocated NEDNSSettings object.
 * @param servers An array of DNS server IP address strings.
 */
- (instancetype)initWithServers:(NSArray<NSString *> *)servers API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property servers
 * @discussion An array of DNS server address strings.
 */
@property (readonly) NSArray<NSString *> *servers API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*! 
 * @property searchDomains
 * @discussion An array of DNS server search domain strings.
 */
@property (copy, nullable) NSArray<NSString *> *searchDomains API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property domainName
 * @discussion A string containing the DNS domain.
 */
@property (copy, nullable) NSString *domainName API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property matchDomains
 * @discussion An array of strings containing domain strings. If this property is non-nil, the DNS settings will only be used to resolve host names within the specified domains.
 */
@property (copy, nullable) NSArray<NSString *> *matchDomains API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property matchDomainsNoSearch
 * @discussion A boolean indicating if the match domains should be appended to the search domain list.  Default is NO (match domains will be appended to the search domain list).
 */
@property BOOL matchDomainsNoSearch API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;
@end

API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface NEDNSOverTLSSettings : NEDNSSettings

/*!
 * @property serverName
 * @discussion The name of the server to use for TLS certificate validation.
 */
@property (copy, nullable) NSString *serverName API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

@end

API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface NEDNSOverHTTPSSettings : NEDNSSettings

/*!
 * @property serverURL
 * @discussion The URL to which to make DNS-over-HTTPS requests. The format should be an HTTPS URL with the path indicating the location of the DNS-over-HTTPS server, such as: "https://dnsserver.example.net/dns-query".
 */
@property (copy, nullable) NSURL *serverURL API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END

