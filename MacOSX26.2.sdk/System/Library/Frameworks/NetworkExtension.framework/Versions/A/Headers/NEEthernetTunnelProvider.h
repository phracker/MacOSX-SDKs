/*
 * Copyright (c) 2022 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEPacketTunnelProvider.h>
#import <Network/Network.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEEthernetTunnelProvider.h
 * @discussion This file declares the NEEthernetTunnelProvider API. The NEEthernetTunnelProvider API is used to implement custom link-layer packet tunneling solutions.
 */

/*!
 * @interface NEEthernetTunnelProvider
 * @discussion The NEEthernetTunnelProvider class declares the programmatic interface of an object that implements the client side of a custom link-layer packet tunneling protocol.
 *
 * NEEthernetTunnelProvider is part of NetworkExtension.framework.
 */
API_AVAILABLE(macos(13.0)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NEEthernetTunnelProvider : NEPacketTunnelProvider

@end

NS_ASSUME_NONNULL_END
