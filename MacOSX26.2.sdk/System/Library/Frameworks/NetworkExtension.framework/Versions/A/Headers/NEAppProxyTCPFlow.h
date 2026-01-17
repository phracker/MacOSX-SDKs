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

/*!
 * @file NEAppProxyTCPFlow
 * @discussion This file declares the NEAppProxyTCPFlow API. The NEAppProxyTCPFlow API is used by NEAppProxyProvider implementations to proxy the payload of TCP connections.
 */

@class NWEndpoint;

/*!
 * @interface NEAppProxyTCPFlow
 * @discussion The NEAppProxyTCPFlow class declares the programmatic interface of an object that is used by NEAppProxyProvider implementations to proxy the payload of TCP connections.
 *
 * NEAppProxyTCPFlow is part of NetworkExtension.framework
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEAppProxyTCPFlow : NEAppProxyFlow

/*!
 * @method readDataWithCompletionHandler:
 * @discussion Read data from the flow.
 * @param completionHandler A block that will be executed when some data is read from the flow. The block is passed either the data that was read or a non-nil error if an error occurred. If data has a length of 0 then no data can be subsequently read from the flow. The completion handler is only called for the single read operation that was initiated by calling this method. If the caller wants to read more data then it should call this method again to schedule another read operation and another execution of the completion handler block.
 */
- (void)readDataWithCompletionHandler:(void (^)(NSData * __nullable data, NSError * __nullable error))completionHandler NS_SWIFT_DISABLE_ASYNC API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method writeData:completionHandler
 * @discussion Write data to the flow.
 * @param data The data to write.
 * @param completionHandler A block that will be executed when the data is written into the associated socket's receive buffer. The caller should use this callback as an indication that it is possible to write more data to the flow without using up excessive buffer memory. If an error occurs while writing the data then a non-nil NSError object is passed to the block.
 */
- (void)writeData:(NSData *)data withCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property remoteFlowEndpoint
 * @discussion An `nw_endpoint_t` object containing information about the intended remote endpoint of the flow.
 */
@property (readonly) nw_endpoint_t remoteFlowEndpoint API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property remoteEndpoint
 * @discussion An NWEndpoint object containing information about the intended remote endpoint of the flow.
 */
@property (readonly) NWEndpoint *remoteEndpoint API_DEPRECATED_WITH_REPLACEMENT("remoteFlowEndpoint", macos(10.11, 15.0), ios(9.0, 18.0), visionos(1.0, 2.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

