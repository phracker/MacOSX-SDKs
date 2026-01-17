/*
 * Copyright (c) 2020 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEAppProxyProvider.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NETransparentProxyProvider.h
 * @discussion This file declares the NETransparentProxyProvider API. The NETransparentProxyProvider is used to implement custom transparent network proxy solutions.
 */

/*!
 * @interface NETransparentProxyProvider
 * @discussion The NETransparentProxyProvider class declares the programmatic interface for an object that implements the client side of a custom transparent network proxy solution.
 *     The NETransparentProxyProvider class has the following behavior differences from its super class NEAppProxyProvider:
 *         - Returning NO from handleNewFlow: and handleNewUDPFlow:initialRemoteEndpoint: causes the flow to proceed to communicate directly with the flow's ultimate destination, instead of closing the flow with a "Connection Refused" error.
 *         - NEDNSSettings and NEProxySettings specified within NETransparentProxyNetworkSettings are ignored. Flows that match the includedNetworkRules within NETransparentProxyNetworkSettings will use the same DNS and proxy settings that other flows on the system are currently using.
 *         - Flows that are created using a "connect by name" API (such as Network.framework or NSURLSession) that match the includedNetworkRules will not bypass DNS resolution.
 *
 * NETransparentProxyProvider is part of NetworkExtension.framework
 */
API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NETransparentProxyProvider : NEAppProxyProvider
@end

NS_ASSUME_NONNULL_END
