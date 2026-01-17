/*
 * Copyright (c) 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <Network/Network.h>
#import <NetworkExtension/NEFilterProvider.h>
#import <NetworkExtension/NENetworkRule.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEFilterPacketProvider.h
 * @discussion This file declares the NEFilterPacketProvider API. The NEFilterPacketProvider API is used to implement custom network packet filters.
 *
 * This API is part of NetworkExtension.framework.
 */

@class NEFilterPacketSet;
@class NEPacket;

/*!
 * @interface NEFilterPacketContext
 * @discussion The NEFilterPacketContext class identifies the current filtering context.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NEFilterPacketContext : NSObject
@end

/*!
 * @typedef NEFilterPacketProviderVerdict
 * @abstract Verdict for a packet
 */
typedef NS_ENUM(NSInteger, NEFilterPacketProviderVerdict) {
	/*! @const NEFilterPacketProviderVerdictAllow Allow a packet */
	NEFilterPacketProviderVerdictAllow = 0,
	/*! @const NEFilterPacketProviderVerdictDrop Drop a packet */
	NEFilterPacketProviderVerdictDrop = 1,
	/* @const NEFilterPacketProviderVerdictDelay Delay a packet until a future verdict */
	NEFilterPacketProviderVerdictDelay = 2,
} NS_SWIFT_NAME(NEFilterPacketProvider.Verdict) API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @typedef NEFilterPacketHandler
 * @discussion A block that makes a filtering decision about a network packet.
 * @param context The context of the current packet filter.
 * @param interface The ingress or egress interface of the packet.
 * @param direction The direction of the packet.
 * @param packetBytes The packet bytes.
 * @param packetLength The length of packetBytes.
 * @return A NEFilterPacketProviderVerdict. If the returned verdict is NEFilterPacketProviderVerdictDelay, then the framework assumes that the block already called -[NEFilterPacketProvider delayCurrentPacket] to obtain a reference to the packet.
 */
typedef NEFilterPacketProviderVerdict (^NEFilterPacketHandler)(NEFilterPacketContext *context, _Nonnull nw_interface_t interface, NETrafficDirection direction, const void *packetBytes, const size_t packetLength)
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @interface NEFilterPacketProvider
 * @discussion The NEFilterPacketProvider class declares the programmatic interface for an object that evaluates network packets decisions about whether to block, allow, or delay the packets.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NEFilterPacketProvider : NEFilterProvider

/*!
 * @property packetHandler
 * @discussion A block to be set to handle each packet received or to be sent.  A verdict
 *             to allow, drop or delay must be returned to indicate the treatment of
 *             the packet.  Since there may be multiple filtering sources presenting
 *             frames to the provider, this packet handler may be executed by multiple
 *			   simultaneous threads.  This packet handler must be able to handle execution
 *			   in a multi-threaded environment.
 */
@property (strong, nullable) NEFilterPacketHandler packetHandler API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @method delayCurrentPacket
 * @discussion This function is used to delay a packet currently presented by packetHandler.
 *             This function is only valid within the packetHandler block and a verdict of
 *             NEFilterPacketProviderVerdictDelay must be returned after a packet is delayed.  A delayed
 *             packet will be prevented from continuing its journey through the networking stack until
 *             it is either allowed by calling allow() or is dropped by being released.
 * @param context The context of the current packet filter which is passed to the packetHandler block.
 *		   The packetHandler block must pass this context when calling delayCurrentPacket().
 */
- (NEPacket *)delayCurrentPacket:(NEFilterPacketContext *)context API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @method allowPacket:
 * @discussion This function is used to allow a previously-delayed packet to continue its journey into or out of the networking stack.
 * @param packet A NEPacket object that contains the data of the packet that was previously delayed by the NEFilterPacketProvider.
 */
- (void)allowPacket:(NEPacket *)packet API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

@end

NS_ASSUME_NONNULL_END
