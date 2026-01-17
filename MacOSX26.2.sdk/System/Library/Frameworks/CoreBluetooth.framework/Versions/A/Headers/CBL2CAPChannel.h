/*
 *	@file CBL2CAPChannel.h
 *	@framework CoreBluetooth
 *
 *  @discussion
 *
 *	@copyright 2017 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBPeer.h>
#import <Foundation/Foundation.h>

typedef uint16_t CBL2CAPPSM;

/*!
 *  @class CBL2CAPChannel
 *
 *  @discussion A CBL2CAPChannel represents a live L2CAP connection to a remote device
 */
NS_CLASS_AVAILABLE(10_13, 11_0)
CB_EXTERN_CLASS @interface CBL2CAPChannel : NSObject

/*!
 *  @property peer
 *
 *  @discussion The peer connected to the channel
 */
@property(readonly, nonatomic) CBPeer *peer;

/*!
 *  @property inputStream
 *
 *  @discussion An NSStream used for reading data from the remote peer
 */
@property(readonly, nonatomic) NSInputStream *inputStream;

/*!
 *  @property outputStream
 *
 *  @discussion An NSStream used for writing data to the peer
 */
@property(readonly, nonatomic) NSOutputStream *outputStream;

/*!
 *  @property PSM
 *
 *  @discussion The PSM (Protocol/Service Multiplexer) of the channel
 */
@property(readonly, nonatomic) CBL2CAPPSM PSM;
@end
