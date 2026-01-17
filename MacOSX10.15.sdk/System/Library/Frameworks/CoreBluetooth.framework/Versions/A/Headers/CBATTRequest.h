/*
 *	@file CBATTRequest.h
 *	@framework CoreBluetooth
 *
 *  @discussion
 *
 *	@copyright 2012 Apple, Inc. All rights reserved.
 */

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CBCentral, CBCharacteristic;

/*!
 *  @class CBATTRequest
 *
 *  @discussion Represents a read or write request from a central.
 *
 */
NS_CLASS_AVAILABLE(10_9, 6_0)
CB_EXTERN_CLASS @interface CBATTRequest : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 *  @property central
 *
 *  @discussion The central that originated the request.
 *
 */
@property(readonly, nonatomic) CBCentral *central;

/*!
 *  @property characteristic
 *
 *  @discussion The characteristic whose value will be read or written.
 *
 */
@property(readonly, nonatomic) CBCharacteristic *characteristic;

/*!
 *  @property offset
 *
 *  @discussion The zero-based index of the first byte for the read or write.
 *
 */
@property(readonly, nonatomic) NSUInteger offset;

/*!
 *  @property value
 *
 *  @discussion The data being read or written.
 *				For read requests, <i>value</i> will be nil and should be set before responding via @link respondToRequest:withResult: @/link.
 *				For write requests, <i>value</i> will contain the data to be written.
 *
 */
@property(readwrite, copy, nullable) NSData *value;

@end

NS_ASSUME_NONNULL_END
