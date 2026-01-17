// Copyright (C) 2021-2022 Apple Inc. All Rights Reserved.

#ifndef DEVICE_DISCOVERY_EXTENSION_INDIRECT_INCLUDES
#error "Please #import <DeviceDiscoveryExtension/DeviceDiscoveryExtension.h> instead of this file directly."
#endif

#pragma once

#import <DeviceDiscoveryExtension/DDCommon.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

@class DDDevice;
@class DDDeviceEvent;

//===========================================================================================================================
/// Type of event.
typedef NS_ENUM( NSInteger, DDEventType )
{
	DDEventTypeUnknown NS_SWIFT_NAME(unknown)								= 0,	/// Unknown event. Placeholder for initializing event types.
	DDEventTypeDeviceFound NS_SWIFT_NAME(deviceFound)						= 40,	/// [DDDeviceEvent] Device found.
	DDEventTypeDeviceLost NS_SWIFT_NAME(deviceLost)							= 41,	/// [DDDeviceEvent] Device lost.
	DDEventTypeDeviceChanged NS_SWIFT_NAME(deviceChanged)					= 42,	/// [DDDeviceEvent] Device changed.
} NS_SWIFT_NAME(DDDeviceEvent.EventType);

/// Converts an event to a string for logging, etc.
DD_EXTERN
API_AVAILABLE( ios( 16.0 ) )
NSString * DDEventTypeToString( DDEventType inValue );

/// Invoked when an event occurs.
typedef void ( ^DDEventHandler )( DDDeviceEvent *inEvent );

//===========================================================================================================================

/// Device-related event (e.g. found, lost).
DD_EXTERN
API_AVAILABLE( ios( 16.0 ) )
@interface DDDeviceEvent : NSObject

/// Initializes a device event.
- (instancetype) initWithEventType:(DDEventType) type device:(DDDevice *) device;

/// Device found or lost.
@property (readonly, strong, nonatomic) DDDevice *device;

/// Type of event.
@property (readonly, assign, nonatomic) DDEventType eventType;

@end

#ifdef __cplusplus
}
#endif

NS_ASSUME_NONNULL_END
