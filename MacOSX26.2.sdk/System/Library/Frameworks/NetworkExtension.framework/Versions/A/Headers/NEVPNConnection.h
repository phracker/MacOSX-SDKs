/*
 * Copyright (c) 2013-2015, 2018, 2022 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

#if !defined(NEVPN_EXPORT)
#define NEVPN_EXPORT extern
#endif

@class NEVPNManager;

/*!
 * @typedef NEVPNStatus
 * @abstract VPN status codes
 */
typedef NS_ENUM(NSInteger, NEVPNStatus) {
    /*! @const NEVPNStatusInvalid The VPN is not configured. */
    NEVPNStatusInvalid = 0,
    /*! @const NEVPNStatusDisconnected The VPN is disconnected. */
    NEVPNStatusDisconnected = 1,
    /*! @const NEVPNStatusConnecting The VPN is connecting. */
    NEVPNStatusConnecting = 2,
    /*! @const NEVPNStatusConnected The VPN is connected. */
    NEVPNStatusConnected = 3,
    /*! @const NEVPNStatusReasserting The VPN is reconnecting following loss of underlying network connectivity. */
    NEVPNStatusReasserting = 4,
    /*! @const NEVPNStatusDisconnecting The VPN is disconnecting. */
    NEVPNStatusDisconnecting = 5,
} API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*! @const NEVPNStatusDidChangeNotification Name of the NSNotification that is posted when the VPN status changes. */
NEVPN_EXPORT NSString * const NEVPNStatusDidChangeNotification API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*! @const NEVPNConnectionStartOptionUsername Specify this key in the options dictionary passed to startVPNTunnelWithOptions:returningError: to override the username saved in the configuration. The value is a string */
NEVPN_EXPORT NSString * const NEVPNConnectionStartOptionUsername API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*! @const NEVPNConnectionStartOptionPassword Specify this key in the options dictionary passed to startVPNTunnelWithOptions:returningError: to override the password saved in the configuration. The value is a string */
NEVPN_EXPORT NSString * const NEVPNConnectionStartOptionPassword API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @typedef NEVPNConnectionError
 * @abstract VPN error codes
 */
typedef NS_ENUM(NSInteger, NEVPNConnectionError) {
	/*! @const NEVPNConnectionErrorOverslept The VPN connection was terminated because the system slept for an extended period of time. */
	NEVPNConnectionErrorOverslept = 1,
	/*! @const NEVPNConnectionErrorNoNetworkAvailable The VPN connection could not be established because the system is not connected to a network. */
	NEVPNConnectionErrorNoNetworkAvailable = 2,
	/*! @const NEVPNConnectionErrorUnrecoverableNetworkChange The VPN connection was terminated because the network conditions changed in such a
	 * way that the VPN connection could not be maintained. */
	NEVPNConnectionErrorUnrecoverableNetworkChange = 3,
	/*! @const NEVPNConnectionErrorConfigurationFailed The VPN connection could not be established because the configuration is invalid. */
	NEVPNConnectionErrorConfigurationFailed = 4,
	/*! @const NEVPNConnectionErrorServerAddressResolutionFailed The address of the VPN server could not be determined. */
	NEVPNConnectionErrorServerAddressResolutionFailed = 5,
	/*! @const NEVPNConnectionErrorServerNotResponding Network communication with the VPN server has failed. */
	NEVPNConnectionErrorServerNotResponding = 6,
	/*! @const NEVPNConnectionErrorServerDead The VPN server is no longer functioning. */
	NEVPNConnectionErrorServerDead = 7,
	/*! @const NEVPNConnectionErrorAuthenticationFailed The user credentials were rejected by the VPN server. */
	NEVPNConnectionErrorAuthenticationFailed = 8,
	/*! @const NEVPNConnectionErrorClientCertificateInvalid The client certificate is invalid. */
	NEVPNConnectionErrorClientCertificateInvalid = 9,
	/*! @const NEVPNConnectionErrorClientCertificateNotYetValid The client certificate will not be valid until some future point in time. */
	NEVPNConnectionErrorClientCertificateNotYetValid = 10,
	/*! @const NEVPNConnectionErrorClientCertificateExpired The validity period of the client certificate has passed. */
	NEVPNConnectionErrorClientCertificateExpired = 11,
	/*! @const NEVPNConnectionErrorPluginFailed The VPN plugin died unexpectedly. */
	NEVPNConnectionErrorPluginFailed = 12,
	/*! @const NEVPNConnectionErrorConfigurationNotFound The VPN configuration could not be found . */
	NEVPNConnectionErrorConfigurationNotFound = 13,
	/*! @const NEVPNConnectionErrorPluginDisabled The VPN plugin could not be found or needed to be updated. */
	NEVPNConnectionErrorPluginDisabled = 14,
	/*! @const NEVPNConnectionErrorNegotiationFailed The VPN protocol negotiation failed. */
	NEVPNConnectionErrorNegotiationFailed = 15,
	/*! @const NEVPNConnectionErrorServerDisconnected The VPN server terminated the connection. */
	NEVPNConnectionErrorServerDisconnected = 16,
	/*! @const NEVPNConnectionErrorServerCertificateInvalid The server certificate is invalid. */
	NEVPNConnectionErrorServerCertificateInvalid = 17,
	/*! @const NEVPNConnectionErrorServerCertificateNotYetValid The server certificate will not be valid until some future point in time. */
	NEVPNConnectionErrorServerCertificateNotYetValid = 18,
	/*! @const NEVPNConnectionErrorServerCertificateExpired The validity period of the server certificate has passed. */
	NEVPNConnectionErrorServerCertificateExpired = 19,
} API_AVAILABLE(macos(13.0), ios(16.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*! @const NEVPNConnectionErrorDomain The VPN connection error domain */
NEVPN_EXPORT NSString * const NEVPNConnectionErrorDomain API_AVAILABLE(macos(13.0), ios(16.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @interface NEVPNConnection
 * @discussion The NEVPNConnection class declares the programmatic interface for an object that manages VPN connections.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface NEVPNConnection : NSObject

/*!
 * @method startVPNTunnelAndReturnError:
 * @discussion This function is used to start the VPN tunnel using the current VPN configuration. The VPN tunnel connection process is started and this function returns immediately.
 * @param error If the VPN tunnel was started successfully, this parameter is set to nil. Otherwise this parameter is set to the error that occurred. Possible errors include:
 *    1. NEVPNErrorConfigurationInvalid
 *    2. NEVPNErrorConfigurationDisabled
 * @return YES if the VPN tunnel was started successfully, NO if an error occurred.
 */
- (BOOL)startVPNTunnelAndReturnError:(NSError **)error API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @method startVPNTunnelWithOptions:andReturnError:
 * @discussion This function is used to start the VPN tunnel using the current VPN configuration. The VPN tunnel connection process is started and this function returns immediately.
 * @param options A dictionary that will be passed to the tunnel provider during the process of starting the tunnel.
 *    If not nil, 'options' is an NSDictionary may contain the following keys
 *        NEVPNConnectionStartOptionUsername
 *        NEVPNConnectionStartOptionPassword
 * @param error If the VPN tunnel was started successfully, this parameter is set to nil. Otherwise this parameter is set to the error that occurred. Possible errors include:
 *    1. NEVPNErrorConfigurationInvalid
 *    2. NEVPNErrorConfigurationDisabled
 * @return YES if the VPN tunnel was started successfully, NO if an error occurred.
 */
- (BOOL)startVPNTunnelWithOptions:(nullable NSDictionary<NSString *,NSObject *> *)options andReturnError:(NSError **)error API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @method stopVPNTunnel:
 * @discussion This function is used to stop the VPN tunnel. The VPN tunnel disconnect process is started and this function returns immediately.
 */
- (void)stopVPNTunnel API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @method fetchLastDisconnectErrorWithCompletionHandler:
 * @discussion Retrive the most recent error that caused the VPN to disconnect. If the error was generated by the VPN system (including the IPsec client) then the error will be in the NEVPNConnectionErrorDomain error domain. If the error was generated by a tunnel provider app extension then the error will be the NSError that the provider passed when disconnecting the tunnel.
 * @param handler A block which takes an optional NSError that will be called when the error is obtained.
 */
- (void)fetchLastDisconnectErrorWithCompletionHandler:(void (^)(NSError * _Nullable))handler API_AVAILABLE(macos(13.0), ios(16.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property status
 * @discussion The current status of the VPN.
 */
@property (readonly) NEVPNStatus status API_AVAILABLE(macos(10.11), ios(8.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property connectedDate
 * @discussion The date and time when the connection status changed to NEVPNStatusConnected. This property is nil if the connection is not fully established.
 */
@property (readonly, nullable) NSDate *connectedDate API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property manager
 * @discussion The NEVPNManager associated with this NEVPNConnection.
 */
@property (readonly) NEVPNManager *manager API_AVAILABLE(macos(10.12), ios(10.0), tvos(17.0)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

