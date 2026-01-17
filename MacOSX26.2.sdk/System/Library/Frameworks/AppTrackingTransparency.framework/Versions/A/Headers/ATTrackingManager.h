//
//  ATTrackingManager.h
//  AppTrackingTransparency
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

/// The status values for app tracking authorization.
/// 
/// After a device receives an authorization request to approve access to app-related
/// data that can be used for tracking the user or the device, the returned value is
/// either:
///
/// - ``AppTrackingTransparency/ATTrackingManager/AuthorizationStatus/authorized``, or
/// - ``AppTrackingTransparency/ATTrackingManager/AuthorizationStatus/denied``.
///
/// Before a device receives an authorization request to approve access to app-related
/// data that can be used for tracking the user or the device, the returned value is:
/// ``AppTrackingTransparency/ATTrackingManager/AuthorizationStatus/notDetermined``.
///
/// If authorization to use app tracking data is restricted, the value is: ``AppTrackingTransparency/ATTrackingManager/AuthorizationStatus/restricted``.
typedef NS_ENUM(NSUInteger, ATTrackingManagerAuthorizationStatus) {
    /// The value that returns when the app can’t determine the user’s
    /// authorization status for access to app-related data for tracking the
    /// user or the device.
    ///
    /// - Note: If you call `ATTrackingManager.trackingAuthorizationStatus` in
    /// macOS, the result is always `ATTrackingManager.AuthorizationStatus.notDetermined`.
    ATTrackingManagerAuthorizationStatusNotDetermined = 0,
    /// The value that returns if authorization to access app-related data for
    /// tracking the user or the device has a restricted status.
    ///
    /// A restricted condition means the device does not prompt for tracking
    /// authorization when
    /// ``ATTrackingManager/requestTrackingAuthorizationWithCompletionHandler:``
    /// is called, nor is it displayed when the
    /// <doc://com.apple.documentation/documentation/bundleresources/information_property_list/NSUserTrackingUsageDescription>
    /// is triggered. Also, on restricted devices, the Allow Apps To Request To
    /// Track setting is disabled and cannot be changed. This setting allows
    /// users to opt in or out of allowing apps to request user consent to
    /// access app-related data that can be used for tracking the user or the
    /// device.
    ATTrackingManagerAuthorizationStatusRestricted,
    /// The value that returns if the user denies authorization to access
    /// app-related data for tracking the user or the device.
    ///
    /// The end user has denied the authorization request to access app-related
    /// data that can be used for tracking the user or the device.
    ATTrackingManagerAuthorizationStatusDenied,
    /// The value that returns if the user authorizes access to app-related data for
    /// tracking the user or the device.
    ///
    /// This setting allows users to opt in or out of allowing apps to request user
    /// consent to access app-related data for tracking the user or the device. End
    /// users can revoke permission at any time through the Allow Apps to Request to
    /// Track privacy setting on the device.
    ATTrackingManagerAuthorizationStatusAuthorized
} NS_SWIFT_NAME(ATTrackingManager.AuthorizationStatus) API_AVAILABLE(ios(14), macosx(11.0), tvos(14));

API_AVAILABLE(ios(14), macosx(11.0), tvos(14))
/// A class that provides a tracking authorization request and the tracking
/// authorization status of the app.
@interface ATTrackingManager : NSObject

/// The authorization status that is current for the calling application.
///
/// If the user has not yet been prompted to approve access, the return value
/// will either be ``ATTrackingManagerAuthorizationStatusNotDetermined``, or
/// ``ATTrackingManagerAuthorizationStatusRestricted`` if this value is
/// managed. Once the user has been prompted, the return value will be either
/// ``ATTrackingManagerAuthorizationStatusDenied`` or
/// ``ATTrackingManagerAuthorizationStatusAuthorized``.
///
/// Use the ``ATTrackingManager/trackingAuthorizationStatus`` property to check
/// authorization status.
///
/// - Returns: Information about your application’s tracking authorization
///   status. Users are able to grant or deny developers tracking privileges on
///   a per-app basis. Application developers must call
///   `requestTrackingAuthorizationWithCompletionHandler:` for the ability to
///   track users.
@property (class, nonatomic, readonly, assign) ATTrackingManagerAuthorizationStatus trackingAuthorizationStatus;

/// The request for user authorization to access app-related data.
///
/// The ``ATTrackingManager/requestTrackingAuthorizationWithCompletionHandler:``
/// is a one-time request to authorize or deny access to app-related data that
/// can be used for tracking the user or the device. The system remembers the
/// user’s choice and doesn’t prompt again unless a user uninstalls and then
/// reinstalls the app on the device.
///
/// Calls to the API only prompt when the application state
/// is `UIApplicationStateActive`. The authorization prompt doesn’t display if
/// another permission request is pending user confirmation. Concurrent requests
/// aren’t preserved by iOS, and calls to the API through an app extension don’t
/// prompt. Check the ``ATTrackingManager/trackingAuthorizationStatus`` for a
/// status of
/// ``ATTrackingManagerAuthorizationStatus/ATTrackingManagerAuthorizationStatusNotDetermined``
/// to determine if you need to make an additional call.
///
/// The completion handler will be called with the result of the user's
/// decision for granting or denying permission to use application tracking.
/// The completion handler will be called immediately if access to request
/// authorization is restricted.
///
/// - Important: To use
/// ``ATTrackingManager/requestTrackingAuthorizationWithCompletionHandler:``,
/// the
/// <doc://com.apple.documentation/documentation/bundleresources/information_property_list/NSUserTrackingUsageDescription>
/// key must be in the
/// <doc://com.apple.documentation/documentation/bundleresources/information_property_list>.
+ (void)requestTrackingAuthorizationWithCompletionHandler:(void(^)(ATTrackingManagerAuthorizationStatus status))completion;

// This class, at this time, should not be instantiated.
+ (instancetype)new NS_UNAVAILABLE;

// This class, at this time, should not be instantiated.
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
