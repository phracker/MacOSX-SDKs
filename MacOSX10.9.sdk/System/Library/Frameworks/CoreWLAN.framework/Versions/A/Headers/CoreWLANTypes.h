/*!
 * @header CoreWLANTypes.h
 * @copyright 2010 Apple Inc. All rights reserved.
 * @updated 2010-03-09
 * @version 2.0.0
 */

#ifndef _CORE_WLAN_TYPES_H_
#define _CORE_WLAN_TYPES_H_

#import <Foundation/Foundation.h>

/*! @group CoreWLAN Error Codes */
/*!
 * @enum CWErr
 * @const kCWNoErr Success.
 * @const kCWEAPOLErr EAPOL-related error.
 * @const kCWInvalidParameterErr Parameter error.
 * @const kCWNoMemoryErr Memory allocation failed.
 * @const kCWUnknownErr Unexpected error condition encountered for which no error code exists.
 * @const kCWNotSupportedErr Operation not supported.
 * @const kCWInvalidFormatErr Invalid protocol element field detected.
 * @const kCWTimeoutErr Authentication/Association timed out.
 * @const kCWUnspecifiedFailureErr Access point did not specify a reason for authentication/association failure.
 * @const kCWUnsupportedCapabilitiesErr Access point cannot support all requested capabilities.
 * @const kCWReassociationDeniedErr Reassociation was denied because the access point was unable to determine that an association exists.
 * @const kCWAssociationDeniedErr Association was denied for an unspecified reason.
 * @const kCWAuthenticationAlgorithmUnsupportedErr Specified authentication algorithm is not supported.
 * @const kCWInvalidAuthenticationSequenceNumberErr Authentication frame received with an authentication sequence number out of expected sequence.
 * @const kCWChallengeFailureErr Authentication was rejected because of a challenge failure.
 * @const kCWAPFullErr Access point is unable to handle another associated station.
 * @const kCWUnsupportedRateSetErr Interface does not support all of the rates in the access point's basic rate set.
 * @const kCWShortSlotUnsupportedErr Association denied because short slot time option is not supported by requesting station.
 * @const kCWDSSSOFDMUnsupportedErr Association denied because DSSS-OFDM is not supported by requesting station.
 * @const kCWInvalidInformationElementErr Invalid information element included in association request.
 * @const kCWInvalidGroupCipherErr Invalid group cipher requested.
 * @const kCWInvalidPairwiseCipherErr Invalid pairwise cipher requested.
 * @const kCWInvalidAKMPErr Invalid authentication selector requested.
 * @const kCWUnsupportedRSNVersionErr Invalid WPA/WPA2 version specified.
 * @const kCWInvalidRSNCapabilitiesErr Invalid RSN capabilities specified in association request.
 * @const kCWCipherSuiteRejectedErr Cipher suite rejected due to network security policy.
 * @const kCWInvalidPMKErr PMK rejected by the access point.
 * @const kCWSupplicantTimeoutErr WPA/WPA2 handshake timed out.
 * @const kCWHTFeaturesNotSupportedErr Association was denied because the requesting station does not support HT features.
 * @const kCWPCOTransitionTimeNotSupportedErr Association was denied because the requesting station does not support the 
 * PCO transition time required by the AP.
 * @const kCWReferenceNotBoundErr No interface is bound to the CWInterface.
 * @const kCWIPCFailureErr Error communicating with a separate process.
 * @const kCWOperationNotPermittedErr Calling process does not have permission to perform this operation.
 * @const kCWErr Generic error, no specific error code exists to describe the error condition.
 */
enum {
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
};
typedef NSInteger CWErr;

/*!
 * @enum CWPHYMode
 * @const kCWPHYModeNone No PHY mode.
 * @const kCWPHYMode11a IEEE 802.11a PHY.
 * @const kCWPHYMode11b IEEE 802.11b PHY.
 * @const kCWPHYMode11g IEEE 802.11g PHY.
 * @const kCWPHYMode11n IEEE 802.11n PHY.
 * @discussion CoreWLAN physical layer modes.
 */
enum {
	kCWPHYModeNone		= 0,
	kCWPHYMode11a		= 1,
	kCWPHYMode11b		= 2,
	kCWPHYMode11g		= 3,
	kCWPHYMode11n		= 4,
    kCWPHYMode11ac      = 5,
};
typedef NSInteger CWPHYMode;

/*!
 * @enum CWInterfaceMode
 * @const kCWInterfaceModeNone Interface is not in any mode 
 * @const kCWInterfaceModeStation Interface is participating in an infrastructure network as a non-AP station.
 * @const kCWInterfaceModeIBSS Interface is participating in an IBSS network.
 * @const kCWInterfaceModeHostAP Interface is participating in an infrastructure network as an access point.
 * @discussion CoreWLAN interface operation modes.
 */
enum {
	kCWInterfaceModeNone			= 0,
	kCWInterfaceModeStation			= 1,
	kCWInterfaceModeIBSS			= 2,
	kCWInterfaceModeHostAP			= 3,
};
typedef NSInteger CWInterfaceMode;

/*!
 * @enum CWSecurity
 * @const kCWSecurityNone Open System authentication.
 * @const kCWSecurityWEP WEP security.
 * @const kCWSecurityWPAPersonal WPA Personal authentication.
 * @const kCWSecurityWPAPersonalMixed WPA/WPA2 Personal authentication.
 * @const kCWSecurityWPA2Personal WPA2 Personal authentication.
 * @const kCWSecurityDynamicWEP Dynamic WEP security.
 * @const kCWSecurityWPAEnterprise WPA Enterprise authentication.
 * @const kCWSecurityWPAEnterpriseMixed WPA/WPA2 Enterprise authentication.
 * @const kCWSecurityWPA2Enterprise WPA2 Enterprise authentication.
 * @const kCWSecurityUnknown Unknown security type.
 * @discussion CoreWLAN security types.
 */
enum {
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
};
typedef NSInteger CWSecurity;

/*!
 * @enum CWIBSSModeSecurity
 * @const kCWIBSSModeSecurityNone Open System authentication.
 * @const kCWIBSSModeSecurityWEP40 WEP security.
 * @const kCWIBSSModeSecurityWEP104 WPA Personal authentication.
 * @discussion IBSS mode security types.
 */
enum {
	kCWIBSSModeSecurityNone						= 0,
	kCWIBSSModeSecurityWEP40					= 1,
	kCWIBSSModeSecurityWEP104					= 2,
};
typedef NSInteger CWIBSSModeSecurity;

/*!
 * @enum CWChannelWidth
 * @const kCWChannelWidthUnknown Unknown channel width.
 * @const kCWChannelWidth20MHz 20MHz channel width.
 * @const kCWChannelWidth40MHz 40MHz channel width.
 * @const kCWChannelWidth80MHz 80MHz channel width.
 * @const kCWChannelWidth160MHz 160MHz channel width.
 * @discussion CoreWLAN channel widths used for CWChannel.
 */
enum {
    kCWChannelWidthUnknown	= 0,
    kCWChannelWidth20MHz	= 1,
    kCWChannelWidth40MHz	= 2,
    kCWChannelWidth80MHz	= 3,
    kCWChannelWidth160MHz	= 4,
};
typedef NSInteger CWChannelWidth;

/*!
 * @enum CWChannelBand
 * @const kCWChannelBandUnknown Unknown channel band.
 * @const kCWChannelBand2GHz 2 GHz channel band.
 * @const kCWChannelBand5GHz 5 GHz channel band.
 * @discussion CoreWLAN channel bands used for CWChannel.
 */
enum {
	kCWChannelBandUnknown	= 0,
	kCWChannelBand2GHz		= 1,
	kCWChannelBand5GHz		= 2,
};
typedef NSInteger CWChannelBand;

/*!
 * @enum CWCipherKeyFlags
 * @const kCWCipherKeyFlagsNone Open System authentication.
 * @const kCWCipherKeyFlagsUnicast Cipher key will be used for unicast packets.
 * @const kCWCipherKeyFlagsMulticast Cipher key will be used for multicast packets.
 * @const kCWCipherKeyFlagsTx Cipher key will be used for packets sent from the interface.
 * @const kCWCipherKeyFlagsRx Cipher key will be used for packets received by the interface.
 * @discussion CoreWLAN channel bands used for CWChannel.
 */
enum {
	kCWCipherKeyFlagsNone			= 0,
	kCWCipherKeyFlagsUnicast		= (1UL << 1),
	kCWCipherKeyFlagsMulticast		= (1UL << 2),
	kCWCipherKeyFlagsTx				= (1UL << 3),
	kCWCipherKeyFlagsRx				= (1UL << 4),
};
typedef NSUInteger CWCipherKeyFlags;

/*!
 * @enum CWKeychainDomain
 * @const kCWKeychainDomainNone No keychain domain specified.
 * @const kCWKeychainDomainUser The login (user) keychain domain.
 * @const kCWKeychainDomainSystem The system keychain domain.
 * @discussion CoreWLAN keychain domains used in the CWKeychain API.
 */
enum {
    kCWKeychainDomainNone       = 0,
    kCWKeychainDomainUser       = 1,
    kCWKeychainDomainSystem     = 2,
};
typedef NSInteger CWKeychainDomain;

#endif /* _CORE_WLAN_TYPES_H_ */
