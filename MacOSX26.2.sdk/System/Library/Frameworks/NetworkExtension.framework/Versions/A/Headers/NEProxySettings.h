/*
 * Copyright (c) 2013-2015, 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEProxySettings.h
 * @discussion This file declares the NEProxySettings API. The NEProxySettings API is used to specify proxy settings to be used when a Network Extension is active.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NEProxyServer
 * @discussion The NEProxyServer class declares the programmatic interface for an object that contains settings for a proxy server.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface NEProxyServer : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithAddress:port:
 * @discussion This function initializes a newly-allocated NEProxyServer object
 * @param address The string representation of the proxy server IP address.
 * @param port The TCP port of the proxy server.
 */
- (instancetype)initWithAddress:(NSString *)address port:(NSInteger)port API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property address
 * @discussion The string representation of the proxy server IP address.
 */
@property (readonly) NSString *address API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property port
 * @discussion The TCP port of the proxy server.
 */
@property (readonly) NSInteger port API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property authenticationRequired
 * @discussion A flag indicating if the server requires authentication credentials.
 */
@property BOOL authenticationRequired API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property username
 * @discussion The username portion of the authentication credential to use when communicating with the proxy server.
 */
@property (copy, nullable) NSString *username API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property password
 * @discussion The password portion of the authentication credential to use when communicating with the proxy server. This property is only saved persistently if the username property is non-nil and non-empty and if the authenticationRequired flag is set.
 */
@property (copy, nullable) NSString *password API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

@end

/*!
 * @interface NEProxySettings
 * @discussion The NEProxySettings class declares the programmatic interface for an object that contains proxy settings.
 *
 * NEProxySettings is used in the context of a Network Extension configuration to specify the proxy that should be used for network traffic when the Network Extension is active.
 */
API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface NEProxySettings : NSObject <NSSecureCoding,NSCopying>

/*!
 * @property autoProxyConfigurationEnabled
 * @discussion A boolean indicating if proxy auto-configuration is enabled.
 */
@property BOOL autoProxyConfigurationEnabled API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property proxyAutoConfigurationURL
 * @discussion A URL specifying where the PAC script is located.
 */
@property (copy, nullable) NSURL *proxyAutoConfigurationURL API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property proxyAutoConfigurationJavaScript
 * @discussion A string containing the PAC JavaScript source code.
 */
@property (copy, nullable) NSString *proxyAutoConfigurationJavaScript API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property HTTPEnabled
 * @discussion A boolean indicating if the static HTTP proxy is enabled.
 */
@property BOOL HTTPEnabled API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property HTTPServer
 * @discussion A NEProxyServer object containing the HTTP proxy server settings.
 */
@property (copy, nullable) NEProxyServer *HTTPServer API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property HTTPSEnabled
 * @discussion A boolean indicating if the static HTTPS proxy is enabled.
 */
@property BOOL HTTPSEnabled API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property HTTPSServer
 * @discussion A NEProxyServer object containing the HTTPS proxy server settings.
 */
@property (copy, nullable) NEProxyServer *HTTPSServer API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property excludeSimpleHostnames
 * @discussion A flag indicating if the proxy settings should not be used for network destinations specified using single-label host names.
 */
@property BOOL excludeSimpleHostnames API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property exceptionList
 * @discussion An array of domain strings. If the destination host name of a connection shares a suffix with one of these strings then the proxy settings will not be used for the connection.
 */
@property (copy, nullable) NSArray<NSString *> *exceptionList API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property matchDomains
 * @discussion An array of domain strings. If the destination host name of a connection shares a suffix with one of these strings then the proxy settings will be used for the connection. Otherwise the proxy settings will not be used. If this property is nil then all connections to which the Network Extension applies will use the proxy settings.
 */
@property (copy, nullable) NSArray<NSString *> *matchDomains API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

