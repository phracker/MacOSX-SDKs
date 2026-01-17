/*
 * Copyright (c) 2015, 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEVPNConnection.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NETunnelProviderSession.h
 * @discussion This file declares the NETunnelProviderSession API. The NETunnelProviderSession API is used to control network tunnel services provided by NETunnelProvider implementations.
 *
 * This API is part of NetworkExtension.framework.
 */

API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NETunnelProviderSession : NEVPNConnection

/*!
 * @method startTunnelWithOptions:andReturnError:
 * @discussion This function is used to start the tunnel using the configuration associated with this connection object. The tunnel connection process is started and this function returns immediately.
 * @param options A dictionary that will be passed as-is to the tunnel provider during the process of starting the tunnel.
 * @param error If the tunnel was started successfully, this parameter is set to nil. Otherwise this parameter is set to the error that occurred. Possible errors include:
 *    1. NEVPNErrorConfigurationInvalid
 *    2. NEVPNErrorConfigurationDisabled
 * @return YES if the tunnel was started successfully, NO if an error occurred.
 */
- (BOOL)startTunnelWithOptions:(nullable NSDictionary<NSString *,id> *)options andReturnError:(NSError **)error API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method stopTunnel
 * @discussion This function is used to stop the tunnel. The tunnel disconnect process is started and this function returns immediately.
 */
- (void)stopTunnel API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method sendProviderMessage:responseHandler:
 * @discussion This function sends a message to the NETunnelProvider and provides a way to receive a response.
 * @param messageData An NSData object containing the message to be sent.
 * @param error If the message was sent successfully, this parameter is set to nil. Otherwise this parameter is set to the error that occurred. Possible errors include:
 *    1. NEVPNErrorConfigurationInvalid
 *    2. NEVPNErrorConfigurationDisabled
 * @param responseHandler A block that handles the response. Can be set to nil if no response is expected.
 * @return YES if the message was sent successfully, NO if an error occurred.
 */
- (BOOL)sendProviderMessage:(NSData *)messageData returnError:(NSError **)error responseHandler:(nullable void (^)( NSData * __nullable responseData))responseHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END
