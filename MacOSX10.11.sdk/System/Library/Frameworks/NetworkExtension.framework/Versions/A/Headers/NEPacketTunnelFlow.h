/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

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
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEPacketTunnelFlow : NSObject

/*!
 * @method readPacketsWithCompletionHandler:
 * @discussion Read available IP packets from the flow.
 * @param completionHandler A block that will be executed to handle the packets. This block takes an array of NSData objects and an array of NSNumber objects. The NSData and NSNumber in corresponding indicies in the array represent one packet. If after handling the packets the caller wants to read more packets then the caller must call this method again.
 */
- (void)readPacketsWithCompletionHandler:(void (^)(NSArray<NSData *> *packets, NSArray<NSNumber *> *protocols))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @method writePackets:completionHandler:
 * @discussion Write multiple IP packets to the flow.
 * @param packets An array of NSData objects, each containing packet data to be written.
 * @param protocols An array of NSNumber objects. Each number contains the protocol of the packet in the corresponding index in the packets array.
 */
- (BOOL)writePackets:(NSArray<NSData *> *)packets withProtocols:(NSArray<NSNumber *> *)protocols NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

