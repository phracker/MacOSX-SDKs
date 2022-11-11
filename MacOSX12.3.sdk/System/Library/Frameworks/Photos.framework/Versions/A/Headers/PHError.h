//
//  PHError.h
//  Photos
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

API_AVAILABLE_BEGIN(macos(10.15), ios(13), tvos(13))

OS_EXPORT NSErrorDomain const PHPhotosErrorDomain;

/// Array of NSString values representing local identifiers related to the specific error
extern NSErrorUserInfoKey const PHLocalIdentifiersErrorKey API_AVAILABLE(macos(12), ios(15), tvos(15));

typedef NS_ERROR_ENUM(PHPhotosErrorDomain, PHPhotosError) {
    PHPhotosErrorInternalError API_AVAILABLE(macos(10.15), ios(13), tvos(13)) = -1, // An unknown, internal error occured

    PHPhotosErrorUserCancelled = 3072, // The user cancelled the asset resource or editing request
    PHPhotosErrorLibraryVolumeOffline = 3114, // The photo library is unavailable because the file system volume that contains it is not mounted (register for PHPhotoLibraryAvailabilityObserver)
    PHPhotosErrorRelinquishingLibraryBundleToWriter = 3142, // The photo library became unavailable because the user moved, renamed, or deleted the system photo library (register for PHPhotoLibraryAvailabilityObserver)
    PHPhotosErrorSwitchingSystemPhotoLibrary = 3143, // The photo library became unavailable because the user switched the system photo library (register for PHPhotoLibraryAvailabilityObserver)
    PHPhotosErrorNetworkAccessRequired API_AVAILABLE(macos(11.0), ios(14), tvos(14)) = 3164, // The request for an asset resource failed because network access is required, set networkAccessAllowed = YES to enable network access
    PHPhotosErrorIdentifierNotFound API_AVAILABLE(macos(12), ios(15), tvos(15)) = 3201, // Identifier was not found
    PHPhotosErrorMultipleIdentifiersFound API_AVAILABLE(macos(12), ios(15), tvos(15)) = 3202, // More than one identifier was found

    PHPhotosErrorChangeNotSupported API_AVAILABLE(macos(12), ios(15), tvos(15)) = 3300, // The change request is not supported as configured
    PHPhotosErrorOperationInterrupted API_AVAILABLE(macos(12), ios(15), tvos(15)) = 3301, // Operation was interrupted and could not be completed, transient error
    PHPhotosErrorInvalidResource API_AVAILABLE(macos(12), ios(15), tvos(15)) = 3302, // Asset resource validation failed
    PHPhotosErrorMissingResource API_AVAILABLE(macos(12), ios(15), tvos(15)) = 3303, // Asset resource missing
    PHPhotosErrorNotEnoughSpace API_AVAILABLE(macos(12), ios(15), tvos(15)) = 3305, // Not enough space to perform the requested change
    PHPhotosErrorRequestNotSupportedForAsset API_AVAILABLE(macos(12), ios(15), tvos(15)) = 3306, // The request could not be completed because it is not supported for the specified asset
    
    PHPhotosErrorAccessRestricted API_AVAILABLE(macos(12), ios(15), tvos(15)) = 3310, // Access restricted by system configuration
    PHPhotosErrorAccessUserDenied API_AVAILABLE(macos(12), ios(15), tvos(15)) = 3311, // The user has denied access

    PHPhotosErrorLibraryInFileProviderSyncRoot API_AVAILABLE(macos(12.3), ios(15.4), tvos(15.4)) = 5423, // The Photos library bundle is in a File Provider Sync Root directory, which is not supported because it can corrupt the photo library

    PHPhotosErrorInvalid API_DEPRECATED_WITH_REPLACEMENT("PHPhotosErrorInternalError", macos(10.15, 12), ios(13, 15), tvos(13, 15)) = -1, // DEPRECATED An unknown error occured
};

#ifdef __swift__
static const NSInteger PHPhotosErrorInvalidDeprecated NS_SWIFT_NAME(PHPhotosErrorInvalid) API_DEPRECATED_WITH_REPLACEMENT("PHPhotosErrorInvalid", macos(10.15, 11.0), ios(13, 14), tvos(13, 14)) = PHPhotosErrorInvalid;
static const NSInteger PHPhotosErrorUserCancelledDeprecated NS_SWIFT_NAME(PHPhotosErrorUserCancelled) API_DEPRECATED_WITH_REPLACEMENT("PHPhotosErrorUserCancelled", macos(10.15, 11.0), ios(13, 14), tvos(13, 14)) = PHPhotosErrorUserCancelled;
static const NSInteger PHPhotosErrorLibraryVolumeOfflineDeprecated NS_SWIFT_NAME(PHPhotosErrorLibraryVolumeOffline) API_DEPRECATED_WITH_REPLACEMENT("PHPhotosErrorLibraryVolumeOffline", macos(10.15, 11.0), ios(13, 14), tvos(13, 14)) = PHPhotosErrorLibraryVolumeOffline;
static const NSInteger PHPhotosErrorRelinquishingLibraryBundleToWriterDeprecated NS_SWIFT_NAME(PHPhotosErrorRelinquishingLibraryBundleToWriter) API_DEPRECATED_WITH_REPLACEMENT("PHPhotosErrorRelinquishingLibraryBundleToWriter", macos(10.15, 11.0), ios(13, 14), tvos(13, 14)) = PHPhotosErrorRelinquishingLibraryBundleToWriter;
static const NSInteger PHPhotosErrorSwitchingSystemPhotoLibraryDeprecated NS_SWIFT_NAME(PHPhotosErrorSwitchingSystemPhotoLibrary) API_DEPRECATED_WITH_REPLACEMENT("PHPhotosErrorSwitchingSystemPhotoLibrary", macos(10.15, 11.0), ios(13, 14), tvos(13, 14)) = PHPhotosErrorSwitchingSystemPhotoLibrary;
#endif

API_AVAILABLE_END
