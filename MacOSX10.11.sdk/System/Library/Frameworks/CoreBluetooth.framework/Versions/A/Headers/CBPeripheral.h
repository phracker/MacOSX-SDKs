/*
 *	@file CBPeripheral.h
 *	@framework CoreBluetooth
 *
 *  @discussion Representation of a remote peripheral.
 *
 *	@copyright 2011 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CBCentralManager;

/*!
 *  @enum CBPeripheralState
 *
 *  @discussion Represents the current connection state of a CBPeripheral.
 *
 */
typedef NS_ENUM(NSInteger, CBPeripheralState) {
	CBPeripheralStateDisconnected = 0,
	CBPeripheralStateConnecting,
	CBPeripheralStateConnected,
} NS_AVAILABLE(10_9, 7_0);

/*!
 *  @enum CBCharacteristicWriteType
 *
 *  @discussion Specifies which type of write is to be performed on a CBCharacteristic.
 *
 */
typedef NS_ENUM(NSInteger, CBCharacteristicWriteType) {
	CBCharacteristicWriteWithResponse = 0,
	CBCharacteristicWriteWithoutResponse,
};

@protocol CBPeripheralDelegate;
@class CBService, CBCharacteristic, CBDescriptor, CBUUID;

/*!
 *  @class CBPeripheral
 *
 *  @discussion Represents a peripheral.
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
CB_EXTERN_CLASS @interface CBPeripheral : NSObject <NSCopying>
{
@private
	id<CBPeripheralDelegate>	 _delegate;
	
	CFUUIDRef					 _UUID;
	NSUUID						*_identifier;
	
	NSString					*_name;
	NSNumber					*_RSSI;
	CBPeripheralState			 _state;
	NSMutableArray				*_services;
	
	CBCentralManager			*_centralManager;
	
    NSUInteger                  mtuLength;
    
	NSMutableDictionary			*_attributes;
	BOOL						 _isPaired;
	BOOL						 _isConnectedToSystem;
}

/*!
 *  @property delegate
 *
 *  @discussion The delegate object that will receive peripheral events.
 */
@property(assign, nonatomic, nullable) id<CBPeripheralDelegate> delegate;

/*!
 *  @property UUID
 *
 *  @discussion Once a peripheral has been connected at least once by the system, it is assigned a UUID. This UUID can be stored and later provided to a
 *              <code>CBCentralManager</code> to retrieve the peripheral.
 *
 *	@deprecated Use the {@link identifier} property instead.
 */
@property(readonly, nonatomic) CFUUIDRef UUID NS_DEPRECATED(10_7, 10_9, 5_0, 7_0);

/*!
 *  @property identifier
 *
 *  @discussion The unique identifier associated with the peripheral. This identifier can be stored and later provided to a <code>CBCentralManager</code>
 *				to retrieve the peripheral.
 */
@property(readonly, nonatomic) NSUUID *identifier;

/*!
 *  @property name
 *
 *  @discussion The name of the peripheral.
 */
@property(retain, readonly, nullable) NSString *name;

/*!
 *  @property RSSI
 *
 *  @discussion The most recently read RSSI, in decibels.
 */
@property(retain, readonly, nullable) NSNumber *RSSI;

/*!
 *  @property isConnected
 *
 *  @discussion Whether or not the peripheral is currently connected.
 *              
 *	@deprecated Use the {@link state} property instead.
 */
@property(readonly) BOOL isConnected NS_DEPRECATED(10_7, 10_9, 5_0, 7_0);

/*!
 *  @property state
 *
 *  @discussion The current connection state of the peripheral.
 */
@property(readonly) CBPeripheralState state;

/*!
 *  @property services
 *
 *  @discussion A list of <code>CBService</code> objects that have been discovered on the peripheral.
 */
@property(retain, readonly, nullable) NSArray<CBService *> *services;

/*!
 *  @method readRSSI
 *
 *	@discussion While connected, retrieves the current RSSI of the link.
 *
 *	@see		peripheralDidUpdateRSSI:error:
 */
- (void)readRSSI;

/*!
 *  @method discoverServices:
 *
 *  @param serviceUUIDs A list of <code>CBUUID</code> objects representing the service types to be discovered. If <i>nil</i>,
 *						all services will be discovered, which is considerably slower and not recommended.
 *
 *  @discussion			Discovers available service(s) on the peripheral.
 *
 *  @see				peripheral:didDiscoverServices:
 */
- (void)discoverServices:(nullable NSArray<CBUUID *> *)serviceUUIDs;

/*!
 *  @method discoverIncludedServices:forService:
 *
 *  @param includedServiceUUIDs A list of <code>CBUUID</code> objects representing the included service types to be discovered. If <i>nil</i>,
 *								all of <i>service</i>s included services will be discovered, which is considerably slower and not recommended.
 *  @param service				A GATT service.
 *
 *  @discussion					Discovers the specified included service(s) of <i>service</i>.
 *
 *  @see						peripheral:didDiscoverIncludedServicesForService:error:
 */
- (void)discoverIncludedServices:(nullable NSArray<CBUUID *> *)includedServiceUUIDs forService:(CBService *)service;

/*!
 *  @method discoverCharacteristics:forService:
 *
 *  @param characteristicUUIDs	A list of <code>CBUUID</code> objects representing the characteristic types to be discovered. If <i>nil</i>,
 *								all characteristics of <i>service</i> will be discovered, which is considerably slower and not recommended.
 *  @param service				A GATT service.
 *
 *  @discussion					Discovers the specified characteristic(s) of <i>service</i>.
 *
 *  @see						peripheral:didDiscoverCharacteristicsForService:error:
 */
- (void)discoverCharacteristics:(nullable NSArray<CBUUID *> *)characteristicUUIDs forService:(CBService *)service;

/*!
 *  @method readValueForCharacteristic:
 *
 *  @param characteristic	A GATT characteristic.
 *
 *  @discussion				Reads the characteristic value for <i>characteristic</i>.
 *
 *  @see					peripheral:didUpdateValueForCharacteristic:error:
 */
- (void)readValueForCharacteristic:(CBCharacteristic *)characteristic;

/*!
 *  @method writeValue:forCharacteristic:type:
 *
 *  @param data				The value to write.
 *  @param characteristic	The characteristic whose characteristic value will be written.
 *  @param type				The type of write to be executed.
 *
 *  @discussion				Writes <i>value</i> to <i>characteristic</i>'s characteristic value. If the <code>CBCharacteristicWriteWithResponse</code>
 *							type is specified, {@link peripheral:didWriteValueForCharacteristic:error:} is called with the result of the write request.
 *
 *  @see					peripheral:didWriteValueForCharacteristic:error:
 *	@see					CBCharacteristicWriteType
 */
- (void)writeValue:(NSData *)data forCharacteristic:(CBCharacteristic *)characteristic type:(CBCharacteristicWriteType)type;

/*!
 *  @method setNotifyValue:forCharacteristic:
 *
 *  @param enabled			Whether or not notifications/indications should be enabled.
 *  @param characteristic	The characteristic containing the client characteristic configuration descriptor.
 *
 *  @discussion				Enables or disables notifications/indications for the characteristic value of <i>characteristic</i>. If <i>characteristic</i>
 *							allows both, notifications will be used.
 *                          When notifications/indications are enabled, updates to the characteristic value will be received via delegate method 
 *                          @link peripheral:didUpdateValueForCharacteristic:error: @/link. Since it is the peripheral that chooses when to send an update,
 *                          the application should be prepared to handle them as long as notifications/indications remain enabled.
 *
 *  @see					peripheral:didUpdateNotificationStateForCharacteristic:error:
 *  @seealso                CBConnectPeripheralOptionNotifyOnNotificationKey
 */
- (void)setNotifyValue:(BOOL)enabled forCharacteristic:(CBCharacteristic *)characteristic;

/*!
 *  @method discoverDescriptorsForCharacteristic:
 *
 *  @param characteristic	A GATT characteristic.
 *
 *  @discussion				Discovers the characteristic descriptor(s) of <i>characteristic</i>.
 *
 *  @see					peripheral:didDiscoverDescriptorsForCharacteristic:error:
 */
- (void)discoverDescriptorsForCharacteristic:(CBCharacteristic *)characteristic;

/*!
 *  @method readValueForDescriptor:
 *
 *  @param descriptor	A GATT characteristic descriptor.
 *
 *  @discussion			Reads the value of <i>descriptor</i>.
 *
 *  @see				peripheral:didUpdateValueForDescriptor:error:
 */
- (void)readValueForDescriptor:(CBDescriptor *)descriptor;

/*!
 *  @method writeValue:forDescriptor:
 *
 *  @param data			The value to write.
 *  @param descriptor	A GATT characteristic descriptor.
 *
 *  @discussion			Writes <i>data</i> to <i>descriptor</i>'s value. Client characteristic configuration descriptors cannot be written using
 *						this method, and should instead use @link setNotifyValue:forCharacteristic: @/link.
 *
 *  @see				peripheral:didWriteValueForCharacteristic:error:
 */
- (void)writeValue:(NSData *)data forDescriptor:(CBDescriptor *)descriptor;

@end



/*!
 *  @protocol CBPeripheralDelegate
 *
 *  @discussion Delegate for CBPeripheral.
 *
 */
@protocol CBPeripheralDelegate <NSObject>

@optional

/*!
 *  @method peripheralDidUpdateName:
 *
 *  @param peripheral	The peripheral providing this update.
 *
 *  @discussion			This method is invoked when the @link name @/link of <i>peripheral</i> changes.
 */
- (void)peripheralDidUpdateName:(CBPeripheral *)peripheral NS_AVAILABLE(10_9, 6_0);

/*!
 *  @method peripheralDidInvalidateServices:
 *
 *  @param peripheral	The peripheral providing this update.
 *
 *  @discussion			This method is invoked when the @link services @/link of <i>peripheral</i> have been changed. At this point, 
 *						all existing <code>CBService</code> objects are invalidated. Services can be re-discovered via @link discoverServices: @/link.
 *
 *	@deprecated			Use {@link peripheral:didInvalidateServices:} instead.
 */
- (void)peripheralDidInvalidateServices:(CBPeripheral *)peripheral NS_DEPRECATED(NA, NA, 6_0, 7_0);

/*!
 *  @method peripheral:didModifyServices:
 *
 *  @param peripheral	The peripheral providing this update.
 *  @param services		The services that have been invalidated
 *
 *  @discussion			This method is invoked when the @link services @/link of <i>peripheral</i> have been changed.
 *						At this point, the designated <code>CBService</code> objects have been invalidated.
 *						Services can be re-discovered via @link discoverServices: @/link.
 */
- (void)peripheral:(CBPeripheral *)peripheral didModifyServices:(NSArray<CBService *> *)invalidatedServices NS_AVAILABLE(10_9, 7_0);

/*!
 *  @method peripheralDidUpdateRSSI:error:
 *
 *  @param peripheral	The peripheral providing this update.
 *	@param error		If an error occurred, the cause of the failure.
 *
 *  @discussion			This method returns the result of a @link readRSSI: @/link call.
 */
- (void)peripheralDidUpdateRSSI:(CBPeripheral *)peripheral error:(nullable NSError *)error;

/*!
 *  @method peripheral:didDiscoverServices:
 *
 *  @param peripheral	The peripheral providing this information.
 *	@param error		If an error occurred, the cause of the failure.
 *
 *  @discussion			This method returns the result of a @link discoverServices: @/link call. If the service(s) were read successfully, they can be retrieved via
 *						<i>peripheral</i>'s @link services @/link property.
 *
 */
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverServices:(nullable NSError *)error;

/*!
 *  @method peripheral:didDiscoverIncludedServicesForService:error:
 *
 *  @param peripheral	The peripheral providing this information.
 *  @param service		The <code>CBService</code> object containing the included services.
 *	@param error		If an error occurred, the cause of the failure.
 *
 *  @discussion			This method returns the result of a @link discoverIncludedServices:forService: @/link call. If the included service(s) were read successfully, 
 *						they can be retrieved via <i>service</i>'s <code>includedServices</code> property.
 */
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverIncludedServicesForService:(CBService *)service error:(nullable NSError *)error;

/*!
 *  @method peripheral:didDiscoverCharacteristicsForService:error:
 *
 *  @param peripheral	The peripheral providing this information.
 *  @param service		The <code>CBService</code> object containing the characteristic(s).
 *	@param error		If an error occurred, the cause of the failure.
 *
 *  @discussion			This method returns the result of a @link discoverCharacteristics:forService: @/link call. If the characteristic(s) were read successfully, 
 *						they can be retrieved via <i>service</i>'s <code>characteristics</code> property.
 */
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverCharacteristicsForService:(CBService *)service error:(nullable NSError *)error;

/*!
 *  @method peripheral:didUpdateValueForCharacteristic:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param characteristic	A <code>CBCharacteristic</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method is invoked after a @link readValueForCharacteristic: @/link call, or upon receipt of a notification/indication.
 */
- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic error:(nullable NSError *)error;

/*!
 *  @method peripheral:didWriteValueForCharacteristic:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param characteristic	A <code>CBCharacteristic</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method returns the result of a {@link writeValue:forCharacteristic:type:} call, when the <code>CBCharacteristicWriteWithResponse</code> type is used.
 */
 - (void)peripheral:(CBPeripheral *)peripheral didWriteValueForCharacteristic:(CBCharacteristic *)characteristic error:(nullable NSError *)error;

/*!
 *  @method peripheral:didUpdateNotificationStateForCharacteristic:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param characteristic	A <code>CBCharacteristic</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method returns the result of a @link setNotifyValue:forCharacteristic: @/link call. 
 */
- (void)peripheral:(CBPeripheral *)peripheral didUpdateNotificationStateForCharacteristic:(CBCharacteristic *)characteristic error:(nullable NSError *)error;

/*!
 *  @method peripheral:didDiscoverDescriptorsForCharacteristic:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param characteristic	A <code>CBCharacteristic</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method returns the result of a @link discoverDescriptorsForCharacteristic: @/link call. If the descriptors were read successfully, 
 *							they can be retrieved via <i>characteristic</i>'s <code>descriptors</code> property.
 */
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverDescriptorsForCharacteristic:(CBCharacteristic *)characteristic error:(nullable NSError *)error;

/*!
 *  @method peripheral:didUpdateValueForDescriptor:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param descriptor		A <code>CBDescriptor</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method returns the result of a @link readValueForDescriptor: @/link call.
 */
- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForDescriptor:(CBDescriptor *)descriptor error:(nullable NSError *)error;

/*!
 *  @method peripheral:didWriteValueForDescriptor:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param descriptor		A <code>CBDescriptor</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method returns the result of a @link writeValue:forDescriptor: @/link call.
 */
- (void)peripheral:(CBPeripheral *)peripheral didWriteValueForDescriptor:(CBDescriptor *)descriptor error:(nullable NSError *)error;

@end

NS_ASSUME_NONNULL_END