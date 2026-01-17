/*
 *	@file CBAttribute.h
 *	@framework CoreBluetooth
 *
 *	@copyright 2014 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CBUUID;
@class CBPeripheral, CBCentral;
@class CBService, CBCharacteristic, CBDescriptor;

NS_CLASS_AVAILABLE(10_13, 8_0)
CB_EXTERN_CLASS @interface CBAttribute : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @property UUID
 *
 * @discussion
 *      The Bluetooth UUID of the attribute.
 *
 */
@property(readonly, nonatomic) CBUUID *UUID;

@end

NS_ASSUME_NONNULL_END
