//
//  QLThumbnailErrors.h
//  Quick Look Thumbnailing
//
//  Copyright (c) 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuickLookThumbnailing/QLThumbnailingBase.h>

QLT_EXPORT extern NSErrorDomain const QLThumbnailErrorDomain API_AVAILABLE(macos(10.15), ios(13.0));

typedef NS_ERROR_ENUM(QLThumbnailErrorDomain, QLThumbnailError) {
    QLThumbnailErrorGenerationFailed,
    QLThumbnailErrorSavingToURLFailed,
    QLThumbnailErrorNoCachedThumbnail,
    QLThumbnailErrorNoCloudThumbnail,
    QLThumbnailErrorRequestInvalid,
    QLThumbnailErrorRequestCancelled,
} API_AVAILABLE(macos(10.15), ios(13.0));
