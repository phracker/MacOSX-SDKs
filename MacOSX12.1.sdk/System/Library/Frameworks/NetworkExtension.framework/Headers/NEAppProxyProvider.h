/*
 * Copyright (c) 2015, 2017, 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NETunnelProvider.h>

NS_ASSUME_NONNULL_BEGIN

@class NEAppProxyFlow;
@class NEAppProxyUDPFlow;
@class NWEndpoint;

/*!
 * @file NEAppProxyProvider
 * @discussion This file declares the NEAppProxyProvider API. The NEAppProxyProvider is used to implement custom network proxy solutions.
 */

/*!
 * @interface NEAppProxyProvider
 * @discussion The NEAppProxyProvider class declares the programmatic interface for an object that implements the client side of a custom network proxy solution.
 *
 * NEAppProxyProvider is part of NetworkExtension.framework
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface NEAppProxyProvider : NETunnelProvider

/*!
 * @method startProxyWithOptions:completionHandler:
 * @discussion This function is called by the framework when a new proxy instance is being created. Subclasses must override this method to perform whatever steps are necessary to ready the proxy for handling flows of network data.
 * @param options A dictionary containing keys and values passed by the provider's containing app. If the containing app did not start the proxy then this parameter will be nil.
 * @param completionHandler A block that must be called when the process of starting the proxy is complete. If the proxy cannot be started then the subclass' implementation of this method must pass a non-nil NSError object to this block. A value of nil passed to the completion handler indicates that the proxy was successfully started.
 */
- (void)startProxyWithOptions:(nullable NSDictionary<NSString *,id> *)options completionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method stopProxyWithReason:completionHandler:
 * @discussion This function is called by the framework when the proxy is being stopped. Subclasses must override this method to perform whatever steps are necessary to stop the proxy.
 * @param reason An NEProviderStopReason indicating why the proxy is being stopped.
 * @param completionHandler A block that must be called when the proxy is completely stopped.
 */
- (void)stopProxyWithReason:(NEProviderStopReason)reason completionHandler:(void (^)(void))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method cancelProxyWithError:
 * @discussion This function is called by proxy provider implementations to stop the proxy when a network error is encountered that renders the proxy no longer viable. Subclasses should not override this method.
 * @param error An NSError object containing details about the error that the proxy provider implementation encountered.
 */
- (void)cancelProxyWithError:(nullable NSError *)error API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method handleNewFlow:
 * @discussion This function is called by the framework to deliver a new network data flow to the proxy provider implementation. Subclasses must override this method to perform whatever steps are necessary to ready the proxy to receive data from the flow. The proxy provider implementation indicates that the proxy is ready to handle flow data by calling -[NEAppProxyFlow openWithLocalEndpoint:completionHandler:] on the flow. If the proxy implementation decides to not handle the flow and instead terminate it, the subclass implementation of this method should return NO. If the proxy implementation decides to handle the flow, the subclass implementation of this method should return YES. In this case the proxy implementation is responsible for retaining the NEAppProxyFlow object.
 * @param flow The new flow
 * @return YES if the proxy implementation has retained the flow and intends to handle the flow data. NO if the proxy implementation has not retained the flow and will not handle the flow data. In this case the flow is terminated.
 */
- (BOOL)handleNewFlow:(NEAppProxyFlow *)flow API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method handleNewUDPFlow:initialRemoteEndpoint:
 * @discussion This function is called by the framework to deliver a new UDP data flow to the proxy provider implementation. Subclasses can override this method to perform whatever steps are necessary to ready the proxy to receive
 *     data from the flow. The proxy provider implementation indicates that the proxy is ready to handle flow data by calling -[NEAppProxyFlow openWithLocalEndpoint:completionHandler:] on the flow. If the proxy implementation decides
 *     to not handle the flow and instead terminate it, the subclass implementation of this method should return NO. If the proxy implementation decides to handle the flow, the subclass implementation of this method should return YES.
 *     In this case the proxy implementation is responsible for retaining the NEAppProxyUDPFlow object.
 *     The default implementation of this method calls -[NEAppProxyProvider handleNewFlow:] and returns its result.
 * @param flow The new UDP flow
 * @param remoteEndpoint The initial remote endpoint provided by the proxied app when the flow was opened.
 * @return YES if the proxy implementation has retained the flow and intends to handle the flow data. NO if the proxy implementation has not retained the flow and will not handle the flow data. In this case the flow is terminated.
 */
- (BOOL)handleNewUDPFlow:(NEAppProxyUDPFlow *)flow initialRemoteEndpoint:(NWEndpoint *)remoteEndpoint API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
