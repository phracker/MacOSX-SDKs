/*
 *	@file CBCentral.h
 *	@framework CoreBluetooth
 *
 *  @discussion Representation of a remote central.
 *
 *	@copyright 2012 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @class CBCentral
 *
 *  @discussion Represents a remote central.
 *
 */
NS_CLASS_AVAILABLE(10_9, 6_0)
CB_EXTERN_CLASS @interface CBCentral : NSObject <NSCopying>
{
@private
	CFUUIDRef	_UUID;
	NSUUID		*_identifier;
	NSUInteger	_maximumUpdateValueLength;
}

/*!
 *  @property	UUID
 *
 *  @discussion The UUID of the central. This UUID can be used to retrieve the equivalent @link CBPeripheral @/link object via @link retrievePeripherals: @/link.
 *
 *	@deprecated Use the {@link identifier} property instead.
 */
@property(readonly, nonatomic) CFUUIDRef UUID NS_DEPRECATED(10_7, 10_9, 5_0, 7_0);

/*!
 *  @property	identifier
 *
 *  @discussion	The unique identifier associated with the central. This identifier can be used to retrieve the equivalent @link CBPeripheral @/link object
 *				via @link retrievePeripheralsWithIdentifiers: @/link.
 */
@property(readonly, nonatomic) NSUUID *identifier;

/*!
 *  @property	maximumUpdateValueLength
 *
 *  @discussion	The maximum amount of data, in bytes, that can be received by the central in a single notification or indication.
 
 *	@see		updateValue:forCharacteristic:onSubscribedCentrals:
 */
@property(readonly, nonatomic) NSUInteger maximumUpdateValueLength;

@end

NS_ASSUME_NONNULL_END