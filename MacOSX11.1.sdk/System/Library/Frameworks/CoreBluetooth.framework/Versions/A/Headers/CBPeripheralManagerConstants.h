/*
 *	@file CBPeripheralManagerConstants.h
 *	@framework CoreBluetooth
 *
 *	@copyright 2013 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @const  CBPeripheralManagerOptionShowPowerAlertKey
 *
 *  @discussion An NSNumber (Boolean) indicating that the system should, if Bluetooth is powered off when <code>CBPeripheralManager</code> is instantiated, display
 *				a warning dialog to the user.
 *
 *  @see		initWithDelegate:queue:options:
 *
 */
CB_EXTERN NSString * const CBPeripheralManagerOptionShowPowerAlertKey NS_AVAILABLE(10_9, 7_0);

/*!
 *  @const  CBPeripheralManagerOptionRestoreIdentifierKey
 *
 *  @discussion An NSString containing a unique identifier (UID) for the <code>CBPeripheralManager</code> that is being instantiated. This UID is used
 *				by the system to identify a specific <code>CBPeripheralManager</code> instance for restoration and, therefore, must remain the same for
 *				subsequent application executions in order for the manager to be restored.
 *
 *  @see		initWithDelegate:queue:options:
 *  @seealso	centralManager:willRestoreState:
 *
 */
CB_EXTERN NSString * const CBPeripheralManagerOptionRestoreIdentifierKey NS_AVAILABLE(10_9, 7_0);

/*!
 *  @const  CBPeripheralManagerRestoredStateServicesKey
 *
 *  @discussion An NSArray of <code>CBMutableService</code> objects containing all services that were published to the local database at the time the
 *				application was terminated by the system. All information for each service will be restored, including all discovered
 *				services, characteristics and descriptors, as well as characteristic notification states.
 *
 *  @see		peripheralManager:willRestoreState:
 *  @seealso	addService:
 *
 */
CB_EXTERN NSString * const CBPeripheralManagerRestoredStateServicesKey NS_AVAILABLE(10_9, 7_0);

/*!
 *  @const  CBPeripheralManagerRestoredStateAdvertisementDataKey
 *
 *  @discussion An NSDictionary containing the data being advertised at the time the application was terminated by the system.
 *
 *  @see		peripheralManager:willRestoreState:
 *  @seealso	startAdvertising:
 *
 */
CB_EXTERN NSString * const CBPeripheralManagerRestoredStateAdvertisementDataKey NS_AVAILABLE(10_9, 7_0);

NS_ASSUME_NONNULL_END
