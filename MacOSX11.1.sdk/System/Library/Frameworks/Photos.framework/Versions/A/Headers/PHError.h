//
//  PHError.h
//  Photos
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

API_AVAILABLE_BEGIN(macos(10.15), ios(13), tvos(13))

OS_EXPORT NSErrorDomain const PHPhotosErrorDomain;

typedef NS_ERROR_ENUM(PHPhotosErrorDomain, PHPhotosError) {
    PHPhotosErrorInvalid = -1,
    PHPhotosErrorUserCancelled = 3072,
    PHPhotosErrorLibraryVolumeOffline = 3114,
    PHPhotosErrorRelinquishingLibraryBundleToWriter = 3142,
    PHPhotosErrorSwitchingSystemPhotoLibrary = 3143,
    PHPhotosErrorNetworkAccessRequired API_AVAILABLE(macos(11.0), ios(14), tvos(14)) = 3164,
};

#ifdef __swift__
static const NSInteger PHPhotosErrorInvalidDeprecated NS_SWIFT_NAME(PHPhotosErrorInvalid) API_DEPRECATED_WITH_REPLACEMENT("PHPhotosErrorInvalid", macos(10.15, 11.0), ios(13, 14), tvos(13, 14)) = PHPhotosErrorInvalid;
static const NSInteger PHPhotosErrorUserCancelledDeprecated NS_SWIFT_NAME(PHPhotosErrorUserCancelled) API_DEPRECATED_WITH_REPLACEMENT("PHPhotosErrorUserCancelled", macos(10.15, 11.0), ios(13, 14), tvos(13, 14)) = PHPhotosErrorUserCancelled;
static const NSInteger PHPhotosErrorLibraryVolumeOfflineDeprecated NS_SWIFT_NAME(PHPhotosErrorLibraryVolumeOffline) API_DEPRECATED_WITH_REPLACEMENT("PHPhotosErrorLibraryVolumeOffline", macos(10.15, 11.0), ios(13, 14), tvos(13, 14)) = PHPhotosErrorLibraryVolumeOffline;
static const NSInteger PHPhotosErrorRelinquishingLibraryBundleToWriterDeprecated NS_SWIFT_NAME(PHPhotosErrorRelinquishingLibraryBundleToWriter) API_DEPRECATED_WITH_REPLACEMENT("PHPhotosErrorRelinquishingLibraryBundleToWriter", macos(10.15, 11.0), ios(13, 14), tvos(13, 14)) = PHPhotosErrorRelinquishingLibraryBundleToWriter;
static const NSInteger PHPhotosErrorSwitchingSystemPhotoLibraryDeprecated NS_SWIFT_NAME(PHPhotosErrorSwitchingSystemPhotoLibrary) API_DEPRECATED_WITH_REPLACEMENT("PHPhotosErrorSwitchingSystemPhotoLibrary", macos(10.15, 11.0), ios(13, 14), tvos(13, 14)) = PHPhotosErrorSwitchingSystemPhotoLibrary;
#endif

API_AVAILABLE_END
