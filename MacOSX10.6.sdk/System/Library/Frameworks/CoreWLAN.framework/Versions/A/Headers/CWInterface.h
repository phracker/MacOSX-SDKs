/*!
 * @header CWInterface.h
 * @copyright 2009 Apple Inc. All rights reserved.
 * @version 1.0.0
 */

#ifndef _CORE_WLAN_INTERFACE_H_
#define _CORE_WLAN_INTERFACE_H_

@class CWNetwork;
@class CWConfiguration;
@class SFAuthorization;

/*!
 * @class
 * @abstract CoreWLAN interface 
 * @discussion Encapsulates an CoreWLAN interface providing controlled access to various interface operations such as scanning, 
 * assocation, and IBSS creation, and providing a means to query and manipulate interface parameters. 
 */
@interface CWInterface : NSObject 

/*!
 * @property
 * @abstract Authorization object which is used to commit configuration changes.
 */
@property(readwrite, retain) SFAuthorization *authorization __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract CoreWLAN interface supports wake on wireless capability. 
 */
@property(readonly) BOOL supportsWoW __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract CoreWLAN interface supports WEP authentication (IEEE 802.11 Wired Equivalent Privacy). 
 */
@property(readonly) BOOL supportsWEP __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract CoreWLAN interface supports AES-CCM (IEEE 802.11i Advanced Encryption Standard - Counter Mode 
 * with Cipher-Block Chaining Message Authentication Code). 
 */
@property(readonly) BOOL supportsAES_CCM __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract CoreWLAN interface supports IBSS networks (IEEE 802.11 Independent Basic Service Set). 
 */
@property(readonly) BOOL supportsIBSS __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract CoreWLAN interface supports TKIP (IEEE 802.11i Temporal Key Integrity Protocol). 
 */
@property(readonly) BOOL supportsTKIP __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract CoreWLAN interface supports power save modes. 
 */
@property(readonly) BOOL supportsPMGT __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract CoreWLAN interface supports host access point mode. 
 */
@property(readonly) BOOL supportsHostAP __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract CoreWLAN interface supports monitor mode. 
 */
@property(readonly) BOOL supportsMonitorMode __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract CoreWLAN interface supports WPA (Wi-Fi Alliance Wi-Fi Protected Access). 
 */
@property(readonly) BOOL supportsWPA __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract CoreWLAN interface supports WPA2 (Wi-Fi Alliance Wi-Fi Protected Access 2). 
 */
@property(readonly) BOOL supportsWPA2 __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract CoreWLAN interface supports WME (IEEE 802.11e Wireless Multimedia Extensions).
 */
@property(readonly) BOOL supportsWME __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract CoreWLAN interface supports short guard interval in 40MHz channels.
 */
@property(readonly) BOOL supportsShortGI40MHz __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract CoreWLAN interface supports short guard interval in 20MHz channels. 
 */
@property(readonly) BOOL supportsShortGI20MHz __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract CoreWLAN interface supports TSN authentication (Transitional Security Network). 
 */
@property(readonly) BOOL supportsTSN __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Current power state for the CoreWLAN interface.
 * @discussion Dynamically queries the interface for the current power state.
 */
@property(readonly) BOOL power __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Current power save state for the CoreWLAN interface. 
 * @discussion Dynamically queries the interface for the current power save state.
 */
@property(readonly) BOOL powerSave __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract BSD name for the CoreWLAN interface. 
 */
@property(readonly) NSString * name __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Array of channels (NSNumber) supported by the CoreWLAN interface for the active country code.
 * @discussion Dynamically queries the interface for the supported channels.
 */
@property(readonly) NSArray *supportedChannels __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Array PHY modes (NSNumber) supported by the CoreWLAN interface. 
 * @discussion Dynamically queries the interface for the supported PHY modes.
 * @see //apple_ref/occ/tdef/CWPHYMode CWPHYMode
 */
@property(readonly) NSArray *supportedPHYModes __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Current channel of the CoreWLAN interface. 
 * @discussion Dynamically queries the interface for the current channel.
 */
@property(readonly) NSNumber *channel __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Current active PHY mode of the CoreWLAN interface. 
 * @discussion Dynamically queries the interface for the current active PHY mode.
 * @see //apple_ref/occ/tdef/CWPHYMode CWPHYMode
 */
@property(readonly) NSNumber *phyMode __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Current SSID of the CoreWLAN interface.
 * @discussion Dynamically queries the interface for the current SSID.
 */
@property(readonly) NSString *ssid __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Current BSSID of the CoreWLAN interface. 
 * @discussion Dynamically queries the interface for the current BSSID.
 */
@property(readonly) NSString *bssid __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Current BSSID of the CoreWLAN interface. 
 * @discussion Dynamically queries the interface for the current BSSID.
 */
@property(readonly) NSData *bssidData __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Current aggregate RSSI measurement (dBm) of the CoreWLAN interface. 
 * @discussion Dynamically queries the interface for the current aggregate RSSI measurement.
 */
@property(readonly) NSNumber *rssi __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Current aggregate noise measurement (dBm) of the CoreWLAN interface. 
 * @discussion Dynamically queries the interface for the current aggregate noise measurement.
 */
@property(readonly) NSNumber *noise __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Current transmit rate (Mbps) of the CoreWLAN interface. 
 * @discussion Dynamically queries the interface for the current transmit rate.
 */
@property(readonly) NSNumber *txRate __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Current security mode of the CoreWLAN interface. 
 * @discussion Dynamically queries the interface for the current security mode.
 * @see //apple_ref/occ/tdef/CWSecurityMode CWSecurityMode
 */
@property(readonly) NSNumber *securityMode __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Current state of the CoreWLAN interface.
 * @discussion Dynamically queries the interface for the current interface state.
 * @see //apple_ref/occ/tdef/CWInterfaceState CWInterfaceState
 */
@property(readonly) NSNumber *interfaceState __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Country code (ISO/IEC 3166-1:1997) of the CoreWLAN interface. 
 * @discussion Dynamically queries the interface for the current country code.
 */
@property(readonly) NSString *countryCode __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Current operation mode of the CoreWLAN interface.
 * @discussion Dynamically queries the interface for the current operation mode.
 * @see //apple_ref/occ/tdef/CWOpMode CWOpMode
 */
@property(readonly) NSNumber *opMode __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Current target transmit power (mW) of the CoreWLAN interface. 
 * @discussion Dynamically queries the interface for the current transmit power.
 */
@property(readonly) NSNumber *txPower __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Current stored configuration for the CoreWLAN interface. 
 */
@property(readonly) CWConfiguration *configuration __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*! @methodgroup Getting all supported interfaces */
/*!
 * @method     
 * @result An NSArray object containing NSString objects representing CoreWLAN interface names.
 * @abstract Returns the list of CoreWLAN interfaces available on the current system.
 * @discussion Returns an NSArray of NSString objects representing the supported CoreWLAN interface 
 * names avaliable on the current system (i.e. "en1", "en2").  If there are no supported interfaces for the current system,
 * then this method will return an empty NSArray object.
 */
+ (NSArray*)supportedInterfaces __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*! @methodgroup Getting an interface */
/*!
 * @method
 * @result An CWInterface object.
 * @abstract Creates and returns an CWInterface for the primary interface.
 */
- (CWInterface*)init __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @method
 * @result An CWInterface object.
 * @abstract Convenience method for getting an CWInterface object for the primary interface.
 */
+ (CWInterface*)interface __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @method
 * @param name An NSString representing the name of an Airport interface.
 * @result An CWInterface object configured to control the named CoreWLAN interface.
 * @abstract An instance method for obtaining an CWInterface object.
 * @discussion The interface name must be in the BSD name form (e.g. "en1"), and 
 * can be passed in explicitly or derived from the call to <i>+(NSString*)supportedInterfaces</i>.  
 * If <i>name</i> is <i>nil</i>, the method returns an CWInterface object for the primary interface.
 * This method is the designated initializer for the CWInterface class.
 */
+ (CWInterface*)interfaceWithName:(NSString*)name __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @method
 * @param name An NSString representing the name of an Airport interface.
 * @result An CWInterface object configured to control the named CoreWLAN interface.
 * @abstract Convenience method for getting an CWInterface object with the specified name.
 * @discussion The interface name must be in the BSD name form (e.g. "en1"), and 
 * can be passed in explicitly or derived from the call to <i>+(NSString*)supportedInterfaces</i>.  
 * If <i>name</i> is <i>nil</i>, the method returns an CWInterface object for the primary interface.
 */
- (CWInterface*)initWithInterfaceName:(NSString*)name __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*! @methodgroup Comparing interfaces */
/*!
 * @method
 * @param interface The CWInterface object for which to test equality.
 * @result <i>YES</i> if the objects are equal.
 * @abstract Method for determining CWInterface object equality.
 * @discussion Two CWInterface objects are considered equal if their corresponding <i>name</i> and capabilities properties are equal. 
 */
- (BOOL)isEqualToInterface:(CWInterface*)interface __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*! @methodgroup Setting interface parameters */
/*!
 * @method
 * @param power A BOOL value indicating the power state to which the CoreWLAN interface should be set.  
 * <i>NO</i> indicates the "OFF" state.
 * @param error An NSError object passed by reference, which will be populated with error code and error description
 * if an error occurs during the execution of the method.  This parameter is optional and can be passed as <i>nil</i>.
 * @result A BOOL value which will indicate whether or not a failure occured.  <i>YES</i> indicates no error occured.
 * @abstract Sets the power state for the given CoreWLAN interface.
 * @discussion This method may prompt for an administrator password if the corresponding preference is enabled in the current configuration.
 */
- (BOOL)setPower:(BOOL)power error:(NSError**)error __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @method
 * @param channel An NSUInteger object representing the channel to which the CoreWLAN interface should be tuned.  
 * @param error An NSError object passed by reference, which will be populated with error code and error description
 * if an error occurs during the execution of the method.  This parameter is optional and can be passed as <i>nil</i>.
 * @result A BOOL value which will indicate whether or not a failure occured.  <i>YES</i> indicates no error occured.
 * @abstract Sets the channel for the given CoreWLAN interface.
 * @discussion The current channel cannot be changed if the CoreWLAN interface is associated to a network.  <i>channel</i>
 * must be supported by the given interface.
 */
- (BOOL)setChannel:(NSUInteger)channel error:(NSError**)error __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @method
 * @param key An NSData object containing the pairwise master key (PMK).  
 * @param error An NSError object passed by reference, which will be populated with error code and error description
 * if an error occurs during the execution of the method.  This parameter is optional and can be passed as <i>nil</i>.
 * @result A BOOL value which will indicate whether or not a failure occured.  <i>YES</i> indicates no error occured.
 * @abstract Sets the interface pairwise master key (PMK).
 * @discussion <i>key</i> must be 32 octets.  If <i>key</i> is <i>nil</i>, 
 * this method clears the PMK for the interface.
 */
- (BOOL)setPairwiseMasterKey:(NSData*)key error:(NSError**)error __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @method
 * @param key An NSData object containing the WEP key.  
 * @param flags An NSUInteger indicating which cipher key flags to use for the specified key. 
 * @param index An NSUInteger indicating which default key index to use for the specified key.
 * @param error An NSError object passed by reference, which will be populated with error code and error description
 * if an error occurs during the execution of the method.  This parameter is optional and can be passed as <i>nil</i>.
 * @result A BOOL value which will indicate whether or not a failure occured.  <i>YES</i> indicates no error occured. 
 * @abstract Sets the interface WEP key.
 * @discussion <i>key</i> must be 5 octets for WEP-40 or 13 octets for WEP-104. If <i>key</i> is <i>nil</i>, 
 * this method clears the WEP key for the interface.  <i>index</i> must correspond to default key index 1-4.
 */
- (BOOL)setWEPKey:(NSData*)key flags:(NSUInteger)flags index:(NSUInteger)index error:(NSError**)error __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*! @methodgroup Scanning for networks */
/*!
 * @method
 * @param parameters An NSDicitonary object containing optional scan parameters which can be used to control the behavior of the scan.
 * This parameter is optional and may be passed as <i>nil</i>.
 * @param error An NSError object passed by reference, which will be populated with error code and error description
 * if an error occurs during the execution of the method.  This parameter is optional and can be passed as <i>nil</i>.
 * @result An NSArray object containing CWNetwork objects representing the networks found in the scan.
 * @abstract Performs a scan with the given CoreWLAN interface, returning any found networks.
 * @discussion See the scan parameters defined in CWGlobals.h for controlling scan behavior.  
 * If no scan parameters are present, the default behavior is to perform a broadcast scan on active channels, for 
 * all supported PHY modes.  This method will block for the duration of the scan.
 */
- (NSArray*)scanForNetworksWithParameters:(NSDictionary*)parameters error:(NSError**)error __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*! @methodgroup Associating to a network */
/*!
 * @method
 * @param parameters An NSDicitonary object containing association parameters.
 * @param error An NSError object passed by reference, which will be populated with error code and error description
 * if an error occurs during the execution of the method.  This parameter is optional and can be passed as <i>nil</i>.
 * @result A BOOL value which will indicate whether or not a failure occured.  <i>YES</i> indicates no error occured.
 * @abstract Attempts to associate to the given CWNetwork, with the given association parameters.
 * @discussion See the association parameters defined in CWGlobals.h for more information.  Certain networks will require specific 
 * authentication credentials for association (i.e. a network using WPA2 Personal authentication will require a passphrase).  This method will
 * block for the duration of the association.  This method may prompt for an administrator password if the corresponding preference is enabled in the current configuration.
 */
- (BOOL)associateToNetwork:(CWNetwork*)network parameters:(NSDictionary*)parameters error:(NSError**)error __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @method
 * @abstract Disassociates the CoreWLAN interface from the currently associated network.
 * @discussion This method is a no-op if the given CoreWLAN interface is not associated to a network.  
 * This method may prompt for an administrator password if the corresponding preference is enabled in the current configuration.
 */
- (void)disassociate __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*! @methodgroup Creating computer-to-computer networks */
/*!
 * @method
 * @param parameters An NSDicitonary object containing optional parameters for creating an IBSS network.  This parameter is optional
 * and may be passed as <i>nil</i>.
 * @param error An NSError object passed by reference, which will be populated with error code and error description
 * if an error occurs during the execution of the method.  This parameter is optional and can be passed as <i>nil</i>.
 * @result A BOOL value which will indicate whether or not a failure occured.  <i>YES</i> indicates no error occured.
 * @abstract Attempts to create a computer-to-computer network with the given parameters.
 * @discussion See the IBSS creation parameters defined in CWGlobals.h for more information.  If no IBSS creation parameters
 * are present, the default behavior is to create an open authentication computer-to-computer network using the machine name as the 
 * network name.  This method may prompt for an administrator password if the corresponding preference is enabled in the current configuration.
 */
- (BOOL)enableIBSSWithParameters:(NSDictionary*)parameters error:(NSError**)error __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*! @methodgroup Changing the interface configuration */
/*!
 * @method
 * @param config An CWConfiguration object containing the desired changes to the current CW configuration preferences.
 * @param error An NSError object passed by reference, which will be populated with error code and error description
 * if an error occurs during the execution of the method.  This parameter is optional and can be passed as <i>nil</i>.
 * @result A BOOL value which will indicate whether or not a failure occured.  <i>YES</i> indicates no error occured.
 * @abstract Attempts to change the current CW configuration.
 * @discussion This method uses the SFAuthorization property of the given CWInterface object to commit the given configuration.
 * The SFAuthorization property must be authorized with administrative privileges.
 */
- (BOOL)commitConfiguration:(CWConfiguration*)config error:(NSError**)error __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );
@end

#endif /* _CORE_WLAN_INTERFACE_H_ */
