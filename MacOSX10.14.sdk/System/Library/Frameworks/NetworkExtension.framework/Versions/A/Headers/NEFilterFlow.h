/*
 * Copyright (c) 2015, 2016, 2018 Apple Inc.
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
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NEFilterFlow : NSObject <NSSecureCoding,NSCopying>
/*!
 * @property URL
 * @discussion The flow's HTTP request URL. Will be nil if the flow did not originate from WebKit.
 */
@property (readonly, nullable) NSURL *URL API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property sourceAppUniqueIdentifier
 * @discussion A byte string that uniquely identifies the binary for each build of the source application of the flow.
 */
@property (readonly, nullable) NSData *sourceAppUniqueIdentifier API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property sourceAppIdentifier
 * @discussion A string containing the identifier of the source application of the flow. This identifier stays the same for all versions and builds of the application. This identifier is unique among all applications.
 */
@property (readonly, nullable) NSString *sourceAppIdentifier API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property sourceAppVersion
 * @discussion The short version string of the source application. Will be nil if the app info is unavailable.
 */
@property (readonly, nullable) NSString *sourceAppVersion API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

@end

/*!
 * @interface NEFilterBrowserFlow
 * @discussion The NEFilterBrowserFlow class declares the programmatic interface of an object that represents a flow of network data to be filtered, which is originated from NEFilterSource.
 *
 * NEFilterBrowserFlow is part of NetworkExtension.framework
 */
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NEFilterBrowserFlow :  NEFilterFlow <NSSecureCoding,NSCopying>
/*!
 *	@property request
 *	@discussion The NSURLRequest of the flow. This property is always nil for the control providers.
 */
@property (readonly, nullable) NSURLRequest *request API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 *	@property response
 *	@discussion The NSURLResponse of the flow. This will be nil until the request is sent to the server and the response headers are received. And this property is always nil for the control providers.
 */
@property (readonly, nullable) NSURLResponse *response API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);
/*!
 *	@property parentURL
 *	@discussion The parent URL for the current flow which is created to load the sub frames because the flow with the parent URL was allowed. Will be nil if the parent flow does not exist.
 */
@property (readonly, nullable) NSURL *parentURL API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);
@end

/*!
 * @interface NEFilterSocketFlow
 * @discussion The NEFilterSocketFlow class declares the programmatic interface of an object that represents a flow of network data to be filtered, which is originated from the socket.
 *
 * NEFilterSocketFlow is part of NetworkExtension.framework
 */
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NEFilterSocketFlow : NEFilterFlow <NSSecureCoding,NSCopying>
/*!
 * @property remoteEndpoint
 * @discussion The flow's remote endpoint. This endpoint object may be nil when [NEFilterDataProvider handleNewFlow:] is invoked and if so will be populated upon receiving network data.
		In such a case, filtering on the flow may still be performed based on its socket type, socket family or socket protocol.
 */
@property (readonly, nullable) NWEndpoint *remoteEndpoint API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property localEndpoint
 * @discussion The flow's local endpoint. This endpoint object may be nil when [NEFilterDataProvider handleNewFlow:] is invoked and if so will be populated upon receiving network data.
		In such a case, filtering on the flow may still be performed based on its socket type, socket family or socket protocol.
 */
@property (readonly, nullable) NWEndpoint *localEndpoint API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 *	@property socketFamily
 *	@discussion Socket family of the socket flow, such as PF_INET.
 */
@property int socketFamily API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 *	@property socketType
 *	@discussion Socket type of the socket flow, such as SOCK_STREAM.
 */
@property int socketType API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 *	@property socketProtocol
 *	@discussion Socket protocol of the socket flow, such as IPPROTO_TCP.
 */
@property int socketProtocol API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);
@end

NS_ASSUME_NONNULL_END

