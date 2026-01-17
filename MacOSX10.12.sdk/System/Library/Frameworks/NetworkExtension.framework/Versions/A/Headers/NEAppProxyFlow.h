/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

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
	NEAppProxyFlowErrorDatagramTooLarge NS_AVAILABLE(10_11, 9_3) = 9,
	/*! @const NEAppProxyFlowErrorReadAlreadyPending A read operation on the flow is already pending */
	NEAppProxyFlowErrorReadAlreadyPending NS_AVAILABLE(10_11, 9_3) = 10,
} NS_ENUM_AVAILABLE(10_11, 9_0);

/*! @const NEAppProxyErrorDomain The NEAppProxyFlow error domain */
NEAPPPROXYFLOW_EXPORT NSString * const NEAppProxyErrorDomain NS_AVAILABLE(10_11, 9_0);

/*!
 * @interface NEAppProxyFlow
 * @discussion The NEAppProxyFlow class is an abstract base class that declares the programmatic interface for a flow of network data.
 *
 * NEAppProxyFlow is part of NetworkExtension.framework.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEAppProxyFlow : NSObject

/*!
 * @method openWithLocalAddress:completionHandler:
 * @discussion This function is used by an NEProvider implementation to indicate that it is ready to handle flow data.
 * @param localEndpoint The address and port that should be used as the local endpoint of the socket associated with this flow. If the source application already specifed a local endpoint by binding the socket then this parameter is ignored.
 * @param completionHandler A block that is called when the process of opening flow is complete. A nil value passed to this block indicates that the flow was opened successfully. A non-nil NSError value indicates that the flow failed to open successfully.
 */
- (void)openWithLocalEndpoint:(nullable NWHostEndpoint *)localEndpoint completionHandler:(void (^)(NSError *__nullable error))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @method closeReadWithError:
 * @discussion This function is used by an NEProvider implementation to indicate that it does not want to receive any more data from the flow.
 * @param error An error in NEAppProxyErrorDomain that should be passed to the flow's source application.
 */
- (void)closeReadWithError:(nullable NSError *)error NS_AVAILABLE(10_11, 9_0);

/*!
 * @method closeWriteWithError:
 * @discussion This functions is used by an NEProvider implementation to indicate that it does not have any more data to write to the flow.
 * @param error An error in NEAppProxyErrorDomain that should be passed to the flow's source application.
 */
- (void)closeWriteWithError:(nullable NSError *)error NS_AVAILABLE(10_11, 9_0);

/*!
 * @property metaData
 * @discussion An NEFlowMetaData object containing meta data for the flow.
 */
@property (readonly) NEFlowMetaData *metaData NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

