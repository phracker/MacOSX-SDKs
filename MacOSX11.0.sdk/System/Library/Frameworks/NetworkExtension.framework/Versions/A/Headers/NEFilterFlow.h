/*
 * Copyright (c) 2015, 2016, 2018, 2020 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NENetworkRule.h>

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
API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface NEFilterFlow : NSObject <NSSecureCoding,NSCopying>
/*!
 * @property URL
 * @discussion The flow's HTTP request URL. Will be nil if the flow did not originate from WebKit.
 */
@property (readonly, nullable) NSURL *URL API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property sourceAppUniqueIdentifier
 * @discussion A byte string that uniquely identifies the binary for each build of the source application of the flow.
 */
@property (readonly, nullable) NSData *sourceAppUniqueIdentifier API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property sourceAppIdentifier
 * @discussion A string containing the identifier of the source application of the flow. This identifier stays the same for all versions and builds of the application. This identifier is unique among all applications.
 */
@property (readonly, nullable) NSString *sourceAppIdentifier API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property sourceAppVersion
 * @discussion The short version string of the source application. Will be nil if the app info is unavailable.
 */
@property (readonly, nullable) NSString *sourceAppVersion API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 *	@property direction
 *	@discussion Initial direciton of the flow (outgoing or incoming flow)
 */
@property (readonly) NETrafficDirection direction API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 *	@property sourceAppAuditToken
 *	@discussion Audit token of the source application of the flow.
 */
@property (readonly, nullable) NSData *sourceAppAuditToken API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property identifier
 * @discussion The unique identifier of the flow.
 */
@property (readonly) NSUUID *identifier API_AVAILABLE(macos(10.15), ios(13.1)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

@end

/*!
 * @interface NEFilterBrowserFlow
 * @discussion The NEFilterBrowserFlow class declares the programmatic interface of an object that represents a flow of network data to be filtered, which is originated from NEFilterSource.
 *
 * NEFilterBrowserFlow is part of NetworkExtension.framework
 */
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED
@interface NEFilterBrowserFlow : NEFilterFlow <NSSecureCoding,NSCopying>
/*!
 *	@property request
 *	@discussion The NSURLRequest of the flow. This property is always nil for the control providers.
 */
@property (readonly, nullable) NSURLRequest *request API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 *	@property response
 *	@discussion The NSURLResponse of the flow. This will be nil until the request is sent to the server and the response headers are received. And this property is always nil for the control providers.
 */
@property (readonly, nullable) NSURLResponse *response API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;
/*!
 *	@property parentURL
 *	@discussion The parent URL for the current flow which is created to load the sub frames because the flow with the parent URL was allowed. Will be nil if the parent flow does not exist.
 */
@property (readonly, nullable) NSURL *parentURL API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;
@end

/*!
 * @interface NEFilterSocketFlow
 * @discussion The NEFilterSocketFlow class declares the programmatic interface of an object that represents a flow of network data to be filtered, which is originated from the socket.
 *
 * NEFilterSocketFlow is part of NetworkExtension.framework
 */
API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface NEFilterSocketFlow : NEFilterFlow <NSSecureCoding,NSCopying>
/*!
 * @property remoteEndpoint
 * @discussion The flow's remote endpoint. This endpoint object may be nil when [NEFilterDataProvider handleNewFlow:] is invoked and if so will be populated upon receiving network data.
		In such a case, filtering on the flow may still be performed based on its socket type, socket family or socket protocol.
 */
@property (readonly, nullable) NWEndpoint *remoteEndpoint API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property remoteHostname
 * @discussion The flow's remote hostname. This property is only non-nil if the flow was created using Network.framework or NSURLSession.
 */
@property (readonly, nullable) NSString *remoteHostname API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property localEndpoint
 * @discussion The flow's local endpoint. This endpoint object may be nil when [NEFilterDataProvider handleNewFlow:] is invoked and if so will be populated upon receiving network data.
		In such a case, filtering on the flow may still be performed based on its socket type, socket family or socket protocol.
 */
@property (readonly, nullable) NWEndpoint *localEndpoint API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 *	@property socketFamily
 *	@discussion Socket family of the socket flow, such as PF_INET.
 */
@property (readonly) int socketFamily API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 *	@property socketType
 *	@discussion Socket type of the socket flow, such as SOCK_STREAM.
 */
@property (readonly) int socketType API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 *	@property socketProtocol
 *	@discussion Socket protocol of the socket flow, such as IPPROTO_TCP.
 */
@property (readonly) int socketProtocol API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;
@end

NS_ASSUME_NONNULL_END

