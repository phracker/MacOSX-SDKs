/*
 * Copyright (c) 2013-2015 Apple Inc.
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
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEProxyServer : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithAddress:port:
 * @discussion This function initializes a newly-allocated NEProxyServer object
 * @param address The string representation of the proxy server IP address.
 * @param port The TCP port of the proxy server.
 */
- (instancetype)initWithAddress:(NSString *)address port:(NSInteger)port NS_AVAILABLE(10_11, 9_0);

/*!
 * @property address
 * @discussion The string representation of the proxy server IP address.
 */
@property (readonly) NSString *address NS_AVAILABLE(10_11, 9_0);

/*!
 * @property port
 * @discussion The TCP port of the proxy server.
 */
@property (readonly) NSInteger port NS_AVAILABLE(10_11, 9_0);

/*!
 * @property authenticationRequired
 * @discussion A flag indicating if the server requires authentication credentials.
 */
@property BOOL authenticationRequired NS_AVAILABLE(10_11, 9_0);

/*!
 * @property username
 * @discussion The username portion of the authentication credential to use when communicating with the proxy server.
 */
@property (copy, nullable) NSString *username NS_AVAILABLE(10_11, 9_0);

/*!
 * @property password
 * @discussion The password portion of the authentication credential to use when communicating with the proxy server. This property is only saved persistently if the username property is non-nil and non-empty and if the authenticationRequired flag is set.
 */
@property (copy, nullable) NSString *password NS_AVAILABLE(10_11, 9_0);

@end

/*!
 * @interface NEProxySettings
 * @discussion The NEProxySettings class declares the programmatic interface for an object that contains proxy settings.
 *
 * NEProxySettings is used in the context of a Network Extension configuration to specify the proxy that should be used for network traffic when the Network Extension is active.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEProxySettings : NSObject <NSSecureCoding,NSCopying>

/*!
 * @property autoProxyConfigurationEnabled
 * @discussion A boolean indicating if proxy auto-configuration is enabled.
 */
@property BOOL autoProxyConfigurationEnabled NS_AVAILABLE(10_11, 9_0);

/*!
 * @property proxyAutoConfigurationURL
 * @discussion A URL specifying where the PAC script is located.
 */
@property (copy, nullable) NSURL *proxyAutoConfigurationURL NS_AVAILABLE(10_11, 9_0);

/*!
 * @property proxyAutoConfigurationJavaScript
 * @discussion A string containing the PAC JavaScript source code.
 */
@property (copy, nullable) NSString *proxyAutoConfigurationJavaScript NS_AVAILABLE(10_11, 9_0);

/*!
 * @property HTTPEnabled
 * @discussion A boolean indicating if the static HTTP proxy is enabled.
 */
@property BOOL HTTPEnabled NS_AVAILABLE(10_11, 9_0);

/*!
 * @property HTTPServer
 * @discussion A NEProxyServer object containing the HTTP proxy server settings.
 */
@property (copy, nullable) NEProxyServer *HTTPServer NS_AVAILABLE(10_11, 9_0);

/*!
 * @property HTTPSEnabled
 * @discussion A boolean indicating if the static HTTPS proxy is enabled.
 */
@property BOOL HTTPSEnabled NS_AVAILABLE(10_11, 9_0);

/*!
 * @property HTTPSServer
 * @discussion A NEProxyServer object containing the HTTPS proxy server settings.
 */
@property (copy, nullable) NEProxyServer *HTTPSServer NS_AVAILABLE(10_11, 9_0);

/*!
 * @property excludeSimpleHostnames
 * @discussion A flag indicating if the proxy settings should not be used for network destinations specified using single-label host names.
 */
@property BOOL excludeSimpleHostnames NS_AVAILABLE(10_11, 9_0);

/*!
 * @property exceptionList
 * @discussion An array of domain strings. If the destination host name of a connection shares a suffix with one of these strings then the proxy settings will not be used for the connection.
 */
@property (copy, nullable) NSArray<NSString *> *exceptionList NS_AVAILABLE(10_11, 9_0);

/*!
 * @property matchDomains
 * @discussion An array of domain strings. If the destination host name of a connection shares a suffix with one of these strings then the proxy settings will be used for the connection. Otherwise the proxy settings will not be used. If this property is nil then all connections to which the Network Extension applies will use the proxy settings.
 */
@property (copy, nullable) NSArray<NSString *> *matchDomains NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

