/*
 *	@file CBCentral.h
 *	@framework CoreBluetooth
 *
 *  @discussion Representation of a remote central.
 *
 *	@copyright 2012 Apple, Inc. All rights reserved.
 */

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBDefines.h>
#import <CoreBluetooth/CBPeer.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @class CBCentral
 *
 *  @discussion Represents a remote central.
 *
 */
NS_CLASS_AVAILABLE(10_9, 6_0)
CB_EXTERN_CLASS @interface CBCentral : CBPeer

/*!
 *  @property	maximumUpdateValueLength
 *
 *  @discussion	The maximum amount of data, in bytes, that can be received by the central in a single notification or indication.
 *
 *	@see		updateValue:forCharacteristic:onSubscribedCentrals:
 */
@property(readonly, nonatomic) NSUInteger maximumUpdateValueLength;

@end

NS_ASSUME_NONNULL_END
