// Copyright © 2020 Apple Inc. All rights reserved.

#import <AppClip/APBase.h>
#import <Foundation/Foundation.h>

@class CLRegion;

NS_ASSUME_NONNULL_BEGIN

AP_EXTERN API_AVAILABLE(ios(14.0))
/// A string that identifies the activation payload’s error domain.
NSErrorDomain const APActivationPayloadErrorDomain;

/// Error codes that an App Clip activation payload returns.
typedef NS_ERROR_ENUM(APActivationPayloadErrorDomain, APActivationPayloadErrorCode) {
    /// The user denied location access, or the source of the App Clip
    /// invocation wasn’t from an NFC tag or visual code.
    APActivationPayloadErrorCodeDisallowed = 1,
    /// The provided URL doesn’t match the registered App Clip URL.
    APActivationPayloadErrorCodeDoesNotMatch = 2,
} API_AVAILABLE(ios(14.0));

AP_EXTERN API_AVAILABLE(ios(14.0))
/// Information that’s passed to an App Clip on launch.
///
/// When users launch an App Clip, the platform passes an activation payload to
/// the App Clip as part of an
/// <doc://com.apple.documentation/documentation/foundation/nsuseractivity>
/// object. When the App Clip receives the payload, confirm the user’s physical
/// location at the time of the invocation.
///
/// For more information, see <doc:responding-to-invocations>.
@interface APActivationPayload : NSObject <NSSecureCoding, NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// The URL of the link that launched the App Clip.
///
/// Use `url` to retrieve data that’s passed to an App Clip on launch, and use
/// the data to update the user interface of the App Clip.
///
/// The value of `url` is the same as the
/// <doc://com.apple.documentation/documentation/foundation/nsuseractivity>
/// <doc://com.apple.documentation/documentation/foundation/nsuseractivity/1418086-webpageurl>
/// property. If you don’t need to verify the user’s location when they launch
/// your App Clip, use `webpageURL` instead.
///
/// For more information, see <doc:responding-to-invocations>.
@property (nonatomic, strong, readonly, nullable) NSURL *URL;

/// Checks whether an App Clip invocation happened at an expected physical
/// location.
///
///- Parameters:
///   - region: The expected physical location at the time of the App Clip
/// invocation.
///   - completionHandler: A closure called when the platform confirms the
/// expected physical location at the time of the App Clip invocation.
///
///     The closure takes the following parameters:
///
///     - term `inRegion`: A Boolean value that indicates whether the App Clip
///     invocation happened at the expected physical location.
///     - term `error`: The error object that describes why the platform
///     couldn't confirm the user's physical location.
///
/// This parameter is `nil` if the platform was able to determine the user's
/// physical location at the time of the App Clip invocation.
///
/// Confirm the user's location at the time of the App Clip invocation if the
/// App Clip is associated with a physical location. The request to confirm the
/// location fails with ``App_clips/Apactivationpayloaderror/disallowed`` if the
/// source of the invocation isn't an NFC tag or visual code.
///
/// For the platform to accept the request to confirm the user's location, you
/// need to make modifications to the `Info.plist` file of the App Clip. For
/// more information, see <doc:enabling-notifications-in-app-clips>.
///
/// - Note: Functionality to confirm the user's location is only available to
/// App Clips. For the full app, request permission to access the user's
/// location and make use of the
/// <doc://com.apple.documentation/documentation/corelocation> framework. For
/// more information, see
/// <doc://com.apple.documentation/documentation/corelocation/getting_the_current_location_of_a_device>.
- (void)confirmAcquiredInRegion:(CLRegion *)region completionHandler:(void (^)(BOOL inRegion, NSError *_Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
