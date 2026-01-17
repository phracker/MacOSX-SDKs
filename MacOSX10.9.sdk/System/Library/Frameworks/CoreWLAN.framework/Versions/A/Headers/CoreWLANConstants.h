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

#endif /* _CORE_WLAN_CONSTANTS_H_ */
