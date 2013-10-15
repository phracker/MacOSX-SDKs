/*
 *	CBCentralManager.h
 *	CoreBluetooth
 *
 *	Copyright 2011 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>



/*
 *  CBCentralManagerState
 *
 *  Discussion:
 *      Represents the current state of a CBCentralManager.
 *
 */
enum {
	CBCentralManagerStateUnknown = 0,	// State unknown, update imminent.
	CBCentralManagerStateResetting,		// The connection with the system service was momentarily lost, update imminent.
	CBCentralManagerStateUnsupported,	// The platform doesn't support Bluetooth Low Energy.
	CBCentralManagerStateUnauthorized,	// The app is not authorized to use Bluetooth Low Energy.
	CBCentralManagerStatePoweredOff,	// Bluetooth is currently powered off.
	CBCentralManagerStatePoweredOn,		// Bluetooth is currently powered on and available to use.

};
typedef NSInteger CBCentralManagerState;

/*
 *  CBCentralManagerScanOption keys
 *
 *  Discussion:
 *      Keys used to pass options to the -[scanForPeripheralsWithServices:options:] method.
 *
 */
CB_EXTERN NSString * const CBCentralManagerScanOptionAllowDuplicatesKey;	// A NSNumber

/*
 *  CBConnectPeripheralOption keys
 *
 *  Discussion:
 *      Keys used to pass options to the -[connectPeripheral:] method.
 *
 */
CB_EXTERN NSString * const CBConnectPeripheralOptionNotifyOnDisconnectionKey;	// A NSNumber



@protocol CBCentralManagerDelegate;
@class CBUUID, CBPeripheral;

/*
 *  CBCentralManager
 *
 *  Discussion:
 *      Entry point to the central role.
 *      Commands should only be issued when its state is CBCentralStatePoweredOn.
 *
 */
NS_CLASS_AVAILABLE(10_7, NA)
CB_EXTERN_CLASS @interface CBCentralManager : NSObject
{
@package
	id<CBCentralManagerDelegate> _delegate;
	
	CBCentralManagerState	_state;
}

/*
 *  delegate
 *
 *  Discussion:
 *      The delegate object you want to receive central events.
 *
 */
@property(assign, nonatomic) id<CBCentralManagerDelegate> delegate;

/*
 *  state
 *
 *  Discussion:
 *      The current state of the central.
 *      Initially set to CBCentralStateUnknown.
 *		It can be updated at any moment, upon which the relevant delegate callback will be invoked.
 *
 */
@property(readonly) CBCentralManagerState state;

/*
 *  initWithPeripheral:queue:
 *
 *  Discussion:
 *      The initialization call.
 *      The events of the central & its associated peripherals will be dispatched on the provided queue.
 *      If nil, the main queue will be used by default.
 *
 */
- (CBCentralManager *)initWithDelegate:(id<CBCentralManagerDelegate>)delegate queue:(dispatch_queue_t)queue;

/*
 *  retrievePeripherals:
 *
 *  Discussion:
 *      Ask the central to retrieve a list of known peripherals by their UUIDs.
 *      The relevant delegate callback will then promptly be invoked with the status of the request.
 *
 */
- (void)retrievePeripherals:(NSArray *)peripheralUUIDs;

/*
 *  retrieveConnectedPeripherals
 *
 *  Discussion:
 *      Ask the central to retrieve the list of the peripherals currently connected to the system.
 *      The relevant delegate callback will then promptly be invoked with the status of the request.
 *
 */
- (void)retrieveConnectedPeripherals;

/*
 *  scanForPeripheralsWithServices:options:
 *
 *  Discussion:
 *      Ask the central to scan for peripherals.
 *      The relevant delegate callback will then be invoked for each discovered peripheral.
 *      An array of CBUUIDs may be provided in "serviceUUIDs", in which case the central will
 *      only return peripherals which advertise this/these service(s) (recommended).
 *      If nil, all discovered peripherals will be returned (not recommmended).
 *      If the central is already scanning with different parameters, the provided parameters
 *      will replace them.
 *
 */
- (void)scanForPeripheralsWithServices:(NSArray *)serviceUUIDs options:(NSDictionary *)options;

/*
 *  stopScan:
 *
 *  Discussion:
 *      Ask the central to stop scanning for peripherals.
 *
 */
- (void)stopScan;

/*
 *  connectPeripheral:options:
 *
 *  Discussion:
 *      Establish a connection to the peripheral.
 *      This never times out, use -[cancelPeripheralConnection:] to cancel a pending connection.
 *
 */
- (void)connectPeripheral:(CBPeripheral *)peripheral options:(NSDictionary *)options;

/*
 *  cancelPeripheralConnection:
 *
 *  Discussion:
 *      Cancel a pending connection or a connection to the peripheral.
 *
 */
- (void)cancelPeripheralConnection:(CBPeripheral *)peripheral;

@end



/*
 *  CBAdvertisementData keys
 *
 *  Discussion:
 *      Keys used to index the advertisement data.
 *
 */
CB_EXTERN NSString * const CBAdvertisementDataServiceUUIDsKey;		// An array of CBUUIDs
CB_EXTERN NSString * const CBAdvertisementDataLocalNameKey;			// A NSString
CB_EXTERN NSString * const CBAdvertisementDataTxPowerLevelKey;		// A NSNumber
CB_EXTERN NSString * const CBAdvertisementDataManufacturerDataKey;	// A NSData
CB_EXTERN NSString * const CBAdvertisementDataServiceDataKey;		// A NSDictionary of NSDatas, indexed by CBUUIDs



@class CBPeripheral;

/*
 *  CBCentralManagerDelegate
 *
 *  Discussion:
 *      Delegate protocol for CBCentral.
 *
 */
@protocol CBCentralManagerDelegate <NSObject>

@required

/*
 *  centralManagerDidUpdateState:
 *
 *  Discussion:
 *      Invoked whenever the central's state has been updated.
 *      See the "state" property for more information.
 *
 */
- (void)centralManagerDidUpdateState:(CBCentralManager *)central;

@optional

/*
 *  centralManager:didRetrievePeripheral:
 *
 *  Discussion:
 *      Invoked when the central retrieved a list of known peripherals.
 *      See the -[retrievePeripherals:] method for more information.
 *
 */
- (void)centralManager:(CBCentralManager *)central didRetrievePeripherals:(NSArray *)peripherals;

/*
 *  centralManager:didRetrieveConnectedPeripherals:
 *
 *  Discussion:
 *      Invoked when the central retrieved the list of peripherals currently connected to the system.
 *      See the -[retrieveConnectedPeripherals] method for more information.
 *
 */
- (void)centralManager:(CBCentralManager *)central didRetrieveConnectedPeripherals:(NSArray *)peripherals;

/*
 *  centralManager:didDiscoverPeripheral:advertisementData:RSSI:
 *
 *  Discussion:
 *      Invoked when the central discovered a peripheral while scanning.
 *      The advertisement / scan response data is stored in "advertisementData", and
 *      can be accessed through the CBAdvertisementData* keys.
 *      The peripheral must be retained if any command is to be performed on it.
 *
 */
- (void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI;

/*
 *  centralManager:didConnectPeripheral:
 *
 *  Discussion:
 *      Invoked whenever a connection has been succesfully created with the peripheral.
 *
 */
- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral;

/*
 *  centralManager:didFailToConnectPeripheral:error:
 *
 *  Discussion:
 *      Invoked whenever a connection has failed to be created with the peripheral.
 *      The failure reason is stored in "error".
 *
 */
- (void)centralManager:(CBCentralManager *)central didFailToConnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;

/*
 *  centralManager:didDisconnectPeripheral:error:
 *
 *  Discussion:
 *      Invoked whenever an existing connection with the peripheral has been teared down.
 *
 */
- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;

@end
