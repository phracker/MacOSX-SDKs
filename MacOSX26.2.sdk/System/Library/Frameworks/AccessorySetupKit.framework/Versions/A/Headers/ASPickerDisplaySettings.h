/*
    Copyright (C) 2025 Apple Inc. All Rights Reserved.
*/

#pragma once

#ifndef ACCESSORY_SETUP_KIT_INDIRECT_INCLUDES
#error "Please #import <AccessorySetupKit/AccessorySetupKit.h> instead of this file directly."
#endif

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

//===========================================================================================================================
/*!    @brief        Picker Options
*/
typedef NS_OPTIONS( NSUInteger, ASPickerDisplaySettingsOptions )
{
    /// An option to pass discovered accessories to the app for more custom filtering, before they're displayed in the picker for selection.
    ///
    /// When your picker uses this option, your ``ASAccessorySession-class`` receives events of type ``ASAccessoryEventType/accessoryDiscovered``.
    /// Handle this event by examining the discovered accessory.
    /// To include it in the picker, create a new ``ASDiscoveredDisplayItem`` for it and call ``ASAccessorySession/updatePicker(showing:completionHandler:)``.
    ASPickerDisplaySettingsOptionFilterDiscoveryResults                          = ( 1U << 0 )
} NS_SWIFT_NAME(ASPickerDisplaySettings.Options);

//---------------------------------------------------------------------------------------------------------------------------

/// The type used for the accessory picker's discovery timeout value.
typedef NSTimeInterval ASPickerDisplaySettingsDiscoveryTimeout NS_TYPED_ENUM NS_SWIFT_NAME(ASPickerDisplaySettings.DiscoveryTimeout) API_AVAILABLE( ios( 26.0 ) );

/// A picker discovery timeout value that times out after about about 60 seconds.
AS_EXTERN ASPickerDisplaySettingsDiscoveryTimeout const ASPickerDisplaySettingsDiscoveryTimeoutShort API_AVAILABLE( ios( 26.0 ) );
/// A picker discovery timeout value that times out after about two minutes.
AS_EXTERN ASPickerDisplaySettingsDiscoveryTimeout const ASPickerDisplaySettingsDiscoveryTimeoutMedium API_AVAILABLE( ios( 26.0 ) );
/// A picker discovery timeout value that times out after about five minutes.
AS_EXTERN ASPickerDisplaySettingsDiscoveryTimeout const ASPickerDisplaySettingsDiscoveryTimeoutLong API_AVAILABLE( ios( 26.0 ) );
/// A picker discovery that only times out when the app tells it to.
///
/// Use this timeout value if you set the picker display option ``ASPickerDisplaySettings/Options/filterDiscoveryResults`` and need unlimited time for filtering.
/// After performing manual discovery, perform the manual timeout by calling the ``ASAccessorySession`` method ``ASAccessorySession/finishPickerDiscovery(completionHandler:)``.
/// This process shows a timeout message if your filtering added no accessories to the picker, or returns silently if you updated the picker.
AS_EXTERN ASPickerDisplaySettingsDiscoveryTimeout const ASPickerDisplaySettingsDiscoveryTimeoutUnbounded API_AVAILABLE( ios( 26.1 ) );

/// A type that contains settings to customize the display of the accessory picker
AS_EXTERN
API_AVAILABLE( ios( 26.0 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos)
NS_SWIFT_SENDABLE
@interface ASPickerDisplaySettings : NSObject

/// An empty settings object.
@property (class, readonly, nonatomic) ASPickerDisplaySettings *defaultSettings;

/// Custom timeout for picker. Default is 30 seconds.
@property (readwrite, assign, nonatomic) ASPickerDisplaySettingsDiscoveryTimeout discoveryTimeout;

/// Custom options for the picker.
@property (readwrite, assign, nonatomic) ASPickerDisplaySettingsOptions options API_AVAILABLE( ios( 26.1 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos);

@end

NS_ASSUME_NONNULL_END
