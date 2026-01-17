/*!
 * @header CWGlobals.h
 * @copyright 2009 Apple Inc. All rights reserved.
 * @version 1.0.0
 */

#ifndef _CORE_WLAN_GLOBALS_H_
#define _CORE_WLAN_GLOBALS_H_

#import <Foundation/Foundation.h>

/*!
 * @enum CWErr
 * @const kCWNoErr Success.
 * @const kCWParamErr Parameter error.
 * @const kCWNoMemErr Memory allocation failed.
 * @const kCWUknownErr Unexpected error condition encountered for which no error code exists.
 * @const kCWNotSupportedErr Operation not supported.
 * @const kCWFormatErr Invalid protocol element field detected.
 * @const kCWTimeoutErr Authentication/Association timed out.
 * @const kCWUnspecifiedFailureErr Access point did not specify a reason for authentication/association failure.
 * @const kCWUnsupportedCapabilitiesErr Access point cannot support all requested capabilities.
 * @const kCWReassociationDeniedErr Reassociation was denied because the access point was unable to determine that an association exists.
 * @const kCWAssociationDeniedErr Association was denied for an unspecified reason.
 * @const kCWAuthAlgUnsupportedErr Specified authentication algorithm is not supported.
 * @const kCWInvalidAuthSeqNumErr Authentication frame received with an authentication sequence number out of expected sequence.
 * @const kCWChallengeFailureErr Authentication was rejected because of a challenge failure.
 * @const kCWAPFullErr Access point is unable to handle another associated station.
 * @const kCWUnsupportedRateSetErr Interface does not support all of the rates in the access point's basic rate set.
 * @const kCWShortSlotUnsupportedErr Association denied because short slot time option is not supported by requesting station.
 * @const kCWDSSSOFDMUnsupportedErr Association denied because DSSS-OFDM is not supported by requesting station.
 * @const kCWInvalidInfoElementErr Invalid information element included in association request.
 * @const kCWInvalidGroupCipherErr Invalid group cipher requested.
 * @const kCWInvalidPairwiseCipherErr Invalid pairwise cipher requested.
 * @const kCWInvalidAKMPErr Invalid authentication selector requested.
 * @const kCWUnsupportedRSNVersionErr Invalid WPA/WPA2 version specified.
 * @const kCWInvalidRSNCapabilitiesErr Invalid RSN capabilities specified in association request.
 * @const kCWCipherSuiteRejectedErr Cipher suite rejected due to network security policy.
 * @const kCWInvalidPMKErr PMK rejected by the access point.
 * @const kCWSupplicantTimeoutErr WPA/WPA2 handshake timed out.
 * @const kCWHTFeaturesNotSupported Association was denied because the requesting station does not support HT features.
 * @const kCWPCOTransitionTimeNotSupported Association was denied because the requesting station does not support the 
 * PCO transition time required by the AP.
 * @const kCWRefNotBoundErr No interface is bound to the CWInterface.
 * @const kCWIPCError Error communicating with a separate process.
 * @const kCWOpNotPermitted Calling process does not have permission to perform this operation.
 * @const kCWError Generic error, no specific error code exists to describe the error condition.
 */
typedef enum
{
	kCWNoErr							=  0,
	kCWParamErr							= -3900,
	kCWNoMemErr							= -3901,
	kCWUknownErr						= -3902,
	kCWNotSupportedErr					= -3903,
	kCWFormatErr						= -3904,
	kCWTimeoutErr						= -3905,
	kCWUnspecifiedFailureErr			= -3906,
	kCWUnsupportedCapabilitiesErr		= -3907,
	kCWReassociationDeniedErr			= -3908,
	kCWAssociationDeniedErr				= -3909,
	kCWAuthAlgUnsupportedErr			= -3910,
	kCWInvalidAuthSeqNumErr				= -3911,
	kCWChallengeFailureErr				= -3912,
	kCWAPFullErr						= -3913,
	kCWUnsupportedRateSetErr			= -3914,
	kCWShortSlotUnsupportedErr			= -3915,
	kCWDSSSOFDMUnsupportedErr			= -3916,
	kCWInvalidInfoElementErr			= -3917,
	kCWInvalidGroupCipherErr			= -3918,
	kCWInvalidPairwiseCipherErr			= -3919,
	kCWInvalidAKMPErr					= -3920,
	kCWUnsupportedRSNVersionErr			= -3921,
	kCWInvalidRSNCapabilitiesErr		= -3922,
	kCWCipherSuiteRejectedErr			= -3923,
	kCWInvalidPMKErr					= -3924,
	kCWSupplicantTimeoutErr				= -3925,
	kCWHTFeaturesNotSupported			= -3926,
	kCWPCOTransitionTimeNotSupported	= -3927,
	kCWRefNotBoundErr					= -3928,
	kCWIPCError							= -3929,
	kCWOpNotPermitted					= -3930,
	kCWError							= -3931,
} CWErr;

/*!
 * @enum CWPHYMode
 * @const kCWPHYMode11A IEEE 802.11a PHY.
 * @const kCWPHYMode11B IEEE 802.11b PHY.
 * @const kCWPHYMode11G IEEE 802.11g PHY.
 * @const kCWPHYMode11N IEEE 802.11n PHY.
 * @discussion CoreWLAN physical layer modes.
 */
typedef enum
{
	kCWPHYMode11A	= 0,
	kCWPHYMode11B,
	kCWPHYMode11G,
	kCWPHYMode11N
} CWPHYMode;

/*!
 * @enum CWOpMode
 * @const kCWOpModeStation Interface is participating in an infrastructure network as a non-AP station.
 * @const kCWOpModeIBSS Interface is participating in an IBSS network.
 * @const kCWOpModeHostAP Interface is participating in an infrastructure network as an access point.
 * @const kCWOpModeMonitorMode Interface is in 802.11 monitor mode.
 * @discussion CoreWLAN interface operation modes.
 */
typedef enum
{
	kCWOpModeStation	= 0,
	kCWOpModeIBSS,
	kCWOpModeMonitorMode,
	kCWOpModeHostAP
} CWOpMode;

/*!
 * @enum CWSecurityMode
 * @const kCWSecurityModeOpen Open System authentication.
 * @const kCWSecurityModeWEP WEP authentication.
 * @const kCWSecurityModeWPA_PSK WPA Personal authentication.
 * @const kCWSecurityModeWPA2_PSK WPA2 Personal authentication.
 * @const kCWSecurityModeWPA_Enterprise WPA Enterprise authentication.
 * @const kCWSecurityModeWPA2_Enterprise WPA2 Enterprise authentication.
 * @const kCWSecurityModeWPS WiFi Protected Setup authentication.
 * @const kCWSecurityModeDynamicWEP Dynamic WEP 802.1X authentication.
 * @discussion CoreWLAN security modes.
 */
typedef enum
{
	kCWSecurityModeOpen	= 0,
	kCWSecurityModeWEP,
	kCWSecurityModeWPA_PSK,
	kCWSecurityModeWPA2_PSK,
	kCWSecurityModeWPA_Enterprise,
	kCWSecurityModeWPA2_Enterprise,
	kCWSecurityModeWPS,
	kCWSecurityModeDynamicWEP
} CWSecurityMode;

/*!
 * @enum CWInterfaceState
 * @const kCWInterfaceStateInactive CoreWLAN interface is in the initial, inactive state.
 * @const kCWInterfaceStateScanning CoreWLAN interface is scanning.
 * @const kCWInterfaceStateAuthenticating CoreWLAN interface is authenticating.
 * @const kCWInterfaceStateAssociating CoreWLAN interface is associating.
 * @const kCWInterfaceStateRunning CoreWLAN interface is running.
 * @discussion CoreWLAN interface states.
 */
typedef enum
{
	kCWInterfaceStateInactive			= 0,
	kCWInterfaceStateScanning,
	kCWInterfaceStateAuthenticating,
	kCWInterfaceStateAssociating,
	kCWInterfaceStateRunning
} CWInterfaceState;

/*!
 * @enum CWScanType
 * @const kCWScanTypeActive In accordance with the supported channels for the active country code, the interface 
 * will transmit probe request frames and listen for probe responses.
 * @const kCWScanTypePassive The interface will listen for beacon frames on each channel irrespective of country code.
 * @const kCWScanTypeFast The scan will return cached scan results.
 * @discussion CoreWLAN scan types.
 */
typedef enum
{
	kCWScanTypeActive		= 0,
	kCWScanTypePassive,
	kCWScanTypeFast
} CWScanType;

#pragma mark Error Domain
/*! @group Error Domain */
/*!
 * @const kCWErrorDomain 
 * @abstract error domain for NSErrors returned by calls to CWInterface
 */
extern NSString * const kCWErrorDomain __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

#pragma mark Notifications
/*! @group Notifications */
/*!
 * @const kCWPowerDidChangeNotification
 * @discussion Posted when the power state of the CoreWLAN interface changes.  This notification does not contain a <i>userInfo</i> dictionary.
 */
extern NSString * const kCWPowerDidChangeNotification __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @const kCWSSIDDidChangeNotification
 * @discussion Posted when the SSID of the CoreWLAN interface changes.  This notification does not contain a <i>userInfo</i> dictionary.
 */

extern NSString * const kCWSSIDDidChangeNotification __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @const kCWBSSIDDidChangeNotification
 * @discussion Posted when the BSSID of the wireless interface changes.  This notification does not contain a <i>userInfo</i> dictionary.
 */
extern NSString * const kCWBSSIDDidChangeNotification __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @const kCWLinkDidChangeNotification
 * @discussion Posted when the link state of the CoreWLAN interface changes.  This notification does not contain a <i>userInfo</i> dictionary.
 */
extern NSString * const kCWLinkDidChangeNotification __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @const kCWModeDidChangeNotification
 * @discussion Posted when the op mode of the CoreWLAN interface changes.  This notification does not contain a <i>userInfo</i> dictionary.
 */
extern NSString * const kCWModeDidChangeNotification __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @const kCWCountryCodeDidChangeNotification
 * @discussion Posted when the country code of the CoreWLAN interface changes.  This notification does not contain a <i>userInfo</i> dictionary.
 */
extern NSString * const kCWCountryCodeDidChangeNotification __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

#pragma mark Association Parameter Keys
/*! @group Association Parameter Keys */
/*!
 * @const kCWAssocKeyPassphrase
 * @discussion NSString containing network passphrase or key. Required for association to WEP and WPA/WPA2 Personal networks.
 */
extern NSString * const kCWAssocKeyPassphrase __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @const kCWAssocKey8021XProfile
 * @discussion CW8021XProfile object containing the network IEEE 802.1X profile.  Required for association 
 * to IEEE 802.1X dynamic WEP and WPA/WPA2 Enterprise networks.
 */
extern NSString * const kCWAssocKey8021XProfile __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

#pragma mark IBSS Parameter Keys
/*! @group IBSS Parameter Keys */
/*!
 * @const kCWIBSSKeySSID
 * @discussion NSString containing the SSID of the network to be created.
 */
extern NSString * const kCWIBSSKeySSID __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @const kCWIBSSKeyChannel
 * @discussion NSNumber containing the channel number on which the network will be created.  Defaults to channel 11.
 */
extern NSString * const kCWIBSSKeyChannel __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @const kCWIBSSKeyPassphrase
 * @discussion NSString containing network cipher key.  40-bit and 104-bit WEP modes are currently supported. 
 * Cipher mode is inferred from the key length. A cipher key that has 5 characters or has 10 hexidecimal characters 
 * corresponds to a 40-bit WEP key. A cipher key that has 13 characters or has 26 hexidecimal characters corresponds 
 * to a 104-bit WEP key. If this key is not present, then no cipher key will be used on the network.
 */
extern NSString * const kCWIBSSKeyPassphrase __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

#pragma mark Scan Parameter Keys
/*! @group Scan Parameter Keys */
/*!
 * @const kCWScanKeySSID
 * @discussion NSString containing the target SSID of a directed scan request.
 */
extern NSString * const kCWScanKeySSID __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @const kCWScanKeyBSSID
 * @discussion NSString containing the target BSSID of a directed scan request.
 */
extern NSString * const kCWScanKeyBSSID __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @const kCWScanKeyMerge
 * @discussion NSNumber boolean value indicating whether or not duplicate SSID entries should be included 
 * in the scan results.  A value evaluating to <i>true</i> will include the BSSID with the strongest 
 * signal strength and remove all other duplicate SSID entries. Defaults to <i>true</i>.
 */
extern NSString * const kCWScanKeyMerge __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @const kCWScanKeyScanType
 * @discussion NSString indicating the type of scan to perform.  Defaults to <i>APScanTypeActive</i>.
 */
extern NSString * const kCWScanKeyScanType __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @const kCWScanKeyDwellTime
 * @discussion NSNumber specifying the time in milliseconds that the interface will spend on each channel 
 * listening for beacon frames and probe responses.  Defaults to driver default.
 */
extern NSString * const kCWScanKeyDwellTime __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @const kCWScanKeyRestTime
 * @discussion NSNumber specifying the time in milliseconds that the interface will spend on its home channels 
 * between intervals of off-channel activity during the scan request.  Defaults to driver default.
 */
extern NSString * const kCWScanKeyRestTime __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

#pragma mark Cipher Key Flags
/*! @group Cipher Key Flags */
/*!
 * @const kCWCipherKeyFlagsMulticast
 * @discussion Cipher key will be used for multicast packets.
 */
extern NSUInteger const kCWCipherKeyFlagsMulticast __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @const kCWCipherKeyFlagsTx
 * @discussion Cipher key will be used for packets sent from the interface.
 */
extern NSUInteger const kCWCipherKeyFlagsTx __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @const kCWCipherKeyFlagsRx
 * @discussion Cipher key will be used for packets received by the interface.
 */
extern NSUInteger const kCWCipherKeyFlagsRx __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @const kCWCipherKeyFlagsUnicast
 * @discussion Cipher key will be used for unicast packets.
 */
extern NSUInteger const kCWCipherKeyFlagsUnicast __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );	

#endif /* _CORE_WLAN_GLOBALS_H_ */
