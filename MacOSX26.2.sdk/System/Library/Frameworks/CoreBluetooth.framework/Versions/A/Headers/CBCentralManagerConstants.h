/*
 *	@file CBCentralManagerConstants.h
 *	@framework CoreBluetooth
 *
 *	@copyright 2013 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#define CB_CM_API_AVAILABLE		API_AVAILABLE( ios( 13.0 ), tvos( 13.0 ), watchos( 6.0 ) ) API_UNAVAILABLE(macos)

/*!
 *  @const  CBCentralManagerOptionShowPowerAlertKey
 *
 *  @discussion An NSNumber (Boolean) indicating that the system should, if Bluetooth is powered off when <code>CBCentralManager</code> is instantiated, display
 *				a warning dialog to the user.
 *
 *  @see		initWithDelegate:queue:options:
 *
 */
CB_EXTERN NSString * const CBCentralManagerOptionShowPowerAlertKey NS_AVAILABLE(10_9, 7_0);

/*!
 *  @const  CBCentralManagerOptionRestoreIdentifierKey
 *
 *  @discussion An NSString containing a unique identifier (UID) for the <code>CBCentralManager</code> that is being instantiated. This UID is used
 *				by the system to identify a specific <code>CBCentralManager</code> instance for restoration and, therefore, must remain the same for
 *				subsequent application executions in order for the manager to be restored.
 *
 *  @see		initWithDelegate:queue:options:
 *  @seealso	centralManager:willRestoreState:
 *
 */
CB_EXTERN NSString * const CBCentralManagerOptionRestoreIdentifierKey NS_AVAILABLE(10_13, 7_0);

/*!
 *  @const  CBCentralManagerOptionDeviceAccessForMedia
 *
 *  @discussion A Boolean representing the CBCentralManager init purpose is for DeviceAccess for media only. This will limit the functionality of this
 *  				manager and only allow media device access without prompting the user for Bluetooth generic TCC.
 *
 *  @see		initWithDelegate:queue:options:
 *
 */
CB_EXTERN NSString * const CBCentralManagerOptionDeviceAccessForMedia NS_AVAILABLE_IOS(16_0);


/*!
 *  @const CBCentralManagerScanOptionAllowDuplicatesKey
 *
 *  @discussion An NSNumber (Boolean) indicating that the scan should run without duplicate filtering. By default, multiple discoveries of the
 *              same peripheral are coalesced into a single discovery event. Specifying this option will cause a discovery event to be generated
 *				every time the peripheral is seen, which may be many times per second. This can be useful in specific situations, such as making
 *				a connection based on a peripheral's RSSI, but may have an adverse affect on battery-life and application performance.
 *
 *  @see        scanForPeripheralsWithServices:options:
 *
 */
CB_EXTERN NSString * const CBCentralManagerScanOptionAllowDuplicatesKey;

/*!
 *  @const CBCentralManagerScanOptionSolicitedServiceUUIDsKey
 *
 *  @discussion An NSArray of <code>CBUUID</code> objects respresenting service UUIDs. Causes the scan to also look for peripherals soliciting
 *				any of the services contained in the list.
 *
 *  @see        scanForPeripheralsWithServices:options:
 *
 */
CB_EXTERN NSString * const CBCentralManagerScanOptionSolicitedServiceUUIDsKey NS_AVAILABLE(10_9, 7_0);

/*!
 *  @const CBConnectPeripheralOptionNotifyOnConnectionKey
 *
 *  @discussion An NSNumber (Boolean) indicating that the system should display a connection alert for a given peripheral, if the application is suspended
 *              when a successful connection is made.
 *              This is useful for applications that have not specified the <code>bluetooth-central</code> background mode and cannot display their
 *              own alert. If more than one application has requested notification for a given peripheral, the one that was most recently in the foreground
 *              will receive the alert.
 *
 *  @see        connectPeripheral:
 *
 */
CB_EXTERN NSString * const CBConnectPeripheralOptionNotifyOnConnectionKey NS_AVAILABLE(10_13, 6_0);

/*!
 *  @const CBConnectPeripheralOptionNotifyOnDisconnectionKey
 *
 *  @discussion An NSNumber (Boolean) indicating that the system should display a disconnection alert for a given peripheral, if the application
 *              is suspended at the time of the disconnection.
 *              This is useful for applications that have not specified the <code>bluetooth-central</code> background mode and cannot display their
 *              own alert. If more than one application has requested notification for a given peripheral, the one that was most recently in the foreground
 *              will receive the alert.
 *
 *  @see        connectPeripheral:
 *
 */
CB_EXTERN NSString * const CBConnectPeripheralOptionNotifyOnDisconnectionKey;

/*!
 *  @const CBConnectPeripheralOptionNotifyOnNotificationKey
 *
 *  @discussion An NSNumber (Boolean) indicating that the system should display an alert for all notifications received from a given peripheral, if
 *              the application is suspended at the time.
 *              This is useful for applications that have not specified the <code>bluetooth-central</code> background mode and cannot display their
 *              own alert. If more than one application has requested notification for a given peripheral, the one that was most recently in the foreground
 *              will receive the alert.
 *
 *  @see        connectPeripheral:
 *
 */
CB_EXTERN NSString * const CBConnectPeripheralOptionNotifyOnNotificationKey NS_AVAILABLE(10_13, 6_0);


/*!
 *  @const CBConnectPeripheralOptionStartDelayKey
 *
 *  @discussion An NSNumber indicating the number of seconds for the system to wait before starting a connection.
 *
 *  @see        connectPeripheral:
 *
 */
CB_EXTERN NSString * const CBConnectPeripheralOptionStartDelayKey NS_AVAILABLE(10_13, 6_0);

/*!
 *  @const CBConnectPeripheralOptionEnableTransportBridgingKey
 *
 *  @discussion An NSNumber (Boolean) indicating that the system will bring up classic transport profiles when low energy transport for peripheral is connected.
 *
 *  @see        connectPeripheral:
 *
 */
CB_EXTERN NSString * const CBConnectPeripheralOptionEnableTransportBridgingKey NS_AVAILABLE_IOS(13_0);

/*!
 *  @const CBConnectPeripheralOptionRequiresANCS
 *
 *  @discussion An NSNumber (Boolean) indicating that the ANCS (Apple Notification Center Service) is required for the peripheral is connected.
 *
 *  @see        connectPeripheral:
 *
 */
CB_EXTERN NSString * const CBConnectPeripheralOptionRequiresANCS NS_AVAILABLE_IOS(13_0);

/*!
 *  @const  CBCentralManagerRestoredStatePeripheralsKey
 *
 *  @discussion An NSArray of <code>CBPeripheral</code> objects containing all peripherals that were connected or pending connection at the time the
 *				application was terminated by the system. When possible, all known information for each peripheral will be restored, including any discovered
 *				services, characteristics and descriptors, as well as characteristic notification states.
 *
 *  @see		centralManager:willRestoreState:
 *	@seealso	connectPeripheral:options:
 *
 */
CB_EXTERN NSString * const CBCentralManagerRestoredStatePeripheralsKey NS_AVAILABLE(10_13, 7_0);

/*!
 *  @const  CBCentralManagerRestoredStateScanServicesKey
 *
 *  @discussion An NSArray of <code>CBUUID</code> objects containing the service(s) being scanned for at the time the application was terminated by the system.
 *
 *  @see		centralManager:willRestoreState:
 *	@seealso	scanForPeripheralsWithServices:options:
 *
 */
CB_EXTERN NSString * const CBCentralManagerRestoredStateScanServicesKey NS_AVAILABLE(10_13, 7_0);

/*!
 *  @const  CBCentralManagerRestoredStateScanOptionsKey
 *
 *  @discussion An NSDictionary containing the scan options at the time the application was terminated by the system.
 *
 *  @see		centralManager:willRestoreState:
 *	@seealso	scanForPeripheralsWithServices:options:
 *
 */
CB_EXTERN NSString * const CBCentralManagerRestoredStateScanOptionsKey NS_AVAILABLE(10_13, 7_0);


typedef NSString * CBConnectionEventMatchingOption NS_TYPED_ENUM;

/*!
 *  @const  CBConnectionEventMatchingOptionServiceUUIDs
 *
 *  @discussion An NSArray of <code>CBUUID</code> objects respresenting service UUIDs. A connected peer with any matching service UUIDs will result
 *         		in a call to {@link centralManager:connectionEventDidOccur:}.
 *              A maximum of 4 services can be registered.
 *
 *  @see		centralManager:connectionEventDidOccur:forPeripheral:
 *	@seealso	registerForConnectionEventsWithOptions:
 *
 */
CB_EXTERN CBConnectionEventMatchingOption const CBConnectionEventMatchingOptionServiceUUIDs CB_CM_API_AVAILABLE;

/*!
 *  @const  CBConnectionEventMatchingOptionPeripheralUUIDs
 *
 *  @discussion An NSArray of <code>NSUUID</code> objects respresenting <i>peripheral</i> identifiers. A connected peer with any matching identifier(s) will result
 *         		in a call to {@link centralManager:connectionEventDidOccur:}.
 *
 *  @see		centralManager:connectionEventDidOccur:forPeripheral:
 *	@seealso	registerForConnectionEventsWithOptions:
 *
 */
CB_EXTERN CBConnectionEventMatchingOption const CBConnectionEventMatchingOptionPeripheralUUIDs CB_CM_API_AVAILABLE;


/*!
 *  @const CBConnectPeripheralOptionEnableAutoReconnect
 *
 *  @discussion An NSNumber (Boolean) indicating that the AutoReconnect is enabled for the peripheral is connected. After peripheral device is connected, this will allow
 *              the system to initiate connect to the peer device automatically when link is dropped. Caller will get notified about the disconnection with potential delay via
 *              {@link centralManager:didDisconnectPeripheral:timestamp:isReconnecting:error:}
 *
 *  @see        connectPeripheral:
 *
 */
CB_EXTERN NSString * const CBConnectPeripheralOptionEnableAutoReconnect NS_AVAILABLE(14_0, 17_0);

NS_ASSUME_NONNULL_END
