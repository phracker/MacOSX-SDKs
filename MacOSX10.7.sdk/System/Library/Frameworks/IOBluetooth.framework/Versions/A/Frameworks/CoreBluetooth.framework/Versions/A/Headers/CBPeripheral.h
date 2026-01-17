/*
 *	CBPeripheral.h
 *	CoreBluetooth
 *
 *	Copyright 2011 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>



/*
 *  CBCharacteristicWriteType
 *
 *  Discussion:
 *      Specifies which type of write is to be performed on a CBCharacteristic.
 *
 */
enum {
	CBCharacteristicWriteWithResponse = 0,
	CBCharacteristicWriteWithoutResponse,
};
typedef NSInteger CBCharacteristicWriteType;



@protocol CBPeripheralDelegate;
@class CBService, CBCharacteristic, CBDescriptor, CBUUID;

/*
 *  CBPeripheral
 *
 *  Discussion:
 *      Represents a peripheral.
 *      Commands should only be issued when it is connected.
 *
 */
NS_CLASS_AVAILABLE(10_7, NA)
CB_EXTERN_CLASS @interface CBPeripheral : NSObject
{
@package
	id<CBPeripheralDelegate> _delegate;
	
	CFUUIDRef	 _UUID;
	
	NSString	*_name;
	NSNumber	*_RSSI;
	BOOL		 _isConnected;
	NSArray		*_services;
}

/*
 *  delegate
 *
 *  Discussion:
 *      The delegate object you want to receive peripheral events.
 *
 */
@property(assign, nonatomic) id<CBPeripheralDelegate> delegate;

/*
 *  UUID
 *
 *  Discussion:
 *      The UUID of the peripheral.
 *      This UUID can be stored and then later used to retrieve this specific peripheral
 *      with another central instance.
 *
 */
@property(readonly, nonatomic) CFUUIDRef UUID;

/*
 *  name
 *
 *  Discussion:
 *      The name of the peripheral.
 *
 */
@property(retain, readonly) NSString *name;

/*
 *  RSSI
 *
 *  Discussion:
 *      While connected, the RSSI of the link in dB.
 *
 */
@property(retain, readonly) NSNumber *RSSI;

/*
 *  isConnected
 *
 *  Discussion:
 *      Whether the peripheral is currently connected or not.
 *
 */
@property(readonly) BOOL isConnected;

/*
 *  services
 *
 *  Discussion:
 *      A list of CBServices that have so far been discovered on the peripheral.
 *
 */
@property(retain, readonly) NSArray *services;

/*
 *  readRSSI
 *
 *  Discussion:
 *      While connected, fetch the current RSSI of the link.
 *
 */
- (void)readRSSI;

/*
 *  discoverServices
 *
 *  Discussion:
 *      Discover available services on the peripheral.
 *      The relevant delegate callback will then be invoked with the status of the request.
 *      An array of CBUUIDs may be provided in "serviceUUIDs", in which case only services
 *      with matching UUIDs will be discovered (recommended).
 *      If nil, all services will be discovered (not recommmended).
 *
 */
- (void)discoverServices:(NSArray *)serviceUUIDs;

/*
 *  discoverIncludedServices:forService:
 *
 *  Discussion:
 *      Discover included services of a service.
 *      The relevant delegate callback will then be invoked with the status of the request.
 *      An array of CBUUIDs may be provided in "includedServiceUUIDs", in which case only
 *      included services with matching UUIDs will be discovered (recommended).
 *      If nil, all included services will be discovered (not recommmended).
 *
 */
- (void)discoverIncludedServices:(NSArray *)includedServiceUUIDs forService:(CBService *)service;

/*
 *  discoverCharacteristics:forService:
 *
 *  Discussion:
 *      Discover characteristics of a service.
 *      The relevant delegate callback will then be invoked with the status of the request.
 *      An array of CBUUIDs may be provided in "characteristicUUIDs", in which case only
 *      characteristics with matching UUIDs will be discovered (recommended).
 *      If nil, all characteristics will be discovered (not recommmended).
 *
 */
- (void)discoverCharacteristics:(NSArray *)characteristicUUIDs forService:(CBService *)service;

/*
 *  readValueForCharacteristic:
 *
 *  Discussion:
 *      Fetch the value of a characteristic.
 *      The relevant delegate callback will then be invoked with the status of the request.
 *
 */
- (void)readValueForCharacteristic:(CBCharacteristic *)characteristic;

/*
 *  writeValue:forCharacteristic:withResponse:
 *
 *  Discussion:
 *      Write the value of a characteristic.
 *      The passed data is copied and can be disposed of after the call finishes.
 *      The relevant delegate callback will then be invoked with the status of the request.
 *
 */
- (void)writeValue:(NSData *)data forCharacteristic:(CBCharacteristic *)characteristic type:(CBCharacteristicWriteType)type;

/*
 *  reliablyWriteValues:forCharacteristics:
 *
 *  Discussion:
 *      Reliably write the values of multiple characteristics using prepared & executed writes.
 *      The passed data is copied and can be disposed of after the call finishes.
 *      The relevant delegate callback will then be invoked with the status of the request.
 */
- (void)reliablyWriteValues:(NSArray *)values forCharacteristics:(NSArray *)array;

/*
 *  setBroadcastValue:forCharacteristic:
 *
 *  Discussion:
 *      Ask for a characteristic to start/stop being broadcasted.
 *      The relevant delegate callback will then be invoked with the status of the request.
 *
 */
- (void)setBroadcastValue:(BOOL)broadcastValue forCharacteristic:(CBCharacteristic *)characteristic;

/*
 *  setNotifyValue:forCharacteristic:
 *
 *  Discussion:
 *      Ask to start/stop receiving notifications for a characteristic.
 *      The relevant delegate callback will then be invoked with the status of the request.
 *
 */
- (void)setNotifyValue:(BOOL)notifyValue forCharacteristic:(CBCharacteristic *)characteristic;

/*
 *  discoverDescriptorsForCharacteristic:
 *
 *  Discussion:
 *      Discover the descriptors of a characteristic.
 *      The relevant delegate callback will then be invoked with the status of the request.
 *
 */
- (void)discoverDescriptorsForCharacteristic:(CBCharacteristic *)characteristic;

/*
 *  readValueForDescriptor:
 *
 *  Discussion:
 *      Fetch the value of a descriptor.
 *      The relevant delegate callback will then be invoked with the status of the request.
 *
 */
- (void)readValueForDescriptor:(CBDescriptor *)descriptor;

/*
 *  writeValue:forDescriptor:
 *
 *  Discussion:
 *      Write the value of a descriptor.
 *      The passed data is copied and can be disposed of after the call finishes.
 *      The relevant delegate callback will then be invoked with the status of the request.
 *
 */
- (void)writeValue:(NSData *)data forDescriptor:(CBDescriptor *)descriptor;

@end



/*
 *  CBPeripheralDelegate
 *
 *  Discussion:
 *      Delegate for CBPeripheral.
 *
 */
@protocol CBPeripheralDelegate <NSObject>

@optional

/*
 *  peripheralDidUpdateRSSI:error:
 *
 *  Discussion:
 *      Invoked upon completion of a -[readRSSI:] request.
 *      If successful, "error" is nil and the "RSSI" property of the peripheral has been updated.
 *      If unsuccessful, "error" is set with the encountered failure.
 *
 */
- (void)peripheralDidUpdateRSSI:(CBPeripheral *)peripheral error:(NSError *)error;

/*
 *  peripheral:didDiscoverServices:error:
 *
 *  Discussion:
 *      Invoked upon completion of a -[discoverServices:] request.
 *      If successful, "error" is nil and discovered services, if any, have been merged into the
 *      "services" property of the peripheral.
 *      If unsuccessful, "error" is set with the encountered failure.
 *
 */
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverServices:(NSError *)error;

/*
 *  peripheral:didDiscoverIncludedServicesForService:error:
 *
 *  Discussion:
 *      Invoked upon completion of a -[discoverIncludedServices:forService:] request.
 *      If successful, "error" is nil and discovered services, if any, have been merged into the
 *      "includedServices" property of the service.
 *      If unsuccessful, "error" is set with the encountered failure.
 *
 */
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverIncludedServicesForService:(CBService *)service error:(NSError *)error;

/*
 *  peripheral:didDiscoverCharacteristics:error:
 *
 *  Discussion:
 *      Invoked upon completion of a -[discoverCharacteristics:forService:] request.
 *      If successful, "error" is nil and discovered characteristics, if any, have been merged into the
 *      "characteristics" property of the service.
 *      If unsuccessful, "error" is set with the encountered failure.
 *
 */
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverCharacteristicsForService:(CBService *)service error:(NSError *)error;

/*
 *  peripheral:didUpdateValueForCharacteristic:error:
 *
 *  Discussion:
 *      Invoked upon completion of a -[readValueForCharacteristic:] request or on the reception of a notification/indication.
 *      If unsuccessful, "error" is set with the encountered failure.
 *
 */
- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;

/*
 *  peripheral:didWriteValueForCharacteristic:error:
 *
 *  Discussion:
 *      Invoked upon completion of a -[writeValue:forCharacteristic:] request.
 *      If unsuccessful, "error" is set with the encountered failure.
 *
 */
- (void)peripheral:(CBPeripheral *)peripheral didWriteValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;

/*
 *  peripheral:didWriteValuesForCharacteristics:error:
 *
 *  Discussion:
 *      Invoked upon completion of a -[reliablyWriteValues:forCharacteristics:] request.
 *      If unsuccessful, "error" is set with the encountered failure.
 *
 */
- (void)peripheral:(CBPeripheral *)peripheral didReliablyWriteValuesForCharacteristics:(NSArray *)characteristics error:(NSError *)error;

/*
 *  peripheral:didUpdateBroadcastStateForCharacteristic:error:
 *
 *  Discussion:
 *      Invoked upon completion of a -[setBroadcastValue:forCharacteristic:] request.
 *      If unsuccessful, "error" is set with the encountered failure.
 *
 */
- (void)peripheral:(CBPeripheral *)peripheral didUpdateBroadcastStateForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;

/*
 *  peripheral:didUpdateNotificationStateForCharacteristic:error:
 *
 *  Discussion:
 *      Invoked upon completion of a -[setNotifyValue:forCharacteristic:] request.
 *      If unsuccessful, "error" is set with the encountered failure.
 *
 */
- (void)peripheral:(CBPeripheral *)peripheral didUpdateNotificationStateForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;

/*
 *  peripheral:didDiscoverDescriptorsForCharacteristic:error:
 *
 *  Discussion:
 *      Invoked upon completion of a -[discoverDescriptorsForCharacteristic:] request.
 *      If successful, "error" is nil and discovered descriptors, if any, have been merged into the
 *      "descriptors" property of the characteristic.
 *      If unsuccessful, "error" is set with the encountered failure.
 *
 */
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverDescriptorsForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;

/*
 *  peripheral:didUpdateValueForDescriptor:error:
 *
 *  Discussion:
 *      Invoked upon completion of a -[readValueForDescriptor:] request.
 *      If unsuccessful, "error" is set with the encountered failure.
 *
 */
- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForDescriptor:(CBDescriptor *)descriptor error:(NSError *)error;

/*
 *  peripheral:didWriteValueForDescriptor:error:
 *
 *  Discussion:
 *      Invoked upon completion of a -[writeValue:forDescriptor:] request.
 *      If unsuccessful, "error" is set with the encountered failure.
 *
 */
- (void)peripheral:(CBPeripheral *)peripheral didWriteValueForDescriptor:(CBDescriptor *)descriptor error:(NSError *)error;

@end
