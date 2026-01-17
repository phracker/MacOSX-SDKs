/*!
 * @header CWInterface.h
 * @copyright 2010 Apple Inc. All rights reserved.
 * @updated 2010-03-09
 * @version 2.0.0
 */

#ifndef _CORE_WLAN_INTERFACE_H_
#define _CORE_WLAN_INTERFACE_H_

#import <Foundation/Foundation.h>
#import <CoreWLAN/CoreWLANTypes.h>

#pragma mark -
@class CWNetwork, CWChannel, CWConfiguration, SFAuthorization;

/*!
 * @class
 * @abstract Encapsulates an IEEE 802.11 interface.
 * @discussion Provides access to various WLAN interface parameters, and operations such as scanning for networks, 
 * association, and creating computer-to-computer (ad-hoc) networks.
 */
@interface CWInterface : NSObject {
@private
	void *_device;
	NSString *_interfaceName;
	NSArray *_capabilities;
	IONotificationPortRef _interfaceRemovedNotificationPort;
	io_iterator_t _interfaceRemovedNotification;
	BOOL _deviceAttached;
	id _eapolClient;
	id _ipMonitor;
	dispatch_queue_t _internalQueue;
	void *_serviceStore;
	void *_interfaceStore;
    BOOL _lastPowerState;
    NSXPCConnection *_anqpConn;
}

/*!
 * @property
 * @abstract The interface power state is set to "ON".
 * @discussion Dynamically queries the interface for the current power state. Returns <i>NO</i> in the case
 * of an error.
 */
@property(readonly, assign) BOOL powerOn NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The BSD name of the interface. 
 */
@property(readonly, copy) NSString *interfaceName NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract An array of channels supported by the interface for the active country code.
 * @discussion Dynamically queries the interface for the supported channels. Returns an array of CWChannel objects,
 * or <i>nil<i/> in the case of an error.
 */
@property(readonly) NSSet *supportedWLANChannels NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The current channel for the interface. 
 * @discussion Dynamically queries the interface for the current channel. Returns <i>nil</i> 
 * in the case of an error, or if the interface is not 
 * participating in a network.
 */
@property(readonly) CWChannel *wlanChannel NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The current active PHY modes for the interface. 
 * @discussion Dynamically queries the interface for the current active PHY mode.
 * Returns <i>kCWPHYModeNone</i> in the case of an error, 
 * or if the interface is not participating in a network.
 */
@property(readonly) CWPHYMode activePHYMode NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The current service set identifier (SSID) for the interface, encoded as a string.
 * @discussion Dynamically queries the interface for the current SSID. Returns <i>nil</i> 
 * in the case of an error, or if the interface is not 
 * participating in a network, or if the SSID can not be encoded as a valid UTF-8 or WinLatin1 string.
 */
@property(readonly) NSString *ssid NS_AVAILABLE_MAC(10_6);

/*!
 * @property
 * @abstract The current service set identifier (SSID) for the interface, returned as data.
 * @discussion Dynamically queries the interface for the current SSID. The SSID is 1-32 octets.
 * Returns <i>nil</i> in the case of an error, or if the interface is not 
 * participating in a network.
 */
@property(readonly) NSData *ssidData NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The current basic service set identifier (BSSID) for the interface, returned as a UTF-8 string. 
 * @discussion Dynamically queries the interface for the current BSSID. Returns a UTF-8 string formatted as 
 * <00:00:00:00:00:00>, or <i>nil</i> in the case of an error, or 
 * if the interface is not participating in a network.
 */
@property(readonly) NSString *bssid NS_AVAILABLE_MAC(10_6);

/*!
 * @property
 * @abstract The current aggregate received signal strength indication (RSSI) measurement (dBm) for the interface. 
 * @discussion Dynamically queries the interface for the current aggregate RSSI measurement.
 * Returns 0 in the case of an error, or if the interface is not 
 * participating in a network.
 */
@property(readonly) NSInteger rssiValue NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The current aggregate noise measurement (dBm) for the interface. 
 * @discussion Dynamically queries the interface for the current aggregate noise measurement.
 * Returns 0 in the case of an error, or if the interface is not 
 * participating in a network.
 */
@property(readonly) NSInteger noiseMeasurement NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The current security mode for the interface. 
 * @discussion Dynamically queries the interface for the security mode.
 * Returns <i>kCWSecurityUnknown</i> in the case of an error,
 * or if the interface is not participating in a network.
 */
@property(readonly) CWSecurity security NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The current transmit rate (Mbps) for the interface. 
 * @discussion Dynamically queries the interface for the current transmit rate.
 * Returns 0 in the case of an error, or if the interface is not 
 * participating in a network.
 */
@property(readonly) double transmitRate NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The current country code (ISO/IEC 3166-1:1997) for the interface. 
 * @discussion Dynamically queries the interface for the current country code.
 * Returns <i>nil</i> in the case of an error, or if the interface is <i>OFF</i>.
 */
@property(readonly) NSString *countryCode NS_AVAILABLE_MAC(10_6);

/*!
 * @property
 * @abstract The current mode for the interface.
 * @discussion Dynamically queries the interface for the current mode.
 * Returns <i>kCWInterfaceModeNone</i> in the case of an error,
 * or if the interface is not participating in a network.
 */
@property(readonly) CWInterfaceMode interfaceMode NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The current transmit power (mW) for the interface. 
 * @discussion Dynamically queries the interface for the current transmit power.
 * Returns 0 in the case of an error.
 */
@property(readonly) NSUInteger transmitPower NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The hardware media access control (MAC) address for the interface, returned as a UTF-8 string.
 * @discussion The standard format for printing a MAC-48 address <00:00:00:00:00:00> is used to represent 
 * the MAC address as a string. Returns <i>nil</i> in the case of an error.
 */
@property(readonly) NSString *hardwareAddress NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The interface has its corresponding hardware attached.
 * @discussion Returns <i>NO</i> in the case of an error.
 */
@property(readonly, assign) BOOL deviceAttached NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The interface has its corresponding network service enabled.
 * @discussion Returns <i>NO</i> in the case of an error.
 */
@property(readonly) BOOL serviceActive NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The networks currently in the scan cache for the WLAN interface. 
 * @discussion Returns <i>nil</i> in the case of an error.
 */
@property(readonly) NSSet *cachedScanResults NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 * @abstract The current configuration for the given WLAN interface.
 * @discussion Returns <i>nil</i> in the case of an error.
 */
@property(readonly) CWConfiguration *configuration NS_AVAILABLE_MAC(10_6);

/*! @methodgroup Getting all attached interfaces */
/*!
 * @method     
 * @result An NSSet object containing NSString objects representing BSD interface names.
 * @abstract Returns the list of BSD names for WLAN interfaces available on the current system.
 * @discussion Returns an NSArray of NSString objects representing the supported WLAN BSD interface 
 * names avaliable on the current system (i.e. "en1", "en2"). If there are no supported interfaces for 
 * the current system, then this method will return an empty NSArray object.
 * Returns <i>nil</i> in the case of an error.
 */
+ (NSSet *)interfaceNames NS_AVAILABLE_MAC(10_7);

/*! @methodgroup Getting an interface */
/*!
 * @method
 * @result An CWInterface object.
 * @abstract Convenience method for getting an CWInterface object for the default WLAN interface.
 */
+ (CWInterface *)interface NS_AVAILABLE_MAC(10_6);

/*!
 * @method
 * @param name An NSString representing the BSD name of a WLAN interface.
 * @result An CWInterface object configured to control the named CoreWLAN interface.
 * @abstract An instance method for obtaining an CWInterface object.
 * @discussion The interface name must be in the BSD name form (e.g. "en1"), and 
 * can be passed in explicitly or derived from the call to <i>+(NSString *)supportedInterfaces</i>.
 * If <i>name</i> is <i>nil</i>, the method returns an CWInterface object for the primary interface.
 * This method is the designated initializer for the CWInterface class.
 */
+ (CWInterface *)interfaceWithName:(NSString *)name NS_AVAILABLE_MAC(10_6);

/*!
 * @method
 * @param name An NSString representing the BSD name of a WLAN interface.
 * @result An CWInterface object configured to control the named CoreWLAN interface.
 * @abstract Convenience method for getting an CWInterface object with the specified name.
 * @discussion The interface name must be in the BSD name form (e.g. "en1"), and 
 * can be passed in explicitly or derived from the call to <i>+(NSString *)supportedInterfaces</i>.
 * If <i>name</i> is <i>nil</i>, the method returns an CWInterface object for the primary interface.
 */
- (id)initWithInterfaceName:(NSString *)name NS_AVAILABLE_MAC(10_6);

/*! @methodgroup Setting interface parameters */
/*!
 * @method
 * @param power A Boolean value corresponding to the power state. <i>NO</i> indicates the "OFF" state.
 * @param error An NSError object passed by reference, which will be populated with the error code and the error description
 * if an error occurs during the execution of this method. This parameter is optional and can be passed as <i>nil</i>.
 * @result A Boolean value which will indicate whether or not a failure occurred during execution. <i>YES</i> indicates no error occurred.
 * @abstract Sets the interface power state.
 * @discussion This operation may require an administrator password.
 */
- (BOOL)setPower:(BOOL)power error:(NSError **)error NS_AVAILABLE_MAC(10_6);

/*!
 * @method
 * @param channel A CWChannel object corresponding to the channel.
 * @param error An NSError object passed by reference, which will be populated with the error code and the error description
 * if an error occurs during the execution of this method. This parameter is optional and can be passed as <i>nil</i>.
 * @result A Boolean value which will indicate whether or not a failure occurred during execution. <i>YES</i> indicates no error occurred.
 * @abstract Sets the interface channel.
 * @discussion The channel cannot be changed if the interface is associated to a network.
 */
- (BOOL)setWLANChannel:(CWChannel *)channel error:(NSError **)error NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 * @param key An NSData object containing the pairwise master key (PMK).
 * @param error An NSError object passed by reference, which will be populated with the error code and the error description
 * if an error occurs during the execution of this method. This parameter is optional and can be passed as <i>nil</i>.
 * @result A Boolean value which will indicate whether or not a failure occurred during execution. <i>YES</i> indicates no error occurred. 
 * @abstract Sets the interface pairwise master key (PMK).
 * @discussion <i>key</i> must be 32 octets. If <i>key</i> is <i>nil</i>, 
 * this method clears the PMK for the interface.
 */
- (BOOL)setPairwiseMasterKey:(NSData *)key error:(NSError **)error NS_AVAILABLE_MAC(10_6);

/*!
 * @method
 * @param key An NSData object containing the WEP key.
 * @param flags An NSUInteger indicating which cipher key flags to use for the specified key. 
 * @param index An NSUInteger indicating which default key index to use for the specified key.
 * @param error An NSError object passed by reference, which will be populated with the error code and the error description
 * if an error occurs during the execution of this method. This parameter is optional and can be passed as <i>nil</i>.
 * @result A Boolean value which will indicate whether or not a failure occurred during execution. <i>YES</i> indicates no error occurred.
 * @abstract Sets the interface WEP key.
 * @discussion <i>key</i> must be 5 octets for WEP-40 or 13 octets for WEP-104. If <i>key</i> is <i>nil</i>, 
 * this method clears the WEP key for the interface. <i>index</i> must correspond to default key index 1-4.
 */
- (BOOL)setWEPKey:(NSData *)key flags:(CWCipherKeyFlags)flags index:(NSUInteger)index error:(NSError **)error NS_AVAILABLE_MAC(10_6);

/*! @methodgroup Scanning for networks */
/*!
 * @method
 * @param ssid The SSID for which to scan.
 * @param error An NSError object passed by reference, which will be populated with the error code and the error description
 * if an error occurs during the execution of this method. This parameter is optional and can be passed as <i>nil</i>.
 * @result A set of CWNetwork objects.
 * @abstract Scans for networks.
 * @discussion If <i>ssid</i> parameter is present, a directed scan will be performed by the 
 * interface, otherwise a broadcast scan will be performed. This method will block for the duration of the scan.
 */
- (NSSet *)scanForNetworksWithSSID:(NSData *)ssid error:(NSError **)error NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 * @param networkName The name (SSID) of the network for which to scan.
 * @param error An NSError object passed by reference, which will be populated with the error code and the error description
 * if an error occurs during the execution of this method. This parameter is optional and can be passed as <i>nil</i>.
 * @result A set of CWNetwork objects.
 * @abstract Scans for networks.
 * @discussion If <i>ssid</i> parameter is present, a directed scan will be performed by the 
 * interface, otherwise a broadcast scan will be performed. This method will block for the duration of the scan.
 */
- (NSSet *)scanForNetworksWithName:(NSString *)networkName error:(NSError **)error NS_AVAILABLE_MAC(10_7);

/*! @methodgroup Associating to a network */
/*!
 * @method
 * @param network The network to which the interface will associate.
 * @param password The network passphrase or key. Required for association to WEP, WPA Personal, and WPA2 Personal networks.
 * @param error An NSError object passed by reference, which will be populated with the error code and the error description
 * if an error occurs during the execution of this method. This parameter is optional and can be passed as <i>nil</i>.
 * @result A Boolean value which will indicate whether or not a failure occurred during execution. <i>YES</i> indicates no error occurred.
 * @abstract Associates to a given network using the given network passphrase.
 * @discussion This method will block for the duration of the association. This operation may require an administrator password.
 */
- (BOOL)associateToNetwork:(CWNetwork *)network password:(NSString *)password error:(NSError **)error NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 * @param network The network to which the interface will associate.
 * @param username The username to use for IEEE 802.1X authentication.
 * @param password The password to use for IEEE 802.1X authentication.
 * @param identity The identity to use for IEEE 802.1X authentication. Holds the corresponding client certificate. 
 * @param error An NSError object passed by reference, which will be populated with the error code and the error description
 * if an error occurs during the execution of this method. This parameter is optional and can be passed as <i>nil</i>.
 * @result A Boolean value which will indicate whether or not a failure occurred during execution. <i>YES</i> indicates no error occurred.
 * @abstract Connects to the given enterprise network.
 * @discussion This method will block for the duration of the association. This operation may require an administrator password.
 */
- (BOOL)associateToEnterpriseNetwork:(CWNetwork *)network identity:(SecIdentityRef)identity username:(NSString *)username password:(NSString *)password error:(NSError **)error NS_AVAILABLE_MAC(10_7);


/*! @methodgroup Creating computer-to-computer networks */
/*!
 * @method
 * @param name The network name. This parameter is optional and may be passed as <i>nil</i>.
 * @param security The security type to be used.
 * @param channel The channel on which the network will be created.
 * @param password The password to be used. This paramter is not applicable to open system authentication.
 * @result A Boolean value which will indicate whether or not a failure occurred during execution. <i>YES</i> indicates no error occurred.
 * @abstract Creates a computer-to-computer (ad-hoc) network with the given network name, security type, and password on the specified channel.
 * @discussion If <i>name</i> is <i>nil</i>, the machine name will be used as the network name.
 * This operation may require an administrator password.
 */
- (BOOL)startIBSSModeWithSSID:(NSData *)ssidData security:(CWIBSSModeSecurity)security channel:(NSUInteger)channel password:(NSString *)password error:(NSError **)error NS_AVAILABLE_MAC(10_7);

/*! @methodgroup Disassociating from a network */
/*!
 * @method
 * @abstract Disassociates from the current network.
 * @discussion This method has no effect if the interface is not associated to a network.
 * This operation may require an administrator password.
 */
- (void)disassociate NS_AVAILABLE_MAC(10_6);

/*! @methodgroup Committing a configuration */
/*!
 * @method
 * @param configuration The configuration to commit.
 * @param authorization An SFAuthorization object to use for authorizing the commit. This parameter is optional 
 * and can be passed as <i>nil</i>.
 * @param error An NSError object passed by reference, which will be populated with the error code and the error description
 * if an error occurs during the execution of this method. This parameter is optional and can be passed as <i>nil</i>.
 * @result A Boolean value which will indicate whether or not a failure occurred during execution. <i>YES</i> indicates no error occurred. 
 * @abstract Commit a configuration for the given WLAN interface.
 * @discussion This method requires the caller have root privileges 
 * or obtain administrator privileges with the <i>authorization</i> parameter.
 */
- (BOOL)commitConfiguration:(CWConfiguration *)configuration authorization:(SFAuthorization *)authorization error:(NSError **)error NS_AVAILABLE_MAC(10_7);
@end

#endif /* _CORE_WLAN_INTERFACE_H_ */
