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



@class CBPeripheral, CBUUID;

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
@property(weak, readonly, nonatomic) CBPeripheral *peripheral;

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
@property(retain, readonly) NSArray *includedServices;

/*!
 * @property characteristics
 *
 * @discussion
 *      A list of CBCharacteristics that have so far been discovered in this service.
 *
 */
@property(retain, readonly) NSArray *characteristics;

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

@property(retain, readwrite, nonatomic) CBUUID *UUID;
@property(readwrite, nonatomic) BOOL isPrimary;
@property(retain, readwrite) NSArray *includedServices;
@property(retain, readwrite) NSArray *characteristics;

/*!
 *  @method initWithType:primary:
 *
 *  @param UUID			The Bluetooth UUID of the service.
 *  @param isPrimary	The type of the service (primary or secondary).
 *
 *  @discussion			Returns a service, initialized with a service type and UUID.
 *
 */
- (id)initWithType:(CBUUID *)UUID primary:(BOOL)isPrimary;

@end
