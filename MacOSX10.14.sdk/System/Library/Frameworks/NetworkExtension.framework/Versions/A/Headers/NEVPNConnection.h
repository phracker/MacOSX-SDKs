/*
 * Copyright (c) 2013-2015, 2018 Apple Inc.
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
} API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*! @const NEVPNStatusDidChangeNotification Name of the NSNotification that is posted when the VPN status changes. */
NEVPN_EXPORT NSString * const NEVPNStatusDidChangeNotification API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*! @const NEVPNConnectionStartOptionUsername Specify this key in the options dictionary passed to startVPNTunnelWithOptions:returningError: to override the username saved in the configuration. The value is a string */
NEVPN_EXPORT NSString * const NEVPNConnectionStartOptionUsername API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*! @const NEVPNConnectionStartOptionPassword Specify this key in the options dictionary passed to startVPNTunnelWithOptions:returningError: to override the password saved in the configuration. The value is a string */
NEVPN_EXPORT NSString * const NEVPNConnectionStartOptionPassword API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @interface NEVPNConnection
 * @discussion The NEVPNConnection class declares the programmatic interface for an object that manages VPN connections.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEVPNConnection : NSObject

/*!
 * @method startVPNTunnelAndReturnError:
 * @discussion This function is used to start the VPN tunnel using the current VPN configuration. The VPN tunnel connection process is started and this function returns immediately.
 * @param error If the VPN tunnel was started successfully, this parameter is set to nil. Otherwise this parameter is set to the error that occurred. Possible errors include:
 *    1. NEVPNErrorConfigurationInvalid
 *    2. NEVPNErrorConfigurationDisabled
 * @return YES if the VPN tunnel was started successfully, NO if an error occurred.
 */
- (BOOL)startVPNTunnelAndReturnError:(NSError **)error API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

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
- (BOOL)startVPNTunnelWithOptions:(nullable NSDictionary<NSString *,NSObject *> *)options andReturnError:(NSError **)error API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method stopVPNTunnel:
 * @discussion This function is used to stop the VPN tunnel. The VPN tunnel disconnect process is started and this function returns immediately.
 */
- (void)stopVPNTunnel API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property status
 * @discussion The current status of the VPN.
 */
@property (readonly) NEVPNStatus status API_AVAILABLE(macos(10.11), ios(8.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property connectedDate
 * @discussion The date and time when the connection status changed to NEVPNStatusConnected. This property is nil if the connection is not fully established.
 */
@property (readonly, nullable) NSDate *connectedDate API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property manager
 * @discussion The NEVPNManager associated with this NEVPNConnection.
 */
@property (readonly) NEVPNManager *manager API_AVAILABLE(macos(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

