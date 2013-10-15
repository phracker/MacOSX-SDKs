/*
 *	CBUUID.h
 *	CoreBluetooth
 *
 *	Copyright 2011 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>



CB_EXTERN NSString * const CBUUIDGenericAccessProfileString;
CB_EXTERN NSString * const CBUUIDGenericAttributeProfileString;

CB_EXTERN NSString * const CBUUIDCharacteristicExtendedPropertiesString;
CB_EXTERN NSString * const CBUUIDCharacteristicUserDescriptionString;
CB_EXTERN NSString * const CBUUIDClientCharacteristicConfigurationString;
CB_EXTERN NSString * const CBUUIDServerCharacteristicConfigurationString;
CB_EXTERN NSString * const CBUUIDCharacteristicFormatString;
CB_EXTERN NSString * const CBUUIDCharacteristicAggregateFormatString;

CB_EXTERN NSString * const CBUUIDDeviceNameString;
CB_EXTERN NSString * const CBUUIDAppearanceString;
CB_EXTERN NSString * const CBUUIDPeripheralPrivacyFlagString;
CB_EXTERN NSString * const CBUUIDReconnectionAddressString;
CB_EXTERN NSString * const CBUUIDPeripheralPreferredConnectionParametersString;
CB_EXTERN NSString * const CBUUIDServiceChangedString;



/*
 *  CBUUID
 *
 *  Discussion:
 *      A 16-bits, 32-bit, or 128 bits Bluetooth UUID.
 *      16-bits and 32-bits UUIDs are implicitely pre-filled with the Bluetooth Base UUID.
 *
 */
NS_CLASS_AVAILABLE(10_7, NA)
CB_EXTERN_CLASS @interface CBUUID : NSObject <NSCopying>
{
@private
	NSData	*_data;
	NSRange	 _range;
}

/*
 *  data
 *
 *  Discussion:
 *      The UUID as NSData.
 *
 */
@property(nonatomic, readonly) NSData *data;

/*
 *  UUIDWithString:
 *
 *  Discussion:
 *      Creates a CBUUID with either a 16-bits, 32-bits, or 128-bits UUID string representation.
 *
 */
+ (CBUUID *)UUIDWithString:(NSString *)theString;

/*
 *  UUIDWithData:
 *
 *  Discussion:
 *      Creates a CBUUID with either a 16-bits, 32-bits, or 128-bits UUID data container.
 *
 */
+ (CBUUID *)UUIDWithData:(NSData *)theData;

/*
 *  UUIDWithCFUUID:
 *
 *  Discussion:
 *      Creates a CBUUID with a CFUUIDRef.
 *
 */
+ (CBUUID *)UUIDWithCFUUID:(CFUUIDRef)theUUID;

@end
