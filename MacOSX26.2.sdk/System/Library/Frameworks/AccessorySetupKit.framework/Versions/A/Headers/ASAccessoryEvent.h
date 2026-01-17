/*
    Copyright (C) 2024 Apple Inc. All Rights Reserved.
*/

#ifndef ACCESSORY_SETUP_KIT_INDIRECT_INCLUDES
#error "Please #import <AccessorySetupKit/AccessorySetupKit.h> instead of this file directly."
#endif

#pragma once

#import <AccessorySetupKit/ASCommon.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

@class ASAccessory;

//===========================================================================================================================
/// Type of event.
typedef NS_ENUM( NSInteger, ASAccessoryEventType )
{
    /// An unknown event occurred.
    ///
    /// This is a placeholder value used when initializing event type instances.
    ASAccessoryEventTypeUnknown                     = 0,    // Unknown event. Placeholder for initializing event types.
    /// The discovery session activated.
    ASAccessoryEventTypeActivated                   = 10,   // [ASAccessoryEvent] Instance activate completed.
    /// The discovery session invalidated.
    ASAccessoryEventTypeInvalidated                 = 11,   // [ASAccessoryEvent] Instance invalidated.
    /// The migration of an accessory completed.
    ASAccessoryEventTypeMigrationComplete           = 20,   // [ASAccessoryEvent] Accessories migration complete.
    /// The session added an accessory.
    ASAccessoryEventTypeAccessoryAdded              = 30,   // [ASAccessoryEvent] Accessory added.
    /// The session removed an accessory.
    ASAccessoryEventTypeAccessoryRemoved            = 31,   // [ASAccessoryEvent] Accessory removed from system.
    /// The properties of an accessory changed.
    ASAccessoryEventTypeAccessoryChanged            = 32,   // [ASAccessoryEvent] Accessory properties changed.
    /// The session discovered an accessory.
    ///
    /// Your app only receives this event if your picker uses the ``ASPickerDisplaySettings/Options/filterDiscoveryResults`` option.
    ASAccessoryEventTypeAccessoryDiscovered         = 33,   // [ASAccessoryEvent] Accessory discovered.
    /// The discovery session picker appeared.
    ASAccessoryEventTypePickerDidPresent            = 40,   // [ASAccessoryEvent] Picker did present.
    /// The discovery session picker dismissed.
    ASAccessoryEventTypePickerDidDismiss            = 50,   // [ASAccessoryEvent] Picker did dismiss.
    /// The discovery session picker started bridging with an accessory.
    ASAccessoryEventTypePickerSetupBridging         = 60,   // [ASAccessoryEvent] Picker started bridging with accessory.
    /// The discovery session picker setup failed.
    ASAccessoryEventTypePickerSetupFailed           = 70,   // [ASAccessoryEvent] Picker failed setup for accessory.
    /// The discovery session picker started pairing with a Bluetooth accessory.
    ASAccessoryEventTypePickerSetupPairing          = 80,   // [ASAccessoryEvent] Picker started pairing with accessory.
    /// The discovery session picker started renaming an accessory.
    ASAccessoryEventTypePickerSetupRename           = 90,   // [ASAccessoryEvent] Picker started rename of accessory.
};

//===========================================================================================================================
/// Event for status and other updates.
AS_EXTERN
API_AVAILABLE( ios( 18.0 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos)
NS_SWIFT_SENDABLE
@interface ASAccessoryEvent : NSObject

/// The type of event, such as accessory addition or removal, or picker presentation or removal.
///
/// Some event types may indicate that the event is a subclass of ``ASAccessoryEvent-c.class`` that provides additional properties.
@property (readonly, assign, nonatomic) ASAccessoryEventType eventType;

/// The accessory involved in the event, if any.
///
/// The session populates this member for event types like ``ASAccessoryEventType/accessoryAdded`` and ``ASAccessoryEventType/accessoryChanged``, but not for life cycle or picker events like ``ASAccessoryEventType/activated`` or ``ASAccessoryEventType/pickerDidPresent``.
@property (readonly, copy, nullable, nonatomic) ASAccessory *accessory;

/// The error associated with the event, if any.
@property (readonly, copy, nullable, nonatomic) NSError *error;

- (instancetype) init NS_UNAVAILABLE;
- (instancetype) new NS_UNAVAILABLE;

@end

#ifdef __cplusplus
}
#endif

NS_ASSUME_NONNULL_END
