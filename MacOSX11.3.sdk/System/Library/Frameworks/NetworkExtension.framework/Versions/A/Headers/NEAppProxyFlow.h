/*
 * Copyright (c) 2015, 2017-2018, 2020 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <Network/Network.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEAppProxyFlow.h
 * @discussion This file declares the NEAppProxyFlow API. The NEAppProxyFlow API is used to interact with various streams of network data in the context of NEProvider implementations.
 */

@class NWHostEndpoint;
@class NEFlowMetaData;

#if defined(__cplusplus)
#define NEAPPPROXYFLOW_EXPORT extern "C"
#else
#define NEAPPPROXYFLOW_EXPORT extern
#endif

/*!
 * @typedef NEAppProxyFlowError
 * @abstract Flow error codes
 */
typedef NS_ENUM(NSInteger, NEAppProxyFlowError) {
	/*! @const NEAppProxyFlowErrorNotOpen The flow is not fully open. */
	NEAppProxyFlowErrorNotConnected = 1,
	/*! @const NEAppProxyFlowErrorPeerReset The remote peer reset the flow. */
	NEAppProxyFlowErrorPeerReset = 2,
	/*! @const NEAppProxyFlowErrorHostUnreachable The remote peer is unreachable. */
	NEAppProxyFlowErrorHostUnreachable = 3,
	/*! @const NEAppProxyFlowErrorInvalidArgument An invalid argument was passed to one of the NEAppProxyFlow methods. */
	NEAppProxyFlowErrorInvalidArgument = 4,
	/*! @const NEAppProxyFlowErrorAborted The flow was aborted. */
	NEAppProxyFlowErrorAborted = 5,
	/*! @const NEAppProxyFlowErrorRefused The flow was disallowed. */
	NEAppProxyFlowErrorRefused = 6,
	/*! @const NEAppProxyFlowErrorTimedOut The flow timed out. */
	NEAppProxyFlowErrorTimedOut = 7,
	/*! @const NEAppProxyFlowErrorInternal An internal error occurred. */
	NEAppProxyFlowErrorInternal = 8,
	/*! @const NEAppProxyFlowErrorDatagramTooLarge An attempt was made to write a datagram that is larger than the socket's receive window */
	NEAppProxyFlowErrorDatagramTooLarge API_AVAILABLE(macos(10.11), ios(9.3)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED = 9,
	/*! @const NEAppProxyFlowErrorReadAlreadyPending A read operation on the flow is already pending */
	NEAppProxyFlowErrorReadAlreadyPending API_AVAILABLE(macos(10.11), ios(9.3)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED = 10,
} API_AVAILABLE(macos(10.11), ios(9.0));

/*! @const NEAppProxyErrorDomain The NEAppProxyFlow error domain */
NEAPPPROXYFLOW_EXPORT NSString * const NEAppProxyErrorDomain API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @interface NEAppProxyFlow
 * @discussion The NEAppProxyFlow class is an abstract base class that declares the programmatic interface for a flow of network data.
 *
 * NEAppProxyFlow is part of NetworkExtension.framework.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface NEAppProxyFlow : NSObject

/*!
 * @method openWithLocalEndpoint:completionHandler:
 * @discussion This function is used by an NEProvider implementation to indicate that it is ready to handle flow data.
 * @param localEndpoint The address and port that should be used as the local endpoint of the socket associated with this flow. If the source application already specifed a local endpoint by binding the socket then this parameter is ignored.
 * @param completionHandler A block that is called when the process of opening flow is complete. A nil value passed to this block indicates that the flow was opened successfully. A non-nil NSError value indicates that the flow failed to open successfully.
 */
- (void)openWithLocalEndpoint:(nullable NWHostEndpoint *)localEndpoint completionHandler:(void (^)(NSError *__nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method closeReadWithError:
 * @discussion This function is used by an NEProvider implementation to indicate that it does not want to receive any more data from the flow.
 * @param error An error in NEAppProxyErrorDomain that should be passed to the flow's source application.
 */
- (void)closeReadWithError:(nullable NSError *)error API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method closeWriteWithError:
 * @discussion This functions is used by an NEProvider implementation to indicate that it does not have any more data to write to the flow.
 * @param error An error in NEAppProxyErrorDomain that should be passed to the flow's source application.
 */
- (void)closeWriteWithError:(nullable NSError *)error API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method setMetadata:
 * @discussion Set the flow's NEFlowMetaData object in an nw_parameters_t object. The nw_parameters_t object can then be used to create a connection that transparently proxies the flow's
 *     data, and provides accurate source app information to any subsequent NEAppProxyProvider instances that transparently proxy the flow.
 * @param parameters An nw_parameters_t object.
 */
- (void)setMetadata:(nw_parameters_t)parameters API_AVAILABLE(macos(10.15.4)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property metaData
 * @discussion An NEFlowMetaData object containing meta data for the flow.
 */
@property (readonly) NEFlowMetaData *metaData API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

#if OS_OBJECT_USE_OBJC
#define NECOPYNULLABLE (copy, nullable)
#else
#define NECOPYNULLABLE (nullable)
#endif

/*!
 * @property networkInterface
 * @discussion An nw_interface_t containing information about the network interface used by the flow. If the flow's data is transported using a different interface, this property
 *    should be set to that interface.
 */
@property NECOPYNULLABLE nw_interface_t networkInterface API_AVAILABLE(macos(10.15.4), ios(13.4)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property remoteHostname
 * @discussion If the flow was created by passing a hostname to a "connect by name" API such as NSURLSession or Network.framework, this property is set to the
 *     remote hostname.
 */
@property (readonly, nullable) NSString *remoteHostname API_AVAILABLE(macos(11.0), ios(14.2)) API_UNAVAILABLE(tvos, watchos) __WATCHOS_PROHIBITED;

/*!
 * @property isBound
 * @discussion YES if the flow was bound by the application to a specific interface (contained in the networkInterface property), NO otherwise.
 */
@property (readonly) BOOL isBound API_AVAILABLE(macos(11.1), ios(14.3)) API_UNAVAILABLE(tvos, watchos) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END

