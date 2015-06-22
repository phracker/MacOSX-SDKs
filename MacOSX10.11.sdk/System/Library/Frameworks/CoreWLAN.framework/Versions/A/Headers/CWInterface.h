/*!
 * @header CWInterface.h
 * @copyright 2009-2014 Apple Inc. All rights reserved.
 */

#ifndef _CORE_WLAN_INTERFACE_H_
#define _CORE_WLAN_INTERFACE_H_

#import <Foundation/Foundation.h>
#import <CoreWLAN/CoreWLANTypes.h>

@class CWNetwork;

@class CWChannel;

@class CWConfiguration;

@class SFAuthorization;

/*!
 * @class
 *
 * @abstract 
 * Control and query a Wi-Fi interface on OS X.
 *
 * @discussion 
 * All actions performed by a CWInterface object are executed on the Wi-Fi device with the corresponding interface name.
 */
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE_MAC(10_6)
@interface CWInterface : NSObject
{
    @private
    
        void                    *_device;
    
        NSString                *_interfaceName;
    
        NSArray<NSNumber *>     *_capabilities;
    
        IONotificationPortRef   _interfaceRemovedNotificationPort;
    
        io_iterator_t           _interfaceRemovedNotification;
    
        BOOL                    _deviceAttached;
    
        id                      _eapolClient;
    
        id                      _ipMonitor;
    
        dispatch_queue_t        _internalQueue;
    
        void                    *_serviceStore;
    
        void                    *_interfaceStore;
    
        BOOL                    _lastPowerState;
    
        NSXPCConnection         *_xpcConnection;
}

/*!
 * @property
 *
 * @abstract 
 * Returns the BSD name of the Wi-Fi interface (e.g. "en0").
 */
@property(readonly, nullable) NSString *interfaceName NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @result
 * YES if the Wi-Fi interface is on, NO otherwise.
 *
 * @abstract 
 * Indicates the Wi-Fi interface power state.
 *
 * @discussion 
 * Returns NO if an error occurs.
 */
- (BOOL)powerOn NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @result
 * An NSSet of CWChannel objects.
 *
 * @abstract 
 * Returns the set of channels supported by the Wi-Fi interface for the currently adopted country code.
 *
 * @discussion
 * Returns nil if an error occurs.
 */
- (nullable NSSet<CWChannel *> *)supportedWLANChannels NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @abstract 
 * Returns the current channel of the Wi-Fi interface.
 *
 * @discussion 
 * Returns nil if an error occurs.
 */
- (nullable CWChannel *)wlanChannel NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @abstract 
 * Returns the currently active physical layer (PHY) mode of the Wi-Fi interface.
 *
 * @discussion 
 * Returns kCWPHYModeNone if an error occurs.
 */
- (CWPHYMode)activePHYMode NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @abstract 
 * Returns the current service set identifier (SSID) of the Wi-Fi interface, encoded as a string.
 *
 * @discussion 
 * Returns nil if an error occurs, or if the interface is not participating in a Wi-Fi network,
 * or if the SSID can not be encoded as a valid UTF-8 or WinLatin1 string.
 */
- (nullable NSString *)ssid NS_AVAILABLE_MAC(10_6);

/*!
 * @method
 *
 * @abstract 
 * Returns the current service set identifier (SSID) for the interface, encapsulated in an NSData object.
 *
 * @discussion 
 * Returns nil if an error occurs, or if the interface is not participating in a Wi-Fi network.
 */
- (nullable NSData *)ssidData NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @abstract 
 * Returns the current basic service set identifier (BSSID) of the Wi-Fi interface, returned as an UTF-8 string.
 *
 * @discussion 
 * Returns a UTF-8 string using hexadecimal characters formatted as XX:XX:XX:XX:XX:XX.
 * Returns nil if an error occurred, or if the interface is not participating in a Wi-Fi network.
 */
- (nullable NSString *)bssid NS_AVAILABLE_MAC(10_6);

/*!
 * @method
 *
 * @abstract 
 * Returns the current received signal strength indication (RSSI) measurement (dBm) for the Wi-Fi interface.
 *
 * @discussion 
 * Returns 0 if an error occurs, or if the interface is not participating in a Wi-Fi network.
 */
- (NSInteger)rssiValue NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @abstract 
 * Returns the current noise measurement (dBm) for the Wi-Fi interface.
 *
 * @discussion 
 * Returns 0 if an error occurs, or if the interface is not participating in a Wi-Fi network.
 */
- (NSInteger)noiseMeasurement NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @abstract 
 * Returns the current security type of the Wi-Fi interface.
 *
 * @discussion 
 * Returns kCWSecurityUnknown if an error occurs, or if the interface is not participating in a Wi-Fi network.
 */
- (CWSecurity)security NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @abstract 
 * Returns the current transmit rate (Mbps) for the Wi-Fi interface.
 *
 * @discussion 
 * Returns 0 if an error occurs, or if the interface is not participating in a Wi-Fi network.
 */
- (double)transmitRate NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @abstract 
 * Returns the currently adopted country code (ISO/IEC 3166-1:1997) for the Wi-Fi interface.
 *
 * @discussion 
 * Returns nil if an error occurs, or if the Wi-Fi interface is off.
 */
- (nullable NSString *)countryCode NS_AVAILABLE_MAC(10_6);

/*!
 * @method
 *
 * @abstract 
 * Returns the current operating mode for the Wi-Fi interface.
 *
 * @discussion
 * Returns kCWInterfaceModeNone if an error occurs, or if the interface is not participating in a Wi-Fi network.
 */
- (CWInterfaceMode)interfaceMode NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @abstract 
 * Returns the current transmit power (mW) for the Wi-Fi interface.
 *
 * @discussion 
 * Returns 0 if an error occurs.
 */
- (NSInteger)transmitPower NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @abstract 
 * Returns the hardware media access control (MAC) address for the Wi-Fi interface, returned as an UTF-8 string.
 *
 * @discussion 
 * The standard format for printing a MAC-48 address XX:XX:XX:XX:XX:XX is used to represent
 * the MAC address as a string. 
 * Returns nil if an error occurs.
 */
- (nullable NSString *)hardwareAddress NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @result
 * YES if the corresponding network service is active, NO otherwise.
 *
 * @abstract 
 * Indicates the network service state of the Wi-Fi interface.
 *
 * @discussion 
 * Returns NO if an error occurs.
 */
- (BOOL)serviceActive NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @result
 * An NSSet of CWNetwork objects.
 *
 * @abstract 
 * Returns the scan results currently in the scan cache for the Wi-Fi interface.
 *
 * @discussion 
 * Returns nil if an error occurs.
 */
- (nullable NSSet<CWNetwork *> *)cachedScanResults NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @abstract 
 * Returns the current configuration for the Wi-Fi interface.
 *
 * @discussion
 * Returns nil if an error occurs.
 */
- (nullable CWConfiguration *)configuration NS_AVAILABLE_MAC(10_6);

/*! @functiongroup Creating a Wi-Fi Interface */

/*!
 * @method 
 *
 * @result
 * An NSSet of NSString objects.
 *
 * @abstract 
 * Returns the list of available Wi-Fi interface names (e.g. "en0").
 *
 * @discussion 
 * Returns an empty NSArray object if no Wi-Fi interfaces exist.
 * Returns nil if an error occurs.
 */
+ (nullable NSSet<NSString *> *)interfaceNames NS_DEPRECATED_MAC(10_6, 10_10, "Use +[CWWiFiClient interfaceNames] instead");

/*!
 * @method
 *
 * @abstract 
 * Convenience method for getting a CWInterface object for the default Wi-Fi interface.
 */
+ (instancetype)interface NS_DEPRECATED_MAC(10_6, 10_10, "Use -[CWWiFiClient interface] instead");

/*!
 * @method
 *
 * @param name 
 * The name of an available Wi-Fi interface.
 *
 * @abstract 
 * Convenience method for getting a CWInterface object bound to the Wi-Fi interface with a specific interface name.
 *
 * @discussion 
 * Use +[CWInterface interfaceNames] to get a list of available Wi-Fi interface names.
 * Returns a CWInterface object for the default Wi-Fi interface if no interface name is specified.
 */
+ (instancetype)interfaceWithName:(NSString *)name NS_DEPRECATED_MAC(10_6, 10_10, "Use -[CWWiFiClient interfaceWithName:] instead");

/*!
 * @method
 *
 * @param name
 * The name of an available Wi-Fi interface.
 *
 * @abstract
 * Initializes a CWInterface object, binding to the Wi-Fi interface with a specific interface name.
 *
 * @discussion
 * Use +[CWInterface interfaceNames] to get a list of available Wi-Fi interface names.
 * Returns a CWInterface object for the default Wi-Fi interface if no interface name is specified.
 */
- (instancetype)initWithInterfaceName:(NSString *)name NS_DEPRECATED_MAC(10_6, 10_10, "Use -[CWWiFiClient interfaceWithName:] instead");

/*! @functiongroup Setting the Power State */

/*!
 * @method
 *
 * @param power 
 * A BOOL value indicating Wi-Fi power state. Specify YES to turn on the Wi-Fi interface.
 *
 * @param error 
 * An NSError object passed by reference, which upon return will contain the error if an error occurs. 
 * This parameter is optional.
 *
 * @result 
 * A BOOL value indicating whether or not an error occurred. YES indicates no error occurred.
 *
 * @abstract 
 * Sets the Wi-Fi interface power state.
 *
 * @discussion
 * Requires the <i>com.apple.wifi.set_power</i> entitlement.
 */
- (BOOL)setPower:(BOOL)power error:(out NSError **)error NS_AVAILABLE_MAC(10_6);

/*! @functiongroup Setting the Channel */

/*!
 * @method
 *
 * @param channel
 * A CWChannel object.
 *
 * @param error
 * An NSError object passed by reference, which upon return will contain the error if an error occurs.
 * This parameter is optional.
 *
 * @result
 * A BOOL value indicating whether or not an error occurred. YES indicates no error occurred.
 *
 * @abstract 
 * Sets the Wi-Fi interface channel.
 *
 * @discussion 
 * Setting the channel while the interface is associated to a Wi-Fi network is not permitted.
 * Requires the <i>com.apple.wifi.set_channel</i> entitlement.
 */
- (BOOL)setWLANChannel:(CWChannel *)channel error:(out NSError **)error NS_AVAILABLE_MAC(10_7);

/*! @functiongroup Setting Keys */

/*!
 * @method
 *
 * @param key 
 * An NSData object containing the pairwise master key (PMK).
 * Passing nil clear the PMK for the Wi-Fi interface.
 *
 * @param error
 * An NSError object passed by reference, which upon return will contain the error if an error occurs.
 * This parameter is optional.
 *
 * @result
 * A BOOL value indicating whether or not an error occurred. YES indicates no error occurred.
 *
 * @abstract 
 * Sets the Wi-Fi interface pairwise master key (PMK).
 *
 * @discussion 
 * The specified key must be exactly 32 octets. 
 * Requires the <i>com.apple.wifi.set_pmk</i> entitlement.
 */
- (BOOL)setPairwiseMasterKey:(nullable NSData *)key error:(out NSError **)error NS_AVAILABLE_MAC(10_6);

/*!
 * @method
 *
 * @param key 
 * An NSData object containing the WEP key.
 * Passing nil clears the WEP key for the Wi-Fi interface.
 *
 * @param flags 
 * A bitmask indicating which CWCipherKeyFlags to use for the specified WEP key.
 *
 * @param index 
 * An NSInteger indicating which default key index (1-4) to use for the specified key.
 *
 * @param error
 * An NSError object passed by reference, which upon return will contain the error if an error occurs.
 * This parameter is optional.
 *
 * @result
 * A BOOL value indicating whether or not an error occurred. YES indicates no error occurred.
 *
 * @abstract 
 * Sets the Wi-Fi interface WEP key.
 *
 * @discussion
 * Requires the <i>com.apple.wifi.set_wep_key</i> entitlement.
 */
- (BOOL)setWEPKey:(nullable NSData *)key flags:(CWCipherKeyFlags)flags index:(NSInteger)index error:(out NSError **)error NS_AVAILABLE_MAC(10_6);

/*! @functiongroup Scanning for Networks */

/*!
 * @method
 *
 * @param ssid
 * Probe request SSID.  
 * Pass an SSID to perform a directed scan for hidden Wi-Fi networks.
 * This parameter is optional.
 *
 * @param error
 * An NSError object passed by reference, which upon return will contain the error if an error occurs.
 * This parameter is optional.
 *
 * @result
 * An NSSet of CWNetwork objects, or nil if an error occurs.
 *
 * @abstract 
 * Performs a scan for Wi-Fi networks and returns scan results to the caller.
 *
 * @discussion 
 * This method will block for the duration of the scan.
 * Requires the <i>com.apple.wifi.scan</i> entitlement.
 */
- (nullable NSSet<CWNetwork *> *)scanForNetworksWithSSID:(nullable NSData *)ssid error:(out NSError **)error NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @param networkName
 * Probe request SSID, encoded as an UTF-8 string.
 * Pass a networkName to perform a directed scan for hidden Wi-Fi networks.
 * This parameter is optional.
 *
 * @param error
 * An NSError object passed by reference, which upon return will contain the error if an error occurs.
 * This parameter is optional.
 *
 * @result
 * An NSSet of CWNetwork objects, or nil if an error occurs.
 *
 * @abstract
 * Performs a scan for Wi-Fi networks and returns scan results to the caller.
 *
 * @discussion
 * This method will block for the duration of the scan.
 * Requires the <i>com.apple.wifi.scan</i> entitlement.
 */
- (nullable NSSet<CWNetwork *> *)scanForNetworksWithName:(nullable NSString *)networkName error:(out NSError **)error NS_AVAILABLE_MAC(10_7);

/*! @functiongroup Joining a Network */

/*!
 * @method
 *
 * @param network
 * The network to which the Wi-Fi interface will associate.
 *
 * @param password
 * The network passphrase or key. Required for association to WEP, WPA Personal, and WPA2 Personal networks.
 *
 * @param error
 * An NSError object passed by reference, which upon return will contain the error if an error occurs.
 * This parameter is optional.
 *
 * @result
 * A BOOL value indicating whether or not an error occurred. YES indicates no error occurred.
 *
 * @abstract 
 * Associates to a W-Fi network using the specified passphrase.
 *
 * @discussion 
 * This method will block for the duration of the association.
 * Requires the <i>com.apple.wifi.associate</i> entitlement.
 */
- (BOOL)associateToNetwork:(CWNetwork *)network password:(nullable NSString *)password error:(out NSError **)error NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @abstract 
 * Disassociates from the current Wi-Fi network.
 *
 * @discussion
 * Requires the <i>com.apple.wifi.associate</i> entitlement.
 */
- (void)disassociate NS_AVAILABLE_MAC(10_6);

/*!
 * @method
 *
 * @param network
 * The network to which the Wi-Fi interface will associate.
 *
 * @param username 
 * The username to use for 802.1X authentication.
 *
 * @param password 
 * The password to use for 802.1X authentication.
 *
 * @param identity 
 * The identity to use for IEEE 802.1X authentication. Holds the corresponding client certificate.
 *
 * @param error
 * An NSError object passed by reference, which upon return will contain the error if an error occurs.
 * This parameter is optional.
 *
 * @result
 * A BOOL value indicating whether or not an error occurred. YES indicates no error occurred.
 *
 * @abstract
 * Associates to an enterprise W-Fi network using the specified 802.1X credentials.
 *
 * @discussion
 * This method will block for the duration of the association.
 * Requires the <i>com.apple.wifi.associate</i> entitlement.
 */
- (BOOL)associateToEnterpriseNetwork:(CWNetwork *)network identity:(nullable SecIdentityRef)identity username:(nullable NSString *)username password:(nullable NSString *)password error:(out NSError **)error NS_AVAILABLE_MAC(10_7);

/*! @functiongroup Creating an IBSS Network */

/*!
 * @method
 *
 * @param ssidData
 * The SSID to use for the IBSS network.
 * Pass nil to use the machine name as the IBSS network name.
 *
 * @param security 
 * The CWIBSSModeSecurity type.
 *
 * @param channel 
 * The channel on which the IBSS network will be created.
 *
 * @param password 
 * The password to be used. This paramter is required for kCWIBSSModeSecurityWEP40 or kCWIBSSModeSecurityWEP104 security types.
 *
 * @param error
 * An NSError object passed by reference, which upon return will contain the error if an error occurs.
 * This parameter is optional.
 *
 * @result
 * A BOOL value indicating whether or not an error occurred. YES indicates no error occurred.
 *
 * @abstract
 * Creates a computer-to-computer (IBSS) network.
 *
 * @discussion
 * Requires the <i>com.apple.wifi.ibss</i> entitlement.
 */
- (BOOL)startIBSSModeWithSSID:(NSData *)ssidData security:(CWIBSSModeSecurity)security channel:(NSUInteger)channel password:(nullable NSString *)password error:(out NSError **)error NS_AVAILABLE_MAC(10_7);

/*! @functiongroup Committing a Wi-Fi Configuration */

/*!
 * @method
 *
 * @param configuration
 * The Wi-Fi configuration to commit to disk.
 *
 * @param authorization
 * An SFAuthorization object to use for authorizing the commit.
 * This parameter is optional.
 *
 * @param error
 * An NSError object passed by reference, which upon return will contain the error if an error occurs.
 * This parameter is optional.
 *
 * @result
 * A BOOL value indicating whether or not an error occurred. YES indicates no error occurred.
 *
 * @abstract 
 * Commits a CWConfiguration for the given Wi-Fi interface.
 *
 * @discussion 
 * This method requires the caller have root privileges
 * or obtain administrator privileges using the SFAuthorization API.
 */
- (BOOL)commitConfiguration:(CWConfiguration *)configuration authorization:(nullable SFAuthorization *)authorization error:(out NSError **)error NS_AVAILABLE_MAC(10_7);

@end
NS_ASSUME_NONNULL_END

#endif /* _CORE_WLAN_INTERFACE_H_ */
