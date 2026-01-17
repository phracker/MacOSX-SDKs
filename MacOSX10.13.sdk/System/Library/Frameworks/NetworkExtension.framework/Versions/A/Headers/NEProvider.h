/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <Foundation/NSObjCRuntime.h>

NS_ASSUME_NONNULL_BEGIN

@class NWTCPConnection;
@class NWTLSParameters;
@class NWUDPSession;
@class NWEndpoint;
@class NWHostEndpoint;
@class NWPath;

/*!
 * @typedef NEProviderStopReason
 * @abstract Provider stop reasons
 */
typedef NS_ENUM(NSInteger, NEProviderStopReason) {
	/*! @const NEProviderStopReasonNone No specific reason. */
	NEProviderStopReasonNone = 0,
	/*! @const NEProviderStopReasonUserInitiated The user stopped the provider. */
	NEProviderStopReasonUserInitiated = 1,
	/*! @const NEProviderStopReasonProviderFailed The provider failed. */
	NEProviderStopReasonProviderFailed = 2,
	/*! @const NEProviderStopReasonNoNetworkAvailable There is no network connectivity. */
	NEProviderStopReasonNoNetworkAvailable = 3,
	/*! @const NEProviderStopReasonUnrecoverableNetworkChange The device attached to a new network. */
	NEProviderStopReasonUnrecoverableNetworkChange = 4,
	/*! @const NEProviderStopReasonProviderDisabled The provider was disabled. */
	NEProviderStopReasonProviderDisabled = 5,
	/*! @const NEProviderStopReasonAuthenticationCanceled The authentication process was cancelled. */
	NEProviderStopReasonAuthenticationCanceled = 6,
	/*! @const NEProviderStopReasonConfigurationFailed The provider could not be configured. */
	NEProviderStopReasonConfigurationFailed = 7,
	/*! @const NEProviderStopReasonIdleTimeout The provider was idle for too long. */
	NEProviderStopReasonIdleTimeout = 8,
	/*! @const NEProviderStopReasonConfigurationDisabled The associated configuration was disabled. */
	NEProviderStopReasonConfigurationDisabled = 9,
	/*! @const NEProviderStopReasonConfigurationRemoved The associated configuration was deleted. */
	NEProviderStopReasonConfigurationRemoved = 10,
	/*! @const NEProviderStopReasonSuperceded A high-priority configuration was started. */
	NEProviderStopReasonSuperceded = 11,
	/*! @const NEProviderStopReasonUserLogout The user logged out. */
	NEProviderStopReasonUserLogout = 12,
	/*! @const NEProviderStopReasonUserSwitch The active user changed. */
	NEProviderStopReasonUserSwitch = 13,
	/*! @const NEProviderStopReasonConnectionFailed Failed to establish connection. */
	NEProviderStopReasonConnectionFailed = 14,
} NS_AVAILABLE(10_11, 9_0);

/*!
 * @file NEProvider.h
 * @discussion This file declares the NEProvider API. The NEProvider API declares the base class for Network Extension service providers.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NEProvider
 * @discussion The NEProvider class declares the programmatic interface that is common for all Network Extension providers.
 *
 * See the sub classes of NEProvider for more details. Developers of Network Extension providers should create sub classes of the sub classes of NEProvider.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEProvider : NSObject

/*!
 * @method sleepWithCompletionHandler:
 * @discussion This function is called by the framework when the system is about to go to sleep. Subclass developers can override this method to implement custom behavior such as closing connections or pausing some network activity.
 * @param completionHandler When the method is finished handling the sleep event it must execute this completion handler.
 */
- (void)sleepWithCompletionHandler:(void (^)(void))completionHandler NS_AVAILABLE(10_11, 9_0);

/*!
 * @method wake
 * @discussion This function is called by the framework immediately after the system wakes up from sleep. Subclass developers can override this method to implement custom behavior such as re-establishing connections or resuming some network activity.
 */
- (void)wake NS_AVAILABLE(10_11, 9_0);

/*!
 * @method createTCPConnectionToEndpoint:enableTLS:TLSParameters:delegate:
 * @discussion This function can be called by subclass implementations to create a TCP connection to a given network endpoint. This function should not be overridden by subclasses.
 * @param remoteEndpoint An NWEndpoint object that specifies the remote network endpoint to connect to.
 * @param enableTLS A flag indicating if a TLS session should be negotiated on the connection.
 * @param TLSParameters A set of optional TLS parameters. Only valid if enableTLS is YES. If TLSParameters is nil, the default system parameters will be used for TLS negotiation.
 * @param delegate An object to use as the connections delegate. This object should conform to the NWTCPConnectionAuthenticationDelegate protocol.
 * @return An NWTCPConnection object.
 */
- (NWTCPConnection *)createTCPConnectionToEndpoint:(NWEndpoint *)remoteEndpoint enableTLS:(BOOL)enableTLS TLSParameters:(nullable NWTLSParameters *)TLSParameters delegate:(nullable id)delegate NS_AVAILABLE(10_11, 9_0);

/*!
 * @method createUDPSessionToEndpoint:fromEndpoint:
 * @discussion This function can be called by subclass implementations to create a UDP session between a local network endpoint and a remote network endpoint. This function should not be overridden by subclasses.
 * @param remoteEndpoint An NWEndpoint object that specifies the remote endpoint to which UDP datagrams will be sent by the UDP session.
 * @param localEndpoint An NWHostEndpoint object that specifies the local IP address endpoint to use as the source endpoint of the UDP session.
 * @return An NWUDPSession object.
 */
- (NWUDPSession *)createUDPSessionToEndpoint:(NWEndpoint *)remoteEndpoint fromEndpoint:(nullable NWHostEndpoint *)localEndpoint NS_AVAILABLE(10_11, 9_0);

/*!
 * @method displayMessage:completionHandler:
 * @discussion This method can be called by subclass implementations to display a message to the user.
 * @param message The message to be displayed.
 * @param completionHandler A block that is executed when the user acknowledges the message. If this method is called on a NEFilterDataProvider instance or the message cannot be displayed, then the completion handler block will be executed immediately with success parameter set to NO. If the message was successfully displayed to the user, then the completion handler block is executed with the success parameter set to YES when the user dismisses the message.
 */
- (void)displayMessage:(NSString *)message completionHandler:(void (^)(BOOL success))completionHandler NS_AVAILABLE(10_12, 10_0);

/*!
 * @property defaultPath
 * @discussion The current default path for connections created by the provider. Use KVO to watch for network changes.
 */
@property (readonly, nullable) NWPath *defaultPath NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

