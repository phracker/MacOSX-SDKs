//
//  MPError.h
//  MediaPlayer
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

MP_EXTERN NSString * const MPErrorDomain MP_API(ios(9.3), tvos(9.0), watchos(5.0), macos(10.12.2));

// error codes for the MPErrorDomain
typedef NS_ENUM(NSInteger, MPErrorCode) {
    MPErrorUnknown                              = 0,
    // the user has not granted permission for this request.
    MPErrorPermissionDenied                     = 1,
    // the user has not enabled this capability
    MPErrorCloudServiceCapabilityMissing        = 2,
    // the device could not connect to the network
    MPErrorNetworkConnectionFailed              = 3,
    // the id could not be found in the current storefront
    MPErrorNotFound                             = 4,
    // the request is not supported (ex: trying to add items to a smart playlist)
    MPErrorNotSupported                         = 5,
    // the request was cancelled before it could complete
    MPErrorCancelled            MP_API(ios(10.1), tvos(10.1), watchos(5.0), macos(10.14.2))     = 6,
    MPErrorRequestTimedOut      MP_API(ios(10.3), tvos(10.3), watchos(5.0), macos(10.14.2))     = 7,
} MP_API(ios(9.3), tvos(9.0), watchos(5.0), macos(10.14.2));

NS_ASSUME_NONNULL_END
