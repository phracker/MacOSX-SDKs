/*
 *	CBError.h
 *	CoreBluetooth
 *
 *	Copyright 2011 Apple, Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>



extern NSString * const CBErrorDomain;
enum {
	CBErrorUnknown,
};
typedef NSInteger CBError;

extern NSString * const CBATTErrorDomain;
enum {
	CBATTErrorInvalidHandle					= 0x01,
	CBATTErrorReadNotPermitted				= 0x02,
	CBATTErrorWriteNotPermitted				= 0x03,
	CBATTErrorInvalidPdu					= 0x04,
	CBATTErrorInsufficientAuthentication	= 0x05,
	CBATTErrorRequestNotSupported			= 0x06,
	CBATTErrorInvalidOffset					= 0x07,
	CBATTErrorInsufficientAuthorization		= 0x08,
	CBATTErrorPrepareQueueFull				= 0x09,
	CBATTErrorAttributeNotFound				= 0x0A,
	CBATTErrorAttributeNotLong				= 0x0B,
	CBATTErrorInsufficientEncryptionKeySize	= 0x0C,
	CBATTErrorInvalidAttributeValueLength	= 0x0D,
	CBATTErrorUnlikelyError					= 0x0E,
	CBATTErrorInsufficientEncryption		= 0x0F,
	CBATTErrorUnsupportedGroupType			= 0x10,
	CBATTErrorInsufficientResources			= 0x11,
};
typedef NSInteger CBATTError;