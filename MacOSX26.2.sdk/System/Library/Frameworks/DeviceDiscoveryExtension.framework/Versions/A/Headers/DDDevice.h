// Copyright (C) 2021-2024 Apple Inc. All Rights Reserved.

#ifndef DEVICE_DISCOVERY_EXTENSION_INDIRECT_INCLUDES
#error "Please #import <DeviceDiscoveryExtension/DeviceDiscoveryExtension.h> instead of this file directly."
#endif

#pragma once

#import <DeviceDiscoveryExtension/DDCommon.h>
#import <Foundation/Foundation.h>
#import <Network/Network.h>
#import <UniformTypeIdentifiers/UniformTypeIdentifiers.h>

NS_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------------------------------------------------------
///	@defgroup	Supported Protocols
typedef NSString * DDDeviceProtocolString NS_STRING_ENUM;

API_AVAILABLE( ios( 16.0 ) )
DD_EXTERN DDDeviceProtocolString const DDDeviceProtocolStringInvalid;

API_AVAILABLE( ios( 16.0 ) )
DD_EXTERN DDDeviceProtocolString const DDDeviceProtocolStringDIAL NS_SWIFT_NAME(DDDeviceProtocolString.dial);

//---------------------------------------------------------------------------------------------------------------------------

typedef NS_ENUM( NSInteger, DDDeviceProtocol )
 {
	DDDeviceProtocolInvalid NS_SWIFT_NAME(invalid)					= 0,	/// Invalid protocol.
	DDDeviceProtocolDIAL NS_SWIFT_NAME(dial)						= 1,	/// DIAL protocol.
 } NS_SWIFT_NAME(DDDevice.Protocol);

/// Converts a device protocol type to a string for logging, etc.
DD_EXTERN
API_AVAILABLE( ios( 16.0 ) )
NSString * DDDeviceProtocolToString( DDDeviceProtocol inValue );

//---------------------------------------------------------------------------------------------------------------------------
/// Category of the device.
typedef NS_ENUM( NSInteger, DDDeviceCategory )
{
	DDDeviceCategoryHiFiSpeaker NS_SWIFT_NAME(hifiSpeaker)					= 0,	/// Hi-Fi speaker.
	DDDeviceCategoryHiFiSpeakerMultiple NS_SWIFT_NAME(hifiSpeakerMultiple)	= 1,	/// Multiple Hi-Fi speakers.
	DDDeviceCategoryTVWithMediaBox NS_SWIFT_NAME(tvWithMediaBox)			= 2,	/// TV with MediaBox.
	DDDeviceCategoryTV NS_SWIFT_NAME(tv)									= 3,	/// TV.
	DDDeviceCategoryLaptopComputer NS_SWIFT_NAME(laptopComputer)			= 4,	/// Laptop computer.
	DDDeviceCategoryDesktopComputer NS_SWIFT_NAME(desktopComputer)			= 5,	/// Desktop computer.
	DDDeviceCategoryAccessorySetup NS_SWIFT_NAME(accessorySetup)			= 6,	/// AccessorySetupKit.
} NS_SWIFT_NAME(DDDevice.Category);

/// Converts a device category to a string for logging, etc.
DD_EXTERN
API_AVAILABLE( ios( 16.0 ) )
NSString * DDDeviceCategoryToString( DDDeviceCategory inValue );

//===========================================================================================================================
/// State of the device.
typedef NS_ENUM( NSInteger, DDDeviceState )
{
	DDDeviceStateInvalid		= 0,  /// Invalid/unapproved state.
	DDDeviceStateActivating		= 10, /// Selected by the user.
	DDDeviceStateActivated		= 20, /// Authorized and connected.
	DDDeviceStateAuthorized		= 25, /// Authorized by the user.
	DDDeviceStateInvalidating	= 30, /// Invalidating state.
};

/// Converts a device state to a string for logging, etc.
DD_EXTERN
API_AVAILABLE( ios( 16.0 ) )
NSString * DDDeviceStateToString( DDDeviceState inValue );

//===========================================================================================================================
/// State of media playback on the device.
typedef NS_ENUM( NSInteger, DDDeviceMediaPlaybackState )
{
	DDDeviceMediaPlaybackStateNoContent		= 0, /// Not playing any media content.
	DDDeviceMediaPlaybackStatePaused		= 1, /// Media content playback is paused.
	DDDeviceMediaPlaybackStatePlaying		= 2, /// Media content is playing.
} NS_SWIFT_NAME(DDDevice.MediaPlaybackState);

//===========================================================================================================================
/*!    @brief		Device Support
*/
typedef NS_OPTIONS( NSUInteger, DDDeviceSupports )
{
	DDDeviceSupportsBluetoothPairingLE								= ( 1U << 1 ),	/// Device supports Bluetooth Low Energy pairing.
	DDDeviceSupportsBluetoothTransportBridging						= ( 1U << 2 ),	/// Device supports bring up of classic transport profiles when low energy transport for peripheral is connected.
	DDDeviceSupportsBluetoothHID API_AVAILABLE( ios( 26.0 ) )		= ( 1U << 3 ),  /// Device supports Bluetooth Low Energy HID service.
};

//===========================================================================================================================
/*!    @brief        Wi-Fi Aware Service's Role
*/
typedef NS_ENUM( NSInteger, DDDeviceWiFiAwareServiceRole )
{
	DDDeviceWiFiAwareServiceRoleSubscriber			= 10,
	DDDeviceWiFiAwareServiceRolePublisher			= 20,
} NS_SWIFT_NAME(DDDevice.WiFiAwareServiceRole);

/// Converts a device media playback state to a string for logging, etc.
DD_EXTERN
API_AVAILABLE( ios( 16.0 ) )
NSString * DDDeviceMediaPlaybackStateToString( DDDeviceMediaPlaybackState inValue );

//===========================================================================================================================
/// DeviceDiscoveryExtension device.
DD_EXTERN
API_AVAILABLE( ios( 16.0 ) )
@interface DDDevice : NSObject

- (instancetype) init NS_UNAVAILABLE;

/// Initializes a DD device with display name, category, protocol type, and identifier.
- (instancetype) initWithDisplayName:(NSString *) displayName category:(DDDeviceCategory) category
	protocolType:(UTType *) protocolType identifier:(NSString *) identifier NS_DESIGNATED_INITIALIZER;

/// Device supported capabilities.
@property (readwrite, assign, nonatomic) DDDeviceSupports deviceSupports
	API_AVAILABLE( ios( 18.0 ) );

/// Identifier to communicate with the device via Bluetooth.
@property (readwrite, strong, nullable, nonatomic) NSUUID *bluetoothIdentifier;

/// Category of the device.
@property (readwrite, assign, nonatomic) DDDeviceCategory category;

/// Device's custom asset for product image name in the main App bundle.
@property (readwrite, copy, nullable, nonatomic) NSString *displayImageName
	API_AVAILABLE( ios( 18.0 ) );

/// Name of the device. Should be suitable for displaying to a user.
@property (readwrite, copy, nonatomic) NSString *displayName;

/// Identifier of the device.
@property (readwrite, copy, nonatomic) NSString *identifier;

/// Current state of media playback on this device.
@property (readwrite, assign, nonatomic) DDDeviceMediaPlaybackState mediaPlaybackState;

/// Title of the media content being played.
@property (readwrite, copy, nullable, nonatomic) NSString *mediaContentTitle;

/// Subtitle of the media content being played. It can be used to display extra information about the content, such as the name of the artist.
@property (readwrite, copy, nullable, nonatomic) NSString *mediaContentSubtitle;

/// Endpoint to communicate with the device via networking.
@property (readwrite, dd_os_ownership, nullable, nonatomic) nw_endpoint_t networkEndpoint
	NS_REFINED_FOR_SWIFT;

/// Protocol of the device.
@property (readwrite, assign, nonatomic) DDDeviceProtocol protocol;

/// Uniform Type for the protocol.
@property (readwrite, strong, nonatomic) UTType *protocolType;

/// State of the device.
@property (readwrite, assign, nonatomic) DDDeviceState state;

/// Device's WiFi Hotspot SSID.
@property (readwrite, copy, nullable, nonatomic) NSString *SSID
	API_AVAILABLE( ios( 18.0 ) );

/// Whether the device supports grouping with other devices with the same protocol.
@property (readwrite, assign, nonatomic) BOOL supportsGrouping
	API_AVAILABLE( ios( 17.0 ) );

/// TXT record of the device.
@property (readwrite, copy, nullable, nonatomic) NSData *txtRecordData
	NS_REFINED_FOR_SWIFT;

/// URL used for SSDP connection.
/// The URL must have a valid hostname, no query parameters, and a maximum size of 100 bytes.
@property (readwrite, copy, nonatomic) NSURL *url;

/// Device's Wi-Fi Aware's service name.
@property (readwrite, copy, nullable, nonatomic) NSString *wifiAwareServiceName
API_AVAILABLE( ios( 26.0 ) );

/// Device's Wi-Fi Aware's service. Default is `DDDeviceWiFiAwareServiceRoleSubscriber`
@property (readwrite, assign, nonatomic) DDDeviceWiFiAwareServiceRole wifiAwareServiceRole
API_AVAILABLE( ios( 26.0 ) );

/// Device's Wi-Fi Aware model name.
@property (readwrite, copy, nullable, nonatomic) NSString *wifiAwareModelName
API_AVAILABLE( ios( 26.0 ) );

/// Device's Wi-Fi Aware vendor name.
@property (readwrite, copy, nullable, nonatomic) NSString *wifiAwareVendorName
API_AVAILABLE( ios( 26.0 ) );

@end

#ifdef __cplusplus
}
#endif

NS_ASSUME_NONNULL_END
