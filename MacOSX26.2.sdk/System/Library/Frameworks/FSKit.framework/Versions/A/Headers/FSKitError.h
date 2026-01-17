//
//  Copyright (c) 2024 Apple Inc.  All rights reserved.
//
//  FSKitError.h
//  FSKit
//

#import <Foundation/Foundation.h>
#import <FSKit/FSKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// An error domain for FSKit errors.
///
/// See <doc://com.apple.documentation/documentation/Foundation/NSError> for more information on error domains.
FSKIT_API_AVAILABILITY_V1
FOUNDATION_EXPORT NSErrorDomain const FSKitErrorDomain;

/// A code that indicates a specific FSKit error.
typedef NS_ERROR_ENUM(FSKitErrorDomain, FSErrorCode) {
    /// The module failed to load.
    FSErrorModuleLoadFailed          = 4500,

    /// FSKit didn't recognize the resource, and probing failed to find a match.
    FSErrorResourceUnrecognized      = 4501,

    /// The resource is damaged.
    ///
    /// This error indicates the resource needs a repair operation, or that a repair operation failed.
    /// > Note: The status in this error applies to the resource. A failing repair operation reports a more specific error status.
    FSErrorResourceDamaged           = 4502,

    /// FSKit recognizes the resource, but the resource isn't usable.
    ///
    /// For example, this error occurs when a resource uses a file system's internal feature flags.
    /// If the only modules that support the file system don't support those feature flags, this code indicates an unusable resource.
    /// The error tells the person using the module why the resource isn't usable.
    FSErrorResourceUnusable          = 4503,

    /// An operation is in progress.
    FSErrorStatusOperationInProgress = 4504,

    /// An operation is paused.
    FSErrorStatusOperationPaused     = 4505,

    /// While enumerating a directory, the given cookie didn't resolve to a valid directory entry.
    FSErrorInvalidDirectoryCookie    = 4506,
};

NS_ASSUME_NONNULL_END
