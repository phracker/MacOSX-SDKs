//
//  MPError.h
//  MediaPlayer
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>

NS_ASSUME_NONNULL_BEGIN

MP_EXTERN NSString * const MPErrorDomain NS_AVAILABLE(10_12_2, 9_3);

// error codes for the MPErrorDomain
typedef NS_ENUM(NSInteger, MPErrorCode) {
    MPErrorUnknown,
    MPErrorPermissionDenied,                        // the user has not granted permission for this request.
    MPErrorCloudServiceCapabilityMissing,           // the user has not enabled this capability
    MPErrorNetworkConnectionFailed,                 // the device could not connect to the network
    MPErrorNotFound,                                // the id could not be found in the current storefront
    MPErrorNotSupported,                            // the request is not supported (ex: trying to add items to a smart playlist)
    MPErrorCancelled NS_ENUM_AVAILABLE_IOS(10_1),   // the request was cancelled before it could complete
} NS_ENUM_AVAILABLE_IOS(9_3);

NS_ASSUME_NONNULL_END
