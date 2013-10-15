/*
 *	CBCharacteristic.h
 *	CoreBluetooth
 *
 *	Copyright 2011 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>



enum {
	CBCharacteristicPropertyBroadcast					= 0x01,
	CBCharacteristicPropertyRead						= 0x02,
	CBCharacteristicPropertyWriteWithoutResponse		= 0x04,
	CBCharacteristicPropertyWrite						= 0x08,
	CBCharacteristicPropertyNotify						= 0x10,
	CBCharacteristicPropertyIndicate					= 0x20,
	CBCharacteristicPropertyAuthenticatedSignedWrites	= 0x40,
	CBCharacteristicPropertyExtendedProperties			= 0x80,
};
typedef NSUInteger CBCharacteristicProperties;



@class CBService, CBUUID;

/*
 *  CBCharacteristic
 *
 *  Discussion:
 *      Represents a service's characteristic.
 *
 */
NS_CLASS_AVAILABLE(10_7, NA)
CB_EXTERN_CLASS @interface CBCharacteristic : NSObject
{
@package
	CBService					*_service;
	CBUUID						*_UUID;
	CBCharacteristicProperties	 _properties;
	
	NSData						*_value;
	NSArray						*_descriptors;
	BOOL						 _isBroadcasted;
	BOOL						 _isNotifying;
}

/*
 *  service
 *
 *  Discussion:
 *      A back-pointer to the service this characteristic belongs to.
 *
 */
@property(readonly, nonatomic) CBService *service;

/*
 *  UUID
 *
 *  Discussion:
 *      The Bluetooth UUID of the characteristic.
 *
 */
@property(readonly, nonatomic) CBUUID *UUID;

/*
 *  properties
 *
 *  Discussion:
 *      The properties of the characteristic.
 *
 */
@property(readonly, nonatomic) CBCharacteristicProperties properties;

/*
 *  value
 *
 *  Discussion:
 *      The value of the characteristic.
 *
 */
@property(retain, readonly) NSData *value;

/*
 *  descriptors
 *
 *  Discussion:
 *      A list of the CBDescriptors that have so far been discovered in this characteristic.
 *
 */
@property(retain, readonly) NSArray *descriptors;

/*
 *  isBroadcasted
 *
 *  Discussion:
 *      Whether the characteristic is currently broadcasted or not.
 *
 */
@property(readonly) BOOL isBroadcasted;

/*
 *  isNotifying
 *
 *  Discussion:
 *      Whether the characteristic is currently notifying or not.
 *
 */
@property(readonly) BOOL isNotifying;

@end
