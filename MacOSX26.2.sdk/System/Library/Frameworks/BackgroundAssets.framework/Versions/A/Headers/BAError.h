//
//  BAError.h
//  BackgroundAssets
//
//  Copyright (c) 2022, Apple Inc.
//  All rights reserved.
//

#import <Foundation/Foundation.h>
#import <BackgroundAssets/BackgroundAssets.h>

NS_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

#pragma mark -
#pragma mark BAErrorDomain


/// @brief The error domain used for Background Assets errors.
BA_EXPORT
NSString * const BAErrorDomain
API_AVAILABLE(macos(14.0), ios(17.0), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos);

/// @typedef Background Assets error codes.
/// @constant BAErrorCodeDownloadInvalid Invalid error code.
/// @constant BAErrorCodeCallFromExtensionNotAllowed Calling this method from the download extension is not allowed.
/// @constant BAErrorCodeCallFromInactiveProcessNotAllowed Calling this method from an inactive process is not allowed.
/// @constant BAErrorCodeCallerConnectionNotAccepted This operation cannot be performed because the caller is not accepted based on its application or extension identifier.
/// @constant BAErrorCodeCallerConnectionInvalid This operation cannot be performed because the connection to the background asset system service is invalid.
/// @constant BAErrorCodeDownloadAlreadyScheduled A download with the requested identifier has already been scheduled.
/// @constant BAErrorCodeDownloadNotScheduled The requested download is not scheduled.
/// @constant BAErrorCodeDownloadFailedToStart The requested download failed to start.
/// @constant BAErrorCodeDownloadAlreadyFailed The requested download has failed.
/// @constant BAErrorCodeDownloadEssentialDownloadNotPermitted The requested download could not be enqueued because the download is marked as essential, which is prohibited in this context.
/// @constant BAErrorCodeDownloadBackgroundActivityProhibited The requested download could not be enqueued. Check the device‘s Low Power Mode or Background App Refresh settings.
/// @constant BAErrorCodeDownloadWouldExceedAllowance The requested download cannot be enqueued. The download would exceed the download allowance.
/// @constant BAErrorCodeDownloadDoesNotExist The operation for a download cannot be performed because that BADownload object does not exist.
/// @constant BAErrorCodeSessionDownloadDisallowedByDomain The requested URL is not permitted to be downloaded until the application is launched.
/// @constant BAErrorCodeSessionDownloadDisallowedByAllowance The requested download will not be allowed due to running out of download allowance.
/// @constant BAErrorCodeSessionDownloadAllowanceExceeded The requested download failed because the download allowance has been exceeded.
/// @constant BAErrorCodeSessionDownloadNotPermittedBeforeAppLaunch The requested download cannot be scheduled before the app has been launched.
typedef NS_ENUM(NSInteger, BAErrorCode) {
    BAErrorCodeDownloadInvalid = 0,

    BAErrorCodeCallFromExtensionNotAllowed = 50,
    BAErrorCodeCallFromInactiveProcessNotAllowed = 51,
    BAErrorCodeCallerConnectionNotAccepted = 55,
    BAErrorCodeCallerConnectionInvalid = 56,

    BAErrorCodeDownloadAlreadyScheduled = 100,
    BAErrorCodeDownloadNotScheduled = 101,
    BAErrorCodeDownloadFailedToStart = 102,
    BAErrorCodeDownloadAlreadyFailed = 103,
    BAErrorCodeDownloadEssentialDownloadNotPermitted = 109,
    BAErrorCodeDownloadBackgroundActivityProhibited = 111,
    BAErrorCodeDownloadWouldExceedAllowance = 112,
    BAErrorCodeDownloadDoesNotExist = 113,

    BAErrorCodeSessionDownloadDisallowedByDomain = 202,
    BAErrorCodeSessionDownloadDisallowedByAllowance = 203,
    BAErrorCodeSessionDownloadAllowanceExceeded = 204,
    BAErrorCodeSessionDownloadNotPermittedBeforeAppLaunch = 206,
}
API_AVAILABLE(macos(14.0), ios(17.0), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos);

__END_DECLS

NS_ASSUME_NONNULL_END
