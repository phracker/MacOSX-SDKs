/*
 *	@file CBError.h
 *	@framework CoreBluetooth
 *
 *  @discussion The possible errors returned during LE transactions.
 *
 *	@copyright 2011 Apple, Inc. All rights reserved.
 */

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

CB_EXTERN NSString * const CBErrorDomain;

/*!
 * @enum CBError
 *
 * @discussion The possible errors returned during LE transactions.
 */
typedef NS_ENUM(NSInteger, CBError) {
	CBErrorUnknown												= 0,
	CBErrorInvalidParameters NS_ENUM_AVAILABLE(10_9, 6_0)		= 1,
	CBErrorInvalidHandle NS_ENUM_AVAILABLE(10_9, 6_0)			= 2,
	CBErrorNotConnected NS_ENUM_AVAILABLE(10_9, 6_0)			= 3,
	CBErrorOutOfSpace NS_ENUM_AVAILABLE(10_9, 6_0)				= 4,
	CBErrorOperationCancelled NS_ENUM_AVAILABLE(10_9, 6_0)		= 5,
	CBErrorConnectionTimeout NS_ENUM_AVAILABLE(10_9, 6_0)		= 6,
	CBErrorPeripheralDisconnected NS_ENUM_AVAILABLE(10_9, 6_0)	= 7,
	CBErrorUUIDNotAllowed NS_ENUM_AVAILABLE(10_9, 6_0)			= 8,
	CBErrorAlreadyAdvertising NS_ENUM_AVAILABLE(10_9, 6_0)		= 9,
	CBErrorConnectionFailed NS_ENUM_AVAILABLE(10_13, 7_1)		= 10,
	CBErrorConnectionLimitReached NS_ENUM_AVAILABLE(10_13, 9_0)	= 11,
	CBErrorUnkownDevice NS_ENUM_DEPRECATED(10_13, 10_15, 9_0, 13_0, "Use CBErrorUnknownDevice instead") = 12,
	CBErrorUnknownDevice NS_ENUM_AVAILABLE(10_14, 12_0)			= 12,
	CBErrorOperationNotSupported NS_ENUM_AVAILABLE(10_14, 12_0)	= 13,
	CBErrorPeerRemovedPairingInformation NS_ENUM_AVAILABLE(10_15, 13_4)	= 14,
	CBErrorEncryptionTimedOut NS_ENUM_AVAILABLE(10_15, 13_3)	= 15,
	CBErrorTooManyLEPairedDevices NS_ENUM_AVAILABLE(11_0, 14_0) = 16,
};

CB_EXTERN NSString * const CBATTErrorDomain;

typedef NS_ENUM(NSInteger, CBATTError) {
	CBATTErrorSuccess NS_ENUM_AVAILABLE(10_9, 6_0)	= 0x00,
	CBATTErrorInvalidHandle							= 0x01,
	CBATTErrorReadNotPermitted						= 0x02,
	CBATTErrorWriteNotPermitted						= 0x03,
	CBATTErrorInvalidPdu							= 0x04,
	CBATTErrorInsufficientAuthentication			= 0x05,
	CBATTErrorRequestNotSupported					= 0x06,
	CBATTErrorInvalidOffset							= 0x07,
	CBATTErrorInsufficientAuthorization				= 0x08,
	CBATTErrorPrepareQueueFull						= 0x09,
	CBATTErrorAttributeNotFound						= 0x0A,
	CBATTErrorAttributeNotLong						= 0x0B,
	CBATTErrorInsufficientEncryptionKeySize			= 0x0C,
	CBATTErrorInvalidAttributeValueLength			= 0x0D,
	CBATTErrorUnlikelyError							= 0x0E,
	CBATTErrorInsufficientEncryption				= 0x0F,
	CBATTErrorUnsupportedGroupType					= 0x10,
	CBATTErrorInsufficientResources					= 0x11
};

NS_ASSUME_NONNULL_END
