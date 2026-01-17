/*
    Copyright (C) 2024 Apple Inc. All Rights Reserved.
*/

#pragma once

#ifndef ACCESSORY_SETUP_KIT_INDIRECT_INCLUDES
#error "Please #import <AccessorySetupKit/AccessorySetupKit.h> instead of this file directly."
#endif

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class ASDiscoveredAccessory;
@class ASDiscoveryDescriptor;

//---------------------------------------------------------------------------------------------------------------------------
/*!    @brief        Accessory Setup Options
*/
typedef NS_OPTIONS( NSUInteger, ASPickerDisplayItemSetupOptions )
{
    /// An option to ask the person using the app to rename the accessory.
    ASPickerDisplayItemSetupRename                          = ( 1U << 0 ),   // Ask user to rename accessory.
    /// An option to require the app to finish accessory authorization before showing the setup view.
    ///
    /// If the accessory supports ``ASAccessory/SupportOptions/bluetoothPairingLE``, then the app needs to start pairing by accessing a protected GATT characteristic.
    ASPickerDisplayItemSetupConfirmAuthorization            = ( 1U << 1 ),   // App session finishes accessory authorization.
    /// An option to ask the person setting up the accessory to finish additional setup in the app after the accessory is authorized.
    ASPickerDisplayItemSetupFinishInApp                     = ( 1U << 2 ),   // Display instruction to finish setup in app after accessory is authorized to use.
} NS_SWIFT_NAME(ASPickerDisplayItem.SetupOptions);

AS_EXTERN
API_AVAILABLE( ios( 18.0 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos)
NS_SWIFT_SENDABLE
@interface ASPickerDisplayItem : NSObject

/// >Note: The picker ignores `name` and `productImage` if the displayed item matched with an already authorized accessory for another app.

/// The accessory name to display in the picker.
@property (readonly, copy, nonatomic) NSString *name;

/// An image of the accessory to display in the picker.
@property (readonly, copy, nonatomic) UIImage *productImage;

/// A descriptor that the picker uses to determine which discovered accessories to display.
@property (readonly, copy, nonatomic) ASDiscoveryDescriptor *descriptor;

/// Options to allow renaming a matched accessory.
///
/// To permit renaming, include ``SetupOptions-swift.struct/rename`` in the ``setupOptions-c.property``
@property (readwrite, assign, nonatomic) ASAccessoryRenameOptions renameOptions;

/// Custom setup options for the accessory.
@property (readwrite, assign, nonatomic) ASPickerDisplayItemSetupOptions setupOptions;

/// Creates a picker display item with a name and image to display and a descriptor to match discovered accessories.
/// - Parameters:
///   - name: The accessory name to display in the picker.
///   - productImage: An image of the accessory to display in the picker.
///   - descriptor: A descriptor that the picker uses to determine which discovered accessories to display.
- (instancetype)initWithName:(NSString *) name productImage:(UIImage *) productImage
        descriptor:(ASDiscoveryDescriptor *) descriptor NS_DESIGNATED_INITIALIZER;

- (instancetype) init NS_UNAVAILABLE;
- (instancetype) new NS_UNAVAILABLE;

@end

// MARK: -
//===========================================================================================================================

AS_EXTERN
API_AVAILABLE( ios( 18.0 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos)
NS_SWIFT_SENDABLE
@interface ASMigrationDisplayItem : ASPickerDisplayItem

/// The Bluetooth identifier of the accessory to migrate.
@property (readwrite, copy, nullable, nonatomic) NSUUID *peripheralIdentifier;

/// The Wi-Fi hotspot SSID of the accessory to migrate.
@property (readwrite, copy, nullable, nonatomic) NSString *hotspotSSID;

/// The Wi-Fi Aware paired device identififer of the accessory to migrate.
@property (readwrite, assign, nonatomic) ASAccessoryWiFiAwarePairedDeviceID wifiAwarePairedDeviceID
API_AVAILABLE( ios( 26.1 ) );

@end

//===========================================================================================================================

/// A picker display item created from customizing a discovered accessory.
///
/// Use this type when your app's picker uses the ``ASPickerDisplaySettings/Options/filterDiscoveryResults`` option.
/// With this option enabled, your discovery session receives ``ASAccessoryEventType/accessoryDiscovered`` events with discovered accessories.
/// To include a discovered accessory in the picker, create an instance of this class, optionally using the Bluetooth properties of the event's ``ASDiscoveredAccessory`` to provide a more specific name or product image.
/// Then send the `ASDiscoveredDisplayItem` to the picker with the session's ``ASAccessorySession/updatePicker(showing:completionHandler:)`` method.
AS_EXTERN
API_AVAILABLE( ios( 26.1 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos)
NS_SWIFT_SENDABLE
@interface ASDiscoveredDisplayItem : ASPickerDisplayItem

/// Creates a discovered picker display item with a name and image to display and a descriptor to match discovered accessories.
/// - Parameters:
///   - name: The accessory name to display in the picker.
///   - productImage: An image of the accessory to display in the picker.
///   - accessory: App filtered accessory to display in the picker.
- (instancetype)initWithName:(NSString *) name productImage:(UIImage *) productImage accessory:(ASDiscoveredAccessory *) accessory;

- (instancetype)initWithName:(NSString *) name productImage:(UIImage *) productImage
                  descriptor:(ASDiscoveryDescriptor *) descriptor NS_UNAVAILABLE;
@end

NS_ASSUME_NONNULL_END
