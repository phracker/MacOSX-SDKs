/*
 * Copyright (c) 2019 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <Network/Network.h>

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
} NS_SWIFT_NAME(NENetworkRule.Protocol) API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

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
} API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(watchos, tvos);

@class NWHostEndpoint;

/*!
 * @interface NENetworkRule
 * @discussion The NENetworkRule class declares the programmatic interface of an object that contains a specification of a rule that matches the attributes of network traffic.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NENetworkRule : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithDestinationNetworkEndpoint:prefix:protocol:
 * @discussion Initialize a newly-allocated NENetworkRule object that matches network traffic destined for a host within a specific network.
 * @param networkEndpoint An endpoint object that contains the port and address or network that the rule matches. This endpoint must contain an address, not a hostname.
 *        If the address is a wildcard address (0.0.0.0 or ::) then the rule will match all destinations except for loopback (127.0.0.1 or ::1). To match loopback traffic set the address to the loopback address.
 *        If the port string of the endpoint is "0" or is the empty string, then the rule will match traffic on any port destined for the given address or network.
 * @param destinationPrefix An integer that in combination with the address in the endpoint specifies the destination network that the rule matches.
 * @param protocol A NENetworkRuleProtocol value indicating the protocol that the rule matches.
 * @return The initialized NENetworkRule instance.
 */
- (instancetype)initWithDestinationNetworkEndpoint:(nw_endpoint_t)networkEndpoint prefix:(NSUInteger)destinationPrefix protocol:(NENetworkRuleProtocol)protocol API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos, visionos);

/*!
 * @method initWithDestinationNetwork:prefix:protocol:
 * @discussion Initialize a newly-allocated NENetworkRule object that matches network traffic destined for a host within a specific network.
 * @param networkEndpoint An endpoint object that contains the port and address or network that the rule matches. This endpoint must contain an address, not a hostname.
 *        If the address is a wildcard address (0.0.0.0 or ::) then the rule will match all destinations except for loopback (127.0.0.1 or ::1). To match loopback traffic set the address to the loopback address.
 *        If the port string of the endpoint is "0" or is the empty string, then the rule will match traffic on any port destined for the given address or network.
 * @param destinationPrefix An integer that in combination with the address in the endpoint specifies the destination network that the rule matches.
 * @param protocol A NENetworkRuleProtocol value indicating the protocol that the rule matches.
 * @return The initialized NENetworkRule instance.
 */
- (instancetype)initWithDestinationNetwork:(NWHostEndpoint *)networkEndpoint prefix:(NSUInteger)destinationPrefix protocol:(NENetworkRuleProtocol)protocol API_DEPRECATED_WITH_REPLACEMENT("initWithDestinationNetworkEndpoint:prefix:protocol:", macos(10.15, 15.0)) API_DEPRECATED_WITH_REPLACEMENT("initWithDestinationNetworkEndpoint:prefix:protocol:", ios(13.0, 18.0), watchos(6.0, 11.0), tvos(13.0, 18.0), visionos(1.0, 2.0));

/*!
 * @method initWithDestinationHostEndpoint:protocol:
 * @discussion Initialize a newly-allocated NENetworkRule object that matches network traffic destined for a host within a specific DNS domain.
 * @param hostEndpoint An endpoint object that contains the port and hostname or domain that the rule matches. This endpoint must contain a hostname, not an address.
 *    If the port string of the `nw_endpoint_t` is "0" or is the empty string, then the rule will match traffic on any port destined for the given hostname or domain.
 *    If the hostname string of the endpoint consists of a single label, then the rule will match traffic destined to the specific host with that single label as its name.
 *    If the hostname string of the endpoint consists of 2 or more labels, then the rule will match traffic destined to hosts within the domain specified by the hostname string.
 *    Examples:
 *        [[NENetworkRule alloc] initWithDestinationHost:nw_endpoint_create_host("com", "0") protocol:NENetworkRuleProtocolAny] - matches all TCP and UDP traffic to the host named "com".
 *        [[NENetworkRule alloc] initWithDestinationHost:nw_endpoint_create_host("example.com", "0") protocol:NENetworkRuleProtocolAny] - matches all TCP and UDP traffic to hosts in the "example.com" DNS domain, including all DNS queries for names in the example.com DNS domain.
 *        [[NENetworkRule alloc] initWithDestinationHost:nw_endpoint_create_host("example.com", "53") protocol:NENetworkRuleProtocolAny] - matches all DNS queries/responses for hosts in the "example.com" domain.
 *        [[NENetworkRule alloc] initWithDestinationHost:nw_endpoint_create_host("example.com", "443") protocol:NENetworkRuleProtocolTCP] - matches all TCP port 443 traffic to hosts in the "example.com" domain.
 * @param protocol A NENetworkRuleProtocol value indicating the protocol that the rule matches.
 * @return The initialized NENetworkRule instance.
 */
- (instancetype)initWithDestinationHostEndpoint:(nw_endpoint_t)hostEndpoint protocol:(NENetworkRuleProtocol)protocol API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos, visionos);

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
- (instancetype)initWithDestinationHost:(NWHostEndpoint *)hostEndpoint protocol:(NENetworkRuleProtocol)protocol API_DEPRECATED_WITH_REPLACEMENT("initWithDestinationHostEndpoint:protocol:", macos(10.15, 15.0)) API_DEPRECATED_WITH_REPLACEMENT("initWithDestinationHostEndpoint:protocol:", ios(13.0, 18.0), watchos(6.0, 11.0), tvos(13.0, 18.0), visionos(1.0, 2.0));

/*!
 * @method initWithRemoteNetworkEndpoint:remotePrefix:localNetworkEndpoint:localPrefix:protocol:direction:
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
- (instancetype)initWithRemoteNetworkEndpoint:(nullable nw_endpoint_t)remoteNetwork
								 remotePrefix:(NSUInteger)remotePrefix
						 localNetworkEndpoint:(nullable nw_endpoint_t)localNetwork
								  localPrefix:(NSUInteger)localPrefix
									 protocol:(NENetworkRuleProtocol)protocol
									direction:(NETrafficDirection)direction API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos, visionos);

/*!
 * @method initWithRemoteNetwork:remotePrefix:localNetwork:localPrefix:protocol:direction:
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
							direction:(NETrafficDirection)direction API_DEPRECATED_WITH_REPLACEMENT("initWithRemoteNetworkEndpoint:remotePrefix:localNetworkEndpoint:localPrefix:protocol:direction:", macos(10.15, 15.0)) API_DEPRECATED_WITH_REPLACEMENT("initWithRemoteNetworkEndpoint:remotePrefix:localNetworkEndpoint:localPrefix:protocol:direction:", ios(13.0, 18.0), watchos(6.0, 11.0), tvos(13.0, 18.0), visionos(1.0, 2.0));

/*!
 * @property matchRemoteHostOrNetworkEndpoint
 * @discussion The remote endpoint that the rule matches.
 */
@property (readonly, nullable) nw_endpoint_t matchRemoteHostOrNetworkEndpoint API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos, visionos);

/*!
 * @property matchRemoteEndpoint
 * @discussion The remote endpoint that the rule matches.
 */
@property (readonly, nullable) NWHostEndpoint *matchRemoteEndpoint API_DEPRECATED_WITH_REPLACEMENT("matchRemoteHostOrNetworkEndpoint", macos(10.15, 15.0)) API_DEPRECATED_WITH_REPLACEMENT("matchRemoteHostOrNetworkEndpoint", ios(13.0, 18.0), watchos(6.0, 11.0), tvos(13.0, 18.0), visionos(1.0, 2.0));

/*!
 * @property matchRemotePrefix
 * @discussion A number that specifies the remote sub-network that the rule matches. This property is set to NSNotFound for rules where matchRemoteEndpoint does not contain an IP address.
 */
@property (readonly) NSUInteger matchRemotePrefix API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property matchLocalNetworkEndpoint
 * @discussion The local network that the rule matches.
 */
@property (readonly, nullable) nw_endpoint_t matchLocalNetworkEndpoint API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos, visionos);

/*!
 * @property matchLocalNetwork
 * @discussion The local network that the rule matches.
 */
@property (readonly, nullable) NWHostEndpoint *matchLocalNetwork API_DEPRECATED_WITH_REPLACEMENT("matchLocalNetworkEndpoint", macos(10.15, 15.0)) API_DEPRECATED_WITH_REPLACEMENT("matchLocalNetworkEndpoint", ios(13.0, 18.0), watchos(6.0, 11.0), tvos(13.0, 18.0), visionos(1.0, 2.0));

/*!
 * @property matchLocalPrefix
 * @discussion A number that specifies the local sub-network that the rule matches. This property is set to NSNotFound for rules with a nil matchLocalNetwork property.
 */
@property (readonly) NSUInteger matchLocalPrefix API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property matchProtocol
 * @discussion A NENetworkRuleProtocol value containing the protocol that the rule matches.
 */
@property (readonly) NENetworkRuleProtocol matchProtocol API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property matchDirection
 * @discussion A NETrafficDirection value indicating the network traffic direction that the rule matches.
 */
@property (readonly) NETrafficDirection matchDirection API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

@end

NS_ASSUME_NONNULL_END
