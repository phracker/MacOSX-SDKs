/*
 *	@file CBCentralManager.h
 *	@framework CoreBluetooth
 *
 *  @discussion Entry point to the central role.
 *
 *	@copyright 2011 Apple, Inc. All rights reserved.
 */

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBAdvertisementData.h>
#import <CoreBluetooth/CBCentralManagerConstants.h>
#import <CoreBluetooth/CBDefines.h>
#import <CoreBluetooth/CBManager.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @enum CBCentralManagerState
 *
 *  @discussion Represents the current state of a CBCentralManager.
 *
 *  @constant CBCentralManagerStateUnknown       State unknown, update imminent.
 *  @constant CBCentralManagerStateResetting     The connection with the system service was momentarily lost, update imminent.
 *  @constant CBCentralManagerStateUnsupported   The platform doesn't support the Bluetooth Low Energy Central/Client role.
 *  @constant CBCentralManagerStateUnauthorized  The application is not authorized to use the Bluetooth Low Energy Central/Client role.
 *  @constant CBCentralManagerStatePoweredOff    Bluetooth is currently powered off.
 *  @constant CBCentralManagerStatePoweredOn     Bluetooth is currently powered on and available to use.
 *
 */
typedef NS_ENUM(NSInteger, CBCentralManagerState) {
	CBCentralManagerStateUnknown = CBManagerStateUnknown,
	CBCentralManagerStateResetting = CBManagerStateResetting,
	CBCentralManagerStateUnsupported = CBManagerStateUnsupported,
	CBCentralManagerStateUnauthorized = CBManagerStateUnauthorized,
	CBCentralManagerStatePoweredOff = CBManagerStatePoweredOff,
	CBCentralManagerStatePoweredOn = CBManagerStatePoweredOn,
} NS_DEPRECATED(10_7, 10_13, 5_0, 10_0, "Use CBManagerState instead");

/*!
 *  @enum CBConnectionEvent
 *
 *  @discussion Represents the connection state of a peer.
 *
 *  @constant CBConnectionEventPeerDisconnected	Peer is disconnected.
 *  @constant CBConnectionEventPeerConnected	Peer is connected.
 *
 */
typedef NS_ENUM(NSInteger, CBConnectionEvent) {
	CBConnectionEventPeerDisconnected = 0,
	CBConnectionEventPeerConnected	= 1,
};

/*!
 *  @enum CBCentralManagerFeature
 *
 *  @discussion The set of device specific features.
 *
 *	@constant CBCentralManagerFeatureExtendedScanAndConnect      The hardware supports extended scans and enhanced connection creation
 *
 */
typedef NS_OPTIONS(NSUInteger, CBCentralManagerFeature) {
	CBCentralManagerFeatureExtendedScanAndConnect CB_CM_API_AVAILABLE = 1UL << 0,
} NS_SWIFT_NAME(CBCentralManager.Feature);

@protocol CBCentralManagerDelegate;
@class CBUUID, CBPeripheral;

/*!
 *  @class CBCentralManager
 *
 *  @discussion Entry point to the central role. Commands should only be issued when its state is <code>CBCentralManagerStatePoweredOn</code>.
 *
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
CB_EXTERN_CLASS @interface CBCentralManager : CBManager

/*!
 *  @property delegate
 *
 *  @discussion The delegate object that will receive central events.
 *
 */
@property(nonatomic, weak, nullable) id<CBCentralManagerDelegate> delegate;

/*!
 *  @property isScanning
 *
 *  @discussion Whether or not the central is currently scanning.
 *
 */
@property(nonatomic, assign, readonly) BOOL isScanning NS_AVAILABLE(10_13, 9_0);

/*!
 *  @method supportsFeatures
 *
 *  @param features	One or more features you would like to check if supported.
 *
 *  @discussion     Returns a boolean value representing the support for the provided features.
 *
 */
+ (BOOL)supportsFeatures:(CBCentralManagerFeature)features CB_CM_API_AVAILABLE NS_SWIFT_NAME(supports(_:));

- (instancetype)init;

/*!
 *  @method initWithDelegate:queue:
 *
 *  @param delegate The delegate that will receive central role events.
 *  @param queue    The dispatch queue on which the events will be dispatched.
 *
 *  @discussion     The initialization call. The events of the central role will be dispatched on the provided queue.
 *                  If <i>nil</i>, the main queue will be used.
 *
 */
- (instancetype)initWithDelegate:(nullable id<CBCentralManagerDelegate>)delegate
						   queue:(nullable dispatch_queue_t)queue;

/*!
 *  @method initWithDelegate:queue:options:
 *
 *  @param delegate The delegate that will receive central role events.
 *  @param queue    The dispatch queue on which the events will be dispatched.
 *  @param options  An optional dictionary specifying options for the manager.
 *
 *  @discussion     The initialization call. The events of the central role will be dispatched on the provided queue.
 *                  If <i>nil</i>, the main queue will be used.
 *
 *	@seealso		CBCentralManagerOptionShowPowerAlertKey
 *	@seealso		CBCentralManagerOptionRestoreIdentifierKey
 *
 */
- (instancetype)initWithDelegate:(nullable id<CBCentralManagerDelegate>)delegate
						   queue:(nullable dispatch_queue_t)queue
						 options:(nullable NSDictionary<NSString *, id> *)options NS_AVAILABLE(10_9, 7_0) NS_DESIGNATED_INITIALIZER;

/*!
 *  @method retrievePeripheralsWithIdentifiers:
 *
 *  @param identifiers	A list of <code>NSUUID</code> objects.
 *
 *  @discussion			Attempts to retrieve the <code>CBPeripheral</code> object(s) with the corresponding <i>identifiers</i>.
 *
 *	@return				A list of <code>CBPeripheral</code> objects.
 *
 */
- (NSArray<CBPeripheral *> *)retrievePeripheralsWithIdentifiers:(NSArray<NSUUID *> *)identifiers NS_AVAILABLE(10_9, 7_0);

/*!
 *  @method retrieveConnectedPeripheralsWithServices
 *
 *  @discussion Retrieves all peripherals that are connected to the system and implement any of the services listed in <i>serviceUUIDs</i>.
 *				Note that this set can include peripherals which were connected by other applications, which will need to be connected locally
 *				via {@link connectPeripheral:options:} before they can be used.
 *
 *	@return		A list of <code>CBPeripheral</code> objects.
 *
 */
- (NSArray<CBPeripheral *> *)retrieveConnectedPeripheralsWithServices:(NSArray<CBUUID *> *)serviceUUIDs NS_AVAILABLE(10_9, 7_0);

/*!
 *  @method scanForPeripheralsWithServices:options:
 *
 *  @param serviceUUIDs A list of <code>CBUUID</code> objects representing the service(s) to scan for.
 *  @param options      An optional dictionary specifying options for the scan.
 *
 *  @discussion         Starts scanning for peripherals that are advertising any of the services listed in <i>serviceUUIDs</i>. Although strongly discouraged,
 *                      if <i>serviceUUIDs</i> is <i>nil</i> all discovered peripherals will be returned. If the central is already scanning with different
 *                      <i>serviceUUIDs</i> or <i>options</i>, the provided parameters will replace them.
 *                      Applications that have specified the <code>bluetooth-central</code> background mode are allowed to scan while backgrounded, with two
 *                      caveats: the scan must specify one or more service types in <i>serviceUUIDs</i>, and the <code>CBCentralManagerScanOptionAllowDuplicatesKey</code>
 *                      scan option will be ignored.
 *
 *  @see                centralManager:didDiscoverPeripheral:advertisementData:RSSI:
 *  @seealso            CBCentralManagerScanOptionAllowDuplicatesKey
 *	@seealso			CBCentralManagerScanOptionSolicitedServiceUUIDsKey
 *
 */
- (void)scanForPeripheralsWithServices:(nullable NSArray<CBUUID *> *)serviceUUIDs options:(nullable NSDictionary<NSString *, id> *)options;

/*!
 *  @method stopScan:
 *
 *  @discussion Stops scanning for peripherals.
 *
 */
- (void)stopScan;

/*!
 *  @method connectPeripheral:options:
 *
 *  @param peripheral   The <code>CBPeripheral</code> to be connected.
 *  @param options      An optional dictionary specifying connection behavior options.
 *
 *  @discussion         Initiates a connection to <i>peripheral</i>. Connection attempts never time out and, depending on the outcome, will result
 *                      in a call to either {@link centralManager:didConnectPeripheral:} or {@link centralManager:didFailToConnectPeripheral:error:}.
 *                      Pending attempts are cancelled automatically upon deallocation of <i>peripheral</i>, and explicitly via {@link cancelPeripheralConnection}.
 *
 *  @see                centralManager:didConnectPeripheral:
 *  @see                centralManager:didFailToConnectPeripheral:error:
 *  @seealso            CBConnectPeripheralOptionNotifyOnConnectionKey
 *  @seealso            CBConnectPeripheralOptionNotifyOnDisconnectionKey
 *  @seealso            CBConnectPeripheralOptionNotifyOnNotificationKey
 *  @seealso            CBConnectPeripheralOptionEnableTransportBridgingKey
 *	@seealso			CBConnectPeripheralOptionRequiresANCS
 *  @seealso            CBConnectPeripheralOptionEnableAutoReconnect
 *
 */
- (void)connectPeripheral:(CBPeripheral *)peripheral options:(nullable NSDictionary<NSString *, id> *)options;

/*!
 *  @method cancelPeripheralConnection:
 *
 *  @param peripheral   A <code>CBPeripheral</code>.
 *
 *  @discussion         Cancels an active or pending connection to <i>peripheral</i>. Note that this is non-blocking, and any <code>CBPeripheral</code>
 *                      commands that are still pending to <i>peripheral</i> may or may not complete.
 *
 *  @see                centralManager:didDisconnectPeripheral:error:
 *
 */
- (void)cancelPeripheralConnection:(CBPeripheral *)peripheral;

/*!
 *  @method registerForConnectionEventsWithOptions:
 *
 *  @param options		A dictionary specifying connection event options.
 *
 *  @discussion     	Calls {@link centralManager:connectionEventDidOccur:forPeripheral:} when a connection event occurs matching any of the given options.
 *                      Passing nil in the option parameter clears any prior registered matching options.
 *
 *  @see				centralManager:connectionEventDidOccur:forPeripheral:
 *  @seealso        	CBConnectionEventMatchingOptionServiceUUIDs
 *  @seealso            CBConnectionEventMatchingOptionPeripheralUUIDs
 */
- (void)registerForConnectionEventsWithOptions:(nullable NSDictionary<CBConnectionEventMatchingOption, id> *)options CB_CM_API_AVAILABLE;

@end


/*!
 *  @protocol CBCentralManagerDelegate
 *
 *  @discussion The delegate of a {@link CBCentralManager} object must adopt the <code>CBCentralManagerDelegate</code> protocol. The
 *              single required method indicates the availability of the central manager, while the optional methods allow for the discovery and
 *              connection of peripherals.
 *
 */
@protocol CBCentralManagerDelegate <NSObject>

@required

/*!
 *  @method centralManagerDidUpdateState:
 *
 *  @param central  The central manager whose state has changed.
 *
 *  @discussion     Invoked whenever the central manager's state has been updated. Commands should only be issued when the state is
 *                  <code>CBCentralManagerStatePoweredOn</code>. A state below <code>CBCentralManagerStatePoweredOn</code>
 *                  implies that scanning has stopped and any connected peripherals have been disconnected. If the state moves below
 *                  <code>CBCentralManagerStatePoweredOff</code>, all <code>CBPeripheral</code> objects obtained from this central
 *                  manager become invalid and must be retrieved or discovered again.
 *
 *  @see            state
 *
 */
- (void)centralManagerDidUpdateState:(CBCentralManager *)central;

@optional

/*!
 *  @method centralManager:willRestoreState:
 *
 *  @param central      The central manager providing this information.
 *  @param dict			A dictionary containing information about <i>central</i> that was preserved by the system at the time the app was terminated.
 *
 *  @discussion			For apps that opt-in to state preservation and restoration, this is the first method invoked when your app is relaunched into
 *						the background to complete some Bluetooth-related task. Use this method to synchronize your app's state with the state of the
 *						Bluetooth system.
 *
 *  @seealso            CBCentralManagerRestoredStatePeripheralsKey;
 *  @seealso            CBCentralManagerRestoredStateScanServicesKey;
 *  @seealso            CBCentralManagerRestoredStateScanOptionsKey;
 *
 */
- (void)centralManager:(CBCentralManager *)central willRestoreState:(NSDictionary<NSString *, id> *)dict;

/*!
 *  @method centralManager:didDiscoverPeripheral:advertisementData:RSSI:
 *
 *  @param central              The central manager providing this update.
 *  @param peripheral           A <code>CBPeripheral</code> object.
 *  @param advertisementData    A dictionary containing any advertisement and scan response data.
 *  @param RSSI                 The current RSSI of <i>peripheral</i>, in dBm. A value of <code>127</code> is reserved and indicates the RSSI
 *								was not available.
 *
 *  @discussion                 This method is invoked while scanning, upon the discovery of <i>peripheral</i> by <i>central</i>. A discovered peripheral must
 *                              be retained in order to use it; otherwise, it is assumed to not be of interest and will be cleaned up by the central manager. For
 *                              a list of <i>advertisementData</i> keys, see {@link CBAdvertisementDataLocalNameKey} and other similar constants.
 *
 *  @seealso                    CBAdvertisementData.h
 *
 */
- (void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary<NSString *, id> *)advertisementData RSSI:(NSNumber *)RSSI;

/*!
 *  @method centralManager:didConnectPeripheral:
 *
 *  @param central      The central manager providing this information.
 *  @param peripheral   The <code>CBPeripheral</code> that has connected.
 *
 *  @discussion         This method is invoked when a connection initiated by {@link connectPeripheral:options:} has succeeded.
 *
 */
- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral;

/*!
 *  @method centralManager:didFailToConnectPeripheral:error:
 *
 *  @param central      The central manager providing this information.
 *  @param peripheral   The <code>CBPeripheral</code> that has failed to connect.
 *  @param error        The cause of the failure.
 *
 *  @discussion         This method is invoked when a connection initiated by {@link connectPeripheral:options:} has failed to complete. As connection attempts do not
 *                      timeout, the failure of a connection is atypical and usually indicative of a transient issue.
 *
 */
- (void)centralManager:(CBCentralManager *)central didFailToConnectPeripheral:(CBPeripheral *)peripheral error:(nullable NSError *)error;

/*!
 *  @method centralManager:didDisconnectPeripheral:error:
 *
 *  @param central      The central manager providing this information.
 *  @param peripheral   The <code>CBPeripheral</code> that has disconnected.
 *  @param error        If an error occurred, the cause of the failure.
 *
 *  @discussion         This method is invoked upon the disconnection of a peripheral that was connected by {@link connectPeripheral:options:}. If the disconnection
 *                      was not initiated by {@link cancelPeripheralConnection}, the cause will be detailed in the <i>error</i> parameter. Once this method has been
 *                      called, no more methods will be invoked on <i>peripheral</i>'s <code>CBPeripheralDelegate</code>.
 *
 */
- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(nullable NSError *)error;

/*!
 *  @method centralManager:didDisconnectPeripheral:timestamp:isReconnecting:error
 *
 *  @param central      The central manager providing this information.
 *  @param peripheral   The <code>CBPeripheral</code> that has disconnected.
 *  @param timestamp        Timestamp of the disconnection, it can be now or a few seconds ago.
 *  @param isReconnecting      If reconnect was triggered upon disconnection.
 *  @param error        If an error occurred, the cause of the failure.
 *
 *  @discussion         This method is invoked upon the disconnection of a peripheral that was connected by {@link connectPeripheral:options:}. If perihperal is
 *                      connected with connect option {@link CBConnectPeripheralOptionEnableAutoReconnect}, once this method has been called, the system
 *                      will automatically invoke connect to the peripheral. And if connection is established with the peripheral afterwards,
 *                      {@link centralManager:didConnectPeripheral:} can be invoked. If perihperal is connected without option
 *                      CBConnectPeripheralOptionEnableAutoReconnect, once this method has been called, no more methods will be invoked on
 *                       <i>peripheral</i>'s <code>CBPeripheralDelegate</code> .
 *
 */
- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral timestamp:(CFAbsoluteTime)timestamp isReconnecting:(BOOL)isReconnecting error:(nullable NSError *)error;

/*!
 *  @method centralManager:connectionEventDidOccur:forPeripheral:
 *
 *  @param central      The central manager providing this information.
 *  @param event		The <code>CBConnectionEvent</code> that has occurred.
 *  @param peripheral   The <code>CBPeripheral</code> that caused the event.
 *
 *  @discussion         This method is invoked upon the connection or disconnection of a peripheral that matches any of the options provided in {@link registerForConnectionEventsWithOptions:}.
 *
 */
- (void)centralManager:(CBCentralManager *)central connectionEventDidOccur:(CBConnectionEvent)event forPeripheral:(CBPeripheral *)peripheral CB_CM_API_AVAILABLE;

/*!
 *  @method centralManager:didUpdateANCSAuthorizationForPeripheral:
 *
 *  @param central      The central manager providing this information.
 *  @param peripheral   The <code>CBPeripheral</code> that caused the event.
 *
 *  @discussion         This method is invoked when the authorization status changes for a peripheral connected with {@link connectPeripheral:} option {@link CBConnectPeripheralOptionRequiresANCS}.
 *
 */
- (void)centralManager:(CBCentralManager *)central didUpdateANCSAuthorizationForPeripheral:(CBPeripheral *)peripheral NS_AVAILABLE_IOS(13_0);

@end

NS_ASSUME_NONNULL_END
