/*
 * Copyright (c) 2015, 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

@class NEPacket;

/*!
 * @file NEPacketTunnelFlow.h
 * @discussion This file declares the NEPacketTunnelFlow API. The NEPacketTunnelFlow is used by NEPacketTunnelProvider implementations to tunnel IP packets.
 */

/*!
 * @interface NEPacketTunnelFlow
 * @discussion The NEPacketTunnelFlow class declares the programmatic interface of an object that is used by NEPacketTunnelProvider implementations to tunnel IP packets.
 *
 * NEPacketTunnelFlow is part of NetworkExtension.framework
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEPacketTunnelFlow : NSObject

/*!
 * @method readPacketsWithCompletionHandler:
 * @discussion Read available IP packets from the flow.
 * @param completionHandler A block that will be executed to handle the packets. This block takes an array of NSData objects and an array of NSNumber objects. The NSData and NSNumber in corresponding indicies in the array represent one packet. If after handling the packets the caller wants to read more packets then the caller must call this method again.
 */
- (void)readPacketsWithCompletionHandler:(void (^)(NSArray<NSData *> *packets, NSArray<NSNumber *> *protocols))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method writePackets:completionHandler:
 * @discussion Write multiple IP packets to the flow.
 * @param packets An array of NSData objects, each containing packet data to be written.
 * @param protocols An array of NSNumber objects. Each number contains the protocol of the packet in the corresponding index in the packets array.
 */
- (BOOL)writePackets:(NSArray<NSData *> *)packets withProtocols:(NSArray<NSNumber *> *)protocols API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method readPacketObjectsWithCompletionHandler:
 * @discussion Read available IP packets from the flow.
 * @param completionHandler A block that will be executed to handle the packets. This block takes an array of NEPacket objects. If after handling the packets the caller wants to read more packets then the caller must call this method again.
 */
- (void)readPacketObjectsWithCompletionHandler:(void (^)(NSArray<NEPacket *> *packets))completionHandler API_AVAILABLE(macos(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method writePacketObjects:
 * @discussion Write multiple IP packets to the flow.
 * @param packets An array of NEPacket objects, each containing packet data and protocol family to be written.
 */
- (BOOL)writePacketObjects:(NSArray<NEPacket *> *)packets API_AVAILABLE(macos(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

