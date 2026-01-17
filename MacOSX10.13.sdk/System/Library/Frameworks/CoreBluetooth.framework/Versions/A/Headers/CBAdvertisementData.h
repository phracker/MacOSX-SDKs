/*
 *	@file CBAdvertisementData.h
 *	@framework CoreBluetooth
 *
 *	@copyright 2012 Apple, Inc. All rights reserved.
 */

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @constant CBAdvertisementDataLocalNameKey
 *
 *  @discussion A <code>NSString</code> containing the local name of a peripheral.
 *
 */
CB_EXTERN NSString * const CBAdvertisementDataLocalNameKey;


/*!
 *  @constant CBAdvertisementDataTxPowerLevelKey
 *
 *  @discussion A <code>NSNumber</code> containing the transmit power of a peripheral.
 *
 */
CB_EXTERN NSString * const CBAdvertisementDataTxPowerLevelKey;


/*!
 *  @constant CBAdvertisementDataServiceUUIDsKey
 *
 *  @discussion A list of one or more <code>CBUUID</code> objects, representing <code>CBService</code> UUIDs.
 *
 */
CB_EXTERN NSString * const CBAdvertisementDataServiceUUIDsKey;


/*!
 *  @constant CBAdvertisementDataServiceDataKey
 *
 *  @discussion A dictionary containing service-specific advertisement data. Keys are <code>CBUUID</code> objects, representing
 *              <code>CBService</code> UUIDs. Values are <code>NSData</code> objects.
 *
 */
CB_EXTERN NSString * const CBAdvertisementDataServiceDataKey;


/*!
 *  @constant CBAdvertisementDataManufacturerDataKey
 *
 *  @discussion A <code>NSData</code> object containing the manufacturer data of a peripheral.
 *
 */
CB_EXTERN NSString * const CBAdvertisementDataManufacturerDataKey;


/*!
 *  @constant CBAdvertisementDataOverflowServiceUUIDsKey
 *
 *  @discussion A list of one or more <code>CBUUID</code> objects, representing <code>CBService</code> UUIDs that were
 *              found in the "overflow" area of the advertising data. Due to the nature of the data stored in this area,
 *              UUIDs listed here are "best effort" and may not always be accurate.
 *
 *  @see        startAdvertising:
 *
 */
CB_EXTERN NSString * const CBAdvertisementDataOverflowServiceUUIDsKey NS_AVAILABLE(10_9, 6_0);


/*!
 *  @constant CBAdvertisementDataIsConnectable
 *
 *  @discussion A NSNumber (Boolean) indicating whether or not the advertising event type was connectable. This can be used to determine
 *				whether or not a peripheral is connectable in that instant.
 *
 */
CB_EXTERN NSString * const CBAdvertisementDataIsConnectable NS_AVAILABLE(10_9, 7_0);


/*!
 *  @constant CBAdvertisementDataSolicitedServiceUUIDsKey
 *
 *  @discussion A list of one or more <code>CBUUID</code> objects, representing <code>CBService</code> UUIDs.
 *
 */
CB_EXTERN NSString * const CBAdvertisementDataSolicitedServiceUUIDsKey NS_AVAILABLE(10_9, 7_0);

NS_ASSUME_NONNULL_END
