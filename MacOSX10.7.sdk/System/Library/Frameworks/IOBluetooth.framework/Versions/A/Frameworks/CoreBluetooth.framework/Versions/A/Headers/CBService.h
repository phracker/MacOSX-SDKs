/*
 *	CBService.h
 *	CoreBluetooth
 *
 *	Copyright 2011 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>



@class CBPeripheral, CBUUID;

/*
 *  CBService
 *
 *  Discussion:
 *      Represents a peripheral's service or a service's included service.
 *
 */
NS_CLASS_AVAILABLE(10_7, NA)
CB_EXTERN_CLASS @interface CBService : NSObject
{
@package
	CBPeripheral	*_peripheral;
	CBUUID			*_UUID;
	
	NSArray			*_includedServices;
	NSArray			*_characteristics;
}

/*
 *  peripheral
 *
 *  Discussion:
 *      A back-pointer to the peripheral this service belongs to.
 *
 */
@property(readonly, nonatomic) CBPeripheral *peripheral;

/*
 *  UUID
 *
 *  Discussion:
 *      The Bluetooth UUID of the service.
 *
 */
@property(readonly, nonatomic) CBUUID *UUID;

/*
 *  includedServices
 *
 *  Discussion:
 *      A list of included CBServices that have so far been discovered in this service.
 *
 */
@property(retain, readonly) NSArray *includedServices;

/*
 *  characteristics
 *
 *  Discussion:
 *      A list of CBCharacteristics that have so far been discovered in this service.
 *
 */
@property(retain, readonly) NSArray *characteristics;

@end
