/*
    Copyright (C) 2024 Apple Inc. All Rights Reserved.
*/

#pragma once

#ifndef ACCESSORY_SETUP_KIT_INDIRECT_INCLUDES
#error "Please #import <AccessorySetupKit/AccessorySetupKit.h> instead of this file directly."
#endif

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// NSError domain for AccessorySetupKit errors.
AS_EXTERN NSErrorDomain const ASErrorDomain;

/// Error codes used with ASErrorDomain.
typedef NS_ERROR_ENUM( ASErrorDomain, ASErrorCode )
{
    /// A code that represents a successful action.
    ASErrorCodeSuccess                      = 0,        // Success.
    /// An underlying failure with an unknown cause.
    ASErrorCodeUnknown                      = 1,        // Underlying failure with an unknown cause.
    /// Session activation failed.
    ASErrorCodeActivationFailed             = 100,      // Unable to activate discovery session.
    /// The session was unable to establish a connection.
    ASErrorCodeConnectionFailed             = 150,      // Unable to establish connection with accessory.
    /// Accessory discovery timed out.
    ASErrorCodeDiscoveryTimeout             = 200,      // Discovery timed out.
    /// The framework couldn't find the app extension.
    ASErrorCodeExtensionNotFound            = 300,      // Unable to find App Extension.
    /// The session invalidated prior to completing the operation.
    ASErrorCodeInvalidated                  = 400,      // Invalidate was called before the operation completed normally.
    /// The session received an invalid request.
    ASErrorCodeInvalidRequest               = 450,      // Invalid request.
    /// The picker received a show request when it was already active.
    ASErrorCodePickerAlreadyActive          = 500,      // Picker already active.
    /// The picker can't be used because the app is in the background.
    ASErrorCodePickerRestricted             = 550,      // Picker restricted due to application in background.
    /// The person using the app canceled the operation.
    ASErrorCodeUserCancelled                = 700,      // User cancelled.
    /// The person using the app restricted access.
    ASErrorCodeUserRestricted               = 750,      // Access restricted by user.
}   API_AVAILABLE( ios( 18.0 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos);

NS_ASSUME_NONNULL_END
