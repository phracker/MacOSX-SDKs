/*
 * Copyright (c) 2016, 2020 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <netinet/in.h>
#import <NetworkExtension/NENetworkRule.h>
#import "NEFilterFlow.h"

NS_ASSUME_NONNULL_BEGIN

@class NEFlowMetaData;

/*!
 * @interface NEPacket
 * @discussion An NEPacket object represents the data, protocol family, and metadata associated with an IP packet. 
 *	These packets are used to read and write on an NEPacketTunnelFlow.
 *
 * NEPacket is part of NetworkExtension.framework
 *
 * Instances of this class are thread safe.
 */
__attribute__((visibility("default")))
API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface NEPacket : NSObject <NSCopying,NSSecureCoding>

/*!
 * @method initWithData:protocolFamily:
 * @discussion Initializes a new NEPacket object with data and protocol family.
 * @param data The content of the packet.
 * @param protocolFamily The protocol family of the packet (such as AF_INET or AF_INET6).
 */
- (instancetype)initWithData:(NSData *)data
			  protocolFamily:(sa_family_t)protocolFamily API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property data
 * @discussion The data content of the packet.
 */
@property (readonly, copy) NSData *data API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property protocolFamily
 * @discussion The protocol family of the packet (such as AF_INET or AF_INET6).
 */
@property (readonly) sa_family_t protocolFamily API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property direction
 * @discussion The direction of the packet.
 */
@property (readonly) NETrafficDirection direction API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property metadata
 * @discussion Metadata about the source application and flow for this packet.
 *	This property will only be non-nil when the routing method for the NEPacketTunnelProvider
 *	is NETunnelProviderRoutingMethodSourceApplication.
 */
@property (readonly, nullable) NEFlowMetaData *metadata API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
