/*
 *	@file CBService.h
 *	@framework CoreBluetooth
 *
 *  @discussion A Bluetooth LE service representation. A LE Service provides a number of
 *		characteristics and may also reference other services.
 *
 *	@copyright 2011 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CBPeripheral, CBUUID, CBCharacteristic;

/*!
 * @class CBService
 *
 * @discussion
 *      Represents a peripheral's service or a service's included service.
 *
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
CB_EXTERN_CLASS @interface CBService : NSObject
{
@protected
	CBPeripheral	*_peripheral;
	CBUUID			*_UUID;
	BOOL			_isPrimary;
	
	NSArray			*_includedServices;
	NSArray			*_characteristics;
	
	NSNumber		*_startHandle;
	NSNumber		*_endHandle;
}

/*!
 * @property peripheral
 *
 * @discussion
 *      A back-pointer to the peripheral this service belongs to.
 *
 */
@property(assign, readonly, nonatomic, nonnull) CBPeripheral *peripheral;

/*!
 * @property UUID
 *
 * @discussion
 *      The Bluetooth UUID of the service.
 *
 */
@property(readonly, nonatomic) CBUUID *UUID;

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
{
@private
	NSNumber *_ID;
}

@property(retain, readwrite, nonatomic, nullable) CBUUID *UUID;
@property(readwrite, nonatomic) BOOL isPrimary;
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
- (id)initWithType:(nullable CBUUID *)UUID primary:(BOOL)isPrimary;

@end

NS_ASSUME_NONNULL_END
