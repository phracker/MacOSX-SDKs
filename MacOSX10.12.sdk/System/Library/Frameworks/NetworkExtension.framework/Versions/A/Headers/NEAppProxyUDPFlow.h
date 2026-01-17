/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEAppProxyFlow.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEAppProxyUDPFlow.h
 * @discussion This file declares the NEAppProxyUDPFlow API. The NEAppProxyUDPFlow API is used by NEAppProxyProvider implementations to proxy the payload of UDP datagrams.
 */

@class NWEndpoint;

/*!
 * @interface NEAppProxyUDPFlow
 * @discussion The NEAppProxyUDPFlow class declares the programmatic interface of an object that is used by NEAppProxyProvider implementations to proxy the payload of UDP datagrams.
 *
 * NEAppProxyUDPFlow is part of NetworkExtension.framework.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEAppProxyUDPFlow : NEAppProxyFlow

/*!
 * @method readDatagramWithCompletionHandler:
 * @discussion Read a datagram from the flow.
 * @param completionHandler A block that will be executed when datagrams have been read from the flow. The block takes the datagrams that were read, the destination endpoints of the datagrams, and an NSError. If an error occurred while reading then the error parameter will be non-nil. If the datagrams and remoteEndpoints arrays are non-nill but 
 */
- (void)readDatagramsWithCompletionHandler:(void (^)(NSArray<NSData *> * __nullable datagrams, NSArray<NWEndpoint *> * __nullable remoteEndpoints,  NSError * __nullable error))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @method writeDatagram:sentByEndpoint:completionHandler:
 * @discussion Write a datagram to the flow.
 * @param datagrams An array of NSData objects containing the data to be written.
 * @param remoteEndpoints The source endpoints of the datagrams.
 * @param completionHandler A block that will be executed when the datagrams have been written to the corresponding socket's receive buffer.
 */
- (void)writeDatagrams:(NSArray<NSData *> *)datagrams sentByEndpoints:(NSArray<NWEndpoint *> *)remoteEndpoints completionHandler:(void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @property localEndpoint
 * @discussion An NWEndpoint object containing the local endpoint of the flow's corresponding socket.
 */
@property (readonly, nullable) NWEndpoint *localEndpoint NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

