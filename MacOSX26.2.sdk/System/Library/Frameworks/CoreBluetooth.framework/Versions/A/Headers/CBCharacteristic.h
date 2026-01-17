/*
 *	@file CBCharacteristic.h
 *	@framework CoreBluetooth
 *
 *	@copyright 2011 Apple, Inc. All rights reserved.
 */

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBAttribute.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @enum CBCharacteristicProperties
 *
 *	@discussion Characteristic properties determine how the characteristic value can be	used, or how the descriptor(s) can be accessed. Can be combined. Unless
 *				otherwise specified, properties are valid for local characteristics published via @link CBPeripheralManager @/link.
 *
 *	@constant CBCharacteristicPropertyBroadcast						Permits broadcasts of the characteristic value using a characteristic configuration descriptor. Not allowed for local characteristics.
 *	@constant CBCharacteristicPropertyRead							Permits reads of the characteristic value.
 *	@constant CBCharacteristicPropertyWriteWithoutResponse			Permits writes of the characteristic value, without a response.
 *	@constant CBCharacteristicPropertyWrite							Permits writes of the characteristic value.
 *	@constant CBCharacteristicPropertyNotify						Permits notifications of the characteristic value, without a response.
 *	@constant CBCharacteristicPropertyIndicate						Permits indications of the characteristic value.
 *	@constant CBCharacteristicPropertyAuthenticatedSignedWrites		Permits signed writes of the characteristic value
 *	@constant CBCharacteristicPropertyExtendedProperties			If set, additional characteristic properties are defined in the characteristic extended properties descriptor. Not allowed for local characteristics.
 *	@constant CBCharacteristicPropertyNotifyEncryptionRequired		If set, only trusted devices can enable notifications of the characteristic value.
 *	@constant CBCharacteristicPropertyIndicateEncryptionRequired	If set, only trusted devices can enable indications of the characteristic value.
 *
 */
typedef NS_OPTIONS(NSUInteger, CBCharacteristicProperties) {
	CBCharacteristicPropertyBroadcast												= 0x01,
	CBCharacteristicPropertyRead													= 0x02,
	CBCharacteristicPropertyWriteWithoutResponse									= 0x04,
	CBCharacteristicPropertyWrite													= 0x08,
	CBCharacteristicPropertyNotify													= 0x10,
	CBCharacteristicPropertyIndicate												= 0x20,
	CBCharacteristicPropertyAuthenticatedSignedWrites								= 0x40,
	CBCharacteristicPropertyExtendedProperties										= 0x80,
	CBCharacteristicPropertyNotifyEncryptionRequired NS_ENUM_AVAILABLE(10_9, 6_0)	= 0x100,
	CBCharacteristicPropertyIndicateEncryptionRequired NS_ENUM_AVAILABLE(10_9, 6_0)	= 0x200
};



/*!
 *  @class CBCharacteristic
 *
 *  @discussion
 *      Represents a service's characteristic.
 *
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
CB_EXTERN_CLASS @interface CBCharacteristic : CBAttribute

/*!
 * @property service
 *
 *  @discussion
 *      A back-pointer to the service this characteristic belongs to.
 *
 */
@property(weak, readonly, nonatomic) CBService *service;

/*!
 * @property properties
 *
 *  @discussion
 *      The properties of the characteristic.
 *
 */
@property(readonly, nonatomic) CBCharacteristicProperties properties;

/*!
 * @property value
 *
 *  @discussion
 *      The value of the characteristic.
 *
 */
@property(retain, readonly, nullable) NSData *value;

/*!
 * @property descriptors
 *
 *  @discussion
 *      A list of the CBDescriptors that have so far been discovered in this characteristic.
 *
 */
@property(retain, readonly, nullable) NSArray<CBDescriptor *> *descriptors;

/*!
 * @property isBroadcasted
 *
 *  @discussion
 *      Whether the characteristic is currently broadcasted or not.
 *
 */
@property(readonly) BOOL isBroadcasted NS_DEPRECATED(10_9, 10_13, 5_0, 8_0);

/*!
 * @property isNotifying
 *
 *  @discussion
 *      Whether the characteristic is currently notifying or not.
 *
 */
@property(readonly) BOOL isNotifying;

@end

/*!
 *  @enum CBAttributePermissions
 *
 *	@discussion Read, write, and encryption permissions for an ATT attribute. Can be combined.
 *
 *	@constant CBAttributePermissionsReadable					Read-only.
 *	@constant CBAttributePermissionsWriteable					Write-only.
 *	@constant CBAttributePermissionsReadEncryptionRequired		Readable by trusted devices.
 *	@constant CBAttributePermissionsWriteEncryptionRequired		Writeable by trusted devices.
 *
 */
typedef NS_OPTIONS(NSUInteger, CBAttributePermissions) {
	CBAttributePermissionsReadable					= 0x01,
	CBAttributePermissionsWriteable					= 0x02,
	CBAttributePermissionsReadEncryptionRequired	= 0x04,
	CBAttributePermissionsWriteEncryptionRequired	= 0x08
} NS_ENUM_AVAILABLE(10_9, 6_0);


/*!
 *	@class CBMutableCharacteristic
 *
 *	@discussion Used to create a local characteristic, which can be added to the local database via <code>CBPeripheralManager</code>. Once a characteristic
 *				is published, it is cached and can no longer be changed. 
 *				If a characteristic value is specified, it will be cached and marked <code>CBCharacteristicPropertyRead</code> and 
 *				<code>CBAttributePermissionsReadable</code>. If a characteristic value needs to be writeable, or may change during the lifetime of the
 *				published <code>CBService</code>, it is considered a dynamic value and will be requested on-demand. Dynamic values are identified by a
 *				<i>value</i> of <i>nil</i>.
 *
 */
NS_CLASS_AVAILABLE(10_9, 6_0)
CB_EXTERN_CLASS @interface CBMutableCharacteristic : CBCharacteristic

/*!
 *	@property permissions
 *
 *	@discussion The permissions of the characteristic value.
 *
 *	@see		CBAttributePermissions
 */
@property(assign, readwrite, nonatomic) CBAttributePermissions permissions;

/*!
 *  @property subscribedCentrals
 *
 *  @discussion For notifying characteristics, the set of currently subscribed centrals.
 */
@property(retain, readonly, nullable) NSArray<CBCentral *> *subscribedCentrals NS_AVAILABLE(10_9, 7_0);

@property(assign, readwrite, nonatomic) CBCharacteristicProperties properties;
@property(retain, readwrite, nullable) NSData *value;
@property(retain, readwrite, nullable) NSArray<CBDescriptor *> *descriptors;

/*!
 *  @method initWithType:properties:value:permissions
 *
 *  @param UUID			The Bluetooth UUID of the characteristic.
 *  @param properties	The properties of the characteristic.
 *  @param value		The characteristic value to be cached. If <i>nil</i>, the value will be dynamic and requested on-demand.
 *	@param permissions	The permissions of the characteristic value.
 *
 *  @discussion			Returns an initialized characteristic.
 *
 */
- (instancetype)initWithType:(CBUUID *)UUID properties:(CBCharacteristicProperties)properties value:(nullable NSData *)value permissions:(CBAttributePermissions)permissions API_AVAILABLE(ios(6.0), macos(10.9)) API_UNAVAILABLE(watchos, tvos) NS_DESIGNATED_INITIALIZER
#if TARGET_OS_VISION
API_UNAVAILABLE(visionos)
#endif
;

@end

NS_ASSUME_NONNULL_END
