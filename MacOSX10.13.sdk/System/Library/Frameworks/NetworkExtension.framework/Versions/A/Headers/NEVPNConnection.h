/*
 * Copyright (c) 2013-2015 Apple Inc.
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
} NS_ENUM_AVAILABLE(10_11, 8_0);

/*! @const NEVPNStatusDidChangeNotification Name of the NSNotification that is posted when the VPN status changes. */
NEVPN_EXPORT NSString * const NEVPNStatusDidChangeNotification NS_AVAILABLE(10_11, 8_0);

/*! @const NEVPNConnectionStartOptionUsername Specify this key in the options dictionary passed to startVPNTunnelWithOptions:returningError: to override the username saved in the configuration. The value is a string */
NEVPN_EXPORT NSString * const NEVPNConnectionStartOptionUsername NS_AVAILABLE(10_11, 9_0);

/*! @const NEVPNConnectionStartOptionPassword Specify this key in the options dictionary passed to startVPNTunnelWithOptions:returningError: to override the password saved in the configuration. The value is a string */
NEVPN_EXPORT NSString * const NEVPNConnectionStartOptionPassword NS_AVAILABLE(10_11, 9_0);

/*!
 * @interface NEVPNConnection
 * @discussion The NEVPNConnection class declares the programmatic interface for an object that manages VPN connections.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 8_0)
@interface NEVPNConnection : NSObject

/*!
 * @method startVPNTunnelAndReturnError:
 * @discussion This function is used to start the VPN tunnel using the current VPN configuration. The VPN tunnel connection process is started and this function returns immediately.
 * @param error If the VPN tunnel was started successfully, this parameter is set to nil. Otherwise this parameter is set to the error that occurred. Possible errors include:
 *    1. NEVPNErrorConfigurationInvalid
 *    2. NEVPNErrorConfigurationDisabled
 * @return YES if the VPN tunnel was started successfully, NO if an error occurred.
 */
- (BOOL)startVPNTunnelAndReturnError:(NSError **)error NS_AVAILABLE(10_11, 8_0);

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
- (BOOL)startVPNTunnelWithOptions:(nullable NSDictionary<NSString *,NSObject *> *)options andReturnError:(NSError **)error NS_AVAILABLE(10_11, 9_0);

/*!
 * @method stopVPNTunnel:
 * @discussion This function is used to stop the VPN tunnel. The VPN tunnel disconnect process is started and this function returns immediately.
 */
- (void)stopVPNTunnel NS_AVAILABLE(10_11, 8_0);

/*!
 * @property status
 * @discussion The current status of the VPN.
 */
@property (readonly) NEVPNStatus status NS_AVAILABLE(10_11, 8_0);

/*!
 * @property connectedDate
 * @discussion The date and time when the connection status changed to NEVPNStatusConnected. This property is nil if the connection is not fully established.
 */
@property (readonly, nullable) NSDate *connectedDate NS_AVAILABLE(10_11, 9_0);

/*!
 * @property manager
 * @discussion The NEVPNManager associated with this NEVPNConnection.
 */
@property (readonly) NEVPNManager *manager NS_AVAILABLE(10_12, 10_0);

@end

NS_ASSUME_NONNULL_END

