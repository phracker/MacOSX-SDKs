/*
	Copyright (C) 2021-2022 Apple Inc. All Rights Reserved.
*/

#ifndef DEVICE_DISCOVERY_EXTENSION_INDIRECT_INCLUDES
#error "Please #import <DeviceAccess/DeviceAccess.h> instead of this file directly."
#endif

#pragma once

#import <DeviceDiscoveryExtension/DeviceDiscoveryExtension.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

/// NSError domain for DeviceAccess errors.
API_AVAILABLE( ios( 16.0 ) )
DD_EXTERN NSString * const DDErrorDomain;

/// Error codes used with DDErrorDomain.
/// DeviceDiscoveryExtension error code range: 350000-350999.
typedef NS_ERROR_ENUM( DDErrorDomain, DDErrorCode )
{
	DDErrorCodeSuccess				= 0,		/// Success.
	DDErrorCodeUnknown				= 350000,	/// Underlying failure with an unknown cause.
	DDErrorCodeBadParameter			= 350001,	/// Bad parameter.
	DDErrorCodeUnsupported			= 350002,	/// Unsupported value, operation, etc.
	DDErrorCodeTimeout				= 350003,	/// Session or operation timed out.
	DDErrorCodeInternal				= 350004,	/// Internal problem.
	DDErrorCodeMissingEntitlement	= 350005,	/// Missing entitlement.
	DDErrorCodePermission			= 350006,	/// Lacks permission to perform the operation.
	
	// Next error code to be allocated
	DDErrorCodeNext,
	
}	API_AVAILABLE( ios( 16.0 ) );

/// Type for returning NSError's from functions. Avoids long and repetitious method signatures.
API_AVAILABLE( ios( 16.0 ) )
typedef NSError * _Nullable __autoreleasing * _Nullable		DDErrorOutType;

/// Invoked when a fail-able operation completes or an error occurs.
/// @param		inError		nil if successful. non-nil if an error occurred.
API_AVAILABLE( ios( 16.0 ) )
typedef void ( ^DDErrorHandler )( NSError * _Nullable inError );

#ifdef __cplusplus
}
#endif

NS_ASSUME_NONNULL_END
