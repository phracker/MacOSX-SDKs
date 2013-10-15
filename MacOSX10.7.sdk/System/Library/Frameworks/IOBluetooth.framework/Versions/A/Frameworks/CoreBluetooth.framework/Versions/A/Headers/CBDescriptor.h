/*
 *	CBDescriptor.h
 *	CoreBluetooth
 *
 *	Copyright 2011 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>



@class CBCharacteristic, CBUUID;

/*
 *  CBDescriptor
 *
 *  Discussion:
 *      Represents a characteristic's descriptor.
 *
 */
NS_CLASS_AVAILABLE(10_7, NA)
CB_EXTERN_CLASS @interface CBDescriptor : NSObject
{
@package
	CBCharacteristic	*_characteristic;
	CBUUID				*_UUID;
	
	id					 _value;
}

/*
 *  service
 *
 *  Discussion:
 *      A back-pointer to the characteristic this descriptor belongs to.
 *
 */
@property(readonly, nonatomic) CBCharacteristic *characteristic;

/*
 *  UUID
 *
 *  Discussion:
 *      The Bluetooth UUID of the descriptor.
 *
 */
@property(readonly, nonatomic) CBUUID *UUID;

/*
 *  value
 *
 *  Discussion:
 *      The value of the descriptor.
 *
 */
@property(retain, readonly) id value;

@end
