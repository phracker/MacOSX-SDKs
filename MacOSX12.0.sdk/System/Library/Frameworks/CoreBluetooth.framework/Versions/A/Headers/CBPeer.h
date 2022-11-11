/*
 *	@file CBPeer.h
 *	@framework CoreBluetooth
 *
 *	@copyright 2014 Apple, Inc. All rights reserved.
 */

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_13, 8_0)
CB_EXTERN_CLASS @interface CBPeer : NSObject <NSCopying>

- (instancetype)init NS_UNAVAILABLE;

/*!
 *  @property identifier
 *
 *  @discussion The unique, persistent identifier associated with the peer.
 */
@property(readonly, nonatomic) NSUUID *identifier NS_AVAILABLE(10_13, 7_0);

@end

NS_ASSUME_NONNULL_END
