/*
 * Copyright (c) 2015, 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEProvider.h>

NS_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
#define NETUNNELPROVIDER_EXPORT extern "C"
#else
#define NETUNNELPROVIDER_EXPORT extern
#endif

/*!
 * @file NETunnelProvider.h
 * @discussion This file declares the NETunnelProvider API. The NETunnelProvider API is used to implement Network Extension providers that provide network tunneling services.
 *
 * This API is part of NetworkExtension.framework
 */

@class NEVPNProtocol;
@class NETunnelNetworkSettings;
@class NEAppRule;

/*!
 * @typedef NETunnelProviderError
 * @abstract Tunnel Provider error codes
 */
typedef NS_ENUM(NSInteger, NETunnelProviderError) {
	/*! @const NETunnelProviderErrorNetworkSettingsInvalid The provided tunnel network settings are invalid. */
	NETunnelProviderErrorNetworkSettingsInvalid = 1,
	/*! @const NETunnelProviderErrorNetworkSettingsCanceled The request to set/clear the tunnel network settings was canceled. */
	NETunnelProviderErrorNetworkSettingsCanceled = 2,
	/*! @const NETunnelProviderErrorNetworkSettingsFailed The request to set/clear the tunnel network settings failed. */
	NETunnelProviderErrorNetworkSettingsFailed = 3,
} API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @typedef NETunnelProviderRoutingMethod
 * @abstract Network traffic routing methods.
 */
typedef NS_ENUM(NSInteger, NETunnelProviderRoutingMethod) {
	/*! @const NETunnelProviderRoutingMethodDestinationIP Route network traffic to the tunnel based on destination IP */
	NETunnelProviderRoutingMethodDestinationIP = 1,
	/*! @const NETunnelProviderRoutingMethodSourceApplication Route network traffic to the tunnel based on source application */
	NETunnelProviderRoutingMethodSourceApplication = 2,
} API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);


/*! @const NETunnelProviderErrorDomain The tunnel provider error domain */
NETUNNELPROVIDER_EXPORT NSString * const NETunnelProviderErrorDomain API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @interface NETunnelProvider
 * @discussion The NETunnelProvider class declares the programmatic interface for an object that provides a network tunnel service.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NETunnelProvider : NEProvider

/*!
 * @method handleAppMessage:completionHandler:
 * @discussion This function is called by the framework when the container app sends a message to the provider. Subclasses should override this method to handle the message and optionally send a response.
 * @param messageData An NSData object containing the message sent by the container app.
 * @param completionHandler A block that the method can execute to send a response to the container app. If this parameter is non-nil then the method implementation should always execute the block. If this parameter is nil then the method implementation should treat this as an indication that the container app is not expecting a response.
 */
- (void)handleAppMessage:(NSData *)messageData completionHandler:(nullable void (^)(NSData * __nullable responseData))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method setTunnelNetworkSettings:completionHandler:
 * @discussion This function is called by tunnel provider implementations to set the network settings of the tunnel, including IP routes, DNS servers, and virtual interface addresses depending on the tunnel type. Subclasses should not override this method. This method can be called multiple times during the lifetime of a particular tunnel. It is not necessary to call this function with nil to clear out the existing settings before calling this function with a non-nil configuration.
 * @param tunnelNetworkSettings An NETunnelNetworkSettings object containing all of the desired network settings for the tunnel. Pass nil to clear out the current network settings.
 * @param completionHandler A block that will be called by the framework when the process of setting or clearing the network settings is complete. If an error occurred during the process of setting or clearing the IP network settings then a non-nill NSError object will be passed to this block containing error details.
 */
- (void)setTunnelNetworkSettings:(nullable NETunnelNetworkSettings *)tunnelNetworkSettings completionHandler:(nullable void (^)( NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property protocolConfiguration
 * @discussion An NEVPNProtocol object containing the provider's current configuration. The value of this property may change during the lifetime of the tunnel provided by this NETunnelProvider, KVO can be used to detect when changes occur.  For different protocol types, this property will contain the corresponding subclass.   For NEVPNProtocolTypePlugin protocol type, this property will contain the NETunnelProviderProtocol subclass.  For NEVPNProtocolTypeIKEv2 protocol type, this property will contain the NEVPNProtocolIKEv2 subclass.
 */
@property (readonly) NEVPNProtocol *protocolConfiguration API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property appRules
 * @discussion An array of NEAppRule objects specifying which applications are currently being routed through the tunnel provided by this NETunnelProvider. If application-based routing is not enabled for the tunnel, then this property is set to nil. 
 */
@property (readonly, nullable) NSArray<NEAppRule *> *appRules API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property routingMethod
 * @discussion The method by which network traffic is routed to the tunnel. The default is NETunnelProviderRoutingMethodDestinationIP.
 */
@property (readonly) NETunnelProviderRoutingMethod routingMethod API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property reasserting
 * @discussion A flag that indicates to the framework if this NETunnelProvider is currently re-establishing the tunnel. Setting this flag will cause the session status visible to the user to change to "Reasserting". Clearing this flag will change the user-visible status of the session back to "Connected". Setting and clearing this flag only has an effect if the session is in the "Connected" state.
 */
@property BOOL reasserting API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

