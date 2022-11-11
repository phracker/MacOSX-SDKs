//
//  LinkPresentation
//  Copyright © 2015-2019 Apple Inc. All rights reserved.
//

#import <LinkPresentation/LPFoundation.h>

/** LPErrorDomain is used to indicate a LinkPresentation error. */
LP_EXTERN NSErrorDomain const LPErrorDomain API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0));

/** Constants used by NSError to indicate errors in the LinkPresentation domain. */
typedef NS_ERROR_ENUM(LPErrorDomain, LPErrorCode) {
    /** LPErrorUnknown indicates that an unknown error occurred. */
    LPErrorUnknown = 1,

    /** LPErrorMetadataFetchFailed indicates that a metadata fetch failed.
     This can be due to network conditions, server availability, or any number of other causes. */
    LPErrorMetadataFetchFailed,

    /** LPErrorMetadataFetchCancelled indicates that the metadata fetch was cancelled by the client. */
    LPErrorMetadataFetchCancelled,

    /** LPErrorMetadataFetchTimedOut indicates that the metadata fetch took longer than allowed. */
    LPErrorMetadataFetchTimedOut
} API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0));
