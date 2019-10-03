/*!
 * @header CoreWLANConstants.h
 * @copyright 2010-2014 Apple Inc. All rights reserved.
 */

#ifndef _CORE_WLAN_CONSTANTS_H_
#define _CORE_WLAN_CONSTANTS_H_

#import <Foundation/Foundation.h>
NS_ASSUME_NONNULL_BEGIN

/*! @group Error Domain */

/*!
 * @constant CWErrorDomain
 *
 * @abstract 
 * Error domain corresponding to the CWErr type.
 */
FOUNDATION_EXTERN NSString * const CWErrorDomain NS_AVAILABLE_MAC(10_7);

/*! @group Wi-Fi Notifications */

/*!
 * @constant CWPowerDidChangeNotification
 *
 * @abstract
 * Posted when the power state of the Wi-Fi interface changes.
 *
 * @discussion
 * The <i>object</i> for this notification is the corresponding Wi-Fi interface name.
 * This notification does not contain a <i>userInfo</i> dictionary.
 */
FOUNDATION_EXTERN NSString * const CWPowerDidChangeNotification NS_DEPRECATED_MAC(10_6, 10_10, "Use -[CWWiFiClient startMonitoringEventWithType:error:] with the CWEventTypePowerDidChange event type");

/*!
 * @constant CWSSIDDidChangeNotification
 *
 * @abstract
 * Posted when the SSID of the Wi-Fi interface changes.
 *
 * @discussion 
 * The <i>object</i> for this notification is the corresponding Wi-Fi interface name.
 * This notification does not contain a <i>userInfo</i> dictionary.
 */
FOUNDATION_EXTERN NSString * const CWSSIDDidChangeNotification NS_DEPRECATED_MAC(10_6, 10_10, "Use -[CWWiFiClient startMonitoringEventWithType:error:] with the CWEventTypeSSIDDidChange event type");

/*!
 * @constant CWBSSIDDidChangeNotification
 *
 * @abstract
 * Posted when the BSSID of the Wi-Fi interface changes.
 *
 * @discussion
 * The <i>object</i> for this notification is the corresponding Wi-Fi interface name.
 * This notification does not contain a <i>userInfo</i> dictionary.
 */
FOUNDATION_EXTERN NSString * const CWBSSIDDidChangeNotification NS_DEPRECATED_MAC(10_6, 10_10, "Use -[CWWiFiClient startMonitoringEventWithType:error:] with the CWEventTypeBSSIDDidChange event type");

/*!
 * @constant CWLinkDidChangeNotification
 *
 * @abstract
 * Posted when the link of the Wi-Fi interface changes.
 *
 * @discussion
 * The <i>object</i> for this notification is the corresponding Wi-Fi interface name.
 * This notification does not contain a <i>userInfo</i> dictionary.
 */
FOUNDATION_EXTERN NSString * const CWLinkDidChangeNotification NS_DEPRECATED_MAC(10_6, 10_10, "Use -[CWWiFiClient startMonitoringEventWithType:error:] with the CWEventTypeLinkDidChange event type");

/*!
 * @constant CWModeDidChangeNotification
 *
 * @abstract
 * Posted when the operating mode of the Wi-Fi interface changes.
 *
 * @discussion
 * The <i>object</i> for this notification is the corresponding Wi-Fi interface name.
 * This notification does not contain a <i>userInfo</i> dictionary.
 */
FOUNDATION_EXTERN NSString * const CWModeDidChangeNotification NS_DEPRECATED_MAC(10_6, 10_10, "Use -[CWWiFiClient startMonitoringEventWithType:error:] with the CWEventTypeModeDidChange event type");

/*!
 * @constant CWCountryCodeDidChangeNotification
 *
 * @abstract
 * Posted when the adopted country code of the Wi-Fi interface changes.
 *
 * @discussion
 * The <i>object</i> for this notification is the corresponding Wi-Fi interface name.
 * This notification does not contain a <i>userInfo</i> dictionary.
 */
FOUNDATION_EXTERN NSString * const CWCountryCodeDidChangeNotification NS_DEPRECATED_MAC(10_6, 10_10, "Use -[CWWiFiClient startMonitoringEventWithType:error:] with the CWEventTypeCountryCodeDidChange event type");

/*!
 * @constant CWScanCacheDidUpdateNotification
 *
 * @abstract
 * Posted when the scan cache of the Wi-Fi interface is updated with new scan results.
 *
 * @discussion
 * The <i>object</i> for this notification is the corresponding Wi-Fi interface name.
 * This notification does not contain a <i>userInfo</i> dictionary.
 */
FOUNDATION_EXTERN NSString * const CWScanCacheDidUpdateNotification NS_DEPRECATED_MAC(10_7, 10_10, "Use -[CWWiFiClient startMonitoringEventWithType:error:] with the CWEventTypeScanCacheUpdated event type");

/*!
 * @constant CWLinkQualityDidChangeNotification
 *
 * @abstract
 * Posted when the link quality of the current Wi-Fi association changes.
 *
 * @discussion
 * The <i>object</i> for this notification is the corresponding Wi-Fi interface name.
 * This notification does not contain a <i>userInfo</i> dictionary.
 */
FOUNDATION_EXTERN NSString * const CWLinkQualityDidChangeNotification NS_DEPRECATED_MAC(10_7, 10_10, "Use -[CWWiFiClient startMonitoringEventWithType:error:] with the CWEventTypeLinkQualityDidChange event type");

/*!
 * @constant CWLinkQualityNotificationRSSIKey
 *
 * @abstract
 * NSNumber containing the current RSSI value for the Wi-Fi interface.
 *
 * @discussion
 * Found in the <i>userInfo</i> dictionary for the <i>CWLinkQualityChangedNotification</i>.
 */
FOUNDATION_EXTERN NSString * const CWLinkQualityNotificationRSSIKey NS_DEPRECATED_MAC(10_6, 10_10, "Use -[CWWiFiClient startMonitoringEventWithType:error:] with the CWEventTypeLinkQualityDidChange event type");

/*!
 * @constant CWLinkQualityNotificationTransmitRateKey
 *
 * @abstract
 * NSNumber containing the current transmit rate for the Wi-Fi interface.
 *
 * @discussion
 * Found in the <i>userInfo</i> dictionary for the <i>CWLinkQualityChangedNotification</i>.
 */
FOUNDATION_EXTERN NSString * const CWLinkQualityNotificationTransmitRateKey NS_DEPRECATED_MAC(10_6, 10_10, "Use -[CWWiFiClient startMonitoringEventWithType:error:] with the CWEventTypeLinkQualityDidChange event type");

NS_ASSUME_NONNULL_END

#endif /* _CORE_WLAN_CONSTANTS_H_ */
