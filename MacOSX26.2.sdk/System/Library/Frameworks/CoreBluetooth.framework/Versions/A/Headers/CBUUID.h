/*
 *	@file CBUUID.h
 *	@framework CoreBluetooth
 *
 *  @discussion The CBUUID class represents bluetooth LE UUIDs. It automatically handles
 *     transformations of 16 and 32 bit UUIDs into 128 bit UUIDs.
 *
 *	@copyright 2011 Apple, Inc. All rights reserved.
 */

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @const CBUUIDCharacteristicExtendedPropertiesString
 *  @discussion The string representation of the UUID for the extended properties descriptor.
 *				The corresponding value for this descriptor is an <code>NSNumber</code> object.
 */
CB_EXTERN NSString * const CBUUIDCharacteristicExtendedPropertiesString;
/*!
 *  @const CBUUIDCharacteristicUserDescriptionString
 *  @discussion The string representation of the UUID for the user description descriptor.
 *				The corresponding value for this descriptor is an <code>NSString</code> object.
 */
CB_EXTERN NSString * const CBUUIDCharacteristicUserDescriptionString;
/*!
 *  @const CBUUIDClientCharacteristicConfigurationString
 *  @discussion The string representation of the UUID for the client configuration descriptor.
 *				The corresponding value for this descriptor is an <code>NSNumber</code> object.
 */
CB_EXTERN NSString * const CBUUIDClientCharacteristicConfigurationString;
/*!
 *  @const CBUUIDServerCharacteristicConfigurationString
 *  @discussion The string representation of the UUID for the server configuration descriptor.
 *				The corresponding value for this descriptor is an <code>NSNumber</code> object.
 */
CB_EXTERN NSString * const CBUUIDServerCharacteristicConfigurationString;
/*!
 *  @const CBUUIDCharacteristicFormatString
 *  @discussion The string representation of the UUID for the presentation format descriptor.
 *				The corresponding value for this descriptor is an <code>NSData</code> object.
 */
CB_EXTERN NSString * const CBUUIDCharacteristicFormatString;
/*!
 *  @const CBUUIDCharacteristicAggregateFormatString
 *  @discussion The string representation of the UUID for the aggregate descriptor.
 */
CB_EXTERN NSString * const CBUUIDCharacteristicAggregateFormatString;
/*!
 *  @const CBUUIDCharacteristicValidRangeString
 *  @discussion Data representing the valid min/max values accepted for a characteristic.
 */
CB_EXTERN NSString * const CBUUIDCharacteristicValidRangeString;

/*!
 *  @const CBUUIDCharacteristicObservationScheduleString
 *  @discussion Data representing the observation schedule for a characteristic.
 */
CB_EXTERN NSString * const CBUUIDCharacteristicObservationScheduleString;

/*!
 *  @const CBUUIDL2CAPPSMCharacteristicString
 *  @discussion The PSM (a little endian uint16_t) of an L2CAP Channel associated with the GATT service
 *				containing this characteristic.  Servers can publish this characteristic with the UUID
 *				ABDD3056-28FA-441D-A470-55A75A52553A
 */
CB_EXTERN NSString * const CBUUIDL2CAPPSMCharacteristicString NS_AVAILABLE(10_13, 11_0);

/*!
 * @class CBUUID
 *
 * @discussion
 *      A 16-bit, 32-bit, or 128-bit Bluetooth UUID.
 *      16-bit and 32-bit UUIDs are implicitly pre-filled with the Bluetooth Base UUID.
 *
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
CB_EXTERN_CLASS @interface CBUUID : NSObject <NSCopying>

/*!
 * @property data
 *
 *  @discussion
 *      The UUID as NSData.
 *
 */
@property(nonatomic, readonly) NSData *data;

/*!
 * @property UUIDString
 *
 *  @discussion
 *      The UUID as NSString.
 *
 */
@property(nonatomic, readonly) NSString *UUIDString NS_AVAILABLE(10_10, 7_1);

/*!
 * @method UUIDWithString:
 *
 *  @discussion
 *      Creates a CBUUID with a 16-bit, 32-bit, or 128-bit UUID string representation.
 *      The expected format for 128-bit UUIDs is a string punctuated by hyphens, for example 68753A44-4D6F-1226-9C60-0050E4C00067.
 *
 */
+ (CBUUID *)UUIDWithString:(NSString *)theString;

/*!
 * @method UUIDWithData:
 *
 *  @discussion
 *      Creates a CBUUID with a 16-bit, 32-bit, or 128-bit UUID data container.
 *
 */
+ (CBUUID *)UUIDWithData:(NSData *)theData;

/*!
 * @method UUIDWithCFUUID:
 *
 *  @discussion
 *      Creates a CBUUID with a CFUUIDRef.
 *
 */
+ (CBUUID *)UUIDWithCFUUID:(CFUUIDRef)theUUID NS_DEPRECATED(10_7, 10_13, 5_0, 9_0);

/*!
 * @method UUIDWithNSUUID:
 *
 *  @discussion
 *      Creates a CBUUID with an NSUUID.
 *
 */
+ (CBUUID *)UUIDWithNSUUID:(NSUUID *)theUUID NS_AVAILABLE(10_9, 7_0);

@end

NS_ASSUME_NONNULL_END
