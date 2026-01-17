/*
 * Copyright (c) 2015, 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <Network/Network.h>
#import <NetworkExtension/NEAppProxyFlow.h>

NS_ASSUME_NONNULL_BEGIN

#if OS_OBJECT_USE_OBJC
typedef NSArray<nw_endpoint_t> NWEndpointArray;
#else
typedef NSArray NWEndpointArray;
#endif

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
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEAppProxyUDPFlow : NEAppProxyFlow

/*!
 * @method readDatagramsAndFlowEndpointsWithCompletionHandler:
 * @discussion Read datagrams from the flow.
 * @param completionHandler A block that will be executed when datagrams have been read from the flow. The block takes the datagrams that were read, the destination endpoints of the datagrams, and an NSError. If an error occurred while reading then the error parameter will be non-nil.
 */
- (void)readDatagramsAndFlowEndpointsWithCompletionHandler:(void (^)(NSArray<NSData *> * _Nullable datagrams, NWEndpointArray * _Nullable remoteEndpoints, NSError * _Nullable error))completionHandler NS_SWIFT_DISABLE_ASYNC API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method readDatagramsWithCompletionHandler:
 * @discussion Read datagrams from the flow.
 * @param completionHandler A block that will be executed when datagrams have been read from the flow. The block takes the datagrams that were read, the destination endpoints of the datagrams, and an NSError. If an error occurred while reading then the error parameter will be non-nil.
 */
- (void)readDatagramsWithCompletionHandler:(void (^)(NSArray<NSData *> * _Nullable datagrams, NSArray<NWEndpoint *> * _Nullable remoteEndpoints, NSError * _Nullable error))completionHandler NS_SWIFT_DISABLE_ASYNC API_DEPRECATED_WITH_REPLACEMENT("readDatagramsAndFlowEndpointsWithCompletionHandler:", macos(10.11, 15.0), ios(9.0, 18.0), visionos(1.0, 2.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method writeDatagrams:sentByFlowEndpoints:completionHandler:
 * @discussion Write datagrams to the flow.
 * @param datagrams An array of NSData objects containing the data to be written.
 * @param remoteEndpoints The source endpoints of the datagrams.
 * @param completionHandler A block that will be executed when the datagrams have been written to the corresponding socket's receive buffer.
 */
- (void)writeDatagrams:(NSArray<NSData *> *)datagrams sentByFlowEndpoints:(NWEndpointArray *)remoteEndpoints completionHandler:(void (^)(NSError * _Nullable error))completionHandler API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method writeDatagrams:sentByEndpoint:completionHandler:
 * @discussion Write datagrams to the flow.
 * @param datagrams An array of NSData objects containing the data to be written.
 * @param remoteEndpoints The source endpoints of the datagrams.
 * @param completionHandler A block that will be executed when the datagrams have been written to the corresponding socket's receive buffer.
 */
- (void)writeDatagrams:(NSArray<NSData *> *)datagrams sentByEndpoints:(NSArray<NWEndpoint *> *)remoteEndpoints completionHandler:(void (^)(NSError * _Nullable error))completionHandler API_DEPRECATED_WITH_REPLACEMENT("writeDatagrams:sentByFlowEndpoints:completionHandler:", macos(10.11, 15.0), ios(9.0, 18.0), visionos(1.0, 2.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property localFlowEndpoint
 * @discussion An `nw_endpoint_t` object containing the local endpoint of the flow's corresponding socket.
 */
@property (readonly, nullable) nw_endpoint_t localFlowEndpoint API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property localEndpoint
 * @discussion An NWEndpoint object containing the local endpoint of the flow's corresponding socket.
 */
@property (readonly, nullable) NWEndpoint *localEndpoint API_DEPRECATED_WITH_REPLACEMENT("localFlowEndpoint", macos(10.11, 15.0), ios(9.0, 18.0), visionos(1.0, 2.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

