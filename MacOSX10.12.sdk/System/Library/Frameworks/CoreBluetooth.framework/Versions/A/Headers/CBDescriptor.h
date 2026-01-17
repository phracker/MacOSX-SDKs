/*
 *	@file CBDescriptor.h
 *	@framework CoreBluetooth
 *
 *	@copyright 2011 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CBCharacteristic, CBUUID;

/*!
 * @class CBDescriptor
 *
 *  @discussion
 *      Represents a characteristic's descriptor.
 *
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
CB_EXTERN_CLASS @interface CBDescriptor : NSObject
{
@protected
	CBCharacteristic	*_characteristic;
	CBUUID				*_UUID;
	
	id					 _value;
	
	CBPeripheral		*_peripheral;
	NSNumber			*_handle;
}

/*!
 *  @property characteristic
 *
 *  @discussion
 *      A back-pointer to the characteristic this descriptor belongs to.
 *
 */
@property(assign, readonly, nonatomic) CBCharacteristic *characteristic;

/*!
 *  @property UUID
 *
 *  @discussion
 *      The Bluetooth UUID of the descriptor.
 *
 */
@property(readonly, nonatomic) CBUUID *UUID;

/*!
 *  @property value
 *
 *  @discussion
 *      The value of the descriptor. The corresponding value types for the various descriptors are detailed in @link CBUUID.h @/link.
 *
 */
@property(retain, readonly, nullable) id value;

@end


/*!
 * @class CBMutableDescriptor
 *
 * @discussion
 *      Used to create a local characteristic descriptor, which can be added to the local database via <code>CBPeripheralManager</code>.
 *		Once a descriptor is published, it is cached and can no longer be changed.
 *		Descriptor types are detailed in @link CBUUID.h @/link, but only the <code>Characteristic User Description</code> and <code>Characteristic Presentation
 *		Format</code> descriptors are currently supported. The <code>Characteristic Extended Properties</code> and <code>Client Characteristic 
 *		Configuration</code> descriptors will be created automatically upon publication of the parent service, depending on the properties of the characteristic itself.
 */
NS_CLASS_AVAILABLE(10_9, 6_0)
CB_EXTERN_CLASS @interface CBMutableDescriptor : CBDescriptor
{
@private
	NSNumber *_ID;
}

/*!
 *  @method initWithType:value:
 *
 *  @param UUID		The Bluetooth UUID of the descriptor.
 *  @param value	The value of the descriptor.
 *
 *  @discussion 	Returns a decriptor, initialized with a service type and value. The <i>value</i> is required and cannot be updated dynamically
 *					once the parent service has been published.
 *
 */
- (id)initWithType:(CBUUID *)UUID value:(nullable id)value;

@end

NS_ASSUME_NONNULL_END
