/*
    Copyright (C) 2024 Apple Inc. All Rights Reserved.
*/

#pragma once

#ifndef ACCESSORY_SETUP_KIT_INDIRECT_INCLUDES
#error "Please #import <AccessorySetupKit/AccessorySetupKit.h> instead of this file directly."
#endif

#import <AccessorySetupKit/ASCommon.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CBUUID;

//---------------------------------------------------------------------------------------------------------------------------
/*!    @brief        Discovery Range
*/
typedef NS_ENUM( NSInteger, ASDiscoveryDescriptorRange )
{
    /// The default range in which to discover accessories.
    ASDiscoveryDescriptorRangeDefault            = 0,
    /// A range in the immediate vicinity of the device performing accessory discovery.
    ///
    /// This range means that an accessory is right next to the device running your app.
    ASDiscoveryDescriptorRangeImmediate          = 10,
} NS_SWIFT_NAME(ASDiscoveryDescriptor.Range);

//---------------------------------------------------------------------------------------------------------------------------
/// A type that defines service roles for Wi-Fi Aware accessories.
typedef NS_ENUM( NSInteger, ASDiscoveryDescriptorWiFiAwareServiceRole )
{
    /// The subscriber service role.
    ASDiscoveryDescriptorWiFiAwareServiceRoleSubscriber       = 10,
    /// The publisher service role.
    ASDiscoveryDescriptorWiFiAwareServiceRolePublisher        = 20,
} NS_SWIFT_NAME(ASDiscoveryDescriptor.WiFiAwareServiceRole);

AS_EXTERN
API_AVAILABLE( ios( 18.0 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos)
NS_SWIFT_SENDABLE
@interface ASDiscoveryDescriptor : NSObject

/// Options supported by an accessory.
@property (readwrite, assign, nonatomic) ASAccessorySupportOptions supportedOptions;

/// The accessory's 16-bit Bluetooth Company Identifier.
@property (readwrite, assign, nonatomic) ASBluetoothCompanyIdentifier bluetoothCompanyIdentifier;

/// A byte buffer that matches the accessory's Bluetooth manufacturer data.
@property (readwrite, copy, nullable, nonatomic) NSData *bluetoothManufacturerDataBlob;

/// The accessory's Bluetooth manufacturer data mask.
@property (readwrite, copy, nullable, nonatomic) NSData *bluetoothManufacturerDataMask;

/// The accessory's over-the-air Bluetooth name substring compare options.
@property (readwrite, assign, nonatomic) NSStringCompareOptions bluetoothNameSubstringCompareOptions
API_AVAILABLE( ios( 18.2 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos);

/// The accessory's over-the-air Bluetooth name substring.
@property (readwrite, copy, nullable, nonatomic) NSString *bluetoothNameSubstring;

/// A property that tells the session to discover accessories within a specific Bluetooth range.
@property (readwrite, assign, nonatomic) ASDiscoveryDescriptorRange bluetoothRange;

/// A byte buffer that matches the accessory's Bluetooth service data.
@property (readwrite, copy, nullable, nonatomic) NSData *bluetoothServiceDataBlob;

/// The accessory's Bluetooth service data mask.
@property (readwrite, copy, nullable, nonatomic) NSData *bluetoothServiceDataMask;

/// The accessory's Bluetooth service UUID.
@property (readwrite, copy, nullable, nonatomic) CBUUID *bluetoothServiceUUID;

/// The SSID of the accessory's Wi-Fi network.
@property (readwrite, copy, nullable, nonatomic) NSString *SSID;

/// The prefix string of SSID of the accessory's Wi-Fi network.
@property (readwrite, copy, nullable, nonatomic) NSString *SSIDPrefix;

/// The accessory's Wi-Fi Aware's service name if available.
@property (readwrite, copy, nullable, nonatomic) NSString *wifiAwareServiceName
API_AVAILABLE( ios( 26.0 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos);

/// The role of the accessory's Wi-Fi Aware's service.
///
/// This property defaults to ``ASDiscoveryDescriptor/WiFiAwareServiceRole/subscriber``
@property (readwrite, assign, nonatomic) ASDiscoveryDescriptorWiFiAwareServiceRole wifiAwareServiceRole
API_AVAILABLE( ios( 26.0 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos);

/// The accessory's Wi-Fi Aware model name and matching options.
@property (readwrite, copy, nullable, nonatomic) ASPropertyCompareString *wifiAwareModelNameMatch
API_AVAILABLE( ios( 26.0 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos);

/// The accessory's Wi-Fi Aware vendor name and matching options.
@property (readwrite, copy, nullable, nonatomic) ASPropertyCompareString *wifiAwareVendorNameMatch
API_AVAILABLE( ios( 26.0 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos);

@end

NS_ASSUME_NONNULL_END
