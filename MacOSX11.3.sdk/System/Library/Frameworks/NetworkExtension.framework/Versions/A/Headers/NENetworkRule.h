/*
 * Copyright (c) 2019 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NENetworkRule.h
 * @discussion This file declares the NENetworkRule API. The NENetworkRule API is used to specify a rule that matches network traffic.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @typedef NENetworkRuleProtocol
 * @abstract IP protocols
 */
typedef NS_ENUM(NSInteger, NENetworkRuleProtocol) {
	/*! @const NENetworkRuleProtocolAny Matches TCP and UDP traffic */
	NENetworkRuleProtocolAny = 0,
	/*! @const NENetworkRuleProtocolTCP Matches TCP traffic */
	NENetworkRuleProtocolTCP = 1,
	/*! @const NENetworkRuleProtocolUDP Matches UDP traffic */
	NENetworkRuleProtocolUDP = 2,
} NS_SWIFT_NAME(NENetworkRule.Protocol) API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @typedef NETrafficDirection
 * @abstract The direction of network traffic
 */
typedef NS_ENUM(NSInteger, NETrafficDirection) {
	/*! @const NETrafficDirectionAny Any direction */
	NETrafficDirectionAny = 0,
	/*! @const NETrafficDirectionInbound Inbound direction */
	NETrafficDirectionInbound = 1,
	/*! @const NETrafficDirectionOutbound Outbound direction */
	NETrafficDirectionOutbound = 2,
} API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

@class NWHostEndpoint;

/*!
 * @interface NENetworkRule
 * @discussion The NENetworkRule class declares the programmatic interface of an object that contains a specification of a rule that matches the attributes of network traffic.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED
@interface NENetworkRule : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithDestinationNetwork:prefix:protocol
 * @discussion Initialize a newly-allocated NENetworkRule object that matches network traffic destined for a host within a specific network.
 * @param networkEndpoint An endpoint object that contains the port and address or network that the rule matches. This endpoint must contain an address, not a hostname.
 *        If the address is a wildcard address (0.0.0.0 or ::) then the rule will match all destinations except for loopback (127.0.0.1 or ::1). To match loopback traffic set the address to the loopback address.
 *        If the port string of the endpoint is "0" or is the empty string, then the rule will match traffic on any port destined for the given address or network.
 * @param destinationPrefix An integer that in combination with the address in the endpoint specifies the destination network that the rule matches.
 * @param protocol A NENetworkRuleProtocol value indicating the protocol that the rule matches.
 * @return The initialized NENetworkRule instance.
 */
- (instancetype)initWithDestinationNetwork:(NWHostEndpoint *)networkEndpoint prefix:(NSUInteger)destinationPrefix protocol:(NENetworkRuleProtocol)protocol API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @method initWithDestinationHost:protocol:
 * @discussion Initialize a newly-allocated NENetworkRule object that matches network traffic destined for a host within a specific DNS domain.
 * @param hostEndpoint An endpoint object that contains the port and hostname or domain that the rule matches. This endpoint must contain a hostname, not an address.
 *    If the port string of the NWHostEndpoint is "0" or is the empty string, then the rule will match traffic on any port destined for the given hostname or domain.
 *    If the hostname string of the endpoint consists of a single label, then the rule will match traffic destined to the specific host with that single label as its name.
 *    If the hostname string of the endpoint consists of 2 or more labels, then the rule will match traffic destined to hosts within the domain specified by the hostname string.
 *    Examples:
 *        [[NENetworkRule alloc] initWithDestinationHost:[NWHostEndpoint endpointWithHostname:@"com" port:@"0"] protocol:NENetworkRuleProtocolAny] - matches all TCP and UDP traffic to the host named "com".
 *        [[NENetworkRule alloc] initWithDestinationHost:[NWHostEndpoint endpointWithHostname:@"example.com" port:@"0"] protocol:NENetworkRuleProtocolAny] - matches all TCP and UDP traffic to hosts in the "example.com" DNS domain, including all DNS queries for names in the example.com DNS domain.
 *        [[NENetworkRule alloc] initWithDestinationHost:[NWHostEndpoint endpointWithHostname:@"example.com" port:@"53"] protocol:NENetworkRuleProtocolAny] - matches all DNS queries/responses for hosts in the "example.com" domain.
 *        [[NENetworkRule alloc] initWithDestinationHost:[NWHostEndpoint endpointWithHostname:@"example.com" port:@"443"] protocol:NENetworkRuleProtocolTCP] - matches all TCP port 443 traffic to hosts in the "example.com" domain.
 * @param protocol A NENetworkRuleProtocol value indicating the protocol that the rule matches.
 * @return The initialized NENetworkRule instance.
 */
- (instancetype)initWithDestinationHost:(NWHostEndpoint *)hostEndpoint protocol:(NENetworkRuleProtocol)protocol API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @method initWithRemoteNetwork:prefix:localNetwork:prefix:interface:protocol:direction:
 * @discussion Initialize a newly-allocated NENetworkRule object that matches traffic by remote network, local network, protocol, and direction. If both remoteNetwork and localNetwork are nil
 *    then the rule will match all traffic of the given protocol and direction, except for loopback traffic. To match loopback traffic create a NENetworkRule with remoteNetwork and/or localNetwork properties that
 *    explicitly match traffic to the loopback address (127.0.0.1 or ::1).
 * @param remoteNetwork An endpoint object that contains the remote port and the remote address or network that the rule matches. This endpoint must contain an address, not a hostname.
 *    If the address is a wildcard address (0.0.0.0 or ::) then the rule will match all destinations except for loopback (127.0.0.1 or ::1). To match loopback traffic set the address to the loopback address.
 *    If the port string of the endpoint is "0" or is the empty string, then the rule will match traffic on any port coming from the remote network.
 *    Pass nil to cause the rule to match any remote network.
 * @param remotePrefix An integer that in combination with the address in remoteNetwork specifies the remote network that the rule matches.
 * @param localNetwork An endpoint object that contains the local port and the local address or network that the rule matches. This endpoint must contain an address, not a hostname.
 *    If the address is a wildcard address (0.0.0.0 or ::) then the rule will match all local networks except for loopback (127.0.0.1 or ::1). To match loopback traffic set the address to the loopback address.
 *    If the port string of the endpoint is "0" or is the empty string, then the rule will match traffic on any port coming from the local network.
 *    Pass nil to cause the rule to match any local network.
 * @param localPrefix An integer that in combination with the address in localNetwork specifies the local network that the rule matches. This parameter
 *    is ignored if localNetwork is nil.
 * @param protocol A NENetworkRuleProtocol value indicating the protocol that the rule matches.
 * @param direction A NETrafficDirection value indicating the direction of network traffic that the rule matches.
 * @return The initialized NENetworkRule instance.
 */
- (instancetype)initWithRemoteNetwork:(nullable NWHostEndpoint *)remoteNetwork
						 remotePrefix:(NSUInteger)remotePrefix
						 localNetwork:(nullable NWHostEndpoint *)localNetwork
						  localPrefix:(NSUInteger)localPrefix
							 protocol:(NENetworkRuleProtocol)protocol
							direction:(NETrafficDirection)direction API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property matchRemoteEndpoint
 * @discussion The remote endpoint that the rule matches.
 */
@property (readonly, nullable) NWHostEndpoint *matchRemoteEndpoint API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property matchRemotePrefix
 * @discussion A number that specifies the remote sub-network that the rule matches. This property is set to NSNotFound for rules where matchRemoteEndpoint does not contain an IP address.
 */
@property (readonly) NSUInteger matchRemotePrefix API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property matchLocalNetwork
 * @discussion The local network that the rule matches.
 */
@property (readonly, nullable) NWHostEndpoint *matchLocalNetwork API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property matchLocalPrefix
 * @discussion A number that specifies the local sub-network that the rule matches. This property is set to NSNotFound for rules with a nil matchLocalNetwork property.
 */
@property (readonly) NSUInteger matchLocalPrefix API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property matchProtocol
 * @discussion A NENetworkRuleProtocol value containing the protocol that the rule matches.
 */
@property (readonly) NENetworkRuleProtocol matchProtocol API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property matchDirection
 * @discussion A NETrafficDirection value indicating the network traffic direction that the rule matches.
 */
@property (readonly) NETrafficDirection matchDirection API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
