//
//  LinkPresentation
//  Copyright © 2015-2023 Apple Inc. All rights reserved.
//

#import <LinkPresentation/LPFoundation.h>

/// The domain for Link Presentation errors.
LP_EXTERN NSErrorDomain const LPErrorDomain API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0));

typedef NS_ERROR_ENUM(LPErrorDomain, LPErrorCode) {
/// An unknown error.
    LPErrorUnknown = 1,

/// An error indicating that a metadata fetch failed.
    LPErrorMetadataFetchFailed,

/// An error indicating that the metadata fetch was canceled by the client.
    LPErrorMetadataFetchCancelled,

/// An error indicating that the metadata fetch took longer than allowed.
    LPErrorMetadataFetchTimedOut,

/// An error indicating that the metadata fetch was not allowed due to system policies.
    LPErrorMetadataFetchNotAllowed API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0))
} API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0));
