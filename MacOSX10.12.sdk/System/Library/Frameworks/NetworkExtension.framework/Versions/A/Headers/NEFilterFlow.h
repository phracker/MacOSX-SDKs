/*
 * Copyright (c) 2015, 2016 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 @define NEFilterFlowBytesMax The maximum number of bytes to be passed or peeked for a flow.
 This value indicates that all upcoming bytes should be passed when used as a pass value, and
 indicates that the flow should peek as many bytes as possible when used as a peek value.
 */
#define	NEFilterFlowBytesMax	UINT64_MAX

/*!
 * @file NEFilterFlow.h
 * @discussion This file declares the NEFilterFlow API.
 */

@class NWEndpoint;

/*!
 * @interface NEFilterFlow
 * @discussion The NEFilterFlow class declares the programmatic interface of an object that represents a flow of network data to be filtered.
 *
 * NEFilterFlow is part of NetworkExtension.framework
 */
NS_CLASS_AVAILABLE(NA, 9_0)
@interface NEFilterFlow : NSObject <NSSecureCoding,NSCopying>
/*!
 * @property URL
 * @discussion The flow's HTTP request URL. Will be nil if the flow did not originate from WebKit.
 */
@property (readonly, nullable) NSURL *URL NS_AVAILABLE(NA, 9_0);
@end

/*!
 * @interface NEFilterBrowserFlow
 * @discussion The NEFilterBrowserFlow class declares the programmatic interface of an object that represents a flow of network data to be filtered, which is originated from NEFilterSource.
 *
 * NEFilterBrowserFlow is part of NetworkExtension.framework
 */
NS_CLASS_AVAILABLE(NA, 9_0)
@interface NEFilterBrowserFlow :  NEFilterFlow <NSSecureCoding,NSCopying>
/*!
 *	@property request
 *	@discussion The NSURLRequest of the flow.
 */
@property (readonly) NSURLRequest *request NS_AVAILABLE(10_11, 9_0);

/*!
 *	@property response
 *	@discussion The NSURLResponse of the flow. This will be nil until the request is sent to the server and the response headers are received.
 */
@property (readonly, nullable) NSURLResponse *response NS_AVAILABLE(10_11, 9_0);
/*!
 *	@property parentURL
 *	@discussion The parent URL for the current flow which is created to load the sub frames because the flow with the parent URL was allowed. Will be nil if the parent flow does not exist.
 */
@property (readonly, nullable) NSURL *parentURL NS_AVAILABLE(NA, 9_0);
@end

/*!
 * @interface NEFilterSocketFlow
 * @discussion The NEFilterSocketFlow class declares the programmatic interface of an object that represents a flow of network data to be filtered, which is originated from the socket.
 *
 * NEFilterSocketFlow is part of NetworkExtension.framework
 */
NS_CLASS_AVAILABLE(NA, 9_0)
@interface NEFilterSocketFlow : NEFilterFlow <NSSecureCoding,NSCopying>
/*!
 * @property remoteEndpoint
 * @discussion The flow's remote endpoint. This endpoint object may be nil when [NEFilterDataProvider handleNewFlow:] is invoked and if so will be populated upon receiving network data.
		In such a case, filtering on the flow may still be performed based on its socket type, socket family or socket protocol.
 */
@property (readonly, nullable) NWEndpoint *remoteEndpoint NS_AVAILABLE(NA, 9_0);

/*!
 * @property localEndpoint
 * @discussion The flow's local endpoint. This endpoint object may be nil when [NEFilterDataProvider handleNewFlow:] is invoked and if so will be populated upon receiving network data.
		In such a case, filtering on the flow may still be performed based on its socket type, socket family or socket protocol.
 */
@property (readonly, nullable) NWEndpoint *localEndpoint NS_AVAILABLE(NA, 9_0);

/*!
 *	@property socketFamily
 *	@discussion Socket family of the socket flow, such as PF_INET.
 */
@property int socketFamily NS_AVAILABLE(NA, 9_0);

/*!
 *	@property socketType
 *	@discussion Socket type of the socket flow, such as SOCK_STREAM.
 */
@property int socketType NS_AVAILABLE(NA, 9_0);

/*!
 *	@property socketProtocol
 *	@discussion Socket protocol of the socket flow, such as IPPROTO_TCP.
 */
@property int socketProtocol NS_AVAILABLE(NA, 9_0);
@end

NS_ASSUME_NONNULL_END

