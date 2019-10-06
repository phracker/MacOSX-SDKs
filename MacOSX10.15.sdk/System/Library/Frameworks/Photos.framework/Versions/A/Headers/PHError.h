//
//  PHError.h
//  Photos
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

API_AVAILABLE_BEGIN(macos(10.15), ios(13), tvos(13))

OS_EXPORT NSErrorDomain const PHPhotosErrorDomain;

NS_ERROR_ENUM(PHPhotosErrorDomain) {
    PHPhotosErrorInvalid = -1,
    PHPhotosErrorUserCancelled = 3072,
    PHPhotosErrorLibraryVolumeOffline = 3114,
    PHPhotosErrorRelinquishingLibraryBundleToWriter = 3142,
    PHPhotosErrorSwitchingSystemPhotoLibrary = 3143,
};

API_AVAILABLE_END
