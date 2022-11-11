/*
 *	@file CBService.h
 *	@framework CoreBluetooth
 *
 *  @discussion A Bluetooth LE service representation. A LE Service provides a number of
 *		characteristics and may also reference other services.
 *
 *	@copyright 2011 Apple, Inc. All rights reserved.
 */

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBAttribute.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @class CBService
 *
 * @discussion
 *      Represents a peripheral's service or a service's included service.
 *
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
CB_EXTERN_CLASS @interface CBService : CBAttribute

/*!
 * @property peripheral
 *
 * @discussion
 *      A back-pointer to the peripheral this service belongs to.
 *
 */
@property(weak, readonly, nonatomic) CBPeripheral *peripheral;

/*!
 * @property isPrimary
 *
 * @discussion
 *      The type of the service (primary or secondary).
 *
 */
@property(readonly, nonatomic) BOOL isPrimary;

/*!
 * @property includedServices
 *
 * @discussion
 *      A list of included CBServices that have so far been discovered in this service.
 *
 */
@property(retain, readonly, nullable) NSArray<CBService *> *includedServices;

/*!
 * @property characteristics
 *
 * @discussion
 *      A list of CBCharacteristics that have so far been discovered in this service.
 *
 */
@property(retain, readonly, nullable) NSArray<CBCharacteristic *> *characteristics;

@end


/*!
 * @class CBMutableService
 *
 * @discussion
 *      Used to create a local service or included service, which can be added to the local database via <code>CBPeripheralManager</code>.
 *		Once a service is published, it is cached and can no longer be changed. This class adds write access to all properties in the
 *		@link CBService @/link class.
 *
 */
NS_CLASS_AVAILABLE(10_9, 6_0)
CB_EXTERN_CLASS @interface CBMutableService : CBService

@property(retain, readwrite, nullable) NSArray<CBService *> *includedServices;
@property(retain, readwrite, nullable) NSArray<CBCharacteristic *> *characteristics;

/*!
 *  @method initWithType:primary:
 *
 *  @param UUID			The Bluetooth UUID of the service.
 *  @param isPrimary	The type of the service (primary or secondary).
 *
 *  @discussion			Returns a service, initialized with a service type and UUID.
 *
 */
- (instancetype)initWithType:(CBUUID *)UUID primary:(BOOL)isPrimary NS_DESIGNATED_INITIALIZER __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
