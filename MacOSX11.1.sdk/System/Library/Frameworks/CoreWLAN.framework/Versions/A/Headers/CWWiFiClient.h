/*!
 * @header CWWiFiClient.h
 * @copyright 2014 Apple Inc. All rights reserved.
 */

#ifndef _CORE_WLAN_WIFI_CLIENT_H_
#define _CORE_WLAN_WIFI_CLIENT_H_

#import <Foundation/Foundation.h>
#import <CoreWLAN/CoreWLANTypes.h>

/*!
 * @protocol
 *
 * @abstract 
 * Receive Wi-Fi event notifications.
 */
NS_ASSUME_NONNULL_BEGIN
@protocol CWEventDelegate

@optional

/*!
 * @method
 *
 * @abstract
 * Invoked if the connection to the Wi-Fi subsystem is temporarily interrupted.
 *
 * @discussion
 * All event notifications for which the Wi-Fi client has registered will be automatically re-registered if 
 * the connection is interrupted.  
 * The Wi-Fi client should re-sync any local state which is updated as a result of Wi-Fi event notifications.
 */
- (void)clientConnectionInterrupted;

/*!
 * @method
 *
 * @abstract
 * Invoked if the connection to the Wi-Fi subsystem is permanently invalidated.
 */
- (void)clientConnectionInvalidated;

/*!
 * @method
 *
 * @param interfaceName
 * The name of the Wi-Fi interface.
 *
 * @abstract
 * Invoked when the Wi-Fi power state changes.
 *
 * @discussion
 * Use -[CWWiFiClient startMonitoringEventWithType:error:] with the CWEventTypePowerDidChange event type
 * to register for power event notifications.
 * Use -[CWInterface powerOn] to query the current Wi-Fi power state.
 */
- (void)powerStateDidChangeForWiFiInterfaceWithName:(NSString *)interfaceName;

/*!
 * @method
 *
 * @param interfaceName
 * The name of the Wi-Fi interface.
 *
 * @abstract
 * Invoked when the current SSID changes.
 *
 * @discussion
 * Use -[CWWiFiClient startMonitoringEventWithType:error:] with the CWEventTypeSSIDDidChange event type
 * to register for SSID event notifications.
 * Use -[CWInterface ssidData] or -[CWInterface ssid] to query the current SSID.
 */
- (void)ssidDidChangeForWiFiInterfaceWithName:(NSString *)interfaceName;

/*!
 * @method
 *
 * @param interfaceName
 * The name of the Wi-Fi interface.
 *
 * @abstract
 * Invoked when the current BSSID changes.
 *
 * @discussion
 * Use -[CWWiFiClient startMonitoringEventWithType:error:] with the CWEventTypeBSSIDDidChange event type
 * to register for BSSID event notifications.
 * Use -[CWInterface bssid] to query the current BSSID.
 */
- (void)bssidDidChangeForWiFiInterfaceWithName:(NSString *)interfaceName;

/*!
 * @method
 *
 * @param interfaceName
 * The name of the Wi-Fi interface.
 *
 * @abstract
 * Invoked when the currently adopted country code changes.
 *
 * @discussion
 * Use -[CWWiFiClient startMonitoringEventWithType:error:] with the CWEventTypeCountryCodeDidChange event type 
 * to register for country code event notifications.
 * Use -[CWInterface countryCode] to query the currently adopted country code.
 */
- (void)countryCodeDidChangeForWiFiInterfaceWithName:(NSString *)interfaceName;

/*!
 * @method
 *
 * @param interfaceName
 * The name of the Wi-Fi interface.
 *
 * @abstract
 * Invoked when the Wi-Fi link state changes.
 *
 * @discussion
 * Use -[CWWiFiClient startMonitoringEventWithType:error:] with the CWEventTypeLinkDidChange event type
 * to register for link event notifications.
 */
- (void)linkDidChangeForWiFiInterfaceWithName:(NSString *)interfaceName;

/*!
 * @method
 *
 * @param interfaceName
 * The name of the Wi-Fi interface.
 *
 * @param rssi
 * The RSSI value for the currently associated network on the Wi-Fi interface.
 *
 * @param transmitRate
 * The transmit rate for the currently associated network on the Wi-Fi interface.
 *
 * @abstract
 * Invoked when the Wi-Fi link quality changes.
 *
 * @discussion
 * Use -[CWWiFiClient startMonitoringEventWithType:error:] with the CWEventTypeLinkQualityDidChange event type
 * to register for link quality event notifications.
 * Use -[CWInterface rssiValue] and -[CWInterface transmitRate] to query the current RSSI and transmit rate, respectively.
 */
- (void)linkQualityDidChangeForWiFiInterfaceWithName:(NSString *)interfaceName rssi:(NSInteger)rssi transmitRate:(double)transmitRate;

/*!
 * @method
 *
 * @param interfaceName
 * The name of the Wi-Fi interface.
 *
 * @abstract
 * Invoked when the Wi-Fi operating mode changes.
 *
 * @discussion
 * Use -[CWWiFiClient startMonitoringEventWithType:error:] with the CWEventTypeModeDidChange event type
 * to register for interface mode event notifications.
 * Use -[CWInterface interfaceMode] to query the current operating mode.
 */
- (void)modeDidChangeForWiFiInterfaceWithName:(NSString *)interfaceName;

/*!
 * @method
 *
 * @param interfaceName
 * The name of the Wi-Fi interface.
 *
 * @abstract
 * Invoked when the Wi-Fi interface scan cache is updated with new scan results.
 *
 * @discussion
 * Use -[CWWiFiClient startMonitoringEventWithType:error:] with the CWEventTypeScanCacheUpdated event type
 * to register for scan cache event notifications.
 * Use -[CWInterface cachedScanResults] to query scan cache results from the last scan.
 */
- (void)scanCacheUpdatedForWiFiInterfaceWithName:(NSString *)interfaceName;

@end

@class CWInterface;

/*!
 * @class
 *
 * @abstract
 * The interface to the Wi-Fi subsystem on OS X.
 * 
 * @discussion 
 * Provides access to all Wi-Fi interfaces and allows Wi-Fi clients to setup event notifications.
 * 
 * CWWiFiClient objects are heavy objects, therefore, clients of the CoreWLAN framework should use a single, 
 * long-running instance rather than creating several short-lived instances.  
 * For convenience, +[CWWiFiClient sharedWiFiClient] can be used to return a singleton instance.
 *
 * The CWWiFiClient object should be used to instantiate CWInterface objects rather than using a CWInterface
 * initializer directly.
 */
NS_CLASS_AVAILABLE_MAC(10_10)
@interface CWWiFiClient : NSObject
{
    @private
    
        NSXPCConnection     *_xpcConnection;
        
        NSMutableSet        *_eventList;
    
        dispatch_queue_t    _eventQueue;

        NSMutableDictionary *_interfaceMap;
        
        dispatch_queue_t    _mutex;
        
        id                  _delegate;
}

/*! @functiongroup Setting the Delegate */

/*!
 * @property
 *
 * @abstract
 * Sets the delegate to the specified object, which may implement CWWiFiEventDelegate protocol for Wi-Fi event handling.
 *
 * @discussion
 * Clients may register for specific Wi-Fi events using -[CWWiFiClient startMonitoringEventWithType:error:].
 */
@property(nonatomic, weak) id delegate NS_AVAILABLE_MAC(10_10);

/*! @functiongroup Getting a Wi-Fi Client */

/*!
 * @method
 *
 * @abstract 
 * Returns the shared CWWiFiClient instance. There is a single shared instance per process.
 */
+ (CWWiFiClient *)sharedWiFiClient NS_AVAILABLE_MAC(10_10);

/*!
 * @method
 *
 * @abstract
 * Initializes a CWWiFiClient object.
 */
- (instancetype)init NS_AVAILABLE_MAC(10_10);

/*! @functiongroup Getting a Wi-Fi Interface */

/*!
 * @method
 *
 * @abstract
 * Returns the CWInterface object for the default Wi-Fi interface.
 */
- (nullable CWInterface *)interface NS_AVAILABLE_MAC(10_10);

/*!
 * @method
 *
 * @result 
 * An NSArray of NSString objects corresponding to Wi-Fi interface names.
 *
 * @abstract
 * Returns the list of available Wi-Fi interface names (e.g. "en0").
 *
 * @discussion
 * If no Wi-Fi interfaces are available, this method will return an empty array.
 * Returns nil if an error occurs.
 */
+ (nullable NSArray<NSString *> *)interfaceNames NS_AVAILABLE_MAC(10_10);

/*!
 * @method
 *
 * @param interfaceName
 * The name of an available Wi-Fi interface.
 *
 * @abstract
 * Get the CWInterface object bound to the Wi-Fi interface with a specific interface name.
 *
 * @discussion
 * Use +[CWWiFiClient interfaceNames] to get a list of available Wi-Fi interface names.
 * Returns a CWInterface object for the default Wi-Fi interface if no interface name is specified.
 */
- (nullable CWInterface *)interfaceWithName:(nullable NSString *)interfaceName NS_AVAILABLE_MAC(10_10);

/*!
 * @method
 *
 * @result 
 * An NSArray of CWInterface objects.
 *
 * @abstract 
 * Returns all available Wi-Fi interfaces.
 *
 * @discussion 
 * If no Wi-Fi interfaces are available, this method will return an empty array.
 * Returns nil if an error occurs.
 */
- (nullable NSArray<CWInterface *> *)interfaces NS_AVAILABLE_MAC(10_10);

/*! @functiongroup Register for Wi-Fi Events */

/*!
 * @method
 *
 * @param type
 * A CWEventType value.
 *
 * @param error
 * An NSError object passed by reference, which upon return will contain the error if an error occurs.
 * This parameter is optional.
 *
 * @result
 * A BOOL value indicating whether or not an error occurred. YES indicates no error occurred.
 *
 * @abstract 
 * Register for specific Wi-Fi event notifications.
 */
- (BOOL)startMonitoringEventWithType:(CWEventType)type error:(out NSError **)error NS_AVAILABLE_MAC(10_10);

/*!
 * @method
 *
 * @param type
 * A CWEventType value.
 *
 * @param error
 * An NSError object passed by reference, which upon return will contain the error if an error occurs.
 * This parameter is optional.
 *
 * @result
 * A BOOL value indicating whether or not an error occurred. YES indicates no error occurred.
 *
 * @abstract
 * Unregister for specific Wi-Fi event notifications.
 */
- (BOOL)stopMonitoringEventWithType:(CWEventType)type error:(out NSError **)error NS_AVAILABLE_MAC(10_10);

/*!
 * @method
 *
 * @param error
 * An NSError object passed by reference, which upon return will contain the error if an error occurs.
 * This parameter is optional.
 *
 * @result
 * A BOOL value indicating whether or not an error occurred. YES indicates no error occurred.
 *
 * @abstract
 * Unregister for all Wi-Fi event notifications.
 */
- (BOOL)stopMonitoringAllEventsAndReturnError:(out NSError **)error NS_AVAILABLE_MAC(10_10);

@end
NS_ASSUME_NONNULL_END

#endif // _CORE_WLAN_WIFI_CLIENT_H_
