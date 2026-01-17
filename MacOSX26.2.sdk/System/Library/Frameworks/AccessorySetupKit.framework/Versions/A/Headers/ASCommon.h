/*
    Copyright (C) 2024 Apple Inc. All Rights Reserved.
*/

#ifndef ACCESSORY_SETUP_KIT_INDIRECT_INCLUDES
#error "Please #import <AccessorySetupKit/AccessorySetupKit.h> instead of this file directly."
#endif

#pragma once

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

/// Marks an API as exported.
#ifndef AS_EXTERN
#ifdef __cplusplus
#define AS_EXTERN extern "C" __attribute__((visibility("default")))
#else
#define AS_EXTERN extern __attribute__((visibility("default")))
#endif
#endif

/// Work around some projects disabling OS_OBJECT_USE_OBJC by mapping to strong/assign as needed.
#if defined( OS_OBJECT_USE_OBJC ) && OS_OBJECT_USE_OBJC
    #define as_os_ownership        strong
#else
    #define as_os_ownership        assign
#endif

// MARK: == Constants and Types ==

/// The type used to identify a Bluetooth accessory provider.
typedef uint16_t ASBluetoothCompanyIdentifier NS_TYPED_EXTENSIBLE_ENUM;

// MARK: - Interfaces
//===========================================================================================================================

/// A type that specifies how to filter a property against a given string and comparison options.
AS_EXTERN
API_AVAILABLE( ios( 26.0 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos)
NS_SWIFT_SENDABLE
@interface ASPropertyCompareString : NSObject

/// The string to compare against.
@property (readonly, copy, nonatomic) NSString *string;

/// Comparison options to apply when comparing strings.
@property (readonly, assign, nonatomic) NSStringCompareOptions compareOptions;

/// Creates a property compare string instance with the given string and comparison options.
/// - Parameters:
///   - string: The string to compare against.
///   - compareOptions: Options to apply when comparing strings.
- (instancetype)initWithString:(NSString *) string compareOptions:(NSStringCompareOptions) compareOptions
    NS_DESIGNATED_INITIALIZER;

- (instancetype) init NS_UNAVAILABLE;
- (instancetype) new NS_UNAVAILABLE;

@end

#ifdef __cplusplus
}
#endif

NS_ASSUME_NONNULL_END
