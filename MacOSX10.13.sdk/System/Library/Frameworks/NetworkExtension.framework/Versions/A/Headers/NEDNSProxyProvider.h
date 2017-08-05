/*
 * Copyright (c) 2017 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEProvider.h>

NS_ASSUME_NONNULL_BEGIN

@class NEAppProxyFlow;
@class NEDNSSettings;

/*!
 * @file NEDNSProxyProvider.h
 * @discussion This file declares the NEDNSProxyProvider API. The NEDNSProxyProvider is used to implement custom DNS proxy solutions.
 */

/*!
 * @interface NEDNSProxyProvider
 * @discussion The NEDNSProxyProvider class declares the programmatic interface for an object that implements the client side of a custom DNS proxy solution.
 *
 * NEDNSProxyProvider is part of NetworkExtension.framework
 */
NS_CLASS_AVAILABLE(NA, 11_0)
@interface NEDNSProxyProvider : NEProvider

/*!
 * @method startProxyWithOptions:completionHandler:
 * @discussion This function is called by the framework when a new proxy instance is being created. Subclasses must override this method to perform whatever steps are necessary to ready the proxy for handling flows of network data.
 * @param options A dictionary containing keys and values passed by the provider's containing app. If the containing app did not start the proxy then this parameter will be nil.
 * @param completionHandler A block that must be called when the process of starting the proxy is complete. If the proxy cannot be started then the subclass' implementation of this method must pass a non-nil NSError object to this block. A value of nil passed to the completion handler indicates that the proxy was successfully started.
 */
- (void)startProxyWithOptions:(nullable NSDictionary<NSString *,id> *)options completionHandler:(void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE(NA, 11_0);

/*!
 * @method stopProxyWithReason:completionHandler:
 * @discussion This function is called by the framework when the proxy is being stopped. Subclasses must override this method to perform whatever steps are necessary to stop the proxy.
 * @param reason An NEProviderStopReason indicating why the proxy is being stopped.
 * @param completionHandler A block that must be called when the proxy is completely stopped.
 */
- (void)stopProxyWithReason:(NEProviderStopReason)reason completionHandler:(void (^)(void))completionHandler NS_AVAILABLE(NA, 11_0);

/*!
 * @method cancelProxyWithError:
 * @discussion This function is called by proxy provider implementations to stop the proxy when a network error is encountered that renders the proxy no longer viable. Subclasses should not override this method.
 * @param error An NSError object containing details about the error that the proxy provider implementation encountered.
 */
- (void)cancelProxyWithError:(nullable NSError *)error NS_AVAILABLE(NA, 11_0);

/*!
 * @method handleNewFlow:
 * @discussion This function is called by the framework to deliver a new network data flow to the proxy provider implementation. Subclasses must override this method to perform whatever steps are necessary to ready the proxy to receive data from the flow. The proxy provider implementation indicates that the proxy is ready to handle flow data by calling -[NEAppProxyFlow openWithLocalEndpoint:completionHandler:] on the flow. If the proxy implementation decides to not handle the flow and instead terminate it, the subclass implementation of this method should return NO. If the proxy implementation decides to handle the flow, the subclass implementation of this method should return YES. In this case the proxy implementation is responsible for retaining the NEAppProxyFlow object.
 * @param flow The new flow
 * @return YES if the proxy implementation has retained the flow and intends to handle the flow data. NO if the proxy implementation has not retained the flow and will not handle the flow data. In this case the flow is terminated.
 */
- (BOOL)handleNewFlow:(NEAppProxyFlow *)flow NS_AVAILABLE(NA, 11_0);

/*!
 * @property systemDNSSettings
 * @discussion The current system DNS settings. Use KVO to watch for changes.
 */
@property (readonly, nullable) NSArray<NEDNSSettings *> *systemDNSSettings NS_AVAILABLE(NA, 11_0);

@end

NS_ASSUME_NONNULL_END
