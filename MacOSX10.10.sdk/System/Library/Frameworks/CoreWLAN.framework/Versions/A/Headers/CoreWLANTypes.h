/*!
 * @header CoreWLANTypes.h
 * @copyright 2010-2014 Apple Inc. All rights reserved.
 */

#ifndef _CORE_WLAN_TYPES_H_
#define _CORE_WLAN_TYPES_H_

#import <Foundation/Foundation.h>

/*!
 * @typedef CWErr
 *
 * @abstract Error codes corresponding to the CWErrorDomain domain.
 *
 * @constant kCWNoErr
 * Success.
 *
 * @constant kCWEAPOLErr
 * EAPOL-related error.
 *
 * @constant kCWInvalidParameterErr
 * Parameter error.
 *
 * @constant kCWNoMemoryErr
 * Memory allocation failed.
 *
 * @constant kCWUnknownErr
 * Unexpected error condition encountered for which no error code exists.
 *
 * @constant kCWNotSupportedErr
 * Operation not supported.
 *
 * @constant kCWInvalidFormatErr
 * Invalid protocol element field detected.
 *
 * @constant kCWTimeoutErr 
 * Operation timed out.
 *
 * @constant kCWUnspecifiedFailureErr 
 * Access point did not specify a reason for authentication/association failure.
 *
 * @constant kCWUnsupportedCapabilitiesErr
 * Access point cannot support all requested capabilities.
 *
 * @constant kCWReassociationDeniedErr
 * Reassociation was denied because the access point was unable to determine that an association exists.
 *
 * @constant kCWAssociationDeniedErr
 * Association was denied for an unspecified reason.
 *
 * @constant kCWAuthenticationAlgorithmUnsupportedErr
 * Specified authentication algorithm is not supported.
 *
 * @constant kCWInvalidAuthenticationSequenceNumberErr 
 * Authentication frame received with an authentication sequence number out of expected sequence.
 *
 * @constant kCWChallengeFailureErr
 * Authentication was rejected because of a challenge failure.
 *
 * @constant kCWAPFullErr
 * Access point is unable to handle another associated station.
 *
 * @constant kCWUnsupportedRateSetErr
 * Interface does not support all of the rates in the basic rate set of the access point.
 *
 * @constant kCWShortSlotUnsupportedErr
 * Association denied because short slot time option is not supported by requesting station.
 *
 * @constant kCWDSSSOFDMUnsupportedErr
 * Association denied because DSSS-OFDM is not supported by requesting station.
 *
 * @constant kCWInvalidInformationElementErr
 * Invalid information element included in association request.
 *
 * @constant kCWInvalidGroupCipherErr
 * Invalid group cipher requested.
 *
 * @constant kCWInvalidPairwiseCipherErr
 * Invalid pairwise cipher requested.
 *
 * @constant kCWInvalidAKMPErr 
 * Invalid authentication selector requested.
 *
 * @constant kCWUnsupportedRSNVersionErr 
 * Invalid WPA/WPA2 version specified.
 *
 * @constant kCWInvalidRSNCapabilitiesErr 
 * Invalid RSN capabilities specified in association request.
 *
 * @constant kCWCipherSuiteRejectedErr 
 * Cipher suite rejected due to network security policy.
 *
 * @constant kCWInvalidPMKErr 
 * PMK rejected by the access point.
 *
 * @constant kCWSupplicantTimeoutErr 
 * WPA/WPA2 handshake timed out.
 *
 * @constant kCWHTFeaturesNotSupportedErr 
 * Association was denied because the requesting station does not support HT features.
 *
 * @constant kCWPCOTransitionTimeNotSupportedErr
 * Association was denied because the requesting station does not support the PCO transition time required by the AP.
 *
 * @constant kCWReferenceNotBoundErr 
 * No interface is bound to the CWInterface object.
 *
 * @constant kCWIPCFailureErr 
 * Error communicating with a separate process.
 *
 * @constant kCWOperationNotPermittedErr 
 * Calling process does not have permission to perform this operation.
 *
 * @constant kCWErr 
 * Generic error, no specific error code exists to describe the error condition.
 */
typedef NS_ENUM(NSInteger, CWErr)
{
    kCWNoErr									= 0,
	kCWEAPOLErr									= 1,
	kCWInvalidParameterErr						= -3900,
	kCWNoMemoryErr								= -3901,
	kCWUnknownErr								= -3902,
	kCWNotSupportedErr							= -3903,
	kCWInvalidFormatErr							= -3904,
	kCWTimeoutErr								= -3905,
	kCWUnspecifiedFailureErr					= -3906,
	kCWUnsupportedCapabilitiesErr				= -3907,
	kCWReassociationDeniedErr					= -3908,
	kCWAssociationDeniedErr						= -3909,
	kCWAuthenticationAlgorithmUnsupportedErr	= -3910,
	kCWInvalidAuthenticationSequenceNumberErr	= -3911,
	kCWChallengeFailureErr						= -3912,
	kCWAPFullErr								= -3913,
	kCWUnsupportedRateSetErr					= -3914,
	kCWShortSlotUnsupportedErr					= -3915,
	kCWDSSSOFDMUnsupportedErr					= -3916,
	kCWInvalidInformationElementErr				= -3917,
	kCWInvalidGroupCipherErr					= -3918,
	kCWInvalidPairwiseCipherErr					= -3919,
	kCWInvalidAKMPErr							= -3920,
	kCWUnsupportedRSNVersionErr					= -3921,
	kCWInvalidRSNCapabilitiesErr				= -3922,
	kCWCipherSuiteRejectedErr					= -3923,
	kCWInvalidPMKErr							= -3924,
	kCWSupplicantTimeoutErr						= -3925,
	kCWHTFeaturesNotSupportedErr				= -3926,
	kCWPCOTransitionTimeNotSupportedErr			= -3927,
	kCWReferenceNotBoundErr						= -3928,
	kCWIPCFailureErr							= -3929,
	kCWOperationNotPermittedErr					= -3930,
	kCWErr										= -3931,	
} NS_ENUM_AVAILABLE_MAC(10_6);

/*!
 * @typedef CWPHYMode
 *
 * @abstract Type describing the IEEE 802.11 physical layer mode.
 *
 * @constant kCWPHYModeNone 
 *
 * @constant kCWPHYMode11a 
 * IEEE 802.11a physical layer mode.
 *
 * @constant kCWPHYMode11b
 * IEEE 802.11b physical layer mode.
 *
 * @constant kCWPHYMode11g 
 * IEEE 802.11g physical layer mode.
 *
 * @constant kCWPHYMode11n 
 * IEEE 802.11n physical layer mode.
 *
 * @constant kCWPHYMode11ac
 * IEEE 802.11ac physical layer mode.
 */
typedef NS_ENUM(NSInteger, CWPHYMode)
{
	kCWPHYModeNone		= 0,
	kCWPHYMode11a		= 1,
	kCWPHYMode11b		= 2,
	kCWPHYMode11g		= 3,
	kCWPHYMode11n		= 4,
    kCWPHYMode11ac      = 5,
} NS_ENUM_AVAILABLE_MAC(10_7);

/*!
 * @typedef CWInterfaceMode
 *
 * @abstract Wi-Fi interface operating modes returned by -[CWInterface interfaceMode].
 *
 * @constant kCWInterfaceModeNone
 * Interface is not in any mode.
 *
 * @constant kCWInterfaceModeStation 
 * Interface is participating in an infrastructure network as a non-AP station.
 *
 * @constant kCWInterfaceModeIBSS 
 * Interface is participating in an IBSS network.
 *
 * @constant kCWInterfaceModeHostAP 
 * Interface is participating in an infrastructure network as an access point.
 */
typedef NS_ENUM(NSInteger, CWInterfaceMode)
{
	kCWInterfaceModeNone			= 0,
	kCWInterfaceModeStation			= 1,
	kCWInterfaceModeIBSS			= 2,
	kCWInterfaceModeHostAP			= 3,
} NS_ENUM_AVAILABLE_MAC(10_7);

/*!
 * @typedef CWSecurity
 *
 * @abstract Wi-Fi security types.
 *
 * @constant kCWSecurityNone 
 * Open System authentication.
 *
 * @constant kCWSecurityWEP 
 * WEP security.
 *
 * @constant kCWSecurityWPAPersonal
 * WPA Personal authentication.
 *
 * @constant kCWSecurityWPAPersonalMixed 
 * WPA/WPA2 Personal authentication.
 *
 * @constant kCWSecurityWPA2Personal 
 * WPA2 Personal authentication.
 *
 * @constant kCWSecurityDynamicWEP 
 * Dynamic WEP security.
 *
 * @constant kCWSecurityWPAEnterprise 
 * WPA Enterprise authentication.
 *
 * @constant kCWSecurityWPAEnterpriseMixed 
 * WPA/WPA2 Enterprise authentication.
 *
 * @constant kCWSecurityWPA2Enterprise
 * WPA2 Enterprise authentication.
 *
 * @constant kCWSecurityUnknown 
 * Unknown security type.
 */
typedef NS_ENUM(NSInteger, CWSecurity)
{
	kCWSecurityNone                 = 0,
	kCWSecurityWEP                  = 1,
	kCWSecurityWPAPersonal          = 2,
    kCWSecurityWPAPersonalMixed     = 3,
	kCWSecurityWPA2Personal         = 4,
    kCWSecurityPersonal             = 5,
	kCWSecurityDynamicWEP           = 6,
	kCWSecurityWPAEnterprise        = 7,
    kCWSecurityWPAEnterpriseMixed   = 8,
	kCWSecurityWPA2Enterprise       = 9,
    kCWSecurityEnterprise           = 10,
    kCWSecurityUnknown              = NSIntegerMax,
} NS_ENUM_AVAILABLE_MAC(10_7);

/*!
 * @typedef CWIBSSModeSecurity
 *
 * @abstract IBSS security types used in -[CWInterface startIBSSModeWithSSID:security:channel:password:error:].
 *
 * @constant kCWIBSSModeSecurityNone 
 * Open System authentication.
 *
 * @constant kCWIBSSModeSecurityWEP40
 * WEP security.
 *
 * @constant kCWIBSSModeSecurityWEP104
 * WPA Personal authentication.
 */
typedef NS_ENUM(NSInteger, CWIBSSModeSecurity)
{
	kCWIBSSModeSecurityNone         = 0,
	kCWIBSSModeSecurityWEP40		= 1,
	kCWIBSSModeSecurityWEP104       = 2,
} NS_ENUM_AVAILABLE_MAC(10_7);

/*!
 * @typedef CWChannelWidth
 *
 * @abstract Channel width values returned by -[CWChannel channelWidth].
 *
 * @constant kCWChannelWidthUnknown
 * Unknown channel width.
 *
 * @constant kCWChannelWidth20MHz 
 * 20MHz channel width.
 *
 * @constant kCWChannelWidth40MHz
 * 40MHz channel width.
 *
 * @constant kCWChannelWidth80MHz 
 * 80MHz channel width.
 *
 * @constant kCWChannelWidth160MHz
 * 160MHz channel width.
 */
typedef NS_ENUM(NSInteger, CWChannelWidth)
{
    kCWChannelWidthUnknown	= 0,
    kCWChannelWidth20MHz	= 1,
    kCWChannelWidth40MHz	= 2,
    kCWChannelWidth80MHz	= 3,
    kCWChannelWidth160MHz	= 4,
} NS_ENUM_AVAILABLE_MAC(10_7);

/*!
 * @typedef CWChannelBand
 *
 * @abstract Channel band values returned by -[CWChannel channelBand].
 *
 * @constant kCWChannelBandUnknown
 * Unknown channel band.
 *
 * @constant kCWChannelBand2GHz
 * 2.4GHz channel band.
 *
 * @constant kCWChannelBand5GHz
 * 5GHz channel band.
 */
typedef NS_ENUM(NSInteger, CWChannelBand)
{
	kCWChannelBandUnknown	= 0,
	kCWChannelBand2GHz		= 1,
	kCWChannelBand5GHz		= 2,
} NS_ENUM_AVAILABLE_MAC(10_7);

/*!
 * @typedef CWCipherKeyFlags
 *
 * @abstract Cipher key flags used in -[CWInterface setWEPKey:flags:index:error:].
 *
 * @constant kCWCipherKeyFlagsNone 
 * Open System authentication.
 *
 * @constant kCWCipherKeyFlagsUnicast
 * Cipher key will be used for unicast packets.
 *
 * @constant kCWCipherKeyFlagsMulticast 
 * Cipher key will be used for multicast packets.
 *
 * @constant kCWCipherKeyFlagsTx 
 * Cipher key will be used for packets sent from the interface.
 *
 * @constant kCWCipherKeyFlagsRx 
 * Cipher key will be used for packets received by the interface.
 */
typedef NS_OPTIONS(NSUInteger, CWCipherKeyFlags)
{
	kCWCipherKeyFlagsNone			= 0,
	kCWCipherKeyFlagsUnicast		= (1UL << 1),
	kCWCipherKeyFlagsMulticast		= (1UL << 2),
	kCWCipherKeyFlagsTx				= (1UL << 3),
	kCWCipherKeyFlagsRx				= (1UL << 4),
} NS_ENUM_AVAILABLE_MAC(10_7);

/*!
 * @typedef CWKeychainDomain
 *
 * @abstract Keychain domain types used by CoreWLAN keychain methods.
 *
 * @constant kCWKeychainDomainNone
 * No keychain domain specified.
 *
 * @constant kCWKeychainDomainUser
 * The user keychain domain. If iCloud Keychain is enabled, the iCloud keychain is the user keychain.
 *
 * @constant kCWKeychainDomainSystem
 * The system keychain domain.
 */
typedef NS_ENUM(NSInteger, CWKeychainDomain)
{
    kCWKeychainDomainNone       = 0,
    kCWKeychainDomainUser       = 1,
    kCWKeychainDomainSystem     = 2,
} NS_ENUM_AVAILABLE_MAC(10_10);

/*!
 * @typedef CWEventType
 *
 * @abstract Wi-Fi event types used in -[CWWiFiClient startMonitoringEventWithType:error:].
 *
 * @constant CWEventTypeNone 
 * No event type specified.
 *
 * @constant CWEventTypePowerDidChange
 * Posted when the power state of any Wi-Fi interface changes.
 *
 * @constant CWEventTypeSSIDDidChange 
 * Posted when the current SSID of any Wi-Fi interface changes.
 *
 * @constant CWEventTypeBSSIDDidChange
 * Posted when the current BSSID of any Wi-Fi interface changes.
 *
 * @constant CWEventTypeCountryCodeDidChange
 * Posted when the adopted country code of any Wi-Fi interface changes.
 *
 * @constant CWEventTypeLinkDidChange 
 * Posted when the link state for any Wi-Fi interface changes.
 *
 * @constant CWEventTypeLinkQualityDidChange
 * Posted when the RSSI or transmit rate for any Wi-Fi interface changes.
 *
 * @constant CWEventTypeModeDidChange 
 * Posted when the operating mode of any Wi-Fi interface changes.
 *
 * @constant CWEventTypeScanCacheUpdated
 * Posted when the scan cache of any Wi-Fi interface is updated with new scan results.
 *
 * @constant CWEventTypeUnknown
 * Unknown event type.
 */
typedef NS_ENUM(NSInteger, CWEventType)
{
    CWEventTypeNone                     = 0,
    CWEventTypePowerDidChange           = 1,
    CWEventTypeSSIDDidChange            = 2,
    CWEventTypeBSSIDDidChange           = 3,
    CWEventTypeCountryCodeDidChange     = 4,
    CWEventTypeLinkDidChange            = 5,
    CWEventTypeLinkQualityDidChange     = 6,
    CWEventTypeModeDidChange            = 7,
    CWEventTypeScanCacheUpdated         = 8,
    CWEventTypeUnknown                  = NSIntegerMax,
} NS_ENUM_AVAILABLE_MAC(10_10);

#endif /* _CORE_WLAN_TYPES_H_ */
