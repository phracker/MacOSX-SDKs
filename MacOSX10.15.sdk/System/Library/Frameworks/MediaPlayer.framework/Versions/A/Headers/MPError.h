//
//  MPError.h
//  MediaPlayer
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

MP_EXTERN NSString * const MPErrorDomain MP_API(ios(9.3), macos(10.12.2)) MP_PROHIBITED(watchos);

// error codes for the MPErrorDomain
typedef NS_ENUM(NSInteger, MPErrorCode) {
    MPErrorUnknown,
    MPErrorPermissionDenied,                        // the user has not granted permission for this request.
    MPErrorCloudServiceCapabilityMissing,           // the user has not enabled this capability
    MPErrorNetworkConnectionFailed,                 // the device could not connect to the network
    MPErrorNotFound,                                // the id could not be found in the current storefront
    MPErrorNotSupported,                            // the request is not supported (ex: trying to add items to a smart playlist)
    MPErrorCancelled MP_API(ios(10.1)),             // the request was cancelled before it could complete
    MPErrorRequestTimedOut MP_API(ios(10.3)),
} MP_API(ios(9.3), macos(10.14.2)) MP_PROHIBITED(watchos);

NS_ASSUME_NONNULL_END
