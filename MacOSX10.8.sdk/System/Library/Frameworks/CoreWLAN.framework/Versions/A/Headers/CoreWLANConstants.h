/*!
 * @header CoreWLANConstants.h
 * @copyright 2010 Apple Inc. All rights reserved.
 * @updated 2010-03-09
 * @version 2.0.0
 */

#ifndef _CORE_WLAN_CONSTANTS_H_
#define _CORE_WLAN_CONSTANTS_H_

#import <Foundation/Foundation.h>

#pragma mark -
#pragma mark CoreWLAN Error Domain
/*! @group CoreWLAN Error Domain */
/*!
 * @constant CWErrorDomain 
 */
FOUNDATION_EXTERN NSString * const CWErrorDomain NS_AVAILABLE_MAC(10_7);

#pragma mark Notifications
/*! @group Notifications */
/*!
 * @constant CWPowerDidChangeNotification
 * @discussion Posted when the power state of any WLAN interface changes.  The <i>object</i> for this notification is the corresponding BSD interface name.  This notification does not contain a <i>userInfo</i> dictionary.
 */
FOUNDATION_EXTERN NSString * const CWPowerDidChangeNotification NS_AVAILABLE_MAC(10_6);

/*!
 * @constant CWSSIDDidChangeNotification
 * @discussion Posted when the SSID of any WLAN interface changes.  The <i>object</i> for this notification is the corresponding BSD interface name.  This notification does not contain a <i>userInfo</i> dictionary.
 */
FOUNDATION_EXTERN NSString * const CWSSIDDidChangeNotification NS_AVAILABLE_MAC(10_6);

/*!
 * @constant CWBSSIDDidChangeNotification
 * @discussion Posted when the BSSID of any WLAN interface changes.  The <i>object</i> for this notification is the corresponding BSD interface name.  This notification does not contain a <i>userInfo</i> dictionary.
 */
FOUNDATION_EXTERN NSString * const CWBSSIDDidChangeNotification NS_AVAILABLE_MAC(10_6);

/*!
 * @constant CWLinkDidChangeNotification
 * @discussion Posted when the link state of any WLAN interface changes.  The <i>object</i> for this notification is the corresponding BSD interface name.  This notification does not contain a <i>userInfo</i> dictionary.
 */
FOUNDATION_EXTERN NSString * const CWLinkDidChangeNotification NS_AVAILABLE_MAC(10_6);

/*!
 * @constant CWModeDidChangeNotification
 * @discussion Posted when the mode of any WLAN interface changes.  The <i>object</i> for this notification is the corresponding BSD interface name.  This notification does not contain a <i>userInfo</i> dictionary.
 */
FOUNDATION_EXTERN NSString * const CWModeDidChangeNotification NS_AVAILABLE_MAC(10_6);

/*!
 * @constant CWCountryCodeDidChangeNotification
 * @discussion Posted when the country code of any WLAN interface changes.  The <i>object</i> for this notification is the corresponding BSD interface name.  This notification does not contain a <i>userInfo</i> dictionary.
 */
FOUNDATION_EXTERN NSString * const CWCountryCodeDidChangeNotification NS_AVAILABLE_MAC(10_6);

/*!
 * @constant CWScanCacheDidUpdateNotification
 * @discussion Posted when new entries are added to the scan cache, or existing entries are updated with more current information.  The <i>object</i> for this notification is the corresponding BSD interface name.  This notification does not contain a <i>userInfo</i> dictionary.
 */
FOUNDATION_EXTERN NSString * const CWScanCacheDidUpdateNotification NS_AVAILABLE_MAC(10_7);

/*!
 * @constant CWLinkQualityDidChangeNotification
 * @discussion Posted when the link quality for any WLAN interface changes.  The <i>object</i> for this notification is the corresponding BSD interface name.  The <i>userInfo</i> dictionary for this notification contains the current RSSI and current transmit rate for the given CoreWLAN interface.
 */
FOUNDATION_EXTERN NSString * const CWLinkQualityDidChangeNotification NS_AVAILABLE_MAC(10_7);

/*!
 * @constant CWLinkQualityNotificationRSSIKey
 * @discussion NSNumber containing the current RSSI value for the WLAN interface.  Found in the <i>userInfo</i> dictionary for the <i>CWLinkQualityChangedNotification</i>.
 */
FOUNDATION_EXTERN NSString * const CWLinkQualityNotificationRSSIKey NS_AVAILABLE_MAC(10_7);

/*!
 * @constant CWLinkQualityNotificationTransmitRateKey
 * @discussion NSNumber containing the current transmit rate value for the WLAN interface.  Found in the <i>userInfo</i> dictionary for the <i>CWLinkQualityChangedNotification</i>.
 */
FOUNDATION_EXTERN NSString * const CWLinkQualityNotificationTransmitRateKey NS_AVAILABLE_MAC(10_7);

/*!
 * @constant CWServiceDidChangeNotification
 * @discussion Posted when the network service availability for any WLAN interface changes.  The <i>object</i> for this notification is the corresponding BSD interface name.  This notification does not contain a <i>userInfo</i> dictionary.
 */
FOUNDATION_EXTERN NSString * const CWServiceDidChangeNotification NS_AVAILABLE_MAC(10_7);

#pragma mark -

#pragma mark Error Domain
/*! @group Error Domain */
/*!
 * @const CWGenericErrorDomain 
 * @abstract error domain for NSErrors returned by calls to CWInterface
 */
FOUNDATION_EXTERN NSString * const kCWErrorDomain NS_DEPRECATED_MAC(10_6, 10_7);

#pragma mark Notifications
/*! @group Notifications */
/*!
 * @const CWPowerDidChangeNotification
 * @discussion Posted when the power state of the CoreWLAN interface changes.  This notification does not contain a <i>userInfo</i> dictionary.
 */
FOUNDATION_EXTERN NSString * const kCWPowerDidChangeNotification NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @const CWSSIDDidChangeNotification
 * @discussion Posted when the SSID of the CoreWLAN interface changes.  This notification does not contain a <i>userInfo</i> dictionary.
 */

FOUNDATION_EXTERN NSString * const kCWSSIDDidChangeNotification NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @const CWBSSIDDidChangeNotification
 * @discussion Posted when the BSSID of the wireless interface changes.  This notification does not contain a <i>userInfo</i> dictionary.
 */
FOUNDATION_EXTERN NSString * const kCWBSSIDDidChangeNotification NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @const CWLinkDidChangeNotification
 * @discussion Posted when the link state of the CoreWLAN interface changes.  This notification does not contain a <i>userInfo</i> dictionary.
 */
FOUNDATION_EXTERN NSString * const kCWLinkDidChangeNotification NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @const CWModeDidChangeNotification
 * @discussion Posted when the op mode of the CoreWLAN interface changes.  This notification does not contain a <i>userInfo</i> dictionary.
 */
FOUNDATION_EXTERN NSString * const kCWModeDidChangeNotification NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @const CWCountryCodeDidChangeNotification
 * @discussion Posted when the country code of the CoreWLAN interface changes.  This notification does not contain a <i>userInfo</i> dictionary.
 */
FOUNDATION_EXTERN NSString * const kCWCountryCodeDidChangeNotification NS_DEPRECATED_MAC(10_6, 10_7);

#pragma mark Association Parameter Keys
/*! @group Association Parameter Keys */
/*!
 * @const kCWAssocKeyPassphrase
 * @discussion NSString containing network passphrase or key. Required for association to WEP and WPA/WPA2 Personal networks.
 */
FOUNDATION_EXTERN NSString * const kCWAssocKeyPassphrase NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @const kCWAssocKey8021XProfile
 * @discussion CW8021XProfile object containing the network IEEE 802.1X profile.  Required for association 
 * to IEEE 802.1X dynamic WEP and WPA/WPA2 Enterprise networks.
 */
FOUNDATION_EXTERN NSString * const kCWAssocKey8021XProfile NS_DEPRECATED_MAC(10_6, 10_7);

#pragma mark IBSS Parameter Keys
/*! @group IBSS Parameter Keys */
/*!
 * @const kCWIBSSKeySSID
 * @discussion NSString containing the SSID of the network to be created.
 */
FOUNDATION_EXTERN NSString * const kCWIBSSKeySSID NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @const kCWIBSSKeyChannel
 * @discussion NSNumber containing the channel number on which the network will be created.  Defaults to channel 11.
 */
FOUNDATION_EXTERN NSString * const kCWIBSSKeyChannel NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @const kCWIBSSKeyPassphrase
 * @discussion NSString containing network cipher key.  40-bit and 104-bit WEP modes are currently supported. 
 * Cipher mode is inferred from the key length. A cipher key that has 5 characters or has 10 hexidecimal characters 
 * corresponds to a 40-bit WEP key. A cipher key that has 13 characters or has 26 hexidecimal characters corresponds 
 * to a 104-bit WEP key. If this key is not present, then no cipher key will be used on the network.
 */
FOUNDATION_EXTERN NSString * const kCWIBSSKeyPassphrase NS_DEPRECATED_MAC(10_6, 10_7);

#pragma mark Scan Parameter Keys
/*! @group Scan Parameter Keys */
/*!
 * @const kCWScanKeySSID
 * @discussion NSString containing the target SSID of a directed scan request.
 */
FOUNDATION_EXTERN NSString * const kCWScanKeySSID NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @const kCWScanKeyBSSID
 * @discussion NSString containing the target BSSID of a directed scan request.
 */
FOUNDATION_EXTERN NSString * const kCWScanKeyBSSID NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @const kCWScanKeyMerge
 * @discussion NSNumber boolean value indicating whether or not duplicate SSID entries should be included 
 * in the scan results.  A value evaluating to <i>true</i> will include the BSSID with the strongest 
 * signal strength and remove all other duplicate SSID entries. Defaults to <i>true</i>.
 */
FOUNDATION_EXTERN NSString * const kCWScanKeyMerge NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @const kCWScanKeyScanType
 * @discussion NSString indicating the type of scan to perform.  Defaults to <i>APScanTypeActive</i>.
 */
FOUNDATION_EXTERN NSString * const kCWScanKeyScanType NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @const kCWScanKeyDwellTime
 * @discussion NSNumber specifying the time in milliseconds that the interface will spend on each channel 
 * listening for beacon frames and probe responses.  Defaults to driver default.
 */
FOUNDATION_EXTERN NSString * const kCWScanKeyDwellTime NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @const kCWScanKeyRestTime
 * @discussion NSNumber specifying the time in milliseconds that the interface will spend on its home channels 
 * between intervals of off-channel activity during the scan request.  Defaults to driver default.
 */
FOUNDATION_EXTERN NSString * const kCWScanKeyRestTime NS_DEPRECATED_MAC(10_6, 10_7);

#endif /* _CORE_WLAN_CONSTANTS_H_ */
